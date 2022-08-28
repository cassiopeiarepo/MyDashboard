#include "mainwindow.h"

#include <QApplication>
#include "coreqt/Common/tml.h"

#include "app/Utils/Workspace.h"
#include "app/Gui/Views/TrivialMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Workspace::get()->init("D:/Workspace");

    //testTml(QString("c:\\DashboardTest\\"));

    //MainWindow w;
    //w.show();

    TrivialMainWindow w;
    w.show();

    return a.exec();
}
