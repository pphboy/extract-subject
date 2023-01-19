#ifndef ADDONESUBJECTDETAIL_H
#define ADDONESUBJECTDETAIL_H

#include <QWidget>

namespace Ui {
class AddOneSubjectDetail;
}

class AddOneSubjectDetail : public QWidget
{
    Q_OBJECT

public:
    explicit AddOneSubjectDetail(QWidget *parent = nullptr);
    ~AddOneSubjectDetail();

private:
    Ui::AddOneSubjectDetail *ui;
};

#endif // ADDONESUBJECTDETAIL_H
