#include "daoconfig.h"
#include <QSqlDatabase>
#include <QCoreApplication>
#include <QSqlQuery>
#include <QDebug>
#include <QCoreApplication>

DaoConfig::DaoConfig()
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QString("%1/es.db").arg(QCoreApplication::applicationDirPath()));
    db.open(); // 初始化时需要打开
    qDebug() << "数据库成功打开" << QString("%1/es.db").arg(QCoreApplication::applicationDirPath());
}

void DaoConfig::sqlInit()
{
    QString path = QCoreApplication::applicationDirPath();
    qDebug() << path;

    QSqlQuery query(db);

    const QString createDatabaseSql = R"(
                                                    /*==============================================================*/
                                        /* Table: s_answer                                              */
                                        /*==============================================================*/
                                        create table s_answer
                                        (
                                           a_id                 integer primary key autoincrement,
                                           t_id                 int,
                                           pc_id                int,
                                           a_detail             text,
                                           update_time          datetime

                                        );

                                        /*==============================================================*/
                                        /* Table: s_category                                            */
                                        /*==============================================================*/
                                        create table s_category
                                        (
                                           c_id                 integer primary key autoincrement,
                                           s_id                 int,
                                           c_name               varchar(255) not null,
                                           create_time          datetime,
                                           update_time          datetime

                                        );

                                        /*==============================================================*/
                                        /* Table: s_paper                                               */
                                        /*==============================================================*/
                                        create table s_paper
                                        (
                                           p_id                 integer primary key autoincrement,
                                           s_id                 int,
                                           p_name               varchar(255),
                                           create_time          datetime

                                        );

                                        /*==============================================================*/
                                        /* Table: s_paper_category                                      */
                                        /*==============================================================*/
                                        create table s_paper_category
                                        (
                                           pc_id                INTEGER PRIMARY KEY AUTOINCREMENT,
                                           c_id                 int,
                                           p_id                 int,
                                           pc_status            smallint

                                        );

                                        /*==============================================================*/
                                        /* Table: s_subject                                             */
                                        /*==============================================================*/
                                        create table s_subject
                                        (
                                           s_id                 INTEGER PRIMARY KEY AUTOINCREMENT,
                                           s_name               varchar(255) not null,
                                           create_time          datetime,
                                           update_time          datetime
                                        );

                                        /*==============================================================*/
                                        /* Table: s_task                                                */
                                        /*==============================================================*/
                                        create table s_task
                                        (
                                           t_id                 INTEGER PRIMARY KEY AUTOINCREMENT,
                                           c_id                 int,
                                           s_id int,
                                           t_title              text,
                                           t_answer             text,
                                           t_description        text,
                                           t_content            text,
                                           create_time          datetime,
                                           update_time          datetime
                                        )

                                      )";

    for(auto sql: createDatabaseSql.split(";")){
//        qDebug() << sql << query.exec(sql);
        query.exec(sql);
    }

    qDebug() << "初始化数据库完成" << endl;


}

QSqlDatabase DaoConfig::getDB()
{
    // 这里的DB默认是打开的
    return db;
}

// 查询的接口就是这一个了
/**
 * @brief DaoConfig::query
 * @example 例子: DaoConfig::get().query()->exec("sql");
 * @return  queryPtr
 */
QSqlQuery* DaoConfig::query()
{
    if(queryPtr == nullptr){
        queryPtr = new QSqlQuery(DaoConfig::get()->getDB());
    }
    return queryPtr;
}

void DaoConfig::open()
{
    db.open();
}


// 因为这个static没怎么搞明白，先写到这里
static DaoConfig *dc = nullptr;

DaoConfig* DaoConfig::get()
{
    if(dc == nullptr){
        dc = new DaoConfig;
    }

//    qDebug() << "引用一次DaoConfig" << dc ;
    return dc;
}


DaoConfig::~DaoConfig()
{
    delete this;
    // 这里删除了，不知道有没有用
    delete dc;
}
