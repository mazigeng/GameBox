#ifndef TETRISJUDGER_H
#define TETRISJUDGER_H

#include <QObject>
class TetrisData;

class TetrisJudger : public QObject
{
    Q_OBJECT
public:
    explicit TetrisJudger(const TetrisData& d, QObject *parent = 0);

    //

    /// \brief Eliminate 判断是否消除，依据给定点的所在行来判断。
    /// \param pts 点队列
    /// \return 可以消除的y索引。
    QList<int> Eliminate(const QList<QPoint>& pts, const QPoint &LT);

signals:

public slots:

private:
    const TetrisData& _d;
};

#endif // TETRISJUDGER_H
