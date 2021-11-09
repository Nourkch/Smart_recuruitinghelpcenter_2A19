#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include "QDate"
#include <QtGui>
#include <QMessageBox>
#include <QString>
employe EMP;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setModel(EMP.afficher());

}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{
    int Id=ui->id->text().toInt();
    QString Nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    int CIN=ui->CIN->text().toInt();
    QString Sexe=ui->sexe->currentText();
    QString departement=ui->departement->currentText();
    QDate Bdate=ui->dateEdit_3->date();
    int TEL=ui->TELephone->text().toInt();
    employe e(Id,CIN,Nom,prenom,TEL,Bdate,Sexe,departement);
    bool ajout = e.ajouter();
       if(ajout)
       {
           QMessageBox::information(nullptr, QObject::tr("ajout"),
                       QObject::tr("Visiteur ajouté.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
           ui->tableView_2->setModel(EMP.afficher());

   }
       else
           QMessageBox::critical(nullptr, QObject::tr("ajout"),
                       QObject::tr("problème d'ajout.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);


   }


void MainWindow::on_pushButton_9_clicked()//supp button
{
 int Id=ui->id->text().toInt();
 bool test=EMP.supprimer(Id);//appel de la methode supp()
        if (test)
        {
        QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("Suppression effectuée\n"
                            "Click Cancel non to exit.") , QMessageBox :: Cancel);
       ui->tableView_2->setModel((EMP.afficher()));//refrerch
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                  QObject::tr("Suppression non effectuée.\n"
                                              "Click Cancel to exit."),QMessageBox::Cancel);
        ui->tableView_2->setModel((EMP.afficher()));


    }



void MainWindow::on_pushButton_5_clicked()
{
    int Id=ui->id->text().toInt();
    QString Nom=ui->nom->text();
    QString prenom=ui->prenom->text();
       employe(Id ,Nom,prenom);
       bool test=e.modifier(id);//appel a la methode modifier
       if (test)
       {
       QMessageBox::information(nullptr,QObject::tr("OK"),
               QObject::tr("Modification effectuée\n"
                           "Click Cancel non to exit.") , QMessageBox :: Cancel);

       ui->tableView_2->setModel((EMP.afficher()));


       }
       else
           QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                 QObject::tr("Modification non effectuée.\n"
                                             "Click Cancel to exit."),QMessageBox::Cancel);
       ui->tableView_2->setModel((EMP.afficher()));
}

