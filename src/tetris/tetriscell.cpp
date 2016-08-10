#include "tetriscell.h"
#include <QDebug>

const QMap<TetrisCell::Shape, QList<QPoint> > TetrisCell::CELLS(TetrisCell::InitCells());

TetrisCell::TetrisCell(Shape s, QObject *parent) : QObject(parent),_s(s)
{
}

TetrisCell::TetrisCell(const TetrisCell &other) : _s(other._s), QObject(other.parent())
{
}


const QList<QPoint> TetrisCell::Points() const
{
    return CELLS[_s];
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

