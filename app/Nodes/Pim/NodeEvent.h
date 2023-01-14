#ifndef __NODE_EVENT_H__
#define __NODE_EVENT_H__

#include <QString>
#include <QDateTime>
#include "app/Nodes/NodeBase.h"

class NodeTask;

class NodeEvent : public NodeBase {
	Q_OBJECT
public:
	
	const QString& getCaption() { return caption; }
	void setCaption(const QString& _caption) { caption = _caption; }

	NodeTask* getTask() { return task; }
	void setTask(NodeTask* _task) { task = _task; }

	const QDateTime& getStart() { return start; }
	void setStart(const QDateTime& _start) { start = _start; }

	const QDateTime& getEnd() { return end; }
	void setEnd(const QDateTime& _end) { end = _end; }

	float getDuration();
	void setDuration(float _duration);

	virtual void LoadTml(TmlNode* node);

	virtual QString getClassName() { return "event"; }

private:
	NodeTask* task;
	QString caption;
	QDateTime start;
	QDateTime end;
};


#endif /* __NODE_EVENT_H__ */
