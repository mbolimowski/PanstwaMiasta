#include "application.h"


Application::Application(QWidget * parent) : QMainWindow(parent)
{
    login = new Login(this);
    gamemain = new gameMain(this);
    gamemain->hide();
    login->show();
    login->setIpAddr("localhost");
    login->setPort("5000");
    if(login->readUsername() == -1)
    {
        closeAll();
        delete this;
    }
    connect(login->getConnectButton(), &QPushButton::clicked, this, &Application::connectButtonHit);
    connect(gamemain->getStartButton(), &QPushButton::clicked, this, &Application::startButtonHit);
}


Application::~Application()
{
    delete sock;
    delete login;
    delete gamemain;
    delete connectionTimeoutTimer;
}

void Application::sendMessage(QString message){
    sock->write(message.toUtf8(), message.toUtf8().length());
}


void Application::connectButtonHit()
{
    sock = new QTcpSocket();
    connectionTimeoutTimer = new QTimer();
    connectionTimeoutTimer->setSingleShot(true);

    connect(connectionTimeoutTimer, &QTimer::timeout, [&]{
            connectionTimeoutTimer->deleteLater();
            QMessageBox::critical(login, "Błąd", "Nie udało się połączyć!");
        });
    connect(sock, &QTcpSocket::connected, this, &Application::connected);
    connect(sock, &QTcpSocket::disconnected, this, &Application::disconnected);
    connect(sock, &QTcpSocket::readyRead, this, &Application::readyRead);
    sock->connectToHost(login->getIpAddr(), login->getPort().toInt());
    connectionTimeoutTimer->start(4000);
    if(login->setUsername() == -1)
    {
        closeAll();
        delete this;
    }

}

void Application::startButtonHit(){
    QString message;
    if(gamemain->isRoundsCorrect() == 1 && gamemain->isCheckedAtLeastOneBox() == 1){
        message = gamemain->getRounds() + ",";
        QStringList checkBoxesList = gamemain->getCheckedBoxes();
        for(int i = 0; i < checkBoxesList.size(); i++){
            message += checkBoxesList[i] + ",";
        }
        sendMessage("s" + message + "\n");
    }
}



void Application::connected()
{
    connectionTimeoutTimer->stop();
    connectionTimeoutTimer->deleteLater();
    login->hide();
    gamemain->show();
    sendMessage("n" + login->getUsername() + "\n");
}


void Application::disconnected()
{
    sock->close();
    QMessageBox::critical(this, "Błąd", "Rozłączono z serwerem!");
    login->show();
    gamemain->hide();
}

void Application::readyRead()
{
    QString message = QString(sock->readAll());
    std::vector<QString> actions;
    int counter = 0;
    qDebug() << message;
    for(int i=0;i<(int)message.length();i++)
    {
        if(message[i] == '\n')
                {
                    QString action = message.mid(counter, i-counter);
                    counter = i+1;
                    actions.push_back(action);
                }
    }
    for(auto it = actions.begin();it != actions.end();++it)
    {
        QString action = (*it);
        if(action[0] == '1')
        {
            gamemain->setCategoriesDisabled();
            QMessageBox mb;
            mb.information(gamemain, "Informacja", "Zostałeś właścicielem! Oznacza to, że możesz wybrać kategorie dostępne w następnej grze oraz ilość rund. Kliknij przycisk start gdy będziesz gotowy!");

        }
        if(action[0] == '2')
        {
            gamemain->setCheckboxesDisabled();
            gamemain->setCategoriesDisabled();
            gamemain->setStartButtonDisabled();
            gamemain->setEditRoundsTextEditDisabled();
            QMessageBox mb;
            mb.information(gamemain, "Informacja", "Poczekaj, aż właściciel poczekalni rozpocznie grę!");
        }
        qDebug() << action;
        if(action[0] == 'i')
        {
            gamemain->clearPlayerAndPointsListWidget();
            QString name;
            QString points;

            int whereSpace = -1;
            int whereComma = -1;

            action = action.mid(1, action.length()-1);
            for(int i = 0; i < action.length(); i++){
                if(action[i] == ' '){
                    whereSpace = i;
                    name = action.mid(whereComma +1, i - whereComma - 1);
                    gamemain->addPlayerName(name);
                }
                if(action[i] == ','){
                    whereComma = i;
                    points = action.mid(whereSpace + 1, i - whereSpace - 1);
                    gamemain->addPoints(points);
                }
            }
        }
        if(action[0] == 's'){
            action = action.mid(1, action.length()-1);
            QString rounds;
            QString letter;
            int counter = 0;

            do{
                counter++;
            }while(action[counter] == ',');

            rounds = action.mid(0, counter);
            action = action.mid(counter + 1, action.length() - counter -1);

            letter = action.mid(0, 1);
            action = action.mid(2, action.length() - 2);

            gamemain->setLetter(letter);
            gamemain->setRounds(rounds);

            QString tmp;

            for(int i = 0; i < action.length(); i++){
                if(action[i] == ','){
                    tmp = action[i-1];
                    if(tmp == "1") gamemain->setCountryTextEditEnabled();
                    else if(tmp == "2") gamemain->setCityTextEditEnabled();
                    else if(tmp == "3") gamemain->setAnimalTextEditEnabled();
                    else if(tmp == "4") gamemain->setPlantTextEditEnabled();
                    else if(tmp == "5") gamemain->setNameTextEditEnabled();
                    else if(tmp == "6") gamemain->setWaterTextEditEnabled();
                    else if(tmp == "7") gamemain->setThingTextEditEnabled();
                    else if(tmp == "8") gamemain->setFamousPersonTextEditEnabled();
                }
            }
        }
    }
}

void Application::closeAll()
{
    login->close();
    this->close();
    gamemain->close();
}

