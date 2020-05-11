#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    myDatabase.CheckOpen();
    ui->setupUi(this);
    setWindowTitle(u8"会员管理系统");

    /*-----------------------------------------*/
    ui->tableView_5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_5->verticalHeader()->hide();
    ui->tableView_7->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_7->verticalHeader()->hide();
    ui->tableView_6->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_6->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->hide();
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_2->verticalHeader()->hide();
    ui->tableView_17->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_17->verticalHeader()->hide();
    ui->tableView_10->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_10->verticalHeader()->hide();
    ui->tableView_11->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_11->verticalHeader()->hide();
    ui->tableView_43->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_43->verticalHeader()->hide();
    ui->tableView_44->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_44->verticalHeader()->hide();
    ui->tableView_9->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_9->verticalHeader()->hide();

    /*---------------------------------------*/
    int i = 0;
    foreach(auto b,ui->buttonGroup->buttons())  //л
    {
        ui->buttonGroup->setId(b,i);i++;        //лID
        connect(b,&QPushButton::clicked,this,&MainWindow::norSetCurrentIndex);          //л水
    }
    connect(ui->tabWidget,&QTabWidget::currentChanged,this,&MainWindow::tabSetchecked); //tabал
    connect(ui->pushButton_20,&QPushButton::clicked,this,&MainWindow::SubCardInfo);   //
    connect(ui->pushButton_20,&QPushButton::clicked,this,&MainWindow::SubMemberInfo);   //
    connect(ui->pushButton_45,&QPushButton::clicked,this,&MainWindow::SubProductInfo);   //

    /*--------------------------------------------*/
    connect(ui->pushButton_30,&QPushButton::clicked,this,&MainWindow::FindMember);   //
    connect(ui->pushButton_33,&QPushButton::clicked,this,&MainWindow::FindProduct);   //
    connect(ui->pushButton_24,&QPushButton::clicked,this,&MainWindow::FindPayCard);   //
    connect(ui->pushButton_25,&QPushButton::clicked,this,&MainWindow::UpdateCard);   //
    connect(ui->pushButton_19,&QPushButton::clicked,this,&MainWindow::FindTheMember);   //
    connect(ui->pushButton_21,&QPushButton::clicked,this,&MainWindow::FindComMem);   //
    connect(ui->pushButton_22,&QPushButton::clicked,this,&MainWindow::FindComPro);   //
    connect(ui->pushButton_23,&QPushButton::clicked,this,&MainWindow::Purchase);   //
    connect(ui->pushButton_84,&QPushButton::clicked,this,&MainWindow::FindGitfMem);   //
    connect(ui->pushButton_85,&QPushButton::clicked,this,&MainWindow::FindTheGift);   //
    connect(ui->pushButton_86,&QPushButton::clicked,this,&MainWindow::Conversion);   //

    connect(ui->pushButton_71,&QPushButton::clicked,this,&MainWindow::FindDiscount);   //
    connect(ui->pushButton_72,&QPushButton::clicked,this,&MainWindow::FindActivity);   //
    connect(ui->pushButton_37,&QPushButton::clicked,this,&MainWindow::FindGift);   //

    connect(ui->pushButton_32,&QPushButton::clicked,this,&MainWindow::deletMemRow);   //
    connect(ui->pushButton_80,&QPushButton::clicked,this,&MainWindow::deletLevRow);   //
    connect(ui->pushButton_81,&QPushButton::clicked,this,&MainWindow::deletProRow);   //
    connect(ui->pushButton_83,&QPushButton::clicked,this,&MainWindow::deletDisRow);   //
    connect(ui->pushButton_87,&QPushButton::clicked,this,&MainWindow::deletActRow);   //
    connect(ui->pushButton_88,&QPushButton::clicked,this,&MainWindow::deletGifRow);   //


    connect(ui->tableView_5,&QTableView::clicked,this,&MainWindow::GetmemTableCurrentrow);   //
    connect(ui->tableView_6,&QTableView::clicked,this,&MainWindow::GetlevTableCurrentrow);   //
    connect(ui->tableView_7,&QTableView::clicked,this,&MainWindow::GetproTableCurrentrow);   //
    connect(ui->tableView_17,&QTableView::clicked,this,&MainWindow::GetdisTableCurrentrow);   //
    connect(ui->tableView_10,&QTableView::clicked,this,&MainWindow::GetactTableCurrentrow);   //
    connect(ui->tableView_11,&QTableView::clicked,this,&MainWindow::GetgifTableCurrentrow);   //


    /*---------------------------------------------*/
    int j = 0;
    foreach(auto c,ui->buttonGroup_2->buttons())  //
    {
        ui->buttonGroup_2->setId(c,j);j++;        //ID
        connect(c,&QPushButton::clicked,this,&MainWindow::setTableEdit);          //
    }


    /*---------------------------------------*/
    ShowMemList();
    ShowProList();
    ShowLevList();
    ShowComList();
    ShowTemProList();
    ShowDiscList();
    ShowActList();
    ShowGiftList();
    ShowTemGiftList();
    ShowClassList();


    /*---------------------------*/
    ChangeComb(ui->comboBox_4,"LEVEL_INFORMATION");
    ChangeComb(ui->comboBox_5,"DISCOUNT_INFORMATION");
    ChangeComb(ui->comboBox_6,"ACTIVITY_INFORMATION");

    SetFormat();
}


//
MainWindow::~MainWindow()
{
    delete ui;
}

//ж
int MainWindow::isDigitStr(QString src)
{
    QByteArray ba = src.toLatin1();//QString  char*
     const char *s = ba.data();

    while(*s && *s>='0' && *s<='9') s++;

    if (*s)
    { //
        return -1;
    }
    else
    { //
        return 0;
    }
}


//修改后提交
void MainWindow::Submit(QTableView *tableview)
{

    QSqlTableModel *pMode = new QSqlTableModel(this, myDatabase.database);
    pMode = dynamic_cast<QSqlTableModel *>(ui->tableView_5->model());
    pMode->database().transaction(); //
    if (pMode->submitAll()) // б
    {
        pMode->database().commit(); //
        qDebug()<< pMode->lastError();
    } else {
        pMode->database().rollback(); //
        qDebug()<<pMode->lastError().text();
        QMessageBox::warning(this, tr("tableModel"),tr(u8": 数据库错误%1").arg(pMode->lastError().text()));
    }

    tableview->setEditTriggers ( QAbstractItemView::NoEditTriggers );
    tableview->setSelectionMode ( QAbstractItemView::SingleSelection );
    tableview->setSelectionBehavior( QAbstractItemView::SelectRows );

    tableview->clearSelection();
}


