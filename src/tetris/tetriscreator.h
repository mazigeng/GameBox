#ifndef TETRISCREATOR_H
#define TETRISCREATOR_H

#include <QMap>
#include <QPoint>

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

    /// \brief RandShape 随机产生形状
    /// \return 形状Shape
    static Shape RandShape();

    /// \brief Clockwise 围绕center旋转一个点90度的算法
    /// \param pt 被旋转点坐标
    /// \param center 旋转中心坐标
    static void Clockwise(QPoint& pt, const QPoint& center);
    static void Anticlockwise(QPoint& pt, const QPoint& center);

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
