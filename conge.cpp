#include "conge.h"
#include "ui_conge.h"

conge::conge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::conge)
{
    ui->setupUi(this);
}

conge::~conge()
{
    delete ui;
}
