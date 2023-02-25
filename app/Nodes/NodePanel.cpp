#include "NodePanel.h"

void NodePanel::LoadTml(TmlNode* node) {
	NodeBase::LoadTml(node);

	for (int i = 0; i < node->getNumArgs(); i++) {
		TmlArgument* arg = node->getArg(i);

		if (arg->getName() == "name") {
			name = arg->getValue();
		}
		else if (arg->getName() == "place") {

			if (!StrToPanelPlace(arg->getValue(), &place)) {
				
			}


		}
	}
}

void NodePanel::SaveTml(TmlNode* node) {
    NodeBase::SaveTml(node);
    //node->setArgValue("name", objectName());
    //node->setArgValue("tags", tags.toString());
}

bool NodePanel::StrToPanelPlace(const QString& str, TrivialMainWindow::PanelPlace* panel_place) {
	return true;

}
