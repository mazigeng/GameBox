#include "tetrisgame.h"
#include "tetriscell.h"
#include <qt_windows.h>
#include "keyboardmonitor.h"


TetrisGame::TetrisGame(QObject *parent) : QObject(parent), _data(10,20),_forecast(), _driver(_data), _out(_data,_forecast.data()), _judger(_data), _pause(false)
{
    _km.start();
    connect(&_km,SIGNAL(KeyClicked(long)), this, SLOT(KeyControl(long)));
    QObject::connect(&_driver, SIGNAL(DataChange()), &_out, SLOT(Repaint()));
    QObject::connect(&_forecast, SIGNAL(DataChange()), &_out, SLOT(Repaint()));
    QObject::connect(&_driver, SIGNAL(DropEnd()), this, SLOT(DropEnd()));
}

void TetrisGame::Start()
{

    _forecast.Enqueue(TetrisCreator::RandShape());
    _forecast.Enqueue(TetrisCreator::RandShape());
    _forecast.Enqueue(TetrisCreator::RandShape());
    AddCell();
}

void TetrisGame::Pause()
{
    _driver.Drop(false);
    _pause = true;

}

void TetrisGame::Resume()
{
    if(_driver.Active())
        _driver.Drop(true);
    _pause = false;
}

void TetrisGame::AddCell()
{

    _driver.AddCell(_forecast.Dequeue(), QPoint(_data.Size().width() / 2, 0));
    _driver.Drop(true);
    _forecast.Enqueue(TetrisCreator::RandShape());


}

void TetrisGame::DropEnd()
{

    const TetrisCell* active = _driver.Active();
    if(active)
    {
        _driver.Solidify();
        _driver.RemoveLine(_judger.Eliminate(active->Points()));
    }
    AddCell();
}

void TetrisGame::KeyControl(long vk)
{
    if(!_driver.Active())
        return ;

    // 先判断暂停逻辑
    if(VK_RETURN == vk)
        _pause ? Resume() : Pause();

    if(_pause)
        return;

    switch(vk)
    {
    case VK_LEFT:  _driver.Move(TetrisDriver::Left); break;
    case VK_UP: _driver.Rotate(); break;
    case VK_RIGHT: _driver.Move(TetrisDriver::Right); break;
    case VK_DOWN: _driver.Move(TetrisDriver::Down); break;
    case VK_SPACE:
        if(_driver.Active())
            _driver.DropFinish();
        break;

    default:
        break;
    }
}

