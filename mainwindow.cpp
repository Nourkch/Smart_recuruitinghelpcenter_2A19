#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include "QDate"
#include <QtGui>
#include <QMessageBox>
#include <QString>
#include <QLabel>
#include <QRegularExpression>
#include "crudconge.h"
#include "pointage.h"

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

void MainWindow::SetOuputMessage(QString message ,bool state)
{
    if (!state)
        ui->label_SortieApplication->setStyleSheet("color: rgb(255, 0, 0);");
    else
        ui->label_SortieApplication->setStyleSheet("color: rgb(0, 180, 0);");

    ui->label_SortieApplication->setText(message);


}
void MainWindow::SetOuputMessageConge(QString message ,bool state)
{
    if (!state)
        ui->SortieApplicationConge->setStyleSheet("color: rgb(255, 0, 0);");
    else
        ui->SortieApplicationConge->setStyleSheet("color: rgb(0, 180, 0);");

    ui->SortieApplicationConge->setText(message);

}

void MainWindow::on_pushButton_supprmier_clicked()
{
    Employe EmployeAsupprimer;
    unsigned long long loginUtilisateur=ui->lineEdit_ID->text().toLongLong();
    if (EmployeAsupprimer.RechercherInstEmploye(loginUtilisateur))
    {

        if (EmployeAsupprimer.SupprimerEmploye())
        {
            EnClear(0);
            SetOuputMessage("L'employe a ete supprime avec succes ",true);
        }
        else
            SetOuputMessage("L'employe n'as pas ete supprime, Verifiez vos donnees et reessayez encore ",false);

    }

}
void MainWindow::EnClear(int choix){
    if (!choix)
    {
        ui->lineEdit_ID->clear();
    }
    ui->lineEdit_nom->clear();
    ui->lineEdit_prenom->clear();
    ui->lineEdit_adresse->clear();
    ui->lineEdit_CIN->clear();
    ui->comboBox_sexe->setCurrentIndex(-1);
    ui->comboBox_service->setCurrentIndex(-1);
    ui->dateEdit_dateNaissance->setDate(QDate::fromString("01/01/1800","dd/MM/yyyy"));
    ui->lineEdit_confirmermotdepasse->clear();
    ui->lineEdit_motdepasse->clear();
    ui->lineEdit_mailTravail->clear();
    ui->lineEdit_NSS->clear();
    ui->label_NomControl->clear();
    ui->label_PrenomControl->clear();
    ui->label_ServiceControl->clear();
    ui->label_NssControl->clear();
    ui->label_PasswordConfirmControl->clear();
    ui->label_PasswordControl->clear();
    ui->label_CinControl->clear();
    ui->label_AdresseControl->clear();
    ui->label_mailControl->clear();
    ui->label_IDControl->clear();
    ui->label_SexeControl->clear();
    ui->label_DateNaissanceControl->clear();

}
bool MainWindow::VerifNom()
{


    /*QRegExp("[^a-zA-Z\\d\\s]*/
    if (ui->lineEdit_nom->text().contains(QRegularExpression("[^a-zA-Z ]") ) || ui->lineEdit_nom->text().isEmpty())
    {
        ui->label_NomControl->setPixmap(PixFalseIcon);
        ui->label_NomControl->setToolTip( tr("Le nom de l'employe doit comporte seulement des lettres alphabetique !"));
        return false;
    }
    else
    {
        ui->label_NomControl->setPixmap(PixTrueIcon);
        return true;
    }

}

bool MainWindow::VerifPrenom()
{

    if (ui->lineEdit_prenom->text().contains(QRegularExpression("[^a-zA-Z ]")) || ui->lineEdit_prenom->text().isEmpty())
    {
        ui->label_PrenomControl->setPixmap(PixFalseIcon);
        return false;
    }
    else
    {
        ui->label_PrenomControl->setPixmap(PixTrueIcon);
        return true;
    }
}

bool MainWindow::VerifNSS()
{


    if (ui->lineEdit_NSS->text().contains(QRegularExpression("[^0-9]")) || ui->lineEdit_NSS->text().isEmpty())
    {
        ui->label_NssControl->setPixmap(PixFalseIcon);
        return false;
    }
    else
    {
        ui->label_NssControl->setPixmap(PixTrueIcon);
        return true;
    }


}



