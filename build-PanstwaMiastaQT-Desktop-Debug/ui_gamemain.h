/********************************************************************************
** Form generated from reading UI file 'gamemain.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEMAIN_H
#define UI_GAMEMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_gameMain
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QTextEdit *textEdit_3;
    QTextEdit *textEdit_4;
    QTextEdit *textEdit_5;
    QTextEdit *textEdit_6;
    QTextEdit *textEdit_7;
    QTextEdit *textEdit_8;
    QTextEdit *textEdit_9;
    QTextEdit *textEdit_10;

    void setupUi(QDialog *gameMain)
    {
        if (gameMain->objectName().isEmpty())
            gameMain->setObjectName(QString::fromUtf8("gameMain"));
        gameMain->resize(834, 722);
        label = new QLabel(gameMain);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(160, 370, 67, 17));
        label_2 = new QLabel(gameMain);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(160, 420, 67, 17));
        label_3 = new QLabel(gameMain);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(190, 440, 67, 17));
        label_4 = new QLabel(gameMain);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(190, 500, 67, 17));
        label_5 = new QLabel(gameMain);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(170, 590, 67, 17));
        label_6 = new QLabel(gameMain);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(160, 630, 67, 17));
        label_7 = new QLabel(gameMain);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(180, 670, 67, 17));
        label_8 = new QLabel(gameMain);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(200, 560, 67, 17));
        label_9 = new QLabel(gameMain);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(230, 520, 67, 17));
        label_10 = new QLabel(gameMain);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(230, 470, 67, 17));
        textEdit = new QTextEdit(gameMain);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 520, 104, 41));
        textEdit_2 = new QTextEdit(gameMain);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(20, 100, 130, 40));
        textEdit_3 = new QTextEdit(gameMain);
        textEdit_3->setObjectName(QString::fromUtf8("textEdit_3"));
        textEdit_3->setGeometry(QRect(20, 380, 104, 41));
        textEdit_4 = new QTextEdit(gameMain);
        textEdit_4->setObjectName(QString::fromUtf8("textEdit_4"));
        textEdit_4->setGeometry(QRect(20, 660, 130, 40));
        textEdit_5 = new QTextEdit(gameMain);
        textEdit_5->setObjectName(QString::fromUtf8("textEdit_5"));
        textEdit_5->setGeometry(QRect(20, 590, 104, 41));
        textEdit_6 = new QTextEdit(gameMain);
        textEdit_6->setObjectName(QString::fromUtf8("textEdit_6"));
        textEdit_6->setGeometry(QRect(20, 450, 104, 41));
        textEdit_7 = new QTextEdit(gameMain);
        textEdit_7->setObjectName(QString::fromUtf8("textEdit_7"));
        textEdit_7->setGeometry(QRect(20, 310, 104, 41));
        textEdit_8 = new QTextEdit(gameMain);
        textEdit_8->setObjectName(QString::fromUtf8("textEdit_8"));
        textEdit_8->setGeometry(QRect(20, 240, 104, 41));
        textEdit_9 = new QTextEdit(gameMain);
        textEdit_9->setObjectName(QString::fromUtf8("textEdit_9"));
        textEdit_9->setGeometry(QRect(20, 170, 130, 40));
        textEdit_10 = new QTextEdit(gameMain);
        textEdit_10->setObjectName(QString::fromUtf8("textEdit_10"));
        textEdit_10->setGeometry(QRect(20, 30, 130, 40));
        textEdit_10->setLineWidth(1);

        retranslateUi(gameMain);

        QMetaObject::connectSlotsByName(gameMain);
    } // setupUi

    void retranslateUi(QDialog *gameMain)
    {
        gameMain->setWindowTitle(QCoreApplication::translate("gameMain", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("gameMain", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("gameMain", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("gameMain", "TextLabel", nullptr));
        label_4->setText(QCoreApplication::translate("gameMain", "TextLabel", nullptr));
        label_5->setText(QCoreApplication::translate("gameMain", "TextLabel", nullptr));
        label_6->setText(QCoreApplication::translate("gameMain", "TextLabel", nullptr));
        label_7->setText(QCoreApplication::translate("gameMain", "TextLabel", nullptr));
        label_8->setText(QCoreApplication::translate("gameMain", "TextLabel", nullptr));
        label_9->setText(QCoreApplication::translate("gameMain", "TextLabel", nullptr));
        label_10->setText(QCoreApplication::translate("gameMain", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gameMain: public Ui_gameMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEMAIN_H
