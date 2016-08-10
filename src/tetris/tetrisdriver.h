#ifndef TETRISDRIVER_H
#define TETRISDRIVER_H

#include <QObject>
#include "tetriscell.h"
#include <QPoint>
#include <QList>
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


signals:

public slots:
private:
    TetrisData& _datas;
    QList<TetrisCell> _cells;
};

#endif // TETRISDRIVER_H
