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

    void updateSize(QSize client_widget_size);

    void setShowHeaders(bool show_headers);

    TrivialSceneWidget* getSceneWidget() { return scene_widget; }

public slots:
    void onObjectNamePressed();

    void aboutTiHideOptionsMenu();
    void recreateOptionsMenu();

    void onOptionNewNode();
    void onOptionCut();
    void onOptionCopy();
    void onOptionPaste();
    void onOptionProperties();

private:
    NodeBase* object;
    bool show_headers;
    TrivialSceneWidget* scene_widget;

    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButton_3;
    ObjectNameLabel *label_2;
    QTextEdit *textEdit;

    void createWidget();

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

public slots:
    void aboutTiHideAddMenu();
    void recreateAddMenu();

private:
    NodeBase* selected;
    bool show_headers;

    QList<TrivialSceneItemWidget*> items;

    QGridLayout *gridLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;

    QToolButton *addToolButton;
    QWidget* expand_widget;

    int clientWidth;

    QMenu* addMenu;
    void createAddMenu();

    void createWidget();

    void rebuildChilds();

};


#endif
