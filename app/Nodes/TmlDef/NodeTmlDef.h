#ifndef __NODE_TML_DEF_H__
#define __NODE_TML_DEF_H__

#include "app/Nodes/NodeBase.h"

class TmlDef;

class NodeTmlDef : public NodeBase {
	Q_OBJECT
public:

	virtual void LoadTml(TmlNode* node);

	virtual QString getClassName() { return "tmldef"; }

	TmlDef* getTmlDef() { return tml_def; }

private:
	QString name;
	QString root_name;
	QString root_type;

	TmlDef* tml_def;
};

#endif /* __NODE_TML_DEF_H__ */
