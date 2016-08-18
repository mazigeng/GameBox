#ifndef TETRISGAME_H
#define TETRISGAME_H

#include <QObject>
#include "tetrisdata.h"
#include "tetrisdriver.h"
#include "consolemodem.h"
#include "tetrisjudger.h"
#include "tetrisforecast.h"

class TetrisGame : public QObject
{
    Q_OBJECT
public:
    explicit TetrisGame(QObject *parent = 0);
    void Start();
    void Pause();
    void Resume();

signals:

public slots:

private slots:
    void AddCell();
    void DropEnd();
    void KeyControl(long vk);



private:
    TetrisData _data;
    TetrisForecast _forecast;
    TetrisDriver _driver;
    ConsoleModem _out;
    TetrisJudger _judger;
    KeyboardMonitor _km;
    bool _pause;

};

#endif // TETRISGAME_H
