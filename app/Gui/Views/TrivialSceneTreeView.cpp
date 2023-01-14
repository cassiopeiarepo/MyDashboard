#include "app/Gui/Views/TrivialSceneTreeView.h"
#include "app/Gui/Widgets/TrivialSceneTreeWidget.h"
#include "app/Utils/Gui.h"

#include <QDebug>

TrivialSceneTreeView::TrivialSceneTreeView(QWidget* parent) : QWidget(parent) {
	createWidget();
}

void TrivialSceneTreeView::createWidget() {
	scene_tree_widget = new TrivialSceneTreeWidget(this);
	QObject::connect(scene_tree_widget, &TrivialSceneTreeWidget::selected, this, &TrivialSceneTreeView::onSelected);

	Gui::get()->addChildWidgetAndFillInGrid(this, scene_tree_widget);

}


void TrivialSceneTreeView::setRoot(QObject* root) { 
	qDebug() << "TrivialSceneTreeView::setRoot " << root;
	scene_tree_widget->setRoot(root); 
}

void TrivialSceneTreeView::onSelected(QObject* obj) {
	emit selected(obj);
}
