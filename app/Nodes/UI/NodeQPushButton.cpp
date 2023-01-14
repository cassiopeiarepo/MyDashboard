#include "NodeQPushButton.h"

NodeQPushButton::NodeQPushButton() : NodeQWidget(NULL) {
	button = new QPushButton();
	setWidget(button);
}


void NodeQPushButton::LoadTml(TmlNode* node) {
	NodeQWidget::LoadTml(node);

}
