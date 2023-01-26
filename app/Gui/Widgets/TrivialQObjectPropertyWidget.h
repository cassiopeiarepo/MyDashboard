#ifndef TRIVIAL_QOBJECTPROPERTYWIDGET_H
#define TRIVIAL_QOBJECTPROPERTYWIDGET_H

#include <QTableView>
#include <QTimer>
#include <QStyledItemDelegate>

class TrivialQObjectPropertyWidget;

class TrivialQObjectPropertyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TrivialQObjectPropertyModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void setObject(QObject* _obj);

    void setTimerUpdate(bool enabled);

public slots:
    void onTimerInterval();

private:
    QObject* obj;
    QTimer timer;

    int getNumProperties(QObject* obj) const;
    QString getPropertyName(int index) const;
    QVariant getPropertyValue(int index) const;
    QString getPropertyValueString(int index) const;
    bool setPropertyValue(int index, const QVariant& val);
};

class TrivialPropertyDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    TrivialPropertyDelegate(TrivialQObjectPropertyWidget* _prop_widget);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

private:
    TrivialQObjectPropertyWidget* prop_widget;
};

class TrivialQObjectPropertyWidget : public QTableView
{
    Q_OBJECT
public:
    TrivialQObjectPropertyWidget(QWidget *parent = nullptr);
    ~TrivialQObjectPropertyWidget();

    void setTimerUpdate(bool enabled);

protected:
    void resizeEvent(QResizeEvent *event);

signals:

public slots:
    void SetObject(QObject* item);

private:
    QObject* obj;
    TrivialQObjectPropertyModel* model;
    TrivialPropertyDelegate* delegate;

};

#endif // TRIVIAL_QOBJECTPROPERTYWIDGET_H
