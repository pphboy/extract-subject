#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createsubjectwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 设置窗口状态
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->setFixedSize(QSize(this->width(),this->height()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_createSubjectList_clicked()
{
    // 单例
    if(this->csw==nullptr){
        this->csw = new CreateSubjectWindow();
    }
    this->hide();
    this->csw->setRealParent(this);// 设置主窗
    this->csw->show();

}

