/****************************************************************************
 *
 * Propeller2 assembler
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
#include <QObject>
#include <QString>
#include <QVariant>
#include <QHash>
#include "p2defs.h"
#include "p2token.h"
#include "p2atom.h"
#include "p2asmsymtbl.h"


class P2AsmWord
{
public:
    explicit P2AsmWord(const QString& str = QString(), int pos = 0, int end = 0)
        : m_str(str), m_tok(t_invalid), m_pos(pos), m_end(end)
    {}
    explicit P2AsmWord(p2_token_e tok, const QString& str, int pos, int end)
        : m_str(str), m_tok(tok), m_pos(pos), m_end(end)
    {}

    p2_token_e tok() const { return m_tok; }
    const QString& str() const { return m_str; }
    int pos() const { return m_pos; }
    int len() const { return m_end + 1 - m_pos; }
    int end() const { return m_end; }
    void setToken(p2_token_e tok) { m_tok = tok; }
    void append(const QString& str, int end) { m_str.append(str); m_end = end; }

private:
    QString m_str;
    p2_token_e m_tok;
    int m_pos;
    int m_end;
};
typedef QVector<P2AsmWord> P2AsmWords;
Q_DECLARE_METATYPE(P2AsmWord);
Q_DECLARE_METATYPE(P2AsmWords);

typedef QHash<int, p2_LONG> p2_PC_hash_t;
typedef QHash<int, p2_opcode_u> p2_IR_hash_t;
typedef QHash<int, P2AsmWords> p2_words_hash_t;
typedef QMultiHash<int, QString> p2_error_hash_t;

/**
 * @brief The P2Asm class implements an Propeller2 assembler
 */
class P2Asm : public QObject
{
    Q_OBJECT

public:
    enum Section {
        sec_dat,
        sec_con,
        sec_pub,
        sec_pri,
        sec_var
    };

    explicit P2Asm(QObject *parent = nullptr);
    ~P2Asm();


    void clear();
    void pass_clear();

    int pass() const;

    const QStringList& source() const;
    const QString& source(int idx) const;

    int count() const;
    const p2_PC_hash_t& PC_hash() const;
    p2_LONG PC_value(int lineno) const;
    bool PC_available(int lineno) const;

    const p2_IR_hash_t& IR_hash() const;
    p2_opcode_u IR_value(int lineno) const;
    bool IR_available(int lineno) const;

    const p2_words_hash_t& words_hash() const;
    P2AsmWords words(int lineno) const;
    bool words_available(int lineno) const;

    const p2_error_hash_t& error_hash() const;
    QStringList errors(int lineno) const;

    const P2AsmSymTbl& symbols() const;

    bool assemble_pass();
    bool assemble(const QStringList& source);
    bool assemble(const QString& filename);

signals:
    void Error(int m_lineno, QString message);

public slots:
    void setSource(const QStringList& source);

private:
    int m_pass;                             //!< current pass
    QStringList m_source;                   //!< source code as QStringList
    QStringList m_listing;                  //!< listing as QStringList
    p2_PC_hash_t m_hash_PC;                 //!< optional program counters per line
    p2_IR_hash_t m_hash_IR;                 //!< optional instruction register (opcode) per line
    p2_words_hash_t m_hash_words;           //!< optional words per line
    p2_error_hash_t m_hash_error;           //!< optional (multiple) error messages per line
    P2AsmSymTbl m_symbols;                  //!< symbol table
    int m_lineno;                           //!< current line number
    int m_in_curly;                         //!< parser inside curly braces comment level
    QString m_line;                         //!< current line of source
    QString m_error;                        //!< error message from parameters parser
    p2_LONG m_next_PC;                      //!< next program counter
    p2_LONG m_curr_PC;                      //!< current program counter (origin of the instruction)
    p2_LONG m_last_PC;                      //!< last program counter (maximum of next_pc)
    p2_LONG m_advance;                      //!< advance by n longs
    p2_opcode_u m_IR;                       //!< current instruction register
    P2Atom m_data;                          //!< data generated by BYTE, WORD, LONG instructions
    P2AsmWords m_words;                     //!< current P2AsmWords on the line
    p2_token_e m_instr;                     //!< current instruction token
    QString m_symbol;                       //!< currently defined symbol (first name on the line before an instruction token)
    QHash<Section,QString> m_function;      //!< currently defined function symbol, i.e. a name w/o initial dot (.)
    Section m_section;                      //!< currently selected section
    int m_wcnt;                             //!< count of (relevant) words
    int m_widx;                             //!< token (and word) index

    union {
        p2_BYTE BYTES[MEM_SIZE];            //!< as bytes
        p2_WORD WORDS[MEM_SIZE/2];          //!< as words
        p2_LONG LONGS[MEM_SIZE/4];          //!< as longs
    } MEM;                                  //!< binary data

private:
    enum imm_to_e {
        immediate_none,
        immediate_im,
        immediate_wz,
        immediate_wc
    };
    QHash<Section,QString> m_sections;      //!< currently defined function symbol, i.e. a name w/o initial dot (.)

