#ifndef TRIVIAL_FLOATPROPERTYWIDGET_H
#define TRIVIAL_FLOATPROPERTYWIDGET_H

#include <QDoubleSpinBox>
#include "app/Gui/PropertyWidgets/ITrivialPropertyWidget.h"

class TrivialFloatPropertyWidget : public QDoubleSpinBox, public ITrivialPropertyWidget {
  Q_OBJECT
public:
    TrivialFloatPropertyWidget(QWidget* parent = NULL) : QDoubleSpinBox(parent) {
        setMinimum(-FLT_MAX);
        setMaximum(FLT_MAX);
        setDecimals(5);
    }

    void setPropValue(const QVariant val) override {
        setValue(val.toFloat());
    }

    QVariant getPropValue() override {
        return QVariant((float) this->value());
    }

};

#endif
