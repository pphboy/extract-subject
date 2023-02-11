#include "paperwidget.h"
#include <QPushButton>
#include <config/esutil.h>
#include <QTextEdit>
#include <math.h>
#include <QTextBrowser>
#include <QDebug>
#include <QMessageBox>

PaperWidget::PaperWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(700,800);

    QPushButton *saveBtn = new QPushButton("保存",this);
    saveBtn->move(this->width()-75,0);

    // 绑定槽
    connect(saveBtn,&QPushButton::clicked,this,&PaperWidget::saveAnswer);

    paperTitle = new QLabel("卷子名",this);
    paperTitle->setStyleSheet("font-size:20px;");
    paperTitle->move(0,2);

    qsa = new QScrollArea(this);
    qsa->setFixedSize(700,760);
    qsa->move(0,40);

}

void PaperWidget::closeEvent(QCloseEvent *event)
{
    EsUtil::MainWindow->show();
    this->hide();
}

void PaperWidget::refreshPaper(int pid)
{

    // 把题目查出来
    // 这个玩意，每次显示的时候都需要重新绘制，不然就出问题
    paperView = new QWidget; // 题目显示的窗口
    paperView->setMinimumHeight(700);
    paperPaint = new QGridLayout; // 题目显示的布局，就是把一些细节插入到内
    paperView->setLayout(paperPaint);

    s = EsUtil::subjectService->getSPaperById(pid);

    this->setWindowTitle(tr("《%1》卷子详细页").arg(s.getPname()));
    this->paperTitle->setText(tr("《%1》 注意：写完要保存，没写自动保存").arg(s.getPname()));


    QTextBrowser *qtshow = new QTextBrowser;
    qDebug() << s.getPname();
    int height;
    for(auto a: s.getCategoryTaskList()){
        QLabel *t = new QLabel(a->getCname());
        t->setStyleSheet("font-size:20px");
        // 分类
        paperPaint->addWidget(t);
        for(auto t: a->getTaskList()){
            paperPaint->addWidget(new QLabel(""));
            height = ceil(t->getT_title().size()/40.00)*26;
            // 题目
            // 这是一个空格
            QTextBrowser *qtb = new QTextBrowser;
            qtb->setHtml(t->getT_description());
            qtb->setFixedSize(qsa->width()-35,height);
            paperPaint->addWidget(qtb);
            // 显示答案的按钮
            QPushButton* qb = new QPushButton("显示答案");
            connect(qb,&QPushButton::clicked,[=](){
                qtshow->setHtml(t->getT_content());
                qtshow->setWindowFlags(Qt::WindowStaysOnTopHint);
                qtshow->setWindowTitle("答案显示框");
                qtshow->show();
            });
            paperPaint->addWidget(qb);

            // 这个应该在查询的时候就初始化好了，因为我需要设置答案
            t->getQte()->setFixedWidth(qsa->width()-35);
            paperPaint->addWidget(t->getQte());

        }
    }

    qsa->setWidget(paperView);
}

void PaperWidget::saveAnswer()
{
    for(auto a: s.getCategoryTaskList()){
        for(auto t: a->getTaskList()){
            EsUtil::subjectService->savePaperAnswer(t);
        }
    }
    QMessageBox::information(this,"成功","您的答案保存成功");
}
