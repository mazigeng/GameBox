#ifndef TETRISCELL_H
#define TETRISCELL_H

#include <QObject>
#include <QPoint>
#include <QList>
#include <QRect>
#include "tetriscreator.h"
#include "define.h"

class TetrisCell : public QObject
{
    Q_OBJECT
public:
    explicit TetrisCell(TetrisCreator::Shape s, const QPoint& lt = QPoint(0,0), int rotation = 0, Diamond d = Cell, QObject *parent = 0);
    TetrisCell(const TetrisCell& other);
    TetrisCell& operator=(const TetrisCell& other);

    // 形状的点数据
    QList<QPoint> Points() const;
    QPoint Point(int i) const;

    /// \brief Size 获得对应形状点的个数
    /// \return 对应形状点的个数
    int Size() const;

    /// \brief Shape 获得形状
    /// \return 形状值
    TetrisCreator::Shape Shape() const;

    void SetDiamond(Diamond d);
    Diamond GetDiamond() const;

    /// 设置左上角相对坐标
    void SetLT(const QPoint& lt);
    const QPoint& LT() const;

    /// \brief Rect 根据Points()，实时获得坐标点的左上右下的极值。
    /// \return 左上右下对应的极值坐标
    QRect Rect() const;

    QPoint RelativeZero() const;

    /// \brief Rotation 获得旋转角度
    /// \return 获得90度的倍数
    int Rotation() const;

    /// \brief SetRotation 设定旋转角度90度的倍数
    /// \param r 90度的倍数，0-3之间
    void SetRotation(int r);

    /// \brief Rotate 顺时针旋转90度，只是改变角度记录值，而不对点做操作
    void Rotate();

    /// \brief ReRotate 逆时针旋转90度
    void ReRotate();

    /// \brief Move 移动方块，SetLt()函数的一种扩展使用
    /// \param d
    void Move(Direction d, int step = 1);
    void Move(const QPoint &offset);
signals:

public slots:

private:
    TetrisCreator::Shape _s;               // 记录本cell形状
    QPoint _lt;             // cell相对坐标
    int _rotaiton;          // cell当前旋转度
    Diamond _diamond;       // cell的方块

};

#endif // TETRISCELL_H
