#ifndef INPUTTEXTEDIT_H
#define INPUTTEXTEDIT_H

#include <QTextEdit>
#include <QObject>
#include <QMenu>

class InputTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    InputTextEdit(QWidget* parent);

    void contextMenuEvent(QContextMenuEvent *event) override;

public slots:
    void onBold(bool checked);
    void onItalic(bool checked);
    void onUnderline(bool checked);
    void onStrikeOut(bool checked);
    void onInsertWidget(bool checked);

    void onLink();

private:

};

#endif // INPUTTEXTEDIT_H
