#include "duree.h"

Duree::~Duree()
{

}

Duree::Duree(int h,int m, int s){
	if (!verifHeure(h)
		|| !verifMinute(m)
		|| !verifSeconde(s)){
		throw CalendarException("Durée indiquée invalide");
	}
	heure = h;
	minute = m;
	seconde = s;
}

int Duree::getHeure() const{
	return heure;
}

int Duree::getMinute() const{
	return minute;
}

int Duree::getSeconde() const{
	return seconde;
}

void Duree::setDuree(int h, int m, int s){
	if (!verifHeure(h)
		|| !verifMinute(m)
		|| !verifSeconde(s)){
		throw CalendarException("Durée indiquée invalide");
	}
	heure = h;
	minute = m;
	seconde = s;
}

Duree Duree::operator+(const Duree& d) const{
	int s,m,h,reserve=0;
	s = d.getSeconde() + getSeconde();
	if (s >= 60){
		s = s % 60;
		reserve = 1;
	}
	m = d.getMinute() + getMinute() + reserve;
	if (m >= 60){
		m = m % 60;
		reserve = 1;
	} else {
		reserve = 0;
	}
	h = d.getHeure() + getHeure() + reserve;
	Duree dureeFinale(h,m,s);
	return dureeFinale;
}

bool Duree::operator==(const Duree& d) const{
	if (getHeure() == d.getHeure()
		&& getMinute() == d.getMinute()
		&& getSeconde() == d.getSeconde()) return true;
	return false;
}

QTime Duree::getQTime() const{
    QTime formatedT;
    formatedT.setHMS(heure,minute,seconde);
    return formatedT;
}


Duree::Duree(QTime temps){
    heure = temps.hour();
    minute = temps.minute();
    seconde = temps.second();
}
