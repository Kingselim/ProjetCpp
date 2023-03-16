#include "clients.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QtWidgets/QMessageBox>
#include <QRegularExpression>

Clients::Clients()
{
    CIN=0; nom=""; prenom=""; tel=0; adresse=""; email=""; age=0 ;

}


Clients::Clients(int CIN,QString nom,QString prenom,int tel,QString adresse,QString email,int age)
 {
this->CIN=CIN; this->nom=nom; this->prenom=prenom; this->tel=tel; this->adresse=adresse; this->email=email; this->age=age;
}

int getCIN();
QString getnom();
QString getprenom();
int gettel();
QString getadresse();
QString getemail();
int getage();

void setCIN(int);
void setnom(QString);
void setprenom(QString);
void settel(int);
void setadresse(QString);
void setemail(QString);
void setage(int);

bool Clients::ajouter()
{
    QSqlQuery query;

    QString CIN_string = QString::number(CIN);
    if (CIN_string.length() != 8) {
        QMessageBox::warning(nullptr, "CIN invalide", "Le CIN doit contenir exactement 8 nombres! ");
        return false;
    }
    if (nom.contains(QRegExp("[0-9]")) || prenom.contains(QRegExp("[0-9]"))) {
        QMessageBox::warning(nullptr, "Nom ou prenom invalide", "Le nom et le prenom ne doivent pas contenir de chiffres.");
        return false;
    }

    QString tel_string = QString::number(tel);
    if (tel_string.length() != 8) {
        QMessageBox::warning(nullptr, "Telephone invalide", "Le telephone doit contenir exactement 8 chiffres.");
        return false;
    }
    QString age_string = QString::number(age);
    if (age < 0 || age > 100) {
        QMessageBox::warning(nullptr, "Age invalide", "L'age doit etre compris entre 0 et 100.");
        return false;
    }

    // All checks passed, insert data into the database
    query.prepare("INSERT INTO CLIENTS (CIN,nom,prenom,tel,adresse,email,age) "
                  "VALUES (:CIN,:nom,:prenom,:tel,:adresse,:email,:age)");
    query.bindValue(":CIN",CIN_string);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":tel",tel_string);
    query.bindValue(":adresse",adresse);
    query.bindValue(":email",email);
    query.bindValue(":age",age_string);

    return query.exec();
}

QSqlQueryModel* Clients::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM Clients");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("tel"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("age"));

    return model;
}

/*bool Clients::supprimer(int CIN)
{
    QSqlQuery query;
          query.prepare("Delete from Clients where CIN=:CIN");

          QString CIN_string=QString::number(CIN);
          query.bindValue(":CIN",CIN_string);
          return query.exec();
}*/


bool Clients::supprimer(int CIN)
{
QSqlQuery query;
QString res=QString::number(CIN);
query.prepare("Delete from Clients where CIN= :CIN");
query.bindValue(":CIN",res);
return query.exec();
}


bool Clients::modifier(int CIN,QString nom,QString prenom,int tel,QString adresse ,QString email, int age )
{
     QSqlQuery query;

     query.prepare("UPDATE Clients SET CIN=:CIN,nom=:nom,prenom=:prenom,tel=:tel,adresse=:adresse,email=:email,age=:age WHERE CIN=:CIN");

     QString CIN_string=QString::number(CIN);




     query.bindValue(":CIN",CIN_string);
     query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":tel",tel);
     query.bindValue(":adresse",adresse);
     query.bindValue(":email",email);
     query.bindValue(":adresse",adresse);
     query.bindValue(":age",age);
     return query.exec();
 }


QSqlQueryModel * Clients::remplircombo()
{
    QSqlQueryModel * mod= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select CIN from Clients");
    query.exec();
    mod->setQuery(query);
    return mod;
}



QSqlQuery Clients::trouver_client(int CIN)
{
    QSqlQuery query;


    QString CIN_string=QString::number(CIN);
    query.prepare("select * from Clients where CIN=:CIN ");
    query.bindValue(":CIN",CIN_string);
    query.exec();
    QStringList list;


    return query;
}



