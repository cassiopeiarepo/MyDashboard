#include "TrivialMainWindow.h"

#include <QMenuBar>
#include <QTextEdit>
#include <QWidget>

#include "app/Gui/Views/TrivialDirExplorer.h"
#include "app/Gui/Views/TrivialDocumentsView.h"


TrivialMainWindow::TrivialMainWindow(QWidget* parent) {

	createActions();
	createPanels();

	dir_explorer = new TrivialDirExplorer();
	doc_view = new TrivialDocumentsView();

	addPanel(PanelPlace::LEFT, QString("Workspace"), dir_explorer);
	addPanel(PanelPlace::CENTER, QString("Documents"), doc_view);

}

TrivialMainWindow::~TrivialMainWindow() {
	
}

void TrivialMainWindow::createActions() {
	QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
	//QToolBar* fileToolBar = addToolBar(tr("File"));

		QAction* newAct = new QAction(tr("Nowy"), this);
		newAct->setShortcuts(QKeySequence::New);
		//newAct->setStatusTip(tr("Create a new file"));
		connect(newAct, &QAction::triggered, this, &TrivialMainWindow::fileNew);
		fileMenu->addAction(newAct);

		QAction* openAct = new QAction(tr("Otworz"), this);
		openAct->setShortcuts(QKeySequence::Open);
		//newAct->setStatusTip(tr("Create a new file"));
		connect(openAct, &QAction::triggered, this, &TrivialMainWindow::fileOpen);
		fileMenu->addAction(openAct);

		QAction* saveAct = new QAction(tr("Zapisz"), this);
		saveAct->setShortcuts(QKeySequence::Save);
		//newAct->setStatusTip(tr("Create a new file"));
		connect(saveAct, &QAction::triggered, this, &TrivialMainWindow::fileSave);
		fileMenu->addAction(saveAct);

		QAction* saveAsAct = new QAction(tr("Zapisz jako"), this);
		saveAsAct->setShortcuts(QKeySequence::SaveAs);
		//newAct->setStatusTip(tr("Create a new file"));
		connect(saveAsAct, &QAction::triggered, this, &TrivialMainWindow::fileSaveAs);
		fileMenu->addAction(saveAsAct);

		fileMenu->addSeparator();

		QAction* exitAct = new QAction(tr("Zakoncz"), this);
		exitAct->setShortcuts(QKeySequence::Quit);
		//newAct->setStatusTip(tr("Create a new file"));
		connect(exitAct, &QAction::triggered, this, &TrivialMainWindow::fileExit);
		fileMenu->addAction(exitAct);
}

void TrivialMainWindow::createStatusBar() {

}

void TrivialMainWindow::createPanels() {
	spliter1 = new QSplitter(this);
	spliter1->setOrientation(Qt::Vertical);
	spliter2 = new QSplitter(this);
	spliter2->setOrientation(Qt::Horizontal);

	spliter3 = new QSplitter(this);
	spliter3->setOrientation(Qt::Horizontal);

	panel_central = new CentralWidget();

	panels_left = new QTabWidget(this);
	panels_right = new QTabWidget(this);
	bottom_left = new QTabWidget(this);
	bottom_right = new QTabWidget(this);

	spliter1->addWidget(spliter2);

	spliter2->addWidget(panels_left);
	spliter2->addWidget(panel_central);
	spliter2->addWidget(panels_right);

	spliter1->addWidget(spliter3);

	spliter3->addWidget(bottom_left);
	spliter3->addWidget(bottom_right);

	setCentralWidget(spliter1);
}

void TrivialMainWindow::addPanel( PanelPlace place, QString& tab_caption, QWidget* pane) {
	switch (place) {
		case LEFT: panels_left->addTab(pane, tab_caption); break;
		case CENTER: { panel_central->setCentral(pane); break; }
		case RIGHT: panels_right->addTab(pane, tab_caption); break;
		case BOTTOM_LEFT: bottom_left->addTab(pane, tab_caption); break;
		case BOTTOM_RIGHT: bottom_right->addTab(pane, tab_caption); break;
	}
}

void TrivialMainWindow::fileNew() {
	doc_view->fileNew();
}

void TrivialMainWindow::fileOpen() {
	doc_view->fileOpen();
}

void TrivialMainWindow::fileSave() {
	doc_view->fileSave();
}

void TrivialMainWindow::fileSaveAs() {
	doc_view->fileSaveAs();
}

void TrivialMainWindow::fileExit() {

}


