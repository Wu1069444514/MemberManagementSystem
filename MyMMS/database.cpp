#include "database.h"

//构造函数
//创建数据库并设置相应值
DataBase::DataBase()
{
    if (QSqlDatabase::contains("MyMMS"))
    {
        database = QSqlDatabase::database("MyMMS");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE","MyMMS");        //添加驱动名驱动名和默认连接名称
        database.setDatabaseName("MyDataBase.db");              //默认连接名称
        database.setUserName("XingYeZhiXia");
        database.setPassword("123456");
    }
}

//查看数据库是否成功连接以及是否创建表格
void DataBase::CheckOpen()
{

    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug() << "成功连接.";
        if(IsTableExist("VIP_INFORMATION")&&IsTableExist("CARD_INFORMATION")
                &&IsTableExist("PRODUCT_INFORMATION")&&IsTableExist("CONSUME_RECORD")
                &&IsTableExist("LEVEL_INFORMATION")&&IsTableExist("TEMP_INFORMATION")
                &&IsTableExist("DISCOUNT_INFORMATION")&&IsTableExist("ACTIVITY_INFORMATION")
                &&IsTableExist("GIFT_INFORMATION")&&IsTableExist("CLASS_INFORMATION")
                &&IsTableExist("MANAGER_INFORMATION"))
            qDebug()<<"表已存在";
        else
        {
            CreateTables();
        }
    }
}

//判断指定表是否存在
bool DataBase:: IsTableExist(QString table)
{
   QSqlQuery query(database);
   QString sql = QString("select * from sqlite_master where name='%1'").arg(table);
   query.exec(sql);
   return query.next();
}


//创建表格
void DataBase::CreateTables()
{

    //创建会员信息表
    QSqlQuery sql_query(database);
    QString create_sql1 = "create table VIP_INFORMATION ("
                          "VIP_ID int(11) primary key,"
                          "CARD_NUMBER int(11), "
                          "VIP_NAME text(20), "
                          "CODE text(20),"
                          "SEX  text(10),"
                          "DATE_OF_BIRTH text(30),"
                          "TELEPHONE int(11),"
                          "EMAIL text(20),"
                          "LEVEL text(10)"
                          ")";
    sql_query.prepare(create_sql1);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create VIP_INFORMATION." << sql_query.lastError();
    }
    else
    {
        qDebug() << "VIP_INFORMATION created!";
    }

    //创建会员卡信息表
    QString create_sql2 = "create table CARD_INFORMATION ("
                          "CARD_NUMBER int(11) primary key, "
                          "CODE text(20), "
                          "BALANCE real(60),"
                          "INTEGRAL int(10),"
                          "STATE text(10),"
                          "REGISTER_TIME date,"
                          "LEVEL text(10),"
                          "REMARK text(500)"
                          ")";
    sql_query.prepare(create_sql2);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create CARD_INFORMATION." << sql_query.lastError();
    }
    else
    {
        qDebug() << "CARD_INFORMATION created!";
    }

    //创建产品信息表
    QString create_sql3 = "create table PRODUCT_INFORMATION ("
                          "PRODUCT_NUMBER int(11) primary key, "
                          "PRODUCT_NAME text(20), "
                          "LEFT_NUMBER int(10),"
                          "PRICE real(20),"
                          "COST real(20),"
                          "DATE_IN_PRODUCED date,"
                          "CATEGORY text(20),"
                          "INTEGRAL_NUMBER int(10)"
                          ")";
    sql_query.prepare(create_sql3);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create PRODUCT_INFORMATION." << sql_query.lastError();
    }
    else
    {
        qDebug() << "PRODUCT_INFORMATION created!";
    }

    //创建订单信息表
    QString create_sql4 = "create table CONSUME_RECORD ("
                          "ORDER_NUMBER int(11) primary key,"
                          "PRODUCT_NAME text(20), "
                          "CARD_ NUMBER int(11),"
                          "CONSUMPTION_AMOUNT real(10),"
                          "CONSUMPTION_QUALITY int(10),"
                          "CONSUMPTION_TIME date "
                          ")";
    sql_query.prepare(create_sql4);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create CONSUME_RECORD." << sql_query.lastError();
    }
    else
    {
        qDebug() << "CONSUME_RECORD created!";
    }
    //创建等级信息表
    QString create_sql5 = "create table LEVEL_INFORMATION("
                          "LEVEL text(20) primary key,"
                          "DISCOUNT  real(10),"
                          "INTEGRAL int(10),"
                          "INDEX_ROW int(5)"
                          ")";
    sql_query.prepare(create_sql5);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create LEVEL_INFORMATION." << sql_query.lastError();
    }
    else
    {
        qDebug() << "LEVEL_INFORMATION created!";
    }

    //创建临时操作表
    QString create_sql6 ="create table TEMP_INFORMATION ("
                         "NUMBER int(11) primary key, "
                         "NAME text(20), "
                         "PRICE real(20),"
                         "CATEGORY text(20),"
                         "INTEGRAL_NUMBER int(10),"
                         "MOUNT int(10)"
                         ")";
    sql_query.prepare(create_sql6);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create TEMP_INFORMATION." << sql_query.lastError();
    }
    else
    {
        qDebug() << "TEMP_INFORMATION created!";
    }
    //优惠券信息表
    QString create_sql7 ="create table DISCOUNT_INFORMATION ("
                         "DISCOUNT_NAME text(20) primary key, "
                         "MONEY real(20), "
                         "DISCOUN real(20),"
                         "INTEGRAL_NUMBER int(10),"
                         "INDEX_ROW int(5)"
                         ")";
    sql_query.prepare(create_sql7);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create DISCOUNT_INFORMATION." << sql_query.lastError();
    }
    else
    {
        qDebug() << "DISCOUNT_INFORMATION created!";
    }
    //优惠活动信息表
    QString create_sql8 ="create table ACTIVITY_INFORMATION ("
                         "ACTIVITY_NAME text(20) primary key, "
                         "MONEY real(20), "
                         "DISCOUN real(20),"
                         "INTEGRAL_NUMBER int(10),"
                         "INDEX_ROW int(5)"
                         ")";
    sql_query.prepare(create_sql8);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create ACTIVITY_INFORMATION." << sql_query.lastError();
    }
    else
    {
        qDebug() << "ACTIVITY_INFORMATION created!";
    }


    //创建礼品信息表
    QString create_sql9 = "create table GIFT_INFORMATION ("
                          "GIFT_NUMBER int(11) primary key, "
                          "GITF_NAME text(20), "
                          "LEFT_NUMBER int(10),"
                          "INTEGRAL_NUMBER int(10)"
                          ")";
    sql_query.prepare(create_sql9);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create GIFT_INFORMATION." << sql_query.lastError();
    }
    else
    {
        qDebug() << "GIFT_INFORMATION created!";
    }

    //创建商品类别表
    QString create_sql10 = "create table CLASS_INFORMATION ("
                          "CLASS_NUMBER int(11) primary key, "
                          "CLASS_NAME text(20), "
                          "CONDITION int(10)"
                          ")";
    sql_query.prepare(create_sql10);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create CLASS_INFORMATION." << sql_query.lastError();
    }
    else
    {
        qDebug() << "CLASS_INFORMATION created!";
    }

    //创建管理员信息表
    QString create_sql11 = "create table MANAGER_INFORMATION ("
                           "ACCOUNT text(10) primary key,"
                            "CODE text(20),"
                           "MANAGER_NAME text(20) , "
                          "TELEPHON int(11)"
                          ")";
    sql_query.prepare(create_sql11);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create MANAGER_INFORMATION." << sql_query.lastError();
    }
    else
    {
        qDebug() << "MANAGER_INFORMATION created!";
    }
}

