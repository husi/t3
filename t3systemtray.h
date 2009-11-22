#ifndef T3SYSTEMTRAY_H
#define T3SYSTEMTRAY_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>

#include "t3projecttreemodel.h"

class t3SystemTray : public QObject
{
    Q_OBJECT

public:
    t3SystemTray(t3ProjectTreeModel * model_, QObject *parent_=0);
    virtual ~t3SystemTray();

private:
    QMenu * createProjectSelectorMenu();
    void populateMenu(QMenu * menu_, QActionGroup * actionGroup_, const QModelIndex &index_);

private:
    QMenu * _trayMenu;
    QSystemTrayIcon * _trayIcon;
    QMenu * _projectSelectorMenu;
    t3ProjectTreeModel * _model;
};

#endif // T3SYSTEMTRAY_H
