#include "addonesubjectdetail.h"
#include "ui_addonesubjectdetail.h"

AddOneSubjectDetail::AddOneSubjectDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddOneSubjectDetail)
{
    ui->setupUi(this);
}

AddOneSubjectDetail::~AddOneSubjectDetail()
{
    delete ui;
}
