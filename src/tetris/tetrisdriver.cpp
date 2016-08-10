#include "tetrisdriver.h"
#include "tetrisdata.h"

TetrisDriver::TetrisDriver(TetrisData& d, QObject *parent) : QObject(parent), _datas(d)
{

}

int TetrisDriver::AddCell(TetrisCell::Shape s, const QPoint &lt)
{
    TetrisCell cell(s);

    const QList<QPoint> pts = cell.Points();
    for(int n=0; n<pts.size(); ++n)
    {
        _datas.At(pts[n] + lt) = 1;
    }

    // 存储新添加的cell
    _cells.push_back(cell);
    return _cells.size() - 1;
}

