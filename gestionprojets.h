#ifndef GESTIONPROJETS_H
#define GESTIONPROJETS_H

/*!
 * \file gestionprojets.h
 * \brief fichier de la FenGestionProjets
 * \author Gourlaouen Penisson
 */


#include <QMainWindow>
#include <QMenuBar>
#include <QWidget>
#include <QListView>
#include <QFileDialog>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QDateEdit>
#include "projetmanager.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>
#include <QStringListModel>
#include <QTextEdit>
#include <QDateTimeEdit>
#include "projettreeview.h"
#include <QPushButton>
#include <QTreeView>
#include "fencreationprojet.h"
#include <QModelIndex>
#include "fenajouttache.h"
#include <QDate>
#include <QTime>

/*! \class FenGestionProjets
 * \brief classe FenGestionProjets hérite QMainWindow
 *
 *  La classe gere l'interface de gestion de projets
 */

class FenGestionProjets: public QWidget {
    Q_OBJECT
private:
    ProjetManager* projetManager; /*!< instance de projetManager */
    Projet* projetSelectionne; /*!< projet sélectionné */

    QLineEdit* modifNomProjet;
    QLabel* titreProj;
    QCheckBox* dateDispo,*dateEch;
    QDateTimeEdit* dateDispoEdit, *dateEchEdit;
    QStringList* listeDeProjets, *listeDeTaches;
    QListView* listeProjets, *listeTaches;
    QTreeView* vue;
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe FenGestionProjets
     *
     *  \param pm : instance de projetManager
     *  \param parent : fenêtre cible
     */
    FenGestionProjets(ProjetManager* pm = &(ProjetManager::getInstance()), QWidget* parent=0);

    void updateProjets();

signals:

public slots:
    /*!
     *  \brief addNewXMLProject
     *
     *  slot gérant l'ajout d'un nouveau projet à partir d'un fichier XML
     */
    void addNewXMLProject(){
        QString chemin=QFileDialog::getOpenFileName();
        projetManager->creerProjetXML(chemin,this);
        update();
    }

    /*!
     *  \brief exportProjet
     *
     *  slot gérant l'export d'un projet en XML
     *  \param pr : projet à exporter
     */
    void exportProjet();

    /*!
     *  \brief exportAllProjets
     *
     *  slot gérant l'export de tous les projets en XML
     */
    void exportAllProjets();

    /*!
     *  \brief addProjet
     *
     *  slot gérant l'ajout de projets
     */
    void addProjet();

    /*!
     *  \brief changeProject
     *
     *  slot gérant le changement de projet
     * \param index : index du projet
     */
    void changeProject(QModelIndex index);

    /*!
     *  \brief addTacheUnitaire
     *
     *  slot gérant l'ajout d'une tache unitaire
     */
    void addTacheUnitaire();

    /*!
     *  \brief addTacheComposite
     *
     *  slot gérant l'ajout d'une tache composite
     */
    void addTacheComposite();

    /*!
     *  \brief saveSelectedProjets
     *
     *  slot gérant la sauvegarde des projets sélectionnés
     */
    void saveSelectedProjets();

    /*!
     *  \brief deleteProjet
     *
     *  slot gérant la suppression du projet
     */
    void deleteProjet();


    /*!
     *  \brief actualiser
     *
     *  slot gérant l'actualisation de la fenetre
     */
    void actualiser();


    /*!
     *  \brief openTachesMenu
     *
     *  slot gérant l'ouverture du menu de tâches
     *  \param index
     */
    void openTachesMenu(QModelIndex index);
};

#endif // GESTIONPROJETS_H
