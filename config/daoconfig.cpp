#include "daoconfig.h"
#include <QSqlDatabase>
#include <QCoreApplication>
#include <QSqlQuery>
#include <QDebug>

DaoConfig::DaoConfig()
{

}

void DaoConfig::sqlInit()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../es.db");
    db.open();
    QString path = QCoreApplication::applicationDirPath();
    qDebug() << path;

    QSqlQuery query;

    const QString createDatabaseSql = R"(
                                        /*==============================================================*/
                                        /* Table: s_anwser                                              */
                                        /*==============================================================*/
                                        create table s_anwser
                                        (
                                           a_id                 int not null,
                                           t_id                 int,
                                           pc_id                int,
                                           a_detail             text,
                                           update_time          datetime,
                                           primary key (a_id)
                                        );

                                        /*==============================================================*/
                                        /* Table: s_category                                            */
                                        /*==============================================================*/
                                        create table s_category
                                        (
                                           c_id                 int not null,
                                           s_id                 int,
                                           c_name               varchar(255) not null,
                                           create_time          datetime,
                                           update_time          datetime,
                                           primary key (c_id)
                                        );

                                        /*==============================================================*/
                                        /* Table: s_paper                                               */
                                        /*==============================================================*/
                                        create table s_paper
                                        (
                                           p_id                 int not null,
                                           s_id                 int,
                                           p_name               varchar(255),
                                           create_time          datetime,
                                           primary key (p_id)
                                        );

                                        /*==============================================================*/
                                        /* Table: s_paper_category                                      */
                                        /*==============================================================*/
                                        create table s_paper_category
                                        (
                                           pc_id                int not null,
                                           c_id                 int,
                                           p_id                 int,
                                           pc_status            smallint,
                                           primary key (pc_id)
                                        );

                                        /*==============================================================*/
                                        /* Table: s_subject                                             */
                                        /*==============================================================*/
                                        create table s_subject
                                        (
                                           s_id                 int not null,
                                           s_name               varchar(255) not null,
                                           create_time          datetime,
                                           update_time          datetime,
                                           primary key (s_id)
                                        );

                                        /*==============================================================*/
                                        /* Table: s_task                                                */
                                        /*==============================================================*/
                                        create table s_task
                                        (
                                           t_id                 int not null,
                                           c_id                 int,
                                           t_description        text,
                                           t_content            text,
                                           create_time          datetime,
                                           update_time          datetime,
                                           primary key (t_id)
                                        )
                                      )";

    for(auto sql: createDatabaseSql){
        query.exec(sql);
    }

    qDebug() << "初始化数据库完成" << endl;


}
