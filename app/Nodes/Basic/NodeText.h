#ifndef __NODE_TEXT_H__
#define __NODE_TEXT_H__

#include "app/Nodes/NodeBase.h"


class NodeText : public NodeBase {
	Q_OBJECT
public:

	virtual void LoadTml(TmlNode* node);

	virtual QString getClassName() { return "text"; }

private:
	QString text;
};

#endif /* __NODE_TEXT_H__ */
