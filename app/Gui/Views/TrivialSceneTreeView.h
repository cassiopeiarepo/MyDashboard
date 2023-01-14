#ifndef TRIVIAL_SCENE_TREE_VIEW_H
#define TRIVIAL_SCENE_TREE_VIEW_H

#include <QWidget>

class TrivialSceneTreeWidget;

class TrivialSceneTreeView : public QWidget {
    Q_OBJECT
public:
    TrivialSceneTreeView(QWidget* parent);

    void setRoot(QObject* root);

signals:
    void selected(QObject* obj);

public slots:
    void onSelected(QObject* obj);

private:
    void createWidget();

    TrivialSceneTreeWidget* scene_tree_widget;
};


#endif
