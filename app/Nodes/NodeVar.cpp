#include "NodeVar.h"
#include "app/Utils/Workspace.h"


void NodeVar::LoadTml(TmlNode* node) {
	NodeBase::LoadTml(node);

	for (int i = 0; i < node->getNumArgs(); i++) {
		TmlArgument* arg = node->getArg(i);

		if (arg->getName() == "name") {
			name = arg->getValue();
		} else if (arg->getName() == "value") {
			value = arg->getValue();
		}
	}

	Workspace::get()->setVar(name, value);
}