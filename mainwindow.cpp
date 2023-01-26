#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createsubjectwindow.h"
#include <QSqlTableModel>
#include "config/daoconfig.h"
#include <QInputDialog>
#include <QMessageBox>

#include "config/esutil.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    DaoConfig::get()->sqlInit(); // sql 初始化

    ui->setupUi(this);
    // 设置窗口状态
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->setFixedSize(QSize(this->width(),this->height()));

    QSqlTableModel *model;
    model = new QSqlTableModel(this);
    model->setTable("s_subject");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, tr("科目编号"));
    model->setHeaderData(1, Qt::Horizontal, tr("科目名称"));
    model->setHeaderData(2, Qt::Horizontal, tr("创建时间"));
    model->setHeaderData(3, Qt::Horizontal, tr("更新时间"));

    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(2,140);
    ui->tableView->setColumnWidth(3,140);
    ui->tableView->verticalHeader()->hide(); // 隐藏行号
//QTableView::horizontalHeader()->hide()//隐藏列头方法

//QTableView::verticalHeader()->hide()//隐藏行号方法


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_createSubjectList_clicked()
{
    bool ok;
    QString text=  QInputDialog::getText(this, tr("添加科目"),
                                          tr("请输入分科目名"), QLineEdit::Normal,
                                          "", &ok,Qt::WindowFlags(),Qt::ImhDate);
    // 单例
    if(this->csw==nullptr){
        this->csw = new CreateSubjectWindow();
        // 初始化在这里，之前的单例我不去解绝了，但后面的写法肯定是一开始就需要做一个全局变量把这些窗口的指针全部存起来
         EsUtil::CreateSubjectWindow = this->csw;
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

