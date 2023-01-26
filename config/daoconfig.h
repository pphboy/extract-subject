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
    QSqlQuery* query();
    /**
     * @brief 打开DB
     */
    void open();
    ~DaoConfig();
private:
    QSqlDatabase db;
    QSqlQuery *queryPtr = nullptr;
};

#endif // DAOCONFIG_H
