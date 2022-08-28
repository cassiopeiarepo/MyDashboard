#ifndef __NODE_BASE_H__
#define __NODE_BASE_H__

#include "core/node/Node.h"
#include "coreqt/Common/Tml.h"
#include "coreqt/Utils/Tags.h"

class NodeBase : public Node {
public:

	virtual void LoadTml(TmlNode* node);

	virtual QString getClassName() { return "NodeBase"; }

	Tags& getTags() { return tags; }

private:
	Tags tags;
};

class NodeDummy : public NodeBase {
public:
	virtual QString getClassName() { return "dummy"; }
};


#endif /* __NODE_BASE_H__ */

