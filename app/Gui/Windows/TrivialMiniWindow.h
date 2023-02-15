#ifndef TRIVIAL_MINI_WINDOW_H
#define TRIVIAL_MINI_WINDOW_H

#include <QDialog>
#include "app/Gui/Widgets/TrivialQObjectPropertyWidget.h"
#include "app/Utils/Gui.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

class TrivialMiniWindow : public QDialog {

    Q_OBJECT
public:
    TrivialMiniWindow(QWidget* parent) : QDialog(parent) {
        setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        setAttribute(Qt::WA_DeleteOnClose);

        int w = Gui::get()->getWidth();
        int h = Gui::get()->getHeight();
        QPoint win_pos = Gui::get()->getGloabalPos();
        QRect geom(win_pos.x(), win_pos.y(), w, h);
        this->setGeometry(geom);

        gridLayout = new QGridLayout(this);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        horizontalLayout = new QHBoxLayout();
        label = new QLabel(this);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        toolButton = new QToolButton(this);
        toolButton->setText("Close");
        connect(toolButton, &QAbstractButton::pressed, this, &TrivialMiniWindow::closePressed);

        horizontalLayout->addWidget(toolButton);

        verticalLayout->addLayout(horizontalLayout);

        widget = new QWidget(this);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(widget);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

    }

    ~TrivialMiniWindow() {
    }

    QWidget* getClient() { return widget; }

    void setCaption(const QString& txt) { label->setText(txt); }


 protected slots:
    void closePressed() { this->close(); }

 private:

    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QToolButton *toolButton;
    QWidget *widget;

};


#endif
