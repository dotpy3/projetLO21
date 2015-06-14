#include "fenprincipale.h"

QString dayOfTheWeek(int i){
    switch(i){
        case 1:
            return QString("Monday");
        case 2:
            return QString("Tuesday");
        case 3:
            return QString("Wednesday");
        case 4:
            return QString("Thursday");
        case 5:
            return QString("Friday");
        case 6:
            return QString("Saturday");
        case 7:
            return QString("Sunday");
        default:
            return QString("");
    }
}

FenPrincipale::FenPrincipale(QWidget *parent) :
    QWidget(parent){

    this->resize(800,800);
    this->setWindowTitle("Calendrier");

    menFichier = new QMenu("Fichier");
    menEdition = new QMenu("Edition");
    menGerer = new QMenu("Gérer");

    QWidget *barreWidget = new QWidget(this);

    barreMenus = new QMenuBar(barreWidget);

    QAction *action1 = new QAction("Exporter la semaine",menFichier);
    QAction::connect(action1, SIGNAL(triggered()), this, SLOT(/*export semaine ?*/  ));

    QAction *action2 = new QAction("Quitter",menFichier);
    QAction::connect(action2, SIGNAL(triggered()), this, SLOT(quit()));


    QMenu* menAddEvent = menEdition->addMenu("Ajouter un événement");
    QAction* menCreaActivite = menAddEvent->addAction("Activité");
    QAction* menCreaTache = menAddEvent->addAction("Tâche");

    QAction::connect(menAddEvent,SIGNAL(triggered()),this,SLOT(openCreationActivity()));

    QAction* projets = menGerer->addAction("Projet");
    QAction::connect(projets, SIGNAL(triggered()), this, SLOT(fetchProjets()));

    barreMenus->addMenu(menFichier);
    barreMenus->addMenu(menEdition);
    barreMenus->addMenu(menGerer);

    grid = new QTableView();
    grid->resize(780,780);

    ProgrammationManager &pm = ProgrammationManager::getInstance();

    QStandardItemModel *model = new QStandardItemModel(24,7,this);
    for (int i = 0; i < 7; i++){
        model->setHorizontalHeaderItem(i,
                                       new QStandardItem(dayOfTheWeek(i+1)));
    }
    for (int i = 0; i < 24; i++){
        model->setVerticalHeaderItem(i,new QStandardItem(QString((to_string(i) + "h").c_str())));
    }

    grid->setModel(model);

    QHBoxLayout *choice = new QHBoxLayout();
    QPushButton *changeLeft = new QPushButton("<<<<<");

    QPushButton::connect(changeLeft,SLOT(click()),this,SIGNAL(changeLeft()));

    QLabel *label = new QLabel("Pas de semaine sélectionnée");
    QPushButton *changeRight = new QPushButton(">>>>>");

    QPushButton::connect(changeRight,SLOT(click()),this,SIGNAL(changeRight()));

    choice->addWidget(changeLeft);
    choice->addWidget(label);
    choice->addWidget(changeRight);


    QVBoxLayout* layout = new QVBoxLayout();
    layout->addLayout(choice);
    layout->addWidget(grid);

    this->setLayout(layout);

    std::cout<<"test1";

}

FenPrincipale::~FenPrincipale()
{
    delete menFichier;
    delete cal;
    delete menEdition;
    delete menGerer;
    delete barreMenus;

}

void FenPrincipale::quit()
{
    FenPrincipale::close();
}

void FenPrincipale::fetchProjets(){

    FenGestionProjets* gestionProjets = new FenGestionProjets();
    gestionProjets->show();
}

void FenPrincipale::openCreationActivity(){
    //FenCreateEve* createEvenement = new
}

void FenPrincipale::openCreationTask(){

}
