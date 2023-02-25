#include "NodeLink.h"

#include "app/Utils/SceneUtils.h"

void NodeLink::LoadTml(TmlNode* node) {
    NodeBase::LoadTml(node);

    for (int i = 0; i < node->getNumArgs(); i++) {
        TmlArgument* arg = node->getArg(i);

        if (arg->getName() == "node_link") {
            //rel_path = arg->getValue();
        }
    }

}

void NodeLink::SaveTml(TmlNode* node) {
    NodeBase::SaveTml(node);
    node->setArgValue("node_link", SceneUtils::getNodePath(this->node));
}
