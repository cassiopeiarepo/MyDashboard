#ifndef TRIVIAL_DOUBLEPROPERTYWIDGET_H
#define TRIVIAL_DOUBLEPROPERTYWIDGET_H

#include <QDoubleSpinBox>
#include "app/Gui/PropertyWidgets/ITrivialPropertyWidget.h"

class TrivialDoublePropertyWidget : public QDoubleSpinBox, public ITrivialPropertyWidget {
  Q_OBJECT
public:
    TrivialDoublePropertyWidget(QWidget* parent = NULL) : QDoubleSpinBox(parent) {
        setMinimum(-DBL_MAX);
        setMaximum(DBL_MAX);
        setDecimals(5);
    }

    void setPropValue(const QVariant val) override {
        setValue(val.toDouble());
    }

    QVariant getPropValue() override {
        return QVariant(this->value());
    }

};

#endif
