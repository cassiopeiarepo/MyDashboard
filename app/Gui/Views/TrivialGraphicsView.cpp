#include "TrivialGraphicsView.h"

#include "TrivialTextItem.h"
#include "TrivialTextEditor.h"
#include "QWheelEvent"
#include <QtMath>
#include <QScrollbar>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QCoreApplication>
#include <QObject>

#include "TrivialGuiItems.h"
#include "TrivialGraphicsItem.h"
#include "coreqt/Common/Tml.h"

#include "app/Utils/Workspace.h"

TrivialGraphicsView::TrivialGraphicsView() : QGraphicsView(), zoom(250.0f), focusItem(NULL), mouseItem(NULL), watcher(NULL),
    middleMousePressed(false), focusWidget(NULL) {


    scene = new QGraphicsScene();
    this->setScene(scene);

    scene->setSceneRect(QRectF(0, 0, 10000, 10000));

    //this->setMouseTracking(true);
    this->setInteractive(false);

    this->setDragMode(QGraphicsView::ScrollHandDrag);

    //setRenderHint(QGraphicsView::DontAdjustForAntialiasing, true);

}

void TrivialGraphicsView::init() {
//QGraphicsRectItem* rect = scene.addRect(QRectF(0, 0, 100, 100));


    QGraphicsProxyWidget* proxy1 = new QGraphicsProxyWidget();
    QLineEdit* line_edit = new QLineEdit();
    proxy1->setWidget(line_edit);
    scene->addItem(proxy1);
    proxy1->setFlag(QGraphicsItem::ItemIsFocusable);
    proxy1->setFocus();

    proxy1->setPos(1000, 1000);
    line_edit->resize(100, 40);


    QGraphicsProxyWidget* proxy = new QGraphicsProxyWidget();
    ComplexMouseTestWidget* complex_widget = new ComplexMouseTestWidget();

    proxy->setWidget(complex_widget);
    scene->addItem(proxy);
    proxy->setFlag(QGraphicsItem::ItemIsFocusable);
    proxy->setFocus();

    proxy->setPos(500, 500);
    complex_widget->resize(300, 300);

    /*
    QGraphicsProxyWidget* proxy2 = new QGraphicsProxyWidget();
    TrivialSceneWidget* scene_widget = new TrivialSceneWidget(NULL, 300);

    scene_widget->setObject(Workspace::get()->getRoot());
    scene_widget->select(Workspace::get()->getRoot());

    proxy2->setWidget(scene_widget);
    scene->addItem(proxy2);
    proxy2->setFlag(QGraphicsItem::ItemIsFocusable);
    proxy2->setFocus();

    proxy2->setPos(0, 0);
    //scene_widget->resize(300, 300);
    */



    this->setInteractive(true);
    //this->setOptimizationFlag(QGraphicsView::sce)

/*
TrivialTextItem* text_item = new TrivialTextItem();



TrivialTextItem* text_item2 = new TrivialTextItem();
text_item2->setPos(1000.0, 1000.0);

scene->addItem(text_item);
scene->addItem(text_item2);


*/

/*
TrivialWindowItem* win = new TrivialWindowItem();
scene->addItem(win);
win->setPos(400, 400);
win->setItemSize(QPointF(400, 200));
*/

/*
TrivialTextItem* triv_text_item = new TrivialTextItem();
scene->addItem(triv_text_item);
triv_text_item->setPos(400, 400);
triv_text_item->setItemSize(QPointF(100, 68));
QString text("To jest fajny tekst\r\nTo jest druga linia\r\nTo Jest trzecia linia");
triv_text_item->setText(text);
*/
//watchFile(QString("d:/scene.xml"));

/*
TrivComplexMouseTestWidget* complex = new TrivComplexMouseTestWidget();
scene->addItem(complex->getProxy());
complex->getProxy()->setPos(500, 500);
complex->resize(100, 100);
*/
/*
TrivMouseTestWidget* triv_mouse_test = new TrivMouseTestWidget();
scene->addItem(triv_mouse_test->getProxy());
triv_mouse_test->getProxy()->setPos(500, 500);
triv_mouse_test->resize(100, 100);
//triv_mouse_test->getProxy()->setRotation(45.0);
//triv_mouse_test->getProxy()->setScale(2.0);

TrivProxyCheckBox* triv_checkbox = new TrivProxyCheckBox("Press me");
scene->addItem(triv_checkbox->getProxy());
triv_checkbox->getProxy()->setPos(600, 600);
//triv_mouse_test->resize(100, 100);
*/

/*
TrivProxySceneWidget* scene_wid = new TrivProxySceneWidget();
scene_wid->setObject(Workspace::get()->getRoot());
scene_wid->select(Workspace::get()->getRoot());
scene_wid->getProxy()->setPos(500, 500);
scene_wid->resize(300, 300);
scene->addItem(scene_wid->getProxy());
*/

/*
TestGraphicsItem* test_gi = new TestGraphicsItem();
scene->addItem(test_gi);
test_gi->setPos(800, 800);
*/

/*
TrivProxyTextEdit* triv_textedit = new TrivProxyTextEdit();
scene->addItem(triv_textedit->getProxy());
triv_textedit->getProxy()->setPos(1000, 1000);

TrivProxyLineEdit* triv_lineedit = new TrivProxyLineEdit();
scene->addItem(triv_lineedit->getProxy());
triv_lineedit->getProxy()->setPos(1400, 1400);

TrivProxyLineEdit* triv_lineedit2 = new TrivProxyLineEdit();
scene->addItem(triv_lineedit2->getProxy());
triv_lineedit2->getProxy()->setPos(1600, 1600);
*/

}

