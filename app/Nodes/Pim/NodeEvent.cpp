#include "NodeEvent.h"
#include "coreqt/Utils/QStringUtils.h"
#include <QtMath>
#include "app/Utils/Workspace.h"
#include "app/Utils/Log.h"
#include "app/Utils/Calendar.h"


float NodeEvent::getDuration() {
	return 0.0f;
}

void NodeEvent::setDuration(float _duration) {
	end = start.addSecs(qFloor(_duration * 60.0 * 60.0));
}

void NodeEvent::LoadTml(TmlNode* node) {
	NodeBase::LoadTml(node);

	for (int i = 0; i < node->getNumArgs(); i++) {
		TmlArgument* arg = node->getArg(i);

		if (arg->getName() == "caption") {
			caption = arg->getValue();
		}
		else if (arg->getName() == "start") {

			if (!QStringUtils::StrToDateTime(arg->getValue(), start)) {
				QString str_current_day = Workspace::get()->getVar(QString("current_day"));
				
				if (str_current_day != "") {
					QDate day;
					if (!QStringUtils::StrToDate(str_current_day, day)) {
						qCritical() << " event can not parse current_day var";
					}
					else {
						QTime time;
						if (!QStringUtils::StrToTime(arg->getValue(), time)) {
							qCritical() << " event can not parse current_day var";
						}
						else {
							start = QDateTime(day, time);
						}
					}
				}
				else {
					//Log::get()->error(" event can not parse current_day var");
				}
			}

		}
		else if (arg->getName() == "duration") {
			float duration;
			if (QStringUtils::StrToDuration(arg->getValue(), duration)) {
				setDuration(duration);
			}
			else {
				//Log::get()->file_error()
			}
		}
	}

	Calendar::get()->addEvent(this);
}

