/****************************************************************************
 *
 * Propeller2 assembler table model class
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
#pragma once
#include <QAbstractTableModel>
#include <QColor>
#include <QFont>
#include <QFontMetrics>
#include <QIcon>

#include "p2asm.h"

class P2AsmModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum column_e {
        c_Origin,
        c_Opcode,
        c_Tokens,
        c_Symbols,
        c_Errors,
        c_Source,
    };
    enum format_e {
        f_bin,
        f_hex,
        f_oct
    };

    explicit P2AsmModel(P2Asm* p2asm, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    format_e opcode_format() const { return m_opcode_format; }
    QSize sizeHint(column_e column) const { return m_size_normal.value(column); }

public slots:
    void invalidate();
    void setOpcodeFormat(format_e format);
    void updateSizes();

private:
    P2Asm* m_asm;
    format_e m_opcode_format;
    QFont m_font;
    QFont m_bold;
    QIcon m_error;
    QHash<column_e,QString> m_header;
    QHash<column_e,QSize> m_size_normal;
    QHash<column_e,QSize> m_size_bold;
    QHash<column_e,QRgb> m_background;
    QHash<column_e,int> m_header_alignment;
    QHash<column_e,int> m_text_alignment;
    QString tokenToolTip(const p2_token_v& tokens, const QStringList& words, const QString& bgd) const;
    QString symbolsToolTip(const P2AsmSymTbl& symbols, const QStringList& defined, const QString& bgd) const;
    QString errorsToolTip(const QStringList& list, const QString& bgd) const;
};
