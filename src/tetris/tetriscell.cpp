#include "tetriscell.h"
#include <QDebug>
#include <QRect>

TetrisCell::TetrisCell(TetrisCreator::Shape s, const QPoint &lt, int rotation, Diamond d, QObject *parent) : QObject(parent), _s(s), _lt(lt), _rotaiton(rotation), _diamond(d)
{
}

TetrisCell::TetrisCell(const TetrisCell &other) :  QObject(other.parent()), _s(other._s), _lt(other._lt), _rotaiton(other._rotaiton), _diamond(other._diamond)
{

}

TetrisCell &TetrisCell::operator=(const TetrisCell &other)
{
    if(this != &other)
    {
        _s = other._s;
        _lt = other._lt;
        _rotaiton = other._rotaiton;
        _diamond = other._diamond;
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

void TetrisCell::SetDiamond(Diamond d)
{
    _diamond = d;
}

Diamond TetrisCell::GetDiamond() const
{
    return _diamond;
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
    for(int i=0; i<Size(); ++i)
    {
        const QPoint pt = Point(i);
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

QPoint TetrisCell::RelativeZero() const
{
    QRect rc = Rect();
    return QPoint((rc.left() >= 0 ? 0 : -rc.left()), (rc.top() >= 0 ? 0 : -rc.top()));

}

int TetrisCell::Rotation() const
{
    return _rotaiton;
}

void TetrisCell::SetRotation(int r)
{
    _rotaiton = r;
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


void TetrisCell::Move(Direction d, int step)
{
    QPoint offset;
    switch (d)
    {
    case Left: offset=QPoint(-step,0); break;
    case Up: offset=QPoint(0,-step); break;
    case Right: offset=QPoint(step,0); break;
    case Down: offset=QPoint(0,step); break;
    default:
        break;
    }

    Move(offset);
}

void TetrisCell::Move(const QPoint &offset)
{
    SetLT(LT() + offset);
}

