#ifndef INTERFACE_CLIENT_H
#define INTERFACE_CLIENT_H

#include <QMainWindow>
#include "clients.h"

namespace Ui {
class interface_Client;
}

class interface_Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit interface_Client(QWidget *parent = nullptr);
    ~interface_Client();

private slots:

  void on_ajouter7_clicked();



  void on_modifier7_clicked();

  void refresh();


  //void on_recherche7_cursorPositionChanged(int arg7,int arg8);

  void on_CINmod_currentIndexChanged(int index2);



  void on_supprimer_7_clicked();

private:
    Ui::interface_Client *ui;
    Clients c;
    QByteArray data;
    Clients Etmp;

};

#endif // INTERFACE_CLIENT_H
