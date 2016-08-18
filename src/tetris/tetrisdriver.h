#ifndef TETRISDRIVER_H
#define TETRISDRIVER_H

#include <QObject>
#include "tetriscell.h"
#include <QPoint>
#include <QList>
#include "keyboardmonitor.h"
#include <QTimer>
#include "define.h"
class TetrisData;

class TetrisDriver : public QObject
{
    Q_OBJECT
public:
    enum Direction
    {
        Left,
        Up,
        Right,
        Down
    };

public:
    explicit TetrisDriver(TetrisData& d, QObject *parent = 0);

    /// \brief AddCell 添加一个Cell到所驱动的TetrisData中。
    /// \param s 添加Cell的形状
    /// \param lt Cell显示位置的左上角起点坐标
    /// \return 返回添加的索引代码
    void AddCell(TetrisCreator::Shape s, const QPoint& lt);

    /// \brief Drop 活动的Cell下落开关
    /// \param on bool 开关
    void Drop(bool on);

    /// \brief Move 移动活动Cell指定方向一格
    /// \param d 方向
    /// \return 移动是否成功
    bool Move(Direction d);

    /// \brief Move 移动活动Cell到指定坐标
    /// \param offset 相对位移
    /// \return 移动是否成功
    bool Move(const QPoint& offset);

    /// \brief DropFinish 将active方块直接落到底
    void DropFinish();

    /// \brief Rotate 旋转当前活动的Cell
    /// \return 旋转是否成功
    bool Rotate();

    /// \brief RemoveLine 删除Data中，索引标记的整行
    /// \param lines 行索引数组
    void RemoveLine(const QList<int>& lines);

    /// \brief Active 获得ActiveCell的读权限
    /// \return NULL 当前没有Active， 返回ActiveCell指针
    const TetrisCell* Active();

    /// \brief Solidify 将Active的Cell固化到背景，并将active设为空。
    void Solidify();



signals:
    /// \brief DataChange 当修改了驱动的Data，发送此信号
    void DataChange();

    /// \brief DropEnd 已经不能下落时，发送此信号
    void DropEnd();


private slots:
    void Drop();

private:
    /// \brief SolidifyValue 根据active的点信息，将v值写入data中
    /// \param v 写入值
    void SolidifyValue(Diamond v);
    void SolidifyValue(TetrisCell* cell, Diamond v);

    /// \brief IsSpacious 判断是否有存放空间
    /// \param pts 点集合
    /// \param lt 相对data左上角坐标
    /// \param value 对比值
    /// \return 返回true 有空间存放
    bool IsSpacious(const QList<QPoint>& pts, const QPoint& lt, Diamond value = Background) const;

    bool Adjust();

    void Predict();
    void ClearPredict();

private:
    TetrisData& _datas;
    TetrisCell* _active;
    TetrisCell* _prediction;
    QTimer _dropTimer;
};

#endif // TETRISDRIVER_H
