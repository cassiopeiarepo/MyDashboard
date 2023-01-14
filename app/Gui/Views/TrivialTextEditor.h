#ifndef TRIVIALTEXTEDITOR_H
#define TRIVIALTEXTEDITOR_H

#include "coreqt/Utils/Base.h"

#include <QWidget>
#include <QScrollBar>
#include "coreqt/Common/Tml.h"

#include <QList>

class Place {
public:
    int line;
    int pos;
    Place() {}
    Place(int _line, int _pos) : line(_line), pos(_pos) {}
    Place(const Place& p) : line(p.line), pos(p.pos) { }

    void offset(int delta_line, int delta_pos) 
    {
        line += delta_line;
        pos += delta_pos;
    }

    bool isUnset() { return line == INT_MAX; }
    void setUnset() { line = INT_MAX; }
};

INLINE bool operator==(const Place& p0, const Place& p1) {
    return (p0.line == p1.line && p0.pos == p1.pos);
}

INLINE bool operator!=(const Place& p0, const Place& p1) {
    return (p0.line != p1.line || p0.pos != p1.pos);
}

INLINE bool operator<(const Place& p0, const Place& p1) {
    if (p0.line < p1.line) return true;
    if (p0.line > p1.line) return false;
    if (p0.pos < p1.pos) return true;
    return false;
}

INLINE bool operator<=(const Place& p0, const Place& p1) {
    if (p0.line < p1.line) return true;
    if (p0.line > p1.line) return false;
    if (p0.pos <= p1.pos) return true;
    return false;
}

INLINE bool operator>(const Place& p0, const Place& p1) {
    if (p0.line > p1.line) return true;
    if (p0.line < p1.line) return false;
    if (p0.pos > p1.pos) return true;
    return false;
}

INLINE bool operator>=(const Place& p0, const Place& p1) {
    if (p0.line > p1.line) return true;
    if (p0.line < p1.line) return false;
    if (p0.pos >= p1.pos) return true;
    return false;
}

INLINE Place operator+(const Place& p0, const Place& p1) {
    return Place(p0.line + p1.line, p0.pos + p1.pos);
}

class Range {
public:
    Range() {}
    Range(const Range& _r) : from(_r.from), to(_r.to) {}
    Range(int from_line, int from_pos, int to_line, int to_pos) {
        from.line = from_line;
        from.pos = from_pos;
        to.line = to_line;
        to.pos = to_pos;
    }
    Range(Place _from, Place _to) : from(_from), to(_to) {}

    Place from;
    Place to;

    INLINE bool isEmpty() { return from == to;  }

    // todo
    bool contains(Place& p) {
        return false;
    }

    void normalize() {
        if (to.line > from.line || ((to.line == from.line) && from.pos > to.pos)) {
            Place temp(from);
            from = to;
            to = temp;
        }
    }

};


class TTELine {
public:
    QList<QChar> line;
    int line_width;

    QString getString() {
        QString str;

        for (int j = 0; j < line.size(); j++) {
            str += line[j];
        }
        return str;
    }
};

class TTEBuffer : public QObject {
    Q_OBJECT
public:
    TTEBuffer();

    int loadFile(QString& path);
    int saveFile(QString& path);

    void setText(QString& str);
    QString getText();
    QString getLineString(int line_nr);
    QString getString(int line_nr, int from_pos, int to_pos);
    QString getString(int line_from, int pos_from, int line_to, int pos_to);
    QString getString(const Range& r);

    void insertString(int& line, int& pos, QString str);
    void removeBlock(int& line_from, int& pos_from, int line_to, int pos_to);
    void clear();

    int getNumLines() { return lines.size(); }
    int getLineSize(int line_nr);

signals:
    void addLine(int line_nr);
    void removeLine(int line_nr);
    void preInsertString(int line_nr, int pos, const QString& str);
    void postInsertString(int line_nr, int pos_from, int pos_to);
    void preRemoveString(int line_nr, int pos_from, int pos_to);
    void postRemoveString(int line_nr, int pos, const QString& str);

protected:
    QList<TTELine*> lines;

