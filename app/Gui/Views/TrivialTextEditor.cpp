#include "TrivialTextEditor.h"
#include <QPainter>
#include <QColor>
#include <QKeyEvent>
#include <QTextStream>
#include <QClipboard>
#include <QGuiApplication>
#include <QMimeData>
#include <QTimer>
#include <QDebug>
#include <QFile>

#include "coreqt/Utils/QStringUtils.h"

TTEBuffer::TTEBuffer() {
    lines.append(new TTELine());

}

QList<TTELine*> TTEBuffer::stringToLines(QString& str) 
{
    QList<TTELine*> result;

    TTELine* line = new TTELine();
    result.append(line);

    for (int i = 0; i < str.size(); i++) {

        if (str[i] == '\r' || str[i] == '\n')
        {
            if (i > 0)
            {
                if (str[i] == '\n' && str[i - 1] == '\r') {
                    line = new TTELine();
                    result.append(line);
                }
            }
        }
        else {
            line->line.append(str[i]);
        }
    }

    return result;
}

int TTEBuffer::loadFile(QString& path) 
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return -1;
    }

    QString text;

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    //text = in.readAll();

    while (!in.atEnd())
    {
        QString line = in.readLine();
        text += line;
        if (!in.atEnd()) {
            text += "\r\n";
        }
    }

    setText(text);
    
    in.flush();
    file.close();

    return 0;
}

int TTEBuffer::saveFile(QString& path) 
{
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return -1;
    }

    QString text;

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    for (int i = 0; i < lines.size(); i++) {
        text = getLineString(i);
        out << text;
        if (i != lines.size()-1)
           out << "\n";
    }

    out.flush();
    file.close();
    return 0;
}

void TTEBuffer::setText(QString& str) {

    for (int i = lines.size() - 1; i >= 0; i--) {
        QString str = this->getLineString(i);
        if (str != "") {
            emit preRemoveString(i, 0, getLineSize(i));

            lines[i]->line.clear();
            emit postRemoveString(i, 0, str);
        }

        delete lines[i];
        lines.remove(i);
        emit removeLine(i);
    }

    QList<TTELine*> text_lines = stringToLines(str);
    for (int i = 0; i < text_lines.size(); i++) {
        // add emty line to emit addLine signal
        lines.append(new TTELine());
        emit addLine(i);
        // remove line
        delete lines[i];
        lines.remove(i);

        // create a string for preInsertString
        QString str = text_lines[i]->getString();

        if (str != "")
            emit preInsertString(i, 0, str);

        lines.append(text_lines[i]);

        if (str != "")
            emit postInsertString(i, 0, getLineSize(i));
    }
}

QString TTEBuffer::getText() {

    QString result;

    for (int i = 0; i < lines.size(); i++) 
    {
        TTELine* line = lines[i];

        for (int j = 0; j < line->line.size(); j++) {
            result.append(line->line[j]);
        }

        if (i != lines.size() - 1) {
            result.append('\r');
            result.append('\n');
        }
    }

    return result;
}

QString TTEBuffer::getLineString(int line_nr) {
    QString result;

    if (line_nr >= lines.size())
        return result;

    TTELine* line = lines[line_nr];

    for (int j = 0; j < line->line.size(); j++) {
        result.append(line->line[j]);
    }

    return result;
}

int TTEBuffer::getLineSize(int line_nr) {
    if (line_nr >= lines.size())
        return 0;

    return lines[line_nr]->line.size();
}

QString TTEBuffer::getString(int line_nr, int from_pos, int to_pos) {
    QString result;

    if (line_nr >= lines.size())
        return result;

    if (from_pos > to_pos)
        return result;

    TTELine* line = lines[line_nr];

    if (from_pos > line->line.size())
        return result;

    if (to_pos > line->line.size())
        return result;

    for (int j = from_pos; j < to_pos; j++) {
        result.append(line->line[j]);
    }

    return result;
}

QString TTEBuffer::getString(int line_from, int pos_from, int line_to, int pos_to) 
{
    if (line_from >= lines.size())
        return QString();

    if (line_to >= lines.size())
        return QString();

    if (pos_from > this->getLineSize(line_from))
        return QString();

    if (pos_to > this->getLineSize(line_to))
        return QString();

    if (line_from > line_to)
    {
        int temp = line_to;

        line_to = line_from;
        line_from = temp;

        temp = pos_to;
        pos_to = pos_from;
        pos_from = temp;

    }
    else if (line_from == line_to) {
        if (pos_from > pos_to) {
            int temp = pos_from;
            pos_from = pos_to;
            pos_to = temp;
        }
    }

    if (line_from == line_to) 
    {
        return this->getString(line_from, pos_from, pos_to);
    }
    else {
        QString result;

        TTELine* line = lines[line_from];
        
        for (int j = pos_from; j < getLineSize(line_from); j++) {
            result.append(line->line[j]);
        }

        result.append('\r');
        result.append('\n');

        for (int i = line_from+1; i < line_to; i++) 
        {
            line = lines[i];

            for (int j = 0; j < getLineSize(i); j++) {
                result.append(line->line[j]);
            }

            result.append('\r');
            result.append('\n');
        }

        line = lines[line_to];

        for (int j = 0; j < pos_to; j++) {
            result.append(line->line[j]);
        }

        return result;
    }

}

QString TTEBuffer::getString(const Range& r) {
    return getString(r.from.line, r.from.pos, r.to.line, r.to.pos);
}

