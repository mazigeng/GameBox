#ifndef TETRISDRIVER_H
#define TETRISDRIVER_H

#include <QObject>
#include "tetriscell.h"
#include <QPoint>
#include <QList>
#include "keyboardmonitor.h"
#include <QTimer>
#include "define.h"
class TetrisData;

class TetrisDriver : public QObject
{
    Q_OBJECT
public:
    explicit TetrisDriver(TetrisData& d, QObject *parent = 0);

    /// \brief RemoveLine 删除Data中，索引标记的整行
    /// \param lines 行索引数组
    void RemoveLine(const QList<int>& lines);


signals:
    /// \brief DataChange 当修改了驱动的Data，发送此信号
    void DataChange();

public slots:

    /// \brief SolidifyValue 将一个cell写入data棋盘
    /// \param cell 一个cell信息
    void Solidify(const TetrisCell* cell);
    void Solidify(const TetrisCell& cell);

    /// \brief Erasure 将一个cell在棋盘中擦除，最终cell所在位置，肯定全是空
    /// \param cell 一个cell信息
    void Erasure(const TetrisCell* cell);
    void Erasure(const TetrisCell& cell);


    /// \brief UpdateCell 将src调用Erasure 将des调用Solidify
    /// \param des 被写入的Cell
    /// \param src 被擦除的Cell
    void UpdateCell(const TetrisCell* des, const TetrisCell* src);


private:
    TetrisData& _datas;



};

#endif // TETRISDRIVER_H
