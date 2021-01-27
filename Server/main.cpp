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

class Client;
int servFd;
int epollFd;
bool gameStarted;
std::unordered_set<Client*> clients;
void ctrl_c(int);
void sendToAllBut(int fd, char * buffer, int count);
void sendToAll(char * buffer, int count);
uint16_t readPort(char * txt);
void setReuseAddr(int sock);
void startOptions(Client * client);
void sendPlayersInfo();



struct Handler {
    virtual ~Handler(){}
    virtual void handleEvent(uint32_t events) = 0;
};
class Client : public Handler {
    int _fd;
    char name[255];
    int points;
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
    }
    virtual ~Client(){
        epoll_ctl(epollFd, EPOLL_CTL_DEL, _fd, nullptr);
        shutdown(_fd, SHUT_RDWR);
        close(_fd);
    }
    int fd() const {return _fd;}
    char * getName() {return name;}
    int getPoints() {return points;}
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
                        //sendToAllBut(_fd, readBuffer.data, thismsglen);
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
            if(!gameStarted)
            startOptions(newClient);
        }
        if(events & ~EPOLLIN){
            error(0, errno, "Event %x on server socket", events);
            ctrl_c(SIGINT);
        }
    }
} servHandler;

int main(int argc, char ** argv){
    gameStarted = false;
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