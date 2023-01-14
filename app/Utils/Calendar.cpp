#include "Calendar.h"

#include "app/Nodes/Pim/NodeEvent.h"

#include <QDate>

void Calendar::addEvent(NodeEvent* _event) {
	events.append(_event);
}

QList<NodeEvent*> Calendar::getEvents(int year, int manth, int day) {
	QList<NodeEvent*> result;

	QDate data = QDate(year, manth, day);

	for (NodeEvent* event : events) {
		if (event->getStart().date() == data)
			result.append(event);
	}

	return result;
}
