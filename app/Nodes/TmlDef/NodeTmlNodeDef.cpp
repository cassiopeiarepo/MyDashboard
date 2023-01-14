#include "NodeTmlNodeDef.h"

#include "coreqt/Common/TmlDef.h"
#include "app/Nodes/TmlDef/NodeTmlDef.h"

void NodeTmlNodeDef::LoadTml(TmlNode* node) {
	NodeBase::LoadTml(node);

	for (int i = 0; i < node->getNumArgs(); i++) {
		TmlArgument* arg = node->getArg(i);

		if (arg->getName() == "type") {
			type = arg->getValue();
		}
	
	}

	if (type == "") {
		// dodac warnning
		return;
	}

	QObject* _parent = parent();
	NodeTmlDef* node_tml_def = qobject_cast<NodeTmlDef*>(_parent);

	if (node_tml_def == NULL)
		return;

	TmlDef* tml_def = node_tml_def->getTmlDef();

	tml_def->defineNodeDef(type, NULL);

}
