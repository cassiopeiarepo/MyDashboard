#include "NodeQTextEdit.h"

NodeQTextEdit::NodeQTextEdit() : NodeQWidget(NULL) {
	edit = new QTextEdit();
	setWidget(edit);
}


void NodeQTextEdit::LoadTml(TmlNode* node) {
	NodeQWidget::LoadTml(node);


}