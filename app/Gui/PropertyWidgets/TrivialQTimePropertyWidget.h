#ifndef TRIVIAL_QTIMEPROPERTYWIDGET_H
#define TRIVIAL_QTIMEPROPERTYWIDGET_H

#include <QTimeEdit>
#include "app/Gui/PropertyWidgets/ITrivialPropertyWidget.h"

class TrivialQTimePropertyWidget : public QTimeEdit, public ITrivialPropertyWidget {
  Q_OBJECT
public:
    TrivialQTimePropertyWidget(QWidget* parent = NULL) : QTimeEdit(parent) {

    }

    void setPropValue(const QVariant val) override {
        setTime(val.toTime());
    }

    QVariant getPropValue() override {
        return QVariant(time());
    }

};

#endif
