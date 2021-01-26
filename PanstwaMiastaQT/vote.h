#ifndef VOTE_H
#define VOTE_H

#include <QDialog>

namespace Ui {
class vote;
}

class vote : public QDialog
{
    Q_OBJECT

public:
    explicit vote(QWidget *parent = nullptr);
    ~vote();

private:
    Ui::vote *ui;
};

#endif // VOTE_H
