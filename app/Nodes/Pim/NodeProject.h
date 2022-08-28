#ifndef __NODE_PROJECT_H__
#define __NODE_PROJECT_H__

#include <QString>
#include <QDateTime>
#include "app/Nodes/NodeBase.h"
#include "core/types/Vector.h"

class NodeTask;

class NodeProject : public NodeBase {
public:

	virtual void LoadTml(TmlNode* node);

	virtual QString getClassName() { return "project"; }

	void addTask(NodeTask* task) { tasks.append(task); }

	Vector<NodeTask*> getTasks() { return tasks; }

private:
	QString name;
	Vector<NodeTask*> tasks;
};


#endif /* __NODE_PROJECT_H__ */