#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QLabel>
#include <QWidgetList>
#include <QAction>
#include <QActionGroup>
#include <QToolBar>
#include "editor.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void newFile();
    void openFile(const QString & fileName);

private slots:
    void open();
    void save();
    void saveas();
    void cut();
    void copy();
    void paste();
    void about();
    void updateActions();
    void loadFiles();

protected:
    void closeEvent(QCloseEvent * event);


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    void createActions();
    void createMenus();
    void createToolbars();
    void createStatusbars();
    void addEditor(Editor * editor);
    Editor * activeEditor();
    QMdiArea * mdiArea;
    QLabel * readyLbl;
    QWidgetList windows;

    QMenu * fileMenu;
    QMenu * editMenu;
    QMenu * windowMenu;
    QMenu * helpMenu;

    QToolBar * fileToolbar;
    QToolBar * editToolbar;

    QAction * newAction;
    QAction * openAction;
    QAction * saveAction;
    QAction * saveasAction;
    QAction * exitAction;
    QAction * cutAction;
    QAction * copyAction;
    QAction * pasteAction;
    QAction * closeAction;
    QAction * closeAllAction;
    QAction * tileAction;
    QAction * cascadeAction;
    QAction * nextAction;
    QAction * previousAction;
    QAction * aboutAction;
    QAction * aboutQtAction;
    QAction * separatorAction;
    QActionGroup * windowsAction;
};
#endif // MAINWINDOW_H
