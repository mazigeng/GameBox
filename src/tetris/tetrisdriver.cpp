#include "tetrisdriver.h"
#include "tetrisdata.h"
#include <QTimer>
#include <QDebug>
#include <conio.h>
#include "keyboardmonitor.h"
#include <qt_windows.h>

TetrisDriver::TetrisDriver(TetrisData& d, QObject *parent) : QObject(parent), _datas(d), _dropTimer(this)
{
    _km.start();
    connect(&_km,SIGNAL(KeyClicked(long)), this, SLOT(KeyControl(long)));
    connect(&_dropTimer, SIGNAL(timeout()), this, SLOT(DropActive()));
}

int TetrisDriver::AddCell(TetrisCell::Shape s, const QPoint &lt)
{
    TetrisCell cell(s);
    cell.SetLT(lt);

    ChangeDataValue(cell,1);

    emit DataChange(_datas);
    // 存储新添加的cell
    _cells.push_back(cell);
    //_dropTimer.start(700);
    return _cells.size() - 1;
}

void TetrisDriver::MoveCell(int index, const QPoint &newLT)
{
    Q_ASSERT(_cells.size() > index && index >= 0);
    TetrisCell& cell = _cells[index];

    ChangeDataValue(cell,0);        // 擦除当前显示

    // 探测新位置是否有障碍。
    if(IsSpacious(cell.Points(), newLT))
    {
        cell.SetLT(newLT);              // 更改坐标
        ChangeDataValue(cell,1);        // 更新当前显示

        emit DataChange(_datas);
    }
    else    // 有障碍不能放置
    {
        ChangeDataValue(cell,1);
        QPoint offset = newLT - cell.LT();
        if(offset.y() > 0 )
            DropEnd();
    }

}

void TetrisDriver::RotateCell(int index)
{
    Q_ASSERT(_cells.size() > index && index >= 0);
    TetrisCell& cell = _cells[index];

    ChangeDataValue(cell,0);        // 擦除当前显示
    cell.Rotate();


    if(!IsSpacious(cell.Points(),cell.LT()))
        cell.ReRotate();

    ChangeDataValue(cell,1);        // 更新当前显示
    emit DataChange(_datas);

}

void TetrisDriver::RemoveLine(const QList<int> &lines)
{
    QList<int> sorted = lines;
    qSort(sorted);
    for(int n=0; n<sorted.size(); ++n)
    {
        _datas.RemoveLine(sorted.at(n));
    }
}


void TetrisDriver::KeyControl(long vk)
{
    if(_cells.size() <= 0)
        return;

    int index = _cells.size() - 1;
    const TetrisCell& cell= _cells[index];

    switch(vk)
    {
    case VK_LEFT:  MoveCell(index,cell.LT() + QPoint(-1,0)); break;
    case VK_UP: RotateCell(index); break;
    case VK_RIGHT: MoveCell(index,cell.LT() + QPoint(1,0)); break;
    case VK_DOWN: MoveCell(index,cell.LT() + QPoint(0,1)); break;
    default:
        break;
    }


}

void TetrisDriver::DropActive()
{
    if(_cells.size() > 0)
        MoveCell(_cells.size() - 1,_cells.last().LT() + QPoint(0,1));
}

void TetrisDriver::ChangeDataValue(const TetrisCell &cell, int value)
{
    const QList<QPoint> pts = cell.Points();
    foreach (QPoint pt, pts)
    {

        _datas.At(pt + cell.LT()) = value;
    }
}

bool TetrisDriver::IsSpacious(const QList<QPoint> &pts, const QPoint &lt, int value) const
{
    foreach(const QPoint& pt, pts)
    {
        QPoint ptAt = pt + lt;
        if(ptAt.x() < 0 || ptAt.x() >= _datas.Size().width() ||
           ptAt.y() < 0 || ptAt.y() >= _datas.Size().height() ||
           _datas.At(ptAt) != value)
            return false;
    }
    return true;
}

void TetrisDriver::DropEnd()
{
    _dropTimer.stop();
    if(_cells.size())
    {
        TetrisCell cell = _cells.takeLast();
        emit MoveEnd(cell);
    }
}

