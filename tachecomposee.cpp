#include "tachecomposee.h"

using namespace std;

TacheComposee::TacheComposeeIterator::TacheComposeeIterator(int n, Tache** lT){
	nb = n;
	pointer = 0;
	listeTachesIt = lT;
}

bool TacheComposee::isTacheComposee(){
    return true;
}

bool TacheComposee::TacheComposeeIterator::isDone(){
	return (nb == pointer);
}

void TacheComposee::TacheComposeeIterator::next(){
	if (isDone()) throw new TacheException("On a atteint la fin de l'itérateur");
	pointer++;
}

Tache* TacheComposee::TacheComposeeIterator::current(){
	return listeTachesIt[pointer];
}

TacheComposee::TacheComposeeIterator TacheComposee::getIterator(){
	TacheComposeeIterator it = TacheComposeeIterator(nb,listeTaches);
	return it;
}

void TacheComposee::AddTacheToCompo(Tache* tache)
{
	if (listeTaches == 0){
		listeTaches = new Tache*;
		*listeTaches = tache;
		nb=1,nbMax=1;
		return;
	}

	// ON PARCOURT LA LISTE

	for(TacheComposeeIterator it = (*this).getIterator(); it.isDone(); it.next()){
		if (it.current() == tache){
			throw new TacheException("Tache déjà présente dans la composition");
		}
	}

	// on parcourt ensuite la liste des dépendances
	if (nbPrecedences > 0) {
		for(int j = 0; j < nbPrecedences; j++){
			if (precedence[j] == tache) throw new TacheException("Tache présente dans les précédences");
		}
	}

	// on vérifie qu'il reste de la place sinon on en rajoute

	if (nb == nbMax){
		// on rajoute de la place
		Tache** newtab = new Tache*[nb*2];
		for (int j=0;j<nb;j++) newtab[j] = listeTaches[j];
		delete[] listeTaches;
		listeTaches = newtab;
		nbMax*=2;
	}

	// on rajoute la tâche

	listeTaches[nb++] = tache;
	return;
}

void TacheComposee::DeleteTacheFromCompo(Tache* tache)
{
	for(int j=0;j<nb;j++){
		if (listeTaches[j] == tache){
			for (int i=j;j<nb-1;j++){
				listeTaches[i] = listeTaches[i+1];
			}
			nb--;
			return;
		}
	}

	throw new TacheException("Tache non présente dans la composition");
}

Tache** TacheComposee::getListeTaches(){
	return listeTaches;
}

bool TacheComposee::IsPlanifiee(){
	if (nb == 0) return true;
	for (TacheComposeeIterator it = (*this).getIterator(); it.isDone(); it.next()){
		if (!(it.current()->IsPlanifiee())) return false;
	}
	return true;
}

TacheComposee::~TacheComposee(){
    for (int i=0; i<nb; i++){
		delete listeTaches[i];
	}
	delete[] listeTaches;
}

bool TacheComposee::isInListeDeCompositions(Tache *t){
    for (int i=0;i<nb;i++){
        if (listeTaches[i] == t) return true;
    }
    return false;
}

bool TacheComposee::Composes(Tache* t){
    for (int i=0; i<nb; i++){
        if (listeTaches[i] == t) return true;
        if (listeTaches[i]->isTacheComposee())
        {
            TacheComposee* proj = dynamic_cast<TacheComposee*>(listeTaches[i]);
            if(proj->Composes(t)) return true;
        }
    }
    return false;
}

vector<TacheComposee*> TacheComposee::cheminTo(Tache* t){
    vector<TacheComposee*> chemin;
    chemin.push_back(this);
    for(int i=0;i<nb;i++){
        if(listeTaches[i] == t) return chemin;
        if(listeTaches[i]->isTacheComposee() && static_cast<TacheComposee*>(listeTaches[i])->Composes(t)){
            vector<TacheComposee*> cheminAnterieur = static_cast<TacheComposee*>(listeTaches[i])->cheminTo(t);
            for(int j=0;j<cheminAnterieur.size();j++){
                chemin.push_back(cheminAnterieur[j]);
            }
            return chemin;
        }
    }
    throw "Impossible de trouver la tâche dans la tâche composée";
}

vector<Tache*> TacheComposee::listeTotaleSousTaches(){
    vector<Tache*> listeTotaleDeTaches;
    vector<Tache*> sousListeTotaleDeTaches;
    for(int i=0;i<nb;i++){
        listeTotaleDeTaches.push_back(listeTaches[i]);
        if (listeTaches[i]->isTacheComposee()){
            sousListeTotaleDeTaches.clear();
            sousListeTotaleDeTaches = static_cast<TacheComposee*>(listeTaches[i])->listeTotaleSousTaches();
            for (size_t j=0;j<sousListeTotaleDeTaches.size();j++){
                listeTotaleDeTaches.push_back(sousListeTotaleDeTaches[j]);
            }
        }
    }
    return listeTotaleDeTaches;
}
