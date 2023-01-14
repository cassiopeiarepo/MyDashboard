#ifndef __CALENDAR_H__
#define __CALENDAR_H__

#include "coreqt/Utils/Base.h"
#include "coreqt/Utils/Singleton.h"

#include <QList>

class NodeEvent;

class Calendar : public Singleton<Calendar> {
public:

	void addEvent(NodeEvent* _event);

	QList<NodeEvent*> getEvents(int year, int manth, int day);

private:
	QList<NodeEvent*> events;

};


#endif /* __CALENDAR_H__ */

