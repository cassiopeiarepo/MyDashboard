#ifndef TRIVIAL_GUI_ITEMS_H
#define TRIVIAL_GUI_ITEMS_H

#include <QCheckBox>
#include <QPainter>
#include <QMouseEvent>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QLineEdit>
#include <QApplication>

#include "TrivialTextEditor.h"
#include "TrivialGraphicsView.h"

#include "app/Gui/Widgets/TrivialSceneWidget.h"

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
    MouseTestWidget(QWidget* parent = NULL) : QWidget(parent) {
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

class ComplexMouseTestWidget : public QWidget {
    Q_OBJECT
public:
    ComplexMouseTestWidget() : QWidget(NULL) {
        gridLayout = new QGridLayout(this);
        verticalLayout = new QVBoxLayout();

        edit1 = new QLineEdit(this);
        verticalLayout->addWidget(edit1);

        test_wid = new MouseTestWidget(this);
        verticalLayout->addWidget(test_wid);

        edit2 = new QLineEdit(this);
        verticalLayout->addWidget(edit2);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);
    }

private:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;


    QLineEdit* edit1;
    MouseTestWidget* test_wid;
    QLineEdit* edit2;
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


class TrivMouseTestWidget : public MouseTestWidget, public TrivProxyWidget {
	Q_OBJECT
public:
	TrivMouseTestWidget() : MouseTestWidget(), TrivProxyWidget(){
		proxy->setWidget(this);
	}

protected:
    /*
	void mouseMoveEvent(QMouseEvent* event) override {
        QMouseEvent* event2 = new QMouseEvent(QEvent::MouseMove, mapPoint(event->pos()),
            event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
        //event->setLocalPos(mapPoint(event->pos()));
        //MouseTestWidget::mouseMoveEvent(event2);
        QApplication::sendEvent(this, event2);
	}

	void mousePressEvent(QMouseEvent* event) override {
        QMouseEvent* event2 = new QMouseEvent(QEvent::MouseButtonPress, mapPoint(event->pos()),
            event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
        //event->setLocalPos(mapPoint(event->pos()));
        MouseTestWidget::mousePressEvent(event2);
	}

	void mouseReleaseEvent(QMouseEvent* event) override {
        QMouseEvent* event2 = new QMouseEvent(QEvent::MouseButtonRelease, mapPoint(event->pos()),
            event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
        //event->setLocalPos(mapPoint(event->pos()));
        MouseTestWidget::mouseReleaseEvent(event2);
	}
    */
};


class TrivComplexMouseTestWidget : public ComplexMouseTestWidget, public TrivProxyWidget {
    Q_OBJECT
public:
    TrivComplexMouseTestWidget() : ComplexMouseTestWidget(), TrivProxyWidget(){
        proxy->setWidget(this);
    }

protected:
    /*
    void mouseMoveEvent(QMouseEvent* event) override {
        QMouseEvent* event2 = new QMouseEvent(QEvent::MouseMove, mapPoint(event->pos()),
            event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
        //event->setLocalPos(mapPoint(event->pos()));
        //MouseTestWidget::mouseMoveEvent(event2);
        QApplication::sendEvent(this, event2);
    }

    void mousePressEvent(QMouseEvent* event) override {
        QMouseEvent* event2 = new QMouseEvent(QEvent::MouseButtonPress, mapPoint(event->pos()),
            event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
        //event->setLocalPos(mapPoint(event->pos()));
        MouseTestWidget::mousePressEvent(event2);
    }

    void mouseReleaseEvent(QMouseEvent* event) override {
        QMouseEvent* event2 = new QMouseEvent(QEvent::MouseButtonRelease, mapPoint(event->pos()),
            event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
        //event->setLocalPos(mapPoint(event->pos()));
        MouseTestWidget::mouseReleaseEvent(event2);
    }
    */
};

class TrivProxyCheckBox : public QCheckBox, public TrivProxyWidget {
	Q_OBJECT
public:
	TrivProxyCheckBox(QString str) : QCheckBox(str), TrivProxyWidget(){
		proxy->setWidget(this);
	}

protected:
    void mouseMoveEvent(QMouseEvent* event) override {
        QMouseEvent* event2 = new QMouseEvent(QEvent::MouseMove, mapPoint(event->pos()),
            event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
        //event->setLocalPos(mapPoint(event->pos()));
        QCheckBox::mouseMoveEvent(event2);
    }

    void mousePressEvent(QMouseEvent* event) override {
        QMouseEvent* event2 = new QMouseEvent(QEvent::MouseButtonPress, mapPoint(event->pos()),
            event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
        //event->setLocalPos(mapPoint(event->pos()));
        QCheckBox::mousePressEvent(event2);
    }

    void mouseReleaseEvent(QMouseEvent* event) override {
        QMouseEvent* event2 = new QMouseEvent(QEvent::MouseButtonRelease, mapPoint(event->pos()),
            event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
        //event->setLocalPos(mapPoint(event->pos()));
        QCheckBox::mouseReleaseEvent(event2);
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
        QMouseEvent* event2 = new QMouseEvent(QEvent::MouseMove, mapPoint(event->pos()),
            event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
        //event->setLocalPos(mapPoint(event->pos()));
        TrivialTextEditor::mouseMoveEvent(event2);
    }

    void mousePressEvent(QMouseEvent* event) override {
        QMouseEvent* event2 = new QMouseEvent(QEvent::MouseButtonPress, mapPoint(event->pos()),
            event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
        //event->setLocalPos(mapPoint(event->pos()));
        TrivialTextEditor::mousePressEvent(event2);
    }

    void mouseReleaseEvent(QMouseEvent* event) override {
        QMouseEvent* event2 = new QMouseEvent(QEvent::MouseButtonRelease, mapPoint(event->pos()),
            event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
        //event->setLocalPos(mapPoint(event->pos()));
        TrivialTextEditor::mouseReleaseEvent(event2);
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
        QMouseEvent* event2 = new QMouseEvent(QEvent::MouseMove, mapPoint(event->pos()),
            event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
        //event->setLocalPos(mapPoint(event->pos()));
        QLineEdit::mouseMoveEvent(event2);
    }

    void mousePressEvent(QMouseEvent* event) override {
        QMouseEvent* event2 = new QMouseEvent(QEvent::MouseButtonPress, mapPoint(event->pos()),
            event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
        //event->setLocalPos(mapPoint(event->pos()));
        QLineEdit::mousePressEvent(event2);
    }

    void mouseReleaseEvent(QMouseEvent* event) override {
        QMouseEvent* event2 = new QMouseEvent(QEvent::MouseButtonRelease, mapPoint(event->pos()),
            event->windowPos(), event->screenPos(), event->button(), event->buttons(), event->modifiers());
        //event->setLocalPos(mapPoint(event->pos()));
        QLineEdit::mouseReleaseEvent(event2);
    }

};

class TrivProxySceneWidget : public TrivialSceneWidget, public TrivProxyWidget {
    Q_OBJECT
public:
    TrivProxySceneWidget() : TrivialSceneWidget(NULL, 300), TrivProxyWidget() {
        proxy->setWidget(this);
    }

};

#endif // TRIVIAL_GUI_ITEMS_H
