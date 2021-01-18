#include "preferencedialog.h"
#include <QDebug>

PreferenceDialog::PreferenceDialog(QWidget *parent)
    : QDialog(parent)
{
    createAppearancePage();
    createWebBrowserPage();
    createMailAndNewsPage();
    createAdvancedPage();


    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
                                     QDialogButtonBox::Cancel);
    listWidget = new QListWidget;
    listWidget->addItem(tr("Appearance"));
    listWidget->addItem(tr("Web browser"));
    listWidget->addItem(tr("Mail & News"));
    listWidget->addItem(tr("Advanced"));

    stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(appearancePage);
    stackedLayout->addWidget(webBrowserPage);
    stackedLayout->addWidget(mailAndNewsPage);
    stackedLayout->addWidget(advancedPage);
    connect(listWidget, &QListWidget::currentRowChanged,
            stackedLayout, &QStackedLayout::setCurrentIndex);

    mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(1, 3);
    mainLayout->addWidget(listWidget, 0, 0);
    mainLayout->addLayout(stackedLayout, 0, 1);
    mainLayout->addWidget(buttonBox, 1, 0, 1, 2);
    setLayout(mainLayout);

    connect(buttonBox, &QDialogButtonBox::rejected, this, &PreferenceDialog::reject);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &PreferenceDialog::accept);

    setWindowTitle(tr("Preference"));
    listWidget->setCurrentRow(0);
}

PreferenceDialog::~PreferenceDialog()
{
}

void PreferenceDialog::createAppearancePage()
{
    appearancePage = new QWidget;

    openGroupBox = new QGroupBox(tr("Open at startup"));
    webBrowserCheckBox = new QCheckBox(tr("Web browser"));
    mailEditorCheckBox = new QCheckBox(tr("Mail editor"));
    newsGroupCheckBox = new QCheckBox(tr("Newsgroups"));

    toolbarsGroupBox = new QGroupBox(tr("Show toolbars as"));
    picturesAndTextRadioBtn = new QRadioButton(tr("Pictures and text"));
    pictureOnlyRadioBtn = new QRadioButton(tr("Pictures only"));
    textOnlyRadioBtn = new QRadioButton(tr("Text only"));

    toolTipsChkBox = new QCheckBox(tr("Show tooltips"));
    websiteIconChkBox = new QCheckBox(tr("Show web site icons"));
    resizeImagesChkBox = new QCheckBox(tr("Resize large images to"
                                          " fit in the windows"));

    openGrpLayout = new QVBoxLayout;
    openGrpLayout->addWidget(webBrowserCheckBox);
    openGrpLayout->addWidget(mailEditorCheckBox);
    openGrpLayout->addWidget(newsGroupCheckBox);
    openGroupBox->setLayout(openGrpLayout);

    toolbarsGrpLayout = new QVBoxLayout;
    toolbarsGrpLayout->addWidget(picturesAndTextRadioBtn);
    toolbarsGrpLayout->addWidget(pictureOnlyRadioBtn);
    toolbarsGrpLayout->addWidget(textOnlyRadioBtn);
    toolbarsGroupBox->setLayout(toolbarsGrpLayout);

    appearancePageLayout = new QVBoxLayout;
    appearancePageLayout->setMargin(0);
    appearancePageLayout->addWidget(openGroupBox);
    appearancePageLayout->addWidget(toolbarsGroupBox);
    appearancePageLayout->addWidget(toolTipsChkBox);
    appearancePageLayout->addWidget(websiteIconChkBox);
    appearancePageLayout->addWidget(resizeImagesChkBox);
    appearancePageLayout->addStretch();
    appearancePage->setLayout(appearancePageLayout);

    webBrowserCheckBox->setChecked(true);
    mailEditorCheckBox->setChecked(true);
    picturesAndTextRadioBtn->setChecked(true);
    toolTipsChkBox->setChecked(true);
    websiteIconChkBox->setChecked(true);
}

