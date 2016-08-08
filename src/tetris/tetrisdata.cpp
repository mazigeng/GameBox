#include "tetrisdata.h"

TetrisData::TetrisData(QObject *parent) : QObject(parent), _datas(DX,QVector<int>(DY,0))
{
}

