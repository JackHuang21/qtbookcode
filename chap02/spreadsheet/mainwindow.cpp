#include "mainwindow.h"
#include <QApplication>
#include <QIcon>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QSettings>
#include <QDebug>
#include "gotocelldialog.h"
#include "sortdialog.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    spreadsheet = new Spreadsheet;
    setCentralWidget(spreadsheet);

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBars();

    readSettings();
    findDialog = nullptr;

    setWindowIcon(QIcon(":/images/icon"));
    setCurrentFile("");
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/image/new"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("create a new spreadsheet file"));
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);

    openAction = new QAction(tr("&Open"), this);
    openAction->setIcon(QIcon(":/image/open"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("open an exist spreadsheet file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/image/save"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("save the spreadsheet to disk"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);

    saveasAction = new QAction(tr("Save &As..."), this);
    saveasAction->setStatusTip(tr("save the spreadsheet under a new"));
    connect(saveasAction, &QAction::triggered, this, &MainWindow::saveas);

    for (int i = 0; i < MaxRecentFile; i++)
    {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], &QAction::triggered,
                this, &MainWindow::openRecentFile);
    }

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("exit the application"));
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    cutAction = new QAction(tr("Cu&t"), this);
    cutAction->setIcon(QIcon(":/image/cut"));
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("cut current selection's contents to clipboard"));
    connect(cutAction, &QAction::triggered, spreadsheet, &Spreadsheet::cut);

    copyAction = new QAction(tr("&Copt"), this);
    copyAction->setIcon(QIcon(":/image/copy"));
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("copy current selection's contents to clipboard"));
    connect(copyAction, &QAction::triggered, spreadsheet, &Spreadsheet::copy);

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/image/paste"));
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("paste current clipboard's contents to current selection"));
    connect(pasteAction, &QAction::triggered, spreadsheet, &Spreadsheet::paste);

    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setStatusTip(tr("delete the current selection contents"));
    connect(deleteAction, &QAction::triggered, spreadsheet, &Spreadsheet::del);

    selectRowAction = new QAction(tr("&Row"), this);
    selectRowAction->setStatusTip(tr("select all the cells in the current row"));
    connect(selectRowAction, &QAction::triggered, spreadsheet, &Spreadsheet::selectCurrentRow);

    selectColumnAction = new QAction(tr("&Column"), this);
    selectColumnAction->setStatusTip(tr("select all the cells in the current column"));
    connect(selectColumnAction, &QAction::triggered, spreadsheet, &Spreadsheet::selectCurrentColumn);

    selectAllAction = new QAction(tr("&All"), this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setStatusTip(tr("select all the cells in the spreadsheet"));
    connect(selectAllAction, &QAction::triggered, spreadsheet, &Spreadsheet::selectAll);

    findAction = new QAction(tr("&Find..."), this);
    findAction->setIcon(QIcon(":/image/find"));
    findAction->setShortcut(QKeySequence::Find);
    findAction->setStatusTip(tr("find a match cell"));
    connect(findAction, &QAction::triggered, this, &MainWindow::find);

    goToCellAction = new QAction(tr("&Go To Cell..."), this);
    goToCellAction->setIcon(QIcon(":/image/goto"));
    goToCellAction->setShortcut(tr("Ctrl+G"));
    goToCellAction->setStatusTip(tr("go to specific cell"));
    connect(goToCellAction, &QAction::triggered, this, &MainWindow::goToCell);

    recalculateAction = new QAction(tr("&Recalculate"), this);
    recalculateAction->setShortcut(tr("F9"));
    recalculateAction->setStatusTip(tr("recalculate all the spreadsheet formulas"));
    connect(recalculateAction, &QAction::triggered, spreadsheet, &Spreadsheet::recalculate);

    sortAction = new QAction(tr("&Sort..."), this);
    sortAction->setStatusTip(tr("sort the selected cells or all the cells"));
    connect(sortAction,&QAction::triggered, this, &MainWindow::sort);

    showGridAction = new QAction(tr("Show grid"), this);
    showGridAction->setCheckable(true);
    showGridAction->setChecked(spreadsheet->showGrid());
    showGridAction->setStatusTip(tr("show or hide the spreadsheet's grid"));
    connect(showGridAction, &QAction::toggled, spreadsheet, &Spreadsheet::setShowGrid);

    autoRecalcAction = new QAction(tr("&Auto Recalculate"), this);
    autoRecalcAction->setCheckable(true);
    autoRecalcAction->setChecked(spreadsheet->autoRecalculate());
    autoRecalcAction->setStatusTip(tr("switch auto recalculate on or off"));
    connect(autoRecalcAction, &QAction::toggled, spreadsheet, &Spreadsheet::setAutoRecaculate);

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("show the application's about box"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("show the Qt library's about boc"));
    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveasAction);
    separtorAction = fileMenu->addSeparator();
    for (int i = 0; i < MaxRecentFile; i++)
        fileMenu->addAction(recentFileActions[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);
    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(goToCellAction);

    selectSubMenu = menuBar()->addMenu(tr("&Select"));
    selectSubMenu->addAction(selectRowAction);
    selectSubMenu->addAction(selectColumnAction);
    selectSubMenu->addAction(selectAllAction);

    toolsMenu =  menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(recalculateAction);
    toolsMenu->addAction(sortAction);

    optionMenu = menuBar()->addMenu(tr("&Options"));
    optionMenu->addAction(showGridAction);
    optionMenu->addAction(autoRecalcAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}


void MainWindow::createContextMenu()
{
    spreadsheet->addAction(cutAction);
    spreadsheet->addAction(copyAction);
    spreadsheet->addAction(pasteAction);
    spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(findAction);
    editToolBar->addAction(goToCellAction);
}

void MainWindow::createStatusBars()
{
    locationLabel = new QLabel(tr(" W999 "));
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);

    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(formulaLabel, 1);
    connect(spreadsheet, &Spreadsheet::currentCellChanged, this, &MainWindow::updateStatusBar);
    connect(spreadsheet, &Spreadsheet::modified, this, &MainWindow::spreadsheetModified);
    updateStatusBar();
}

