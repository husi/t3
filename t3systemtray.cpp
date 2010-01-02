#include "t3systemtray.h"
#include "t3projecttimer.h"
#include <QApplication>
#include <QStyle>
#include <QDebug>
#include <QIcon>

t3SystemTray::t3SystemTray( t3ProjectTreeModel * model_, QObject *parent_) :
        QObject(parent_),
        _trayIcon(new QSystemTrayIcon(this)),
        _model(model_)
{
    _trayMenu = new QMenu();
    _trayMenu->addMenu(createProjectSelectorMenu());
    _trayIcon->setContextMenu(_trayMenu);
    _trayIcon->setIcon(QIcon(":/icons//clock.svg"));
    _trayIcon->setVisible(true);
}

t3SystemTray::~t3SystemTray()
{
    delete _trayMenu;
}

QMenu * t3SystemTray::createProjectSelectorMenu()
{
    QMenu * menu = new QMenu("Projects");
    QActionGroup * actiongroup =  new QActionGroup(menu);

    populateMenu(menu,actiongroup,QModelIndex());

    //TODO: the timer should be a singleton like something and not owned by the systray
    t3ProjectTimer * timer = new t3ProjectTimer(this);

    connect(actiongroup,SIGNAL(triggered(QAction*)),timer,SLOT(startProjectTimer(QAction*)));
    connect(qApp,SIGNAL(aboutToQuit()),timer,SLOT(stopProjectTimer()));

    return menu;
}

void t3SystemTray::populateMenu(QMenu * menu_, QActionGroup * actionGroup_, const QModelIndex &index)
{
    int numrows = _model->rowCount(index);
    if(numrows < 1)
        return;

    qDebug() << "NumRows: " << numrows;

    for (int i = 0; i < numrows; ++i)
    {
        QModelIndex projectindex = _model->index(i,0,index);
        qDebug() << "creating menu: " << _model->data(projectindex,Qt::DisplayRole).toString();
        if(_model->rowCount(projectindex))
        {
             QMenu *projectmenu = new QMenu(_model->data(projectindex,Qt::DisplayRole).toString());
             menu_->addMenu(projectmenu);
             populateMenu(projectmenu,actionGroup_,projectindex);
        } else {
            QAction * action = new QAction(_model->data(projectindex,Qt::DisplayRole).toString(),actionGroup_);
            action->setData(_model->data(projectindex,t3::IdRole));
            menu_->addAction(action);
        }
    }
}
