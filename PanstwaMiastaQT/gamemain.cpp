#include "gamemain.h"
#include "ui_gamemain.h"

gameMain::gameMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameMain)
{
    ui->setupUi(this);
}

gameMain::~gameMain()
{
    delete ui;
}


void gameMain::setCategoriesDisabled()
{
    ui->panstwoTextEdit->setReadOnly(true);
    ui->miastoTextEdit->setReadOnly(true);
    ui->zwierzeTextEdit->setReadOnly(true);
    ui->roslinaTextEdit->setReadOnly(true);
    ui->imieTextEdit->setReadOnly(true);
    ui->wodyTextEdit->setReadOnly(true);
    ui->przedmiotTextEdit->setReadOnly(true);
    ui->slawnaOsobaTextEdit->setReadOnly(true);
    ui->zglosButton->setEnabled(false);
}


void gameMain::setCheckboxesDisabled()
{
    ui->panstwoCheckBox->setEnabled(false);
    ui->miastoCheckBox->setEnabled(false);
    ui->zwierzeCheckBox->setEnabled(false);
    ui->roslinaCheckBox->setEnabled(false);
    ui->imieCheckBox->setEnabled(false);
    ui->wodyCheckBox->setEnabled(false);
    ui->przedmiotCheckBox->setEnabled(false);
    ui->slawnaOsobaCheckBox->setEnabled(false);
}

void gameMain::setStartButtonDisabled()
{
    ui->startButton->setEnabled(false);
}

void gameMain::setEditRoundsTextEditDisabled()
{
    ui->iloscRundTextEdit->setReadOnly(true);
}


void gameMain::clearPlayerAndPointsListWidget(){
    ui->graczListWidget->clear();
    ui->punktyListWidget->clear();
}

void gameMain::addPlayerName(QString name)
{
    ui->graczListWidget->addItem(name);
}

void gameMain::addPoints(QString points)
{
    ui->punktyListWidget->addItem(points);
}

QString gameMain::getRounds(){
    return ui->iloscRundTextEdit->toPlainText();
}

int gameMain::isCheckedAtLeastOneBox(){
    int counter = 0;
    counter += ui->panstwoCheckBox->isChecked();
    counter += ui->miastoCheckBox->isChecked();
    counter += ui->zwierzeCheckBox->isChecked();
    counter += ui->roslinaCheckBox->isChecked();
    counter += ui->imieCheckBox->isChecked();
    counter += ui->wodyCheckBox->isChecked();
    counter += ui->przedmiotCheckBox->isChecked();
    counter += ui->slawnaOsobaCheckBox->isChecked();
    if(counter == 0){
        QMessageBox messageBox;
        messageBox.critical(this, "Błąd", "Należy wybrać przynajmniej jedną kategorie!");
        return -1;
    }

    return 1;
}

QStringList gameMain::getCheckedBoxes(){
    QStringList checkedBoxes = {};
    if(ui->panstwoCheckBox->isChecked()){
        checkedBoxes << "1";
    }
    if(ui->miastoCheckBox->isChecked()){
        checkedBoxes << "2";
    }
    if(ui->zwierzeCheckBox->isChecked()){
        checkedBoxes << "3";
    }
    if(ui->roslinaCheckBox->isChecked()){
        checkedBoxes << "4";
    }
    if(ui->imieCheckBox->isChecked()){
        checkedBoxes << "5";
    }
    if(ui->wodyCheckBox->isChecked()){
        checkedBoxes << "6";
    }
    if(ui->przedmiotCheckBox->isChecked()){
        checkedBoxes << "7";
    }
    if(ui->slawnaOsobaCheckBox->isChecked()){
        checkedBoxes << "8";
    }

    return checkedBoxes;
}

int gameMain::isRoundsCorrect(){
    QString rounds = ui->iloscRundTextEdit->toPlainText();
    if(rounds == ""){
        QMessageBox messageBox;
        messageBox.critical(this, "Błąd", "Należy wpisac liczbe rund!");
        return -1;
    }
    for(int i = 0; i < rounds.length(); i++){
        if(!rounds[i].isDigit()){
            return -1;
        }
    }
    return 1;
}


QPushButton * gameMain::getStartButton(){
    return ui->startButton;
}

void gameMain::setCountryTextEditEnabled(){
    ui->panstwoTextEdit->setReadOnly(false);
}

void gameMain::setCityTextEditEnabled(){
    ui->miastoTextEdit->setReadOnly(false);
}

void gameMain::setAnimalTextEditEnabled(){
    ui->zwierzeTextEdit->setReadOnly(false);
}

void gameMain::setPlantTextEditEnabled(){
    ui->roslinaTextEdit->setReadOnly(false);
}

void gameMain::setNameTextEditEnabled(){
    ui->imieTextEdit->setReadOnly(false);
}

void gameMain::setWaterTextEditEnabled(){
    ui->wodyTextEdit->setReadOnly(false);
}

void gameMain::setThingTextEditEnabled(){
    ui->przedmiotTextEdit->setReadOnly(false);
}

void gameMain::setFamousPersonTextEditEnabled(){
    ui->slawnaOsobaTextEdit->setReadOnly(false);
}

void gameMain::setEditRoundsTextEditEnabled(){
    ui->iloscRundTextEdit->setReadOnly(false);
}

void gameMain::setRounds(QString rounds){
    ui->iloscRundTextEdit->setText(rounds);
    setEditRoundsTextEditDisabled();
}

void gameMain::setLetter(QString letter){
    ui->aktualnaLiteraLabel->setText(letter);
}
