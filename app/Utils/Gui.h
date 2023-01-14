#ifndef __GUI_H__
#define __GUI_H__

#include "coreqt/Utils/singleton.h"

#include <QObject>
#include <QGridLayout>
#include <QWidget>
#include <QMainWindow>

/*
    Pc: 2560x1377
    tablet: 1333x716
    tel: 360x747

    do 900 mini
    do 1600 midi
    od 1600 maxi

  */






class Gui : public QObject, public Singleton<Gui> {
    Q_OBJECT
public:
    explicit Gui() : width(0), height(0), size(GUI_MINI), prev_size(GUI_MINI) { }

    bool isDesktop() {
    #ifdef Q_OS_WINDOWS
        return true;
    #else
        return false;
    #endif
    }

    enum GuiSize {
        GUI_MINI,
        GUI_MIDI,
        GUI_MAXI
    };

    GuiSize getSize() { return size; }
    GuiSize getPrevSize() { return prev_size; }

    int getWidth() { return width; }
    int getHeight() { return height; }

    QPoint getGloabalPos() { return global_pos; }

    QMainWindow* getMainWindow() { return main_window; }

    void addChildWidgetAndFillInGrid(QWidget* parent, QWidget* child) {
        QGridLayout* gridLayout_3 = new QGridLayout(parent);
        gridLayout_3->setObjectName(child->objectName() + "_fill_grid");
        child->setParent(parent);
        gridLayout_3->addWidget(child, 0, 0, 1, 1);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
    }


private:
    int width;
    int height;
    QPoint global_pos;
    GuiSize size;
    GuiSize prev_size;
    QMainWindow* main_window;

    void updateSize(int new_width, int new_height);
    void updateGlobalPos(QPoint _gloabal_pos);
    void setMainWindow(QMainWindow* _main_window) { main_window = _main_window; }

    friend class TrivialMainWindow;
};


#endif /* __GUI_H__ */
