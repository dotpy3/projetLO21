#include "fenjournee.h"
#include "ui_fenjournee.h"

FenJournee::FenJournee(QWidget *parent) :
    QDialog(parent)
{
    this->setFixedSize(300,300);

    journee = new QLabel("now");
    couche = new QHBoxLayout();
    couche1 = new QVBoxLayout();
    couche2 = new QVBoxLayout();
    lstDeb = new QListView();
    lstFin = new QListView();
    lstEve = new QListView();
    sa = new QScrollArea();

    couche->addLayout(couche1);
    couche->addLayout(couche2);

    couche1->addWidget(journee);

    couche2->addWidget(sa);
    sa->setFixedSize(couche2->sizeHint());
    sa->setWidget(lstDeb);
    sa->setWidget(lstFin);
    sa->setWidget(lstEve);
}

FenJournee::~FenJournee()
{
 }
