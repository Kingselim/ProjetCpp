#ifndef CLIENTS_H
#define CLIENTS_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QtGui>
#include <QtSql>
#include <QtCore>
//#include <QtCharts>

class Clients
{
public:
    //constructeurs

    Clients();
    Clients(int,QString,QString,int,QString,QString,int);
    //getters
    int getCIN();
    QString getnom();
    QString getprenom();
    int gettel();
    QString getadresse();
    QString getemail();
    int getage();

    //setters

    void setCIN(int CIN) ;
    void setnom(QString);
    void setprenom(QString);
    void settel(int);
    void setadresse(QString);
    void setemail(QString);
    void setage(int);

    //crud

       bool ajouter();
       QSqlQueryModel* afficher();
       bool supprimer(int);
       bool modifier(int,QString,QString,int,QString,QString,int);
       QSqlQueryModel * remplircombo();
       QSqlQueryModel*chercher_client(QString rech);
       QSqlQueryModel*tri_CIN();
       QSqlQueryModel*tri_nom();
       QSqlQueryModel*tri_prenom();
        QSqlQuery trouver_client(int);

 private:
    int CIN, tel, age;
    QString nom, prenom, adresse, email;




};

#endif // CLIENTS_H