void MainWindow::updateStatusBar()
{
    locationLabel->setText(spreadsheet->currentLocation());
    formulaLabel->setText(spreadsheet->currentFormula());
}

void MainWindow::spreadsheetModified()
{
    setWindowModified(true);
    updateStatusBar();
}

void MainWindow::newFile()
{
    if (okToContinue())
    {
        spreadsheet->clear();
        setCurrentFile("");
    }
}

void MainWindow::open()
{
    if (okToContinue())
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open Spreadsheet", "."),
                                                        tr("Spreadsheet files (*.sp"));
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::loadFile(const QString &filename)
{
    if (!spreadsheet->readFile(filename))
    {
        statusBar()->showMessage(tr("Loading canceled"), 2000);
        return false;
    }
    setCurrentFile(filename);
    statusBar()->showMessage(tr("File loaded"), 2000);
    return true;
}

bool MainWindow::save()
{
    if (curFile.isEmpty())
        return saveas();
    else
        return saveFile(curFile);
}

bool MainWindow::saveFile(const QString &filename)
{
    if (!spreadsheet->writeFile(filename))
    {
        statusBar()->showMessage(tr("Saving canceled"), 2000);
        return false;
    }

    setCurrentFile(filename);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

bool MainWindow::saveas()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Spreadsheet"), ".",
                                                    tr("Spreadsheet file (*.sp)"));
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (okToContinue())
    {
        writeSettings();
        event->accept();
    }
    else
        event->ignore();
}

bool MainWindow::okToContinue()
{
    if (isWindowModified())
    {
        int r = QMessageBox::warning(this, tr("Spreadshett"),
                                     tr("The document has been modified.\n"
                                        "Do you want to save your changes?"),
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (r == QMessageBox::Yes)
            return save();
        else if (r == QMessageBox::Cancel)
            return false;
    }
    return true;
}


void MainWindow::setCurrentFile(const QString &filename)
{
    curFile = filename;
    setWindowModified(false);
    QString shownName = tr("Untitled");
    if (!curFile.isEmpty())
    {
        shownName = strippedName(curFile);
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);
        updateRecentFileActions();
    }
    setWindowTitle(tr("%1[*] - %2").arg(shownName)
                   .arg(tr("Spreadsheet")));
}

