/****************************************************************************
 *
 * Propeller2 assembler symbol table
 *
 * Copyright (C) 2019 Jürgen Buchmüller <pullmoll@t-online.de>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/
#include "p2symboltable.h"

P2SymbolTableClass::P2SymbolTableClass()
    : m_symbols()
    , m_references()
{
}

/**
 * @brief Clear the symbol table
 */
void P2SymbolTableClass::clear()
{
    m_symbols.clear();
    m_references.clear();
}

/**
 * @brief Return the number of symols in the table
 * @param key optional name of the symbol to return the count for
 * @return Number of symbols
 */
int P2SymbolTableClass::count(const QString& name) const
{
    if (name.isEmpty())
        return m_symbols.count();
    return m_symbols.count(name);
}

/**
 * @brief Check if the symbol table contains a name
 * @param name symbol name to check for
 * @return true if known, or false if unknown
 */
bool P2SymbolTableClass::contains(const QString& name) const
{
    return m_symbols.contains(name);
}

/**
 * @brief Insert a symbol into the symbol table
 * @param symbol const reference to the symbol to insert
 * @return false if the symbol was already in the table, or true if inserted
 */
bool P2SymbolTableClass::insert(const P2Symbol& symbol)
{
    if (m_symbols.contains(symbol.name()))
        return false;
    m_symbols.insert(symbol.name(), symbol);
    return true;
}

/**
 * @brief Insert a symbol name / value into the symbol table
 * @param name name of the new symbol
 * @param value initial value of the new symbol
 * @return false if the symbol was already in the table, or true if inserted
 */
bool P2SymbolTableClass::insert(const QString& name, const P2Atom& value)
{
    return insert(P2Symbol(name, value));
}

/**
 * @brief Set a symbol to a new value
 * @param name symbol name
 * @param value new symbol value
 * @return
 */
bool P2SymbolTableClass::set_atom(const QString& name, const P2Atom& value)
{
    if (!m_symbols.contains(name))
        return false;
    m_symbols[name].set_atom(value);
    return true;
}

/**
 * @brief Return a copy of the P2Symbol with %name
 * @param name name of the symbold
 * @return P2Symbol which may be empty, if the symbol name is not in the table
 */
P2Symbol P2SymbolTableClass::symbol(const QString& name) const
{
    return m_symbols.value(name);
}

p2_union_e P2SymbolTableClass::type(const QString& name) const
{
    return m_symbols.value(name).type();
}

/**
 * @brief Return the QVariant::Type for the value of the symbol with %name
 * @param name of the symbol to check for
 * @return QVariant::Type of the value
 */


P2Word P2SymbolTableClass::definition(const QString& name) const
{
    return m_symbols.value(name).definition();
}

const QList<P2Symbol> P2SymbolTableClass::references_in(int lineno) const
{
    QList<P2Symbol> symbols;
    QStringList names = m_references.values(lineno);
    foreach(const QString& name, names)
        symbols += m_symbols.values(name);
    return symbols;
}

P2Word P2SymbolTableClass::reference(const QString& name, int idx) const
{
    if (!m_symbols.contains(name))
        return P2Word();
    return m_symbols[name].reference(idx);
}

const QList<int> P2SymbolTableClass::references(const QString& name) const
{
    QList<int> references = m_references.keys(name);
    QMap<int,int> sorted;
    foreach(int lineno, references)
        sorted.insert(lineno, 1);
    return sorted.keys();
}

bool P2SymbolTableClass::add_reference(int lineno, const QString& name, const P2Word& word)
{
    if (m_references.contains(lineno, name))
        return true;
    m_references.insert(lineno, name);
    if (!m_symbols.contains(name))
        return false;
    m_symbols[name].add_reference(lineno, word);
    return true;
}

/**
 * @brief Return a symbol's atom
 * The symbol values are stored as P2Atoms
 */
const P2Atom& P2SymbolTableClass::atom(const QString& name) const
{
    const P2Symbol sym = m_symbols.value(name);
    return sym.atom();
}

QStringList P2SymbolTableClass::names() const
{
    QStringList names;
    foreach (const P2Symbol sym, m_symbols)
        names += sym.name();
    names.sort();
    return names;
}

const p2_symbols_hash_t& P2SymbolTableClass::symbols() const
{
    return m_symbols;
}

const QMultiHash<int,QString>& P2SymbolTableClass::references() const
{
    return m_references;
}
