#ifndef SPAPERCATEGORY_H
#define SPAPERCATEGORY_H

#include <QObject>
#include <QVector>
#include "pojo/sanswer.h"

class SPaperCategory : public QObject
{
public:
    explicit SPaperCategory(QObject *parent = nullptr);
    SPaperCategory(int cid,int num):cid(cid),num(num){}

    void setPcid(int pcid) {this->pcid = pcid;};
    int getPcid()  {return this->pcid;};
    void setCid(int cid) {this->cid = cid;};
    int getCid()  {return this->cid;};
    void setPid(int pid) {this->pid = pid;};
    int getPid()  {return this->pid;};
    void setPcStatus(bool pcStatus) {this->pcStatus = pcStatus;};
    int getPcStatus()  {return this->pcStatus;};
    // 返回地址即可
    QVector<SAnswer*>* getAnswerList() {return & this->answerList;};
    void setNum(int num){this->num = num;};
    int getNum() { return this->num;};

private:
    int pcid;
    int cid;
    int pid;
    int num;
    bool pcStatus;
    QVector<SAnswer*> answerList;

signals:

};

#endif // SPAPERCATEGORY_H
