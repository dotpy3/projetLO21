#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H
/*!
 * \file programmation.h
 * \brief fichier de la classe programmation
 * \author Gourlaouen Penisson
 */

#include "date.h"
#include "duree.h"

/*! \class Programmation
 * \brief classe Proogrammation
 *
 *  La classe gere les programmations de l'agenda
 */

class Programmation
{
private:
    friend class ProgrammationManager;
    friend class TacheUnitaire;
    Date debut; /*!< date de début de la programmation */
    Duree duree; /*!< duree de la programmation */
protected:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur par défaut de la classe Programmation
     *
     */
    Programmation();

    /*!
     *  \brief Constructeur de recopie
     *
     *  Constructeur de recopie de la classe Programmation
     * \param dateDonnee : date de la programmation
     * \param dureeDonnee : duree de la programmation
     */
    Programmation(const Date& dateDonnee, const Duree& dureeDonnee);

    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe Programmation
     *
     */
    virtual ~Programmation();
public:

    /*!
     *  \brief getDuree
     *
     *  Acces en lecture de l'attribut duree
     *  \return un objet Duree
     */
    Duree getDuree();

    /*!
     *  \brief getDebut
     *
     *  Acces en lecture de l'attribut debut
     *  \return un objet Date
     */
    Date getDebut();

    /*!
     *  \brief getDebut
     *
     *  Calcul la date de fin la programmation en fonction du debut et de la duree
     *  \return un objet Date
     */
    Date getFin();

    /*!
     *  \brief setDuree
     *
     *  Acces en écriture de l'attribut duree
     *  \param d : duree à modifier
     */
    void setDuree(const Duree& d);

    /*!
     *  \brief setDebut
     *
     *  Acces en écriture de l'attribut debut
     *  \param d : date à modifier
     */
    void setDebut(const Date& d);
};


#include "programmationmanager.h"

#endif // PROGRAMMATION_H
