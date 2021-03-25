#ifndef EDITOR_H
#define EDITOR_H

#include <QString>
#include <QTextEdit>
#include <QSize>
#include <QCloseEvent>
#include <QAction>



class Editor : public QTextEdit
{
    Q_OBJECT
public:
    Editor(QWidget * parent  = nullptr);

    void newFile();
    bool save();
    bool saveas();
    QSize sizeHint() const;
    QAction * windowMenuAction() const { return action; }
    static Editor * open(QWidget * parent = nullptr);
    static Editor * openFile(const QString & fileName,
                             QWidget * parent = nullptr);

protected:
    void closeEvent(QCloseEvent * event);

private slots:
    void documentWasModified();

private:
    bool okToContinue();
    bool saveFile(const QString & fileName);
    void setCurrentFile(const QString & fileName);
    bool readFile(const QString & fileName);
    bool writeFile(const QString & fileName);
    QString strippedName(const QString & fileName);

    QString curFile;
    bool isUntitled;
    QAction * action;
};

#endif // EDITOR_H
