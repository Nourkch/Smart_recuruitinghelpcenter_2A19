#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>
#include <QtDebug>
#include <QMessageBox>
#include <QString>
#include <QDate>
#include <QDateEdit>
#include <QMediaPlayer>
#include <QSystemTrayIcon>
#include <QRegExpValidator>
#include<QElapsedTimer>
#include<QDebug>
#include <QSound>
#include <QMediaPlayer>
#include <iostream>
#include <QProgressBar>
#include <QStatusBar>
#include "connection.h"
#include<QTimer>
#include<QTime>
#include<QDateTime>
#include <QLCDNumber>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPainter>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QPrintDialog>
#include<QPdfWriter>
#include "app.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


     QPixmap background("C:/Users/Raider/Desktop/INTEGRATION/Atelier_Connexion/resources/background_login.jpg");
     ui->label_backgroundpic_login->setPixmap(background);


           mSystemTrayIcon = new QSystemTrayIcon(this);
           mSystemTrayIcon->setIcon(QIcon("C:/Users/Raider/Desktop/INTEGRATION/Atelier_Connexion/resources/logo_khadamni.png")); // app icon
           mSystemTrayIcon->setVisible(true);

}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_login_clicked()
{
    QString login = ui->lineEdit_login->text();
    QString mdp = ui->lineEdit_mdp->text();

    if (login == "nour" && mdp == "test")
{ QMessageBox::information(this,"Login","authentification terminee avec succes");
    hide();
    App = new app(this);
    App->show(); }
        else
        QMessageBox::warning(this,"Login","Login ou mot de passe incorrecte");

}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked) {
        ui->lineEdit_mdp->setEchoMode(QLineEdit::Normal);
        return;
    }
    ui->lineEdit_mdp->setEchoMode(QLineEdit::Password);
}

