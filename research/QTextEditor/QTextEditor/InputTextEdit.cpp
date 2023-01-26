#include "InputTextEdit.h"
#include <QContextMenuEvent>
#include <QPushButton>

InputTextEdit::InputTextEdit(QWidget* parent) : QTextEdit(parent)
{
    /*
    connect(this, &QTextEdit::, [](const QUrl &url) {
        // handle the click here
    });*/
}

void InputTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
    QTextCursor cursor = this->textCursor();
    QTextCharFormat format;

    QMenu *menu = createStandardContextMenu();

    QAction* action = menu->addAction("Bold");
    connect(action, &QAction::toggled, this, &InputTextEdit::onBold);
    action->setCheckable(true);
    action->setChecked((cursor.charFormat().fontWeight() == QFont::Bold));

    action = menu->addAction("Italic");
    connect(action, &QAction::toggled, this, &InputTextEdit::onItalic);
    action->setCheckable(true);
    action->setChecked(cursor.charFormat().fontItalic());

    action = menu->addAction("Underline");
    connect(action, &QAction::toggled, this, &InputTextEdit::onUnderline);
    action->setCheckable(true);
    action->setChecked(cursor.charFormat().fontUnderline());

    action = menu->addAction("StrikeOut");
    connect(action, &QAction::toggled, this, &InputTextEdit::onStrikeOut);
    action->setCheckable(true);
    action->setChecked(cursor.charFormat().fontStrikeOut());

    action = menu->addAction("link");
    connect(action, &QAction::triggered, this, &InputTextEdit::onLink);

    action = menu->addAction("Insert widget");
    connect(action, &QAction::triggered, this, &InputTextEdit::onInsertWidget);
    action->setCheckable(true);
    action->setChecked(false);

    menu->exec(event->globalPos());
    delete menu;
}

void InputTextEdit::onBold(bool checked) {
    qDebug() << " onbold";

    QTextCursor cursor = this->textCursor();
    QTextCharFormat format;

    if (checked)
        format.setFontWeight(QFont::Bold);
    else
         format.setFontWeight(QFont::Normal);

    cursor.mergeCharFormat(format);
    this->mergeCurrentCharFormat(format);
}

void InputTextEdit::onItalic(bool checked) {
    QTextCursor cursor = this->textCursor();
    QTextCharFormat format;
    format.setFontItalic(checked);
    cursor.mergeCharFormat(format);
    this->setTextCursor(cursor);
}

void InputTextEdit::onUnderline(bool checked) {
    QTextCursor cursor = this->textCursor();
    QTextCharFormat format;
    format.setFontUnderline(checked);
    cursor.mergeCharFormat(format);
    this->setTextCursor(cursor);
}

void InputTextEdit::onStrikeOut(bool checked) {
    QTextCursor cursor = this->textCursor();
    QTextCharFormat format;
    format.setFontStrikeOut(checked);
    cursor.mergeCharFormat(format);
    this->setTextCursor(cursor);
}

void InputTextEdit::onLink() {
    QTextCursor cursor = this->textCursor();
    QTextCharFormat format;
    format.setAnchor(true);
    format.setAnchorHref("http://example.com");
    format.setForeground(QBrush(Qt::blue));
    cursor.mergeCharFormat(format);
    this->setTextCursor(cursor);

}

void InputTextEdit::onInsertWidget(bool checked) {
    QTextCursor cursor = this->textCursor();
    QPushButton* button = new QPushButton(this);
    button->setAttribute(Qt::WA_TransparentForMouseEvents, false);

    //this->insertWidget(cursor, button);


}
