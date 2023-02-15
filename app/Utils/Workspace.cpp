#include "Workspace.h"
#include "app/Utils/Log.h"
#include "app/Utils/Calendar.h"

//#include <QScriptEngine>


#include "coreqt/Utils/QStringUtils.h"
#include <QDebug>


#include "app/Nodes/NodeBase.h"
#include "app/Nodes/NodeInclude.h"
#include "app/Nodes/NodeVar.h"
#include "app/Nodes/Pim/NodeEvent.h"
#include "app/Nodes/Pim/NodePerson.h"
#include "app/Nodes/Pim/NodeProject.h"
#include "app/Nodes/Pim/NodeTask.h"
#include "app/Nodes/Document/NodeDocumentFileType.h"

#include "app/Nodes/UI/NodeUi.h"
#include "app/Nodes/UI/NodeQWidget.h"
#include "app/Nodes/UI/NodeQWindow.h"
#include "app/Nodes/UI/NodeQLabel.h"
#include "app/Nodes/UI/NodeQPushButton.h"
#include "app/Nodes/UI/NodeQTextEdit.h"

#include "app/Nodes/Basic/NodeText.h"
#include "app/Nodes/Basic/NodeLink.h"
#include "app/Nodes/Basic/NodeHeading1.h"
#include "app/Nodes/Basic/NodeHeading2.h"
#include "app/Nodes/Basic/NodeHeading3.h"

#include "app/Nodes/Media/NodeImage.h"
#include "app/Nodes/Media/NodeVideo.h"

#include "app/Utils/Script.h"
#include "app/Utils/TypeDef.h"

#include "coreqt/Common/TmlDef.h"

#include "app/Gui/PropertyWidgets/NodePropTest.h"

void Workspace::init(QString _dir) {

    //TypeSystem::get()->init();

	//loadDefaultFile(_dir);

	NodeDummy* dummy_root = new NodeDummy();
	dummy_root->setObjectName("Root");

	root = dummy_root;

	NodeDummy* dummy1 = new NodeDummy();
	dummy1->setObjectName("Calendar");
	dummy1->setParent(dummy_root);
	
    NodeText* text1 = new NodeText();
    text1->setObjectName("Text1");
    text1->setParent(dummy1);

    NodeLink* link1 = new NodeLink();
    link1->setObjectName("Link11");
    link1->setParent(dummy1);
    link1->setNode(text1);

    NodeHeading1* heading1 = new NodeHeading1();
    heading1->setObjectName("heading1");
    heading1->setParent(dummy1);
    heading1->setText("Treść heading1");

    NodeHeading2* heading2 = new NodeHeading2();
    heading2->setObjectName("heading2");
    heading2->setParent(dummy1);
    heading2->setText("Treść heading2");

    NodeHeading3* heading3 = new NodeHeading3();
    heading3->setObjectName("heading3");
    heading3->setParent(dummy1);
    heading3->setText("Treść heading3");

    NodeImage* image1 = new NodeImage();
    image1->setObjectName("image1");
    image1->setParent(dummy1);
    image1->setPath("D:/Tapety/pexels-errin-casano-2356045.jpg");

    NodeVideo* video1 = new NodeVideo();
    video1->setObjectName("video1");
    video1->setParent(dummy1);
    //video1->setPath("https://youtu.be/lWqJTKdznaM");
    video1->setPath("C:/Users/mhers/Downloads/sample_960x400_ocean_with_audio.mpeg");

/*
    NodeText* text2 = new NodeText();
    text2->setObjectName("Text2");
    text2->setParent(dummy1);

    NodeText* text3 = new NodeText();
    text3->setObjectName("Text3");
    text3->setParent(dummy1);

    NodeText* text4 = new NodeText();
    text4->setObjectName("Text4");
    text4->setParent(dummy1);

    NodeText* text5 = new NodeText();
    text5->setObjectName("Text5");
    text5->setParent(dummy1);
*/

    /*
    NodePropTest* event1 = new NodePropTest();
    event1->setObjectName("prop_test");
	event1->setParent(dummy1);

	NodeEvent* event2 = new NodeEvent();
	event2->setObjectName("event2");
	event2->setParent(dummy1);

	NodeEvent* event3 = new NodeEvent();
	event3->setObjectName("event3");
	event3->setParent(dummy1);
    */

    /*
	QList<NodeEvent*> events = Calendar::get()->getEvents(2022, 06, 16);

	for (NodeEvent* event : events) {
		qInfo() << "Event " << event->getStart();
	}
    */

    //Script::get()->init();
}

void Workspace::loadDefaultFile(QString _dir) {
	QDir di = QDir(_dir);

	if (!di.exists()) {
		qCritical() << "Workspace::init dir not exist";
		return;
	}

	dir = di;

	QString workscpace_file_name = dir.absoluteFilePath("workspace.xml");

	QFileInfo workspace_file(workscpace_file_name);

	if (!workspace_file.exists()) {
		qCritical() << "Workspace::init workspace file not exist";
		return;
	}

	pushInputFile("workspace.xml");
	loadTml(NULL);
}

