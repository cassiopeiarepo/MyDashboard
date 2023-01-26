#ifndef TRIVIAL_QDATETIMEPROPERTYWIDGET_H
#define TRIVIAL_QDATETIMEPROPERTYWIDGET_H

#include <QDateTimeEdit>
#include "app/Gui/PropertyWidgets/ITrivialPropertyWidget.h"

class TrivialQDateTimePropertyWidget : public QDateTimeEdit, public ITrivialPropertyWidget {
  Q_OBJECT
public:
    TrivialQDateTimePropertyWidget(QWidget* parent = NULL) : QDateTimeEdit(parent) {

    }

    void setPropValue(const QVariant val) override {
        setDateTime(val.toDateTime());
    }

    QVariant getPropValue() override {
        return QVariant(dateTime());
    }

};

#endif
