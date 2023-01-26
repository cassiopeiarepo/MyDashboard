#include "NodeText.h"
#include "app/Utils/Workspace.h"

void NodeText::LoadTml(TmlNode* node) {
	NodeBase::LoadTml(node);

	for (int i = 0; i < node->getNumArgs(); i++) {
		TmlArgument* arg = node->getArg(i);

		//if (arg->getName() == "rel_path") {
		//	rel_path = arg->getValue();
		//}
	}

}
