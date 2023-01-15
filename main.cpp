#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
#include "coreqt/Common/tml.h"

#include "app/Utils/Workspace.h"
#include "app/Gui/Views/TrivialMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    TrivialMainWindow w;

    Workspace::get()->init("D:/Workspace");
    w.init();
    w.show();

    return a.exec();
}
