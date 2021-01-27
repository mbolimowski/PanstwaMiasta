#ifndef GAMEMAIN_H
#define GAMEMAIN_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class gameMain;
}

class gameMain : public QDialog
{
    Q_OBJECT

public:
    explicit gameMain(QWidget *parent = nullptr);
    ~gameMain();
    Ui::gameMain * getUi();

    void setCategoriesDisabled();

    void setCheckboxesDisabled();

    void setStartButtonDisabled();

    void setEditRoundsTextEditDisabled();

    void clearPlayerAndPointsListWidget();

    void addPlayerName(QString name);

    void addPoints(QString points);

    QString getRounds();

    int isCheckedAtLeastOneBox();

    int isRoundsCorrect();

    QStringList getCheckedBoxes();

    QPushButton * getStartButton();

private:
    Ui::gameMain *ui;
};

#endif // GAMEMAIN_H
