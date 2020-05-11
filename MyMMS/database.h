#ifndef DATABASE_H
#define DATABASE_H


#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlDatabase>

/*namespace Data {
class DataBase;
}*/

class DataBase
{
public:
    QSqlDatabase database;

public:
    QSqlQueryModel *memModel;

public:
    DataBase();
    DataBase(const QString& dbNmae);
    void CheckOpen();
    void CreateTables();
    bool IsTableExist(QString table);
    void InsertVIP_INFO(int VIP_ID,int CARD_NUMBER,QString VIP_NAME,
                        QString CODE,QString SEX,QString DATE_OF_BIRTH,
                        int TELEPHONE,QString EMAIL,QString LEVEL);

    void InsertPRO_INFO(int PRODUCT_NUMBER,QString PRODUCT_NAME,
                        int LEFT_NUMBER,double PRICE,double COST,
                        QString DATE_IN_PRODUCED,QString CATEGORY,
                        int INTEGRAL_NUMBER);   //INTEGRAL_NUMBER：产品积分

    void  InsertCARD_INFO(int CARD_NUMBER,QString CODE,double BALANCE,
                          int INTEGRAL,QString STATE,QString REGISTER_TIME,
                           QString LEVEL, QString REMARK);

    void  InsertTEMP_INFO(int NUMBER,QString NAME,
                          double PRICE, QString CATEGORY,
                          int INTEGRAL_NUMBER,int MOUNT);

    void InsertDISC_INFO(QString DISCOUNT_NAME,double MONEY,
                           double DISCOUN, int INTEGRAL_NUMBER);


    void InsertACT_INFO(QString ACTIVITYT_NAME,double MONEY,
                           double DISCOUN, int INTEGRAL_NUMBER);

    void InsertGIFT_INFO(int GIFT_NUMBER, QString GITF_NAME,
                           int LEFT_NUMBER,int INTEGRAL_NUMBER);

    void InsertLEVEL_INFO(QString LEVEL,double DISCOUNT,int INTEGRAL);

    void InsertMAN_INFO(QString ACCOUNT, QString CODE,
                                    QString MANAGER_NAME,int TELEPHON);

};

#endif // DATABASE_H
