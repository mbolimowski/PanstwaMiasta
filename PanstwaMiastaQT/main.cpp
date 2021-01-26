#include "application.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Application * app = new Application();
    app->hide();
    return a.exec();
}
