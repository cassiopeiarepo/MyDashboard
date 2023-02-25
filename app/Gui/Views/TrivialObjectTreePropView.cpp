#include "app/Gui/Views/TrivialObjectTreePropView.h"
#include "app/Gui/Widgets/TrivialSceneTreeWidget.h"
#include "app/Gui/Widgets/TrivialQObjectPropertyWidget.h"
#include "app/Utils/Gui.h"

#include <QDebug>

TrivialObjectTreePropView::TrivialObjectTreePropView(QWidget* parent) : QWidget(parent) {
    createWidget();
}

void TrivialObjectTreePropView::createWidget() {

    splitter = new QSplitter(Qt::Vertical, this);

    scene_tree_widget = new TrivialSceneTreeWidget(this);

    QObject::connect(scene_tree_widget, &TrivialSceneTreeWidget::selected, this, &TrivialObjectTreePropView::onTreeSelected);

    prop_widget = new TrivialQObjectPropertyWidget(this);

    splitter->addWidget(scene_tree_widget);
    splitter->addWidget(prop_widget);

    Gui::get()->addChildWidgetAndFillInGrid(this, splitter);

}


void TrivialObjectTreePropView::setRoot(QObject* root) {
    scene_tree_widget->setRoot(root);
}

void TrivialObjectTreePropView::onTreeSelected(QObject* obj) {
    prop_widget->SetObject(obj);
    emit selected(obj);
}

