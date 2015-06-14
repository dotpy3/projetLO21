#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H
/*!
 * \file fenprincipale.h
 * \brief fichier de la FenPrincipale
 * \author Gourlaouen Penisson
 */

#include <QDateTime>
#include <QCalendarWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTableView>
#include "gestionprojets.h"
#include "programmationmanager.h"
#include <QStandardItemModel>
#include <QListView>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "fencreateeve.h"


/*! \class FenPrincipale
 * \brief classe FenJournee hérite QWidget
 *
 *  La classe gere l'interface principale
 */
class FenPrincipale : public QWidget
{
    Q_OBJECT
    QCalendarWidget *cal;
    QMenuBar *barreDeMenu;
    QMenu *menFichier, *menEdition, *menGerer, *menAddEvent;
    QMenuBar* barreMenus;
    QVBoxLayout* layout;
    QTableView *grid;
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe FenPrincipale
     *
     *  \param parent : fenêtre cible
     */
    explicit FenPrincipale(QWidget *parent = 0);

    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe FenJournee
     *
     */
    ~FenPrincipale();

private:


public slots:
    /*!
     *  \brief quit
     *
     *  slot gérant la fermeture de l'application
     *
     */
    void quit();

    /*!
     *  \brief fetchProjets
     *
     *  slot gérant l'ouverture de la fenêtre de gestion de projets
     *
     */
    void fetchProjets();

    /*!
     *  \brief openCreationActivity
     *
     *  slot gérant l'ouverture de la fenêtre de création d'activité
     *
     */
    void openCreationActivity();

    /*!
     *  \brief openCreationTask
     *
     *  slot gérant l'ouverture de la fenêtre de création de tâches
     *
     */
    void openCreationTask();



};


#endif // FENPRINCIPALE_H
