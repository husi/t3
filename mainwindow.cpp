#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "t3projecttreemodel.h"
#include "t3systemtray.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "Seting up the model";
    t3ProjectTreeModel *model = new t3ProjectTreeModel(this);
    qDebug() << "associating the model with view";
    ui->ProjectsTree->setModel(model);
    qDebug() << "initializing tray icon";
    new t3SystemTray(model,this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
