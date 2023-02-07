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

bool SubjectService::addTask(Task *task)
{

    // 添加题目到数据库
    QString sql = R"(
                 INSERT INTO "main"."s_task"("t_id", "c_id", "t_description", "t_content", "create_time", "update_time","t_title","s_id","t_answer")
                  VALUES (null, ?, ?, ?, ?, ?, ?, ?, ?);
                  )";
    query->prepare(sql);
    // 设置 分类 ID
    query->bindValue(0,task->getC_id());
    query->bindValue(1,task->getT_description());
    query->bindValue(2,task->getT_content());
    query->bindValue(3,EsUtil::getCurrentFormatData());
    query->bindValue(4,EsUtil::getCurrentFormatData());
    query->bindValue(5,task->getT_title());
    // 设置当前窗口的Subject为此题目的id
    query->bindValue(6,EsUtil::CreateSubjectWindow->getSubject()->getS_id());
    query->bindValue(7,task->getT_answer());
    bool ok = query->exec();
    query->clear();
    return ok;

}

bool SubjectService::updateSubjectTite(int s_id, QString s_name)
{
    QString sql = "update s_subject set s_name = ? where s_id = ?";
    query->prepare(sql);
    query->bindValue(0,s_name);
    query->bindValue(1,s_id);
    bool ok = query->exec();
    query->clear();
    return ok;
}


Subject* SubjectService::getSubjectById(int sid)
{
    query->prepare("select * from s_subject where s_id = ?");
    query->bindValue(0,sid);
    query->exec();
    query->next();
    Subject *sb = new Subject(query->value("s_id").toInt(),query->value("s_name").toString());
    query->clear();
    return sb;
}

Category *SubjectService::getCategoryById(int cid)
{
    query->prepare("select * from s_category where c_id = ?");
    query->bindValue(0,cid);
    query->exec();
    query->next();
    Category *cg = new Category(query->value("c_id").toInt(),query->value("c_name").toString());
    query->clear();
    return cg;
}

// 因为这里有字段类型限制，所以可以直接拼接到字符串，我不是把字符串直接拼接到sql里的

bool SubjectService::deleteCagegoryById(int cid)
{
    // 删除分类
    bool ok = query->exec(QString("delete from s_category where c_id = %1").arg(cid));
    // 删除题目
    ok &= query->exec(QString("delete from s_task where c_id = %1").arg(cid));
    query->clear();
    return ok;
}

bool SubjectService::deleteTaskById(int tid)
{
    // 删除题目
    bool ok = query->exec(QString("delete from s_task where t_id = %1").arg(tid));
    query->clear();
    return ok;
}

bool SubjectService::updateCategoryById(int cid, QString cname)
{
    query->prepare("update s_category set c_name = ? , update_time = ? where c_id = ?");
    query->bindValue(0,cname);
    query->bindValue(1,EsUtil::getCurrentFormatData());
    query->bindValue(2,cid);
    bool ok = query->exec();
    query->clear();
    return ok;
}

bool SubjectService::updateTaskById(Task *task)
{
    QString sql = R"(
    UPDATE "main"."s_task" SET "c_id" = ?,  "t_title" = ? , "t_answer" = ?, "t_description" = ?, "t_content" = ?,
                   "update_time" = ? WHERE "t_id" = ?;
                  )";
    query->prepare(sql);
    query->bindValue(0,task->getC_id());
    query->bindValue(1,task->getT_title());
    query->bindValue(2,task->getT_answer());
    query->bindValue(3,task->getT_description());
    query->bindValue(4,task->getT_content());
    query->bindValue(5, EsUtil::getCurrentFormatData());
    query->bindValue(6,task->getT_id());
    bool ok = query->exec();
    query->clear();
    return ok;
}

