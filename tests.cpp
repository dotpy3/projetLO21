#include "tests.h"

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
        std::cout<<"Création d'un tableau de précedences, ajout de la tache "
        <<(*contrainte).getTitre()<<" en précédence à "
        <<(*this).getTitre()<<"\n";
        return;
    }

    do{
        tacheEnEtude = precedence[i];
        i++;
        if (tacheEnEtude == contrainte) throw new TacheException("Tache déjà ajoutée !");
    }while(i < nbPrecedences);

    // LA CONTRAINTE N'A PAS ETE RENCONTREE DANS LES PRECEDENCES

    // ON L'AJOUTE A PRESENT

    if(nbPrecedences == nbPrecedencesMax){
        // IL FAUT RAJOUTER DE LA PLACE DANS LE TABLEAU
        std::cout<<"Extension du tableau de précédences\n";
        Tache** newTab = new Tache*[nbPrecedencesMax*2];
        for(int j=0;j<nbPrecedences;j++) newTab[j] = precedence[j];
        delete[] precedence;
        precedence = newTab;
        nbPrecedencesMax *= 2;
    }
    this->precedence[nbPrecedences] = contrainte;
    nbPrecedences++;
    std::cout<<"Tache "<<(*contrainte).getTitre()<<" ajoutée\n";
    return;
}

void Tache::deleteContrainte(Tache* contrainte)
{

    if (precedence == 0) throw new TacheException("Précédence non présente");
    
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

    throw new TacheException("Précédence non présente");
}

Tache::~Tache(){
    delete[] precedence;
}

void TacheUnitaire::setDuree(Duree duree)
{
    this->duree = duree;
}

CalendarException::~CalendarException()
{

}

bool verifJour(int j,int m,int a){
    if (j == 31
        && (m == 2
            || m == 4
            || m == 6
            || m == 9
            || m == 11)) return false;
    if (j == 30 && m == 2) return false;
    if (j == 29 && m == 2 && !(a%4 == 0)) return false;
    if (j>31 || j<=0) return false;

    // TOUS LES CAS ONT ETE VERIFIES

    return true;
}

bool verifMois(int m){
    if (m>12 || m < 1) return false;

    return true;
}
bool verifHeure(int h){
    if (h > 23 || h < 0) return false;
    
    return true;
}
bool verifMinute(int m){
    if (m >= 60 || m < 0) return false;
    
    return true;
}
bool verifSeconde(int s){
    if (s >= 60 || s < 0) return false;
    
    return true;
}

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

Date::~Date()
{

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
    j += reserve;
    if (!verifJour(j,getMois(),getAnnee())){
        j = 1;
        reserve = 1;
    } else {
        reserve = 0;
    }

    // MOIS
    mo += reserve;
    if (!verifMois(mo)){
        a += 1;
        mo = 1;
    }

    Date dateRetour(j,mo,a,h,m,s);
    return dateRetour;
}

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



ProgrammationTache::~ProgrammationTache(){

}

TacheUnitaire* ProgrammationTache::getTacheAssociee(){
    return tacheAssociee;
}

using namespace std;

ProgrammationManager::ProgrammationManager():programmations(0),nb(0),nbMax(0){}
void ProgrammationManager::addItem(Programmation* t){
    if (nb==nbMax){
        Programmation** newtab=new Programmation*[nbMax+10];
        for(unsigned int i=0; i<nb; i++) newtab[i]=programmations[i];
        // ou memcpy(newtab,Programmations,nb*sizeof(Programmation*));
        nbMax+=10;
        Programmation** old=programmations;
        programmations=newtab;
        delete[] old;
    }
    programmations[nb++]=t;
}

vector<Programmation*> ProgrammationManager::trouverProgrammation(const Tache& t)const{
    vector<Programmation*> listeProgrammations;
    Programmation* iter;
    ProgrammationTache* iterTache;
    for(unsigned int i=0;i<nb;i++){
        try
        {
            iterTache = dynamic_cast<ProgrammationTache*>(iter);
            if (iterTache->getTacheAssociee() == &t){
                listeProgrammations.push_back(iter);
            }
        } 
        catch(std::bad_cast &e)
        {

        }
    }
    return listeProgrammations;
}

void ProgrammationManager::ajouterProgrammationTache(TacheUnitaire& t, const Date& d, const Duree& h){
    TacheUnitaire* pTache = &t;
    ProgrammationTache* newt=new ProgrammationTache(d,h,pTache);
    addItem(newt);
}

void ProgrammationManager::ajouterProgrammationActivite(const std::string &s,const Date& d, const Duree& h){
    ProgrammationActivite* newp = new ProgrammationActivite(s,d,h);
    addItem(newp);
}


std::string ProgrammationActivite::getTitre(){
    return titre;
}


ProgrammationManager::~ProgrammationManager(){
    for(unsigned int i=0; i<nb; i++) delete programmations[i];
    delete[] programmations;
}

ProgrammationManager::ProgrammationManager(const ProgrammationManager& um):nb(um.nb),nbMax(um.nbMax), programmations(new Programmation*[um.nb]){
    for(unsigned int i=0; i<nb; i++) programmations[i]=new Programmation(*um.programmations[i]);
}

ProgrammationManager& ProgrammationManager::operator=(const ProgrammationManager& um){
    if (this==&um) return *this;
    this->~ProgrammationManager();
    for(unsigned int i=0; i<um.nb; i++) addItem(new Programmation(*um.programmations[i]));
    return *this;
}

int main(){
    Date test;
    Duree dureeTest(23,4,4);
    Date test2 = test + dureeTest;
    TacheUnitaire test()
    Programmation prog(test,dureeTest);
    std::cout<<"Heure :"<<prog.getFin().getHeure();
    return 1;
}