#ifndef CONSOLEMODEM_H
#define CONSOLEMODEM_H

#include <QObject>
#include <QTextStream>
class TetrisData;

class ConsoleModem : public QObject
{
    Q_OBJECT
public:
    explicit ConsoleModem(QObject *parent = 0);



signals:

public slots:
    // 将d中的数据，输出到控制台一次
    void ShowTetrisData(const TetrisData& d);


private:
    // 将TetrisData中的int数据，转换为显示用的QString字符
    QString TransData(int d) const;

    void Gotoxy(int x, int y);


private:
    QTextStream _stdOut;        // 标准输出,到控制台
};

#endif // CONSOLEMODEM_H
