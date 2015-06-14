#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H
/*!
 * \file projetmanager
 * \brief fichier de la classe ProjetManager
 * \author Gourlaouen Penisson
 */
#include <string>
#include "projet.h"
#include "tache.h"
#include "Date.h"
#include <QtXml>
#include <QString>
#include <QDomDocument>
#include <QMessageBox>
#include <cstring>
#include <stdlib.h>

class Projet;


/*! \class ProjetManager
 * \brief classe singleton ProjetManager
 *
 *  La classe gere l'accès aux projets
 */
class ProjetManager
{
private:
    Projet** tabProjets; /*!< projets de l'application*/
    int nbProjets; /*!< nb de projet */
    int nbProjetsMax; /*!< nb max de projet */

    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe ProjetManager
     */
    ProjetManager(); //ok

    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe ProjetManager
     */
    ~ProjetManager(); //ok
public:
    static ProjetManager* instance; /*!< instance unique de la classe ProjetManager */

    /*! \class Iterator
     * \brief classe itérator de la classe ProjetManager
     *
     *  La classe gère l'itération sur les projets
     */
    class Iterator{
        friend class ProjetManager;
    private:
        /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe TacheComposee
         *
         *  \param nbProj : nb de projets
         *  \param nbMaxProj : nb max de projets
         */
        Iterator(int nbProj, int nbMaxProj, Projet** projets); //ok
  //      ~Iterator(); //ok
        Projet** instance; /*!< projet courant */
        int nb, nbMax, currentIndex; /*!< nb de projets, nb max de projet ; indice du projet courant */
    public:
        /*!
         *  \brief current
         *
         *  Définit le projet courant
         * \return pointeur sur projet courante
         */
        Projet* current(); // OK

        /*!
         *  \brief isDone()
         *
         *  Teste si on est arrivé à la fin de la liste des projets
         * \return true si fin, false sinon
         */
        bool isDone(); // OK :

        /*!
         *  \brief next
         *
         *  Pointe sur le projet suivant
         */
        void next(); // OK
    };
public: 
    /*!
     *  \brief getInstance
     *
     *  Obtient l'unique instance de ProjetManager
     * \return reférence vers l'instance
     */
    static ProjetManager& getInstance(); //ok

    /*!
     *  \brief libereInstance
     *
     *  Détruit l'unique instance de ProjetManager
     */
    static void libererInstance(); //ok

    /*!
     *  \brief ajouterProjet
     *
     *  Ajoute un projet
     * \param t : projet à ajouter
     */
    void ajouterProjet(Projet* t); //ok

    /*!
     *  \brief supprimerProjet
     *
     *  Supprime un projet
     * \param t : projet à supprimer
     */
    void supprimerProjet(Projet* t); //ok

    /*!
     *  \brief creerProjet
     *
     *  Crée un projet
     * \param nomProjet : nom du projet à créer
     * \return pointeur vers le projet créé
     */
    Projet* creerProjet(std::string nomProjet); //ok

    /*!
     *  \brief creerProjetXML;
     *
     *  Crée un projet à partir d'un fichier XML
     * \param adresseXML : chemin du fichier XML
     * \param fenetre : fenetre cible
     */
    void creerProjetXML(QString adresseXML, QWidget* fenetre);

    /*!
     *  \brief getProjet
     *
     *  obtient un projet à partir de son nom
     * \param nomProjet : nom du projet
     * \return pointeur sur le projet
     */
    Projet* getProjet(std::string nomProjet); //ok


    /*!
     *  \brief getNbTache
     *
     *  Obtient le nombre de tache de tous les projets
     *  \return le nombre de tache de tous les projets
     */
    int getNbTache(); // ok


    /*!
     *  \brief getIterator
     *
     *  Acces à l'itérateur de la classe ProjetManager
     *  \return l'itérateur de la classe ProjetManager
     */
    Iterator getIterator(); // ok

    /*!
     *  \brief getProjetAssocie
     *
     *  obtient un projet à partir d'une tâche
     * \param t : tâche dont on souhaite connaître le projet associé
     * \return référence sur le projet
     */
    Projet& getProjetAssocie(Tache* t);
};

#endif // PROJETMANAGER_H
