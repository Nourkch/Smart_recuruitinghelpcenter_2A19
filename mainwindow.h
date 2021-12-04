#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"
#include "crudconge.h"
#include "pointage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void EnClear(int);
    void EnClearConge();

    void SetOuputMessage(QString,bool);
    void SetOuputMessagePointage(QString ,bool);
    void SetOuputMessageConge(QString,bool);
    bool VerifNom();
    bool VerifPrenom();
    bool VerifPassport();
    bool VerifNSS();
    bool VerifCIN();
    bool VerifPassword();
    bool VerifService();
    bool VerifPasswordIndiv();
    bool VerifAdresse();
    bool VerifMail();
    bool VerifSexe();
    bool VerifEtatCivil();
    bool VerifNationnalite();
    bool VerifdateNaissance();
    bool verifID();
    bool verifIDPointage();
    bool verifIDConge();
    bool VerifTypeConge();
    bool VerifdateDebutConge();
    bool VerifDateFinConge();
    void InitIndication();
    ~MainWindow();

private slots:

    void AfficheEmployeInstantane(Employe EmployeAafficher);
    void AfficheCongeInstantaneConge(CRUDconge);
    void on_pushButton_supprmier_clicked();

    void on_lineEdit_nom_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_prenom_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_NSS_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_ID_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_passport_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_CIN_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_motdepasse_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_confirmermotdepasse_cursorPositionChanged(int arg1, int arg2);

    void on_comboBox_sexe_currentIndexChanged(int index);

    void on_comboBox_EtatCivil_currentIndexChanged(int index);

    void on_lineEdit_nationnalite_cursorPositionChanged(int arg1, int arg2);

    void on_dateEdit_dateNaissance_dateChanged(const QDate &date);

    void on_lineEdit_adresse_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_Edit_clicked();

    void on_pushButton_AjoutConge_clicked();

    void on_pushButton_ModifierConge_clicked();

    void on_lineEdit_IDCongeEmployeRechercher_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_SupprimerConge_clicked();

    void on_pushButton_NettoyerConge_clicked();

   // void on_pushButton_ListingConge_clicked();

    void on_lineEdit_IDCongeEmploye_cursorPositionChanged(int arg1, int arg2);

    void on_comboBox_TypeConge_currentIndexChanged(int index);

    void on_dateEdit_DebutConge_dateChanged(const QDate &date);

    void on_dateEdit_FinConge_dateChanged(const QDate &date);

    void on_lineEdit_IDRechercherPointage_cursorPositionChanged(int arg1, int arg2);

private:
    QString nomRecherche;
    QString prenomRecherche;
    QString lastOutputMessage;
    QPixmap PixTrueIcon;
    QPixmap PixFalseIcon;
    bool AppelAffiche;
    bool AppelAffichePaiement;
    bool AppelAfficheConge;
    bool ConditionPrimaire;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
