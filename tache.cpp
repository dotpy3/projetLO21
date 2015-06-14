#include "tache.h"

using namespace std;



void Tache::addContrainte(Tache* contrainte)
{
	int i =0;
	Tache* tacheEnEtude;

	/* ON PARCOURT TOUTES LES CONTRAINTES JUSQU'A CE QUE :

		- SOIT ON RENCONTRE LA CONTRAINTE DANS LES PRECEDENCES

		- SOIT ON ATTEINT LA FIN DES PRECEDENCES : ON AJOUTE ALORS
		LA CONTRAINTE

	*/

	if (this->precedence==0){

		// cas où le tableau des précédences n'a pas été initialisé

		this->precedence = new Tache*;
		*this->precedence = contrainte;
		nbPrecedences = 1;
		nbPrecedencesMax = 1;
        std::cout<<"Creation d'un tableau de precedences, ajout de la tache "
        <<(*contrainte).getTitre()<<" en precedence a "
		<<(*this).getTitre()<<"\n";
		return;
	}

	do{
		tacheEnEtude = precedence[i];
		i++;
        if (tacheEnEtude == contrainte) throw new TacheException("Tache deja ajoutee !");
	}while(i < nbPrecedences);

	// LA CONTRAINTE N'A PAS ETE RENCONTREE DANS LES PRECEDENCES

	// ON L'AJOUTE A PRESENT

	if(nbPrecedences == nbPrecedencesMax){
		// IL FAUT RAJOUTER DE LA PLACE DANS LE TABLEAU
        std::cout<<"Extension du tableau de precedences\n";
		Tache** newTab = new Tache*[nbPrecedencesMax*2];
		for(int j=0;j<nbPrecedences;j++) newTab[j] = precedence[j];
		delete[] precedence;
		precedence = newTab;
		nbPrecedencesMax *= 2;
	}
	this->precedence[nbPrecedences] = contrainte;
	nbPrecedences++;
    std::cout<<"Tache "<<(*contrainte).getTitre()<<" ajoutee\n";
	return;
}

void Tache::deleteContrainte(Tache* contrainte)
{

    if (precedence == 0) throw new TacheException("Precedence non presente");
	
	int i =0;

	Tache* tacheEnEtude;
	
	/*

	ON PARCOUT LE TABLEAU DES CONTRAINTES JUSQU'À CE QUE :

	- ON ARRIVE A LA CONTRAINTE DITE

	- ON ARRIVE A LA FIN DU TABLEAU DES PRECEDENCES

	*/

	do{
		tacheEnEtude = precedence[i];
		i++;
		if (tacheEnEtude == contrainte) {

			// ON ARRIVE A LA TACHE VOULUE

			for(int j=i+1;j<nbPrecedences;j++){
				precedence[j-1] = precedence[j];
			}
			precedence[nbPrecedences-1]=0;
			nbPrecedences--;
			return;

		}
	}while(i < nbPrecedences);

    throw new TacheException("Precedence non presente");
}

Tache::~Tache(){
	delete[] precedence;
}

void Tache::removeDateDispo(){
	if (isDateDisp()) delete dateDispo;
}

void Tache::removeDateEcheance(){
	if (isDateEcheance()) delete dateEcheance;
}

void Tache::setDateDisp(const Date& disp){
	removeDateDispo();
    dateDispo = new Date(disp);
}

void Tache::setDateEch(const Date& ech){
	removeDateEcheance();
    dateEcheance = new Date(ech);
}

bool Tache::isDateDisp(){
	return (dateDispo != 0);
}

bool Tache::isDateEcheance(){
	return (dateEcheance != 0);
}

Date Tache::getDateDisp(){
    if (isDateDisp()) return *dateDispo;
    else throw CalendarException("Pas de date de disponibilite");
}

Date Tache::getDateEcheance(){
    if (isDateEcheance()) return *dateEcheance;
    else throw CalendarException("Pas de date d'echeance");
}

bool Tache::isCompositionOf(TacheComposee* t){
    return t->Composes(this);
}

