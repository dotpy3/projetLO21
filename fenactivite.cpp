#include "fenactivite.h"
#include "ui_fenactivite.h"
#include "programmationmanager.h"

Fenactivite::Fenactivite(QWidget *parent) :
    QDialog(parent)
{
    this->setFixedSize(300,300);

    couche = new QHBoxLayout(this);
    couche1 = new QVBoxLayout();//titre act
    couche2 = new QVBoxLayout();//champs
    couche3 = new QVBoxLayout();//buton

    createAct = new QLabel("Programmation d'une activité");
    createAct->adjustSize();

    titre = new QLabel("Titre :");
    date = new QLabel("Début : ");
    duree = new QLabel("Durée : ");

    annuler = new QPushButton("Annuler");
    sauver = new QPushButton("Sauvegarder");

    textTitre = new QTextEdit;
    dateDeb = new QDateEdit;
    dur = new QTimeEdit;

    //asso couches
    couche->addLayout(couche1);
    couche->addLayout(couche2);
    couche->addLayout(couche3);

    couche1->addWidget(createAct);

    couche2->addWidget(titre);
    couche2->addWidget(textTitre);
    couche2->addWidget(date);
    couche2->addWidget(dateDeb);
    couche2->addWidget(duree);
    couche2->addWidget(dur);

    couche3->addWidget(sauver);
    couche3->addWidget(annuler);
}

Fenactivite::~Fenactivite()
{
}


void Fenactivite::on_btnSave_clicked()
{
    QString n = textTitre->toPlainText();
    const string &nom = n.toStdString();

    QTime du = dur->time();
    const Duree * duree = new Duree(du.hour(), du.minute(), du.second());
    const Duree& duree2 = *duree;

    QDate dat = dateDeb->date();
    const Date * date = new Date(dat.day(), dat.month(), dat.year());
    const Date& date2 = *date;

    ProgrammationManager::getInstance().ajouterProgrammationActivite(nom, date2, duree2);
    QMessageBox::information(this, "Projet Calendar", "L'activité a bien été ajoutée !");
    Fenactivite::close();

}

void Fenactivite::on_BtnCancel_clicked()
{
    Fenactivite::close();
}
