#include "tacheunitaire.h"

void TacheUnitaire::setDuree(Duree duree)
{
	this->duree = duree;
}

void TacheUnitaire::deleteTachesAssociees(){
    vector<Programmation*> listeProg = ProgrammationManager::getInstance().trouverProgrammation(*this);
    for (unsigned int i = 0; i < listeProg.size(); i++){
        Programmation* toDelete = listeProg[i];
        delete toDelete;
    }
}

bool TacheUnitaire::isTacheComposee(){
    return false;
}

TacheUnitaire::~TacheUnitaire(){
    deleteTachesAssociees();
}

bool TacheUnitaire::IsPlanifiee(){
	std::vector<Programmation*> progAssociees = ProgrammationManager::getInstance()
		.trouverProgrammation(*this);
		Duree dureeTotale;
    for(unsigned int i=0;i<progAssociees.size();i++){
		dureeTotale = dureeTotale + progAssociees[i]->getDuree();
	}
	if (dureeTotale == duree) return true;
	else return false;
}
