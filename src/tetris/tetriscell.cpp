#include "tetriscell.h"
#include <QDebug>


const QMap<TetrisCell::Shape, QList<QPoint> > TetrisCell::CELLS(TetrisCell::InitCells());
const QMap<TetrisCell::Shape, int> TetrisCell::ROTATE_TIMES(TetrisCell::InitRotateTimes());
const QMap<TetrisCell::Shape, QPoint> TetrisCell::ROTATE_CENTER(TetrisCell::InitRotateCenter());     // 形状旋转中心

TetrisCell::TetrisCell(Shape s, QObject *parent) : QObject(parent), _pts(CELLS[s]), _s(s), _lt(0,0), _rotaiton(0)
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

void TetrisCell::SetLT(const QPoint &lt)
{
    _lt = lt;
}

const QPoint &TetrisCell::LT() const
{
    return _lt;
}



int TetrisCell::Times() const
{
    return ROTATE_TIMES[_s];
}

void TetrisCell::Rotate()
{
    if(Times() == 2)
    {
        _rotaiton = (_rotaiton + 1) % Times();
        for(int n=0; n<_pts.size(); ++n)
        {
            if(_rotaiton == 0)
                Anticlockwise(_pts[n], ROTATE_CENTER[_s]);
            else
                Clockwise(_pts[n], ROTATE_CENTER[_s]);
        }
    }
    else if(Times() == 4)
    {
        _rotaiton = (_rotaiton + 1) % Times();
        for(int n=0; n<_pts.size(); ++n)
        {
            Clockwise(_pts[n],ROTATE_CENTER[_s]);
        }
    }

}

void TetrisCell::ReRotate()
{
    if(Times() == 2)
    {
        _rotaiton = (_rotaiton - 1 + Times()) % Times();
        for(int n=0; n<_pts.size(); ++n)
        {
            if(_rotaiton)
                Anticlockwise(_pts[n], ROTATE_CENTER[_s]);
            else
                Clockwise(_pts[n], ROTATE_CENTER[_s]);
        }
    }
    else if(Times() == 4)
    {
        _rotaiton = (_rotaiton - 1 + Times()) % Times();
        for(int n=0; n<_pts.size(); ++n)
        {
            Anticlockwise(_pts[n],ROTATE_CENTER[_s]);
        }
    }
}

void TetrisCell::Clockwise(QPoint &pt, const QPoint &center)
{
    pt -= center;

    int temp = pt.x();
    pt.setX(-pt.y());
    pt.setY(temp);

    pt += center;
}

void TetrisCell::Anticlockwise(QPoint &pt, const QPoint &center)
{
    pt -= center;

    int temp = pt.x();
    pt.setX(pt.y());
    pt.setY(-temp);

    pt += center;
}


QMap<TetrisCell::Shape, QList<QPoint> > TetrisCell::InitCells()
{
    QList<QPoint> O,T,L,J,I,S,Z;
    O << QPoint(0,0) << QPoint(1,0) << QPoint(0,1) << QPoint(1,1);
    T << QPoint(0,0) << QPoint(1,0) << QPoint(2,0) << QPoint(1,1);
    L << QPoint(0,0) << QPoint(0,1) << QPoint(0,2) << QPoint(1,2);
    J << QPoint(1,0) << QPoint(1,1) << QPoint(0,2) << QPoint(1,2);
    I << QPoint(0,0) << QPoint(0,1) << QPoint(0,2) << QPoint(0,3);
    S << QPoint(1,0) << QPoint(2,0) << QPoint(0,1) << QPoint(1,1);
    Z << QPoint(0,0) << QPoint(1,0) << QPoint(1,1) << QPoint(2,1);

    QMap<TetrisCell::Shape, QList<QPoint> > ret;
    ret.insert(TetrisCell::O,O);
    ret.insert(TetrisCell::T,T);
    ret.insert(TetrisCell::L,L);
    ret.insert(TetrisCell::J,J);
    ret.insert(TetrisCell::I,I);
    ret.insert(TetrisCell::S,S);
    ret.insert(TetrisCell::Z,Z);

    return ret;
}

QMap<TetrisCell::Shape, int> TetrisCell::InitRotateTimes()
{
    QMap<TetrisCell::Shape, int> ret;
    ret.insert(TetrisCell::O,0);
    ret.insert(TetrisCell::T,4);
    ret.insert(TetrisCell::L,4);
    ret.insert(TetrisCell::J,4);
    ret.insert(TetrisCell::I,2);
    ret.insert(TetrisCell::S,2);
    ret.insert(TetrisCell::Z,2);

    return ret;
}

QMap<TetrisCell::Shape, QPoint> TetrisCell::InitRotateCenter()
{
    QMap<TetrisCell::Shape, QPoint> ret;
    ret.insert(TetrisCell::O,QPoint(0,0));
    ret.insert(TetrisCell::T,QPoint(1,0));
    ret.insert(TetrisCell::L,QPoint(1,1));
    ret.insert(TetrisCell::J,QPoint(0,1));
    ret.insert(TetrisCell::I,QPoint(0,1));
    ret.insert(TetrisCell::S,QPoint(1,0));
    ret.insert(TetrisCell::Z,QPoint(1,0));

    return ret;
}

