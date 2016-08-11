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
    cell.SetLT(newLT);              // 更改坐标
    ChangeDataValue(cell,1);        // 更新当前显示

    emit DataChange(_datas);
}

void TetrisDriver::KeyControl(long vk)
{
    QPoint offset(0,0);
    switch(vk)
    {
    case VK_LEFT: offset=QPoint(-1,0); break;
    case VK_UP: offset=QPoint(0,-1); break;
    case VK_RIGHT: offset=QPoint(1,0); break;
    case VK_DOWN: offset=QPoint(0,1); break;
    default:
        break;
    }

    // 取最后一个加入的，作为活动Cell
    if(_cells.size())
        MoveCell(_cells.size() - 1, _cells[_cells.size() - 1].LT() + offset);

    qDebug() << QString::number(vk,16);

}

void TetrisDriver::ChangeDataValue(const TetrisCell &cell, int value)
{
    const QList<QPoint> pts = cell.Points();
    for(int n=0; n<pts.size(); ++n)
    {
        _datas.At(pts[n] + cell.LT()) = value;
    }
}

