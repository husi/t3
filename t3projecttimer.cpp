#include "t3projecttimer.h"
#include <QDebug>
#include <QTimerEvent>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>

t3ProjectTimer::t3ProjectTimer(QObject * parent_) :
        QObject(parent_),
        _currentAction(0),
        _time(QTime::currentTime()),
        _secTimer(0),
        _minuteTimer(0),
        _rowId(0)
{
    _time.start();
}

void t3ProjectTimer::startProjectTimer(QAction *action_)
{
    if (action_ == _currentAction)
        return;

    QDateTime start = QDateTime::currentDateTime();
    if(_currentAction)
    {
        closeTiming();
    }
    _currentAction = action_;

    if(_currentAction) //start the next one
    {
        _originalText = _currentAction->text();
        _secTimer = startTimer(1000);
        _minuteTimer = startTimer(60000);

        //insert row into the db

        QSqlQuery query;
        query.prepare("INSERT INTO times (ProjectId,Start) VALUES (?,?)");
        query.addBindValue(_currentAction->data());
        query.addBindValue(start);
        query.exec();

        qDebug() << query.lastQuery();

        _rowId = query.lastInsertId().toInt();

        qDebug() << "Current Row Id=" << _rowId;
    }
}

void t3ProjectTimer::stopProjectTimer()
{
    if(!_currentAction)
    {
        return;
    }
    closeTiming();
}

void t3ProjectTimer::timerEvent(QTimerEvent * event_)
{
    if(!_currentAction)
        return;

    if (event_->timerId() == _secTimer)
    {
        QTime elapsed = QTime().addMSecs(_time.elapsed());
        _currentAction->setText(_originalText + elapsed.toString(" (hh:mm:ss)"));
    }
    else if (event_->timerId() == _minuteTimer)
    {
        updateRecord();
    }
}


void t3ProjectTimer::updateRecord()
{
    updateRecord(QTime().addMSecs(_time.elapsed()));
}

void t3ProjectTimer::updateRecord(QTime elapsed_)
{
    QSqlQuery query;
    query.prepare("UPDATE times SET Duration=? where Id = ?");
    query.addBindValue(elapsed_);
    query.addBindValue(_rowId);
    query.exec();
}

void t3ProjectTimer::closeTiming()
{
    QTime elapsed = QTime().addMSecs(_time.restart());
    if(_currentAction) //close the current action
    {
        qDebug() << "Timing Finished: " << _originalText << elapsed.toString(" (hh:mm:ss)");
        _currentAction->setText(_originalText);
        updateRecord(elapsed);
    }
    _currentAction = NULL;

}
