#include "NodeProject.h"



void NodeProject::LoadTml(TmlNode* node) {
	NodeBase::LoadTml(node);

	for (int i = 0; i < node->getNumArgs(); i++) {
		TmlArgument* arg = node->getArg(i);

		if (arg->getName() == "name") {
			name = arg->getValue();
		}
		
	}
}

