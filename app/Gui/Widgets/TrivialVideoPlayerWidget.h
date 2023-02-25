#ifndef TRIVIAL_VIDEO_PLAYER_H
#define TRIVIAL_VIDEO_PLAYER_H

#include <QLabel>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>


class TrivialVideoPlayerWidget : public QWidget {
    Q_OBJECT

public:
    TrivialVideoPlayerWidget(QWidget* parent = NULL);

    void openFile(const QString &fileName);

public slots:
    void play();
    void pause();
    void setVolume(int vol);


protected slots:
    void errorOccurred(QMediaPlayer::Error error, const QString &errorString);
    void playPause();
    void toogleFullscren();
    void positionChanged(qint64 position);
    void volumeSliderChange(int vol);
    void videoFrameChanged();

private:

    int controlsHeight;

    QGridLayout* gridLayout_3;

    QWidget* videoWidget;

    QAudioOutput* audioOutput;
    QMediaPlayer *mPlayer;
    QVideoWidget *mVideoWidget;
    QPushButton *mPlayButton;
    QSlider *mVolumeSlider;
    QLabel* m_MediaPositionLabel;
    QPushButton *mFullscreenButton;

    //QLabel* mMsgLabel;
    QRect m_originalGeometry;
    int windowFlags;

    QVBoxLayout *videoLayout;
    QHBoxLayout *controlsLayout;

    void createWidget();


    void showMesage(const QString& txt);
    void setControlsEnabled(bool enabled);
    void setIcon(const QString& icon_name);
    void setFullscreenIcon(const QString& icon_name);

    void addChildWidgetAndFillInGrid(QWidget* parent, QWidget* child) {
        gridLayout_3 = new QGridLayout(parent);
        gridLayout_3->setObjectName(child->objectName() + "_fill_grid");
        child->setParent(parent);
        gridLayout_3->addWidget(child, 0, 0, 1, 1);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
    }

};

#endif
