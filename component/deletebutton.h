#ifndef DELETEBUTTON_H
#define DELETEBUTTON_H

#include <QPushButton>
#include <QWidget>
#include "config/esutil.h"

class DeleteButton : public QPushButton
{
public:
    explicit DeleteButton(int pid,QString title,QWidget *parent = nullptr);
    DeleteButton();
private:
    int pid;
};

#endif // DELETEBUTTON_H
