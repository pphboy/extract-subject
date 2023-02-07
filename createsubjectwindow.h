#ifndef CREATESUBJECTWINDOW_H
#define CREATESUBJECTWINDOW_H

#include <QWidget>
#include "mainwindow.h"
#include "config/subjectservice.h"
#include "pojo/subject.h"
#include <QSqlTableModel>
#include "addonesubjectdetail.h"

namespace Ui {
class CreateSubjectWindow;
}

class AddOneSubjectDetail;

class CreateSubjectWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CreateSubjectWindow(QWidget *parent = nullptr);
    ~CreateSubjectWindow();
    void setRealParent(MainWindow* p);
    MainWindow* getRealParent();
    /**
     * @brief 切换编辑窗口的标题，
     */
    void refreshSubjecTitle();
    /**
     * @brief 添加科目
     * @param name
     * @return
     */
    bool addSubject(QString name);
    /**
     * @brief 获Subject类型的指针
     * @return  Subject指针
     */
    Subject* getSubject();
    /**
     * @brief 刷新分类列表
     */
    void refreshCategoryList();
    void initCategoryList();
    void refreshTaskList();
    /**
     * @brief 初始化题目列表
     */
    void initTaskList();
protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_addCategory_clicked();
    void on_saveMajor_clicked();

    void on_addTask_clicked();

    void on_majorLineEdit_returnPressed();

    void on_delCategoryBtn_clicked();

    void on_deleteTaskBtn_clicked();

    void on_modifyCategoryBtn_clicked();

    void on_modifyTaskBtn_clicked();

private:
    /**
     * @brief 创建题目的窗口
     */
    AddOneSubjectDetail *asd = nullptr;
    Subject subject; // 这是一个共享的变量，用于存放当前科目的信息
    int windowStatus; // 窗口的状态
    Ui::CreateSubjectWindow *ui;
    MainWindow* realParent = nullptr;
    SubjectService subjectService;
    /**
     * @brief 这是分类的model
     */
    QSqlTableModel *model = nullptr;
    /**
     * @brief 题目的model
     */
    QSqlTableModel *taskModel = nullptr;
};

#endif // CREATESUBJECTWINDOW_H
