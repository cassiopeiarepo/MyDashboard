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

    TmlNode* child = node->getChild("param_text");

    if (child) {
        text = child->getData();
    }

}

void NodeText::SaveTml(TmlNode* node) {
    NodeBase::SaveTml(node);
    TmlNode* child = node->createChild("param_text");
    child->setData(text);
}
