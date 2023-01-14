#ifndef __NODE_BASE_H__
#define __NODE_BASE_H__

#include "coreqt/Common/Tml.h"
#include "coreqt/Utils/Tags.h"

#include <QObject>

class NodeBase : public QObject {

	Q_OBJECT

public:
	NodeBase() : QObject() { }

	virtual void LoadTml(TmlNode* node);

	virtual QString getClassName() { return "NodeBase"; }

	Tags& getTags() { return tags; }

private:
	Tags tags;
};

class NodeDummy : public NodeBase {
	Q_OBJECT
public:
	virtual QString getClassName() { return "dummy"; }
};


#endif /* __NODE_BASE_H__ */

