#ifndef CREATESUBJECTWINDOW_H
#define CREATESUBJECTWINDOW_H

#include <QWidget>
#include "mainwindow.h"
#include "service/addclassservice.h"

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
    AddClassService *acs = new AddClassService;
};

#endif // CREATESUBJECTWINDOW_H
