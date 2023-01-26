#include "subjectservice.h"
#include "daoconfig.h"
#include <QDebug>
#include "config/esutil.h"

// query 对象
SubjectService::SubjectService()
{
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
    // 这个query仅是一个临时的指针罢了
    query = DaoConfig::get()->query();
    query->prepare(sql);
    query->bindValue(0,name);
    query->bindValue(1,EsUtil::getCurrentFormatData());
    query->bindValue(2,EsUtil::getCurrentFormatData());

    bool ok = query->exec();
    qDebug() << ok;
    int insertId = query->lastInsertId().toInt();
    qDebug() << "插入ID: " << insertId; // 具体需要了解QVariant的使用
    query->clear(); // 清楚语句信息
    // 添加完后如果成功了，则需要将ID传到创建窗口
    if(ok){
        EsUtil::CreateSubjectWindow->getSubject()->setS_id(insertId); // 设置ID
        EsUtil::CreateSubjectWindow->getSubject()->setS_name(name); // 设置科目名
    }
    return ok;
}

bool SubjectService::addCategory(QString name, int subjectId)
{

}
