#include "mainwindow.h"
#include "loginwindow.h"
#include "database.h"
#include <QApplication>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;       //主窗口
    LoginWindow l;      //登录窗口
    //QStringList drivers = QSqlDatabase::drivers();

    //DataBase myDatabase;
    //myDatabase.CheckOpen();

    l.show();
    //w.show();
    return a.exec();

}
