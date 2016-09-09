#ifndef TETRISFORECAST_H
#define TETRISFORECAST_H

#include <QObject>
#include "tetrisdata.h"
#include "tetriscreator.h"
#include "tetriscell.h"
#include "tetrisdriver.h"
#include <QQueue>

class TetrisForecast : public QObject
{
    Q_OBJECT
public:
    explicit TetrisForecast(QObject *parent = 0);

    void Enqueue(const TetrisCell& cell);
    TetrisCell Dequeue();

    const TetrisData& data();

signals:
    void DataChange();

public slots:

private:
    TetrisData _data;
    QQueue<TetrisCell> _qCell;
};

#endif // TETRISFORECAST_H
