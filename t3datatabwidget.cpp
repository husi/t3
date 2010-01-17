#include "t3datatabwidget.h"
#include "t3sqlview.h"
#include <QHBoxLayout>
#include <QLCDNumber>

t3DataTabWidget::t3DataTabWidget(QWidget *parent) :
    QWidget(parent)
{
    _toolBox = new QToolBox();
    _viewStack = new QStackedWidget();

    QHBoxLayout * layout = new QHBoxLayout();

    layout->addWidget(_toolBox,1);
    layout->addWidget(_viewStack,100);

    _viewStack->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    connect(_toolBox,SIGNAL(currentChanged(int)),_viewStack,SLOT(setCurrentIndex(int)));

    this->setLayout(layout);
    this->show();


    t3SqlView * view = new t3SqlView(this);
    registerView(view->category(),view->title(),view->widget());


}


void t3DataTabWidget::registerView(const QString &category_, const QString &name_, QWidget *view_)
{
    int categoryindex = findCategory(category_);
    if (categoryindex == -1)
    {
        categoryindex = newCategory(category_);
    }
    _toolPanes[categoryindex]->addItem(new QListWidgetItem(name_));
    _views[categoryindex]->addWidget(view_);
}

int t3DataTabWidget::newCategory(const QString & name_)
{
    QListWidget * listwidget = new QListWidget();
    int index = _toolBox->addItem(listwidget,name_);
    _toolPanes << listwidget;

    QStackedWidget * stack = new QStackedWidget();
    _viewStack->addWidget(stack);
    _views << stack;

    connect(listwidget,SIGNAL(currentRowChanged(int)),stack,SLOT(setCurrentIndex(int)));

    return index;
}

int t3DataTabWidget::findCategory(const QString &name_)
{
    int index = _toolBox->count();
    while(--index >= 0 && _toolBox->itemText(index) != name_) {}
    return index;
}
