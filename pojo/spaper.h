#ifndef SPAPER_H
#define SPAPER_H

#include <QString>
#include <QVector>
#include "pojo/spapercategory.h"

class SPaper
{
public:
    SPaper();
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
private:
    int pid;
    int sid;
    QString pname;
    QString createTime;
    QVector<SPaperCategory*> categoryList;
};

#endif // SPAPER_H
