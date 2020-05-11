#ifndef ADDDISCOUNT_H
#define ADDDISCOUNT_H

#include <QDialog>
#include "database.h"
#include <QValidator>
#include<QMessageBox>

namespace Ui {
class addDiscount;
}

class addDiscount : public QDialog
{
    Q_OBJECT

public:
    explicit addDiscount(QWidget *parent = nullptr);
    ~addDiscount();
    DataBase myDatabase;

private:
    Ui::addDiscount *ui;

public slots:
    void Submit();

};

#endif // ADDDISCOUNT_H
