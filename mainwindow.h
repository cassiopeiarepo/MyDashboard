#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class TrivialTextEditor;
class TrivialGraphicsView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    TrivialTextEditor* text_ditor;
    TrivialGraphicsView* gview;
};

#endif // MAINWINDOW_H
