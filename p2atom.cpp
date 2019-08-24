#include "p2atom.h"

P2Atom::P2Atom()
    : m_type(Invalid)
    , m_data()
{
}

P2Atom::P2Atom(bool value)
    : m_type(Byte)
    , m_data()
{
    set(Byte, value & 1);
}

P2Atom::P2Atom(p2_BYTE value)
    : m_type(Byte)
    , m_data()
{
    set(Byte, value);
}

P2Atom::P2Atom(p2_WORD value)
    : m_type(Word)
    , m_data()
{
    set(Word, value);
}

P2Atom::P2Atom(p2_LONG value)
    : m_type(Long)
    , m_data()
{
    set(Long, value);
}

P2Atom::P2Atom(p2_QUAD value)
    : m_type(Quad)
    , m_data()
{
    set(Quad, value);
}

/**
 * @brief Clear the atom
 */
void P2Atom::clear()
{
    m_data.clear();
    m_type = Invalid;
}

/**
 * @brief Return true, if the atom is invalid
 * @return true if empty, or false otherwise
 */
bool P2Atom::isNull() const
{
    return m_type == Invalid;
}

/**
 * @brief Return true, if the atom contains no data
 * @return true if empty, or false otherwise
 */
bool P2Atom::isEmpty() const
{
    return m_data.isEmpty();
}

/**
 * @brief Return true, if the atom is valid, i.e. contains data
 * @return true if valid, or false otherwise
 */
bool P2Atom::isValid() const
{
    return m_type != Invalid;
}

/**
 * @brief Return the type of the atom, i.e. max size inserted
 * @return One of the %Type enumeration values
 */
P2Atom::Type P2Atom::type() const
{
    return m_type;
}

/**
 * @brief Set the type of the atom
 * @brie type one of the %Type enumeration values
 */
void P2Atom::setType(Type type)
{
    m_type = type;
    switch (type) {
    case Invalid:
        m_data.clear();
        break;
    case Byte:
        m_data.truncate(1);
        break;
    case Word:
        m_data.truncate(2);
        break;
    case Long:
        m_data.truncate(4);
        break;
    case Quad:
        m_data.truncate(8);
        break;
    case String:
        break;
    }
}

/**
 * @brief Append a number of bytes to the data
 * @param type new type of the atom
 * @param value with lower %nbits valid
 * @return truen on success, or false on error
 */
bool P2Atom::append(Type type, p2_QUAD value)
{
    switch (type) {
    case Invalid:
        break;
    case Byte:
        return append<Byte>(value);
    case Word:
        return append<Word>(value);
    case Long:
        return append<Long>(value);
    case Quad:
        return append<Quad>(value);
    case String:
        return append<String>(value);
    }
    return false;
}

bool P2Atom::append(int nbits, p2_QUAD value)
{
    if (nbits <= 0)
        return false;
    if (nbits <= 8)
        return append<Byte>(value);
    if (nbits <= 16)
        return append<Word>(value);
    if (nbits <= 32)
        return append<Long>(value);
    if (nbits <= 64)
        return append<Quad>(value);
    return false;
}

bool P2Atom::append(p2_QUAD value)
{
    return append(m_type, value);
}

bool P2Atom::append(const P2Atom& atom)
{
    m_data.append(atom.m_data);
    return true;
}

/**
 * @brief Set the data to a new value
 * @param type Type of the data to set
 * @param value with lower %nbits valid
 * @return true on success, or false on error
 */
bool P2Atom::set(Type type, p2_QUAD value)
{
    m_data.clear();
    m_type = type;
    return append(type, value);
}

/**
 * @brief Set the data to a new value
 * @param nbits number of bits to set
 * @param value with lower %nbits valid
 * @return true on success, or false on error
 */
bool P2Atom::set(int nbits, p2_QUAD value)
{
    m_data.clear();
    return append(nbits, value);
}

/**
 * @brief Set the data to a new value keeping the %m_type
 * @param value new value
 * @return true on success, or false on error
 */
bool P2Atom::set(p2_QUAD value)
{
    m_data.clear();
    return append(value);
}

/**
 * @brief Set atom to its one's complement (~) if flag is true
 * @param flag one's complement if true, leave unchanged otherwise
 */
void P2Atom::complement1(bool flag)
{
    if (!flag)
        return;
    switch (m_type) {
    case Invalid: return;
    case Byte:
        set(Byte, ~toByte());
        break;
    case Word:
        set(Word, ~toWord());
        break;
    case Long:
        set(Long, ~toLong());
        break;
    case Quad:
        set(Quad, ~toQuad());
        break;
    case String:
        Q_ASSERT(m_type);
    }
}

