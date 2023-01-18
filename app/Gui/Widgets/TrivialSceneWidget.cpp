#include "app/Gui/Widgets/TrivialSceneWidget.h"
#include "app/Gui/Views/TrivialSceneView.h"

TrivialSceneItemWidget::TrivialSceneItemWidget(TrivialSceneWidget* _sene_widget, NodeBase* obj) : QWidget(NULL) , object(obj),
    scene_widget(_sene_widget), optionsMenu(NULL)
{
    createWidget();
}

TrivialSceneItemWidget::~TrivialSceneItemWidget() {

}

void TrivialSceneItemWidget::update() {

}

void TrivialSceneItemWidget::resizeEvent(QResizeEvent* event) {
    updateSize();
    QWidget::resizeEvent(event);
}

void TrivialSceneItemWidget::createWidget() {

    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName("gridLayout");
    gridLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout_3 = new QVBoxLayout();
    verticalLayout_3->setSpacing(0);
    verticalLayout_3->setObjectName("verticalLayout_3");
    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName("horizontalLayout_2");
    toolButton_3 = new QToolButton(this);
    toolButton_3->setObjectName("toolButton_3");

    horizontalLayout_2->addWidget(toolButton_3);

    label_2 = new ObjectNameLabel(this);
    label_2->setObjectName("label_2");

    horizontalLayout_2->addWidget(label_2);


    verticalLayout_3->addLayout(horizontalLayout_2);

    textEdit = new QTextEdit(this);
    textEdit->setObjectName("textEdit");
    textEdit->setFrameShape(QFrame::NoFrame);
    textEdit->setFrameShadow(QFrame::Sunken);

    verticalLayout_3->addWidget(textEdit);


    gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

    updateSize();

    label_2->setText(object->objectName() + " : NodeText" );

    QObject::connect(label_2, &ObjectNameLabel::onMousePress, this, &TrivialSceneItemWidget::onObjectNamePressed);

    createOptionsMenu();
}


void TrivialSceneItemWidget::createOptionsMenu() {
    if (optionsMenu)
        delete optionsMenu;

    optionsMenu = new QMenu(this);
    QAction* action = optionsMenu->addAction("Edit");
    //action->setCheckable(true);
    //action->setChecked(scene_widget->getShowHeaders());
    //QObject::connect(action, &QAction::toggled, this, &TrivialSceneComplexView::optionsShowHeadersTriggered);
    //m_contextMenu->addAction("Option 2");
    //connect(m_contextMenu, &QMenu::aboutToHide, m_contextMenu, &QMenu::deleteLater);

    QSize size = optionsMenu->sizeHint();
    //size.setWidth(100);
    optionsMenu->setFixedSize(100, size.height());

    toolButton_3->setMenu(optionsMenu);
    toolButton_3->setPopupMode(QToolButton::InstantPopup);
    connect(optionsMenu, &QMenu::aboutToHide, this, &TrivialSceneItemWidget::aboutTiHideOptionsMenu);
}

void TrivialSceneItemWidget::setShowHeaders(bool show_headers) {
    label_2->setVisible(show_headers);
    toolButton_3->setVisible(show_headers);
}

void TrivialSceneItemWidget::updateSize() {

}

void TrivialSceneItemWidget::onObjectNamePressed() {
    if (scene_widget) {
        scene_widget->select(object);
    }
}

void TrivialSceneItemWidget::aboutTiHideOptionsMenu() {
    QTimer::singleShot(1, this, &TrivialSceneItemWidget::recreateOptionsMenu);
}

void TrivialSceneItemWidget::recreateOptionsMenu() {
    createOptionsMenu();
}

TrivialSceneWidget::TrivialSceneWidget(QWidget* parent, int _clientWidth) : QWidget(parent), selected(NULL), clientWidth(_clientWidth), expand_widget(NULL),
    show_headers(true)
{
    createWidget();
}

void TrivialSceneWidget::createWidget() {

    gridLayout_2 = new QGridLayout(this);
    gridLayout_2->setObjectName("gridLayout_2");
    gridLayout_2->setContentsMargins(0, 0, 0, 0);
    scrollArea = new QScrollArea(this);
    scrollArea->setObjectName("scrollArea");
    scrollArea->setWidgetResizable(true);
    scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
    scrollAreaWidgetContents->setGeometry(QRect(0, 0, 678, 739));
    gridLayout = new QGridLayout(scrollAreaWidgetContents);
    gridLayout->setObjectName("gridLayout");
    gridLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName("verticalLayout");
    verticalLayout->setSizeConstraint(QLayout::SetFixedSize);

    gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

    scrollArea->setWidget(scrollAreaWidgetContents);

    gridLayout_2->addWidget(scrollArea, 0, 0, 1, 1);

    expand_widget = new QWidget(this);
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    expand_widget->setSizePolicy(sizePolicy);

    rebuildChilds();
}

void TrivialSceneWidget::rebuildChilds() {
    if (!selected) return;

    for (int i = 0; i < items.size(); i++) {
        verticalLayout->removeWidget(items[i]);
        delete items[i];
    }

    items.clear();

    verticalLayout->removeWidget(expand_widget);

    QObjectList childs_obj = selected->children();

    for (int i = 0; i < childs_obj.size(); i++) {
        NodeBase* child_node = qobject_cast<NodeBase*>(childs_obj[i]);
        TrivialSceneItemWidget* child = new TrivialSceneItemWidget(this, child_node);
        child->setShowHeaders(show_headers);
        items.append(child);
        child->setFixedSize(300, 100);
        verticalLayout->addWidget(child);
    }

    verticalLayout->addWidget(expand_widget);

    /*
    for (int i = 0; i < items.size(); i++) {
        delete items[i];
    }

    items.clear();

    QObjectList childs_obj = selected->children();

    int margin = 20;
    int max_width = 300;

    int separ = 20;
    int pos_y = 0;

    int pos_x = margin;
    int width = this->size().width() - 2 * margin;

    if (width > max_width) {
        width = max_width;
        pos_x = (this->size().width() - max_width) / 2;
    }

    for (int i = 0; i < childs_obj.size(); i++) {
        NodeBase* child_node = qobject_cast<NodeBase*>(childs_obj[i]);
        TrivialSceneItemWidget* child = new TrivialSceneItemWidget(this, child_node);
        items.append(child);
        child->move(pos_x, pos_y);
        child->resize(width, 200);
        QSize size_hint = child->sizeHint();
        child->resize(width, size_hint.height());
        pos_y += child->size().height() + separ;
    }

    this->setVisible(false);
    this->setVisible(true);
    */

}

void TrivialSceneWidget::select(NodeBase* object) {
    emit goChild(object);
}

void TrivialSceneWidget::setShowHeaders(bool _show_headers) {
    if (show_headers == _show_headers)
        return;

    for (int i = 0; i < items.size(); i++) {
        items[i]->setShowHeaders(_show_headers);
    }

    show_headers = _show_headers;
}
