#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QSqlDatabase>
#include <QString>
#include <QDir>
#include <QDebug>
#include "t3projecttreenode.h"

static const QString datadir(".t3");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*Initiate DB connection*/

    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    QString dbName = QDir::homePath() + "/" + datadir + "/data.db";
    db.setDatabaseName(dbName);
    bool ok = db.open();

    if(!ok)
    {
        qDebug() << "DB Initialization failed";
        return 1;
    }

    qDebug() << "DB Initialized";

    t3ProjectTreeNode::rebuildFromDB();

    /*Create the main window*/
    MainWindow w;
    w.show();
    return a.exec();
}