/**
 * @brief Set atom to its two's complement (-) if flag is true
 * @param flag two's complement if true, leave unchanged otherwise
 */
void P2Atom::complement2(bool flag)
{
    if (!flag)
        return;
    switch (m_type) {
    case Invalid:
        return;
    case Byte:
        set(Byte, ~toByte() + 1);
        break;
    case Word:
        set(Word, ~toWord() + 1);
        break;
    case Long:
        set(Long, ~toLong() + 1);
        break;
    case Quad:
        set(Quad, ~toQuad() + 1);
        break;
    case String:
        Q_ASSERT(m_type);
    }
}

/**
 * @brief Set atom to its logical not (!) value
 * @param flag do the not if true, leave unchanged otherwise
 */
void P2Atom::logical_not(bool flag)
{
    if (!flag)
        return;
    switch (m_type) {
    case Invalid:
        return;
    case Byte:
        set(Byte, toByte() ? 0 : 1);
        break;
    case Word:
        set(Word, toWord() ? 0 : 1);
        break;
    case Long:
        set(Long, toLong() ? 1 : 0);
        break;
    case Quad:
        set(Quad, toQuad() ? 0 : 1);
        break;
    case String:
        Q_ASSERT(m_type);
    }
}

void P2Atom::make_bool(bool flag)
{
    if (!flag)
        return;
    switch (m_type) {
    case Invalid:
        return;
    case Byte:
        set(Byte, toByte() ? 1 : 0);
        break;
    case Word:
        set(Word, toWord() ? 1 : 0);
        break;
    case Long:
        set(Long, toLong() ? 1 : 0);
        break;
    case Quad:
        set(Quad, toQuad() ? 1 : 0);
        break;
    case String:
        Q_ASSERT(m_type);
    }
}

void P2Atom::unary_dec(bool flag)
{
    if (!flag)
        return;
    switch (m_type) {
    case Invalid:
        return;
    case Byte:
        set(Byte, toByte() - 1);
        break;
    case Word:
        set(Word, toWord() - 1);
        break;
    case Long:
        set(Long, toLong() - 1);
        break;
    case Quad:
        set(Quad, toQuad() - 1);
        break;
    case String:
        Q_ASSERT(m_type);
    }
}

void P2Atom::unary_inc(bool flag)
{
    if (!flag)
        return;
    switch (m_type) {
    case Invalid:
        return;
    case Byte:
        set(Byte, toByte() + 1);
        break;
    case Word:
        set(Word, toWord() + 1);
        break;
    case Long:
        set(Long, toLong() + 1);
        break;
    case Quad:
        set(Quad, toQuad() + 1);
        break;
    case String:
        Q_ASSERT(m_type);
    }
}

void P2Atom::arith_mul(p2_QUAD val)
{
    switch (m_type) {
    case Invalid:
        return;
    case Byte:
        set(Byte, toByte() * val);
        break;
    case Word:
        set(Word, toWord() * val);
        break;
    case Long:
        set(Long, toLong() * val);
        break;
    case Quad:
        set(Quad, toQuad() * val);
        break;
    case String:
        Q_ASSERT(m_type);
    }

}

void P2Atom::arith_div(p2_QUAD val)
{
    if (!val) {
        // Division by zero
        set(~0u);
        return;
    }
    switch (m_type) {
    case Invalid:
        return;
    case Byte:
        set(Byte, toByte() / val);
        break;
    case Word:
        set(Word, toWord() / val);
        break;
    case Long:
        set(Long, toLong() / val);
        break;
    case Quad:
        set(Quad, toQuad() / val);
        break;
    case String:
        Q_ASSERT(m_type);
    }

}

void P2Atom::arith_mod(p2_QUAD val)
{
    if (!val) {
        // Division by zero
        set(~0u);
        return;
    }
    switch (m_type) {
    case Invalid:
        return;
    case Byte:
        set(Byte, toByte() % val);
        break;
    case Word:
        set(Word, toWord() % val);
        break;
    case Long:
        set(Long, toLong() % val);
        break;
    case Quad:
        set(Quad, toQuad() % val);
        break;
    case String:
        Q_ASSERT(m_type);
    }

}

void P2Atom::arith_add(p2_QUAD val)
{
    if (!val)
        return;
    switch (m_type) {
    case Invalid:
        return;
    case Byte:
        set(Byte, toByte() + val);
        break;
    case Word:
        set(Word, toWord() + val);
        break;
    case Long:
        set(Long, toLong() + val);
        break;
    case Quad:
        set(Quad, toQuad() + val);
        break;
    case String:
        Q_ASSERT(m_type);
    }
}

