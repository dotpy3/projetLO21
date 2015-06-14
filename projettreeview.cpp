#include "projettreeview.h"

projetTreeView::projetTreeView(Projet& proj, QObject *parent):QAbstractItemModel(parent),projtemp(false)
{
    projet = &proj;
}

projetTreeView::projetTreeView(QObject *parent):QAbstractItemModel(parent),projtemp(true){
    projet = new Projet("temp");
}

projetTreeView::~projetTreeView()
{
    if (projtemp) delete projet;
}

void projetTreeView::changeProjet(Projet& proj){
    if (projtemp) delete projet;
    projtemp = false;
    projet = &proj;
}

QVariant projetTreeView::data(const QModelIndex &index, int role) const{
    if (!index.isValid()) return QString("");
    if (role != Qt::DisplayRole) return QString("");

    Tache* item = static_cast<Tache*>(index.internalPointer());

    return QVariant(QString(item->getTitre().c_str()));
}

Qt::ItemFlags projetTreeView::flags(const QModelIndex &index) const{
    if (!index.isValid()) return 0;
    return QAbstractItemModel::flags(index);
}

QVariant projetTreeView::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return QString(projet->getTitre().c_str());

    return QString("");
}

QModelIndex projetTreeView::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row,column,parent)) return QModelIndex();

    if(!parent.isValid()){
        if(row < projet->premiersEnfants().size()) {
            return createIndex(row,column,projet->premiersEnfants()[row]);
        } else {
            return QModelIndex();
        }
    } else {
        TacheComposee* parentItem = static_cast<TacheComposee*>(parent.internalPointer());
        Tache* childItem = parentItem->getListeTaches()[row];
        return createIndex(row,column,childItem);
    }
}

QModelIndex projetTreeView::parent(const QModelIndex &index) const{
    int row;
    if (!index.isValid()) return QModelIndex();

    vector<TacheComposee*> vecteur = projet->getParente(static_cast<Tache*>(index.internalPointer()));
    if (vecteur.size() == 0) return QModelIndex();

    // on veut déterminer la ligne dans laquelle il est
    if (vecteur.size() == 1) {
        vector<Tache*> premiersEnfantsDuProjet = projet->premiersEnfants();
        for (size_t i=0;i<premiersEnfantsDuProjet.size();i++){
            if (vecteur.back() == premiersEnfantsDuProjet[i]) row = i;
        }
    } else {
        TacheComposee* listeEnfants = vecteur[vecteur.size()-2];
        for (int i=0;i<listeEnfants->getNbTaches();i++){
            if (vecteur.back() == listeEnfants->getListeTaches()[i]) row = i;
        }
    }

    return createIndex(row, 0, vecteur.back());
}

int projetTreeView::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid()){
        return projet->premiersEnfants().size();
    } else {
        Tache* tache = static_cast<Tache*>(parent.internalPointer());
        if (!tache->isTacheComposee()) return 0;
        else {
            TacheComposee* tacheC = static_cast<TacheComposee*>(parent.internalPointer());
            return tacheC->getNbTaches();
        }
    }
}

void projetTreeView::update(QString* phrase){
    ProjetManager& pm = ProjetManager::getInstance();
    changeProjet(*pm.getProjet(phrase->toStdString()));
}
