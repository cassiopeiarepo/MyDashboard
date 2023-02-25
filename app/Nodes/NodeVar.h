#ifndef __NODE_VAR_H__
#define __NODE_VAR_H__

#include "app/Nodes/NodeBase.h"


class NodeVar : public NodeBase {
	Q_OBJECT
public:

    void LoadTml(TmlNode* node) override;
    void SaveTml(TmlNode* node) override;

	virtual QString getClassName() { return "var"; }

private:
	QString value;
};

#endif /* __NODE_VAR_H__ */