void P2Atom::arith_sub(p2_QUAD val)
{
    if (!val)
        return;
    switch (m_type) {
    case Invalid:
        return;
    case Byte:
        set(Byte, toByte() - val);
        break;
    case Word:
        set(Word, toWord() - val);
        break;
    case Long:
        set(Long, toLong() - val);
        break;
    case Quad:
        set(Quad, toQuad() - val);
        break;
    case String:
        Q_ASSERT(m_type);
    }
}

void P2Atom::binary_shl(p2_QUAD bits)
{
    if (!bits)
        return;
    switch (m_type) {
    case Invalid:
        return;
    case Byte:
        set(toLong() << bits);
        break;
    case Word:
        set(toLong() << bits);
        break;
    case Long:
        set(toLong() << bits);
        break;
    case Quad:
        set(toQuad() << bits);
        break;
    case String:
        Q_ASSERT(m_type);
    }
}

void P2Atom::binary_shr(p2_QUAD bits)
{
    if (!bits)
        return;
    switch (m_type) {
    case Invalid:
        return;
    case Byte:
        set(toByte() >> bits);
        break;
    case Word:
        set(toWord() >> bits);
        break;
    case Long:
        set(toLong() >> bits);
        break;
    case Quad:
        set(toQuad() >> bits);
        break;
    case String:
        Q_ASSERT(m_type);
    }
}

void P2Atom::binary_and(p2_QUAD mask)
{
    switch (m_type) {
    case Invalid:
        return;
    case Byte:
        set(toByte() & mask);
        break;
    case Word:
        set(toWord() & mask);
        break;
    case Long:
        set(toLong() & mask);
        break;
    case Quad:
        set(toQuad() & mask);
        break;
    case String:
        Q_ASSERT(m_type);
    }
}

void P2Atom::binary_xor(p2_QUAD mask)
{
    switch (m_type) {
    case Invalid:
        return;
    case Byte:
        set(toByte() ^ mask);
        break;
    case Word:
        set(toWord() ^ mask);
        break;
    case Long:
        set(toLong() ^ mask);
        break;
    case Quad:
        set(toQuad() ^ mask);
        break;
    case String:
        Q_ASSERT(m_type);
    }
}

void P2Atom::binary_or(p2_QUAD mask)
{
    switch (m_type) {
    case Invalid:
        return;
    case Byte:
        set(toByte() | mask);
        break;
    case Word:
        set(toWord() | mask);
        break;
    case Long:
        set(toLong() | mask);
        break;
    case Quad:
        set(toQuad() | mask);
        break;
    case String:
        Q_ASSERT(m_type);
    }
}

/**
 * @brief Return data as a single byte
 * @param ok optional pointer to a bool set to true if data is available
 * @return One p2_BYTE
 */
p2_BYTE P2Atom::toByte(bool* ok) const
{
    return value<p2_BYTE>(ok);
}

/**
 * @brief Return data as a single word
 * @param ok optional pointer to a bool set to true if data is available
 * @return One p2_WORD
 */
p2_WORD P2Atom::toWord(bool* ok) const
{
    return value<p2_WORD>(ok);
}

/**
 * @brief Return data as a single long
 * @param ok optional pointer to a bool set to true if data is available
 * @return One p2_LONG
 */
p2_LONG P2Atom::toLong(bool* ok) const
{
    return value<p2_LONG>(ok);
}

/**
 * @brief Return data as a single quad
 * @param ok optional pointer to a bool set to true if data is available
 * @return One p2_LONG
 */
p2_QUAD P2Atom::toQuad(bool* ok) const
{
    return value<p2_QUAD>(ok);
}

/**
 * @brief Return data as a vector of bytes
 * @return p2_BYTEs of all data
 */
p2_BYTES P2Atom::toBYTES() const
{
    const int bytes = m_data.size();
    p2_BYTES result(bytes, 0);
    if (bytes > 0)
        memcpy(result.data(), m_data.constData(), static_cast<size_t>(bytes));
    return result;
}

/**
 * @brief Return data as a vector of words
 * @return p2_WORDs of all data
 */
p2_WORDS P2Atom::toWORDS() const
{
    const int bytes = m_data.size();
    p2_WORDS result((bytes + 1)  / 2, 0);
    if (bytes > 0)
        memcpy(result.data(), m_data.constData(), static_cast<size_t>(bytes));
    return result;
}

/**
 * @brief Return data as a vector of longs
 * @return p2_LONGs of all data
 */
p2_LONGS P2Atom::toLONGS() const
{
    const int bytes = m_data.size();
    p2_LONGS result((bytes + 3) / 4);
    if (bytes > 0)
        memcpy(result.data(), m_data.constData(), static_cast<size_t>(bytes));
    return result;
}

bool P2Atom::operator==(const P2Atom& other)
{
    return m_data == other.m_data;
}