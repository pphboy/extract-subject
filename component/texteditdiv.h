#ifndef TEXTEDITDIV_H
#define TEXTEDITDIV_H

#include <QObject>

#include <QWidget>
#include <QTextEdit>
#include <QTextBrowser>

class Task;

class TextEditDiv : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEditDiv(Task *task,QWidget *parent = nullptr);
    virtual void keyPressEvent(QKeyEvent *e) override;
    void setQtShow(QTextBrowser *qtshow) { this->qtshow = qtshow;};

private:
    /**
     * @brief qtshow 用于使用快捷键Ctrl+t 显示 答案
     */
    QTextBrowser *qtshow = nullptr;
    bool qtshowStatus = false;
    Task *task = nullptr;


signals:

};

#endif // TEXTEDITDIV_H
