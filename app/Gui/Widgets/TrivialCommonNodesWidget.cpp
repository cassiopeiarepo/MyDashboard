#include "app/Gui/Widgets/TrivialCommonNodesWidget.h"

TrivialCommonNodesWidget::TrivialCommonNodesWidget(QWidget* parent) : QWidget(parent){

    createWidget();
}

void TrivialCommonNodesWidget::createWidget() {

    gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(8, 8, 8, 8);

    label = new QLabel(this);
    label->setObjectName("label");
    label->setText("Basisc");
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    label->setSizePolicy(sizePolicy);
    gridLayout->addWidget(label, 0, 0, 1, 1);

    createButton("NodeText", 1, 0); createButton("NodeHeading1", 1, 1);
    createButton("NodeHeading2", 2, 0); createButton("NodeHeading3", 2, 1);
    createButton("NodeLink", 3, 0);

    label2 = new QLabel(this);
    label2->setObjectName("label");
    label2->setText("Media");
    QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
    label2->setSizePolicy(sizePolicy2);
    gridLayout->addWidget(label2, 4, 0, 1, 1);

    createButton("NodeImage", 5, 0); createButton("NodeVideo", 5, 1);
    createButton("NodeAudio", 6, 0);

    fill_widget = new QWidget(this);
    QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
    fill_widget->setSizePolicy(sizePolicy3);
    gridLayout->addWidget(fill_widget, 7, 0, 1, 1);
}

void TrivialCommonNodesWidget::createButton(const QString& nodeTypeName, int row, int column) {
    QPushButton* pushButton = new QPushButton(this);
    pushButton->setObjectName(nodeTypeName);
    pushButton->setText(nodeTypeName);

    gridLayout->addWidget(pushButton, row, column, 1, 1);
}