QString MainWindow::strippedName(const QString &fullFilename)
{
    return QFileInfo(fullFilename).fileName();
}

void MainWindow::updateRecentFileActions()
{
    QMutableStringListIterator i(recentFiles);

    while (i.hasNext())
    {
        if (!QFile::exists(i.next()))
            i.remove();
    }

    for (int j = 0; j < MaxRecentFile; ++j)
    {
        if (j < recentFiles.count())
        {
            QString text = tr("&%1 %2").arg(j + 1)
                    .arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        }
        else
            recentFileActions[j]->setVisible(false);
    }
    separtorAction->setVisible(!recentFiles.isEmpty());
}

void MainWindow::openRecentFile()
{
    if (okToContinue())
    {
        QAction * action = qobject_cast<QAction *>(sender());
        if (action)
            loadFile(action->data().toString());
    }
}

void MainWindow::find()
{
    if (!findDialog)
    {
        findDialog = new FindDialog(this);
        connect(findDialog, &FindDialog::findNext, spreadsheet, &Spreadsheet::findNext);
        connect(findDialog, &FindDialog::findPrevious, spreadsheet, &Spreadsheet::findPrevious);
    }
    findDialog->show();
    findDialog->raise();
    findDialog->activateWindow();
}

void MainWindow::goToCell()
{
    GoToCellDialog dialog(this);
    if (dialog.exec())
    {
        QString str = dialog.lineEdit->text().toUpper();
        spreadsheet->setCurrentCell(str.mid(1).toInt() - 1, str[0].unicode() - 'A');
    }
}

void MainWindow::sort()
{
    SortDialog dialog(this);
    QTableWidgetSelectionRange range = spreadsheet->selectedRange();
    dialog.setColumnRange('A' + range.leftColumn(), 'A' + range.rightColumn());
    if (dialog.exec())
    {
        SpreadsheetCompare compare;
        compare.keys[0] =
                dialog.primaryColumnCombo->currentIndex();
        compare.keys[1] =
                dialog.secondaryColumnCombo->currentIndex() - 1;
        compare.keys[2] =
                dialog.tertiaryColumnCombo->currentIndex() - 1;
        compare.ascending[0] =
                (dialog.primaryOrderCombo->currentIndex() == 0);
        compare.ascending[1] =
                (dialog.secondaryOrderCombo->currentIndex() == 0);
        compare.ascending[2] =
                (dialog.tertiaryOrderCombo->currentIndex() == 0);
        spreadsheet->sort(compare);
    }
}
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Spreadsheet"),
                       tr("<h2>Spreadsheet 1.1</h2>"
                          "<p>Copyright &copy; 2021 Software Inc."
                          "<p>Spreasheet is a small application that"
                          "demonstrates QAction, QMainWindow, QMenubar,"
                          "QStatusBar, QTableWidget, QToolBar, and many other "
                          "Qt classes."));
}

void MainWindow::readSettings()
{
    QSettings settings("Software Inc.", "Spreadsheet");
    restoreGeometry(settings.value("geometry").toByteArray());

    recentFiles = settings.value("recentFiles").toStringList();
    updateRecentFileActions();

    bool showGrid = settings.value("showGrid", true).toBool();

    showGridAction->setChecked(showGrid);



    bool autoRecalc = settings.value("autoRecalc", true).toBool();
    autoRecalcAction->setChecked(autoRecalc);
}

void MainWindow::writeSettings()
{
    QSettings settings("Software Inc.", "Spreadsheet");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("recentFiles", recentFiles);
    settings.setValue("showGrid", showGridAction->isChecked());
    settings.setValue("autoRecalc", autoRecalcAction->isChecked());
}


