#ifndef TRIVIAL_SCENE_TREE_WIDGET_H
#define TRIVIAL_SCENE_TREE_WIDGET_H


#include <QTreeView>
#include <QMenu>
#include <QDialog>
#include <QToolButton>
#include <QResizeEvent>
#include <QGestureEvent>
#include <QMouseEvent>
#include <QTextEdit>

#include "app/Nodes/NodeBase.h"

void list_children(QObject* parent) ;


class NewNodeDialog : public QDialog {
    Q_OBJECT
public:
    NewNodeDialog(QWidget* parent) : QDialog(parent) {
        setWindowTitle("New node");
        
        //setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        setWindowFlags(Qt::Popup);
        setAttribute(Qt::WA_DeleteOnClose);

        child = new QWidget(this);
        child->move(0, 0);
        child->resize(100, 800);

        button1 = new QToolButton(child);
        button1->move(10, 10);
        button1->setText("button1");
        QObject::connect(button1, &QAbstractButton::released, this, &NewNodeDialog::onReleased);

        button2 = new QToolButton(child);
        button2->move(10, 600);
        button2->setText("button2");
        QObject::connect(button2, &QAbstractButton::released, this, &NewNodeDialog::onReleased);

        edit = new QTextEdit(child);
        edit->move(10, 100);
        edit->resize(100, 100);

        list_children(edit);

        child->installEventFilter(this);

        QObjectList obj_list = child->children();
        for (int i = 0; i < obj_list.size(); i++) {
            qDebug() << " installEventFilter" << obj_list[i];
            obj_list[i]->installEventFilter(this);
        }

    }

    void resizeEvent(QResizeEvent* event) override {
        child->resize(event->size().width(), 800);
    }



    /*
    bool event(QEvent *event) override {
        //qDebug() << "event " << event->type();
        if (event->type() == QEvent::MouseButtonPress) {
            qDebug() << " MouseButtonPress";

        } else  if (event->type() == QEvent::MouseMove) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

        } else if (event->type() == QEvent::Gesture) {
                //qDebug() << "gesture";

                QGestureEvent *gestureEvent = static_cast<QGestureEvent*>(event);
                if (QGesture *pan = gestureEvent->gesture(Qt::PanGesture)) {

                    qDebug() << " Pan gesture";

                    QPanGesture *panGesture = static_cast<QPanGesture*>(pan);
                    QPointF delta = panGesture->delta();
                    if (delta.y() > 0) {
                        // Przesuwanie w dół
                        child->move(this->x(), this->y() + delta.y());
                    } else {
                        // Przesuwanie w górę
                        child->move(this->x(), this->y() + delta.y());
                    }
                    return true;

                }

            }

        return QDialog::event(event);

    }
    */


public slots:
    void onReleased();
    
protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (event->type() == QEvent::MouseButtonPress) {
            qDebug() << " mousebuttonpress";
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            mouse_button_press_widget = qobject_cast<QWidget*>(obj);
            start_mouse_pos = mouse_button_press_widget->mapToGlobal(mouseEvent->pos());
            start_child_pos = child->pos();
        } else if (event->type() == QEvent::MouseMove) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (obj == mouse_button_press_widget) {
                QPoint mouse_pos = mouse_button_press_widget->mapToGlobal(mouseEvent->pos());
                QPoint diff = mouse_pos - start_mouse_pos;
                diff.setX(0);
                QPoint new_pos = start_child_pos + diff;

                if (new_pos.y() > 0) {
                    new_pos.setY(0);
                } else if (new_pos.y() < -(child->size().height() - this->size().height())){
                    new_pos.setY(-(child->size().height() - this->size().height()));
                }

                child->move(new_pos);
            }
        }

        return QWidget::eventFilter(obj, event);
    }


private:
    QPoint start_child_pos;
    QPoint start_mouse_pos;
    QWidget* mouse_button_press_widget;

    QWidget* child;
    QToolButton* button1, *button2;
    QTextEdit* edit;

};



class TrivialSceneTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TrivialSceneTreeModel(QObject* parent = nullptr);
    ~TrivialSceneTreeModel();

    QVariant data(const QModelIndex& index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
        const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    void setRoot(QObject* root) { rootItem = root; }

    void update(QObject* parent);

private:
    QObject* rootItem;
};



class TrivialSceneTreeWidget : public QTreeView
{
    Q_OBJECT
public:
    TrivialSceneTreeWidget(QWidget* parent = nullptr);
    ~TrivialSceneTreeWidget();

    void setRoot(QObject* root);

signals:
    void selected(QObject* obj);

public slots:
    void onActivated(const QModelIndex& index);

    void onNewNodeActionTriggered();
    void onCopyActionTriggered();
    void onPasteActionTriggered();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    TrivialSceneTreeModel* model;

    QList<QModelIndex> expandedIndexes;

    QPoint m_pressPos;
    bool m_longPress;

    NodeBase* getSelectedNode();

    void saveExpandedState(const QModelIndex &parentIndex);
    void saveExpandedState();
    void restoreExpandedState();
};


#endif
