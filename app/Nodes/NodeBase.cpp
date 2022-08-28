#include "NodeBase.h"

void NodeBase::LoadTml(TmlNode* node) {

	for (int i = 0; i < node->getNumArgs(); i++) {
		TmlArgument* arg = node->getArg(i);

		if (arg->getName() == "tags") {
			tags = Tags::fromString(arg->getValue());
		}
	}

}
