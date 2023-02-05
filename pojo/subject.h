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
    Subject(int s_id, QString s_name):s_id(s_id),s_name(s_name){};
    int getS_id(){return s_id;};
    void setS_id(int id) { s_id = id;}
    QString getS_name() { return s_name;}
    void setS_name(QString name){s_name = name;}
    QString getCreate_time() { return create_time;}
    void setCreate_time(QString time){create_time = time;}
    QString getUpdate_time() { return update_time;}
    void setUpdate_time(QString time){update_time= time;}

private:
    int s_id; // 科目ID,如果有ID就是编辑，没有ID就是新增
    QString s_name; // 科目名称
    QString create_time;
    QString update_time;

};

#endif // SUBJECT_H
