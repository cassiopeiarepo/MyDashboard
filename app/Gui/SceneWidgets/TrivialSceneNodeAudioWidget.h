#ifndef TRIVIAL_SCENE_NODE_AUDIO_WIDGET_H
#define TRIVIAL_SCENE_NODE_AUDIO_WIDGET_H

#include "app/Gui/SceneWidgets/ITrivialSceneWidget.h"
#include "app/Nodes/Media/NodeAudio.h"
#include "app/Gui/Widgets/TrivialAudioPlayerWidget.h"

class TrivialSceneNodeAudioWidget : public TrivialAudioPlayerWidget, public ITrivialSceneWidget {
    Q_OBJECT

public:
    TrivialSceneNodeAudioWidget(QWidget* parent = NULL) : TrivialAudioPlayerWidget(parent) {


    }

    void setObject(NodeBase* obj) override {
        object = obj;
        audio_node = qobject_cast<NodeAudio*>(obj);
        if (audio_node) {

           openFile(audio_node->getPath());

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
        updateSize();
    }

private:
    NodeBase* object;
    NodeAudio* audio_node;
    TrivialSceneItemWidget* scene_item_widget;

    void updateSize() {
        QSize current_size = size();
        QSize new_size = QSize(current_size.width(), 42);

        resize(new_size);

        if (scene_item_widget) {
            scene_item_widget->updateSize(new_size);
        }

    }

};

#endif
