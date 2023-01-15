#ifndef _TRIVIAL_MAINWINDOW_H
#define _TRIVIAL_MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QTabWidget>
#include <QTimer>
#include <QHostAddress>

#include <QtWidgets/QTextEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

//#include <qmqtt.h>

class TrivialDirExplorer;
class TrivialDocumentsView;
class CentralWidget;
class TrivialScriptView;
class TrivialLogView;
class TrivialSceneComplexView;
class TrivialSceneTreeView;
class TrivialMainView;

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>


class Ui_MainMenuMini
{
public:
    QGridLayout* gridLayout;
    QVBoxLayout* verticalLayout;
    QWidget* child_widget_placeholder;
    QHBoxLayout* horizontalLayout;
    QToolButton* toolButton_2;
    QToolButton* toolButton_3;
    QToolButton* toolButton;

    void setupUi(QWidget* MainMenuMini)
    {
        if (MainMenuMini->objectName().isEmpty())
            MainMenuMini->setObjectName("MainMenuMini");
        MainMenuMini->resize(364, 497);
        gridLayout = new QGridLayout(MainMenuMini);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        child_widget_placeholder = new QWidget(MainMenuMini);
        child_widget_placeholder->setObjectName("child_widget_placeholder");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(child_widget_placeholder->sizePolicy().hasHeightForWidth());
        child_widget_placeholder->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(child_widget_placeholder);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        toolButton_2 = new QToolButton(MainMenuMini);
        toolButton_2->setObjectName("toolButton_2");
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(toolButton_2->sizePolicy().hasHeightForWidth());
        toolButton_2->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(toolButton_2);

        toolButton_3 = new QToolButton(MainMenuMini);
        toolButton_3->setObjectName("toolButton_3");
        sizePolicy1.setHeightForWidth(toolButton_3->sizePolicy().hasHeightForWidth());
        toolButton_3->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(toolButton_3);

        toolButton = new QToolButton(MainMenuMini);
        toolButton->setObjectName("toolButton");
        sizePolicy1.setHeightForWidth(toolButton->sizePolicy().hasHeightForWidth());
        toolButton->setSizePolicy(sizePolicy1);
        toolButton->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(toolButton);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(MainMenuMini);

        QMetaObject::connectSlotsByName(MainMenuMini);
    } // setupUi

    void retranslateUi(QWidget* MainMenuMini)
    {
        MainMenuMini->setWindowTitle(QCoreApplication::translate("MainMenuMini", "Form", nullptr));
        toolButton_2->setText(QCoreApplication::translate("MainMenuMini", "Scene", nullptr));
        toolButton_3->setText(QCoreApplication::translate("MainMenuMini", "...", nullptr));
        toolButton->setText(QCoreApplication::translate("MainMenuMini", "Log", nullptr));
    } // retranslateUi

};




class Ui_MainMenuMidi
{
public:
    QGridLayout* gridLayout;
    QHBoxLayout* horizontalLayout;
    QVBoxLayout* verticalLayout_2;
    QToolButton* toolButton_4;
    QToolButton* toolButton_3;
    QToolButton* toolButton_2;
    QToolButton* toolButton;
    QVBoxLayout* verticalLayout;
    QTextEdit* textEdit;

    void setupUi(QWidget* MainMenuMidi)
    {
        if (MainMenuMidi->objectName().isEmpty())
            MainMenuMidi->setObjectName("MainMenuMidi");
        MainMenuMidi->resize(637, 594);
        gridLayout = new QGridLayout(MainMenuMidi);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        toolButton_4 = new QToolButton(MainMenuMidi);
        toolButton_4->setObjectName("toolButton_4");

        verticalLayout_2->addWidget(toolButton_4);

        toolButton_3 = new QToolButton(MainMenuMidi);
        toolButton_3->setObjectName("toolButton_3");

        verticalLayout_2->addWidget(toolButton_3);

        toolButton_2 = new QToolButton(MainMenuMidi);
        toolButton_2->setObjectName("toolButton_2");

        verticalLayout_2->addWidget(toolButton_2);

        toolButton = new QToolButton(MainMenuMidi);
        toolButton->setObjectName("toolButton");

        verticalLayout_2->addWidget(toolButton);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        textEdit = new QTextEdit(MainMenuMidi);
        textEdit->setObjectName("textEdit");

        verticalLayout->addWidget(textEdit);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(MainMenuMidi);

        QMetaObject::connectSlotsByName(MainMenuMidi);
    } // setupUi

    void retranslateUi(QWidget* MainMenuMidi)
    {
        MainMenuMidi->setWindowTitle(QCoreApplication::translate("MainMenuMidi", "Form", nullptr));
        toolButton_4->setText(QCoreApplication::translate("MainMenuMidi", "Home", nullptr));
        toolButton_3->setText(QCoreApplication::translate("MainMenuMidi", "Scene", nullptr));
        toolButton_2->setText(QCoreApplication::translate("MainMenuMidi", "...", nullptr));
        toolButton->setText(QCoreApplication::translate("MainMenuMidi", "...", nullptr));
    } // retranslateUi

};

class TrivialMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    TrivialMainWindow(QWidget* parent = nullptr);
    ~TrivialMainWindow();

    enum PanelPlace {
        LEFT, CENTER, RIGHT,
        BOTTOM_LEFT, BOTTOM_RIGHT
    };

    void addPanel(PanelPlace place, const QString& tab_caption, QWidget* panel);

    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent* event) override;
    void init();

private slots:
    void fileNew();
    void fileOpen();
    void fileSave();
    void fileSaveAs();
    void fileExit();

private:
    void createGui();
    void updateGui();

    void createMiniMenu();

    void createDesktopActions();
    void createDesktopStatusBar();
    void createDesktopPanels();

    void deleteCentralWidgetChilds();

    void updateTitle();

    QGridLayout *miniGridLayout;
    QVBoxLayout *miniVerticalLayout;
    QTextEdit   *miniTextEdit;
    QHBoxLayout *miniHorizontalLayout;
    QToolButton *miniToolButton_2;
    QToolButton *miniToolButton_3;
    QToolButton *miniToolButton;

    QSplitter* spliter1;
    QSplitter* spliter2;
    QSplitter* spliter3;

    QTabWidget* panels_left;
    QTabWidget* panels_right;
    QTabWidget* bottom_left;
    QTabWidget* bottom_right;
    CentralWidget* panel_central;

    TrivialDirExplorer* dir_explorer;
    TrivialDocumentsView* doc_view;
    TrivialScriptView* script_view;
    TrivialLogView* log_view;
    TrivialSceneComplexView* scene_view_complex;
    TrivialSceneTreeView* scene_tree_view;
    TrivialMainView* main_view;

    //Publisher* publisher;
    //MonoPlugin* mono;

    QWidget* centralwidget;

    Ui_MainMenuMini ui_main_menu_mini;
    Ui_MainMenuMidi ui_main_menu_midi;
};


class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    CentralWidget() : central(NULL) {
    
    }

    void setCentral(QWidget* wid) {
        if (central) {
            central->setParent(NULL);
            delete central;
            central = NULL;
        }

        if (wid) {
            wid->setParent(this);
            central = wid;
        }
    }

    void resizeEvent(QResizeEvent* event) override {
        if (central) {
            central->resize(size());
        }
    }

private:
    QWidget* central;
};

#endif // _TRIVIAL_MAINWINDOW_H
