#include "TrivialCppParser.h"


QChar TrivialCppLex::getChar() {
    index++;

    if (ch == QChar(13)) {
        pos = 0;
        line++;
    }
    else if (ch != QChar(0)) {
        pos++;
    }

    if (index >= input_size) {
        ch = QChar(0);
        return QChar(0);
    }

    if ((*input)[index] == '\r') {
        if (index < input_size - 1) {
            if ((*input)[index + 1] == '\n') {
                index++;
                ch = QChar(13);
                return QChar(13);
            }
        }
    }

    ch = (*input)[index];
    return ch;
}

void TrivialCppLex::skipWhitespace() {
    while (ch == QChar(13) || ch == ' ' || ch == '\t')
    {
        getChar();
    }
}

bool TrivialCppLex::isAlpha(QChar ch) {
    if (ch >= QChar('a') && ch <= QChar('z'))
        return true;
    else if (ch >= QChar('A') && ch <= QChar('Z'))
        return true;

    return false;
}

bool TrivialCppLex::isNum(QChar ch) {
    if (ch >= QChar('0') && ch <= QChar('9'))
        return true;

    return false;
}


TrivialCppLex::Sym TrivialCppLex::next() {

    text = "";
    skipWhitespace();

    // ident or keyword

    if (isAlpha(ch) || ch == QChar('_')) {
        text += ch;
        getChar();

        while (isAlpha(ch) || isNum(ch)|| ch == QChar('_'))
        {
            text += ch;
            getChar();
        }

        if (text == "class") {
            sym = SYM_KEY_CLASS;
        } else if (text == "private") {
            sym = SYM_KEY_PRIVATE;
        } else if (text == "protected") {
            sym = SYM_KEY_PROTECTED;
        } else if (text == "public") {
            sym = SYM_KEY_PUBLIC;
        } else {
            sym = SYM_IDENT;
        }
    } else if (isNum(ch)) {

        text += ch;
        getChar();

        while (isNum(ch)) {
            text += ch;
            getChar();
        }

    }
}



TrivialCppParser::TrivialCppParser(QObject *parent)
    : QObject{parent}
{

}
