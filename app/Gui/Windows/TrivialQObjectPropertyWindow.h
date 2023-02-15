#ifndef TRIVIAL_QOBJECT_PROPERTY_WINDOW_H
#define TRIVIAL_QOBJECT_PROPERTY_WINDOW_H

#include <QDialog>
#include "app/Gui/Widgets/TrivialQObjectPropertyWidget.h"
#include "app/Gui/Windows/TrivialMiniWindow.h"
#include "app/Utils/Gui.h"

class TrivialQObjectPropertyWindow : public TrivialMiniWindow {

    Q_OBJECT
public:
    TrivialQObjectPropertyWindow(QWidget* parent, QObject* obj) : TrivialMiniWindow(parent) {

        setCaption("Property");
        prop_widget = new TrivialQObjectPropertyWidget(this);
        prop_widget->SetObject(obj);

        Gui::get()->addChildWidgetAndFillInGrid(getClient(), prop_widget);
    }

    ~TrivialQObjectPropertyWindow() {

    }

private:
    TrivialQObjectPropertyWidget* prop_widget;
};


#endif
