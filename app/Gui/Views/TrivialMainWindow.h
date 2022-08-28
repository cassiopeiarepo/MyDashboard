#ifndef _TRIVIAL_MAINWINDOW_H
#define _TRIVIAL_MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QTabWidget>

class TrivialDirExplorer;
class TrivialDocumentsView;
class CentralWidget;


class TrivialMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    TrivialMainWindow(QWidget* parent = nullptr);
    ~TrivialMainWindow();

    enum PanelPlace {
        LEFT, CENTER, RIGHT,
        BOTTOM_LEFT, BOTTOM_RIGHT
    };

    void addPanel(PanelPlace place, QString& tab_caption, QWidget* panel);

private slots:
    void fileNew();
    void fileOpen();
    void fileSave();
    void fileSaveAs();
    void fileExit();

private:
    void createActions();
    void createStatusBar();
    void createPanels();

    QSplitter* spliter1;
    QSplitter* spliter2;
    QSplitter* spliter3;

    QTabWidget* panels_left;
    QTabWidget* panels_right;
    QTabWidget* bottom_left;
    QTabWidget* bottom_right;
    CentralWidget* panel_central;

    TrivialDirExplorer* dir_explorer;
    TrivialDocumentsView* doc_view;
};


class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    CentralWidget() : central(NULL) {
    
    }

    void setCentral(QWidget* wid) {
        if (central) {
            central->setParent(NULL);
            delete central;
            central = NULL;
        }

        if (wid) {
            wid->setParent(this);
            central = wid;
        }
    }

    void resizeEvent(QResizeEvent* event) override {
        if (central) {
            central->resize(size());
        }
    }

private:
    QWidget* central;
};

#endif // _TRIVIAL_MAINWINDOW_H
