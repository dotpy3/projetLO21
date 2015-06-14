#include "fenprojet.h"
#include "ui_fenprojet.h"

FenProjet::FenProjet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenProjet)
{
    ui->setupUi(this);
}

FenProjet::~FenProjet()
{
    delete ui;
}
