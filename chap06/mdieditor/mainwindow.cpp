#include <QApplication>
#include <QMenuBar>
#include <QStatusBar>
#include <QTimer>
#include <QMdiSubWindow>
#include <QMessageBox>
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea;
    setCentralWidget(mdiArea);
    connect(mdiArea, &QMdiArea::subWindowActivated, this, &MainWindow::updateActions);
    createActions();
    createMenus();
    createToolbars();
    createStatusbars();

    setWindowIcon(QPixmap(":/images/icon"));
    setWindowTitle(tr("MDI Editor"));
    QTimer::singleShot(0, this, &MainWindow::loadFiles);
}

MainWindow::~MainWindow()
{
}


void MainWindow::createActions()
{
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("create a new file"));
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);

    openAction = new QAction(tr("&Open"), this);
    openAction->setIcon(QIcon(":/images/open"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("open a existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/images/save"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("save the file to disk"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);

    saveasAction = new QAction(tr("Saveas"), this);
    saveasAction->setStatusTip(tr("save the file under a new name"));
    connect(saveasAction, &QAction::triggered, this, &MainWindow::saveas);

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("exit the application"));
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    cutAction = new QAction(tr("Cu&t"), this);
    cutAction->setIcon(QIcon(":/images/cut"));
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("cut the current selection to the "
                               "clipboard"));
    connect(cutAction, &QAction::triggered, this, &MainWindow::cut);

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon(":/images/copy"));
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("copy the current selection to the "
                               "clipboard"));
    connect(copyAction, &QAction::triggered, this, &MainWindow::copy);

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/images/paste"));
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("paste the clipboard's content"
                                 "at the cursor position"));
    connect(pasteAction, &QAction::triggered, this, &MainWindow::paste);

    closeAction = new QAction(tr("Cl&ose"), this);
    closeAction->setShortcut(tr("Ctrl+W"));
    closeAction->setStatusTip(tr("close the active window"));
    connect(closeAction, &QAction::triggered, mdiArea, &QMdiArea::closeActiveSubWindow);

    closeAllAction = new QAction(tr("Close &All"), this);
    closeAllAction->setStatusTip(tr("close all the windows"));
    connect(closeAllAction, &QAction::triggered, this, &MainWindow::close);

    tileAction = new QAction(tr("&Tile"), this);
    tileAction->setStatusTip(tr("tile the windows"));
    connect(tileAction, &QAction::triggered, mdiArea, &QMdiArea::tileSubWindows);

    cascadeAction = new QAction(tr("&Cascade"), this);
    cascadeAction->setStatusTip(tr("cascade the windows"));
    connect(cascadeAction, &QAction::triggered, mdiArea, &QMdiArea::cascadeSubWindows);

    nextAction = new QAction(tr("Ne&xt"), this);
    nextAction->setShortcut(QKeySequence::NextChild);
    nextAction->setStatusTip(tr("move the focus to the next window"));
    connect(nextAction, &QAction::triggered, mdiArea, &QMdiArea::activateNextSubWindow);

    previousAction = new QAction(tr("Pre&vious"), this);
    previousAction->setShortcut(QKeySequence::PreviousChild);
    previousAction->setStatusTip(tr("move the focus to the next window"));
    connect(previousAction, &QAction::triggered, mdiArea, &QMdiArea::activatePreviousSubWindow);

    separatorAction = new QAction(this);
    separatorAction->setSeparator(true);

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("show the application's about box"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("show the Qt libiary's about box"));
    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);

    windowsAction = new QActionGroup(this);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveasAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    windowMenu = menuBar()->addMenu(tr("&Window"));
    windowMenu->addAction(closeAction);
    windowMenu->addAction(closeAllAction);
    windowMenu->addSeparator();
    windowMenu->addAction(tileAction);
    windowMenu->addAction(cascadeAction);
    windowMenu->addSeparator();
    windowMenu->addAction(nextAction);
    windowMenu->addAction(previousAction);
    windowMenu->addSeparator();

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolbars()
{
    fileToolbar = addToolBar(tr("File"));
    fileToolbar->addAction(newAction);
    fileToolbar->addAction(openAction);
    fileToolbar->addAction(saveAction);

    editToolbar = addToolBar(tr("Edit"));
    editToolbar->addAction(cutAction);
    editToolbar->addAction(copyAction);
    editToolbar->addAction(pasteAction);
}