void PreferenceDialog::createWebBrowserPage()
{
    webBrowserPage = new QWidget;

    displayGroupBox = new QGroupBox(tr("Display on startup"));
    blankRadioBtn = new QRadioButton(tr("Blank page"));
    homeRadioBtn = new QRadioButton(tr("Home page"));
    lastRadioBtn = new QRadioButton(tr("Last page visited"));

    homeGroupBox = new QGroupBox(tr("Home Page"));
    lblLocation = new QLabel(tr("Location:"));
    locationLineEdit = new QLineEdit();
    //lblLocation->setBuddy(locationLineEdit);

    selectGroupBox = new QGroupBox(tr("Select the buttons"
                                      " you want in the toolbar"));
    bookmarksChkBox = new QCheckBox(tr("Bookmarks"));
    searchChkBox = new QCheckBox(tr("Search"));
    goChkBox = new QCheckBox(tr("Go"));
    printChkBox = new QCheckBox(tr("Print"));
    homeChkBox = new QCheckBox(tr("Home"));    

    displayGrpLayout = new QVBoxLayout;
    displayGrpLayout->addWidget(blankRadioBtn);
    displayGrpLayout->addWidget(homeRadioBtn);
    displayGrpLayout->addWidget(lastRadioBtn);
    displayGroupBox->setLayout(displayGrpLayout);

    homeGrpLayout = new QHBoxLayout;
    homeGrpLayout->addWidget(lblLocation);
    homeGrpLayout->addWidget(locationLineEdit);
    homeGroupBox->setLayout(homeGrpLayout);

    selectGrpLayout = new QGridLayout;
    selectGrpLayout->addWidget(bookmarksChkBox, 0, 0);
    selectGrpLayout->addWidget(searchChkBox, 0, 1);
    selectGrpLayout->addWidget(goChkBox, 1, 0);
    selectGrpLayout->addWidget(printChkBox, 1, 1);
    selectGrpLayout->addWidget(homeChkBox, 2, 0);
    selectGroupBox->setLayout(selectGrpLayout);



    webBrowserPageLayout = new QVBoxLayout;
    webBrowserPageLayout->setMargin(0);
    webBrowserPageLayout->addWidget(displayGroupBox);
    webBrowserPageLayout->addWidget(homeGroupBox);
    webBrowserPageLayout->addWidget(selectGroupBox);
    webBrowserPageLayout->addStretch();
    webBrowserPage->setLayout(webBrowserPageLayout);

    homeRadioBtn->setChecked(true);
    locationLineEdit->setText(tr("http://www.trolltech.com/"));
    bookmarksChkBox->setChecked(true);
    searchChkBox->setChecked(true);
    printChkBox->setChecked(true);
    homeChkBox->setChecked(true);
}

void PreferenceDialog::createMailAndNewsPage()
{
    mailAndNewsPage = new QWidget;

    generalSetGroupBox = new QGroupBox(tr("General settings"));
    confirmChkBox = new QCheckBox(tr("Warn when moving folders "
                                     "to the trash"));
    rememberChkBox = new QCheckBox(tr("Remember the last "
                                      "last selected message"));

    selectBtnGroupBox = new QGroupBox(tr("Select the buttons "
                                         "you want in the toolbar"));
    fileChkBox = new QCheckBox(tr("File"));
    stopChkBox = new QCheckBox(tr("Stop"));
    nextChkBox = new QCheckBox(tr("Next"));
    junkChkBox = new QCheckBox(tr("Junk"));

    generalSetGrpLayout = new QVBoxLayout;
    generalSetGrpLayout->addWidget(confirmChkBox);
    generalSetGrpLayout->addWidget(rememberChkBox);
    generalSetGroupBox->setLayout(generalSetGrpLayout);

    selectBtnGrpLayout = new QGridLayout;
    selectBtnGrpLayout->addWidget(fileChkBox,0, 0);
    selectBtnGrpLayout->addWidget(stopChkBox, 0, 1);
    selectBtnGrpLayout->addWidget(nextChkBox, 1, 0);
    selectBtnGrpLayout->addWidget(junkChkBox, 1, 1);
    selectBtnGroupBox->setLayout(selectBtnGrpLayout);

    mailAndNewsPageLayout = new QVBoxLayout;
    mailAndNewsPageLayout->setMargin(0);
    mailAndNewsPageLayout->addWidget(generalSetGroupBox);
    mailAndNewsPageLayout->addWidget(selectBtnGroupBox);
    mailAndNewsPageLayout->addStretch();
    mailAndNewsPage->setLayout(mailAndNewsPageLayout);

    confirmChkBox->setChecked(true);
    rememberChkBox->setChecked(true);
    nextChkBox->setChecked(true);
    junkChkBox->setChecked(true);
}

void PreferenceDialog::createAdvancedPage()
{
    advancedPage = new QWidget;
    featuresGroupBox = new QGroupBox;
    javaChkBox = new QCheckBox(tr("Enable Java"));
    ftpChkBox = new QCheckBox(tr("Use this email for "
                                 "anonymous FTP:"));
    ftpLineEdit = new QLineEdit();

    featuresGrpLayout = new QVBoxLayout;
    featuresGrpLayout->addWidget(javaChkBox);
    featuresGrpLayout->addWidget(ftpChkBox);
    featuresGrpLayout->addWidget(ftpLineEdit);
    featuresGroupBox->setLayout(featuresGrpLayout);

    advancedPageLayout = new QVBoxLayout;
    advancedPageLayout->setMargin(0);
    advancedPageLayout->addWidget(featuresGroupBox);
    advancedPageLayout->addStretch();
    advancedPage->setLayout(advancedPageLayout);

    javaChkBox->setChecked(true);
    ftpLineEdit->setEnabled(false);
}
