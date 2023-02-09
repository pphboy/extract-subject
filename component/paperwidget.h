#ifndef PAPERWIDGET_H
#define PAPERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QGridLayout>

class PaperWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaperWidget(QWidget *parent = nullptr);

    /**
     * @brief refreshPaper 刷新界面
     * @param pid
     */
    void refreshPaper(int pid);

private:
    QLabel* paperTitle;
    QScrollArea *qsa;
    QGridLayout *paperPaint;
    QWidget* paperView;
signals:

};

#endif // PAPERWIDGET_H
