#include "tetriscell.h"
#include <QDebug>
#include <QRect>

TetrisCell::TetrisCell(TetrisCreator::Shape s, const QPoint &lt, QObject *parent) : QObject(parent), _pts(TetrisCreator::CELLS[s]), _s(s), _lt(lt), _rotaiton(0)
{
}

TetrisCell::TetrisCell(const TetrisCell &other) :  QObject(other.parent()), _pts(other._pts), _s(other._s), _lt(other._lt), _rotaiton(0)
{

}

TetrisCell &TetrisCell::operator=(const TetrisCell &other)
{
    if(this != &other)
    {
        _pts = other._pts;
        _s = other._s;
        _lt = other._lt;
        _rotaiton = other._rotaiton;
    }
    return *this;
}

const QList<QPoint> TetrisCell::Points() const
{
    return _pts;
}

TetrisCreator::Shape TetrisCell::Shape() const
{
    return _s;
}

void TetrisCell::SetLT(const QPoint &lt)
{
    _lt = lt;
}

const QPoint &TetrisCell::LT() const
{
    return _lt;
}

QRect TetrisCell::Rect() const
{
    QRect ret(QPoint(10,10),QPoint(-10,-10));
    foreach(const QPoint& pt, _pts)
    {
        if(pt.x() < ret.left())
            ret.setLeft(pt.x());
        if(pt.x() > ret.right())
            ret.setRight(pt.x());
        if(pt.y() < ret.top())
            ret.setTop(pt.y());
        if(pt.y() > ret.bottom())
            ret.setBottom(pt.y());
    }
    return ret;
}





void TetrisCell::Rotate()
{
    int times = TetrisCreator::Times(_s);
    if(times == 2)
    {
        _rotaiton = (_rotaiton + 1) % times;
        for(int n=0; n<_pts.size(); ++n)
        {
            if(_rotaiton == 0)
                TetrisCreator::Anticlockwise(_pts[n], TetrisCreator::ROTATE_CENTER[_s]);
            else
                TetrisCreator::Clockwise(_pts[n], TetrisCreator::ROTATE_CENTER[_s]);
        }
    }
    else if(times == 4)
    {
        _rotaiton = (_rotaiton + 1) % times;
        for(int n=0; n<_pts.size(); ++n)
        {
            TetrisCreator::Clockwise(_pts[n],TetrisCreator::ROTATE_CENTER[_s]);
        }
    }

}

void TetrisCell::ReRotate()
{
    int times = TetrisCreator::Times(_s);
    if(times == 2)
    {
        Rotate();
    }
    else if(times == 4)
    {
        _rotaiton = (_rotaiton - 1 + times) % times;
        for(int n=0; n<_pts.size(); ++n)
        {
            TetrisCreator::Anticlockwise(_pts[n],TetrisCreator::ROTATE_CENTER[_s]);
        }
    }
}
