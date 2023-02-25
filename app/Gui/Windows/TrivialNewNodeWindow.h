#ifndef TRIVIAL_NEW_NODE_WINDOW_H
#define TRIVIAL_NEW_NODE_WINDOW_H

#include <QDialog>

#include "app/Gui/Widgets/TrivialCommonNodesWidget.h"
#include "app/Utils/Gui.h"

class TrivialNewNodeWindow : public QDialog {
    Q_OBJECT
public:
    TrivialNewNodeWindow(QWidget* parent) : QDialog(parent) {
        setWindowTitle("New node");

        //setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        setWindowFlags(Qt::Popup);
        setAttribute(Qt::WA_DeleteOnClose);

        common_nodes = new TrivialCommonNodesWidget(this);
        Gui::get()->addChildWidgetAndFillInGrid(this, common_nodes);

    }


private:
    TrivialCommonNodesWidget* common_nodes;

};

#endif
