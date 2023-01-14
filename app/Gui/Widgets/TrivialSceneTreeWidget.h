#ifndef TRIVIAL_SCENE_TREE_WIDGET_H
#define TRIVIAL_SCENE_TREE_WIDGET_H


#include <QTreeView>
#include <QMenu>
#include <QDialog>
#include <QToolButton>
#include <QResizeEvent>

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
    }

    void resizeEvent(QResizeEvent* event) override {
        child->resize(event->size().width(), 800);
    }


public slots:
    void onReleased();
    
private:
    QWidget* child;
    QToolButton* button1, *button2;

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

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    TrivialSceneTreeModel* model;
    //QMenu* m_contextMenu;

    QPoint m_pressPos;
    bool m_longPress;
};


#endif
