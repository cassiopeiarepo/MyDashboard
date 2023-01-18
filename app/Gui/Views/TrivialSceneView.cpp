#include "app/Gui/Views/TrivialSceneView.h"
#include "app/Utils/SceneUtils.h"
#include "app/Utils/Gui.h"
#include "qmenu.h"

TrivialSceneComplexView::TrivialSceneComplexView(QWidget* parent) : QWidget(parent), optionsMenu(NULL) {
	createWidget();
}

void TrivialSceneComplexView::createWidget() {
	scene_view_complex.setupUi(this);
	connect(scene_view_complex.toolButton_2, &QToolButton::pressed, this, &TrivialSceneComplexView::onUp);

    //connect(scene_view_complex.toolButton, &QToolButton::pressed, this, &TrivialSceneComplexView::showOptionsMenu);

	scene_widget = new TrivialSceneWidget(this, 400);
	Gui::get()->addChildWidgetAndFillInGrid(scene_view_complex.widget, scene_widget);

    connect(scene_widget, &TrivialSceneWidget::goChild, this, &TrivialSceneComplexView::onGoChild);

    createOptionsMenu();
}

void TrivialSceneComplexView::createOptionsMenu() {
    if (optionsMenu)
        delete optionsMenu;

    optionsMenu = new QMenu(this);
    QAction* action = optionsMenu->addAction("Show Headers");
    action->setCheckable(true);
    action->setChecked(scene_widget->getShowHeaders());
    QObject::connect(action, &QAction::toggled, this, &TrivialSceneComplexView::optionsShowHeadersTriggered);
    //m_contextMenu->addAction("Option 2");
    //connect(m_contextMenu, &QMenu::aboutToHide, m_contextMenu, &QMenu::deleteLater);

    QSize size = optionsMenu->sizeHint();
    //size.setWidth(100);
    optionsMenu->setFixedSize(150, size.height());

    scene_view_complex.toolButton->setMenu(optionsMenu);
    scene_view_complex.toolButton->setPopupMode(QToolButton::InstantPopup);
    connect(optionsMenu, &QMenu::aboutToHide, this, &TrivialSceneComplexView::aboutTiHideOptionsMenu);
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

    if (_parent) {
		select(_parent);
    }
}

void TrivialSceneComplexView::onGoChild(NodeBase* child) {
    select(child);
}

void TrivialSceneComplexView::aboutTiHideOptionsMenu() {
    QTimer::singleShot(1, this, &TrivialSceneComplexView::recreateOptionsMenu);
}

void TrivialSceneComplexView::recreateOptionsMenu() {
    createOptionsMenu();
}

void TrivialSceneComplexView::optionsShowHeadersTriggered(bool checked) {
    scene_widget->setShowHeaders(checked);
}
