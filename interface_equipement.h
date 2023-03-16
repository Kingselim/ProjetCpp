#ifndef INTERFACE_EQUIPEMENT_H
#define INTERFACE_EQUIPEMENT_H

#include <QMainWindow>
#include"equipement.h"


namespace Ui {
class interface_equipement;
}

class interface_equipement : public QMainWindow
{
    Q_OBJECT

public:
    explicit interface_equipement(QWidget *parent = nullptr);
    ~interface_equipement();



private slots:
    void on_ajouter_clicked();

    void refresh();


    void on_supprimer_clicked();

    void on_idsupp_currentIndexChanged(int index);

    void on_lineEditchercher_cursorPositionChanged(int arg1, int arg2);

    //void on_idsupp_currentIndexChanged(const QString &arg1);

    void on_comboBoxox_currentIndexChanged(int index);

    void on_modifier_clicked();
    void statistiqueequipement();

private:
    Ui::interface_equipement *ui;
    Equipement E;
};

#endif // INTERFACE_EQUIPEMENT_H
