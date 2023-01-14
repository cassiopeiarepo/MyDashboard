#ifndef TRIVIAL_MAIN_VIEW_H
#define TRIVIAL_MAIN_VIEW_H

#include <QWidget>
#include <QList>
#include <QGridLayout>
#include <QTextEdit>
#include <QToolButton>
#include <QStackedWidget>
#include <QMenu>

class TrivialMainView;


class TrivialMainViewItem : public QObject {
	Q_OBJECT
public:
	TrivialMainViewItem(TrivialMainView* _main_view, const QString& _name, const QString& _icon, QWidget* _widget) : main_view(_main_view), name(_name), icon(_icon),widget(_widget), toolButton(NULL), menu(NULL) {}

	TrivialMainView* main_view;
	QString name;
	QString icon;
	QWidget* widget;
	QList<TrivialMainViewItem*> submenu;
	QToolButton* toolButton;
	
	QMenu* menu;

	void rebuildMenu() {
		if (menu)
			delete menu;

		menu = new QMenu();

		for (int i = 0; i < submenu.size(); i++) {
			QAction* action1 = new QAction(submenu[i]->name, menu);
			menu->addAction(action1);
		}
	}


public slots:
	void released();
};

class TrivialMainView : public QWidget {
	Q_OBJECT
public:

	TrivialMainView(QWidget* parent, bool _vertical);

	bool addTopMenu(const QString &name, const QString& icon, QWidget* widget);
	bool addSubMenu(const QString& top_name, const QString& name, QWidget* widget);

	void select(const QString& item, const QString& submenu);

	bool IsVertical() { return vertical; }

private:

	void create_view(QWidget* parent);

	void items_create();
	void items_free();

	TrivialMainViewItem* getItem(const QString& name);

	bool vertical;
	QList<TrivialMainViewItem*> items;
	QString slected_item;
	QString selected_submanu;

	QGridLayout* gridLayout;
	//QTextEdit* edit;
	QStackedWidget* stacked_widget;

	QVBoxLayout* verticalLayout;
	QHBoxLayout* horizontalLayout;
	QToolButton* toolButton_2;

};


#endif
