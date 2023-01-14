#ifndef TRIVIAL_SCENE_VIEW_H
#define TRIVIAL_SCENE_VIEW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QToolButton>
#include <QCoreApplication>

#include "app/Utils/Workspace.h"

class TrivialSceneItemWidget : public QWidget {
	Q_OBJECT

public:
    TrivialSceneItemWidget(QWidget* parent, NodeBase* obj);
    ~TrivialSceneItemWidget();
	NodeBase* getObject() { return object; }

	void update();

	void resizeEvent(QResizeEvent* event);

private:
    NodeBase* object;


	QLabel* name_label;
	void createWidget();
	void updateSize();

};


class TrivialSceneWidget : public QWidget {
	Q_OBJECT

public:
    TrivialSceneWidget(QWidget* parent, int _clientWidth);

    NodeBase* getObject() { return selected; }
    void setObject(NodeBase* sel) {
        selected = sel; rebuildChilds();
    }

    int getClientWidth() { return clientWidth; }

private:
    NodeBase* selected;
	QVBoxLayout* verticalLayout;
    QList<TrivialSceneItemWidget*> items;
    int clientWidth;

	void createWidget();

	void rebuildChilds();

};

class Ui_SceneViewComplex
{
public:
    QGridLayout* gridLayout;
    QVBoxLayout* verticalLayout;
    QHBoxLayout* horizontalLayout;
    QLabel* label;
    QToolButton* toolButton_2;
    QToolButton* toolButton;
    QWidget* widget;

    void setupUi(QWidget* SceneViewComplex)
    {
        if (SceneViewComplex->objectName().isEmpty())
            SceneViewComplex->setObjectName("SceneViewComplex");
        SceneViewComplex->resize(400, 300);
        gridLayout = new QGridLayout(SceneViewComplex);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(SceneViewComplex);
        label->setObjectName("label");
        label->setTextFormat(Qt::PlainText);

        horizontalLayout->addWidget(label);

        toolButton_2 = new QToolButton(SceneViewComplex);
        toolButton_2->setObjectName("toolButton_2");

        horizontalLayout->addWidget(toolButton_2);

        toolButton = new QToolButton(SceneViewComplex);
        toolButton->setObjectName("toolButton");

        horizontalLayout->addWidget(toolButton);


        verticalLayout->addLayout(horizontalLayout);

        widget = new QWidget(SceneViewComplex);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(widget);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(SceneViewComplex);

        QMetaObject::connectSlotsByName(SceneViewComplex);
    } // setupUi

    void retranslateUi(QWidget* SceneViewComplex)
    {
        SceneViewComplex->setWindowTitle(QCoreApplication::translate("SceneViewComplex", "Form", nullptr));
        label->setText(QString());
        toolButton_2->setText(QCoreApplication::translate("SceneViewComplex", "Up", nullptr));
        toolButton->setText(QCoreApplication::translate("SceneViewComplex", "...", nullptr));
    } // retranslateUi

};



class TrivialSceneComplexView : public QWidget {
	Q_OBJECT
public:
    TrivialSceneComplexView(QWidget* parent);

public slots:
    void select(QObject* obj);

    void onUp();

private:
    Ui_SceneViewComplex scene_view_complex;
    TrivialSceneWidget* scene_widget;

    void createWidget();
};


#endif
