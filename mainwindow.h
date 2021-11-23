#define MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <partenaire.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void sendMail();
     void readyread();

    void mailSent(QString status);

    void on_pushButton_clicked();

    void on_pb_ajouter_clicked();

    void on_le_ajouter_clicked();

    void on_le_supprimer_clicked();

    void on_le_Modifier_clicked();

    void on_radioButton_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_2_clicked();

    void on_le_recherche_abonne_2_textChanged(const QString &arg1);

    void on_le_recherche_textChanged(const QString &arg1);

    void on_pushButton_pdf_clicked();

    void on_se_connecter_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_sendBtn_clicked();

    void on_imprimer_paie_clicked();


private:
    Ui::MainWindow *ui;
    partenaire p;


};
