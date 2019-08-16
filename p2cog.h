/****************************************************************************
 *
 * P2 emulator Cog class
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
#include <QVariant>
#include "p2defs.h"
#include "p2hub.h"

class P2Cog : public QObject
{
    Q_OBJECT
public:
    P2Cog(uchar cog_id = 0, P2Hub* hub = nullptr, QObject* parent = nullptr);

    p2_LONG decode();
    p2_opword_t ir() const { return IR; }
    p2_LONG pc() const { return PC; }
    p2_LONG d() const { return D; }
    p2_LONG s() const { return S; }
    p2_LONG q() const { return Q; }
    p2_LONG c() const { return C; }
    p2_LONG z() const { return Z; }

    p2_LONG rd_cog(p2_LONG addr) const;
    void wr_cog(p2_LONG addr, p2_LONG val);
    p2_LONG rd_lut(p2_LONG addr) const;
    void wr_lut(p2_LONG addr, p2_LONG val);
    p2_LONG rd_mem(p2_LONG addr) const;
    void wr_mem(p2_LONG addr, p2_LONG val);

private:
    P2Hub* HUB;             //!< pointer to the HUB, i.e. the parent of the Propeller2 cog
    quint64 xoro_s[2];      //!< Xoroshiro128 PRNG state
    p2_LONG ID;             //!< this COG's ID
    p2_LONG PC;             //!< program counter
    p2_flags_t FL;          //!< flags register
    p2_opword_t IR;         //!< instruction register
    p2_LONG S;              //!< value of S
    p2_LONG D;              //!< value of D
    p2_LONG Q;              //!< value of Q
    p2_LONG C;              //!< current carry flag
    p2_LONG Z;              //!< current zero flag
    QVariant S_next;        //!< next instruction's S value
    QVariant S_aug;         //!< augment next S with this value, if set
    QVariant D_aug;         //!< augment next D with this value, if set

    p2_cog_t COG;           //!< COG memory (512 longs)
    p2_lut_t LUT;           //!< LUT memory (512 longs)
    uchar *MEM;             //!< HUB memory pointer
    p2_LONG MEMSIZE;        //!< HUB memory size

    //! update C if the WC flag bit is set
    template <typename T>
    void updateC(T c) {
        if (IR.op.wc)
            C = static_cast<p2_LONG>(c) & 1;
    }

    //! update Z if the WC flag bit is set
    template <typename T>
    void updateZ(T z) {
        if (IR.op.wz)
            Z = static_cast<p2_LONG>(z) & 1;
    }

    //! update D, i.e. write result to COG
    template <typename T>
    void updateD(T d) {
        COG.RAM[IR.op.dst] = static_cast<p2_LONG>(d);
    }

    //! update PC (program counter)
    template <typename T>
    void updatePC(T d) {
        // TODO: handle switch between COG, LUT, and HUB ?
        PC = static_cast<p2_LONG>(d);
    }

    //! update PC (program counter)
    template <typename T>
    void updateLUT(p2_LONG addr, T d) {
        LUT.RAM[addr & 0x1ff] = static_cast<p2_LONG>(d);
    }

    //! augment #S or use #S, if the flag bit is set, then possibly set S from next_S
    template <typename T>
    void augmentS(T f) {
        if (f) {
            if (S_aug.isValid()) {
                S = S_aug.toUInt() | IR.op.src;
                S_aug.clear();
            } else {
                S = IR.op.src;
            }
        }
        if (S_next.isValid()) {
            // set S to next_S
            S = S_next.toUInt();
            S_next.clear();
        }
    }

    //! augment #D or use #D, if the flag bit is set
    template <typename T>
    void augmentD(T f) {
        if (f) {
            if (D_aug.isValid()) {
                D = D_aug.toUInt() | IR.op.dst;
                D_aug.clear();
            } else {
                D = IR.op.dst;
            }
        }
    }

    //! update PA, i.e. write result to port A
    template <typename T>
    void updatePA(T d) {
        LUT.REG.PA = static_cast<p2_LONG>(d);
        if (HUB)
            HUB->wr_PA(LUT.REG.PA);
    }

    //! update PB, i.e. write result to port A
    template <typename T>
    void updatePB(T d) {
        LUT.REG.PB = static_cast<p2_LONG>(d);
        if (HUB)
            HUB->wr_PB(LUT.REG.PA);
    }

    //! update PTRA, i.e. write result to pointer A
    template <typename T>
    void updatePTRA(T d) {
        if (HUB)
            HUB->wr_LONG(LUT.REG.PTRA, static_cast<p2_LONG>(d));
    }

    //! update PTRB, i.e. write result to pointer B
    template <typename T>
    void updatePTRB(T d) {
        if (HUB)
            HUB->wr_LONG(LUT.REG.PTRB, static_cast<p2_LONG>(d));
    }

    //! return a signed 32 bit value for val[15:0]
    template <typename T>
    qint32 S16(T val) {
        return static_cast<qint32>(static_cast<qint16>(val));
    }

    //! return the usigned 32 bit value for val[15:0]
    template <typename T>
    p2_LONG U16(T val) {
        return static_cast<p2_LONG>(static_cast<quint16>(val));
    }

    //! return the signed 32 bit value for val[31:0]
    template <typename T>
    qint32 S32(T val) {
        return static_cast<qint32>(val);
    }

    //! return the usigned 32 bit value for val[31:0]
    template <typename T>
    p2_LONG U32(T val) {
        return static_cast<p2_LONG>(val);
    }

    //! return the 64 bit sign extended value
    template <typename T>
    qint64 SX64(T val) {
        return static_cast<qint64>(static_cast<qint32>(val));
    }

    //! return the usigned 64 bit value
    template <typename T>
    quint64 U64(T val) {
        return static_cast<quint64>(val);
    }

    //! return the upper half of a 64 bit value as 32 bit unsigned
    template <typename T>
    p2_LONG U32H(T val) {
        return static_cast<p2_LONG>(static_cast<quint64>(val) >> 32);
    }

    //! return the lower half of a 64 bit value as 32 bit unsigned
    template <typename T>
    p2_LONG U32L(T val) {
        return static_cast<p2_LONG>(val);
    }

    //! most significant bit in a 32 bit word
    static const p2_LONG MSB = 1u << 31;

    //! least significant bit in a 32 bit word
    static const p2_LONG LSB = 1u;

    //! least significant nibble in a 32 bit word
    static const p2_LONG LNIBBLE = 0x0000000fu;

    //! least significant byte in a 32 bit word
    static const p2_LONG LBYTE = 0x000000ffu;

    //! least significant word in a 32 bit word
    static const p2_LONG LWORD = 0x0000ffffu;

    //! most significant word in a 32 bit word
    static const p2_LONG HWORD = 0xffff0000u;

    //! bits without sign bit in a 32 bit word
    static const p2_LONG IMAX = 0x7fffffffu;

    //! all bits in a 32 bit word
    static const p2_LONG UMAX = 0xffffffffu;

    //! least significant 20 bits for an address value
    static const p2_LONG ADDR = (1u << 20) - 1;

    //! most significant 23 bits for an augmentation value
    static const p2_LONG AUG = 0xfffffe00;

    //! upper word max / mask in a 64 bit unsigned
    static const quint64 HMAX = Q_UINT64_C(0xffffffff00000000);

    //! lower word max / mask in a 64 bit unsigned
    static const quint64 LMAX = Q_UINT64_C(0x00000000ffffffff);

    bool conditional(p2_cond_e cond);
    bool conditional(unsigned cond);
    p2_BYTE msbit(p2_LONG val);
    p2_BYTE ones(p2_LONG val);
    p2_BYTE parity(p2_LONG val);
    quint64 rotl(quint64 val, uchar shift);
    quint64 rnd();

    uint op_nop();
    uint op_ror();
    uint op_rol();
    uint op_shr();
    uint op_shl();
    uint op_rcr();
    uint op_rcl();
    uint op_sar();
    uint op_sal();

    uint op_add();
    uint op_addx();
    uint op_adds();
    uint op_addsx();
    uint op_sub();
    uint op_subx();
    uint op_subs();
    uint op_subsx();

    uint op_cmp();
    uint op_cmpx();
    uint op_cmps();
    uint op_cmpsx();
    uint op_cmpr();
    uint op_cmpm();
    uint op_subr();
    uint op_cmpsub();

    uint op_fge();
    uint op_fle();
    uint op_fges();
    uint op_fles();
    uint op_sumc();
    uint op_sumnc();
    uint op_sumz();
    uint op_sumnz();

    uint op_testb_w();
    uint op_testbn_w();
    uint op_testb_and();
    uint op_testbn_and();
    uint op_testb_or();
    uint op_testbn_or();
    uint op_testb_xor();
    uint op_testbn_xor();

    uint op_bitl();
    uint op_bith();
    uint op_bitc();
    uint op_bitnc();
    uint op_bitz();
    uint op_bitnz();
    uint op_bitrnd();
    uint op_bitnot();

    uint op_and();
    uint op_andn();
    uint op_or();
    uint op_xor();
    uint op_muxc();
    uint op_muxnc();
    uint op_muxz();
    uint op_muxnz();

    uint op_mov();
    uint op_not();
    uint op_not_d();
    uint op_abs();
    uint op_neg();
    uint op_negc();
    uint op_negnc();
    uint op_negz();
    uint op_negnz();

    uint op_incmod();
    uint op_decmod();
    uint op_zerox();
    uint op_signx();
    uint op_encod();
    uint op_ones();
    uint op_test();
    uint op_testn();

    uint op_setnib();
    uint op_setnib_altsn();
    uint op_getnib();
    uint op_getnib_altgn();
    uint op_rolnib();
    uint op_rolnib_altgn();
    uint op_setbyte();
    uint op_setbyte_altsb();
    uint op_getbyte();
    uint op_getbyte_altgb();
    uint op_rolbyte();
    uint op_rolbyte_altgb();

    uint op_setword();
    uint op_setword_altsw();
    uint op_getword();
    uint op_getword_altgw();
    uint op_rolword();
    uint op_rolword_altgw();

    uint op_altsn();
    uint op_altsn_d();
    uint op_altgn();
    uint op_altgn_d();
    uint op_altsb();
    uint op_altsb_d();
    uint op_altgb();
    uint op_altgb_d();

    uint op_altsw();
    uint op_altsw_d();
    uint op_altgw();
    uint op_altgw_d();

    uint op_altr();
    uint op_altr_d();
    uint op_altd();
    uint op_altd_d();
    uint op_alts();
    uint op_alts_d();
    uint op_altb();
    uint op_altb_d();
    uint op_alti();
    uint op_alti_d();

    uint op_setr();
    uint op_setd();
    uint op_sets();
    uint op_decod();
    uint op_decod_d();
    uint op_bmask();
    uint op_bmask_d();
    uint op_crcbit();
    uint op_crcnib();

    uint op_muxnits();
    uint op_muxnibs();
    uint op_muxq();
    uint op_movbyts();
    uint op_mul();
    uint op_muls();
    uint op_sca();
    uint op_scas();

    uint op_addpix();
    uint op_mulpix();
    uint op_blnpix();
    uint op_mixpix();
    uint op_addct1();
    uint op_addct2();
    uint op_addct3();

    uint op_wmlong();
    uint op_rqpin();
    uint op_rdpin();
    uint op_rdlut();
    uint op_rdbyte();
    uint op_rdword();
    uint op_rdlong();

    uint op_popa();
    uint op_popb();
    uint op_calld();
    uint op_resi3();
    uint op_resi2();
    uint op_resi1();
    uint op_resi0();
    uint op_reti3();
    uint op_reti2();
    uint op_reti1();
    uint op_reti0();
    uint op_callpa();
    uint op_callpb();

    uint op_djz();
    uint op_djnz();
    uint op_djf();
    uint op_djnf();
    uint op_ijz();
    uint op_ijnz();
    uint op_tjz();
    uint op_tjnz();
    uint op_tjf();
    uint op_tjnf();
    uint op_tjs();
    uint op_tjns();
    uint op_tjv();

    uint op_jint();
    uint op_jct1();
    uint op_jct2();
    uint op_jct3();
    uint op_jse1();
    uint op_jse2();
    uint op_jse3();
    uint op_jse4();
    uint op_jpat();
    uint op_jfbw();
    uint op_jxmt();
    uint op_jxfi();
    uint op_jxro();
    uint op_jxrl();
    uint op_jatn();
    uint op_jqmt();

    uint op_jnint();
    uint op_jnct1();
    uint op_jnct2();
    uint op_jnct3();
    uint op_jnse1();
    uint op_jnse2();
    uint op_jnse3();
    uint op_jnse4();
    uint op_jnpat();
    uint op_jnfbw();
    uint op_jnxmt();
    uint op_jnxfi();
    uint op_jnxro();
    uint op_jnxrl();
    uint op_jnatn();
    uint op_jnqmt();
    uint op_1011110_1();
    uint op_1011111_0();
    uint op_setpat();

    uint op_wrpin();
    uint op_akpin();
    uint op_wxpin();
    uint op_wypin();
    uint op_wrlut();
    uint op_wrbyte();
    uint op_wrword();
    uint op_wrlong();

    uint op_pusha();
    uint op_pushb();
    uint op_rdfast();
    uint op_wrfast();
    uint op_fblock();
    uint op_xinit();
    uint op_xstop();
    uint op_xzero();
    uint op_xcont();

    uint op_rep();
    uint op_coginit();

    uint op_qmul();
    uint op_qdiv();
    uint op_qfrac();
    uint op_qsqrt();
    uint op_qrotate();
    uint op_qvector();

    uint op_hubset();
    uint op_cogid();
    uint op_cogstop();
    uint op_locknew();
    uint op_lockret();
    uint op_locktry();
    uint op_lockrel();
    uint op_qlog();
    uint op_qexp();

    uint op_rfbyte();
    uint op_rfword();
    uint op_rflong();
    uint op_rfvar();
    uint op_rfvars();
    uint op_wfbyte();
    uint op_wfword();
    uint op_wflong();

    uint op_getqx();
    uint op_getqy();
    uint op_getct();
    uint op_getrnd();
    uint op_getrnd_cz();

    uint op_setdacs();
    uint op_setxfrq();
    uint op_getxacc();
    uint op_waitx();
    uint op_setse1();
    uint op_setse2();
    uint op_setse3();
    uint op_setse4();
    uint op_pollint();
    uint op_pollct1();
    uint op_pollct2();
    uint op_pollct3();
    uint op_pollse1();
    uint op_pollse2();
    uint op_pollse3();
    uint op_pollse4();
    uint op_pollpat();
    uint op_pollfbw();
    uint op_pollxmt();
    uint op_pollxfi();
    uint op_pollxro();
    uint op_pollxrl();
    uint op_pollatn();
    uint op_pollqmt();

    uint op_waitint();
    uint op_waitct1();
    uint op_waitct2();
    uint op_waitct3();
    uint op_waitse1();
    uint op_waitse2();
    uint op_waitse3();
    uint op_waitse4();
    uint op_waitpat();
    uint op_waitfbw();
    uint op_waitxmt();
    uint op_waitxfi();
    uint op_waitxro();
    uint op_waitxrl();
    uint op_waitatn();

    uint op_allowi();
    uint op_stalli();
    uint op_trgint1();
    uint op_trgint2();
    uint op_trgint3();
    uint op_nixint1();
    uint op_nixint2();
    uint op_nixint3();
    uint op_setint1();
    uint op_setint2();
    uint op_setint3();
    uint op_setq();
    uint op_setq2();

    uint op_push();
    uint op_pop();
    uint op_jmp();
    uint op_call();
    uint op_ret();
    uint op_calla();
    uint op_reta();
    uint op_callb();
    uint op_retb();

    uint op_jmprel();
    uint op_skip();
    uint op_skipf();
    uint op_execf();
    uint op_getptr();
    uint op_getbrk();
    uint op_cogbrk();
    uint op_brk();

    uint op_setluts();
    uint op_setcy();
    uint op_setci();
    uint op_setcq();
    uint op_setcfrq();
    uint op_setcmod();
    uint op_setpiv();
    uint op_setpix();
    uint op_cogatn();

    uint op_testp_w();
    uint op_testpn_w();
    uint op_testp_and();
    uint op_testpn_and();
    uint op_testp_or();
    uint op_testpn_or();
    uint op_testp_xor();
    uint op_testpn_xor();

    uint op_dirl();
    uint op_dirh();
    uint op_dirc();
    uint op_dirnc();
    uint op_dirz();
    uint op_dirnz();
    uint op_dirrnd();
    uint op_dirnot();

    uint op_outl();
    uint op_outh();
    uint op_outc();
    uint op_outnc();
    uint op_outz();
    uint op_outnz();
    uint op_outrnd();
    uint op_outnot();

    uint op_fltl();
    uint op_flth();
    uint op_fltc();
    uint op_fltnc();
    uint op_fltz();
    uint op_fltnz();
    uint op_fltrnd();
    uint op_fltnot();

    uint op_drvl();
    uint op_drvh();
    uint op_drvc();
    uint op_drvnc();
    uint op_drvz();
    uint op_drvnz();
    uint op_drvrnd();
    uint op_drvnot();

    uint op_splitb();
    uint op_mergeb();
    uint op_splitw();
    uint op_mergew();
    uint op_seussf();
    uint op_seussr();
    uint op_rgbsqz();
    uint op_rgbexp();
    uint op_xoro32();

    uint op_rev();
    uint op_rczr();
    uint op_rczl();
    uint op_wrc();
    uint op_wrnc();
    uint op_wrz();
    uint op_wrnz();
    uint op_modcz();

    uint op_jmp_abs();
    uint op_call_abs();
    uint op_calla_abs();
    uint op_callb_abs();
    uint op_calld_abs();
    uint op_loc_pa();
    uint op_loc_pb();
    uint op_loc_ptra();
    uint op_loc_ptrb();

    uint op_augs();
    uint op_augd();
};
