#include "vote.h"
#include "ui_vote.h"

vote::vote(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vote)
{
    ui->setupUi(this);
    items = new QListWidgetItem();
    itemsInWidgetList = new QList<QString>;
}

vote::~vote()
{
    delete ui;
}


void vote::addToCountryWidgetList(QString country){
    if(!checkPresenceOfElementInListWidget(country)){
        items->setText(country);
        items->setCheckState(Qt::Unchecked);
        ui->panstwoListWidget->addItem(country);
        addElementToList(country);
    }
}

void vote::addToCityWidgetList(QString city){
    if(!checkPresenceOfElementInListWidget(city)){
        items->setText(city);
        items->setCheckState(Qt::Unchecked);
        ui->miastoListWidget->addItem(city);
        addElementToList(city);
    }
}

void vote::addToAnimalWidgetList(QString animal){
    if(!checkPresenceOfElementInListWidget(animal)){
        items->setText(animal);
        items->setCheckState(Qt::Unchecked);
        ui->zwierzeListWidget->addItem(animal);
        addElementToList(animal);
    }
}

void vote::addToPlantWidgetList(QString plant){
    if(!checkPresenceOfElementInListWidget(plant)){
        items->setText(plant);
        items->setCheckState(Qt::Unchecked);
        ui->roslinaListWidget->addItem(plant);
        addElementToList(plant);
    }
}

void vote::addToNameWidgetList(QString name){
    if(!checkPresenceOfElementInListWidget(name)){
        items->setText(name);
        items->setCheckState(Qt::Unchecked);
        ui->imieListWidget->addItem(name);
        addElementToList(name);
    }
}

void vote::addToWaterWidgetList(QString water){
    if(!checkPresenceOfElementInListWidget(water)){
        items->setText(water);
        items->setCheckState(Qt::Unchecked);
        ui->wodyListWidget->addItem(water);
        addElementToList(water);
    }
}

void vote::addToThingWidgetList(QString thing){
    if(!checkPresenceOfElementInListWidget(thing)){
        items->setText(thing);
        items->setCheckState(Qt::Unchecked);
        ui->przedmiotListWidget->addItem(thing);
        addElementToList(thing);
    }
}

void vote::addToFamousPersonWidgetList(QString famousPerson){
    if(!checkPresenceOfElementInListWidget(famousPerson)){
        items->setText(famousPerson);
        items->setCheckState(Qt::Unchecked);
        ui->slawnaOsobaListWidget->addItem(famousPerson);
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
