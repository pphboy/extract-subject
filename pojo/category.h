#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>

class Category
{
public:
    Category();
    Category(int c_id, QString c_name):c_id(c_id), c_name(c_name) {};
    Category(int c_id, QString c_name,int taskNum):c_id(c_id), c_name(c_name),taskNum(taskNum) {};
    ~Category();
    int getC_id() {return this->c_id;};
    void setTaskNum(int taskNum){this->taskNum = taskNum;};
    QString getCname() {return this->c_name;};
    int getTaskNum(){ return this->taskNum;};

private:
    int c_id;
    QString c_name;
    int taskNum;
};

#endif // CATEGORY_H
