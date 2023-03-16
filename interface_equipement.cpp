#include "interface_equipement.h"
#include "ui_interface_equipement.h"

#include "equipement.h"
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
#include<QDialog>





interface_equipement::interface_equipement(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interface_equipement)
{
    ui->setupUi(this);
    this->setWindowTitle("Gestion Des Equipements");

    Equipement E;
    QSqlQueryModel * TV;
    TV = E.afficher();
    ui->tableViewe->setModel(TV);
    ui->comboBoxox->setModel(E.remplircombo());


}

interface_equipement::~interface_equipement()
{
    delete ui;
}
void interface_equipement::refresh()
{
   ui->tableViewe->setModel(E.afficher());
    // ui->tableequipement->setModel(E.afficher());
   // ui->table_equipement->setModel(E.afficher());
    //ui->idmod->setModel(E.remplircombo());
    ui->comboBoxox->setModel(E.remplircombo());
    //ui->nomcal->setModel(E.remplircomboCalcul());

}

void interface_equipement::on_ajouter_clicked()
{
   /* QDateTime now = QDateTime::currentDateTime();
        if (ui->numv->text().isEmpty()||ui->timeEdit->time().hour()<9||ui->timeEdit->time().hour()>18||!ui->numv->text().contains(QRegExp("^[0-9]+$"))||ui->dateEdit->date()<now.date())
        {
            QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                                  QObject::tr("ajout non effectué. Service fermé ou numéro incorrect ou date invalid\n"
                                                              "Click Cancel to exit."),QMessageBox::Cancel);
        }*/






    int id_equipement=ui->idaj->text().toInt();
            QString nom_centre=ui->nomcaj->text();
            QString nom_equipement=ui->nomeaj->text();
            QString date_intervention=ui->date->text();
            int etat_equipement=ui->etataj->text().toInt();
             Equipement E(id_equipement, nom_centre, nom_equipement, date_intervention, etat_equipement);
            bool test=E.ajouter();

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
}


void interface_equipement::on_supprimer_clicked()
{
    QMessageBox::StandardButton reply =QMessageBox::question(this,
                              "Supprimer","Voulez-vous vraiment supprimer ?",
                              QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            int aux = ui->comboBoxox->currentText().toInt();
            bool test=E.supprimer(aux);
            if(test)
            {
                QMessageBox::information(nullptr, QObject::tr("ok"),
                            QObject::tr("Supprimer effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                //refresh combobox + tableau
                refresh();

            }
            else
            {
                QMessageBox::critical(this, QObject::tr("Supprimer un client"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }

        }
}





/*void interface_equipement::on_idsupp_currentIndexChanged(int)
{
    Equipement E;
    QSqlQuery query;
    int id_equipement = ui->idsupp->currentText().toInt();
    query = E.trouver_equipement(id_equipement);
    qDebug()<<id_equipement <<"haw el donnee el oulaa"<<endl;


}*/

void interface_equipement::on_lineEditchercher_cursorPositionChanged(int arg1, int arg2)
{
    ui->tableViewe->setModel(E.chercher_Equipement(ui->lineEditchercher->text()));


        if(ui->lineEditchercher->text()=="")
        {
            ui->tableViewe->setModel(E.afficher());//refresh
        }

}

/*void interface_equipement::on_idsupp_currentIndexChanged(const QString &arg1)
{

}*/

void interface_equipement::on_comboBoxox_currentIndexChanged(int index)
{

}

void interface_equipement::on_modifier_clicked()
{
    Equipement E;

    QString id_equipement= ui->idaj->text();
    QString nom_centre=ui->nomcaj->text();
    QString nom_equipement=ui->nomeaj->text();

    QString date_itervention=ui->date->text();
    QString etat_equipement= ui->etataj->text();


     bool test = E.modifier(id_equipement,nom_centre,nom_equipement,date_itervention,etat_equipement);


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
void interface_equipement::statistiqueequipement()
{

    QPieSeries *series=new QPieSeries();
    QStringList l=E.listequipement();
QString var;
    for (int i = 0; i < l.size(); ++i){

        //QString etat_equipement_string=QString::number(E.calculetat_equipement(l[i]));
        //series->append(l[i] ,var = QString::number(E.calculetat_equipement(l[i])));
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

    ui->stat4->setLayout(mainLayout);
    ui->stat4->layout()->update();


}

