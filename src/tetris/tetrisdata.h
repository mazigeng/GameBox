#ifndef TETRISDATA_H
#define TETRISDATA_H

#include <QObject>
#include <QVector>
#include <QSize>

class TetrisData : public QObject
{
    Q_OBJECT
public:
    explicit TetrisData(QObject *parent = 0);

    // 获得(x,y)元素的使用权限
    int& At(int x, int y);
    int& At(const QPoint& xy);
    const int& At(int x, int y) const;

    // 删除以y坐标定义的一整行
    void RemoveLine(int y);


    /// \brief indexOfY 找到以X定义的列中，value的索引
    /// \param x 第几列
    /// \param value 查找的值
    /// \param from 起点索引
    /// \return  未找到返回-1，找到返回索引
    int indexOfY(int x, int value, int from = 0);

    // 获得棋盘尺寸
    QSize Size() const;

signals:

public slots:

private:
    QVector<QVector<int> >  _datas;
    static const int DX = 10;
    static const int DY = 20;
};



#endif // TETRISDATA_H
