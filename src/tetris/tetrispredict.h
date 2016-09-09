#ifndef TETRISPREDICT_H
#define TETRISPREDICT_H

#include <QObject>
class TetrisData;
class TetrisCell;

class TetrisPredict : public QObject
{
    Q_OBJECT
public:
    explicit TetrisPredict(const TetrisData& d, QObject *parent = 0);

    void Predict(const TetrisCell* active);
    const TetrisCell& CurPrediction() const;
signals:
    void NewPredict(const TetrisCell* New, const TetrisCell* Old);

public slots:

private:
    const TetrisData& _data;
    TetrisCell* _cur;
};

#endif // TETRISPREDICT_H
