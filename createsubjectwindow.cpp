#include "createsubjectwindow.h"
#include "ui_createsubjectwindow.h"
#include "qwidget.h"
#include "qlineedit.h"
#include "qdebug.h"
#include "qinputdialog.h"
#include "config/esutil.h"
#include <QDebug>
#include <QMessageBox>
#include "pojo/task.h"

CreateSubjectWindow::CreateSubjectWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateSubjectWindow)
{
    if(asd == nullptr){
        asd = new AddOneSubjectDetail();
        EsUtil::AddOneSubjectDetail = asd; // 直接在初始化的时候保存指针，太强了CPP
    }

    qDebug() << parent << endl;
    ui->setupUi(this);
    ui->currentMajorName->hide();
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->setFixedSize(this->width(),this->height());
    // 默认刷新一次
    initCategoryList();
    initTaskList();


    ui->categoryView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->categoryView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->taskView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->taskView->setSelectionMode(QAbstractItemView::SingleSelection);

}


CreateSubjectWindow::~CreateSubjectWindow()
{
    delete ui;
}

void CreateSubjectWindow::setRealParent(MainWindow * tmp)
{
    this->realParent = tmp;
}

MainWindow * CreateSubjectWindow::getRealParent()
{
    return this->realParent;
}

void CreateSubjectWindow::refreshSubjecTitle()
{
    // 设置 科目 和ID
    this->ui->currentMajorName->setText(tr("科目名: %1  科目ID: %2").arg(subject.getS_name()).arg(subject.getS_id()));
    this->ui->currentMajorName->show();
    this->ui->majorLineEdit->setText(subject.getS_name());// 更新编辑框的标题
}

/**
 * @brief 添加科目类
 * @param name
 * @return
 */
bool CreateSubjectWindow::addSubject(QString name)
{
    bool ok = this->subjectService.addSubject(name);
    // 如果添加成功就设置窗口的标题和科目Label
    if(ok){
        refreshSubjecTitle();
        refreshTaskList();
        refreshCategoryList();
    }
    return ok;
}

/**
 * @brief 就直接返回地址
 * @return
 */
Subject *CreateSubjectWindow::getSubject()
{
    return &subject;
}

/**
 * @brief CreateSubjectWindow::refreshCategoryList
 * 刷新分类列表
 *
 */
void CreateSubjectWindow::refreshCategoryList()
{
    model->setFilter(tr("s_id=%1").arg(subject.getS_id()));
}

void CreateSubjectWindow::refreshTaskList()
{
    taskModel->setFilter(tr("s_id=%1").arg(subject.getS_id()));
}

/**
 * @brief 初始化分类表
 */
void CreateSubjectWindow::initCategoryList()
{
    // 刷新成功
    // 需要拿到分类的数据，重新设置这个categoryView
    if(model == nullptr) model = new QSqlTableModel(this);

    model->setTable("s_category");
    // 设置为当前的subject的子分类
    model->setFilter(tr("s_id=%1").arg(subject.getS_id()));
    qDebug() << "Subject Id = " << subject.getS_id();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    qDebug() << "Category Model RowCount" << model->rowCount();

    model->setHeaderData(2, Qt::Horizontal, tr("分类名称"));
    model->setHeaderData(3, Qt::Horizontal, tr("创建时间"));

    ui->categoryView->setModel(model);
    ui->categoryView->verticalHeader()->hide(); // 隐藏行号
    ui->categoryView->setColumnHidden(0,true); // 隐藏编号一列
    ui->categoryView->setColumnHidden(1,true); // 隐藏分类编号
    ui->categoryView->setColumnHidden(4,true); // 隐藏编辑时间

}


void CreateSubjectWindow::initTaskList()
{
    if(taskModel == nullptr) taskModel = new QSqlTableModel(this);

    taskModel->setTable("s_task");
    // 设置为当前的subject的子分类
    taskModel->setFilter(tr("s_id=%1").arg(subject.getS_id()));
    qDebug() << "Subject Id = " << subject.getS_id();
    taskModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    taskModel->select();

    qDebug() << "Model RowCount" << taskModel->rowCount();

    for (int i = taskModel->rowCount(); i >= 0; i--) {
//        qDebug() << taskModel->data(i);
    }

    taskModel->setHeaderData(3, Qt::Horizontal, tr("题目描述"));
    taskModel->setHeaderData(4, Qt::Horizontal, tr("答案"));
    taskModel->setHeaderData(7,Qt::Horizontal,tr("创建时间"));

    ui->taskView->setModel(taskModel);
    ui->taskView->verticalHeader()->hide(); // 隐藏行号
    ui->taskView->setColumnHidden(0,true); // 隐藏编号一列
    ui->taskView->setColumnHidden(1,true); // 隐藏C_ID
    ui->taskView->setColumnHidden(2,true); // 隐藏S_ID
    ui->taskView->setColumnHidden(5,true); // 隐藏标题HTML
    ui->taskView->setColumnHidden(6,true); // 隐藏内容HTML
    ui->taskView->setColumnHidden(8,true); // 隐藏编辑时间
}


void CreateSubjectWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "Close EVent";


    // 开启主窗口
    this->realParent->show();
    // 关注窗口的时候清除列表的数据
    // 清除题目数据
    taskModel->removeRows(0,taskModel->rowCount());
    // 清除分类数据
    model->removeRows(0,model->rowCount());
    // 更新父窗口的列表
    EsUtil::MainWindow->refreshSubjectList();

}


