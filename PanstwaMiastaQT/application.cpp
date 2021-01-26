#include "application.h"


Application::Application(QWidget * parent) : QMainWindow(parent)
{
    login = new Login();
    gamemain = new gameMain();
    gamemain->hide();
    login->show();
}


