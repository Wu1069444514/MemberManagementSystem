#ifndef REGISTWINDOW_H
#define REGISTWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "database.h"

namespace Ui {
class RegistWindow;
}

class RegistWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistWindow(QWidget *parent = nullptr);
    ~RegistWindow();

private:
    Ui::RegistWindow *ui;
    MainWindow mainwindow;
    DataBase myDatabase;


public slots:
    void Login();
    void Regist();
};

#endif // REGISTWINDOW_H