    int left();
    void results(bool opcode = false);
    QString expand_tabs(const QString& src);
    bool split_and_tokenize(const QString& m_line);
    p2_cond_e conditional(p2_token_e cond);
    p2_cond_e parse_modcz(p2_token_e cond);
    bool skip_spc(int& pos, const QString& str);
    P2Atom make_atom();
    P2Atom from_bin(int& pos, const QString& str);
    P2Atom from_byt(int& pos, const QString& str);
    P2Atom from_oct(int& pos, const QString& str);
    P2Atom from_dec(int& pos, const QString& str);
    P2Atom from_hex(int& pos, const QString& str);
    P2Atom from_str(int& pos, const QString& str);
    QString find_symbol(Section sect = sec_con, const QString& func = QString(), const QString& local = QString());
    P2Atom parse_atom(int& pos, const QString& word);
    P2Atom parse_mulops(int& pos, const QString& str);
    P2Atom parse_addops(int& pos, const QString& str);
    P2Atom parse_shiftops(int& pos, const QString& str);
    P2Atom parse_binops(int& pos, const QString& str);
    P2Atom parse_subexpression(int& pos, const QString& str);
    P2Atom parse_expression(imm_to_e imm_to = immediate_none);

    bool end_of_line(bool binary = true);
    bool parse_comma();
    void optional_comma();
    bool optional_wcz();
    bool optional_wc();
    bool optional_wz();

    bool asm_assign();
    bool asm_org();
    bool asm_orgh();

    bool parse_with_wcz();
    bool parse_with_wc();
    bool parse_with_wz();
    bool parse_inst();
    bool parse_d_imm_s_wcz();
    bool parse_d_imm_s_wc();
    bool parse_d_imm_s_wz();
    bool parse_wz_d_imm_s();
    bool parse_d_imm_s_nnn(uint max = 7);
    bool parse_d_imm_s();
    bool parse_d_cz();
    bool parse_cz();
    bool parse_cccc_zzzz_wcz();
    bool parse_d();
    bool parse_wz_d();
    bool parse_imm_d();
    bool parse_imm_d_wcz();
    bool parse_imm_d_wc();
    bool parse_imm_s();
    bool parse_imm_s_wcz();
    bool parse_pc_abs();
    bool parse_ptr_pc_abs();
    bool parse_imm23(QVector<p2_inst7_e> aug);

    bool asm_byte();
    bool asm_word();
    bool asm_long();
    bool asm_res();
    bool asm_fit();

    bool asm_nop();
    bool asm_ror();
    bool asm_rol();
    bool asm_shr();
    bool asm_shl();
    bool asm_rcr();
    bool asm_rcl();
    bool asm_sar();
    bool asm_sal();

    bool asm_add();
    bool asm_addx();
    bool asm_adds();
    bool asm_addsx();
    bool asm_sub();
    bool asm_subx();
    bool asm_subs();
    bool asm_subsx();

    bool asm_cmp();
    bool asm_cmpx();
    bool asm_cmps();
    bool asm_cmpsx();
    bool asm_cmpr();
    bool asm_cmpm();
    bool asm_subr();
    bool asm_cmpsub();

    bool asm_fge();
    bool asm_fle();
    bool asm_fges();
    bool asm_fles();
    bool asm_sumc();
    bool asm_sumnc();
    bool asm_sumz();
    bool asm_sumnz();

    bool asm_testb_w();
    bool asm_testbn_w();
    bool asm_testb_and();
    bool asm_testbn_and();
    bool asm_testb_or();
    bool asm_testbn_or();
    bool asm_testb_xor();
    bool asm_testbn_xor();

    bool asm_bitl();
    bool asm_bith();
    bool asm_bitc();
    bool asm_bitnc();
    bool asm_bitz();
    bool asm_bitnz();
    bool asm_bitrnd();
    bool asm_bitnot();

    bool asm_and();
    bool asm_andn();
    bool asm_or();
    bool asm_xor();
    bool asm_muxc();
    bool asm_muxnc();
    bool asm_muxz();
    bool asm_muxnz();

    bool asm_mov();
    bool asm_not();
    bool asm_not_d();
    bool asm_abs();
    bool asm_neg();
    bool asm_negc();
    bool asm_negnc();
    bool asm_negz();
    bool asm_negnz();

    bool asm_incmod();
    bool asm_decmod();
    bool asm_zerox();
    bool asm_signx();
    bool asm_encod();
    bool asm_ones();
    bool asm_test();
    bool asm_testn();

