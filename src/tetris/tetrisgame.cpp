#include "tetrisgame.h"
#include "tetriscell.h"
#include <qt_windows.h>
#include "keyboardmonitor.h"


TetrisGame::TetrisGame(QObject *parent) : QObject(parent), _data(), _driver(_data), _out(_data), _judger(_data)
{
    _km.start();
    connect(&_km,SIGNAL(KeyClicked(long)), this, SLOT(KeyControl(long)));
    QObject::connect(&_driver, SIGNAL(DataChange()), &_out, SLOT(Repaint()));
    QObject::connect(&_driver, SIGNAL(DropEnd()), this, SLOT(DropEnd()));
}

void TetrisGame::Start()
{
    AddCell();
}

void TetrisGame::AddCell()
{
    _driver.AddCell(TetrisCreator::RandShape(), QPoint(_data.Size().width() / 2, 0));
    _driver.Drop(true);
}

void TetrisGame::DropEnd()
{
    const TetrisCell* active = _driver.Active();
    if(active)
    {
        _driver.RemoveLine(_judger.Eliminate(active->Points(), active->LT()));
    }
    _driver.Solidify();
    AddCell();
}

void TetrisGame::KeyControl(long vk)
{
    if(!_driver.Active())
        return ;

    switch(vk)
    {
    case VK_LEFT:  _driver.Move(TetrisDriver::Left); break;
    case VK_UP: _driver.Rotate(); break;
    case VK_RIGHT: _driver.Move(TetrisDriver::Right); break;
    case VK_DOWN: _driver.Move(TetrisDriver::Down); break;
    default:
        break;
    }
}

