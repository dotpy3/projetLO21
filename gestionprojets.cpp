#include "gestionprojets.h"

FenGestionProjets::FenGestionProjets(ProjetManager* pm, QWidget* parent):QWidget(parent),projetSelectionne(0){
    projetManager = pm;

    this->setFixedSize(800,700);

    QHBoxLayout *layout2 = new QHBoxLayout(this); // choixproj + détailsproj
    QVBoxLayout *layout3 = new QVBoxLayout; // détailsproj : haut détails, bas tâches
    QGridLayout *layout4 = new QGridLayout(); // détails tech projet

    /*
     *
     * BARRE DE MENUS
     *
     */
    std::cout<<"test2";
    QMenuBar* barreDeMenus = new QMenuBar(this);

    QMenu* menuFichier = barreDeMenus->addMenu("Fichier");

    QAction *action1 = menuFichier->addAction("Importer");

    QAction::connect(action1, SIGNAL(triggered()), this, SLOT(addNewXMLProject()));

    QAction *action2 = menuFichier->addAction("Exporter le projet");

    QAction::connect(action2, SIGNAL(triggered()), this, SLOT(exportProjet()));

    QAction *action3 = menuFichier->addAction("Exporter tous les projets");
    QAction::connect(action3, SIGNAL(triggered()), this, SLOT(exportAllProjets()));

    QAction *action9 = menuFichier->addAction("Actualiser");
    QAction::connect(action9, SIGNAL(triggered()), this, SLOT(actualiser()));

    QMenu* menuProjets = barreDeMenus->addMenu("Projets");

    QAction *action4 = menuProjets->addAction("Ajouter un projet");
    QAction::connect(action4, SIGNAL(triggered()), this, SLOT(addProjet()));
    QAction *action5 = menuProjets->addAction("Supprimer le projet");
    QAction::connect(action5, SIGNAL(triggered()), this, SLOT(deleteProjet()));

    QMenu* menuTaches = barreDeMenus->addMenu("Tâches");

    QMenu *action6 = menuTaches->addMenu("Ajouter une tâche");
    QAction *action7 = action6->addAction("Ajouter une tâche unitaire");
    QAction::connect(action7, SIGNAL(triggered()), this, SLOT(addTacheUnitaire()));
    QAction *action8 = action6->addAction("Ajouter une tâche composite");
    QAction::connect(action8, SIGNAL(triggered()), this, SLOT(addTacheComposite()));
std::cout<<"test3";
    /*
     *
     * LISTE DE PROJETS
     *
     */

    listeProjets = new QListView;


    listeDeProjets = new QStringList();

    ProjetManager::Iterator it = pm->getIterator();
    QString str;
    for(true;!it.isDone();it.next()){
        *listeDeProjets << (str = it.current()->getTitre().c_str());
    }


    QStringListModel *modele = new QStringListModel(*listeDeProjets);

    listeProjets->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listeProjets->setModel(modele);

    QListView::connect(listeProjets,SIGNAL(clicked(const QModelIndex)),this,SLOT(changeProject(QModelIndex)));


    /*
     *
     * INFOS DU PROJET
     *
     */
    std::cout<<"test4";
    titreProj = new QLabel("Titre du projet");

    modifNomProjet = new QLineEdit("Nouveau nom");

    QPushButton* boutonSauvegarde = new QPushButton("Sauvegarder");
    QPushButton::connect(boutonSauvegarde,SIGNAL(clicked()), this, SLOT(saveSelectedProjets()));

    dateDispo = new QCheckBox("Date de disponibilité");
    dateDispoEdit = new QDateTimeEdit();

    dateEch = new QCheckBox("Date d\'échéance");
    dateEchEdit = new QDateTimeEdit();

    layout4->addWidget(titreProj,0,0);
    layout4->addWidget(modifNomProjet,1,0);
    layout4->addWidget(boutonSauvegarde,1,1);
    layout4->addWidget(dateDispo,2,0);
    layout4->addWidget(dateDispoEdit,2,1);
    layout4->addWidget(dateEch,3,0);
    layout4->addWidget(dateEchEdit,3,1);


    /*
     *
     * TÂCHES DU PROJET
     *
     */

    listeTaches = new QListView();
    listeDeTaches = new QStringList();

    QStringListModel *modeleTaches = new QStringListModel(*listeDeTaches);

    listeTaches->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listeTaches->setModel(modeleTaches);

    QListView::connect(listeTaches,
                       SIGNAL(clicked(const QModelIndex)),
                       this,
                       SLOT(openTacheMenu(QModelIndex))
                );


    /*
     *
     * RAJOUT DES LAYOUTS
     *
     */

    layout3->addLayout(layout4);
    layout3->addWidget(listeTaches);


    layout2->addWidget(listeProjets);
    layout2->addLayout(layout3);
    listeTaches->adjustSize();
    // on a ajouté la liste des projets

    this->setLayout(layout2);
}

