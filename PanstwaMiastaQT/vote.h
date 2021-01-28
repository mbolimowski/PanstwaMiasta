#ifndef VOTE_H
#define VOTE_H

#include <QDialog>
#include <QListWidgetItem>

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

    void checkPresenceOfElementInListWidget(QString element);

private:
    Ui::vote *ui;
};

#endif // VOTE_H
