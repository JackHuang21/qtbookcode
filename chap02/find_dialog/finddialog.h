#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

signals:
    void findNext(const QString & str, Qt::CaseSensitivity cs);
    void findPrevious(const QString & str, Qt::CaseSensitivity cs);

private slots:
    void findClicked();
    void enableFindButton(const QString & text);

private:
    QLabel * label;
    QLineEdit * lineEdit;
    QCheckBox * caseCheckBox;
    QCheckBox * backwardCheckBox;
    QPushButton * findButton;
    QPushButton * closeButton;
};
#endif // DIALOG_H
