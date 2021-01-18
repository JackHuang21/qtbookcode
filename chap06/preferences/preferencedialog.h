#ifndef PREFERENCEDIALOG_H
#define PREFERENCEDIALOG_H

#include <QDialog>
#include <QStackedLayout>
#include <QWidget>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QListWidget>


class PreferenceDialog : public QDialog
{
    Q_OBJECT

public:
    PreferenceDialog(QWidget *parent = nullptr);
    ~PreferenceDialog();

private:
    void createAppearancePage();
    void createWebBrowserPage();
    void createMailAndNewsPage();
    void createAdvancedPage();

    QStackedLayout * stackedLayout;
    QListWidget * listWidget;
    QWidget * appearancePage;
    QWidget * webBrowserPage;
    QWidget * mailAndNewsPage;
    QWidget * advancedPage;
    QDialogButtonBox * buttonBox;

    QGroupBox * openGroupBox;
    QCheckBox * webBrowserCheckBox;
    QCheckBox * mailEditorCheckBox;
    QCheckBox * newsGroupCheckBox;
    QGroupBox * toolbarsGroupBox;
    QRadioButton * picturesAndTextRadioBtn;
    QRadioButton * pictureOnlyRadioBtn;
    QRadioButton * textOnlyRadioBtn;
    QCheckBox * toolTipsChkBox;
    QCheckBox * websiteIconChkBox;
    QCheckBox * resizeImagesChkBox;
    QVBoxLayout * openGrpLayout;
    QVBoxLayout * toolbarsGrpLayout;
    QVBoxLayout * appearancePageLayout;

    QGroupBox * displayGroupBox;
    QRadioButton * blankRadioBtn;
    QRadioButton * homeRadioBtn;
    QRadioButton * lastRadioBtn;

    QGroupBox * homeGroupBox;
    QLabel * lblLocation;
    QLineEdit * locationLineEdit;

    QGroupBox * selectGroupBox;
    QCheckBox * bookmarksChkBox;
    QCheckBox * searchChkBox;
    QCheckBox * goChkBox;
    QCheckBox * printChkBox;
    QCheckBox * homeChkBox;

    QVBoxLayout * displayGrpLayout;
    QHBoxLayout * homeGrpLayout;
    QGridLayout * selectGrpLayout;
    QVBoxLayout * webBrowserPageLayout;

    QGroupBox * generalSetGroupBox;
    QCheckBox * confirmChkBox;
    QCheckBox * rememberChkBox;
    QGroupBox * selectBtnGroupBox;
    QCheckBox * fileChkBox;
    QCheckBox * stopChkBox;
    QCheckBox * nextChkBox;
    QCheckBox * junkChkBox;

    QVBoxLayout * generalSetGrpLayout;
    QGridLayout * selectBtnGrpLayout;
    QVBoxLayout * mailAndNewsPageLayout;

    QGroupBox * featuresGroupBox;
    QCheckBox * javaChkBox;
    QCheckBox * ftpChkBox;
    QLineEdit * ftpLineEdit;
    QVBoxLayout * featuresGrpLayout;
    QVBoxLayout * advancedPageLayout;

    QGridLayout * mainLayout;
};
#endif // PREFERENCEDIALOG_H
