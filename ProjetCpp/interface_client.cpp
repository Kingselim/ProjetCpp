#include "interface_client.h"
#include "ui_interface_client.h"
#include "clients.h"

//include pour temps
#include<QTimer>
#include<QDateTime>


#include <QMessageBox>
#include "connection.h"
#include<QtPrintSupport/QPrintDialog>
#include<QPrinter>
#include<QPrintPreviewDialog>
#include<QPieSeries>
#include<QtCharts>
#include<QChartView>


interface_Client::interface_Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interface_Client)
{
    ui->setupUi(this);
    this->setWindowTitle("Gestion Des Clients");
    ui->tableclient->setModel(Etmp.afficher());
}

interface_Client::~interface_Client()
{
    delete ui;
}

void interface_Client::refresh()
{
    ui->tableclient->setModel(c.afficher());
    ui->CINmod->setModel(c.remplircombo());
    ui->CINsupp->setModel(c.remplircombo());
  //  ui->nomcal->setModel(c.remplircomboCalcul());

}

void interface_Client::on_ajouter7_clicked()
{
    int CIN = ui->CINaj->text().toInt();
    QString nom=ui->NOMaj->text();
    QString prenom=ui->PRENOMaj->text();


    int tel=ui->TELEPHONEaj->text().toInt();
    QString adresse= ui->ADRESSEaj->text();
    QString email= ui->MAILaj->text();
    int age = ui->AGEaj->text().toInt();




   Clients c(CIN,nom,prenom,tel,adresse,email,age) ;
   bool test=c.ajouter();

   if(test)
   {

               QMessageBox::information(nullptr, QObject::tr("ok"),
                           QObject::tr("ajout effectué.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);

    }
           else
               QMessageBox::critical(nullptr, QObject::tr("not ok"),
                           QObject::tr("ajout non effectué.\n"

                                       "Click Cancel to exit."), QMessageBox::Cancel);
  ui->CINaj->setText(" ");
  ui->NOMaj->setText(" ");
  ui->PRENOMaj->setText(" ");

  ui->TELEPHONEaj->setText(" ");
  ui->ADRESSEaj->setText(" ");
  ui->MAILaj->setText(" ");
  ui->AGEaj->setText(" ");
 refresh();
}











void interface_Client::on_modifier7_clicked()
{
     Clients c;


     QString nom=ui->NOMmod->text();
     QString prenom=ui->PRENOMmod->text();
     int tel=ui->TELEPHONEmod->text().toInt();
     QString adresse=ui->ADRESSEmod->text();
     QString email=ui->MAILmod->text();
     int age=ui->AGEmod->text().toInt();

    int CIN = ui->CINmod->currentText().toInt();

      bool test = c.modifier(CIN,nom,prenom,tel,adresse,email,age);


      if(test)
      {

          QMessageBox::information(nullptr, QObject::tr("ok"),
                      QObject::tr("Modification effectué.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

refresh();
      }
      else
      {
          QMessageBox::critical(nullptr, QObject::tr("not ok"),
                      QObject::tr("Modification non effectué.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

         }
refresh();
}


void interface_Client::on_CINmod_currentIndexChanged(int index2)
{
    Clients c;
    QSqlQuery query;
    int CIN = ui->CINmod->currentText().toInt();
    query = c.trouver_client(CIN);
    QString item4;

    QStringList list_CIN;
    QStringList list_nom;
    QStringList list_prenom;

    QStringList list_tel;
        QStringList list_adresse;
            QStringList list_email;

                    QStringList list_age;

    while(query.next()){
        list_CIN.append(query.value(0).toString());
        list_nom.append(query.value(1).toString());
        list_prenom.append(query.value(2).toString());

        list_tel.append(query.value(3).toString());
        list_adresse.append(query.value(4).toString());
        list_email.append(query.value(5).toString());
        list_age.append(query.value(6).toString());




    }

    foreach(QString item, list_CIN)
    {
           qDebug() << "List CIN = " << item;
           //ui->CINmod->setText(item);

    }
    foreach(QString item, list_nom)
    {
           qDebug() << "List nom = " << item;

           ui->NOMmod->setText(item);
    }

    foreach(QString item, list_prenom)
    {
           qDebug() << "List prenom = " << item;

           ui->PRENOMmod->setText(item);
    }


    foreach(QString item, list_tel)
    {
           qDebug() << "List tel = " << item;

           ui->TELEPHONEmod->setText(item);
    }
    foreach(QString item, list_adresse)
    {
           qDebug() << "List adresse = " << item;

           ui->ADRESSEmod->setText(item);
    }
    foreach(QString item, list_email)
    {
           qDebug() << "List email = " << item;

           ui->MAILmod->setText(item);
    }
    foreach(QString item, list_age)
    {
           qDebug() << "List age = " << item;

           ui->AGEmod->setText(item);
    }



}








































void interface_Client::on_supprimer_7_clicked()
{
    Clients c ;
    int CIN = ui->CINsupp->currentText().toInt();
    bool test = c.supprimer(CIN);
    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("Supression effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

   refresh();
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("Supression non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

       }

}
