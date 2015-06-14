#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Duree
{
    int heure;
    int minute;
    int seconde;
public:
    Duree(int h=0,int m=0, int s=0);
    ~Duree();
    int getHeure() const;
    int getMinute() const;
    int getSeconde() const;
    void setDuree(int h=0, int m=0, int s=0);
    Duree operator+(const Duree& d) const;
};

class Tache {
    std::string unique_titre;
    //interdire creation tache par utilisateur
    friend class TacheManager;// peut être mis n'importe où ds la classe
protected:

    Tache(const std::string& unique_t):unique_titre(unique_t),nbPrecedences(0),nbPrecedencesMax(0),precedence(0){}
    ~Tache(); // OK : non testé
    Tache(const  Tache &t){
        unique_titre = t.unique_titre;
    }
    Tache & operator=(const Tache&);
    Tache ** precedence;
    int nbPrecedences;
    int nbPrecedencesMax;

public:

    std::string getTitre() const { return unique_titre; } // OK : testé
    Tache** getContraintes(){ return precedence; }
    void setTitre(string titre){ unique_titre = titre; }
    virtual bool IsPlanifiee() = 0;
    void addContrainte(Tache* contrainte);
    void deleteContrainte(Tache* contrainte);
};


class TacheException{
public:
    TacheException(const std::string& message):info(message){}
    std::string getInfo() const { return info; }
private:
    std::string info;
};

class TacheUnitaire : public Tache {
private:
    Duree duree;
    bool preemptable;
    
    TacheUnitaire(const std::string &titre,Duree d, bool p):Tache(titre),duree(d),preemptable(p){}
    ~TacheUnitaire();
    TacheUnitaire(const  TacheUnitaire &t);
    TacheUnitaire & operator=(const TacheUnitaire&);
    
public:

    bool EstPreemptable() const { return preemptable;}
    Duree GetDuree() const { return duree;}
    void setDuree(Duree duree);
};

class Date
{
    int jour;
    int mois;
    int annee;
    int heure;
    int minute;
    int seconde;
public:
    Date(int j=1,int mo=1,int a=2015,int h=0,int mi=0,int s=0);
    ~Date();
    int getJour() const;
    int getMois() const;
    int getAnnee() const;
    int getHeure() const;
    int getMinute() const;
    int getSeconde() const;
    void setDate(int j=1,int mo=1,int a=2015,int h=0,int mi=0,int s=0);
    Date operator+(const Duree& d) const;
};

class CalendarException{
public:
    CalendarException(const std::string& message):info(message){}
    std::string getInfo() const { return info; }
    ~CalendarException();
private:
    std::string info;
};

bool verifJour(int j,int m,int a);
bool verifMois(int m);
bool verifHeure(int h);
bool verifMinute(int m);
bool verifSeconde(int s);

class Programmation
{
private:
    friend class ProgrammationManager;
    Date debut;
    Duree duree;
public:
    Programmation();
    Programmation(const Date& dateDonnee, const Duree& dureeDonnee);
    virtual ~Programmation();
    Duree getDuree();
    Date getDebut();
    Date getFin();
    void setDuree(const Duree& d);
    void setDebut(const Date& d);
};

class ProgrammationTache : public Programmation{
private:
    friend class ProgrammationTache;
    TacheUnitaire* tacheAssociee;
public:
    ProgrammationTache():tacheAssociee(0){}
    ~ProgrammationTache();
    ProgrammationTache(const Date& dateDonnee, const Duree& dureeDonnee, TacheUnitaire* tacheAssoc):Programmation(dateDonnee,dureeDonnee),tacheAssociee(tacheAssoc){}
    TacheUnitaire* getTacheAssociee();
};

class ProgrammationActivite: public Programmation{

private:
    std::string titre;

public:
    ProgrammationActivite(const std::string &s, const Date& d, const Duree& h):Programmation(),titre(s){}
    std::string getTitre();
    void setTitre(const std::string &s);
};

class ProgrammationManager {
private:
    Programmation** programmations;
    unsigned int nb;
    unsigned int nbMax;
    void addItem(Programmation* t);
    std::vector<Programmation*> trouverProgrammation(const Tache& t) const;
public:
    ProgrammationManager();
    ~ProgrammationManager();
    ProgrammationManager(const ProgrammationManager& um);
    ProgrammationManager& operator=(const ProgrammationManager& um);
    void ajouterProgrammationTache(TacheUnitaire& t, const Date& d, const Duree& h);
    void ajouterProgrammationActivite(const std::string &s,const Date& d, const Duree& h);
};

