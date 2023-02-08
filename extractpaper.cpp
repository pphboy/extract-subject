#include "extractpaper.h"
#include "ui_extractpaper.h"
#include <QDebug>
#include <QCheckBox>
#include "component/numberlineedit.h"
#include "config/esutil.h"
#include <QMessageBox>
#include "config/esutil.h"
#include "config/daoconfig.h"

using namespace std;

ExtractPaper::ExtractPaper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtractPaper)
{
    ui->setupUi(this);
    // 初始化
    initCategoryList();

}

ExtractPaper::~ExtractPaper()
{
    delete ui;
    delete subject;
}

void ExtractPaper::showEvent(QShowEvent *event)
{
    // 设置标题
    this->setWindowTitle(tr("抽卷界面 科目：%1 ").arg(subject->getS_name()));
    ui->subjectName->setText(tr("科目：%1 ").arg(subject->getS_name()));

    // 每次进入窗口的时候都需要把之前的数据清除了
    // 如果不为0，就清除第一行，让其一直清除第一行就行，这是个动态的表
    while(ui->categoryTableWidget->rowCount() != 0){
        ui->categoryTableWidget->removeRow(0);
    }

    // 更新数据需要放到最后面
    refreshCategoryList();
}

void ExtractPaper::closeEvent(QCloseEvent *event)
{
    EsUtil::MainWindow->show();
}

void ExtractPaper::initCategoryList()
{
    ui->categoryTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);// 选择一行
//    ui->categoryTableWidget->setSelectionModel(QAbstractItemView::SingleSelection); // 只能单选
    ui->categoryTableWidget->setColumnCount(4); // 设置列数
    ui->categoryTableWidget->resizeColumnToContents(0); // 自动调节宽度
    ui->categoryTableWidget->resizeColumnsToContents(); // 行高与内容高度相匹配
    QHeaderView* wl = ui->categoryTableWidget->horizontalHeader();
    wl->resizeSection(0,35);
    wl->resizeSection(1,150);
    wl->resizeSection(2,60);
    wl->setStretchLastSection(true);
    QStringList list;
    list << "选项" << "分类名" << "抽取数量" << "题目数量";
    ui->categoryTableWidget->setHorizontalHeaderLabels(list);
}

void ExtractPaper::refreshCategoryList()
{
    list =  subjectService.getCategoryListBySubjectId(subject->getS_id());

    // 使用 for i 是为了让在保存的时候拿的数据能够直接根据索引进行获取
    for(int i = 0;i < list.size(); i++){
        ui->categoryTableWidget->insertRow(i);

        ui->categoryTableWidget->setCellWidget(i,0,new QCheckBox);
        ui->categoryTableWidget->setItem(i,1,new QTableWidgetItem((list)[i]->getCname()));
        NumberLineEdit *nle = new NumberLineEdit((list)[i]->getTaskNum());
        ui->categoryTableWidget->setCellWidget(i,2,nle);
        ui->categoryTableWidget->setItem(i,3,new QTableWidgetItem(tr("%1").arg((list)[i]->getTaskNum())));
    }
}


void ExtractPaper::setSubject(Subject *subject)
{
    this->subject = subject;
}

void ExtractPaper::on_pushButton_clicked()
{
    // 判断是否输入了标题
    QString text = ui->titleLineEdit->text(); // 去除空格
    text.remove(QRegExp("\\s"));
    ui->titleLineEdit->setText(text);

    if(ui->titleLineEdit->text().isEmpty()){
        QMessageBox::critical(this,"错误","试卷标题不能带空格，且不能为空");
        return;
    }

    int count = 0;
    bool haveZero = false;
    // 设置 s_id
    SPaper *spaper = new SPaper(subject->getS_id(),ui->titleLineEdit->text());


    // 获取列表的状态
    for(int i = 0 ; i < ui->categoryTableWidget->rowCount();i++){
     // 为0的是不计入统计
        if(dynamic_cast<QCheckBox*>(ui->categoryTableWidget->cellWidget(i,0))->checkState() == Qt::Checked ){
            QString str = dynamic_cast<QLineEdit*>(ui->categoryTableWidget->cellWidget(i,2))->text();
            if(str.toInt() == 0){
                haveZero = true;
            }else {
                count ++;
                qDebug() << list[i]->getCname() << " num = " << str.toInt();
                spaper->getCategoryList()->push_back(new SPaperCategory(list[i]->getC_id(),str.toInt()));
            }
        }
    }
    if(haveZero){
        if(count !=0){
            QMessageBox::information(this,"警告","有些题目你选择了，但数量是0\n这样的题目是不计入抽题的。");
        }else {
            QMessageBox::information(this,"警告","至少选择一个分类，请输入数量");
            return;
        }
    }

    if(count == 0){
        QMessageBox::information(this,"警告","至少选择一个分类，并输入数量");
    }else {
        // 抽题
        extractSubject(spaper);
    }

}

/**
 * @brief ExtractPaper::extractSubject 抽题函数
 * @param spaper
 * @return
 */
bool ExtractPaper::extractSubject(SPaper *spaper)
{
    // 开始事务
    DaoConfig::get()->getDB().transaction();

    // 插入spaper
    // pid 会直接设置到spaper
    subjectService.addSPaper(spaper);

    for(auto scg: *(spaper->getCategoryList())){
        // 在插入之前需要拿到 paper id，paper id直接设置到 scg里
        scg->setPid(spaper->getPid());
        // 插入分类
        subjectService.addSPaperCategory(scg);
        // 获取分类下的所有题目
        QVector<Task*> taskList = subjectService.getTaskListByCid(scg->getCid());
//        qDebug() << "taskList size" << taskList.size();
        // 生成题目，需要有分类id，相当于是指定哪个分类生成多少个题目就行，需要插入PCID
        QVector<int> indexList = EsUtil::extract(scg->getNum(),taskList.size());
        for(auto a: indexList){
            // 插入数据，插入数据的时候需要用到t_id题目ID 和 pc_id 分类ID
            subjectService.addSPaperAnswer(new SAnswer(taskList[a]->getT_id(),scg->getPcid()));
        }
    }

    // 反正没有执行到这一步都直接不提交
    DaoConfig::get()->getDB().commit();

    EsUtil::MainWindow->show(); // 打开主窗口
    this->hide(); // 隐藏窗口，等待下次使用

    // clear 清理
    ui->titleLineEdit->setText("");
    subject->setS_id(-1);
}

