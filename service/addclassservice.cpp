#include "addclassservice.h"

AddClassService::AddClassService()
{

}

bool AddClassService::addCategory(QString cname)
{
    qDebug()  << "添加成功: " << cname << endl;
    return cname.isEmpty();
}
