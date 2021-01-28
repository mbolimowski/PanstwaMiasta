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
        ui->panstwoListWidget->addItem(country);
        addElementToList(country);
    }
}

void vote::addToCityWidgetList(QString city){
    if(!checkPresenceOfElementInListWidget(city)){
        ui->miastoListWidget->addItem(city);
        addElementToList(city);
    }
}

void vote::addToAnimalWidgetList(QString animal){
    if(!checkPresenceOfElementInListWidget(animal)){
        ui->zwierzeListWidget->addItem(animal);
        addElementToList(animal);
    }
}

void vote::addToPlantWidgetList(QString plant){
    if(!checkPresenceOfElementInListWidget(plant)){
        ui->roslinaListWidget->addItem(plant);
        addElementToList(plant);
    }
}

void vote::addToNameWidgetList(QString name){
    if(!checkPresenceOfElementInListWidget(name)){
        ui->imieListWidget->addItem(name);
        addElementToList(name);
    }
}

void vote::addToWaterWidgetList(QString water){
    if(!checkPresenceOfElementInListWidget(water)){
        ui->wodyListWidget->addItem(water);
        addElementToList(water);
    }
}

void vote::addToThingWidgetList(QString thing){
    if(!checkPresenceOfElementInListWidget(thing)){
        ui->przedmiotListWidget->addItem(thing);
        addElementToList(thing);
    }
}

void vote::addToFamousPersonWidgetList(QString famousPerson){
    if(!checkPresenceOfElementInListWidget(famousPerson)){
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

void vote::clearAllWidgetLists(){

    for(int i = 1; i < 9; i++){
        QListWidget * currentWidget = getWidget(i);
        currentWidget->clear();
    }
}

void vote::addToSpecialWidgetList(QString category){
    int whichWidget = category[0].digitValue();

}

QPushButton * vote::getVoteButton(){
    return ui->glosujButton;
}

QString vote::getVoices(){
    QString voices = "";
    for(int i = 1; i < 9; i++){
        QListWidget * currentWidget = getWidget(i);
        for(int j = 0; j < (int)currentWidget->selectedItems().size(); j++){
            voices += currentWidget->selectedItems().value(j)->text() + ",";
        }
    }
    return voices;
}

QListWidget * vote::getWidget(int whichWidget){
    switch(whichWidget){
    case 1:
        return ui->panstwoListWidget;
        break;
    case 2:
        return ui->miastoListWidget;
        break;
    case 3:
        return ui->zwierzeListWidget;
        break;
    case 4:
        return ui->roslinaListWidget;
        break;
    case 5:
        return ui->imieListWidget;
        break;
    case 6:
        return ui->wodyListWidget;
        break;
    case 7:
        return ui->przedmiotListWidget;
        break;
    case 8:
        return ui->slawnaOsobaListWidget;
        break;
    }
    return NULL;
}


