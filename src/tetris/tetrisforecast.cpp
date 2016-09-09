#include "tetrisforecast.h"

TetrisForecast::TetrisForecast(QObject *parent) : QObject(parent), _data(4,4*3)
{

}

void TetrisForecast::Enqueue(const TetrisCell& cell)
{
    _qCell.enqueue(cell);

    _qCell.last().Move(QPoint(0,4*2));
    // 保证绘制在最低下
    for(int y=0; y<4; ++y)
    {
        _data.RemoveLine(0,false);
    }

    foreach(const QPoint& pt, _qCell.last().Points())
    {
        _data.At(pt) = Cell;
    }
    emit DataChange();
}

TetrisCell TetrisForecast::Dequeue()
{
    return _qCell.dequeue();
}

const TetrisData &TetrisForecast::data()
{
    return _data;
}

