#ifndef FENCREATEACTIVITE_H
#define FENCREATEACTIVITE_H
/*!
 * \file fencreateactivite.h
 * \brief fichier de la classe fencreateactivite
 * \author Gourlaouen Penisson
 */


#include <QWidget>

/*! \class fencreateactivite
 * \brief classe fencreateactivite hérite QWidget
 *
 *  La classe gere l'interface d'ajout de tâches
 */
class fencreateactivite:public QWidget
{
    Q_OBJECT
       /* TacheUnitaire &t;
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
*/
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe fencreateactivite
     *
     *  \param parent : fenêtre cible
     */
    fencreateactivite(QWidget* parent = 0);

    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe fencreateactivite
     *
     */
    ~fencreateactivite();
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
};

#endif // FENCREATEACTIVITE_H
