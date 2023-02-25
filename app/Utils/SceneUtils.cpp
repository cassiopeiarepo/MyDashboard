#include "app/Utils/SceneUtils.h"
#include "app/Utils/TypeDef.h"

#include "QClipboard"
#include "QApplication"

NodeBase* SceneUtils::createNode(const QString& node_type_name) {
    QMetaType mt = QMetaType::fromName(QByteArrayView(node_type_name.toUtf8()));

    if (!mt.isValid())
        return NULL;

    NodeBase* result = static_cast<NodeBase*>(mt.create());
    return result;
}

QString SceneUtils::getNodePath(NodeBase* node) {
	NodeBase* cur = node;
	QString path;

	while (cur != NULL) {
		path = "/" + cur->objectName() + path;
		cur = qobject_cast<NodeBase*>(cur->parent());
	}

	return path;
}

TmlNode* SceneUtils::nodeToTml(NodeBase* node, TmlNode* tml_node_parent) {
    TmlNode* tml_node = NULL;

    if (tml_node_parent) {
        tml_node = tml_node_parent->createChild("");
    } else {
        tml_node= new TmlNode();
    }

    const TypeDef* type_def = TypeSystem::get()->getType(node->metaObject()->metaType().name());
    QString tml_node_name = type_def->getTmlName();
    if (tml_node_name == "")
        tml_node_name = node->metaObject()->metaType().name();

    tml_node->setName(tml_node_name);

    node->SaveTml(tml_node);

    QObjectList child_list = node->children();
    for (int i = 0; i < child_list.length(); i++) {
        NodeBase* child_node = dynamic_cast<NodeBase*>(child_list[i]);
        if (child_node) {
            nodeToTml(child_node, tml_node);
        }
    }

    return tml_node;
}

TmlNode* SceneUtils::serializeNodeToTml(NodeBase* node) {
    if (!node)
        return NULL;
    TmlNode* result = nodeToTml(node, NULL);

    return result;
}

void SceneUtils::deserializeNodeFromTml(NodeBase* parent_node, TmlNode* tml_node) {
    qDebug() << " deserializeNodeFromTml1 " << tml_node->getName();
    QString node_type_name = TypeSystem::get()->getTmlNameMap()[tml_node->getName()];
    if (node_type_name == "") {
        qCritical() << "SceneUtils::deserializeNodeFromTml empty node typename";
        return;
    }

    qDebug() << " deserializeNodeFromTml2 " << node_type_name;

    NodeBase* node = createNode(node_type_name);
    if (!node) {
        qCritical() << "SceneUtils::deserializeNodeFromTml can not create node for " << node_type_name << " typename";
        return;
    }

    node->setParent(parent_node);

    node->LoadTml(tml_node);

    for (int i = 0; i < tml_node->getNumChilds(); i++) {
        TmlNode* child = tml_node->getChild(i);

        if ((child->getName().left(6) == "param_") || (child->getName().left(5) == "prop_")) {

        }
        else {
            deserializeNodeFromTml(node, child);
        }
    }


}

bool SceneUtils::serializeNodeToString(NodeBase* node, QString& out) {

    TmlNode* tml_node = serializeNodeToTml(node);
    if (tml_node) {
        out = tml_node->toString(80);
        delete tml_node;
        return true;
    }

    return false;
}

bool SceneUtils::deserializeNodeFromString(NodeBase* parent_node, QString& input) {

    TmlNode* root_node = new TmlNode();

    TmlStringSource* source = new TmlStringSource(input);
    root_node->parse(source);

    if (!source->error) {
        delete source;
        qDebug() << "pass2";
        deserializeNodeFromTml(parent_node, root_node);
        delete root_node;
        return true;
    }

    delete source;

    return false;
}

void SceneUtils::copyNodeToClipboard(NodeBase* node) {
    QString data;
    if (serializeNodeToString(node, data) ) {
        QApplication::clipboard()->setText(data);
    }
}

void SceneUtils::pasteNodeFromClipbord(NodeBase* parent_node) {
    QString input = QApplication::clipboard()->text();

    if (input != "")
        deserializeNodeFromString(parent_node, input);

}

