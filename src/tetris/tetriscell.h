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
    // 设置左上角相对坐标
    void SetLT(const QPoint& lt);
    const QPoint& LT() const;

signals:

public slots:

private:
    // 坐标数据库初始化函数
    static QMap<TetrisCell::Shape, QList<QPoint> > InitCells();

private:
    static const QMap<TetrisCell::Shape, QList<QPoint> > CELLS;     // 形状坐标数据库

    Shape _s;     // 记录本cell形状
    QPoint _lt;
};

#endif // TETRISCELL_H
