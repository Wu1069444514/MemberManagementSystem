#ifndef ADDGIFT_H
#define ADDGIFT_H

#include <QDialog>
#include "database.h"
#include <QValidator>
#include<QMessageBox>

namespace Ui {
class addGift;
}

class addGift : public QDialog
{
    Q_OBJECT

public:
    explicit addGift(QWidget *parent = nullptr);
    ~addGift();
    DataBase myDatabase;

private:
    Ui::addGift *ui;

public slots:
    void Submit();
};

#endif // ADDGIFT_H
