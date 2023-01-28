#ifndef ADDONESUBJECTDETAIL_H
#define ADDONESUBJECTDETAIL_H

#include <QWidget>
#include <QSqlQuery>
#include "pojo/category.h"
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

private slots:

    void on_saveButton_clicked();

private:
    Ui::AddOneSubjectDetail *ui;
    QSqlQuery *query;
    QVector<Category*> cateList;
    SubjectService subjectService;
};

#endif // ADDONESUBJECTDETAIL_H