bool MainWindow::VerifCIN()
{


    if (ui->lineEdit_CIN->text().contains(QRegularExpression("[^0-9]")) || ui->lineEdit_CIN->text().isEmpty() || ui->lineEdit_CIN->text().length()!=8)
    {
        ui->label_CinControl->setPixmap(PixFalseIcon);
        return false;
    }
    else
    {
        ui->label_CinControl->setPixmap(PixTrueIcon);
        return true;
    }


}

bool MainWindow::VerifPassword()
{

    if (!ui->lineEdit_motdepasse->text().isEmpty() && !ui->lineEdit_confirmermotdepasse->text().isEmpty())
    {
        if (ui->lineEdit_motdepasse->text()==ui->lineEdit_confirmermotdepasse->text())
        {
            ui->label_PasswordConfirmControl->setPixmap(PixTrueIcon);

            return true;
        }
        else
        {
            ui->label_PasswordConfirmControl->setPixmap(PixFalseIcon);

            return false;
        }
    }
    else
        return false;

}

bool MainWindow::VerifService()
{
    if (ui->comboBox_service->currentIndex()>-1)
    {
        ui->label_ServiceControl->setPixmap(PixTrueIcon);
        return true;
    }
    else
    {
        ui->label_ServiceControl->setPixmap(PixFalseIcon);
        return false;

    }
}

bool  MainWindow::VerifPasswordIndiv()
{
    if (ui->lineEdit_motdepasse->text().length()<6 || ui->lineEdit_motdepasse->text().isEmpty())
    {
        ui->label_PasswordControl->setPixmap(PixFalseIcon);
        return false;
    }
    else
    {
        ui->label_PasswordControl->setPixmap(PixTrueIcon);
        return true;
    }
}

bool MainWindow::VerifAdresse()
{
    if (ui->lineEdit_adresse->text().isEmpty())
    {
        ui->label_AdresseControl->setPixmap(PixFalseIcon);
        return false;
    }
    else

    {
        ui->label_AdresseControl->setPixmap(PixTrueIcon);

        return true;
    }
}



bool  MainWindow::VerifMail(){

    if (ui->lineEdit_mailTravail->text().isEmpty() || (ui->lineEdit_mailTravail->text().lastIndexOf("@",-1)>ui->lineEdit_mailTravail->text().lastIndexOf(".",-1)) || ui->lineEdit_mailTravail->text().lastIndexOf("@",-1)==-1 || ui->lineEdit_mailTravail->text().lastIndexOf("@",-1)==-1)
    {
        ui->label_mailControl->setPixmap(PixFalseIcon);
        return false;

    }
    else
    {
        ui->label_mailControl->setPixmap(PixTrueIcon);
        return true;


    }
}
bool MainWindow::VerifSexe()
{
    if (ui->comboBox_sexe->currentIndex()>-1)
    {
        ui->label_SexeControl->setPixmap(PixTrueIcon);
        return true;
    }
    else
    {
        ui->label_SexeControl->setPixmap(PixFalseIcon);
        return false;
    }
}





bool MainWindow::VerifdateNaissance()
{
    if (ui->dateEdit_dateNaissance->date()==QDate::fromString("01/01/1800","dd/MM/yyyy"))
    {
        ui->label_DateNaissanceControl->setPixmap(PixFalseIcon);
        return false;
    }
    else
    {

        ui->label_DateNaissanceControl->setPixmap(PixTrueIcon);
        return true;
    }
}



bool MainWindow::verifID(){
    if (ui->lineEdit_ID->text().isEmpty() || ui->lineEdit_ID->text().length()<3 || ui->lineEdit_ID->text().contains(QRegularExpression("[^0-9]")))
    {
        ui->label_IDControl->setPixmap(PixFalseIcon);
        return false;

    }
    else
    {
        ui->label_IDControl->setPixmap(PixTrueIcon);
        return true;

    }

}

