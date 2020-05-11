#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include"registwindow.h"
#include "mainwindow.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private:
    Ui::LoginWindow *ui;
    MainWindow mainwindow;
    RegistWindow registwindow;
    DataBase myDatabase;

public slots:
    void Login();
    void Regist();
};

#endif // LOGINWINDOW_H
