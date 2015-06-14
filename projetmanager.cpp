#include "projetmanager.h"

using namespace std;

ProjetManager::ProjetManager():tabProjets(0),nbProjets(0),nbProjetsMax(0)
{
    instance = this;
    // FINI
}

ProjetManager::~ProjetManager()
{
    if (tabProjets != 0) delete[] tabProjets;
}

ProjetManager::Iterator::Iterator(int nbProj, int nbMaxProj, Projet** projets){
    nb = nbProj;
    nbMax = nbMaxProj;
    instance = projets;
    currentIndex = 0;
}

//ProjetManager::Iterator::~Iterator(){}

bool ProjetManager::Iterator::isDone(){
    return (currentIndex == nb);
}

Projet* ProjetManager::Iterator::current(){
    return instance[currentIndex];
}

void ProjetManager::Iterator::next(){
    currentIndex++;
}

ProjetManager& ProjetManager::getInstance(){

    // A COMPLETER : Il faut vérifier si instance est déjà défini avant.

    if (instance == 0) instance = new ProjetManager;
    return *instance;
}

void ProjetManager::libererInstance(){

    delete instance;
}

/* LISTE DES FONCTIONS :
 *
 * PRIVATE :
 *
 X  ProjetManager();
 X  ~ProjetManager();
 X  ProjetManager(ProjetManager& projet); : PAS BESOIN DE LE FAIRE, ON Y EMPECHE L'ACCES
 X  Iterator(int nb, int nbMax, Projet* projets);
 X  Iterator::~Iterator();

    PUBLIC :

 X  static ProjetManager& getInstance();
 X  void libererInstance();
 X  void ajouterProjet(Projet* t);
    void supprimerProjet(Projet* t);
    void getProjet(string nomProjet);
    void getProjet(int i);
    int getNbTache();
    Iterator getIterator();
    bool Iterator::isDone();
    void Iterator::next();

    */

void ProjetManager::ajouterProjet(Projet* t){
    if (nbProjets == nbProjetsMax){
        // alors il n'y a pas assez de place dans le tableau de pointeurs
        Projet** newtab = new Projet*[nbProjets+1];
        for(int i=0;i<nbProjets;i++){
            newtab[i] = tabProjets[i];
        }
        delete[] tabProjets;
        tabProjets = newtab;
        nbProjetsMax++;
    }
    tabProjets[nbProjets] = t;
    nbProjets++;
}

void ProjetManager::supprimerProjet(Projet* t){
    for (int i=0;i<nbProjets;i++){
        if (tabProjets[i] == t) {
            delete t;
            for (int j=i;j<nbProjets-1;j++) tabProjets[j] = tabProjets[j+1];
            nbProjets--;
            return;
        }
    }
    throw CalendarException("Projet non trouvé");
}

Projet* ProjetManager::creerProjet(std::string nomProjet){
    Projet* newProj = new Projet(nomProjet);
    ajouterProjet(newProj);
    return newProj;
}

