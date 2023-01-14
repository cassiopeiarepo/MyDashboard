#ifndef __NODE_PROJECT_H__
#define __NODE_PROJECT_H__

#include <QString>
#include <QDateTime>
#include <QList>

#include "app/Nodes/NodeBase.h"


class NodeTask;

class NodeProject : public NodeBase {
	Q_OBJECT
public:

	virtual void LoadTml(TmlNode* node);

	virtual QString getClassName() { return "project"; }

	void addTask(NodeTask* task) { tasks.append(task); }

	QList<NodeTask*> getTasks() { return tasks; }

private:
	QString name;
	QList<NodeTask*> tasks;
};


#endif /* __NODE_PROJECT_H__ */