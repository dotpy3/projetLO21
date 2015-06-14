#ifndef TACHEMANAGER_h
#define TACHEMANAGER_h
#include<string>
#include<iostream>

#include "tache.h"
#include "date.h"

class TacheManager {
private:
	Tache** taches;
	unsigned int nb;
	unsigned int nbMax;
	void addItem(Tache* t);
	Tache* trouverTache(const string& id) const;

	//design pattern singleton
	static TacheManager * instance;
	TacheManager();
	~TacheManager();
	TacheManager(const TacheManager& um);
	TacheManager& operator=(const TacheManager& um);

public:
	//design pattern singleton
	static TacheManager& getInstance();
	static void LibererInstance();

	Tache& ajouterTache(const string& id, const string& t, const Duree& dur, const Date& dispo, const Date& deadline);
	Tache& getTache(const string& id);
	const Tache& getTache(const string& code) const;
	
    //design pattern iterator
	class Iterator
	{
		Tache ** currentTache;
		unsigned int nbRemain; // cpt tjrs + => unsigned
        Iterator(Tache ** tachesDonnees, unsigned int nb) : currentTache(tachesDonnees), nbRemain(nb){ }
        friend class TacheManager;
    public:
        Iterator(): currentTache(0), nbRemain(0){		}
		bool isDone() const { return nbRemain == 0;}
		void next(){
			if(isDone())
				throw CalendarException("erreur iterator");

			nbRemain--;
			currentTache++;
		}
		Tache &current() const{
			if(isDone())
			throw CalendarException("erreur iterator");
			return ** currentTache;
		
		}
    };
		
    Iterator getIterator()
    {
        return Iterator(taches, nb);
    }
};

#endif
