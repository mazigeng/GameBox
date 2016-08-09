#ifndef TETRISDATA_H
#define TETRISDATA_H

#include <QObject>
#include <QVector>
#include <QSize>

class TetrisData : public QObject
{
    Q_OBJECT
public:
    explicit TetrisData(QObject *parent = 0);

    // 获得(x,y)元素的使用权限
    int& At(int x, int y);
    const int& At(int x, int y) const;

    // 获得棋盘尺寸
    QSize Size() const;

signals:

public slots:

private:
    QVector<QVector<int> >  _datas;
    static const int DX = 10;
    static const int DY = 20;
};

#endif // TETRISDATA_H
