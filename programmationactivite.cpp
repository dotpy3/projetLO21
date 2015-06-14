#include "programmationactivite.h"

std::string ProgrammationActivite::getTitre(){
	return titre;
}

void ProgrammationActivite::setTitre(const std::string &s){
    titre = s;
}
