#ifndef TRIVIAL_BOOLPROPERTYWIDGET_H
#define TRIVIAL_BOOLPROPERTYWIDGET_H

#include <QCheckBox>
#include "app/Gui/PropertyWidgets/ITrivialPropertyWidget.h"

class TrivialBoolPropertyWidget : public QCheckBox, public ITrivialPropertyWidget {
  Q_OBJECT
public:
    TrivialBoolPropertyWidget(QWidget* parent = NULL) : QCheckBox(parent) {

    }

    void setPropValue(const QVariant val) override {
        setChecked(val.toBool());
    }

    QVariant getPropValue() override {
        return QVariant(this->isChecked());
    }

};

#endif
