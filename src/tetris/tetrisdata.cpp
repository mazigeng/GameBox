#include "tetrisdata.h"
#include <QPoint>
#include <QDebug>

TetrisData::TetrisData(int w, int h, QObject *parent) : QObject(parent), W(w), H(h),_datas(w,QVector<Diamond>(h,Blank))
{
}

Diamond &TetrisData::At(int x, int y)
{
    Q_ASSERT(x<W && x>=0 && y<H && y>=0);
    return _datas[x][y];
}

Diamond &TetrisData::At(const QPoint &xy)
{
    return At(xy.x(),xy.y());
}

const Diamond &TetrisData::At(int x, int y) const
{
    Q_ASSERT(x<W && x>=0 && y<H && y>=0);
    return _datas[x][y];
}


const Diamond &TetrisData::At(const QPoint &xy) const
{
    return At(xy.x(),xy.y());
}

void TetrisData::RemoveLine(int y, bool down)
{
    for(int x=0; x<W; ++x)
    {
        _datas[x].remove(y);
        _datas[x].insert(down ? 0 : _datas[x].size(),Blank);
    }
}

int TetrisData::indexOfY(int x, Diamond value, int from) const
{
    Q_ASSERT(x>=0 && x<_datas.size());
    return _datas[x].indexOf(value,from);

}

void TetrisData::Fill(Diamond value)
{
    for(int y=0; y<_datas.size(); ++y)
    {
        _datas[y].fill(value);
    }
}



QSize TetrisData::Size() const
{
    return QSize(W,H);
}




