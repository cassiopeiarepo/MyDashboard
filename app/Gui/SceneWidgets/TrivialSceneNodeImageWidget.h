#ifndef TRIVIAL_SCENE_NODE_IMAGE_WIDGET_H
#define TRIVIAL_SCENE_NODE_IMAGE_WIDGET_H

#include "app/Gui/SceneWidgets/ITrivialSceneWidget.h"
#include "app/Nodes/Media/NodeImage.h"

#include <QLabel>

class TrivialSceneNodeImageWidget : public QLabel, public ITrivialSceneWidget {
    Q_OBJECT

public:
    TrivialSceneNodeImageWidget(QWidget* parent = NULL) : QLabel(parent) {
        setScaledContents(true);
    }

    void setObject(NodeBase* obj) override {
        object = obj;
        image_node = qobject_cast<NodeImage*>(obj);
        if (image_node) {
            //this->setMarkdown(image_node->getText());
            QPixmap pixmap(image_node->getPath());
            setPixmap(pixmap);

            QSize new_size(300, 300* pixmap.height()/pixmap.width());

            //300/x = img_w/img_h
            //x = 300*img_h/img_w;

            resize(new_size);

            if (scene_item_widget) {
                scene_item_widget->updateSize(new_size);
            }
        }
        //update();
    }

    NodeBase* getObject() override { return object; }

    void setTrivialSceneItemWidget(TrivialSceneItemWidget* _scene_item_widget) override { scene_item_widget = _scene_item_widget; }

    void init() override {
        //updateSize();
    }

protected:


private:
    NodeBase* object;
    NodeImage* image_node;
    TrivialSceneItemWidget* scene_item_widget;
};

#endif