    bool asm_setnib();
    bool asm_setnib_altsn();
    bool asm_getnib();
    bool asm_getnib_altgn();
    bool asm_rolnib();
    bool asm_rolnib_altgn();
    bool asm_setbyte();
    bool asm_setbyte_altsb();
    bool asm_getbyte();
    bool asm_getbyte_altgb();
    bool asm_rolbyte();
    bool asm_rolbyte_altgb();

    bool asm_setword();
    bool asm_setword_altsw();
    bool asm_getword();
    bool asm_getword_altgw();
    bool asm_rolword();
    bool asm_rolword_altgw();

    bool asm_altsn();
    bool asm_altsn_d();
    bool asm_altgn();
    bool asm_altgn_d();
    bool asm_altsb();
    bool asm_altsb_d();
    bool asm_altgb();
    bool asm_altgb_d();

    bool asm_altsw();
    bool asm_altsw_d();
    bool asm_altgw();
    bool asm_altgw_d();

    bool asm_altr();
    bool asm_altr_d();
    bool asm_altd();
    bool asm_altd_d();
    bool asm_alts();
    bool asm_alts_d();
    bool asm_altb();
    bool asm_altb_d();
    bool asm_alti();
    bool asm_alti_d();

    bool asm_setr();
    bool asm_setd();
    bool asm_sets();
    bool asm_decod();
    bool asm_decod_d();
    bool asm_bmask();
    bool asm_bmask_d();
    bool asm_crcbit();
    bool asm_crcnib();

    bool asm_muxnits();
    bool asm_muxnibs();
    bool asm_muxq();
    bool asm_movbyts();
    bool asm_mul();
    bool asm_muls();
    bool asm_sca();
    bool asm_scas();

    bool asm_addpix();
    bool asm_mulpix();
    bool asm_blnpix();
    bool asm_mixpix();
    bool asm_addct1();
    bool asm_addct2();
    bool asm_addct3();

    bool asm_wmlong();
    bool asm_rqpin();
    bool asm_rdpin();
    bool asm_rdlut();
    bool asm_rdbyte();
    bool asm_rdword();
    bool asm_rdlong();

    bool asm_popa();
    bool asm_popb();
    bool asm_calld();
    bool asm_resi3();
    bool asm_resi2();
    bool asm_resi1();
    bool asm_resi0();
    bool asm_reti3();
    bool asm_reti2();
    bool asm_reti1();
    bool asm_reti0();
    bool asm_callpa();
    bool asm_callpb();

    bool asm_djz();
    bool asm_djnz();
    bool asm_djf();
    bool asm_djnf();
    bool asm_ijz();
    bool asm_ijnz();
    bool asm_tjz();
    bool asm_tjnz();
    bool asm_tjf();
    bool asm_tjnf();
    bool asm_tjs();
    bool asm_tjns();
    bool asm_tjv();

    bool asm_jint();
    bool asm_jct1();
    bool asm_jct2();
    bool asm_jct3();
    bool asm_jse1();
    bool asm_jse2();
    bool asm_jse3();
    bool asm_jse4();
    bool asm_jpat();
    bool asm_jfbw();
    bool asm_jxmt();
    bool asm_jxfi();
    bool asm_jxro();
    bool asm_jxrl();
    bool asm_jatn();
    bool asm_jqmt();

    bool asm_jnint();
    bool asm_jnct1();
    bool asm_jnct2();
    bool asm_jnct3();
    bool asm_jnse1();
    bool asm_jnse2();
    bool asm_jnse3();
    bool asm_jnse4();
    bool asm_jnpat();
    bool asm_jnfbw();
    bool asm_jnxmt();
    bool asm_jnxfi();
    bool asm_jnxro();
    bool asm_jnxrl();
    bool asm_jnatn();
    bool asm_jnqmt();
    bool asm_1011110_1();
    bool asm_1011111_0();
    bool asm_setpat();

    bool asm_wrpin();
    bool asm_akpin();
    bool asm_wxpin();
    bool asm_wypin();
    bool asm_wrlut();
    bool asm_wrbyte();
    bool asm_wrword();
    bool asm_wrlong();

    bool asm_pusha();
    bool asm_pushb();
    bool asm_rdfast();
    bool asm_wrfast();
    bool asm_fblock();
    bool asm_xinit();
    bool asm_xstop();
    bool asm_xzero();
    bool asm_xcont();

    bool asm_rep();
    bool asm_coginit();

    bool asm_qmul();
    bool asm_qdiv();
    bool asm_qfrac();
    bool asm_qsqrt();
    bool asm_qrotate();
    bool asm_qvector();

    bool asm_hubset();
    bool asm_cogid();
    bool asm_cogstop();
    bool asm_locknew();
    bool asm_lockret();
    bool asm_locktry();
    bool asm_lockrel();
    bool asm_qlog();
    bool asm_qexp();

