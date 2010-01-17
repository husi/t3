#ifndef T3SQLVIEW_H
#define T3SQLVIEW_H

#include "t3dataviewbase.h"
#include <QLineEdit>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QTableView>
#include <QFrame>

class t3SqlView : public t3DataViewBase
{
    Q_OBJECT
public:
    t3SqlView(QObject *parent_);
    QString title() const;
    QWidget * widget() const;

public slots:
    void displayed();
    void runQuery();

private:
    QLineEdit * _edit;
    QSqlQueryModel * _model;
    QTableView * _view;
    QPushButton * _button;
    QFrame * _frame;
};

#endif // T3SQLVIEW_H
