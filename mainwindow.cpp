#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formation.h"
#include "cours.h"
#include "examen.h"
#include "certificat.h"
#include "calendrier.h"
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QDateTime>
#include <QPainter>
#include <QPdfWriter>
 #include<QUrl>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

  ui->setupUi(this);
  ui->tab_formation->setModel(f.afficher());
  ui->tab_calendrier->setModel(ca.afficher());
  ui->tab_cours->setModel(c.afficher());
  ui->tab_examen->setModel(e.afficher());
  ui->tab_certificat->setModel(cer.afficher());
  //PARTIE ARDUINO
      int ret=A.connect_arduino(); // lancer la connexion à arduino
      switch(ret)
      {
      case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
          break;
      case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
         break;
      case(-1):qDebug() << "arduino is not available";
      }
       QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(on_pb_arduino_clicked())); // permet de lancer
       //le slot update_label suite à la reception du signal readyRead (reception des données).

   }

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pb_ajouter_clicked()
{
    int idf=ui->le_identifiant->text().toInt();
       QString type=ui->le_type->text();
       QString periode=ui->la_periode->text();

       formation f(idf,type,periode);
        bool test=f.ajouter();
        if (test)
        {
            erreur->setMedia(QUrl("C:/Users/Dhia Jmour/Desktop/gestion_formation_nv/gestion_formation/sounds/faj.mp3")) ;
            erreur->setVolume(100) ;
            erreur->play() ;
          QMessageBox::information(nullptr,QObject::tr("Ajout avec succes"),QObject::tr("SUCCES"),QMessageBox::Ok) ;
        ui->tab_formation->setModel(f.afficher());
        }else
            {
            erreur->setMedia(QUrl("C:/Users/Dhia Jmour/Desktop/gestion_formation_nv/gestion_formation/sounds/erreur.mp3")) ;
            erreur->setVolume(100) ;
            erreur->play() ;
            QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                        QObject::tr("Echec d'ajout.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
            }
}

void MainWindow::on_pb_supp_clicked()
{
    formation f1; f1.setidf(ui->le_id_supp->text().toInt());
        bool test=f1.supprimer(f1.getidf());
        if (test)
        {
            erreur->setMedia(QUrl("C:/Users/Dhia Jmour/Desktop/gestion_formation_nv/gestion_formation/sounds/fsupp.mp3")) ;
            erreur->setVolume(100) ;
            erreur->play() ;
          QMessageBox::information(nullptr,QObject::tr("Suppression avec succes"),QObject::tr("SUCCES"),QMessageBox::Ok) ;
        }else
            {
            erreur->setMedia(QUrl("C:/Users/Dhia Jmour/Desktop/gestion_formation_nv/gestion_formation/sounds/erreur.mp3")) ;
            erreur->setVolume(100) ;
            erreur->play() ;
            QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                        QObject::tr("Echec de suppression.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
             ui->tab_formation->setModel(f.afficher());
             }

}

void MainWindow::on_pb_moddifier_clicked()
{
    int idf=ui->le_identifiant->text().toInt() ;
        QString type=ui->le_type->text() ;
        QString periode=ui->la_periode->text();

                formation f (idf,type,periode);
                bool test=f.modifier(idf);
                if(test)
                {
                    erreur->setMedia(QUrl("C:/Users/Dhia Jmour/Desktop/gestion_formation_nv/gestion_formation/sounds/fmodif.mp3")) ;
                    erreur->setVolume(100) ;
                    erreur->play() ;
                    ui->tab_formation->setModel(f.afficher());
                    QMessageBox::information(nullptr, QObject::tr("succes"),
                                QObject::tr("FORMATION modifié."), QMessageBox::Ok);
            }
                else
                {
                    erreur->setMedia(QUrl("C:/Users/Dhia Jmour/Desktop/gestion_formation_nv/gestion_formation/sounds/erreur.mp3")) ;
                    erreur->setVolume(100) ;
                    erreur->play() ;
                    QMessageBox::critical(nullptr, QObject::tr("erreur"),
                               QObject::tr("erreur de modification."), QMessageBox::Ok);
        }
}

void MainWindow::on_tab_formation_activated(const QModelIndex &index)
{
    QSqlQuery query ;
            QString val=ui->tab_formation->model()->data(index).toString();
            query.prepare("SELECT * from formation where idf=:idf ");

            query.bindValue(":idf",val);
            if(query.exec())
            {
                while(query.next())
                {
                    ui->le_identifiant->setText(query.value(0).toString());
                    ui->le_type->setText(query.value(1).toString());
                    ui->la_periode->setText(query.value(2).toString());


                }
            }
            else
            {
                    QMessageBox::critical(nullptr, QObject::tr("Transferer données"),
                                QObject::tr("Erreur !.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
            }
}



void MainWindow::on_pb_rechercher_clicked()
{
    int iden=ui->rechercher->text().toInt() ;
        ui->tab_formation->setModel(f.rechercher(iden)) ;
        QMessageBox::information(nullptr, QObject::tr("succes"),
                    QObject::tr(" affiche  dans le tableau !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_annuler_clicked()
{
              ui->le_identifiant->setText(0) ;
              ui->le_type->setText(0) ;
              ui->la_periode->setText(0) ;
              ui->rechercher->setText(0);
              ui->tab_formation->setModel(f.afficher());
  }

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index==1)
          {
              ui->tab_formation->setModel(f.sort_formation());
          }else
              ui->tab_formation->setModel(f.sort_formation());
}

void MainWindow::on_pb_ajouter_6_clicked()
{
    int ide=ui->le_ide_2->text().toInt();
            QDate date_exam=ui->le_date_exam->date();
           QString temps=ui->le_temps->text();


            calendrier ca (ide,date_exam,temps);

        bool test=ca.ajouter();
        if(test){
            QMessageBox::information(nullptr,QObject::tr("calendrier"),QObject::tr("calendrier ajouté\n" "click ok to exit"),QMessageBox::Ok);
            ui->le_ide_2->setText("");//bech ba3ed mankamel l ajout yarja3 a 0
            ui->tab_calendrier->setModel(ca.afficher());//actualisation


            QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                                     notifyIcon->show();
                                     notifyIcon->setIcon(QIcon("icone.png"));

                                     notifyIcon->showMessage("  projet2a19   ","calendrier Ajouté",QSystemTrayIcon::Information,15000);
                     QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);


        }
        else
        {
            erreur->setMedia(QUrl("C:/Users/Dhia Jmour/Desktop/gestion_formation_nv/gestion_formation/sounds/erreur.mp3")) ;
            erreur->setVolume(100) ;
            erreur->play() ;
            QMessageBox::critical(nullptr,QObject::tr("calendrier"),QObject::tr("Erreur!\n" "click ok to exit"),QMessageBox::Ok);
        }




        }


void MainWindow::on_pb_moddifier_4_clicked()
{
    int ide= ui->le_ide_2->text().toInt();
    QDate date_exam=ui->le_date_exam->date();
    QString temps=ui->le_temps->text();
                               calendrier ca (ide,date_exam,temps);
                               ui->le_ide_2->setText("");


                    bool test = ca.update(ide,date_exam,temps);


                    if(test)

                    {
                         ui->tab_calendrier->setModel(ca.afficher());
                         QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                                                  notifyIcon->show();
                                                  notifyIcon->setIcon(QIcon("icone.png"));

                                                  notifyIcon->showMessage("gestion formation  ","calendrier Modifier",QSystemTrayIcon::Information,15000);
                                  QMessageBox::information(nullptr, QObject::tr("OK"),
                                              QObject::tr("Modification effectué.\n"
                                                          "Click Cancel to exit."), QMessageBox::Cancel);
                        QMessageBox::information(nullptr, QObject::tr("update "),
                                    QObject::tr("examen modifie\n"
                    "Click Cancel to exit."), QMessageBox::Cancel);}

}

void MainWindow::on_pb_supp_6_clicked()
{
    calendrier c1;
        ca.setide(ui->le_ide_2->text().toInt());
            bool test=ca.supprimer(ca.getide());
            QMessageBox msgBox;
            if(test)
               { msgBox.setText("Suppression avec succes.");
                ui->tab_calendrier->setModel(ca.afficher());
                QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                                         notifyIcon->show();
                                         notifyIcon->setIcon(QIcon("icone.png"));

                                         notifyIcon->showMessage("gestion formationz   ","calendrier supprimer",QSystemTrayIcon::Information,15000);
                         QMessageBox::information(nullptr, QObject::tr("OK"),
                                     QObject::tr("suppression effectué.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);

        }
            else
                msgBox.setText("Echec de suppression");
            msgBox.exec();
}

void MainWindow::on_pb_ajouter_2_clicked()
{
    int idc=ui->le_identifiant_2->text().toInt();
       QString matiere=ui->la_matiere->text();
       QString temps=ui->le_temps_2->text();
       QString duree=ui->la_duree->text();


       cours c (idc,matiere,temps,duree);
        bool test=c.ajouter();
        if (test)
        {
            erreur->setMedia(QUrl("C:/Users/Dhia Jmour/Desktop/gestion_formation_nv/gestion_formation/sounds/caj.mp3")) ;
            erreur->setVolume(100) ;
            erreur->play() ;
          QMessageBox::information(nullptr,QObject::tr("Ajout avec succes"),QObject::tr("SUCCES"),QMessageBox::Ok) ;
        ui->tab_cours->setModel(c.afficher());
        }else
            {
            erreur->setMedia(QUrl("C:/Users/Dhia Jmour/Desktop/gestion_formation_nv/gestion_formation/sounds/erreur.mp3")) ;
            erreur->setVolume(100) ;
            erreur->play() ;
            QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                        QObject::tr("Echec d'ajout.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
            }
}




void MainWindow::on_pb_moddifier_2_clicked()
{
    int idc=ui->le_identifiant_2->text().toInt() ;
        QString matiere=ui->la_matiere->text() ;
        QString temps=ui->le_temps_2->text();
        QString duree=ui->la_duree->text();

                cours c (idc,matiere,temps,duree);
                bool test=c.modifier(idc);
                if(test)
                {
                    erreur->setMedia(QUrl("C:/Users/Dhia Jmour/Desktop/gestion_formation_nv/gestion_formation/sounds/cmod.mp3")) ;
                    erreur->setVolume(100) ;
                    erreur->play() ;
                    ui->tab_cours->setModel(c.afficher());
                    QMessageBox::information(nullptr, QObject::tr("succes"),
                                QObject::tr("COURS modifié."), QMessageBox::Ok);
            }
                else
                {
                    erreur->setMedia(QUrl("C:/Users/Dhia Jmour/Desktop/gestion_formation_nv/gestion_formation/sounds/erreur.mp3")) ;
                    erreur->setVolume(100) ;
                    erreur->play() ;
                    QMessageBox::critical(nullptr, QObject::tr("erreur"),
                               QObject::tr("erreur de modification."), QMessageBox::Ok);
        }
}

void MainWindow::on_pb_supp_3_clicked()
{
    cours c1; c1.setidc(ui->le_id_supp_2->text().toInt());
        bool test=c1.supprimer(c1.getidc());
        if (test)
        {
            erreur->setMedia(QUrl("C:/Users/Dhia Jmour/Desktop/gestion_formation_nv/gestion_formation/sounds/csupp.mp3")) ;
            erreur->setVolume(100) ;
            erreur->play() ;
          QMessageBox::information(nullptr,QObject::tr("Suppression avec succes"),QObject::tr("SUCCES"),QMessageBox::Ok) ;
        }
        else
        {

            QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                        QObject::tr("Echec de suppression.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_cours->setModel(c.afficher());
}
}

void MainWindow::on_pb_ajouter_3_clicked()
{
       int ide=ui->le_identifiant_3->text().toInt();
       QString matiere=ui->la_matiere_2->text();
       QString duree=ui->la_duree_2->text();
       QString note=ui->la_note->text();


       examen e (ide,matiere,duree,note);
        bool test=e.ajouter();
        if (test)
        {
          QMessageBox::information(nullptr,QObject::tr("Ajout avec succes"),QObject::tr("SUCCES"),QMessageBox::Ok) ;
        ui->tab_examen->setModel(e.afficher());
        }else
            erreur->setMedia(QUrl("C:/Users/Dhia Jmour/Desktop/gestion_formation_nv/gestion_formation/sounds/erreur.mp3")) ;
            erreur->setVolume(100) ;
            erreur->play() ;
            QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                        QObject::tr("Echec d'ajout.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_moddifier_3_clicked()
{
    int ide=ui->le_identifiant_3->text().toInt() ;
        QString matiere=ui->la_matiere_2->text() ;
        QString duree=ui->la_duree_2->text();
        QString note=ui->la_note->text();

                examen e (ide,matiere,duree,note);
                bool test=e.modifier(ide);
                if(test)
                {
                    ui->tab_examen->setModel(e.afficher());
                    QMessageBox::information(nullptr, QObject::tr("succes"),
                                QObject::tr("EXAMEN modifié."), QMessageBox::Ok);
            }
                else
                {
                    QMessageBox::critical(nullptr, QObject::tr("erreur"),
                               QObject::tr("erreur de modification."), QMessageBox::Ok);
        }
}

void MainWindow::on_pb_supp_4_clicked()
{
    examen e1; e1.setide(ui->le_id_supp_3->text().toInt());
        bool test=e1.supprimer(e1.getide());
        if (test)
        {
          QMessageBox::information(nullptr,QObject::tr("Suppression avec succes"),QObject::tr("SUCCES"),QMessageBox::Ok) ;
        }else

            QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                        QObject::tr("Echec de suppression.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_examen->setModel(e.afficher());
}

void MainWindow::on_pb_modifier_5_clicked()
{
    int idcertif=ui->le_identifiant_5->text().toInt() ;
        QString categorie=ui->la_categorie->text() ;
        QString cible=ui->le_cible->text();
        QString titre=ui->le_titre->text();

                certificat cer (idcertif,categorie,cible,titre);
                bool test=cer.modifier(idcertif);
                if(test)
                {
                    ui->tab_certificat->setModel(cer.afficher());
                    QMessageBox::information(nullptr, QObject::tr("succes"),
                                QObject::tr("CERTIFICAT modifié."), QMessageBox::Ok);
            }
                else
                {
                    QMessageBox::critical(nullptr, QObject::tr("erreur"),
                               QObject::tr("erreur de modification."), QMessageBox::Ok);
}
   }

void MainWindow::on_pb_supp_5_clicked()
{
    certificat ce1; ce1.setidcertif(ui->le_identifiant_5->text().toInt());
        bool test=ce1.supprimer(ce1.getidcertif());
        if (test)
        {
          QMessageBox::information(nullptr,QObject::tr("Suppression avec succes"),QObject::tr("SUCCES"),QMessageBox::Ok) ;
        }else

            QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                        QObject::tr("Echec de suppression.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_certificat->setModel(cer.afficher());
}


void MainWindow::on_pb_ajouter_5_clicked()
{
    int idcertif=ui->le_identifiant_5->text().toInt();
    QString categorie=ui->la_categorie->text();
    QString cible=ui->le_cible->text();
    QString titre=ui->le_titre->text();


    certificat cer (idcertif,categorie,cible,titre);
     bool test=cer.ajouter();
     if (test)
     {
       QMessageBox::information(nullptr,QObject::tr("Ajout avec succes"),QObject::tr("SUCCES"),QMessageBox::Ok) ;
     ui->tab_certificat->setModel(cer.afficher());
     }else
         erreur->setMedia(QUrl("C:/Users/Dhia Jmour/Desktop/gestion_formation_nv/gestion_formation/sounds/erreur.mp3")) ;
         erreur->setVolume(100) ;
         erreur->play() ;
         QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                     QObject::tr("Echec d'ajout.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_pdf_clicked()
{
    QDateTime datecreation = date.currentDateTime();
    QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;

       QPdfWriter pdf("C:/PDFformation.pdf");
       QPainter painter(&pdf);
      int i = 4000;


           painter.setPen(Qt::blue);
           painter.setFont(QFont("Arial", 30));
           painter.drawText(1100,1200,"Liste Des Formation");
           painter.setPen(Qt::black);
           painter.setFont(QFont("Arial", 15));
           painter.drawText(1100,2000,afficheDC);
           painter.drawRect(100,100,7300,2600);
           painter.drawRect(0,3000,9600,500);
           painter.setFont(QFont("Arial", 9));
           painter.drawText(200,3300,"ID Formation");
           painter.drawText(1300,3300,"Type Formation");
           painter.drawText(2100,3300,"Période Formation");


           QSqlQuery query;
           query.prepare("select * from FORMATION ");
           query.exec();
           while (query.next())
           {

               painter.drawText(200,i,query.value(0).toString());
               painter.drawText(1300,i,query.value(1).toString());
               painter.drawText(2200,i,query.value(2).toString());
               painter.drawText(3200,i,query.value(3).toString());
               painter.drawText(4500,i,query.value(4).toString());
               painter.drawText(7700,i,query.value(5).toString());

              i = i + 500;


           }
           int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);



               if (reponse == QMessageBox::Yes)
               {
                   service.openUrl(QUrl("C:/"));
                   painter.end();
               }
               if (reponse == QMessageBox::No)
               {
                    painter.end();
               }

}

void MainWindow::on_pb_ask_clicked()
{
    QString text = ui->le_pb_ask->text();
    if(text=="help")
    {
        erreur->setMedia(QUrl("C:/Users/Dhia Jmour/Desktop/gestion_formation_nv/gestion_formation/sounds/helpajout.mp3")) ;
        erreur->setVolume(100) ;
        erreur->play() ;
    }
        else if(text=="formation disponible")
    {
        erreur->setMedia(QUrl("C:/Users/Dhia Jmour/Desktop/gestion_formation_nv/gestion_formation/sounds/fordispo.mp3")) ;
        erreur->setVolume(100) ;
        erreur->play() ;
    }
        else if(text=="salut")
        {
            erreur->setMedia(QUrl("C:/Users/Dhia Jmour/Desktop/gestion_formation_nv/gestion_formation/sounds/salut.mp3")) ;
            erreur->setVolume(100) ;
            erreur->play() ;
        }
    else
    {
        erreur->setMedia(QUrl("C:/Users/Dhia Jmour/Desktop/gestion_formation_nv/gestion_formation/sounds/helpadmin.mp3")) ;
        erreur->setVolume(100) ;
        erreur->play() ;
    }
}

void MainWindow::on_pb_arduino_clicked()
{
    A.write_to_arduino("1");
}
