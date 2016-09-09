#include "tetrispredict.h"
#include "tetriscell.h"
#include "tetrisdata.h"
#include "tetrisjudger.h"

TetrisPredict::TetrisPredict(const TetrisData &d, QObject *parent) : QObject(parent), _data(d), _cur(NULL)
{

}

void TetrisPredict::Predict(const TetrisCell* active)
{
    Q_ASSERT(active);
    TetrisCell* PreCell = new TetrisCell(*active);
    PreCell->SetLT(QPoint(PreCell->LT().x(),_data.Size().height()));

    TetrisJudger j(_data);

    foreach(const QPoint& pt, active->Points())
    {
        int i = _data.indexOfY(pt.x(),Background, pt.y());
        i = (i == -1 ? _data.Size().height() : i);

        int offset = i - pt.y() - 1;

        TetrisCell temp(*active);
        temp.SetLT(active->LT() + QPoint(0,offset));

        if(j.IsSpacious(temp))
        {
            if(PreCell->LT().y() > temp.LT().y())
                *PreCell = temp;
        }
    }

    PreCell->SetDiamond(Prediction);

    emit NewPredict(PreCell, _cur);
    _cur = PreCell;
}

const TetrisCell &TetrisPredict::CurPrediction() const
{
    return *_cur;
}