void TTEBuffer::insertString(int& line_nr, int& pos, QString str) 
{

    // checking line and pos correct
    if (line_nr >= lines.size())
        return;

    if (pos > this->getLineSize(line_nr))
        return;

    if (str == "")
        return;

    QList<TTELine*> text_lines = stringToLines(str);

    if (text_lines.size() == 1) {
        TTELine* src_line = text_lines[0];
        TTELine* dest_line = lines[line_nr];

        QString str = src_line->getString();

        if (str != "") {
            emit preInsertString(line_nr, pos, str);

            int pos_from = pos;

            for (int i = 0; i < src_line->line.size(); i++) {
                dest_line->line.insert(pos, src_line->line[i]);
                pos++;
            }

            emit postInsertString(line_nr, pos_from, pos);
        }
    }
    else {

        TTELine* line = text_lines[0];
        TTELine* sline = lines[line_nr];

        int dest_pos = 0;
        
        QString str;


        // linia 0 - usuwama wszystko od pos do konca linii
        for (int i = pos; i < sline->line.size(); i++) {
            str += sline->line[i];
        }

        if (str != "")
        {
            emit preRemoveString(line_nr, pos, sline->line.size());
            sline->line.remove(pos, sline->line.size() - pos);
            emit postRemoveString(line_nr, pos, str);
        }

        // linia 0 - wstawiam w miejsce pos pierwsza linie tekstu
        QString str2 = line->getString();

        if (str2 != "") 
        {
            emit preInsertString(line_nr, pos, str2);

            int from_pos = pos;

            for (int i = 0; i < str2.size(); i++) {
                sline->line.insert(pos, str2[i]);
                pos++;
            }
            emit postInsertString(line_nr, from_pos, pos);
        }

        line_nr++;

        for (int i = 1; i < text_lines.size(); i++) {
            TTELine* src_line = text_lines[i];
            TTELine* dest_line = NULL;

            dest_line = new TTELine();
            lines.insert(line_nr, dest_line);
            emit addLine(line_nr);

            

            if (i == text_lines.size() - 1) {
                
                pos = src_line->line.size();
               
                for (int j = 0; j < src_line->line.size(); j++) {
                    str.insert(j, src_line->line[j]);
                }

                if (str != "") {
                    emit preInsertString(line_nr, 0, str);

                    for (int j = 0; j < str.size(); j++) 
                    {
                        dest_line->line.insert(j, str[j]);
                    }
                    emit postInsertString(line_nr, 0, str.size());
                }
            }
            else {
                // line copy
                pos = 0;
                QString line_str = src_line->getString();

                if (line_str != "") {
                    emit preInsertString(line_nr, 0, line_str);

                    for (int j = 0; j < src_line->line.size(); j++) {
                        dest_line->line.insert(j, src_line->line[j]);
                        pos++;
                    }

                    emit postInsertString(line_nr, 0, dest_line->line.size());
                }

                line_nr += 1;
            }
        }
    }

    // zwalniam text_lines
    for (int i = 0; i < text_lines.size(); i++) 
    {
        delete text_lines[i];
        text_lines[i] = NULL;
    }
    text_lines.clear();

}

void TTEBuffer::removeBlock(int& line_from, int& pos_from, int line_to, int pos_to) 
{
    if (line_from >= lines.size())
        return;

    if (line_to >= lines.size())
        return;

    if (pos_from > this->getLineSize(line_from))
        return;

    if (pos_to > this->getLineSize(line_to))
        return;

    if (line_from == line_to && pos_from == pos_to)
        return;

    if (line_from > line_to) 
    {
        int temp = line_to;

        line_to = line_from;
        line_from = temp;

        temp = pos_to;
        pos_to = pos_from;
        pos_from = temp;

    }
    else if (line_from == line_to) {
        if (pos_from > pos_to) {
            int temp = pos_from;
            pos_from = pos_to;
            pos_to = temp;
        }
    }

    if (line_from == line_to) {
        TTELine* line = lines[line_from];

        QString str;

        for (int i = pos_from; i < pos_to; i++) {
            str += line->line[i];
        }

        emit preRemoveString(line_from, pos_from, pos_to);

        line->line.remove(pos_from, pos_to - pos_from);

        emit postRemoveString(line_from, pos_from, str);
    }
    else {
        TTELine* dest_line = lines[line_from];
        TTELine* src_line = lines[line_to];

        int num = getLineSize(line_from) - pos_from;
        if (num > 0) {
            emit preRemoveString(line_from, pos_from, getLineSize(line_from));

            QString str;

            for (int i = pos_from; i < getLineSize(line_from); i++) {
                str += dest_line->line[i];
            }

            dest_line->line.remove(pos_from, num);
            emit postRemoveString(line_from, pos_from, str);
        }

        QString str;

        for (int i = pos_to; i < getLineSize(line_to); i++)
        {
            str += src_line->line[i];
        }

        if (str != "") {
            int j = pos_from;

            emit preInsertString(line_from, pos_from, str);

            for (int i = pos_to; i < getLineSize(line_to); i++)
            {
                dest_line->line.insert(j, src_line->line[i]);
                j++;
            }

            emit postInsertString(line_from, pos_from, j);
        }

        for (int i = line_to; i > line_from; i--)
        {
            int line_len = getLineSize(i);

            if (line_len != 0) {
                emit preRemoveString(i, 0, line_len);
                QString str = lines[i]->getString();
                lines[i]->line.clear();
                emit postRemoveString(i, 0, str);
            }

            delete lines[i];
            lines.remove(i);
            emit removeLine(i);
        }
    }
}

void TTEBuffer::clear() {
    
    for (int i = lines.size()-1; i >= 0; i--) {
        QString str = lines[i]->getString();

        if (str != "") {
            emit preRemoveString(i, 0, str.size());
            lines[i]->line.clear();
            emit postRemoveString(i, 0, str);
        }

        delete lines[i];
        lines.remove(i);
        emit removeLine(i);
    }

    lines.append(new TTELine());
    emit addLine(0);
}

class HistoryItem {

public:
    HistoryItem(TrivialTextEditor* _editor) : editor(_editor), prev(NULL), next(NULL) { }

    virtual void run_undo() = 0;
    virtual void run_redo() = 0;

protected:
    TrivialTextEditor* editor;

    void insertString(int line_nr, int pos, QString& str) { editor->historyInsertString(line_nr, pos, str); }
    void removeBlock(int from_line, int from_pos, int to_line, int to_pos) { editor->historyRemoveBlock(from_line, from_pos, to_line, to_pos); }

private:
    HistoryItem* prev;
    HistoryItem* next;

