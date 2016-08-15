#include "tetrisdata.h"
#include "consolemodem.h"
#include <QCoreApplication>
#include <QDebug>
#include <QPoint>
#include "tetriscell.h"
#include "tetrisdriver.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TetrisData d;
    TetrisDriver driver(d);
    ConsoleModem out;

    QObject::connect(&driver, SIGNAL(DataChange(TetrisData)), &out, SLOT(ShowTetrisData(TetrisData)));

    // 写入L
    driver.AddCell(TetrisCell::L,QPoint(1,1));
    driver.AddCell(TetrisCell::J,QPoint(7,1));
    driver.AddCell(TetrisCell::O,QPoint(7,6));
    driver.AddCell(TetrisCell::Z,QPoint(1,10));
    driver.AddCell(TetrisCell::I,QPoint(5,14));
    driver.AddCell(TetrisCell::S,QPoint(7,10));
    driver.AddCell(TetrisCell::T,QPoint(2,6));
    out.ShowTetrisData(d);


    return a.exec();
}


