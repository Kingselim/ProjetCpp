#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include "equipement.h"

Equipement::Equipement()
{
    id_equipement=0; nom_centre=""; nom_equipement=""; date_intervention=""; etat_equipement=0;
}

Equipement::Equipement (int id_equipement,QString nom_centre,QString nom_equipement ,QString date_intervention,int etat_equipement)
{
    this->id_equipement=id_equipement;
    this->nom_centre=nom_centre;
    this->nom_equipement=nom_equipement;
    this->date_intervention=date_intervention;
    this->etat_equipement=etat_equipement;}


    bool Equipement::ajouter()
    {
        QSqlQuery query;
        QString id_equipement_string=QString::number(id_equipement);
        QString etat_equipement_string=QString::number(etat_equipement);

              query.prepare("INSERT INTO EQUIPEMENT (ID_EQUIPEMENT,NOM_CENTRE,NOM_EQUIPEMENT,DERNIERE_DATE_INTERVENTION,ETAT_EQUIPEMENT) "
                            "VALUES (:ID_EQUIPEMENT, :NOM_CENTRE, :NOM_EQUIPEMENT, :DERNIERE_DATE_INTERVENTION, :ETAT_EQUIPEMENT)");
              query.bindValue(":ID_EQUIPEMENT",id_equipement_string);
               query.bindValue(":NOM_CENTRE",nom_centre);
               query.bindValue(":NOM_EQUIPEMENT",nom_equipement);
                query.bindValue(":DERNIERE_DATE_INTERVENTION",date_intervention);
                 query.bindValue(":ETAT_EQUIPEMENT",etat_equipement_string);
              return query.exec();


    }
QSqlQuery Equipement::complett()
    {QSqlQuery query;

    query.prepare("select ID_EQUIPEMENT from EQUIPEMENT");

        return query;
    }
bool Equipement::supprimer(int id_equipementt)
{

        QSqlQuery query;
        QString id_equipement_string=QString::number(id_equipementt);
              query.prepare("Delete from EQUIPEMENT where ID_EQUIPEMENT=:id_equipement");
              query.bindValue(id_equipement,id_equipement_string);
              return query.exec();

}

QSqlQuery Equipement::trouver_equipement(int id_equipement)
{
    QSqlQuery query;

    QString id_equipement_string=QString::number(id_equipement);
    qInfo()<<id_equipement <<"haw el ID_EQUIPEMENT ya baba"<<endl;
    query.prepare("select ID_EQUIPEMENT from EQUIPEMENT ID_EQUIPEMENT=:ID_EQUIPEMENT");
    query.bindValue(":ID_EQUIPEMENT",id_equipement_string);
    query.exec();
    qDebug()<<query.value(1).toString() <<"haw el donnee"<<endl;

        return query;
}


QSqlQueryModel* Equipement::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM EQUIPEMENT");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EQUIPEMENT"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_CENTRE"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM_EQUIPEMENT"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("DERNIERE_DATE_INTERVENTION"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT_EQUIPEMENT"));

    return model;
}

QSqlQueryModel* Equipement::chercher_Equipement(QString rech){
    QString sQuery="SELECT *  FROM EQUIPEMENT WHERE ID_EQUIPEMENT LIKE'%"+rech+"%' or NOM_CENTRE LIKE'%"+rech+"%'or NOM_EQUIPEMENT LIKE'%"+rech+"%'";

    QSqlQueryModel*model4=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model4->setQuery(qry);
    return model4;
}
bool Equipement::modifier(QString id_equipement, QString nom_centre,QString nom_equipement,QString date_intervention,QString etat_equipement)
{
     QSqlQuery query;

     query.prepare("UPDATE EQUIPEMENT SET NOM_CENTRE=:NOM_CENTRE,NOM_EQUIPEMENT=:NOM_EQUIPEMENT,DERNIERE_DATE_INTERVENTION=:DERNIERE_DATE_INTERVENTION,ETAT_EQUIPEMENT=:ETAT_EQUIPEMENT where ID_EQUIPEMENT=:ID_EQUIPEMENT");
      query.bindValue(":ID_EQUIPEMENT",id_equipement);
     query.bindValue(":NOM_CENTRE",nom_centre);
     query.bindValue(":NOM_EQUIPEMENT",nom_equipement);
     query.bindValue(":DERNIERE_DATE_INTERVENTION",date_intervention);
     query.bindValue(":ETAT_EQUIPEMENT",etat_equipement);



     return query.exec();
}

//******REMPLIR COMBO BOX

QSqlQueryModel * Equipement::remplircombo()
{
    QSqlQueryModel * mod= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select ID_EQUIPEMENT from EQUIPEMENT");
    query.exec();
    mod->setQuery(query);
    return mod;
}


QSqlQuery Equipement::request(QString id_equipement)
{
    QSqlQuery query;
    query.prepare("select * from EQUIPEMENT where ID_EQUIPEMENT= '"+id_equipement+"'");
    query.addBindValue(id_equipement);
    query.exec();
    return query;
}

//******RECHERCHE AVANCEE

/*QSqlQueryModel * equipement::afficherecherche(QString res)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from EQUIPEMENT  where (id LIKE '%"+res+"%' OR nom LIKE '%"+res+"%' OR prix LIKE '%"+res+"%' OR description LIKE '%"+res+"%' )");
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));

    return model;
}*/


/*int equipement::calculdescription(QString description)
{
    QSqlQuery query;
     query.prepare("select  * from EQUIPEMENT  WHERE description= :description ");
     query.bindValue(":description",description);

     query.exec();
      int total=0;

     while(query.next()){
       total++;

     }


     return total;
}
*/
//********STAT

//STAT
/*QStringList equipement::listdescription()
{
    QSqlQuery query;
    query.prepare("select DISTINCT description from EQUIPEMENT");
    query.exec();
    QStringList list;
    while(query.next()){
        list.append(query.value(0).toString());
    }

    return list;
}
*/
QStringList Equipement::listequipement()
{
    QSqlQuery query;
    query.prepare("select DISTINCT ETAT_EQUIPEMENT from EQUIPEMENT");
    query.exec();
    QStringList list;
    while(query.next()){
        list.append(query.value(0).toString());
    }

    return list;
}
int Equipement::calculetat_equipement(int etat_equipement)
{
    QSqlQuery query;
    QString etat_equipement_string=QString ::number(etat_equipement);
     query.prepare("select  * from EQUIPEMENT  WHERE ETAT_EQUIPEMENT= :etat_equipement ");
     query.bindValue(":etat_equipement",etat_equipement);

     query.exec();
      int total=0;

     while(query.next()){
       total++;

     }


     return total;
}


