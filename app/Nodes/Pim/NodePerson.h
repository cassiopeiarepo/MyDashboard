#ifndef __NODE_PERSON_H__
#define __NODE_PERSON_H__

#include <QString>
#include <QDateTime>
#include "app/Nodes/NodeBase.h"


class NodePerson : public NodeBase {
public:

	const QString& getNick() { return nick;  }
	void setNick(const QString& _nick) { nick = _nick; }

	const QString& getFirstName() { return first_name; }
	void setFirstName(const QString& fname) { first_name = fname; }

	const QString& getSecondName() { return second_name; }
	void setSecondName(const QString& sname) { second_name = sname; }

	virtual void LoadTml(TmlNode* node);

	virtual QString getClassName() { return "person"; }

private:
	QString nick;
	QString first_name;
	QString second_name;
};


#endif /* __NODE_PERSON_H__ */
