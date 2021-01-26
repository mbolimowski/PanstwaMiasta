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
}


Application::~Application()
{
    delete sock;
    delete login;
    delete gamemain;
    delete connectionTimeoutTimer;
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


void Application::connected()
{
    connectionTimeoutTimer->stop();
    connectionTimeoutTimer->deleteLater();
    login->hide();
    gamemain->show();
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
            QMessageBox mb;
            mb.information(gamemain, "Informacja", "Poczekaj, aż właściciel poczekalni rozpocznie grę!");
        }
        if(action[0] == 'i')
        {

        }

    }
}

void Application::closeAll()
{
    login->close();
    this->close();
    gamemain->close();
}

