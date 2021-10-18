#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"


// test tuto git

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    setCentralWidget(ui->groupBox);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionCommentaires_triggered()
{

   Dialog dialog;

   dialog.setModal(true);
   dialog.exec();

}
