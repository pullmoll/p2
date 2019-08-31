/****************************************************************************
 *
 * Propeller2 assembler source code delegate
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
#include "p2sourcedelegate.h"
#include "p2asmmodel.h"
#include <QPainter>

P2SourceDelegate::P2SourceDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void P2SourceDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    const P2AsmModel* model = qobject_cast<const P2AsmModel*>(index.model());
    Q_ASSERT(model);
    QVariant v_words = model->data(index, Qt::UserRole);
    const P2Words words = qvariant_cast<P2Words>(v_words);
    const P2Word hword = model->highlight(index);

    QStyleOptionViewItem opt(option);
    initStyleOption(&opt, index);
    opt.showDecorationSelected = true;

    const bool highlight = opt.state & QStyle::State_HasFocus ? true : false;
    const QString line = model->data(index).toString();
    const int ll = line.length() ? line.length() : 1;

    QRect rect = option.rect;
    QVector<QRect> bounding(ll);
    const int flags = static_cast<int>(opt.displayAlignment) |
                      Qt::TextSingleLine | Qt::TextDontClip | Qt::TextExpandTabs | Qt::TextForceLeftToRight;
    const int lw = opt.fontMetrics.size(flags, line).width();
    const int x0 = rect.x();


    painter->save();
    painter->setClipRect(rect);

    // fill the background
    painter->setBackgroundMode(Qt::OpaqueMode);
    if (highlight) {
        int size = painter->pen().width();
        QBrush brush = opt.backgroundBrush;
        brush.setColor(brush.color().darker(105));
        painter->fillRect(opt.rect.adjusted(0,0,-size,-size), brush);
        painter->drawRect(opt.rect);
    } else {
        painter->fillRect(opt.rect, opt.backgroundBrush);
    }

    painter->setBackgroundMode(Qt::TransparentMode);
    painter->setFont(opt.font);
    painter->setPen(p2_palette(color_source, highlight));

    // paint all text character wise to collect the bounding rects
    int pos = 0;
    foreach(const QChar ch, line) {
        rect.setX(x0 + pos * lw / ll);
        painter->drawText(rect, flags, ch, &bounding[pos]);
        pos++;
    }

    // re-draw tokenized words
    foreach(const P2Word& word, words) {
        const int len = word.len();
        int pos = word.pos();
        const QString text = line.mid(pos, len);

        QPalette pal;
        QColor color = p2_palette(color_source, highlight);

        p2_token_e tok = word.tok();
        switch (tok) {
        case t_comment:
        case t_comment_eol:
        case t_comment_lcurly:
        case t_comment_rcurly:
            color = p2_palette(color_comment, highlight);
            break;

        case t_COMMA:
            color = p2_palette(color_comma, highlight);
            break;

        case t_str_const:
            color = p2_palette(color_str_const, highlight);
            break;

        case t_bin_const:
            color = p2_palette(color_bin_const, highlight);
            break;

        case t_byt_const:
            color = p2_palette(color_byt_const, highlight);
            break;

        case t_dec_const:
            color = p2_palette(color_dec_const, highlight);
            break;

        case t_hex_const:
            color = p2_palette(color_hex_const, highlight);
            break;

        case t_real_const:
            color = p2_palette(color_real_const, highlight);
            break;

        case t_locsym:
            color = p2_palette(color_locsym, highlight);
            break;

        case t_symbol:
            color = p2_palette(color_symbol, highlight);
            break;

        default:
            if (Token.is_type(tok, tm_section))
                color = p2_palette(color_section, highlight);
            if (Token.is_type(tok, tm_conditional))
                color = p2_palette(color_conditional, highlight);
            if (Token.is_type(tok, tm_mnemonic))
                color = p2_palette(color_instruction, highlight);
            if (Token.is_type(tok, tm_wcz_suffix))
                color = p2_palette(color_wcz_suffix, highlight);
            if (Token.is_type(tok, tm_expression))
                color = p2_palette(color_expression, highlight);
            break;
        }
        painter->setPen(color);

        // draw the character
        QRect box;
        foreach(const QChar ch, text) {
            QRect br = bounding[pos++];
            painter->drawText(br, flags, ch);
            box = box.united(br);
        }

        if (word == hword) {
            painter->setPen(QColor(0x00,0x00,0xff));
            painter->drawRect(box);
        }
    }

    painter->restore();
}
