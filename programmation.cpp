#include "programmation.h"

Programmation::Programmation(){
	Date* ndate = new Date;
	Duree* nduree = new Duree;
	debut = *ndate;
	duree = *nduree;
	delete ndate;
	delete nduree;
}

Programmation::Programmation(const Date& dateDonnee, const Duree& dureeDonnee)
{
	debut = dateDonnee;
	duree = dureeDonnee;
}

Programmation::~Programmation()
{

}


Duree Programmation::getDuree(){
	return duree;
}
Date Programmation::getDebut(){
	return debut;
}
Date Programmation::getFin(){
    Date fin = debut + duree;
	return fin;
}

void Programmation::setDuree(const Duree& d){
	duree = d;
}
void Programmation::setDebut(const Date& d){
	debut = d;
}
