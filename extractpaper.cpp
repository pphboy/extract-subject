#include "extractpaper.h"
#include "ui_extractpaper.h"
#include <QDebug>
#include <QCheckBox>
#include "component/numberlineedit.h"
#include "config/esutil.h"

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
     // 获取列表的状态
     for(int i = 0 ; i < ui->categoryTableWidget->rowCount();i++){
         qDebug() << list[i]->getCname() << dynamic_cast<QCheckBox*>(ui->categoryTableWidget->cellWidget(i,0))->checkState()
         << dynamic_cast<QLineEdit*>(ui->categoryTableWidget->cellWidget(i,2))->text();
     }
}
