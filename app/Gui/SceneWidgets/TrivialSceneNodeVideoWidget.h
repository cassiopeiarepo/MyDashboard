#ifndef TRIVIAL_SCENE_NODE_VIDEO_WIDGET_H
#define TRIVIAL_SCENE_NODE_VIDEO_WIDGET_H

#include "app/Gui/SceneWidgets/ITrivialSceneWidget.h"
#include "app/Nodes/Media/NodeVideo.h"

#include <QLabel>




#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>

class TrivialSceneNodeVideoWidget : public QWidget, public ITrivialSceneWidget {
    Q_OBJECT

public:
    TrivialSceneNodeVideoWidget(QWidget* parent = NULL) : QWidget(parent) {
        mPlayer = new QMediaPlayer(this);
                mVideoWidget = new QVideoWidget(this);
                mPlayButton = new QPushButton("Play", this);
                mPauseButton = new QPushButton("Pause", this);
                mStopButton = new QPushButton("Stop", this);
                mVolumeSlider = new QSlider(Qt::Horizontal, this);

                QVBoxLayout *layout = new QVBoxLayout(this);
                layout->addWidget(mVideoWidget);

                QHBoxLayout *controlsLayout = new QHBoxLayout();
                controlsLayout->addWidget(mPlayButton);
                controlsLayout->addWidget(mPauseButton);
                controlsLayout->addWidget(mStopButton);
                controlsLayout->addWidget(mVolumeSlider);
                layout->addLayout(controlsLayout);

                mPlayer->setVideoOutput(mVideoWidget);
                //mPlayer->setVolume(50);

                connect(mPlayButton, &QPushButton::clicked, mPlayer, &QMediaPlayer::play);
                connect(mPauseButton, &QPushButton::clicked, mPlayer, &QMediaPlayer::pause);
                connect(mStopButton, &QPushButton::clicked, mPlayer, &QMediaPlayer::stop);
                //connect(mVolumeSlider, &QSlider::valueChanged, mPlayer, &QMediaPlayer::setVolume);

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

protected:


private:
    NodeBase* object;
    NodeVideo* video_node;
    TrivialSceneItemWidget* scene_item_widget;

    QMediaPlayer *mPlayer;
        QVideoWidget *mVideoWidget;
        QPushButton *mPlayButton;
        QPushButton *mPauseButton;
        QPushButton *mStopButton;
        QSlider *mVolumeSlider;

    void openFile(const QString &fileName)
        {
            //mPlayer->setMedia(QUrl::fromLocalFile(fileName));
            mPlayer->setSource(QUrl(fileName));//QUrl::fromLocalFile(fileName));
        }
};

#endif
