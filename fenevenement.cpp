#include "fenevenement.h"
#include "ui_fenevenement.h"

FenEvenement::FenEvenement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenEvenement)
{
    ui->setupUi(this);
}

FenEvenement::~FenEvenement()
{
    delete ui;
}
