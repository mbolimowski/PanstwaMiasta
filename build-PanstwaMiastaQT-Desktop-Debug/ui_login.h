/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QPushButton *connectButton;
    QLabel *portLabel;
    QLabel *ipAdressLabel;
    QTextEdit *userNameTextEdit;
    QTextEdit *portTextEdit;
    QTextEdit *ipAdressTextEdit;
    QLabel *userNameLabel;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(281, 400);
        connectButton = new QPushButton(Login);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setGeometry(QRect(50, 320, 181, 51));
        portLabel = new QLabel(Login);
        portLabel->setObjectName(QString::fromUtf8("portLabel"));
        portLabel->setGeometry(QRect(0, 200, 281, 51));
        portLabel->setLayoutDirection(Qt::LeftToRight);
        portLabel->setAlignment(Qt::AlignCenter);
        ipAdressLabel = new QLabel(Login);
        ipAdressLabel->setObjectName(QString::fromUtf8("ipAdressLabel"));
        ipAdressLabel->setGeometry(QRect(0, 110, 281, 51));
        ipAdressLabel->setAlignment(Qt::AlignCenter);
        userNameTextEdit = new QTextEdit(Login);
        userNameTextEdit->setObjectName(QString::fromUtf8("userNameTextEdit"));
        userNameTextEdit->setGeometry(QRect(50, 160, 181, 41));
        portTextEdit = new QTextEdit(Login);
        portTextEdit->setObjectName(QString::fromUtf8("portTextEdit"));
        portTextEdit->setGeometry(QRect(50, 70, 181, 41));
        ipAdressTextEdit = new QTextEdit(Login);
        ipAdressTextEdit->setObjectName(QString::fromUtf8("ipAdressTextEdit"));
        ipAdressTextEdit->setGeometry(QRect(50, 250, 181, 41));
        userNameLabel = new QLabel(Login);
        userNameLabel->setObjectName(QString::fromUtf8("userNameLabel"));
        userNameLabel->setGeometry(QRect(0, 20, 281, 51));
        userNameLabel->setLayoutDirection(Qt::LeftToRight);
        userNameLabel->setAutoFillBackground(false);
        userNameLabel->setAlignment(Qt::AlignCenter);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Dialog", nullptr));
        connectButton->setText(QCoreApplication::translate("Login", "CONNECT", nullptr));
        portLabel->setText(QCoreApplication::translate("Login", "PORT", nullptr));
        ipAdressLabel->setText(QCoreApplication::translate("Login", "IP ADRESS", nullptr));
        userNameLabel->setText(QCoreApplication::translate("Login", "USER NAME", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
