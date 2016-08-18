#include "tetrisdriver.h"
#include "tetrisdata.h"
#include <QTimer>
#include <QDebug>

TetrisDriver::TetrisDriver(TetrisData& d, QObject *parent) : QObject(parent), _datas(d), _active(NULL),_prediction(NULL), _dropTimer(this)
{
    connect(&_dropTimer, SIGNAL(timeout()), this, SLOT(Drop()));
}

void TetrisDriver::AddCell(TetrisCreator::Shape s, const QPoint &lt)
{
    Q_ASSERT(_active == NULL);
    _active = new TetrisCell(s,lt,this);

    Predict();
    SolidifyValue(Cell);
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
    bool ret = false;

    // 探测新位置是否有障碍。
    if(IsSpacious(_active->Points(), _active->LT() + offset))
    {
        SolidifyValue(Blank);        // 擦除
        _active->SetLT(_active->LT() + offset);              // 更改坐标

        Predict();
        SolidifyValue(Cell);        // 更新当前显示

        emit DataChange();
        ret = true;
    }

    return ret;
}

void TetrisDriver::DropFinish()
{
    Q_ASSERT(_active);
    Q_ASSERT(_prediction);
    SolidifyValue(Blank);
    _active->SetLT(_prediction->LT());
    Drop();
}

bool TetrisDriver::Rotate()
{
    Q_ASSERT(_active);
    bool ret=true;

    SolidifyValue(Blank);
    _active->Rotate();

    if(!IsSpacious(_active->Points(),_active->LT()))
    {
        if(!Adjust())
        {
            _active->ReRotate();
            ret = false;
        }
    }

    Predict();
    SolidifyValue(Cell);        // 更新当前显示

    if(ret)
    {
        emit DataChange();
    }

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
    {

        emit DataChange();
    }
}

const TetrisCell *TetrisDriver::Active()
{
    return _active;
}

void TetrisDriver::Solidify()
{
    ClearPredict();
    SolidifyValue(Background);
    _active = NULL;
}


void TetrisDriver::SolidifyValue(Diamond v)
{
    Q_ASSERT(_active);
    SolidifyValue(_active,v);
}

void TetrisDriver::SolidifyValue(TetrisCell *cell, Diamond v)
{
    Q_ASSERT(cell);
    foreach (QPoint pt, cell->Points())
    {
        _datas.At(pt + cell->LT()) = v;
    }
}

bool TetrisDriver::IsSpacious(const QList<QPoint> &pts, const QPoint &lt, Diamond value) const
{
    foreach(const QPoint& pt, pts)
    {
        QPoint ptAt = pt + lt;
        if(ptAt.x() < 0 || ptAt.x() >= _datas.Size().width() ||
           ptAt.y() < 0 || ptAt.y() >= _datas.Size().height() ||
           _datas.At(ptAt) == value)
            return false;
    }
    return true;
}

bool TetrisDriver::Adjust()
{
    Q_ASSERT(_active);
    QPoint lt = _active->LT();
    // 左移一格调整
    _active->SetLT(lt + QPoint(-1,0));
    if(IsSpacious(_active->Points(), _active->LT()))
        return true;

    // 右移一格调整
    _active->SetLT(lt + QPoint(1,0));
    if(IsSpacious(_active->Points(), _active->LT()))
        return true;

    // 对于I形状，我们特殊处理，允许它再右移一次。
    if(_active->Shape() == TetrisCreator::I)
    {
        // 右移二格调整
        _active->SetLT(lt + QPoint(2,0));
        if(IsSpacious(_active->Points(), _active->LT()))
            return true;
    }

    _active->SetLT(lt);
    return false;

}

void TetrisDriver::Predict()
{
    Q_ASSERT(_active);
    QPoint PreLt(_active->LT().x(), _datas.Size().height());

    foreach(const QPoint& pt, _active->Points())
    {
        int i = _datas.indexOfY(pt.x() + _active->LT().x(),Background, pt.y() + _active->LT().y());
        i = (i == -1 ? _datas.Size().height() : i);

        int offset = i - pt.y() - _active->LT().y() - 1;

        QPoint newLt = _active->LT() + QPoint(0,offset);

        if(IsSpacious(_active->Points(),newLt))
        {
            if(PreLt.y() > newLt.y())
                PreLt = newLt;
        }
    }


    // 显示
    if(PreLt != _active->LT())
    {
        if(_prediction)
        {
            ClearPredict();
        }
        _prediction = new TetrisCell(*_active);
        _prediction->SetLT(PreLt);
        SolidifyValue(_prediction,Prediction);
    }

}

void TetrisDriver::ClearPredict()
{
    if(_prediction)
    {
        SolidifyValue(_prediction,Blank);
        delete _prediction;
        _prediction = NULL;
    }

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