/*
void TrivialGraphicsView::mouseDoubleClickEvent(QMouseEvent* event) {
    QGraphicsItem* item = itemAt(event->pos());

    if (item != NULL) {
        QGraphicsProxyWidget* proxy = dynamic_cast<QGraphicsProxyWidget*>(item);
        TrivialGraphicsItem* gitem = dynamic_cast<TrivialGraphicsItem*>(item);

        if (proxy != NULL) {

            TrivProxyWidget* triv_proxy = dynamic_cast<TrivProxyWidget*>(proxy->widget());

            QPointF point1 = triv_proxy->mapPoint(event->pos());
            QPoint point2(point1.x(), point1.y());

            findWidgetAndPos(proxy->widget(), point2);

            if (find_widget_wid) {
                QMouseEvent* event2 = new QMouseEvent(QEvent::MouseButtonDblClick, find_widget_pos,
                    event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());

                QApplication::sendEvent(find_widget_wid, event2);
            }
        }
        else if (gitem != NULL) {
            QPointF scene_point = mapToScene(event->pos());
            scene_point = gitem->sceneTransform().inverted().map(scene_point);
            //event->setLocalPos(scene_point);
            gitem->mouseDoubleClickEvent(event);

        }
    }
}
*/

void TrivialGraphicsView::mouseMoveEvent(QMouseEvent* event) 
{
    QGraphicsView::mouseMoveEvent(event);

    /*
    if (middleMousePressed) {

        QPointF p2 = mapToScene(event->x(), event->y());
        QPointF diff = p2 - p1;
        int w = width();
        int h = height();

        if (this->horizontalScrollBar()->isVisible())
            h -= horizontalScrollBar()->height();

        if (this->verticalScrollBar()->isVisible())
            w -= verticalScrollBar()->width();

        center1 = mapToScene( w / 2, h / 2);

        QPointF center2 = center1 - diff;
        centerOn(center2);
        event->accept();
        return;
    }
    */

    /*
    QGraphicsItem* item = NULL;
        
    if (IsNullButtonPressed(event)) {
        item = itemAt(event->pos());
        mouseItem = item;
    }
    else {
        item = mouseItem;
    }    

    if (item != NULL) {
        //
        TrivialGraphicsItem* gitem = dynamic_cast<TrivialGraphicsItem*>(item);
        QGraphicsProxyWidget* proxy = dynamic_cast<QGraphicsProxyWidget*>(item);

        if (proxy != NULL) {

            TrivProxyWidget* triv_proxy = dynamic_cast<TrivProxyWidget*>(proxy->widget());

            QPointF point1 = triv_proxy->mapPoint(event->pos());
            QPoint point2(point1.x(), point1.y());

            findWidgetAndPos(proxy->widget(), point2);

            if (find_widget_wid) {
                QMouseEvent* event2 = new QMouseEvent(QEvent::MouseMove, find_widget_pos,
                    event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());

                qDebug() << " mouse_move 3";

                QApplication::sendEvent(find_widget_wid, event2);
            }
        }
        else if (gitem != NULL){
            QPointF scene_point = mapToScene(event->pos());
            scene_point = gitem->sceneTransform().inverted().map(scene_point);
            //event->setLocalPos(scene_point);
            gitem->mouseMoveEvent(event);
            
        }
    }
    */
   
}

