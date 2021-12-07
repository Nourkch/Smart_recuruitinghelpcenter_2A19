#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}






/*

void Autentification::on_pushButton_2_clicked()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("java");
    if(db.open())
    {
        QSqlQuery query;
        if(query.exec("SELECT * FROM user"))
        {
            while(query.next())
            {
                if(query.value(1).toString()==ui->loginLineEdit->text() && query.value(3).toString()==ui->motDePasseLineEdit->text())
                {QMessageBox::information(this,"Succés","Bienvenue "+ui->loginLineEdit->text());
                    db.close();
                    MainWindow *mw=new MainWindow();
                    mw->showMaximized();
                    Autentification::close();

                    return;}
               }
            QMessageBox::critical(this, "Erreur de connection", "Vos données de connexion sont erronés, veuillez réessayer !");
        }
        else {
            qDebug() << "Error = " << db.lastError().text();
        }

        db.close();
    }
}
*/

void login::on_checkBox_clicked(bool checked)
{

    if(checked) {
        ui->lineEdit_mdp->setEchoMode(QLineEdit::Normal);
        return;
    }
    ui->lineEdit_mdp->setEchoMode(QLineEdit::Password);

}

