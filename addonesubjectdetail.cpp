#include "addonesubjectdetail.h"
#include "ui_addonesubjectdetail.h"
#include "config/esutil.h"
#include "config/daoconfig.h"
#include <QDebug>
#include "createsubjectwindow.h"
#include <QMessageBox>

AddOneSubjectDetail::AddOneSubjectDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddOneSubjectDetail)
{
    ui->setupUi(this);
    // 设置query
    query = DaoConfig::get()->query();

    // 初始化 分类下拉选项框 // showEvent会做
//    initCategoryList();
}

AddOneSubjectDetail::~AddOneSubjectDetail()
{
    delete ui;
}

int AddOneSubjectDetail::initCategoryList()
{
    query->prepare("select * from s_category where s_id = ?");
    query->bindValue(0,EsUtil::CreateSubjectWindow->getSubject()->getS_id());
    bool ok = query->exec();
    qDebug() << "select s_category query: " << ok;
    // 如果查询成功则直接清除categoryBox的数据
    if(ok){
        // Note: If you have set an external model on the combobox this model will still be cleared when calling this function.
        ui->categoryBox->clear();
        // remove the orignal
        cateList.clear();
    }

    while(query->next()){
        // 将查到的数据包装成category实例，插到cateList列表中
        // 这个数据目前只是保存下来，没有什么用，还没到优化的地步，而且这个玩意是个GUI，用一次查一次也问题不大
        // 并且只拿到的是内存
        cateList.push_back(new Category(query->value("c_id").toInt(),query->value("c_name").toString()));
        // 将数据显示到
        ui->categoryBox->addItem(query->value("c_name").toString(),QVariant(query->value("c_id").toInt()));
    }

    // 用完后清除，这是习惯
    query->clear();
    // 返回长度，用来判断
    return cateList.length();
}

void AddOneSubjectDetail::showEvent(QShowEvent *event)
{
    qDebug() << "刷新 Category 列表 ";
    initCategoryList();
}

void AddOneSubjectDetail::updateTaskDoc(Task *t)
{
    task.setT_id(t->getT_id());
    task.setT_content(t->getT_content());
    task.setT_description(t->getT_description());
    // 更新组件内的数据
    ui->questionEdit->setHtml(task.getT_content());
    ui->answerEdit->setHtml(task.getT_description());
    // 按理来说还需要复现这个 分类的选择
    qDebug() << "编辑 t_id = " << t->getT_id() << " c_id = " << t->getC_id();

    // 下拉菜单应当选择 该题目原本的分类
    int index = ui->categoryBox->findData(QVariant(t->getC_id()));
    qDebug()  << "设置Index = " << index;
    ui->categoryBox->setCurrentIndex(index);
}

/**
 * @brief AddOneSubjectDetail::on_saveButton_clicked
 */
void AddOneSubjectDetail::on_saveButton_clicked()
{
    qDebug() << ui->categoryBox->currentData().toInt();
    qDebug() << "Quest : " << ui->questionEdit->document()->isEmpty();
    qDebug() << "Quest : " << ui->questionEdit->document()->toRawText();

    if(!ui->categoryBox->currentData().isValid()){
        // 没有选择类，无法添加
        QMessageBox::critical(this,"警示","请选择分类");
        return;
    }

    if(ui->questionEdit->document()->isEmpty() || ui->answerEdit->document()->isEmpty()){
        QMessageBox::critical(this,"警示","请输入正确的题目和答案");
        return;
    }

    // 获取框框的数据

    task.setC_id(ui->categoryBox->currentData().toInt());

    task.setT_title(ui->questionEdit->document()->toRawText());
    task.setT_content(ui->answerEdit->toHtml());
    task.setT_answer(ui->answerEdit->document()->toRawText());
    task.setT_description(ui->questionEdit->toHtml()); // description 是描述,也就是题目

    // t_id = -1 时为新增 ， 为其他值时是编辑
    bool ok;
    if(task.getT_id() == -1){
        ok = subjectService.addTask(&task); // 2023年01月30日 加上了 这个答案的简单版
    } else {
        // 编辑数据
        ok = subjectService.updateTaskById(&task);
    }

    // 判断是否插入成功
    if(ok){
        // 还需要刷新题目列表
        QMessageBox::information(this,"成功",tr("%1题目成功").arg(task.getT_id() == -1 ? "添加":"编辑"));
        // 刷新题目列表
        EsUtil::CreateSubjectWindow->refreshTaskList();
        // 清除数据
        ui->questionEdit->clear();
        ui->answerEdit->clear();
        ui->categoryBox->clear();

        task.setT_id(-1);
        // 隐藏子窗口，打开父窗口
        this->hide();
    } else {
        QMessageBox::critical(this,"错误",tr("%1题目失败").arg(task.getT_id() == -1 ? "添加":"编辑"));
    }
}
