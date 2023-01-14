#include "mainwindow.h"

#include <QApplication>
#include "coreqt/Common/tml.h"

#include "app/Utils/Workspace.h"
#include "app/Gui/Views/TrivialMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    

    //testTml(QString("c:\\DashboardTest\\"));

    //MainWindow w;
    //w.show();

    TrivialMainWindow w;

    Workspace::get()->init("D:/Workspace");
    w.init();
    w.show();

    //QMainWindow win1;
    //win1.show();

    //QMainWindow win2;
    //win2.show();

    return a.exec();
}
