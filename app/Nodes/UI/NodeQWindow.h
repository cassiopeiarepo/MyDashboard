#ifndef __NODE_QWINDOW_H__
#define __NODE_QWINDOW_H__

#include "app/Nodes/UI/NodeQWidget.h"

#include <QMainWindow>

class NodeQWindow : public NodeQWidget {
	Q_OBJECT

public:

	NodeQWindow();

	virtual void LoadTml(TmlNode* node);

	virtual QString getClassName() { return "qwindow"; }

	QMainWindow* getMainWindow() { return window; }

protected:
	QMainWindow* window;

};


#endif /* __NODE_QWINDOW_H__ */
