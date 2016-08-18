#ifndef CONSOLEMODEM_H
#define CONSOLEMODEM_H

#include <QObject>
#include <QTextStream>
class TetrisData;

class ConsoleModem : public QObject
{
    Q_OBJECT
public:
    explicit ConsoleModem(const TetrisData& d, QObject *parent = 0);



signals:

public slots:
    void Repaint();


private:
    // 将TetrisData中的int数据，转换为显示用的QString字符
    QString TransData(int d) const;

    void Reflash();

    void Gotoxy(int x, int y);


private:
    QTextStream _stdOut;        // 标准输出,到控制台
    const TetrisData& _d;
};

#endif // CONSOLEMODEM_H
