#include "subjectservice.h"
#include "daoconfig.h"
#include <QMessageBox>
#include <QDebug>
#include "config/esutil.h"

// query 对象
SubjectService::SubjectService()
{
    // 这个query仅是一个临时的指针罢了，因为不是静态类，所以使用这个类之指必然首先执行此构造方法
    query = DaoConfig::get()->query();
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
    QString sql = QString(R"(
        INSERT INTO "main"."s_category"("c_id", "s_id", "c_name", "create_time", "update_time")
                          VALUES (NULL,?,?,?,?);
    )");
    query->prepare(sql);
    query->bindValue(0,subjectId);
    query->bindValue(1,name);
    query->bindValue(2,EsUtil::getCurrentFormatData());
    query->bindValue(3,EsUtil::getCurrentFormatData());

    // 添加成功后需要刷新科目的表
    bool ok = query->exec();
    query->clear(); // 清除状态
    if(ok){
        // 不错，这个指针保存的用法是真的不错
        QMessageBox::information(EsUtil::CreateSubjectWindow,QString("成功"),QString("添加类成功"));
        // 添加成功后需要刷新列表
        EsUtil::CreateSubjectWindow->refreshCategoryList();

    }else {
        QMessageBox::critical(EsUtil::CreateSubjectWindow,QString("类错误"),QString("添加类错误，信息有误，或软件出现问题"));
    }
    return ok;
}

bool SubjectService::addSubjectTask(QString title, QString answer, int categoryId)
{
    QString sql = R"(
                 INSERT INTO "main"."s_task"("t_id", "c_id", "t_description", "t_content", "create_time", "update_time")
                  VALUES (NULL,?,?,?,?,?);
                  )";
    query->prepare(sql);

    // 设置时间
    query->bindValue(3,EsUtil::getCurrentFormatData());
    query->bindValue(4,EsUtil::getCurrentFormatData());

    return false;
}

bool SubjectService::addTask(QString t_title, QString questionHtml, QString answerHtml, int categoryId, QString textContent)
{

    // 添加题目到数据库
    QString sql = R"(
                 INSERT INTO "main"."s_task"("t_id", "c_id", "t_description", "t_content", "create_time", "update_time","t_title","s_id","t_answer")
                  VALUES (null, ?, ?, ?, ?, ?, ?, ?, ?);
                  )";
    query->prepare(sql);
    // 设置 分类 ID
    query->bindValue(0,categoryId);
    query->bindValue(1,questionHtml);
    query->bindValue(2,answerHtml);
    query->bindValue(3,EsUtil::getCurrentFormatData());
    query->bindValue(4,EsUtil::getCurrentFormatData());
    query->bindValue(5,t_title);
    // 设置当前窗口的Subject为此题目的id
    query->bindValue(6,EsUtil::CreateSubjectWindow->getSubject()->getS_id());
    query->bindValue(7,textContent);

    bool ok = query->exec();

    query->clear();
    return ok;

}

