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
    Editor();

    void newFile();
    void save();
    void saveas();
    QSize sizeHint() const;
    QAction * windowMenuAction() const { return action; }
    static Editor * open(QWidget * parent = 0);
    static Editor * openFile(const QString & fileName,
                             QWidget * parent = 0);

protected:
    void closeEvent(QCloseEvent * event);

private slots:
    void documentWasModified();

private:
    bool okToContinue();
    bool saveFile(const QString & fileName);
    void setCurrentFile(const QString & fileName);
    bool readFile(const QString & fileName);
    bool writeFile(const QSrting & fileName);
    QString strippedName(const QString & fileName);

    QString curFile;
    bool isUntitled;
    QAction * action;
};

#endif // EDITOR_H
