#ifndef CREATESUBJECTWINDOW_H
#define CREATESUBJECTWINDOW_H

#include <QWidget>
#include "mainwindow.h"
#include "config/subjectservice.h"

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
    bool addSubject(QString name);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_addCategory_clicked();
    void on_saveMajor_clicked();

    void on_addSubject_clicked();

private:
    int windowStatus; // 窗口的状态
    Ui::CreateSubjectWindow *ui;
    MainWindow* realParent = nullptr;
    SubjectService subjectService;
};

#endif // CREATESUBJECTWINDOW_H
