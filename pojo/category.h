#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>

class Category
{
public:
    Category();
    Category(int c_id, QString c_name):c_id(c_id), c_name(c_name) {};
    ~Category();
    int getC_id() {return this->c_id;};

private:
    int c_id;
    QString c_name;
};

#endif // CATEGORY_H
