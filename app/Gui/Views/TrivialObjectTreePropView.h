#ifndef TRIVIAL_OBJECT_TREE_PROP_VIEW_H
#define TRIVIAL_OBJECT_TREE_PROP_VIEW_H

#include <QWidget>
#include <QSplitter>

class TrivialSceneTreeWidget;
class TrivialQObjectPropertyWidget;

class TrivialObjectTreePropView : public QWidget {
    Q_OBJECT
public:
    TrivialObjectTreePropView(QWidget* parent);

    void setRoot(QObject* root);

signals:
    void selected(QObject* obj);

public slots:
    void onTreeSelected(QObject* obj);

private:
    void createWidget();

    QSplitter* splitter;
    TrivialSceneTreeWidget *scene_tree_widget;
    TrivialQObjectPropertyWidget *prop_widget;
};


#endif
