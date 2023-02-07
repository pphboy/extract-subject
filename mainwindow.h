#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSqlTableModel>
#include <QMainWindow>
#include "config/subjectservice.h"



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

private slots:
    void on_createSubjectList_clicked();

    void on_checkSubjectBtn_clicked();

    void on_deleteSubjectBtn_clicked();

    void on_modifySubjectBtn_clicked();

private:
    QSqlTableModel *model;
    Ui::MainWindow *ui;
    CreateSubjectWindow *csw = nullptr;
    SubjectService subjectService;

};
#endif // MAINWINDOW_H
