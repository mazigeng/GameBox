#ifndef TETRISGAME_H
#define TETRISGAME_H

#include <QObject>
#include "tetrisdata.h"
#include "tetrisdriver.h"
#include "consolemodem.h"
#include "tetrisjudger.h"

class TetrisGame : public QObject
{
    Q_OBJECT
public:
    explicit TetrisGame(QObject *parent = 0);
    void Start();

signals:

public slots:

private slots:
    void AddCell();
    void MoveEnd(TetrisCell cell);


private:
    TetrisData _data;
    TetrisDriver _driver;
    ConsoleModem _out;
    TetrisJudger _judger;
};

#endif // TETRISGAME_H
