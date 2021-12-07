#ifndef APP_H
#define APP_H

#include <QDialog>
#include <QSystemTrayIcon>
#include "candidats.h"
#include <QMainWindow>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPixmap>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSignalMapper>
#include <QList>
#include <QVector>
#include <QTimer>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QPrinter>
#include <QPainter>

#include "stmp.h"
#include "annonce.h"
#include "employe.h"
#include"finance.h"
#include<QPainter>
#include<QPdfWriter>
#include<QtCharts>
#include<QChartView>
#include"notification.h"
namespace Ui {
class app;
}

class app : public QDialog
{
    Q_OBJECT

public:
    explicit app(QWidget *parent = nullptr);
    ~app();

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

    /////
    ///
    ///
    ///
    void creerPlan();
    void creerPayment();
    void creerDesign();
    void display();
    void filtre();
    void trie();
    void prepareChartData(QVector<int> &data ,QStringList &categories);
    void constructChart();

    void deleteAnnonce(int id);
    void sendEmails();

    void AfficheEmployeInstantane(Employe EmployeAafficher);

   // void AfficheCongeInstantaneConge(CRUDconge);  CONGE.H IS MISSING

private slots:
    void on_pushbutton_browser_clicked();

    void on_pushButton_listeCandidat_clicked();

    void on_pushButton_clicked();
    
    void on_pushButton_ajoutCandidat_clicked();

    void on_pushButton_cancelAjoutCandidat_clicked();

    void on_pushButton_validerAjoutCandidat_clicked();

    void on_pushButton_precedent_ajoutCandidat_clicked();

    void on_pushButton_supprimerCandidat_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_precedentCandidatSupprimer_clicked();

    void on_pushButton_precedent_Candidat_clicked();

    void on_pushButton_annuler_suppCandidat_clicked();

    void on_pushButton_modifierCandidat_clicked();

    void on_pushButton_valider_modifCandidat_clicked();

    void on_pushButton_precendent_modifCandidat_clicked();

    void on_pushButton_precedentajoutCandidat_clicked();

    void on_pushButton_chercherCandidat_clicked();

    void on_pushButton_triASC_clicked();

    void on_pushButton_triDESC_clicked();

    void on_pushButton_Sponsoring_clicked();

    void on_pushButton_precedentAnnonces_clicked();

    void on_pushButton_creerAnnonce_clicked();

    void on_logo_khadamni_clicked();

    void on_suiv_creer_annonce_clicked();

    void on_prec_creer_annoncePlan_clicked();

    void on_suiv_creer_annoncePlan_clicked();

    void on_pushButton_prec_payment_clicked();

    void on_pushButton_suiv_payement_clicked();

    void on_pushButton_selectionner_image_annonce_clicked();

    void on_pushButton_trouver_image_annonce_clicked();

    void on_Confirmer_annonce_clicked();

    void on_tout_les_candidat_annonce_clicked();

    void on_candidat_precis_annonce_clicked();

    void on_email_oui_annonce_clicked();

    void on_email_non_annonce_clicked();

    void on_calcul_prix_annonce_clicked();

    void on_pushButton_consulterAnnonces_clicked();

    void on_pushButton_statAnnonces_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_comboBox_6_currentIndexChanged(int index);

    void on_comboBox_7_currentIndexChanged(int index);

    void on_filtre_val_textChanged(const QString &arg1);

    void on_filtre_val_editingFinished();

    void on_echelle_currentIndexChanged(int index);

    void on_pushButton_imprimer_clicked();

    void on_pushButton_annulerCreationAnnonce_clicked();

    void on_pushButton_precedentConsulterAnnonces_clicked();

    void on_pushButton_PrecendentStatAnnonces_clicked();

    void on_pushButton_listeEmployers_clicked();

    void on_pushButton_4_clicked();

    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_load_clicked();

    void on_pb_modifier_clicked();

    void on_pb_trier_id_clicked();

    void on_pb_trier_nom_clicked();

    void on_pb_trier_prenom_clicked();

    void on_pb_rechercher_clicked();

    void on_pb_pdf_clicked();

    void on_pb_stat_clicked();

    void on_pushButton_Factures_clicked();

    void on_pb_precedent_finance_clicked();

private:
    Ui::app *ui;
    QSystemTrayIcon *mSystemTrayIcon ;
    candidats tabCandidat;

    Annonce a;
    QList<Annonce> qResult;
    QList<Annonce> filtredResult;
    int filtre_index;
    int tri_index;
    QString filtre_val;
    finance f;
};

#endif // APP_H
