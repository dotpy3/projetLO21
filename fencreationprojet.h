#ifndef FENCREATIONPROJET_H
#define FENCREATIONPROJET_H
/*!
 * \file fencreationprojet.h
 * \brief fichier de la classe fenCreationProjet
 * \author Gourlaouen Penisson
 */
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include "projetmanager.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "gestionprojets.h"

/*! \class fenCreationProjet
 * \brief classe fenCreationProjet hérite QDialog
 *
 *  La classe gere l'interface d'ajout d'un projet
 */
class fenCreationProjet:public QDialog
{
    Q_OBJECT
    QPushButton *sauvegarde,*annuler;
    QLineEdit *titreProjet;
    QVBoxLayout *layout;
    QLabel *labelSauvegarde;
public:

    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe fenCreationProjet
     *
     *  \param parent : fenêtre cible
     */

    fenCreationProjet(QWidget* parent = 0);

    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe fenCreationProjet
     */
    ~fenCreationProjet();
public slots:

    /*!
     *  \brief saveProject
     *
     *  slot gérant la sauvegarde du projet
     *
     */
    void saveProject();
};

#endif // FENCREATIONPROJET_H
