#ifndef PROGRAMMATIONACTI_H
#define PROGRAMMATIONACTI_H

/*!
 * \file programmationactivite.h
 * \brief fichier de la classe ProgrammationActivite
 * \author Gourlaouen Penisson
 */

#include <iostream>
#include <string>
#include "programmation.h"

/*! \class ProgrammationActivite
 * \brief classe ProogrammationActivite
 *
 *  La classe gere les programmations d'activité de l'agenda
 */
class ProgrammationActivite: public Programmation{

private:
    std::string titre; /*!< titre de l'activité */

public:

    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe ProgrammationActivite
     * \param s : titre de l'activite
     * \param d : date de la programmation
     * \param h : duree de la programmation
     */
    ProgrammationActivite(const std::string &s, const Date& d, const Duree& h):Programmation(d,h),titre(s){}

    /*!
     *  \brief getTitre
     *
     *  Acces en lecture de l'attribut titre
     *  \return le titre de l'activite
     */
    std::string getTitre();

    /*!
     *  \brief setTitre
     *
     *  Acces en écriture de l'attribut titre
     *  \param s : titre de l'activité
     */
    void setTitre(const std::string &s);
};

#endif
