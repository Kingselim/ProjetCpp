#include "interface_employe.h"
#include "ui_interface_employe.h"
#include "personnel.h"

//include pour temps
#include<QTimer>
#include<QDateTime>


#include <QMessageBox>
#include "connection.h"

#include<QtPrintSupport/QPrintDialog>
#include<QPrinter>
#include<QPrintPreviewDialog>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>

interface_employe::interface_employe(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interface_employe)
{
    ui->setupUi(this);
    this->setWindowTitle("Gestion Des Employes");
    //Ce code pour afficher le temps
    QTimer *timer=new QTimer(this);
    connect(timer ,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start();

    QDateTime datetime = QDateTime::currentDateTime();
    QString datetimetext = datetime.toString("dd / MMM / yyyy");
    ui->datetime_vehicule->setText(datetimetext);

    employe e;

    QSqlQueryModel *tv;
    tv = e.afficher();
    ui->tableemploye->setModel(tv);

            ui->IDENTIFIANTaj->setValidator(new QIntValidator(0,999, this));

            ui->SALAIREaj->setValidator(new QIntValidator(0,9999999, this));

            ui->TELEPHONEaj->setValidator(new QIntValidator(0,99999999, this));

            QRegExp regExp("^[A-Za-z]*$"); // Autorise uniquement les caractères numériques
            ui->NOMaj->setValidator(new QRegExpValidator(regExp, this));

            QRegExp regExppppp("^[A-Za-z]*$"); // Autorise uniquement les caractères numériques
            ui->PRENOMaj->setValidator(new QRegExpValidator(regExp, this));

            QRegExp regExppp("^[A-Za-z]*$"); // Autorise uniquement les majuscules et les chiffres
            ui->FONCTIONaj->setValidator(new QRegExpValidator(regExppppp, this));

          /*  QRegExp regEx("^[A-Za-z]*$"); // Autorise uniquement les majuscules et les chiffres
            ui->email->setValidator(new QRegExpValidator(regEx, this));*/



}
void interface_employe::showtime()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh:mm:ss");

    if((time.second() % 2)==0)
    {
        time_text[2]=' ';
        time_text[5]=' ';
    }

    ui->digitalclock_vehicule->setText(time_text);


}

interface_employe::~interface_employe()
{
    delete ui;
}

void interface_employe::refresh()
{
    ui->tableemploye->setModel(e.afficher());
    ui->IDENTIFIANTmod->setModel(e.remplircombo());
    ui->IDENTIFIANTsupp->setModel(e.remplircombo());

}

