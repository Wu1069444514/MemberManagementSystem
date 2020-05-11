#include "registwindow.h"
#include "ui_registwindow.h"

RegistWindow::RegistWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistWindow)
{
    ui->setupUi(this);
    setWindowTitle(u8"��Ա����ϵͳ");       //���ô�������
    connect(ui->pushButton_3,&QPushButton::clicked,this,&RegistWindow::Regist);
    connect(ui->pushButton_4,&QPushButton::clicked,this,&RegistWindow::Login);


    //11λ����
    QRegExp num("[0-9]{11}$");
    QRegExpValidator *validator_num = new QRegExpValidator(num, this);

    //����
    QRegExp code("^[a-zA-Z0-9~!@#$%^&*()_+-=;:,./<>?`]{6,16}$");
    QRegExpValidator *validator_code = new QRegExpValidator(code, this);

    //����
    QRegExp nam("^[a-zA-Z0-9_\u4e00-\u9fa5\\w]{1,10}$");
    QRegExpValidator *validator_nam = new QRegExpValidator(nam, this);


    ui->lineEdit_36->setValidator(validator_num);
    ui->lineEdit_37->setValidator(validator_nam);
    ui->lineEdit_38->setValidator(validator_code);
    ui->lineEdit_39->setValidator(validator_code);
}

RegistWindow::~RegistWindow()
{
    delete ui;
}



void RegistWindow::Login()
{

    ui->lineEdit_33->setText("");
    ui->lineEdit_36->setText("");
    ui->lineEdit_37->setText("");
    ui->lineEdit_38->setText("");
    ui->lineEdit_39->setText("");

}


void RegistWindow::Regist()
{
    if(ui->lineEdit_33->text().isEmpty())
    {
        QMessageBox::warning(this,"", u8"����������");

    }
    else if (ui->lineEdit_36->text().isEmpty()) {
        QMessageBox::warning(this,"", u8"������绰");

    }
    else if (ui->lineEdit_37->text().isEmpty()) {
        QMessageBox::warning(this,"", u8"�������˻�");

    }
    else if (ui->lineEdit_38->text().isEmpty()) {
        QMessageBox::warning(this,"", u8"����������");

    }

    else {

        bool ok;
        QString MANAGER_NAME = ui->lineEdit_33->text();
        int TELEPHON= ui->lineEdit_36->text().toInt(&ok,10);
        QString ACCOUNT = ui->lineEdit_37->text();
        QString CODE = ui->lineEdit_38->text();
        QString reCODE = ui->lineEdit_39->text();


        if(CODE != reCODE)
        {
            QMessageBox::warning(this,"", u8"������������벻һ�£�");

        }
        else
        {

            myDatabase.InsertMAN_INFO( ACCOUNT,  CODE,MANAGER_NAME, TELEPHON);


            //�����������
            ui->lineEdit_33->setText("");
            ui->lineEdit_36->setText("");
            ui->lineEdit_37->setText("");
            ui->lineEdit_38->setText("");
            ui->lineEdit_39->setText("");

            QMessageBox::about(this,"", u8"ע��ɹ���");


        }
        this->close();

        mainwindow.show();

    }



}
