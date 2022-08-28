#ifndef TRIVIAL_GRAPHICS_VIEW_H
#define TRIVIAL_GRAPHICS_VIEW_H

#include <QGraphicsView>
//#include <QGraphicsScane>
#include <QMouseEvent>
#include <QDebug>
#include <QFileSystemWatcher>

class TrivialGraphicsView : public QGraphicsView {
	Q_OBJECT
public:
	TrivialGraphicsView();

	void wheelEvent(QWheelEvent*) override;

	void mouseDoubleClickEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;

	float getZoom() { return zoom; }
	void setZoom(float new_zoom) { zoom = new_zoom; update_transform(); }

	void setFocusItem(QGraphicsItem* _focusItem) { focusItem = _focusItem;  }

	void clear();

	void loadFile(const QString& abs_path);
	void watchFile(const QString& abs_path);


protected:
	void update_transform();
	bool isOnlyOneButtonPressed(QMouseEvent* event);
	bool IsNullButtonPressed(QMouseEvent* event);

public slots:
	void onWatchFileChanged(const QString& path);

private:
	QGraphicsScene* scene;

	float zoom;

	bool middleMousePressed;
	QPointF p1, center1;

	QGraphicsItem* focusItem;
	QGraphicsItem* mouseItem;
	QFileSystemWatcher* watcher;
};

#endif // TRIVIAL_GRAPHICS_VIEW_H
