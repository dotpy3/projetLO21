#ifndef FENEVENEMENT_H
#define FENEVENEMENT_H

#include <QDialog>

namespace Ui {
class FenEvenement;
}

class FenEvenement : public QDialog
{
    Q_OBJECT

public:
    explicit FenEvenement(QWidget *parent = 0);
    ~FenEvenement();

private:
    Ui::FenEvenement *ui;
};

#endif // FENEVENEMENT_H
