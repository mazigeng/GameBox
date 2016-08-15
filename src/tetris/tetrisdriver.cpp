#include "tetrisdriver.h"
#include "tetrisdata.h"
#include <QTimer>
#include <QDebug>
#include <conio.h>
#include "keyboardmonitor.h"
#include <qt_windows.h>

TetrisDriver::TetrisDriver(TetrisData& d, QObject *parent) : QObject(parent), _datas(d)
{
    _km.start();
    connect(&_km,SIGNAL(KeyClicked(long)), this, SLOT(KeyControl(long)));
}

int TetrisDriver::AddCell(TetrisCell::Shape s, const QPoint &lt)
{
    TetrisCell cell(s);
    cell.SetLT(lt);

    ChangeDataValue(cell,1);

    emit DataChange(_datas);
    // 存储新添加的cell
    _cells.push_back(cell);
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
    else
        ChangeDataValue(cell,1);

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

    qDebug() << QString::number(vk,16);

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

