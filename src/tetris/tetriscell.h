#ifndef TETRISCELL_H
#define TETRISCELL_H

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QMap>
#include <QList>

class TetrisCell : public QObject
{
    Q_OBJECT
public:
    enum Shape{
        O,
        T,
        L,
        J,
        I,
        S,
        Z
    };

public:
    explicit TetrisCell(Shape s, QObject *parent = 0);
    explicit TetrisCell(const TetrisCell& other);
    TetrisCell& operator=(const TetrisCell& other);

    // 读取形状的点数据
    const QList<QPoint> Points() const;

signals:

public slots:

private:
    // 坐标数据库初始化函数
    static QMap<TetrisCell::Shape, QList<QPoint> > InitCells();

private:
    const Shape _s;     // 记录本cell形状
    static const QMap<TetrisCell::Shape, QList<QPoint> > CELLS;     // 形状坐标数据库
};

#endif // TETRISCELL_H
