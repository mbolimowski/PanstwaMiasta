#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}


QString Login::getPort()
{
    return ui->portTextEdit->toPlainText();
}
QString Login::getUsername()
{
    return ui->nazwaUzytkownikaTextEdit->toPlainText();
}
QString Login::getIpAddr()
{
    return ui->ipAdresTextEdit->toPlainText();
}

void Login::setPort(QString port)
{
    ui->portTextEdit->setText(port);
}

void Login::setUsername(QString username)
{
    ui->nazwaUzytkownikaTextEdit->setText(username);
}

void Login::setIpAddr(QString ipAddr)
{
    ui->ipAdresTextEdit->setText(ipAddr);
}

QPushButton * Login::getConnectButton()
{
    return ui->polaczButton;
}


int Login::readUsername()
{
    QFile file("username.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
            QMessageBox mb;
            mb.critical(this, "Error", "Failed opening file username.txt!");
            return -1;
    }
    QTextStream instream(&file);
    QString username = instream.readLine();
    ui->nazwaUzytkownikaTextEdit->setText(username);
    file.close();
    return 0;
}

int Login::setUsername()
{
    QFile file("username.txt");
    if(!file.open(QIODevice::Truncate|QIODevice::WriteOnly))
    {
        QMessageBox mb;
        mb.critical(this, "Error", "Failed opening file username.txt!");
        return -1;
    }
    file.write(ui->nazwaUzytkownikaTextEdit->toPlainText().toUtf8(), ui->nazwaUzytkownikaTextEdit->toPlainText().toUtf8().size());
    file.close();
    return 0;
}
