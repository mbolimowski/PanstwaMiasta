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

bool vote::checkPresenceOfElementInListWidget(QString element){
    return itemsInWidgetList->contains(element);
}

void vote::addElementToList(QString element){
    itemsInWidgetList->append(element);
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
    QListWidget * currentWidget = getWidget(whichWidget);
    if(!checkPresenceOfElementInListWidget(category)){
        currentWidget->addItem(category);
        addElementToList(category);
    }
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


