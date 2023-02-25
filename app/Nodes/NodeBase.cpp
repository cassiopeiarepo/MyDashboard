#include "NodeBase.h"

void NodeBase::LoadTml(TmlNode* node) {

	for (int i = 0; i < node->getNumArgs(); i++) {
		TmlArgument* arg = node->getArg(i);
        if (arg->getName() == "name") {
            setObjectName(arg->getValue());
        }
        else if (arg->getName() == "tags") {
			tags = Tags::fromString(arg->getValue());
		}
	}

}

void NodeBase::SaveTml(TmlNode* node) {
    node->setArgValue("name", objectName());
    node->setArgValue("tags", tags.toString());
}
