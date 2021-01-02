#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QAction>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include "finddialog.h"
#include "spreadsheet.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent * event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveas();
    void find();
    void goToCell();
    void sort();
    void about();
    void openRecentFile();
    void updateStatusBar();
    void spreadsheetModified();

private:
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBars();
    void readSettings();
    void writeSettings();
    bool okToContinue();
    bool loadFile(const QString & filename);
    bool saveFile(const QString & filename);
    void setCurrentFile(const QString & filename);
    void updateRecentFileActions();
    QString strippedName(const QString & fullFilename);

    Spreadsheet * spreadsheet;
    FindDialog * findDialog;
    QLabel * locationLabel;
    QLabel * formulaLabel;
    QStringList recentFiles;
    QString curFile;

    enum { MaxRecentFile = 5 };
    QAction * recentFileActions[MaxRecentFile];
    QAction * separtorAction;

    QMenu * fileMenu;
    QMenu * editMenu;
    QMenu * selectSubMenu;
    QMenu * toolsMenu;
    QMenu * optionMenu;
    QMenu * helpMenu;
    QToolBar * fileToolBar;
    QToolBar * editToolBar;
    QAction * newAction;
    QAction * openAction;
    QAction * saveAction;
    QAction * saveasAction;
    QAction * exitAction;
    QAction * cutAction;
    QAction * copyAction;
    QAction * pasteAction;
    QAction * deleteAction;
    QAction * selectRowAction;
    QAction * selectColumnAction;
    QAction * selectAllAction;
    QAction * findAction;
    QAction * goToCellAction;
    QAction * recalculateAction;
    QAction * sortAction;
    QAction * showGridAction;
    QAction * autoRecalcAction;
    QAction * aboutAction;
    QAction * aboutQtAction;
};
#endif // MAINWINDOW_H
