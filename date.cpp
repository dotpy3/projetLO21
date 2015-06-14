#include "date.h"

using namespace std;

Date::~Date()
{

}

Date::Date(const QString& xmlDate){
    std::string dateString = xmlDate.toStdString();
    jour = stoi(dateString.substr(0,2));
    mois = stoi(dateString.substr(3,2));
    annee = stoi(dateString.substr(6,4));
    heure = stoi(dateString.substr(11,2));
    minute = stoi(dateString.substr(14,2));
    seconde = stoi(dateString.substr(17,2));
}

Date::Date(int j,int mo,int a,int h,int mi,int s){
	setDate(j,mo,a,h,mi,s);
}

int Date::getJour() const{
	return jour;
}
int Date::getMois() const{
	return mois;
}
int Date::getAnnee() const{
	return annee;
}
int Date::getHeure() const{
	return heure;
}
int Date::getMinute() const{
	return minute;
}
int Date::getSeconde() const{
	return seconde;
}

QDateTime Date::getQDateTime() const{
    QDate formatedD;
    formatedD.setDate(annee,mois,jour);
    QTime formatedT;
    formatedT.setHMS(heure,minute,seconde);
    QDateTime formated(formatedD,formatedT);
    return formated;
}


void Date::setDate(int j,int mo,int a,int h,int mi,int s){
	if (!verifJour(j,mo,a)
	|| !verifMois(mo)
	|| !verifHeure(h)
	|| !verifMinute(mi)
	|| !verifSeconde(s)) throw CalendarException("Date indiquée invalide");
	jour = j;
	mois = mo;
	annee = a;
	heure = h;
	minute = mi;
	seconde = s;
}

Date Date::operator+(const Duree& d) const{
	int h, m, s, j, mo, a, reserve=0;

	// SECONDE
	s = getSeconde() + d.getSeconde();
	if (!verifSeconde(s)){
		s = s%60;
		reserve = 1;
	}

	// MINUTE
	m = getMinute() + d.getMinute() + reserve;
	if (!verifMinute(m)){
		m = m%60;
		reserve = 1;
	} else {
		reserve = 0;
	}

	// HEURE
	h = getHeure() + d.getHeure() + reserve;
	if (!verifHeure(h)){
		h = h%24;
		reserve = 1;
	} else {
		reserve = 0;
	}

	// JOUR
    j = jour;
	j += reserve;
	if (!verifJour(j,getMois(),getAnnee())){
		j = 1;
		reserve = 1;
	} else {
		reserve = 0;
	}

    // ANNEE
    a = annee;

	// MOIS
    mo = mois;
	mo += reserve;
	if (!verifMois(mo)){
		a += 1;
		mo = 1;
	}

	Date dateRetour(j,mo,a,h,m,s);
	return dateRetour;
}

std::string Date::getFormatedTime() const{
    std::string resultat("");

    if(jour < 10) resultat+="0";
    resultat+=to_string(jour);

    resultat+="-";

    if(mois < 10) resultat+="0";
    resultat+=to_string(mois);

    resultat+="-";

    if(annee < 10) resultat+="000";
    else if(annee < 100) resultat +="00";
    else if(annee < 1000) resultat +="0";
    resultat+=to_string(annee);

    if(heure < 10) resultat+="0";
    resultat+=to_string(heure);

    resultat+=":";

    if(minute < 10) resultat+="0";
    resultat+=to_string(minute);

    resultat+=":";

    if(seconde < 10) resultat+="0";
    resultat+=to_string(seconde);

    return resultat;
}

bool Date::operator<(const Date& d) const{
    if (annee < d.getAnnee()) return true;
    else if (annee > d.getAnnee()) return false;

    // annee identique

    if(mois < d.getMois()) return true;
    else if (mois > d.getMois()) return false;

    // mois identique

    if (jour < d.getJour()) return true;
    else if (jour > d.getJour()) return false;

    // jour identique

    if (heure < d.getHeure()) return true;
    else if (heure > d.getHeure()) return false;

    // heure identique

    if (minute < d.getMinute()) return true;
    else if (minute > d.getMinute()) return false;

    // minute identique

    if (seconde < d.getSeconde()) return true;
    else return false;

}
