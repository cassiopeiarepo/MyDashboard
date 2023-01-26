#include "app/Gui/Widgets/TrivialQObjectPropertyWidget.h"
#include "qmetaobject.h"
#include <QHeaderView>

#include "app/Gui/PropertyWidgets/TrivialIntPropertyWidget.h"
#include "app/Gui/PropertyWidgets/TrivialStringPropertyWidget.h"
#include "app/Gui/PropertyWidgets/TrivialBoolPropertyWidget.h"
#include "app/Gui/PropertyWidgets/TrivialFloatPropertyWidget.h"
#include "app/Gui/PropertyWidgets/TrivialDoublePropertyWidget.h"
#include "app/Gui/PropertyWidgets/TrivialQDateTimePropertyWidget.h"
#include "app/Gui/PropertyWidgets/TrivialQDatePropertyWidget.h"
#include "app/Gui/PropertyWidgets/TrivialQTimePropertyWidget.h"

TrivialQObjectPropertyModel::TrivialQObjectPropertyModel(QObject *parent)
    : QAbstractTableModel(parent), obj(NULL)
{
    timer.setInterval(1000);
    timer.start();
    QObject::connect(&timer, &QTimer::timeout, this, &TrivialQObjectPropertyModel::onTimerInterval);
}

void TrivialQObjectPropertyModel::setTimerUpdate(bool enabled) {
    if (enabled)
        timer.start();
    else
        timer.stop();
}

void TrivialQObjectPropertyModel::onTimerInterval() {
    if (obj) {
        this->beginResetModel();
        this->endResetModel();
    }
}

void TrivialQObjectPropertyModel::setObject(QObject* _obj) {
    this->beginResetModel();
    obj = _obj;
    this->endResetModel();
}

int TrivialQObjectPropertyModel::rowCount(const QModelIndex & /*parent*/) const
{
    int rows = 0;
    if (obj) {
        rows = getNumProperties(obj);
    }
   return rows;
}

int TrivialQObjectPropertyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 2;
}

QVariant TrivialQObjectPropertyModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.column() == 0) {
            return getPropertyName(index.row());
        } else if (index.column() == 1) {
            return getPropertyValueString(index.row());
        }

    } else if (role == Qt::EditRole) {
        if (index.column() == 1) {
            return getPropertyValue(index.row());
        }

    }

    return QVariant();
}

bool TrivialQObjectPropertyModel::setData(const QModelIndex &index, const QVariant &value, int role) {

    if (role == Qt::EditRole) {
        if (index.column() == 1) {
            return setPropertyValue(index.row(), value);;
        }

    }
    return false;
}

Qt::ItemFlags TrivialQObjectPropertyModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (index.column() == 0)
        flags = flags & ~Qt::ItemIsSelectable;
    else if (index.column() == 1)
        flags |= Qt::ItemIsEditable;
    return flags;
}

int TrivialQObjectPropertyModel::getNumProperties(QObject* obj) const {
    auto mo = obj->metaObject();

    int result = 0;
    do {
      result += (mo->propertyCount() - mo->propertyOffset());
    } while ((mo = mo->superClass()));

    return result;
}

QString TrivialQObjectPropertyModel::getPropertyName(int index) const {
    auto mo = obj->metaObject();

    int size = 0;
    do {

      size = mo->propertyCount() - mo->propertyOffset();

      if (index < size) {
          int prop_index = mo->propertyOffset() + index;
          return QString(mo->property(prop_index).name());
      }

      index -= size;

    } while ((mo = mo->superClass()));

    return QString("");
}

QVariant TrivialQObjectPropertyModel::getPropertyValue(int index) const {
    auto mo = obj->metaObject();

    int size = 0;
    do {

      size = mo->propertyCount() - mo->propertyOffset();

      if (index < size) {
          int prop_index = mo->propertyOffset() + index;
          QVariant val = obj->property(mo->property(prop_index).name());
          return val;
      }

      index -= size;

    } while ((mo = mo->superClass()));

    return QVariant();
}

