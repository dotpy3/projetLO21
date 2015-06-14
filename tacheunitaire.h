#ifndef TACHEUNITAIRE_h
#define TACHEUNITAIRE_h
/*!
 * \file tacheunitaire.h
 * \brief fichier de la classe TacheUnitaire
 * \author Gourlaouen Penisson
 */


#include <string>
#include <iostream>
#include "tache.h"
#include <vector>

/*! \class TacheUnitaire
 * \brief classe TacheUnitaire hérite de Tache
 *
 *  La classe gere les taches unitaires des projets
 */
class TacheUnitaire : public Tache {
    friend class Projet;
private:
    Duree duree; /*!< durée de la tâche */
    bool preemptable; /*!< indique si la tâche est interruptible */
	
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe TacheUnitaire
     *
     *  \param titre : titre de la tâche
     *  \param d : duree de la tâche
     *  \param p : attribut preemptable de la tâche
     */
    TacheUnitaire(const std::string &titre,Duree d, bool p):Tache(titre),duree(d),preemptable(p){}

    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe TacheUnitaire
     */
    ~TacheUnitaire();
public:

    /*!
     *  \brief EstPreemptable
     *
     *  Acces en lecture de l'attribut preemptable
     *  \return true si elle est preemptable, false sinon
     */
	bool EstPreemptable() const { return preemptable;}

    /*!
     *  \brief GetDuree
     *
     *  Acces en lecture de l'attribut duree
     *  \return un objet de type Duree
     */
	Duree GetDuree() const { return duree;}

    /*!
     *  \brief GetDuree
     *
     *  Acces en écriture de l'attribut duree
     *  \param duree : duree de la tâche
     */
    void setDuree(Duree duree);

    /*!
     *  \brief IsPlanifiee
     *
     *  Vérifie si la tâche est planifiee
     *  \return true si elle est planifiee, false sinon
     */
    bool IsPlanifiee();

    /*!
     *  \brief deleteTachesAssociees
     *
     *  supprime les programmations liées à cette tâche
     */
    void deleteTachesAssociees();

    /*!
     *  \brief isTacheComposee
     *
     *  vérifie si la tâche est composee
     *  \return true si elle est composee, false sinon
     */
    bool isTacheComposee();
};
#include "programmation.h"
#include "programmationmanager.h"
#include "programmationtache.h"²
#endif
