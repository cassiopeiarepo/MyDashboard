#ifndef TRIVIAL_SCENE_NODE_VIDEO_WIDGET_H
#define TRIVIAL_SCENE_NODE_VIDEO_WIDGET_H

#include "app/Gui/SceneWidgets/ITrivialSceneWidget.h"
#include "app/Nodes/Media/NodeVideo.h"
#include "app/Gui/Widgets/TrivialVideoPlayerWidget.h"

class TrivialSceneNodeVideoWidget : public TrivialVideoPlayerWidget, public ITrivialSceneWidget {
    Q_OBJECT

public:
    TrivialSceneNodeVideoWidget(QWidget* parent = NULL) : TrivialVideoPlayerWidget(parent) {


    }

    void setObject(NodeBase* obj) override {
        object = obj;
        video_node = qobject_cast<NodeVideo*>(obj);
        if (video_node) {

           openFile(video_node->getPath());

            QSize new_size(300, 200);//(300, 300* pixmap.height()/pixmap.width());

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

private:
    NodeBase* object;
    NodeVideo* video_node;
    TrivialSceneItemWidget* scene_item_widget;

};

#endif
