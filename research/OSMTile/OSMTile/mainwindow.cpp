#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    osm = new OSMWidget(this, &manager);
    this->setCentralWidget(osm);
    osm->update_map();
    osm->setFocus();
}

MainWindow::~MainWindow()
{

}

