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
            QMessageBox::critical(this, "Error", "Connection failed!");
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
    QMessageBox::critical(this, "Error", "Disconnected!");
    login->show();
    gamemain->hide();
}

void Application::readyRead()
{

}

void Application::closeAll()
{
    login->close();
    this->close();
    gamemain->close();
}

