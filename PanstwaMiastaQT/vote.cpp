#include "vote.h"
#include "ui_vote.h"

vote::vote(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vote)
{
    ui->setupUi(this);
}

vote::~vote()
{
    delete ui;
}


void vote::addToCountryWidgetList(QString country){
    QListWidgetItem * item = new QListWidgetItem;
    item->setText(country);
    item->setCheckState(Qt::Unchecked);
    ui->panstwoListWidget->addItem(country);
}

void vote::addToCityWidgetList(QString city){
    QListWidgetItem * item = new QListWidgetItem;
    item->setText(city);
    item->setCheckState(Qt::Unchecked);
    ui->miastoListWidget->addItem(city);
}

void vote::addToAnimalWidgetList(QString animal){
    QListWidgetItem * item = new QListWidgetItem;
    item->setText(animal);
    item->setCheckState(Qt::Unchecked);
    ui->zwierzeListWidget->addItem(animal);
}

void vote::addToPlantWidgetList(QString plant){
    QListWidgetItem * item = new QListWidgetItem;
    item->setText(plant);
    item->setCheckState(Qt::Unchecked);
    ui->roslinaListWidget->addItem(plant);
}

void vote::addToNameWidgetList(QString name){
    QListWidgetItem * item = new QListWidgetItem;
    item->setText(name);
    item->setCheckState(Qt::Unchecked);
    ui->imieListWidget->addItem(name);
}

void vote::addToWaterWidgetList(QString water){
    QListWidgetItem * item = new QListWidgetItem;
    item->setText(water);
    item->setCheckState(Qt::Unchecked);
    ui->wodyListWidget->addItem(water);
}

void vote::addToThingWidgetList(QString thing){
    QListWidgetItem * item = new QListWidgetItem;
    item->setText(thing);
    item->setCheckState(Qt::Unchecked);
    ui->przedmiotListWidget->addItem(thing);
}

void vote::addToFamousPersonWidgetList(QString famousPerson){
    QListWidgetItem * item = new QListWidgetItem;
    item->setText(famousPerson);
    item->setCheckState(Qt::Unchecked);
    ui->slawnaOsobaListWidget->addItem(famousPerson);
}

void vote::checkPresenceOfElementInListWidget(QString element){

}
