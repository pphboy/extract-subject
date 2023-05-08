#include "texteditdiv.h"

#include <QDebug>
#include "pojo/task.h"

#include <QKeyEvent>
TextEditDiv::TextEditDiv(Task *task, QWidget *parent):task(task),QTextEdit(parent)
{

}

void TextEditDiv::keyPressEvent(QKeyEvent *e)
{
    if(e->modifiers() == Qt::ControlModifier){
        if(e->key() == Qt::Key_T){
            // 如果qtshowStatus为false则需要打开窗口
            qtshow->setHtml(task->getT_content());
            qtshow->setWindowFlags(Qt::WindowStaysOnTopHint);
            qtshow->setWindowTitle("答案显示框");
            qtshow->setMinimumWidth(450);
            qtshow->show();
        }
    }
    QTextEdit::keyPressEvent(e);
}
