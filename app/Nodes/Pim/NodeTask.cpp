#include "NodeTask.h"
#include "coreqt/Utils/QStringUtils.h"
#include "app/Utils/Log.h"
#include "app/Utils/Workspace.h"

void NodeTask::LoadTml(TmlNode* node) {
	NodeBase::LoadTml(node);

	for (int i = 0; i < node->getNumArgs(); i++) {
		TmlArgument* arg = node->getArg(i);

		if (arg->getName() == "name") {
			name = arg->getValue();
		} else if (arg->getName() == "estimeted") {
			if (!QStringUtils::StrToFloat(arg->getValue(), estimeted)) {
				qCritical() << log_file(Workspace::get()->getCorrentInputFile(), arg->line, arg->pos) << "Parse estimeted value faild";
			}
		}
	}

	for (int i = 0; i < node->getNumChilds(); i++) {
		TmlNode* child = node->getChild(i);

		if (child->getName() == "param_description") {
			description = child->getData();
		}
	}
}
