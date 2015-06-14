#ifndef PROGRAMMATIONTACHE_H
#define PROGRAMMATIONTACHE_H
/*!
 * \file programmatiotache.h
 * \brief fichier de la classe ProgrammationTache
 * \author Gourlaouen Penisson
 */

#include "tache.h"
#include "programmation.h"

class TacheUnitaire;

/*! \class ProgrammationTache
 * \brief classe ProogrammationTache
 *
 *  La classe gere les programmations de tâches de l'agenda
 */
class ProgrammationTache : public Programmation{
private:
	friend class ProgrammationTache;
    friend class ProgrammationManager;
    TacheUnitaire* tacheAssociee; /*!< tâche associée à la programmation */
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe ProgrammationTache
     */
    ProgrammationTache():tacheAssociee(0){};

    /*!
     *  \brief Constructeur de recopie
     *
     *  Constructeur de recopie de la classe ProgrammationTache
     * \param dateDonnee : date de la programmation
     * \param dureeDonnee : duree de la programmation
     * \param tacheAssoc : tâche à programmer
     */
	ProgrammationTache(const Date& dateDonnee, const Duree& dureeDonnee, TacheUnitaire* tacheAssoc):Programmation(dateDonnee,dureeDonnee),tacheAssociee(tacheAssoc){}

    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe ProgrammationTache
     */
    ~ProgrammationTache();
public:


    /*!
     *  \brief getTacheAssociee
     *
     *  Acces en lecture de l'attribut tacheAssociee
     *  \return un pointeur sur la tâche unitaire associée
     *
     */
	TacheUnitaire* getTacheAssociee();
};

#include "tacheunitaire.h"

#endif // PROGRAMMATIONTACHE_H
