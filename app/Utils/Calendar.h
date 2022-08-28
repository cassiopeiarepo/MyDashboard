#ifndef __CALENDAR_H__
#define __CALENDAR_H__

#include "core/types/Base.h"
#include "core/types/Vector.h"
#include "core/utils/Singleton.h"

class NodeEvent;

class Calendar : public Singleton<Calendar> {
public:

	void addEvent(NodeEvent* _event);

	Vector<NodeEvent*> getEvents(int year, int manth, int day);

private:
	Vector<NodeEvent*> events;

};


#endif /* __CALENDAR_H__ */

