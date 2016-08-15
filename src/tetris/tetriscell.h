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

    // 形状的点数据
    const QList<QPoint> Points() const;

    // 设置左上角相对坐标
    void SetLT(const QPoint& lt);
    const QPoint& LT() const;


    // 旋转
    void Rotate();
    // 反向旋转
    void ReRotate();




signals:

public slots:

private:
    // 坐标数据库初始化函数
    static QMap<TetrisCell::Shape, QList<QPoint> > InitCells();
    static QMap<TetrisCell::Shape, int > InitRotateTimes();
    static QMap<TetrisCell::Shape, QPoint > InitRotateCenter();

    // 基础旋转算法
    static void Clockwise(QPoint& pt, const QPoint& center);
    static void Anticlockwise(QPoint& pt, const QPoint& center);
    int Times() const;


private:
    static const QMap<TetrisCell::Shape, QList<QPoint> > CELLS;     // 形状坐标数据库
    static const QMap<TetrisCell::Shape, int> ROTATE_TIMES;         // 形状可旋转次数
    static const QMap<TetrisCell::Shape, QPoint> ROTATE_CENTER;     // 形状旋转中心

    QList<QPoint> _pts;     // cell点坐标
    TetrisCell::Shape _s;               // 记录本cell形状
    QPoint _lt;             // cell相对坐标
    int _rotaiton;          // cell当前旋转度

};

#endif // TETRISCELL_H
