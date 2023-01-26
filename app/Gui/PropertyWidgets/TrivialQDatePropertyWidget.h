#ifndef TRIVIAL_QDATEPROPERTYWIDGET_H
#define TRIVIAL_QDATEPROPERTYWIDGET_H

#include <QDateEdit>
#include "app/Gui/PropertyWidgets/ITrivialPropertyWidget.h"

class TrivialQDatePropertyWidget : public QDateEdit, public ITrivialPropertyWidget {
  Q_OBJECT
public:
    TrivialQDatePropertyWidget(QWidget* parent = NULL) : QDateEdit(parent) {

    }

    void setPropValue(const QVariant val) override {
        setDate(val.toDate());
    }

    QVariant getPropValue() override {
        return QVariant(date());
    }

};

#endif