bool MainWindow::verifIDPointage(){
    if (ui->lineEdit_IDRechercherPointage->text().contains(QRegularExpression("[^0-9]")))
    {
        ui->label_RechercherPointageControl->setPixmap(PixFalseIcon);
        return false;

    }
    else
    {
        ui->label_RechercherPointageControl->setPixmap(PixTrueIcon);
        return true;

    }
}


bool  MainWindow::verifIDConge(){
    if (ui->lineEdit_IDCongeEmploye->text().isEmpty() || ui->lineEdit_IDCongeEmploye->text().length()<3 || ui->lineEdit_IDCongeEmploye->text().contains(QRegularExpression("[^0-9]")))
    {
        ui->label_IDCongeControl->setPixmap(PixFalseIcon);
        return false;

    }
    else
    {
        ui->label_IDCongeControl->setPixmap(PixTrueIcon);
        return true;

    }




}

bool MainWindow::VerifTypeConge(){
    if (ui->comboBox_TypeConge->currentIndex()>-1)
    {
        ui->label_typeCongeControl->setPixmap(PixTrueIcon);
        return true;
    }
    else
    {
        ui->label_typeCongeControl->setPixmap(PixFalseIcon);
        return false;
    }
}

bool MainWindow::VerifdateDebutConge()
{
    if (ui->dateEdit_DebutConge->date()==QDate::fromString("01/01/1800","dd/MM/yyyy"))
    {
        ui->label_DateDebutCongeControl->setPixmap(PixFalseIcon);
        return false;
    }
    else
    {

        ui->label_DateDebutCongeControl->setPixmap(PixTrueIcon);
        return true;
    }
}

bool MainWindow::VerifDateFinConge()
{
    if (((ui->dateEdit_DebutConge->date().year() - ui->dateEdit_FinConge->date().year())>=0) && ((ui->dateEdit_FinConge->date().month() - ui->dateEdit_DebutConge->date().month())>=0) &&  ((ui->dateEdit_FinConge->date().day() - ui->dateEdit_DebutConge->date().day())>0))
    {

        ui->label_DateFinCongeControl->setPixmap(PixTrueIcon);

        return true;
    }
    else
    {
        ui->label_DateFinCongeControl->setPixmap(PixFalseIcon);
        return false;
    }

}

void MainWindow::on_lineEdit_nom_cursorPositionChanged(int arg1, int arg2)
{
    if (AppelAffiche)
        VerifNom();
}
void MainWindow::on_lineEdit_prenom_cursorPositionChanged(int arg1, int arg2)
{
    if (AppelAffiche)
        VerifPrenom();
}
void MainWindow::on_lineEdit_NSS_cursorPositionChanged(int arg1, int arg2)
{
    if (AppelAffiche)
        VerifNSS();
}
void MainWindow::AfficheEmployeInstantane(Employe EmployeAafficher)
{

    QString nss=QString::number(EmployeAafficher.GetNss());
    QString cin=QString::number(EmployeAafficher.GetCin());
    QPixmap pixmap;

    AppelAffiche=false;
    ui->lineEdit_nom->setText(EmployeAafficher.GetNom());
    ui->lineEdit_prenom->setText(EmployeAafficher.GetPrenom());
    ui->lineEdit_ID->setText(EmployeAafficher.GetLogin());
    ui->lineEdit_motdepasse->setText(EmployeAafficher.GetMotDePasse());
    ui->lineEdit_adresse->setText(EmployeAafficher.GetAdresse());
    ui->lineEdit_mailTravail->setText(EmployeAafficher.GetAdresseMail());
    ui->dateEdit_dateNaissance->setDate(QDate::fromString(EmployeAafficher.GetDateNaissance(),"dd/MM/yyyy"));
    ui->comboBox_service->setCurrentIndex(ui->comboBox_service->findData(EmployeAafficher.GetService(),Qt::DisplayRole));
    ui->comboBox_sexe->setCurrentIndex(ui->comboBox_sexe->findData(EmployeAafficher.GetSexe(), Qt::DisplayRole));
    ui->lineEdit_NSS->setText(nss);
    ui->lineEdit_CIN->setText(cin);

    ui->lineEdit_confirmermotdepasse->setText(EmployeAafficher.GetMotDePasse());
    AppelAffiche=true;



}

