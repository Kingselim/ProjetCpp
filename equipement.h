#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H


#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QtGui>
#include <QtSql>
#include <QtCore>

class Equipement
{
public:
    Equipement();
    Equipement(int,QString,QString,QString,int);
    bool ajouter();
    QSqlQuery trouver_equipement(int);
    QSqlQuery complett();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    QSqlQueryModel*chercher_Equipement(QString rech);
    bool modifier(QString,QString,QString,QString,QString);
    QSqlQueryModel * remplircombo();
    //QSqlQueryModel * remplircomboCalcul();
    QSqlQuery request(QString);
    QStringList listequipement();
    int calculetat_equipement(int etat_equipement);
    //int calculdescription(QString);
    QSqlQueryModel * afficherecherche(QString);
    int Calculer(QString);


private:
    int id_equipement;
    QString nom_centre;
    QString nom_equipement;
    QString date_intervention;
    int etat_equipement;
};
#endif // EQUIPEMENT_H
