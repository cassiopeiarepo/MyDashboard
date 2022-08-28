#ifndef TRIVIAL_TEXT_ITEM_H
#define TRIVIAL_TEXT_ITEM_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "TrivialGraphicsItem.h"
#include "coreqt/Common/Tml.h"
#include "coreqt/Utils/QStringUtils.h"

class TrivialNoteItem : public TrivialGraphicsItem {

public:
	TrivialNoteItem() : TrivialGraphicsItem() { }

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

	void mouseMoveEvent(QMouseEvent* event) override { }
	void mousePressEvent(QMouseEvent* event) override { }
	void mouseReleaseEvent(QMouseEvent* event) override { }

	QPointF mouseMovePos;

};

class TrivSizableItem : public TrivialGraphicsItem {

public:
	TrivSizableItem() :TrivialGraphicsItem(), size(100, 50) { }

	QRectF boundingRect() const override { QPointF s = getItemSize();  return QRectF(0, 0, s.x(), s.y()); }
	QPainterPath shape() const override {
		QPainterPath path;
		QPointF s = getItemSize();
		path.addRect(0, 0, s.x(), s.y());
		return path;
	}

	QPointF getItemPos() { return pos(); }

	void setItemPos(QPointF _pos) {
		setPos(_pos);
	}

	QPointF getItemSize() const { return size; }

	void setItemSize(QPointF new_size) {
		size = new_size;

		QList<QGraphicsItem*> childs = this->childItems();
		foreach(QGraphicsItem * item, childs)
		{
			TrivSizableItem* sizable_item = dynamic_cast<TrivSizableItem*> (item);
			if (sizable_item != NULL) {
				sizable_item->updateParentSize();
			}
		}

		if (scene())
			scene()->update();
	}

	QRectF getItemMargin() { return margin; }

	void setItemMargin(QRectF _margin) {
		margin = _margin;
	}

	virtual bool loadTml(TmlNode* node)  
	{ 
		if (node->isArg("pos")) {
			float _pos[2];
			if (!QStringUtils::StrToFloatArray(node->getArgValue("pos"), _pos, 2)) {
				qDebug() << "pos arg parse failed";
				return false;
			}
			setItemPos(QPointF(_pos[0], _pos[1]));
		}

		if (node->isArg("size")) {
			float _size[2];
			if (!QStringUtils::StrToFloatArray(node->getArgValue("size"), _size, 2)) {
				qDebug() << "size arg parse failed";
				return false;
			}
			setItemSize(QPointF(_size[0], _size[1]));
		}

		return true;
	}

protected:
	virtual void updateParentSize() { }

private:
	QPointF size;
	QRectF margin;
};

class TrivialTextItem : public TrivSizableItem {

public:
	TrivialTextItem() : TrivSizableItem() , text_font(NULL), text_font_matrics(NULL)
	{
		setFontSize(12);
	}

	void setText(QString& _text) { text = _text; lines = QStringUtils::splitLinesUnix(text);  update(); }

	const QString& getText() const { return text; }

	int getFontSize() {  return text_font_size; }
	void setFontSize(int _size) {
		text_font_size = _size;

		if (text_font)
			delete text_font;
		text_font = new QFont("Arial", text_font_size);

		if (text_font_matrics)
			delete text_font_matrics;
		text_font_matrics = new QFontMetrics(*text_font);
	}

	bool loadTml(TmlNode* node) override {
		if (!TrivSizableItem::loadTml(node))
			return false;

		if (node->isArg("font_size")) {
			int font_size;
			if (!QStringUtils::StrToInt(node->getArgValue("font_size"), font_size)) {
				qDebug() << "font_size arg parse failed";
				return false;
			}
			setFontSize(font_size);
		}

		QString data = node->getData();
		setText(data);

		return true;
	}

protected:

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) override {
		painter->setFont(*this->text_font);
		QPointF size = getItemSize();
		painter->setClipRect(0, 0, size.x(), size.y());
		for (int i = 0; i < lines.size(); i++)
		{
			int line_offset_y = getLineOffset(i);
			painter->drawText( 0 , line_offset_y, lines[i]);
		}
	}
	int getLineHeight() {
		return text_font_matrics->lineSpacing();
	}

	int getLineOffset(int line_nr) {
		return (line_nr + 1) * getLineHeight() - text_font_matrics->descent();
	}

	QString text;
	QList<QString> lines;

	QFont* text_font;
	QFontMetrics* text_font_matrics;
	int text_font_size;
};

class TrivialGotoItem : public TrivSizableItem {

public:
	TrivialGotoItem() : TrivSizableItem(), text_font(NULL), text_font_matrics(NULL)
	{
		setFontSize(12);
	}

	void setText(QString& _text) { text = _text;  update(); }

	const QString& getText() const { return text; }

	int getFontSize() { return text_font_size; }
	void setFontSize(int _size) {
		text_font_size = _size;

		if (text_font)
			delete text_font;
		text_font = new QFont("Arial", text_font_size);

		if (text_font_matrics)
			delete text_font_matrics;
		text_font_matrics = new QFontMetrics(*text_font);
	}