    friend class HistoryList;
};

class HistoryList
{
public:
    HistoryList(int _max_size) : first(NULL), last(NULL), current(NULL), max_size(_max_size), size(0), minimum(true), maximum(false) { }

    HistoryItem* get() { return current; }

    bool canUndo() {
        if (current != NULL)
            return true;
        else if (maximum && (last != NULL))
            return true;
        return false;
    }

    bool canRedo() {
        if (current) {
            if (current->next != NULL)
                return true;
            else
                return false;
        }
        else {
            if (minimum && (first != NULL))
                return true;

        }
        return false;
    }

    bool isLast() {
        return (current == last) && (last != NULL);
    }

    void undo() {
        if (!canUndo())
            return;

        if (current)
        {
            current->run_undo();
            current = current->prev;

            if (current == NULL)
                minimum = true;
        }
        else if (maximum) {
            current = last;

            if (current)
            {
                current->run_undo();
                current = current->prev;

                if (current == NULL)
                    minimum = true;
            }
        }
    }

    void redo() {
        if (!canRedo())
            return;

        if (current)
        {
            current = current->next;
            if (current)
                current->run_redo();
            else
                maximum = true;
        }
        else if (minimum) {
            current = first;

            if (current)
                current->run_redo();
        }
    }

    void append(HistoryItem* item)
    {
        if (current)
        {
            free_next_items(current->next);
            current->next = NULL;
            update_size();
            if (size == max_size)
                free_first_item();
            current->next = item;
            item->next = NULL;
            item->prev = current;
            current = item;
            last = current;
        }
        else {
            if (minimum) {
                free_next_items(first);
                first = NULL;
                item->prev = NULL;
                item->next = NULL;
                current = item;
                last = current;
                first = current;
                update_size();
            }
            else if (maximum) {
                if (size == max_size)
                    free_first_item();
                item->prev = last;
                item->next = NULL;
                current = item;
                last = current;
            }
        }
    }

private:
    int size;
    int max_size;
    bool minimum;
    bool maximum;
    HistoryItem* first;
    HistoryItem* last;
    HistoryItem* current;

    void free_next_items(HistoryItem* item)
    {
        if (item != NULL)
        {
            free_next_items(item->next);
            delete item;
        }
    }

    void free_first_item() {
        HistoryItem* item = first;
        first = item->next;
        first->prev = NULL;
        delete item;
    }


    void update_size()
    {
        size = 0;
        HistoryItem* item = first;
        while (item)
        {
            size++;
            item = item->next;
        }
    }
};

class InsertStringHistoryItem : public HistoryItem {

public:
    InsertStringHistoryItem(TrivialTextEditor* _editor, Range& _range, const QString& _str) :
        HistoryItem(_editor), range(_range), str(_str)
    {

    }

    bool append(Range& _range, const QString& _str) {
        if (range.to == _range.from) {
            range.to = _range.to;
            str += _str;
            return true;
        }

        return false;
    }

    void run_undo() override {
        removeBlock(range.from.line, range.from.pos, range.to.line, range.to.pos);
    }

    void run_redo() override {
        insertString(range.from.line, range.from.pos, str);
    }

protected:
    QString str;
    Range range;
};

class RemoveBlockHistoryItem : public HistoryItem {

public:
    RemoveBlockHistoryItem(TrivialTextEditor* _editor, Range& _range, QString& _str) :
        HistoryItem(_editor), range(_range), str(_str)
    {

    }

    bool append(Range& _range, QString& _str) {
        if (range.from == _range.to) {
            range.from = _range.from;
            str = _str + str;
            return true;
        }

        return false;
    }

    void run_undo() override {
        insertString(range.from.line, range.from.pos, str);
    }

    void run_redo() override {
        removeBlock(range.from.line, range.from.pos, range.to.line, range.to.pos);
    }

protected:
    QString str;
    Range range;
};

TrivialTextEditor::TrivialTextEditor(QWidget* parent) : QWidget(parent), buffer(NULL), sh(NULL) {

    TTEBuffer* text_buffer = new TTEBuffer();

    cursor_line = 0;
    cursor_pos = 0;

    sel_line = 0;
    sel_pos = 0;

    mouse_selection_pressed = false;
    
    history_list = new HistoryList(20);

    background_color = QColor(Qt::white);
    def_text_color = QColor(Qt::black);
    sel_color = QColor(Qt::blue);

    text_font = new QFont("Arial", 10);
    text_font_matrics = new QFontMetrics(*text_font);

    //QString str = QString("To jest pierwsza linijka\r\nTo jest druga linijka\r\nTrzecia linijka");
    //buffer->setText(str);
    //text_buffer->loadFile(QString("C:\\Projekty\\MyDashboard\\test_utf8.txt"));

    setFocus();
    setMouseTracking(true);

    hscrollbar = new QScrollBar(Qt::Horizontal, this);
    vscrollbar = new QScrollBar(Qt::Vertical, this);
    scrollbar_size = 15;
    QObject::connect(vscrollbar, &QScrollBar::valueChanged, this, &TrivialTextEditor::vscrollbarValueChanged);
    QObject::connect(hscrollbar, &QScrollBar::valueChanged, this, &TrivialTextEditor::hscrollbarValueChanged);

    color_from = Place(0, 0);

    setTextBuffer(text_buffer);

    update_pos();
    update_scrollbar_range();

    mouse_selection_timer = new QTimer(this);
    connect(mouse_selection_timer, &QTimer::timeout, this, &TrivialTextEditor::onMouseSelectionTimer);
    mouse_selection_timer->start(100);
}

TrivialTextEditor::~TrivialTextEditor() {

    if (text_font_matrics) delete text_font_matrics;
    if (text_font) delete text_font;
    if (buffer) delete buffer;
    if (mouse_selection_timer) delete mouse_selection_timer;
    if (history_list) delete history_list;
}

