#include "programmationmanager.h"

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

ProgrammationManager& ProgrammationManager::getInstance(){
    if (instance == 0) instance = new ProgrammationManager();
    return *instance;
}

void ProgrammationManager::libererInstance(){
    if (instance != 0) delete instance;
    instance = 0;
}

vector<Programmation*> ProgrammationManager::trouverProgrammation(const Tache& t)const{
    vector<Programmation*> listeProgrammations;
    Programmation* iter;
    ProgrammationTache* iterTache;
    for(unsigned int i=0;i<nb;i++){
        try
        {
            iter = listeProgrammations[i];
            iterTache = dynamic_cast<ProgrammationTache*>(iter);
            if (iterTache == 0) throw std::bad_cast();
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


ProgrammationManager::~ProgrammationManager(){
    for(unsigned int i=0; i<nb; i++) delete programmations[i];
    delete[] programmations;
}

ProgrammationManager::ProgrammationManager(const ProgrammationManager& um){
    nb = um.nb;
    nbMax = um.nbMax;
    programmations = new Programmation*[um.nb];
    for(unsigned int i=0; i<nb; i++) programmations[i]=new Programmation(*um.programmations[i]);
}

ProgrammationManager& ProgrammationManager::operator=(const ProgrammationManager& um){
    if (this==&um) return *this;
    this->~ProgrammationManager();
    for(unsigned int i=0; i<um.nb; i++) addItem(new Programmation(*um.programmations[i]));
    return *this;
}

void ProgrammationManager::deleteProgrammation(Programmation* prog){
    for(unsigned int i = 0; i < nb ; i++ ){
        if (prog == programmations[i]){
            for (size_t j = i ; j < nb - 1 ; j++){
                programmations[j] = programmations[j+1];
            }
            nb--;
            delete prog;
            return;
        }
    }
    throw CalendarException("Programmation non trouvée");
}