//切换页面
void MainWindow::norSetCurrentIndex()
{
    int id = ui->buttonGroup->checkedId();  //е

    switch (id)
    {
    case 0:ui->stackedWidget->setCurrentIndex(2);break;
    case 1:ui->stackedWidget->setCurrentIndex(3);break;
    case 2:ui->stackedWidget->setCurrentIndex(4);break;
    case 3:ui->stackedWidget->setCurrentIndex(1);break;
    case 4:ui->stackedWidget->setCurrentIndex(5);break;
    case 5:ui->stackedWidget->setCurrentIndex(0);break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:ui->stackedWidget->setCurrentIndex(id);break;
    //case 13:
    default:ui->stackedWidget->setCurrentIndex(id-13);break;
    }
}

//设置修改表格
void MainWindow::setTableEdit()
{
    int id = ui->buttonGroup_2->checkedId();  //е
    qDebug()<< id;
    switch (id)
    {
    case 0:
        ui->tableView_5->setEditTriggers ( QAbstractItemView::DoubleClicked );
        ui->tableView_5->setSelectionMode ( QAbstractItemView::SingleSelection );
        ui->tableView_5->setSelectionBehavior( QAbstractItemView::SelectItems );

        break;
    case 1:
    {   Submit(ui->tableView_5);
        break;
    }
    case 2:
        ui->tableView_6->setEditTriggers ( QAbstractItemView::DoubleClicked );
        ui->tableView_6->setSelectionMode ( QAbstractItemView::SingleSelection );
        ui->tableView_6->setSelectionBehavior( QAbstractItemView::SelectItems );

        break;

    case 3:
        Submit(ui->tableView_6);
        ChangeComb(ui->comboBox_4,"LEVEL_INFORMATION");
        break;
    case 4:
    {
        newlevel.exec();
        ShowLevList();
        ChangeComb(ui->comboBox_4,"LEVEL_INFORMATION");
        break;
    }
    case 5:
        ui->tableView_7->setEditTriggers ( QAbstractItemView::DoubleClicked );
        ui->tableView_7->setSelectionMode ( QAbstractItemView::SingleSelection );
        ui->tableView_7->setSelectionBehavior( QAbstractItemView::SelectItems );

        break;

    case 6:
        Submit(ui->tableView_7);
        break;
    case 7:
        ui->tableView_9->setEditTriggers ( QAbstractItemView::DoubleClicked );
        ui->tableView_9->setSelectionMode ( QAbstractItemView::SingleSelection );
        ui->tableView_9->setSelectionBehavior( QAbstractItemView::SelectItems );

        break;

    case 8:break;
    case 9:
        Submit(ui->tableView_9);
        break;
    case 10:
        ui->tableView_17->setEditTriggers ( QAbstractItemView::DoubleClicked );
        ui->tableView_17->setSelectionMode ( QAbstractItemView::SingleSelection );
        ui->tableView_17->setSelectionBehavior( QAbstractItemView::SelectItems );

        break;

    case 11:
    {
         newDiscount.exec();
         ShowDiscList();
         ChangeComb(ui->comboBox_5,"DISCOUNT_INFORMATION");
         break;

    }
    case 12:
        Submit(ui->tableView_17);
        ChangeComb(ui->comboBox_5,"DISCOUNT_INFORMATION");
        break;
    case 13:

        ui->tableView_10->setEditTriggers ( QAbstractItemView::DoubleClicked );
        ui->tableView_10->setSelectionMode ( QAbstractItemView::SingleSelection );
        ui->tableView_10->setSelectionBehavior( QAbstractItemView::SelectItems );

        break;
    case 14:
    {
        newActivity.exec();
        ShowActList();
        ChangeComb(ui->comboBox_6,"ACTIVITY_INFORMATION");
        break;
    }
    case 15:
        Submit(ui->tableView_10);
        ChangeComb(ui->comboBox_6,"ACTIVITY_INFORMATION");
        break;
    case 16:
    {
        newGift.exec();
        ShowGiftList();
        break;
    }
    case 17:
        Submit(ui->tableView_11);
        break;
    case 18:
        ui->tableView_11->setEditTriggers ( QAbstractItemView::DoubleClicked );
        ui->tableView_11->setSelectionMode ( QAbstractItemView::SingleSelection );
        ui->tableView_11->setSelectionBehavior( QAbstractItemView::SelectItems );

        break;

    default:ui->stackedWidget->setCurrentIndex(id-13);break;
    }



}

//切换tab页
void MainWindow::tabSetchecked()
{

    int n = ui->tabWidget->currentIndex();  //tab
    switch (n)
    {
    case 0:ui->pushButton->click();break;
    case 1:ui->pushButton_7->click();break;
    case 2:ui->pushButton_10->click();break;
    case 3:ui->pushButton_16->click();break;
    default:break;
    }
}

//设置输入框格式
void MainWindow::SetFormat()
{
    //11位整数
    QRegExp num("[0-9]{11}$");
    QRegExpValidator *validator_num = new QRegExpValidator(num, this);

    //邮箱
    QRegExp emi("^([a-zA-Z0-9]+[_|\_|\.]?)*[a-zA-Z0-9]+@([a-zA-Z0-9]+[_|\_|\.]?)*[a-zA-Z0-9]+\.[a-zA-Z]{2,3}$");
    QRegExpValidator *validator_emi = new QRegExpValidator(emi, this);

    //正整数
    QRegExp inte("^[0-9]*$");
    QRegExpValidator *validator_inte = new QRegExpValidator(inte, this);

    //正实数
    QRegExp real("^[0-9]+(.[0-9]{1,3})?$");
    QRegExpValidator *validator_real = new QRegExpValidator(real, this);

    //密码
    QRegExp code("^[a-zA-Z0-9~!@#$%^&*()_+-=;:,./<>?`]{6,16}$");
    QRegExpValidator *validator_code = new QRegExpValidator(code, this);

    //名称
    QRegExp nam("^[a-zA-Z0-9_\u4e00-\u9fa5\\w]{1,10}$");
    QRegExpValidator *validator_nam = new QRegExpValidator(nam, this);


    //设置格式
    ui->lineEdit_28->setValidator(validator_num);
    ui->lineEdit_29->setValidator(validator_nam);
    ui->lineEdit_25->setValidator(validator_num);
    ui->lineEdit_30->setValidator(validator_num);
    ui->lineEdit_24->setValidator(validator_emi);
    ui->lineEdit_16->setValidator(validator_code);
    ui->lineEdit_17->setValidator(validator_code);
    ui->lineEdit_13->setValidator(validator_num);
    ui->lineEdit_26->setValidator(validator_nam);
    ui->lineEdit_18->setValidator(validator_num);
    ui->lineEdit_40->setValidator(validator_real);
    ui->lineEdit_39->setValidator(validator_real);
    ui->lineEdit_23->setValidator(validator_inte);
    ui->lineEdit_139->setValidator(validator_num);
    ui->lineEdit_140->setValidator(validator_num);
    ui->lineEdit_32->setValidator(validator_nam);
    ui->lineEdit_61->setValidator(validator_num);
    ui->lineEdit_62->setValidator(validator_nam);
    ui->lineEdit_59->setValidator(validator_inte);
    ui->lineEdit_57->setValidator(validator_real);
    ui->lineEdit_58->setValidator(validator_real);
    ui->lineEdit_60->setValidator(validator_inte);
    ui->lineEdit_35->setValidator(validator_nam);
    ui->lineEdit_46->setValidator(validator_num);
    ui->lineEdit->setValidator(validator_num);
}


