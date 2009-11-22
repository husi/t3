#include "t3projecttimer.h"
#include <QDebug>

t3ProjectTimer::t3ProjectTimer(QObject * parent_) :
        QObject(parent_),
        _currentAction(0)
{
    _time.start();
}

void t3ProjectTimer::startProjectTimer(QAction *action_)
{
    if (action_ == _currentAction)
        return;

    QTime elapsed = QTime().addMSecs(_time.restart());
    if(_currentAction)
    {
        qDebug() << "Timing Finished: " << _originalText << elapsed.toString(" (hh:mm:ss)");
        _currentAction->setText(_originalText);        
    }

    _currentAction = action_;

    if(_currentAction)
    {
        _originalText = _currentAction->text();
        startTimer(1000);
    }
}

void t3ProjectTimer::timerEvent(QTimerEvent * event_)
{
    if(!_currentAction)
        return;

    QTime elapsed = QTime().addMSecs(_time.elapsed());
    _currentAction->setText(_originalText + elapsed.toString(" (hh:mm:ss)"));
}
