#ifndef ADDONESUBJECTDETAIL_H
#define ADDONESUBJECTDETAIL_H

#include <QWidget>
#include <QSqlQuery>
#include "pojo/category.h"
#include "pojo/task.h"
#include "config/subjectservice.h"

namespace Ui {
class AddOneSubjectDetail;
}

class AddOneSubjectDetail : public QWidget
{
    Q_OBJECT

public:
    explicit AddOneSubjectDetail(QWidget *parent = nullptr);
    ~AddOneSubjectDetail();
    int initCategoryList();
    virtual void showEvent(QShowEvent *event);
    virtual void closeEvent(QCloseEvent *event);
    void updateTaskDoc(Task *task);

private slots:

    void on_saveButton_clicked();

private:
    Task task;
    Ui::AddOneSubjectDetail *ui;
    QSqlQuery *query;
    QVector<Category*> cateList;
    SubjectService subjectService;
};

#endif // ADDONESUBJECTDETAIL_H
