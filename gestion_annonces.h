#ifndef GESTION_ANNONCES_H
#define GESTION_ANNONCES_H

#include <QMainWindow>

namespace Ui {
class gestion_annonces;
}

class gestion_annonces : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestion_annonces(QWidget *parent = nullptr);
    ~gestion_annonces();

private:
    Ui::gestion_annonces *ui;
};

#endif // GESTION_ANNONCES_H
