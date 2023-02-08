#ifndef MAXLINEEDIT_H
#define MAXLINEEDIT_H

#include <QLineEdit>

class NumberLineEdit: public QLineEdit
{
public:
    explicit NumberLineEdit(QWidget *parent = nullptr);
    explicit NumberLineEdit(int maxNum,QWidget *parent = nullptr);

private:
    int maxNum;
};

#endif // MAXLINEEDIT_H