//向会员信息表中插入行
void DataBase:: InsertVIP_INFO(int VIP_ID,int CARD_NUMBER,QString VIP_NAME,
                    QString CODE,QString SEX,QString DATE_OF_BIRTH,
                    int TELEPHONE,QString EMAIL,QString LEVEL)
{

    QSqlQuery sql_query(database);
    QString insert_sql = "insert into VIP_INFORMATION values (?, ?, ?,?,?,?,?,?,?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(VIP_ID);
    sql_query.addBindValue(CARD_NUMBER);
    sql_query.addBindValue(VIP_NAME);
    sql_query.addBindValue(CODE);
    sql_query.addBindValue(SEX);
    sql_query.addBindValue(DATE_OF_BIRTH);
    sql_query.addBindValue(TELEPHONE);
    sql_query.addBindValue(EMAIL);
    sql_query.addBindValue(LEVEL);
    if(!sql_query.exec())
    {
          qDebug() << sql_query.lastError();
    }

    else
    {
        qDebug() << "inserted "<<TELEPHONE;
    }
}

//向产品信息表中插入行
void DataBase:: InsertPRO_INFO(int PRODUCT_NUMBER,QString PRODUCT_NAME,int LEFT_NUMBER,
                               double PRICE,double COST,QString DATE_IN_PRODUCED,
                               QString CATEGORY,int INTEGRAL_NUMBER)
{

    QSqlQuery sql_query(database);
    QString insert_sql = "insert into PRODUCT_INFORMATION values (?, ?, ?,?,?,?,?,?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(PRODUCT_NUMBER);
    sql_query.addBindValue(PRODUCT_NAME);
    sql_query.addBindValue(LEFT_NUMBER);
    sql_query.addBindValue(PRICE);
    sql_query.addBindValue(COST);
    sql_query.addBindValue(DATE_IN_PRODUCED);
    sql_query.addBindValue(CATEGORY);
    sql_query.addBindValue(INTEGRAL_NUMBER);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted "<<PRODUCT_NAME;
    }
}

