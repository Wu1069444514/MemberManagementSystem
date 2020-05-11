#include "adddiscount.h"
#include "ui_adddiscount.h"

addDiscount::addDiscount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDiscount)
{
    ui->setupUi(this);
    setWindowTitle(u8"折扣添加");       //设置窗口名称
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&addDiscount::Submit);
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
    ui->lineEdit_68->setValidator(validator_real);
    ui->lineEdit_64->setValidator(validator_num);

}

addDiscount::~addDiscount()
{
    delete ui;
}


//提交优惠券信息
void addDiscount:: Submit()
{

    if(ui->lineEdit_67->text().isEmpty())
    {
        QMessageBox::warning(this,u8"", u8"请输入优惠券名称");

    }
    else if (ui->lineEdit_65->text().isEmpty()||ui->lineEdit_68->text().isEmpty()
             ||ui->lineEdit_64->text().isEmpty()) {
        QMessageBox::warning(this,u8"", u8"请输入优惠条件");

    }

    else {

        bool ok;
        QString DISCOUNT_NAME = ui->lineEdit_67->text();             //优惠券名称
        double MONEY= ui->lineEdit_65->text().toDouble();            //优惠金额
        double DISCOUN = ui->lineEdit_68->text().toDouble();         //优惠额度
        int INTEGRAL_NUMBER = ui->lineEdit_64->text().toInt(&ok,10); //赠送积分



        //插入优惠券信息
        myDatabase.InsertDISC_INFO(DISCOUNT_NAME,MONEY,DISCOUN,INTEGRAL_NUMBER);



        //清空信息
        ui->lineEdit_67->setText(u8"");
        ui->lineEdit_65->setText(u8"");
        ui->lineEdit_68->setText(u8"");
        ui->lineEdit_64->setText(u8"");

    }


}
