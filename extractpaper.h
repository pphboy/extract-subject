#ifndef EXTRACTPAPER_H
#define EXTRACTPAPER_H

#include <QWidget>
#include "pojo/subject.h"
#include "config/subjectservice.h"
#include "pojo/spaper.h"
#include "pojo/spapercategory.h"

namespace Ui {
class ExtractPaper;
}

class ExtractPaper : public QWidget
{
    Q_OBJECT

public:
    explicit ExtractPaper(QWidget *parent = nullptr);
    ~ExtractPaper();
    /**
     * @brief initCategoryList 初始化分类表
     */
    void initCategoryList();
    /**
     * @brief refreshCategoryList 刷新分类表
     */
    void refreshCategoryList();
    /**
     * @brief extractSubject 真正抽题的函数
     * @param spaper
     * @return
     */
    bool extractSubject(SPaper *spaper);
    // 不知道直接设置指针会不会出问题
    void setSubject(Subject *subject);
    virtual void showEvent(QShowEvent *event);
    virtual void closeEvent(QCloseEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ExtractPaper *ui;
    SubjectService subjectService;
    Subject *subject;
    QVector<Category*>  list;
};

#endif // EXTRACTPAPER_H
