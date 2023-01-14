#include "NodeQWindow.h"

NodeQWindow::NodeQWindow() : NodeQWidget(NULL) {
	window = new QMainWindow();
	setWidget(window);
	window->show();
}


void NodeQWindow::LoadTml(TmlNode* node) {
	NodeQWidget::LoadTml(node);


}

