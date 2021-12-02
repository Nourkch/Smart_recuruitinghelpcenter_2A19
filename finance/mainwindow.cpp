#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QIntValidator>
#include <QApplication>
#include <QMessageBox>
#include"finance.h"
#include<QPainter>
#include<QPdfWriter>
#include"notification.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //ajouter
    notification n ;
    int id=ui->id_lineEdit->text().toInt();
    int salaire=ui->salaire_lineEdit_4->text().toInt();
    int telephone=ui->tele_lineEdit_5->text().toInt();
    QString nom=ui->nom_lineEdit_2->text();
    QString prenom=ui->prenom_lineEdit_3->text();
    QString adress=ui->adress_lineEdit_6->text();

    finance f(nom,prenom,telephone,id,salaire,adress);
bool test=f.ajouter();
     if(test)
      {
       n.notification_ajoute();
         QMessageBox::information(nullptr, QObject::tr("ajout avec succes"),
                                    QObject::tr("ajout successful.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
      ui->tableView->setModel(f.afficher());

                }
                    else
                        QMessageBox::critical(nullptr, QObject::tr("Ajout errer"),
                                    QObject::tr("ajout failed.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_load_pushButton_4_clicked()
{
    //load
    QSqlQueryModel *model= new QSqlQueryModel();
            QSqlQuery   *query= new QSqlQuery();
            query->prepare("SELECT id from finace");
             query->exec();
             model->setQuery(*query);
             ui->comboBox->setModel(model);
}

void MainWindow::on_pushButton_2_clicked()
{
    //supprimer
  notification n ;
    finance f;
        f.setid(ui->comboBox->currentText().toInt());
        bool test;
        test=f.supprimer(f.getid());
        if(test)
         {
            n.notification_supprimer();

            QMessageBox::information(nullptr, QObject::tr("supp avec succes"),
                                       QObject::tr("sup successful.\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);

    ui->tableView->setModel(f.afficher());
                   }
                       else
                           QMessageBox::critical(nullptr, QObject::tr("sup errer"),
                                       QObject::tr("sup failed.\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pushButton_3_clicked()
{



      notification n ;
        int id=ui->id_lineEdit->text().toInt();
            QString nom=ui->nom_lineEdit_2->text();
            QString prenom=ui->prenom_lineEdit_3->text();
            QString adress=ui->adress_lineEdit_6->text();

            int telephone=ui->tele_lineEdit_5->text().toInt();

              int salaire=ui->salaire_lineEdit_4->text().toInt();


   finance f(nom,prenom,telephone,id,salaire,adress);

            bool test=f.modifier(f.getnom(),f.getprenom(),f.gettelephone(),f.getid(),f.getsalaire(),f.getadress());

            QMessageBox msgBox;

            if(test)
                {
                n.notification_modifier();

                    msgBox.setText("Modification avec succes.");
                    ui->tableView->setModel(f.afficher());
                }
            else
                msgBox.setText("Echec de Modification!!!!!!");
                msgBox.exec();
}

void MainWindow::on_trier_id_pt_clicked()
{
    //id
    finance f;
      ui->tableView->setModel(f.trier());
}

void MainWindow::on_trier_nom_clicked()
{
    finance f;
      ui->tableView->setModel(f.trier1());
}

void MainWindow::on_trier_prenom_clicked()
{
    finance f;
      ui->tableView->setModel(f.trier2());
}



void MainWindow::on_pt_rechercher_clicked()
{
    finance f;
    QString rech=ui->rech->text();
    if (rech=="")
     ui->tableView->setModel(f.afficher());
    else
        ui->tableView->setModel(f.rechercher(rech));
}

void MainWindow::on_pdf_pt_clicked()
{
    QPdfWriter pdf("C:\\Users\\Saif Manai\\Desktop\\yasmine\\finance\\Nouveau dossier\\finance.pdf");


   QPainter painter(&pdf);
   int i = 4000;
          painter.setPen(Qt::red);
          painter.setFont(QFont("Time New Roman", 25));
          painter.drawText(3000,1400,"finance");
          painter.setPen(Qt::black);
          painter.setFont(QFont("Time New Roman", 15));
          painter.drawRect(100,100,9400,2500);
          painter.drawRect(100,3000,9400,500);
          painter.setFont(QFont("Time New Roman", 10));
          painter.drawText(500,3300,"NOM");
          painter.drawText(1500,3300,"prenom");
          painter.drawText(2500,3300,"telephone");
          painter.drawText(3500,3300,"id");
          painter.drawText(4500,3300,"salaire");
          painter.drawText(5500,3300,"adress");
          painter.drawRect(100,3000,9400,9000);

          QSqlQuery query;
          query.prepare("select * from finace");
          query.exec();
          while (query.next())
          {
              painter.drawText(500,i,query.value(0).toString());
              painter.drawText(1500,i,query.value(1).toString());
              painter.drawText(2500,i,query.value(2).toString());
              painter.drawText(3500,i,query.value(3).toString());
              painter.drawText(4500,i,query.value(4).toString());
              painter.drawText(5500,i,query.value(5).toString());

             i = i + 350;
          }
          QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
          QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}

/*
void MainWindow::on_stat_pt_clicked()
{
    finance e;

        QBarSeries *series = new QBarSeries();
        for(int i=0;i<10;i++){
          QSqlQueryModel * modal1=e.afficher();
          float salaire =modal1->index(i,3).data().toFloat();
          QString nom=modal1->index(i,1).data().toString();
          QString prenom=modal1->index(i,2).data().toString();
          if(modal1->index(i,1).data().toString().length()){
          QBarSet *set0 = new QBarSet(nom+" "+prenom);
            *set0 << salaire;
            series->append(set0);
            series->setLabelsVisible(set0);
          }
         }
        QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("FINANCE");
            chart->setAnimationOptions(QChart::SeriesAnimations);
            QBarCategoryAxis *axis = new QBarCategoryAxis();
            chart->createDefaultAxes();
            chart->setAxisX(axis, series);
            QChartView *chartView = new QChartView(chart);
             chartView->setParent(ui->horizontalFrame);

    }

*/
