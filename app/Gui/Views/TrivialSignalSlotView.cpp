#include "app/Gui/Views/TrivialSignalSlotView.h"
#include <QScrollBar>

TrivialSignalSlotView* TSSBaseItem::getView() {
    QGraphicsScene *scene1 = scene();
   return dynamic_cast<TrivialSignalSlotView* >(scene1->views().first());
}



void TSSConnectionItemGraph::updateSize() {

    TrivialSignalSlotView* view = getView();

    TSSObjectItemGraph* signalObject = view->getObjectItemGraph(this->conn->getSender());
    TSSObjectItemGraph* slotObject = view->getObjectItemGraph(this->conn->getReceiver());

    fromPoint = signalObject->getSignalPoint(this->conn->getSignalSignature());
    toPoint = slotObject->getSlotPoint(this->conn->getSlotSignature());
    centralPoint = (fromPoint + toPoint)/2;

    QRectF rect;

    qreal left = qMin(fromPoint.x(), toPoint.x());
    qreal top = qMin(fromPoint.y(), toPoint.y());
    qreal right = qMax(fromPoint.x(), toPoint.x());
    qreal bottom = qMax(fromPoint.y(), toPoint.y());

    rect.setCoords(left, top, right, bottom);

    setPos(left, top);

    width = rect.width();
    height = rect.height();

    //qDebug() << "w " << width << " h " << height;

    fromPoint = mapFromScene(fromPoint);
    toPoint = mapFromScene(toPoint);
    centralPoint = mapFromScene(centralPoint);

}

void TSSConnectionItemGraph::paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget)  {

    /*
    QTransform transform = painter->worldTransform();

        // Pobierz skalowanie
        qreal scaleX = sqrt(transform.m11() * transform.m11() + transform.m21() * transform.m21());
        qreal scaleY = sqrt(transform.m22() * transform.m22() + transform.m12() * transform.m12());

        // Wybierz najmniejsze skalowanie, aby zachować proporcje
        qreal scale = qMin(scaleX, scaleY);

        // Uaktualnij szerokość pióra, uwzględniając skalowanie
        QPen pen;
        pen.setColor(Qt::black);
        pen.setStyle(Qt::SolidLine);
        pen.setWidthF(1 / scale); // Odwróć skalowanie, aby uzyskać stałą grubość linii

        // Ustaw pióro dla malowania
        painter->setPen(pen);
    */

    QPen pen;
    if (getView()->getSelected() == this) {
        pen.setColor(Qt::blue);
    } else {
        pen.setColor(Qt::black);
    }

    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(2); // Odwróć skalowanie, aby uzyskać stałą grubość linii

    // Ustaw pióro dla malowania
    painter->setPen(pen);

    painter->drawLine(fromPoint.x(), fromPoint.y(), centralPoint.x(), fromPoint.y());
    painter->drawLine(centralPoint.x(), fromPoint.y(), centralPoint.x(), toPoint.y());
    painter->drawLine(centralPoint.x(), toPoint.y(), toPoint.x(), toPoint.y());
}

void TSSConnectionItemGraph::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    getView()->setSelected(this);
}

void TSSObjectItemGraph::mousePressEvent(QGraphicsSceneMouseEvent *event)  {
    m_dragStartPosition = event->pos();
    getView()->setSelected(this);
    setCursor(Qt::ClosedHandCursor);
}

void TSSObjectItemGraph::mouseMoveEvent(QGraphicsSceneMouseEvent *event)  {
    QPointF delta = event->pos() - m_dragStartPosition;
    setPos(pos() + delta);
    this->getView()->updateAllConnections(this);

    /*
    // Przesunięcie widoku, gdy kursor zbliża się do krawędzi
        QGraphicsView *view = scene()->views().first();
        QRectF visibleRect = view->mapToScene(view->viewport()->rect()).boundingRect();
        QPointF cursorPos = event->scenePos();
        qreal margin = 50; // Margines od krawędzi, w którym widok zacznie się przesuwać

        if (cursorPos.x() < visibleRect.left() + margin) {
            view->horizontalScrollBar()->setValue(view->horizontalScrollBar()->value() - 10);
        } else if (cursorPos.x() > visibleRect.right() - margin) {
            view->horizontalScrollBar()->setValue(view->horizontalScrollBar()->value() + 10);
        }

        if (cursorPos.y() < visibleRect.top() + margin) {
            view->verticalScrollBar()->setValue(view->verticalScrollBar()->value() - 10);
        } else if (cursorPos.y() > visibleRect.bottom() - margin) {
            view->verticalScrollBar()->setValue(view->verticalScrollBar()->value() + 10);
        }
    */

}

void TSSObjectItemGraph::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)  {
    setCursor(Qt::ArrowCursor);
}

void TSSObjectItemGraph::paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) {

    if (getView()->getSelected() == this) {
        QColor strokeColor = QColor(Qt::blue);
        QPen pen(strokeColor);

        painter->setPen(pen);
    }

    QString obj_name = obj_item->getObject()->objectName();
    if (obj_name == "")
        obj_name = "Unknown";

    int obj_name_w = getTextWidth(obj_name);
    int obj_name_h = getLineHeight();

    QPoint obj_name_point(width/2 - obj_name_w/2, margins + obj_name_h);

    painter->drawText(obj_name_point, obj_name);

    int slot_y_offset = margins + obj_name_h / 2 - slotSize / 2;

    painter->drawRect(QRectF(margins, slot_y_offset, slotSize, slotSize));
    painter->drawRect(QRectF(width - margins - slotSize, slot_y_offset, slotSize, slotSize));

    for (int i = 0; i < obj_slots.size(); i++)  {
        slot_y_offset = margins + obj_name_h * (1.5 + i) - slotSize / 2;

        painter->drawRect(QRectF(margins, slot_y_offset, slotSize, slotSize));
        painter->drawText(QPointF(2*margins + slotSize, margins + obj_name_h * (2 + i)), obj_slots[i]);
    }

    for (int i = 0; i < obj_signals.size(); i++)  {
        slot_y_offset = margins + obj_name_h * (1.5 + i) - slotSize / 2;
        painter->drawRect(QRectF(width - margins - slotSize, slot_y_offset, slotSize, slotSize));
        int slot_name_w = getTextWidth(obj_signals[i]);
        painter->drawText(QPointF(width - margins - slotSize - slot_name_w, margins + obj_name_h * (2 + i)), obj_signals[i]);
    }

    painter->drawRect(QRectF(0, 0, width, height));
}
