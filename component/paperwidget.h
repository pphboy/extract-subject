#ifndef PAPERWIDGET_H
#define PAPERWIDGET_H

#include <QWidget>
#include <QTextBrowser>
#include <QLabel>
#include <QScrollArea>
#include <QGridLayout>
#include <pojo/spaper.h>

class PaperWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaperWidget(QWidget *parent = nullptr);
    virtual void closeEvent(QCloseEvent *event);

    virtual void keyPressEvent(QKeyEvent *event);
    /**
     * @brief refreshPaper 刷新界面
     * @param pid
     */
    void refreshPaper(int pid);
    /**
     * @brief saveAnswer 保存答案
     */
    void saveAnswer(bool ok = true);

private:
    QLabel* paperTitle;
    QScrollArea *qsa;
    QGridLayout *paperPaint;
    QWidget* paperView;
    SPaper s;
    QTextBrowser *qtshow = nullptr;
signals:

};

#endif // PAPERWIDGET_H
