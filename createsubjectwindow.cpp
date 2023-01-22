#include "createsubjectwindow.h"
#include "ui_createsubjectwindow.h"
#include "qwidget.h"
#include "qlineedit.h"
#include "qdebug.h"
#include "qinputdialog.h"
#include "addonesubjectdetail.h"

CreateSubjectWindow::CreateSubjectWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateSubjectWindow)
{
    qDebug() << parent << endl;
    ui->setupUi(this);
    ui->currentMajorName->hide();
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->setFixedSize(this->width(),this->height());
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

bool CreateSubjectWindow::addSubject(QString name)
{
    this->ui->majorLineEdit->setText(name);
    this->subjectService.addSubject(name);
}

void CreateSubjectWindow::closeEvent(QCloseEvent *event)
{
    // 开启主窗口
    this->realParent->show();
}



void CreateSubjectWindow::on_addCategory_clicked()
{
    bool ok;
    QString text=  QInputDialog::getText(this, tr("添加分类"),
                                          tr("请输入分类名"), QLineEdit::Normal,
                                          "", &ok,Qt::WindowFlags(),Qt::ImhDate);
    this->subjectService.addSubject(text);

    qDebug() << text <<  text.isEmpty()  << ok << endl;
}


void CreateSubjectWindow::on_saveMajor_clicked()
{
    qDebug() << ui->majorLineEdit->text();
    ui->currentMajorName->setText(QString("科目名: ").append(ui->majorLineEdit->text()));
    ui->currentMajorName->show();
}


void CreateSubjectWindow::on_addSubject_clicked()
{
    AddOneSubjectDetail *asd = new AddOneSubjectDetail();
    asd->show();
    qDebug() << "添加一个题目" << endl;
}

