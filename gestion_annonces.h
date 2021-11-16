#ifndef GESTION_ANNONCES_H
#define GESTION_ANNONCES_H

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

#include "annonce.h"
#include "smtp.h"

namespace Ui {
class gestion_annonces;
}

class gestion_annonces : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestion_annonces(QWidget *parent = nullptr);
    ~gestion_annonces();
    void creerPlan();
    void creerPayment();
    void creerDesign();
    void display();
    void filtre();
    void trie();
    void prepareChartData(QVector<int> &data ,QStringList &categories);
    void constructChart();

private slots:
    void on_pushButton_trouver_image_annonce_clicked();
    void on_pushButton_selectionner_image_annonce_clicked();
    void on_prec_creer_annonce_clicked();
    void on_suiv_creer_annonce_clicked();
    void on_Confirmer_annonce_clicked();
    void on_tout_les_candidat_annonce_clicked();
    void on_candidat_precis_annonce_clicked();
    void on_email_oui_annonce_clicked();
    void on_email_non_annonce_clicked();
    void on_calcul_prix_annonce_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_comboBox_6_currentIndexChanged(int index);
    void on_comboBox_7_currentIndexChanged(int index);
    void on_filtre_val_textChanged(const QString &arg1);
    void on_filtre_val_editingFinished();
    void on_echelle_currentIndexChanged(int index);

    void deleteAnnonce(int id);
    void sendEmails();



    void on_pushButton_clicked();

private:
    Ui::gestion_annonces *ui;
    Annonce a;
    QList<Annonce> qResult;
    QList<Annonce> filtredResult;
    int filtre_index;
    int tri_index;
    QString filtre_val;

};

#endif // GESTION_ANNONCES_H
