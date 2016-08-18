#ifndef TETRISCELL_H
#define TETRISCELL_H

#include <QObject>
#include <QPoint>
#include <QList>
#include "tetriscreator.h"

class TetrisCell : public QObject
{
    Q_OBJECT
public:
    explicit TetrisCell(TetrisCreator::Shape s, const QPoint& lt = QPoint(0,0), QObject *parent = 0);
    TetrisCell(const TetrisCell& other);
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
    QList<QPoint> _pts;     // cell点坐标
    TetrisCreator::Shape _s;               // 记录本cell形状
    QPoint _lt;             // cell相对坐标
    int _rotaiton;          // cell当前旋转度

};

#endif // TETRISCELL_H
