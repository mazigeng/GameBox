#include "tetrisdata.h"
#include <QPoint>

TetrisData::TetrisData(QObject *parent) : QObject(parent), _datas(DX,QVector<int>(DY,0))
{
}

int &TetrisData::At(int x, int y)
{
    Q_ASSERT(x<DX && x>=0 && y<DY && y>=0);
    return _datas[x][y];
}

int &TetrisData::At(const QPoint &xy)
{
    return At(xy.x(),xy.y());
}

const int &TetrisData::At(int x, int y) const
{
    Q_ASSERT(x<DX && x>=0 && y<DY && y>=0);
    return _datas[x][y];
}

void TetrisData::RemoveLine(int y)
{
    for(int x=0; x<DX; ++x)
    {
        _datas[x].remove(y);
        _datas[x].insert(0,0);
    }
}

int TetrisData::indexOfY(int x, int value, int from)
{
    Q_ASSERT(x>=0 && x<_datas.size());
    return _datas[x].indexOf(value,from);

}



QSize TetrisData::Size() const
{
    return QSize(DX,DY);
}



