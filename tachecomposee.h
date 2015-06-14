#ifndef TACHECOMPOSEE_h
#define TACHECOMPOSEE_h
/*!
 * \file tachecomposee.h
 * \brief fichier de la classe TacheUnitaire
 * \author Gourlaouen Penisson
 */
#include<string>
#include<iostream>
#include "tache.h"

using namespace std;

/*! \class TacheComposee
 * \brief classe TacheComposee hérite de Tache
 *
 *  La classe gere les taches composees des projets
 */
class TacheComposee : public Tache {
    friend class Projet;
    Tache** listeTaches; /*!< liste des taches */
    int nb, nbMax; /*!< nb de tâches, nb max de tâches */

    /*! \class TacheComposee
     * \brief classe itérator de la classe TacheComposee
     *
     *  La classe gère l'itération sur les taches composees des projets
     */
	class TacheComposeeIterator{
		friend class TacheComposee;
        /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe TacheComposee
         *
         *  \param n : indice de la tâche
         *  \param IT : tâche composite
         */
		TacheComposeeIterator(int n, Tache** lT); // OK : non testé
        int nb, pointer; /*!< nb de tâche, indice de la tâche courante */
        Tache** listeTachesIt; /*!< liste des tâches composites */
	public:
        /*!
         *  \brief current
         *
         *  Définit la tâche courante
         * \return pointeur sur tâche courante
         */
		Tache* current(); // OK : non testé

        /*!
         *  \brief isDone()
         *
         *  Teste si on est arrivé à la fin de l'arborescence
         * \return true si fin, false sinon
         */
        bool isDone(); // OK : non testé

        /*!
         *  \brief next
         *
         *  Pointe sur la tâche suivante
         */
		void next(); // OK : non testé
    };

    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe TacheComposee
     *
     *  \param unique_t : titre de la tâche
     */
    TacheComposee(const string& unique_t):Tache(unique_t),listeTaches(0){}

    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe TacheComposee
     */
    ~TacheComposee();
public:
    /*!
     *  \brief AddTacheToCompo
     *
     *  Ajoute une tâche à la tâche composée
     * \param tache : tâche à ajouter
     */
	void AddTacheToCompo(Tache* tache); // OK : testé

    /*!
     *  \brief DeleteTacheFromCompo
     *
     *  Supprime une tâche à la tâche composée
     * \param tache : tâche à supprimer
    */
	void DeleteTacheFromCompo(Tache* tache); // OK : testé

    /*!
     *  \brief getListeTaches
     *
     *  Renvoie toutes les tâches composites
     * \return liste des tâches composites
     */
    Tache** getListeTaches(); // OK : testé

    /*!
     *  \brief getNbTaches
     *
     *  Acces en lecture de l'attribut nb
     *  \return le titre de la tâche
     */
    int getNbTaches(){ return nb; }

    /*!
     *  \brief getIterator
     *
     *  Acces à l'itérateur de la classe TacheComposee
     *  \return l'itérateur de la classe TacheComposee
     */
	TacheComposeeIterator getIterator();

    /*!
     *  \brief IsPlanifiee
     *
     *  Vérifie si la tâche est planifiee
     *  \return true si elle est planifiee, false sinon
     */
	bool IsPlanifiee(); // OK : testé

    /*!
     *  \brief isTacheComposee
     *
     *  vérifie si la tâche est composee
     *  \return true si elle est composee, false sinon
     */
    bool isTacheComposee();

    /*!
     *  \brief isInListeDeCompositions
     *
     *  vérifie si la tâche t est composite de la tâche composee
     * \param t : tâche
     *  \return true si elle est composite, false sinon
     */
    bool isInListeDeCompositions(Tache* t);

    /*!
     *  \brief isTacheComposee
     *
     *  vérifie si la tâche t est dans l'arborescence
     * \param t : tâche
     *  \return true si elle est composee, false sinon
     */
    bool Composes(Tache* t);

    /*!
     *  \brief cheminTo
     *
     *  Trouve la tâche dans la tâche composee
     * \param t : tâche dont on souhaite connaître l'arborescence
     * \return l'arborescence jusqu'à la tâche t
     */
    vector<TacheComposee*> cheminTo(Tache* t);

    /*!
     *  \brief listeTotaleSousTaches
     *
     *  Trouve les sous tâches de la tâche composee
     * \return l'arborescence de la tâche composee
     */
    vector<Tache*> listeTotaleSousTaches();
};
#endif