/*----------------会员卡充值-------------------------*/
//提交会员信息
void MainWindow:: SubMemberInfo()
{


    if(ui->lineEdit_28->text().isEmpty())
    {
        QMessageBox::warning(this,"", u8"请输入会员ID");

    }
    else if (ui->lineEdit_29->text().isEmpty()) {
        QMessageBox::warning(this,"", u8"请输入会员名");

    }
    else if (ui->lineEdit_25->text().isEmpty()) {
        QMessageBox::warning(this,"", u8"请输入卡号");

    }
    else if (ui->lineEdit_30->text().isEmpty()) {
        QMessageBox::warning(this,"", u8"请输入电话号码");

    }
    else if (ui->lineEdit_16->text().isEmpty()) {
        QMessageBox::warning(this,"", u8"请输入密码");

    }
    else if (ui->lineEdit_17->text().isEmpty()) {
        QMessageBox::warning(this,"", u8"请确认密码");

    }
    else {

        bool ok;
        int VIP_ID = ui->lineEdit_28->text().toInt(&ok,10);             //会员id
        QString VIP_NAME= ui->lineEdit_29->text();                      //会员名
        int CARD_NUMBER = ui->lineEdit_25->text().toInt(&ok,10);        //卡号
        int TELEPHON = ui->lineEdit_30->text().toInt(&ok,10);          //电话号
        QString EMAIL= ui->lineEdit_24->text();                         //邮箱
        QString CODE= ui->lineEdit_16->text();                          //密码
        QString reCODE = ui->lineEdit_17->text();                       //确认密码
        QString SEX;                                                    //性别

        if(CODE != reCODE)
        {
            QMessageBox::warning(this,"", u8"两次输入的密码不一致！");

        }
        else
        {
            if(ui->radioButton->isChecked()==true)
            {
                SEX = "\347\224\267";
            }
            else if(ui->radioButton_2->isChecked()==true)
            {
                SEX="\345\245\263";
            }
                                                                    //生日
            QString year = ui->comboBox->currentText();             //年
            QString month = ui->comboBox_2->currentText();          //月
            QString day = ui->comboBox_3->currentText();            //日
            QString DATE_OF_BIRTH = year+"\345\271\264"+month+"\346\234\210"+day+"\346\227\245";

            QString LEVEL= ui->comboBox_4->currentText();           //会员等级




            myDatabase.InsertVIP_INFO(VIP_ID, CARD_NUMBER,VIP_NAME, //插入会员表
                CODE,SEX,DATE_OF_BIRTH,TELEPHON,EMAIL,LEVEL);

            //清空所有输入
            ui->lineEdit_28->setText("");
            ui->lineEdit_29->setText("");
            ui->lineEdit_25->setText("");
            ui->lineEdit_30->setText("");
            ui->lineEdit_24->setText("");
            ui->lineEdit_16->setText("");
            ui->lineEdit_17->setText("");
            ui->radioButton->setChecked(true);
            ui->comboBox->setCurrentText(0);
            ui->comboBox_2->setCurrentText(0);
            ui->comboBox_3->setCurrentText(0);
            ui->comboBox_4->setCurrentText(0);
            ShowMemList();
        }


    }

}

//补充会员卡信息
void MainWindow:: SubCardInfo()
{


    bool ok;
    int CARD_NUMBER = ui->lineEdit_25->text().toInt(&ok,10);        //卡号
    QString CODE= ui->lineEdit_16->text();                          //密码
    double BALANCE = 0;
    int INTEGRAL=0;
    QString STATE = "\346\255\243\345\270\270";                     //卡状态
    QString REGISTER_TIME = QDate::currentDate().toString("yyyy\345\271\264MM\346\234\210dd\346\227\245");
    QString LEVEL= ui->comboBox_4->currentText();                   //会员等级
    QString REMARK = "";                                            //备注
    myDatabase.InsertCARD_INFO(CARD_NUMBER, CODE,BALANCE,           //插入会员卡表
                               INTEGRAL,STATE, REGISTER_TIME,
                                LEVEL,REMARK);



}

/*-----------------------------------------------------------*/






/*----------------------添加商品-------------------------------*/

//提交商品信息
void MainWindow:: SubProductInfo()
{


    if(ui->lineEdit_61->text().isEmpty())
    {
        QMessageBox::warning(this,"", u8"请输入商品编号");

    }
    else if (ui->lineEdit_62->text().isEmpty()) {
        QMessageBox::warning(this,"", u8"请输入商品名称");

    }
    else if (ui->lineEdit_59->text().isEmpty()) {
        QMessageBox::warning(this,"", u8"请输入剩余数量");

    }
    else if (ui->lineEdit_57->text().isEmpty()) {
        QMessageBox::warning(this,"", u8"请输入价格");

    }
    else {

        bool ok;
        int PRODUCT_NUMBER = ui->lineEdit_61->text().toInt(&ok,10);             //商品编号
        QString PRODUCT_NAME= ui->lineEdit_62->text();                          //商品名称
        int LEFT_NUMBER = ui->lineEdit_59->text().toInt(&ok,10);                //剩余数量
        double PRICE = ui->lineEdit_57->text().toDouble();                      //价格
        double COST= ui->lineEdit_58->text().toDouble();                        //成本

        QString CATEGORY = ui->comboBox_17->currentText();                      //类别

        int INTEGRAL_NUMBER;                                                    //积分
        if(ui->checkBox->isChecked()==true)                                     //选择是否可以积累积分
        {
            ui->lineEdit_60->setReadOnly(false);
            INTEGRAL_NUMBER = ui->lineEdit_60->text().toInt(&ok,10);
        }
        else
        {
            ui->lineEdit_60->setReadOnly(true);
            INTEGRAL_NUMBER = 0;
        }

        QString year = ui->comboBox_13->currentText();          //生产日期
        QString month = ui->comboBox_14->currentText();
        QString day = ui->comboBox_15->currentText();
        QString DATE_IN_PRODUCED = year+"\345\271\264"+month+"\346\234\210"+day+"\346\227\245";
        qDebug()<<DATE_IN_PRODUCED;

        //插入商品信息表
        myDatabase.InsertPRO_INFO(PRODUCT_NUMBER,PRODUCT_NAME,LEFT_NUMBER,
                                PRICE,COST,DATE_IN_PRODUCED,CATEGORY,
                                INTEGRAL_NUMBER);

        //清空输入信息
        ui->lineEdit_61->setText("");
        ui->lineEdit_62->setText("");
        ui->lineEdit_59->setText("");
        ui->lineEdit_57->setText("");
        ui->lineEdit_58->setText("");
        ui->lineEdit_60->setText("");
        ui->lineEdit_6->setText("");
        ui->comboBox_17->setCurrentText(0);
        ui->checkBox->setChecked(true);
        ui->comboBox_13->setCurrentText(0);
        ui->comboBox_14->setCurrentText(0);
        ui->comboBox_15->setCurrentText(0);
        ShowProList();
        ShowComList();
    }

}