void MainWindow::on_lineEdit_ID_cursorPositionChanged(int arg1, int arg2)
{
    if (ui->checkBox_IDSearch->isChecked())
    {
        unsigned long long login=ui->lineEdit_ID->text().toLongLong();
        Employe EmployeAchercher;
        EmployeAchercher.RechercherInstEmploye(login);

        if (!EmployeAchercher.GetLogin().isEmpty())
        {
            AfficheEmployeInstantane(EmployeAchercher);
        }
        else
            EnClear(1);
    }
    else
    {
        if (AppelAffiche)
            verifID();
    }
}



void MainWindow::on_lineEdit_CIN_cursorPositionChanged(int arg1, int arg2)
{
    if (AppelAffiche)
        VerifCIN();
}

void MainWindow::on_lineEdit_motdepasse_cursorPositionChanged(int arg1, int arg2)
{
    if (AppelAffiche)
        VerifPassword();
}

void MainWindow::on_lineEdit_confirmermotdepasse_cursorPositionChanged(int arg1, int arg2)
{
    if (AppelAffiche)
        VerifPasswordIndiv();
}

void MainWindow::on_comboBox_sexe_currentIndexChanged(int index)
{
    if (AppelAffiche)
        VerifSexe();
}





void MainWindow::on_dateEdit_dateNaissance_dateChanged(const QDate &date)
{
    if (AppelAffiche)
        VerifdateNaissance();
}


void MainWindow::on_lineEdit_adresse_cursorPositionChanged(int arg1, int arg2)
{
    if (AppelAffiche)
        VerifAdresse();
}


void MainWindow::on_pushButton_Edit_clicked()
{
    Employe EmployeAmodifier;
    unsigned long long loginUtilisateur=ui->lineEdit_ID->text().toLongLong();
    EmployeAmodifier.RechercherInstEmploye(loginUtilisateur);
    if (!EmployeAmodifier.GetLogin().isEmpty())
    {
        EmployeAmodifier.SetNom(ui->lineEdit_nom->text());
        EmployeAmodifier.SetPrenom(ui->lineEdit_prenom->text());
        EmployeAmodifier.SetLogin(ui->lineEdit_ID->text());
        EmployeAmodifier.SetAdresseMail(ui->lineEdit_mailTravail->text());
        EmployeAmodifier.SetAdresse(ui->lineEdit_adresse->text());
        EmployeAmodifier.SetService(ui->comboBox_service->currentText());
        EmployeAmodifier.SetSexe(ui->comboBox_sexe->currentText());
        EmployeAmodifier.SetNss(ui->lineEdit_NSS->text().toInt());
        EmployeAmodifier.SetCin(ui->lineEdit_CIN->text().toInt());
        EmployeAmodifier.SetDateNaissance(ui->dateEdit_dateNaissance->text());
        EmployeAmodifier.SetMotDePasse(ui->lineEdit_motdepasse->text());



        VerifNom();
        VerifPrenom();
        VerifService();
        VerifNSS();
        VerifCIN();
        VerifPassword();
        VerifPasswordIndiv();
        VerifAdresse();

        VerifMail();
        VerifSexe();
        VerifdateNaissance();

        if (  VerifdateNaissance() && VerifSexe() && VerifMail() && VerifAdresse() &&  VerifNom() && VerifPrenom() && VerifService() && VerifNSS()  && VerifCIN() && VerifPassword() && VerifPasswordIndiv())
        {
            EmployeAmodifier.ModifierEmploye();
            SetOuputMessage("L'employe a ete modifie avec succes ",true);
        }
        else
            SetOuputMessage("L'employe n'as pas ete modifie, Veuillez verifier les champs a saisir !",false);

    }
    else
    {

        SetOuputMessage("L'employe que vous voulez modifier n'existe pas dans la base de donnees",false);

    }
}


