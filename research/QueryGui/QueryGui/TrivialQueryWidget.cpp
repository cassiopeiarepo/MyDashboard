#include "TrivialQueryWidget.h"

void addChildWidgetAndFillInGrid(QWidget* parent, QWidget* child) {
    QGridLayout* gridLayout_3 = new QGridLayout(parent);
    gridLayout_3->setObjectName(child->objectName() + "_fill_grid");
    child->setParent(parent);
    gridLayout_3->addWidget(child, 0, 0, 1, 1);
    gridLayout_3->setContentsMargins(0, 0, 0, 0);
}


TrivaialQueryItemWidget::TrivaialQueryItemWidget(QWidget *parent) : QWidget(parent){
    createWidget();
}

void TrivaialQueryItemWidget::createWidget() {

    gridLayout = new QGridLayout(this);

    horizontalLayout = new QHBoxLayout();

    toolButton = new QToolButton(this);
    toolButton->setPopupMode(QToolButton::DelayedPopup);
    toolButton->setToolButtonStyle(Qt::ToolButtonTextOnly);
    toolButton->setText("And");
    horizontalLayout->addWidget(toolButton);

    label = new QLabel(this);
    label->setText("Name contains");
    horizontalLayout->addWidget(label);

    lineEdit = new QLineEdit(this);
    horizontalLayout->addWidget(lineEdit);

    gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

    gridLayout->setContentsMargins(0, 0, 0, 0);

}


TrivialQueryWidget::TrivialQueryWidget(QWidget *parent)
    : QWidget{parent}
{

    createWidget(parent);

}


void TrivialQueryWidget::createWidget(QWidget* parent) {

    gridLayout = new QGridLayout(this);

    verticalLayout = new QVBoxLayout();

    toolButton = new QToolButton(this);
    toolButton->setText("+");

    connect(toolButton, &QAbstractButton::pressed, this, &TrivialQueryWidget::onAddPressed);

    verticalLayout->addWidget(toolButton);
    gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);
    gridLayout->setContentsMargins(0, 0, 0, 0);
}


void TrivialQueryWidget::addItem() {
    removeWidgets();
    items.append(new TrivaialQueryItemWidget(this));
    addWidgets();
}

void TrivialQueryWidget::removeWidgets() {
    for (int i =0 ;i < items.size(); i++) {
        verticalLayout->removeWidget(items[i]);
    }

    verticalLayout->removeWidget(toolButton);
}

void TrivialQueryWidget::addWidgets() {

    for (int i =0 ;i < items.size(); i++) {
        verticalLayout->addWidget(items[i]);
    }

    verticalLayout->addWidget(toolButton);

}

void TrivialQueryWidget::onAddPressed() {
    addItem();
}

