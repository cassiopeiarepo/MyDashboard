#ifndef __NODE_TML_NODE_DEF_H__
#define __NODE_TML_NODE_DEF_H__

#include "app/Nodes/NodeBase.h"

class TmlNodeDef;

class NodeTmlNodeDef : public NodeBase {
	Q_OBJECT
public:

	virtual void LoadTml(TmlNode* node);

	virtual QString getClassName() { return "tml_nodedef"; }

	TmlNodeDef* getNodeDef() { return node_def; }

private:
	QString type;

	TmlNodeDef* node_def;

};

#endif /* __NODE_TML_NODE_DEF_H__ */

