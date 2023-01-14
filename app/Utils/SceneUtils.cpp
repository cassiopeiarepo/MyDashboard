#include "app/Utils/SceneUtils.h"

QString SceneUtils::getNodePath(NodeBase* node) {
	NodeBase* cur = node;
	QString path;

	while (cur != NULL) {
		path = "/" + cur->objectName() + path;
		cur = qobject_cast<NodeBase*>(cur->parent());
	}

	return path;
}