void TrivialGraphicsView::mousePressEvent(QMouseEvent* event) 
{
    QGraphicsView::mousePressEvent(event);

    /*
    if (event->button() == Qt::MiddleButton)
    {
        middleMousePressed = true;
        p1 = mapToScene(event->x(), event->y());

        event->accept();
        return;
    }
    */

    /*
    QGraphicsItem* item = NULL;

    if (isOnlyOneButtonPressed(event)) {
        item = itemAt(event->pos());
        mouseItem = item;
    }
    else {
        item = mouseItem;
    }

    if (item != NULL) {
        QGraphicsProxyWidget* proxy = dynamic_cast<QGraphicsProxyWidget*>(item);
        TrivialGraphicsItem* gitem = dynamic_cast<TrivialGraphicsItem*>(item);

        

        if (proxy != NULL) {

            TrivProxyWidget* triv_proxy = dynamic_cast<TrivProxyWidget*>(proxy->widget());

            QPointF point1 = triv_proxy->mapPoint(event->pos());
            QPoint point2(point1.x(), point1.y());

            findWidgetAndPos(proxy->widget(), point2);

            if (find_widget_wid) {
                QMouseEvent* event2 = new QMouseEvent(QEvent::MouseButtonPress, find_widget_pos,
                    event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());

                qDebug() << " mouse press " << find_widget_pos << "widget: " << find_widget_wid;

                find_widget_wid->setFocus();
                focusWidget = find_widget_wid;

                QApplication::sendEvent(find_widget_wid, event2);
            }
        }
        else if (gitem != NULL) {
            QPointF scene_point = mapToScene(event->pos());
            scene_point = gitem->sceneTransform().inverted().map(scene_point);
            //event->setLocalPos(scene_point);
            gitem->mousePressEvent(event);

        }

    }
    */

}

void TrivialGraphicsView::mouseReleaseEvent(QMouseEvent* event) 
{
    QGraphicsView::mouseReleaseEvent(event);
/*
    if (event->button() == Qt::MiddleButton)
    {
        middleMousePressed = false;
        event->accept();
        return;
    }
*/
    /*
    QGraphicsItem* item = mouseItem;

    if (item != NULL) {
        QGraphicsProxyWidget* proxy = dynamic_cast<QGraphicsProxyWidget*>(item);
        TrivialGraphicsItem* gitem = dynamic_cast<TrivialGraphicsItem*>(item);

        if (proxy != NULL) {
            TrivProxyWidget* triv_proxy = dynamic_cast<TrivProxyWidget*>(proxy->widget());

            QPointF point1 = triv_proxy->mapPoint(event->pos());
            QPoint point2(point1.x(), point1.y());

            findWidgetAndPos(proxy->widget(), point2);

            if (find_widget_wid) {
                QMouseEvent* event2 = new QMouseEvent(QEvent::MouseButtonRelease, find_widget_pos,
                    event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());

                QApplication::sendEvent(find_widget_wid, event2);
            }
        }
        else if (gitem != NULL) {
            QPointF scene_point = mapToScene(event->pos());
            scene_point = gitem->sceneTransform().inverted().map(scene_point);
            //event->setLocalPos(scene_point);
            gitem->mouseReleaseEvent(event);

        }

    }
    */
}


