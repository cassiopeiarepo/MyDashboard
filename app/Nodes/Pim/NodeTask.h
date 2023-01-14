#ifndef __NODE_TASK_H__
#define __NODE_TASK_H__

#include <QString>
#include <QDateTime>
#include "app/Nodes/NodeBase.h"


class NodeTask : public NodeBase {
	Q_OBJECT
public:

	const QString& getName() { return name; }
	void setName(const QString& _name) { name = _name; }

	const QString& getDescription() { return description; }
	void setDescription(const QString& _description) { description = _description; }

	float getEstimeted() { return estimeted; }
	void setEstimeted(float _estimeted) { estimeted = _estimeted; }

	virtual void LoadTml(TmlNode* node);

	virtual QString getClassName() { return "task"; }

private:
	QString name;
	QString description;
	float estimeted;
};


#endif /* __NODE_TASK_H__ */
