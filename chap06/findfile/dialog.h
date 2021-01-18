#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QTreeWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

class Dialog : public QDialog
{
    Q_OBJECT

private:
    QLabel * lblName;
    QLabel * lblLookDir;
    QLineEdit * editName;
    QLineEdit * editLookDir;
    QCheckBox * chkSubDir;
    QTreeWidget * tableWidhget;
    QLabel * lblMessage;
    QPushButton * btnFind;
    QPushButton * btnStop;
    QPushButton * btnClose;
    QPushButton * btnHelp;
    QGridLayout * leftLayout;
    QVBoxLayout * rightLayout;
    QHBoxLayout * mainLayout;

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
};
#endif // DIALOG_H
