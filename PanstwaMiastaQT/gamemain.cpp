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
    ui->iloscRundTextEdit->setEnabled(false);
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
        checkedBoxes << "panstwo";
    }
    if(ui->miastoCheckBox->isChecked()){
        checkedBoxes << "miasto";
    }
    if(ui->zwierzeCheckBox->isChecked()){
        checkedBoxes << "zwierze";
    }
    if(ui->roslinaCheckBox->isChecked()){
        checkedBoxes << "roslina";
    }
    if(ui->imieCheckBox->isChecked()){
        checkedBoxes << "imie";
    }
    if(ui->wodyCheckBox->isChecked()){
        checkedBoxes << "wody";
    }
    if(ui->przedmiotCheckBox->isChecked()){
        checkedBoxes << "przedmiot";
    }
    if(ui->slawnaOsobaCheckBox->isChecked()){
        checkedBoxes << "slawnaOsoba";
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