/**
 * @brief CreateSubjectWindow::on_addCategory_clicked
 */
void CreateSubjectWindow::on_addCategory_clicked()
{
    bool ok;
    QString text=  QInputDialog::getText(this, tr("添加分类"),
                                          tr("请输入分类名"), QLineEdit::Normal,
                                          "", &ok,Qt::WindowFlags(),Qt::ImhDate);
    text.remove(QRegExp("\\s")); // 除去空格
    if(!text.isEmpty()){
        // 在这里传一个 Subject对象过去，这个对象可以当作编辑状态，也可以当作新增的状态
        // createSubject同时只能主导一个Subject对象
        this->subjectService.addCategory(text,subject.getS_id());
        qDebug() << text <<  text.isEmpty()  << ok << endl;
    }
    // 如果text为空就啥也不干
}


void CreateSubjectWindow::on_saveMajor_clicked()
{
    QString s_name = ui->majorLineEdit->text().remove(QRegExp("\\s"));
    qDebug() << tr("change s_name=%1").arg(s_name);
    subjectService.updateSubjectTite(subject.getS_id(),s_name);
    subject.setS_name(s_name);
    this->ui->currentMajorName->setText(tr("科目名: %1  科目ID: %2").arg(subject.getS_name()).arg(subject.getS_id()));
}

void CreateSubjectWindow::on_majorLineEdit_returnPressed()
{
    // 直接调用
    on_saveMajor_clicked();
}


void CreateSubjectWindow::on_addTask_clicked()
{
    // 拿到 categoryList的数据，判断一下是否可以打开，如果不能打开，就提示需要添加分类
    int length = asd->initCategoryList();
    qDebug() << tr("length = %1").arg(length);
    if(length < 1){
        QMessageBox::critical(this, "警示","你还没有添加分类，请先添加分类后再添加题目");
        return;
    }
    qDebug() << "点击了添加题目的窗口" << endl;
    asd->show();
}


void CreateSubjectWindow::on_delCategoryBtn_clicked()
{
    QModelIndex qmi = ui->categoryView->selectionModel()->currentIndex();
    if(qmi.row() == -1){
        QMessageBox::critical(this,"失败","请选择分类!");
        return;
    }
    // 获取ID直接删除
    int categoryId = model->index(qmi.row(),0).data().toInt();
    // 直接把0和1转成bool值
    bool ok = ! QMessageBox::information(this,"提示","删除分类会连同题目一起删除，是否确认删除？","确认","取消");
//    qDebug() << "a =" << ok;
    if(ok){
        subjectService.deleteCagegoryById(categoryId);
        refreshTaskList();
        refreshCategoryList();
        QMessageBox::information(this,"成功","删除分类和题目数据成功!");
    }
}

void CreateSubjectWindow::on_deleteTaskBtn_clicked()
{
    QModelIndex qmi = ui->taskView->selectionModel()->currentIndex();
    if(qmi.row() == -1){
        QMessageBox::critical(this,"失败","请选择题目!");
        return;
    }
    // 获取ID直接删除
    int taskId= taskModel->index(qmi.row(),0).data().toInt();
    // 直接把0和1转成bool值
    bool ok = ! QMessageBox::information(this,"提示","删除题目后将无法恢复，确认删除？","确认","取消");
//    qDebug() << "a =" << ok;
    if(ok){
        subjectService.deleteTaskById(taskId);
        refreshTaskList();
        QMessageBox::information(this,"成功","删除题目成功!");
    }
}

/**
 * @brief CreateSubjectWindow::on_modifyCategoryBtn_clicked
 * 修改分类
 */
void CreateSubjectWindow::on_modifyCategoryBtn_clicked()
{
    QModelIndex qmi = ui->categoryView->selectionModel()->currentIndex();
    if(qmi.row() == -1){
        QMessageBox::critical(this,"失败","请选择分类!");
        return;
    }
    int cid = model->index(qmi.row(),0).data().toInt();
    QString cname = model->index(qmi.row(),2).data().toString();

    bool ok;
    QString text=  QInputDialog::getText(this, tr("修改分类"),
                                          tr("编辑下列文本即可修改分类名"), QLineEdit::Normal,
                                          cname, &ok,Qt::WindowFlags(),Qt::ImhDate);
    text.remove(QRegExp("\\s")); // 除去空格
    if(!text.isEmpty()){
        // text才是修改后的分类名
        qDebug() << subjectService.updateCategoryById(cid,text);
        refreshCategoryList();
    }else {
        QMessageBox::critical(this,"警告","分类名不能为空，需要编辑请重新填写");
    }
}

void CreateSubjectWindow::on_modifyTaskBtn_clicked()
{
    QModelIndex qmi = ui->taskView->selectionModel()->currentIndex();
    if(qmi.row() == -1){
        QMessageBox::critical(this,"失败","请选择题目!");
        return;
    }
    // 获取ID直接删除
    int taskId= taskModel->index(qmi.row(),0).data().toInt();
    int categoryId= taskModel->index(qmi.row(),1).data().toInt();
    QString questionHtml = taskModel->index(qmi.row(),5).data().toString();
    QString answerHtml= taskModel->index(qmi.row(),6).data().toString();

    Task* tmp= new Task(taskId,questionHtml,answerHtml);
    tmp->setC_id(categoryId); // 需要 设置分类的ID，以便初始窗口的时候直接选择这个分类
    this->asd->show();
    // 更新一定要在showEvent之后，不然设置数据后又重置了
    this->asd->updateTaskDoc(tmp);
}
