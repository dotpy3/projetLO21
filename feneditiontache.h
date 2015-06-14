#ifndef FENEDITIONTACHE_H
#define FENEDITIONTACHE_H

/*!
 * \file feneditiontache.h
 * \brief fichier de la FenGestionProjets
 * \author Gourlaouen Penisson
 */

#include <QMainWindow>


/*! \class feneditiontache
 * \brief classe feneditiontache hérite QMainWindow
 *
 *  La classe gere l'interface d'éditions de tâches
 */
class feneditiontache : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe feneditiontache
     *
     *  \param parent : fenêtre cible
     */
    explicit feneditiontache(QWidget *parent = 0);

    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe feneditiontache
     *
     */
    ~feneditiontache();

private:
    feneditiontache *ui;
};

#endif // FENEDITIONTACHE_H
