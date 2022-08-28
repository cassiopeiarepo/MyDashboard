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

TrivialGraphicsView::TrivialGraphicsView() : QGraphicsView(), zoom(250.0f), focusItem(NULL), mouseItem(NULL), watcher(NULL), middleMousePressed(false){


    scene = new QGraphicsScene();
    this->setScene(scene);

	//QGraphicsRectItem* rect = scene.addRect(QRectF(0, 0, 100, 100));

	TrivialTextItem* text_item = new TrivialTextItem();



	TrivialTextItem* text_item2 = new TrivialTextItem();
	text_item2->setPos(1000.0, 1000.0);

	scene->addItem(text_item);
	scene->addItem(text_item2);

    scene->setSceneRect(QRectF(0, 0, 100000, 100000));

    /*
    TrivialWindowItem* win = new TrivialWindowItem();
    scene->addItem(win);
    win->setPos(400, 400);
    win->setItemSize(QPointF(400, 200));
    */

    TrivialTextItem* triv_text_item = new TrivialTextItem();
    scene->addItem(triv_text_item);
    triv_text_item->setPos(400, 400);
    triv_text_item->setItemSize(QPointF(100, 68));
    triv_text_item->setText(QString("To jest fajny tekst\r\nTo jest druga linia\r\nTo Jest trzecia linia"));

    watchFile(QString("d:/scene.xml"));

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

    TestGraphicsItem* test_gi = new TestGraphicsItem();
    scene->addItem(test_gi);
    test_gi->setPos(800, 800);

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
    this->setMouseTracking(true);
    this->setInteractive(false);
}

void TrivialGraphicsView::mouseDoubleClickEvent(QMouseEvent* event) {
    QGraphicsItem* item = itemAt(event->pos());

    if (item != NULL) {
        QGraphicsProxyWidget* proxy = dynamic_cast<QGraphicsProxyWidget*>(item);
        TrivialGraphicsItem* gitem = dynamic_cast<TrivialGraphicsItem*>(item);

        if (proxy != NULL) {
            QMouseEvent* event2 = new QMouseEvent(QEvent::MouseButtonDblClick, event->pos(),
                event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
            QApplication::sendEvent(proxy->widget(), event);
        }
        else if (gitem != NULL) {
            QPointF scene_point = mapToScene(event->pos());
            scene_point = gitem->sceneTransform().inverted().map(scene_point);
            event->setLocalPos(scene_point);
            gitem->mouseDoubleClickEvent(event);

        }
    }
}


void TrivialGraphicsView::mouseMoveEvent(QMouseEvent* event) 
{
    
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
    
    QGraphicsItem* item = NULL;
        
    if (IsNullButtonPressed(event)) {
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
            QMouseEvent* event2 = new QMouseEvent(QEvent::MouseMove, event->pos(),
                event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
            QApplication::sendEvent(proxy->widget(), event);
        }
        else if (gitem != NULL){
            QPointF scene_point = mapToScene(event->pos());
            scene_point = gitem->sceneTransform().inverted().map(scene_point);
            event->setLocalPos(scene_point);
            gitem->mouseMoveEvent(event);
            
        }
    }
   
}

void TrivialGraphicsView::mousePressEvent(QMouseEvent* event) 
{

    if (event->button() == Qt::MiddleButton)
    {
        middleMousePressed = true;
        p1 = mapToScene(event->x(), event->y());

        event->accept();
        return;
    }

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
            QMouseEvent* event2 = new QMouseEvent(QEvent::MouseButtonPress, event->pos(),
                event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
            QApplication::sendEvent(proxy->widget(), event);
            
        }
        else if (gitem != NULL) {
            QPointF scene_point = mapToScene(event->pos());
            scene_point = gitem->sceneTransform().inverted().map(scene_point);
            event->setLocalPos(scene_point);
            gitem->mousePressEvent(event);

        }

    }

}

void TrivialGraphicsView::mouseReleaseEvent(QMouseEvent* event) 
{

    if (event->button() == Qt::MiddleButton)
    {
        middleMousePressed = false;
        event->accept();
        return;
    }

    QGraphicsItem* item = mouseItem;

    if (item != NULL) {
        QGraphicsProxyWidget* proxy = dynamic_cast<QGraphicsProxyWidget*>(item);
        TrivialGraphicsItem* gitem = dynamic_cast<TrivialGraphicsItem*>(item);

        if (proxy != NULL) {
            QMouseEvent* event2 = new QMouseEvent(QEvent::MouseButtonRelease, event->pos(),
                event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
            QApplication::sendEvent(proxy->widget(), event);
        }
        else if (gitem != NULL) {
            QPointF scene_point = mapToScene(event->pos());
            scene_point = gitem->sceneTransform().inverted().map(scene_point);
            event->setLocalPos(scene_point);
            gitem->mouseReleaseEvent(event);

        }

    }
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

void TrivialGraphicsView::keyPressEvent(QKeyEvent* event) {
    if (focusItem) {
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
    if (focusItem) {
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