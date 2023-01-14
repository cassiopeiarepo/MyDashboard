#include "app/Gui/Views/TrivialSceneView.h"
#include "app/Utils/SceneUtils.h"
#include "app/Utils/Gui.h"

TrivialSceneItemWidget::TrivialSceneItemWidget(QWidget* parent, NodeBase* obj) : QWidget(parent) , object(obj) {
	createWidget();
}

TrivialSceneItemWidget::~TrivialSceneItemWidget() {
	delete name_label;
}

void TrivialSceneItemWidget::update() {
	
}

void TrivialSceneItemWidget::resizeEvent(QResizeEvent* event) {
	updateSize();
	QWidget::resizeEvent(event);
}

void TrivialSceneItemWidget::createWidget() {
	name_label = new QLabel(this);
	name_label->setText(object->objectName());
	name_label->move(0,0);
	qDebug() << "obj_name " << object->objectName();

	updateSize();
}

void TrivialSceneItemWidget::updateSize() {
	name_label->resize(this->size());
}

TrivialSceneWidget::TrivialSceneWidget(QWidget* parent, int _clientWidth) : QWidget(parent), selected(NULL), clientWidth(_clientWidth) {
	createWidget();
}

void TrivialSceneWidget::createWidget() {
	verticalLayout = new QVBoxLayout(this);

	rebuildChilds();
}

void TrivialSceneWidget::rebuildChilds() {
	if (!selected) return;

	for (int i = 0; i < items.size(); i++) {
		delete items[i];
	}

	items.clear();

	QObjectList childs_obj = selected->children();

	int offset = 20;
	int pos_x = 0;

	for (int i = 0; i < childs_obj.size(); i++) {
		NodeBase* child_node = qobject_cast<NodeBase*>(childs_obj[i]);
		TrivialSceneItemWidget* child = new TrivialSceneItemWidget(this, child_node);
		items.append(child);
		child->move(0, pos_x);
		pos_x += offset;
	}
}


TrivialSceneComplexView::TrivialSceneComplexView(QWidget* parent) : QWidget(parent) {
	createWidget();
}

void TrivialSceneComplexView::createWidget() {
	scene_view_complex.setupUi(this);
	connect(scene_view_complex.toolButton_2, &QToolButton::pressed, this, &TrivialSceneComplexView::onUp);

	scene_widget = new TrivialSceneWidget(this, 400);
	Gui::get()->addChildWidgetAndFillInGrid(scene_view_complex.widget, scene_widget);

}

void TrivialSceneComplexView::select(QObject* obj) {
	//qDebug() << "TrivialSceneComplexView::slect " << obj;
	NodeBase* _obj = qobject_cast<NodeBase*>(obj);

	scene_widget->setObject(_obj);
	QString path = SceneUtils::getNodePath(_obj);
	scene_view_complex.label->setText(path);
}

void TrivialSceneComplexView::onUp() {
	NodeBase* _obj = scene_widget->getObject();
	NodeBase* _parent = qobject_cast<NodeBase*>(_obj->parent());

	if (_parent)
		select(_parent);
}