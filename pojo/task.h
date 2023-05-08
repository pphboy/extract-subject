#ifndef TASK_H
#define TASK_H


#include <QTextEdit>
#include <QString>
#include "component/texteditdiv.h"


class Task
{
public:
    Task();
    Task(int t_id):t_id(t_id){};
    /**
     * @brief Task 在查询卷子的时候需要用到
     * @param t_id
     * @param aid
     */
    Task(int t_id,int aid):t_id(t_id),aid(aid){};
    Task(int t_id,QString t_content,QString t_description):t_id(t_id),t_content(t_content),t_description(t_description){};

    Task(int t_id,int c_id,QString t_content,QString t_description,QString t_title,QString t_answer)
        :t_id(t_id),t_content(t_content),t_description(t_description),c_id(c_id),t_title(t_title),t_answer(t_answer){};

    // 简单的getter/setter就在这里写了
    int getT_id() {return this->t_id;};
    void setT_id(int t_id){this->t_id = t_id;};
    int getC_id() {return this->c_id;};
    void setC_id(int cid){this->c_id = cid;};

    QString getT_content(){return this->t_content;};
    void setT_content(QString content){this->t_content = content;};
    void setT_description(QString t_description){this->t_description = t_description;};
    QString getT_description(){return this->t_description;};
    void setT_title(QString t_title) {this->t_title = t_title;};
    QString getT_title(){return this->t_title;};
    void setT_answer(QString t_answer){this->t_answer = t_answer;};
    QString getT_answer(){return this->t_answer;};
    // 用来保存答案的ID
    void setAid(int aid) {this->aid = aid;};
    int getAid()  {return this->aid;};
    TextEditDiv* getQte(){return this->qte;};
    void setQte(TextEditDiv* qte){this->qte = qte;};


private:
    int t_id = -1;
    int c_id;
    int s_id;
    // 题目里存答案的ID，就只是用来保存答案用的，没其他用处，这里设计有点小问题
    int aid;
    QString t_title;
    QString t_answer;
    QString t_description;
    QString t_content;
    QString create_time;
    QString update_time;
    /**
     * @brief 答案的输入框
     */
    TextEditDiv *qte;
};

#endif // TASK_H
