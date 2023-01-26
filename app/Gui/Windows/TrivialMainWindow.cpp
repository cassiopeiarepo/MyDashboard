#include "TrivialMainWindow.h"

#include <QMenuBar>
#include <QTextEdit>
#include <QWidget>
#include <QResizeEvent>


#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>


#include <QtWidgets/QToolButton>

#include <QtWidgets/QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QLineEdit>

#include "app/Gui/Views/TrivialDirExplorer.h"
#include "app/Gui/Views/TrivialDocumentsView.h"
#include "app/Gui/Views/TrivialScriptView.h"
#include "app/Gui/Views/TrivialLogView.h"
#include "app/Gui/Views/TrivialSceneView.h"
#include "app/Gui/Views/TrivialSceneTreeView.h"
#include "app/Gui/Views/TrivialMainView.h"

#include "app/Utils/Log.h"
#include "app/Utils/Gui.h"
#include "app/Utils/Workspace.h"


TrivialMainWindow::TrivialMainWindow(QWidget* parent) {
	resize(360, 747); // telefon
	//resize(1333, 716); //tablet

    Gui::get()->setMainWindow(this);
    Gui::get()->updateSize(width(), height());

    createGui();

}


TrivialMainWindow::~TrivialMainWindow() {
	
}

void TrivialMainWindow::createGui() {

	log_view = new TrivialLogView();

    /*
	if (Gui::get()->isDesktop()) {
		
		dir_explorer = new TrivialDirExplorer();
		doc_view = TrivialDocumentsView::get();
		script_view = new TrivialScriptView();
	}
    */

    centralwidget = new QWidget(this);
    centralwidget->setObjectName("centralwidget");
    this->setCentralWidget(centralwidget);


    if (Gui::get()->getSize() == Gui::GUI_MINI) {

        scene_view_complex = new TrivialSceneComplexView(NULL);
        scene_tree_view = new TrivialSceneTreeView(NULL);
        QObject::connect(scene_tree_view, &TrivialSceneTreeView::selected, scene_view_complex, &TrivialSceneComplexView::select);

		main_view = new TrivialMainView(centralwidget, false);
        main_view->addTopMenu("Tree", ":/icons/ui/icons/home_FILL0_wght400_GRAD0_opsz48.png", scene_tree_view);
        main_view->addTopMenu(QString("Scene"),":/icons/ui/icons/home_FILL0_wght400_GRAD0_opsz48.png",  scene_view_complex);
		main_view->addTopMenu(QString("Windows"), ":/icons/ui/icons/home_FILL0_wght400_GRAD0_opsz48.png", NULL);
		main_view->addSubMenu("Windows", "Sub1", NULL);
		main_view->addTopMenu(QString("Log"), ":/icons/ui/icons/home_FILL0_wght400_GRAD0_opsz48.png",  log_view);

		Gui::get()->addChildWidgetAndFillInGrid(centralwidget, main_view);

		main_view->select("Log", "");

    }

    /*else if (Gui::get()->getSize() == Gui::GUI_MIDI) {
		ui_main_menu_midi.setupUi(centralwidget);
    } else if (Gui::get()->getSize() == Gui::GUI_MAXI && Gui::get()->isDesktop()) {

        createDesktopActions();
        createDesktopPanels();

        addPanel(PanelPlace::LEFT, QString("Workspace"), dir_explorer);
        addPanel(PanelPlace::CENTER, QString("Documents"), doc_view);
        addPanel(PanelPlace::BOTTOM_LEFT, QString("Script"), script_view);
        addPanel(PanelPlace::BOTTOM_RIGHT, QString("Log"), log_view);
    }
    */
}

void TrivialMainWindow::updateGui() {
    /*
	if (Gui::get()->getSize() != Gui::get()->getPrevSize()) {
		deleteCentralWidgetChilds();

		if (Gui::get()->getSize() == Gui::GUI_MINI) {
			ui_main_menu_mini.setupUi(centralwidget);
		}
		else if (Gui::get()->getSize() == Gui::GUI_MIDI) {
			ui_main_menu_midi.setupUi(centralwidget);
		}
		else if (Gui::get()->getSize() == Gui::GUI_MAXI && Gui::get()->isDesktop()) {

			createDesktopActions();
			createDesktopPanels();

			addPanel(PanelPlace::LEFT, QString("Workspace"), dir_explorer);
			addPanel(PanelPlace::CENTER, QString("Documents"), doc_view);
			addPanel(PanelPlace::BOTTOM_LEFT, QString("Script"), script_view);
			addPanel(PanelPlace::BOTTOM_RIGHT, QString("Log"), log_view);		
		}
	}
        */

}

