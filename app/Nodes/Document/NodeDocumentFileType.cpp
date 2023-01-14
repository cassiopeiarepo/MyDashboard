#include "NodeDocumentFileType.h"
#include "app/Gui/Views/TrivialDocumentsView.h"


void NodeDocumentFileType::LoadTml(TmlNode* node) {
	NodeBase::LoadTml(node);

	for (int i = 0; i < node->getNumArgs(); i++) {
		TmlArgument* arg = node->getArg(i);

		if (arg->getName() == "name") {
			name = arg->getValue();
		}
		else if (arg->getName() == "ext") {
			ext = arg->getValue();
		}
		else if (arg->getName() == "type") {
			type = arg->getValue();
		}
		else if (arg->getName() == "subtype") {
			subtype = arg->getValue();
		}
	}

	TrivialDocumentsView::get()->addFileType(name, ext, type, subtype);
}