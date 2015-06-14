#include "fencreateeve.h"
#include "programmationmanager.h"

FenCreateEve::FenCreateEve(TacheUnitaire &ta, QWidget *parent) : t(ta),
    QWidget(parent)
{
    this->setFixedSize(300,300);

    couche = new QHBoxLayout(this);
    couche1 = new QVBoxLayout();//titre eve
    couche2 = new QVBoxLayout();//champs
    couche3 = new QVBoxLayout();//buton

    createEve = new QLabel("Programmation d'une tâche");
    createEve->adjustSize();

    tacheAsso = new QLabel("Tâche associée :");
    titre = new QLabel("Nom : ");
    date = new QLabel("Début : ");
    duree = new QLabel("Durée : ");

    annuler = new QPushButton("Annuler");
    sauver = new QPushButton("Sauvegarder");

    dateDeb = new QDateEdit;
    dur = new QTimeEdit;
    textTitre = new QLineEdit;
    tache = new QComboBox();


    //asso couches
    couche->addLayout(couche1);
    couche->addLayout(couche2);
    couche->addLayout(couche3);

    couche1->addWidget(createEve);

    couche2->addWidget(tacheAsso);
    couche2->addWidget(tache);
    couche2->addWidget(titre);
    couche2->addWidget(textTitre);
    couche2->addWidget(date);
    couche2->addWidget(dateDeb);
    couche2->addWidget(duree);
    couche2->addWidget(dur);

    couche3->addWidget(sauver);
    couche3->addWidget(annuler);


    remplirCombobox(tache);

    QObject::connect(sauver, SIGNAL(clicked), this, SLOT(on_btnSave_clicked()));
    QObject::connect(annuler, SIGNAL(clicked), this, SLOT(on_btnCancel_clicked()));
}

FenCreateEve::~FenCreateEve()
{
}

void FenCreateEve::remplirCombobox(QComboBox *t)
{
    ProjetManager & ptr = ProjetManager::getInstance();
    int nbTaches = ptr.getNbTache();
    lesTaches = ptr.getIterator().current()->getListeTotaleTaches();
    for(int i = 0 ; i <= nbTaches ; i++)
    {
        tache->addItem(lesTaches[i]->getTitre().c_str());
    }
}


void FenCreateEve::on_btnSave_clicked()
{
    QString n = textTitre->text();
    const string &nom = n.toStdString();

    QTime du = dur->time();
    const Duree * duree = new Duree(du.hour(), du.minute(), du.second());
    const Duree& duree2 = *duree;


    QDate dat = dateDeb->date();
    const Date * date = new Date(dat.day(), dat.month(), dat.year());
    const Date& date2 = *date;

    if(verifJour(date2.getJour(), date2.getMois(), date2.getAnnee()) == true
            && verifHeure(duree2.getHeure()) == true
            && verifMinute(duree2.getMinute()) == true
            && verifSeconde(duree2.getSeconde()) == true )
    {
        ProgrammationManager::getInstance().ajouterProgrammationTache(t,date2, duree2 );
        QMessageBox::information(this, "Projet Calendar", "La tâche a bien été ajoutée !");
        FenCreateEve::close();
    }
    else
        throw new CalendarException("Erreur dans le format de la date et/ou de la durée");
}

void FenCreateEve::on_btnCancel_clicked()
{
    FenCreateEve::close();
}
