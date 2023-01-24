#ifndef DAOCONFIG_H
#define DAOCONFIG_H


#include <QSqlDatabase>
/**
 * @brief 配置数据库连接
 * @name 皮豪
 * @author 皮豪
 * @email pphboy@qq.com
 */
class DaoConfig
{
public:
    DaoConfig();
    void sqlInit();
    static DaoConfig *get(); // 使用单例模式
    QSqlDatabase getDB();
private:
    QSqlDatabase db;
};

#endif // DAOCONFIG_H
