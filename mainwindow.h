#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "formation.h"
#include "cours.h"
#include "examen.h"
#include "certificat.h"
#include <QDesktopServices>
#include <QMediaPlayer>
#include <QDateTime>
#include <QHeaderView>
#include <QStandardItemModel>
#include "calendrier.h"
#include "arduino.h"
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




    void on_pb_ajouter_clicked();

    void on_pb_supp_clicked();

    void on_pb_moddifier_clicked();

    void on_tab_formation_activated(const QModelIndex &index);


    void on_pb_rechercher_clicked();

    void on_pb_annuler_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pb_ajouter_6_clicked();

    void on_pb_moddifier_4_clicked();

    void on_pb_supp_6_clicked();

    void on_pb_ajouter_2_clicked();

    void on_pb_moddifier_2_clicked();

    void on_pb_supp_3_clicked();

    void on_pb_ajouter_3_clicked();

    void on_pb_moddifier_3_clicked();

    void on_pb_supp_4_clicked();


    void on_pb_modifier_5_clicked();

    void on_pb_supp_5_clicked();

    void on_pb_ajouter_5_clicked();

    void on_pb_pdf_clicked();

    void on_pb_ask_clicked();

    void on_pb_arduino_clicked();

private:
    QMediaPlayer * erreur = new QMediaPlayer ;
    Ui::MainWindow *ui;
    QDesktopServices service;
    formation f;
    cours c;
    examen e;
    certificat cer;
    QDateTime date;
    calendrier ca;
    Arduino A;
    QByteArray data;
};

#endif // MAINWINDOW_H
