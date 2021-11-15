#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QRegExpValidator>
#include<QPrinter>
#include <QPainter>
#include <QFileDialog>
#include "commentaires.h"
#include <QDesktopServices>
#include <QUrl>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    QPixmap bkngd("C:/Users/Raider/Desktop/MY_PROJECT/Candidats_vf/resources/back.jpg");
    bkngd=bkngd.scaled(this->size(),Qt::IgnoreAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Background,bkngd);
    this->setPalette(palette);

      ui->setupUi(this);












      mSystemTrayIcon = new QSystemTrayIcon(this);
      mSystemTrayIcon->setIcon(QIcon("C:/Users/Raider/Desktop/MY_PROJECT/Candidats_vf/resources/background_vf.png")); // app icon
      mSystemTrayIcon->setVisible(true);

   //  QPixmap background("C:/Users/Raider/Desktop/MY_PROJECT/Candidats_vf/resources/background_vf.png");  //pic in a label
    // ui->label_background->setPixmap(background); 


/*  Table view not working (without button)

    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select * from CANDIDAT ");  //  * : everything
    q.exec();
    modal->setQuery(q);
    ui->tabCandidat->setModel(modal);
*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_valider_clicked()
{

    QString prenom = ui->lineEdit_prenom->text();
    QString nom=ui->lineEdit_nom->text();

    QDate date_naissance=ui->date_naissance->date();

    QString rue=ui->lineEdit_rue->text();
    int codepostal=ui->lineEdit_code_postal->text().toInt();
    int cin = ui->lineEdit_cin->text().toInt();

    QString sexe=ui->comboBox_sexe->currentText();

    QString email=ui->lineEdit_email->text();

  QString ville = ui->comboBox_ville->currentText();

 Candidatss c (cin,nom,prenom,email,sexe,rue,codepostal,date_naissance,ville);

 bool index ;

 index = c.ajouter_candidat();
mSystemTrayIcon->showMessage(tr("notification"),tr("ajout avec succes"));

  if (index==true)
     {

      QMessageBox::information(nullptr, QObject::tr("Ajouter un candidat"),
                  QObject::tr("Candidat ajouté avec succès.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

      ui->stackedWidget->setCurrentIndex(0);

}
}

void MainWindow::on_bouton_ajouter_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_bouton_supprimer_clicked()
{
      ui->stackedWidget->setCurrentIndex(2);
      QSqlQueryModel * modal = new QSqlQueryModel ();
      QSqlQuery q;
      q.prepare("select ID_CANDIDAT from CANDIDAT ");
      q.exec();
      modal->setQuery(q);
      ui->comboBox_id_supprimer->setModel(modal);
}

void MainWindow::on_pushButton_valider_supprimer_clicked()
{

  QMessageBox::StandardButton reply;

   reply = QMessageBox::question(this, "Supprimer un candidat ", "Etes-vous sur de la suppression?",
                                 QMessageBox::Yes|QMessageBox::No);

   if (reply == QMessageBox::Yes) {
     qDebug() << "Yes was clicked";

     int id = ui->comboBox_id_supprimer->currentText().toInt();

   bool test=tabCandidat.supprimer_candidat(id); //instatiation de la classe candidat
         mSystemTrayIcon->showMessage(tr("notification"),tr("suppression faite avec succes"));

   if (test)
   {
       QMessageBox::information(nullptr, QObject::tr("Supprimer un candidat"),
                   QObject::tr("Candidat supprimé avec succès .\n"
                               "Click Ok to exit."), QMessageBox::Ok);

       ui->stackedWidget->setCurrentIndex(0);

     }

}
}

void MainWindow::on_pushButton_annuler_supprimer_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}

////////////////////////

void MainWindow::on_pushButton_annuler_clicked() // annuler ajout
{
     ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_bouton_modifier_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select ID_CANDIDAT from CANDIDAT ");  // taabilek combobox bel IDs
    q.exec();
    modal->setQuery(q);
    ui->comboBox_modif_id->setModel(modal);
}

// valider la modification

void MainWindow::on_pushButton_modif_valider_clicked()
{

    int id=ui->comboBox_modif_id->currentText().toInt();

     QString nom = ui->lineEdit_modif_nom->text();

     QString prenom = ui->lineEdit_modif_prenom->text();

     QDate date_naissance=ui->dateNaissance_modif->date();

     QString rue=ui->lineEdit_modif_rue->text();

     int codepostal=ui->lineEdit_modif_codePostal->text().toInt();

     int cin = ui->lineEdit_modif_cin->text().toInt();

     QString sexe=ui->comboBox_modif_genre->currentText();

     QString email=ui->lineEdit_modif_email->text();

   QString ville = ui->comboBox_modif_ville->currentText();


      Candidatss c (id,cin,nom,prenom,email,sexe,rue,codepostal,date_naissance,ville);

            QMessageBox::StandardButton reply;

             reply = QMessageBox::question(this, "CANDIDAT ", "modifier?",
                                           QMessageBox::Yes|QMessageBox::No);

 if (reply == QMessageBox::Yes)
             {

            bool test=c.modifier_candidat();
             mSystemTrayIcon->showMessage(tr("notification"),tr("modification faite avec succes"));

            qDebug()<<id;

            if (test)
            {

                QMessageBox::information(nullptr, QObject::tr("Modifier un candidat"),
                            QObject::tr("Candidat modifié avec succès.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

                ui->stackedWidget->setCurrentIndex(0);

            }

             }

}

// annuler la modification

void MainWindow::on_pushButton_modif_annuler_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_bouton_afficher_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select * from CANDIDAT ");  //  * : everything
    q.exec();
    modal->setQuery(q);
    ui->tabCandidat->setModel(modal);

    mSystemTrayIcon->showMessage(tr("notification"),tr("affichage fait avec succes")); // notification sys // zid l cruds lokhrin

}

void MainWindow::on_triASC_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select * from CANDIDAT ORDER BY prenom ASC ");  //  * : everything
    q.exec();
    modal->setQuery(q);
    ui->tabCandidat->setModel(modal);
}

void MainWindow::on_triDEC_clicked()
{

    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select * from CANDIDAT ORDER BY prenom DESC ");  //  * : everything
    q.exec();
    modal->setQuery(q);
    ui->tabCandidat->setModel(modal);

}

// AJOUT : controle de saisie

void MainWindow::on_lineEdit_nom_cursorPositionChanged(int arg1, int arg2)  //old&new pos
{

    QRegExp rx ("^[A-Z][a-z]+(([',. -][a-zA-Z ])?[a-zA-Z]*)*$");

       QRegExpValidator *validnom = new QRegExpValidator(rx,this);
       ui->lineEdit_nom->setValidator(validnom);

}

void MainWindow::on_lineEdit_prenom_cursorPositionChanged(int arg1, int arg2)
{

    QRegExp rx ("^[A-Z][a-z]+(([',. -][a-zA-Z ])?[a-zA-Z]*)*$");

       QRegExpValidator *validprenom = new QRegExpValidator(rx,this);
       ui->lineEdit_prenom->setValidator(validprenom);

}

void MainWindow::on_lineEdit_cin_cursorPositionChanged(int arg1, int arg2)
{
    QRegExp rx ("^[0-9]{8}$");
    QRegExpValidator *validcin = new QRegExpValidator(rx,this);
    ui->lineEdit_cin->setValidator(validcin);

}

void MainWindow::on_lineEdit_email_cursorPositionChanged(int arg1, int arg2)
{
    QRegExp rx ("^[\\w\\-_.]+[@][A-Za-z]+\\.[a-z]{2,3}$");
    QRegExpValidator *validemail = new QRegExpValidator(rx,this);
    ui->lineEdit_email->setValidator(validemail);
}

void MainWindow::on_lineEdit_code_postal_cursorPositionChanged(int arg1, int arg2)
{
    QRegExp rx ("^[0-9]{4}$");
    QRegExpValidator *valideCodePostal = new QRegExpValidator(rx,this);
    ui->lineEdit_code_postal->setValidator(valideCodePostal);
}

void MainWindow::on_lineEdit_rue_cursorPositionChanged(int arg1, int arg2)
{
    QRegExp rx ("^[A-Za-z\\'-_.\\s]*$");
    QRegExpValidator *validrue = new QRegExpValidator(rx,this);
    ui->lineEdit_rue->setValidator(validrue);
}

///////////////////////////////////////////////////////////////////////////////////



// Modifier : controle de saisie


void MainWindow::on_lineEdit_modif_nom_cursorPositionChanged(int arg1, int arg2)
{
    QRegExp rx ("^[A-Z][a-z]+(([',. -][a-zA-Z ])?[a-zA-Z]*)*$");

       QRegExpValidator *validnom = new QRegExpValidator(rx,this);
       ui->lineEdit_modif_nom->setValidator(validnom);
}



void MainWindow::on_lineEdit_modif_prenom_cursorPositionChanged(int arg1, int arg2)
{
    QRegExp rx ("^[A-Z][a-z]+(([',. -][a-zA-Z ])?[a-zA-Z]*)*$");

       QRegExpValidator *validprenom = new QRegExpValidator(rx,this);
       ui->lineEdit_modif_prenom->setValidator(validprenom);
}



void MainWindow::on_lineEdit_modif_cin_cursorPositionChanged(int arg1, int arg2)
{
    QRegExp rx ("^[0-9]{8}$");

       QRegExpValidator *validcin = new QRegExpValidator(rx,this);
       ui->lineEdit_modif_cin->setValidator(validcin);
}



void MainWindow::on_lineEdit_modif_email_cursorPositionChanged(int arg1, int arg2)
{
    QRegExp rx ("^[\\w\\-_.]+[@][A-Za-z]+\\.[a-z]{2,3}$");
    QRegExpValidator *validemail = new QRegExpValidator(rx,this);
    ui->lineEdit_modif_email->setValidator(validemail);
}



void MainWindow::on_lineEdit_modif_rue_cursorPositionChanged(int arg1, int arg2)
{

    QRegExp rx ("^[A-Za-z\\'-_.\\s]*$");
    QRegExpValidator *validrue = new QRegExpValidator(rx,this);
    ui->lineEdit_modif_rue->setValidator(validrue);
}


void MainWindow::on_lineEdit_modif_codePostal_cursorPositionChanged(int arg1, int arg2)
{
    QRegExp rx ("^[0-9]{4}$");
    QRegExpValidator *valideCodePostal = new QRegExpValidator(rx,this);
    ui->lineEdit_modif_codePostal->setValidator(valideCodePostal);
}





void MainWindow::on_bouton_recherche_clicked()
{


    QString chercher = ui->lineEdit_recherche_texte->text();

   QString prenom;

              if((chercher !=  ""))
              {
                  QSqlQuery q;
                  QSqlQueryModel *modal=new QSqlQueryModel();

                  if(chercher != "")
                  {
                  q.prepare("select * from CANDIDAT where prenom like '%"+chercher+"%' ");
                  q.bindValue(":prenom",chercher);
                  q.exec();
                  modal->setQuery(q);

                  ui->tabCandidat->setModel(modal);

              }
              else
              {
                  QMessageBox::warning(this,"Erreur", "recherche invalide ");
              }
}
}


void MainWindow::on_pushButton_pdf_clicked()
{

    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    QString exporter = "C:/Users/Raider/Desktop/MY_PROJECT/Candidats_vf/PDF" ;
    printer.setOutputFileName(exporter+"CANDIDAT_liste.pdf");
    QPainter painter;
    painter.begin(&printer);

    QFont font;
    QSqlQuery query;
    QString NOM,PRENOM,ID_CANDIDAT,CIN,ADRESSEMAIL,SEXE,RUE,CODEPOSTAL,VILLE,DATE_NAISSANCE;



        int i=0,ligne1=250,ligne2=300,ligne3=350,ligne4=400,ligne5=450,ligne6=560,ligne7=490,ligne8=510, ligne9=530,ligne10=550;
        query.prepare("select * from CANDIDAT");
        query.exec();
        if (query.exec())
        {
            while (query.next())
            {
                ID_CANDIDAT=query.value(0).toString();
                CIN=query.value(1).toString();
                CODEPOSTAL=query.value(2).toString();

                i++;
                if(i>=2)
                {
                ligne1+=250;
                ligne2+=250;
                ligne3+=250;
                ligne4+=250;
                ligne5+=250;
                ligne6+=250;
                ligne7+=250;
                ligne8+=250;
                ligne9+=250;
                ligne10+=250;


               }
                qDebug()<< i ;

            font.setPixelSize(50);
            painter.setFont(font);
            painter.setPen(Qt::red);
            painter.drawText(350,150,"Candidats");

            // NOM,PRENOM,ID_CANDIDAT,CIN,ADRESSEMAIL,SEXE,RUE,CODEPOSTAL,VILLE,DATE_NAISSANCE

            font.setPixelSize(35);
            painter.setFont(font);
            painter.setPen(Qt::blue);
            painter.drawText(20,ligne1,"NOM: ");
            painter.drawText(20,ligne2,"PRENOM: ");
            painter.drawText(20,ligne3,"CIN:");
            painter.drawText(20,ligne4,"DATE_NAISSANCE:");
            painter.drawText(20,ligne5,"ID_CANDIDAT:");
            painter.drawText(20,ligne6,"SEXE:");
            painter.drawText(20,ligne7,"RUE:");
            painter.drawText(20,ligne8,"VILLE:");
            painter.drawText(20,ligne9,"CODEPOSTAL:");
            painter.drawText(20,ligne10,"ADRESSEMAIL:");


            font.setPixelSize(22);
            painter.setFont(font);
            painter.setPen(Qt::black);
            painter.drawText(250,ligne1,NOM);
            painter.drawText(250,ligne2,PRENOM);
            painter.drawText(250,ligne3,CIN);
            painter.drawText(250,ligne4,DATE_NAISSANCE);
            painter.drawText(550,ligne5,SEXE);
            painter.drawText(350,ligne6,RUE);
            painter.drawText(350,ligne7,VILLE);
            painter.drawText(350,ligne8,CODEPOSTAL);
            painter.drawText(350,ligne9,ADRESSEMAIL);

            painter.drawText(0,ligne10,"--------------------------------------------------------------------------------------------------");

            }



    }


    painter.end();
    qDebug()<<"le pdf a ete cree";
    QMessageBox::information(this,"PDF cree","Ce PDF a ete cree Dans Desktop Sous le Nom CANDIDAT_liste.pdf");

}


void MainWindow::on_pushButton_excel_clicked()
{
    QTableView *table;
    table = ui->tabCandidat;

    QString filters("CSV files (*.csv);;All files (*.*)"); // lanci csv extension ta excel
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", "C:/Users/Raider/Desktop/MY_PROJECT/Candidats_vf",
                       filters, &defaultFilter); // chemin
    QFile file(fileName);

    QAbstractItemModel *model =  table->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream data(&file); //?
        QStringList strList;
        for (int i = 0; i < model->columnCount(); i++) {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\""); // hot fihe
            else
                strList.append("");
        }
        data << strList.join(";") << "\n"; // lasaq l headers

        // yemshi aal lignes
        for (int i = 0; i < model->rowCount(); i++) {
            strList.clear(); // ynahi l headers besh yetaamloush f les lignes
            for (int j = 0; j < model->columnCount(); j++) {

                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append("\"" + model->data(model->index(i, j)).toString() + "\""); // think of it as matrice
                else
                    strList.append("");
            }
            data << strList.join(";") + "\n";
        }
        file.close();
        QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
    }
}

void MainWindow::on_pushButton_google_clicked()
{
    QString link = "http://www.google.com";
    QDesktopServices::openUrl(QUrl(link));

}

void MainWindow::on_pushButton_stat_clicked()
{
    // Assign names to the set of bars used
            QBarSet *set010 = new QBarSet("id_candidat");

            QSqlQuery q;
                          q.prepare("select id_candidat from candidat order by id_candidat desc ");
                          if(q.exec())
                          {
                                         while (q.next())
                                         {
                                             int a=q.value(0).toInt();
                                           *set010 << a ;
                                         }
}
            QBarSeries *series10 = new QBarSeries();

            // 2. Stacked bar chart
            // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
            series10->append(set010);


            // Used to define the bar chart to display, title
            // legend,
            QChart *chart10 = new QChart();

            // Add the chart
            chart10->addSeries(series10);

            // Set title
            chart10->setTitle("id du candidat en fonction de leurs noms et prenoms ");

            // Define starting animation
            // NoAnimation, GridAxisAnimations, SeriesAnimations
            chart10->setAnimationOptions(QChart::AllAnimations);

            // Holds the category titles
            QStringList categories10;
            //QSqlQuery q;
                          q.prepare("select NOM,PRENOM from CANDIDAT order by ID_CANDIDAT  ");
                          if(q.exec())
                        {
                            while (q.next())
                            {
                            QString a=q.value(0).toString() ;
                             categories10 << a ;
                            }
                        }
            // Adds categories to the axes
            QBarCategoryAxis *axis = new QBarCategoryAxis();
            axis->append(categories10);
            chart10->createDefaultAxes();

            // 1. Bar chart
            chart10->setAxisX(axis, series10);

            // 2. Stacked Bar chart
            // chart->setAxisY(axis, series);

            // Define where the legend is displayed
            chart10->legend()->setVisible(true);
            chart10->legend()->setAlignment(Qt::AlignBottom);

            // Used to display the chart
            QChartView *chartView10= new QChartView(chart10);
            chartView10->setRenderHint(QPainter::Antialiasing);

            // Used to change the palette
            QPalette pal = qApp->palette();

            // Change the color around the chart widget and text
            pal.setColor(QPalette::Window, QRgb(0xffffff));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));

            // Apply palette changes to the application
            qApp->setPalette(pal);

chartView10->setParent(ui->horizontalFrame);
ui->stackedWidget->setCurrentIndex(4);

}
