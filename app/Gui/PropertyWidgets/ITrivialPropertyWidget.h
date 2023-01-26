#ifndef ITRIVIAL_PROPERTYWIDGET_H
#define ITRIVIAL_PROPERTYWIDGET_H

#include <QVariant>

class ITrivialPropertyWidget {

public:
    virtual void setPropValue(const QVariant val) = 0;
    virtual QVariant getPropValue() = 0;

};

#endif
