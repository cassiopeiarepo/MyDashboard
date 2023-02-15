#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

#include "TrivialQueryWidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    TrivialQueryWidget* query_widget;
    QListWidget *list_widget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QWidget* central_widget;

};
#endif // MAINWINDOW_H
