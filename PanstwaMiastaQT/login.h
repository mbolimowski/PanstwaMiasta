#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    QString getPort();
    QString getUsername();
    QString getIpAddr();

    void setPort(QString port);
    void setUsername(QString username);
    void setIpAddr(QString ipAddr);

    QPushButton * getConnectButton();

   int readUsername();
   int setUsername();
private:
    Ui::Login *ui;
};

#endif // LOGIN_H