void TrivialGraphicsView::wheelEvent(QWheelEvent* e)
{
    if (e->modifiers() & Qt::ControlModifier) {
        if (e->angleDelta().y() > 0)
            setZoom(getZoom() + 1.0f);
        else
            setZoom(getZoom() - 1.0f);
        e->accept();
    }
    else {
        QGraphicsView::wheelEvent(e);
    }
}
/*
void TrivialGraphicsView::keyPressEvent(QKeyEvent* event) {
    if (find_widget_wid) {
        QApplication::sendEvent(find_widget_wid, event);
    } else if (focusItem) {
        QGraphicsProxyWidget* proxy = dynamic_cast<QGraphicsProxyWidget*>(focusItem);
        TrivialGraphicsItem* gitem = dynamic_cast<TrivialGraphicsItem*>(focusItem);

        if (proxy) {
            QApplication::sendEvent(proxy->widget(), event);
        }
        else if (gitem) {
            gitem->keyPressEvent(event);
        }
    }
}

void TrivialGraphicsView::keyReleaseEvent(QKeyEvent* event) {
    if (find_widget_wid) {
        QApplication::sendEvent(find_widget_wid, event);
    } else if (focusItem) {
        QGraphicsProxyWidget* proxy = dynamic_cast<QGraphicsProxyWidget*>(focusItem);
        TrivialGraphicsItem* gitem = dynamic_cast<TrivialGraphicsItem*>(focusItem);

        if (proxy) {
            QApplication::sendEvent(proxy->widget(), event);
        }
        else if (gitem) {
            gitem->keyPressEvent(event);
        }
    }
}
*/

void TrivialGraphicsView::findWidgetAndPos(QWidget* parent, QPoint pos) {
    QWidget* child = parent->childAt(pos);

    if (child != NULL) {
        findWidgetAndPos(child, child->mapFromParent(pos));
    } else {
        find_widget_wid = parent;
        find_widget_pos = pos;
    }

}

void TrivialGraphicsView::update_transform() {
    //qreal scale = qPow(qreal(2), (zoom - 250) / qreal(50));
    qreal scale = qPow(2.0f, zoom - 250);

    QTransform matrix;
    matrix.scale(scale, scale);
    setTransform(matrix);
}


bool TrivialGraphicsView::isOnlyOneButtonPressed(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) 
    {
        if (event->buttons() & Qt::MiddleButton || event->buttons() & Qt::RightButton)
            return false;
    }

    if (event->button() == Qt::MiddleButton)
    {
        if (event->buttons() & Qt::LeftButton || event->buttons() & Qt::RightButton)
            return false;
    }

    if (event->button() == Qt::RightButton)
    {
        if (event->buttons() & Qt::LeftButton || event->buttons() & Qt::MiddleButton)
            return false;
    }

    return true;
}

bool TrivialGraphicsView::IsNullButtonPressed(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton || event->buttons() & Qt::RightButton || event->buttons() & Qt::MiddleButton)
        return false;
    return true;
}

void TrivialGraphicsView::clear() {
    scene->clear();
}


void TrivialGraphicsView::loadFile(const QString& abs_path)
{
    clear();

    TmlNode* tml = new TmlNode();
    if (!tml->loadFile(abs_path)) {
        qDebug() << "load file failed - " << abs_path;
        return;
    }

    if (tml->getName() == "dashboard") {
        for (int i = 0; i < tml->getNumChilds(); i++) {
            TmlNode* child = tml->getChild(i);

            if (child->getName() == "text") {
                TrivialTextItem* triv_text_item = new TrivialTextItem();
                triv_text_item->loadTml(child);
                scene->addItem(triv_text_item);
            } else if (child->getName() == "image") {
                TrivialImageItem* triv_image_item = new TrivialImageItem();
                triv_image_item->loadTml(child);
                scene->addItem(triv_image_item);
            } else if (child->getName() == "goto") {
                TrivialGotoItem* triv_goto_item = new TrivialGotoItem();
                triv_goto_item->loadTml(child);
                scene->addItem(triv_goto_item);
            }
        }
    }
    else {
        qDebug() << "expected dashboard node";
    }

    qDebug() << "load file success - " << abs_path;
}

void TrivialGraphicsView::onWatchFileChanged(const QString& path) {
    loadFile(path);
}

void TrivialGraphicsView::watchFile(const QString& abs_path) {
    loadFile(abs_path);

    if (watcher)
        delete watcher;

    watcher = new QFileSystemWatcher();
    watcher->addPath(abs_path);
    QObject::connect(watcher, &QFileSystemWatcher::fileChanged, this, &TrivialGraphicsView::onWatchFileChanged);

}
