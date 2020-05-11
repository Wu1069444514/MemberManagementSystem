#include "addlevel.h"
#include "ui_addlevel.h"

addLevel::addLevel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addLevel)
{
    ui->setupUi(this);
    setWindowTitle(u8"�ȼ����");       //���ô�������
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&addLevel::Submit);
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
    ui->lineEdit_68->setValidator(validator_num);
}

addLevel::~addLevel()
{
    delete ui;
}

//�ύ��Ʒ��Ϣ
void addLevel:: Submit()
{
    if(ui->lineEdit_67->text().isEmpty())
    {
        QMessageBox::warning(this,u8"", u8"������ȼ�����");

    }
    else if (ui->lineEdit_65->text().isEmpty()||ui->lineEdit_68->text().isEmpty())
    {
        QMessageBox::warning(this,u8"", u8"�������Ż�����");

    }
    else {


        bool ok;
        QString LEVEL= ui->lineEdit_67->text();                          //�ȼ�
        double DISCOUNT = ui->lineEdit_65->text().toDouble();            //�ۿ�
        int INTEGRAL = ui->lineEdit_68->text().toInt(&ok,10);            //����

        //����ȼ���Ϣ
        myDatabase.InsertLEVEL_INFO(LEVEL,DISCOUNT,INTEGRAL);

        //�����Ϣ
        ui->lineEdit_67->setText(u8"");
        ui->lineEdit_65->setText(u8"");
        ui->lineEdit_68->setText(u8"");
    }



}
