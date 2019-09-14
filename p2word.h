#pragma once
#include "p2defs.h"
#include "p2tokens.h"

class P2Word
{
public:
    explicit P2Word(p2_TOKEN_e tok = t_invalid,
                    const QStringRef& ref = QStringRef(),
                    int lineno = 0);

    bool isValid() const;
    const QStringRef ref() const;
    const QString str() const;
    p2_TOKEN_e tok() const;
    int lineno() const;
    int pos() const;
    int len() const;
    int end() const;

    void set_tok(p2_TOKEN_e tok);
    void set_lineno(const int lineno);

    static bool remove(QVector<P2Word>& words, p2_TOKEN_e tok);

    bool operator==(const P2Word& other) const;
private:
    QStringRef m_ref;
    p2_TOKEN_e m_tok;
    int m_lineno;
};
Q_DECLARE_METATYPE(P2Word);

typedef QList<P2Word> P2Words;
Q_DECLARE_METATYPE(P2Words);

//! A QHash of (multiple) P2Word per line number
typedef QMultiHash<int,P2Word> p2_word_hash_t;
Q_DECLARE_METATYPE(p2_word_hash_t);

//! A QHash of the list of P2Word per line number
typedef QHash<int,P2Words> p2_words_hash_t;
Q_DECLARE_METATYPE(p2_words_hash_t);
