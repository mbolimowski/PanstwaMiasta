#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>

#include "gamemain.h"
#include "login.h"


class Application : public QMainWindow
{
    Q_OBJECT
private:
    gameMain * gamemain;
    Login * login;
public:
    explicit Application(QWidget * parent = nullptr);
};

#endif // APPLICATION_H
