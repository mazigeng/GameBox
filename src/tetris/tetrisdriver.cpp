#include "tetrisdriver.h"
#include "tetrisdata.h"
#include <QTimer>
#include <QDebug>

TetrisDriver::TetrisDriver(TetrisData& d, QObject *parent) : QObject(parent), _datas(d), _active(NULL), _dropTimer(this)
{
    connect(&_dropTimer, SIGNAL(timeout()), this, SLOT(Drop()));
}

void TetrisDriver::AddCell(TetrisCreator::Shape s, const QPoint &lt)
{
    Q_ASSERT(_active == NULL);
    _active = new TetrisCell(s,lt,this);

    SolidifyValue(1);
    emit DataChange();
}

void TetrisDriver::Drop(bool on)
{
    if(on)
        _dropTimer.start(700);
    else
        _dropTimer.stop();
}

bool TetrisDriver::Move(TetrisDriver::Direction d)
{
    Q_ASSERT(_active);
    QPoint offset;
    switch (d)
    {
    case Left: offset=QPoint(-1,0); break;
    case Up: offset=QPoint(0,-1); break;
    case Right: offset=QPoint(1,0); break;
    case Down: offset=QPoint(0,1); break;
    default:
        break;
    }

    return Move(offset);
}

bool TetrisDriver::Move(const QPoint &offset)
{
    Q_ASSERT(_active);
    bool ret = true;

    SolidifyValue(0);

    // 探测新位置是否有障碍。
    if(IsSpacious(_active->Points(), _active->LT() + offset))
    {
        _active->SetLT(_active->LT() + offset);              // 更改坐标
        SolidifyValue(1);        // 更新当前显示

        emit DataChange();
        ret = true;
    }
    else    // 有障碍不能放置
    {
        SolidifyValue(1);
        ret = false;
    }

    return ret;
}

bool TetrisDriver::Rotate()
{
    Q_ASSERT(_active);
    bool ret=true;

    SolidifyValue(0);
    _active->Rotate();

    if(!IsSpacious(_active->Points(),_active->LT()))
    {
        _active->ReRotate();
        ret = false;
    }

    SolidifyValue(1);        // 更新当前显示

    if(ret)
        emit DataChange();

    return ret;
}


void TetrisDriver::RemoveLine(const QList<int> &lines)
{
    QList<int> sorted = lines;
    qSort(sorted);
    for(int n=0; n<sorted.size(); ++n)
    {
        _datas.RemoveLine(sorted.at(n));
    }

    if(lines.size())
        emit DataChange();
}

const TetrisCell *TetrisDriver::Active()
{
    return _active;
}

void TetrisDriver::Solidify()
{
    if(_active)
        delete _active;
    _active = NULL;
}


void TetrisDriver::SolidifyValue(int v)
{
    Q_ASSERT(_active);
    foreach (QPoint pt, _active->Points())
    {
        _datas.At(pt + _active->LT()) = v;
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


void TetrisDriver::Drop()
{
    if(_active)
    {
        if(!Move(Down))
        {
            _dropTimer.stop();
            emit DropEnd();
        }
    }
    else
        _dropTimer.stop();
}

