#ifndef FENPROJET_H
#define FENPROJET_H

#include <QMainWindow>

namespace Ui {

    class FenProjet : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit FenProjet(QWidget *parent = 0);
        ~FenProjet();

    private:
        Ui::FenProjet *ui;
    };

}
#endif // FENPROJET_H
