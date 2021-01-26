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
