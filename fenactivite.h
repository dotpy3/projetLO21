#ifndef FENACTIVITE_H
#define FENACTIVITE_H
#include "QMessageBox"
#include "QDialog"
#include "QString"
#include "QDate"
#include "QTime"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QDateEdit>
#include <QWidget>
#include <QTimeEdit>
#include <QMessageBox>
#include <QObject>
#include "duree.h"
#include "date.h"
#include "tacheunitaire.h"
#include <QComboBox>
#include <QDialog>



namespace Ui {
class Fenactivite;
}

class Fenactivite : public QDialog
{
    Q_OBJECT
    QHBoxLayout *couche;
    QVBoxLayout *couche1, *couche2,*couche3;
    QLabel *createAct, *titre, *date, *duree;
    QPushButton *annuler, *sauver;
    QTextEdit *textTitre;
    QDateEdit *dateDeb;
    QTimeEdit *dur;

public:
    explicit Fenactivite(QWidget *parent = 0);
    ~Fenactivite();

private slots:
    void on_btnSave_clicked();

    void on_BtnCancel_clicked();

private:
    Ui::Fenactivite *ui;
};

#endif // FENACTIVITE_H
