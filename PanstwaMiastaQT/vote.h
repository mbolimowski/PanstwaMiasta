#ifndef VOTE_H
#define VOTE_H

#include <QDialog>
#include <QListWidgetItem>
#include <QList>
#include <QDebug>

namespace Ui {
class vote;
}

class vote : public QDialog
{
    Q_OBJECT

public:
    explicit vote(QWidget *parent = nullptr);
    ~vote();

    bool checkPresenceOfElementInListWidget(QString element);

    void addElementToList(QString element);

    void clearElementsList();

    void clearAllWidgetLists();

    void addToSpecialWidgetList(QString category);

    QPushButton * getVoteButton();

    QString getVoices();

    QListWidget * getWidget(int whichWidget);


private:

    QList<QString> * itemsInWidgetList;

    Ui::vote *ui;
};

#endif // VOTE_H