//向会员卡信息表中插入行
void DataBase:: InsertCARD_INFO(int CARD_NUMBER,QString CODE,
                                double BALANCE,int INTEGRAL,
                                QString STATE,QString REGISTER_TIME,
                                QString LEVEL, QString REMARK)
{

    QSqlQuery sql_query(database);
    QString insert_sql = "insert into CARD_INFORMATION values (?,?,?,?,?,?,?,?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(CARD_NUMBER);
    sql_query.addBindValue(CODE);
    sql_query.addBindValue(BALANCE);
    sql_query.addBindValue(INTEGRAL);
    sql_query.addBindValue(STATE);
    sql_query.addBindValue(REGISTER_TIME);
    sql_query.addBindValue(LEVEL);
    sql_query.addBindValue(REMARK);

    if(!sql_query.exec())
    {
          qDebug() << sql_query.lastError();
    }

    else
    {
        qDebug() << "inserted "<<CARD_NUMBER;
    }
}



//向临时操作表中插入行
void DataBase:: InsertTEMP_INFO(int NUMBER,QString NAME,
                               double PRICE, QString CATEGORY,
                               int INTEGRAL_NUMBER,int MOUNT)
{

    QSqlQuery sql_query(database);
    QString insert_sql = "insert into TEMP_INFORMATION values (?, ?, ?,?,?,?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(NUMBER);
    sql_query.addBindValue(NAME);
    sql_query.addBindValue(PRICE);
    sql_query.addBindValue(CATEGORY);
    sql_query.addBindValue(INTEGRAL_NUMBER);
    sql_query.addBindValue(MOUNT);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted "<<NAME;
    }
}


//向会员等级表中插入行
void DataBase:: InsertLEVEL_INFO(QString LEVEL,
                               double DISCOUNT,
                               int INTEGRAL)
{

    QSqlQuery sql_query(database);

    bool ok;
    QString count_sql = "select count(*) from LEVEL_INFORMATION ";
    sql_query.exec(count_sql);
    sql_query.next();
    int INDEX = sql_query.value(0).toString().toInt(&ok,10);


    QString insert_sql = "insert into LEVEL_INFORMATION values (?, ?, ?,?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(LEVEL);
    sql_query.addBindValue(DISCOUNT);
    sql_query.addBindValue(INTEGRAL);
    sql_query.addBindValue(INDEX);

    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted "<<LEVEL;
    }
}

//向优惠券信息表中插入行
void DataBase:: InsertDISC_INFO(QString DISCOUNT_NAME,double MONEY,
                               double DISCOUN, int INTEGRAL_NUMBER)
{

    QSqlQuery sql_query(database);

    bool ok;
    QString count_sql = "select count(*) from DISCOUNT_INFORMATION ";
    sql_query.exec(count_sql);
    sql_query.next();
    int INDEX = sql_query.value(0).toString().toInt(&ok,10);

    QString insert_sql = "insert into DISCOUNT_INFORMATION values (?, ?, ?,?,?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(DISCOUNT_NAME);
    sql_query.addBindValue(MONEY);
    sql_query.addBindValue(DISCOUN);
    sql_query.addBindValue(INTEGRAL_NUMBER);
    sql_query.addBindValue(INDEX);

    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted "<<DISCOUNT_NAME;
    }
}

//向优惠活动信息表中插入行
void DataBase:: InsertACT_INFO(QString ACTIVITYT_NAME,double MONEY,
                               double DISCOUN, int INTEGRAL_NUMBER)
{

    QSqlQuery sql_query(database);

    bool ok;
    QString count_sql = "select count(*) from ACTIVITY_INFORMATION ";
    sql_query.exec(count_sql);
    sql_query.next();
    int INDEX = sql_query.value(0).toString().toInt(&ok,10);


    QString insert_sql = "insert into ACTIVITY_INFORMATION values (?, ?, ?,?,?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(ACTIVITYT_NAME);
    sql_query.addBindValue(MONEY);
    sql_query.addBindValue(DISCOUN);
    sql_query.addBindValue(INTEGRAL_NUMBER);
    sql_query.addBindValue(INDEX);

    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted "<<ACTIVITYT_NAME;
    }
}

//向礼品信息表中插入行
void DataBase:: InsertGIFT_INFO(int GIFT_NUMBER, QString GITF_NAME,
                                int LEFT_NUMBER,int INTEGRAL_NUMBER)
{

    QSqlQuery sql_query(database);
    QString insert_sql = "insert into GIFT_INFORMATION values (?, ?, ?,?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(GIFT_NUMBER);
    sql_query.addBindValue(GITF_NAME);
    sql_query.addBindValue(LEFT_NUMBER);
    sql_query.addBindValue(INTEGRAL_NUMBER);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted "<<GIFT_NUMBER;
    }
}



//管理员注册

void DataBase:: InsertMAN_INFO(QString ACCOUNT, QString CODE,
                                QString MANAGER_NAME,int TELEPHON)
{

    QSqlQuery sql_query(database);
    QString insert_sql = "insert into MANAGER_INFORMATION values (?, ?, ?,?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(ACCOUNT);
    sql_query.addBindValue(CODE);
    sql_query.addBindValue(MANAGER_NAME);
    sql_query.addBindValue(TELEPHON);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted "<<MANAGER_NAME;
    }
}



