#ifndef TRIVIAL_SCENE_NODE_HEADING2_WIDGET_H
#define TRIVIAL_SCENE_NODE_HEADING2_WIDGET_H

#include "app/Gui/SceneWidgets/ITrivialSceneWidget.h"
#include "app/Nodes/Basic/NodeHeading2.h"

#include <QTextEdit>
#include <QAbstractTextDocumentLayout>
#include <QMimeData>

class TrivialSceneNodeHeading2Widget : public QTextEdit, public ITrivialSceneWidget {
    Q_OBJECT

public:
    TrivialSceneNodeHeading2Widget(QWidget* parent = NULL) : QTextEdit(parent) {

        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        setFrameStyle(0);
        setFrameShape(QFrame::NoFrame);

        QObject::connect(this, &QTextEdit::textChanged, this, &TrivialSceneNodeHeading2Widget::OnTextChanged);

        QObject::connect(document()->documentLayout(), &QAbstractTextDocumentLayout::update, [&]() {
                //qDebug() << "Wysokość dokumentu: " << document()->documentLayout()->documentSize().height();
                updateSize();
            });

    }

    void setObject(NodeBase* obj) override {
        object = obj;
        heading_node = qobject_cast<NodeHeading2*>(obj);
        if (heading_node) {
            this->setMarkdown("## " + heading_node->getText());
        }
    }

    NodeBase* getObject() override { return object; }

    void setTrivialSceneItemWidget(TrivialSceneItemWidget* _scene_item_widget) override { scene_item_widget = _scene_item_widget; }

    void init() override {
        //updateSize();
    }

    void insertFromMimeData(const QMimeData *source) override
        {
            if (source->hasText()) {
                QString text = source->text();
                this->insertPlainText(text);
            }
        }

protected:
    void OnTextChanged() {
        if (heading_node) {
            heading_node->setText(this->toPlainText());
        }
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
    NodeHeading2* heading_node;
    TrivialSceneItemWidget* scene_item_widget;
};

#endif
