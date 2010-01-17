#include "t3sqlview.h"
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

t3SqlView::t3SqlView(QObject *parent_) :
        t3DataViewBase(parent_)
{

    _frame = new QFrame();
    QHBoxLayout *toplayout = new QHBoxLayout;

    _edit = new QLineEdit();
    _button = new QPushButton("Query");

    toplayout->addWidget(_edit);
    toplayout->addWidget(_button);

    QVBoxLayout *mainlayout = new QVBoxLayout();

    _view = new QTableView();

    mainlayout->addLayout(toplayout);
    mainlayout->addWidget(_view);

    _frame->setLayout(mainlayout);

    _model = new QSqlQueryModel(this);
    _view->setModel(_model);
    connect(_button,SIGNAL(clicked()),this,SLOT(runQuery()));


}

QString t3SqlView::title() const
{
    return "Sql Querry";
}

QWidget * t3SqlView::widget() const
{
    return _frame;
}

void t3SqlView::displayed()
{

}


void t3SqlView::runQuery()
{
    qDebug() << _edit->text();
    _model->setQuery(_edit->text());
}