void TrivialTextEditor::setTextBuffer(TTEBuffer* text_buffer) 
{
    if (buffer) {
        QObject::disconnect(buffer, &TTEBuffer::addLine, this, &TrivialTextEditor::onBufferAddLine);
        QObject::disconnect(buffer, &TTEBuffer::removeLine, this, &TrivialTextEditor::onBufferRemoveLine);
        QObject::disconnect(buffer, &TTEBuffer::postInsertString, this, &TrivialTextEditor::onBufferPostInsertString);
        QObject::disconnect(buffer, &TTEBuffer::postRemoveString, this, &TrivialTextEditor::onBufferPostRemoveString);
    }

    buffer = text_buffer;
    initLineSize();

    text_color.clear();
    if (sh)
        sh->update();

    for (int i = 0; i < buffer->getNumLines(); i++) {
        QList<QColor> line;
        line.resize(buffer->getLineSize(i));
        text_color.insert(i, line);
    }


    if (buffer) 
    {
        QObject::connect(buffer, &TTEBuffer::addLine, this, &TrivialTextEditor::onBufferAddLine);
        QObject::connect(buffer, &TTEBuffer::removeLine, this, &TrivialTextEditor::onBufferRemoveLine);
        QObject::connect(buffer, &TTEBuffer::postInsertString, this, &TrivialTextEditor::onBufferPostInsertString);
        QObject::connect(buffer, &TTEBuffer::postRemoveString, this, &TrivialTextEditor::onBufferPostRemoveString);
    }
}

void TrivialTextEditor::update_pos() 
{

    hscrollbar->resize(width() - scrollbar_size, scrollbar_size);
    hscrollbar->move(0, height() - scrollbar_size);

    vscrollbar->resize(scrollbar_size, height() - scrollbar_size);
    vscrollbar->move(width() - scrollbar_size, 0);
}

void TrivialTextEditor::update_scrollbar_range() {
    int max = getClientHeight() - (height() - scrollbar_size);

    vscrollbar->setRange(0, max);
    vscrollbar->setSingleStep(getLineHeight());
    vscrollbar->setPageStep(height() - scrollbar_size);
   
    max = getMaxLineSize() - (width() - scrollbar_size);

    hscrollbar->setRange(0, max);
    hscrollbar->setSingleStep(20);
    hscrollbar->setPageStep(width() - scrollbar_size);
    
}

int TrivialTextEditor::getClientHeight() {
    return getLineHeight() * buffer->getNumLines();
}

int TrivialTextEditor::getLineHeight() {
    return text_font_matrics->lineSpacing();
}

int TrivialTextEditor::getLineAt(int y) {

    if (y < 0)
        y = 0;

    int line =  (y + vscrollbar->value()) / getLineHeight();

    if (line >= buffer->getNumLines())
        line = buffer->getNumLines() -  1;

    return line;
}

int TrivialTextEditor::getLineOffset(int line_nr) {
    return (line_nr + 1) * getLineHeight() - text_font_matrics->descent();
}

int TrivialTextEditor::getCharOffset(int line_nr, int pos) 
{
    QString str = buffer->getString(line_nr, 0, pos);
    return text_font_matrics->horizontalAdvance(str);
}

void TrivialTextEditor::getLinePosAt(int& line, int& pos, int x, int y) 
{
    line = getLineAt(y);
    x += hscrollbar->value();

    for (int i = 1; i <= buffer->getLineSize(line); i++) 
    {
        QString str = buffer->getString(line, 0, i);
        int str_len = text_font_matrics->horizontalAdvance(str);
        if (str_len > x) 
        {
            pos = i - 1;
            return;
        }
        else if (i == buffer->getLineSize(line)) {
            if (str_len <= x)
            {
                pos = i;
                return;
            }
        }
    }

    pos = 0;
}

int TrivialTextEditor::getMaxLineSize() {
    int max = 0;

    for (int i = 0; i < buffer_line_size.size(); i++) {
        if (buffer_line_size[i] > max)
            max = buffer_line_size[i];
    }
    return max;
}

void TrivialTextEditor::initLineSize() {
    buffer_line_size.resize(buffer->getNumLines());

    for (int i = 0; i < buffer->getNumLines(); i++) {
        buffer_line_size[i] = getCharOffset(i, buffer->getLineSize(i));
    }
}

void TrivialTextEditor::moveViewToCursor() {
    int vline_from = getLineAt(0);
    int vline_to = getLineAt(height() - scrollbar_size);

    if (cursor_line < vline_from) {
        vscrollbar->setValue(cursor_line * getLineHeight());
    } else if (cursor_line >= vline_to) {
        vscrollbar->setValue((cursor_line - (vline_to - vline_from-1)) * getLineHeight());
    }

    int cursor_offset = getCharOffset(cursor_line, cursor_pos);

    if (cursor_offset < hscrollbar->value()) {
        int val = cursor_offset - 10;
        if (val < 0)
            val = 0;
        hscrollbar->setValue(val);
    }
    else if (cursor_offset >= hscrollbar->value() + (width() - scrollbar_size)) {
        int val = cursor_offset - (width() - scrollbar_size) + 10;
        hscrollbar->setValue(val);
    }
}

void TrivialTextEditor::emitTextChanged() {
    emit textChanged();

    if (sh) {
        sh->update();
    }

}

void TrivialTextEditor::insertString(int& line_nr, int& pos, const QString& str) 
{

    int from_line = line_nr;
    int from_pos = pos;

    buffer->insertString(line_nr, pos, str);

    bool appended = false;

    if (history_list->isLast()) {
        HistoryItem* hi = history_list->get();
        InsertStringHistoryItem* insert_history = dynamic_cast<InsertStringHistoryItem*>(hi);
        if (insert_history != NULL) {
            Range r(from_line, from_pos, line_nr, pos);
            appended = insert_history->append(r, str);
        }
    }
 
    if (!appended) 
    {
        Range r(from_line, from_pos, line_nr, pos);
        InsertStringHistoryItem* history_item = new InsertStringHistoryItem(this, r, str);
        history_list->append(history_item);
    }
}

