#ifndef INTERFACE_EMPLOYE_H
#define INTERFACE_EMPLOYE_H

#include <QMainWindow>
#include"personnel.h"
namespace Ui {
class interface_employe;
}

class interface_employe : public QMainWindow
{
    Q_OBJECT

public:
    explicit interface_employe(QWidget *parent = nullptr);
    ~interface_employe();
private slots:
    //afficher le temps
    void showtime();
    void on_pushButton_cliked();
    void refresh();
    void on_ajouter1_clicked();
    void on_supprimer1_clicked();
    void on_IDENTIFIANTsupp_currentIndexChanged(const QString &arg3);
    void on_IDENTIFIANTsupp_currentIndexChanged(int index);
    void on_modifier1_clicked();
    void on_recherche1_cursorPositionChanged(int arg1,int arg2);
    void on_IDENTIFIANTmod_currentIndexChanged(int index1);
    //void on_trier1_clicked();
    void on_pushButton_4_clicked();
    //void statistique2();

private:
    Ui::interface_employe *ui;
    employe e;
    QByteArray data;


};

#endif // INTERFACE_EMPLOYE_H
