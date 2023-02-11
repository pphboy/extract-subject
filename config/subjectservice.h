#ifndef SUBJECTSERVICE_H
#define SUBJECTSERVICE_H

#include <QSqlQuery>
#include <QVector>
#include <QString>
#include "daoconfig.h"
#include "pojo/subject.h"
#include "pojo/category.h"
#include "pojo/task.h"
#include "pojo/spaper.h"
#include "pojo/spapercategory.h"
#include "pojo/sanswer.h"

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
    QVector<Category *> getCategoryListBySubjectId(int sid);
    bool addSPaper(SPaper *spaper);
    bool addSPaperCategory(SPaperCategory *scg);
    QVector<Task *> getTaskListByCid(int cid);
    bool addSPaperAnswer(SAnswer *asnwer);
    QVector<SPaper *> getSPaperList();
    bool deleteSPaperById(int pid);
    SPaper getSPaperById(int pid);

    bool savePaperAnswer(Task *task);
private:
    QSqlQuery *query;

};

#endif // SUBJECTSERVICE_H
