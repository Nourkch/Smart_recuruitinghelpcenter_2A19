#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QRegExpValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    /*QPixmap bkngd("C:/Users/Raider/Desktop/MY_PROJECT/Candidats_vf/resources/background_vf.png");
    bkngd=bkngd.scaled(this->size(),Qt::IgnoreAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Background,bkngd);
    this->setPalette(palette); */ 

      ui->setupUi(this);


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
