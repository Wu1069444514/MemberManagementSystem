#ifndef ADDACTIVITY_H
#define ADDACTIVITY_H

#include <QDialog>
#include "database.h"
#include <QValidator>
#include<QMessageBox>

namespace Ui {
class addActivity;
}



class addActivity : public QDialog
{
    Q_OBJECT

public:
    explicit addActivity(QWidget *parent = nullptr);
    ~addActivity();


private:
    Ui::addActivity *ui;
    DataBase myDatabase;

public slots:

    void Submit();

};

#endif // ADDACTIVITY_H
