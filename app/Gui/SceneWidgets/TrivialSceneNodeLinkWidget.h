#ifndef TRIVIAL_SCENE_NODE_LINK_WIDGET_H
#define TRIVIAL_SCENE_NODE_LINK_WIDGET_H

#include "app/Utils/SceneUtils.h"
#include "app/Gui/SceneWidgets/ITrivialSceneWidget.h"
#include "app/Nodes/Basic/NodeLink.h"



#include <QTextEdit>
#include <QAbstractTextDocumentLayout>

class TrivialSceneNodeLinkWidget : public QTextEdit, public ITrivialSceneWidget {
    Q_OBJECT

public:
    TrivialSceneNodeLinkWidget(QWidget* parent = NULL) : QTextEdit(parent) {

        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        //setStyleSheet("QTextEdit { margin: 0px; }");

        setReadOnly(true);

        QObject::connect(this, &QTextEdit::textChanged, this, &TrivialSceneNodeLinkWidget::OnTextChanged);

        //QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        //setSizePolicy(sizePolicy);

        QObject::connect(document()->documentLayout(), &QAbstractTextDocumentLayout::update, [&]() {
                //qDebug() << "Wysokość dokumentu: " << document()->documentLayout()->documentSize().height();
                updateSize();
            });

    }

    void setObject(NodeBase* obj) override {
        object = obj;
        text_link = qobject_cast<NodeLink*>(obj);
        if (text_link) {
            //this->setMarkdown(text_node->getText());
            if (text_link->getNode()) {
                setText(SceneUtils::getNodePath(text_link->getNode()));
            }
        }
        //update();
    }

    NodeBase* getObject() override { return object; }

    void setTrivialSceneItemWidget(TrivialSceneItemWidget* _scene_item_widget) override { scene_item_widget = _scene_item_widget; }

    void init() override {
        //updateSize();
    }

    void mousePressEvent(QMouseEvent *e) override {
        if (text_link->getNode()) {
            scene_item_widget->getSceneWidget()->select(text_link->getNode());
        }
    }

protected:
    void OnTextChanged() {
        //if (text_node) {
        //    text_node->setText(this->toMarkdown());
        //}
        //updateSize();
    }

    void updateSize() {
        QSize current_size = size();

        QTextDocument* document = this->document();
        QAbstractTextDocumentLayout* layout = document->documentLayout();
        QSizeF size = layout->documentSize();
        QSize s(size.width(), size.height());

        QSize new_size = QSize(current_size.width(), s.height() + 6);

        qDebug() << "updateSize: " << new_size;

        resize(new_size);

        if (scene_item_widget) {
            scene_item_widget->updateSize(new_size);
        }

    }

private:
    NodeBase* object;
    NodeLink* text_link;
    TrivialSceneItemWidget* scene_item_widget;
};

#endif
