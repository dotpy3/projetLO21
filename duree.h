#ifndef DUREE_H
#define DUREE_H
/*!
 * \file duree.h
 * \brief fichier de la classe Duree
 * \author Gourlaouen Penisson
 */

#include <QTime>

#include "calendarexception.h"

/*! \class Duree
 * \brief classe Duree
 *
 *  La classe gere le format des durees de l'application
 */
class Duree
{
    int heure;/*!< heure */
    int minute;/*!< minute */
    int seconde;/*!< seconde */
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe Date
     *
     *  \param h : heure initialisé à 0
     *  \param mi : minute initialisé à 0
     *  \param s : seconde initialisé à 0
     */
    Duree(int h=0,int m=0, int s=0);

    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe Duree
     */
    ~Duree();
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

    /*!  \brief SetDuree
     *
     *  Accesseur en écriture pour modifier la duree
     *
     *  \param h : heure initialisé à 0
     *  \param mi : minute initialisé à 0
     *  \param s : seconde initialisé à 0
     */
    void setDuree(int h=0, int m=0, int s=0);

    /*!  \brief operator+
     *
     *  Definit l'addition de deux durees
     *
     *  \param const Duree& d : duree à ajouter à la date
     *  \return la nouvelle date
     */
    Duree operator+(const Duree& d) const;

    /*!  \brief operator==
     *
     *  Definit l'égalité de deux durees
     *
     *  \param const Duree& d : duree à comparer à la duree courante
     *  \return true si la duree en paramètre est égale à la duree courante, false sinon
     */
    bool operator==(const Duree& d) const;

    /*!  \brief getQTime
     *
     *  Accesseur en lecture d'un objet QTime
     *  \return un objet QTime
     */
    QTime getQTime() const;

    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe Date à partir d'un objet QTime
     *  \param temps : objet QTime
     */
    Duree(QTime temps);
};

#endif // DUREE_H