void MainWindow::createStatusbars()
{
    readyLbl = new QLabel(tr(" Ready"));
    statusBar()->addWidget(readyLbl, 1);
}


void MainWindow::loadFiles()
{
    QStringList args = QApplication::arguments();
    args.removeFirst();
    if (!args.isEmpty())
    {
        foreach (QString arg, args)
            openFile(arg);
        mdiArea->cascadeSubWindows();
    }
    else {
        newFile();
    }
    mdiArea->activateNextSubWindow();
}

void MainWindow::newFile()
{
    Editor * editor = new Editor;
    editor->newFile();
    addEditor(editor);
}

void MainWindow::openFile(const QString & fileName)
{
    Editor * editor = Editor::openFile(fileName, this);
    if (editor)
        addEditor(editor);
}

void MainWindow::open()
{
    Editor * editor = Editor::open(this);
    if (editor)
        addEditor(editor);
}

void MainWindow::addEditor(Editor *editor)
{
    connect(editor, &Editor::copyAvailable, cutAction, &QAction::setEnabled);
    connect(editor, &Editor::copyAvailable, copyAction, &QAction::setEnabled);
    QMdiSubWindow * subWindow = mdiArea->addSubWindow(editor);
    windowMenu->addAction(editor->windowMenuAction());
    windowsAction->addAction(editor->windowMenuAction());
    subWindow->show();
}

void MainWindow::save()
{
    if (activeEditor())
        activeEditor()->save();
}

void MainWindow::saveas()
{
    if (activeEditor())
        activeEditor()->saveas();
}

Editor * MainWindow::activeEditor()
{
    // 获取当前子窗口，强制转换为editor类型并返回
    QMdiSubWindow * subWindow = mdiArea->activeSubWindow();
    if (subWindow)
        return qobject_cast<Editor *>(subWindow->widget());
    return nullptr;
}


void MainWindow::cut()
{
    if (activeEditor())
        activeEditor()->cut();
}

void MainWindow::copy()
{
    if (activeEditor())
        activeEditor()->copy();
}

void MainWindow::paste()
{
    if (activeEditor())
        activeEditor()->paste();
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("About MDI Editor"),
                       tr("<h2>Editor 1.1</h2>"
                          "<p>Copyright &copy; 2007 Software Inc."
                          "<p>MDI Editor is a small apllication that demonstrates "
                          "QMdiArea."));
}

void MainWindow::updateActions()
{
    bool hasEditor = (activeEditor() != nullptr);
    bool hasSelection = activeEditor() && activeEditor()->textCursor().hasSelection();

    saveAction->setEnabled(hasEditor);
    saveasAction->setEnabled(hasEditor);
    cutAction->setEnabled(hasSelection);
    copyAction->setEnabled(hasSelection);
    pasteAction->setEnabled(hasEditor);
    closeAction->setEnabled(hasEditor);
    closeAllAction->setEnabled(hasEditor);
    tileAction->setEnabled(hasEditor);
    cascadeAction->setEnabled(hasEditor);
    nextAction->setEnabled(hasEditor);
    previousAction->setEnabled(hasEditor);
    separatorAction->setVisible(hasEditor);

    if (activeEditor())
        activeEditor()->windowMenuAction()->setChecked(true);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    mdiArea->closeAllSubWindows();
    if (!mdiArea->subWindowList().isEmpty()) {
        event->ignore();
    }
    else {
        event->accept();
    }
}





