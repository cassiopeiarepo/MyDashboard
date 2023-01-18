#include "app/Gui/Widgets/TrivialSceneTreeWidget.h"
#include <QContextMenuEvent>
#include <QTimer>
#include <QApplication>

#include "app/Utils/Gui.h"


void list_children(QObject* parent) {
    QObjectList childs = parent->children();
    for (int i =0; i < childs.size(); i++) {
        qDebug() << "child " << childs[i];
    }
}

void NewNodeDialog::onReleased() {
    qDebug() << "onToogled " << QObject::sender();
}


TrivialSceneTreeModel::TrivialSceneTreeModel(QObject* parent)
    : QAbstractItemModel(parent), rootItem(NULL)
{

}

TrivialSceneTreeModel::~TrivialSceneTreeModel()
{
    delete rootItem;
}

QModelIndex TrivialSceneTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!rootItem)
        return QModelIndex();

    QObject* parentItem;

    if (!parent.isValid())
        return createIndex(row, column, rootItem);
    else
        parentItem = static_cast<QObject*>(parent.internalPointer());

    QObject* childItem = parentItem->children()[row];

    if (childItem)
        return createIndex(row, column, childItem);

    return QModelIndex();
}

QModelIndex TrivialSceneTreeModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    QObject* childItem = static_cast<QObject*>(index.internalPointer());
    QObject* parentItem = childItem->parent();

    if (!parentItem)
        return QModelIndex();

    QObject* grandparentItem = parentItem->parent();

    if (!grandparentItem)
        return createIndex(0, 0, rootItem);

    int row = grandparentItem->children().indexOf(parentItem);
    return createIndex(row, 0, parentItem);
}

int TrivialSceneTreeModel::rowCount(const QModelIndex& parent) const
{
    if (!parent.isValid())
        return 1;

    if (parent.column() > 0)
        return 0;

    QObject* parentItem = static_cast<QObject*>(parent.internalPointer());
    return parentItem->children().size();
}

int TrivialSceneTreeModel::columnCount(const QModelIndex& parent) const
{
    return 1;
}

QVariant TrivialSceneTreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    if (index.column() > 0)
        return QVariant();

    QObject* item = static_cast<QObject*>(index.internalPointer());

    return QVariant(item->objectName());
}

Qt::ItemFlags TrivialSceneTreeModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant TrivialSceneTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    //    return QVariant("Nazwa");

    return QVariant();
}

TrivialSceneTreeWidget::TrivialSceneTreeWidget(QWidget* parent)
    : QTreeView{ parent }
{
    model = new TrivialSceneTreeModel();

    this->setModel(model);

    QObject::connect(this, &QAbstractItemView::clicked,
        this, &TrivialSceneTreeWidget::onActivated);

    //this->expandToDepth(0);



//#ifdef Q_OS_ANDROID
    //this->setStyleSheet("QTreeView { font-size: 20pt; }");

    //this->setStyleSheet("QTreeView { font-size: 20pt; } ");
                        //"QTreeView::branch:open:has-children { width: 40px; height: 40px;  } "
                        //"QTreeView::branch:closed:has-children { width: 40px; height: 40px; } ");

//#endif


}

void TrivialSceneTreeWidget::setRoot(QObject* root) {
    model->setRoot(root);
    QModelIndex index = model->index(0, 0, QModelIndex());
    this->expand(index);
}

TrivialSceneTreeWidget::~TrivialSceneTreeWidget() {
    //delete m_contextMenu;
}


void TrivialSceneTreeWidget::onActivated(const QModelIndex& index) {
    QObject* item = static_cast<QObject*>(index.internalPointer());
    emit selected(item);
}

void TrivialSceneTreeWidget::onNewNodeActionTriggered() {
    NewNodeDialog* new_node_dialog = new NewNodeDialog(this);
    int w = Gui::get()->getWidth();
    int h = Gui::get()->getHeight();
    int h03 = h / 3;
    QPoint win_pos = Gui::get()->getGloabalPos();
    QRect geom(win_pos.x(), win_pos.y() + h03, w, h - h03);
    new_node_dialog->setGeometry(geom);
    new_node_dialog->show();
}

void TrivialSceneTreeWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_pressPos = event->pos();
        m_longPress = false;
        QTimer::singleShot(QApplication::doubleClickInterval(), this, [this]() {
            if (QApplication::mouseButtons() == Qt::LeftButton) {
                m_longPress = true;
            }
            });
    }
    QTreeView::mousePressEvent(event);
}

void TrivialSceneTreeWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_longPress) {
        QMenu* m_contextMenu = new QMenu(Gui::get()->getMainWindow());
        QAction* action = m_contextMenu->addAction("New");
        QObject::connect(action, &QAction::triggered, this, &TrivialSceneTreeWidget::onNewNodeActionTriggered);
        m_contextMenu->addAction("Option 2");
        connect(m_contextMenu, &QMenu::aboutToHide, m_contextMenu, &QMenu::deleteLater);

        QSize size = m_contextMenu->sizeHint();
        //size.setWidth(100);
        m_contextMenu->setFixedSize(100, size.height());

        m_contextMenu->exec(viewport()->mapToGlobal(m_pressPos));
    }
    else {
        
    }
    QTreeView::mouseReleaseEvent(event);
}
