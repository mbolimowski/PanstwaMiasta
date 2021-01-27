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