    bool asm_rfbyte();
    bool asm_rfword();
    bool asm_rflong();
    bool asm_rfvar();
    bool asm_rfvars();
    bool asm_wfbyte();
    bool asm_wfword();
    bool asm_wflong();

    bool asm_getqx();
    bool asm_getqy();
    bool asm_getct();
    bool asm_getrnd();
    bool asm_getrnd_cz();

    bool asm_setdacs();
    bool asm_setxfrq();
    bool asm_getxacc();
    bool asm_waitx();
    bool asm_setse1();
    bool asm_setse2();
    bool asm_setse3();
    bool asm_setse4();
    bool asm_pollint();
    bool asm_pollct1();
    bool asm_pollct2();
    bool asm_pollct3();
    bool asm_pollse1();
    bool asm_pollse2();
    bool asm_pollse3();
    bool asm_pollse4();
    bool asm_pollpat();
    bool asm_pollfbw();
    bool asm_pollxmt();
    bool asm_pollxfi();
    bool asm_pollxro();
    bool asm_pollxrl();
    bool asm_pollatn();
    bool asm_pollqmt();

    bool asm_waitint();
    bool asm_waitct1();
    bool asm_waitct2();
    bool asm_waitct3();
    bool asm_waitse1();
    bool asm_waitse2();
    bool asm_waitse3();
    bool asm_waitse4();
    bool asm_waitpat();
    bool asm_waitfbw();
    bool asm_waitxmt();
    bool asm_waitxfi();
    bool asm_waitxro();
    bool asm_waitxrl();
    bool asm_waitatn();

    bool asm_allowi();
    bool asm_stalli();
    bool asm_trgint1();
    bool asm_trgint2();
    bool asm_trgint3();
    bool asm_nixint1();
    bool asm_nixint2();
    bool asm_nixint3();
    bool asm_setint1();
    bool asm_setint2();
    bool asm_setint3();
    bool asm_setq();
    bool asm_setq2();

    bool asm_push();
    bool asm_pop();
    bool asm_jmp();
    bool asm_call();
    bool asm_ret();
    bool asm_calla();
    bool asm_reta();
    bool asm_callb();
    bool asm_retb();

    bool asm_jmprel();
    bool asm_skip();
    bool asm_skipf();
    bool asm_execf();
    bool asm_getptr();
    bool asm_getbrk();
    bool asm_cogbrk();
    bool asm_brk();

    bool asm_setluts();
    bool asm_setcy();
    bool asm_setci();
    bool asm_setcq();
    bool asm_setcfrq();
    bool asm_setcmod();
    bool asm_setpiv();
    bool asm_setpix();
    bool asm_cogatn();

    bool asm_testp_w();
    bool asm_testpn_w();
    bool asm_testp_and();
    bool asm_testpn_and();
    bool asm_testp_or();
    bool asm_testpn_or();
    bool asm_testp_xor();
    bool asm_testpn_xor();

    bool asm_dirl();
    bool asm_dirh();
    bool asm_dirc();
    bool asm_dirnc();
    bool asm_dirz();
    bool asm_dirnz();
    bool asm_dirrnd();
    bool asm_dirnot();

    bool asm_outl();
    bool asm_outh();
    bool asm_outc();
    bool asm_outnc();
    bool asm_outz();
    bool asm_outnz();
    bool asm_outrnd();
    bool asm_outnot();

    bool asm_fltl();
    bool asm_flth();
    bool asm_fltc();
    bool asm_fltnc();
    bool asm_fltz();
    bool asm_fltnz();
    bool asm_fltrnd();
    bool asm_fltnot();

    bool asm_drvl();
    bool asm_drvh();
    bool asm_drvc();
    bool asm_drvnc();
    bool asm_drvz();
    bool asm_drvnz();
    bool asm_drvrnd();
    bool asm_drvnot();

    bool asm_splitb();
    bool asm_mergeb();
    bool asm_splitw();
    bool asm_mergew();
    bool asm_seussf();
    bool asm_seussr();
    bool asm_rgbsqz();
    bool asm_rgbexp();
    bool asm_xoro32();

    bool asm_rev();
    bool asm_rczr();
    bool asm_rczl();
    bool asm_wrc();
    bool asm_wrnc();
    bool asm_wrz();
    bool asm_wrnz();
    bool asm_modcz();
    bool asm_setscp();
    bool asm_getscp();

    bool asm_jmp_abs();
    bool asm_call_abs();
    bool asm_calla_abs();
    bool asm_callb_abs();
    bool asm_calld_pa_abs();
    bool asm_calld_pb_abs();
    bool asm_calld_ptra_abs();
    bool asm_calld_ptrb_abs();
    bool asm_loc();
    bool asm_loc_pa();
    bool asm_loc_pb();
    bool asm_loc_ptra();
    bool asm_loc_ptrb();

    bool asm_augs();
    bool asm_augd();
};