void TrivialTextEditor::removeBlock(int& from_line, int& from_pos, int to_line, int to_pos) 
{

    Range r(from_line, from_pos, to_line, to_pos);
    r.normalize();

    QString str = buffer->getString(r);

    buffer->removeBlock(from_line, from_pos, to_line, to_pos);

    bool appended = false;

    if (history_list->isLast()) {
        HistoryItem* hi = history_list->get();
        RemoveBlockHistoryItem* insert_history = dynamic_cast<RemoveBlockHistoryItem*>(hi);
        if (insert_history != NULL) {
            appended = insert_history->append(r, str);
        }
    }

    if (!appended)
    {
        RemoveBlockHistoryItem* history_item = new RemoveBlockHistoryItem(this, r, str);
        history_list->append(history_item);
    }
}


void TrivialTextEditor::clear() {

}

void TrivialTextEditor::copy() {
    if (cursor_line != sel_line || cursor_pos != sel_pos) {
        QString str = buffer->getString(cursor_line, cursor_pos, sel_line, sel_pos);
        QClipboard* clipboard = QGuiApplication::clipboard();
        clipboard->setText(str);
    }
}

void TrivialTextEditor::cut() {
    if (cursor_line != sel_line || cursor_pos != sel_pos) {
        QString str = buffer->getString(cursor_line, cursor_pos, sel_line, sel_pos);
        QClipboard* clipboard = QGuiApplication::clipboard();
        clipboard->setText(str);

        removeBlock(cursor_line, cursor_pos, sel_line, sel_pos);
        sel_line = cursor_line;
        sel_pos = cursor_pos;
        moveViewToCursor();
        emitTextChanged();
        update();
    }
}

void TrivialTextEditor::paste() {

    bool need_update = false;

    if (cursor_line != sel_line || cursor_pos != sel_pos) {
        removeBlock(cursor_line, cursor_pos, sel_line, sel_pos);
        sel_line = cursor_line;
        sel_pos = cursor_pos;
        need_update = true;
    }

    const QClipboard* clipboard = QGuiApplication::clipboard();
    const QMimeData* mimeData = clipboard->mimeData();

    if (mimeData->hasText()) {
        insertString(cursor_line, cursor_pos, mimeData->text());
        sel_line = cursor_line;
        sel_pos = cursor_pos;

        need_update = true;
    }

    moveViewToCursor();

    if (need_update) {
        emitTextChanged();
        update();
    }
}

void TrivialTextEditor::selectAll() 
{
    sel_line = 0;
    sel_pos = 0;

    cursor_line = buffer->getNumLines() - 1;
    cursor_pos = buffer->getLineSize(cursor_line);

    moveViewToCursor();
    update();
}

void TrivialTextEditor::undo() {
    if (!history_list->canUndo())
        return;

    history_list->undo();
    emitTextChanged();
    update();
}

void TrivialTextEditor::redo() {
    if (!history_list->canRedo())
        return;

    history_list->redo();
    emitTextChanged();
    update();
}

void TrivialTextEditor::moveCursor(int line_nr, int pos) 
{
    cursor_line = line_nr;
    cursor_pos = pos;
    moveViewToCursor();
    this->update();
}

void TrivialTextEditor::backspace() 
{

    if (cursor_line != sel_line || cursor_pos != sel_pos) {
        removeBlock(cursor_line, cursor_pos, sel_line, sel_pos);
        sel_line = cursor_line;
        sel_pos = cursor_pos;
        emitTextChanged();
        update();
    }
    else {

        if (cursor_pos > 0) {
            removeBlock(cursor_line, cursor_pos, cursor_line, cursor_pos - 1);
            sel_line = cursor_line;
            sel_pos = cursor_pos;
            emitTextChanged();
            update();
        }
        else {
            if (cursor_line > 0) {

                cursor_line -= 1;
                cursor_pos = buffer->getLineSize(cursor_line);

                removeBlock(cursor_line, cursor_pos, cursor_line + 1, 0);
                sel_line = cursor_line;
                sel_pos = cursor_pos;
                emitTextChanged();
                update();
            }
        }
    }
    moveViewToCursor();
}

void TrivialTextEditor::enter() {

    if (cursor_line != sel_line || cursor_pos != sel_pos) {
        removeBlock(cursor_line, cursor_pos, sel_line, sel_pos);
    }

    insertString(cursor_line, cursor_pos, QString("\r\n"));
    sel_line = cursor_line;
    sel_pos = cursor_pos;
    emitTextChanged();
    update();
    moveViewToCursor();
}

void TrivialTextEditor::key_delete() 
{
    if (cursor_line != sel_line || cursor_pos != sel_pos) {
        removeBlock(cursor_line, cursor_pos, sel_line, sel_pos);
        sel_line = cursor_line;
        sel_pos = cursor_pos;
        emitTextChanged();
        update();
    }
    else {
        if (cursor_pos == buffer->getLineSize(cursor_line)) 
        {
            if (cursor_line != buffer->getNumLines() - 1) 
            {
                removeBlock(cursor_line, cursor_pos, cursor_line + 1, 0);
                emitTextChanged();
                update();
            }
        }
        else {
            removeBlock(cursor_line, cursor_pos, cursor_line, cursor_pos + 1);
            sel_line = cursor_line;
            sel_pos = cursor_pos;
            emitTextChanged();
            update();
        }
    }
    moveViewToCursor();
}

