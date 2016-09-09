#ifndef TETRISGAME_H
#define TETRISGAME_H

#include <QObject>
#include "tetrisdata.h"
#include "tetrisdriver.h"
#include "consolemodem.h"
#include "tetrisjudger.h"
#include "tetrisforecast.h"
#include "tetrispredict.h"

class TetrisGame : public QObject
{
    Q_OBJECT
public:
    explicit TetrisGame(QObject *parent = 0);
    void Start();
    void Pause();
    void Resume();

signals:
    void GameOver();
    void DataChange();


public slots:
    void DropBottom();
    void Drop();
    void MoveActive(Direction d);
    bool Rotate();

private slots:


    void KeyControl(long vk);


private:
    void AddCell();
    void DropOver();
    bool TryMove(TetrisCell &cell, Direction d);
    bool CanMove(const TetrisCell& cell, Direction d);
    bool Adjust(TetrisCell &cell);





private:
    TetrisData _data;
    TetrisForecast _forecast;
    TetrisDriver _driver;
    ConsoleModem _out;
    TetrisJudger _judger;
    KeyboardMonitor _km;
    bool _pause;
    QTimer _dropTimer;
    TetrisPredict _prediction;
    TetrisCell* _active;



};

#endif // TETRISGAME_H
