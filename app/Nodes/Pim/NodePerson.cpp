#include "NodePerson.h"

void NodePerson::LoadTml(TmlNode* node) {
	NodeBase::LoadTml(node);

	for (int i = 0; i < node->getNumArgs(); i++) {
		TmlArgument* arg = node->getArg(i);

		if (arg->getName() == "nick") {
			nick = arg->getValue();
		}
		else if (arg->getName() == "first_name") {
			first_name = arg->getValue();
		}
		else if (arg->getName() == "second_name") {
			second_name = arg->getValue();
		}
	}
}
