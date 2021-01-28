#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QPushButton>
#include <QTimer>
#include <QMessageBox>
#include "gamemain.h"
#include "login.h"
#include "vote.h"


class Application : public QMainWindow
{
    Q_OBJECT
private:
    vote * voteWindow;
    gameMain * gamemain;
    Login * login;
    QTcpSocket * sock;
    QTimer * connectionTimeoutTimer;
    QTimer * roundTimer;
    int roundSeconds;
public:
    explicit Application(QWidget * parent = nullptr);
    ~Application();
    void connectButtonHit();

    void startButtonHit();

    void sendAnswersButtonHit();

    void voteButtonHit();

    void connected();
    void disconnected();
    void readyRead();

    void sendMessage(QString message);

    void closeAll();

    void updateTime();
};

#endif // APPLICATION_H
