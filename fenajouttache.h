#ifndef FENAJOUTTACHE_H
#define FENAJOUTTACHE_H
/*!
 * \file fenajouttache.h
 * \brief fichier de la classe fenajouttache
 * \author Gourlaouen Penisson
 */

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QTimeEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "tachecomposee.h"
#include "projet.h"

/*! \class fenajouttache
 * \brief classe fenajouttache hérite QMainWindow
 *
 *  La classe gere l'interface d'ajout de tâches
 */
class fenajouttache : public QWidget
{
    Q_OBJECT
    QLabel *association, *labelNom, *labelDuree;
    QLineEdit* choixNom;
    QCheckBox* choixPreemptable;
    QTimeEdit *choixDuree;
    QPushButton *sauvegarde;
    Projet* proj;
    QVBoxLayout *layout;
    bool isUnitaire;
    TacheComposee* tacheComposition;

public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe fenajouttache
     *
     *  \param unitaire : indique si la tâche est unitaire ou non
     *  \param projetChoisi : projet sur lequel on ajoute une tâche
     *  \param compo : tâche à ajouter
     *  \param parent : fenêtre cible
     */
    fenajouttache( bool unitaire, Projet* projetChoisi = 0, TacheComposee* compo = 0, QWidget *parent = 0);

    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe fenajouttache
     *
     */
    ~fenajouttache();

public slots:
    /*!
     *  \brief processSauvegarder
     *
     *  slot gérant la sauvegarde de la tâche
     *
     */
    void processSauvegarder();
private:
    fenajouttache *ui;
};
#include <QMainWindow>
#include "gestionprojets.h"
#endif // FENAJOUTTACHE_H
