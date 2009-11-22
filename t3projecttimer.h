#ifndef T3PROJECTTIMER_H
#define T3PROJECTTIMER_H

#include <QObject>
#include <QAction>
#include <QTime>

class t3ProjectTimer : public QObject
{
    Q_OBJECT

public:
    t3ProjectTimer(QObject *parent_);

public slots:
    void startProjectTimer(QAction * action_);

protected:
    void timerEvent(QTimerEvent * event_);

private:
    QAction * _currentAction;
    QString _originalText;
    QTime _time;
};

#endif // T3PROJECTTIMER_H
