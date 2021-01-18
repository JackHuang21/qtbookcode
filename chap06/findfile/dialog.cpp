#include "dialog.h"
#include <QStringList>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{

    lblName = new QLabel(tr("Name:"));
    editName = new QLineEdit;
    lblName->setBuddy(editName);

    lblLookDir = new QLabel(tr("Look in:"));
    editLookDir = new QLineEdit;
    lblLookDir->setBuddy(editLookDir);

    chkSubDir = new QCheckBox(tr("Include Subfolders"));

    QStringList labels;
    labels << tr("Name") << tr("In Folder") << tr("Size") << tr("Modifed");
    tableWidhget = new QTreeWidget;
    tableWidhget->setColumnCount(4);
    tableWidhget->setHeaderLabels(labels);


    lblMessage = new QLabel(tr("0 files found"));
    lblMessage->setFrameShape(QLabel::Panel);
    lblMessage->setFrameShadow(QLabel::Sunken);

    btnFind = new QPushButton(tr("&Find"));
    btnStop = new QPushButton(tr("Stop"));
    btnClose = new QPushButton(tr("Close"));
    btnHelp = new QPushButton(tr("Help"));

    connect(btnClose, &QPushButton::clicked, this, &Dialog::close);

    leftLayout = new QGridLayout;
    leftLayout->addWidget(lblName, 0, 0);
    leftLayout->addWidget(editName, 0, 1);
    leftLayout->addWidget(lblLookDir, 1, 0);
    leftLayout->addWidget(editLookDir, 1, 1);
    leftLayout->addWidget(chkSubDir, 2, 0, 1, 2);
    leftLayout->addWidget(tableWidhget, 3, 0, 1, 2);
    leftLayout->addWidget(lblMessage, 4, 0, 1, 2);

    rightLayout = new QVBoxLayout;
    rightLayout->addWidget(btnFind);
    rightLayout->addWidget(btnStop);
    rightLayout->addWidget(btnClose);
    rightLayout->addStretch();
    rightLayout->addWidget(btnHelp);


    mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Find files or floders"));
}

Dialog::~Dialog()
{
}