/*-----------------------------------------------------------------------------*/










/*--------------------------------------------------------------------*/

//会员列表显示
void MainWindow::ShowMemList()
{



    QSqlTableModel *model = new QSqlTableModel(this,myDatabase.database);
    model->setTable("VIP_INFORMATION");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->removeColumn(3);         //从表中删除列
    model->removeColumn(6);
    model->removeColumn(7);

    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("会员ID"));	//设置表名
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("会员卡号"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("会员姓名"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("性别"));
    model->setHeaderData(4, Qt::Horizontal, QStringLiteral("生日"));
    model->setHeaderData(5, Qt::Horizontal, QStringLiteral("手机号"));
    model->setHeaderData(6, Qt::Horizontal, QStringLiteral("会员等级"));
    //model->setHeaderData(7, Qt::Horizontal, QStringLiteral(""));


    model->select();            //显示所有行


    qDebug()<< model->lastError();
    ui->tableView_5->setModel(model);


}





//产品列表显示
void MainWindow::ShowProList()
{


    QSqlTableModel *model = new QSqlTableModel;

    model = new QSqlTableModel(this,myDatabase.database);

    model->setTable("PRODUCT_INFORMATION");

    model->removeColumns(6,2);
    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("产品编号"));
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("产品名称"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("库存"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("价格"));
    model->setHeaderData(4, Qt::Horizontal, QStringLiteral("成本"));
    model->setHeaderData(5, Qt::Horizontal, QStringLiteral("生产日期"));

    model->select();

    ui->tableView_7->setModel(model);

}

//优惠券列表显示
void MainWindow::ShowDiscList()
{


    QSqlTableModel *model = new QSqlTableModel;

    model = new QSqlTableModel(this,myDatabase.database);
    model->setTable("DISCOUNT_INFORMATION");
    model->removeColumn(4);

    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("优惠券名称"));	//粻е
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("抵消金额"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("折扣额度"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("赠送积分"));

    model->select();

    ui->tableView_17->setModel(model);

}
//优惠活动列表显示
void MainWindow::ShowActList()
{


    QSqlTableModel *model = new QSqlTableModel;

    model = new QSqlTableModel(this,myDatabase.database);
    model->setTable("ACTIVITY_INFORMATION");
    model->removeColumn(4);

    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("活动名称"));	//粻е
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("抵消金额"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("折扣额度"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("赠送积分"));

    model->select();

    ui->tableView_10->setModel(model);

}


//消费商品列表显示
void MainWindow::ShowComList()
{


    QSqlQueryModel *model = new QSqlQueryModel;

    model = new QSqlTableModel(this,myDatabase.database);
    model->setQuery("SELECT PRODUCT_NUMBER,PRODUCT_NAME,LEFT_NUMBER,PRICE FROM PRODUCT_INFORMATION", myDatabase.database);	//dbsql, db

    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("产品编号"));	//粻е
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("产品名称"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("剩余数量"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("价格"));

    ui->tableView->setModel(model);


}

//会员等级列表显示
void MainWindow::ShowLevList()
{


    QSqlTableModel *model = new QSqlTableModel;

    model = new QSqlTableModel(this,myDatabase.database);
    model->setTable("LEVEL_INFORMATION");
    model->removeColumn(3);

    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("会员等级"));	//粻е
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("折扣额度"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("赠送积分"));

    model->select();

    ui->tableView_6->setModel(model);

}


//礼品列表显示
void MainWindow::ShowGiftList()
{


    QSqlTableModel *model = new QSqlTableModel;

    model = new QSqlTableModel(this,myDatabase.database);

    model->setTable("GIFT_INFORMATION");

    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("礼品编号"));	//粻е
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("礼品名称"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("剩余数量"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("兑换积分"));
    model->select();

    ui->tableView_11->setModel(model);
    ui->tableView_43->setModel(model);

}

//产品分类列表显示
void MainWindow::ShowClassList()
{
    QSqlTableModel *model = new QSqlTableModel;

    model = new QSqlTableModel(this,myDatabase.database);

    model->setTable("CLASS_INFORMATION");

    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("类别编号"));	//粻е
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("产品类别"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("应用场景"));
    model->select();

    ui->tableView_9->setModel(model);

}



//列表查找会员
void MainWindow::FindMember()
{

    QString input = ui->lineEdit_32->text();       //输入卡号或名称

    QSqlTableModel *model = new QSqlTableModel;     //
    model = new QSqlTableModel(this,myDatabase.database);
    model->setTable("VIP_INFORMATION");

    if(ui->lineEdit_32->text().isEmpty())
    {
        model->select();
    }
    else if(isDigitStr(input) == -1)
    {
        model->setFilter(QObject::tr("VIP_NAME = '%1'").arg(input)); //
    }
    else if(isDigitStr(input) == 0)
    {
        model->setFilter(QObject::tr("VIP_ID = '%1'").arg(input)); //
    }


    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("会员ID"));	//设置表名
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("会员卡号"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("会员姓名"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("性别"));
    model->setHeaderData(4, Qt::Horizontal, QStringLiteral("生日"));
    model->setHeaderData(5, Qt::Horizontal, QStringLiteral("手机号"));
    model->setHeaderData(6, Qt::Horizontal, QStringLiteral("会员等级"));
    model->removeColumn(3);
    model->removeColumn(6);
    model->removeColumn(7);
    model->select();

    ui->tableView_5->setModel(model);

}


//列表查找商品
void MainWindow::FindProduct()
{

    QString input = ui->lineEdit_35->text();       //

    QSqlTableModel *model = new QSqlTableModel;     //
    model = new QSqlTableModel(this,myDatabase.database);
    model->setTable("PRODUCT_INFORMATION");

    myDatabase.CheckOpen();                       //

    if(ui->lineEdit_35->text().isEmpty())
    {
        model->select();
    }
    else if(isDigitStr(input) == -1)
    {
        model->setFilter(QObject::tr("PRODUCT_NAME = '%1'").arg(input)); //
    }
    else if(isDigitStr(input) == 0)
    {
        model->setFilter(QObject::tr("PRODUCT_NUMBER = '%1'").arg(input)); //
    }
    model->removeColumns(6,2);
    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("产品编号"));
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("产品名称"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("库存"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("价格"));
    model->setHeaderData(4, Qt::Horizontal, QStringLiteral("成本"));
    model->setHeaderData(5, Qt::Horizontal, QStringLiteral("生产日期"));

    model->select();


    ui->tableView_7->setModel(model);

}



