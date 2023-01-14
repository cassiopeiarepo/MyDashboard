#ifndef TRIVIAL_GRAPHICS_ITEM_H
#define TRIVIAL_GRAPHICS_ITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

class TrivialGraphicsItem : public QGraphicsItem {

public:
	virtual void mouseDoubleClickEvent(QMouseEvent* event) { };
	virtual void mouseMoveEvent(QMouseEvent* event)  { }
	virtual void mousePressEvent(QMouseEvent* event)  { }
	virtual void mouseReleaseEvent(QMouseEvent* event) { }

	virtual void keyPressEvent(QKeyEvent* event) { }
	virtual void keyReleaseEvent(QKeyEvent* event) {}
};



class TestGraphicsItem : public TrivialGraphicsItem {

public:
	TestGraphicsItem() : TrivialGraphicsItem(), i(0) { }

	QRectF boundingRect() const override { return QRectF(0, 0, 100, 50); }
	QPainterPath shape() const override {
		QPainterPath path;
		path.addRect(0, 0, 100, 50);
		return path;
	}

protected:
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) override {
		painter->drawRect(QRectF(0, 0, 100, 50));
		QRect r(mouseMovePos.x() - 1, mouseMovePos.y() - 1, 3, 3);
		painter->drawEllipse(r);
	}

	void mouseMoveEvent(QMouseEvent* event) override { 
		qDebug() << "mouseMoveEvent " << i++;
		mouseMovePos = event->pos();
		update();
	}

	void mousePressEvent(QMouseEvent* event) override { 
		qDebug() << "mousePressEvent " << i++;
	}

	void mouseReleaseEvent(QMouseEvent* event) override { 
		qDebug() << "mouseReleaseEvent " << i++;
	}

	int i;
	QPointF mouseMovePos;

};

#endif // TRIVIAL_GRAPHICS_ITEM_H