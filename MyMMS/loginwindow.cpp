#include "loginwindow.h"
#include "ui_loginwindow.h"

//登录界面构造函数
LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    ui->setupUi(this);
    setWindowTitle(u8"会员管理系统");       //设置窗口名称
    connect(ui->pushButton,&QPushButton::clicked,this,&LoginWindow::Login);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&LoginWindow::Regist);

    //密码
    QRegExp code("^[a-zA-Z0-9~!@#$%^&*()_+-=;:,./<>?`]{6,16}$");
    QRegExpValidator *validator_code = new QRegExpValidator(code, this);

    //名称
    QRegExp nam("^[a-zA-Z0-9_\u4e00-\u9fa5\\w]{1,10}$");
    QRegExpValidator *validator_nam = new QRegExpValidator(nam, this);


    ui->lineEdit->setValidator(validator_nam);
    ui->lineEdit_2->setValidator(validator_code);

}

LoginWindow::~LoginWindow()             //析构函数
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
        QMessageBox::warning(this,"", u8"用户名或密码错误！");
        ui->lineEdit_2->setText("");

    }


}


void LoginWindow::Regist()
{
    registwindow.show();
    this->close();
}