void MainWindow::on_pushButton_AjoutConge_clicked()
{
    QString typeconge,loginemploye,commentaireresponsable,commentaireemploye,datedebutConge,datefinConge;



    typeconge=ui->comboBox_TypeConge->currentText();
    datedebutConge=ui->dateEdit_DebutConge->date().toString();
    datefinConge=ui->dateEdit_FinConge->date().toString();
    commentaireresponsable=ui->textEdit_Responsable->toPlainText();
    commentaireemploye=ui->textEdit_Employe->toPlainText();
    loginemploye=ui->lineEdit_IDCongeEmploye->text();


    verifIDConge();
    VerifdateDebutConge();
    VerifDateFinConge();

    unsigned long long loginUtilsateur;
    loginUtilsateur=ui->lineEdit_IDCongeEmploye->text().toLongLong();
    loginemploye=ui->lineEdit_IDCongeEmploye->text();
    Employe EmployeTest;
    EmployeTest.RechercherInstEmploye(loginUtilsateur);


    if (EmployeTest.GetLogin().isEmpty())
    {
        SetOuputMessageConge("L'employe assosie au conge n'existe pas dans la base de donnees",false);
    }
    else
    {

        if (verifIDConge() && VerifTypeConge() && VerifdateDebutConge() && VerifdateDebutConge())
        {

            CRUDconge newConge(loginemploye,typeconge,commentaireresponsable,commentaireemploye,datedebutConge,datefinConge);
            newConge.AjoutConge();
            SetOuputMessageConge("Le conge a ete ajoute avec succes",true);
        }
        else
        {
            SetOuputMessageConge("Le conge n'as pas ete ajoute,Verifiez les champs a saisir",false);
        }

    }
}


void MainWindow::on_pushButton_ModifierConge_clicked()

{
    CRUDconge CongeAmodifier;
    CongeAmodifier.RechercherConge(ui->lineEdit_IDCongeEmployeRechercher->text());
    if (!CongeAmodifier.getLoginEmploye().isEmpty())
    {
        verifIDConge();
        VerifTypeConge();
        VerifdateDebutConge();
        VerifDateFinConge();

        if (verifIDConge() && VerifTypeConge() && VerifdateDebutConge() && VerifDateFinConge())
        {
            CongeAmodifier.setIdConge(ui->lineEdit_IDCongeEmployeRechercher->text().toLongLong());
            CongeAmodifier.setLoginEmploye(ui->lineEdit_IDCongeEmploye->text());
            CongeAmodifier.setTypeConge(ui->comboBox_TypeConge->currentText());
            CongeAmodifier.setCommentaireEmploye(ui->textEdit_Employe->toPlainText());
            CongeAmodifier.setCommentaireResponsable(ui->textEdit_Responsable->toPlainText());
            CongeAmodifier.setDateDebutConge(ui->dateEdit_DebutConge->text());
            CongeAmodifier.setDateFinConge(ui->dateEdit_FinConge->text());

            CongeAmodifier.ModifierConge();

            SetOuputMessageConge("Le conge a ete modifie avec succes",true);
        }
        else
            SetOuputMessageConge("Le conge n'as pas ete modifie,Verfiez les champs a saisir",false);

    }
    else
        SetOuputMessageConge("Le conge que vous voulez modifier n'existe pas dans la base de donnees",false);
}

void MainWindow::EnClearConge(){

    ui->lineEdit_IDCongeEmploye->clear();
    ui->comboBox_TypeConge->setCurrentIndex(-1);
    ui->dateEdit_DebutConge->setDate(QDate::fromString("01/01/1800","dd/MM/yyyy"));
    ui->dateEdit_FinConge->setDate(QDate::fromString("01/01/1800","dd/MM/yyyy"));
    ui->textEdit_Responsable->clear();
    ui->textEdit_Employe->clear();

    ui->label_IDCongeControl->clear();
    ui->label_typeCongeControl->clear();
    ui->label_DateDebutCongeControl->clear();
    ui->label_DateFinCongeControl->clear();
    ui->SortieApplicationConge->clear();

}