void TrivialTextEditor::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    int width = size().width();
    int height = size().height();

    painter.fillRect(0, 0, width, height, background_color);

    //draw selection
    int sel_from_line = cursor_line;
    int sel_from_pos = cursor_pos;
    int sel_to_line = sel_line;
    int sel_to_pos = sel_pos;

    if (sel_from_line > sel_to_line)
    {
        int temp = sel_from_line;
        sel_from_line = sel_to_line;
        sel_to_line = temp;

        temp = sel_from_pos;
        sel_from_pos = sel_to_pos;
        sel_to_pos = temp;
    }
    else if (sel_from_line == sel_to_line) {
        if (sel_from_pos > sel_to_pos)
        {
            int temp = sel_from_pos;
            sel_from_pos = sel_to_pos;
            sel_to_pos = temp;
        }
    }

    if (sel_from_line == sel_to_line) {
        int x = getCharOffset(sel_from_line, sel_from_pos);
        int y = getLineOffset(sel_from_line) - text_font_matrics->ascent() - vscrollbar->value();//getLineHeight();
        int height = getLineHeight();
        int width = getCharOffset(sel_to_line, sel_to_pos) - x;
        
        painter.fillRect(-hscrollbar->value() + x, y, width, height, sel_color);
    }
    else {
        
        int x = getCharOffset(sel_from_line, sel_from_pos);
        int y = getLineOffset(sel_from_line) - text_font_matrics->ascent() - vscrollbar->value();//getLineHeight();
        int height = getLineHeight();
        int width = getCharOffset(sel_from_line, buffer->getLineSize(sel_from_line)) - x;

        painter.fillRect(-hscrollbar->value() + x, y, width, height, sel_color);

        for (int i = sel_from_line + 1; i < sel_to_line; i++) {
            x = getCharOffset(i, 0);
            y = getLineOffset(i) - text_font_matrics->ascent() - vscrollbar->value();//- getLineHeight();
            height = getLineHeight();
            width = getCharOffset(i, buffer->getLineSize(i)) - x;

            painter.fillRect(-hscrollbar->value() + x, y, width, height, sel_color);
        }

        x = getCharOffset(sel_to_line, 0);
        y = getLineOffset(sel_to_line) - text_font_matrics->ascent() - vscrollbar->value();//getLineHeight();
        height = getLineHeight();
        width = getCharOffset(sel_to_line, sel_to_pos) - x;

        painter.fillRect(-hscrollbar->value() + x, y, width, height, sel_color);
    }

    // draw text
    int from_line = getLineAt(0);
    int to_line = getLineAt(height - 1);

    if (to_line >= buffer->getNumLines())
        to_line = buffer->getNumLines() - 1;

    if (sh) {
    
        painter.setFont(*this->text_font);

        for (int i = from_line; i <= to_line; i++)
        {
            int pos_from = 0;
            int pos_to = 0;
            QColor color;

            if (i >= text_color.size())
                qDebug() << "TrivialTextEditor::paintEvent line nr out of baund";

            if (text_color[i].size() != buffer->getLineSize(i))
                qDebug() << "TrivialTextEditor::paintEvent different line size";

            while (pos_from < buffer->getLineSize(i)) 
            {
                pos_to = pos_from;
                color = text_color[i][pos_to];

                while (color == text_color[i][pos_to]) {
                    pos_to++;

                    if (pos_to >= buffer->getLineSize(i))
                        break;
                }

                QString str = buffer->getString(i, pos_from, pos_to);
                int x_offset = this->getCharOffset(i, pos_from);
                
                painter.setPen(color);
                painter.drawText(-hscrollbar->value() + x_offset, getLineOffset(i) - vscrollbar->value(), str);

                pos_from = pos_to;
            }
        }
    }
    else {
        painter.setPen(def_text_color);
        painter.setFont(*this->text_font);

        for (int i = from_line; i <= to_line; i++)
        {
            QString str = buffer->getLineString(i);
            painter.drawText(-hscrollbar->value(), getLineOffset(i) - vscrollbar->value(), str);
        }
    }

    // draw cursor
    int cursor_x = getCharOffset(cursor_line, cursor_pos);
    int cursor_y = getLineOffset(cursor_line) + text_font_matrics->descent();
    painter.drawLine(-hscrollbar->value() + cursor_x, cursor_y  - vscrollbar->value(), -hscrollbar->value() + cursor_x, cursor_y - getLineHeight() - vscrollbar->value());
    
    if (cursor_line == sel_line && cursor_pos == sel_pos)
        painter.drawRect(0, cursor_y - vscrollbar->value() - getLineHeight(), width - scrollbar_size-1, getLineHeight());

    painter.fillRect(width - scrollbar_size, height - scrollbar_size, scrollbar_size, scrollbar_size, background_color);
}

