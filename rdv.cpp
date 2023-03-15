#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include "rdv.h"
rdv::rdv()
{
     id=0;
     matricule=0;
     date_visite="";
     heure_visite="";
     num_visite=0;
     adresse_visite="";
     etat=0;

}
rdv::rdv(int id,int matricule,QString date_visite,QString heure_visite,int num_visite,QString adresse_visite,int etat)
{
  this->id=id;
  this->matricule=matricule;
  this->date_visite=date_visite;
  this->heure_visite=heure_visite;
  this->num_visite=num_visite;
  this->adresse_visite=adresse_visite;
  this->etat=etat;




}

bool rdv::ajouter()
{
   QSqlQuery query;
   QString res = QString::number(id);
   query.prepare("insert into rendez_vous(num_visite,date_visite,adresse_visite,matricule,etat,id_employe,heure_visite) values (:num_visite,:date_visite,:adresse_visite,:matricule,:etat,:id_employe,:heure_visite)");
   query.bindValue(":id_employe", id);
   query.bindValue(":matricule", matricule);
   query.bindValue(":date_visite", date_visite);
   query.bindValue(":heure_visite", heure_visite);
   query.bindValue(":num_visite", num_visite);
   query.bindValue(":adresse_visite", adresse_visite);
   query.bindValue(":etat", etat);

   return query.exec();
}

bool rdv::modifier(int id,int matricule,QString date_visite,QString heure_visite,QString adresse_visite,int num_visite,int etat)
{
     QSqlQuery query;

     query.prepare("UPDATE rendez_vous SET num_visite=:num_visite,date_visite=:date_visite,adresse_visite=:adresse_visite,matricule=:matricule,etat=:etat,id_employe=:id_employe,heure_visite=:heure_visite    WHERE num_visite=:num_visite");
    QString id_string=QString::number(id);
    QString matricule_string=QString::number(matricule);
    QString num_visite_string=QString::number(num_visite);
    QString etat_string=QString::number(etat);



     query.bindValue(":id_employe", id_string);
     query.bindValue(":matricule", matricule_string);
     query.bindValue(":date_visite", date_visite);
     query.bindValue(":heure_visite", heure_visite);
     query.bindValue(":num_visite", num_visite_string);
     query.bindValue(":adresse_visite", adresse_visite);
     query.bindValue(":etat", etat_string);


qInfo()<<id <<"id"<<endl;

qInfo()<<matricule <<"matricule"<<endl;

qInfo()<<date_visite <<"date visite"<<endl;

qInfo()<<heure_visite <<"heure visite"<<endl;

qInfo()<<num_visite <<"num visite"<<endl;

qInfo()<<adresse_visite <<"adresse visite"<<endl;

qInfo()<<etat <<"etat"<<endl;





     return query.exec();

}











QSqlQueryModel * rdv::afficher_rdv()
{
QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("select * from rendez_vous");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("num_visite"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("date_visite"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("adresse_visite"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("matricule"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("etat"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("id_employe"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("heure_visite"));



return model;
}

bool rdv::supprimer(int num_visite)
{
QSqlQuery query;
QString res=QString::number(num_visite);
query.prepare("Delete from RENDEZ_VOUS where num_visite= :num_visite");
query.bindValue(":num_visite",res);
return query.exec();
}


//******REMPLIR COMBO BOX
QSqlQueryModel * rdv::remplircombo()
{
    QSqlQueryModel * mod= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select MATRICULE from VEHICULES");
    query.exec();
    mod->setQuery(query);
    return mod;
}

QSqlQueryModel * rdv::remplircombo1()
{
    QSqlQueryModel * mod= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select IDENTIFIANT from EMPLOYES");
    query.exec();
    mod->setQuery(query);
    return mod;
}

QSqlQueryModel * rdv::remplircombosupp()
{
    QSqlQueryModel * mod= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select Num_visite from Rendez_vous");
    query.exec();
    mod->setQuery(query);
    return mod;
}


QSqlQueryModel * rdv::afficherecherche(QString res)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from RENDEZ_VOUS  where (num_visite LIKE '%"+res+"%' OR matricule LIKE '%"+res+"%' OR date_visite LIKE '%"+res+"%')");
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("num_visite"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("date_visite"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("adresse_visite"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("matricule"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("etat"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("id_employe"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("heure_visite"));


    return model;
}



QSqlQueryModel *rdv::trid(QString a)
{
    QSqlQueryModel *model=new QSqlQueryModel;
    if(a=="Date")
    {
      model->setQuery("select * from RENDEZ_VOUS order by date_visite");

    }
   else if(a=="Numero Visite")
    {
      model->setQuery("select * from RENDEZ_VOUS order by num_visite");

    }
    else if(a=="Adresse")
     {
      model->setQuery("select * from RENDEZ_VOUS order by adresse_visite");

     }
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("num_visite"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("date_visite"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("adresse_visite"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("matricule"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("etat"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("id_employe"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("heure_visite"));
return model;
}




QSqlQuery rdv::trouver_num_visite(int num_visite)
{
    QSqlQuery query;


    QString num_visite_string=QString::number(num_visite);
    query.prepare("select * from RENDEZ_VOUS where num_visite=:num_visite ");
    query.bindValue(":num_visite",num_visite_string);
    query.exec();
    QStringList list;


    return query;
}

int rdv::calculAdresse_visite(QString Adresse_visite)
{
    QSqlQuery query;
     query.prepare("select  * from RENDEZ_VOUS  WHERE ADRESSE_VISITE= :Adresse_visite ");
     query.bindValue(":Adresse_visite",Adresse_visite);

     query.exec();
      int total=0;

     while(query.next()){
       total++;

     }


     return total;
}
QStringList rdv::listAdresse_visite()
{
    QSqlQuery query;
    query.prepare("select DISTINCT ADRESSE_VISITE from RENDEZ_VOUS");
    query.exec();
    QStringList list;
    while(query.next()){
        list.append(query.value(0).toString());
    }

    return list;
}
