#ifndef TETRISDATA_H
#define TETRISDATA_H

#include <QObject>
#include <QVector>
#include <QSize>
#include "define.h"

class TetrisData : public QObject
{
    Q_OBJECT
public:
    explicit TetrisData(int w, int h,QObject *parent = 0);

    // 获得(x,y)元素的使用权限
    Diamond& At(int x, int y);
    Diamond& At(const QPoint& xy);
    const Diamond& At(int x, int y) const;
    const Diamond& At(const QPoint& xy) const;

    /// \brief RemoveLine 删除以y坐标定义的一整行
    /// \param y
    /// \param down ture 删除后整体向下填充，false 删除后整体向上填充
    void RemoveLine(int y, bool down = true);


    /// \brief indexOfY 找到以X定义的列中，value的索引
    /// \param x 第几列
    /// \param value 查找的值
    /// \param from 起点索引
    /// \return  未找到返回-1，找到返回索引
    int indexOfY(int x, Diamond value, int from = 0) const;

    /// \brief Fill 填充Data所有At为value
    /// \param value
    void Fill(Diamond value);


    // 获得棋盘尺寸
    QSize Size() const;

signals:

public slots:

private:
    const int W;
    const int H;
    QVector<QVector<Diamond> >  _datas;

};



#endif // TETRISDATA_H
