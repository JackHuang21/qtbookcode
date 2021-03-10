#ifndef MAILCLIENT_H
#define MAILCLIENT_H

#include <QMainWindow>
#include <QSplitter>
#include <QTreeWidget>
#include <QTextEdit>
#include <QTreeWidget>
#include <QIcon>
#include <QString>
#include <QCloseEvent>


class MailClient : public QMainWindow
{
    Q_OBJECT

public:
    MailClient(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent * event);

private:
    void addFolder(const QIcon & icon, const QString & name);
    void addMessage(const QString & subject, const QString & from,
                    const QString & date);
    void readSettings();
    void writeSettings();

    QSplitter * mainSplitter;
    QSplitter * rightSplitter;
    QTreeWidget * foldersTreeWidget;
    QTreeWidget * messagesTreeWidget;
    QTextEdit * textEdit;
};
#endif // MAILCLIENT_H
