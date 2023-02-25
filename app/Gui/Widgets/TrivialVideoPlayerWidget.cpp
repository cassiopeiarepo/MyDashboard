#include "app/Gui/Widgets/TrivialVideoPlayerWidget.h"
#include "app/Utils/Gui.h"
#include <QTime>
#include <QVideoFrame>

TrivialVideoPlayerWidget::TrivialVideoPlayerWidget(QWidget* parent) : QWidget(parent), controlsHeight(30) {
    createWidget();
}

void TrivialVideoPlayerWidget::createWidget() {

    videoWidget = new QWidget(this);

    addChildWidgetAndFillInGrid(this, videoWidget);

    mPlayer = new QMediaPlayer(videoWidget);
    audioOutput = new QAudioOutput(videoWidget);
    mPlayButton = new QPushButton(videoWidget);
    mVolumeSlider = new QSlider(Qt::Horizontal, videoWidget);
    m_MediaPositionLabel = new QLabel(videoWidget);
    mFullscreenButton = new QPushButton(videoWidget);

    mPlayButton->setFixedSize(controlsHeight, controlsHeight);
    mVolumeSlider->setFixedSize(60, controlsHeight);
    mFullscreenButton->setFixedSize(controlsHeight, controlsHeight);

    m_MediaPositionLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    controlsLayout = new QHBoxLayout();
    controlsLayout->addWidget(mPlayButton);
    controlsLayout->addWidget(mVolumeSlider);
    controlsLayout->addWidget(m_MediaPositionLabel);
    controlsLayout->addWidget(mFullscreenButton);

    controlsLayout->setContentsMargins(0,0,0,0);

    videoLayout = new QVBoxLayout(videoWidget);

    videoLayout->setContentsMargins(0,0,0,0);

    mVideoWidget = new QVideoWidget(videoWidget);

    mVideoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    videoLayout->addWidget(mVideoWidget);
    videoLayout->addLayout(controlsLayout);

    mPlayer->setVideoOutput(mVideoWidget);
    mPlayer->setAudioOutput(audioOutput);
    setVolume(50);

    connect(mPlayButton, &QPushButton::clicked, this, &TrivialVideoPlayerWidget::playPause);
    connect(mVolumeSlider, &QSlider::valueChanged, this, &TrivialVideoPlayerWidget::volumeSliderChange);
    connect(mFullscreenButton, &QPushButton::clicked, this, &TrivialVideoPlayerWidget::toogleFullscren);

    QObject::connect(mPlayer, &QMediaPlayer::errorOccurred, this, &TrivialVideoPlayerWidget::errorOccurred);
    QObject::connect(mPlayer, &QMediaPlayer::positionChanged, this, &TrivialVideoPlayerWidget::positionChanged);
    //QObject::connect(mPlayer, &QMediaPlayer::videoFrameChanged, this, &TrivialVideoPlayerWidget::videoFrameChanged);

    setIcon(":/icons/ui/icons/play_arrow_FILL0_wght400_GRAD0_opsz48.png");
    setFullscreenIcon(":/icons/ui/icons/fullscreen_FILL0_wght400_GRAD0_opsz48.png");
    m_MediaPositionLabel->setText("00:00:00");
}

void TrivialVideoPlayerWidget::errorOccurred(QMediaPlayer::Error error, const QString &errorString) {
   qDebug() << error << " " << errorString;
    showMesage(errorString);
}

void TrivialVideoPlayerWidget::positionChanged(qint64 position) {
    QTime currentTime(0, 0, 0, 0);
    currentTime = currentTime.addMSecs(position);
    QString timeString = currentTime.toString("hh:mm:ss");
    m_MediaPositionLabel->setText(timeString);
}

void TrivialVideoPlayerWidget::videoFrameChanged() {

    /*
    QVideoFrame frame = mPlayer->videoFrame();
    if (!frame.isValid()) {
        return;
    }
    QSize size = frame.size();
    //resolutionLabel->setText(QString("Resolution: %1x%2").arg(size.width()).arg(size.height()));
    */

}

void TrivialVideoPlayerWidget::volumeSliderChange(int vol) {
    audioOutput->setVolume(vol/100.0);
}

void TrivialVideoPlayerWidget::openFile(const QString &fileName)
{
    setControlsEnabled(true);
    setIcon(":/icons/ui/icons/play_arrow_FILL0_wght400_GRAD0_opsz48.png");
    mPlayer->setSource(QUrl(fileName));
}

void TrivialVideoPlayerWidget::playPause() {
    if (mPlayer->playbackState() == QMediaPlayer::PlayingState) {
        pause();
    } else {
        play();
    }
}

void TrivialVideoPlayerWidget::toogleFullscren() {
    qDebug() << " TrivialVideoPlayerWidget::toogleFullscren " << videoWidget->isFullScreen();
    qDebug() << "parent" << videoWidget->parent() << " parent_widget" << videoWidget->parentWidget();

    if (videoWidget->isFullScreen()) {
        videoWidget->showNormal();
        videoWidget->setWindowFlags((Qt::WindowFlags) windowFlags);
        gridLayout_3->addWidget(videoWidget, 0, 0, 1, 1);
        setGeometry(m_originalGeometry);

    } else {
        m_originalGeometry = geometry();
        windowFlags = videoWidget->windowFlags();
        videoWidget->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        videoWidget->showFullScreen();
        videoWidget->show();
        gridLayout_3->removeWidget(videoWidget);
    }
}

void TrivialVideoPlayerWidget::play() {
    mPlayer->play();
    setIcon(":/icons/ui/icons/pause_FILL0_wght400_GRAD0_opsz48.png");
}

void TrivialVideoPlayerWidget::pause() {
    mPlayer->pause();
    setIcon(":/icons/ui/icons/play_arrow_FILL0_wght400_GRAD0_opsz48.png");
}

void TrivialVideoPlayerWidget::setVolume(int vol) {
    audioOutput->setVolume(vol);
    mVolumeSlider->setValue(vol);
}

void TrivialVideoPlayerWidget::showMesage(const QString& txt) {
    m_MediaPositionLabel->setText(txt);
    setControlsEnabled(false);
}

void TrivialVideoPlayerWidget::setControlsEnabled(bool enabled) {
    mPlayButton->setEnabled(enabled);
    mVolumeSlider->setEnabled(enabled);
}

void TrivialVideoPlayerWidget::setIcon(const QString& icon_name) {
    QIcon _icon;
    _icon.addFile(icon_name, QSize(), QIcon::Normal, QIcon::Off);
    mPlayButton->setIcon(_icon);
    mPlayButton->setIconSize(QSize(24, 24));
}

void TrivialVideoPlayerWidget::setFullscreenIcon(const QString& icon_name) {
    QIcon _icon;
    _icon.addFile(icon_name, QSize(), QIcon::Normal, QIcon::Off);
    mFullscreenButton->setIcon(_icon);
    mFullscreenButton->setIconSize(QSize(24, 24));

}


