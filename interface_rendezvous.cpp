#include "interface_rendezvous.h"
#include "ui_interface_rendezvous.h"
#include "rdv.h"
#include "interface_rendezvous.h"
//include pour temps
#include<QTimer>
#include<QDateTime>
#include<QDebug>
#include<QString>
#include<QSqlQuery>
#include <QMessageBox>
#include "connection.h"
#include <QPdfWriter>
#include <QPainter>
#include<QPieSeries>
#include<QtCharts>
#include<QChartView>

interface_rendezvous::interface_rendezvous(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interface_rendezvous)
{
    ui->setupUi(this);
    this->setWindowTitle("Gestion Des Rendez-vous");
    ui->tableView->setModel(Etmp.afficher_rdv());
    ui->matricule->setModel(Etmp.remplircombo());
    ui->Idc->setModel(Etmp.remplircombo1());
    ui->combosupp->setModel(Etmp.remplircombosupp());

    statistique1();
}

interface_rendezvous::~interface_rendezvous()
{
    delete ui;
}


void interface_rendezvous::refresh()
{
    ui->tableView->setModel(Etmp.afficher_rdv());
    ui->numvm->setModel(Etmp.remplircombosupp());
    ui->combosupp->setModel(Etmp.remplircombosupp());
    ui->matriculem->setModel((Etmp.remplircombo()));
    ui->idcm->setModel(Etmp.remplircombo1());


}

void interface_rendezvous::on_btajouterrdv_clicked()
{
    int id=ui->Idc->currentText().toInt();
    int matricule=ui->matricule->currentText().toInt();
    QString date_visite=ui->dateEdit->date().toString("dd/MM/yyyy");
    QString heure_visite=ui->timeEdit->time().toString("hh:mm");
    int num_visite=ui->numv->text().toInt();
    QString adresse_visite=ui->adressev->currentText();
    int etat=ui->etat->currentText().toInt();
    if (ui->numv->text().isEmpty()||ui->timeEdit->time().hour()<9||ui->timeEdit->time().hour()>18||!ui->numv->text().contains(QRegExp("^[0-9]+$")))
    {
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                              QObject::tr("ajout non effectué. Service fermé ou num incorrect\n"
                                                          "Click Cancel to exit."),QMessageBox::Cancel);
    }
    else
    {
        rdv r(id,matricule,date_visite,heure_visite,num_visite,adresse_visite,etat);
        bool test=r.ajouter();

           if(test)
           {QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("ajout avec succes"));}
           else QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                      QObject::tr("ajout non effectué.\n"
                                                  "Click Cancel to exit."),QMessageBox::Cancel);
    }
refresh();
}



void interface_rendezvous::on_btpdfrdv_clicked()
{
    QPdfWriter pdf("C:\\Users\\21650\\Desktop\\2A2\\QT\\smart_technical_visite_center\\smart_technical_visite_center\\pdfrdv.pdf");

    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::red);
    painter.setFont(QFont("Time New Roman", 25));
    painter.drawText(3000, 1400, "Liste Des Rendez_vous");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 15));
    painter.drawRect(100, 100, 9200, 2700); // dimension ta3 rectangle eli fih liste des rdv
    painter.drawRect(100, 3000, 9200, 500);
    painter.drawText(200,3300,"Num Visite");
    painter.drawText(1500,3300,"Date Visite");
    painter.drawText(2900,3300,"Adresse Visite");
    painter.drawText(4700,3300,"Matricule");
    painter.drawText(5800,3300,"Etat");
    painter.drawText(6400,3300,"Id Employe");
    painter.drawText(7800,3300,"Heure Visite");

    painter.drawRect(100, 3700, 9200, 9000);

    QSqlQuery query;
    query.prepare("select * from RENDEZ_VOUS");
    query.exec();
    while (query.next())
    {
        painter.drawText(300, i, query.value(0).toString());
        painter.drawText(1450, i, query.value(1).toString());
        painter.drawText(3200, i, query.value(2).toString());
        painter.drawText(4750, i, query.value(3).toString());
        painter.drawText(5850, i, query.value(4).toString());
        painter.drawText(6700, i, query.value(5).toString());
        painter.drawText(8000, i, query.value(6).toString());

        i = i + 350;
    }

    QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
        QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}

