#include "t3systemtray.h"
#include <QApplication>
#include <QStyle>
#include <QDebug>

t3SystemTray::t3SystemTray( t3ProjectTreeModel * model_, QObject *parent_) :
        QObject(parent_),
        _trayIcon(new QSystemTrayIcon(this)),
        _model(model_)
{
    _trayMenu = new QMenu();
    _trayMenu->addMenu(createProjectSelectorMenu());
    _trayIcon->setContextMenu(_trayMenu);
    _trayIcon->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));
    _trayIcon->setVisible(true);
}

t3SystemTray::~t3SystemTray()
{
    delete _trayMenu;
}

QMenu * t3SystemTray::createProjectSelectorMenu()
{
    QMenu * menu = new QMenu("Projects");

    populateMenu(menu,QModelIndex());

    return menu;
}

void t3SystemTray::populateMenu(QMenu * menu_, const QModelIndex &index)
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
             populateMenu(projectmenu,projectindex);
        } else {
            menu_->addAction(_model->data(projectindex,Qt::DisplayRole).toString());
        }
    }
}
