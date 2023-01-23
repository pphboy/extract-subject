#ifndef SUBJECT_H
#define SUBJECT_H


#include <QString>
#include <QtGlobal>

/**
 * @brief 科目的具体的类
 */
class Subject
{
public:
    Subject();
private:
    int s_id; // 科目ID,如果有ID就是编辑，没有ID就是新增
    QString s_name; // 科目名称
    QString create_time;
    QString update_time;

};

#endif // SUBJECT_H
