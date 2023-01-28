#include "mainwindow.h"
#include <QApplication>
#include "config/esutil.h"
#include "config/daoconfig.h"
#include <QDebug>

void testing();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    testing();

    return a.exec();
}


/**
 * @brief 测试类
 */
void testing(){
//    下面是一些类的执行代码
    EsUtil::getCurrentFormatData();

    DaoConfig::get()->query()->exec("select * from s_category");
    DaoConfig::get()->query()->next();
    qDebug() << "DaoConfig " << DaoConfig::get()->query()->value("c_id").toString();
    qDebug() << "DaoConfig " << DaoConfig::get()->query()->value("c_name").toString();

}
