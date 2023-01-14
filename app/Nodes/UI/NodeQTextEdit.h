#ifndef __NODE_QTEXTEDIT_H__
#define __NODE_QTEXTEDIT_H__

#include "app/Nodes/UI/NodeQWidget.h"

#include <QTextEdit>

class NodeQTextEdit : public NodeQWidget {
	Q_OBJECT
public:

	NodeQTextEdit();

	virtual void LoadTml(TmlNode* node);

	virtual QString getClassName() { return "qtextedit"; }

	QTextEdit* getTextEdit() { return edit; }

protected:
	QTextEdit* edit;

};


#endif /* __NODE_QTEXTEDIT_H__ */