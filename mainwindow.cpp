#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createsubjectwindow.h"
#include "config/daoconfig.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>

#include "config/esutil.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    DaoConfig::get()->sqlInit(); // sql 初始化
    // 单例套着单例
    // 初始化放这里了，肯定是单例
    if(EsUtil::CreateSubjectWindow == nullptr){
        EsUtil::CreateSubjectWindow = new CreateSubjectWindow(); // 初始化一个窗口
        EsUtil::MainWindow = this; // 把主窗口的指针拿来
        EsUtil::ExtractPaper = new ExtractPaper();
        this->ep = EsUtil::ExtractPaper;
        this->csw = EsUtil::CreateSubjectWindow;
        this->csw->setRealParent(this);// 设置主窗
    }

    ui->setupUi(this);
    // 设置窗口状态
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->setFixedSize(QSize(this->width(),this->height()));

    model = new QSqlTableModel(this);
    model->setTable("s_subject");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, tr("科目编号"));
    model->setHeaderData(1, Qt::Horizontal, tr("科目名称"));
    model->setHeaderData(2, Qt::Horizontal, tr("创建时间"));
    model->setHeaderData(3, Qt::Horizontal, tr("更新时间"));
    model->setHeaderData(4, Qt::Horizontal, tr("编辑"));

    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(2,140);
    ui->tableView->setColumnWidth(3,140);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableView->verticalHeader()->hide(); // 隐藏行号
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshSubjectList()
{
    model->select();
}


void MainWindow::on_createSubjectList_clicked()
{
    bool ok;
    QString text=  QInputDialog::getText(this, tr("添加科目"),
                                          tr("请输入分科目名"), QLineEdit::Normal,
                                          "", &ok,Qt::WindowFlags(),Qt::ImhDate);
    if(!text.isEmpty()){
        this->csw->addSubject(text);
        this->hide();
        this->csw->setRealParent(this);// 设置主窗
        this->csw->show();
    }else {
        QMessageBox::warning(this,tr("科目名错误"),tr("请输入正确的科目名"));
    }
}


/**
 * @brief MainWindow::on_checkSubjectBtn_clicked \n
 *  查看按钮
 */
void MainWindow::on_checkSubjectBtn_clicked()
{
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    if(index.row() == -1){
        QMessageBox::critical(this,"失败","请选择科目");
        return;
    }
    int subject_id = model->index(index.row(),0).data().toInt();
    // 0 位是 ID
    Subject *sb = subjectService.getSubjectById(subject_id);
    qDebug() << "科目ID: " << subject_id  << sb->getS_id() << sb->getS_name();
    this->csw->getSubject()->setS_id(sb->getS_id());
    this->csw->getSubject()->setS_name(sb->getS_name());
    this->csw->refreshSubjecTitle(); // 更新科目标题
    // 更新分类列表，更新题目列表
    this->csw->refreshCategoryList();
    this->csw->refreshTaskList();

    this->csw->show();
    this->hide();
}

void MainWindow::on_deleteSubjectBtn_clicked()
{
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    if(index.row() == -1){
        QMessageBox::critical(this,"失败","请选择科目");
        return;
    }
    int subject_id = model->index(index.row(),0).data().toInt();
    QString sname = model->index(index.row(),1).data().toString();

    bool ok;
    QString text=  QInputDialog::getText(this, tr("警告"),
                                          tr("删除数据后将不可恢复! \n删除请输入: %1").arg(sname), QLineEdit::Normal,
                                          "", &ok,Qt::WindowFlags(),Qt::ImhDate);
    if(text.compare(sname) == 0){
        subjectService.deleteSubjectById(subject_id);
        QMessageBox::information(this,"成功","删除题目成功!");
        refreshSubjectList();
    }else {
        QMessageBox::information(this,"真是一个名称的决定","您做了一个明智的决定，\n因为数据删除了就不可逆，\n我懒得写了");
    }

}

void MainWindow::on_modifySubjectBtn_clicked()
{
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    if(index.row() == -1){
        QMessageBox::critical(this,"失败","请选择科目");
        return;
    }
    int subject_id = model->index(index.row(),0).data().toInt();
    QString sname = model->index(index.row(),1).data().toString();

    bool ok;
    QString text=  QInputDialog::getText(this, tr("修改科目名"),
                                          tr("请修改如下科目名"), QLineEdit::Normal,
                                          sname, &ok,Qt::WindowFlags(),Qt::ImhDate);

    text.remove(QRegExp("\\s")); // 去除空格
    if(text.isEmpty()){
        QMessageBox::critical(this,"警告","科目名不能为空或空格");
    } else {
        // 反正都写了，可以重用
        ok = subjectService.updateSubjectTite(subject_id,text);
        if(ok){
            refreshSubjectList();
            QMessageBox::information(this,"成功","更新数据列表成功了");
        } else {
            QMessageBox::critical(this,"警告","懒得修,\n可能出BUG了,\n我相信我自己不会出现捏。");
        }
    }
}

void MainWindow::on_extractPaperBtn_clicked()
{
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    if(index.row() == -1){
        QMessageBox::critical(this,"失败","抽题需要选择科目");
        return;
    }
    int subject_id = model->index(index.row(),0).data().toInt();
    QString sname = model->index(index.row(),1).data().toString();
    Subject *s = new Subject(subject_id,sname);
    // 直接传了个指针
    this->ep->setSubject(s);
    this->ep->show();
    this->hide();
}