void interface_rendezvous::on_btsupprimerrdv_clicked()
{
    rdv r ;
    int num = ui->combosupp->currentText().toInt();
    bool test = r.supprimer(num);
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

void interface_rendezvous::on_bttrierrdv_clicked()
{
    QString a=ui->trier->currentText();
    ui->tableView->setModel(Etmp.trid(a));


}



void interface_rendezvous::on_linerecherche_cursorPositionChanged(int arg1, int arg2)
{
    ui->tableView->setModel(Etmp.afficherecherche(ui->linerecherche->text()));


        if(ui->linerecherche->text()=="")
        {
            ui->tableView->setModel(Etmp.afficher_rdv());//refresh
        }
}




void interface_rendezvous::on_btvaliderrdv_clicked()
{
    rdv r;


    int id=ui->idcm->currentText().toInt();
    int matricule=ui->matriculem->currentText().toInt();
    QString date_visite=ui->datem->date().toString("dd/MM/yyyy");
    QString heure_visite=ui->timem->time().toString("hh:mm");
    int num_visite=ui->numvm->currentText().toInt();
    QString adresse_visite=ui->adressevm->currentText();
    int etat=ui->etatm->currentText().toInt();


     bool test = Etmp.modifier(id,matricule,date_visite,heure_visite,adresse_visite,num_visite,etat);


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

void interface_rendezvous::on_numvm_currentIndexChanged(int index)
{

    QSqlQuery query;
    int numero_visite = ui->numvm->currentText().toInt();
    query = Etmp.trouver_num_visite(numero_visite);
    QString item3;

    QStringList list_id;
    QStringList list_matricule;
    QStringList list_date_visite;
    QStringList list_heure_visite;
    QStringList list_num_visite;
    QStringList list_adresse_visite;
    QStringList list_etat;




    while(query.next()){
        list_num_visite.append(query.value(0).toString());
        list_date_visite.append(query.value(1).toString());
        list_adresse_visite.append(query.value(2).toString());
        list_matricule.append(query.value(3).toString());
        list_etat.append(query.value(4).toString());
        list_id.append(query.value(5).toString());
        list_heure_visite.append(query.value(6).toString());


    }

    foreach(QString item, list_id)
    {
           qDebug() << "List id = " << item;
           ui->idcm->setCurrentText(item);

    }
    foreach(QString item, list_matricule)
    {
           qDebug() << "List matricule = " << item;

           ui->matriculem->setCurrentText(item);
    }
    foreach(QString item, list_date_visite)
    {
        qDebug() << "List date_visite = " << item;
        QDate date = QDate::fromString(item, "dd/MM/yyyy");
        ui->datem->setDate(date);
        ui->datem->setDisplayFormat("dd/MM/yyyy");
    }
    foreach(QString item, list_heure_visite)
    {
        qDebug() << "List heure_visite = " << item;
        QTime time = QTime::fromString(item, "hh:mm");
        ui->timem->setTime(time);
        ui->timem->setDisplayFormat("hh:mm");
    }
    foreach(QString item, list_adresse_visite)
    {
           qDebug() << "List adresse_visite = " << item;

           ui->adressevm->setCurrentText(item);
    }
    foreach(QString item, list_etat)
    {
           qDebug() << "List etat = " << item;

           ui->etatm->setCurrentText(item);
    }


}
void interface_rendezvous::statistique1()
{

    QPieSeries *series=new QPieSeries();
    QStringList l=Etmp.listAdresse_visite();

    for (int i = 0; i < l.size(); ++i){

        series->append(l[i] ,Etmp.calculAdresse_visite(l[i]));
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

    ui->stat144->setLayout(mainLayout);
    ui->stat144->layout()->update();


}
