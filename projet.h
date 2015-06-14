#ifndef PROJET_H
#define PROJET_H

/*!
 * \file projet.h
 * \brief fichier de la classe Projet
 * \author Gourlaouen Penisson
 */
#include <string>
#include "date.h"
#include "tache.h"
#include "tachecomposee.h"
#include "tacheunitaire.h"
#include <QFileDialog>
#include <QString>

using namespace std;

/*! \class Projet
 * \brief classe Projet
 *
 *  La classe gere les projets
 */
class Projet
{
private:
    friend class ProjetManager;
    std::string titre; /*!< titre du projet */
    Date* dateDispo; /*!< date de disponibilité du projet */
    Date* dateEcheance; /*!< date d'échéance du projet */
    vector<Tache*> taches; /*!< taches du projet */
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe Projet
     *
     *  \param nTitre : titre du projet
     */
    Projet(const std::string& nTitre):titre(nTitre),dateDispo(0),dateEcheance(0){} // ok

    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe Projet
     */
    ~Projet(); // ok

    /*!
     *  \brief setTitre
     *
     *  Acces en écriture de l'attribut titre
     *  \param titre : titre du projet
     */
    void setTitre(const string& nTitre); // ok

    /*!
     *  \brief getTitre
     *
     *  Acces en lecture de l'attribut titre
     *  \return le titre de la tâche
     */
    string getTitre(); //ok

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
     *  \brief AddTacheComposee
     *
     *  Ajoute une tâche composée au projet
     * \param tacheTitre : titre de la tâche à ajouter
     * \param appartenance : indique si c'est une tâche composite
     * \return pointeur sur la tâche composée ajoutée
     */
    TacheComposee* addTacheComposee(const std::string& tacheTitre, TacheComposee* appartenance=0); //ok

    /*!
     *  \brief AddTacheUnitaire
     *
     *  Ajoute une tâche unitaire au projet
     * \param tacheTitre : titre de la tâche à ajouter
     * \param preemp : indique si la tâche est preemptable
     * \param d : durée de la tâche
     * \param appartenance : indique si c'est une tâche composite
     * \return pointeur sur la tâche composée ajoutée
     */
    TacheUnitaire* addTacheUnitaire(const std::string& tacheTitre, bool preemp, Duree d, TacheComposee* appartenance=0); //ok

    /*!
     *  \brief deleteTache
     *
     *  Supprime une tâche du projet
     * \param tache : tâche à supprimer
    */
    void deleteTache(Tache* tache); //ok

    /*!
     *  \brief containsTache
     *
     *  Cherche si la tâche appartient au projet courant
     * \param tache : tâche cherchée
     * \return true si elle appartient, false sinon
    */
    bool containsTache(Tache* tache);

    /*!
     *  \brief getTache
     *
     *  Obtient une tâche à partir de son nom
     * \param nomTache : nom de la tâche
     * \return pointeur sur la tâche
    */
    Tache* getTache(std::string nomTache);

    /*!
     *  \brief getParente
     *
     *  Obtient les tâches parentes d'une tâche
     * \param tache : tâche dont on souhaite connaître les tâches parentes
     * \return vecteur des tâches parentes
    */
    vector<TacheComposee*> getParente(Tache* tache);

    /*!
     *  \brief getListeTotaleTaches
     *
     *  Obtient toutes les tâches d'un projet
     * \return vecteur des tâches d'un projet
    */
    vector<Tache*> getListeTotaleTaches();

    /*!
     *  \brief premiersEnfants
     *
     *  Obtient les premières tâches d'un projet
     * \return vecteur des premières tâches d'un projet
    */
    vector<Tache*> premiersEnfants();

    /*!
     *  \brief exportXML
     *
     *  Gère l'export en XML des tâches d'un projet
     * \return vecteur des tâches parentes
    */
    void exportXML(QWidget* fenparent);
};

#endif // PROJET_H
