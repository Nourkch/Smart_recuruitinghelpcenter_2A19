#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "partenaire.h"
#include <QtDebug>
#include <QString>
#include <QMessageBox>
#include <QIntValidator>
#include <qsqlquerymodel.h>
#include <QWidget>
#include"chatclient.h"
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QPrintDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->table_partenaire->setModel(p.afficher());

    //email
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));

}
void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void MainWindow::sendMail()
{
   chatclient* Chatclient = new chatclient(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toUShort());
    connect(Chatclient, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
  Chatclient->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_le_ajouter_clicked()
{
{
       int id=ui->le_id->text().toInt();
       QString nom=ui->le_nom->text();
       QString adresse=ui->le_adresse->text();
       QString mail=ui->le_mail->text();
       int numero=ui->le_numero->text().toInt();



       partenaire p(id,nom,mail,adresse,numero);
       bool test=p.ajouter();

   if (test)
   {
       ui->table_partenaire->setModel(p.afficher());

       QMessageBox::information(nullptr, QObject::tr("ok"),
                       QObject::tr("ajout effectue.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
}

}}

void MainWindow::on_le_supprimer_clicked()
{
  p.setid(ui->le_id_sup->text().toInt());

        bool test=p.supprimer(p.getid());
        if(test)
           {
            ui->table_partenaire->setModel(p.afficher());

                     QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("suppression effectué.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);


    }
        else

            QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                                QObject::tr("suppression non effectue.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);



}
void MainWindow::on_le_Modifier_clicked()
{
    ui->table_partenaire->setModel(p.afficher());
   int id=ui->le_id->text().toInt();
       QString nom=ui->le_nom->text();
       QString adresse=ui->le_adresse->text();
       QString mail=ui->le_mail->text();
        int numero=ui->le_numero->text().toInt();
       bool    test=p.update(id,nom,adresse,mail,numero);
       if (test)
             {
                     ui->table_partenaire->setModel(p.afficher());

                 QMessageBox::information(nullptr,QObject::tr("OK"),
                                      QObject::tr("modification établie"),
                                      QMessageBox::Ok);}
             else{
             QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                     QObject::tr("modification non établie"),
                                     QMessageBox::Cancel);
}
}


void MainWindow::on_radioButton_clicked() //tri par id
{
    {QMessageBox msgBox ;
            QSqlQueryModel * model= new QSqlQueryModel();


               model->setQuery("select * from PARTENAIRE order by CAST(id as INT) desc");

               model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
               model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
               model->setHeaderData(3, Qt::Horizontal, QObject::tr("mail"));
               model->setHeaderData(4, Qt::Horizontal, QObject::tr("numero"));


                        ui->tableView->setModel(model);
                        ui->tableView->show();
                        msgBox.setText("Tri par id avec succés.");
                        msgBox.exec();

        }
}

void MainWindow::on_radioButton_3_clicked() //tri par nom
{
    {
        QMessageBox msgBox ;
            QSqlQueryModel * model= new QSqlQueryModel();



               model->setQuery("select * from PARTENAIRE order by nom");

               model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
               model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
               model->setHeaderData(3, Qt::Horizontal, QObject::tr("mail"));
               model->setHeaderData(4, Qt::Horizontal, QObject::tr("numero"));


                        ui->tableView->setModel(model);
                        ui->tableView->show();
                        msgBox.setText("Tri par nom avec succés.");
                        msgBox.exec();
    }

}

void MainWindow::on_radioButton_2_clicked() //tri par adresse
{
    QMessageBox msgBox ;
        QSqlQueryModel * model= new QSqlQueryModel();



           model->setQuery("select * from PARTENAIRE order by adresse");
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("mail"));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("numero"));

                    ui->tableView->setModel(model);
                    ui->tableView->show();
                    msgBox.setText("Tri par adresse avec succés.");
                    msgBox.exec();
}


void MainWindow::on_le_recherche_textChanged(const QString &arg1)
{

        partenaire p;
            if(ui->le_recherche->text() == "")
                {
                    ui->tableView->setModel(p.afficher());
                }
                else
                {
                     ui->tableView->setModel(p.rechercher(ui->le_recherche->text()));
                }


}

void MainWindow::on_pushButton_pdf_clicked()
{QString strStream;
QTextStream out(&strStream);

const int rowCount = ui->table_partenaire->model()->rowCount();
const int columnCount = ui->table_partenaire->model()->columnCount();

out <<  "<html>\n"
    "<head>\n"
    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
    <<  QString("<title>%1</title>\n").arg("strTitle")
    <<  "</head>\n"
    "<body bgcolor=#ffffff link=#5000A0>\n"

    //     "<align='right'> " << datefich << "</align>"
    "<center> <H1>Liste es partenaires </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

// headers
out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
for (int column = 0; column < columnCount; column++)
    if (!ui->table_partenaire->isColumnHidden(column))
        out << QString("<th>%1</th>").arg(ui->table_partenaire->model()->headerData(column, Qt::Horizontal).toString());
out << "</tr></thead>\n";

// data table
for (int row = 0; row < rowCount; row++)
{
    out << "<tr> <td bkcolor=0>" << row + 1 << "</td>";
    for (int column = 0; column < columnCount; column++)
    {
        if (!ui->table_partenaire->isColumnHidden(column))
        {
            QString data = ui->table_partenaire->model()->data(ui->table_partenaire->model()->index(row, column)).toString().simplified();
            out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
        }
    }
    out << "</tr>\n";
}
out <<  "</table> </center>\n"
    "</body>\n"
    "</html>\n";

QString fileName = QFileDialog::getSaveFileName((QWidget * )0, "Sauvegarder en PDF", QString(), "*.pdf");
if (QFileInfo(fileName).suffix().isEmpty())
{
    fileName.append(".pdf");
}

QPrinter printer (QPrinter::PrinterResolution);
printer.setOutputFormat(QPrinter::PdfFormat);
printer.setPaperSize(QPrinter::A4);
printer.setOutputFileName(fileName);

QTextDocument doc;
doc.setHtml(strStream);
doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
doc.print(&printer);
}


ChatClient::ChatClient(QObject *parent)
    : QObject(parent)
    , m_clientSocket(new QTcpSocket(this))
    , m_loggedIn(false)
{
    // Forward the connected and disconnected signals
    connect(m_clientSocket, &QTcpSocket::connected, this, &ChatClient::connected);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, &ChatClient::disconnected);
    // connect readyRead() to the slot that will take care of reading the data in
    //connect(m_clientSocket, &QTcpSocket::readyRead, this, &ChatClient:: onReadyRead);
    // Forward the error signal, QOverload is necessary as error() is overloaded, see the Qt docs
    connect(m_clientSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &ChatClient::error);
    // Reset the m_loggedIn variable when we disconnect. Since the operation is trivial we use a lambda instead of creating another slot
    connect(m_clientSocket, &QTcpSocket::disconnected, this, [this]()->void{m_loggedIn = false;});
}


void MainWindow::on_imprimer_paie_clicked()
{
    QString strStream;
            QTextStream out(&strStream);

            const int rowCount = ui->table_partenaire->model()->rowCount();
            const int columnCount = ui->table_partenaire->model()->columnCount();
            QString TT = QDate::currentDate().toString("yyyy/MM/dd");
            out <<"<html>\n"
                  "<head>\n"
                   "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                << "<title>ERP - COMmANDE LIST<title>\n "
                << "</head>\n"
                "<body bgcolor=#ffffff link=#5000A0>\n"
                "<h1 style=\"text-align: center;\"><strong> *****LISTE DES Factures ***** "+TT+"</strong></h1>"
                "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                  "</br> </br>";
            // headers
            out << "<thead><tr bgcolor=#d6e5ff>";
            for (int column = 0; column < columnCount; column++)
                if (!ui-> table_partenaire ->isColumnHidden(column))
                    out << QString("<th>%1</th>").arg(ui->table_partenaire->model()->headerData(column, Qt::Horizontal).toString());
            out << "</tr></thead>\n";

            // data table
            for (int row = 0; row < rowCount; row++) {
                out << "<tr>";
                for (int column = 0; column < columnCount; column++) {
                    if (!ui->table_partenaire->isColumnHidden(column)) {
                        QString data =ui->table_partenaire->model()->data(ui->table_partenaire->model()->index(row, column)).toString().simplified();
                        out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                    }
                }
                out << "</tr>\n";
            }
            out <<  "</table>\n"
                "</body>\n"
                "</html>\n";

            QTextDocument *document = new QTextDocument();
            document->setHtml(strStream);

            QPrinter printer;

            QPrintDialog *baba = new QPrintDialog(&printer, NULL);
            if (baba->exec() == QDialog::Accepted) {
                document->print(&printer);
            }

            delete document;
}

