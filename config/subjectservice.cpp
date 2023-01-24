#include "subjectservice.h"
#include "daoconfig.h"
#include <QDebug>
#include "config/esutil.h"

// query 对象
SubjectService::SubjectService()
{
    query = new QSqlQuery(DaoConfig::get()->getDB());
}


/**
 * @brief 添加科目
 * @param name
 * @return
 */
bool SubjectService::addSubject(QString name)
{
    QString sql = QString(R"(
                         INSERT INTO "main"."s_subject"("s_id", "s_name", "create_time", "update_time") VALUES (null,?,?,?);
                          )");
    query->prepare(sql);
    query->bindValue(0,name);
    query->bindValue(1,EsUtil::getCurrentFormatData());
    query->bindValue(2,EsUtil::getCurrentFormatData());

    bool ok = query->exec();
    qDebug() << ok;
    qDebug() << "插入ID: " <<  query->lastInsertId().toInt(); // 具体需要了解QVariant的使用
    query->clear(); // 清楚语句信息
    return ok;
}

bool SubjectService::addCategory(QString name, int subjectId)
{

}
