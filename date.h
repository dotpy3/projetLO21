#ifndef DATE_H
#define DATE_H

/*!
 * \file date.h
 * \brief fichier de la classe Date
 * \author Gourlaouen Penisson
 */
#include "duree.h"
#include "calendarexception.h"
#include <QDateTime>
#include <QString>
#include <string>
#include <iostream>
#include <QTime>

/*! \class Date
 * \brief classe Date
 *
 *  La classe gere le format des dates de l'application
 */
class Date
{
    int jour; /*!< jour */
    int mois; /*!< mois */
    int annee;/*!< annee */
    int heure;/*!< heure */
    int minute;/*!< minute */
    int seconde;/*!< seconde */
public:
   /*!
    *  \brief Constructeur
    *
    *  Constructeur de la classe Date
    *
    *  \param j : jour initialisé à 1
    *  \param mo : mois initialisé à 1
    *  \param a : annee initialisé à 2015
    *  \param h : heure initialisé à 0
    *  \param mi : minute initialisé à 0
    *  \param s : seconde initialisé à 0
    */
    Date(int j=1,int mo=1,int a=2015,int h=0,int mi=0,int s=0);

    Date(const QString& xmlDate);

    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe Date
     */
    ~Date();

   /*!
    *  \brief getJour
    *
    *  Acces en lecture de l'attribut jour
    *  \return le jour sous forme d'entier
    */
    int getJour() const;

    /*!
     *  \brief getMois
     *
     *  Acces en lecture de l'attribut mois
     *  \return le mois sous forme d'entier
     */
    int getMois() const;

    /*!
     *  \brief getAnnee
     *
     *  Acces en lecture de l'attribut annee
     *  \return l'annee sous forme d'entier
     */
    int getAnnee() const;

    /*!
     *  \brief getHeure
     *
     *  Acces en lecture de l'attribut heure
     *  \return l'heure sous forme d'entier
     */
    int getHeure() const;

    /*!
     *  \brief getMinute
     *
     *  Acces en lecture de l'attribut minute
     *  \return la minute sous forme d'entier
     */
    int getMinute() const;

    /*!
     *  \brief getSeconde
     *
     *  Acces en lecture de l'attribut seconde
     *  \return la seconde sous forme d'entier
     */
    int getSeconde() const;

   /*!  \brief SetDate
    *
    *  Accesseur en écriture pour modifier la date
    *
    *  \param j : jour initialisé à 1
    *  \param mo : mois initialisé à 1
    *  \param a : annee initialisé à 2015
    *  \param h : heure initialisé à 0
    *  \param mi : minute initialisé à 0
    *  \param s : seconde initialisé à 0
    */
    void setDate(int j=1,int mo=1,int a=2015,int h=0,int mi=0,int s=0);

   /*!  \brief operator+
    *
    *  Definit l'addition d'une duree à une date
    *
    *  \param const Duree& d : duree à ajouter à la date
    *  \return la nouvelle date
    */
    Date operator+(const Duree& d) const;

   /*!  \brief getQDateTime
    *
    *  Accesseur en lecture d'un objet QDateTime
    *  \return un objet QDateTime
    */
    QDateTime getQDateTime() const;

    /*!  \brief getFormatedTime
     *
     *  Formate la date
     *  \return la date sous forme jj-mm-aaaa hh:mm:ss en string
     */
    std::string getFormatedTime() const;

    /*!  \brief operator <
     *
     *  Compare deux date
     *  \param d : date à comparer
     *  \return true si la date courante est inférieure à d
     */
    bool operator<(const Date& d) const;
};

#endif // DATE_H
