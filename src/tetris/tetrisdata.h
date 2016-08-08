#ifndef TETRISDATA_H
#define TETRISDATA_H

#include <QObject>
#include <QVector>

class TetrisData : public QObject
{
    Q_OBJECT
public:
    explicit TetrisData(QObject *parent = 0);

signals:

public slots:

private:
    QVector<QVector<int> >  _datas;
    static const int DX = 10;
    static const int DY = 20;
};

#endif // TETRISDATA_H
