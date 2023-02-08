#include "numberlineedit.h"
#include <QRegExpValidator>
#include <QDebug>

NumberLineEdit::NumberLineEdit(QWidget *parent):QLineEdit(parent)
{
}

NumberLineEdit::NumberLineEdit(int maxNum, QWidget *parent):QLineEdit(parent)
{
    this->setText("0");// 默认值为0
    this->maxNum = maxNum;

    QRegExp regx("[0-9]+$");

    QValidator* validator = new QRegExpValidator(regx,this);
    this->setValidator(validator);

    QString numStr= tr("%1").arg(maxNum);
    // 设置最大长度
    this->setMaxLength(numStr.length());

    // 写的很好
    connect(this,&QLineEdit::textChanged,[=](QString num){
        int number = num.toInt();
        if(number > this->maxNum){
            this->setText(numStr);
        }
    });
}
