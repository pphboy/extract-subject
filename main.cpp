#include "mainwindow.h"
#include "config/esutil.h"

#include <QApplication>

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
}
