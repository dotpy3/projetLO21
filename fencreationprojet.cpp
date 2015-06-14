#include "fencreationprojet.h"

fenCreationProjet::fenCreationProjet(QWidget* parent):QDialog(parent)
{

    this->setWindowTitle("Créer projet");
    QLabel* labelTitre = new QLabel("Titre : ");

    titreProjet=new QLineEdit("Titre du projet");

    sauvegarde = new QPushButton("Sauvegarder");
    connect(sauvegarde,SIGNAL(clicked()),this,SLOT(saveProject()));
    labelSauvegarde = new QLabel("");
    annuler = new QPushButton("Fermer la fenêtre");
    connect(annuler,SIGNAL(clicked()),this,SLOT(close()));

    layout = new QVBoxLayout;
    layout->addWidget(labelTitre);
    layout->addWidget(titreProjet);
    layout->addWidget(labelSauvegarde);
    layout->addWidget(sauvegarde);
    layout->addWidget(annuler);

    this->setLayout(layout);
}

fenCreationProjet::~fenCreationProjet()
{
    delete sauvegarde;
    delete annuler;
    delete titreProjet;
    delete labelSauvegarde;
}

void fenCreationProjet::saveProject(){

    ProjetManager& projman = ProjetManager::getInstance();
    projman.creerProjet(titreProjet->text().toStdString());
    delete labelSauvegarde;
    labelSauvegarde = new QLabel("Projet sauvegardé !");
    this->update();
    if (this->parentWidget() != 0) dynamic_cast<FenGestionProjets*>(this->parentWidget())->updateProjets();
    this->close();
}
