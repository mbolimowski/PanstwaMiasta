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


void gameMain::setSendAnswerButtonEnable(){
    ui->zglosButton->setEnabled(true);
}

void gameMain::setSendAnswerButtonDisable(){
    ui->zglosButton->setEnabled(false);
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

void gameMain::setStartButtonEnabled(){
    ui->startButton->setEnabled(true);
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

QPushButton * gameMain::getSendAnswerButton(){
    return ui->zglosButton;
}

int gameMain::isSendingAnswerCorrect(){
    if(!ui->panstwoTextEdit->isReadOnly()  && ui->panstwoTextEdit->text().isEmpty()){
        return -1;
    }
    if(!ui->miastoTextEdit->isReadOnly() && ui->miastoTextEdit->text().isEmpty()){
        return -1;
    }
    if(!ui->zwierzeTextEdit->isReadOnly()  && ui->zwierzeTextEdit->text().isEmpty()){
        return -1;
    }
    if(!ui->roslinaTextEdit->isReadOnly()  && ui->roslinaTextEdit->text().isEmpty()){
        return -1;
    }
    if(!ui->imieTextEdit->isReadOnly()  && ui->imieTextEdit->text().isEmpty()){
        return -1;
    }
    if(!ui->wodyTextEdit->isReadOnly()  && ui->wodyTextEdit->text().isEmpty()){
        return -1;
    }
    if(!ui->przedmiotTextEdit->isReadOnly()  && ui->przedmiotTextEdit->text().isEmpty()){
        return -1;
    }
    if(!ui->slawnaOsobaTextEdit->isReadOnly()  && ui->slawnaOsobaTextEdit->text().isEmpty()){
        return -1;
    }
    return 1;
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

void gameMain::setTime(int seconds){
    ui->aktualnyCzasLabel->setText(QString::number(seconds));
}

QString gameMain::getAnswers(){
    QString answers = "";

    if(!ui->panstwoTextEdit->isReadOnly()){
        answers += "1" + ui->panstwoTextEdit->text() + ",";
    }
    if(!ui->miastoTextEdit->isReadOnly()){
        answers += "2" + ui->miastoTextEdit->text() + ",";
    }
    if(!ui->zwierzeTextEdit->isReadOnly()){
        answers += "3" + ui->zwierzeTextEdit->text() + ",";
    }
    if(!ui->roslinaTextEdit->isReadOnly()){
        answers += "4" + ui->roslinaTextEdit->text() + ",";
    }
    if(!ui->imieTextEdit->isReadOnly()){
        answers += "5" + ui->imieTextEdit->text() + ",";
    }
    if(!ui->wodyTextEdit->isReadOnly()){
        answers += "6" + ui->wodyTextEdit->text() + ",";
    }
    if(!ui->przedmiotTextEdit->isReadOnly()){
        answers += "7" + ui->przedmiotTextEdit->text() + ",";
    }
    if(!ui->slawnaOsobaTextEdit->isReadOnly()){
        answers += "8" + ui->slawnaOsobaTextEdit->text() + ",";
    }
    answers = answers.toLower();
    return answers;
}

void gameMain::setCheckBoxesEnabled(){
    ui->panstwoCheckBox->setEnabled(true);
    ui->miastoCheckBox->setEnabled(true);
    ui->zwierzeCheckBox->setEnabled(true);
    ui->roslinaCheckBox->setEnabled(true);
    ui->imieCheckBox->setEnabled(true);
    ui->wodyCheckBox->setEnabled(true);
    ui->przedmiotCheckBox->setEnabled(true);
    ui->slawnaOsobaCheckBox->setEnabled(true);
}