void MainWindow::AfficheCongeInstantaneConge(CRUDconge CongeAafficher)
{

    AppelAfficheConge=false;
    ui->lineEdit_IDCongeEmploye->setText(CongeAafficher.getLoginEmploye());
    ui->comboBox_TypeConge->setCurrentIndex(ui->comboBox_TypeConge->findData(CongeAafficher.getTypeConge(), Qt::DisplayRole));
    ui->dateEdit_DebutConge->setDate(QDate::fromString(CongeAafficher.getDateDebutConge(),"dd/MM/yyyy"));
    ui->dateEdit_FinConge->setDate(QDate::fromString(CongeAafficher.getDateFinConge(),"dd/MM/yyyy"));
    ui->textEdit_Employe->setText(CongeAafficher.getCommentaireEmploye());
    ui->textEdit_Responsable->setText(CongeAafficher.getCommentaireResponsable());
    AppelAfficheConge=true;
}
void MainWindow::on_lineEdit_IDCongeEmployeRechercher_cursorPositionChanged(int arg1, int arg2)
{
    QString login=ui->lineEdit_IDCongeEmployeRechercher->text();
    CRUDconge CongeAchercher;
    CongeAchercher.RechercherConge(login);


    if (!CongeAchercher.getLoginEmploye().isEmpty())
    {

        AfficheCongeInstantaneConge(CongeAchercher);
        SetOuputMessageConge("1 Resultat trouve",true);

    }


    else
    {
        EnClearConge();
        SetOuputMessageConge("Aucun Resultat trouve",false);
    }
}


void MainWindow::on_pushButton_SupprimerConge_clicked()
{
    CRUDconge CongeAmodifier;
    CongeAmodifier.RechercherConge(ui->lineEdit_IDCongeEmployeRechercher->text());
    if (!CongeAmodifier.getLoginEmploye().isEmpty())
    {
        CongeAmodifier.setIdConge(ui->lineEdit_IDCongeEmployeRechercher->text().toLongLong());
        CongeAmodifier.setLoginEmploye(ui->lineEdit_IDCongeEmploye->text());
        CongeAmodifier.setTypeConge(ui->comboBox_TypeConge->currentText());
        CongeAmodifier.setCommentaireEmploye(ui->textEdit_Employe->toPlainText());
        CongeAmodifier.setCommentaireResponsable(ui->textEdit_Responsable->toPlainText());
        CongeAmodifier.setDateDebutConge(ui->dateEdit_DebutConge->text());
        CongeAmodifier.setDateFinConge(ui->dateEdit_FinConge->text());
        CongeAmodifier.SupprimerConge();
        SetOuputMessageConge("Le conge a ete supprime avec succes",true);

    }
    else
        SetOuputMessageConge("Le conge n'as pas ete supprime,Verifiez le login de l'employe",false);



}


void MainWindow::on_pushButton_NettoyerConge_clicked()
{
EnClearConge();
}

/*
void MainWindow::on_pushButton_ListingConge_clicked()
{
    ui->tableViewConge->setModel(CRUDconge.AfficherConge());

}
*/

void MainWindow::on_lineEdit_IDCongeEmploye_cursorPositionChanged(int arg1, int arg2)
{
    if (AppelAfficheConge)
        verifIDConge();
}


void MainWindow::on_comboBox_TypeConge_currentIndexChanged(int index)
{
    if (AppelAfficheConge)
        VerifTypeConge();
}


void MainWindow::on_dateEdit_DebutConge_dateChanged(const QDate &date)
{
    if (AppelAfficheConge)
        VerifdateDebutConge();
}


void MainWindow::on_dateEdit_FinConge_dateChanged(const QDate &date)
{
    if (AppelAfficheConge)
        VerifDateFinConge();
}

/*
void MainWindow::on_lineEdit_IDRechercherPointage_cursorPositionChanged(int arg1, int arg2)
{
    int RowCount;
    QString login=ui->lineEdit_IDRechercherPointage->text();
    pointage point;
    verifIDPointage();

   ui->tableViewPointage->setModel(pointage.ConsulterPointageParticulier(login,&RowCount));
    QString r = QString::number(RowCount);
    if (RowCount==0)
        SetOuputMessagePointage("Aucun Resultat trouves",false);
    else
        SetOuputMessagePointage(r+" Resultats trouves",true);
}
*/
