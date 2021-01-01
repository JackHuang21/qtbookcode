#include "mainwindow.h"
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createContextMenu();
    createToolBars();
    createStatusBars();
    setWindowIcon(QIcon(":/images/newfile"));
    setCurrentFile("");
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
    newAction = new QAction(tr("&New"), this);


}

