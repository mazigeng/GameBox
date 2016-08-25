#include "tetriscreator.h"
#include <QTime>

const QMap<TetrisCreator::Shape, QList<QPoint> > TetrisCreator::CELLS(TetrisCreator::InitCells());
const QMap<TetrisCreator::Shape, int> TetrisCreator::ROTATE_TIMES(TetrisCreator::InitRotateTimes());
const QMap<TetrisCreator::Shape, QPoint> TetrisCreator::ROTATE_CENTER(TetrisCreator::InitRotateCenter());     // 形状旋转中心

TetrisCreator::Shape TetrisCreator::RandShape()
{
    QTime t;
    if(t.msecsSinceStartOfDay() == 0)
    {
        t = QTime::currentTime();
        qsrand(t.msecsSinceStartOfDay());
    }

    return static_cast<TetrisCreator::Shape>(qrand() % TetrisCreator::Z);
}

void TetrisCreator::Clock90(QPoint &pt, const QPoint &center)
{
    pt -= center;

    int temp = pt.x();
    pt.setX(-pt.y());
    pt.setY(temp);

    pt += center;
}

void TetrisCreator::Clock180(QPoint &pt, const QPoint &center)
{
    pt -= center;

    pt.setX(-pt.x());
    pt.setY(-pt.y());

    pt += center;
}

void TetrisCreator::Clock270(QPoint &pt, const QPoint &center)
{
    pt -= center;

    int temp = pt.x();
    pt.setX(pt.y());
    pt.setY(-temp);

    pt += center;
}

void TetrisCreator::ClockWise(int rotation, QList<QPoint> &pts, const QPoint &center)
{
    typedef void (*Clockfunc)(QPoint &pt, const QPoint &center);
    Clockfunc func = NULL;

    switch(rotation % 4)
    {
    case 1: func = Clock90; break;
    case 2: func = Clock180; break;
    case 3: func = Clock270; break;
    default:
        return;
    }

    for(int n=0; n<pts.size(); ++n)
    {
        func(pts[n],center);
    }
}

void TetrisCreator::ClockWise(int rotation, QPoint &pt, const QPoint &center)
{
    switch(rotation % 4)
    {
    case 1: Clock90(pt, center); break;
    case 2: Clock180(pt, center); break;
    case 3: Clock270(pt, center); break;
    default:
        return;
    }
}



int TetrisCreator::Times(TetrisCreator::Shape s)
{
    return ROTATE_TIMES[s];
}



QMap<TetrisCreator::Shape, QList<QPoint> > TetrisCreator::InitCells()
{
    QList<QPoint> O,T,L,J,I,S,Z;
    O << QPoint(0,0) << QPoint(1,0) << QPoint(0,1) << QPoint(1,1);
    T << QPoint(0,0) << QPoint(1,0) << QPoint(2,0) << QPoint(1,1);
    L << QPoint(0,0) << QPoint(0,1) << QPoint(0,2) << QPoint(1,2);
    J << QPoint(1,0) << QPoint(1,1) << QPoint(0,2) << QPoint(1,2);
    I << QPoint(0,0) << QPoint(0,1) << QPoint(0,2) << QPoint(0,3);
    S << QPoint(1,0) << QPoint(2,0) << QPoint(0,1) << QPoint(1,1);
    Z << QPoint(0,0) << QPoint(1,0) << QPoint(1,1) << QPoint(2,1);

    QMap<TetrisCreator::Shape, QList<QPoint> > ret;
    ret.insert(TetrisCreator::O,O);
    ret.insert(TetrisCreator::T,T);
    ret.insert(TetrisCreator::L,L);
    ret.insert(TetrisCreator::J,J);
    ret.insert(TetrisCreator::I,I);
    ret.insert(TetrisCreator::S,S);
    ret.insert(TetrisCreator::Z,Z);

    return ret;
}

QMap<TetrisCreator::Shape, int> TetrisCreator::InitRotateTimes()
{
    QMap<TetrisCreator::Shape, int> ret;
    ret.insert(TetrisCreator::O,0);
    ret.insert(TetrisCreator::T,4);
    ret.insert(TetrisCreator::L,4);
    ret.insert(TetrisCreator::J,4);
    ret.insert(TetrisCreator::I,2);
    ret.insert(TetrisCreator::S,2);
    ret.insert(TetrisCreator::Z,2);

    return ret;
}

QMap<TetrisCreator::Shape, QPoint> TetrisCreator::InitRotateCenter()
{
    QMap<TetrisCreator::Shape, QPoint> ret;
    ret.insert(TetrisCreator::O,QPoint(0,0));
    ret.insert(TetrisCreator::T,QPoint(1,0));
    ret.insert(TetrisCreator::L,QPoint(1,1));
    ret.insert(TetrisCreator::J,QPoint(0,1));
    ret.insert(TetrisCreator::I,QPoint(0,1));
    ret.insert(TetrisCreator::S,QPoint(1,0));
    ret.insert(TetrisCreator::Z,QPoint(1,0));

    return ret;
}
