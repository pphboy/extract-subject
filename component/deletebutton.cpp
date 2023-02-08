#include "deletebutton.h"
#include <QDebug>
#include <QMessageBox>

DeleteButton::DeleteButton(int pid,QString title,QWidget *parent):pid(pid),QPushButton(parent)
{
    this->setText(title);

    connect(this,&DeleteButton::clicked,[=]{
        // 删除的槽函数
        int a = QMessageBox::information(this,"警告","您正在删除试卷，删除后数据将不可恢复!","确认","取消");
        if(a==0){
            EsUtil::subjectService->deleteSPaperById(this->pid);
            // 刷新列表
            EsUtil::MainWindow->refreshPaperWidget();
        }
    });
}

DeleteButton::DeleteButton()
{

}