Tache* traiterTache(const QDomElement& tacheXML, Projet& projetAssocie, TacheComposee* parent=0){
    string titre(tacheXML.attribute(QString("nom")).toStdString());
    QDomNode noeudATraiter = tacheXML.firstChild();

    Tache* tacheATraiter;

    if(tacheXML.tagName() == QString("TacheUnitaire")){
        // ON TRAITE UNE TACHE UNITAIRE DANS LE DOM
        bool p = (tacheXML.attribute(QString("preemptable")).toStdString() == "true");
        int heures(atoi(tacheXML.attribute(QString("heures"),QString("0")).toStdString().c_str()));
        int minutes(atoi(tacheXML.attribute(QString("minutes"),QString("0")).toStdString().c_str()));
        int secondes(atoi(tacheXML.attribute(QString("secondes"),QString("0")).toStdString().c_str()));
        Duree d(heures,minutes,secondes);
        TacheUnitaire* tacheATraiterUni = projetAssocie.addTacheUnitaire(titre,p,d,parent);
        tacheATraiter = static_cast<Tache*>(tacheATraiterUni);
    } else {
        // ON TRAITE UNE TACHE COMPOSEE DANS LE DOM
        TacheComposee* tacheATraiterCom = projetAssocie.addTacheComposee(titre,parent);
        tacheATraiter = static_cast<Tache*>(tacheATraiterCom);
        Tache* tacheRajoutee;
        while(!noeudATraiter.isNull() && (noeudATraiter.toElement().tagName() == QString("TacheUnitaire")
                                          || noeudATraiter.toElement().tagName() == QString("TacheComposee"))){
            tacheRajoutee = traiterTache(noeudATraiter.toElement(),projetAssocie,tacheATraiterCom);
            noeudATraiter = noeudATraiter.nextSibling();
        }
    }
    std::string titreTachePrecedence;
    while(!noeudATraiter.isNull()){
        std::string typeTraitement = noeudATraiter.toElement().tagName().toStdString();
        if (typeTraitement == "dateDisponibilite") {
            Date dateDispo(noeudATraiter.toElement().text());
            tacheATraiter->setDateDisp(dateDispo);
        }
        if (typeTraitement == "dateEcheance") {
            Date dateEcheance(noeudATraiter.toElement().text());
            tacheATraiter->setDateEch(dateEcheance);
        }

        if (typeTraitement == "precedence") {
            titreTachePrecedence = noeudATraiter.toElement().text().toStdString();
            tacheATraiter->addContrainte(projetAssocie.getTache(titreTachePrecedence));
        }
        noeudATraiter = noeudATraiter.nextSibling();
    }



    return tacheATraiter;

}

TacheUnitaire* treatTacheUnitaire(QXmlStreamReader& reader){

}

void ProjetManager::creerProjetXML(QString adresseXML, QWidget* fenetre){
    QFile xml_doc(adresseXML);
    if(!xml_doc.open(QIODevice::ReadOnly | QIODevice::Text))
    {
         QMessageBox::warning(fenetre,"Erreur à l'ouverture du XML","Le nom est mauvais ou le fichier est mal placé");
         return;
    }
    QXmlStreamReader process;

    Projet* proj;

    process.setDevice(&xml_doc);

    process.readNext();
    while(!process.atEnd()){
        if (process.isStartElement()){
            if(process.name() == "Projet"){
                process.readNext();
                while(process.isStartElement() == false){
                    process.readNext();
                }
                if(process.name() == "Titre"){
                    proj = creerProjet(process.readElementText().toStdString());
                    process.readNext();
                    while(process.isStartElement() == false) process.readNext();
                }
                if(process.name() == "Taches"){
                    process.readNext();
                    while (process.isStartElement() == false) {
                        process.readNext();
                    }
                    if(process.name() == "TacheUnitaire"){
                        //proj->addTacheUnitaire(treatTacheUnitaire(&process));
                    }
                }
            }
        }
    }

}

Projet* ProjetManager::getProjet(std::string nomProjet){
    for (int i=0;i<nbProjets;i++){
        if (tabProjets[i]->getTitre() == nomProjet){
            return tabProjets[i];
        }
    }
    throw CalendarException("Projet non trouvé");
}

int ProjetManager::getNbTache(){
    int somme=0;
    for (int i=0;i<nbProjets;i++){
        somme += tabProjets[i]->taches.size();
    }
    return somme;
}

ProjetManager::Iterator ProjetManager::getIterator(){
    Iterator iter(nbProjets,nbProjetsMax,tabProjets);
    return iter;
}

Projet& ProjetManager::getProjetAssocie(Tache *t){
    Iterator iter(nbProjets,nbProjetsMax,tabProjets);
    for(true;!iter.isDone();iter.next()){
        if(iter.current()->containsTache(t)){
            return *iter.current();
        }
    }
    throw "Impossible de récupérer le projet associé";
}
