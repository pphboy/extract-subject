#ifndef SPAPER_H
#define SPAPER_H

#include <QString>
#include <QVector>
#include "pojo/spapercategory.h"
#include "pojo/subject.h"
#include "pojo/category.h"

class SPaper
{
public:
    SPaper();
    SPaper(int sid,QString pname):sid(sid),pname(pname){};
    SPaper(int sid,int pid,QString pname,QString createTime):pid(pid),sid(sid),pname(pname),createTime(createTime){};
    void setSid(int sid) {this->sid = sid;};
    int getSid()  {return this->sid;};
    void setPid(int pid) {this->pid = pid;};
    int getPid()  {return this->pid;};
    void setPname(QString pname) {this->pname = pname;};
    QString getPname()  {return this->pname;};
    void setCreateTime(QString createTime) {this->createTime = createTime;};
    QString getCreateTime()  {return this->createTime;};
    // 直接返回了指针
    QVector<SPaperCategory*>* getCategoryList(){return &this->categoryList;};
    void setSubject(Subject *subject) {this->subject = subject;};
    Subject* getSubject(){return this->subject;};

    QVector<Category*> getCategoryTaskList(){return this->categoryTaskList;};
    void setCategoryTaskList(QVector<Category*> c){this->categoryTaskList = c;};
private:
    int pid;
    int sid;
    QString pname;
    QString createTime;
    /**
     * 这个是用来抽题目或者保存答案的时候用的
     */
    QVector<SPaperCategory*> categoryList;
    /**
     * 这个是用来查询题目的时候用的
     */
    QVector<Category*> categoryTaskList;
    Subject* subject;
};

#endif // SPAPER_H
