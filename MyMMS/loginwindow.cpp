#include "loginwindow.h"
#include "ui_loginwindow.h"

//��¼���湹�캯��
LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    ui->setupUi(this);
    setWindowTitle(u8"��Ա����ϵͳ");       //���ô�������
    connect(ui->pushButton,&QPushButton::clicked,this,&LoginWindow::Login);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&LoginWindow::Regist);

    //����
    QRegExp code("^[a-zA-Z0-9~!@#$%^&*()_+-=;:,./<>?`]{6,16}$");
    QRegExpValidator *validator_code = new QRegExpValidator(code, this);

    //����
    QRegExp nam("^[a-zA-Z0-9_\u4e00-\u9fa5\\w]{1,10}$");
    QRegExpValidator *validator_nam = new QRegExpValidator(nam, this);


    ui->lineEdit->setValidator(validator_nam);
    ui->lineEdit_2->setValidator(validator_code);

}

LoginWindow::~LoginWindow()             //��������
{
    delete ui;
}


void LoginWindow::Login()
{
    QString ACCOUNT = ui->lineEdit->text();
    QString CODE = ui->lineEdit_2->text();

    QSqlQuery sql_query(myDatabase.database);
    QString sele_sql = "select CODE from MANAGER_INFORMATION where MANAGER_INFORMATION.ACCOUNT = '"+ACCOUNT+"'";

    sql_query.exec(sele_sql);
    sql_query.next();

    bool ok;
    QString N_CODE = sql_query.value(0).toString();
    if(N_CODE ==  CODE)
    {
        this->close();
        mainwindow.show();
    }
    else
    {
        QMessageBox::warning(this,"", u8"�û������������");
        ui->lineEdit_2->setText("");

    }


}


void LoginWindow::Regist()
{
    registwindow.show();
    this->close();
}
