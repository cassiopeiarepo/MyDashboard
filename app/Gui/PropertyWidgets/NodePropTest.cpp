#include "app/Gui/PropertyWidgets/NodePropTest.h"

void NodePropTest::LoadTml(TmlNode* node) {
    NodeBase::LoadTml(node);

    for (int i = 0; i < node->getNumArgs(); i++) {
        TmlArgument* arg = node->getArg(i);


    }


}

