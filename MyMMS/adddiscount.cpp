#include "adddiscount.h"
#include "ui_adddiscount.h"

addDiscount::addDiscount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDiscount)
{
    ui->setupUi(this);
    setWindowTitle(u8"�ۿ����");       //���ô�������
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&addDiscount::Submit);
    connect(ui->buttonBox,&QDialogButtonBox::rejected,this,&QDialog::close);

    //11λ���ָ�ʽ
    QRegExp num("[0-9]{11}$");
    QRegExpValidator *validator_num = new QRegExpValidator(num, this);

    //��ʵ����ʽ
    QRegExp real("^[0-9]+(.[0-9]{1,3})?$");
    QRegExpValidator *validator_real = new QRegExpValidator(real, this);

    //���Ƹ�ʽ
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


//�ύ�Ż�ȯ��Ϣ
void addDiscount:: Submit()
{

    if(ui->lineEdit_67->text().isEmpty())
    {
        QMessageBox::warning(this,u8"", u8"�������Ż�ȯ����");

    }
    else if (ui->lineEdit_65->text().isEmpty()||ui->lineEdit_68->text().isEmpty()
             ||ui->lineEdit_64->text().isEmpty()) {
        QMessageBox::warning(this,u8"", u8"�������Ż�����");

    }

    else {

        bool ok;
        QString DISCOUNT_NAME = ui->lineEdit_67->text();             //�Ż�ȯ����
        double MONEY= ui->lineEdit_65->text().toDouble();            //�Żݽ��
        double DISCOUN = ui->lineEdit_68->text().toDouble();         //�Żݶ��
        int INTEGRAL_NUMBER = ui->lineEdit_64->text().toInt(&ok,10); //���ͻ���



        //�����Ż�ȯ��Ϣ
        myDatabase.InsertDISC_INFO(DISCOUNT_NAME,MONEY,DISCOUN,INTEGRAL_NUMBER);



        //�����Ϣ
        ui->lineEdit_67->setText(u8"");
        ui->lineEdit_65->setText(u8"");
        ui->lineEdit_68->setText(u8"");
        ui->lineEdit_64->setText(u8"");

    }


}
