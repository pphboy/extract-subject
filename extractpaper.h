#ifndef EXTRACTPAPER_H
#define EXTRACTPAPER_H

#include <QWidget>

namespace Ui {
class ExtractPaper;
}

class ExtractPaper : public QWidget
{
    Q_OBJECT

public:
    explicit ExtractPaper(QWidget *parent = nullptr);
    ~ExtractPaper();

private:
    Ui::ExtractPaper *ui;
};

#endif // EXTRACTPAPER_H
