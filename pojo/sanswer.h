#ifndef SANSWER_H
#define SANSWER_H

#include <QObject>

class SAnswer : public QObject
{
    Q_OBJECT
public:
    explicit SAnswer(QObject *parent = nullptr);

    void setPcid(int pcid) {this->pcid = pcid;};
    int getPcid()  {return this->pcid;};

    void setAid(int aid) {this->aid = aid;};
    int getAid()  {return this->aid;};

    void setTid(int tid) {this->tid = tid;};
    int getTid()  {return this->tid;};

    void setADetail(QString aDetail) {this->aDetail = aDetail;};
    QString getADetail()  {return this->aDetail;};

    void setCreateTime(QString createTime) {this->createTime = createTime;};
    QString getCreateTime()  {return this->createTime;};


private:
    int aid;
    int tid;
    int pcid;// 分类ID
    QString aDetail;
    QString createTime;

signals:

};

#endif // SANSWER_H
