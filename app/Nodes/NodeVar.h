#ifndef __NODE_VAR_H__
#define __NODE_VAR_H__

#include "app/Nodes/NodeBase.h"


class NodeVar : public NodeBase {
	Q_OBJECT
public:

	virtual void LoadTml(TmlNode* node);

	virtual QString getClassName() { return "var"; }

private:
	QString name;
	QString value;
};

#endif /* __NODE_VAR_H__ */
