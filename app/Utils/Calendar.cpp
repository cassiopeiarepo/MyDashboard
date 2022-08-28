#include "Calendar.h"

#include "app/Nodes/Pim/NodeEvent.h"

#include <QDate>

void Calendar::addEvent(NodeEvent* _event) {
	events.append(_event);
}

Vector<NodeEvent*> Calendar::getEvents(int year, int manth, int day) {
	Vector<NodeEvent*> result;

	QDate data = QDate(year, manth, day);

	for (int i = 0; i < events.size(); i++) {
		NodeEvent* event = events[i];
		if (event->getStart().date() == data)
			result.append(event);
	}

	return result;
}