    QList<TTELine*> stringToLines(QString& str);
    //void updateLineWidth(int line_nr)
};

class HistoryItem;
class HistoryList;
class SyntaxHighliter;

class TrivialTextEditor : public QWidget {
    Q_OBJECT

public:

    TrivialTextEditor(QWidget *parent = nullptr);
    virtual ~TrivialTextEditor();

    void setTextBuffer(TTEBuffer* text_buffer);
    TTEBuffer* getTextBuffer() { return buffer; }

    void setSyntaxHighliter(SyntaxHighliter* _sh) { sh = _sh; }
    SyntaxHighliter* getSyntaxHighliter() { return sh; }

    void clear();
    void copy();
    void cut();
    void paste();
    void selectAll();

    void undo();
    void redo();

    void resetTextColor();
    void setTextColor(const Place& color_to, QColor color);
    void cleanAll(QColor color);

public slots:
    void vscrollbarValueChanged(int value);
    void hscrollbarValueChanged(int value);
    void onBufferAddLine(int line_nr);
    void onBufferRemoveLine(int line_nr);
    void onBufferPostInsertString(int line_nr, int pos_from, int pos_to);
    void onBufferPostRemoveString(int line_nr, int pos, const QString& str);
    void onMouseSelectionTimer();

signals:
    void textChanged();

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

    int getLineHeight();
    int getLineAt(int y);
    void getLinePosAt(int& line, int& pos, int x, int y);
    int getLineOffset(int line_nr);
    int getCharOffset(int line_nr, int pos);

    void moveCursor(int line_nr, int pos);
    void moveViewToCursor();

    void backspace();
    void enter();
    void key_delete();

    void update_pos();
    void update_scrollbar_range();
    int getClientHeight();
    int getMaxLineSize();
    void initLineSize();

    void insertString(int& line_nr, int& pos, const QString& str);
    void removeBlock(int& from_line, int& from_pos, int to_line, int to_pos);

    void historyInsertString(int line_nr, int pos, QString& str);
    void historyRemoveBlock(int from_line, int from_pos, int to_line, int to_pos);

    void emitTextChanged();

    int cursor_line;
    int cursor_pos;

    int sel_line;
    int sel_pos;

    bool mouse_selection_pressed;
    QTimer* mouse_selection_timer;
    TTEBuffer* buffer;

    QColor background_color;
    QColor def_text_color;
    QColor sel_color;
    QFont* text_font;
    QFontMetrics* text_font_matrics;

    QScrollBar* hscrollbar;
    QScrollBar* vscrollbar;
    int scrollbar_size;

    QList<int> buffer_line_size;

    HistoryList* history_list;

    Place color_from;
    QList<QList<QColor>> text_color;

    SyntaxHighliter* sh;

    friend class HistoryItem;
};

class SyntaxHighliter 
{

public:

    SyntaxHighliter(TrivialTextEditor* _editor) : editor(_editor) {}

    virtual void update() = 0;

    INLINE void resetTextColor() { editor->resetTextColor(); }
    INLINE void cleanAll(QColor color) { editor->cleanAll(color); }
    INLINE void setTextColor(const Place& color_to, QColor color) { editor->setTextColor(color_to, color); }

protected:
    TrivialTextEditor* editor;

};

class XmlSyntaxHighliter : public SyntaxHighliter {

public:
    XmlSyntaxHighliter(TrivialTextEditor* _editor);

    void update() override;

private:
    void do_node(TmlNode* node);
    void do_argument(TmlArgument* argument);

    QColor node_name_color;
    QColor arg_name_color;
    QColor normal_color;

    Place place;
    QStringList lines;
};



#endif // TRIVIALTEXTEDITOR_H
