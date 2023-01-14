#include "app/Gui/Views/TrivialMainView.h"


TrivialMainView::TrivialMainView(QWidget* parent, bool _vertical) : QWidget(parent), vertical(_vertical) {

	create_view(parent);
}

bool TrivialMainView::addTopMenu(const QString& name, const QString& icon, QWidget* widget) {
	TrivialMainViewItem* item = new TrivialMainViewItem(this, name, icon, widget);
	items.append(item);

	items_free();
	items_create();

	return true;
}

bool TrivialMainView::addSubMenu(const QString& top_name, const QString& name, QWidget* widget) {
	
	TrivialMainViewItem* top_item = getItem(top_name);
	if (top_item == NULL)
		return false;

	TrivialMainViewItem* sub_item = new TrivialMainViewItem(this, name, "", widget);
	top_item->submenu.append(sub_item);
	top_item->rebuildMenu();

	return true;
}

void TrivialMainView::create_view(QWidget* parent) {
	
	gridLayout = new QGridLayout(this);

	if (vertical) {
		horizontalLayout = new QHBoxLayout();
		verticalLayout = new QVBoxLayout();
		horizontalLayout->addLayout(verticalLayout);
		stacked_widget = new QStackedWidget(this);
		horizontalLayout->addWidget(stacked_widget);
		gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

	}
	else {
		verticalLayout = new QVBoxLayout();
		stacked_widget = new QStackedWidget(this);
		verticalLayout->addWidget(stacked_widget);
		horizontalLayout = new QHBoxLayout();
		verticalLayout->addLayout(horizontalLayout);
		gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);
	}
}

void TrivialMainView::items_create() {

	items_free();

	for (int i = 0; i < items.size(); i++) {
		items[i]->toolButton = new QToolButton(this);		
		items[i]->toolButton->setText(items[i]->name);

		if (vertical) {
			items[i]->toolButton->setMinimumSize(QSize(80, 0));
			items[i]->toolButton->setMaximumSize(QSize(80, 16777215));
			verticalLayout->addWidget(items[i]->toolButton);
		}
		else {

			QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
			sizePolicy1.setHorizontalStretch(0);
			sizePolicy1.setVerticalStretch(0);
			sizePolicy1.setHeightForWidth(items[i]->toolButton->sizePolicy().hasHeightForWidth());
			items[i]->toolButton->setSizePolicy(sizePolicy1);

			horizontalLayout->addWidget(items[i]->toolButton);
		}

		QIcon _icon;
		_icon.addFile(items[i]->icon, QSize(), QIcon::Normal, QIcon::Off);
		items[i]->toolButton->setIcon(_icon);
		items[i]->toolButton->setIconSize(QSize(24, 24));
		items[i]->toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


		if (items[i]->widget)
			stacked_widget->addWidget(items[i]->widget);

		connect(items[i]->toolButton, &QToolButton::released, items[i], &TrivialMainViewItem::released);
	}

	if (vertical) {
		verticalLayout->setAlignment(Qt::AlignTop);
	}
	else {
		//horizontalLayout->addStretch();
	}

	

}

void TrivialMainView::items_free() {
	for (int i = 0; i < items.size(); i++) {
		if (items[i]->toolButton) {
			delete items[i]->toolButton;
			items[i]->toolButton = NULL;
		}

		if (items[i]->widget)
			stacked_widget->removeWidget(items[i]->widget);
	}
}

TrivialMainViewItem* TrivialMainView::getItem(const QString& name) {

	for (int i = 0; i < items.size(); i++) {
		if (items[i]->name == name)
			return items[i];
	}

	return NULL;
}

void TrivialMainView::select(const QString& item, const QString& submenu) {
	TrivialMainViewItem* next_item = getItem(item);

	if (next_item == NULL)
		return;

	TrivialMainViewItem* prev_item = getItem(slected_item);

	if (prev_item == next_item)
		return;

	if (next_item && next_item->widget) {
		stacked_widget->setCurrentWidget(next_item->widget);
	}

	slected_item = item;
}


void TrivialMainViewItem::released() {
	if (this->submenu.size() > 0) {
		QPoint popup_pos = toolButton->mapToGlobal(QPoint(0, 0));

		if (main_view->IsVertical()) {
			popup_pos += QPoint(toolButton->width(), 0);
		}
		else {
			popup_pos -= QPoint(0, this->menu->sizeHint().height());
		}
		this->menu->exec(popup_pos);
	}
	else {
		main_view->select(this->name, "");
	}
}