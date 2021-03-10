#include "editor.h"

Editor::Editor()
{

}

void Editor::newFile()
{
    static int documentNumber = 1;
    curFile = tr("document%1").arg(documentNumber);
    swtWindowTitle(curFile + "[*]");

}
