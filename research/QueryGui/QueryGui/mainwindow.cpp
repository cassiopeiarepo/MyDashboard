#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    central_widget = new QWidget(this);

    this->setCentralWidget(central_widget);

    gridLayout = new QGridLayout(central_widget);

    verticalLayout = new QVBoxLayout();

    query_widget = new TrivialQueryWidget(central_widget);

    list_widget = new QListWidget(central_widget);

    verticalLayout->addWidget(query_widget);
    verticalLayout->addWidget(list_widget);

    gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);
    gridLayout->setContentsMargins(0, 0, 0, 0);

}

MainWindow::~MainWindow()
{
}

