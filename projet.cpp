#include "projet.h"

Projet::~Projet()
{
	removeDateDispo();
	removeDateEcheance();
}

void Projet::removeDateDispo(){
	if (isDateDisp()) delete dateDispo;
}

void Projet::removeDateEcheance(){
	if (isDateEcheance()) delete dateEcheance;
}

void Projet::setTitre(const string& nTitre){
	titre = nTitre;
}

std::string Projet::getTitre(){
	return titre;
}

void Projet::setDateDisp(const Date& disp){
	removeDateDispo();
    dateDispo = new Date(disp);
}

void Projet::setDateEch(const Date& ech){
	removeDateEcheance();
    dateEcheance = new Date(ech);
}

bool Projet::isDateDisp(){
	return (dateDispo != 0);
}

bool Projet::isDateEcheance(){
	return (dateEcheance != 0);
}

Date Projet::getDateDisp(){
    if (isDateDisp()) return *dateDispo;
    else throw CalendarException("Pas de date de disponibilité");
}

Date Projet::getDateEcheance(){
    if (isDateEcheance()) return *dateEcheance;
    else throw CalendarException("Pas de date d'échéance");
}

TacheComposee* Projet::addTacheComposee(const std::string& tacheTitre, TacheComposee* appartenance){
	TacheComposee* tache = new TacheComposee(tacheTitre);
    if (appartenance != 0) appartenance->AddTacheToCompo(tache);
    else taches.push_back(tache);
    return tache;
}

TacheUnitaire* Projet::addTacheUnitaire(const std::string& tacheTitre, bool preemp, Duree d, TacheComposee* appartenance){
	TacheUnitaire* tache = new TacheUnitaire(tacheTitre, d, preemp);
    if (appartenance != 0) appartenance->AddTacheToCompo(tache);
    else taches.push_back(tache);
    return tache;
}

void Projet::deleteTache(Tache* tache){
    for (unsigned int i=0; i<taches.size() ; i++){
        if (taches[i] == tache) {
            taches.erase(taches.begin() + i);
			delete tache;
            return;
        }
	}
	throw CalendarException("Tache non trouvée");
}

bool Projet::containsTache(Tache *tache){
    for(unsigned int i=0;i<taches.size();i++ ){
        if(taches[i] == tache) return true;
        else if (taches[i]->isTacheComposee() && tache->isCompositionOf(static_cast<TacheComposee*>(taches[i]))) return true;
    }
    return false;
}

vector<TacheComposee*> Projet::getParente(Tache* tache){
    vector<TacheComposee*> vecteur;
    for (size_t i=0;i<taches.size();i++){
        if(tache == taches[i]) return vecteur;
        else if (taches[i]->isTacheComposee() && tache->isCompositionOf(static_cast<TacheComposee*>(taches[i]))) {
            return static_cast<TacheComposee*>(taches[i])->cheminTo(tache);
        }
    }
}

Tache* Projet::getTache(std::string nomTache){
    vector<Tache*> listeDesTaches = getListeTotaleTaches();
    for(size_t i=0; i<listeDesTaches.size();i++){
        if (listeDesTaches[i]->getTitre() == nomTache){
            return listeDesTaches[i];
        }
    }
    return 0;
}

vector<Tache*> Projet::getListeTotaleTaches(){
    vector<Tache*> listeTotaleDeTaches;
    vector<Tache*> sousListeTotaleDeTaches;
    for(size_t i=0;i<taches.size();i++){
        listeTotaleDeTaches.push_back(taches[i]);
        if (taches[i]->isTacheComposee()){
            sousListeTotaleDeTaches.clear();
            sousListeTotaleDeTaches = static_cast<TacheComposee*>(taches[i])->listeTotaleSousTaches();
            for (size_t j=0;j<sousListeTotaleDeTaches.size();j++){
                listeTotaleDeTaches.push_back(sousListeTotaleDeTaches[j]);
            }
        }
    }
    return listeTotaleDeTaches;
}

vector<Tache*> Projet::premiersEnfants(){
    vector<Tache*> listeDeTaches;
    for(size_t i=0; i<taches.size();i++){
        listeDeTaches.push_back(taches[i]);
    }
    return listeDeTaches;
}

void Projet::exportXML(QWidget* fenParent){
    QString filename = QFileDialog::getSaveFileName(fenParent,
                                                    QString("Sauvegarde XML du projet"));
    if(filename.isNull()){
        QMessageBox::warning(fenParent,QString("Erreur lors de la sélection du fichier"),QString("Vérifiez que l'adresse saisie est bien conforme"));
        return;
    }

    QXmlStreamWriter xmlWriter;
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly)){
        QMessageBox::warning(fenParent,QString("Erreur"),QString("Erreur lors du chargement du fichier"));
        return;
    }

    xmlWriter.setDevice(&file);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("Projet");

    xmlWriter.writeStartElement("Titre");
    xmlWriter.writeCharacters(titre.c_str());
    xmlWriter.writeEndElement();

    if(taches.size() > 0){

    xmlWriter.writeStartElement("Taches");

    for(size_t i=0;i<taches.size();i++){
        taches[i]->writeOnto(&xmlWriter);
    }

    xmlWriter.writeEndElement();

    }

    if(isDateDisp()){
        xmlWriter.writeStartElement("dateDisponibilite");
        xmlWriter.writeCharacters(dateDispo->getFormatedTime().c_str());
        xmlWriter.writeEndElement();
    }
    if(isDateEcheance()){
        xmlWriter.writeStartElement("dateEcheance");
        xmlWriter.writeCharacters(dateEcheance->getFormatedTime().c_str());
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndDocument();
}
