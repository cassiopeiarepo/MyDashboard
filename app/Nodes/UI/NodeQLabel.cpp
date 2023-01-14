#include "NodeQLabel.h"

NodeQLabel::NodeQLabel() : NodeQWidget(NULL) {
	label = new QLabel();
	setWidget(label);
}


void NodeQLabel::LoadTml(TmlNode* node) {
	NodeQWidget::LoadTml(node);


}
