#include "consolemodem.h"
#include <tetrisdata.h>
#include <QDebug>

#ifdef WIN32
#include <qt_windows.h>
#endif

ConsoleModem::ConsoleModem(QObject *parent) : QObject(parent), _stdOut(stdout)
{

}

void ConsoleModem::ShowTetrisData(const TetrisData &d)
{
    // 输出第一排边框
    _stdOut <<  QString("┌");
    for (int n=0; n<d.Size().width(); ++n)
    {
        _stdOut << QString("─");
    }
    _stdOut << QString("┐") << endl;

    // 输出棋盘20行
    for(int y=0; y<d.Size().height(); ++y)
    {
        // 每行开始先输出边界
        _stdOut << QString("│");
        // 输出每列内容
        for (int x=0; x<d.Size().width(); ++x)
        {
            _stdOut << TransData(d.At(x,y));
        }
        // 结束输出边界
        _stdOut << QString("│") << endl;
    }

    // 最后一排输出边框
    _stdOut <<  QString("└");
    for (int n=0; n<d.Size().width(); ++n)
    {
        _stdOut << QString("─");
    }
    _stdOut << QString("┘") << endl;
}

QString ConsoleModem::TransData(int d) const
{
    // 临时方案的映射表
    Q_ASSERT(d >= 0 && d<2);
    static const QString keymap[] = {"  ", "■"};

    return keymap[d];
}


