#ifndef I_TRIVIAL_SCENE_WIDGET_H
#define I_TRIVIAL_SCENE_WIDGET_H

#include <QVariant>
#include "app/Nodes/NodeBase.h"

#include "app/Gui/Widgets/TrivialSceneWidget.h"

class ITrivialSceneWidget {

public:
    virtual void setObject(NodeBase* obj) = 0;
    virtual NodeBase* getObject() = 0;
    virtual void setTrivialSceneItemWidget(TrivialSceneItemWidget* scene_item_widget) = 0;

    virtual void init() = 0;

};

#endif
