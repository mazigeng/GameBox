#ifndef TETRISJUDGER_H
#define TETRISJUDGER_H

#include <QObject>
#include "define.h"
class TetrisData;
class TetrisCell;

class TetrisJudger : public QObject
{
    Q_OBJECT
public:
    explicit TetrisJudger(const TetrisData& d, QObject *parent = 0);

    /// \brief Eliminate 判断是否消除，依据给定点的所在行来判断。
    /// \param pts 点队列
    /// \return 可以消除的y索引。
    QList<int> Eliminate(const QList<QPoint>& pts);

    /// \brief IsSpacious 判断是否有存放空间
    /// \param pts 点集合
    /// \param lt 相对data左上角坐标
    /// \param value 对比值
    /// \return 返回true 有空间存放
    bool IsSpacious(const TetrisCell &cell, Diamond value = Background) const;
signals:

public slots:

private:
    const TetrisData& _d;
};

#endif // TETRISJUDGER_H