void TrivialTextEditor::keyPressEvent(QKeyEvent* event) {


    if (event->key() == Qt::Key::Key_Left) {

        int new_cursor_line = cursor_line;
        int new_cursor_pos = cursor_pos;
        if (cursor_pos > 0) {
            new_cursor_pos = cursor_pos - 1;
        }
        else {
            if (cursor_line > 0) {
                new_cursor_line = cursor_line - 1;
                new_cursor_pos = buffer->getLineSize(new_cursor_line);
            }
        }

        if (!(event->modifiers() & Qt::ShiftModifier))
        {
            sel_line = new_cursor_line;
            sel_pos = new_cursor_pos;
        }
        moveCursor(new_cursor_line, new_cursor_pos);
    }
    else if (event->key() == Qt::Key::Key_Right) {

        int new_cursor_line = cursor_line;
        int new_cursor_pos = cursor_pos;

        if (cursor_pos < buffer->getLineSize(cursor_line)) {
            new_cursor_pos = cursor_pos + 1;
        }
        else {
            if (cursor_line < buffer->getNumLines() - 1) {
                new_cursor_line = cursor_line + 1;
                new_cursor_pos = 0;
            }
        }

        if (!(event->modifiers() & Qt::ShiftModifier))
        {
            sel_line = new_cursor_line;
            sel_pos = new_cursor_pos;
        }

        moveCursor(new_cursor_line, new_cursor_pos);
    }
    else if (event->key() == Qt::Key::Key_Up) {

        int new_cursor_line = cursor_line;
        int new_cursor_pos = cursor_pos;

        if (cursor_line > 0) {
            new_cursor_line = cursor_line - 1;

            if (cursor_pos > buffer->getLineSize(new_cursor_line))
            {
                new_cursor_pos = buffer->getLineSize(new_cursor_line);
            }
        }

        if (!(event->modifiers() & Qt::ShiftModifier))
        {
            sel_line = new_cursor_line;
            sel_pos = new_cursor_pos;
        }

        moveCursor(new_cursor_line, new_cursor_pos);
    }
    else if (event->key() == Qt::Key::Key_Down) {

        int new_cursor_line = cursor_line;
        int new_cursor_pos = cursor_pos;

        if (cursor_line < buffer->getNumLines() - 1) {
            new_cursor_line = cursor_line + 1;

            if (cursor_pos > buffer->getLineSize(new_cursor_line))
            {
                new_cursor_pos = buffer->getLineSize(new_cursor_line);
            }
        }

        if (!(event->modifiers() & Qt::ShiftModifier))
        {
            sel_line = new_cursor_line;
            sel_pos = new_cursor_pos;
        }

        moveCursor(new_cursor_line, new_cursor_pos);
    }
    else if (event->key() == Qt::Key::Key_End) {

        int new_cursor_line = cursor_line;
        int new_cursor_pos = buffer->getLineSize(new_cursor_line);

        if (!(event->modifiers() & Qt::ShiftModifier))
        {
            sel_line = new_cursor_line;
            sel_pos = new_cursor_pos;
        }

        moveCursor(new_cursor_line, new_cursor_pos);
    }
    else if (event->key() == Qt::Key::Key_Home) {

        int new_cursor_line = cursor_line;
        int new_cursor_pos = 0;

        if (!(event->modifiers() & Qt::ShiftModifier))
        {
            sel_line = new_cursor_line;
            sel_pos = new_cursor_pos;
        }

        moveCursor(new_cursor_line, new_cursor_pos);
    }
    else if (event->key() == Qt::Key::Key_PageUp) {
        int new_cursor_line = cursor_line - (height() - scrollbar_size) / getLineHeight();
        if (new_cursor_line < 0)
            new_cursor_line = 0;

        if (!(event->modifiers() & Qt::ShiftModifier))
        {
            sel_line = new_cursor_line;
        }

        moveCursor(new_cursor_line, cursor_pos);
    }
    else if (event->key() == Qt::Key::Key_PageDown) {
        int new_cursor_line = cursor_line + (height() - scrollbar_size) / getLineHeight();
        if (new_cursor_line >= buffer->getNumLines())
            new_cursor_line = buffer->getNumLines() - 1;

        if (!(event->modifiers() & Qt::ShiftModifier))
        {
            sel_line = new_cursor_line;
        }

        moveCursor(new_cursor_line, cursor_pos);
    }
    else if (event->key() == Qt::Key::Key_Backspace) {
        backspace();
    }
    else if (event->key() == Qt::Key::Key_Enter) {
        enter();
    }
    else if (event->key() == Qt::Key::Key_Return) {
        enter();
    }
    else if (event->key() == Qt::Key::Key_Delete) {
        key_delete();
    }
    else if ((event->modifiers() & Qt::ControlModifier)) {
        if (event->key() == Qt::Key::Key_C) {
            copy();
        } else if (event->key() == Qt::Key::Key_V) {
            paste();
        }
        else if (event->key() == Qt::Key::Key_X) {
            cut();
        }
        else if (event->key() == Qt::Key::Key_A) {
            selectAll();
        } 
        else if (event->key() == Qt::Key::Key_Z) {
            undo();
        } 
        else if (event->key() == Qt::Key::Key_Y) {
            redo();
        }
    } else {

        if (event->text() != "") {

            if (cursor_line != sel_line || cursor_pos != sel_pos) {
                removeBlock(cursor_line, cursor_pos, sel_line, sel_pos);
                sel_line = cursor_line;
                sel_pos = cursor_pos;
            }

            insertString(cursor_line, cursor_pos, event->text());
            sel_line = cursor_line;
            sel_pos = cursor_pos;
            moveViewToCursor();
            emitTextChanged();
            update();
        }
    }
}

void TrivialTextEditor::mouseMoveEvent(QMouseEvent* event) 
{

    if (event->buttons() == Qt::LeftButton) {
        int line;
        int pos;

        getLinePosAt(line, pos, event->pos().x(), event->pos().y());

        cursor_line = line;
        cursor_pos = pos;
        update();
    }
}

void TrivialTextEditor::mousePressEvent(QMouseEvent* event) {

    setFocus();

    if (event->button() == Qt::LeftButton) 
    {
        mouse_selection_pressed = true;
        getLinePosAt(cursor_line, cursor_pos, event->pos().x(), event->pos().y());

        sel_line = cursor_line;
        sel_pos = cursor_pos;

        update();
    }
}

void TrivialTextEditor::mouseReleaseEvent(QMouseEvent* event) 
{
    if (event->button() == Qt::LeftButton)
        mouse_selection_pressed = false;
}

void TrivialTextEditor::wheelEvent(QWheelEvent* event) {
    QPoint numPixels = event->pixelDelta();
    QPoint numDegrees = event->angleDelta() / 8;

    if (!numPixels.isNull()) {
        //scrollWithPixels(numPixels);
    }
    else if (!numDegrees.isNull()) {
        QPoint numSteps = numDegrees / 15;

        if (numSteps.y() != 0) {
            int voffset = vscrollbar->value() - numSteps.y() * 3 * getLineHeight();
            if (voffset < 0) {
                voffset = 0;
            }
            else if (voffset > vscrollbar->maximum()) {
                voffset = vscrollbar->maximum();
            }
            vscrollbar->setValue(voffset);
        }
    }

    event->accept();
}

void TrivialTextEditor::resizeEvent(QResizeEvent* event) {
    update_pos();
    update_scrollbar_range();
}

void TrivialTextEditor::vscrollbarValueChanged(int value) {
    update();
}

void TrivialTextEditor::hscrollbarValueChanged(int value) {
    update();
}

