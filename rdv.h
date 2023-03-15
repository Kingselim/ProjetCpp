#ifndef RDV_H
#define RDV_H
#include <QDate>
#include<QString>
#include<QSqlQuery>
#include <QSqlTableModel>
#include<QSqlQueryModel>
#include <QCalendarWidget>
using namespace std;


class rdv
{private:
    QString adresse_visite,date_visite,heure_visite;
    int num_visite,etat,id,matricule;


public:
    //Constructeurs
    rdv();
    rdv(int,int,QString,QString,int,QString,int);

    //Getters
    int getid(){return id;}
    int getmatricule(){return matricule;}
    QString getdate_visite(){return date_visite;}
    QString getheure_visite(){return heure_visite;}
    int getnum_visite(){return num_visite;}
    QString getadresse_visite(){return adresse_visite;}
    int getetat(){return etat;}


    //Setters
    void setid(int id){this->id=id;}
    void setmatricule(int m){matricule=m;}
    void setdate_visite(QString d){date_visite=d;}
    void setheure_visite(QString h){heure_visite=h;}
    void setnum_visite(int nv){this->num_visite=nv;}
    void setadresse_visite(QString a){adresse_visite=a;}
    void setetat(int e){this->etat=e;}



    //Fonctionnalités de base
    bool ajouter();

    QSqlQueryModel * afficher_rdv();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel*chercher_rdv(QString rech);
    QSqlQueryModel * remplircombo();
    QSqlQueryModel * remplircombo1();
    QSqlQueryModel * remplircombosupp();
    bool modifier(int,int,QString,QString,QString,int,int);
    QSqlQueryModel *trid(QString a);
     QSqlQueryModel * afficherecherche(QString);
     QSqlQuery trouver_num_visite(int);
     int calculAdresse_visite(QString Adresse_visite);
     QStringList listAdresse_visite();


};

#endif // RDV_H
