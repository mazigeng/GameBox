#include "consolemodem.h"
#include <tetrisdata.h>
#include <QDebug>

#ifdef WIN32
#include <qt_windows.h>
#endif

ConsoleModem::ConsoleModem(const TetrisData& c, const TetrisData &f, QObject *parent) : QObject(parent), _stdOut(stdout), _chessboard(c), _forecast(f)
{

}



void ConsoleModem::Repaint()
{
    Reflash();
}

QString ConsoleModem::TransData(Diamond d) const
{
    // 临时方案的映射表
    Q_ASSERT(d >= 0 && d<4);
    static const QString keymap[] = {"  ","□" , "■","■"};

    return keymap[d];
}

void ConsoleModem::Reflash()
{

    Gotoxy(0,0);

    // 输出第一排边框
    _stdOut <<  QString("┌──────────┬────┐") << endl;

    // 输出棋盘20行
    for(int y=0; y<_chessboard.Size().height(); ++y)
    {
        // 每行开始先输出边界
        _stdOut << QString("│");
        // 输出每列内容
        for (int x=0; x<_chessboard.Size().width(); ++x)
        {
            _stdOut << TransData(_chessboard.At(x,y));
        }

        if((y+1) % 5 == 0 && y < 16)
        {
            _stdOut <<  QString("├────┤");
        }
        else if(y - y/5 < _forecast.Size().height() )
        {
            _stdOut << QString("│");
            for(int x=0; x<_forecast.Size().width(); ++x)
            {
                _stdOut << TransData(_forecast.At(x,y - y/5));
            }
            _stdOut << QString("│") ;
        }
        else
            _stdOut << QString("│        │");

        _stdOut << endl;

    }

    // 最后一排输出边框
    _stdOut <<  QString("└");
    for (int n=0; n<_chessboard.Size().width(); ++n)
    {
        _stdOut << QString("─");
    }
    _stdOut << QString("┴────┘") << endl;
}

void ConsoleModem::Gotoxy(int x,int y)
{
    HANDLE hOutput;
    COORD loc;
    loc.X= y*2;
    loc.Y= x;
    hOutput= ::GetStdHandle(STD_OUTPUT_HANDLE);
    ::SetConsoleCursorPosition(hOutput, loc);
    return;
}

