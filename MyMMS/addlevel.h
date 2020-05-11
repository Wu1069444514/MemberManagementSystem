#ifndef ADDLEVEL_H
#define ADDLEVEL_H

#include <QDialog>
#include "database.h"
#include <QValidator>
#include<QMessageBox>

namespace Ui {
class addLevel;
}

class addLevel : public QDialog
{
    Q_OBJECT

public:
    explicit addLevel(QWidget *parent = nullptr);
    ~addLevel();
    DataBase myDatabase;

private:
    Ui::addLevel *ui;

public slots:
    void Submit();
};

#endif // ADDLEVEL_H
