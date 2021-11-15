#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "candidatss.h"
#include<QSystemTrayIcon>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_valider_clicked();

    void on_bouton_ajouter_clicked();

    void on_bouton_supprimer_clicked();

    void on_pushButton_valider_supprimer_clicked();

    void on_pushButton_annuler_supprimer_clicked();

    void on_pushButton_annuler_clicked();

    void on_bouton_modifier_clicked();

    void on_pushButton_valider_2_clicked();

    void on_pushButton_annuler_2_clicked();

    void on_pushButton_modif_valider_clicked();

    void on_pushButton_modif_annuler_clicked();

    void on_bouton_afficher_clicked();

    void on_triASC_clicked();

    void on_triDEC_clicked();

    void on_lineEdit_nom_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_prenom_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_cin_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_email_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_code_postal_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_rue_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_modif_nom_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_modif_prenom_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_modif_cin_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_modif_email_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_modif_rue_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_modif_codePostal_cursorPositionChanged(int arg1, int arg2);

    void on_bouton_recherche_clicked();

    void on_pushButton_pdf_clicked();

    void on_pushButton_clicked();

    void on_pushButton_excel_clicked();

    void on_pushButton_aide_clicked();

    void on_pushButton_google_clicked();

    void on_pushButton_stat_clicked();

private:
    Ui::MainWindow *ui;
QSystemTrayIcon *mSystemTrayIcon ;
    Candidatss tabCandidat;
};

#endif // MAINWINDOW_H
