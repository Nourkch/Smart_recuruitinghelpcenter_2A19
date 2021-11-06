#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "partenaire.h"
#include <QtDebug>
#include <QString>
#include <QMessageBox>
#include <QIntValidator>
#include <qsqlquerymodel.h>
#include <QWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->table_partenaire->setModel(p.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_le_ajouter_clicked()
{
{
       int id=ui->le_id->text().toInt();
       QString nom=ui->le_nom->text();
       QString adresse=ui->le_adresse->text();
       QString mail=ui->le_mail->text();
       int numero=ui->le_numero->text().toInt();



       partenaire p(id,nom,mail,adresse,numero);
       bool test=p.ajouter();

   if (test)
   {
       ui->table_partenaire->setModel(p.afficher());

     //  QMessageBox::information(nullptr, QObject::tr("ok"),
                   //        QObject::tr("ajout effectue.\n"
                      //                 "Click Cancel to exit."), QMessageBox::Cancel);
}

}}

void MainWindow::on_le_supprimer_clicked()
{
  p.setid(ui->le_id_sup->text().toInt());

        bool test=p.supprimer(p.getid());
        if(test)
           {
            ui->table_partenaire->setModel(p.afficher());

                     QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("suppression effectué.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);


    }
        else

            QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                                QObject::tr("suppression non effectue.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);



}
void MainWindow::on_le_Modifier_clicked()
{
    ui->table_partenaire->setModel(p.afficher());
   int id=ui->le_id->text().toInt();
       QString nom=ui->le_nom->text();
       QString adresse=ui->le_adresse->text();
       QString mail=ui->le_mail->text();
        int numero=ui->le_numero->text().toInt();
       bool    test=p.update(id,nom,adresse,mail,numero);
       if (test)
             {
                     ui->table_partenaire->setModel(p.afficher());

                 QMessageBox::information(nullptr,QObject::tr("OK"),
                                      QObject::tr("modification établie"),
                                      QMessageBox::Ok);}
             else{
             QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                     QObject::tr("modification non établie"),
                                     QMessageBox::Cancel);
}
}
