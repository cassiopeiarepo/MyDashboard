#ifndef TRIVIALCPPPARSER_H
#define TRIVIALCPPPARSER_H

#include <QObject>

/*
 Parsuje nagłówki *.h




  */

class TrivialCppParser;

class TrivialCppLex {

public:
    TrivialCppLex(TrivialCppParser* _parser, QString* _input) : parser(_parser), input(_input), sym(SYM_UNKNOWN), ch(' '),
        line(0), pos(-1), index(-1) {
        input_size = _input->size();
        getChar();
        next();
    }

    enum Sym {
        SYM_UNKNOWN,
        SYM_EOS,
        SYM_IDENT,
        SYM_KEY_CLASS,
        SYM_KEY_PRIVATE,
        SYM_KEY_PROTECTED,
        SYM_KEY_PUBLIC,
    };

    Sym next();
    //Sym forward();

    Sym getSym() { return sym; }
    const QString& getText() { return text; }

private:
    TrivialCppParser* parser;
    QString* input;

    Sym sym;
    QChar ch;
    int line;
    int pos;
    int index;
    int input_size;
    QString text;

    QChar getChar();
    void skipWhitespace();

    bool isAlpha(QChar ch);
    bool isNum(QChar ch);
};


class TrivialSimpleCppParser : public QObject
{
    Q_OBJECT
public:
    explicit TrivialSimpleCppParser(QObject *parent = nullptr);

    void parseFile(const QString& filename);


signals:
    void sigError();
    void sigLexSymUnknown();

    friend class TrivialCppLex;
};

#endif // TRIVIALCPPPARSER_H
