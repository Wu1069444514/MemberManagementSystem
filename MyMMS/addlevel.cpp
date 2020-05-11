#include "addlevel.h"
#include "ui_addlevel.h"

addLevel::addLevel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addLevel)
{
    ui->setupUi(this);
    setWindowTitle(u8"等级添加");       //设置窗口名称
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&addLevel::Submit);
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

    ui->lineEdit_67->setValidator(validator_nam);
    ui->lineEdit_65->setValidator(validator_real);
    ui->lineEdit_68->setValidator(validator_num);
}

addLevel::~addLevel()
{
    delete ui;
}

//提交礼品信息
void addLevel:: Submit()
{
    if(ui->lineEdit_67->text().isEmpty())
    {
        QMessageBox::warning(this,u8"", u8"请输入等级名称");

    }
    else if (ui->lineEdit_65->text().isEmpty()||ui->lineEdit_68->text().isEmpty())
    {
        QMessageBox::warning(this,u8"", u8"请输入优惠条件");

    }
    else {


        bool ok;
        QString LEVEL= ui->lineEdit_67->text();                          //等级
        double DISCOUNT = ui->lineEdit_65->text().toDouble();            //折扣
        int INTEGRAL = ui->lineEdit_68->text().toInt(&ok,10);            //积分

        //插入等级信息
        myDatabase.InsertLEVEL_INFO(LEVEL,DISCOUNT,INTEGRAL);

        //清空信息
        ui->lineEdit_67->setText(u8"");
        ui->lineEdit_65->setText(u8"");
        ui->lineEdit_68->setText(u8"");
    }



}
