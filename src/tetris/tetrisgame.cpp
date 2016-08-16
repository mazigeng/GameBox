#include "tetrisgame.h"
#include "tetriscell.h"

TetrisGame::TetrisGame(QObject *parent) : QObject(parent), _data(), _driver(_data), _out(), _judger(_data)
{
    QObject::connect(&_driver, SIGNAL(DataChange(TetrisData)), &_out, SLOT(ShowTetrisData(TetrisData)));
    QObject::connect(&_driver, SIGNAL(MoveEnd(TetrisCell)), this, SLOT(MoveEnd(TetrisCell)));
}

void TetrisGame::Start()
{
    AddCell();
}

void TetrisGame::AddCell()
{
    _driver.AddCell(TetrisCell::RandShape(), QPoint(_data.Size().width() / 2, 0));
}

void TetrisGame::MoveEnd(TetrisCell cell)
{
    _driver.RemoveLine(_judger.Eliminate(cell.Points(), cell.LT()));
    AddCell();

}

