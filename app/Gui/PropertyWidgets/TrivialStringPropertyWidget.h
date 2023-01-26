#ifndef TRIVIAL_STRINGPROPERTYWIDGET_H
#define TRIVIAL_STRINGPROPERTYWIDGET_H

#include <QLineEdit>
#include "app/Gui/PropertyWidgets/ITrivialPropertyWidget.h"

class TrivialStringPropertyWidget : public QLineEdit, public ITrivialPropertyWidget {
  Q_OBJECT
public:
    TrivialStringPropertyWidget(QWidget* parent = NULL) : QLineEdit(parent) {
        //setLineWrapMode(QTextEdit::NoWrap);
    }

    void setPropValue(const QVariant val) override {
        qDebug() << " setPropValue " << val.metaType().id() << "  " <<  val.metaType().name();
        setText(val.toString());
    }

    QVariant getPropValue() override {
        return QVariant(this->text());
    }

};

#endif
