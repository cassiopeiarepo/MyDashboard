
/*
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
*/

#include <QtWidgets>
#include <QtMultimedia>
#include <QVideoWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout(&window);

    QMediaPlayer *player = new QMediaPlayer(&window);
    QVideoWidget *videoWidget = new QVideoWidget(&window);
    player->setVideoOutput(videoWidget);

    layout->addWidget(videoWidget);

    QPushButton *playButton = new QPushButton("Play", &window);
    layout->addWidget(playButton);

    QUrl url("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    //player->setMedia(QMediaContent(url));
    player->setSource(url);

    QObject::connect(playButton, &QPushButton::clicked, player, &QMediaPlayer::play);

    window.show();

    return app.exec();
}
