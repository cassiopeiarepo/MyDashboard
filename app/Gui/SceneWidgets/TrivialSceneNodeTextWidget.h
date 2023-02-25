#ifndef TRIVIAL_SCENE_NODE_TEXT_WIDGET_H
#define TRIVIAL_SCENE_NODE_TEXT_WIDGET_H

#include "app/Gui/SceneWidgets/ITrivialSceneWidget.h"
#include "app/Nodes/Basic/NodeText.h"

#include <QTextEdit>
#include <QTextBlock>
#include <QAbstractTextDocumentLayout>

class TrivialSceneNodeTextWidget : public QTextEdit, public ITrivialSceneWidget {
    Q_OBJECT

public:
    TrivialSceneNodeTextWidget(QWidget* parent = NULL) : QTextEdit(parent) {

        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        setFrameStyle(0);
        setFrameShape(QFrame::NoFrame);

        /*
        QTextCursor cursor = textCursor();
        QTextBlockFormat format;
        format.setLineHeight(120, QTextBlockFormat::ProportionalHeight);
        cursor.setBlockFormat(format);
        */

        //QTextBlockFormat format = document()->begin().blockFormat();
        //format.setLineHeight(120, QTextBlockFormat::ProportionalHeight);
        //document()->begin() = format;//.setBlockFormat(format);

        //QTextOption option = document()->defaultTextOption();
        //option.setLineHeight(120, QTextOption::LineHeightMode::ProportionalHeight);
        //document()->setDefaultTextOption(option);

        //setLineHeight(1.2);

        //setStyleSheet("QTextEdit { margin: 0px; }");

        QObject::connect(this, &QTextEdit::textChanged, this, &TrivialSceneNodeTextWidget::OnTextChanged);

        //QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        //setSizePolicy(sizePolicy);

        QObject::connect(document()->documentLayout(), &QAbstractTextDocumentLayout::update, [&]() {
                //qDebug() << "Wysokość dokumentu: " << document()->documentLayout()->documentSize().height();
                updateSize();
            });

    }

    void setObject(NodeBase* obj) override {
        object = obj;
        text_node = qobject_cast<NodeText*>(obj);
        if (text_node) {
            this->setMarkdown(text_node->getText());
        }
        //update();
    }

    NodeBase* getObject() override { return object; }

    void setTrivialSceneItemWidget(TrivialSceneItemWidget* _scene_item_widget) override { scene_item_widget = _scene_item_widget; }

    void init() override {
        //updateSize();
    }

protected:
    void OnTextChanged() {
        if (text_node) {
            text_node->setText(this->toMarkdown());
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
    NodeText* text_node;
    TrivialSceneItemWidget* scene_item_widget;
};

#endif
