#ifndef CALENDAREXCEPTION_H
#define CALENDAREXCEPTION_H

/*!
 * \file calendarexception.h
 * \brief fichier de la classe CalendarException
 * \author Gourlaouen Penisson
 */
#include <iostream>
#include <string>

/*! \class CalendarException
 * \brief classe CalendarException
 *
 *  La classe gere les exceptions des classes Date et Duree
 */
class CalendarException{
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe CalendarException
     *
     *  \param message : message d'erreur à afficher
     */
    CalendarException(const std::string& message):info(message){}

    /*!
     *  \brief getInfo
     *
     *  Acces en lecture de l'attribut info
     *  \return info sous forme de string
     */
    std::string getInfo() const { return info; }

    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe CalendarException
     */
    ~CalendarException();
private:
    std::string info; /*!< info sur l'erreur */
};

/*!  \brief verifJour
 *
 *   Vérifie si le jour est valide en fonction du jour, mois et annee
 *
 *  \param int j : jour
 *  \param int m : mois
 *  \param int a : annee
 *  \return true si le jour est valide, false sinon
 */
bool verifJour(int j,int m,int a);

/*!  \brief verifMois
 *
 *   Vérifie si le mois est valide
 *
 *  \param int m : mois
 *  \return true si le mois est valide, false sinon
 */
bool verifMois(int m);

/*!  \brief verifHeure
 *
 *   Vérifie si l'heure est valide
 *
 *  \param int h : heure
 *  \return true si l'heure est valide, false sinon
 */
bool verifHeure(int h);

/*!  \brief verifMinute
 *
 *   Vérifie si la minute est valide
 *
 *  \param int m : minute
 *  \return true si la minute est valide, false sinon
 */
bool verifMinute(int m);

/*!  \brief verifSeconde
 *
 *   Vérifie si la seconde est valide
 *
 *  \param int seconde
 *  \return true si la seconde est valide, false sinon
 */
bool verifSeconde(int s);

#endif // CALENDAREXCEPTION_H
