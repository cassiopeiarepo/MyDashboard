#include "app/Gui/Widgets/TrivialAudioPlayerWidget.h"
#include "app/Utils/Gui.h"
#include <QTime>

TrivialAudioPlayerWidget::TrivialAudioPlayerWidget(QWidget* parent) : QWidget(parent), controlsHeight(30) {
    createWidget();
}

void TrivialAudioPlayerWidget::createWidget() {

    videoWidget = new QWidget(this);
    Gui::get()->addChildWidgetAndFillInGrid(this, videoWidget);

    mPlayer = new QMediaPlayer(videoWidget);
    audioOutput = new QAudioOutput(videoWidget);
    mPlayButton = new QPushButton(videoWidget);
    mVolumeSlider = new QSlider(Qt::Horizontal, videoWidget);
    m_MediaPositionLabel = new QLabel(videoWidget);

    mPlayButton->setFixedSize(controlsHeight, controlsHeight);
    mVolumeSlider->setFixedSize(60, controlsHeight);

    m_MediaPositionLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    controlsLayout = new QHBoxLayout();
    controlsLayout->addWidget(mPlayButton);
    controlsLayout->addWidget(mVolumeSlider);
    controlsLayout->addWidget(m_MediaPositionLabel);


    controlsLayout->setContentsMargins(0,0,0,0);

    videoLayout = new QVBoxLayout(videoWidget);

    videoLayout->setContentsMargins(0,0,0,0);

    videoLayout->addLayout(controlsLayout);

    mPlayer->setAudioOutput(audioOutput);
    setVolume(50);

    connect(mPlayButton, &QPushButton::clicked, this, &TrivialAudioPlayerWidget::playPause);
    connect(mVolumeSlider, &QSlider::valueChanged, this, &TrivialAudioPlayerWidget::volumeSliderChange);

    QObject::connect(mPlayer, &QMediaPlayer::errorOccurred, this, &TrivialAudioPlayerWidget::errorOccurred);
    QObject::connect(mPlayer, &QMediaPlayer::positionChanged, this, &TrivialAudioPlayerWidget::positionChanged);

    setIcon(":/icons/ui/icons/play_arrow_FILL0_wght400_GRAD0_opsz48.png");
    m_MediaPositionLabel->setText("00:00:00");
}

void TrivialAudioPlayerWidget::errorOccurred(QMediaPlayer::Error error, const QString &errorString) {
   qDebug() << error << " " << errorString;
    showMesage(errorString);
}

void TrivialAudioPlayerWidget::positionChanged(qint64 position) {
    QTime currentTime(0, 0, 0, 0);
    currentTime = currentTime.addMSecs(position);
    QString timeString = currentTime.toString("hh:mm:ss");
    m_MediaPositionLabel->setText(timeString);
}

void TrivialAudioPlayerWidget::volumeSliderChange(int vol) {
    audioOutput->setVolume(vol/100.0);
}

void TrivialAudioPlayerWidget::openFile(const QString &fileName)
{
    setControlsEnabled(true);
    setIcon(":/icons/ui/icons/play_arrow_FILL0_wght400_GRAD0_opsz48.png");
    mPlayer->setSource(QUrl(fileName));
}

void TrivialAudioPlayerWidget::playPause() {
    if (mPlayer->playbackState() == QMediaPlayer::PlayingState) {
        pause();
    } else {
        play();
    }
}

void TrivialAudioPlayerWidget::play() {
    mPlayer->play();
    setIcon(":/icons/ui/icons/pause_FILL0_wght400_GRAD0_opsz48.png");
}

void TrivialAudioPlayerWidget::pause() {
    mPlayer->pause();
    setIcon(":/icons/ui/icons/play_arrow_FILL0_wght400_GRAD0_opsz48.png");
}

void TrivialAudioPlayerWidget::setVolume(int vol) {
    audioOutput->setVolume(vol);
    mVolumeSlider->setValue(vol);
}

void TrivialAudioPlayerWidget::showMesage(const QString& txt) {
    m_MediaPositionLabel->setText(txt);
    setControlsEnabled(false);
}

void TrivialAudioPlayerWidget::setControlsEnabled(bool enabled) {
    mPlayButton->setEnabled(enabled);
    mVolumeSlider->setEnabled(enabled);
}

void TrivialAudioPlayerWidget::setIcon(const QString& icon_name) {
    QIcon _icon;
    _icon.addFile(icon_name, QSize(), QIcon::Normal, QIcon::Off);
    mPlayButton->setIcon(_icon);
    mPlayButton->setIconSize(QSize(24, 24));
}


