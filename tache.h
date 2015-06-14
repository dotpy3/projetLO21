#ifndef TACHE_h
#define TACHE_h

/*!
 * \file tache.h
 * \brief fichier des classes Tache et TacheException
 * \author Gourlaouen Penisson
 */

#include <string>
#include <iostream>
#include <vector>
#include "date.h"
#include <QtXml>

using namespace std;
class TacheComposee;
class ProjetManager;

/*! \class Tache
 * \brief classe Tache abstraite
 *
 *  La classe gere les taches des projets
 */
class Tache {
    std::string unique_titre; /*!< titre de la tâche */
    //interdire creation tache par utilisateur
    friend class Projet;
    friend class TacheComposee;
protected:

    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe Tache
     *
     *  \param unique_t : titre de la tâche
     */
    Tache(const std::string& unique_t):unique_titre(unique_t),precedence(0),nbPrecedences(0),nbPrecedencesMax(0),dateDispo(0),dateEcheance(0){}

    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe Tache
     */
    virtual ~Tache(); // OK : non test�

    /*!
     *  \brief Constructeur de recopie
     *
     *  Constructeur de recopie de la classe Tache
     */
	Tache(const  Tache &t){
		unique_titre = t.unique_titre;
	}

    /*!
     *  \brief operator=
     *
     *  Définit l'opérateur d'affectation de la classe Tache
     * \param Tache& : ref constante vers une Tache
     * \return ref vers une tache
     */
	Tache & operator=(const Tache&);


    Tache ** precedence;/*!< tache précédente */
    int nbPrecedences; /*!< nb de précédences */
    int nbPrecedencesMax; /*!< nb max de précédences */
    Date* dateDispo; /*!< date de disponibilité */
    Date* dateEcheance; /*!< date d'échéance */
public:

    /*!
     *  \brief getTitre
     *
     *  Acces en lecture de l'attribut titre
     *  \return le titre de la tâche
     */
	std::string getTitre() const { return unique_titre; } // OK : test�

    /*!
     *  \brief getContraintes
     *
     *  Acces en lecture de l'attribut precedence
     *  \return un double pointeur sur les tâches précédente
     */
	Tache** getContraintes(){ return precedence; }

    /*!
     *  \brief setTitre
     *
     *  Acces en écriture de l'attribut unique_titre
     *  \param titre : titre de la tâche
     */
    void setTitre(const string& titre){ unique_titre = titre; }

    /*!
     *  \brief IsPlanifiee
     *
     *  méthode virtuelle vérifiant si la tâche est planifiee
     *  \return true si elle est planifiee, false sinon
     */
	virtual bool IsPlanifiee() = 0;

    /*!
     *  \brief addContrainte
     *
     *  Ajoute une tâche en contrainte de précédence
     * \param contrainte : tâche à ajouter en contrainte de précédence
     */
    void addContrainte(Tache* contrainte); // ok

    /*!
     *  \brief deleteContrainte
     *
     *  Supprime une tâche en contrainte de précédence
     * \param contrainte : tâche à supprimer en contrainte de précédence
     */
    void deleteContrainte(Tache* contrainte); // ok

    /*!
     *  \brief setDateDisp
     *
     *  Acces en écriture de l'attribut dateDispo
     *  \param disp : date de disponibilité de la tâche
     */
    void setDateDisp(const Date& disp); //ok

    /*!
     *  \brief setDateEch
     *
     *  Acces en écriture de l'attribut dateEcheance
     *  \param ech : date d'échéance de la tâche
     */
    void setDateEch(const Date& ech); //ok

    /*!
     *  \brief removeDateDispo
     *
     *  Supprime la date de disponibilité d'une tâche
     */
    void removeDateDispo(); //ok

    /*!
     *  \brief removeDateEcheance
     *
     *  Supprime la date d'échéance d'une tâche
     */
    void removeDateEcheance(); //ok

    /*!
     *  \brief isDateDispo
     *
     *  vérifie si la date de disponibilité d'une tâche est non nulle
     * \return true si non nul, false sinon
     */
    bool isDateDisp(); //ok

    /*!
     *  \brief isDateEcheance
     *
     *  vérifie si la date d'échéance d'une tâche est non nulle
     * \return true si non nul, false sinon
     */
    bool isDateEcheance(); //ok

    /*!
     *  \brief getDateDisp
     *
     *  Acces en lecture de l'attribut dateDispo
     *  \return un objet Date
     */
    Date getDateDisp(); //ok

    /*!
     *  \brief getDateEcheance
     *
     *  Acces en lecture de l'attribut dateEcheance
     *  \return un objet Date
     */
    Date getDateEcheance(); //ok

    /*!
     *  \brief isCompositionOf
     *
     *  teste si cette tache fait partie d'un arbre de composition dont t est la racine
     * \param t : tache composee
     * \return true si la tache en cours fait partie de l'arbre, false sinon
     */

    bool isCompositionOf(TacheComposee* t);

    /*!
     *  \brief isIndirectlyPrecededBy
     *
     *  teste si cette tache est indirectement précédée par t
     * \param t : tache
     * \return true si c'est vérifié, false sinon
     */
    bool isIndirectlyPrecededBy(Tache* t);

    /*!
     *  \brief isPrecededBy
     *
     *  teste si cette tache est  précédée par t
     * \param t : tache
     * \return true si c'est vérifié, false sinon
     */
    bool isPrecededBy(Tache* t);

    /*!
     *  \brief canBePrecedence
     *
     *  teste si cette tache peut être précédée par t
     * \param t : tache
     * \return true si c'est vérifié, false sinon
     */
    bool canBePrecedence(Tache* t);

    /*!
     *  \brief isTacheComposee
     *
     *  méthode virtuelle vérifiant si la tâche est composee
     *  \return true si elle est composee, false sinon
     */
    virtual bool isTacheComposee() = 0;

    /*!
     *  \brief getTachesParentes
     *
     *  retourne les tâches parentes de la tâche est en cours
     *  \return vecteur de pointeur de taches composées  des taches parentes
     */
    vector<TacheComposee*> getTachesParentes();

    /*!
     *  \brief canBeSetAtThisDate
     *
     *  Vérifie si la tâche peut être programmée à la date choisie
     *  \param dateChoisie : date à laquelle on souhaite programmer la tâche
     *  \return true si elle peut être programmée, false sinon
     */
    bool canBeSetAtThisDate(Date dateChoisie);


    /*!
     *  \brief writeOnto
     *
     *  permet de réaliser le fichier pour l'export en XML
     *  \param xmlStream : flux XML
     */
    void writeOnto(QXmlStreamWriter* xmlStream);
};


/*! \class TacheException
 * \brief classe TacheException
 *
 *  La classe gere les exceptions de la classe Tache
 */
class TacheException{
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe TacheException
     *
     *  \param message : message d'erreur à afficher
     */
    TacheException(const std::string& message):info(message){}

    /*!
     *  \brief getInfo
     *
     *  Acces en lecture de l'attribut info
     *  \return info sous forme de string
     */
    std::string getInfo() const { return info; }

  private:
    std::string info; /*!< info sur l'erreur */
};

#include "programmationmanager.h"
#include "tachecomposee.h"
#include "projetmanager.h"

#endif
