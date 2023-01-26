#ifndef TRIVIAL_INTPROPERTYWIDGET_H
#define TRIVIAL_INTPROPERTYWIDGET_H

#include <QSpinBox>
#include "app/Gui/PropertyWidgets/ITrivialPropertyWidget.h"

class TrivialIntPropertyWidget : public QSpinBox, public ITrivialPropertyWidget {
  Q_OBJECT
public:
    TrivialIntPropertyWidget(QWidget* parent = NULL) : QSpinBox(parent) {
        setMinimum(INT_MIN);
        setMaximum(INT_MAX);
    }

    void setPropValue(const QVariant val) override {
        setValue(val.toInt());
    }

    QVariant getPropValue() override {
        return QVariant(this->value());
    }

};

#endif
