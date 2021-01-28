#include "vote.h"
#include "ui_vote.h"

vote::vote(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vote)
{
    ui->setupUi(this);
    itemsInWidgetList = new QList<QString>;
}

vote::~vote()
{
    delete ui;
}


void vote::addToCountryWidgetList(QString country){
    if(!checkPresenceOfElementInListWidget(country)){
        QListWidgetItem * item = new QListWidgetItem();
        item->setText(country);
        item->setCheckState(Qt::Unchecked);
        ui->panstwoListWidget->addItem(item);
        addElementToList(country);
    }
}

void vote::addToCityWidgetList(QString city){
    if(!checkPresenceOfElementInListWidget(city)){
        QListWidgetItem * item = new QListWidgetItem();
        item->setText(city);
        item->setCheckState(Qt::Unchecked);
        ui->miastoListWidget->addItem(item);
        addElementToList(city);
    }
}

void vote::addToAnimalWidgetList(QString animal){
    if(!checkPresenceOfElementInListWidget(animal)){
        QListWidgetItem * item = new QListWidgetItem();
        item->setText(animal);
        item->setCheckState(Qt::Unchecked);
        ui->zwierzeListWidget->addItem(item);
        addElementToList(animal);
    }
}

void vote::addToPlantWidgetList(QString plant){
    if(!checkPresenceOfElementInListWidget(plant)){
        QListWidgetItem * item = new QListWidgetItem();
        item->setText(plant);
        item->setCheckState(Qt::Unchecked);
        ui->roslinaListWidget->addItem(item);
        addElementToList(plant);
    }
}

void vote::addToNameWidgetList(QString name){
    if(!checkPresenceOfElementInListWidget(name)){
        QListWidgetItem * item = new QListWidgetItem();
        item->setText(name);
        item->setCheckState(Qt::Unchecked);
        ui->imieListWidget->addItem(item);
        addElementToList(name);
    }
}

void vote::addToWaterWidgetList(QString water){
    if(!checkPresenceOfElementInListWidget(water)){
        QListWidgetItem * item = new QListWidgetItem();
        item->setText(water);
        item->setCheckState(Qt::Unchecked);
        ui->wodyListWidget->addItem(item);
        addElementToList(water);
    }
}

void vote::addToThingWidgetList(QString thing){
    if(!checkPresenceOfElementInListWidget(thing)){
        QListWidgetItem * item = new QListWidgetItem();
        item->setText(thing);
        item->setCheckState(Qt::Unchecked);
        ui->przedmiotListWidget->addItem(item);
        addElementToList(thing);
    }
}

void vote::addToFamousPersonWidgetList(QString famousPerson){
    if(!checkPresenceOfElementInListWidget(famousPerson)){
        QListWidgetItem * item = new QListWidgetItem();
        item->setText(famousPerson);
        item->setCheckState(Qt::Unchecked);
        ui->slawnaOsobaListWidget->addItem(item);
        addElementToList(famousPerson);
    }
}

bool vote::checkPresenceOfElementInListWidget(QString element){
    return itemsInWidgetList->contains(element);
}

void vote::addElementToList(QString element){
    itemsInWidgetList->append(element);
}

void vote::clearCountryWidgetList(){
    ui->panstwoListWidget->clear();
}

void vote::clearCityWidgetList(){
    ui->miastoListWidget->clear();
}

void vote::clearAnimalWidgetList(){
    ui->zwierzeListWidget->clear();

}

void vote::clearPlantWidgetList(){
    ui->roslinaListWidget->clear();
}

void vote::clearNameWidgetList(){
    ui->imieListWidget->clear();
}

void vote::clearWaterWidgetList(){
    ui->wodyListWidget->clear();
}

void vote::clearThingWidgetList(){
    ui->przedmiotListWidget->clear();
}

void vote::clearFamousPersonWidgetList(){
    ui->slawnaOsobaListWidget->clear();
}

void vote::clearElementsList(){
    itemsInWidgetList->clear();
}
