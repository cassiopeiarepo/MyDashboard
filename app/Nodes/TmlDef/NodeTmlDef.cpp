#include "NodeTmlDef.h"

#include "coreqt/Common/TmlDef.h"
#include "app/Utils/Workspace.h"


void NodeTmlDef::LoadTml(TmlNode* node) {
	NodeBase::LoadTml(node);

	tml_def = new TmlDef();

	for (int i = 0; i < node->getNumArgs(); i++) {
		TmlArgument* arg = node->getArg(i);

		if (arg->getName() == "name") {
			name = arg->getValue();
		} else if (arg->getName() == "root_name") {
			root_name = arg->getValue();
		} else if (arg->getName() == "root_type") {
			root_type = arg->getValue();
		}
	}

	if (name != "") {
		Workspace::get()->setTmlDef(name, tml_def);
	}

}

