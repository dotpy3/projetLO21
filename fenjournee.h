#ifndef FENJOURNEE_H
#define FENJOURNEE_H
/*!
 * \file fenjournee.h
 * \brief fichier de la FenJournee
 * \author Gourlaouen Penisson
 */

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListView>
#include <QScrollArea>

namespace Ui {
class FenJournee;
}

/*! \class FenJournee
 * \brief classe FenJournee hérite QDialog
 *
 *  La classe gere l'interface d'éditions de tâches
 */
class FenJournee : public QDialog
{
    Q_OBJECT
    QLabel *journee;
    QHBoxLayout *couche;
    QVBoxLayout *couche1, *couche2;
    QListView *lstDeb, *lstFin, *lstEve;
    QScrollArea *sa;
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe FenJournee
     *
     *  \param parent : fenêtre cible
     */
    explicit FenJournee(QWidget *parent = 0);


    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe FenJournee
     *
     */
    ~FenJournee();

private:
    Ui::FenJournee *ui;
};

#endif // FENJOURNEE_H
