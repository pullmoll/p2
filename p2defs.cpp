/****************************************************************************
 *
 * Propeller2 constants, enumerations, and opcode structure
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
#include <QString>
#include "p2defs.h"

//! digits of binary numbers
const char bin_digits[] = "01_";

//! digits of byte indices
const char byt_digits[] = "0123_";

//! digits of octal numbers
const char oct_digits[] = "01234567_";

//! digits of decimal numbers
const char dec_digits[] = "0123456789_";

//! digits of hexadecimal numbers
const char hex_digits[] = "0123456789ABCDEF_";

//! Size of the COG memory in longs
constexpr p2_LONG COG_SIZE = 0x200;

//! Mask for the COG memory longs
constexpr p2_LONG COG_MASK = (COG_SIZE-1);

//! Size of the LUT memory in longs
const p2_LONG LUT_SIZE = 0x200;

//! Mask for the LUT memory longs
const p2_LONG LUT_MASK = (LUT_SIZE-1);


//! Number of longs where the PC switches from *1 scale to *4 scale
const p2_LONG PC_LONGS = (COG_SIZE+LUT_SIZE);

//! Lowest HUB memory address
const p2_LONG HUB_ADDR = (PC_LONGS*4);

//! Size of the HUB memory in bytes (1MiB)
extern const p2_LONG MEM_SIZE;

//! most significant bit in a 32 bit word
const p2_LONG MSB = 1u << 31;

//! least significant bit in a 32 bit word
const p2_LONG LSB = 1u;

//! least significant nibble in a 32 bit word
const p2_LONG LNIBBLE = 0x0000000fu;

//! least significant byte in a 32 bit word
const p2_LONG LBYTE = 0x000000ffu;

//! least significant word in a 32 bit word
const p2_LONG LWORD = 0x0000ffffu;

//! most significant word in a 32 bit word
const p2_LONG HWORD = 0xffff0000u;

//! bits without sign bit in a 32 bit word
const p2_LONG IMAX = 0x7fffffffu;

//! no bits in a 32 bit word
const p2_LONG ZERO = 0x00000000u;

//! all bits in a 32 bit word
const p2_LONG FULL = 0xffffffffu;

//! least significant 20 bits for an address value
const p2_LONG A20MASK = (1u << 20) - 1;

//! most significant 23 bits for an augmentation value
const p2_LONG AUGMASK = 0xfffffe00;

//! upper word max / mask in a 64 bit unsigned
const p2_QUAD HMAX = Q_UINT64_C(0xffffffff00000000);

//! lower word max / mask in a 64 bit unsigned
const p2_QUAD LMAX = Q_UINT64_C(0x00000000ffffffff);

const QString template_str_address = QStringLiteral("COG[000] ");

const QString template_str_opcode_bin = QStringLiteral("EEEE OOOOOOO CZI DDDDDDDDD SSSSSSSSS ");
const QString template_str_opcode_byt = QStringLiteral("F FF FFF FFF FFF ");
const QString template_str_opcode_oct = QStringLiteral("37777777777 ");
const QString template_str_opcode_hex = QStringLiteral("FFFFFFFF ");

const QString template_str_tokens = QStringLiteral("T");
const QString template_str_symbols = QStringLiteral("S");
const QString template_str_errors = QStringLiteral("😞");
const QString template_str_instruction = QStringLiteral(" label_name IF_NC_AND_NZ  INSTRUCTION #$1ff,#$1ff,#7 XORCZ ");
const QString template_str_description = QStringLiteral(" Some description string... ");

QString format_opcode_bin(const p2_opcode_u& IR)
{
    return QString("%1 %2 %3%4%5 %6 %7")
            .arg(IR.op.cond, 4, 2, QChar('0'))
            .arg(IR.op.inst, 7, 2, QChar('0'))
            .arg(IR.op.wc,   1, 2, QChar('0'))
            .arg(IR.op.wz,   1, 2, QChar('0'))
            .arg(IR.op.im,   1, 2, QChar('0'))
            .arg(IR.op.dst,  9, 2, QChar('0'))
            .arg(IR.op.src,  9, 2, QChar('0'));
}

QString format_opcode_byt(const p2_opcode_u& IR)
{
    return QString("%1 %2 %3%4%5 %6 %7")
            .arg(IR.op.cond, 1, 16, QChar('0'))
            .arg(IR.op.inst, 2, 16, QChar('0'))
            .arg(IR.op.wc,   1, 16, QChar('0'))
            .arg(IR.op.wz,   1, 16, QChar('0'))
            .arg(IR.op.im,   1, 16, QChar('0'))
            .arg(IR.op.dst,  3, 16, QChar('0'))
            .arg(IR.op.src,  3, 16, QChar('0'));
}

QString format_opcode_oct(const p2_opcode_u& IR)
{
    return QString("%1")
            .arg(IR.opcode, 11, 8, QChar('0'));
}

QString format_opcode_hex(const p2_opcode_u& IR)
{
    return QString("%1")
            .arg(IR.opcode, 8, 16, QChar('0'));
}

QString format_data_bin(const p2_opcode_u& IR)
{
    return QString("%1 %2 %3 %4")
            .arg((IR.opcode >> 24) & 0xff, 8, 2, QChar('0'))
            .arg((IR.opcode >> 16) & 0xff, 8, 2, QChar('0'))
            .arg((IR.opcode >>  8) & 0xff, 8, 2, QChar('0'))
            .arg((IR.opcode >>  0) & 0xff, 8, 2, QChar('0'));
}

QString format_data_byt(const p2_opcode_u& IR)
{
    return QString("%1 %2 %3 %4")
             .arg((IR.opcode >> 24) & 0xff, 2, 16, QChar('0'))
             .arg((IR.opcode >> 16) & 0xff, 2, 16, QChar('0'))
             .arg((IR.opcode >>  8) & 0xff, 2, 16, QChar('0'))
             .arg((IR.opcode >>  0) & 0xff, 2, 16, QChar('0'));
}

QString format_data_oct(const p2_opcode_u& IR)
{
    return QString("%1")
            .arg(IR.opcode, 11, 8, QChar('0'));
}

QString format_data_hex(const p2_opcode_u& IR)
{
    return QString("%1")
            .arg(IR.opcode, 8, 16, QChar('0'));
}

QString format_opcode(const p2_opcode_u& IR, const p2_opcode_format_e fmt)
{
    switch (fmt) {
    case fmt_bin: return format_opcode_bin(IR);
    case fmt_byt: return format_opcode_byt(IR);
    case fmt_oct: return format_opcode_oct(IR);
    case fmt_hex: return format_opcode_hex(IR);
    }
    return QStringLiteral("<invalid format>");
}

QString format_data(const p2_opcode_u& IR, const p2_opcode_format_e fmt)
{
    switch (fmt) {
    case fmt_bin: return format_data_bin(IR);
    case fmt_byt: return format_data_byt(IR);
    case fmt_oct: return format_data_oct(IR);
    case fmt_hex: return format_data_hex(IR);
    }
    return QStringLiteral("<invalid format>");
}
