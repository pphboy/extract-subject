#include "paperwidget.h"
#include <QPushButton>
#include <QTextEdit>
#include <QTextBrowser>

PaperWidget::PaperWidget(QWidget *parent) : QWidget(parent)
{
//    this->setFixedSize(700,800);
    this->resize(700,800);

    QPushButton *saveBtn = new QPushButton("保存",this);
    saveBtn->move(this->width()-75,0);

    paperTitle = new QLabel("卷子名",this);
    paperTitle->move(this->width()/2,0);
    paperTitle->setStyleSheet("font-size:20px;");

    qsa = new QScrollArea(this);
    qsa->setFixedSize(700,700);

    qsa->move(0,100);

    paperView = new QWidget; // 题目显示的窗口

    paperPaint = new QGridLayout; // 题目显示的布局，就是把一些细节插入到内

    paperView->setLayout(paperPaint);

    paperPaint->addWidget(new QLabel("填空题",paperView));
    QTextEdit *qte = new QTextEdit;
    paperPaint->addWidget(qte);
    qte->setFixedWidth(680);
    qte->setReadOnly(true); // 只读
    qte->setText("hello");

    QTextBrowser *qtb = new QTextBrowser;
    qtb->setHtml("<h1>你好啊</h1>");
    paperPaint->addWidget(qtb);

    // 一个题目，一个输入框，把题目的 列表的索引与 输入框的索引对应起来就行

    qsa->setWidget(paperView);

}

void PaperWidget::refreshPaper(int pid)
{

}
