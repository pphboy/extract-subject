#ifndef SPAPER_H
#define SPAPER_H

#include <QString>
#include <QVector>
#include "pojo/spapercategory.h"
#include "pojo/subject.h"

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
private:
    int pid;
    int sid;
    QString pname;
    QString createTime;
    QVector<SPaperCategory*> categoryList;
    Subject* subject;
};

#endif // SPAPER_H
