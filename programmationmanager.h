#ifndef PROGRAMMATIONMANAGER_H
#define PROGRAMMATIONMANAGER_H

#include <vector>
#include <string>
/*!
 * \file ProgrammationManager
 * \brief fichier de la classe ProgrammationManager
 * \author Gourlaouen Penisson
 */
#include "programmation.h"
#include "tache.h"

class TacheUnitaire;

/*! \class ProgrammationManager
 * \brief classe singleton ProgrammationManager
 *
 *  La classe gere l'accès aux programmation
 */
class ProgrammationManager {
private:
    Programmation** programmations;  /*!< programmations de l'agenda*/
    unsigned int nb; /*!< nb de programmation*/
    unsigned int nbMax; /*!< nb max de programmation*/

    /*!
     *  \brief addItem
     *
     *  Ajoute une programmation
     * \param t : programmation à ajouter
     */
    void addItem(Programmation* t);

    /*!
     *  \brief Constructeur
     *
     *  Constructeur par défaut de la classe ProgrammationManager
     */
    ProgrammationManager();

    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe ProgrammationManager
     */
    ~ProgrammationManager();
public:
    static ProgrammationManager* instance; /*!< instance unique de la classe ProgrammationManager */

    /*!
     *  \brief Constructeur
     *
     *  Constructeur par recopie de la classe ProgrammationManager
     * \param um : instance de la classe ProgrammationManager
     */
    ProgrammationManager(const ProgrammationManager& um);

    /*!
     *  \brief getInstance
     *
     *  Obtient l'unique instance de ProgrammationManager
     * \return reférence vers l'instance
     */
    static ProgrammationManager& getInstance(); //ok

    /*!
     *  \brief libereInstance
     *
     *  Détruit l'unique instance de ProjetManager
     */
    static void libererInstance(); //ok

    /*!
     *  \brief operator=
     *
     *  Définit l'opérateur d'affectation de la classe ProgrammationManager
     * \param Tache& : ref constante vers une ProgrammationManager
     * \return ref vers l'instance
     */
    ProgrammationManager& operator=(const ProgrammationManager& um);

    /*!
     *  \brief ajouterProgrammationTache
     *
     *  Ajoute une programmation de tache
     * \param t : tâche à ajouter
     * \param d : date de début de la programmation
     * \param h : duree de la programmation
     */
    void ajouterProgrammationTache(TacheUnitaire& t, const Date& d, const Duree& h);

    /*!
     *  \brief ajouterProgrammationActivite
     *
     *  Ajoute une programmation d'activité
     * \param s : titre de l'activité
     * \param d : date de début de la programmation
     * \param h : duree de la programmation
     */
    void ajouterProgrammationActivite(const std::string &s,const Date& d, const Duree& h);

    /*!
     *  \brief deleteProgrammation
     *
     *  Supprime une programmation
     * \param prog : programmation à supprimer
     */
    void deleteProgrammation(Programmation* prog);

    /*!
     *  \brief trouverProgrammation
     *
     *  Cherche une programmation d'une tâche
     * \param t : tâche dont on souhaite trouver la programmation
     * \return vecteur des programmations de cette tâche
     */
    std::vector<Programmation*> trouverProgrammation(const Tache& t) const;
};
#include "programmationtache.h"
#include "programmationactivite.h"

#include "tacheunitaire.h"

#endif // PROGRAMMATIONMANAGER_H
