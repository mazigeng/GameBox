#ifndef TETRISCREATOR_H
#define TETRISCREATOR_H

#include <QMap>
#include <QPoint>
class TetrisCell;
class TetrisCreator
{
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

    static const QMap<TetrisCreator::Shape, QList<QPoint> > CELLS;     // 形状坐标数据库
    static const QMap<TetrisCreator::Shape, int> ROTATE_TIMES;         // 形状可旋转次数
    static const QMap<TetrisCreator::Shape, QPoint> ROTATE_CENTER;     // 形状旋转中心

    /// \brief RandCell 随机产生Cell, 形状随机，角度随机，其他默认
    /// \return 随机的cell
    static TetrisCell RandCell();

    /// \brief Clockwise 围绕center旋转一个点90度的算法
    /// \param pt 被旋转点坐标
    /// \param center 旋转中心坐标

    static void Clock90(QPoint& pt, const QPoint& center);
    static void Clock180(QPoint& pt, const QPoint& center);
    static void Clock270(QPoint& pt, const QPoint& center);
    /// \brief ClockWise 围绕center依据rotation指定的90度的倍数，顺时针旋转pts,。
    /// \param rotation 指定90度的多少被，取值2即旋转180度
    /// \param pts 被旋转的点集合
    /// \param center 旋转围绕中心
    static void ClockWise(int rotation, QList<QPoint>& pts, const QPoint& center);
    static void ClockWise(int rotation, QPoint& pt, const QPoint& center);


    /// \brief Times 获得一个形状可旋转的次数
    /// \param s 形状Shape
    /// \return 可旋转的次数
    static int Times(Shape s);


private:
    // 坐标数据库初始化函数
    static QMap<TetrisCreator::Shape, QList<QPoint> > InitCells();
    static QMap<TetrisCreator::Shape, int > InitRotateTimes();
    static QMap<TetrisCreator::Shape, QPoint > InitRotateCenter();
};

#endif // TETRISCREATOR_H
