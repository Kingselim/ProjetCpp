#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include "personnel.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
employe::employe()
{
    IDENTIFIANT =0;
    NOM="";
    PRENOM="";
    DATE_DE_NAISSANCE="";
    LIEU_DE_TRAVAIL="";
    TELEPHONE=0;
    EMAIL="";
    SALAIRE=0;
    FONCTION="";
    GENRE="";
}

employe::employe (int IDENTIFIANT,QString NOM,QString PRENOM,QString DATE_DE_NAISSANCE,QString LIEU_DE_TRAVAIL,int TELEPHONE,QString EMAIL,int SALAIRE,QString FONCTION ,QString GENRE)
{
    this->IDENTIFIANT=IDENTIFIANT;
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->DATE_DE_NAISSANCE=DATE_DE_NAISSANCE;
    this->LIEU_DE_TRAVAIL=LIEU_DE_TRAVAIL;
    this->TELEPHONE=TELEPHONE;
    this->EMAIL=EMAIL;
    this->SALAIRE=SALAIRE;
    this->FONCTION=FONCTION;
    this->GENRE=GENRE;

}

bool employe::ajouter1()
{
    QSqlQuery query;
    QString IDENTIFIANT_string=QString::number(IDENTIFIANT);
    QString TELEPHONE_string=QString::number(TELEPHONE);
    QString SALAIRE_string=QString::number(SALAIRE);


          query.prepare("INSERT INTO EMPLOYES (IDENTIFIANT,NOM,PRENOM,DATE_DE_NAISSANCE,LIEU_DE_TRAVAIL,TELEPHONE,EMAIL,SALAIRE,FONCTION,GENRE) "
                        "VALUES (:IDENTIFIANT, :NOM, :PRENOM, :DATE_DE_NAISSANCE, :LIEU_DE_TRAVAIL, :TELEPHONE, :EMAIL, :SALAIRE, :FONCTION, :GENRE)");

          query.bindValue(":IDENTIFIANT",IDENTIFIANT_string);
          query.bindValue(":NOM",NOM);
          query.bindValue(":PRENOM",PRENOM);
          query.bindValue(":DATE_DE_NAISSANCE",DATE_DE_NAISSANCE);
          query.bindValue(":LIEU_DE_TRAVAIL",LIEU_DE_TRAVAIL);
          query.bindValue(":TELEPHONE",TELEPHONE_string);
          query.bindValue(":EMAIL",EMAIL);
          query.bindValue(":SALAIRE",SALAIRE_string);
          query.bindValue(":FONCTION",FONCTION);
          query.bindValue(":GENRE",GENRE);
          qInfo()<<DATE_DE_NAISSANCE <<"haw el DATE YA BABA"<<endl;
          return query.exec();

}
bool employe::supprimer1(int IDENTIFIANT)
{
    QSqlQuery query;
          query.prepare("Delete from EMPLOYES where IDENTIFIANT=:IDENTIFIANT");

          QString IDENTIFIANT_string=QString::number(IDENTIFIANT);
          query.bindValue(":IDENTIFIANT",IDENTIFIANT_string);
          return query.exec();
}
QSqlQueryModel* employe::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM EMPLOYES");
           qInfo()<<DATE_DE_NAISSANCE <<"haw el DATE YA BABA"<<endl;
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDENTIFIANT"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("LIEU_DE_TRAVAIL"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEPHONE"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("EMAIL"));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("SALAIRE"));
          model->setHeaderData(8, Qt::Horizontal, QObject::tr("FONCTION"));
          model->setHeaderData(9, Qt::Horizontal, QObject::tr("GENRE"));

    return model;
}