//列表查询优惠券
void MainWindow::FindDiscount()
{

    QString input = ui->lineEdit_55->text();       //

    QSqlTableModel *model = new QSqlTableModel;     //
    model = new QSqlTableModel(this,myDatabase.database);
    model->setTable("DISCOUNT_INFORMATION");

    myDatabase.CheckOpen();                       //

    if(ui->lineEdit_55->text().isEmpty())
    {
        model->select();
    }
    else
    {
        model->setFilter(QObject::tr("DISCOUNT_NAME = '%1'").arg(input)); //
        model->select();

    }

    model->removeColumn(4);

    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("优惠券名称"));	//粻е
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("抵消金额"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("折扣额度"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("赠送积分"));



    ui->tableView_17->setModel(model);

}


//列表查找优惠活动
void MainWindow::FindActivity()
{

    QString input = ui->lineEdit_56->text();       //

    QSqlTableModel *model = new QSqlTableModel;     //
    model = new QSqlTableModel(this,myDatabase.database);
    model->setTable("ACTIVITY_INFORMATION");

    //myDatabase.CheckOpen();                       //

    model->removeColumn(4);
    if(ui->lineEdit_56->text().isEmpty())
    {
        model->select();
    }
    else
    {

        model->setFilter(QObject::tr("ACTIVITY_NAME = '%1'").arg(input)); //
        model->select();

    }



    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("活动名称"));	//粻е
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("抵消金额"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("折扣额度"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("赠送积分"));



    ui->tableView_10->setModel(model);

}

//б
void MainWindow::FindGift()
{

    QString input = ui->lineEdit_46->text();       //

    QSqlTableModel *model = new QSqlTableModel;     //
    model = new QSqlTableModel(this,myDatabase.database);
    model->setTable("GIFT_INFORMATION");

    myDatabase.CheckOpen();                       //

    if(ui->lineEdit_46->text().isEmpty())
    {
        model->select();
    }
    else if(isDigitStr(input) == -1)
    {
        model->setFilter(QObject::tr("GITF_NAME = '%1'").arg(input)); //
    }
    else if(isDigitStr(input) == 0)
    {
        model->setFilter(QObject::tr("GIFT_NUMBER = '%1'").arg(input)); //
    }
    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("礼品编号"));	//粻е
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("礼品名称"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("剩余数量"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("兑换积分"));
    model->select();


    ui->tableView_11->setModel(model);

}
/*--------------------------------------------------------------*/







/*------------------会员信息查询----------------------------*/
//单独查询会员信息
void MainWindow::FindTheMember()
{
    QString vip_id = ui->lineEdit->text();
    QString card_num = ui->lineEdit_18->text();
    QSqlQuery sql_query(myDatabase.database);
    QString sele_sql = "select * from VIP_INFORMATION where VIP_INFORMATION.VIP_ID = '"+vip_id+"'";
    sql_query.exec(sele_sql);
    int jud = sql_query.next();
    if(jud == 1)
    {
        ui->lineEdit->setStyleSheet("QLineEdit{border-color:rgb(199, 199, 199)}");
        sele_sql = "select * from VIP_INFORMATION where VIP_INFORMATION.VIP_ID = '"+vip_id+"'";
        sql_query.exec(sele_sql);
        sql_query.next();
        //QString card_num =  sql_query.value(1).toString();
        //int value = sql_query.value();
        ui->lineEdit_2->setText(sql_query.value("CARD_NUMBER").toString());
        ui->lineEdit_3->setText(sql_query.value("VIP_NAME").toString());
        ui->lineEdit_4->setText(sql_query.value("VIP_ID").toString());
        ui->lineEdit_7->setText(sql_query.value("TELEPHONE").toString());
        ui->lineEdit_5->setText(sql_query.value("SEX").toString());
        ui->lineEdit_8->setText(sql_query.value("DATE_OF_BIRTH").toString());
        ui->lineEdit_6->setText(sql_query.value("EMAIL").toString());
        ui->lineEdit_12->setText(sql_query.value("LEVEL").toString());

        sele_sql = "select * from CARD_INFORMATION,VIP_INFORMATION where VIP_INFORMATION.VIP_ID = '"+vip_id+"' and CARD_INFORMATION.CARD_NUMBER = VIP_INFORMATION.CARD_NUMBER";
        sql_query.exec(sele_sql);
        sql_query.next();
        ui->lineEdit_9->setText(sql_query.value("CARD_INFORMATION.INTEGRAL").toString());
        ui->lineEdit_14->setText(sql_query.value("CARD_INFORMATION.BALANCE").toString());

        ui->lineEdit->setText("");

    }
    else
    {
        ui->lineEdit->setStyleSheet("QLineEdit{border-color:red }");
        ui->lineEdit->setText("");
    }

}
/*----------------------------------------------------------------*/





/*---------------------会员卡充值-----------------------------*/

//查询充值会员
void MainWindow::FindPayCard()
{
    QString card_num = ui->lineEdit_18->text();
    QSqlQuery sql_query(myDatabase.database);
    QString sele_sql = "select * from CARD_INFORMATION where CARD_INFORMATION.CARD_NUMBER = '"+card_num+"'";

    sql_query.exec(sele_sql);
    sql_query.next();

    bool ok;
    int jud = sql_query.value(0).toString().toInt(&ok,10);
    if(jud)
    {
        findCard = true;
        ui->lineEdit_18->setStyleSheet("QLineEdit{border-color:rgb(199, 199, 199)}");
    }
    else
    {
        findCard = false;
        ui->lineEdit_18->setStyleSheet("QLineEdit{border-color:red }");
        ui->lineEdit_18->setText("");
    }

}



//更新会员卡信息
void MainWindow::UpdateCard()
{



    if(findCard = true)
    {
        if(ui->lineEdit_40->text().isEmpty())
        {
            QMessageBox::warning(this,"", u8"");

        }
        else {

            bool ok;
            QString input = ui->lineEdit_18->text();                //输入卡号
            QSqlQuery sql_query(myDatabase.database);
            double PAYIN  = ui->lineEdit_40->text().toDouble();     //充值金额

            double GIVE;                                            //赠送金额
            if(ui->lineEdit_39->text().isEmpty())
            {
                GIVE = 0;
            }
            else
            {
                GIVE  = ui->lineEdit_39->text().toDouble();
            }
            double BALANCE  = PAYIN + GIVE;                         //总充值金额



            int INTEGRAL  = ui->lineEdit_23->text().toInt(&ok,10);  //赠送积分
            QString REMARK  = ui->textEdit->toPlainText();          //备注

            QString N_BALANCE = QString("%1").arg(BALANCE);
            QString N_INTEGRAL = QString("%1").arg(INTEGRAL);

            QString update_sql = "update CARD_INFORMATION set BALANCE =BALANCE+ '"+N_BALANCE+"',INTEGRAL='"+N_INTEGRAL+"',REMARK = :rem where CARD_INFORMATION.CARD_NUMBER = '"+input+"'";
            sql_query.prepare(update_sql);

            sql_query.bindValue(":balan", BALANCE);
            sql_query.bindValue(":integ", INTEGRAL);
            sql_query.bindValue(":rem", REMARK);
            if(!sql_query.exec())
            {
                qDebug() << sql_query.lastError();
            }
            else
            {
                qDebug() << "updated!";
            }
            ui->lineEdit_40->setText("");
            ui->lineEdit_39->setText("");
            ui->lineEdit_23->setText("");
            ui->textEdit->setText("");
            ui->lineEdit_18->setText("");

            findCard = false;
        }



    }

}