bool Tache::isIndirectlyPrecededBy(Tache* t){
    vector<TacheComposee*> cheminTo = ProjetManager::getInstance().getProjetAssocie(t).getParente(this);
    for(size_t i=0;i<cheminTo.size(); i++){
        if (cheminTo[i] == t || cheminTo[i]->isPrecededBy(t)) return true;
    }
    for(int i=0;i<nbPrecedences;i++){
        if (precedence[i]->isPrecededBy(t)) return true;
    }
    return false;
}

bool Tache::isPrecededBy(Tache *t){
    if (isIndirectlyPrecededBy(t)) return true;
    for (int i = 0; i < nbPrecedences; i++){
        if (precedence[i] == t) return true;
    }
    return false;
}

bool Tache::canBePrecedence(Tache *t){
    try {
        TacheComposee* proj = dynamic_cast<TacheComposee*>(t);
        if (isCompositionOf(proj) || t->isPrecededBy(this)) return false;
    } catch(std::bad_cast e){
        if(t->isPrecededBy(this)) return false;
    }

    return true;
}

vector<TacheComposee*> Tache::getTachesParentes(){
    ProjetManager& pm = ProjetManager::getInstance();
    Projet proj = pm.getProjetAssocie(this);

    return proj.getParente(this);
}

void Tache::writeOnto(QXmlStreamWriter* xmlStream){
    if(isTacheComposee()){
        xmlStream->writeStartElement("TacheComposee");
        xmlStream->writeAttribute("nom",getTitre().c_str());

        for(int i=0;i<dynamic_cast<TacheComposee*>(this)->getNbTaches();i++){
            dynamic_cast<TacheComposee*>(this)->getListeTaches()[i]->writeOnto(xmlStream);
        }
    } else {
        // TACHE UNITAIRE

        xmlStream->writeStartElement("TacheUnitaire");
        xmlStream->writeAttribute("nom",getTitre().c_str());
        TacheUnitaire* cast = dynamic_cast<TacheUnitaire*>(this);
        if (cast->EstPreemptable()) xmlStream->writeAttribute("preemptable","true");
        else xmlStream->writeAttribute("preemptable","false");
        Duree duree = dynamic_cast<TacheUnitaire*>(this)->GetDuree();
        xmlStream->writeAttribute("heures",to_string(duree.getHeure()).c_str());
        xmlStream->writeAttribute("minutes",to_string(duree.getMinute()).c_str());
        xmlStream->writeAttribute("secondes",to_string(duree.getSeconde()).c_str());


    }


    if (isDateDisp()){
        xmlStream->writeStartElement("dateDisponibilite");
        xmlStream->writeCharacters(dateDispo->getFormatedTime().c_str()
                    );
        xmlStream->writeEndElement();
    }
    if (isDateEcheance()){
        xmlStream->writeStartElement("dateEcheance");
        xmlStream->writeCharacters(dateEcheance->getFormatedTime().c_str()
                    );
        xmlStream->writeEndElement();
    }
    for (int i=0;i<nbPrecedences;i++){
        xmlStream->writeStartElement("precedence");
        xmlStream->writeCharacters(precedence[i]->getTitre().c_str()
                    );
        xmlStream->writeEndElement();
    }


    xmlStream->writeEndElement();
}

bool Tache::canBeSetAtThisDate(Date dateChoisie){
    vector<Programmation*> listeProgPrecedence; size_t j;
    ProgrammationManager& progman = ProgrammationManager::getInstance();
    for(int i=0;i<nbPrecedences;i++){
        if(!precedence[i]->IsPlanifiee()) return false;
        listeProgPrecedence = progman.trouverProgrammation(*this);
        for(j=0;j<listeProgPrecedence.size();j++){
            if (!(listeProgPrecedence[j]->getFin() < dateChoisie)) return false;
        }
    }
    vector <TacheComposee*> listeProgCompo = getTachesParentes();
    for(j=0;j<listeProgCompo.size();j++){
        if (!listeProgCompo[j]->canBeSetAtThisDate(dateChoisie)) return false;
    }
    Projet proj = ProjetManager::getInstance().getProjetAssocie(this);
    if(proj.isDateDisp()){
        if (dateChoisie < proj.getDateDisp()) return false;
    }
    return true;
}
