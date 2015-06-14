#include "fenajouttache.h"

fenajouttache::fenajouttache(bool unitaire,  Projet* projetChoisi,TacheComposee* compo, QWidget *parent):QWidget(parent),
    proj(projetChoisi),isUnitaire(unitaire),tacheComposition(compo){

    setWindowTitle("Création tâche");

    layout = new QVBoxLayout;

    if (compo != 0) {
        association = new QLabel(("Associée à la tâche : "+compo->getTitre()).c_str());
        layout->addWidget(association);
    }

    labelNom = new QLabel("Nom :");
    layout->addWidget(labelNom);

    choixNom = new QLineEdit();
    layout->addWidget(choixNom);

    if (isUnitaire){

        choixPreemptable = new QCheckBox("Préemptable");
        layout->addWidget(choixPreemptable);

        labelDuree = new QLabel("Durée :");
        layout->addWidget(labelDuree);

        choixDuree = new QTimeEdit();
        choixDuree->setMaximumTime(QTime(12,0,0,0));
        layout->addWidget(choixDuree);

    }

    sauvegarde = new QPushButton("Sauvegarder");
    QPushButton::connect(sauvegarde,SIGNAL(clicked()),this,SLOT(processSauvegarder()));
    layout->addWidget(sauvegarde);

    this->setLayout(layout);

    this->show();
}

fenajouttache::~fenajouttache(){
    delete association;
    delete labelNom;
    delete labelDuree;
    delete choixNom;
    delete choixPreemptable;
    delete choixDuree;
    delete sauvegarde;
    delete layout;
}

void fenajouttache::processSauvegarder(){
    if (isUnitaire){
        proj->addTacheUnitaire(choixNom->text().toStdString(),
                               choixPreemptable->isChecked(),
                               Duree(choixDuree->time()),
                               tacheComposition);
    } else {
        proj->addTacheComposee(choixNom->text().toStdString(),
                               tacheComposition);
    }

    close();
}
