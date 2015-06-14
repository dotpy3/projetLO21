#ifndef FENGESTIONPRECEDENCE_H
#define FENGESTIONPRECEDENCE_H
/*!
 * \file fengestionprecedence.h
 * \brief fichier de la fengestionprecedence
 * \author Gourlaouen Penisson
 */

#include <QDialog>


/*! \class fengestionprecedence
 * \brief classe fengestionprecedence hérite QDialog
 *
 *  La classe gere l'interface de gestion des précédences de tâches
 */
class fengestionprecedence : public QDialog
{
    Q_OBJECT

public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe fengestionprecedence
     *
     *  \param parent : fenêtre cible
     */
    explicit fengestionprecedence(QWidget *parent = 0);

    /*!
     *  \brief Constructeur
     *
     *  Destructeur de la classe fengestionprecedence
     *
     */
    ~fengestionprecedence();

private:
    fengestionprecedence *ui;
};
#endif // FENGESTIONPRECEDENCE_H
