#include "tetriscell.h"
#include <QDebug>
#include <QRect>

TetrisCell::TetrisCell(TetrisCreator::Shape s, const QPoint &lt, QObject *parent) : QObject(parent), _s(s), _lt(lt), _rotaiton(0)
{
}

TetrisCell::TetrisCell(const TetrisCell &other) :  QObject(other.parent()), _s(other._s), _lt(other._lt), _rotaiton(other._rotaiton)
{

}

TetrisCell &TetrisCell::operator=(const TetrisCell &other)
{
    if(this != &other)
    {
        _s = other._s;
        _lt = other._lt;
        _rotaiton = other._rotaiton;
    }
    return *this;
}

QList<QPoint> TetrisCell::Points() const
{
    QList<QPoint> pts = TetrisCreator::CELLS[_s];
    for(int i=0; i<pts.size(); ++i)
    {
        TetrisCreator::ClockWise(_rotaiton,pts[i],TetrisCreator::ROTATE_CENTER[_s]);
        pts[i] += _lt;
    }
    return pts;
}

QPoint TetrisCell::Point(int i) const
{
    Q_ASSERT(i>=0 && i<Size());
    QPoint ret = TetrisCreator::CELLS[_s][i];

    TetrisCreator::ClockWise(_rotaiton,ret,TetrisCreator::ROTATE_CENTER[_s]);
    ret += _lt;

    return ret;
}

int TetrisCell::Size() const
{
    return TetrisCreator::CELLS[_s].size();
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
    foreach(const QPoint& pt, TetrisCreator::CELLS[_s])
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
    if(times != 0)
        _rotaiton = (_rotaiton + 1) % times;
}

void TetrisCell::ReRotate()
{
    int times = TetrisCreator::Times(_s);
    if(times != 0)
        _rotaiton = (_rotaiton - 1 + times) % times;
}
