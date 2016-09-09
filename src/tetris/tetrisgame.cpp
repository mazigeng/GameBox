#include "tetrisgame.h"
#include "tetriscell.h"
#include <qt_windows.h>
#include "keyboardmonitor.h"
#include <QDebug>


TetrisGame::TetrisGame(QObject *parent) :
    QObject(parent),
    _data(10,20),
    _forecast(),
    _driver(_data),
    _out(_data,_forecast.data()),
    _judger(_data),
    _pause(false),
    _dropTimer(this),
    _prediction(_data,this),
    _active(NULL)
{
    _km.start();
    connect(&_km,SIGNAL(KeyClicked(long)), this, SLOT(KeyControl(long)));
    connect(&_driver, SIGNAL(DataChange()), &_out, SLOT(Repaint()));
    connect(&_forecast, SIGNAL(DataChange()), &_out, SLOT(Repaint()));
    //connect(&_dropTimer, SIGNAL(timeout()), this, SLOT(Drop()));
    connect(&_prediction, SIGNAL(NewPredict(const TetrisCell*,const TetrisCell*)), &_driver, SLOT(UpdateCell(const TetrisCell*,const TetrisCell*)));
}

void TetrisGame::Start()
{
    _forecast.Enqueue(TetrisCell(TetrisCreator::T,QPoint(0,0),1));
    _forecast.Enqueue(TetrisCreator::RandCell());
    _forecast.Enqueue(TetrisCreator::RandCell());
    AddCell();
}

void TetrisGame::Pause()
{
    _dropTimer.stop();
    _pause = true;
}

void TetrisGame::Resume()
{
    if(_dropTimer.isActive())
        _dropTimer.start(700);
    _pause = false;
}


void TetrisGame::AddCell()
{
    _active = new TetrisCell(_forecast.Dequeue());
    _active->SetLT(QPoint(0,0));
    _forecast.Enqueue(TetrisCreator::RandCell());
    _active->SetLT(QPoint(_data.Size().width() / 2, 0) + _active->RelativeZero());

    _driver.Solidify(_active);



    if(!_judger.IsSpacious(*_active))
        emit GameOver();
    else
    {
        _dropTimer.start(700);
        _prediction.Predict(_active);

    }

    emit DataChange();
}



void TetrisGame::DropBottom()
{
    Q_ASSERT(_active);
    TetrisCell prediction = _prediction.CurPrediction();

    if(prediction.LT() != _active->LT())
    {
        _driver.Erasure(_active);
        _active->SetLT(prediction.LT());
        _driver.Solidify(_active);
    }

    DropOver();
}

void TetrisGame::Drop()
{
    MoveActive(Down);
}

void TetrisGame::MoveActive(Direction d)
{
    if(!_active)
        return ;
    // 先判断暂停逻辑
    if(_pause)
        return;

    if(TryMove(*_active, d))
    {
        _prediction.Predict(_active);
        emit DataChange();
    }
    else if(d == Down)
        DropOver();
}


bool TetrisGame::Rotate()
{
    Q_ASSERT(_active);
    bool ret=false;

    TetrisCell temp(*_active);
    temp.Rotate();
    if(_judger.IsSpacious(temp) || Adjust(temp))
    {
        _driver.Erasure(_active);
        *_active = temp;
        _driver.Solidify(_active);
        _prediction.Predict(_active);
        ret = true;

        emit DataChange();
    }

    return ret;
}

void TetrisGame::KeyControl(long vk)
{
    if(!_active)
        return ;

    // 先判断暂停逻辑
    if(VK_RETURN == vk)
        _pause ? Resume() : Pause();

    if(_pause)
        return;

    switch(vk)
    {
    case VK_LEFT:  MoveActive(Left); break;
    case VK_UP: Rotate(); break;
    case VK_RIGHT: MoveActive(Right); break;
    case VK_DOWN: MoveActive(Down); break;
    case VK_SPACE: DropBottom(); break;
    default:
        break;
    }
}

void TetrisGame::DropOver()
{
    Q_ASSERT(_active);
    _dropTimer.stop();
    _active->SetDiamond(Background);
    _driver.Solidify(_active);
    _driver.RemoveLine(_judger.Eliminate(_active->Points()));
    delete _active;
    _active = NULL;
    AddCell();
}

bool TetrisGame::TryMove(TetrisCell &cell, Direction d)
{
    bool ret = false;
    if(CanMove(cell, d))
    {
        _driver.Erasure(cell);
        cell.Move(d);
        _driver.Solidify(cell);
        ret = true;
    }

    return ret;
}

bool TetrisGame::CanMove(const TetrisCell &cell, Direction d)
{
    bool ret = false;
    TetrisCell temp(cell);
    temp.Move(d);
    if(_judger.IsSpacious(temp))
        ret = true;

    return ret;
}


bool TetrisGame::Adjust(TetrisCell &cell)
{
    // 左移一格调整
    if(TryMove(cell,Left))
        return true;

    // 右移一格调整
    if(TryMove(cell, Right))
        return true;

    // 对于I形状，我们特殊处理，允许它再右移一次。
    if(cell.Shape() == TetrisCreator::I)
    {
        // 右移二格调整
        cell.Move(Right);
        if(TryMove(cell, Right))
            return true;
    }

    // 对于刚出生的形状，我们可以让他往下移一次
    if(cell.LT().y() == 0)
    {
        if(TryMove(cell, Down))
            return true;
    }

    return false;

}

