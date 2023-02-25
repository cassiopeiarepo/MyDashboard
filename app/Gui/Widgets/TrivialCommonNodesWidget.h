#ifndef TRIVIAL_COMMON_NODES_WIDGET_H
#define TRIVIAL_COMMON_NODES_WIDGET_H

#include <QLabel>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>


class TrivialCommonNodesWidget : public QWidget {
Q_OBJECT
public:
    TrivialCommonNodesWidget(QWidget* parent = NULL);


private:
    QGridLayout *gridLayout;
    QLabel* label, *label2;
    QWidget* fill_widget;
    void createWidget();

    void createButton(const QString& nodeTypeName, int row, int column);
};

#endif

