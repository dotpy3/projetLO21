#include "main.h"

ProgrammationManager* ProgrammationManager::instance = 0;
ProjetManager* ProjetManager::instance = 0;

int main(int argc, char* argv[]){

    QApplication app(argc,argv);

    ProgrammationManager& proManager = ProgrammationManager::getInstance();
    ProjetManager& projManager = ProjetManager::getInstance();

    FenPrincipale fenGestion;

    fenGestion.show();

    app.exec();

    projManager.libererInstance();
    proManager.libererInstance();
    return 1;
}