void TrivialMainWindow::init() {
    scene_tree_view->setRoot(Workspace::get()->getRoot());
}

void TrivialMainWindow::deleteCentralWidgetChilds() {
	QObjectList obj_list = centralwidget->children();

	for (int i = obj_list.size() - 1; i >= 0; i--) {
		delete obj_list[i];
	}
}

void TrivialMainWindow::createMiniMenu() {
    //miniGridLayout = new QGridLayout(this);
    //miniGridLayout->setObjectName("gridLayout");

    //miniVerticalLayout = new QVBoxLayout();
    //miniVerticalLayout->setObjectName("verticalLayout");
    //miniTextEdit = new QTextEdit(this);
    //miniTextEdit->setObjectName("textEdit");

    /*
    miniVerticalLayout->addWidget(miniTextEdit);

    miniHorizontalLayout = new QHBoxLayout();
    miniHorizontalLayout->setSpacing(6);
    miniHorizontalLayout->setObjectName("horizontalLayout");
    miniHorizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    miniToolButton_2 = new QToolButton(this);
    miniToolButton_2->setObjectName("toolButton_2");
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/icons/ui/icons/home_FILL0_wght400_GRAD0_opsz48.png"), QSize(), QIcon::Normal, QIcon::Off);
    miniToolButton_2->setIcon(icon);
    miniToolButton_2->setIconSize(QSize(32, 32));
    miniToolButton_2->setToolButtonStyle(Qt::ToolButtonIconOnly);
    miniToolButton_2->setAutoRaise(false);

    miniHorizontalLayout->addWidget(miniToolButton_2);

    miniToolButton_3 = new QToolButton(this);
    miniToolButton_3->setObjectName("toolButton_3");
    miniToolButton_3->setMinimumSize(QSize(0, 0));
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/icons/ui/icons/menu_FILL0_wght400_GRAD0_opsz48.png"), QSize(), QIcon::Normal, QIcon::Off);
    miniToolButton_3->setIcon(icon1);
    miniToolButton_3->setIconSize(QSize(32, 32));

    miniHorizontalLayout->addWidget(miniToolButton_3);

    miniToolButton = new QToolButton(this);
    miniToolButton->setObjectName("toolButton");
    QIcon icon2;
    icon2.addFile(QString::fromUtf8(":/icons/ui/icons/add_FILL0_wght400_GRAD0_opsz48.png"), QSize(), QIcon::Normal, QIcon::Off);
    miniToolButton->setIcon(icon2);
    miniToolButton->setIconSize(QSize(32, 32));

    miniHorizontalLayout->addWidget(miniToolButton);


    miniVerticalLayout->addLayout(miniHorizontalLayout);


    miniGridLayout->addLayout(miniVerticalLayout, 0, 0, 1, 1);

    */

    //setLayout(miniGridLayout);

	/*
    QWidget *scrollAreaContent = new QWidget;

    QLineEdit* edit1 = new QLineEdit(scrollAreaContent);
    edit1->resize(200, 200);
    edit1->move(100, 100);

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {width: 20px;}");

    scrollArea->setWidget(scrollAreaContent);

    QVBoxLayout *scrollLayout = new QVBoxLayout;
    scrollLayout->setContentsMargins(0,0,0,0);
    scrollLayout->addWidget(scrollArea);

    setLayout(scrollLayout);
	*/
}


void TrivialMainWindow::createDesktopActions() {
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

void TrivialMainWindow::createDesktopStatusBar() {

}

void TrivialMainWindow::createDesktopPanels() {
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

void TrivialMainWindow::addPanel( PanelPlace place, const QString& tab_caption, QWidget* pane) {
	switch (place) {
		case LEFT: panels_left->addTab(pane, tab_caption); break;
		case CENTER: { panel_central->setCentral(pane); break; }
		case RIGHT: panels_right->addTab(pane, tab_caption); break;
		case BOTTOM_LEFT: bottom_left->addTab(pane, tab_caption); break;
		case BOTTOM_RIGHT: bottom_right->addTab(pane, tab_caption); break;
    }
}

void TrivialMainWindow::resizeEvent(QResizeEvent *event)
{
    Gui::get()->updateSize(event->size().width(), event->size().height());
    QWidget::resizeEvent(event);
    updateTitle();
	updateGui();
}

void TrivialMainWindow::moveEvent(QMoveEvent* event) {
	Gui::get()->updateGlobalPos(event->pos());
	QWidget::moveEvent(event);
}

void TrivialMainWindow::updateTitle() {
    QString title = QString("MyDashboard w:%1 h:%2 ").arg(width()).arg(height());
    setWindowTitle(title);
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


