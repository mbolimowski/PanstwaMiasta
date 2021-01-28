#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <error.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <unordered_set>
#include <list>
#include <iostream>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <chrono>
#include <thread>
#include <map>


class Client;
int servFd;
int epollFd;
bool answerMode = false;
std::unordered_set<Client*> clients;
int numberOfResponses = 0;
int rounds = 0;
std::vector<int> categories;
std::map<std::string, int> answersVotes;


void ctrl_c(int);
void sendToAllBut(int fd, char * buffer, int count);
void sendToAll(char * buffer, int count);
uint16_t readPort(char * txt);
void setReuseAddr(int sock);
void startOptions(Client * client);
void sendPlayersInfo();
char randomNumber();
void gameInfo(char * message);
void startRound();
void readAnswers(Client * client, char * answers, int msglen);
void cleanAnswers(Client * client);
void allAnswers(Client * omittedClient, char * buffer);
void sendAllAnswers();
void readVotes(char * message, int msglen);
void calcClientsPoints();
void cleanBeforeNextRound();

struct Handler {
    virtual ~Handler(){}
    virtual void handleEvent(uint32_t events) = 0;
};
class Client : public Handler {
    int _fd;
    char name[255];
    int points;
    std::vector<std::string> * answers;
    struct Buffer {
        Buffer() {data = (char*) malloc(len);}
        Buffer(const char* srcData, ssize_t srcLen) : len(srcLen) {data = (char*) malloc(len); memcpy(data, srcData, len);}
        ~Buffer() {free(data);}
        Buffer(const Buffer&) = delete;
        void doube() {len*=2; data = (char*) realloc(data, len);}
        ssize_t remaining() {return len - pos;}
        char * dataPos() {return data + pos;}
        char * data;
        ssize_t len = 32;
        ssize_t pos = 0;
    };
    Buffer readBuffer;
    std::list<Buffer> dataToWrite;
    void waitForWrite(bool epollout) {
        epoll_event ee {EPOLLIN|EPOLLRDHUP|(epollout?EPOLLOUT:0), {.ptr=this}};
        epoll_ctl(epollFd, EPOLL_CTL_MOD, _fd, &ee);
    }
public:
    Client(int fd) : _fd(fd) {
        epoll_event ee {EPOLLIN|EPOLLRDHUP, {.ptr=this}};
        epoll_ctl(epollFd, EPOLL_CTL_ADD, _fd, &ee);
        memset(name,0,255);
        points = 0;
        answers = new std::vector<std::string>();
    }
    virtual ~Client(){
        epoll_ctl(epollFd, EPOLL_CTL_DEL, _fd, nullptr);
        shutdown(_fd, SHUT_RDWR);
        close(_fd);
    }
    int fd() const {return _fd;}
    char * getName() {return name;}
    int getPoints() {return points;}
    void addPoints(int pt) {points+=pt;}
    std::vector<std::string> * getAnswers(){return answers;}
    virtual void handleEvent(uint32_t events) override {
        if(events & EPOLLIN) {
            ssize_t count = read(_fd, readBuffer.dataPos(), readBuffer.remaining());
            if(count <= 0)
                events |= EPOLLERR;
            else {
                readBuffer.pos += count;
                char * eol = (char*) memchr(readBuffer.data, '\n', readBuffer.pos);
                if(eol == nullptr) {
                    if(0 == readBuffer.remaining())
                        readBuffer.doube();
                } else {
                    do {
                        auto thismsglen = eol - readBuffer.data + 1;
                        
                        if(readBuffer.data[0] == 'n')
                        {
                            strncat(name, readBuffer.data + 1, thismsglen -2);
                            std::cout << name << std::endl;
                            sendPlayersInfo();
                        }
                        if(readBuffer.data[0] == 's')
                        {
                            numberOfResponses = 0;
                            cleanAnswers(this);
                            categories.clear();
                            categories.shrink_to_fit();
                            answerMode = true;
                            gameInfo(readBuffer.data);
                            startRound();
                        }
                        if(readBuffer.data[0] == 'z')
                        {
                            sendToAll(readBuffer.data, thismsglen);
                        }
                        if(readBuffer.data[0] == 'o')
                        {
                            std::cout << readBuffer.data<<std::endl;
                            readAnswers(this, readBuffer.data, thismsglen);
                            numberOfResponses ++;
                            std::cout << "numberOfResponses" << numberOfResponses<<std::endl;
                            if(numberOfResponses == (int)clients.size())
                            {
                                sendAllAnswers();
                                answerMode = false;
                                numberOfResponses = 0;
                            }
                        }
                        if(readBuffer.data[0] == 'g')
                        {   
                            readVotes(readBuffer.data, thismsglen);
                            numberOfResponses++;
                            if(numberOfResponses == (int)clients.size())
                            {
                                calcClientsPoints();    
                                cleanBeforeNextRound();
                                startRound();
                                sendPlayersInfo();
                                
                            }

                        }
                        auto nextmsgslen =  readBuffer.pos - thismsglen;
                        memmove(readBuffer.data, eol+1, nextmsgslen);
                        readBuffer.pos = nextmsgslen;
                    } while((eol = (char*) memchr(readBuffer.data, '\n', readBuffer.pos)));
                }
            }
        }
        if(events & EPOLLOUT) {
            do {
                int remaining = dataToWrite.front().remaining();
                int sent = send(_fd, dataToWrite.front().data+dataToWrite.front().pos, remaining, MSG_DONTWAIT);
                if(sent == remaining) {
                    dataToWrite.pop_front();
                    if(0 == dataToWrite.size()) {
                        waitForWrite(false);
                        break;
                    }
                    continue;
                } else if(sent == -1) {
                    if(errno != EWOULDBLOCK && errno != EAGAIN)
                        events |= EPOLLERR;
                } else
                    dataToWrite.front().pos += sent;
            } while(false);
        }
        if(events & ~(EPOLLIN|EPOLLOUT)) {
            remove();
        }
    }
    void write(char * buffer, int count) {
        if(dataToWrite.size() != 0) {
            dataToWrite.emplace_back(buffer, count);
            return;
        }
        int sent = send(_fd, buffer, count, MSG_DONTWAIT);
        if(sent == count)
            return;
        if(sent == -1) {
            if(errno != EWOULDBLOCK && errno != EAGAIN){
                remove();
                return;
            }
            dataToWrite.emplace_back(buffer, count);
        } else {
            dataToWrite.emplace_back(buffer+sent, count-sent);
        }
        waitForWrite(true);
    }
    void remove() {
        printf("Removing client %d\n", _fd);
        clients.erase(this);
        delete this;
    }
};

