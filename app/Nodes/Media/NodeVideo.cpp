#include "NodeVideo.h"

void NodeVideo::LoadTml(TmlNode* node) {
    NodeBase::LoadTml(node);

    for (int i = 0; i < node->getNumArgs(); i++) {
        TmlArgument* arg = node->getArg(i);

        if (arg->getName() == "path") {
            path = arg->getValue();
        }
    }
}

void NodeVideo::SaveTml(TmlNode* node) {
    NodeBase::SaveTml(node);
    node->setArgValue("path", path);
}
