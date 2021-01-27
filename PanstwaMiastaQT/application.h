#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QPushButton>
#include <QTimer>
#include <QMessageBox>
#include "gamemain.h"
#include "login.h"


class Application : public QMainWindow
{
    Q_OBJECT
private:
    gameMain * gamemain;
    Login * login;
    QTcpSocket * sock;
    QTimer * connectionTimeoutTimer;
public:
    explicit Application(QWidget * parent = nullptr);
    ~Application();
    void connectButtonHit();

    void startButtonHit();

    void connected();
    void disconnected();
    void readyRead();

    void sendMessage(QString message);

    void closeAll();
};

#endif // APPLICATION_H