	bool loadTml(TmlNode* node) override {
		if (!TrivSizableItem::loadTml(node))
			return false;

		if (node->isArg("font_size")) {
			int font_size;
			if (!QStringUtils::StrToInt(node->getArgValue("font_size"), font_size)) {
				qDebug() << "font_size arg parse failed";
				return false;
			}
			setFontSize(font_size);
		}

		if (node->isArg("text")) {
			setText(node->getArgValue("text"));
		}

		if (node->isArg("goto_pos")) {
			float _goto_pos[2];
			if (!QStringUtils::StrToFloatArray(node->getArgValue("goto_pos"), _goto_pos, 2)) {
				qDebug() << "goto_pos arg parse failed";
				return false;
			}
			goto_pos = QPointF(_goto_pos[0], _goto_pos[1]);
		}

		return true;
	}

protected:

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) override {
		painter->setFont(*this->text_font);
		QPointF size = getItemSize();
		painter->setClipRect(0, 0, size.x(), size.y());
	
		int line_offset_y = getLineOffset(0);
		painter->drawText(0, line_offset_y, text);
		
	}

	void mousePressEvent(QMouseEvent* event) override 
	{ 
		if (event->button() == Qt::LeftButton) {
			if (this->scene()) {
				QList<QGraphicsView*> views = scene()->views();
				if (views.size() > 0)
					views[0]->centerOn(goto_pos);
			}
		}
	}

	int getLineHeight() {
		return text_font_matrics->lineSpacing();
	}

	int getLineOffset(int line_nr) {
		return (line_nr + 1) * getLineHeight() - text_font_matrics->descent();
	}

	QString text;

	QFont* text_font;
	QFontMetrics* text_font_matrics;
	int text_font_size;
	QPointF goto_pos;
};


class TrivialImageItem : public TrivSizableItem {

public:
	TrivialImageItem() : TrivSizableItem()
	{

	}

	void setFilename(QString& _text) { 
		filename = _text;  
		if (!image.load(filename))
			qDebug() << "image file load failed "<< filename;
		update(); 
	}

	const QString& getFilename() const { return filename; }

	bool loadTml(TmlNode* node) override {
		if (!TrivSizableItem::loadTml(node))
			return false;

		if (node->isArg("abs_path")) {
			setFilename(node->getArgValue("abs_path"));
		}

		return true;
	}

protected:

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) override {
		QPointF size = getItemSize();
		painter->drawImage(QRectF(0, 0, size.x(), size.y()), image);
	}

	QImage image;
	QString filename;
};


class TrivialWindowItem : public TrivSizableItem {

public:
	TrivialWindowItem() : TrivSizableItem() , move_mouse(false), resize_mouse(false){
		 move_rect = QRectF(3, 3, 20, 20);
		 
	}

	void setCaption(QString& new_caption) { caption = new_caption; update(); }

protected:

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) override {
		QPointF size = getItemSize();
		painter->drawRect(QRectF(0, 0, size.x(), size.y()));
		QBrush move_brush(Qt::SolidPattern);
		painter->setBrush(Qt::black);
		painter->fillRect(move_rect, move_brush);

		float w = size.x();
		float h = size.y();

		painter->drawLine(QPointF(w, h - 18.0), QPointF(w - 18.0, h));
		painter->drawLine(QPointF(w, h - 13.0), QPointF(w - 13.0, h));
		painter->drawLine(QPointF(w, h - 8.0), QPointF(w - 8.0, h));

	}

	void mouseMoveEvent(QMouseEvent* event) override 
	{ 
		if (move_mouse)
		{
			QPointF move_mouse_scene_pos0 = mapToScene(move_mouse_pos);
			QPointF move_mouse_scene_pos = mapToScene(event->pos());
			setPos(move_mouse_scene_pos - (move_mouse_scene_pos0 - pos()));
		}

		if (resize_mouse) 
		{
			QPointF point = mapToScene(event->pos() + move_diff) - mapToScene(QPointF());
			setItemSize(point);
		}
	}

	void mousePressEvent(QMouseEvent* event) override 
	{ 
		if (event->button() == Qt::LeftButton) {
			if (move_rect.contains(event->pos())) {
				move_mouse_pos = event->pos();
				move_mouse = true;
			}
			QPointF size = getItemSize();
			QRectF resize_rect = QRectF( size.x() - 20, size.y() - 20, 20, 20);

			if (resize_rect.contains(event->pos())) {
				resize_mouse = true;
				move_diff = size - event->pos();
			}
		}
		
	}

	void mouseReleaseEvent(QMouseEvent* event) override { 
		if (event->button() == Qt::LeftButton) {
			move_mouse = false;
			resize_mouse = false;
		}
	
	}

	QString caption;

	bool move_mouse;
	QRectF move_rect;
	QPointF move_mouse_pos;
	
	bool resize_mouse;
	QPointF move_diff;
};






#endif // TRIVIAL_TEXT_ITEM_H
