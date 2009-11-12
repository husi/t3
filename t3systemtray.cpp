#include "t3systemtray.h"

t3SystemTray::t3SystemTray(QObject *parent_, t3ProjectTreeNode * root_) :
        QObject(parent_),
        _trayIcon(new QSystemTrayIcon(this))
{
    _trayMenu = createMenu(root_);
}

QMenu * t3SystemTray::createMenu(t3ProjectTreeNode *root_)
{
    QMenu * menu = new QMenu();

    return menu;
}
