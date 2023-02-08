#include "extractpaper.h"
#include "ui_extractpaper.h"

ExtractPaper::ExtractPaper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtractPaper)
{
    ui->setupUi(this);
}

ExtractPaper::~ExtractPaper()
{
    delete ui;
}
