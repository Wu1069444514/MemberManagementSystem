#include "addgift.h"
#include "ui_addgift.h"

addGift::addGift(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addGift)
{
    ui->setupUi(this);
    setWindowTitle(u8"礼品添加");       //设置窗口名称
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&addGift::Submit);
    connect(ui->buttonBox,&QDialogButtonBox::rejected,this,&QDialog::close);

    //11位数字格式
    QRegExp num("[0-9]{11}$");
    QRegExpValidator *validator_num = new QRegExpValidator(num, this);

    //正实数格式
    QRegExp real("^[0-9]+(.[0-9]{1,3})?$");
    QRegExpValidator *validator_real = new QRegExpValidator(real, this);

    //名称格式
    QRegExp nam("^[a-zA-Z0-9_\u4e00-\u9fa5\\w]{1,10}$");
    QRegExpValidator *validator_nam = new QRegExpValidator(nam, this);

    ui->lineEdit_67->setValidator(validator_num);
    ui->lineEdit_65->setValidator(validator_nam);
    ui->lineEdit_68->setValidator(validator_num);
    ui->lineEdit_64->setValidator(validator_num);

}

addGift::~addGift()
{
    delete ui;
}


//提交礼品信息
void addGift:: Submit()
{

    if(ui->lineEdit_67->text().isEmpty())
    {
        QMessageBox::warning(this,u8"", u8"请输入礼品号");

    }
    else if (ui->lineEdit_65->text().isEmpty()) {
        QMessageBox::warning(this,u8"", u8"请输入礼品名称");

    }
    else if (ui->lineEdit_68->text().isEmpty()) {
        QMessageBox::warning(this,u8"", u8"请输入剩余数目");

    }
    else {

        bool ok;
        int GIFT_NUMBER = ui->lineEdit_67->text().toInt(&ok,10);
        QString GITF_NAME= ui->lineEdit_65->text();
        int LEFT_NUMBER = ui->lineEdit_68->text().toInt(&ok,10);
        int INTEGRAL_NUMBER = ui->lineEdit_64->text().toInt(&ok,10);



        //插入商品信息
        myDatabase.InsertGIFT_INFO(GIFT_NUMBER,GITF_NAME,LEFT_NUMBER,INTEGRAL_NUMBER);

        //清空信息
        ui->lineEdit_67->setText(u8"");
        ui->lineEdit_65->setText(u8"");
        ui->lineEdit_68->setText(u8"");
        ui->lineEdit_64->setText(u8"");
    }



}