void Workspace::loadTml(NodeBase* parent) {
	
	InputFile* inFile = getTopInputFile();

	QString node_name = inFile->current_node->getName();

	NodeBase* node = createNode(node_name);

	if (node == NULL) {
		qCritical() << "Workspace::loadTml can not create node : " << node_name;
		return;
	}
	else {

		if (parent) {
			node->setParent(parent);
		}
		else {
			root = node;
		}

		node->LoadTml(inFile->current_node);
	}

	if (inFile != getTopInputFile()) {
		loadTml(node);
		popInputFile();
	}
	else {
		TmlNode* tml_node = inFile->current_node;
		for (int i = 0; i < tml_node->getNumChilds(); i++) {
			TmlNode* child = tml_node->getChild(i);
			
			if ((child->getName().left(6) == "param_") || (child->getName().left(5) == "prop_")) {
			
			}
			else {
				inFile->current_node = child;
				loadTml(node);
			}
		}
	}
}

NodeBase* Workspace::createNode(QString& name) {
	NodeBase* result = NULL;

	if (name == "dummy") {
		result = new NodeBase();
	}
	else if (name == "include") {
		result = new NodeInclude();
	}
	else if (name == "var") {
		result = new NodeVar();
	}
	else if (name == "event") {
		result = new NodeEvent();
	}
	else if (name == "person") {
		result = new NodePerson();
	}
	else if (name == "project") {
		result = new NodeProject();
	}
	else if (name == "task") {
		result = new NodeTask();
	}
	else if (name == "document_file_type") {
		result = new NodeDocumentFileType();
	}
	else if (name == "ui") {
		result = new NodeUi();
	}
	else if (name == "qwidget") {
		result = new NodeQWidget();
	}
	else if (name == "qwindow") {
		result = new NodeQWindow();
	}
	else if (name == "qlabel") {
		result = new NodeQLabel();
	}
	else if (name == "qpushbutton") {
		result = new NodeQPushButton();
	}
	else if (name == "qtextedit") {
		result = new NodeQTextEdit();
	}

	return result;
}

void Workspace::setVar(const QString& name, const QString& value) {
	vars[name] = value;
}

QString Workspace::getVar(const QString& name) {
	if (vars.contains(name)) {
		return vars[name];
	}
	return "";
}

void Workspace::setTmlDef(const QString& name, TmlDef* tml_def) {
	tml_defs[name] = tml_def;
}

TmlDef* Workspace::getTmlDef(const QString& name) {
	if (tml_defs.contains(name)) {
		return tml_defs[name];
	}
	return NULL;
}

void Workspace::pushInputFile(QString relative_file_path) {
	
	QString file_name;

	if (inputFiles.size() == 0) {
		file_name = dir.absoluteFilePath(relative_file_path);
	}
	else {
		InputFile* in_file = getTopInputFile();
		QDir in_dir = in_file->file.dir();
		file_name = in_dir.absoluteFilePath(relative_file_path);
	}

	QFileInfo fi = QFileInfo(file_name);
	if (!fi.exists()) {
		qCritical() << "Workspace::pushInputFile file not exist";
		return;
	}

	TmlNode* root_node = new TmlNode();

	QString src;
	bool parse_error;
	int parse_error_line, parse_error_pos;

	if (QStringUtils::loadStringFromFileWindows(fi.absoluteFilePath(), src)) {
		TmlStringSource* source = new TmlStringSource(src);
		root_node->parse(source);
		parse_error = source->error;
		parse_error_line = source->error_line;
		parse_error_pos = source->error_pos;
		delete source;
	}
	else {
		qCritical() << "Workspace::pushInputFile file load error";
		return;
	}

	if (parse_error) {
		delete root_node;
		root_node = NULL;
		// todo change to file log message
		qCritical() << "Workspace::pushInputFile file parse error " << fi.absoluteFilePath() << " " << parse_error_line << " " << parse_error_pos;
		return;
	}

	InputFile* in_file = new InputFile();
	in_file->file = fi;
	in_file->root_node = root_node;
	in_file->current_node = root_node;

	inputFiles.append(in_file);
}

void Workspace::popInputFile() {
	if (inputFiles.size() > 0) {
		InputFile* ifile = inputFiles[inputFiles.size() - 1];
		delete ifile->root_node;
		ifile->current_node = NULL;
		ifile->root_node = NULL;
		delete ifile;
		inputFiles.remove(inputFiles.size() - 1);
	}
	else {
		qCritical() << "Workspace::popInputFile inputFiles.size() < 1";
	}
}

const char* Workspace::getCorrentInputFile() {
	if (inputFiles.size() == 0) {
		return "";
	}
	else {
		InputFile* ifile = inputFiles[inputFiles.size() - 1];
		return dir.relativeFilePath(ifile->file.absolutePath()).toLocal8Bit().data();
	}
}

