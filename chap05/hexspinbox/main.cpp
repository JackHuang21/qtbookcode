#include <QApplication>
#include "hexspinbox.h"

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    HexSpinBox hexSpinBox;
    hexSpinBox.show();
    return a.exec();
}
