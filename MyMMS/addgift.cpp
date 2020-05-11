#include "addgift.h"
#include "ui_addgift.h"

addGift::addGift(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addGift)
{
    ui->setupUi(this);
    setWindowTitle(u8"��Ʒ���");       //���ô�������
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&addGift::Submit);
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

    ui->lineEdit_67->setValidator(validator_num);
    ui->lineEdit_65->setValidator(validator_nam);
    ui->lineEdit_68->setValidator(validator_num);
    ui->lineEdit_64->setValidator(validator_num);

}

addGift::~addGift()
{
    delete ui;
}


//�ύ��Ʒ��Ϣ
void addGift:: Submit()
{

    if(ui->lineEdit_67->text().isEmpty())
    {
        QMessageBox::warning(this,u8"", u8"��������Ʒ��");

    }
    else if (ui->lineEdit_65->text().isEmpty()) {
        QMessageBox::warning(this,u8"", u8"��������Ʒ����");

    }
    else if (ui->lineEdit_68->text().isEmpty()) {
        QMessageBox::warning(this,u8"", u8"������ʣ����Ŀ");

    }
    else {

        bool ok;
        int GIFT_NUMBER = ui->lineEdit_67->text().toInt(&ok,10);
        QString GITF_NAME= ui->lineEdit_65->text();
        int LEFT_NUMBER = ui->lineEdit_68->text().toInt(&ok,10);
        int INTEGRAL_NUMBER = ui->lineEdit_64->text().toInt(&ok,10);



        //������Ʒ��Ϣ
        myDatabase.InsertGIFT_INFO(GIFT_NUMBER,GITF_NAME,LEFT_NUMBER,INTEGRAL_NUMBER);

        //�����Ϣ
        ui->lineEdit_67->setText(u8"");
        ui->lineEdit_65->setText(u8"");
        ui->lineEdit_68->setText(u8"");
        ui->lineEdit_64->setText(u8"");
    }



}
