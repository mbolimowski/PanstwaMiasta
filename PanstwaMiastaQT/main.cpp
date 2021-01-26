#include "gamemain.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login x;
    x.show();
    gameMain z;
    z.show();

    return a.exec();
}
