#ifndef INTERFACE_RENDEZVOUS_H
#define INTERFACE_RENDEZVOUS_H

#include <QMainWindow>
#include "rdv.h"
namespace Ui {
class interface_rendezvous;
}

class interface_rendezvous : public QMainWindow
{
    Q_OBJECT

public:
    explicit interface_rendezvous(QWidget *parent = nullptr);
    ~interface_rendezvous();



private slots:
   // void on_pushButton_clicked();

    void refresh();


    void on_btajouterrdv_clicked();

    void on_btpdfrdv_clicked();

    void on_btsupprimerrdv_clicked();

    void on_bttrierrdv_clicked();

    void on_linerecherche_cursorPositionChanged(int arg1, int arg2);

    void on_btvaliderrdv_clicked();


    void on_numvm_currentIndexChanged(int index);

    void statistique1();

private:
    Ui::interface_rendezvous *ui;
    rdv Etmp;
};

#endif // INTERFACE_RENDEZVOUS_H
