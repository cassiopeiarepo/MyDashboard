#ifndef TRIVIAL_SCENE_VIEW_H
#define TRIVIAL_SCENE_VIEW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QToolButton>
#include <QCoreApplication>
#include <QTextEdit>
#include <QScrollArea>
#include <QTimer>

#include "app/Utils/Workspace.h"

class TrivialSceneWidget;
class TrivialSceneComplexView;

class ObjectNameLabel : public QLabel {
    Q_OBJECT
 public:
    ObjectNameLabel(QWidget* parent) : QLabel(parent) { }

    void mousePressEvent(QMouseEvent *event) override {
        QTimer::singleShot(1, this, &ObjectNameLabel::onTimer);
        QLabel::mousePressEvent(event);
    }

signals:
    void onMousePress();

public slots:
    void onTimer() {
        emit onMousePress();
    }
};


class TrivialSceneItemWidget : public QWidget {
	Q_OBJECT

public:
    TrivialSceneItemWidget(TrivialSceneWidget* _scene_widget, NodeBase* obj);
    ~TrivialSceneItemWidget();
	NodeBase* getObject() { return object; }

	void update();

    void resizeEvent(QResizeEvent* event) override;

    void setShowHeaders(bool show_headers);

public slots:
    void onObjectNamePressed();

    void aboutTiHideOptionsMenu();
    void recreateOptionsMenu();

private:
    NodeBase* object;
    TrivialSceneWidget* scene_widget;

    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButton_3;
    ObjectNameLabel *label_2;
    QTextEdit *textEdit;

	void createWidget();
	void updateSize();

    QMenu* optionsMenu;
    void createOptionsMenu();

};


class TrivialSceneWidget : public QWidget {
	Q_OBJECT

public:
    TrivialSceneWidget(QWidget* parent, int _clientWidth);

    NodeBase* getObject() { return selected; }
    void setObject(NodeBase* sel) {
        selected = sel; rebuildChilds();
    }

    bool getShowHeaders() { return show_headers; }
    void setShowHeaders(bool _show_headers);

    int getClientWidth() { return clientWidth; }

    void resizeEvent(QResizeEvent* event) override {
        //rebuildChilds();
    }

    void select(NodeBase* object);

signals:
    void goChild(NodeBase* child);


private:
    NodeBase* selected;
    bool show_headers;

    QList<TrivialSceneItemWidget*> items;

    QGridLayout *gridLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;

    QWidget* expand_widget;

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
        gridLayout->setContentsMargins(0, 0, 0, 0);
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
    void onGoChild(NodeBase* child);

    void aboutTiHideOptionsMenu();
    void recreateOptionsMenu();

    void optionsShowHeadersTriggered(bool checked);
private:
    Ui_SceneViewComplex scene_view_complex;
    TrivialSceneWidget* scene_widget;

    QMenu* optionsMenu;
    void createWidget();
    void createOptionsMenu();
};


#endif
