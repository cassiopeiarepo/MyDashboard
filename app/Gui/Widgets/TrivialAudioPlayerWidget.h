#ifndef TRIVIAL_AUDIO_PLAYER_H
#define TRIVIAL_AUDIO_PLAYER_H

#include <QLabel>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>

class TrivialAudioPlayerWidget : public QWidget {
    Q_OBJECT

public:
    TrivialAudioPlayerWidget(QWidget* parent = NULL);

    void openFile(const QString &fileName);

public slots:
    void play();
    void pause();
    void setVolume(int vol);

protected slots:
    void errorOccurred(QMediaPlayer::Error error, const QString &errorString);
    void playPause();
    void positionChanged(qint64 position);
    void volumeSliderChange(int vol);

private:

    int controlsHeight;

    QWidget* videoWidget;

    QAudioOutput* audioOutput;
    QMediaPlayer *mPlayer;
    QPushButton *mPlayButton;
    QSlider *mVolumeSlider;
    QLabel* m_MediaPositionLabel;

    //QLabel* mMsgLabel;

    QVBoxLayout *videoLayout;
    QHBoxLayout *controlsLayout;

    void createWidget();


    void showMesage(const QString& txt);
    void setControlsEnabled(bool enabled);
    void setIcon(const QString& icon_name);
};

#endif


