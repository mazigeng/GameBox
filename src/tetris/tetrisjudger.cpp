#include "tetrisjudger.h"
#include <QList>
#include "tetrisdata.h"
#include <QPoint>

TetrisJudger::TetrisJudger(const TetrisData &d, QObject *parent) : QObject(parent), _d(d)
{

}

QList<int> TetrisJudger::Eliminate(const QList<QPoint> &pts, const QPoint& LT)
{
    QList<int> ret;
    foreach(const QPoint& pt, pts)
    {
        int y = pt.y() + LT.y();
        if (ret.contains(y))
            continue;
        ret.push_back(y);
        for(int x=0; x<_d.Size().width(); ++x)
        {
            if(_d.At(x,y) == 0)
            {
                ret.pop_back();
                break;
            }
        }
    }
    return ret;
}

