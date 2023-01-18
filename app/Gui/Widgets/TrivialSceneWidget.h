#ifndef TRIVIAL_SCENE_WIDGET_H
#define TRIVIAL_SCENE_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QToolButton>
#include <QCoreApplication>
#include <QTextEdit>
#include <QScrollArea>
#include <QTimer>
#include <QMenu>

#include "app/Utils/Workspace.h"

class TrivialSceneWidget;

class ObjectNameLabel : public QLabel {
    Q_OBJECT
 public:
    ObjectNameLabel(QWidget* parent) : QLabel(parent) { }

    void mousePressEvent(QMouseEvent *event) override {
        QTimer::singleShot(1, this, &ObjectNameLabel::onTimer);
        QLabel::mousePressEvent(event);
    }

signals:
    void onMousePress();

public slots:
    void onTimer() {
        emit onMousePress();
    }
};


class TrivialSceneItemWidget : public QWidget {
    Q_OBJECT

public:
    TrivialSceneItemWidget(TrivialSceneWidget* _scene_widget, NodeBase* obj);
    ~TrivialSceneItemWidget();
    NodeBase* getObject() { return object; }

    void update();

    void resizeEvent(QResizeEvent* event) override;

    void setShowHeaders(bool show_headers);

public slots:
    void onObjectNamePressed();

    void aboutTiHideOptionsMenu();
    void recreateOptionsMenu();

private:
    NodeBase* object;
    TrivialSceneWidget* scene_widget;

    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButton_3;
    ObjectNameLabel *label_2;
    QTextEdit *textEdit;

    void createWidget();
    void updateSize();

    QMenu* optionsMenu;
    void createOptionsMenu();

};


class TrivialSceneWidget : public QWidget {
    Q_OBJECT

public:
    TrivialSceneWidget(QWidget* parent, int _clientWidth);

    NodeBase* getObject() { return selected; }
    void setObject(NodeBase* sel) {
        selected = sel; rebuildChilds();
    }

    bool getShowHeaders() { return show_headers; }
    void setShowHeaders(bool _show_headers);

    int getClientWidth() { return clientWidth; }

    void resizeEvent(QResizeEvent* event) override {
        //rebuildChilds();
    }

    void select(NodeBase* object);

signals:
    void goChild(NodeBase* child);


private:
    NodeBase* selected;
    bool show_headers;

    QList<TrivialSceneItemWidget*> items;

    QGridLayout *gridLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;

    QWidget* expand_widget;

    int clientWidth;

    void createWidget();

    void rebuildChilds();

};


#endif
