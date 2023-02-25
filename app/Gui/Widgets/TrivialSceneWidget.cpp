#include "app/Gui/Widgets/TrivialSceneWidget.h"
#include "app/Gui/Views/TrivialSceneView.h"
#include "app/Gui/Windows/TrivialQObjectPropertyWindow.h"
#include "app/Gui/SceneWidgets/ITrivialSceneWidget.h"


#include "app/Utils/TypeDef.h"

TrivialSceneItemWidget::TrivialSceneItemWidget(TrivialSceneWidget* _sene_widget, NodeBase* obj) : QWidget(NULL) , object(obj),
    scene_widget(_sene_widget), optionsMenu(NULL), show_headers(true)
{
    createWidget();
}

TrivialSceneItemWidget::~TrivialSceneItemWidget() {
    if (optionsMenu)
        delete optionsMenu;
}

void TrivialSceneItemWidget::update() {

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
    label_2->setStyleSheet("padding-left: 4px;");

    horizontalLayout_2->addWidget(label_2);


    verticalLayout_3->addLayout(horizontalLayout_2);

    QString type_name = object->metaObject()->metaType().name();

    const TypeDef* type_def = TypeSystem::get()->getType(type_name);
    if (type_def) {
        QIcon _icon;
        qDebug() << "test1 " << type_def->getIconRes();
        _icon.addFile(type_def->getIconRes()/*":/icons/ui/icons/play_arrow_FILL0_wght400_GRAD0_opsz48.png"*/, QSize(), QIcon::Normal, QIcon::Off);
        toolButton_3->setIcon(_icon);
        //toolButton_3->setIconSize(QSize(24, 24));
    }

    QWidget* central_widget = TypeSystem::get()->createWidgetForSceneView(type_name);

    if (central_widget)
    {
        central_widget->setParent(this);
        verticalLayout_3->addWidget(central_widget);

        ITrivialSceneWidget* i_scene_widget = dynamic_cast<ITrivialSceneWidget*>(central_widget);
        if (i_scene_widget) {
            i_scene_widget->setTrivialSceneItemWidget(this);
            i_scene_widget->setObject(object);
            i_scene_widget->init();
        }

    }

    gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

    QString label_text = object->objectName();

    label_text += " : " + QString(object->metaObject()->metaType().name());

    label_2->setText(label_text);

    QObject::connect(label_2, &ObjectNameLabel::onMousePress, this, &TrivialSceneItemWidget::onObjectNamePressed);

    createOptionsMenu();
}


void TrivialSceneItemWidget::createOptionsMenu() {
    if (optionsMenu)
        delete optionsMenu;

    optionsMenu = new QMenu(this);

    QAction* action = optionsMenu->addAction("New Node");
    QObject::connect(action, &QAction::triggered, this, &TrivialSceneItemWidget::onOptionNewNode);

    action = optionsMenu->addAction("Cut");
    QObject::connect(action, &QAction::triggered, this, &TrivialSceneItemWidget::onOptionCut);

    action = optionsMenu->addAction("Copy");
    QObject::connect(action, &QAction::triggered, this, &TrivialSceneItemWidget::onOptionCopy);

    action = optionsMenu->addAction("Paste");
    QObject::connect(action, &QAction::triggered, this, &TrivialSceneItemWidget::onOptionPaste);

    action = optionsMenu->addAction("Properties");
    QObject::connect(action, &QAction::triggered, this, &TrivialSceneItemWidget::onOptionProperties);

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
    if (this->show_headers != show_headers ) {
        label_2->setVisible(show_headers);
        toolButton_3->setVisible(show_headers);
        QSize _size = size();

        if (show_headers) {
            _size.setHeight(_size.height() + 20);
        } else {
            _size.setHeight(_size.height() - 20);
        }
        setFixedSize(_size);
        this->show_headers = show_headers;
    }
}

void TrivialSceneItemWidget::updateSize(QSize client_widget_size) {
    QSize size = QSize(client_widget_size.width(), client_widget_size.height());

    if (show_headers)
        size.setHeight(size.height() + 20);

    /*
    if (size.height() < 44) {
        size.setHeight(44);
    }*/

    qDebug() << "TrivialSceneItemWidget::updateSize " << size;
    setFixedSize(size);
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

void TrivialSceneItemWidget::onOptionNewNode() {

}

void TrivialSceneItemWidget::onOptionCut() {

}

void TrivialSceneItemWidget::onOptionCopy() {

}

void TrivialSceneItemWidget::onOptionPaste() {

}

void TrivialSceneItemWidget::onOptionProperties() {
    TrivialQObjectPropertyWindow* prop_window = new TrivialQObjectPropertyWindow(this, object);
    prop_window->show();
}

TrivialSceneWidget::TrivialSceneWidget(QWidget* parent, int _clientWidth) : QWidget(parent), selected(NULL), clientWidth(_clientWidth), expand_widget(NULL),
    show_headers(true), addMenu(NULL)
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
    verticalLayout->setSpacing(1);


    gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

    scrollArea->setWidget(scrollAreaWidgetContents);

    gridLayout_2->addWidget(scrollArea, 0, 0, 1, 1);

    addToolButton = new QToolButton(this);

    QIcon _icon;
    _icon.addFile(":/icons/ui/icons/add_FILL0_wght400_GRAD0_opsz48.png", QSize(), QIcon::Normal, QIcon::Off);
    addToolButton->setIcon(_icon);

    expand_widget = new QWidget(this);
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    expand_widget->setSizePolicy(sizePolicy);

    rebuildChilds();
    createAddMenu();
}

void TrivialSceneWidget::rebuildChilds() {
    if (!selected) return;

    for (int i = 0; i < items.size(); i++) {
        verticalLayout->removeWidget(items[i]);
        delete items[i];
    }

    items.clear();


    verticalLayout->removeWidget(expand_widget);
    verticalLayout->removeWidget(addToolButton);


    QObjectList childs_obj = selected->children();

    for (int i = 0; i < childs_obj.size(); i++) {
        NodeBase* child_node = qobject_cast<NodeBase*>(childs_obj[i]);
        TrivialSceneItemWidget* child = new TrivialSceneItemWidget(this, child_node);
        child->setShowHeaders(show_headers);
        items.append(child);
        verticalLayout->addWidget(child);
    }


    verticalLayout->addWidget(addToolButton);
    verticalLayout->addWidget(expand_widget);
}

void TrivialSceneWidget::createAddMenu() {
    if (addMenu)
        delete addMenu;

    addMenu = new QMenu(this);

    QAction* action = addMenu->addAction("New Node");
    //QObject::connect(action, &QAction::triggered, this, &TrivialSceneItemWidget::onOptionNewNode);

    action = addMenu->addAction("Paste");
    //QObject::connect(action, &QAction::triggered, this, &TrivialSceneItemWidget::onOptionPaste);

    QSize size = addMenu->sizeHint();
    addMenu->setFixedSize(100, size.height());


    addToolButton->setMenu(addMenu);
    addToolButton->setPopupMode(QToolButton::InstantPopup);
    connect(addMenu, &QMenu::aboutToHide, this, &TrivialSceneWidget::aboutTiHideAddMenu);
}

void TrivialSceneWidget::aboutTiHideAddMenu() {
    QTimer::singleShot(1, this, &TrivialSceneWidget::recreateAddMenu);
}

void TrivialSceneWidget::recreateAddMenu() {
    createAddMenu();
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
