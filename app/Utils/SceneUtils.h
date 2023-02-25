#ifndef __SCENE_UTILS_H__
#define __SCENE_UTILS_H__

#include "app/Utils/Workspace.h"

class SceneUtils {
public:

    static NodeBase* createNode(const QString& node_type_name);

	static QString getNodePath(NodeBase* node);
	//static NodeBase* getNodeFromPath(const QString& path);

    static void copyNodeToClipboard(NodeBase* node);
    static void pasteNodeFromClipbord(NodeBase* parent_node);

    static bool serializeNodeToString(NodeBase* node, QString& out);
    static bool deserializeNodeFromString(NodeBase* parent_node, QString& input);

    static TmlNode* serializeNodeToTml(NodeBase* node);
    static void deserializeNodeFromTml(NodeBase* parent_node, TmlNode* tml_node);

private:
    static TmlNode* nodeToTml(NodeBase* node, TmlNode* tml_node_parent);
};


#endif /* __SCENE_UTILS_H__ */

