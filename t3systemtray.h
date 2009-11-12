#ifndef T3SYSTEMTRAY_H
#define T3SYSTEMTRAY_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>

#include "t3projecttreenode.h"

class t3SystemTray : public QObject
{
    Q_OBJECT

public:
    t3SystemTray(QObject *parent_, t3ProjectTreeNode * root_);

private:
    QMenu * createMenu(t3ProjectTreeNode * root_);

private:
    QMenu * _trayMenu;
    QSystemTrayIcon * _trayIcon;
};

#endif // T3SYSTEMTRAY_H