class : Handler {
    public:
    virtual void handleEvent(uint32_t events) override {
        if(events & EPOLLIN){
            sockaddr_in clientAddr{};
            socklen_t clientAddrSize = sizeof(clientAddr);
            auto clientFd = accept(servFd, (sockaddr*) &clientAddr, &clientAddrSize);
            if(clientFd == -1) error(1, errno, "accept failed");
            printf("New connection from: %s:%hu (fd: %d)\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), clientFd);
            Client * newClient = new Client(clientFd); 
            clients.insert(newClient);
            startOptions(newClient);
        }
        if(events & ~EPOLLIN){
            error(0, errno, "Event %x on server socket", events);
            ctrl_c(SIGINT);
        }
    }
} servHandler;

int main(int argc, char ** argv){
    if(argc != 2) error(1, 0, "Need 1 argument - port");
    auto port = readPort(argv[1]);
    servFd = socket(AF_INET, SOCK_STREAM, 0);
    if(servFd == -1) error(1, errno, "Socket failed");
    signal(SIGINT, ctrl_c);
    signal(SIGPIPE, SIG_IGN);
    setReuseAddr(servFd);
    sockaddr_in serverAddr{.sin_family=AF_INET, .sin_port=htons((short)port), .sin_addr={INADDR_ANY}};
    int res = bind(servFd, (sockaddr*) &serverAddr, sizeof(serverAddr));
    if(res) error(1, errno, "Bind failed");
    res = listen(servFd, 1);
    if(res) error(1, errno, "Listen failed");
    epollFd = epoll_create1(0);
    epoll_event ee {EPOLLIN, {.ptr=&servHandler}};
    epoll_ctl(epollFd, EPOLL_CTL_ADD, servFd, &ee);
    while(true){
        if(-1 == epoll_wait(epollFd, &ee, 1, -1) && errno!=EINTR) {
            error(0,errno,"Epoll_wait failed");
            ctrl_c(SIGINT);
        }
        ((Handler*)ee.data.ptr)->handleEvent(ee.events);
    }
}

uint16_t readPort(char * txt){
    char * ptr;
    auto port = strtol(txt, &ptr, 10);
    if(*ptr!=0 || port<1 || (port>((1<<16)-1))) error(1,0,"illegal argument %s", txt);
    return port;
}

void setReuseAddr(int sock){
    const int one = 1;
    int res = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    if(res) error(1,errno, "setsockopt failed");
}

void ctrl_c(int){
    for(Client * client : clients)
        delete client;
    close(servFd);
    printf("Closing server\n");
    exit(0);
}

void sendToAllBut(int fd, char * buffer, int count){
    auto it = clients.begin();
    while(it!=clients.end()){
        Client * client = *it;
        it++;
        if(client->fd()!=fd)
            client->write(buffer, count);
    }
}


void sendToAll(char * buffer, int count){
    for(Client * client : clients)
    {
        client->write(buffer, count);
    }
}


void startOptions(Client * newClient)
{
    //sprawdzam ktora osoba jest pierwsza aby odblokowac lub zablokowac jej checkboxy do wyboru kategorii
    int lowest_fd = 1000000;
    for(Client * client : clients)
    {
        if(client->fd() < lowest_fd && client->fd() != servFd)
        {
            lowest_fd = client->fd();
        }
    }
    //f - pierwszy client moze on ustawiac co chce przed rozpoczeciem rozgrywki
    char message[255];
    memset(message, 0 , 255);
    if(newClient->fd() == lowest_fd)
    {
    strcpy(message, "1\n");
    }
    else{
    strcpy(message, "2\n");
    }
    write(newClient->fd(), message, strlen(message));
}


void sendPlayersInfo()
{
    char message[255];
    memset(message,0,255);
    strcpy(message, "i\0");
    for(Client * client : clients)
    {
        std::string s = std::to_string(client->fd());
        char const * fdchar = s.c_str();
        strncat(message, fdchar, strlen(fdchar));
        strncat(message, client->getName(), strlen(client->getName()));
        std::string ps = std::to_string(client->getPoints());
        char const * pointschar = ps.c_str();
        strcat(message, " \0");
        strncat(message, pointschar, strlen(pointschar));
        strcat(message, ",");
    }
    std::cout << message <<std::endl;
    strcat(message, "\n");
    sendToAll(message, strlen(message));
}


char randomNumber()
{
    srand(time(NULL));
    char number = rand() % 26 + 65;
    return number;
}



void gameInfo(char * message)
{
    std::cout<<message<<std::endl;
    bool ifRounds = true;
    for(int i=1;i<(int)strlen(message);i++)
    {
        if(message[i] == ',' && ifRounds)
        {
            char charRounds[255];
            memset(charRounds,0,255);
            strncpy(charRounds, message+1, i-1);
            rounds = atoi(charRounds) + 1; 
            ifRounds = false;
            continue;
        }
        if(message[i] == ',' && !ifRounds)
        {
            categories.push_back(message[i-1]%48);
        }
    }
}



void startRound()
{

    char message[255];
    memset(message, 0, 255);
    strcpy(message, "s\0");
    std::string tmp = std::to_string(--rounds);
    char const * charRounds = tmp.c_str();
    strncat(message, charRounds, strlen(charRounds));
    char tmp2[3] = {',' , randomNumber(), ','};
    strncat(message, tmp2, 3);
    memset(tmp2, 0 , 3);
    for(int i = 0; i < (int)categories.size();i++)
    {
        char tmp3[2] = {(char)(categories[i]+48), ','};
        strncat(message,tmp3,3);
        memset(tmp3,0,2);
    }
    strcat(message,"\n");
    std::cout << message << std::endl;
    sendToAll(message, strlen(message));
}



void readAnswers(Client * client, char * answers, int msglen)
{
    int pos = 1;
    for(int i=1;i<msglen;i++)
    {
        if(answers[i] == ',')
        {
            char answer[31];
            memset(answer,0,31);
            strncpy(answer, answers+pos, i-pos);
            std::string strAnswer(answer);
            client->getAnswers()->push_back(strAnswer);
            pos = i+1;
        }
    }
}

void cleanAnswers(Client * client)
{
    client->getAnswers()->clear();
    client->getAnswers()->shrink_to_fit();
}

//zwraca polaczone odpowiedzi wszystkich clientow z wyjatkiem omittedclient
void allAnswers(Client * omittedClient, char * buffer)
{
    strcpy(buffer, "o\0");
    for(Client * client : clients)
    {
        if(client->fd() != omittedClient->fd())
        {
        for(auto it = client->getAnswers()->begin(); it != client->getAnswers()->end(); it++)
        {
            strncat(buffer, (*it).c_str() , strlen((*it).c_str()));
            strcat(buffer,",\0");
        }
        }
    }
    strcat(buffer,"\n");
    std::cout <<"AllAnswers: " <<  buffer<< std::endl;
}

//wysyla wszystkim odpowiednie 
void sendAllAnswers()
{
    for(Client * client : clients)
    {
        char message[512];
        memset(message, 0, 512); 
        allAnswers(client, message);
        client->write(message, strlen(message));
        std::cout << "Wyslano do " << client->fd() << " " << message << std::endl;
    }
}


void readVotes(char * message, int msglen)
{
    int pos = 1;
    for(int i=1;i<msglen;i++)
    {
        if(message[i] == ',')
        {
            char tmp[31];
            memset(tmp,0,31);
            strncpy(tmp, message+pos, i-pos);
            std::cout << "vote: " << tmp<<std::endl;
            std::string strVote(tmp);
            if(answersVotes.find(strVote) == answersVotes.end())
            {
                answersVotes.insert(std::pair<std::string, int>(strVote,1));
            }
            else{
                answersVotes[strVote]++; 
            }
            pos = i+1;
        }
    }
}



void calcClientsPoints()
{
    for(Client * client : clients)
    {
        int halfClients = 0;
        if((int)clients.size() % 2 == 0)
        {
            halfClients = (int)clients.size()/2;
        }
        else{
            halfClients = ((int)clients.size()-1)/2;
        }
        for(int i=0;i<(int)client->getAnswers()->size();i++)
        {
            std::string answer = (*client->getAnswers())[i];
            if(answersVotes.find(answer) != answersVotes.end())
            {
                if(answersVotes[answer] >= halfClients)
                {
                    int answerRepeat = 0;
                    for(Client * tmpClient : clients)
                    {
                        if(tmpClient->fd() != client->fd())
                        {
                        
                        for(int i=0;i<(int)tmpClient->getAnswers()->size();i++)
                        {
                            if(answer == (*tmpClient->getAnswers())[i])
                            {
                                answerRepeat++;
                            }
                        }
                        }
                    }
                    if(answerRepeat == 0)
                    {
                        client->addPoints(10);
                    }
                    else{
                        client->addPoints(5);
                    }
                }
            }
        }
    }
}



void cleanBeforeNextRound()
{
    numberOfResponses = 0;
    answerMode = true;
    for(Client * client : clients)
    {
        cleanAnswers(client);
    }
    answersVotes.clear();
}