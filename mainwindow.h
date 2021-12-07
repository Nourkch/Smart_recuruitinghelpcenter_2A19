#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "app.h"
#include <QSystemTrayIcon>

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
    void on_pushButton_login_clicked();

    void on_checkBox_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    app *App;
    QSystemTrayIcon *mSystemTrayIcon ;
};

#endif // MAINWINDOW_H
