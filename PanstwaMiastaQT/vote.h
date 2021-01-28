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

    void addToCountryWidgetList(QString country);

    void addToCityWidgetList(QString city);

    void addToAnimalWidgetList(QString animal);

    void addToPlantWidgetList(QString plant);

    void addToNameWidgetList(QString name);

    void addToWaterWidgetList(QString water);

    void addToThingWidgetList(QString thing);

    void addToFamousPersonWidgetList(QString famousPerson);

    bool checkPresenceOfElementInListWidget(QString element);

    void addElementToList(QString element);

    void clearCountryWidgetList();

    void clearCityWidgetList();

    void clearAnimalWidgetList();

    void clearPlantWidgetList();

    void clearNameWidgetList();

    void clearWaterWidgetList();

    void clearThingWidgetList();

    void clearFamousPersonWidgetList();

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
