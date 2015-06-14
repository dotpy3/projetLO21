#ifndef FENCREATEEVE_H
#define FENCREATEEVE_H
/*!
 * \file fencreateeve.h
 * \brief fichier de la classe FenCreateEve
 * \author Gourlaouen Penisson
 */


#include <QMessageBox>
#include <QDialog>
#include <QString>
#include <QDate>
#include <QTime>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QWidget>
#include <QTimeEdit>
#include <QMessageBox>
#include <QObject>
#include "duree.h"
#include "date.h"
#include "tacheunitaire.h"
#include <QComboBox>
#include <QDialog>
#include <QVariant>
#include "projetmanager.h"
#include <vector>
#include "calendarexception.h"

namespace Ui {
class FenCreateEve;
}

/*! \class FenCreateEve
 * \brief classe FenCreateEve hérite QWidget
 *
 *  La classe gere l'interface d'ajout d'activité
 */
class FenCreateEve : public QWidget
{
    Q_OBJECT
        TacheUnitaire &t;
        QHBoxLayout *couche;
        QVBoxLayout *couche1, *couche2,*couche3;
        QLabel *createEve, *tacheAsso, *date, *duree;
        QPushButton *annuler, *sauver;
        QDateEdit *dateDeb;
        QTimeEdit *dur;
        QComboBox *tache;
        vector<Tache*> lesTaches;
        QLineEdit *textTitre;
        QLabel* titre;

public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe fencreateactivite
     *
     *  \param ta : tâche à programmer
     *  \param parent : fenêtre cible
     */
    explicit FenCreateEve(TacheUnitaire &ta, QWidget *parent = 0);

    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe FenCreateEve
     *
     */
     ~FenCreateEve();

    /*!
     *  \brief remplirCombobox
     *
     *  Remplit la combobox des tâches unitaire à programmer
     *
     */
     void remplirCombobox(QComboBox *t);
private slots:
    /*!
     *  \brief on_btnSave_clicked
     *
     *  slot gérant la sauvegarde de l'activité
     *
     */
    void on_btnSave_clicked();

    /*!
     *  \brief on_btnCancel_clicked
     *
     *  slot gérant l'annulation des infos saisies
     *
     */
    void on_btnCancel_clicked();

private:
    Ui::FenCreateEve *ui;
};

#endif // FENCREATEEVE_H
