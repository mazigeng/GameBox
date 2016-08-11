#ifndef KEYBOARDMONITOR_H
#define KEYBOARDMONITOR_H

#include <QThread>

class KeyboardMonitor : public QThread
{
    Q_OBJECT
public:
    explicit KeyboardMonitor(QObject *parent = 0);

signals:
    void KeyClicked(long vk);

public slots:

private:
    virtual void	run();
    long Ascii2Vk(long ascii);


};

#endif // KEYBOARDMONITOR_H