/*---------------------------------------------------------------*/






/*--------------------产品消费---------------------------*/

//查询消费会员
void MainWindow::FindComMem()
{
    QString vip_id = ui->lineEdit_13->text();
    QSqlQuery sql_query(myDatabase.database);
    QString sele_sql = "select * from VIP_INFORMATION where VIP_INFORMATION.VIP_ID = '"+vip_id+"'";

    sql_query.exec(sele_sql);
    int jud = sql_query.next();
    if(jud == 1)
    {
        findComMem = true;
        ui->lineEdit_13->setStyleSheet("QLineEdit{border-color:rgb(199, 199, 199)}");
        //ui->lineEdit_18->setText("");
    }
    else
    {
        findComMem = false;
        ui->lineEdit_13->setStyleSheet("QLineEdit{border-color:red }");
        ui->lineEdit_13->setText("");
    }
}


//查询消费商品
void MainWindow::FindComPro()
{
    if(findComMem = true)
    {
        bool ok;
        QString input = ui->lineEdit_26->text();       //
        QSqlQuery sql_query(myDatabase.database);

        QString sele_sql = "select * from PRODUCT_INFORMATION where PRODUCT_INFORMATION.PRODUCT_NUMBER = '"+input+"'";

        sql_query.exec(sele_sql);
        int jud = sql_query.next();
        if(jud == 1)
        {
            bool ok;
            ui->lineEdit_26->setStyleSheet("QLineEdit{border-color:rgb(199, 199, 199)}");

            /*QString  str_query = "select * from PRODUCT_INFORMATION where PRODUCT_INFORMATION.PRODUCT_NUMBER = '"+input+"'";

            sql_query.exec(str_query);
            sql_query.next();*/
            //QString card_num =  sql_query.value(1).toString();
            //int value = sql_query.value();
            int PRODUCT_NUMBER = sql_query.value("PRODUCT_NUMBER").toString().toInt(&ok,10);
            QString PRODUCT_NAME = sql_query.value("PRODUCT_NAME").toString();
            double PRICE = sql_query.value("PRICE").toString().toDouble();
            QString CATEGORY = sql_query.value("CATEGORY").toString();
            int INTEGRAL_NUMBER = sql_query.value("INTEGRAL_NUMBER").toString().toInt(&ok,10);

            ui->lineEdit->setText("");

            myDatabase.InsertTEMP_INFO(PRODUCT_NUMBER,PRODUCT_NAME,
                                         PRICE, CATEGORY,INTEGRAL_NUMBER,0);
            ShowTemProList();

        }
        else
        {
            ui->lineEdit_26->setStyleSheet("QLineEdit{border-color:red }");
            ui->lineEdit_26->setText("");
        }

        findComMem = false;

    }

}

//展示消费记录表
void MainWindow::ShowTemProList()
{


    QSqlQueryModel *model = new QSqlQueryModel;

    model = new QSqlTableModel(this,myDatabase.database);
    model->setQuery("SELECT NUMBER,NAME,PRICE,CATEGORY,INTEGRAL_NUMBER FROM TEMP_INFORMATION", myDatabase.database);	//dbsql, db

    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("产品编号"));	//粻е
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("产品名称"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("价格"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("产品类别"));
    model->setHeaderData(4, Qt::Horizontal, QStringLiteral("赠送积分"));

    ui->tableView_2->setModel(model);

}

//消费结算
void MainWindow::Purchase()
{
    bool ok;

    QString vip_id = ui->lineEdit_13->text();

    QSqlQuery sql_query(myDatabase.database);


    QString sele_sql = "select SUM(PRICE),SUM(INTEGRAL_NUMBER) from TEMP_INFORMATION";        //查询计算综合积分和价格
    sql_query.exec(sele_sql);
    sql_query.next();
    double BALANCE = sql_query.value(0).toString().toDouble();
    int INTEGRAL = sql_query.value(1).toString().toInt(&ok,10);


    sele_sql = "select  COUNT(*) from TEMP_INFORMATION ";                   //查询是否添加商品
    sql_query.exec(sele_sql);
    sql_query.next();
    int jud = sql_query.value(0).toString().toInt(&ok,10);


    if(jud != 0)                                                        //若添加商品继续操作
    {

        MyResult r= CaculateResult();


        sele_sql = "select CARD_NUMBER,VIP_NAME from VIP_INFORMATION where VIP_INFORMATION.VIP_ID = '"+vip_id+"'";        //活动卡号和会员姓名
        sql_query.exec(sele_sql);
        sql_query.next();

        qDebug()<<sql_query.lastError();
        QString CARD_NUMBER = sql_query.value(0).toString();
        QString VIP_NUMBER = sql_query.value(1).toString().toUtf8();

        sele_sql = "select BALANCE from CARD_INFORMATION where CARD_INFORMATION.CARD_NUMBER = '"+CARD_NUMBER+"'";        //获得余额
        sql_query.exec(sele_sql);
        sql_query.next();
        double NOW_BALANCE = sql_query.value(0).toString().toDouble();



        if(r.sum>NOW_BALANCE)                        //当总价格大于余额则提醒
        {
            QMessageBox::warning(this,"", u8"用户"+VIP_NUMBER+u8"的余额不足");
        }

        else {

            QString L_BALANCE =  QString("%1").arg(BALANCE - r.sum);

            QString L_INTEGRAL =  QString("%1").arg(INTEGRAL + r.integral);

            //更新积分和余额
            QString update_sql = "update CARD_INFORMATION set BALANCE = '"+L_BALANCE+"',INTEGRAL= '"+L_INTEGRAL+"' where   CARD_INFORMATION.CARD_NUMBER = '"+CARD_NUMBER+"'";
            sql_query.prepare(update_sql);
            if(!sql_query.exec())
            {
                qDebug() << sql_query.lastError();
            }
            else
            {
                qDebug() << "update!";
            }

            QMessageBox::about(this, u8"", u8"用户"+VIP_NUMBER+u8"的余额为"+L_BALANCE+u8",积分为"+L_INTEGRAL);
        }

        QString dele_sql = "delete from TEMP_INFORMATION ";                                                     //删除表中数据
        sql_query.prepare(dele_sql);

        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "delete!";
        }

        ShowTemProList();                                                                                        //刷新表并清空输入

        ui->lineEdit_13->setText("");
        ui->lineEdit_26->setText("");

    }


}

