#include "keyboardmonitor.h"
#include <conio.h>
#include <QDebug>
#include <qt_windows.h>

KeyboardMonitor::KeyboardMonitor(QObject *parent) : QThread(parent)
{

}

void KeyboardMonitor::run()
{
    while(1)
    {
        long c = getch();
        if(c == 224)
            c += getch();

        long vk = Ascii2Vk(c);
        if(vk)
            emit KeyClicked(vk);
    }
}

long KeyboardMonitor::Ascii2Vk(long ascii)
{
    // 目前只关心上下左右
    switch(ascii)
    {
    case 224 + 75: return VK_LEFT;
    case 224 + 72: return VK_UP;
    case 224 + 77: return VK_RIGHT;
    case 224 + 80: return VK_DOWN;
    default:
        break;
    }
        return 0;
}

