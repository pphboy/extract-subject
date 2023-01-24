#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createsubjectwindow.h"
#include "config/daoconfig.h"
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 设置窗口状态
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->setFixedSize(QSize(this->width(),this->height()));

    DaoConfig::get()->sqlInit(); // sql 初始化

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_createSubjectList_clicked()
{
    bool ok;
    QString text=  QInputDialog::getText(this, tr("添加分类"),
                                          tr("请输入分类名"), QLineEdit::Normal,
                                          "", &ok,Qt::WindowFlags(),Qt::ImhDate);
    // 单例
    if(this->csw==nullptr){
        this->csw = new CreateSubjectWindow();
    }
    if(!text.isEmpty()){
        this->csw->addSubject(text);
        this->hide();
        this->csw->setRealParent(this);// 设置主窗
        this->csw->show();
    }else {
        QMessageBox::warning(this,tr("科目名错误"),tr("请输入正确的科目名"));
    }
}