//结算金额和积分
MyResult  MainWindow::CaculateResult( )
{
    bool ok;

    MyResult r;

    QSqlQuery sql_query(myDatabase.database);
    QString sele_sql = "select SUM(PRICE),SUM(INTEGRAL_NUMBER) from TEMP_INFORMATION";        //获得总金额和积分
    sql_query.exec(sele_sql);
    sql_query.next();
    double BALANCE = sql_query.value(0).toString().toDouble();
    int INTEGRAL = sql_query.value(1).toString().toInt(&ok,10);

    QString DISCOUNT_NAME = ui->comboBox_5->currentText();
    QString ACTIVITY_NAME = ui->comboBox_6->currentText();

    sele_sql = "select * from DISCOUNT_INFORMATION where DISCOUNT_INFORMATION.DISCOUNT_NAME = '"+ DISCOUNT_NAME +"'";
    sql_query.exec(sele_sql);
    sql_query.next();
    double DIS_MONEY = sql_query.value("MONEY").toString().toDouble();
    double DIS_DISCOUN = sql_query.value("DISCOUN").toString().toDouble();
    int DIS_INTEGRAL_NUMBER = sql_query.value("INTEGRAL_NUMBER").toString().toInt(&ok,10);

    sele_sql = "select * from ACTIVITY_INFORMATION where ACTIVITY_INFORMATION.ACTIVITY_NAME = '"+ ACTIVITY_NAME +"'";
    sql_query.exec(sele_sql);
    sql_query.next();
    double ACT_MONEY = sql_query.value("MONEY").toString().toDouble();
    double ACT_DISCOUN = sql_query.value("DISCOUN").toString().toDouble();
    int ACT_INTEGRAL_NUMBER = sql_query.value("INTEGRAL_NUMBER").toString().toInt(&ok,10);

    double n_sum = BALANCE * DIS_DISCOUN *ACT_DISCOUN - DIS_MONEY - ACT_MONEY;
    int n_inte =  INTEGRAL + DIS_INTEGRAL_NUMBER + ACT_INTEGRAL_NUMBER;
    r.sum = n_sum;
    r.integral = n_inte;

    return r;
}

/*-------------------------------------------------------------*/






/*-------------------兑换礼品---------------------------*/

//查询兑换礼品会员
void MainWindow::FindGitfMem()
{
    QString vip_id = ui->lineEdit_139->text();
    QSqlQuery sql_query(myDatabase.database);
    QString sele_sql = "select * from VIP_INFORMATION where VIP_INFORMATION.VIP_ID = '"+vip_id+"'";

    sql_query.exec(sele_sql);
    int jud = sql_query.next();
    if(jud == 1)
    {
        findGiftMem = true;
        ui->lineEdit_139->setStyleSheet("QLineEdit{border-color:rgb(199, 199, 199)}");
    }
    else
    {
        findGiftMem = false;
        ui->lineEdit_139->setStyleSheet("QLineEdit{border-color:red }");
        ui->lineEdit_139->setText("");
    }
}


//查询要兑换的礼品
void MainWindow::FindTheGift()
{
    if(findGiftMem = true)
    {
        bool ok;
        QString input = ui->lineEdit_140->text();       //
        QSqlQuery sql_query(myDatabase.database);

        QString sele_sql = "select * from GIFT_INFORMATION where GIFT_INFORMATION.GIFT_NUMBER = '"+input+"'";


        sql_query.exec(sele_sql);
        int jud = sql_query.next();
        if(jud == 1)
        {


            bool ok;
            ui->lineEdit_140->setStyleSheet("QLineEdit{border-color:rgb(199, 199, 199)}");

            int GIFT_NUMBER = sql_query.value("GIFT_NUMBER").toString().toInt(&ok,10);
            QString GITF_NAME = sql_query.value("GITF_NAME").toString();
            int LEFT_NUMBER = sql_query.value("LEFT_NUMBER").toString().toInt(&ok,10);
            int INTEGRAL_NUMBER = sql_query.value("INTEGRAL_NUMBER").toString().toInt(&ok,10);

            ui->lineEdit->setText("");

            myDatabase.InsertTEMP_INFO(GIFT_NUMBER,GITF_NAME,
                                       0, "",INTEGRAL_NUMBER,LEFT_NUMBER);
            ShowTemGiftList();

        }
        else
        {
            ui->lineEdit_140->setStyleSheet("QLineEdit{border-color:red }");
            ui->lineEdit_140->setText("");
        }

        findGiftMem = false;

    }

}

//兑换礼品清单显示
void MainWindow::ShowTemGiftList()
{




    QSqlQueryModel *model = new QSqlQueryModel;

    model = new QSqlTableModel(this,myDatabase.database);
    model->setQuery("SELECT  NUMBER,NAME,INTEGRAL_NUMBER,MOUNT FROM TEMP_INFORMATION", myDatabase.database);	//dbsql, db

    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("礼品编号"));	//粻е
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("礼品名称"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("剩余数量"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("兑换积分"));

    ui->tableView_44->setModel(model);

}

//
void MainWindow::Conversion()
{
    bool ok;

    QString vip_id = ui->lineEdit_139->text();

    QSqlQuery sql_query(myDatabase.database);



    QString sele_sql = "select  COUNT(*) from TEMP_INFORMATION ";       //ж
    sql_query.exec(sele_sql);
    sql_query.next();
    int jud = sql_query.value(0).toString().toInt(&ok,10);
    int a = 1;
    if(jud != 0)                                                        //в
    {

        bool ok;

        sele_sql = "select SUM(INTEGRAL_NUMBER) from TEMP_INFORMATION";        //
        sql_query.exec(sele_sql);
        sql_query.next();
        QString INTEGRAL = sql_query.value(0).toString();

        sele_sql = "select INTEGRAL from CARD_INFORMATION";        //
        sql_query.exec(sele_sql);
        sql_query.next();
        QString NOW_INTEGRAL = sql_query.value(0).toString();

        sele_sql = "select CARD_NUMBER,VIP_NAME from VIP_INFORMATION where VIP_INFORMATION.VIP_ID = '"+vip_id+"'";        //
        sql_query.exec(sele_sql);
        sql_query.next();
        QString CARD_NUMBER = sql_query.value(0).toString();
        QString VIP_NAME = sql_query.value(1).toString().toUtf8();


        if(INTEGRAL.toInt(&ok,10)> NOW_INTEGRAL.toInt(&ok,10))                        //
        {
            QMessageBox::warning(this,"", u8"用户"+VIP_NAME+u8"的积分不足");
        }

        else {


                                                                                                                //
        QString update_sql = "update CARD_INFORMATION set INTEGRAL=INTEGRAL - '"+INTEGRAL+"' where   CARD_INFORMATION.CARD_NUMBER = '"+CARD_NUMBER+"'";
        sql_query.prepare(update_sql);
        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "update!";
        }                                                                      //

        }


        QString dele_sql =  "delete from TEMP_INFORMATION ";                                                  //
        sql_query.prepare(dele_sql);

        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "delete!";
        }

        myDatabase.CreateTables();                                                                               //
        ShowTemGiftList();                                                                                        //

        ui->lineEdit_139->setText("");
        ui->lineEdit_140->setText("");
    }

}

/*-------------------------------------------------------------*/

