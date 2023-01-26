#ifndef TRIVIAL_QOBJECT_PROPERTY_WINDOW_H
#define TRIVIAL_QOBJECT_PROPERTY_WINDOW_H

#include <QDialog>
#include "app/Gui/Widgets/TrivialQObjectPropertyWidget.h"
#include "app/Utils/Gui.h"

class TrivialQObjectPropertyWindow : public QDialog {

    Q_OBJECT
public:
    TrivialQObjectPropertyWindow(QWidget* parent, QObject* obj) : QDialog(parent) {
        setWindowTitle("Property");
        setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        setAttribute(Qt::WA_DeleteOnClose);

        int w = Gui::get()->getWidth();
        int h = Gui::get()->getHeight();
        QPoint win_pos = Gui::get()->getGloabalPos();
        QRect geom(win_pos.x(), win_pos.y(), w, h);
        this->setGeometry(geom);

        prop_widget = new TrivialQObjectPropertyWidget(this);
        prop_widget->SetObject(obj);

        Gui::get()->addChildWidgetAndFillInGrid(this, prop_widget);
    }

    ~TrivialQObjectPropertyWindow() {

    }

private:
    TrivialQObjectPropertyWidget* prop_widget;
};


#endif
