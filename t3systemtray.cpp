#include "t3systemtray.h"
#include <QApplication>
#include <QStyle>

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

QMenu * t3SystemTray::createProjectSelectorMenu()
{
    QMenu * menu = new QMenu("Projects",_trayMenu);

    return menu;
}