bool employe:: modifier1(int IDENTIFIANT,QString NOM,QString PRENOM,QString DATE_DE_NAISSANCE,QString LIEU_DE_TRAVAIL,int TELEPHONE,QString EMAIL,int SALAIRE,QString FONCTION,QString GENRE)
{
    QSqlQuery query;
    QString IDENTIFIANT_string = QString::number(IDENTIFIANT);
    QString TELEPHONE_string=QString::number(TELEPHONE);
    QString SALAIRE_string=QString::number(SALAIRE);
            query.prepare("UPDATE EMPLOYES SET  IDENTIFIANT=:IDENTIFIANT, NOM=:NOM, PRENOM=:PRENOM, DATE_DE_NAISSANCE=:DATE_DE_NAISSANCE, LIEU_DE_TRAVAIL=:LIEU_DE_TRAVAIL, TELEPHONE=:TELEPHONE, EMAIL=:EMAIL, SALAIRE=:SALAIRE, FONCTION=:FONCTION, GENRE=:GENRE WHERE IDENTIFIANT=:IDENTIFIANT");
            query.bindValue(":IDENTIFIANT",IDENTIFIANT_string);
            query.bindValue(":NOM", NOM);
            query.bindValue(":PRENOM", PRENOM);
            query.bindValue(":DATE_DE_NAISSANCE",DATE_DE_NAISSANCE);
            query.bindValue(":LIEU_DE_TRAVAIL", LIEU_DE_TRAVAIL);
            query.bindValue(":TELEPHONE", TELEPHONE_string);
            query.bindValue(":EMAIL",EMAIL);
            query.bindValue(":SALAIRE", SALAIRE_string);
            query.bindValue(":FONCTION", FONCTION);
            query.bindValue(":GENRE", GENRE);

    return query.exec();
}

QSqlQueryModel* employe::chercher_employe(QString rech1){
    QString sQuery="SELECT *  FROM EMPLOYES WHERE IDENTIFIANT LIKE'%"+rech1+"%' or LIEU_DE_TRAVAIL LIKE'%"+rech1+"%'";

    QSqlQueryModel*model4=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model4->setQuery(qry);
    return model4;
}
QSqlQueryModel*employe::tri_id()
{
    QSqlQueryModel* model=new  QSqlQueryModel();
    model->setQuery("SELECT *FROM EMPLOYES ORDER BY IDENTIFIANT ASC");

   return model;
}
QSqlQueryModel* employe::tri_nom()
{
    QSqlQueryModel* model=new  QSqlQueryModel();
    model->setQuery("SELECT *FROM EMPLOYES ORDER BY NOM  ASC");

   return model;
}
QSqlQueryModel*employe::tri_salaire()
{
    QSqlQueryModel* model=new  QSqlQueryModel();
    model->setQuery("SELECT *FROM EMPLOYES ORDER BY SALAIRE DESC");

   return model;
}
//******REMPLIR COMBO BOX

QSqlQueryModel * employe::remplircombo()
{
    QSqlQueryModel * mod= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select IDENTIFIANT from EMPLOYES");
    query.exec();
    mod->setQuery(query);
    return mod;
}

QSqlQuery employe::trouver_employe(int IDENTIFIANT)
{
    QSqlQuery query;


    QString IDENTIFIANT_string=QString::number(IDENTIFIANT);
    query.prepare("select * from EMPLOYES where IDENTIFIANT=:IDENTIFIANT ");
    query.bindValue(":IDENTIFIANT",IDENTIFIANT_string);
    query.exec();
    QStringList list;


    return query;
}
QSqlQueryModel * employe::afficherrecherche(QString res)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from EMPLOYES  where (IDENTIFIANT LIKE '%"+res+"%' OR LIEU_DE_TRAVAIL LIKE '%"+res+"%' )");
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDENTIFIANT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("LIEU_DE_TRAVAIL"));


    return model;
}
/*int employe::calculegenre(QString GENRE)
{
    QSqlQuery query;
     query.prepare("select  * from EMPLOYES  WHERE GENRE= :GENRE ");
     query.bindValue(":GENRE",GENRE);

     query.exec();
      int total=0;

     while(query.next()){
       total++;

     }


     return total;
}*/
/*QStringList employe::listGENRE()
{
    QSqlQuery query;
    query.prepare("select DISTINCT GENRE from EMPLOYES");
    query.exec();
    QStringList list;
    while(query.next()){
        list.append(query.value(0).toString());
    }

    return list;
}*/




