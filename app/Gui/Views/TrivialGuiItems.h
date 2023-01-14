#ifndef TRIVIAL_GUI_ITEMS_H
#define TRIVIAL_GUI_ITEMS_H

#include <QCheckBox>
#include <QPainter>
#include <QMouseEvent>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QLineEdit>
#include "TrivialTextEditor.h"
#include "TrivialGraphicsView.h"


class TestWidget : public QWidget {
	Q_OBJECT
public:
	TestWidget(QString _name) : QWidget() , name(_name) {
		this->setMouseTracking(true);
	}

protected:
	void mouseMoveEvent(QMouseEvent* event) override {
		qDebug() << name << " mouseMoveEvent";
	}

	void mousePressEvent(QMouseEvent* event) override { 
		qDebug() << name << " mousePressEvent";
	}

	void mouseReleaseEvent(QMouseEvent* event) override { 
		qDebug() << name << " mouseReleaseEvent";
	}

	void leaveEvent(QEvent* event) override {
		qDebug() << name << " leaveEvent";
	}

	void enterEvent(QEnterEvent* event) override {
		qDebug() << name << " enterEvent";
	}

	void paintEvent(QPaintEvent* event) override {
		QPainter painter(this);
		//QRect r(mouseMovePos.x() - 1, mouseMovePos.y() - 1, 3, 3);
		//painter.drawEllipse(r);
		painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
	}

	QString name;
};


class MouseTestWidget : public QWidget {
	Q_OBJECT
public:
	MouseTestWidget() : QWidget() {
		this->setMouseTracking(true);
	}

protected:
	void mouseMoveEvent(QMouseEvent* event) override {
		mouseMovePos = event->pos();
		update();
	}

	void mousePressEvent(QMouseEvent* event) override { }

	void mouseReleaseEvent(QMouseEvent* event) override { }

	void paintEvent(QPaintEvent* event) override {
		QPainter painter(this);
		QRect r(mouseMovePos.x() - 1, mouseMovePos.y() - 1, 3, 3);
		painter.drawEllipse(r);
		painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
	}

	QPointF mouseMovePos;
};

class TrivProxyWidget {

public:
	TrivProxyWidget() {
		proxy = new QGraphicsProxyWidget();
	}

	QGraphicsProxyWidget* getProxy() { return proxy; }

	QPointF mapPoint(QPoint in) {
		QList<QGraphicsView*> views = proxy->scene()->views();
		QPointF scene_point = views[0]->mapToScene(in);
		scene_point = proxy->sceneTransform().inverted().map(scene_point);
		return scene_point;
	}

	void setFocusItem() {
		QList<QGraphicsView*> views = proxy->scene()->views();
		TrivialGraphicsView* view = qobject_cast<TrivialGraphicsView*> (views[0]);
		if (view)
			view->setFocusItem(proxy);

		if (proxy->widget())
			proxy->widget()->setFocus();
	}


protected:
	QGraphicsProxyWidget* proxy;

};

/*
class TrivMouseTestWidget : public MouseTestWidget, public TrivProxyWidget {
	Q_OBJECT
public:
	TrivMouseTestWidget() : MouseTestWidget(), TrivProxyWidget(){
		proxy->setWidget(this);
	}

protected:
	void mouseMoveEvent(QMouseEvent* event) override {
		event->setLocalPos(mapPoint(event->pos()));
		MouseTestWidget::mouseMoveEvent(event);
	}

	void mousePressEvent(QMouseEvent* event) override {
		event->setLocalPos(mapPoint(event->pos()));
		MouseTestWidget::mousePressEvent(event);
	}

	void mouseReleaseEvent(QMouseEvent* event) override {
		event->setLocalPos(mapPoint(event->pos()));
		MouseTestWidget::mouseReleaseEvent(event);
	}
};

class TrivProxyCheckBox : public QCheckBox, public TrivProxyWidget {
	Q_OBJECT
public:
	TrivProxyCheckBox(QString str) : QCheckBox(str), TrivProxyWidget(){
		proxy->setWidget(this);
	}

protected:
	void mouseMoveEvent(QMouseEvent* event) override {
		event->setLocalPos(mapPoint(event->pos()));
		QCheckBox::mouseMoveEvent(event);
	}

	void mousePressEvent(QMouseEvent* event) override {
		event->setLocalPos(mapPoint(event->pos()));
		QCheckBox::mousePressEvent(event);
	}

	void mouseReleaseEvent(QMouseEvent* event) override {
		event->setLocalPos(mapPoint(event->pos()));
		QCheckBox::mouseReleaseEvent(event);
	}

};

class TrivProxyTextEdit : public TrivialTextEditor, public TrivProxyWidget {
	Q_OBJECT
public:
	TrivProxyTextEdit() : TrivialTextEditor(), TrivProxyWidget() {
		proxy->setWidget(this);
	}

protected:
	void mouseMoveEvent(QMouseEvent* event) override {
		event->setLocalPos(mapPoint(event->pos()));
		TrivialTextEditor::mouseMoveEvent(event);
	}

	void mousePressEvent(QMouseEvent* event) override {
		setFocusItem();
		event->setLocalPos(mapPoint(event->pos()));
		TrivialTextEditor::mousePressEvent(event);
	}

	void mouseReleaseEvent(QMouseEvent* event) override {
		event->setLocalPos(mapPoint(event->pos()));
		TrivialTextEditor::mouseReleaseEvent(event);
	}

};

class TrivProxyLineEdit : public QLineEdit, public TrivProxyWidget {
	Q_OBJECT
public:
	TrivProxyLineEdit() : QLineEdit(), TrivProxyWidget() {
		proxy->setWidget(this);
	}

protected:
	void mouseMoveEvent(QMouseEvent* event) override {
		event->setLocalPos(mapPoint(event->pos()));
		QLineEdit::mouseMoveEvent(event);
	}

	void mousePressEvent(QMouseEvent* event) override {
		setFocusItem();
		event->setLocalPos(mapPoint(event->pos()));
		QLineEdit::mousePressEvent(event);
	}

	void mouseReleaseEvent(QMouseEvent* event) override {
		event->setLocalPos(mapPoint(event->pos()));
		QLineEdit::mouseReleaseEvent(event);
	}

};
*/

#endif // TRIVIAL_GUI_ITEMS_H