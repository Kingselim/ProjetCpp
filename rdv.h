#ifndef RDV_H
#define RDV_H
#include <QDate>
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QCalendarWidget>
using namespace std;


class rdv
{
    QString adresse_visite,date_visite,heure_visite;
    int num_visite,etat,id,matricule;


public:
    //Constructeurs
    rdv();
    rdv(int,int,QString,int,int,QString,QString);

    //Getters
    QString getadresse_visite(){return adresse_visite;}
    QString getdate_visite(){return date_visite;}
    QString getheure_visite(){return heure_visite;}
    int getmatricule(){return matricule;}
    int getnum_visite(){return num_visite;}
    int getetat(){return etat;}
    int getid(){return id;}

    //Setters
    void setadresse_visite(QString a){adresse_visite=a;}
    void setdate_visite(QString d){date_visite=d;}
    void setheure_visite(QString h){heure_visite=h;}
    void setmatricule(int m){matricule=m;}
    void setnum_visite(int nv){this->num_visite=nv;}
    void setetat(int e){this->etat=e;}
    void setid(int id){this->id=id;}


    //Fonctionnalités de base
    bool ajouter();
    QSqlQueryModel * afficher_rdv();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel*chercher_rdv(QString rech);
    QSqlQueryModel * remplircombo();
    QSqlQueryModel * remplircombo1();
    bool modifier(int,int,QString,int,int,QString,QString);
};

#endif // RDV_H
