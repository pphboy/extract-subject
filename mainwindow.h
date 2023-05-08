#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSqlTableModel>
#include <QMainWindow>
#include "config/subjectservice.h"
#include "extractpaper.h"
#include "component/paperwidget.h"
#include <QTextBrowser>



class  CreateSubjectWindow;
QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
 }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /**
     * @brief refreshSubjectList
     * 刷新科目列表
     */
    void refreshSubjectList();
    /**
     * @brief initPaperWidget 初始化PaperWidget表结构
     */
    void initPaperWidget();
    /**
     * @brief refreshPaperWidget 刷新PaperWidget数据
     */
    void refreshPaperWidget();
    virtual void showEvent(QShowEvent *event);

private slots:
    void on_createSubjectList_clicked();

    void on_checkSubjectBtn_clicked();

    void on_deleteSubjectBtn_clicked();

    void on_modifySubjectBtn_clicked();

    void on_extractPaperBtn_clicked();

    void on_makeAnswerBtn_clicked();

    void on_helpAboutMenu_triggered();

private:
    QSqlTableModel *model;
    Ui::MainWindow *ui;
    QVector<SPaper*> plist;
    CreateSubjectWindow *csw = nullptr;
    ExtractPaper *ep = nullptr;
    SubjectService subjectService;
    PaperWidget* paperWidget;
    QTextBrowser *aboutWindows = nullptr;

};


#endif // MAINWINDOW_H
