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
    QList<QPoint> Points() const;

    TetrisCreator::Shape Shape() const;

    // 设置左上角相对坐标
    void SetLT(const QPoint& lt);
    const QPoint& LT() const;

    /// \brief Rect 根据Points()，实时获得坐标点的左上右下的极值。
    /// \return
    QRect Rect() const;

    // 旋转
    void Rotate();
    // 反向旋转
    void ReRotate();

signals:

public slots:

private:
    TetrisCreator::Shape _s;               // 记录本cell形状
    QPoint _lt;             // cell相对坐标
    int _rotaiton;          // cell当前旋转度

};

#endif // TETRISCELL_H