QString TrivialQObjectPropertyModel::getPropertyValueString(int index) const {
    auto mo = obj->metaObject();

    int size = 0;
    do {

      size = mo->propertyCount() - mo->propertyOffset();

      if (index < size) {
          int prop_index = mo->propertyOffset() + index;
          QVariant val = obj->property(mo->property(prop_index).name());
          QMetaType stringType = QMetaType::fromType<QString>();
          if (val.canConvert(stringType)) {
              val.convert(stringType);
              return val.toString();
          } else {
              QString result;
              result = "! " + QString(val.typeName()) + " !";
              return result;
          }
          return QString("");
      }

      index -= size;

    } while ((mo = mo->superClass()));

    return QString("");
}

bool TrivialQObjectPropertyModel::setPropertyValue(int index, const QVariant& val) {
    auto mo = obj->metaObject();

    int size = 0;
    do {

      size = mo->propertyCount() - mo->propertyOffset();

      if (index < size) {
          int prop_index = mo->propertyOffset() + index;
          obj->setProperty(mo->property(prop_index).name(), val);
          return true;
      }
      index -= size;
    } while ((mo = mo->superClass()));

    return false;
}

TrivialPropertyDelegate::TrivialPropertyDelegate(TrivialQObjectPropertyWidget* _prop_widget)
    : QStyledItemDelegate(_prop_widget), prop_widget(_prop_widget)
{

}

QWidget *TrivialPropertyDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem & option,
                                       const QModelIndex & index) const
{

    QVariant data = index.data(Qt::EditRole);

    QWidget* result = NULL;

    qDebug() << " create_editor for type " << data.typeId();

    switch (data.typeId()) {
    case QMetaType::QString : {
            result = new TrivialStringPropertyWidget(parent);
            break;
        }

    case QMetaType::Int: {
            result = new TrivialIntPropertyWidget(parent);
            break;
        }
    case QMetaType::Bool: {
            result = new TrivialBoolPropertyWidget(parent);
            break;
        }
    case QMetaType::Float: {
            result = new TrivialFloatPropertyWidget(parent);
            break;
        }
    case QMetaType::Double: {
            result = new TrivialDoublePropertyWidget(parent);
            break;
        }
    case QMetaType::QDateTime: {
            result = new TrivialQDateTimePropertyWidget(parent);
            break;
        }
    case QMetaType::QTime: {
            result = new TrivialQTimePropertyWidget(parent);
            break;
        }
    case QMetaType::QDate: {
            result = new TrivialQDatePropertyWidget(parent);
            break;
        }

    default : {
        qDebug() << " can not create property editor for type " << data.metaType().name();
    }
    }

    if (result != NULL)
        prop_widget->setTimerUpdate(false);

    return result;
}

void TrivialPropertyDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{

    QVariant val = index.model()->data(index, Qt::EditRole);

    ITrivialPropertyWidget* iprop_widget = dynamic_cast<ITrivialPropertyWidget*>(editor);
    iprop_widget->setPropValue(val);

}

void TrivialPropertyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    ITrivialPropertyWidget* iprop_widget = dynamic_cast<ITrivialPropertyWidget*>(editor);
    QVariant val = iprop_widget->getPropValue();
    model->setData(index, val, Qt::EditRole);
    prop_widget->setTimerUpdate(true);
}

void TrivialPropertyDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}


TrivialQObjectPropertyWidget::TrivialQObjectPropertyWidget(QWidget *parent)
    : QTableView{parent}
{
    model = new TrivialQObjectPropertyModel();
    this->setModel(model);

    delegate = new TrivialPropertyDelegate(this);
    setItemDelegate(delegate);

    setEditTriggers(QAbstractItemView::CurrentChanged);

    verticalHeader()->hide();
    horizontalHeader()->hide();
}

TrivialQObjectPropertyWidget::~TrivialQObjectPropertyWidget() {
    delete delegate; delegate = NULL;
    delete model; model = NULL;

}

void TrivialQObjectPropertyWidget::SetObject(QObject* item) {
    obj = item;

    model->setObject(obj);
    setRowHeight(0, 30);

}

void TrivialQObjectPropertyWidget::setTimerUpdate(bool enabled) {
    model->setTimerUpdate(enabled);
}

void TrivialQObjectPropertyWidget::resizeEvent(QResizeEvent *event) {
    setColumnWidth(0, 120);
    setColumnWidth(1, width() - 122);

}