//
void MainWindow::ChangeComb(QComboBox *combobox,QString tablename)
{

    bool ok;


    QSqlQuery sql_query(myDatabase.database);
    QString sele_sql = "SELECT COUNT(*) FROM '"+tablename+"'";
    sql_query.exec(sele_sql);
    sql_query.next();

    int n = sql_query.value(0).toString().toInt(&ok,10);

    combobox->clear();

    for(int i = 0;i<n;i++)
    {
        QString index =  QString("%1").arg(i);
        sele_sql = "SELECT * FROM '"+tablename+"'where '"+tablename+"'.INDEX_ROW = '"+index+"'";
        sql_query.exec(sele_sql);
        sql_query.next();
        QString item = sql_query.value(0).toString();
        combobox->addItem(item);
    }

}



/*---------------------------------------------------------------*/
//
void MainWindow:: GetmemTableCurrentrow()
{
    memTableCurrentrow = ui->tableView_5->currentIndex().row();
}

void MainWindow:: GetlevTableCurrentrow()
{
    levTableCurrentrow = ui->tableView_6->currentIndex().row();
}

void MainWindow:: GetproTableCurrentrow()
{
    proTableCurrentrow = ui->tableView_7->currentIndex().row();
}

void MainWindow:: GetdisTableCurrentrow()
{
    disTableCurrentrow = ui->tableView_17->currentIndex().row();
}



void MainWindow:: GetactTableCurrentrow()
{
    actTableCurrentrow = ui->tableView_10->currentIndex().row();
}


void MainWindow:: GetgifTableCurrentrow()
{
    gifTableCurrentrow = ui->tableView_11->currentIndex().row();
}
/*----------------------------------------------------*/



/*----------------------------------------------------*/
//
void MainWindow::deletMemRow()
{


    QSqlTableModel *model = new QSqlTableModel(this,myDatabase.database);
    model->setTable("VIP_INFORMATION");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->removeColumn(3);
    model->removeColumn(6);
    model->removeColumn(7);

    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("会员ID"));	//设置表名
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("会员卡号"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("会员姓名"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("性别"));
    model->setHeaderData(4, Qt::Horizontal, QStringLiteral("生日"));
    model->setHeaderData(5, Qt::Horizontal, QStringLiteral("手机号"));
    model->setHeaderData(6, Qt::Horizontal, QStringLiteral("会员等级"));

    model->select();


    ui->tableView_5->setModel(model);

    qDebug()<<u8""<<memTableCurrentrow;

    //
    int ok = QMessageBox::warning(this,tr(u8""),tr(u8"是否删除此行！"),
    QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
    model->revertAll();//
    }
    else
    {
        model->removeRow(memTableCurrentrow);
        model->submitAll(); //

    }
    memTableCurrentrow = -1;
    ShowMemList();
}
//
void MainWindow:: deletLevRow()
{


    QSqlTableModel *model = new QSqlTableModel;

    model = new QSqlTableModel(this,myDatabase.database);
    model->setTable("LEVEL_INFORMATION");
    model->removeColumn(3);

    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("会员等级"));
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("折扣额度"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("赠送积分"));

    model->select();

    ui->tableView_6->setModel(model);



    qDebug()<<u8""<<levTableCurrentrow;

    //е
    //
    int ok = QMessageBox::warning(this,tr(u8""),tr(u8"是否删除此行！"),
    QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
    model->revertAll();//
    }
    else
    {
        model->removeRow(levTableCurrentrow);
        model->submitAll(); //

    }


    levTableCurrentrow=-1;
    ShowLevList();
    ChangeComb(ui->comboBox_4,"LEVEL_INFORMATION");


}

//
void MainWindow:: deletProRow()
{

    QSqlTableModel *model = new QSqlTableModel;

    model = new QSqlTableModel(this,myDatabase.database);

    model->setTable("PRODUCT_INFORMATION");

    model->removeColumns(6,2);

    model->removeColumns(6,2);
    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("产品编号"));
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("产品名称"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("库存"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("价格"));
    model->setHeaderData(4, Qt::Horizontal, QStringLiteral("成本"));
    model->setHeaderData(5, Qt::Horizontal, QStringLiteral("生产日期"));

    model->select();

    ui->tableView_7->setModel(model);



    qDebug()<<u8""<<proTableCurrentrow;

    //е
    //
    int ok = QMessageBox::warning(this,tr(u8""),tr(u8"是否删除此行！"),
    QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
    model->revertAll();//
    }
    else    {
        model->removeRow(proTableCurrentrow);
        model->submitAll(); //

    }
    proTableCurrentrow=-1;
    ShowProList();
}

//
void MainWindow::deletDisRow()
{
    QSqlTableModel *model = new QSqlTableModel;

    model = new QSqlTableModel(this,myDatabase.database);
    model->setTable("DISCOUNT_INFORMATION");
    model->removeColumn(4);


    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("优惠券名称"));	//粻е
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("抵消金额"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("折扣额度"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("赠送积分"));

    model->select();

    ui->tableView_17->setModel(model);

    qDebug()<<u8""<<disTableCurrentrow;

    //е
    //
    int ok = QMessageBox::warning(this,tr(u8""),tr(u8"是否删除此行！"),
    QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
    model->revertAll();//
    }
    else     {
        model->removeRow(disTableCurrentrow);
        model->submitAll(); //

    }

    disTableCurrentrow=-1;
    ShowDiscList();
    ChangeComb(ui->comboBox_5,"DISCOUNT_INFORMATION");

}

//
void MainWindow::deletActRow()
{

    QSqlTableModel *model = new QSqlTableModel;

    model = new QSqlTableModel(this,myDatabase.database);
    model->setTable("ACTIVITY_INFORMATION");
    model->removeColumn(4);

    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("活动名称"));	//粻е
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("抵消金额"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("折扣额度"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("赠送积分"));

    model->select();

    ui->tableView_10->setModel(model);


    qDebug()<<u8""<<actTableCurrentrow;

    //е
    //
    int ok = QMessageBox::warning(this,tr(u8""),tr(u8"是否删除此行！"),
    QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
    model->revertAll();//
    }
    else     {
        model->removeRow(actTableCurrentrow);
        model->submitAll(); //

    }
    actTableCurrentrow=-1;
    ShowActList();
    ChangeComb(ui->comboBox_6,"ACTIVITY_INFORMATION");

}

//
void MainWindow::deletGifRow()
{


    QSqlTableModel *model = new QSqlTableModel;

    model = new QSqlTableModel(this,myDatabase.database);

    model->setTable("GIFT_INFORMATION");

    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("礼品编号"));	//粻е
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("礼品名称"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("剩余数量"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("兑换积分"));
    model->select();

    ui->tableView_11->setModel(model);
    ui->tableView_43->setModel(model);


    qDebug()<<u8""<<gifTableCurrentrow;

    //е
    //
    int ok = QMessageBox::warning(this,tr(u8""),tr(u8"是否删除此行！"),
    QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
    model->revertAll();//
    }
    else     {
        model->removeRow(gifTableCurrentrow);
        model->submitAll(); //

    }
    ShowGiftList();
}