void interface_employe::on_ajouter1_clicked()
{
    int IDENTIFIANT = ui->IDENTIFIANTaj->text().toInt();
    QString NOM=ui->NOMaj->text();
    QString PRENOM=ui->PRENOMaj->text();
    QString DATE_DE_NAISSANCE=ui->DATE_DE_NAISSANCEaj->text();
    QString LIEU_DE_TRAVAIL=ui->LIEU_DE_TRAVAILaj->text();
    int TELEPHONE=ui->TELEPHONEaj->text().toInt();
    QString EMAIL = ui->EMAILaj->text();
    int SALAIRE = ui->SALAIREaj->text().toInt();
    QString FONCTION = ui->FONCTIONaj->text();
    QString GENRE = ui->GENREaj->text();



   employe e(IDENTIFIANT,NOM,PRENOM,DATE_DE_NAISSANCE,LIEU_DE_TRAVAIL,TELEPHONE,EMAIL,SALAIRE,FONCTION,GENRE) ;
   bool test=e.ajouter1();

   if(test)
   {

               QMessageBox::information(nullptr, QObject::tr("ok"),
                           QObject::tr("ajout effectué.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
refresh();
    }
           else
               QMessageBox::critical(nullptr, QObject::tr("not ok"),
                           QObject::tr("ajout non effectué.\n"

                                       "Click Cancel to exit."), QMessageBox::Cancel);
  ui->IDENTIFIANTaj->setText(" ");
  ui->NOMaj->setText(" ");
  ui->PRENOMaj->setText(" ");
  //ui->DATE_DE_NAISSANCEaj->setText(" ");
  ui->LIEU_DE_TRAVAILaj->setText(" ");
  ui->TELEPHONEaj->setText(" ");
  ui->EMAILaj->setText(" ");
  ui->SALAIREaj->setText(" ");
  ui->FONCTIONaj->setText(" ");
  ui->GENREaj->setText(" ");
refresh();
}
void interface_employe::on_supprimer1_clicked()
{

     employe e ;
     int IDENTIFIANT = ui->IDENTIFIANTsupp->currentText().toInt();
     bool test = e.supprimer1(IDENTIFIANT);
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




void interface_employe::on_modifier1_clicked()
{
     employe e;
     QString NOM = ui->NOMmod->text();
     QString PRENOM=ui->PRENOMmod->text();
     QString DATE_DE_NAISSANCE=ui->DATE_DE_NAISSANCEmod->text();
     QString LIEU_DE_TRAVAIL=ui->LIEU_DE_TRAVAILmod->text();
     int TELEPHONE =ui->TELEPHONEmod->text().toInt();
     QString EMAIL=ui->EMAILmod->text();
     int SALAIRE=ui->SALAIREmod->text().toInt();
     QString FONCTION = ui->FONCTIONmod->text();
     QString GENRE =ui->GENREmod->text();


     int IDENTIFIANT = ui->IDENTIFIANTmod->currentText().toInt();

      bool test = e.modifier1(IDENTIFIANT,NOM,PRENOM,DATE_DE_NAISSANCE,LIEU_DE_TRAVAIL,TELEPHONE,EMAIL,SALAIRE,FONCTION,GENRE);


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


void interface_employe::on_IDENTIFIANTmod_currentIndexChanged(int index1)
{
    employe e;
    QSqlQuery query;
    int IDENTIFIANT = ui->IDENTIFIANTmod->currentText().toInt();
    query = e.trouver_employe(IDENTIFIANT);
    QString item3;

    QStringList list_IDENTIFIANT;
    QStringList list_NOM;
    QStringList list_PRENOM;
    QStringList list_DATE_DE_NAISSANCE;
    QStringList list_LIEU_DE_TRAVAIL;
    QStringList list_TELEPHONE;
        QStringList list_EMAIL;
            QStringList list_SALAIRE;
                QStringList list_FONCTION;
                    QStringList list_GENRE;

    while(query.next()){
        list_IDENTIFIANT.append(query.value(2).toString());
        list_NOM.append(query.value(1).toString());
        list_PRENOM.append(query.value(2).toString());
        list_DATE_DE_NAISSANCE.append(query.value(3).toString());
        list_LIEU_DE_TRAVAIL.append(query.value(4).toString());
        list_TELEPHONE.append(query.value(5).toString());
        list_EMAIL.append(query.value(6).toString());
        list_SALAIRE.append(query.value(7).toString());
        list_FONCTION.append(query.value(8).toString());
        list_GENRE.append(query.value(9).toString());



    }

    foreach(QString item, list_NOM)
    {
           qDebug() << "List NOM = " << item;
           ui->NOMmod->setText(item);

    }
    foreach(QString item, list_PRENOM)
    {
           qDebug() << "List PRENOM = " << item;

           ui->PRENOMmod->setText(item);
    }
    foreach(QString item, list_DATE_DE_NAISSANCE)
    {
           qDebug() << "List DATE_DE_NAISSANCE = " << item;

           //ui->DATE_DE_NAISSANCEmod->setText(item);
    }
    foreach(QString item, list_LIEU_DE_TRAVAIL)
    {
           qDebug() << "List LIEU_DE_TRAVAIL = " << item;

           ui->LIEU_DE_TRAVAILmod->setText(item);
    }
    foreach(QString item, list_TELEPHONE)
    {
           qDebug() << "List TELEPHONE = " << item;

           ui->TELEPHONEmod->setText(item);
    }


    foreach(QString item, list_EMAIL)
    {
           qDebug() << "List EMAIL = " << item;

           ui->EMAILmod->setText(item);
    }
    foreach(QString item, list_SALAIRE)
    {
           qDebug() << "List SALAIRE = " << item;

           ui->SALAIREmod->setText(item);
    }
    foreach(QString item, list_FONCTION)
    {
           qDebug() << "List FONCTION = " << item;

           ui->FONCTIONmod->setText(item);
    }
    foreach(QString item, list_GENRE)
    {
           qDebug() << "List GENRE = " << item;

           ui->GENREmod->setText(item);
    }

}
 void interface_employe::on_recherche1_cursorPositionChanged(int arg1,int arg2)
 {

     ui->tableemploye->setModel(e.afficherrecherche(ui->recherche1->text()));


         if(ui->recherche1->text()=="")
         {
             ui->tableemploye->setModel(e.afficher());//refresh
         }
 }
/*void interface_employe::statistique2()
{

    QPieSeries *series=new QPieSeries();
    QStringList l=e.listGENRE();

    for (int i = 0; i < l.size(); ++i){

        series->append(l[i] ,e.calculegenre(l[i]));
    }

    QPieSlice *slice1=series->slices().at(1);
    slice1->setExploded(true);

    QChart *chart =new QChart();
    chart->addSeries(series);

    chart->setTitle("STATISTIQUE");
    chart->backgroundRoundness();
    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView *chartview=new QChartView(chart);
    chartview->setUpdatesEnabled(true);
    QGridLayout *mainLayout=new QGridLayout();
    mainLayout->addWidget(chartview,0,0);

    ui->stat2->setLayout(mainLayout);
    ui->stat2->layout()->update();
}*/

