#ifndef __NODE_LINK_H__
#define __NODE_LINK_H__

#include "app/Nodes/NodeBase.h"


class NodeLink : public NodeBase {
    Q_OBJECT
public:

    void LoadTml(TmlNode* node) override;
    void SaveTml(TmlNode* node) override;

    virtual QString getClassName() { return "link"; }

    void setNode(NodeBase* _node) { node = _node; }
    NodeBase* getNode() { return node;}

private:
    NodeBase* node;
};

#endif /* __NODE_LINK_H__ */
