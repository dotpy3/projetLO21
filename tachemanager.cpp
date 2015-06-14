#include "tachemanager.h"

TacheManager * TacheManager::instance = 0;

TacheManager &TacheManager::getInstance()
{
	//cree l'instance si existe pas
	if(!instance) instance = new TacheManager();
	return *instance;
}

void TacheManager::LibererInstance()
{
	//efface l'instance si existe pas
	if(instance)
	delete instance;
}

TacheManager::TacheManager():taches(0),nb(0),nbMax(0){}


void TacheManager::addItem(Tache* t){
	if (nb==nbMax){
		Tache** newtab=new Tache*[nbMax+10];
		for(unsigned int i=0; i<nb; i++) newtab[i]=taches[i];
		// ou memcpy(newtab,taches,nb*sizeof(Tache*));
		nbMax+=10;
		Tache** old=taches;
		taches=newtab;
		delete[] old;
	}
	taches[nb++]=t;
}

Tache* TacheManager::trouverTache(const string& titre)const{
	for(unsigned int i=0; i<nb; i++)
		if (id==taches[i]->getId()) return taches[i];
	return 0;
}

Tache& TacheManager::ajouterTache(const string& id, const string& t, const Duree& dur, const Date& dispo, const Date& deadline){
	if (trouverTache(id)) throw CalendarException("erreur, TacheManager, tache deja existante");
	Tache* newt=new Tache(id,t,dur,dispo,deadline);
	addItem(newt);
	return *newt;
}

Tache& TacheManager::getTache(const string& titre){
	Tache* t=trouverTache(titre);
	if (!t) throw CalendarException("erreur, TacheManager, tache inexistante");
	return *t;
}

const Tache& TacheManager::getTache(const string& id)const{
	return const_cast<TacheManager*>(this)->getTache(id);
}

TacheManager::~TacheManager(){
	if (file!="") save(file);
	for(unsigned int i=0; i<nb; i++) delete taches[i];
	delete[] taches;
	file="";
}

TacheManager::TacheManager(const TacheManager& um):nb(um.nb),nbMax(um.nbMax), taches(new Tache*[um.nb]){
	for(unsigned int i=0; i<nb; i++) taches[i]=new Tache(*um.taches[i]);
}

TacheManager& TacheManager::operator=(const TacheManager& um){
	if (this==&um) return *this;
	this->~TacheManager();
	for(unsigned int i=0; i<um.nb; i++) addItem(new Tache(*um.taches[i]));
	return *this;
}
