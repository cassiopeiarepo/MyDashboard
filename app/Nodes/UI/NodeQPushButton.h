#ifndef __NODE_QPUSHBUTTON_H__
#define __NODE_QPUSHBUTTON_H__

#include "app/Nodes/UI/NodeQWidget.h"

#include <QPushButton>

class NodeQPushButton : public NodeQWidget {
	Q_OBJECT
public:

	NodeQPushButton();

	virtual void LoadTml(TmlNode* node);

	virtual QString getClassName() { return "qpushbutton"; }

	QPushButton* getPushButton() { return button; }

protected:
	QPushButton* button;

};


#endif /* __NODE_QPUSHBUTTON_H__ */
