#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSqlTableModel>
#include <QMainWindow>



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

private slots:
    void on_createSubjectList_clicked();

    void on_checkSubjectBtn_clicked();

private:
    QSqlTableModel *model;
    Ui::MainWindow *ui;
    CreateSubjectWindow *csw = nullptr;

};
#endif // MAINWINDOW_H