void FenGestionProjets::exportProjet(){
    if(projetSelectionne == 0){
        QMessageBox::warning(this,"Pas de projet sélectionné","Merci de sélectionner un projet");
    } else {
        projetSelectionne->exportXML(this);
    }
}

void FenGestionProjets::exportAllProjets(){
    ProjetManager& projman = ProjetManager::getInstance();
    ProjetManager::Iterator iterateur = projman.getIterator();
    for(true;!iterateur.isDone();iterateur.next()){
        iterateur.current()->exportXML(this);
    }
}

void FenGestionProjets::addProjet(){
    fenCreationProjet* creationProjet=new fenCreationProjet(this);
    creationProjet->show();
}

void FenGestionProjets::changeProject(QModelIndex index){
    std::string* titreProjet = new std::string(index.data().toString().toStdString());
    projetSelectionne = ProjetManager::getInstance().getProjet(*titreProjet);

    titreProj->setText(projetSelectionne->getTitre().c_str());
    if (projetSelectionne->isDateDisp()) {
        dateDispo->setChecked(true);
        dateDispoEdit = new QDateTimeEdit(projetSelectionne->getDateDisp().getQDateTime());
    } else {
        dateDispo->setChecked(false);
        dateDispoEdit = new QDateTimeEdit();
    }
    if (projetSelectionne->isDateEcheance()) {
        dateEch->setChecked(true);
        dateEchEdit = new QDateTimeEdit(projetSelectionne->getDateEcheance().getQDateTime());
        dateEch->setChecked(false);
        dateEchEdit = new QDateTimeEdit();
    }

    listeTaches = new QListView();
    listeDeTaches = new QStringList();

    for(size_t i = 0; i<projetSelectionne->premiersEnfants().size();
        i++){
        *listeDeTaches << projetSelectionne->premiersEnfants()[i]
                          ->getTitre().c_str();
    }

    QStringListModel *modeleTaches = new QStringListModel(*listeDeTaches);

    listeTaches->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listeTaches->setModel(modeleTaches);

    QListView::connect(listeTaches,
                       SIGNAL(clicked(const QModelIndex)),
                       this,
                       SLOT(openTacheMenu(QModelIndex))
                );


    update();
}

void FenGestionProjets::updateProjets(){
}

void FenGestionProjets::actualiser(){
    FenGestionProjets* gestionProjets = new FenGestionProjets();
    gestionProjets->show();

    close();
}

void FenGestionProjets::addTacheUnitaire(){
    if (projetSelectionne == 0){
        QMessageBox::warning(this,"Action impossible","Merci de sélectionner un projet");
        return;
    }
    fenajouttache* fenetre = new fenajouttache(true,projetSelectionne);
}

void FenGestionProjets::addTacheComposite(){
    if (projetSelectionne == 0){
        QMessageBox::warning(this,"Action impossible","Merci de sélectionner un projet");
        return;
    }
    fenajouttache* fenetre = new fenajouttache(false,projetSelectionne);
}

void FenGestionProjets::saveSelectedProjets(){
    if (projetSelectionne == 0){
        QMessageBox::warning(this,"Action impossible","Merci de sélectionner un projet");
        return;
    }

    QMessageBox::warning(this,"Update en cours","");
    projetSelectionne->setTitre(modifNomProjet->text().toStdString());

    if (dateDispo->isChecked()){
        projetSelectionne->setDateDisp(Date(
                                           dateDispoEdit->date().day(),
                                           dateDispoEdit->date().month(),
                                           dateDispoEdit->date().year(),
                                           dateDispoEdit->time().hour(),
                                           dateDispoEdit->time().minute(),
                                           dateDispoEdit->time().second()));
    }

    if (dateEch->isChecked()){
        projetSelectionne->setDateEch(Date(
                                           dateEchEdit->date().day(),
                                           dateEchEdit->date().month(),
                                           dateEchEdit->date().year(),
                                           dateEchEdit->time().hour(),
                                           dateEchEdit->time().minute(),
                                           dateEchEdit->time().second()));
    }

    updateProjets();
}

void FenGestionProjets::deleteProjet(){
    if (projetSelectionne == 0){
        QMessageBox::warning(this,"Action impossible","Merci de sélectionner un projet");
        return;
    }

    ProjetManager::getInstance().supprimerProjet(projetSelectionne);

    updateProjets();
}

void FenGestionProjets::openTachesMenu(QModelIndex index){

}
