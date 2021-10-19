#include "gestion_annonces.h"
#include "ui_gestion_annonces.h"

gestion_annonces::gestion_annonces(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gestion_annonces)
{
    ui->setupUi(this);
}

gestion_annonces::~gestion_annonces()
{
    delete ui;
}
