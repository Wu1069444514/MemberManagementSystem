#include "addactivity.h"
#include "ui_addactivity.h"
#include "mainwindow.h"

addActivity::addActivity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addActivity)
{
    ui->setupUi(this);
    setWindowTitle(u8"����");       //���ô�������
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&addActivity::Submit);
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

addActivity::~addActivity()
{
    delete ui;
}



//�ύ���Ϣ
void addActivity:: Submit()
{
    if(ui->lineEdit_67->text().isEmpty())
    {
        QMessageBox::warning(this,u8"", u8"����������");

    }
    else if (ui->lineEdit_65->text().isEmpty()||ui->lineEdit_68->text().isEmpty()
             ||ui->lineEdit_64->text().isEmpty()) {
        QMessageBox::warning(this,u8"", u8"�������Ż�����");

    }
    else  {

        bool ok;
        QString ACTIVITYT_NAME = ui->lineEdit_67->text();                   //�����
        double MONEY= ui->lineEdit_65->text().toDouble();                   //�ۿ۽��
        double DISCOUN = ui->lineEdit_68->text().toDouble();                //�ۿ۶��
        int INTEGRAL_NUMBER = ui->lineEdit_64->text().toInt(&ok,10);        //���ͻ���



        //������Ϣ
        myDatabase.InsertACT_INFO(ACTIVITYT_NAME,MONEY,DISCOUN,INTEGRAL_NUMBER);

        //�����Ϣ
        ui->lineEdit_67->setText(u8"");
        ui->lineEdit_65->setText(u8"");
        ui->lineEdit_68->setText(u8"");
        ui->lineEdit_64->setText(u8"");
    }

;
}