void TrivialTextEditor::onBufferAddLine(int line_nr) {
    buffer_line_size.insert(line_nr, 0);
    int max = getClientHeight() - (height() - scrollbar_size);
    vscrollbar->setRange(0, max);


    QList<QColor> line;
    text_color.insert(line_nr, line);
}

void TrivialTextEditor::onBufferRemoveLine(int line_nr) {
    buffer_line_size.remove(line_nr);
    int max = getClientHeight() - (height() - scrollbar_size);
    vscrollbar->setRange(0, max);

    text_color.remove(line_nr);
}

void TrivialTextEditor::onBufferPostInsertString(int line_nr, int pos_from, int pos_to) {
    buffer_line_size[line_nr] = getCharOffset(line_nr, buffer->getLineSize(line_nr));
    int max = getMaxLineSize() - (width() - scrollbar_size);
    if (max < 0)
        max = 0;

    if (max != hscrollbar->maximum())
        hscrollbar->setMaximum(max);

    text_color[line_nr].resize(buffer->getLineSize(line_nr));
}

void TrivialTextEditor::onBufferPostRemoveString(int line_nr, int pos, const QString& str) {
    buffer_line_size[line_nr] = getCharOffset(line_nr, buffer->getLineSize(line_nr));
    int max = getMaxLineSize() - (width() - scrollbar_size);
    if (max < 0)
        max = 0;

    if (max != hscrollbar->maximum())
        hscrollbar->setMaximum(max);

    text_color[line_nr].resize(buffer->getLineSize(line_nr));
}

void TrivialTextEditor::onMouseSelectionTimer() 
{

    if (mouse_selection_pressed) {
        QPoint cursor_pos = QCursor::pos();
        QPoint win_global_pos = this->mapToGlobal(QPoint());
        QPoint win_global_pos2 = this->mapToGlobal(QPoint(width() - scrollbar_size, height() - scrollbar_size));

        if (cursor_pos.y() < win_global_pos.y())
        {
            int voffset = vscrollbar->value() - getLineHeight();
            if (voffset < 0) {
                voffset = 0;
            }
            vscrollbar->setValue(voffset);
        }
        else if (cursor_pos.y() > win_global_pos2.y()) {
            int voffset = vscrollbar->value() + getLineHeight();
            if (voffset > vscrollbar->maximum()) {
                voffset = vscrollbar->maximum();
            }
            vscrollbar->setValue(voffset);
        }
    }
}

void TrivialTextEditor::historyInsertString(int line_nr, int pos, QString& str) 
{
    buffer->insertString(line_nr, pos, str);

    cursor_line = line_nr;
    cursor_pos = pos;

    sel_line = cursor_line;
    sel_pos = cursor_pos;
}

void TrivialTextEditor::historyRemoveBlock(int from_line, int from_pos, int to_line, int to_pos) 
{
    buffer->removeBlock(from_line, from_pos, to_line, to_pos);

    cursor_line = from_line;
    cursor_pos = from_pos;

    sel_line = cursor_line;
    sel_pos = cursor_pos;
}

void TrivialTextEditor::resetTextColor() {
    color_from = Place(0, 0);
    /*
    text_color.resize(buffer->getNumLines());
    for (int i = 0; i < buffer->getNumLines(); i++) {
        text_color[i].resize(buffer->getLineSize(i));
    }
    */
}

void TrivialTextEditor::cleanAll(QColor color) {
    color_from = Place(0, 0);
    Place color_to(text_color.size() - 1, text_color[text_color.size() - 1].size());
    setTextColor(color_to, color);
}

void TrivialTextEditor::setTextColor(const Place& color_to, QColor color) {
    if (color_to <= color_from)
        return;

    if (color_to.line == color_from.line) {
        for (int i = color_from.pos; i < color_to.pos; i++) 
            text_color[color_from.line][i] = color;
    }
    else {
        
        for (int i = color_from.pos; i < text_color[color_from.line].size(); i++)
            text_color[color_from.line][i] = color;

        for (int line = color_from.line + 1; line < color_to.line; line++) 
        {
            for (int i = 0; i < text_color[line].size(); i++)
                text_color[line][i] = color;
        }

        for (int i = 0; i < color_to.pos; i++)
            text_color[color_to.line][i] = color;
    }

    color_from = color_to;
}

XmlSyntaxHighliter::XmlSyntaxHighliter(TrivialTextEditor* _editor) : SyntaxHighliter(_editor) {
    node_name_color = QColor(Qt::blue);
    arg_name_color = QColor(Qt::red);
    normal_color = QColor(Qt::black);
}

void XmlSyntaxHighliter::update() {
    resetTextColor();

    QString txt = editor->getTextBuffer()->getText();
    TmlNode* node = new TmlNode();
    if (node->parse(txt)) {
        lines = QStringUtils::splitLinesToVectorWindows(txt);
        do_node(node);
    }
    else {
        cleanAll(normal_color);
    }
    delete node;
}

void XmlSyntaxHighliter::do_node(TmlNode* node) {

    place.line = node->line;
    place.pos = node->pos + 1;

    setTextColor(place, normal_color);

    place.pos = node->getNameEnd(lines);

    setTextColor(place, node_name_color);


    //kolorowanie argumentow
    for (int i = 0; i < node->getNumArgs(); i++) {
        TmlArgument* arg = node->getArg(i);
        do_argument(arg);
    }

    // kolorowanie dzieci
    for (int i = 0; i < node->getNumChilds(); i++) {
        TmlNode* child = node->getChild(i);
        do_node(child);
    }

    if (!node->getEmptyElement())
    {
        place.line = node->end_line;
        place.pos = node->end_pos + 2;

        setTextColor(place, normal_color);

        place.pos = node->getNameEnd2(lines);

        setTextColor(place, node_name_color);
    }

}

void XmlSyntaxHighliter::do_argument(TmlArgument* argument) {
    place.line = argument->line;
    place.pos = argument->pos;

    setTextColor(place, normal_color);

    place.pos = argument->getArgEnd(lines);

    setTextColor(place, arg_name_color);
}

