#include <QCoreApplication>
#include "tetrisgame.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TetrisGame game;
    game.Start();



    return a.exec();
}


