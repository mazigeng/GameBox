#include "tetrisdriver.h"
#include "tetrisdata.h"
#include <QTimer>
#include <QDebug>
#include "define.h"

TetrisDriver::TetrisDriver(TetrisData& d, QObject *parent) : QObject(parent), _datas(d)
{

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


void TetrisDriver::Solidify(const TetrisCell *cell)
{
    Q_ASSERT(cell);
    for (int i=0; i<cell->Size(); ++i)
    {
        QPoint pt = cell->Point(i);

        if(pt.x() >= 0 && pt.y() >= 0 && _datas.At(pt) < cell->GetDiamond())
            _datas.At(pt) = cell->GetDiamond();
    }
    emit DataChange();
}

void TetrisDriver::Solidify(const TetrisCell &cell)
{
    Solidify(&cell);
}


void TetrisDriver::Erasure(const TetrisCell *cell)
{
    Q_ASSERT(cell);
    for (int i=0; i<cell->Size(); ++i)
    {
        QPoint pt = cell->Point(i);
        if(pt.x() >= 0 && pt.y() >= 0 && _datas.At(pt) == cell->GetDiamond() )
            _datas.At(pt) = Blank;
    }
    emit DataChange();
}

void TetrisDriver::Erasure(const TetrisCell &cell)
{
    Erasure(&cell);
}

void TetrisDriver::UpdateCell(const TetrisCell *des, const TetrisCell *src)
{
    if(src)
        Erasure(src);

    if(des)
        Solidify(des);
}

