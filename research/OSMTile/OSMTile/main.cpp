#include "mainwindow.h"

#include <QApplication>
#include <QLabel>

#include <QGraphicsView>
#include <QGraphicsScene>

int main(int argc, char *argv[])
{
    //QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, false);

    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
