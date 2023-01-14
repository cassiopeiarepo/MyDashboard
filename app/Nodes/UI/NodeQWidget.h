#ifndef __NODE_QWIDGET_H__
#define __NODE_QWIDGET_H__

#include "app/Nodes/NodeBase.h"

#include <QWidget>

class NodeQWidget : public NodeBase {
	Q_OBJECT
public:
	NodeQWidget();
	NodeQWidget(QWidget* wid);

	virtual void LoadTml(TmlNode* node);

	virtual QString getClassName() { return "qwidget"; }

	QWidget* getWidget() { return widget; }
	void setWidget(QWidget* wid);


protected:
	QWidget* widget;

};


#endif /* __NODE_QWIDGET_H__ */

