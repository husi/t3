#ifndef T3DATAVIEWBASE_H
#define T3DATAVIEWBASE_H

#include <QObject>
#include <QString>

class t3DataViewBase : public QObject
{
    Q_OBJECT
public:
    t3DataViewBase(QObject * parent_);
    virtual ~t3DataViewBase();
    virtual QString category();
    virtual QString title() const = 0;
    virtual QWidget * widget() const = 0;
public slots:
    virtual void displayed() = 0;
};

#endif // T3DATAVIEWBASE_H
