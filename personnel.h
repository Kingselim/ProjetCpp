#ifndef PERSONNEL_H
#define PERSONNEL_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
//#include <QtCharts>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QtGui>
#include <QtSql>
#include <QtCore>
class employe
{
public:
    //constructeurs
    employe();
     employe(int,QString,QString,QString,QString,int,QString,int,QString,QString);


     // getters
     int getIDENTIFIANT(){return IDENTIFIANT;}
     QString getNOM(){return NOM ;}
     QString getPRENOM(){return PRENOM;}
     QString getDATE_DE_NAISSANCE(){return DATE_DE_NAISSANCE;}
     QString getLIEU_DE_TRAVAIL(){return LIEU_DE_TRAVAIL;}
     int getTELEPHONE(){return TELEPHONE;}
     QString getEMAIL(){return EMAIL;}
     int getSALAIRE(){return SALAIRE;}
     QString getFONCTION(){return FONCTION;}
     QString getGENRE(){return GENRE;}


    // setteurs
    void setIDENTIFIANT (int id){this->IDENTIFIANT=id;}
    void setNOM  (QString n ){NOM=n;}
    void setPRENOM(QString p){PRENOM=p;}
    void setDATE_DE_NAISSANCE(QString date){DATE_DE_NAISSANCE=date;}
    void setLIEU_DE_TRAVAIL(QString lieu_t){this->LIEU_DE_TRAVAIL=lieu_t;}
    void setTELEPHONE (int tel){this->TELEPHONE=tel;}
    void setEMAIL(QString email){EMAIL=email;}
    void setSALAIRE (int salaire){this->SALAIRE=salaire;}
    void setFONCTION(QString fn){FONCTION=fn;}
    void setGENRE(QString genre){GENRE=genre;}

    //cruds
    bool ajouter1();
    QSqlQueryModel * afficher();
    bool supprimer1(int);
    bool modifier1(int,QString,QString,QString,QString,int,QString,int,QString,QString);
    QSqlQueryModel * remplircombo();
    QSqlQuery trouver_employe(int);

    QSqlQueryModel*chercher_employe(QString rech1);
    QSqlQueryModel*tri_id();
    QSqlQueryModel*tri_nom();
    QSqlQueryModel*tri_salaire();

    //void exporterpdf(QTextBrowser *text);
    //QStringList listGENRE();

    //bool existance(QString );
    //QChart* statistique_chart();

    //int calculegenre(QString GENRE);
    QSqlQueryModel * afficherrecherche(QString);


private:
    int IDENTIFIANT;
    QString NOM;
    QString PRENOM;
    QString DATE_DE_NAISSANCE;
    QString LIEU_DE_TRAVAIL;
    int TELEPHONE;
    QString EMAIL;
    int SALAIRE;
    QString FONCTION;
    QString GENRE;
 //arduino a;
};

#endif // PERSONNEL_H
