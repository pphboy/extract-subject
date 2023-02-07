#ifndef SUBJECTSERVICE_H
#define SUBJECTSERVICE_H

#include <QSqlQuery>
#include <QString>
#include "daoconfig.h"
#include "pojo/subject.h"
#include "pojo/category.h"
#include "pojo/task.h"

class SubjectService
{
public:
    SubjectService();
    bool addSubject(QString name); // 添加科目
    bool addCategory(QString name,int subjectId); // 添加分类
    bool addSubjectTask(QString title, QString answer,int categoryId);
    bool addTask(Task *task);
    bool updateSubjectTite(int s_id, QString s_name);
    Subject * getSubjectById(int sid);
    Category *getCategoryById(int cid);
    // 删除分类，连同题目一起删除
    bool deleteCagegoryById(int cid);
    bool deleteTaskById(int tid);
    bool updateCategoryById(int cid, QString cname);
    bool updateTaskById(Task* task);
    bool deleteSubjectById(int sid);
    bool updateSubjectById(Subject *subject);
private:
    QSqlQuery *query;

};

#endif // SUBJECTSERVICE_H
