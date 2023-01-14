#include "NodeQWidget.h"

#include "coreqt/Utils/QStringUtils.h"
#include <QDebug>

NodeQWidget::NodeQWidget() : widget(new QWidget()) {

}

NodeQWidget::NodeQWidget(QWidget* wid) : widget(wid) {

}

void NodeQWidget::setWidget(QWidget* wid) {
	widget = wid; 

	QObject* _parent = parent();

	if (_parent) {
		NodeQWidget* parent_widget = qobject_cast<NodeQWidget*>(_parent);

		if (parent_widget) {
			widget->setParent(parent_widget->widget);
		}
	}
}


void NodeQWidget::LoadTml(TmlNode* node) {
	NodeBase::LoadTml(node);

	for (int i = 0; i < node->getNumArgs(); i++) {
		TmlArgument* arg = node->getArg(i);

		if (arg->getName() == "pos") {
			int _pos[2];
			if (!QStringUtils::StrToIntArray(node->getArgValue("pos"), _pos, 2)) {
				qDebug() << "pos arg parse failed";				
				return;
			}
			widget->move(_pos[0], _pos[1]);
		} else if (arg->getName() == "size") {
			int _size[2];
			if (!QStringUtils::StrToIntArray(node->getArgValue("size"), _size, 2)) {
				qDebug() << "size arg parse failed";
				return;
			}
			widget->resize(_size[0], _size[1]);
		}
	}

}

