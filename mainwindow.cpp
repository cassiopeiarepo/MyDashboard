#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <app/Gui/Views/TrivialTextEditor.h>
#include <app/Gui/Views/TrivialGraphicsView.h>
#include <app/Gui/Views/TrivialGuiItems.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //text_ditor = new TrivialTextEditor(this);
    //this->setCentralWidget(text_ditor);

    
    //gview = new TrivialGraphicsView();
    //gview->setParent(this);
    //gview->move(100, 100);
    //gview->resize(800, 600);

    //this->setCentralWidget(gview);

    /*
    MyCheckBox* checkbox = new MyCheckBox("Test2");
    checkbox->setParent(this);
    checkbox->move(0, 0);
    checkbox->resize(200, 50);
    */

    /*
    TestWidget* widget1 = new TestWidget("wid1");
    widget1->setParent(this);
    widget1->move(50, 50);
    widget1->resize(50, 50);

    TestWidget* widget2 = new TestWidget("wid2");
    widget2->setParent(this);
    widget2->move(100, 50);
    widget2->resize(50, 50);
    */

    resize(1024, 800);
}

MainWindow::~MainWindow()
{

}

