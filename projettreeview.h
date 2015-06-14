#ifndef PROJETTREEVIEW_H
#define PROJETTREEVIEW_H


#include <QAbstractItemModel>
#include "projetmanager.h"

class projetTreeView : public QAbstractItemModel
{
    Q_OBJECT
private:
    Projet* projet;
    bool projtemp;
public:
    projetTreeView(Projet& proj, QObject *parent = 0);
    ~projetTreeView();
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
        Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
        QVariant headerData(int section, Qt::Orientation orientation,
                            int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column,
    const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE{return 1;}
    projetTreeView(QObject *parent = 0);
    void changeProjet(Projet& proj);
public slots:
    void update(QString* phrase);
};

#endif // PROJETTREEVIEW_H
