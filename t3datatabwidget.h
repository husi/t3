#ifndef T3DATATABWIDGET_H
#define T3DATATABWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QListWidget>
#include <QToolBox>
#include <QList>

class t3DataTabWidget : public QWidget
{
Q_OBJECT
public:
    explicit t3DataTabWidget(QWidget *parent = 0);

    void registerView(const QString & category_, const QString &name_, QWidget * view_);

signals:

public slots:

private:
    int newCategory(const QString & name_);
    int findCategory(const QString &name_);
private:
    QToolBox * _toolBox;
    QStackedWidget * _viewStack;

    QList<QListWidget *> _toolPanes;
    QList<QStackedWidget *> _views;
};

#endif // T3DATATABWIDGET_H
