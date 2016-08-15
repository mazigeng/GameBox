#ifndef TETRISDRIVER_H
#define TETRISDRIVER_H

#include <QObject>
#include "tetriscell.h"
#include <QPoint>
#include <QList>
#include "keyboardmonitor.h"
class TetrisData;

class TetrisDriver : public QObject
{
    Q_OBJECT
public:
    explicit TetrisDriver(TetrisData& d, QObject *parent = 0);
    ///
    /// \brief AddCell 添加一个Cell到所驱动的TetrisData中。
    /// \param s 添加Cell的形状
    /// \param lt Cell显示位置的左上角起点坐标
    /// \return 返回添加的索引代码
    ///
    int AddCell(TetrisCell::Shape s, const QPoint& lt);

    void MoveCell(int index, const QPoint& newLT);
    void RotateCell(int index);


signals:
    void DataChange(const TetrisData&);

public slots:
    void KeyControl(long vk);

private:
    void ChangeDataValue(const TetrisCell& cell, int value);
    bool IsSpacious(const QList<QPoint>& pts, const QPoint& lt, int value = 0) const;
private:
    TetrisData& _datas;
    QList<TetrisCell> _cells;
    KeyboardMonitor _km;
};

#endif // TETRISDRIVER_H
