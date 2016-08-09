#include <QCoreApplication>
#include "tetrisdata.h"
#include "consolemodem.h"
#include <QDebug>
#include <QPoint>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TetrisData d;

    // 写入L
    d.At(1,1) = 1;
    d.At(1,2) = 1;
    d.At(1,3) = 1;
    d.At(2,3) = 1;

    // 写入T
    QPoint pts[] = {QPoint(5,5), QPoint(6,5), QPoint(7,5), QPoint(6,6)};
    for(int n=0; n<sizeof(pts) / sizeof(pts[0]); ++n)
    {
        d.At(pts[n].x(), pts[n].y()) = 1;
    }

    ConsoleModem out;
    out.ShowTetrisData(d);


    return a.exec();
}


