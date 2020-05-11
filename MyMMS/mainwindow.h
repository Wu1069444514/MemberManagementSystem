#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include <QDate>
#include <QStandardItemModel>
#include<QTableView>
#include<QMessageBox>
#include<addactivity.h>
#include<adddiscount.h>
#include<addgift.h>
#include<addlevel.h>
#include<QComboBox>
#include <tuple>

struct MyResult{
    double sum;
    int integral;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetFormat();
    void ShowMemList();
    void ShowProList();
    void ShowLevList();
    void ShowComList();
    void ShowTemProList();
    void ShowDiscList();
    void ShowActList();
    void ShowGiftList();

    void ShowClassList();
    void ShowTemGiftList();

    void Submit(QTableView *tableview);  //提交对表单的修改


    int isDigitStr(QString src);    //判断字符串是否为纯数字

    void ChangeComb(QComboBox *combobox,QString tablename);

    void accepCombobox();

    struct MyResult CaculateResult();



private:
    Ui::MainWindow *ui;
    bool findCard = false;
    bool findComMem = false;
    bool findGiftMem = false;
    DataBase myDatabase;
    addLevel newlevel;
    addGift newGift;
    addActivity newActivity;
    addDiscount newDiscount;

    int memTableCurrentrow = -1;
    int levTableCurrentrow = -1;
    int proTableCurrentrow = -1;
    int disTableCurrentrow = -1;
    int actTableCurrentrow = -1;
    int gifTableCurrentrow = -1;





public slots:
    void norSetCurrentIndex();
    void tabSetchecked();
    void SubMemberInfo();
    void SubProductInfo();
    void SubCardInfo();

    void FindMember();
    void FindProduct();
    void FindDiscount();
    void FindActivity();
    void FindGift();

    void FindPayCard();
    void UpdateCard();
    void FindTheMember();

    void FindComMem();
    void FindComPro();
    void Purchase ();

    void FindGitfMem();
    void FindTheGift();
    void Conversion();

    void setTableEdit();

    void deletMemRow();
    void deletLevRow();
    void deletProRow();
    void deletDisRow();
    void deletActRow();
    void deletGifRow();


    void GetmemTableCurrentrow();
    void GetproTableCurrentrow();
    void GetlevTableCurrentrow();
    void GetdisTableCurrentrow();
    void GetactTableCurrentrow();
    void GetgifTableCurrentrow();



};


#endif // MAINWINDOW_H
