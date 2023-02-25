#ifndef __NODE_INCLUDE_H__
#define __NODE_INCLUDE_H__

#include "app/Nodes/NodeBase.h"


class NodeInclude : public NodeBase {
	Q_OBJECT
public:

    void LoadTml(TmlNode* node) override;
    void SaveTml(TmlNode* node) override;

	virtual QString getClassName() { return "include"; }

private:
	QString rel_path;
};

#endif /* __NODE_INCLUDE_H__ */
