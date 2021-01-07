#include "iconeditorplugin.h"

IconEditorPlugin::IconEditorPlugin(QObject * parent)
    : QObject(parent)
{
}

QString IconEditorPlugin::name() const
{
    return "IconEditor";
}

QString IconEditorPlugin::includeFile() const
{
    return "iconeditor.h";
}

QString IconEditorPlugin::group() const
{
    return tr("Image Manipulation Widgets");
}

QIcon IconEditorPlugin::icon() const
{
    return QIcon(":/image/iconeditor.png");
}

QString IconEditorPlugin::tooTip() const
{
    return tr("An icon editor widget");
}

QString IconEditorPlugin::whatsThis() const
{
    return tr("This widgets is presented in chapter 5 of <i>C++ GUI"
              "Programming with Qt 4</i> as an example of a custom Qt"
              "widget.");
}

QString IconEditorPlugin::isContainer() const
{
    return false;
}

QWidget * IconEditorPlugin::createWidget(QWidget * parent)
{
    return new IconEditor(parent);
}
