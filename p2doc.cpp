/****************************************************************************
 *
 * Propeller2 instructions documentation implementation
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
#include "p2doc.h"
#include "p2tokens.h"

// Global instance
P2Doc Doc;

P2Doc::P2Doc()
    : m_masks()
    , m_pattern()
    , m_brief()
    , m_instr()
    , m_token()
{
    m_masks += MaskMatch(p2_mask_opx24,0);
    m_masks += MaskMatch(p2_mask_opsrc,0);
    m_masks += MaskMatch(p2_mask_opdst,0);
    m_masks += MaskMatch(p2_mask_inst9,0);
    m_masks += MaskMatch(p2_mask_inst8,0);
    m_masks += MaskMatch(p2_mask_inst7,0);

    doc_nop(p2_ROR);
    doc_ror(p2_ROR);
    doc_rol(p2_ROL);
    doc_shr(p2_SHR);
    doc_shl(p2_SHL);
    doc_rcr(p2_RCR);
    doc_rcl(p2_RCL);
    doc_sar(p2_SAR);
    doc_sal(p2_SAL);
    doc_add(p2_ADD);
    doc_addx(p2_ADDX);
    doc_adds(p2_ADDS);
    doc_addsx(p2_ADDSX);
    doc_sub(p2_SUB);
    doc_subx(p2_SUBX);
    doc_subs(p2_SUBS);
    doc_subsx(p2_SUBSX);
    doc_cmp(p2_CMP);
    doc_cmpx(p2_CMPX);
    doc_cmps(p2_CMPS);
    doc_cmpsx(p2_CMPSX);
    doc_cmpr(p2_CMPR);
    doc_cmpm(p2_CMPM);
    doc_subr(p2_SUBR);
    doc_cmpsub(p2_CMPSUB);
    doc_fge(p2_FGE);
    doc_fle(p2_FLE);
    doc_fges(p2_FGES);
    doc_fles(p2_FLES);
    doc_sumc(p2_SUMC);
    doc_sumnc(p2_SUMNC);
    doc_sumz(p2_SUMZ);
    doc_sumnz(p2_SUMNZ);

    doc_testb_w(p2_TESTB_WC);
    doc_testb_w(p2_TESTB_WZ);
    doc_testbn_w(p2_TESTBN_WZ);
    doc_testbn_w(p2_TESTBN_WC);
    doc_testb_and(p2_TESTB_ANDZ);
    doc_testb_and(p2_TESTB_ANDC);
    doc_testbn_and(p2_TESTBN_ANDZ);
    doc_testbn_and(p2_TESTBN_ANDC);
    doc_testb_or(p2_TESTB_ORC);
    doc_testb_or(p2_TESTB_ORZ);
    doc_testbn_or(p2_TESTBN_ORC);
    doc_testbn_or(p2_TESTBN_ORZ);
    doc_testb_xor(p2_TESTB_XORC);
    doc_testb_xor(p2_TESTB_XORZ);
    doc_testbn_xor(p2_TESTBN_XORC);
    doc_testbn_xor(p2_TESTBN_XORZ);

    doc_bitl(p2_BITL_eol);
    doc_bitl(p2_BITL_WCZ);
    doc_bith(p2_BITH_eol);
    doc_bith(p2_BITH_WCZ);
    doc_bitc(p2_BITC_eol);
    doc_bitc(p2_BITC_WCZ);
    doc_bitnc(p2_BITNC_eol);
    doc_bitnc(p2_BITNC_WCZ);
    doc_bitz(p2_BITZ_eol);
    doc_bitz(p2_BITZ_WCZ);
    doc_bitnz(p2_BITNZ_eol);
    doc_bitnz(p2_BITNZ_WCZ);
    doc_bitrnd(p2_BITRND_eol);
    doc_bitrnd(p2_BITRND_WCZ);
    doc_bitnot(p2_BITNOT_eol);
    doc_bitnot(p2_BITNOT_WCZ);

    doc_and(p2_AND);
    doc_andn(p2_ANDN);
    doc_or(p2_OR);
    doc_xor(p2_XOR);
    doc_muxc(p2_MUXC);
    doc_muxnc(p2_MUXNC);
    doc_muxz(p2_MUXZ);
    doc_muxnz(p2_MUXNZ);
    doc_mov(p2_MOV);
    doc_not(p2_NOT);
    doc_abs(p2_ABS);
    doc_neg(p2_NEG);
    doc_negc(p2_NEGC);

    doc_negnc(p2_NEGNC);
    doc_negz(p2_NEGZ);
    doc_negnz(p2_NEGNZ);
    doc_incmod(p2_INCMOD);
    doc_decmod(p2_DECMOD);
    doc_zerox(p2_ZEROX);
    doc_signx(p2_SIGNX);
    doc_encod(p2_ENCOD);
    doc_ones(p2_ONES);

    doc_test(p2_TEST);
    doc_testn(p2_TESTN);
    doc_setnib(p2_SETNIB_0);
    doc_setnib(p2_SETNIB_1);
    doc_getnib(p2_GETNIB_0);
    doc_getnib(p2_GETNIB_1);
    doc_rolnib(p2_ROLNIB_0);
    doc_rolnib(p2_ROLNIB_1);
    doc_setbyte(p2_SETBYTE);
    doc_getbyte(p2_GETBYTE);
    doc_rolbyte(p2_ROLBYTE);

    doc_setword_altsw(p2_SETWORD_ALTSW);
    doc_setword(p2_SETWORD);
    doc_getword_altgw(p2_GETWORD_ALTGW);
    doc_getword(p2_GETWORD);
    doc_rolword_altgw(p2_ROLWORD_ALTGW);
    doc_rolword(p2_ROLWORD_ALTGW);
    doc_rolword(p2_ROLWORD);
    doc_altsn_d(p2_ALTSN);
    doc_altsn(p2_ALTSN);
    doc_altgn_d(p2_ALTGN);
    doc_altgn(p2_ALTGN);

    doc_altsb_d(p2_ALTSB);
    doc_altsb(p2_ALTSB);
    doc_altgb_d(p2_ALTGB);
    doc_altgb(p2_ALTGB);
    doc_altsw_d(p2_ALTSW);
    doc_altsw(p2_ALTSW);
    doc_altgw_d(p2_ALTGW);
    doc_altgw(p2_ALTGW);

    doc_altr_d(p2_ALTR);
    doc_altr(p2_ALTR);
    doc_altd_d(p2_ALTD);
    doc_altd(p2_ALTD);
    doc_alts_d(p2_ALTS);
    doc_alts(p2_ALTS);
    doc_altb_d(p2_ALTB);
    doc_altb(p2_ALTB);

    doc_alti_d(p2_ALTI);
    doc_alti(p2_ALTI);
    doc_setr(p2_SETR);
    doc_setd(p2_SETD);
    doc_sets(p2_SETS);

    doc_decod_d(p2_DECOD);
    doc_decod(p2_DECOD);
    doc_bmask_d(p2_BMASK);
    doc_bmask(p2_BMASK);
    doc_crcbit(p2_CRCBIT);
    doc_crcnib(p2_CRCNIB);

    doc_muxnits(p2_MUXNITS);
    doc_muxnibs(p2_MUXNIBS);
    doc_muxq(p2_MUXQ);
    doc_movbyts(p2_MOVBYTS);

    doc_mul(p2_MUL);
    doc_muls(p2_MULS);

    doc_sca(p2_SCA);
    doc_scas(p2_SCAS);

    doc_addpix(p2_ADDPIX);
    doc_mulpix(p2_MULPIX);
    doc_blnpix(p2_BLNPIX);
    doc_mixpix(p2_MIXPIX);

    doc_addct1(p2_ADDCT1);
    doc_addct2(p2_ADDCT2);
    doc_addct3(p2_ADDCT3);
    doc_wmlong(p2_WMLONG);

    doc_rqpin(p2_RQPIN);
    doc_rdpin(p2_RDPIN);

    doc_rdlut(p2_RDLUT);
    doc_rdbyte(p2_RDBYTE);
    doc_rdword(p2_RDWORD);

    doc_rdlong(p2_RDLONG);

    doc_calld(p2_CALLD);

    doc_callpa(p2_CALLPA);
    doc_callpb(p2_CALLPB);

    doc_djz(p2_DJZ);
    doc_djnz(p2_DJNZ);
    doc_djf(p2_DJF);
    doc_djnf(p2_DJNF);
    doc_ijz(p2_IJZ);
    doc_ijnz(p2_IJNZ);
    doc_tjz(p2_TJZ);
    doc_tjnz(p2_TJNZ);
    doc_tjf(p2_TJF);
    doc_tjnf(p2_TJNF);
    doc_tjs(p2_TJS);
    doc_tjns(p2_TJNS);
    doc_tjv(p2_TJV);

    doc_jint(p2_OPDST_JINT);
    doc_jct1(p2_OPDST_JCT1);
    doc_jct2(p2_OPDST_JCT2);
    doc_jct3(p2_OPDST_JCT3);
    doc_jse1(p2_OPDST_JSE1);
    doc_jse2(p2_OPDST_JSE2);
    doc_jse3(p2_OPDST_JSE3);
    doc_jse4(p2_OPDST_JSE4);
    doc_jpat(p2_OPDST_JPAT);
    doc_jfbw(p2_OPDST_JFBW);
    doc_jxmt(p2_OPDST_JXMT);
    doc_jxfi(p2_OPDST_JXFI);
    doc_jxro(p2_OPDST_JXRO);
    doc_jxrl(p2_OPDST_JXRL);
    doc_jatn(p2_OPDST_JATN);
    doc_jqmt(p2_OPDST_JQMT);

    doc_jnint(p2_OPDST_JNINT);
    doc_jnct1(p2_OPDST_JNCT1);
    doc_jnct2(p2_OPDST_JNCT2);
    doc_jnct3(p2_OPDST_JNCT3);
    doc_jnse1(p2_OPDST_JNSE1);
    doc_jnse2(p2_OPDST_JNSE2);
    doc_jnse3(p2_OPDST_JNSE3);
    doc_jnse4(p2_OPDST_JNSE4);
    doc_jnpat(p2_OPDST_JNPAT);
    doc_jnfbw(p2_OPDST_JNFBW);
    doc_jnxmt(p2_OPDST_JNXMT);
    doc_jnxfi(p2_OPDST_JNXFI);
    doc_jnxro(p2_OPDST_JNXRO);
    doc_jnxrl(p2_OPDST_JNXRL);
    doc_jnatn(p2_OPDST_JNATN);
    doc_jnqmt(p2_OPDST_JNQMT);
    doc_1011110_1(p2_1011110_1);

    doc_1011111_0(p2_1011111_0);
    doc_setpat(p2_SETPAT);

    doc_akpin(p2_WRPIN);
    doc_wrpin(p2_WRPIN);
    doc_wxpin(p2_WXPIN);
    doc_wypin(p2_WYPIN);
    doc_wrlut(p2_WRLUT);
    doc_wrbyte(p2_WRBYTE);
    doc_wrword(p2_WRWORD);
    doc_wrlong(p2_WRLONG);
    doc_rdfast(p2_RDFAST);
    doc_wrfast(p2_WRFAST);
    doc_fblock(p2_FBLOCK);

    doc_xstop(p2_XINIT);
    doc_xinit(p2_XINIT);
    doc_xzero(p2_XZERO);
    doc_xcont(p2_XCONT);
    doc_rep(p2_REP);
    doc_coginit(p2_COGINIT);
    doc_qmul(p2_QMUL);
    doc_qdiv(p2_QDIV);
    doc_qfrac(p2_QFRAC);
    doc_qsqrt(p2_QSQRT);
    doc_qrotate(p2_QROTATE);
    doc_qvector(p2_QVECTOR);

    doc_hubset(p2_OPSRC_HUBSET);
    doc_cogid(p2_OPSRC_COGID);
    doc_cogstop(p2_OPSRC_COGSTOP);
    doc_locknew(p2_OPSRC_LOCKNEW);
    doc_lockret(p2_OPSRC_LOCKRET);
    doc_locktry(p2_OPSRC_LOCKTRY);
    doc_lockrel(p2_OPSRC_LOCKREL);
    doc_qlog(p2_OPSRC_QLOG);
    doc_qexp(p2_OPSRC_QEXP);

    doc_rfbyte(p2_OPSRC_RFBYTE);
    doc_rfword(p2_OPSRC_RFWORD);
    doc_rflong(p2_OPSRC_RFLONG);
    doc_rfvar(p2_OPSRC_RFVAR);
    doc_rfvars(p2_OPSRC_RFVARS);
    doc_wfbyte(p2_OPSRC_WFBYTE);
    doc_wfword(p2_OPSRC_WFWORD);
    doc_wflong(p2_OPSRC_WFLONG);

    doc_getqx(p2_OPSRC_GETQX);
    doc_getqy(p2_OPSRC_GETQY);
    doc_getct(p2_OPSRC_GETCT);
    doc_getrnd_cz(p2_OPSRC_GETRND);
    doc_getrnd(p2_OPSRC_GETRND);
    doc_setdacs(p2_OPSRC_SETDACS);
    doc_setxfrq(p2_OPSRC_SETXFRQ);
    doc_getxacc(p2_OPSRC_GETXACC);
    doc_waitx(p2_OPSRC_WAITX);
    doc_setse1(p2_OPSRC_SETSE1);
    doc_setse2(p2_OPSRC_SETSE2);
    doc_setse3(p2_OPSRC_SETSE3);
    doc_setse4(p2_OPSRC_SETSE4);

    doc_pollint(p2_OPX24_POLLINT);
    doc_pollct1(p2_OPX24_POLLCT1);
    doc_pollct2(p2_OPX24_POLLCT2);
    doc_pollct3(p2_OPX24_POLLCT3);
    doc_pollse1(p2_OPX24_POLLSE1);
    doc_pollse2(p2_OPX24_POLLSE2);
    doc_pollse3(p2_OPX24_POLLSE3);
    doc_pollse4(p2_OPX24_POLLSE4);
    doc_pollpat(p2_OPX24_POLLPAT);
    doc_pollfbw(p2_OPX24_POLLFBW);
    doc_pollxmt(p2_OPX24_POLLXMT);
    doc_pollxfi(p2_OPX24_POLLXFI);
    doc_pollxro(p2_OPX24_POLLXRO);
    doc_pollxrl(p2_OPX24_POLLXRL);
    doc_pollatn(p2_OPX24_POLLATN);
    doc_pollqmt(p2_OPX24_POLLQMT);
    doc_waitint(p2_OPX24_WAITINT);
    doc_waitct1(p2_OPX24_WAITCT1);
    doc_waitct2(p2_OPX24_WAITCT2);
    doc_waitct3(p2_OPX24_WAITCT3);
    doc_waitse1(p2_OPX24_WAITSE1);
    doc_waitse2(p2_OPX24_WAITSE2);
    doc_waitse3(p2_OPX24_WAITSE3);
    doc_waitse4(p2_OPX24_WAITSE4);
    doc_waitpat(p2_OPX24_WAITPAT);
    doc_waitfbw(p2_OPX24_WAITFBW);
    doc_waitxmt(p2_OPX24_WAITXMT);
    doc_waitxfi(p2_OPX24_WAITXFI);
    doc_waitxro(p2_OPX24_WAITXRO);
    doc_waitxrl(p2_OPX24_WAITXRL);
    doc_waitatn(p2_OPX24_WAITATN);
    doc_allowi(p2_OPX24_ALLOWI);
    doc_stalli(p2_OPX24_STALLI);
    doc_trgint1(p2_OPX24_TRGINT1);
    doc_trgint2(p2_OPX24_TRGINT2);
    doc_trgint3(p2_OPX24_TRGINT3);
    doc_nixint1(p2_OPX24_NIXINT1);
    doc_nixint2(p2_OPX24_NIXINT2);
    doc_nixint3(p2_OPX24_NIXINT3);

    doc_setint1(p2_OPSRC_SETINT1);
    doc_setint2(p2_OPSRC_SETINT2);
    doc_setint3(p2_OPSRC_SETINT3);
    doc_setq(p2_OPSRC_SETQ);
    doc_setq2(p2_OPSRC_SETQ2);
    doc_push(p2_OPSRC_PUSH);
    doc_pop(p2_OPSRC_POP);
    doc_jmp(p2_OPSRC_JMP);
    doc_call(p2_OPSRC_CALL_RET);
    doc_ret(p2_OPSRC_CALL_RET);
    doc_calla(p2_OPSRC_CALLA_RETA);
    doc_reta(p2_OPSRC_CALLA_RETA);
    doc_callb(p2_OPSRC_CALLB_RETB);
    doc_retb(p2_OPSRC_CALLB_RETB);
    doc_jmprel(p2_OPSRC_JMPREL);
    doc_skip(p2_OPSRC_SKIP);
    doc_skipf(p2_OPSRC_SKIPF);
    doc_execf(p2_OPSRC_EXECF);
    doc_getptr(p2_OPSRC_GETPTR);
    doc_cogbrk(p2_OPSRC_COGBRK);
    doc_getbrk(p2_OPSRC_COGBRK);
    doc_brk(p2_OPSRC_BRK);
    doc_setluts(p2_OPSRC_SETLUTS);
    doc_setcy(p2_OPSRC_SETCY);
    doc_setci(p2_OPSRC_SETCI);
    doc_setcq(p2_OPSRC_SETCQ);
    doc_setcfrq(p2_OPSRC_SETCFRQ);
    doc_setcmod(p2_OPSRC_SETCMOD);
    doc_setpiv(p2_OPSRC_SETPIV);
    doc_setpix(p2_OPSRC_SETPIX);
    doc_cogatn(p2_OPSRC_COGATN);
    doc_testp_w(p2_OPSRC_TESTP_W_DIRL);
    doc_dirl(p2_OPSRC_TESTP_W_DIRL);
    doc_testpn_w(p2_OPSRC_TESTPN_W_DIRH);
    doc_dirh(p2_OPSRC_TESTPN_W_DIRH);
    doc_testp_and(p2_OPSRC_TESTP_AND_DIRC);
    doc_dirc(p2_OPSRC_TESTP_AND_DIRC);
    doc_testpn_and(p2_OPSRC_TESTPN_AND_DIRNC);
    doc_dirnc(p2_OPSRC_TESTPN_AND_DIRNC);
    doc_testp_or(p2_OPSRC_TESTP_OR_DIRZ);
    doc_dirz(p2_OPSRC_TESTP_OR_DIRZ);
    doc_testpn_or(p2_OPSRC_TESTPN_OR_DIRNZ);
    doc_dirnz(p2_OPSRC_TESTPN_OR_DIRNZ);
    doc_testp_xor(p2_OPSRC_TESTP_XOR_DIRRND);
    doc_dirrnd(p2_OPSRC_TESTP_XOR_DIRRND);
    doc_testpn_xor(p2_OPSRC_TESTPN_XOR_DIRNOT);
    doc_dirnot(p2_OPSRC_TESTPN_XOR_DIRNOT);

    doc_outl(p2_OPSRC_OUTL);
    doc_outh(p2_OPSRC_OUTH);
    doc_outc(p2_OPSRC_OUTC);
    doc_outnc(p2_OPSRC_OUTNC);
    doc_outz(p2_OPSRC_OUTZ);
    doc_outnz(p2_OPSRC_OUTNZ);
    doc_outrnd(p2_OPSRC_OUTRND);
    doc_outnot(p2_OPSRC_OUTNOT);
    doc_fltl(p2_OPSRC_FLTL);
    doc_flth(p2_OPSRC_FLTH);
    doc_fltc(p2_OPSRC_FLTC);
    doc_fltnc(p2_OPSRC_FLTNC);
    doc_fltz(p2_OPSRC_FLTZ);
    doc_fltnz(p2_OPSRC_FLTNZ);
    doc_fltrnd(p2_OPSRC_FLTRND);
    doc_fltnot(p2_OPSRC_FLTNOT);
    doc_drvl(p2_OPSRC_DRVL);
    doc_drvh(p2_OPSRC_DRVH);
    doc_drvc(p2_OPSRC_DRVC);
    doc_drvnc(p2_OPSRC_DRVNC);
    doc_drvz(p2_OPSRC_DRVZ);
    doc_drvnz(p2_OPSRC_DRVNZ);
    doc_drvrnd(p2_OPSRC_DRVRND);
    doc_drvnot(p2_OPSRC_DRVNOT);
    doc_splitb(p2_OPSRC_SPLITB);
    doc_mergeb(p2_OPSRC_MERGEB);
    doc_splitw(p2_OPSRC_SPLITW);
    doc_mergew(p2_OPSRC_MERGEW);
    doc_seussf(p2_OPSRC_SEUSSF);
    doc_seussr(p2_OPSRC_SEUSSR);
    doc_rgbsqz(p2_OPSRC_RGBSQZ);
    doc_rgbexp(p2_OPSRC_RGBEXP);
    doc_xoro32(p2_OPSRC_XORO32);
    doc_rev(p2_OPSRC_REV);
    doc_rczr(p2_OPSRC_RCZR);
    doc_rczl(p2_OPSRC_RCZL);
    doc_wrc(p2_OPSRC_WRC);
    doc_wrnc(p2_OPSRC_WRNC);
    doc_wrz(p2_OPSRC_WRZ);
    doc_modcz(p2_OPSRC_WRNZ_MODCZ);
    doc_wrnz(p2_OPSRC_WRNZ_MODCZ);
    doc_setscp(p2_OPSRC_SETSCP);
    doc_getscp(p2_OPSRC_GETSCP);

    doc_jmp_abs(p2_JMP_ABS);
    doc_call_abs(p2_CALL_ABS);
    doc_calla_abs(p2_CALLA_ABS);
    doc_callb_abs(p2_CALLB_ABS);
    doc_calld_pa_abs(p2_CALLD_PA_ABS);
    doc_calld_pb_abs(p2_CALLD_PB_ABS);
    doc_calld_ptra_abs(p2_CALLD_PTRA_ABS);
    doc_calld_ptrb_abs(p2_CALLD_PTRB_ABS);

    doc_loc_pa(p2_LOC_PA);
    doc_loc_pb(p2_LOC_PB);
    doc_loc_ptra(p2_LOC_PTRA);
    doc_loc_ptrb(p2_LOC_PTRB);

    doc_augs(p2_AUGS);
    doc_augs(p2_AUGS_01);
    doc_augs(p2_AUGS_10);
    doc_augs(p2_AUGS_11);

    doc_augd(p2_AUGD);
    doc_augd(p2_AUGD_01);
    doc_augd(p2_AUGD_10);
    doc_augd(p2_AUGD_11);
}

/**
 * @brief Return the brief description for an instruction
 * @param instr 32 bit value of the masked opcode
 * @return pointer to brief descr, or nullptr if none exists
 */
const char* P2Doc::brief(p2_LONG opcode)
{
    foreach(MaskMatch mask_match, m_masks) {
        mask_match.second = opcode & mask_match.first;
        if (m_brief.contains(mask_match))
            return m_brief[mask_match];
    }
    return nullptr;
}

/**
 * @brief Return the assembler source example for an instruction
 * @param instr 32 bit value of the masked opcode
 * @return pointer to instruction example, or nullptr if none exists
 */
const char* P2Doc::instr(p2_LONG opcode)
{
    foreach(MaskMatch mask_match, m_masks) {
        mask_match.second = opcode & mask_match.first;
        if (m_instr.contains(mask_match))
            return m_instr[mask_match];
    }
    return nullptr;
}

/**
 * @brief Return the effects description for an instruction
 * @param instr 32 bit value of the masked opcode
 * @return QList of pointers to the effects description
 */
QList<const char*> P2Doc::descr(p2_LONG opcode)
{
    foreach(MaskMatch mask_match, m_masks) {
        mask_match.second = opcode & mask_match.first;
        if (m_descr.contains(mask_match))
            return m_descr[mask_match];
    }
    return QList<const char *>();
}

/**
 * @brief Return the token value for the mnemonic of an instruction
 * @param instr 32 bit value of the masked opcode
 * @return token value for the instruction, or t_invalid if none exists
 */
p2_token_e P2Doc::token(p2_LONG opcode)
{
    foreach(MaskMatch mask_match, m_masks) {
        mask_match.second = opcode & mask_match.first;
        if (m_token.contains(mask_match))
            return m_token[mask_match];
    }
    return t_invalid;
}

/**
 * @brief Build the opcode for a p2_inst7_e enumeration value
 * @param instr instruction's enumeration value
 * @return adjusted opcode
 */
p2_LONG P2Doc::inst7(const p2_inst7_e instr)
{
    p2_LONG inst7 = static_cast<p2_LONG>(instr) << p2_shift_inst7;
    return inst7;
}

/**
 * @brief Build the opcode for a p2_inst8_e enumeration value
 * @param instr instruction's enumeration value
 * @return adjusted opcode
 */
p2_LONG P2Doc::inst8(const p2_inst8_e instr)
{
    p2_LONG inst8 = static_cast<p2_LONG>(instr) << p2_shift_inst8;
    return inst8;
}

/**
 * @brief Build the opcode for a p2_inst9_e enumeration value
 * @param instr instruction's enumeration value
 * @return adjusted opcode
 */
p2_LONG P2Doc::inst9(const p2_inst9_e instr)
{
    p2_LONG inst9 = static_cast<p2_LONG>(instr) << p2_shift_inst9;
    return inst9;
}

/**
 * @brief Build the opcode for a p2_opdst_e enumeration value
 * @param instr instruction's enumeration value
 * @return adjusted opcode
 */
p2_LONG P2Doc::opdst(const p2_opdst_e instr)
{
    p2_LONG opdst = inst9(p2_OPDST) | static_cast<p2_LONG>(instr) << p2_shift_opdst;
    return opdst;
}

p2_LONG P2Doc::opsrc(const p2_opsrc_e instr)
{
    p2_LONG opsrc = inst7(p2_OPSRC) | static_cast<p2_LONG>(instr) << p2_shift_opsrc;
    return opsrc;
}

p2_LONG P2Doc::opx24(const p2_opx24_e instr)
{
    p2_LONG opx24 = opsrc(p2_OPSRC_X24) | static_cast<p2_LONG>(instr) << p2_shift_opdst;
    return opx24;
}

/**
 * @brief Return a mask / match for an instruction's pattern
 *
 * Meaning of the special characters in the pattern strings:
 * E    conditional execution flags (EEEE)
 * C    with carry flag (WC)
 * Z    with zero flag (WZ)
 * I    immediate flag for source (#S)
 * L    immediate flag for destination (#D)
 * N    nibble, byte, word index or absolute address (N, NN, NNN, ...)
 * D    destination register / immediate value (DDDDDDDDD)
 * S    source register / immediate value
 * c    MODCZ condition for the C flag (cccc)
 * z    MODCZ condition for the Z flag (zzzz)
 * R    relative 20 bit address flag (R)
 * A    20 bit address (AA AAAAAAAAA AAAAAAAAA)
 * W    PTR selection (PA, PB, PTRA, PTRB)
 *
 * Additional characters not used in the original comment:
 * h    for WC + WZ bits which have to be either 00 or 11 (equal)
 * x    for WC + WZ bits which have to be either 10 or 01 (unequal)
 *
 * @param instr instruction's opcode
 * @param pat pattern
 * @return mask / match value in 64 bits
 */
P2Doc::MaskMatch P2Doc::pattern(const char* _func, p2_LONG instr, const char* pat)
{
    MaskMatch result(FULL,instr);
    QString pack = QString::fromLatin1(pat);

    // pattern without spaces
    pack.remove(QChar(' '));
    // size must be 32 bits
    Q_ASSERT(pack.size() == 32);

    // instr_mask: replace '0', 'N', 'H', and 'x' with '1'
    QString instr_mask = pack;
    instr_mask.replace(QRegExp("[0Nhx]"), QChar('1'));

    // binary_mask: replace any special characters with '0'
    QString binary_mask = instr_mask;
    binary_mask.replace(QRegExp("[ECZILNDSczRAW]"), QChar('0'));

    // sum of counts of '0's and '1's must be 32 bits
    Q_ASSERT(binary_mask.count(QChar('0')) + binary_mask.count(QChar('1')) == 32);

    bool ok;
    p2_LONG mask = static_cast<p2_LONG>(binary_mask.toULong(&ok, 2));
    if (ok) {
        // put the binary mask in the first item
        result.first = mask;
    } else {
        qDebug("you missed a special character: %s", qPrintable(binary_mask));
    }

    if (instr & ~mask) {
        QString dbg_mask = binary_mask;
        QString dbg_instr = QString("%1").arg(instr | mask, 32, 2, QChar('0'));
        dbg_mask.replace(QChar('0'), QChar('_'));
        dbg_instr.replace(QChar('0'), QChar('_'));
        qDebug("mask does not cover instr: %s %s (%s)",
               qPrintable(dbg_mask),
               qPrintable(dbg_instr),
               _func);
    }

    // conditional mask
    QString cond_mask = instr_mask;

    // replace '1' with '0'
    cond_mask.replace(QChar('1'), QChar('0'));
    // replace 'E' with '1'
    cond_mask.replace(QChar('E'), QChar('1'));

    m_pattern.insert(result, pat);

    return result;
}

/**
 * @brief Make pattern for 7 bit instruction
 * @param _func calling function's name
 * @param instr instruction enum value
 * @param pat pattern string
 * @return mask / match value pair
 */
P2Doc::MaskMatch P2Doc::pattern(const char* _func, p2_inst7_e instr, const char* pat)
{
    return pattern(_func, inst7(instr), pat);
}

/**
 * @brief Make pattern for 8 bit instruction
 * @param _func calling function's name
 * @param instr instruction enum value
 * @param pat pattern string
 * @return mask / match value pair
 */
P2Doc::MaskMatch P2Doc::pattern(const char* _func, p2_inst8_e instr, const char* pat)
{
    return pattern(_func, inst8(instr), pat);
}

/**
 * @brief Pattern for 9 bit instruction
 * @param _func calling function's name
 * @param instr instruction enum value
 * @param pat pattern string
 * @return mask / match value pair
 */
P2Doc::MaskMatch P2Doc::pattern(const char* _func, p2_inst9_e instr, const char* pat)
{
    return pattern(_func, inst9(instr), pat);
}

/**
 * @brief Pattern for instruction with dst field enumeration value
 * @param _func calling function's name
 * @param instr instruction enum value
 * @param pat pattern string
 * @return mask / match value pair
 */
P2Doc::MaskMatch P2Doc::pattern(const char* _func, p2_opdst_e instr, const char* pat)
{
    return pattern(_func, opdst(instr), pat);
}

/**
 * @brief Pattern for instruction with src field enumeration value
 * @param _func calling function's name
 * @param instr instruction enum value
 * @param pat pattern string
 * @return mask / match value pair
 */
P2Doc::MaskMatch P2Doc::pattern(const char* _func, p2_opsrc_e instr, const char* pat)
{
    return pattern(_func, opsrc(instr), pat);
}

/**
 * @brief Pattern for instruction with dst field enumeration value, src = %000100100
 * @param _func calling function's name
 * @param instr instruction enum value
 * @param pat pattern string
 * @return mask / match value pair
 */
P2Doc::MaskMatch P2Doc::pattern(const char* _func, p2_opx24_e instr, const char* pat)
{
    return pattern(_func, opx24(instr), pat);
}

/**
 * @brief No operation.
 *
 * 0000 0000000 000 000000000 000000000
 *
 * NOP
 *
 */
void P2Doc::doc_nop(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "0000 0000000 000 000000000 000000000");
    m_token.insert(mask_match, t_NOP);
    QList<const char *> descr;
    m_brief.insert(mask_match, "No operation.");
    m_instr.insert(mask_match, "NOP");
}

/**
 * @brief Rotate right.
 *
 * EEEE 0000000 CZI DDDDDDDDD SSSSSSSSS
 *
 * ROR     D,{#}S   {WC/WZ/WCZ}
 * D = [31:0]  of ({D[31:0], D[31:0]}     >> S[4:0]).
 * C = last bit shifted out if S[4:0] > 0, else D[0].
 * Z = (result == 0).
 *
 */
void P2Doc::doc_ror(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0000000 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ROR);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Rotate right.");
    m_instr.insert(mask_match, "ROR     D,{#}S   {WC/WZ/WCZ}");
    descr += "D = [31:0]  of ({D[31:0], D[31:0]}     >> S[4:0]).";
    descr += "C = last bit shifted out if S[4:0] > 0, else D[0].";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Rotate left.
 *
 * EEEE 0000001 CZI DDDDDDDDD SSSSSSSSS
 *
 * ROL     D,{#}S   {WC/WZ/WCZ}
 *
 * D = [63:32] of ({D[31:0], D[31:0]}     << S[4:0]).
 * C = last bit shifted out if S[4:0] > 0, else D[31].
 * Z = (result == 0).
 *
 */
void P2Doc::doc_rol(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0000001 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ROL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Rotate left.");
    m_instr.insert(mask_match, "ROL     D,{#}S   {WC/WZ/WCZ}");
    descr += "D = [63:32] of ({D[31:0], D[31:0]}     << S[4:0]).";
    descr += "C = last bit shifted out if S[4:0] > 0, else D[31].";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Shift right.
 *
 * EEEE 0000010 CZI DDDDDDDDD SSSSSSSSS
 *
 * SHR     D,{#}S   {WC/WZ/WCZ}
 *
 * D = [31:0]  of ({32'b0, D[31:0]}       >> S[4:0]).
 * C = last bit shifted out if S[4:0] > 0, else D[0].
 * Z = (result == 0).
 *
 */
void P2Doc::doc_shr(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0000010 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SHR);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Shift right.");
    m_instr.insert(mask_match, "SHR     D,{#}S   {WC/WZ/WCZ}");
    descr += "D = [31:0]  of ({32'b0, D[31:0]}       >> S[4:0]).";
    descr += "C = last bit shifted out if S[4:0] > 0, else D[0].";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Shift left.
 *
 * EEEE 0000011 CZI DDDDDDDDD SSSSSSSSS
 *
 * SHL     D,{#}S   {WC/WZ/WCZ}
 *
 * D = [63:32] of ({D[31:0], 32'b0}       << S[4:0]).
 * C = last bit shifted out if S[4:0] > 0, else D[31].
 * Z = (result == 0).
 *
 */
void P2Doc::doc_shl(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0000011 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SHL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Shift left.");
    m_instr.insert(mask_match, "SHL     D,{#}S   {WC/WZ/WCZ}");
    descr += "D = [63:32] of ({D[31:0], 32'b0}       << S[4:0]).";
    descr += "C = last bit shifted out if S[4:0] > 0, else D[31].";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Rotate carry right.
 *
 * EEEE 0000100 CZI DDDDDDDDD SSSSSSSSS
 *
 * RCR     D,{#}S   {WC/WZ/WCZ}
 *
 * D = [31:0]  of ({{32{C}}, D[31:0]}     >> S[4:0]).
 * C = last bit shifted out if S[4:0] > 0, else D[0].
 * Z = (result == 0).
 *
 */
void P2Doc::doc_rcr(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0000100 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_RCR);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Rotate carry right.");
    m_instr.insert(mask_match, "RCR     D,{#}S   {WC/WZ/WCZ}");
    descr += "D = [31:0]  of ({{32{C}}, D[31:0]}     >> S[4:0]).";
    descr += "C = last bit shifted out if S[4:0] > 0, else D[0].";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Rotate carry left.
 *
 * EEEE 0000101 CZI DDDDDDDDD SSSSSSSSS
 *
 * RCL     D,{#}S   {WC/WZ/WCZ}
 *
 * D = [63:32] of ({D[31:0], {32{C}}}     << S[4:0]).
 * C = last bit shifted out if S[4:0] > 0, else D[31].
 * Z = (result == 0).
 *
 */
void P2Doc::doc_rcl(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0000101 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_RCL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Rotate carry left.");
    m_instr.insert(mask_match, "RCL     D,{#}S   {WC/WZ/WCZ}");
    descr += "D = [63:32] of ({D[31:0], {32{C}}}     << S[4:0]).";
    descr += "C = last bit shifted out if S[4:0] > 0, else D[31].";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Shift arithmetic right.
 *
 * EEEE 0000110 CZI DDDDDDDDD SSSSSSSSS
 *
 * SAR     D,{#}S   {WC/WZ/WCZ}
 *
 * D = [31:0]  of ({{32{D[31]}}, D[31:0]} >> S[4:0]).
 * C = last bit shifted out if S[4:0] > 0, else D[0].
 * Z = (result == 0).
 *
 */
void P2Doc::doc_sar(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0000110 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SAR);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Shift arithmetic right.");
    m_instr.insert(mask_match, "SAR     D,{#}S   {WC/WZ/WCZ}");
    descr += "D = [31:0]  of ({{32{D[31]}}, D[31:0]} >> S[4:0]).";
    descr += "C = last bit shifted out if S[4:0] > 0, else D[0].";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Shift arithmetic left.
 *
 * EEEE 0000111 CZI DDDDDDDDD SSSSSSSSS
 *
 * SAL     D,{#}S   {WC/WZ/WCZ}
 *
 * D = [63:32] of ({D[31:0], {32{D[0]}}}  << S[4:0]).
 * C = last bit shifted out if S[4:0] > 0, else D[31].
 * Z = (result == 0).
 *
 */
void P2Doc::doc_sal(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0000111 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SAL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Shift arithmetic left.");
    m_instr.insert(mask_match, "SAL     D,{#}S   {WC/WZ/WCZ}");
    descr += "D = [63:32] of ({D[31:0], {32{D[0]}}}  << S[4:0]).";
    descr += "C = last bit shifted out if S[4:0] > 0, else D[31].";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Add S into D.
 *
 * EEEE 0001000 CZI DDDDDDDDD SSSSSSSSS
 *
 * ADD     D,{#}S   {WC/WZ/WCZ}
 *
 * D = D + S.
 * C = carry of (D + S).
 * Z = (result == 0).
 *
 */
void P2Doc::doc_add(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0001000 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ADD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Add S into D.");
    m_instr.insert(mask_match, "ADD     D,{#}S   {WC/WZ/WCZ}");
    descr += "D = D + S.";
    descr += "C = carry of (D + S).";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Add (S + C) into D, extended.
 *
 * EEEE 0001001 CZI DDDDDDDDD SSSSSSSSS
 *
 * ADDX    D,{#}S   {WC/WZ/WCZ}
 *
 * D = D + S + C.
 * C = carry of (D + S + C).
 * Z = Z AND (result == 0).
 *
 */
void P2Doc::doc_addx(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0001001 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ADDX);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Add (S + C) into D, extended.");
    m_instr.insert(mask_match, "ADDX    D,{#}S   {WC/WZ/WCZ}");
    descr += "D = D + S + C.";
    descr += "C = carry of (D + S + C).";
    descr += "Z = Z AND (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Add S into D, signed.
 *
 * EEEE 0001010 CZI DDDDDDDDD SSSSSSSSS
 *
 * ADDS    D,{#}S   {WC/WZ/WCZ}
 *
 * D = D + S.
 * C = correct sign of (D + S).
 * Z = (result == 0).
 *
 */
void P2Doc::doc_adds(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0001010 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ADDS);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Add S into D, signed.");
    m_instr.insert(mask_match, "ADDS    D,{#}S   {WC/WZ/WCZ}");
    descr += "D = D + S.";
    descr += "C = correct sign of (D + S).";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Add (S + C) into D, signed and extended.
 *
 * EEEE 0001011 CZI DDDDDDDDD SSSSSSSSS
 *
 * ADDSX   D,{#}S   {WC/WZ/WCZ}
 *
 * D = D + S + C.
 * C = correct sign of (D + S + C).
 * Z = Z AND (result == 0).
 *
 */
void P2Doc::doc_addsx(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0001011 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ADDSX);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Add (S + C) into D, signed and extended.");
    m_instr.insert(mask_match, "ADDSX   D,{#}S   {WC/WZ/WCZ}");
    descr += "D = D + S + C.";
    descr += "C = correct sign of (D + S + C).";
    descr += "Z = Z AND (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Subtract S from D.
 *
 * EEEE 0001100 CZI DDDDDDDDD SSSSSSSSS
 *
 * SUB     D,{#}S   {WC/WZ/WCZ}
 *
 * D = D - S.
 * C = borrow of (D - S).
 * Z = (result == 0).
 *
 */
void P2Doc::doc_sub(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0001100 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SUB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Subtract S from D.");
    m_instr.insert(mask_match, "SUB     D,{#}S   {WC/WZ/WCZ}");
    descr += "D = D - S.";
    descr += "C = borrow of (D - S).";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Subtract (S + C) from D, extended.
 *
 * EEEE 0001101 CZI DDDDDDDDD SSSSSSSSS
 *
 * SUBX    D,{#}S   {WC/WZ/WCZ}
 *
 * D = D - (S + C).
 * C = borrow of (D - (S + C)).
 * Z = Z AND (result == 0).
 *
 */
void P2Doc::doc_subx(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0001101 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SUBX);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Subtract (S + C) from D, extended.");
    m_instr.insert(mask_match, "SUBX    D,{#}S   {WC/WZ/WCZ}");
    descr += "D = D - (S + C).";
    descr += "C = borrow of (D - (S + C)).";
    descr += "Z = Z AND (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Subtract S from D, signed.
 *
 * EEEE 0001110 CZI DDDDDDDDD SSSSSSSSS
 *
 * SUBS    D,{#}S   {WC/WZ/WCZ}
 *
 * D = D - S.
 * C = correct sign of (D - S).
 * Z = (result == 0).
 *
 */
void P2Doc::doc_subs(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0001110 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SUBS);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Subtract S from D, signed.");
    m_instr.insert(mask_match, "SUBS    D,{#}S   {WC/WZ/WCZ}");
    descr += "D = D - S.";
    descr += "C = correct sign of (D - S).";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Subtract (S + C) from D, signed and extended.
 *
 * EEEE 0001111 CZI DDDDDDDDD SSSSSSSSS
 *
 * SUBSX   D,{#}S   {WC/WZ/WCZ}
 *
 * D = D - (S + C).
 * C = correct sign of (D - (S + C)).
 * Z = Z AND (result == 0).
 *
 */
void P2Doc::doc_subsx(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0001111 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SUBSX);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Subtract (S + C) from D, signed and extended.");
    m_instr.insert(mask_match, "SUBSX   D,{#}S   {WC/WZ/WCZ}");
    descr += "D = D - (S + C).";
    descr += "C = correct sign of (D - (S + C)).";
    descr += "Z = Z AND (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Compare D to S.
 *
 * EEEE 0010000 CZI DDDDDDDDD SSSSSSSSS
 *
 * CMP     D,{#}S   {WC/WZ/WCZ}
 *
 * C = borrow of (D - S).
 * Z = (D == S).
 *
 */
void P2Doc::doc_cmp(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0010000 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_CMP);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Compare D to S.");
    m_instr.insert(mask_match, "CMP     D,{#}S   {WC/WZ/WCZ}");
    descr += "C = borrow of (D - S).";
    descr += "Z = (D == S).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Compare D to (S + C), extended.
 *
 * EEEE 0010001 CZI DDDDDDDDD SSSSSSSSS
 *
 * CMPX    D,{#}S   {WC/WZ/WCZ}
 *
 * C = borrow of (D - (S + C)).
 * Z = Z AND (D == S + C).
 *
 */
void P2Doc::doc_cmpx(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0010001 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_CMPX);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Compare D to (S + C), extended.");
    m_instr.insert(mask_match, "CMPX    D,{#}S   {WC/WZ/WCZ}");
    descr += "C = borrow of (D - (S + C)).";
    descr += "Z = Z AND (D == S + C).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Compare D to S, signed.
 *
 * EEEE 0010010 CZI DDDDDDDDD SSSSSSSSS
 *
 * CMPS    D,{#}S   {WC/WZ/WCZ}
 *
 * C = correct sign of (D - S).
 * Z = (D == S).
 *
 */
void P2Doc::doc_cmps(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0010010 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_CMPS);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Compare D to S, signed.");
    m_instr.insert(mask_match, "CMPS    D,{#}S   {WC/WZ/WCZ}");
    descr += "C = correct sign of (D - S).";
    descr += "Z = (D == S).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Compare D to (S + C), signed and extended.
 *
 * EEEE 0010011 CZI DDDDDDDDD SSSSSSSSS
 *
 * CMPSX   D,{#}S   {WC/WZ/WCZ}
 *
 * C = correct sign of (D - (S + C)).
 * Z = Z AND (D == S + C).
 *
 */
void P2Doc::doc_cmpsx(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0010011 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_CMPSX);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Compare D to (S + C), signed and extended.");
    m_instr.insert(mask_match, "CMPSX   D,{#}S   {WC/WZ/WCZ}");
    descr += "C = correct sign of (D - (S + C)).";
    descr += "Z = Z AND (D == S + C).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Compare S to D (reverse).
 *
 * EEEE 0010100 CZI DDDDDDDDD SSSSSSSSS
 *
 * CMPR    D,{#}S   {WC/WZ/WCZ}
 *
 * C = borrow of (S - D).
 * Z = (D == S).
 *
 */
void P2Doc::doc_cmpr(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0010100 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_CMPR);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Compare S to D (reverse).");
    m_instr.insert(mask_match, "CMPR    D,{#}S   {WC/WZ/WCZ}");
    descr += "C = borrow of (S - D).";
    descr += "Z = (D == S).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Compare D to S, get MSB of difference into C.
 *
 * EEEE 0010101 CZI DDDDDDDDD SSSSSSSSS
 *
 * CMPM    D,{#}S   {WC/WZ/WCZ}
 *
 * C = MSB of (D - S).
 * Z = (D == S).
 *
 */
void P2Doc::doc_cmpm(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0010101 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_CMPM);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Compare D to S, get MSB of difference into C.");
    m_instr.insert(mask_match, "CMPM    D,{#}S   {WC/WZ/WCZ}");
    descr += "C = MSB of (D - S).";
    descr += "Z = (D == S).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Subtract D from S (reverse).
 *
 * EEEE 0010110 CZI DDDDDDDDD SSSSSSSSS
 *
 * SUBR    D,{#}S   {WC/WZ/WCZ}
 *
 * D = S - D.
 * C = borrow of (S - D).
 * Z = (result == 0).
 *
 */
void P2Doc::doc_subr(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0010110 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SUBR);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Subtract D from S (reverse).");
    m_instr.insert(mask_match, "SUBR    D,{#}S   {WC/WZ/WCZ}");
    descr += "D = S - D.";
    descr += "C = borrow of (S - D).";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Compare and subtract S from D if D >= S.
 *
 * EEEE 0010111 CZI DDDDDDDDD SSSSSSSSS
 *
 * CMPSUB  D,{#}S   {WC/WZ/WCZ}
 *
 * If D => S then D = D - S and C = 1, else D same and C = 0.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_cmpsub(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0010111 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_CMPSUB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Compare and subtract S from D if D >= S.");
    m_instr.insert(mask_match, "CMPSUB  D,{#}S   {WC/WZ/WCZ}");
    descr += "If D => S then D = D - S and C = 1, else D same and C = 0.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Force D >= S.
 *
 * EEEE 0011000 CZI DDDDDDDDD SSSSSSSSS
 *
 * FGE     D,{#}S   {WC/WZ/WCZ}
 *
 * If D < S then D = S and C = 1, else D same and C = 0.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_fge(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0011000 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_FGE);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Force D >= S.");
    m_instr.insert(mask_match, "FGE     D,{#}S   {WC/WZ/WCZ}");
    descr += "If D < S then D = S and C = 1, else D same and C = 0.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Force D <= S.
 *
 * EEEE 0011001 CZI DDDDDDDDD SSSSSSSSS
 *
 * FLE     D,{#}S   {WC/WZ/WCZ}
 *
 * If D > S then D = S and C = 1, else D same and C = 0.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_fle(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0011001 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_FLE);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Force D <= S.");
    m_instr.insert(mask_match, "FLE     D,{#}S   {WC/WZ/WCZ}");
    descr += "If D > S then D = S and C = 1, else D same and C = 0.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Force D >= S, signed.
 *
 * EEEE 0011010 CZI DDDDDDDDD SSSSSSSSS
 *
 * FGES    D,{#}S   {WC/WZ/WCZ}
 *
 * If D < S then D = S and C = 1, else D same and C = 0.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_fges(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0011010 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_FGES);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Force D >= S, signed.");
    m_instr.insert(mask_match, "FGES    D,{#}S   {WC/WZ/WCZ}");
    descr += "If D < S then D = S and C = 1, else D same and C = 0.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Force D <= S, signed.
 *
 * EEEE 0011011 CZI DDDDDDDDD SSSSSSSSS
 *
 * FLES    D,{#}S   {WC/WZ/WCZ}
 *
 * If D > S then D = S and C = 1, else D same and C = 0.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_fles(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0011011 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_FLES);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Force D <= S, signed.");
    m_instr.insert(mask_match, "FLES    D,{#}S   {WC/WZ/WCZ}");
    descr += "If D > S then D = S and C = 1, else D same and C = 0.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Sum +/-S into D by  C.
 *
 * EEEE 0011100 CZI DDDDDDDDD SSSSSSSSS
 *
 * SUMC    D,{#}S   {WC/WZ/WCZ}
 *
 * If C = 1 then D = D - S, else D = D + S.
 * C = correct sign of (D +/- S).
 * Z = (result == 0).
 *
 */
void P2Doc::doc_sumc(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0011100 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SUMC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Sum +/-S into D by  C.");
    m_instr.insert(mask_match, "SUMC    D,{#}S   {WC/WZ/WCZ}");
    descr += "If C = 1 then D = D - S, else D = D + S.";
    descr += "C = correct sign of (D +/- S).";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Sum +/-S into D by !C.
 *
 * EEEE 0011101 CZI DDDDDDDDD SSSSSSSSS
 *
 * SUMNC   D,{#}S   {WC/WZ/WCZ}
 *
 * If C = 0 then D = D - S, else D = D + S.
 * C = correct sign of (D +/- S).
 * Z = (result == 0).
 *
 */
void P2Doc::doc_sumnc(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0011101 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SUMNC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Sum +/-S into D by !C.");
    m_instr.insert(mask_match, "SUMNC   D,{#}S   {WC/WZ/WCZ}");
    descr += "If C = 0 then D = D - S, else D = D + S.";
    descr += "C = correct sign of (D +/- S).";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Sum +/-S into D by  Z.
 *
 * EEEE 0011110 CZI DDDDDDDDD SSSSSSSSS
 *
 * SUMZ    D,{#}S   {WC/WZ/WCZ}
 *
 * If Z = 1 then D = D - S, else D = D + S.
 * C = correct sign of (D +/- S).
 * Z = (result == 0).
 *
 */
void P2Doc::doc_sumz(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0011110 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SUMZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Sum +/-S into D by  Z.");
    m_instr.insert(mask_match, "SUMZ    D,{#}S   {WC/WZ/WCZ}");
    descr += "If Z = 1 then D = D - S, else D = D + S.";
    descr += "C = correct sign of (D +/- S).";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Sum +/-S into D by !Z.
 *
 * EEEE 0011111 CZI DDDDDDDDD SSSSSSSSS
 *
 * SUMNZ   D,{#}S   {WC/WZ/WCZ}
 *
 * If Z = 0 then D = D - S, else D = D + S.
 * C = correct sign of (D +/- S).
 * Z = (result == 0).
 *
 */
void P2Doc::doc_sumnz(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0011111 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SUMNZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Sum +/-S into D by !Z.");
    m_instr.insert(mask_match, "SUMNZ   D,{#}S   {WC/WZ/WCZ}");
    descr += "If Z = 0 then D = D - S, else D = D + S.";
    descr += "C = correct sign of (D +/- S).";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Test bit S[4:0] of  D, write to C/Z.
 *
 * EEEE 0100000 CZI DDDDDDDDD SSSSSSSSS
 *
 * TESTB   D,{#}S         WC/WZ
 *
 * C/Z =          D[S[4:0]].
 *
 */
void P2Doc::doc_testb_w(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0100000 xxI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_TESTB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test bit S[4:0] of  D, write to C/Z.");
    m_instr.insert(mask_match, "TESTB   D,{#}S         WC/WZ");
    descr += "C/Z =          D[S[4:0]].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Test bit S[4:0] of !D, write to C/Z.
 *
 * EEEE 0100001 CZI DDDDDDDDD SSSSSSSSS
 *
 * TESTBN  D,{#}S         WC/WZ
 *
 * C/Z =         !D[S[4:0]].
 *
 */
void P2Doc::doc_testbn_w(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0100001 xxI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_TESTBN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test bit S[4:0] of !D, write to C/Z.");
    m_instr.insert(mask_match, "TESTBN  D,{#}S         WC/WZ");
    descr += "C/Z =         !D[S[4:0]].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Test bit S[4:0] of  D, AND into C/Z.
 *
 * EEEE 0100010 CZI DDDDDDDDD SSSSSSSSS
 *
 * TESTB   D,{#}S     ANDC/ANDZ
 *
 * C/Z = C/Z AND  D[S[4:0]].
 *
 */
void P2Doc::doc_testb_and(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0100010 xxI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_TESTB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test bit S[4:0] of  D, AND into C/Z.");
    m_instr.insert(mask_match, "TESTB   D,{#}S     ANDC/ANDZ");
    descr += "C/Z = C/Z AND  D[S[4:0]].";
    m_descr.insert(mask_match, descr);    // t_AND
}

/**
 * @brief Test bit S[4:0] of !D, AND into C/Z.
 *
 * EEEE 0100011 CZI DDDDDDDDD SSSSSSSSS
 *
 * TESTBN  D,{#}S     ANDC/ANDZ
 *
 * C/Z = C/Z AND !D[S[4:0]].
 *
 */
void P2Doc::doc_testbn_and(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0100011 xxI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_TESTBN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test bit S[4:0] of !D, AND into C/Z.");
    m_instr.insert(mask_match, "TESTBN  D,{#}S     ANDC/ANDZ");
    descr += "C/Z = C/Z AND !D[S[4:0]].";
    m_descr.insert(mask_match, descr);   // t_AND
}

/**
 * @brief Test bit S[4:0] of  D, OR  into C/Z.
 *
 * EEEE 0100100 CZI DDDDDDDDD SSSSSSSSS
 *
 * TESTB   D,{#}S       ORC/ORZ
 *
 * C/Z = C/Z OR   D[S[4:0]].
 *
 */
void P2Doc::doc_testb_or(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0100100 xxI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_TESTB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test bit S[4:0] of  D, OR  into C/Z.");
    m_instr.insert(mask_match, "TESTB   D,{#}S       ORC/ORZ");
    descr += "C/Z = C/Z OR   D[S[4:0]].";
    m_descr.insert(mask_match, descr);    // t_OR
}

/**
 * @brief Test bit S[4:0] of !D, OR  into C/Z.
 *
 * EEEE 0100101 CZI DDDDDDDDD SSSSSSSSS
 *
 * TESTBN  D,{#}S       ORC/ORZ
 *
 * C/Z = C/Z OR  !D[S[4:0]].
 *
 */
void P2Doc::doc_testbn_or(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0100101 xxI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_TESTBN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test bit S[4:0] of !D, OR  into C/Z.");
    m_instr.insert(mask_match, "TESTBN  D,{#}S       ORC/ORZ");
    descr += "C/Z = C/Z OR  !D[S[4:0]].";
    m_descr.insert(mask_match, descr);   // t_OR
}

/**
 * @brief Test bit S[4:0] of  D, XOR into C/Z.
 *
 * EEEE 0100110 CZI DDDDDDDDD SSSSSSSSS
 *
 * TESTB   D,{#}S     XORC/XORZ
 *
 * C/Z = C/Z XOR  D[S[4:0]].
 *
 */
void P2Doc::doc_testb_xor(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0100110 xxI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_TESTB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test bit S[4:0] of  D, XOR into C/Z.");
    m_instr.insert(mask_match, "TESTB   D,{#}S     XORC/XORZ");
    descr += "C/Z = C/Z XOR  D[S[4:0]].";
    m_descr.insert(mask_match, descr);    // t_XOR
}

/**
 * @brief Test bit S[4:0] of !D, XOR into C/Z.
 *
 * EEEE 0100111 CZI DDDDDDDDD SSSSSSSSS
 *
 * TESTBN  D,{#}S     XORC/XORZ
 *
 * C/Z = C/Z XOR !D[S[4:0]].
 *
 */
void P2Doc::doc_testbn_xor(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0100111 xxI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_TESTBN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test bit S[4:0] of !D, XOR into C/Z.");
    m_instr.insert(mask_match, "TESTBN  D,{#}S     XORC/XORZ");
    descr += "C/Z = C/Z XOR !D[S[4:0]].";
    m_descr.insert(mask_match, descr);   // t_XOR
}

/**
 * @brief Bit S[4:0] of D = 0,    C,Z = D[S[4:0]].
 *
 * EEEE 0100000 CZI DDDDDDDDD SSSSSSSSS
 *
 * BITL    D,{#}S         {WCZ}
 *
 *
 */
void P2Doc::doc_bitl(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0100000 hhI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_BITL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Bit S[4:0] of D = 0,    C,Z = D[S[4:0]].");
    m_instr.insert(mask_match, "BITL    D,{#}S         {WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Bit S[4:0] of D = 1,    C,Z = D[S[4:0]].
 *
 * EEEE 0100001 CZI DDDDDDDDD SSSSSSSSS
 *
 * BITH    D,{#}S         {WCZ}
 *
 *
 */
void P2Doc::doc_bith(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0100001 hhI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_BITH);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Bit S[4:0] of D = 1,    C,Z = D[S[4:0]].");
    m_instr.insert(mask_match, "BITH    D,{#}S         {WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Bit S[4:0] of D = C,    C,Z = D[S[4:0]].
 *
 * EEEE 0100010 CZI DDDDDDDDD SSSSSSSSS
 *
 * BITC    D,{#}S         {WCZ}
 *
 *
 */
void P2Doc::doc_bitc(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0100010 hhI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_BITC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Bit S[4:0] of D = C,    C,Z = D[S[4:0]].");
    m_instr.insert(mask_match, "BITC    D,{#}S         {WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Bit S[4:0] of D = !C,   C,Z = D[S[4:0]].
 *
 * EEEE 0100011 CZI DDDDDDDDD SSSSSSSSS
 *
 * BITNC   D,{#}S         {WCZ}
 *
 *
 */
void P2Doc::doc_bitnc(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0100011 hhI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_BITNC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Bit S[4:0] of D = !C,   C,Z = D[S[4:0]].");
    m_instr.insert(mask_match, "BITNC   D,{#}S         {WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Bit S[4:0] of D = Z,    C,Z = D[S[4:0]].
 *
 * EEEE 0100100 CZI DDDDDDDDD SSSSSSSSS
 *
 * BITZ    D,{#}S         {WCZ}
 *
 *
 */
void P2Doc::doc_bitz(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0100100 hhI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_BITZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Bit S[4:0] of D = Z,    C,Z = D[S[4:0]].");
    m_instr.insert(mask_match, "BITZ    D,{#}S         {WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Bit S[4:0] of D = !Z,   C,Z = D[S[4:0]].
 *
 * EEEE 0100101 CZI DDDDDDDDD SSSSSSSSS
 *
 * BITNZ   D,{#}S         {WCZ}
 *
 *
 */
void P2Doc::doc_bitnz(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0100101 hhI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_BITNZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Bit S[4:0] of D = !Z,   C,Z = D[S[4:0]].");
    m_instr.insert(mask_match, "BITNZ   D,{#}S         {WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Bit S[4:0] of D = RND,  C,Z = D[S[4:0]].
 *
 * EEEE 0100110 CZI DDDDDDDDD SSSSSSSSS
 *
 * BITRND  D,{#}S         {WCZ}
 *
 *
 */
void P2Doc::doc_bitrnd(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0100110 hhI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_BITRND);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Bit S[4:0] of D = RND,  C,Z = D[S[4:0]].");
    m_instr.insert(mask_match, "BITRND  D,{#}S         {WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Bit S[4:0] of D = !bit, C,Z = D[S[4:0]].
 *
 * EEEE 0100111 CZI DDDDDDDDD SSSSSSSSS
 *
 * BITNOT  D,{#}S         {WCZ}
 *
 *
 */
void P2Doc::doc_bitnot(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0100111 hhI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_BITNOT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Bit S[4:0] of D = !bit, C,Z = D[S[4:0]].");
    m_instr.insert(mask_match, "BITNOT  D,{#}S         {WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief AND S into D.
 *
 * EEEE 0101000 CZI DDDDDDDDD SSSSSSSSS
 *
 * AND     D,{#}S   {WC/WZ/WCZ}
 *
 * D = D & S.
 * C = parity of result.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_and(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0101000 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_AND);
    QList<const char *> descr;
    m_brief.insert(mask_match, "AND S into D.");
    m_instr.insert(mask_match, "AND     D,{#}S   {WC/WZ/WCZ}");
    descr += "D = D & S.";
    descr += "C = parity of result.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief AND !S into D.
 *
 * EEEE 0101001 CZI DDDDDDDDD SSSSSSSSS
 *
 * ANDN    D,{#}S   {WC/WZ/WCZ}
 *
 * D = D & !S.
 * C = parity of result.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_andn(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0101001 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ANDN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "AND !S into D.");
    m_instr.insert(mask_match, "ANDN    D,{#}S   {WC/WZ/WCZ}");
    descr += "D = D & !S.";
    descr += "C = parity of result.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OR S into D.
 *
 * EEEE 0101010 CZI DDDDDDDDD SSSSSSSSS
 *
 * OR      D,{#}S   {WC/WZ/WCZ}
 *
 * D = D | S.
 * C = parity of result.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_or(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0101010 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_OR);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OR S into D.");
    m_instr.insert(mask_match, "OR      D,{#}S   {WC/WZ/WCZ}");
    descr += "D = D | S.";
    descr += "C = parity of result.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief XOR S into D.
 *
 * EEEE 0101011 CZI DDDDDDDDD SSSSSSSSS
 *
 * XOR     D,{#}S   {WC/WZ/WCZ}
 *
 * D = D ^ S.
 * C = parity of result.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_xor(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0101011 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_XOR);
    QList<const char *> descr;
    m_brief.insert(mask_match, "XOR S into D.");
    m_instr.insert(mask_match, "XOR     D,{#}S   {WC/WZ/WCZ}");
    descr += "D = D ^ S.";
    descr += "C = parity of result.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Mux C into each D bit that is '1' in S.
 *
 * EEEE 0101100 CZI DDDDDDDDD SSSSSSSSS
 *
 * MUXC    D,{#}S   {WC/WZ/WCZ}
 *
 * D = (!S & D ) | (S & {32{ C}}).
 * C = parity of result.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_muxc(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0101100 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_MUXC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Mux C into each D bit that is '1' in S.");
    m_instr.insert(mask_match, "MUXC    D,{#}S   {WC/WZ/WCZ}");
    descr += "D = (!S & D ) | (S & {32{ C}}).";
    descr += "C = parity of result.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Mux !C into each D bit that is '1' in S.
 *
 * EEEE 0101101 CZI DDDDDDDDD SSSSSSSSS
 *
 * MUXNC   D,{#}S   {WC/WZ/WCZ}
 *
 * D = (!S & D ) | (S & {32{!C}}).
 * C = parity of result.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_muxnc(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0101101 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_MUXNC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Mux !C into each D bit that is '1' in S.");
    m_instr.insert(mask_match, "MUXNC   D,{#}S   {WC/WZ/WCZ}");
    descr += "D = (!S & D ) | (S & {32{!C}}).";
    descr += "C = parity of result.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Mux Z into each D bit that is '1' in S.
 *
 * EEEE 0101110 CZI DDDDDDDDD SSSSSSSSS
 *
 * MUXZ    D,{#}S   {WC/WZ/WCZ}
 *
 * D = (!S & D ) | (S & {32{ Z}}).
 * C = parity of result.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_muxz(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0101110 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_MUXZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Mux Z into each D bit that is '1' in S.");
    m_instr.insert(mask_match, "MUXZ    D,{#}S   {WC/WZ/WCZ}");
    descr += "D = (!S & D ) | (S & {32{ Z}}).";
    descr += "C = parity of result.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Mux !Z into each D bit that is '1' in S.
 *
 * EEEE 0101111 CZI DDDDDDDDD SSSSSSSSS
 *
 * MUXNZ   D,{#}S   {WC/WZ/WCZ}
 *
 * D = (!S & D ) | (S & {32{!Z}}).
 * C = parity of result.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_muxnz(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0101111 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_MUXNZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Mux !Z into each D bit that is '1' in S.");
    m_instr.insert(mask_match, "MUXNZ   D,{#}S   {WC/WZ/WCZ}");
    descr += "D = (!S & D ) | (S & {32{!Z}}).";
    descr += "C = parity of result.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Move S into D.
 *
 * EEEE 0110000 CZI DDDDDDDDD SSSSSSSSS
 *
 * MOV     D,{#}S   {WC/WZ/WCZ}
 *
 * D = S.
 * C = S[31].
 * Z = (result == 0).
 *
 */
void P2Doc::doc_mov(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0110000 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_MOV);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Move S into D.");
    m_instr.insert(mask_match, "MOV     D,{#}S   {WC/WZ/WCZ}");
    descr += "D = S.";
    descr += "C = S[31].";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get !S into D.
 *
 * EEEE 0110001 CZI DDDDDDDDD SSSSSSSSS
 *
 * NOT     D,{#}S   {WC/WZ/WCZ}
 *
 * D = !S.
 * C = !S[31].
 * Z = (result == 0).
 *
 */
void P2Doc::doc_not(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0110001 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_NOT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get !S into D.");
    m_instr.insert(mask_match, "NOT     D,{#}S   {WC/WZ/WCZ}");
    descr += "D = !S.";
    descr += "C = !S[31].";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get absolute value of S into D.
 *
 * EEEE 0110010 CZI DDDDDDDDD SSSSSSSSS
 *
 * ABS     D,{#}S   {WC/WZ/WCZ}
 *
 * D = ABS(S).
 * C = S[31].
 * Z = (result == 0).
 *
 */
void P2Doc::doc_abs(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0110010 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ABS);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get absolute value of S into D.");
    m_instr.insert(mask_match, "ABS     D,{#}S   {WC/WZ/WCZ}");
    descr += "D = ABS(S).";
    descr += "C = S[31].";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Negate S into D.
 *
 * EEEE 0110011 CZI DDDDDDDDD SSSSSSSSS
 *
 * NEG     D,{#}S   {WC/WZ/WCZ}
 *
 * D = -S.
 * C = MSB of result.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_neg(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0110011 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_NEG);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Negate S into D.");
    m_instr.insert(mask_match, "NEG     D,{#}S   {WC/WZ/WCZ}");
    descr += "D = -S.";
    descr += "C = MSB of result.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Negate S by  C into D.
 *
 * EEEE 0110100 CZI DDDDDDDDD SSSSSSSSS
 *
 * NEGC    D,{#}S   {WC/WZ/WCZ}
 *
 * If C = 1 then D = -S, else D = S.
 * C = MSB of result.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_negc(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0110100 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_NEGC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Negate S by  C into D.");
    m_instr.insert(mask_match, "NEGC    D,{#}S   {WC/WZ/WCZ}");
    descr += "If C = 1 then D = -S, else D = S.";
    descr += "C = MSB of result.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Negate S by !C into D.
 *
 * EEEE 0110101 CZI DDDDDDDDD SSSSSSSSS
 *
 * NEGNC   D,{#}S   {WC/WZ/WCZ}
 *
 * If C = 0 then D = -S, else D = S.
 * C = MSB of result.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_negnc(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0110101 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_NEGNC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Negate S by !C into D.");
    m_instr.insert(mask_match, "NEGNC   D,{#}S   {WC/WZ/WCZ}");
    descr += "If C = 0 then D = -S, else D = S.";
    descr += "C = MSB of result.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Negate S by  Z into D.
 *
 * EEEE 0110110 CZI DDDDDDDDD SSSSSSSSS
 *
 * NEGZ    D,{#}S   {WC/WZ/WCZ}
 *
 * If Z = 1 then D = -S, else D = S.
 * C = MSB of result.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_negz(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0110110 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_NEGZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Negate S by  Z into D.");
    m_instr.insert(mask_match, "NEGZ    D,{#}S   {WC/WZ/WCZ}");
    descr += "If Z = 1 then D = -S, else D = S.";
    descr += "C = MSB of result.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Negate S by !Z into D.
 *
 * EEEE 0110111 CZI DDDDDDDDD SSSSSSSSS
 *
 * NEGNZ   D,{#}S   {WC/WZ/WCZ}
 *
 * If Z = 0 then D = -S, else D = S.
 * C = MSB of result.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_negnz(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0110111 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_NEGNZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Negate S by !Z into D.");
    m_instr.insert(mask_match, "NEGNZ   D,{#}S   {WC/WZ/WCZ}");
    descr += "If Z = 0 then D = -S, else D = S.";
    descr += "C = MSB of result.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Increment with modulus.
 *
 * EEEE 0111000 CZI DDDDDDDDD SSSSSSSSS
 *
 * INCMOD  D,{#}S   {WC/WZ/WCZ}
 *
 * If D = S then D = 0 and C = 1, else D = D + 1 and C = 0.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_incmod(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0111000 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_INCMOD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Increment with modulus.");
    m_instr.insert(mask_match, "INCMOD  D,{#}S   {WC/WZ/WCZ}");
    descr += "If D = S then D = 0 and C = 1, else D = D + 1 and C = 0.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Decrement with modulus.
 *
 * EEEE 0111001 CZI DDDDDDDDD SSSSSSSSS
 *
 * DECMOD  D,{#}S   {WC/WZ/WCZ}
 *
 * If D = 0 then D = S and C = 1, else D = D - 1 and C = 0.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_decmod(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0111001 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_DECMOD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Decrement with modulus.");
    m_instr.insert(mask_match, "DECMOD  D,{#}S   {WC/WZ/WCZ}");
    descr += "If D = 0 then D = S and C = 1, else D = D - 1 and C = 0.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Zero-extend D above bit S[4:0].
 *
 * EEEE 0111010 CZI DDDDDDDDD SSSSSSSSS
 *
 * ZEROX   D,{#}S   {WC/WZ/WCZ}
 *
 * C = MSB of result.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_zerox(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0111010 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ZEROX);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Zero-extend D above bit S[4:0].");
    m_instr.insert(mask_match, "ZEROX   D,{#}S   {WC/WZ/WCZ}");
    descr += "C = MSB of result.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Sign-extend D from bit S[4:0].
 *
 * EEEE 0111011 CZI DDDDDDDDD SSSSSSSSS
 *
 * SIGNX   D,{#}S   {WC/WZ/WCZ}
 *
 * C = MSB of result.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_signx(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0111011 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SIGNX);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Sign-extend D from bit S[4:0].");
    m_instr.insert(mask_match, "SIGNX   D,{#}S   {WC/WZ/WCZ}");
    descr += "C = MSB of result.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get bit position of top-most '1' in S into D.
 *
 * EEEE 0111100 CZI DDDDDDDDD SSSSSSSSS
 *
 * ENCOD   D,{#}S   {WC/WZ/WCZ}
 *
 * D = position of top '1' in S (0..31).
 * C = (S != 0).
 * Z = (result == 0).
 *
 */
void P2Doc::doc_encod(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0111100 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ENCOD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get bit position of top-most '1' in S into D.");
    m_instr.insert(mask_match, "ENCOD   D,{#}S   {WC/WZ/WCZ}");
    descr += "D = position of top '1' in S (0..31).";
    descr += "C = (S != 0).";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get number of '1's in S into D.
 *
 * EEEE 0111101 CZI DDDDDDDDD SSSSSSSSS
 *
 * ONES    D,{#}S   {WC/WZ/WCZ}
 *
 * D = number of '1's in S (0..32).
 * C = LSB of result.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_ones(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0111101 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ONES);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get number of '1's in S into D.");
    m_instr.insert(mask_match, "ONES    D,{#}S   {WC/WZ/WCZ}");
    descr += "D = number of '1's in S (0..32).";
    descr += "C = LSB of result.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Test D with S.
 *
 * EEEE 0111110 CZI DDDDDDDDD SSSSSSSSS
 *
 * TEST    D,{#}S   {WC/WZ/WCZ}
 *
 * C = parity of (D & S).
 * Z = ((D & S) == 0).
 *
 */
void P2Doc::doc_test(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0111110 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_TEST);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test D with S.");
    m_instr.insert(mask_match, "TEST    D,{#}S   {WC/WZ/WCZ}");
    descr += "C = parity of (D & S).";
    descr += "Z = ((D & S) == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Test D with !S.
 *
 * EEEE 0111111 CZI DDDDDDDDD SSSSSSSSS
 *
 * TESTN   D,{#}S   {WC/WZ/WCZ}
 *
 * C = parity of (D & !S).
 * Z = ((D & !S) == 0).
 *
 */
void P2Doc::doc_testn(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 0111111 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_TESTN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test D with !S.");
    m_instr.insert(mask_match, "TESTN   D,{#}S   {WC/WZ/WCZ}");
    descr += "C = parity of (D & !S).";
    descr += "Z = ((D & !S) == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set S[3:0] into nibble N in D, keeping rest of D same.
 *
 * EEEE 100000N NNI DDDDDDDDD SSSSSSSSS
 *
 * SETNIB  D,{#}S,#N
 *
 *
 */
void P2Doc::doc_setnib(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 100000N NNI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SETNIB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set S[3:0] into nibble N in D, keeping rest of D same.");
    m_instr.insert(mask_match, "SETNIB  D,{#}S,#N");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set S[3:0] into nibble established by prior ALTSN instruction.
 *
 * EEEE 1000000 00I 000000000 SSSSSSSSS
 *
 * SETNIB  {#}S
 *
 *
 */
void P2Doc::doc_setnib_altsn(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1000000 00I 000000000 SSSSSSSSS");
    m_token.insert(mask_match, t_SETNIB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set S[3:0] into nibble established by prior ALTSN instruction.");
    m_instr.insert(mask_match, "SETNIB  {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get nibble N of S into D.
 *
 * EEEE 100001N NNI DDDDDDDDD SSSSSSSSS
 *
 * GETNIB  D,{#}S,#N
 *
 * D = {28'b0, S.NIBBLE[N]).
 *
 */
void P2Doc::doc_getnib(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 100001N NNI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_GETNIB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get nibble N of S into D.");
    m_instr.insert(mask_match, "GETNIB  D,{#}S,#N");
    descr += "D = {28'b0, S.NIBBLE[N]).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get nibble established by prior ALTGN instruction into D.
 *
 * EEEE 1000010 000 DDDDDDDDD 000000000
 *
 * GETNIB  D
 *
 *
 */
void P2Doc::doc_getnib_altgn(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1000010 000 DDDDDDDDD 000000000");
    m_token.insert(mask_match, t_GETNIB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get nibble established by prior ALTGN instruction into D.");
    m_instr.insert(mask_match, "GETNIB  D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Rotate-left nibble N of S into D.
 *
 * EEEE 100010N NNI DDDDDDDDD SSSSSSSSS
 *
 * ROLNIB  D,{#}S,#N
 *
 * D = {D[27:0], S.NIBBLE[N]).
 *
 */
void P2Doc::doc_rolnib(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 100010N NNI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ROLNIB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Rotate-left nibble N of S into D.");
    m_instr.insert(mask_match, "ROLNIB  D,{#}S,#N");
    descr += "D = {D[27:0], S.NIBBLE[N]).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Rotate-left nibble established by prior ALTGN instruction into D.
 *
 * EEEE 1000100 000 DDDDDDDDD 000000000
 *
 * ROLNIB  D
 *
 *
 */
void P2Doc::doc_rolnib_altgn(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1000100 000 DDDDDDDDD 000000000");
    m_token.insert(mask_match, t_ROLNIB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Rotate-left nibble established by prior ALTGN instruction into D.");
    m_instr.insert(mask_match, "ROLNIB  D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set S[7:0] into byte N in D, keeping rest of D same.
 *
 * EEEE 1000110 NNI DDDDDDDDD SSSSSSSSS
 *
 * SETBYTE D,{#}S,#N
 *
 *
 */
void P2Doc::doc_setbyte(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1000110 NNI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SETBYTE);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set S[7:0] into byte N in D, keeping rest of D same.");
    m_instr.insert(mask_match, "SETBYTE D,{#}S,#N");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set S[7:0] into byte established by prior ALTSB instruction.
 *
 * EEEE 1000110 00I 000000000 SSSSSSSSS
 *
 * SETBYTE {#}S
 *
 *
 */
void P2Doc::doc_setbyte_altsb(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1000110 00I 000000000 SSSSSSSSS");
    m_token.insert(mask_match, t_SETBYTE);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set S[7:0] into byte established by prior ALTSB instruction.");
    m_instr.insert(mask_match, "SETBYTE {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get byte N of S into D.
 *
 * EEEE 1000111 NNI DDDDDDDDD SSSSSSSSS
 *
 * GETBYTE D,{#}S,#N
 *
 * D = {24'b0, S.BYTE[N]).
 *
 */
void P2Doc::doc_getbyte(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1000111 NNI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_GETBYTE);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get byte N of S into D.");
    m_instr.insert(mask_match, "GETBYTE D,{#}S,#N");
    descr += "D = {24'b0, S.BYTE[N]).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get byte established by prior ALTGB instruction into D.
 *
 * EEEE 1000111 000 DDDDDDDDD 000000000
 *
 * GETBYTE D
 *
 *
 */
void P2Doc::doc_getbyte_altgb(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1000111 000 DDDDDDDDD 000000000");
    m_token.insert(mask_match, t_GETBYTE);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get byte established by prior ALTGB instruction into D.");
    m_instr.insert(mask_match, "GETBYTE D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Rotate-left byte N of S into D.
 *
 * EEEE 1001000 NNI DDDDDDDDD SSSSSSSSS
 *
 * ROLBYTE D,{#}S,#N
 *
 * D = {D[23:0], S.BYTE[N]).
 *
 */
void P2Doc::doc_rolbyte(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001000 NNI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ROLBYTE);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Rotate-left byte N of S into D.");
    m_instr.insert(mask_match, "ROLBYTE D,{#}S,#N");
    descr += "D = {D[23:0], S.BYTE[N]).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Rotate-left byte established by prior ALTGB instruction into D.
 *
 * EEEE 1001000 000 DDDDDDDDD 000000000
 *
 * ROLBYTE D
 *
 *
 */
void P2Doc::doc_rolbyte_altgb(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001000 000 DDDDDDDDD 000000000");
    m_token.insert(mask_match, t_ROLBYTE);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Rotate-left byte established by prior ALTGB instruction into D.");
    m_instr.insert(mask_match, "ROLBYTE D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set S[15:0] into word N in D, keeping rest of D same.
 *
 * EEEE 1001001 0NI DDDDDDDDD SSSSSSSSS
 *
 * SETWORD D,{#}S,#N
 *
 *
 */
void P2Doc::doc_setword(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001001 0NI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SETWORD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set S[15:0] into word N in D, keeping rest of D same.");
    m_instr.insert(mask_match, "SETWORD D,{#}S,#N");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set S[15:0] into word established by prior ALTSW instruction.
 *
 * EEEE 1001001 00I 000000000 SSSSSSSSS
 *
 * SETWORD {#}S
 *
 *
 */
void P2Doc::doc_setword_altsw(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001001 00I 000000000 SSSSSSSSS");
    m_token.insert(mask_match, t_SETWORD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set S[15:0] into word established by prior ALTSW instruction.");
    m_instr.insert(mask_match, "SETWORD {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get word N of S into D.
 *
 * EEEE 1001001 1NI DDDDDDDDD SSSSSSSSS
 *
 * GETWORD D,{#}S,#N
 *
 * D = {16'b0, S.WORD[N]).
 *
 */
void P2Doc::doc_getword(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001001 1NI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_GETWORD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get word N of S into D.");
    m_instr.insert(mask_match, "GETWORD D,{#}S,#N");
    descr += "D = {16'b0, S.WORD[N]).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get word established by prior ALTGW instruction into D.
 *
 * EEEE 1001001 100 DDDDDDDDD 000000000
 *
 * GETWORD D
 *
 *
 */
void P2Doc::doc_getword_altgw(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001001 100 DDDDDDDDD 000000000");
    m_token.insert(mask_match, t_GETWORD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get word established by prior ALTGW instruction into D.");
    m_instr.insert(mask_match, "GETWORD D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Rotate-left word N of S into D.
 *
 * EEEE 1001010 0NI DDDDDDDDD SSSSSSSSS
 *
 * ROLWORD D,{#}S,#N
 *
 * D = {D[15:0], S.WORD[N]).
 *
 */
void P2Doc::doc_rolword(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001010 0NI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ROLWORD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Rotate-left word N of S into D.");
    m_instr.insert(mask_match, "ROLWORD D,{#}S,#N");
    descr += "D = {D[15:0], S.WORD[N]).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Rotate-left word established by prior ALTGW instruction into D.
 *
 * EEEE 1001010 000 DDDDDDDDD 000000000
 *
 * ROLWORD D
 *
 *
 */
void P2Doc::doc_rolword_altgw(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001010 000 DDDDDDDDD 000000000");
    m_token.insert(mask_match, t_ROLWORD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Rotate-left word established by prior ALTGW instruction into D.");
    m_instr.insert(mask_match, "ROLWORD D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter subsequent SETNIB instruction.
 *
 * EEEE 1001010 10I DDDDDDDDD SSSSSSSSS
 *
 * ALTSN   D,{#}S
 *
 * Next D field = (D[11:3] + S) & $1FF, N field = D[2:0].
 * D += sign-extended S[17:9].
 *
 */
void P2Doc::doc_altsn(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001010 10I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ALTSN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter subsequent SETNIB instruction.");
    m_instr.insert(mask_match, "ALTSN   D,{#}S");
    descr += "Next D field = (D[11:3] + S) & $1FF, N field = D[2:0].";
    descr += "D += sign-extended S[17:9].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter subsequent SETNIB instruction.
 *
 * EEEE 1001010 101 DDDDDDDDD 000000000
 *
 * ALTSN   D
 *
 * Next D field = D[11:3], N field = D[2:0].
 *
 */
void P2Doc::doc_altsn_d(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001010 101 DDDDDDDDD 000000000");
    m_token.insert(mask_match, t_ALTSN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter subsequent SETNIB instruction.");
    m_instr.insert(mask_match, "ALTSN   D");
    descr += "Next D field = D[11:3], N field = D[2:0].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter subsequent GETNIB/ROLNIB instruction.
 *
 * EEEE 1001010 11I DDDDDDDDD SSSSSSSSS
 *
 * ALTGN   D,{#}S
 *
 * Next S field = (D[11:3] + S) & $1FF, N field = D[2:0].
 * D += sign-extended S[17:9].
 *
 */
void P2Doc::doc_altgn(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001010 11I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ALTGN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter subsequent GETNIB/ROLNIB instruction.");
    m_instr.insert(mask_match, "ALTGN   D,{#}S");
    descr += "Next S field = (D[11:3] + S) & $1FF, N field = D[2:0].";
    descr += "D += sign-extended S[17:9].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter subsequent GETNIB/ROLNIB instruction.
 *
 * EEEE 1001010 111 DDDDDDDDD 000000000
 *
 * ALTGN   D
 *
 * Next S field = D[11:3], N field = D[2:0].
 *
 */
void P2Doc::doc_altgn_d(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001010 111 DDDDDDDDD 000000000");
    m_token.insert(mask_match, t_ALTGN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter subsequent GETNIB/ROLNIB instruction.");
    m_instr.insert(mask_match, "ALTGN   D");
    descr += "Next S field = D[11:3], N field = D[2:0].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter subsequent SETBYTE instruction.
 *
 * EEEE 1001011 00I DDDDDDDDD SSSSSSSSS
 *
 * ALTSB   D,{#}S
 *
 * Next D field = (D[10:2] + S) & $1FF, N field = D[1:0].
 * D += sign-extended S[17:9].
 *
 */
void P2Doc::doc_altsb(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001011 00I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ALTSB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter subsequent SETBYTE instruction.");
    m_instr.insert(mask_match, "ALTSB   D,{#}S");
    descr += "Next D field = (D[10:2] + S) & $1FF, N field = D[1:0].";
    descr += "D += sign-extended S[17:9].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter subsequent SETBYTE instruction.
 *
 * EEEE 1001011 001 DDDDDDDDD 000000000
 *
 * ALTSB   D
 *
 * Next D field = D[10:2], N field = D[1:0].
 *
 */
void P2Doc::doc_altsb_d(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001011 001 DDDDDDDDD 000000000");
    m_token.insert(mask_match, t_ALTSB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter subsequent SETBYTE instruction.");
    m_instr.insert(mask_match, "ALTSB   D");
    descr += "Next D field = D[10:2], N field = D[1:0].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter subsequent GETBYTE/ROLBYTE instruction.
 *
 * EEEE 1001011 01I DDDDDDDDD SSSSSSSSS
 *
 * ALTGB   D,{#}S
 *
 * Next S field = (D[10:2] + S) & $1FF, N field = D[1:0].
 * D += sign-extended S[17:9].
 *
 */
void P2Doc::doc_altgb(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001011 01I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ALTGB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter subsequent GETBYTE/ROLBYTE instruction.");
    m_instr.insert(mask_match, "ALTGB   D,{#}S");
    descr += "Next S field = (D[10:2] + S) & $1FF, N field = D[1:0].";
    descr += "D += sign-extended S[17:9].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter subsequent GETBYTE/ROLBYTE instruction.
 *
 * EEEE 1001011 011 DDDDDDDDD 000000000
 *
 * ALTGB   D
 *
 * Next S field = D[10:2], N field = D[1:0].
 *
 */
void P2Doc::doc_altgb_d(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001011 011 DDDDDDDDD 000000000");
    m_token.insert(mask_match, t_ALTGB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter subsequent GETBYTE/ROLBYTE instruction.");
    m_instr.insert(mask_match, "ALTGB   D");
    descr += "Next S field = D[10:2], N field = D[1:0].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter subsequent SETWORD instruction.
 *
 * EEEE 1001011 10I DDDDDDDDD SSSSSSSSS
 *
 * ALTSW   D,{#}S
 *
 * Next D field = (D[9:1] + S) & $1FF, N field = D[0].
 * D += sign-extended S[17:9].
 *
 */
void P2Doc::doc_altsw(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001011 10I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ALTSW);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter subsequent SETWORD instruction.");
    m_instr.insert(mask_match, "ALTSW   D,{#}S");
    descr += "Next D field = (D[9:1] + S) & $1FF, N field = D[0].";
    descr += "D += sign-extended S[17:9].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter subsequent SETWORD instruction.
 *
 * EEEE 1001011 101 DDDDDDDDD 000000000
 *
 * ALTSW   D
 *
 * Next D field = D[9:1], N field = D[0].
 *
 */
void P2Doc::doc_altsw_d(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001011 101 DDDDDDDDD 000000000");
    m_token.insert(mask_match, t_ALTSW);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter subsequent SETWORD instruction.");
    m_instr.insert(mask_match, "ALTSW   D");
    descr += "Next D field = D[9:1], N field = D[0].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter subsequent GETWORD/ROLWORD instruction.
 *
 * EEEE 1001011 11I DDDDDDDDD SSSSSSSSS
 *
 * ALTGW   D,{#}S
 *
 * Next S field = ((D[9:1] + S) & $1FF), N field = D[0].
 * D += sign-extended S[17:9].
 *
 */
void P2Doc::doc_altgw(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001011 11I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ALTGW);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter subsequent GETWORD/ROLWORD instruction.");
    m_instr.insert(mask_match, "ALTGW   D,{#}S");
    descr += "Next S field = ((D[9:1] + S) & $1FF), N field = D[0].";
    descr += "D += sign-extended S[17:9].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter subsequent GETWORD/ROLWORD instruction.
 *
 * EEEE 1001011 111 DDDDDDDDD 000000000
 *
 * ALTGW   D
 *
 * Next S field = D[9:1], N field = D[0].
 *
 */
void P2Doc::doc_altgw_d(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001011 111 DDDDDDDDD 000000000");
    m_token.insert(mask_match, t_ALTGW);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter subsequent GETWORD/ROLWORD instruction.");
    m_instr.insert(mask_match, "ALTGW   D");
    descr += "Next S field = D[9:1], N field = D[0].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter result register address (normally D field) of next instruction to (D + S) & $1FF.
 *
 * EEEE 1001100 00I DDDDDDDDD SSSSSSSSS
 *
 * ALTR    D,{#}S
 *
 * D += sign-extended S[17:9].
 *
 */
void P2Doc::doc_altr(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001100 00I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ALTR);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter result register address (normally D field) of next instruction to (D + S) & $1FF.");
    m_instr.insert(mask_match, "ALTR    D,{#}S");
    descr += "D += sign-extended S[17:9].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter result register address (normally D field) of next instruction to D[8:0].
 *
 * EEEE 1001100 001 DDDDDDDDD 000000000
 *
 * ALTR    D
 *
 *
 */
void P2Doc::doc_altr_d(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001100 001 DDDDDDDDD 000000000");
    m_token.insert(mask_match, t_ALTD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter result register address (normally D field) of next instruction to D[8:0].");
    m_instr.insert(mask_match, "ALTR    D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter D field of next instruction to (D + S) & $1FF.
 *
 * EEEE 1001100 01I DDDDDDDDD SSSSSSSSS
 *
 * ALTD    D,{#}S
 *
 * D += sign-extended S[17:9].
 *
 */
void P2Doc::doc_altd(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001100 01I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ALTD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter D field of next instruction to (D + S) & $1FF.");
    m_instr.insert(mask_match, "ALTD    D,{#}S");
    descr += "D += sign-extended S[17:9].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter D field of next instruction to D[8:0].
 *
 * EEEE 1001100 011 DDDDDDDDD 000000000
 *
 * ALTD    D
 *
 *
 */
void P2Doc::doc_altd_d(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001100 011 DDDDDDDDD 000000000");
    m_token.insert(mask_match, t_ALTD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter D field of next instruction to D[8:0].");
    m_instr.insert(mask_match, "ALTD    D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter S field of next instruction to (D + S) & $1FF.
 *
 * EEEE 1001100 10I DDDDDDDDD SSSSSSSSS
 *
 * ALTS    D,{#}S
 *
 * D += sign-extended S[17:9].
 *
 */
void P2Doc::doc_alts(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001100 10I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ALTS);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter S field of next instruction to (D + S) & $1FF.");
    m_instr.insert(mask_match, "ALTS    D,{#}S");
    descr += "D += sign-extended S[17:9].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter S field of next instruction to D[8:0].
 *
 * EEEE 1001100 101 DDDDDDDDD 000000000
 *
 * ALTS    D
 *
 *
 */
void P2Doc::doc_alts_d(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001100 101 DDDDDDDDD 000000000");
    m_token.insert(mask_match, t_ALTS);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter S field of next instruction to D[8:0].");
    m_instr.insert(mask_match, "ALTS    D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter D field of next instruction to (D[13:5] + S) & $1FF.
 *
 * EEEE 1001100 11I DDDDDDDDD SSSSSSSSS
 *
 * ALTB    D,{#}S
 *
 * D += sign-extended S[17:9].
 *
 */
void P2Doc::doc_altb(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001100 11I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ALTB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter D field of next instruction to (D[13:5] + S) & $1FF.");
    m_instr.insert(mask_match, "ALTB    D,{#}S");
    descr += "D += sign-extended S[17:9].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alter D field of next instruction to D[13:5].
 *
 * EEEE 1001100 111 DDDDDDDDD 000000000
 *
 * ALTB    D
 *
 *
 */
void P2Doc::doc_altb_d(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001100 111 DDDDDDDDD 000000000");
    m_token.insert(mask_match, t_ALTB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alter D field of next instruction to D[13:5].");
    m_instr.insert(mask_match, "ALTB    D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Substitute next instruction's I/R/D/S fields with fields from D, per S.
 *
 * EEEE 1001101 00I DDDDDDDDD SSSSSSSSS
 *
 * ALTI    D,{#}S
 *
 * Modify D per S.
 *
 */
void P2Doc::doc_alti(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001101 00I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ALTI);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Substitute next instruction's I/R/D/S fields with fields from D, per S.");
    m_instr.insert(mask_match, "ALTI    D,{#}S");
    descr += "Modify D per S.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Execute D in place of next instruction.
 *
 * EEEE 1001101 001 DDDDDDDDD 101100100
 *
 * ALTI    D
 *
 * D stays same.
 *
 */
void P2Doc::doc_alti_d(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001101 001 DDDDDDDDD 101100100");
    m_token.insert(mask_match, t_ALTI);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Execute D in place of next instruction.");
    m_instr.insert(mask_match, "ALTI    D");
    descr += "D stays same.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set R field of D to S[8:0].
 *
 * EEEE 1001101 01I DDDDDDDDD SSSSSSSSS
 *
 * SETR    D,{#}S
 *
 * D = {D[31:28], S[8:0], D[18:0]}.
 *
 */
void P2Doc::doc_setr(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001101 01I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SETR);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set R field of D to S[8:0].");
    m_instr.insert(mask_match, "SETR    D,{#}S");
    descr += "D = {D[31:28], S[8:0], D[18:0]}.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set D field of D to S[8:0].
 *
 * EEEE 1001101 10I DDDDDDDDD SSSSSSSSS
 *
 * SETD    D,{#}S
 *
 * D = {D[31:18], S[8:0], D[8:0]}.
 *
 */
void P2Doc::doc_setd(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001101 10I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SETD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set D field of D to S[8:0].");
    m_instr.insert(mask_match, "SETD    D,{#}S");
    descr += "D = {D[31:18], S[8:0], D[8:0]}.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set S field of D to S[8:0].
 *
 * EEEE 1001101 11I DDDDDDDDD SSSSSSSSS
 *
 * SETS    D,{#}S
 *
 * D = {D[31:9], S[8:0]}.
 *
 */
void P2Doc::doc_sets(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001101 11I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SETS);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set S field of D to S[8:0].");
    m_instr.insert(mask_match, "SETS    D,{#}S");
    descr += "D = {D[31:9], S[8:0]}.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Decode S[4:0] into D.
 *
 * EEEE 1001110 00I DDDDDDDDD SSSSSSSSS
 *
 * DECOD   D,{#}S
 *
 * D = 1 << S[4:0].
 *
 */
void P2Doc::doc_decod(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001110 00I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_DECOD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Decode S[4:0] into D.");
    m_instr.insert(mask_match, "DECOD   D,{#}S");
    descr += "D = 1 << S[4:0].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Decode D[4:0] into D.
 *
 * EEEE 1001110 000 DDDDDDDDD DDDDDDDDD
 *
 * DECOD   D
 *
 * D = 1 << D[4:0].
 *
 */
void P2Doc::doc_decod_d(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001110 000 DDDDDDDDD DDDDDDDDD");
    m_token.insert(mask_match, t_DECOD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Decode D[4:0] into D.");
    m_instr.insert(mask_match, "DECOD   D");
    descr += "D = 1 << D[4:0].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get LSB-justified bit mask of size (S[4:0] + 1) into D.
 *
 * EEEE 1001110 01I DDDDDDDDD SSSSSSSSS
 *
 * BMASK   D,{#}S
 *
 * D = ($0000_0002 << S[4:0]) - 1.
 *
 */
void P2Doc::doc_bmask(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001110 01I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_BMASK);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get LSB-justified bit mask of size (S[4:0] + 1) into D.");
    m_instr.insert(mask_match, "BMASK   D,{#}S");
    descr += "D = ($0000_0002 << S[4:0]) - 1.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get LSB-justified bit mask of size (D[4:0] + 1) into D.
 *
 * EEEE 1001110 010 DDDDDDDDD DDDDDDDDD
 *
 * BMASK   D
 *
 * D = ($0000_0002 << D[4:0]) - 1.
 *
 */
void P2Doc::doc_bmask_d(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001110 010 DDDDDDDDD DDDDDDDDD");
    m_token.insert(mask_match, t_BMASK);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get LSB-justified bit mask of size (D[4:0] + 1) into D.");
    m_instr.insert(mask_match, "BMASK   D");
    descr += "D = ($0000_0002 << D[4:0]) - 1.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Iterate CRC value in D using C and polynomial in S.
 *
 * EEEE 1001110 10I DDDDDDDDD SSSSSSSSS
 *
 * CRCBIT  D,{#}S
 *
 * If (C XOR D[0]) then D = (D >> 1) XOR S, else D = (D >> 1).
 *
 */
void P2Doc::doc_crcbit(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001110 10I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_CRCBIT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Iterate CRC value in D using C and polynomial in S.");
    m_instr.insert(mask_match, "CRCBIT  D,{#}S");
    descr += "If (C XOR D[0]) then D = (D >> 1) XOR S, else D = (D >> 1).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Iterate CRC value in D using Q[31:28] and polynomial in S.
 *
 * EEEE 1001110 11I DDDDDDDDD SSSSSSSSS
 *
 * CRCNIB  D,{#}S
 *
 * Like CRCBIT, but 4x.
 * Q = Q << 4.
 * Use SETQ+CRCNIB+CRCNIB+CRCNIB.
 *
 */
void P2Doc::doc_crcnib(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001110 11I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_CRCNIB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Iterate CRC value in D using Q[31:28] and polynomial in S.");
    m_instr.insert(mask_match, "CRCNIB  D,{#}S");
    descr += "Like CRCBIT, but 4x.";
    descr += "Q = Q << 4.";
    descr += "Use SETQ+CRCNIB+CRCNIB+CRCNIB.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief For each non-zero bit pair in S, copy that bit pair into the corresponding D bits, else leave that D bit pair the same.
 *
 * EEEE 1001111 00I DDDDDDDDD SSSSSSSSS
 *
 * MUXNITS D,{#}S
 *
 *
 */
void P2Doc::doc_muxnits(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001111 00I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_MUXNITS);
    QList<const char *> descr;
    m_brief.insert(mask_match, "For each non-zero bit pair in S, copy that bit pair into the corresponding D bits, else leave that D bit pair the same.");
    m_instr.insert(mask_match, "MUXNITS D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief For each non-zero nibble in S, copy that nibble into the corresponding D nibble, else leave that D nibble the same.
 *
 * EEEE 1001111 01I DDDDDDDDD SSSSSSSSS
 *
 * MUXNIBS D,{#}S
 *
 *
 */
void P2Doc::doc_muxnibs(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001111 01I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_MUXNIBS);
    QList<const char *> descr;
    m_brief.insert(mask_match, "For each non-zero nibble in S, copy that nibble into the corresponding D nibble, else leave that D nibble the same.");
    m_instr.insert(mask_match, "MUXNIBS D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Used after SETQ.
 *
 * EEEE 1001111 10I DDDDDDDDD SSSSSSSSS
 *
 * MUXQ    D,{#}S
 *
 * For each '1' bit in Q, copy the corresponding bit in S into D.
 * D = (D & !Q) | (S & Q).
 *
 */
void P2Doc::doc_muxq(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001111 10I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_MUXQ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Used after SETQ.");
    m_instr.insert(mask_match, "MUXQ    D,{#}S");
    descr += "For each '1' bit in Q, copy the corresponding bit in S into D.";
    descr += "D = (D & !Q) | (S & Q).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Move bytes within D, per S.
 *
 * EEEE 1001111 11I DDDDDDDDD SSSSSSSSS
 *
 * MOVBYTS D,{#}S
 *
 * D = {D.BYTE[S[7:6]], D.BYTE[S[5:4]], D.BYTE[S[3:2]], D.BYTE[S[1:0]]}.
 *
 */
void P2Doc::doc_movbyts(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1001111 11I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_MOVBYTS);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Move bytes within D, per S.");
    m_instr.insert(mask_match, "MOVBYTS D,{#}S");
    descr += "D = {D.BYTE[S[7:6]], D.BYTE[S[5:4]], D.BYTE[S[3:2]], D.BYTE[S[1:0]]}.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief D = unsigned (D[15:0] * S[15:0]).
 *
 * EEEE 1010000 0ZI DDDDDDDDD SSSSSSSSS
 *
 * MUL     D,{#}S          {WZ}
 *
 * Z = (S == 0) | (D == 0).
 *
 */
void P2Doc::doc_mul(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1010000 0ZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_MUL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "D = unsigned (D[15:0] * S[15:0]).");
    m_instr.insert(mask_match, "MUL     D,{#}S          {WZ}");
    descr += "Z = (S == 0) | (D == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief D = signed (D[15:0] * S[15:0]).
 *
 * EEEE 1010000 1ZI DDDDDDDDD SSSSSSSSS
 *
 * MULS    D,{#}S          {WZ}
 *
 * Z = (S == 0) | (D == 0).
 *
 */
void P2Doc::doc_muls(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1010000 1ZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_MULS);
    QList<const char *> descr;
    m_brief.insert(mask_match, "D = signed (D[15:0] * S[15:0]).");
    m_instr.insert(mask_match, "MULS    D,{#}S          {WZ}");
    descr += "Z = (S == 0) | (D == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Next instruction's S value = unsigned (D[15:0] * S[15:0]) >> 16.
 *
 * EEEE 1010001 0ZI DDDDDDDDD SSSSSSSSS
 *
 * SCA     D,{#}S          {WZ}
 *
 * Z = (result == 0).
 *
 */
void P2Doc::doc_sca(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1010001 0ZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SCA);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Next instruction's S value = unsigned (D[15:0] * S[15:0]) >> 16.");
    m_instr.insert(mask_match, "SCA     D,{#}S          {WZ}");
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Next instruction's S value = signed (D[15:0] * S[15:0]) >> 14.
 *
 * EEEE 1010001 1ZI DDDDDDDDD SSSSSSSSS
 *
 * SCAS    D,{#}S          {WZ}
 *
 * In this scheme, $4000 = 1.0 and $C000 = -1.0.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_scas(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1010001 1ZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SCAS);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Next instruction's S value = signed (D[15:0] * S[15:0]) >> 14.");
    m_instr.insert(mask_match, "SCAS    D,{#}S          {WZ}");
    descr += "In this scheme, $4000 = 1.0 and $C000 = -1.0.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Add bytes of S into bytes of D, with $FF saturation.
 *
 * EEEE 1010010 00I DDDDDDDDD SSSSSSSSS
 *
 * ADDPIX  D,{#}S
 *
 *
 */
void P2Doc::doc_addpix(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1010010 00I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ADDPIX);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Add bytes of S into bytes of D, with $FF saturation.");
    m_instr.insert(mask_match, "ADDPIX  D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Multiply bytes of S into bytes of D, where $FF = 1.
 *
 * EEEE 1010010 01I DDDDDDDDD SSSSSSSSS
 *
 * MULPIX  D,{#}S
 *
 * 0.
 *
 */
void P2Doc::doc_mulpix(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1010010 01I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_MULPIX);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Multiply bytes of S into bytes of D, where $FF = 1.");
    m_instr.insert(mask_match, "MULPIX  D,{#}S");
    descr += "0.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Alpha-blend bytes of S into bytes of D, using SETPIV value.
 *
 * EEEE 1010010 10I DDDDDDDDD SSSSSSSSS
 *
 * BLNPIX  D,{#}S
 *
 *
 */
void P2Doc::doc_blnpix(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1010010 10I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_BLNPIX);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Alpha-blend bytes of S into bytes of D, using SETPIV value.");
    m_instr.insert(mask_match, "BLNPIX  D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Mix bytes of S into bytes of D, using SETPIX and SETPIV values.
 *
 * EEEE 1010010 11I DDDDDDDDD SSSSSSSSS
 *
 * MIXPIX  D,{#}S
 *
 *
 */
void P2Doc::doc_mixpix(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1010010 11I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_MIXPIX);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Mix bytes of S into bytes of D, using SETPIX and SETPIV values.");
    m_instr.insert(mask_match, "MIXPIX  D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set CT1 event to trigger on CT = D + S.
 *
 * EEEE 1010011 00I DDDDDDDDD SSSSSSSSS
 *
 * ADDCT1  D,{#}S
 *
 * Adds S into D.
 *
 */
void P2Doc::doc_addct1(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1010011 00I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ADDCT1);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set CT1 event to trigger on CT = D + S.");
    m_instr.insert(mask_match, "ADDCT1  D,{#}S");
    descr += "Adds S into D.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set CT2 event to trigger on CT = D + S.
 *
 * EEEE 1010011 01I DDDDDDDDD SSSSSSSSS
 *
 * ADDCT2  D,{#}S
 *
 * Adds S into D.
 *
 */
void P2Doc::doc_addct2(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1010011 01I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ADDCT2);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set CT2 event to trigger on CT = D + S.");
    m_instr.insert(mask_match, "ADDCT2  D,{#}S");
    descr += "Adds S into D.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set CT3 event to trigger on CT = D + S.
 *
 * EEEE 1010011 10I DDDDDDDDD SSSSSSSSS
 *
 * ADDCT3  D,{#}S
 *
 * Adds S into D.
 *
 */
void P2Doc::doc_addct3(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1010011 10I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_ADDCT3);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set CT3 event to trigger on CT = D + S.");
    m_instr.insert(mask_match, "ADDCT3  D,{#}S");
    descr += "Adds S into D.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Write only non-$00 bytes in D[31:0] to hub address {#}S/PTRx.
 *
 * EEEE 1010011 11I DDDDDDDDD SSSSSSSSS
 *
 * WMLONG  D,{#}S/P
 *
 * Prior SETQ/SETQ2 invokes cog/LUT block transfer.
 *
 */
void P2Doc::doc_wmlong(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1010011 11I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_WMLONG);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Write only non-$00 bytes in D[31:0] to hub address {#}S/PTRx.");
    m_instr.insert(mask_match, "WMLONG  D,{#}S/P");
    descr += "Prior SETQ/SETQ2 invokes cog/LUT block transfer.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Read smart pin S[5:0] result "Z" into D, don't acknowledge smart pin ("Q" in RQPIN means "quiet").
 *
 * EEEE 1010100 C0I DDDDDDDDD SSSSSSSSS
 *
 * RQPIN   D,{#}S          {WC}
 *
 * C = modal result.
 *
 */
void P2Doc::doc_rqpin(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1010100 C0I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_RQPIN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Read smart pin S[5:0] result \"Z\" into D, don't acknowledge smart pin (\"Q\" in RQPIN means \"quiet\").");
    m_instr.insert(mask_match, "RQPIN   D,{#}S          {WC}");
    descr += "C = modal result.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Read smart pin S[5:0] result "Z" into D, acknowledge smart pin.
 *
 * EEEE 1010100 C1I DDDDDDDDD SSSSSSSSS
 *
 * RDPIN   D,{#}S          {WC}
 *
 * C = modal result.
 *
 */
void P2Doc::doc_rdpin(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1010100 x1I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_RDPIN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Read smart pin S[5:0] result \"Z\" into D, acknowledge smart pin.");
    m_instr.insert(mask_match, "RDPIN   D,{#}S          {WC}");
    descr += "C = modal result.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Read LUT data from address S[8:0] into D.
 *
 * EEEE 1010101 CZI DDDDDDDDD SSSSSSSSS
 *
 * RDLUT   D,{#}S   {WC/WZ/WCZ}
 *
 * C = MSB of data.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_rdlut(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1010101 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_RDLUT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Read LUT data from address S[8:0] into D.");
    m_instr.insert(mask_match, "RDLUT   D,{#}S   {WC/WZ/WCZ}");
    descr += "C = MSB of data.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Read zero-extended byte from hub address {#}S/PTRx into D.
 *
 * EEEE 1010110 CZI DDDDDDDDD SSSSSSSSS
 *
 * RDBYTE  D,{#}S/P {WC/WZ/WCZ}
 *
 * C = MSB of byte.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_rdbyte(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1010110 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_RDBYTE);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Read zero-extended byte from hub address {#}S/PTRx into D.");
    m_instr.insert(mask_match, "RDBYTE  D,{#}S/P {WC/WZ/WCZ}");
    descr += "C = MSB of byte.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Read zero-extended word from hub address {#}S/PTRx into D.
 *
 * EEEE 1010111 CZI DDDDDDDDD SSSSSSSSS
 *
 * RDWORD  D,{#}S/P {WC/WZ/WCZ}
 *
 * C = MSB of word.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_rdword(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1010111 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_RDWORD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Read zero-extended word from hub address {#}S/PTRx into D.");
    m_instr.insert(mask_match, "RDWORD  D,{#}S/P {WC/WZ/WCZ}");
    descr += "C = MSB of word.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Read long from hub address {#}S/PTRx into D.
 *
 * EEEE 1011000 CZI DDDDDDDDD SSSSSSSSS
 *
 * RDLONG  D,{#}S/P {WC/WZ/WCZ}
 *
 * C = MSB of long.
 * Prior SETQ/SETQ2 invokes cog/LUT block transfer.
 *
 */
void P2Doc::doc_rdlong(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011000 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_RDLONG);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Read long from hub address {#}S/PTRx into D.");
    m_instr.insert(mask_match, "RDLONG  D,{#}S/P {WC/WZ/WCZ}");
    descr += "C = MSB of long.";
    descr += "Prior SETQ/SETQ2 invokes cog/LUT block transfer.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Read long from hub address --PTRA into D.
 *
 * EEEE 1011000 CZ1 DDDDDDDDD 101011111
 *
 * POPA    D        {WC/WZ/WCZ}
 *
 * C = MSB of long.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_popa(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011000 CZ1 DDDDDDDDD 101011111");
    m_token.insert(mask_match, t_POPA);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Read long from hub address --PTRA into D.");
    m_instr.insert(mask_match, "POPA    D        {WC/WZ/WCZ}");
    descr += "C = MSB of long.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Read long from hub address --PTRB into D.
 *
 * EEEE 1011000 CZ1 DDDDDDDDD 111011111
 *
 * POPB    D        {WC/WZ/WCZ}
 *
 * C = MSB of long.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_popb(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011000 CZ1 DDDDDDDDD 111011111");
    m_token.insert(mask_match, t_POPB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Read long from hub address --PTRB into D.");
    m_instr.insert(mask_match, "POPB    D        {WC/WZ/WCZ}");
    descr += "C = MSB of long.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Call to S** by writing {C, Z, 10'b0, PC[19:0]} to D.
 *
 * EEEE 1011001 CZI DDDDDDDDD SSSSSSSSS
 *
 * CALLD   D,{#}S   {WC/WZ/WCZ}
 *
 * C = S[31], Z = S[30].
 *
 */
void P2Doc::doc_calld(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011001 CZI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_CALLD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Call to S** by writing {C, Z, 10'b0, PC[19:0]} to D.");
    m_instr.insert(mask_match, "CALLD   D,{#}S   {WC/WZ/WCZ}");
    descr += "C = S[31], Z = S[30].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Resume from INT3.
 *
 * EEEE 1011001 110 111110000 111110001
 *
 * RESI3
 *
 * (CALLD $1F0,$1F1 WC,WZ).
 *
 */
void P2Doc::doc_resi3(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011001 110 111110000 111110001");
    m_token.insert(mask_match, t_RESI3);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Resume from INT3.");
    m_instr.insert(mask_match, "RESI3");
    descr += "(CALLD $1F0,$1F1 WC,WZ).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Resume from INT2.
 *
 * EEEE 1011001 110 111110010 111110011
 *
 * RESI2
 *
 * (CALLD $1F2,$1F3 WC,WZ).
 *
 */
void P2Doc::doc_resi2(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011001 110 111110010 111110011");
    m_token.insert(mask_match, t_RESI2);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Resume from INT2.");
    m_instr.insert(mask_match, "RESI2");
    descr += "(CALLD $1F2,$1F3 WC,WZ).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Resume from INT1.
 *
 * EEEE 1011001 110 111110100 111110101
 *
 * RESI1
 *
 * (CALLD $1F4,$1F5 WC,WZ).
 *
 */
void P2Doc::doc_resi1(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011001 110 111110100 111110101");
    m_token.insert(mask_match, t_RESI1);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Resume from INT1.");
    m_instr.insert(mask_match, "RESI1");
    descr += "(CALLD $1F4,$1F5 WC,WZ).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Resume from INT0.
 *
 * EEEE 1011001 110 111111110 111111111
 *
 * RESI0
 *
 * (CALLD $1FE,$1FF WC,WZ).
 *
 */
void P2Doc::doc_resi0(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011001 110 111111110 111111111");
    m_token.insert(mask_match, t_RESI0);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Resume from INT0.");
    m_instr.insert(mask_match, "RESI0");
    descr += "(CALLD $1FE,$1FF WC,WZ).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Return from INT3.
 *
 * EEEE 1011001 110 111111111 111110001
 *
 * RETI3
 *
 * (CALLD $1FF,$1F1 WC,WZ).
 *
 */
void P2Doc::doc_reti3(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011001 110 111111111 111110001");
    m_token.insert(mask_match, t_RETI3);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Return from INT3.");
    m_instr.insert(mask_match, "RETI3");
    descr += "(CALLD $1FF,$1F1 WC,WZ).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Return from INT2.
 *
 * EEEE 1011001 110 111111111 111110011
 *
 * RETI2
 *
 * (CALLD $1FF,$1F3 WC,WZ).
 *
 */
void P2Doc::doc_reti2(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011001 110 111111111 111110011");
    m_token.insert(mask_match, t_RETI2);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Return from INT2.");
    m_instr.insert(mask_match, "RETI2");
    descr += "(CALLD $1FF,$1F3 WC,WZ).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Return from INT1.
 *
 * EEEE 1011001 110 111111111 111110101
 *
 * RETI1
 *
 * (CALLD $1FF,$1F5 WC,WZ).
 *
 */
void P2Doc::doc_reti1(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011001 110 111111111 111110101");
    m_token.insert(mask_match, t_RETI1);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Return from INT1.");
    m_instr.insert(mask_match, "RETI1");
    descr += "(CALLD $1FF,$1F5 WC,WZ).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Return from INT0.
 *
 * EEEE 1011001 110 111111111 111111111
 *
 * RETI0
 *
 * (CALLD $1FF,$1FF WC,WZ).
 *
 */
void P2Doc::doc_reti0(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011001 110 111111111 111111111");
    m_token.insert(mask_match, t_RETI0);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Return from INT0.");
    m_instr.insert(mask_match, "RETI0");
    descr += "(CALLD $1FF,$1FF WC,WZ).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Call to S** by pushing {C, Z, 10'b0, PC[19:0]} onto stack, copy D to PA.
 *
 * EEEE 1011010 0LI DDDDDDDDD SSSSSSSSS
 *
 * CALLPA  {#}D,{#}S
 *
 *
 */
void P2Doc::doc_callpa(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011010 0LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_CALLPA);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Call to S** by pushing {C, Z, 10'b0, PC[19:0]} onto stack, copy D to PA.");
    m_instr.insert(mask_match, "CALLPA  {#}D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Call to S** by pushing {C, Z, 10'b0, PC[19:0]} onto stack, copy D to PB.
 *
 * EEEE 1011010 1LI DDDDDDDDD SSSSSSSSS
 *
 * CALLPB  {#}D,{#}S
 *
 *
 */
void P2Doc::doc_callpb(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011010 1LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_CALLPB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Call to S** by pushing {C, Z, 10'b0, PC[19:0]} onto stack, copy D to PB.");
    m_instr.insert(mask_match, "CALLPB  {#}D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Decrement D and jump to S** if result is zero.
 *
 * EEEE 1011011 00I DDDDDDDDD SSSSSSSSS
 *
 * DJZ     D,{#}S
 *
 *
 */
void P2Doc::doc_djz(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011011 00I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_DJZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Decrement D and jump to S** if result is zero.");
    m_instr.insert(mask_match, "DJZ     D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Decrement D and jump to S** if result is not zero.
 *
 * EEEE 1011011 01I DDDDDDDDD SSSSSSSSS
 *
 * DJNZ    D,{#}S
 *
 *
 */
void P2Doc::doc_djnz(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011011 01I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_DJNZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Decrement D and jump to S** if result is not zero.");
    m_instr.insert(mask_match, "DJNZ    D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Decrement D and jump to S** if result is $FFFF_FFFF.
 *
 * EEEE 1011011 10I DDDDDDDDD SSSSSSSSS
 *
 * DJF     D,{#}S
 *
 *
 */
void P2Doc::doc_djf(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011011 10I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_DJF);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Decrement D and jump to S** if result is $FFFF_FFFF.");
    m_instr.insert(mask_match, "DJF     D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Decrement D and jump to S** if result is not $FFFF_FFFF.
 *
 * EEEE 1011011 11I DDDDDDDDD SSSSSSSSS
 *
 * DJNF    D,{#}S
 *
 *
 */
void P2Doc::doc_djnf(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011011 11I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_DJNF);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Decrement D and jump to S** if result is not $FFFF_FFFF.");
    m_instr.insert(mask_match, "DJNF    D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Increment D and jump to S** if result is zero.
 *
 * EEEE 1011100 00I DDDDDDDDD SSSSSSSSS
 *
 * IJZ     D,{#}S
 *
 *
 */
void P2Doc::doc_ijz(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011100 00I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_IJZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Increment D and jump to S** if result is zero.");
    m_instr.insert(mask_match, "IJZ     D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Increment D and jump to S** if result is not zero.
 *
 * EEEE 1011100 01I DDDDDDDDD SSSSSSSSS
 *
 * IJNZ    D,{#}S
 *
 *
 */
void P2Doc::doc_ijnz(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011100 01I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_IJNZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Increment D and jump to S** if result is not zero.");
    m_instr.insert(mask_match, "IJNZ    D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Test D and jump to S** if D is zero.
 *
 * EEEE 1011100 10I DDDDDDDDD SSSSSSSSS
 *
 * TJZ     D,{#}S
 *
 *
 */
void P2Doc::doc_tjz(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011100 10I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_TJZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test D and jump to S** if D is zero.");
    m_instr.insert(mask_match, "TJZ     D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Test D and jump to S** if D is not zero.
 *
 * EEEE 1011100 11I DDDDDDDDD SSSSSSSSS
 *
 * TJNZ    D,{#}S
 *
 *
 */
void P2Doc::doc_tjnz(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011100 11I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_TJNZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test D and jump to S** if D is not zero.");
    m_instr.insert(mask_match, "TJNZ    D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Test D and jump to S** if D is full (D = $FFFF_FFFF).
 *
 * EEEE 1011101 00I DDDDDDDDD SSSSSSSSS
 *
 * TJF     D,{#}S
 *
 *
 */
void P2Doc::doc_tjf(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011101 00I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_TJF);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test D and jump to S** if D is full (D = $FFFF_FFFF).");
    m_instr.insert(mask_match, "TJF     D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Test D and jump to S** if D is not full (D != $FFFF_FFFF).
 *
 * EEEE 1011101 01I DDDDDDDDD SSSSSSSSS
 *
 * TJNF    D,{#}S
 *
 *
 */
void P2Doc::doc_tjnf(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011101 01I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_TJNF);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test D and jump to S** if D is not full (D != $FFFF_FFFF).");
    m_instr.insert(mask_match, "TJNF    D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Test D and jump to S** if D is signed (D[31] = 1).
 *
 * EEEE 1011101 10I DDDDDDDDD SSSSSSSSS
 *
 * TJS     D,{#}S
 *
 *
 */
void P2Doc::doc_tjs(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011101 10I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_TJS);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test D and jump to S** if D is signed (D[31] = 1).");
    m_instr.insert(mask_match, "TJS     D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Test D and jump to S** if D is not signed (D[31] = 0).
 *
 * EEEE 1011101 11I DDDDDDDDD SSSSSSSSS
 *
 * TJNS    D,{#}S
 *
 *
 */
void P2Doc::doc_tjns(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011101 11I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_TJNS);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test D and jump to S** if D is not signed (D[31] = 0).");
    m_instr.insert(mask_match, "TJNS    D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Test D and jump to S** if D overflowed (D[31] != C, C = 'correct sign' from last addition/subtraction).
 *
 * EEEE 1011110 00I DDDDDDDDD SSSSSSSSS
 *
 * TJV     D,{#}S
 *
 *
 */
void P2Doc::doc_tjv(p2_inst9_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 00I DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_TJV);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test D and jump to S** if D overflowed (D[31] != C, C = 'correct sign' from last addition/subtraction).");
    m_instr.insert(mask_match, "TJV     D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if INT event flag is set.
 *
 * EEEE 1011110 01I 000000000 SSSSSSSSS
 *
 * JINT    {#}S
 *
 *
 */
void P2Doc::doc_jint(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000000000 SSSSSSSSS");
    m_token.insert(mask_match, t_JINT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if INT event flag is set.");
    m_instr.insert(mask_match, "JINT    {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if CT1 event flag is set.
 *
 * EEEE 1011110 01I 000000001 SSSSSSSSS
 *
 * JCT1    {#}S
 *
 *
 */
void P2Doc::doc_jct1(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000000001 SSSSSSSSS");
    m_token.insert(mask_match, t_JCT1);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if CT1 event flag is set.");
    m_instr.insert(mask_match, "JCT1    {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if CT2 event flag is set.
 *
 * EEEE 1011110 01I 000000010 SSSSSSSSS
 *
 * JCT2    {#}S
 *
 *
 */
void P2Doc::doc_jct2(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000000010 SSSSSSSSS");
    m_token.insert(mask_match, t_JCT2);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if CT2 event flag is set.");
    m_instr.insert(mask_match, "JCT2    {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if CT3 event flag is set.
 *
 * EEEE 1011110 01I 000000011 SSSSSSSSS
 *
 * JCT3    {#}S
 *
 *
 */
void P2Doc::doc_jct3(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000000011 SSSSSSSSS");
    m_token.insert(mask_match, t_JCT3);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if CT3 event flag is set.");
    m_instr.insert(mask_match, "JCT3    {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if SE1 event flag is set.
 *
 * EEEE 1011110 01I 000000100 SSSSSSSSS
 *
 * JSE1    {#}S
 *
 *
 */
void P2Doc::doc_jse1(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000000100 SSSSSSSSS");
    m_token.insert(mask_match, t_JSE1);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if SE1 event flag is set.");
    m_instr.insert(mask_match, "JSE1    {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if SE2 event flag is set.
 *
 * EEEE 1011110 01I 000000101 SSSSSSSSS
 *
 * JSE2    {#}S
 *
 *
 */
void P2Doc::doc_jse2(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000000101 SSSSSSSSS");
    m_token.insert(mask_match, t_JSE2);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if SE2 event flag is set.");
    m_instr.insert(mask_match, "JSE2    {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if SE3 event flag is set.
 *
 * EEEE 1011110 01I 000000110 SSSSSSSSS
 *
 * JSE3    {#}S
 *
 *
 */
void P2Doc::doc_jse3(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000000110 SSSSSSSSS");
    m_token.insert(mask_match, t_JSE3);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if SE3 event flag is set.");
    m_instr.insert(mask_match, "JSE3    {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if SE4 event flag is set.
 *
 * EEEE 1011110 01I 000000111 SSSSSSSSS
 *
 * JSE4    {#}S
 *
 *
 */
void P2Doc::doc_jse4(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000000111 SSSSSSSSS");
    m_token.insert(mask_match, t_JSE4);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if SE4 event flag is set.");
    m_instr.insert(mask_match, "JSE4    {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if PAT event flag is set.
 *
 * EEEE 1011110 01I 000001000 SSSSSSSSS
 *
 * JPAT    {#}S
 *
 *
 */
void P2Doc::doc_jpat(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000001000 SSSSSSSSS");
    m_token.insert(mask_match, t_JPAT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if PAT event flag is set.");
    m_instr.insert(mask_match, "JPAT    {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if FBW event flag is set.
 *
 * EEEE 1011110 01I 000001001 SSSSSSSSS
 *
 * JFBW    {#}S
 *
 *
 */
void P2Doc::doc_jfbw(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000001001 SSSSSSSSS");
    m_token.insert(mask_match, t_JFBW);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if FBW event flag is set.");
    m_instr.insert(mask_match, "JFBW    {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if XMT event flag is set.
 *
 * EEEE 1011110 01I 000001010 SSSSSSSSS
 *
 * JXMT    {#}S
 *
 *
 */
void P2Doc::doc_jxmt(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000001010 SSSSSSSSS");
    m_token.insert(mask_match, t_JXMT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if XMT event flag is set.");
    m_instr.insert(mask_match, "JXMT    {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if XFI event flag is set.
 *
 * EEEE 1011110 01I 000001011 SSSSSSSSS
 *
 * JXFI    {#}S
 *
 *
 */
void P2Doc::doc_jxfi(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000001011 SSSSSSSSS");
    m_token.insert(mask_match, t_JXFI);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if XFI event flag is set.");
    m_instr.insert(mask_match, "JXFI    {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if XRO event flag is set.
 *
 * EEEE 1011110 01I 000001100 SSSSSSSSS
 *
 * JXRO    {#}S
 *
 *
 */
void P2Doc::doc_jxro(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000001100 SSSSSSSSS");
    m_token.insert(mask_match, t_JXRO);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if XRO event flag is set.");
    m_instr.insert(mask_match, "JXRO    {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if XRL event flag is set.
 *
 * EEEE 1011110 01I 000001101 SSSSSSSSS
 *
 * JXRL    {#}S
 *
 *
 */
void P2Doc::doc_jxrl(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000001101 SSSSSSSSS");
    m_token.insert(mask_match, t_JXRL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if XRL event flag is set.");
    m_instr.insert(mask_match, "JXRL    {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if ATN event flag is set.
 *
 * EEEE 1011110 01I 000001110 SSSSSSSSS
 *
 * JATN    {#}S
 *
 *
 */
void P2Doc::doc_jatn(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000001110 SSSSSSSSS");
    m_token.insert(mask_match, t_JATN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if ATN event flag is set.");
    m_instr.insert(mask_match, "JATN    {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if QMT event flag is set.
 *
 * EEEE 1011110 01I 000001111 SSSSSSSSS
 *
 * JQMT    {#}S
 *
 *
 */
void P2Doc::doc_jqmt(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000001111 SSSSSSSSS");
    m_token.insert(mask_match, t_JQMT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if QMT event flag is set.");
    m_instr.insert(mask_match, "JQMT    {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if INT event flag is clear.
 *
 * EEEE 1011110 01I 000010000 SSSSSSSSS
 *
 * JNINT   {#}S
 *
 *
 */
void P2Doc::doc_jnint(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000010000 SSSSSSSSS");
    m_token.insert(mask_match, t_JNINT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if INT event flag is clear.");
    m_instr.insert(mask_match, "JNINT   {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if CT1 event flag is clear.
 *
 * EEEE 1011110 01I 000010001 SSSSSSSSS
 *
 * JNCT1   {#}S
 *
 *
 */
void P2Doc::doc_jnct1(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000010001 SSSSSSSSS");
    m_token.insert(mask_match, t_JNCT1);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if CT1 event flag is clear.");
    m_instr.insert(mask_match, "JNCT1   {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if CT2 event flag is clear.
 *
 * EEEE 1011110 01I 000010010 SSSSSSSSS
 *
 * JNCT2   {#}S
 *
 *
 */
void P2Doc::doc_jnct2(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000010010 SSSSSSSSS");
    m_token.insert(mask_match, t_JNCT2);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if CT2 event flag is clear.");
    m_instr.insert(mask_match, "JNCT2   {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if CT3 event flag is clear.
 *
 * EEEE 1011110 01I 000010011 SSSSSSSSS
 *
 * JNCT3   {#}S
 *
 *
 */
void P2Doc::doc_jnct3(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000010011 SSSSSSSSS");
    m_token.insert(mask_match, t_JNCT3);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if CT3 event flag is clear.");
    m_instr.insert(mask_match, "JNCT3   {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if SE1 event flag is clear.
 *
 * EEEE 1011110 01I 000010100 SSSSSSSSS
 *
 * JNSE1   {#}S
 *
 *
 */
void P2Doc::doc_jnse1(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000010100 SSSSSSSSS");
    m_token.insert(mask_match, t_JNSE1);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if SE1 event flag is clear.");
    m_instr.insert(mask_match, "JNSE1   {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if SE2 event flag is clear.
 *
 * EEEE 1011110 01I 000010101 SSSSSSSSS
 *
 * JNSE2   {#}S
 *
 *
 */
void P2Doc::doc_jnse2(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000010101 SSSSSSSSS");
    m_token.insert(mask_match, t_JNSE2);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if SE2 event flag is clear.");
    m_instr.insert(mask_match, "JNSE2   {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if SE3 event flag is clear.
 *
 * EEEE 1011110 01I 000010110 SSSSSSSSS
 *
 * JNSE3   {#}S
 *
 *
 */
void P2Doc::doc_jnse3(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000010110 SSSSSSSSS");
    m_token.insert(mask_match, t_JNSE3);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if SE3 event flag is clear.");
    m_instr.insert(mask_match, "JNSE3   {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if SE4 event flag is clear.
 *
 * EEEE 1011110 01I 000010111 SSSSSSSSS
 *
 * JNSE4   {#}S
 *
 *
 */
void P2Doc::doc_jnse4(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000010111 SSSSSSSSS");
    m_token.insert(mask_match, t_JNSE4);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if SE4 event flag is clear.");
    m_instr.insert(mask_match, "JNSE4   {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if PAT event flag is clear.
 *
 * EEEE 1011110 01I 000011000 SSSSSSSSS
 *
 * JNPAT   {#}S
 *
 *
 */
void P2Doc::doc_jnpat(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000011000 SSSSSSSSS");
    m_token.insert(mask_match, t_JNPAT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if PAT event flag is clear.");
    m_instr.insert(mask_match, "JNPAT   {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if FBW event flag is clear.
 *
 * EEEE 1011110 01I 000011001 SSSSSSSSS
 *
 * JNFBW   {#}S
 *
 *
 */
void P2Doc::doc_jnfbw(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000011001 SSSSSSSSS");
    m_token.insert(mask_match, t_JNFBW);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if FBW event flag is clear.");
    m_instr.insert(mask_match, "JNFBW   {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if XMT event flag is clear.
 *
 * EEEE 1011110 01I 000011010 SSSSSSSSS
 *
 * JNXMT   {#}S
 *
 *
 */
void P2Doc::doc_jnxmt(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000011010 SSSSSSSSS");
    m_token.insert(mask_match, t_JNXMT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if XMT event flag is clear.");
    m_instr.insert(mask_match, "JNXMT   {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if XFI event flag is clear.
 *
 * EEEE 1011110 01I 000011011 SSSSSSSSS
 *
 * JNXFI   {#}S
 *
 *
 */
void P2Doc::doc_jnxfi(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000011011 SSSSSSSSS");
    m_token.insert(mask_match, t_JNXFI);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if XFI event flag is clear.");
    m_instr.insert(mask_match, "JNXFI   {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if XRO event flag is clear.
 *
 * EEEE 1011110 01I 000011100 SSSSSSSSS
 *
 * JNXRO   {#}S
 *
 *
 */
void P2Doc::doc_jnxro(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000011100 SSSSSSSSS");
    m_token.insert(mask_match, t_JNXRO);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if XRO event flag is clear.");
    m_instr.insert(mask_match, "JNXRO   {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if XRL event flag is clear.
 *
 * EEEE 1011110 01I 000011101 SSSSSSSSS
 *
 * JNXRL   {#}S
 *
 *
 */
void P2Doc::doc_jnxrl(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000011101 SSSSSSSSS");
    m_token.insert(mask_match, t_JNXRL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if XRL event flag is clear.");
    m_instr.insert(mask_match, "JNXRL   {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if ATN event flag is clear.
 *
 * EEEE 1011110 01I 000011110 SSSSSSSSS
 *
 * JNATN   {#}S
 *
 *
 */
void P2Doc::doc_jnatn(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000011110 SSSSSSSSS");
    m_token.insert(mask_match, t_JNATN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if ATN event flag is clear.");
    m_instr.insert(mask_match, "JNATN   {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to S** if QMT event flag is clear.
 *
 * EEEE 1011110 01I 000011111 SSSSSSSSS
 *
 * JNQMT   {#}S
 *
 *
 */
void P2Doc::doc_jnqmt(p2_opdst_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 01I 000011111 SSSSSSSSS");
    m_token.insert(mask_match, t_JNQMT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to S** if QMT event flag is clear.");
    m_instr.insert(mask_match, "JNQMT   {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief <empty>.
 *
 * EEEE 1011110 1LI DDDDDDDDD SSSSSSSSS
 *
 * <empty> {#}D,{#}S
 *
 *
 */
void P2Doc::doc_1011110_1(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011110 1LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_empty);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Undefined instruction <empty> %1011110_1.");
    m_instr.insert(mask_match, "<empty> {#}D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief <empty>.
 *
 * EEEE 1011111 0LI DDDDDDDDD SSSSSSSSS
 *
 * <empty> {#}D,{#}S
 *
 *
 */
void P2Doc::doc_1011111_0(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011111 0LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_empty);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Undefined instruction <empty> %1011111_0.");
    m_instr.insert(mask_match, "<empty> {#}D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set pin pattern for PAT event.
 *
 * EEEE 1011111 1LI DDDDDDDDD SSSSSSSSS
 *
 * SETPAT  {#}D,{#}S
 *
 * C selects INA/INB, Z selects =/!=, D provides mask value, S provides match value.
 *
 */
void P2Doc::doc_setpat(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1011111 1LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_SETPAT);
    QList<const char *> descr;
    m_instr.insert(mask_match, "SETPAT  {#}D,{#}S");
    m_brief.insert(mask_match, "Set pin pattern for PAT event.");
    descr += "C selects INA/INB, Z selects =/!=, D provides mask value, S provides match value.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Write D to mode register of smart pin S[5:0], acknowledge smart pin.
 *
 * EEEE 1100000 0LI DDDDDDDDD SSSSSSSSS
 *
 * WRPIN   {#}D,{#}S
 *
 *
 */
void P2Doc::doc_wrpin(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100000 0LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_WRPIN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Write D to mode register of smart pin S[5:0], acknowledge smart pin.");
    m_instr.insert(mask_match, "WRPIN   {#}D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Acknowledge smart pin S[5:0].
 *
 * EEEE 1100000 01I 000000001 SSSSSSSSS
 *
 * AKPIN   {#}S
 *
 *
 */
void P2Doc::doc_akpin(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100000 01I 000000001 SSSSSSSSS");
    m_token.insert(mask_match, t_AKPIN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Acknowledge smart pin S[5:0].");
    m_instr.insert(mask_match, "AKPIN   {#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Write D to parameter "X" of smart pin S[5:0], acknowledge smart pin.
 *
 * EEEE 1100000 1LI DDDDDDDDD SSSSSSSSS
 *
 * WXPIN   {#}D,{#}S
 *
 *
 */
void P2Doc::doc_wxpin(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100000 1LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_WXPIN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Write D to parameter \"X\" of smart pin S[5:0], acknowledge smart pin.");
    m_instr.insert(mask_match, "WXPIN   {#}D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Write D to parameter "Y" of smart pin S[5:0], acknowledge smart pin.
 *
 * EEEE 1100001 0LI DDDDDDDDD SSSSSSSSS
 *
 * WYPIN   {#}D,{#}S
 *
 *
 */
void P2Doc::doc_wypin(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100001 0LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_WYPIN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Write D to parameter \"Y\" of smart pin S[5:0], acknowledge smart pin.");
    m_instr.insert(mask_match, "WYPIN   {#}D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Write D to LUT address S[8:0].
 *
 * EEEE 1100001 1LI DDDDDDDDD SSSSSSSSS
 *
 * WRLUT   {#}D,{#}S
 *
 *
 */
void P2Doc::doc_wrlut(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100001 1LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_WRLUT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Write D to LUT address S[8:0].");
    m_instr.insert(mask_match, "WRLUT   {#}D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Write byte in D[7:0] to hub address {#}S/PTRx.
 *
 * EEEE 1100010 0LI DDDDDDDDD SSSSSSSSS
 *
 * WRBYTE  {#}D,{#}S/P
 *
 *
 */
void P2Doc::doc_wrbyte(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100010 0LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_WRBYTE);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Write byte in D[7:0] to hub address {#}S/PTRx.");
    m_instr.insert(mask_match, "WRBYTE  {#}D,{#}S/P");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Write word in D[15:0] to hub address {#}S/PTRx.
 *
 * EEEE 1100010 1LI DDDDDDDDD SSSSSSSSS
 *
 * WRWORD  {#}D,{#}S/P
 *
 *
 */
void P2Doc::doc_wrword(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100010 1LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_WRWORD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Write word in D[15:0] to hub address {#}S/PTRx.");
    m_instr.insert(mask_match, "WRWORD  {#}D,{#}S/P");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Write long in D[31:0] to hub address {#}S/PTRx.
 *
 * EEEE 1100011 0LI DDDDDDDDD SSSSSSSSS
 *
 * WRLONG  {#}D,{#}S/P
 *
 * Prior SETQ/SETQ2 invokes cog/LUT block transfer.
 *
 */
void P2Doc::doc_wrlong(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100011 0LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_WRLONG);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Write long in D[31:0] to hub address {#}S/PTRx.");
    m_instr.insert(mask_match, "WRLONG  {#}D,{#}S/P");
    descr += "Prior SETQ/SETQ2 invokes cog/LUT block transfer.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Write long in D[31:0] to hub address PTRA++.
 *
 * EEEE 1100011 0L1 DDDDDDDDD 101100001
 *
 * PUSHA   {#}D
 *
 *
 */
void P2Doc::doc_pusha(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100011 0L1 DDDDDDDDD 101100001");
    m_token.insert(mask_match, t_PUSHA);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Write long in D[31:0] to hub address PTRA++.");
    m_instr.insert(mask_match, "PUSHA   {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Write long in D[31:0] to hub address PTRB++.
 *
 * EEEE 1100011 0L1 DDDDDDDDD 111100001
 *
 * PUSHB   {#}D
 *
 *
 */
void P2Doc::doc_pushb(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100011 0L1 DDDDDDDDD 111100001");
    m_token.insert(mask_match, t_PUSHB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Write long in D[31:0] to hub address PTRB++.");
    m_instr.insert(mask_match, "PUSHB   {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Begin new fast hub read via FIFO.
 *
 * EEEE 1100011 1LI DDDDDDDDD SSSSSSSSS
 *
 * RDFAST  {#}D,{#}S
 *
 * D[31] = no wait, D[13:0] = block size in 64-byte units (0 = max), S[19:0] = block start address.
 *
 */
void P2Doc::doc_rdfast(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100011 1LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_RDFAST);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Begin new fast hub read via FIFO.");
    m_instr.insert(mask_match, "RDFAST  {#}D,{#}S");
    descr += "D[31] = no wait, D[13:0] = block size in 64-byte units (0 = max), S[19:0] = block start address.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Begin new fast hub write via FIFO.
 *
 * EEEE 1100100 0LI DDDDDDDDD SSSSSSSSS
 *
 * WRFAST  {#}D,{#}S
 *
 * D[31] = no wait, D[13:0] = block size in 64-byte units (0 = max), S[19:0] = block start address.
 *
 */
void P2Doc::doc_wrfast(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100100 0LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_WRFAST);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Begin new fast hub write via FIFO.");
    m_instr.insert(mask_match, "WRFAST  {#}D,{#}S");
    descr += "D[31] = no wait, D[13:0] = block size in 64-byte units (0 = max), S[19:0] = block start address.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set next block for when block wraps.
 *
 * EEEE 1100100 1LI DDDDDDDDD SSSSSSSSS
 *
 * FBLOCK  {#}D,{#}S
 *
 * D[13:0] = block size in 64-byte units (0 = max), S[19:0] = block start address.
 *
 */
void P2Doc::doc_fblock(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100100 1LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_FBLOCK);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set next block for when block wraps.");
    m_instr.insert(mask_match, "FBLOCK  {#}D,{#}S");
    descr += "D[13:0] = block size in 64-byte units (0 = max), S[19:0] = block start address.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Issue streamer command immediately, zeroing phase.
 *
 * EEEE 1100101 0LI DDDDDDDDD SSSSSSSSS
 *
 * XINIT   {#}D,{#}S
 *
 *
 */
void P2Doc::doc_xinit(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100101 0LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_XINIT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Issue streamer command immediately, zeroing phase.");
    m_instr.insert(mask_match, "XINIT   {#}D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Stop streamer immediately.
 *
 * EEEE 1100101 011 000000000 000000000
 *
 * XSTOP
 *
 *
 */
void P2Doc::doc_xstop(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100101 011 000000000 000000000");
    m_token.insert(mask_match, t_XSTOP);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Stop streamer immediately.");
    m_instr.insert(mask_match, "XSTOP");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Buffer new streamer command to be issued on final NCO rollover of current command, zeroing phase.
 *
 * EEEE 1100101 1LI DDDDDDDDD SSSSSSSSS
 *
 * XZERO   {#}D,{#}S
 *
 *
 */
void P2Doc::doc_xzero(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100101 1LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_XZERO);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Buffer new streamer command to be issued on final NCO rollover of current command, zeroing phase.");
    m_instr.insert(mask_match, "XZERO   {#}D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Buffer new streamer command to be issued on final NCO rollover of current command, continuing phase.
 *
 * EEEE 1100110 0LI DDDDDDDDD SSSSSSSSS
 *
 * XCONT   {#}D,{#}S
 *
 *
 */
void P2Doc::doc_xcont(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100110 0LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_XCONT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Buffer new streamer command to be issued on final NCO rollover of current command, continuing phase.");
    m_instr.insert(mask_match, "XCONT   {#}D,{#}S");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Execute next D[8:0] instructions S times.
 *
 * EEEE 1100110 1LI DDDDDDDDD SSSSSSSSS
 *
 * REP     {#}D,{#}S
 *
 * If S = 0, repeat infinitely.
 * If D[8:0] = 0, nothing repeats.
 *
 */
void P2Doc::doc_rep(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100110 1LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_REP);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Execute next D[8:0] instructions S times.");
    m_instr.insert(mask_match, "REP     {#}D,{#}S");
    descr += "If S = 0, repeat infinitely.";
    descr += "If D[8:0] = 0, nothing repeats.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Start cog selected by D.
 *
 * EEEE 1100111 CLI DDDDDDDDD SSSSSSSSS
 *
 * COGINIT {#}D,{#}S       {WC}
 *
 * S[19:0] sets hub startup address and PTRB of cog.
 * Prior SETQ sets PTRA of cog.
 *
 */
void P2Doc::doc_coginit(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1100111 CLI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_COGINIT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Start cog selected by D.");
    m_instr.insert(mask_match, "COGINIT {#}D,{#}S       {WC}");
    descr += "S[19:0] sets hub startup address and PTRB of cog.";
    descr += "Prior SETQ sets PTRA of cog.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Begin CORDIC unsigned multiplication of D * S.
 *
 * EEEE 1101000 0LI DDDDDDDDD SSSSSSSSS
 *
 * QMUL    {#}D,{#}S
 *
 * GETQX/GETQY retrieves lower/upper product.
 *
 */
void P2Doc::doc_qmul(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101000 0LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_QMUL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Begin CORDIC unsigned multiplication of D * S.");
    m_instr.insert(mask_match, "QMUL    {#}D,{#}S");
    descr += "GETQX/GETQY retrieves lower/upper product.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Begin CORDIC unsigned division of {SETQ value or 32'b0, D} / S.
 *
 * EEEE 1101000 1LI DDDDDDDDD SSSSSSSSS
 *
 * QDIV    {#}D,{#}S
 *
 * GETQX/GETQY retrieves quotient/remainder.
 *
 */
void P2Doc::doc_qdiv(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101000 1LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_QDIV);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Begin CORDIC unsigned division of {SETQ value or 32'b0, D} / S.");
    m_instr.insert(mask_match, "QDIV    {#}D,{#}S");
    descr += "GETQX/GETQY retrieves quotient/remainder.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Begin CORDIC unsigned division of {D, SETQ value or 32'b0} / S.
 *
 * EEEE 1101001 0LI DDDDDDDDD SSSSSSSSS
 *
 * QFRAC   {#}D,{#}S
 *
 * GETQX/GETQY retrieves quotient/remainder.
 *
 */
void P2Doc::doc_qfrac(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101001 0LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_QFRAC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Begin CORDIC unsigned division of {D, SETQ value or 32'b0} / S.");
    m_instr.insert(mask_match, "QFRAC   {#}D,{#}S");
    descr += "GETQX/GETQY retrieves quotient/remainder.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Begin CORDIC square root of {S, D}.
 *
 * EEEE 1101001 1LI DDDDDDDDD SSSSSSSSS
 *
 * QSQRT   {#}D,{#}S
 *
 * GETQX retrieves root.
 *
 */
void P2Doc::doc_qsqrt(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101001 1LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_QSQRT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Begin CORDIC square root of {S, D}.");
    m_instr.insert(mask_match, "QSQRT   {#}D,{#}S");
    descr += "GETQX retrieves root.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Begin CORDIC rotation of point (D, SETQ value or 32'b0) by angle S.
 *
 * EEEE 1101010 0LI DDDDDDDDD SSSSSSSSS
 *
 * QROTATE {#}D,{#}S
 *
 * GETQX/GETQY retrieves X/Y.
 *
 */
void P2Doc::doc_qrotate(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101010 0LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_QROTATE);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Begin CORDIC rotation of point (D, SETQ value or 32'b0) by angle S.");
    m_instr.insert(mask_match, "QROTATE {#}D,{#}S");
    descr += "GETQX/GETQY retrieves X/Y.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Begin CORDIC vectoring of point (D, S).
 *
 * EEEE 1101010 1LI DDDDDDDDD SSSSSSSSS
 *
 * QVECTOR {#}D,{#}S
 *
 * GETQX/GETQY retrieves length/angle.
 *
 */
void P2Doc::doc_qvector(p2_inst8_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101010 1LI DDDDDDDDD SSSSSSSSS");
    m_token.insert(mask_match, t_QVECTOR);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Begin CORDIC vectoring of point (D, S).");
    m_instr.insert(mask_match, "QVECTOR {#}D,{#}S");
    descr += "GETQX/GETQY retrieves length/angle.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set hub configuration to D.
 *
 * EEEE 1101011 00L DDDDDDDDD 000000000
 *
 * HUBSET  {#}D
 *
 *
 */
void P2Doc::doc_hubset(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000000000");
    m_token.insert(mask_match, t_HUBSET);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set hub configuration to D.");
    m_instr.insert(mask_match, "HUBSET  {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief If D is register and no WC, get cog ID (0 to 15) into D.
 *
 * EEEE 1101011 C0L DDDDDDDDD 000000001
 *
 * COGID   {#}D            {WC}
 *
 * If WC, check status of cog D[3:0], C = 1 if on.
 *
 */
void P2Doc::doc_cogid(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 C0L DDDDDDDDD 000000001");
    m_token.insert(mask_match, t_COGID);
    QList<const char *> descr;
    m_brief.insert(mask_match, "If D is register and no WC, get cog ID (0 to 15) into D.");
    m_instr.insert(mask_match, "COGID   {#}D            {WC}");
    descr += "If WC, check status of cog D[3:0], C = 1 if on.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Stop cog D[3:0].
 *
 * EEEE 1101011 00L DDDDDDDDD 000000011
 *
 * COGSTOP {#}D
 *
 *
 */
void P2Doc::doc_cogstop(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000000011");
    m_token.insert(mask_match, t_COGSTOP);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Stop cog D[3:0].");
    m_instr.insert(mask_match, "COGSTOP {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Request a LOCK.
 *
 * EEEE 1101011 C00 DDDDDDDDD 000000100
 *
 * LOCKNEW D               {WC}
 *
 * D will be written with the LOCK number (0 to 15).
 * C = 1 if no LOCK available.
 *
 */
void P2Doc::doc_locknew(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 C00 DDDDDDDDD 000000100");
    m_token.insert(mask_match, t_LOCKNEW);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Request a LOCK.");
    m_instr.insert(mask_match, "LOCKNEW D               {WC}");
    descr += "D will be written with the LOCK number (0 to 15).";
    descr += "C = 1 if no LOCK available.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Return LOCK D[3:0] for reallocation.
 *
 * EEEE 1101011 00L DDDDDDDDD 000000101
 *
 * LOCKRET {#}D
 *
 *
 */
void P2Doc::doc_lockret(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000000101");
    m_token.insert(mask_match, t_LOCKRET);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Return LOCK D[3:0] for reallocation.");
    m_instr.insert(mask_match, "LOCKRET {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Try to get LOCK D[3:0].
 *
 * EEEE 1101011 C0L DDDDDDDDD 000000110
 *
 * LOCKTRY {#}D            {WC}
 *
 * C = 1 if got LOCK.
 * LOCKREL releases LOCK.
 * LOCK is also released if owner cog stops or restarts.
 *
 */
void P2Doc::doc_locktry(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 C0L DDDDDDDDD 000000110");
    m_token.insert(mask_match, t_LOCKTRY);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Try to get LOCK D[3:0].");
    m_instr.insert(mask_match, "LOCKTRY {#}D            {WC}");
    descr += "C = 1 if got LOCK.";
    descr += "LOCKREL releases LOCK.";
    descr += "LOCK is also released if owner cog stops or restarts.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Release LOCK D[3:0].
 *
 * EEEE 1101011 C0L DDDDDDDDD 000000111
 *
 * LOCKREL {#}D            {WC}
 *
 * If D is a register and WC, get current/last cog id of LOCK owner into D and LOCK status into C.
 *
 */
void P2Doc::doc_lockrel(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 C0L DDDDDDDDD 000000111");
    m_token.insert(mask_match, t_LOCKREL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Release LOCK D[3:0].");
    m_instr.insert(mask_match, "LOCKREL {#}D            {WC}");
    descr += "If D is a register and WC, get current/last cog id of LOCK owner into D and LOCK status into C.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Begin CORDIC number-to-logarithm conversion of D.
 *
 * EEEE 1101011 00L DDDDDDDDD 000001110
 *
 * QLOG    {#}D
 *
 * GETQX retrieves log {5'whole_exponent, 27'fractional_exponent}.
 *
 */
void P2Doc::doc_qlog(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000001110");
    m_token.insert(mask_match, t_QLOG);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Begin CORDIC number-to-logarithm conversion of D.");
    m_instr.insert(mask_match, "QLOG    {#}D");
    descr += "GETQX retrieves log {5'whole_exponent, 27'fractional_exponent}.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Begin CORDIC logarithm-to-number conversion of D.
 *
 * EEEE 1101011 00L DDDDDDDDD 000001111
 *
 * QEXP    {#}D
 *
 * GETQX retrieves number.
 *
 */
void P2Doc::doc_qexp(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000001111");
    m_token.insert(mask_match, t_QEXP);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Begin CORDIC logarithm-to-number conversion of D.");
    m_instr.insert(mask_match, "QEXP    {#}D");
    descr += "GETQX retrieves number.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Read zero-extended byte from FIFO into D. Used after RDFAST.
 *
 * EEEE 1101011 CZ0 DDDDDDDDD 000010000
 *
 * RFBYTE  D        {WC/WZ/WCZ}
 *
 * C = MSB of byte.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_rfbyte(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 DDDDDDDDD 000010000");
    m_token.insert(mask_match, t_RFBYTE);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Read zero-extended byte from FIFO into D. Used after RDFAST.");
    m_instr.insert(mask_match, "RFBYTE  D        {WC/WZ/WCZ}");
    descr += "C = MSB of byte.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Read zero-extended word from FIFO into D. Used after RDFAST.
 *
 * EEEE 1101011 CZ0 DDDDDDDDD 000010001
 *
 * RFWORD  D        {WC/WZ/WCZ}
 *
 * C = MSB of word.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_rfword(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 DDDDDDDDD 000010001");
    m_token.insert(mask_match, t_RFWORD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Read zero-extended word from FIFO into D. Used after RDFAST.");
    m_instr.insert(mask_match, "RFWORD  D        {WC/WZ/WCZ}");
    descr += "C = MSB of word.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Read long from FIFO into D. Used after RDFAST.
 *
 * EEEE 1101011 CZ0 DDDDDDDDD 000010010
 *
 * RFLONG  D        {WC/WZ/WCZ}
 *
 * C = MSB of long.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_rflong(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 DDDDDDDDD 000010010");
    m_token.insert(mask_match, t_RFLONG);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Read long from FIFO into D. Used after RDFAST.");
    m_instr.insert(mask_match, "RFLONG  D        {WC/WZ/WCZ}");
    descr += "C = MSB of long.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Read zero-extended 1..4-byte value from FIFO into D. Used after RDFAST.
 *
 * EEEE 1101011 CZ0 DDDDDDDDD 000010011
 *
 * RFVAR   D        {WC/WZ/WCZ}
 *
 * C = 0.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_rfvar(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 DDDDDDDDD 000010011");
    m_token.insert(mask_match, t_RFVAR);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Read zero-extended 1..4-byte value from FIFO into D. Used after RDFAST.");
    m_instr.insert(mask_match, "RFVAR   D        {WC/WZ/WCZ}");
    descr += "C = 0.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Read sign-extended 1..4-byte value from FIFO into D. Used after RDFAST.
 *
 * EEEE 1101011 CZ0 DDDDDDDDD 000010100
 *
 * RFVARS  D        {WC/WZ/WCZ}
 *
 * C = MSB of value.
 * Z = (result == 0).
 *
 */
void P2Doc::doc_rfvars(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 DDDDDDDDD 000010100");
    m_token.insert(mask_match, t_RFVARS);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Read sign-extended 1..4-byte value from FIFO into D. Used after RDFAST.");
    m_instr.insert(mask_match, "RFVARS  D        {WC/WZ/WCZ}");
    descr += "C = MSB of value.";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Write byte in D[7:0] into FIFO. Used after WRFAST.
 *
 * EEEE 1101011 00L DDDDDDDDD 000010101
 *
 * WFBYTE  {#}D
 *
 *
 */
void P2Doc::doc_wfbyte(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000010101");
    m_token.insert(mask_match, t_WFBYTE);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Write byte in D[7:0] into FIFO. Used after WRFAST.");
    m_instr.insert(mask_match, "WFBYTE  {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Write word in D[15:0] into FIFO. Used after WRFAST.
 *
 * EEEE 1101011 00L DDDDDDDDD 000010110
 *
 * WFWORD  {#}D
 *
 *
 */
void P2Doc::doc_wfword(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000010110");
    m_token.insert(mask_match, t_WFWORD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Write word in D[15:0] into FIFO. Used after WRFAST.");
    m_instr.insert(mask_match, "WFWORD  {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Write long in D[31:0] into FIFO. Used after WRFAST.
 *
 * EEEE 1101011 00L DDDDDDDDD 000010111
 *
 * WFLONG  {#}D
 *
 *
 */
void P2Doc::doc_wflong(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000010111");
    m_token.insert(mask_match, t_WFLONG);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Write long in D[31:0] into FIFO. Used after WRFAST.");
    m_instr.insert(mask_match, "WFLONG  {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Retrieve CORDIC result X into D.
 *
 * EEEE 1101011 CZ0 DDDDDDDDD 000011000
 *
 * GETQX   D        {WC/WZ/WCZ}
 *
 * Waits, in case result not ready.
 * C = X[31].
 * Z = (result == 0).
 *
 */
void P2Doc::doc_getqx(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 DDDDDDDDD 000011000");
    m_token.insert(mask_match, t_GETQX);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Retrieve CORDIC result X into D.");
    m_instr.insert(mask_match, "GETQX   D        {WC/WZ/WCZ}");
    descr += "Waits, in case result not ready.";
    descr += "C = X[31].";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Retrieve CORDIC result Y into D.
 *
 * EEEE 1101011 CZ0 DDDDDDDDD 000011001
 *
 * GETQY   D        {WC/WZ/WCZ}
 *
 * Waits, in case result no ready.
 * C = Y[31].
 * Z = (result == 0).
 *
 */
void P2Doc::doc_getqy(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 DDDDDDDDD 000011001");
    m_token.insert(mask_match, t_GETQY);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Retrieve CORDIC result Y into D.");
    m_instr.insert(mask_match, "GETQY   D        {WC/WZ/WCZ}");
    descr += "Waits, in case result no ready.";
    descr += "C = Y[31].";
    descr += "Z = (result == 0).";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get CT into D.
 *
 * EEEE 1101011 000 DDDDDDDDD 000011010
 *
 * GETCT   D
 *
 * CT is the free-running 32-bit system counter that increments on every clock.
 *
 */
void P2Doc::doc_getct(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 DDDDDDDDD 000011010");
    m_token.insert(mask_match, t_GETCT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get CT into D.");
    m_instr.insert(mask_match, "GETCT   D");
    descr += "CT is the free-running 32-bit system counter that increments on every clock.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get RND into D/C/Z.
 *
 * EEEE 1101011 CZ0 DDDDDDDDD 000011011
 *
 * GETRND  D        {WC/WZ/WCZ}
 *
 * RND is the PRNG that updates on every clock.
 * D = RND[31:0], C = RND[31], Z = RND[30], unique per cog.
 *
 */
void P2Doc::doc_getrnd(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 DDDDDDDDD 000011011");
    m_token.insert(mask_match, t_GETRND);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get RND into D/C/Z.");
    m_instr.insert(mask_match, "GETRND  D        {WC/WZ/WCZ}");
    descr += "RND is the PRNG that updates on every clock.";
    descr += "D = RND[31:0], C = RND[31], Z = RND[30], unique per cog.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get RND into C/Z.
 *
 * EEEE 1101011 CZ1 000000000 000011011
 *
 * GETRND            WC/WZ/WCZ
 *
 * C = RND[31], Z = RND[30], unique per cog.
 *
 */
void P2Doc::doc_getrnd_cz(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ1 000000000 000011011");
    m_token.insert(mask_match, t_GETRND);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get RND into C/Z.");
    m_instr.insert(mask_match, "GETRND            WC/WZ/WCZ");
    descr += "C = RND[31], Z = RND[30], unique per cog.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief DAC3 = D[31:24], DAC2 = D[23:16], DAC1 = D[15:8], DAC0 = D[7:0].
 *
 * EEEE 1101011 00L DDDDDDDDD 000011100
 *
 * SETDACS {#}D
 *
 *
 */
void P2Doc::doc_setdacs(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000011100");
    m_token.insert(mask_match, t_SETDACS);
    QList<const char *> descr;
    m_brief.insert(mask_match, "DAC3 = D[31:24], DAC2 = D[23:16], DAC1 = D[15:8], DAC0 = D[7:0].");
    m_instr.insert(mask_match, "SETDACS {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set streamer NCO frequency to D.
 *
 * EEEE 1101011 00L DDDDDDDDD 000011101
 *
 * SETXFRQ {#}D
 *
 *
 */
void P2Doc::doc_setxfrq(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000011101");
    m_token.insert(mask_match, t_SETXFRQ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set streamer NCO frequency to D.");
    m_instr.insert(mask_match, "SETXFRQ {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get the streamer's Goertzel X accumulator into D and the Y accumulator into the next instruction's S, clear accumulators.
 *
 * EEEE 1101011 000 DDDDDDDDD 000011110
 *
 * GETXACC D
 *
 *
 */
void P2Doc::doc_getxacc(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 DDDDDDDDD 000011110");
    m_token.insert(mask_match, t_GETXACC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get the streamer's Goertzel X accumulator into D and the Y accumulator into the next instruction's S, clear accumulators.");
    m_instr.insert(mask_match, "GETXACC D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Wait 2 + D clocks if no WC/WZ/WCZ.
 *
 * EEEE 1101011 00L DDDDDDDDD 000011111
 *
 * WAITX   {#}D     {WC/WZ/WCZ}
 *
 * If WC/WZ/WCZ, wait 2 + (D & RND) clocks.
 * C/Z = 0.
 *
 */
void P2Doc::doc_waitx(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000011111");
    m_token.insert(mask_match, t_WAITX);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Wait 2 + D clocks if no WC/WZ/WCZ.");
    m_instr.insert(mask_match, "WAITX   {#}D     {WC/WZ/WCZ}");
    descr += "If WC/WZ/WCZ, wait 2 + (D & RND) clocks.";
    descr += "C/Z = 0.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set SE1 event configuration to D[8:0].
 *
 * EEEE 1101011 00L DDDDDDDDD 000100000
 *
 * SETSE1  {#}D
 *
 *
 */
void P2Doc::doc_setse1(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000100000");
    m_token.insert(mask_match, t_SETSE1);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set SE1 event configuration to D[8:0].");
    m_instr.insert(mask_match, "SETSE1  {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set SE2 event configuration to D[8:0].
 *
 * EEEE 1101011 00L DDDDDDDDD 000100001
 *
 * SETSE2  {#}D
 *
 *
 */
void P2Doc::doc_setse2(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000100001");
    m_token.insert(mask_match, t_SETSE2);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set SE2 event configuration to D[8:0].");
    m_instr.insert(mask_match, "SETSE2  {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set SE3 event configuration to D[8:0].
 *
 * EEEE 1101011 00L DDDDDDDDD 000100010
 *
 * SETSE3  {#}D
 *
 *
 */
void P2Doc::doc_setse3(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000100010");
    m_token.insert(mask_match, t_SETSE3);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set SE3 event configuration to D[8:0].");
    m_instr.insert(mask_match, "SETSE3  {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set SE4 event configuration to D[8:0].
 *
 * EEEE 1101011 00L DDDDDDDDD 000100011
 *
 * SETSE4  {#}D
 *
 *
 */
void P2Doc::doc_setse4(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000100011");
    m_token.insert(mask_match, t_SETSE4);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set SE4 event configuration to D[8:0].");
    m_instr.insert(mask_match, "SETSE4  {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get INT event flag into C/Z, then clear it.
 *
 * EEEE 1101011 CZ0 000000000 000100100
 *
 * POLLINT          {WC/WZ/WCZ}
 *
 *
 */
void P2Doc::doc_pollint(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000000000 000100100");
    m_token.insert(mask_match, t_POLLINT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get INT event flag into C/Z, then clear it.");
    m_instr.insert(mask_match, "POLLINT          {WC/WZ/WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get CT1 event flag into C/Z, then clear it.
 *
 * EEEE 1101011 CZ0 000000001 000100100
 *
 * POLLCT1          {WC/WZ/WCZ}
 *
 *
 */
void P2Doc::doc_pollct1(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000000001 000100100");
    m_token.insert(mask_match, t_POLLCT1);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get CT1 event flag into C/Z, then clear it.");
    m_instr.insert(mask_match, "POLLCT1          {WC/WZ/WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get CT2 event flag into C/Z, then clear it.
 *
 * EEEE 1101011 CZ0 000000010 000100100
 *
 * POLLCT2          {WC/WZ/WCZ}
 *
 *
 */
void P2Doc::doc_pollct2(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000000010 000100100");
    m_token.insert(mask_match, t_POLLCT2);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get CT2 event flag into C/Z, then clear it.");
    m_instr.insert(mask_match, "POLLCT2          {WC/WZ/WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get CT3 event flag into C/Z, then clear it.
 *
 * EEEE 1101011 CZ0 000000011 000100100
 *
 * POLLCT3          {WC/WZ/WCZ}
 *
 *
 */
void P2Doc::doc_pollct3(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000000011 000100100");
    m_token.insert(mask_match, t_POLLCT3);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get CT3 event flag into C/Z, then clear it.");
    m_instr.insert(mask_match, "POLLCT3          {WC/WZ/WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get SE1 event flag into C/Z, then clear it.
 *
 * EEEE 1101011 CZ0 000000100 000100100
 *
 * POLLSE1          {WC/WZ/WCZ}
 *
 *
 */
void P2Doc::doc_pollse1(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000000100 000100100");
    m_token.insert(mask_match, t_POLLSE1);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get SE1 event flag into C/Z, then clear it.");
    m_instr.insert(mask_match, "POLLSE1          {WC/WZ/WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get SE2 event flag into C/Z, then clear it.
 *
 * EEEE 1101011 CZ0 000000101 000100100
 *
 * POLLSE2          {WC/WZ/WCZ}
 *
 *
 */
void P2Doc::doc_pollse2(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000000101 000100100");
    m_token.insert(mask_match, t_POLLSE2);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get SE2 event flag into C/Z, then clear it.");
    m_instr.insert(mask_match, "POLLSE2          {WC/WZ/WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get SE3 event flag into C/Z, then clear it.
 *
 * EEEE 1101011 CZ0 000000110 000100100
 *
 * POLLSE3          {WC/WZ/WCZ}
 *
 *
 */
void P2Doc::doc_pollse3(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000000110 000100100");
    m_token.insert(mask_match, t_POLLSE3);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get SE3 event flag into C/Z, then clear it.");
    m_instr.insert(mask_match, "POLLSE3          {WC/WZ/WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get SE4 event flag into C/Z, then clear it.
 *
 * EEEE 1101011 CZ0 000000111 000100100
 *
 * POLLSE4          {WC/WZ/WCZ}
 *
 *
 */
void P2Doc::doc_pollse4(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000000111 000100100");
    m_token.insert(mask_match, t_POLLSE4);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get SE4 event flag into C/Z, then clear it.");
    m_instr.insert(mask_match, "POLLSE4          {WC/WZ/WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get PAT event flag into C/Z, then clear it.
 *
 * EEEE 1101011 CZ0 000001000 000100100
 *
 * POLLPAT          {WC/WZ/WCZ}
 *
 *
 */
void P2Doc::doc_pollpat(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000001000 000100100");
    m_token.insert(mask_match, t_POLLPAT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get PAT event flag into C/Z, then clear it.");
    m_instr.insert(mask_match, "POLLPAT          {WC/WZ/WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get FBW event flag into C/Z, then clear it.
 *
 * EEEE 1101011 CZ0 000001001 000100100
 *
 * POLLFBW          {WC/WZ/WCZ}
 *
 *
 */
void P2Doc::doc_pollfbw(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000001001 000100100");
    m_token.insert(mask_match, t_POLLFBW);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get FBW event flag into C/Z, then clear it.");
    m_instr.insert(mask_match, "POLLFBW          {WC/WZ/WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get XMT event flag into C/Z, then clear it.
 *
 * EEEE 1101011 CZ0 000001010 000100100
 *
 * POLLXMT          {WC/WZ/WCZ}
 *
 *
 */
void P2Doc::doc_pollxmt(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000001010 000100100");
    m_token.insert(mask_match, t_POLLXMT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get XMT event flag into C/Z, then clear it.");
    m_instr.insert(mask_match, "POLLXMT          {WC/WZ/WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get XFI event flag into C/Z, then clear it.
 *
 * EEEE 1101011 CZ0 000001011 000100100
 *
 * POLLXFI          {WC/WZ/WCZ}
 *
 *
 */
void P2Doc::doc_pollxfi(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000001011 000100100");
    m_token.insert(mask_match, t_POLLXFI);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get XFI event flag into C/Z, then clear it.");
    m_instr.insert(mask_match, "POLLXFI          {WC/WZ/WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get XRO event flag into C/Z, then clear it.
 *
 * EEEE 1101011 CZ0 000001100 000100100
 *
 * POLLXRO          {WC/WZ/WCZ}
 *
 *
 */
void P2Doc::doc_pollxro(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000001100 000100100");
    m_token.insert(mask_match, t_POLLXRO);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get XRO event flag into C/Z, then clear it.");
    m_instr.insert(mask_match, "POLLXRO          {WC/WZ/WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get XRL event flag into C/Z, then clear it.
 *
 * EEEE 1101011 CZ0 000001101 000100100
 *
 * POLLXRL          {WC/WZ/WCZ}
 *
 *
 */
void P2Doc::doc_pollxrl(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000001101 000100100");
    m_token.insert(mask_match, t_POLLXRL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get XRL event flag into C/Z, then clear it.");
    m_instr.insert(mask_match, "POLLXRL          {WC/WZ/WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get ATN event flag into C/Z, then clear it.
 *
 * EEEE 1101011 CZ0 000001110 000100100
 *
 * POLLATN          {WC/WZ/WCZ}
 *
 *
 */
void P2Doc::doc_pollatn(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000001110 000100100");
    m_token.insert(mask_match, t_POLLATN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get ATN event flag into C/Z, then clear it.");
    m_instr.insert(mask_match, "POLLATN          {WC/WZ/WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get QMT event flag into C/Z, then clear it.
 *
 * EEEE 1101011 CZ0 000001111 000100100
 *
 * POLLQMT          {WC/WZ/WCZ}
 *
 *
 */
void P2Doc::doc_pollqmt(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000001111 000100100");
    m_token.insert(mask_match, t_POLLQMT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get QMT event flag into C/Z, then clear it.");
    m_instr.insert(mask_match, "POLLQMT          {WC/WZ/WCZ}");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Wait for INT event flag, then clear it.
 *
 * EEEE 1101011 CZ0 000010000 000100100
 *
 * WAITINT          {WC/WZ/WCZ}
 *
 * Prior SETQ sets optional CT timeout value.
 * C/Z = timeout.
 *
 */
void P2Doc::doc_waitint(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000010000 000100100");
    m_token.insert(mask_match, t_WAITINT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Wait for INT event flag, then clear it.");
    m_instr.insert(mask_match, "WAITINT          {WC/WZ/WCZ}");
    descr += "Prior SETQ sets optional CT timeout value.";
    descr += "C/Z = timeout.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Wait for CT1 event flag, then clear it.
 *
 * EEEE 1101011 CZ0 000010001 000100100
 *
 * WAITCT1          {WC/WZ/WCZ}
 *
 * Prior SETQ sets optional CT timeout value.
 * C/Z = timeout.
 *
 */
void P2Doc::doc_waitct1(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000010001 000100100");
    m_token.insert(mask_match, t_WAITCT1);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Wait for CT1 event flag, then clear it.");
    m_instr.insert(mask_match, "WAITCT1          {WC/WZ/WCZ}");
    descr += "Prior SETQ sets optional CT timeout value.";
    descr += "C/Z = timeout.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Wait for CT2 event flag, then clear it.
 *
 * EEEE 1101011 CZ0 000010010 000100100
 *
 * WAITCT2          {WC/WZ/WCZ}
 *
 * Prior SETQ sets optional CT timeout value.
 * C/Z = timeout.
 *
 */
void P2Doc::doc_waitct2(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000010010 000100100");
    m_token.insert(mask_match, t_WAITCT2);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Wait for CT2 event flag, then clear it.");
    m_instr.insert(mask_match, "WAITCT2          {WC/WZ/WCZ}");
    descr += "Prior SETQ sets optional CT timeout value.";
    descr += "C/Z = timeout.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Wait for CT3 event flag, then clear it.
 *
 * EEEE 1101011 CZ0 000010011 000100100
 *
 * WAITCT3          {WC/WZ/WCZ}
 *
 * Prior SETQ sets optional CT timeout value.
 * C/Z = timeout.
 *
 */
void P2Doc::doc_waitct3(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000010011 000100100");
    m_token.insert(mask_match, t_WAITCT3);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Wait for CT3 event flag, then clear it.");
    m_instr.insert(mask_match, "WAITCT3          {WC/WZ/WCZ}");
    descr += "Prior SETQ sets optional CT timeout value.";
    descr += "C/Z = timeout.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Wait for SE1 event flag, then clear it.
 *
 * EEEE 1101011 CZ0 000010100 000100100
 *
 * WAITSE1          {WC/WZ/WCZ}
 *
 * Prior SETQ sets optional CT timeout value.
 * C/Z = timeout.
 *
 */
void P2Doc::doc_waitse1(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000010100 000100100");
    m_token.insert(mask_match, t_WAITSE1);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Wait for SE1 event flag, then clear it.");
    m_instr.insert(mask_match, "WAITSE1          {WC/WZ/WCZ}");
    descr += "Prior SETQ sets optional CT timeout value.";
    descr += "C/Z = timeout.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Wait for SE2 event flag, then clear it.
 *
 * EEEE 1101011 CZ0 000010101 000100100
 *
 * WAITSE2          {WC/WZ/WCZ}
 *
 * Prior SETQ sets optional CT timeout value.
 * C/Z = timeout.
 *
 */
void P2Doc::doc_waitse2(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000010101 000100100");
    m_token.insert(mask_match, t_WAITSE2);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Wait for SE2 event flag, then clear it.");
    m_instr.insert(mask_match, "WAITSE2          {WC/WZ/WCZ}");
    descr += "Prior SETQ sets optional CT timeout value.";
    descr += "C/Z = timeout.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Wait for SE3 event flag, then clear it.
 *
 * EEEE 1101011 CZ0 000010110 000100100
 *
 * WAITSE3          {WC/WZ/WCZ}
 *
 * Prior SETQ sets optional CT timeout value.
 * C/Z = timeout.
 *
 */
void P2Doc::doc_waitse3(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000010110 000100100");
    m_token.insert(mask_match, t_WAITSE3);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Wait for SE3 event flag, then clear it.");
    m_instr.insert(mask_match, "WAITSE3          {WC/WZ/WCZ}");
    descr += "Prior SETQ sets optional CT timeout value.";
    descr += "C/Z = timeout.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Wait for SE4 event flag, then clear it.
 *
 * EEEE 1101011 CZ0 000010111 000100100
 *
 * WAITSE4          {WC/WZ/WCZ}
 *
 * Prior SETQ sets optional CT timeout value.
 * C/Z = timeout.
 *
 */
void P2Doc::doc_waitse4(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000010111 000100100");
    m_token.insert(mask_match, t_WAITSE4);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Wait for SE4 event flag, then clear it.");
    m_instr.insert(mask_match, "WAITSE4          {WC/WZ/WCZ}");
    descr += "Prior SETQ sets optional CT timeout value.";
    descr += "C/Z = timeout.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Wait for PAT event flag, then clear it.
 *
 * EEEE 1101011 CZ0 000011000 000100100
 *
 * WAITPAT          {WC/WZ/WCZ}
 *
 * Prior SETQ sets optional CT timeout value.
 * C/Z = timeout.
 *
 */
void P2Doc::doc_waitpat(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000011000 000100100");
    m_token.insert(mask_match, t_WAITPAT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Wait for PAT event flag, then clear it.");
    m_instr.insert(mask_match, "WAITPAT          {WC/WZ/WCZ}");
    descr += "Prior SETQ sets optional CT timeout value.";
    descr += "C/Z = timeout.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Wait for FBW event flag, then clear it.
 *
 * EEEE 1101011 CZ0 000011001 000100100
 *
 * WAITFBW          {WC/WZ/WCZ}
 *
 * Prior SETQ sets optional CT timeout value.
 * C/Z = timeout.
 *
 */
void P2Doc::doc_waitfbw(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000011001 000100100");
    m_token.insert(mask_match, t_WAITFBW);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Wait for FBW event flag, then clear it.");
    m_instr.insert(mask_match, "WAITFBW          {WC/WZ/WCZ}");
    descr += "Prior SETQ sets optional CT timeout value.";
    descr += "C/Z = timeout.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Wait for XMT event flag, then clear it.
 *
 * EEEE 1101011 CZ0 000011010 000100100
 *
 * WAITXMT          {WC/WZ/WCZ}
 *
 * Prior SETQ sets optional CT timeout value.
 * C/Z = timeout.
 *
 */
void P2Doc::doc_waitxmt(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000011010 000100100");
    m_token.insert(mask_match, t_WAITXMT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Wait for XMT event flag, then clear it.");
    m_instr.insert(mask_match, "WAITXMT          {WC/WZ/WCZ}");
    descr += "Prior SETQ sets optional CT timeout value.";
    descr += "C/Z = timeout.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Wait for XFI event flag, then clear it.
 *
 * EEEE 1101011 CZ0 000011011 000100100
 *
 * WAITXFI          {WC/WZ/WCZ}
 *
 * Prior SETQ sets optional CT timeout value.
 * C/Z = timeout.
 *
 */
void P2Doc::doc_waitxfi(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000011011 000100100");
    m_token.insert(mask_match, t_WAITXFI);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Wait for XFI event flag, then clear it.");
    m_instr.insert(mask_match, "WAITXFI          {WC/WZ/WCZ}");
    descr += "Prior SETQ sets optional CT timeout value.";
    descr += "C/Z = timeout.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Wait for XRO event flag, then clear it.
 *
 * EEEE 1101011 CZ0 000011100 000100100
 *
 * WAITXRO          {WC/WZ/WCZ}
 *
 * Prior SETQ sets optional CT timeout value.
 * C/Z = timeout.
 *
 */
void P2Doc::doc_waitxro(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000011100 000100100");
    m_token.insert(mask_match, t_WAITXRO);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Wait for XRO event flag, then clear it.");
    m_instr.insert(mask_match, "WAITXRO          {WC/WZ/WCZ}");
    descr += "Prior SETQ sets optional CT timeout value.";
    descr += "C/Z = timeout.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Wait for XRL event flag, then clear it.
 *
 * EEEE 1101011 CZ0 000011101 000100100
 *
 * WAITXRL          {WC/WZ/WCZ}
 *
 * Prior SETQ sets optional CT timeout value.
 * C/Z = timeout.
 *
 */
void P2Doc::doc_waitxrl(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000011101 000100100");
    m_token.insert(mask_match, t_WAITXRL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Wait for XRL event flag, then clear it.");
    m_instr.insert(mask_match, "WAITXRL          {WC/WZ/WCZ}");
    descr += "Prior SETQ sets optional CT timeout value.";
    descr += "C/Z = timeout.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Wait for ATN event flag, then clear it.
 *
 * EEEE 1101011 CZ0 000011110 000100100
 *
 * WAITATN          {WC/WZ/WCZ}
 *
 * Prior SETQ sets optional CT timeout value.
 * C/Z = timeout.
 *
 */
void P2Doc::doc_waitatn(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 000011110 000100100");
    m_token.insert(mask_match, t_WAITATN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Wait for ATN event flag, then clear it.");
    m_instr.insert(mask_match, "WAITATN          {WC/WZ/WCZ}");
    descr += "Prior SETQ sets optional CT timeout value.";
    descr += "C/Z = timeout.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Allow interrupts (default).
 *
 * EEEE 1101011 000 000100000 000100100
 *
 * ALLOWI
 *
 *
 */
void P2Doc::doc_allowi(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 000100000 000100100");
    m_token.insert(mask_match, t_ALLOWI);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Allow interrupts (default).");
    m_instr.insert(mask_match, "ALLOWI");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Stall Interrupts.
 *
 * EEEE 1101011 000 000100001 000100100
 *
 * STALLI
 *
 *
 */
void P2Doc::doc_stalli(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 000100001 000100100");
    m_token.insert(mask_match, t_STALLI);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Stall Interrupts.");
    m_instr.insert(mask_match, "STALLI");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Trigger INT1, regardless of STALLI mode.
 *
 * EEEE 1101011 000 000100010 000100100
 *
 * TRGINT1
 *
 *
 */
void P2Doc::doc_trgint1(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 000100010 000100100");
    m_token.insert(mask_match, t_TRGINT1);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Trigger INT1, regardless of STALLI mode.");
    m_instr.insert(mask_match, "TRGINT1");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Trigger INT2, regardless of STALLI mode.
 *
 * EEEE 1101011 000 000100011 000100100
 *
 * TRGINT2
 *
 *
 */
void P2Doc::doc_trgint2(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 000100011 000100100");
    m_token.insert(mask_match, t_TRGINT2);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Trigger INT2, regardless of STALLI mode.");
    m_instr.insert(mask_match, "TRGINT2");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Trigger INT3, regardless of STALLI mode.
 *
 * EEEE 1101011 000 000100100 000100100
 *
 * TRGINT3
 *
 *
 */
void P2Doc::doc_trgint3(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 000100100 000100100");
    m_token.insert(mask_match, t_TRGINT3);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Trigger INT3, regardless of STALLI mode.");
    m_instr.insert(mask_match, "TRGINT3");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Cancel INT1.
 *
 * EEEE 1101011 000 000100101 000100100
 *
 * NIXINT1
 *
 *
 */
void P2Doc::doc_nixint1(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 000100101 000100100");
    m_token.insert(mask_match, t_NIXINT1);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Cancel INT1.");
    m_instr.insert(mask_match, "NIXINT1");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Cancel INT2.
 *
 * EEEE 1101011 000 000100110 000100100
 *
 * NIXINT2
 *
 *
 */
void P2Doc::doc_nixint2(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 000100110 000100100");
    m_token.insert(mask_match, t_NIXINT2);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Cancel INT2.");
    m_instr.insert(mask_match, "NIXINT2");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Cancel INT3.
 *
 * EEEE 1101011 000 000100111 000100100
 *
 * NIXINT3
 *
 *
 */
void P2Doc::doc_nixint3(p2_opx24_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 000100111 000100100");
    m_token.insert(mask_match, t_NIXINT3);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Cancel INT3.");
    m_instr.insert(mask_match, "NIXINT3");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set INT1 source to D[3:0].
 *
 * EEEE 1101011 00L DDDDDDDDD 000100101
 *
 * SETINT1 {#}D
 *
 *
 */
void P2Doc::doc_setint1(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000100101");
    m_token.insert(mask_match, t_SETINT1);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set INT1 source to D[3:0].");
    m_instr.insert(mask_match, "SETINT1 {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set INT2 source to D[3:0].
 *
 * EEEE 1101011 00L DDDDDDDDD 000100110
 *
 * SETINT2 {#}D
 *
 *
 */
void P2Doc::doc_setint2(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000100110");
    m_token.insert(mask_match, t_SETINT2);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set INT2 source to D[3:0].");
    m_instr.insert(mask_match, "SETINT2 {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set INT3 source to D[3:0].
 *
 * EEEE 1101011 00L DDDDDDDDD 000100111
 *
 * SETINT3 {#}D
 *
 *
 */
void P2Doc::doc_setint3(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000100111");
    m_token.insert(mask_match, t_SETINT3);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set INT3 source to D[3:0].");
    m_instr.insert(mask_match, "SETINT3 {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set Q to D.
 *
 * EEEE 1101011 00L DDDDDDDDD 000101000
 *
 * SETQ    {#}D
 *
 * Use before RDLONG/WRLONG/WMLONG to set block transfer.
 * Also used before MUXQ/COGINIT/QDIV/QFRAC/QROTATE/WAITxxx.
 *
 */
void P2Doc::doc_setq(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000101000");
    m_token.insert(mask_match, t_SETQ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set Q to D.");
    m_instr.insert(mask_match, "SETQ    {#}D");
    descr += "Use before RDLONG/WRLONG/WMLONG to set block transfer.";
    descr += "Also used before MUXQ/COGINIT/QDIV/QFRAC/QROTATE/WAITxxx.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set Q to D.
 *
 * EEEE 1101011 00L DDDDDDDDD 000101001
 *
 * SETQ2   {#}D
 *
 * Use before RDLONG/WRLONG/WMLONG to set LUT block transfer.
 *
 */
void P2Doc::doc_setq2(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000101001");
    m_token.insert(mask_match, t_SETQ2);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set Q to D.");
    m_instr.insert(mask_match, "SETQ2   {#}D");
    descr += "Use before RDLONG/WRLONG/WMLONG to set LUT block transfer.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Push D onto stack.
 *
 * EEEE 1101011 00L DDDDDDDDD 000101010
 *
 * PUSH    {#}D
 *
 *
 */
void P2Doc::doc_push(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000101010");
    m_token.insert(mask_match, t_PUSH);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Push D onto stack.");
    m_instr.insert(mask_match, "PUSH    {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Pop stack (K).
 *
 * EEEE 1101011 CZ0 DDDDDDDDD 000101011
 *
 * POP     D        {WC/WZ/WCZ}
 *
 * C = K[31], Z = K[30], D = K.
 *
 */
void P2Doc::doc_pop(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 DDDDDDDDD 000101011");
    m_token.insert(mask_match, t_POP);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Pop stack (K).");
    m_instr.insert(mask_match, "POP     D        {WC/WZ/WCZ}");
    descr += "C = K[31], Z = K[30], D = K.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to D.
 *
 * EEEE 1101011 CZ0 DDDDDDDDD 000101100
 *
 * JMP     D        {WC/WZ/WCZ}
 *
 * C = D[31], Z = D[30], PC = D[19:0].
 *
 */
void P2Doc::doc_jmp(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 DDDDDDDDD 000101100");
    m_token.insert(mask_match, t_JMP);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to D.");
    m_instr.insert(mask_match, "JMP     D        {WC/WZ/WCZ}");
    descr += "C = D[31], Z = D[30], PC = D[19:0].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Call to D by pushing {C, Z, 10'b0, PC[19:0]} onto stack.
 *
 * EEEE 1101011 CZ0 DDDDDDDDD 000101101
 *
 * CALL    D        {WC/WZ/WCZ}
 *
 * C = D[31], Z = D[30], PC = D[19:0].
 *
 */
void P2Doc::doc_call(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 DDDDDDDDD 000101101");
    m_token.insert(mask_match, t_CALL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Call to D by pushing {C, Z, 10'b0, PC[19:0]} onto stack.");
    m_instr.insert(mask_match, "CALL    D        {WC/WZ/WCZ}");
    descr += "C = D[31], Z = D[30], PC = D[19:0].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Return by popping stack (K).
 *
 * EEEE 1101011 CZ1 000000000 000101101
 *
 * RET              {WC/WZ/WCZ}
 *
 * C = K[31], Z = K[30], PC = K[19:0].
 *
 */
void P2Doc::doc_ret(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ1 000000000 000101101");
    m_token.insert(mask_match, t_RET);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Return by popping stack (K).");
    m_instr.insert(mask_match, "RET              {WC/WZ/WCZ}");
    descr += "C = K[31], Z = K[30], PC = K[19:0].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Call to D by writing {C, Z, 10'b0, PC[19:0]} to hub long at PTRA++.
 *
 * EEEE 1101011 CZ0 DDDDDDDDD 000101110
 *
 * CALLA   D        {WC/WZ/WCZ}
 *
 * C = D[31], Z = D[30], PC = D[19:0].
 *
 */
void P2Doc::doc_calla(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 DDDDDDDDD 000101110");
    m_token.insert(mask_match, t_CALLA);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Call to D by writing {C, Z, 10'b0, PC[19:0]} to hub long at PTRA++.");
    m_instr.insert(mask_match, "CALLA   D        {WC/WZ/WCZ}");
    descr += "C = D[31], Z = D[30], PC = D[19:0].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Return by reading hub long (L) at --PTRA.
 *
 * EEEE 1101011 CZ1 000000000 000101110
 *
 * RETA             {WC/WZ/WCZ}
 *
 * C = L[31], Z = L[30], PC = L[19:0].
 *
 */
void P2Doc::doc_reta(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ1 000000000 000101110");
    m_token.insert(mask_match, t_RETA);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Return by reading hub long (L) at --PTRA.");
    m_instr.insert(mask_match, "RETA             {WC/WZ/WCZ}");
    descr += "C = L[31], Z = L[30], PC = L[19:0].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Call to D by writing {C, Z, 10'b0, PC[19:0]} to hub long at PTRB++.
 *
 * EEEE 1101011 CZ0 DDDDDDDDD 000101111
 *
 * CALLB   D        {WC/WZ/WCZ}
 *
 * C = D[31], Z = D[30], PC = D[19:0].
 *
 */
void P2Doc::doc_callb(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 DDDDDDDDD 000101111");
    m_token.insert(mask_match, t_CALLB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Call to D by writing {C, Z, 10'b0, PC[19:0]} to hub long at PTRB++.");
    m_instr.insert(mask_match, "CALLB   D        {WC/WZ/WCZ}");
    descr += "C = D[31], Z = D[30], PC = D[19:0].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Return by reading hub long (L) at --PTRB.
 *
 * EEEE 1101011 CZ1 000000000 000101111
 *
 * RETB             {WC/WZ/WCZ}
 *
 * C = L[31], Z = L[30], PC = L[19:0].
 *
 */
void P2Doc::doc_retb(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ1 000000000 000101111");
    m_token.insert(mask_match, t_RETB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Return by reading hub long (L) at --PTRB.");
    m_instr.insert(mask_match, "RETB             {WC/WZ/WCZ}");
    descr += "C = L[31], Z = L[30], PC = L[19:0].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump ahead/back by D instructions.
 *
 * EEEE 1101011 00L DDDDDDDDD 000110000
 *
 * JMPREL  {#}D
 *
 * For cogex, PC += D[19:0].
 * For hubex, PC += D[17:0] << 2.
 *
 */
void P2Doc::doc_jmprel(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000110000");
    m_token.insert(mask_match, t_JMPREL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump ahead/back by D instructions.");
    m_instr.insert(mask_match, "JMPREL  {#}D");
    descr += "For cogex, PC += D[19:0].";
    descr += "For hubex, PC += D[17:0] << 2.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Skip instructions per D.
 *
 * EEEE 1101011 00L DDDDDDDDD 000110001
 *
 * SKIP    {#}D
 *
 * Subsequent instructions 0..31 get cancelled for each '1' bit in D[0]..D[31].
 *
 */
void P2Doc::doc_skip(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000110001");
    m_token.insert(mask_match, t_SKIP);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Skip instructions per D.");
    m_instr.insert(mask_match, "SKIP    {#}D");
    descr += "Subsequent instructions 0..31 get cancelled for each '1' bit in D[0]..D[31].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Skip cog/LUT instructions fast per D.
 *
 * EEEE 1101011 00L DDDDDDDDD 000110010
 *
 * SKIPF   {#}D
 *
 * Like SKIP, but instead of cancelling instructions, the PC leaps over them.
 *
 */
void P2Doc::doc_skipf(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000110010");
    m_token.insert(mask_match, t_SKIPF);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Skip cog/LUT instructions fast per D.");
    m_instr.insert(mask_match, "SKIPF   {#}D");
    descr += "Like SKIP, but instead of cancelling instructions, the PC leaps over them.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to D[9:0] in cog/LUT and set SKIPF pattern to D[31:10].
 *
 * EEEE 1101011 00L DDDDDDDDD 000110011
 *
 * EXECF   {#}D
 *
 * PC = {10'b0, D[9:0]}.
 *
 */
void P2Doc::doc_execf(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000110011");
    m_token.insert(mask_match, t_EXECF);
    QList<const char *> descr;
    m_instr.insert(mask_match, "EXECF   {#}D");
    m_brief.insert(mask_match, "Jump to D[9:0] in cog/LUT and set SKIPF pattern to D[31:10].");
    descr += "PC = {10'b0, D[9:0]}.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get current FIFO hub pointer into D.
 *
 * EEEE 1101011 000 DDDDDDDDD 000110100
 *
 * GETPTR  D
 *
 *
 */
void P2Doc::doc_getptr(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 DDDDDDDDD 000110100");
    m_token.insert(mask_match, t_GETPTR);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get current FIFO hub pointer into D.");
    m_instr.insert(mask_match, "GETPTR  D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get breakpoint status into D according to WC/WZ/WCZ.
 *
 * EEEE 1101011 CZ0 DDDDDDDDD 000110101
 *
 * GETBRK  D          WC/WZ/WCZ
 *
 * C = 0.
 * Z = 0.
 *
 */
void P2Doc::doc_getbrk(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 DDDDDDDDD 000110101");
    m_token.insert(mask_match, t_GETBRK);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get breakpoint status into D according to WC/WZ/WCZ.");
    m_instr.insert(mask_match, "GETBRK  D          WC/WZ/WCZ");
    descr += "C = 0.";
    descr += "Z = 0.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief If in debug ISR, trigger asynchronous breakpoint in cog D[3:0].
 *
 * EEEE 1101011 00L DDDDDDDDD 000110101
 *
 * COGBRK  {#}D
 *
 * Cog D[3:0] must have asynchronous breakpoint enabled.
 *
 */
void P2Doc::doc_cogbrk(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000110101");
    m_token.insert(mask_match, t_COGBRK);
    QList<const char *> descr;
    m_brief.insert(mask_match, "If in debug ISR, trigger asynchronous breakpoint in cog D[3:0].");
    m_instr.insert(mask_match, "COGBRK  {#}D");
    descr += "Cog D[3:0] must have asynchronous breakpoint enabled.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief If in debug ISR, set next break condition to D.
 *
 * EEEE 1101011 00L DDDDDDDDD 000110110
 *
 * BRK     {#}D
 *
 * Else, trigger break if enabled, conditionally write break code to D[7:0].
 *
 */
void P2Doc::doc_brk(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000110110");
    m_token.insert(mask_match, t_BRK);
    QList<const char *> descr;
    m_brief.insert(mask_match, "If in debug ISR, set next break condition to D.");
    m_instr.insert(mask_match, "BRK     {#}D");
    descr += "Else, trigger break if enabled, conditionally write break code to D[7:0].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief If D[0] = 1 then enable LUT sharing, where LUT writes within the adjacent odd/even companion cog are copied to this LUT.
 *
 * EEEE 1101011 00L DDDDDDDDD 000110111
 *
 * SETLUTS {#}D
 *
 *
 */
void P2Doc::doc_setluts(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000110111");
    m_token.insert(mask_match, t_SETLUTS);
    QList<const char *> descr;
    m_brief.insert(mask_match, "If D[0] = 1 then enable LUT sharing, where LUT writes within the adjacent odd/even companion cog are copied to this LUT.");
    m_instr.insert(mask_match, "SETLUTS {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set the colorspace converter "CY" parameter to D[31:0].
 *
 * EEEE 1101011 00L DDDDDDDDD 000111000
 *
 * SETCY   {#}D
 *
 *
 */
void P2Doc::doc_setcy(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000111000");
    m_token.insert(mask_match, t_SETCY);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set the colorspace converter \"CY\" parameter to D[31:0].");
    m_instr.insert(mask_match, "SETCY   {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set the colorspace converter "CI" parameter to D[31:0].
 *
 * EEEE 1101011 00L DDDDDDDDD 000111001
 *
 * SETCI   {#}D
 *
 *
 */
void P2Doc::doc_setci(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000111001");
    m_token.insert(mask_match, t_SETCI);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set the colorspace converter \"CI\" parameter to D[31:0].");
    m_instr.insert(mask_match, "SETCI   {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set the colorspace converter "CQ" parameter to D[31:0].
 *
 * EEEE 1101011 00L DDDDDDDDD 000111010
 *
 * SETCQ   {#}D
 *
 *
 */
void P2Doc::doc_setcq(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000111010");
    m_token.insert(mask_match, t_SETCQ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set the colorspace converter \"CQ\" parameter to D[31:0].");
    m_instr.insert(mask_match, "SETCQ   {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set the colorspace converter "CFRQ" parameter to D[31:0].
 *
 * EEEE 1101011 00L DDDDDDDDD 000111011
 *
 * SETCFRQ {#}D
 *
 *
 */
void P2Doc::doc_setcfrq(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000111011");
    m_token.insert(mask_match, t_SETCFRQ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set the colorspace converter \"CFRQ\" parameter to D[31:0].");
    m_instr.insert(mask_match, "SETCFRQ {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set the colorspace converter "CMOD" parameter to D[6:0].
 *
 * EEEE 1101011 00L DDDDDDDDD 000111100
 *
 * SETCMOD {#}D
 *
 *
 */
void P2Doc::doc_setcmod(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000111100");
    m_token.insert(mask_match, t_SETCMOD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set the colorspace converter \"CMOD\" parameter to D[6:0].");
    m_instr.insert(mask_match, "SETCMOD {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set BLNPIX/MIXPIX blend factor to D[7:0].
 *
 * EEEE 1101011 00L DDDDDDDDD 000111101
 *
 * SETPIV  {#}D
 *
 *
 */
void P2Doc::doc_setpiv(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000111101");
    m_token.insert(mask_match, t_SETPIV);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set BLNPIX/MIXPIX blend factor to D[7:0].");
    m_instr.insert(mask_match, "SETPIV  {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set MIXPIX mode to D[5:0].
 *
 * EEEE 1101011 00L DDDDDDDDD 000111110
 *
 * SETPIX  {#}D
 *
 *
 */
void P2Doc::doc_setpix(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000111110");
    m_token.insert(mask_match, t_SETPIX);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set MIXPIX mode to D[5:0].");
    m_instr.insert(mask_match, "SETPIX  {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Strobe "attention" of all cogs whose corresponging bits are high in D[15:0].
 *
 * EEEE 1101011 00L DDDDDDDDD 000111111
 *
 * COGATN  {#}D
 *
 *
 */
void P2Doc::doc_cogatn(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 000111111");
    m_token.insert(mask_match, t_COGATN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Strobe \"attention\" of all cogs whose corresponging bits are high in D[15:0].");
    m_instr.insert(mask_match, "COGATN  {#}D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Test  IN bit of pin D[5:0], write to C/Z.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001000000
 *
 * TESTP   {#}D           WC/WZ
 *
 * C/Z =          IN[D[5:0]].
 *
 */
void P2Doc::doc_testp_w(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001000000");
    m_token.insert(mask_match, t_TESTP);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test  IN bit of pin D[5:0], write to C/Z.");
    m_instr.insert(mask_match, "TESTP   {#}D           WC/WZ");
    descr += "C/Z =          IN[D[5:0]].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Test !IN bit of pin D[5:0], write to C/Z.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001000001
 *
 * TESTPN  {#}D           WC/WZ
 *
 * C/Z =         !IN[D[5:0]].
 *
 */
void P2Doc::doc_testpn_w(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001000001");
    m_token.insert(mask_match, t_TESTPN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test !IN bit of pin D[5:0], write to C/Z.");
    m_instr.insert(mask_match, "TESTPN  {#}D           WC/WZ");
    descr += "C/Z =         !IN[D[5:0]].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Test  IN bit of pin D[5:0], AND into C/Z.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001000010
 *
 * TESTP   {#}D       ANDC/ANDZ
 *
 * C/Z = C/Z AND  IN[D[5:0]].
 *
 */
void P2Doc::doc_testp_and(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001000010");
    m_token.insert(mask_match, t_TESTP);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test  IN bit of pin D[5:0], AND into C/Z.");
    m_instr.insert(mask_match, "TESTP   {#}D       ANDC/ANDZ");
    descr += "C/Z = C/Z AND  IN[D[5:0]].";
    m_descr.insert(mask_match, descr);    // t_AND
}

/**
 * @brief Test !IN bit of pin D[5:0], AND into C/Z.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001000011
 *
 * TESTPN  {#}D       ANDC/ANDZ
 *
 * C/Z = C/Z AND !IN[D[5:0]].
 *
 */
void P2Doc::doc_testpn_and(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001000011");
    m_token.insert(mask_match, t_TESTPN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test !IN bit of pin D[5:0], AND into C/Z.");
    m_instr.insert(mask_match, "TESTPN  {#}D       ANDC/ANDZ");
    descr += "C/Z = C/Z AND !IN[D[5:0]].";
    m_descr.insert(mask_match, descr);   // t_AND
}

/**
 * @brief Test  IN bit of pin D[5:0], OR  into C/Z.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001000100
 *
 * TESTP   {#}D         ORC/ORZ
 *
 * C/Z = C/Z OR   IN[D[5:0]].
 *
 */
void P2Doc::doc_testp_or(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001000100");
    m_token.insert(mask_match, t_TESTP);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test  IN bit of pin D[5:0], OR  into C/Z.");
    m_instr.insert(mask_match, "TESTP   {#}D         ORC/ORZ");
    descr += "C/Z = C/Z OR   IN[D[5:0]].";
    m_descr.insert(mask_match, descr);    // t_OR
}

/**
 * @brief Test !IN bit of pin D[5:0], OR  into C/Z.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001000101
 *
 * TESTPN  {#}D         ORC/ORZ
 *
 * C/Z = C/Z OR  !IN[D[5:0]].
 *
 */
void P2Doc::doc_testpn_or(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001000101");
    m_token.insert(mask_match, t_TESTPN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test !IN bit of pin D[5:0], OR  into C/Z.");
    m_instr.insert(mask_match, "TESTPN  {#}D         ORC/ORZ");
    descr += "C/Z = C/Z OR  !IN[D[5:0]].";
    m_descr.insert(mask_match, descr);   // t_OR
}

/**
 * @brief Test  IN bit of pin D[5:0], XOR into C/Z.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001000110
 *
 * TESTP   {#}D       XORC/XORZ
 *
 * C/Z = C/Z XOR  IN[D[5:0]].
 *
 */
void P2Doc::doc_testp_xor(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001000110");
    m_token.insert(mask_match, t_TESTP);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test  IN bit of pin D[5:0], XOR into C/Z.");
    m_instr.insert(mask_match, "TESTP   {#}D       XORC/XORZ");
    descr += "C/Z = C/Z XOR  IN[D[5:0]].";
    m_descr.insert(mask_match, descr);    // t_XOR
}

/**
 * @brief Test !IN bit of pin D[5:0], XOR into C/Z.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001000111
 *
 * TESTPN  {#}D       XORC/XORZ
 *
 * C/Z = C/Z XOR !IN[D[5:0]].
 *
 */
void P2Doc::doc_testpn_xor(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001000111");
    m_token.insert(mask_match, t_TESTPN);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Test !IN bit of pin D[5:0], XOR into C/Z.");
    m_instr.insert(mask_match, "TESTPN  {#}D       XORC/XORZ");
    descr += "C/Z = C/Z XOR !IN[D[5:0]].";
    m_descr.insert(mask_match, descr);   // t_XOR
}

/**
 * @brief DIR bit of pin D[5:0] = 0.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001000000
 *
 * DIRL    {#}D           {WCZ}
 *
 * C,Z = DIR bit.
 *
 */
void P2Doc::doc_dirl(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001000000");
    m_token.insert(mask_match, t_DIRL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "DIR bit of pin D[5:0] = 0.");
    m_instr.insert(mask_match, "DIRL    {#}D           {WCZ}");
    descr += "C,Z = DIR bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief DIR bit of pin D[5:0] = 1.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001000001
 *
 * DIRH    {#}D           {WCZ}
 *
 * C,Z = DIR bit.
 *
 */
void P2Doc::doc_dirh(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001000001");
    m_token.insert(mask_match, t_DIRH);
    QList<const char *> descr;
    m_brief.insert(mask_match, "DIR bit of pin D[5:0] = 1.");
    m_instr.insert(mask_match, "DIRH    {#}D           {WCZ}");
    descr += "C,Z = DIR bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief DIR bit of pin D[5:0] = C.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001000010
 *
 * DIRC    {#}D           {WCZ}
 *
 * C,Z = DIR bit.
 *
 */
void P2Doc::doc_dirc(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001000010");
    m_token.insert(mask_match, t_DIRC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "DIR bit of pin D[5:0] = C.");
    m_instr.insert(mask_match, "DIRC    {#}D           {WCZ}");
    descr += "C,Z = DIR bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief DIR bit of pin D[5:0] = !C.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001000011
 *
 * DIRNC   {#}D           {WCZ}
 *
 * C,Z = DIR bit.
 *
 */
void P2Doc::doc_dirnc(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001000011");
    m_token.insert(mask_match, t_DIRNC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "DIR bit of pin D[5:0] = !C.");
    m_instr.insert(mask_match, "DIRNC   {#}D           {WCZ}");
    descr += "C,Z = DIR bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief DIR bit of pin D[5:0] = Z.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001000100
 *
 * DIRZ    {#}D           {WCZ}
 *
 * C,Z = DIR bit.
 *
 */
void P2Doc::doc_dirz(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001000100");
    m_token.insert(mask_match, t_DIRZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "DIR bit of pin D[5:0] = Z.");
    m_instr.insert(mask_match, "DIRZ    {#}D           {WCZ}");
    descr += "C,Z = DIR bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief DIR bit of pin D[5:0] = !Z.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001000101
 *
 * DIRNZ   {#}D           {WCZ}
 *
 * C,Z = DIR bit.
 *
 */
void P2Doc::doc_dirnz(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001000101");
    m_token.insert(mask_match, t_DIRNZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "DIR bit of pin D[5:0] = !Z.");
    m_instr.insert(mask_match, "DIRNZ   {#}D           {WCZ}");
    descr += "C,Z = DIR bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief DIR bit of pin D[5:0] = RND.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001000110
 *
 * DIRRND  {#}D           {WCZ}
 *
 * C,Z = DIR bit.
 *
 */
void P2Doc::doc_dirrnd(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001000110");
    m_token.insert(mask_match, t_DIRRND);
    QList<const char *> descr;
    m_brief.insert(mask_match, "DIR bit of pin D[5:0] = RND.");
    m_instr.insert(mask_match, "DIRRND  {#}D           {WCZ}");
    descr += "C,Z = DIR bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief DIR bit of pin D[5:0] = !bit.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001000111
 *
 * DIRNOT  {#}D           {WCZ}
 *
 * C,Z = DIR bit.
 *
 */
void P2Doc::doc_dirnot(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001000111");
    m_token.insert(mask_match, t_DIRNOT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "DIR bit of pin D[5:0] = !bit.");
    m_instr.insert(mask_match, "DIRNOT  {#}D           {WCZ}");
    descr += "C,Z = DIR bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = 0.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001001000
 *
 * OUTL    {#}D           {WCZ}
 *
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_outl(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001001000");
    m_token.insert(mask_match, t_OUTL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = 0.");
    m_instr.insert(mask_match, "OUTL    {#}D           {WCZ}");
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = 1.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001001001
 *
 * OUTH    {#}D           {WCZ}
 *
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_outh(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001001001");
    m_token.insert(mask_match, t_OUTH);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = 1.");
    m_instr.insert(mask_match, "OUTH    {#}D           {WCZ}");
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = C.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001001010
 *
 * OUTC    {#}D           {WCZ}
 *
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_outc(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001001010");
    m_token.insert(mask_match, t_OUTC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = C.");
    m_instr.insert(mask_match, "OUTC    {#}D           {WCZ}");
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = !C.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001001011
 *
 * OUTNC   {#}D           {WCZ}
 *
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_outnc(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001001011");
    m_token.insert(mask_match, t_OUTNC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = !C.");
    m_instr.insert(mask_match, "OUTNC   {#}D           {WCZ}");
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = Z.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001001100
 *
 * OUTZ    {#}D           {WCZ}
 *
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_outz(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001001100");
    m_token.insert(mask_match, t_OUTZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = Z.");
    m_instr.insert(mask_match, "OUTZ    {#}D           {WCZ}");
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = !Z.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001001101
 *
 * OUTNZ   {#}D           {WCZ}
 *
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_outnz(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001001101");
    m_token.insert(mask_match, t_OUTNZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = !Z.");
    m_instr.insert(mask_match, "OUTNZ   {#}D           {WCZ}");
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = RND.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001001110
 *
 * OUTRND  {#}D           {WCZ}
 *
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_outrnd(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001001110");
    m_token.insert(mask_match, t_OUTRND);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = RND.");
    m_instr.insert(mask_match, "OUTRND  {#}D           {WCZ}");
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = !bit.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001001111
 *
 * OUTNOT  {#}D           {WCZ}
 *
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_outnot(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001001111");
    m_token.insert(mask_match, t_OUTNOT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = !bit.");
    m_instr.insert(mask_match, "OUTNOT  {#}D           {WCZ}");
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = 0.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001010000
 *
 * FLTL    {#}D           {WCZ}
 *
 * DIR bit = 0.
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_fltl(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001010000");
    m_token.insert(mask_match, t_FLTL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = 0.");
    m_instr.insert(mask_match, "FLTL    {#}D           {WCZ}");
    descr += "DIR bit = 0.";
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = 1.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001010001
 *
 * FLTH    {#}D           {WCZ}
 *
 * DIR bit = 0.
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_flth(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001010001");
    m_token.insert(mask_match, t_FLTH);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = 1.");
    m_instr.insert(mask_match, "FLTH    {#}D           {WCZ}");
    descr += "DIR bit = 0.";
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = C.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001010010
 *
 * FLTC    {#}D           {WCZ}
 *
 * DIR bit = 0.
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_fltc(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001010010");
    m_token.insert(mask_match, t_FLTC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = C.");
    m_instr.insert(mask_match, "FLTC    {#}D           {WCZ}");
    descr += "DIR bit = 0.";
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = !C.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001010011
 *
 * FLTNC   {#}D           {WCZ}
 *
 * DIR bit = 0.
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_fltnc(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001010011");
    m_token.insert(mask_match, t_FLTNC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = !C.");
    m_instr.insert(mask_match, "FLTNC   {#}D           {WCZ}");
    descr += "DIR bit = 0.";
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = Z.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001010100
 *
 * FLTZ    {#}D           {WCZ}
 *
 * DIR bit = 0.
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_fltz(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001010100");
    m_token.insert(mask_match, t_FLTZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = Z.");
    m_instr.insert(mask_match, "FLTZ    {#}D           {WCZ}");
    descr += "DIR bit = 0.";
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = !Z.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001010101
 *
 * FLTNZ   {#}D           {WCZ}
 *
 * DIR bit = 0.
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_fltnz(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001010101");
    m_token.insert(mask_match, t_FLTNZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = !Z.");
    m_instr.insert(mask_match, "FLTNZ   {#}D           {WCZ}");
    descr += "DIR bit = 0.";
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = RND.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001010110
 *
 * FLTRND  {#}D           {WCZ}
 *
 * DIR bit = 0.
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_fltrnd(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001010110");
    m_token.insert(mask_match, t_FLTRND);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = RND.");
    m_instr.insert(mask_match, "FLTRND  {#}D           {WCZ}");
    descr += "DIR bit = 0.";
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = !bit.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001010111
 *
 * FLTNOT  {#}D           {WCZ}
 *
 * DIR bit = 0.
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_fltnot(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001010111");
    m_token.insert(mask_match, t_FLTNOT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = !bit.");
    m_instr.insert(mask_match, "FLTNOT  {#}D           {WCZ}");
    descr += "DIR bit = 0.";
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = 0.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001011000
 *
 * DRVL    {#}D           {WCZ}
 *
 * DIR bit = 1.
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_drvl(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001011000");
    m_token.insert(mask_match, t_DRVL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = 0.");
    m_instr.insert(mask_match, "DRVL    {#}D           {WCZ}");
    descr += "DIR bit = 1.";
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = 1.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001011001
 *
 * DRVH    {#}D           {WCZ}
 *
 * DIR bit = 1.
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_drvh(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001011001");
    m_token.insert(mask_match, t_DRVH);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = 1.");
    m_instr.insert(mask_match, "DRVH    {#}D           {WCZ}");
    descr += "DIR bit = 1.";
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = C.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001011010
 *
 * DRVC    {#}D           {WCZ}
 *
 * DIR bit = 1.
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_drvc(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001011010");
    m_token.insert(mask_match, t_DRVC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = C.");
    m_instr.insert(mask_match, "DRVC    {#}D           {WCZ}");
    descr += "DIR bit = 1.";
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = !C.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001011011
 *
 * DRVNC   {#}D           {WCZ}
 *
 * DIR bit = 1.
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_drvnc(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001011011");
    m_token.insert(mask_match, t_DRVNC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = !C.");
    m_instr.insert(mask_match, "DRVNC   {#}D           {WCZ}");
    descr += "DIR bit = 1.";
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = Z.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001011100
 *
 * DRVZ    {#}D           {WCZ}
 *
 * DIR bit = 1.
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_drvz(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001011100");
    m_token.insert(mask_match, t_DRVZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = Z.");
    m_instr.insert(mask_match, "DRVZ    {#}D           {WCZ}");
    descr += "DIR bit = 1.";
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = !Z.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001011101
 *
 * DRVNZ   {#}D           {WCZ}
 *
 * DIR bit = 1.
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_drvnz(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001011101");
    m_token.insert(mask_match, t_DRVNZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = !Z.");
    m_instr.insert(mask_match, "DRVNZ   {#}D           {WCZ}");
    descr += "DIR bit = 1.";
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = RND.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001011110
 *
 * DRVRND  {#}D           {WCZ}
 *
 * DIR bit = 1.
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_drvrnd(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001011110");
    m_token.insert(mask_match, t_DRVRND);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = RND.");
    m_instr.insert(mask_match, "DRVRND  {#}D           {WCZ}");
    descr += "DIR bit = 1.";
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief OUT bit of pin D[5:0] = !bit.
 *
 * EEEE 1101011 CZL DDDDDDDDD 001011111
 *
 * DRVNOT  {#}D           {WCZ}
 *
 * DIR bit = 1.
 * C,Z = OUT bit.
 *
 */
void P2Doc::doc_drvnot(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZL DDDDDDDDD 001011111");
    m_token.insert(mask_match, t_DRVNOT);
    QList<const char *> descr;
    m_brief.insert(mask_match, "OUT bit of pin D[5:0] = !bit.");
    m_instr.insert(mask_match, "DRVNOT  {#}D           {WCZ}");
    descr += "DIR bit = 1.";
    descr += "C,Z = OUT bit.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Split every 4th bit of S into bytes of D.
 *
 * EEEE 1101011 000 DDDDDDDDD 001100000
 *
 * SPLITB  D
 *
 * D = {S[31], S[27], S[23], S[19], ... S[12], S[8], S[4], S[0]}.
 *
 */
void P2Doc::doc_splitb(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 DDDDDDDDD 001100000");
    m_token.insert(mask_match, t_SPLITB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Split every 4th bit of S into bytes of D.");
    m_instr.insert(mask_match, "SPLITB  D");
    descr += "D = {S[31], S[27], S[23], S[19], ... S[12], S[8], S[4], S[0]}.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Merge bits of bytes in S into D.
 *
 * EEEE 1101011 000 DDDDDDDDD 001100001
 *
 * MERGEB  D
 *
 * D = {S[31], S[23], S[15], S[7], ... S[24], S[16], S[8], S[0]}.
 *
 */
void P2Doc::doc_mergeb(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 DDDDDDDDD 001100001");
    m_token.insert(mask_match, t_MERGEB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Merge bits of bytes in S into D.");
    m_instr.insert(mask_match, "MERGEB  D");
    descr += "D = {S[31], S[23], S[15], S[7], ... S[24], S[16], S[8], S[0]}.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Split bits of S into words of D.
 *
 * EEEE 1101011 000 DDDDDDDDD 001100010
 *
 * SPLITW  D
 *
 * D = {S[31], S[29], S[27], S[25], ... S[6], S[4], S[2], S[0]}.
 *
 */
void P2Doc::doc_splitw(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 DDDDDDDDD 001100010");
    m_token.insert(mask_match, t_SPLITW);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Split bits of S into words of D.");
    m_instr.insert(mask_match, "SPLITW  D");
    descr += "D = {S[31], S[29], S[27], S[25], ... S[6], S[4], S[2], S[0]}.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Merge bits of words in S into D.
 *
 * EEEE 1101011 000 DDDDDDDDD 001100011
 *
 * MERGEW  D
 *
 * D = {S[31], S[15], S[30], S[14], ... S[17], S[1], S[16], S[0]}.
 *
 */
void P2Doc::doc_mergew(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 DDDDDDDDD 001100011");
    m_token.insert(mask_match, t_MERGEW);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Merge bits of words in S into D.");
    m_instr.insert(mask_match, "MERGEW  D");
    descr += "D = {S[31], S[15], S[30], S[14], ... S[17], S[1], S[16], S[0]}.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Relocate and periodically invert bits from S into D.
 *
 * EEEE 1101011 000 DDDDDDDDD 001100100
 *
 * SEUSSF  D
 *
 * Returns to original value on 32nd iteration.
 * Forward pattern.
 */
void P2Doc::doc_seussf(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 DDDDDDDDD 001100100");
    m_token.insert(mask_match, t_SEUSSF);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Relocate and periodically invert bits from S into D.");
    descr += "Returns to original value on 32nd iteration.";
    descr += "Forward pattern.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Relocate and periodically invert bits from S into D.
 *
 * EEEE 1101011 000 DDDDDDDDD 001100101
 *
 * SEUSSR  D
 *
 * Returns to original value on 32nd iteration.
 * Reverse pattern.
 */
void P2Doc::doc_seussr(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 DDDDDDDDD 001100101");
    m_token.insert(mask_match, t_SEUSSR);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Relocate and periodically invert bits from S into D.");
    descr += "Returns to original value on 32nd iteration.";
    descr += "Reverse pattern.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Squeeze 8:8:8 RGB value in S[31:8] into 5:6:5 value in D[15:0].
 *
 * EEEE 1101011 000 DDDDDDDDD 001100110
 *
 * RGBSQZ  D
 *
 * D = {15'b0, S[31:27], S[23:18], S[15:11]}.
 *
 */
void P2Doc::doc_rgbsqz(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 DDDDDDDDD 001100110");
    m_token.insert(mask_match, t_RGBSQZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Squeeze 8:8:8 RGB value in S[31:8] into 5:6:5 value in D[15:0].");
    m_instr.insert(mask_match, "RGBSQZ  D");
    descr += "D = {15'b0, S[31:27], S[23:18], S[15:11]}.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Expand 5:6:5 RGB value in S[15:0] into 8:8:8 value in D[31:8].
 *
 * EEEE 1101011 000 DDDDDDDDD 001100111
 *
 * RGBEXP  D
 *
 * D = {S[15:11,15:13], S[10:5,10:9], S[4:0,4:2], 8'b0}.
 *
 */
void P2Doc::doc_rgbexp(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 DDDDDDDDD 001100111");
    m_token.insert(mask_match, t_RGBEXP);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Expand 5:6:5 RGB value in S[15:0] into 8:8:8 value in D[31:8].");
    m_instr.insert(mask_match, "RGBEXP  D");
    descr += "D = {S[15:11,15:13], S[10:5,10:9], S[4:0,4:2], 8'b0}.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Iterate D with xoroshiro32+ PRNG algorithm and put PRNG result into next instruction's S.
 *
 * EEEE 1101011 000 DDDDDDDDD 001101000
 *
 * XORO32  D
 *
 *
 */
void P2Doc::doc_xoro32(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 DDDDDDDDD 001101000");
    m_token.insert(mask_match, t_XORO32);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Iterate D with xoroshiro32+ PRNG algorithm and put PRNG result into next instruction's S.");
    m_instr.insert(mask_match, "XORO32  D");
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Reverse D bits.
 *
 * EEEE 1101011 000 DDDDDDDDD 001101001
 *
 * REV     D
 *
 * D = D[0:31].
 *
 */
void P2Doc::doc_rev(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 DDDDDDDDD 001101001");
    m_token.insert(mask_match, t_REV);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Reverse D bits.");
    m_instr.insert(mask_match, "REV     D");
    descr += "D = D[0:31].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Rotate C,Z right through D.
 *
 * EEEE 1101011 CZ0 DDDDDDDDD 001101010
 *
 * RCZR    D        {WC/WZ/WCZ}
 *
 * D = {C, Z, D[31:2]}.
 * C = D[1],  Z = D[0].
 *
 */
void P2Doc::doc_rczr(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 DDDDDDDDD 001101010");
    m_token.insert(mask_match, t_RCZR);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Rotate C,Z right through D.");
    m_instr.insert(mask_match, "RCZR    D        {WC/WZ/WCZ}");
    descr += "D = {C, Z, D[31:2]}.";
    descr += "C = D[1],  Z = D[0].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Rotate C,Z left through D.
 *
 * EEEE 1101011 CZ0 DDDDDDDDD 001101011
 *
 * RCZL    D        {WC/WZ/WCZ}
 *
 * D = {D[29:0], C, Z}.
 * C = D[31], Z = D[30].
 *
 */
void P2Doc::doc_rczl(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ0 DDDDDDDDD 001101011");
    m_token.insert(mask_match, t_RCZL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Rotate C,Z left through D.");
    m_instr.insert(mask_match, "RCZL    D        {WC/WZ/WCZ}");
    descr += "D = {D[29:0], C, Z}.";
    descr += "C = D[31], Z = D[30].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Write 0 or 1 to D, according to  C.
 *
 * EEEE 1101011 000 DDDDDDDDD 001101100
 *
 * WRC     D
 *
 * D = {31'b0,  C}.
 *
 */
void P2Doc::doc_wrc(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 DDDDDDDDD 001101100");
    m_token.insert(mask_match, t_WRC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Write 0 or 1 to D, according to  C.");
    m_instr.insert(mask_match, "WRC     D");
    descr += "D = {31'b0,  C}.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Write 0 or 1 to D, according to !C.
 *
 * EEEE 1101011 000 DDDDDDDDD 001101101
 *
 * WRNC    D
 *
 * D = {31'b0, !C}.
 *
 */
void P2Doc::doc_wrnc(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 DDDDDDDDD 001101101");
    m_token.insert(mask_match, t_WRNC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Write 0 or 1 to D, according to !C.");
    m_instr.insert(mask_match, "WRNC    D");
    descr += "D = {31'b0, !C}.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Write 0 or 1 to D, according to  Z.
 *
 * EEEE 1101011 000 DDDDDDDDD 001101110
 *
 * WRZ     D
 *
 * D = {31'b0,  Z}.
 *
 */
void P2Doc::doc_wrz(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 DDDDDDDDD 001101110");
    m_token.insert(mask_match, t_WRZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Write 0 or 1 to D, according to  Z.");
    m_instr.insert(mask_match, "WRZ     D");
    descr += "D = {31'b0,  Z}.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Write 0 or 1 to D, according to !Z.
 *
 * EEEE 1101011 000 DDDDDDDDD 001101111
 *
 * WRNZ    D
 *
 * D = {31'b0, !Z}.
 *
 */
void P2Doc::doc_wrnz(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 DDDDDDDDD 001101111");
    m_token.insert(mask_match, t_WRNZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Write 0 or 1 to D, according to !Z.");
    m_instr.insert(mask_match, "WRNZ    D");
    descr += "D = {31'b0, !Z}.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Modify C and Z according to cccc and zzzz.
 *
 * EEEE 1101011 CZ1 0cccczzzz 001101111
 *
 * MODCZ   c,z      {WC/WZ/WCZ}
 *
 * C = cccc[{C,Z}], Z = zzzz[{C,Z}].
 *
 */
void P2Doc::doc_modcz(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 CZ1 0cccczzzz 001101111");
    m_token.insert(mask_match, t_MODCZ);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Modify C and Z according to cccc and zzzz.");
    m_instr.insert(mask_match, "MODCZ   c,z      {WC/WZ/WCZ}");
    descr += "C = cccc[{C,Z}], Z = zzzz[{C,Z}].";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Set scope mode.
 *
 * EEEE 1101011 00L DDDDDDDDD 001110000
 *
 * SETSCP  {#}D
 *
 * Pins D[5:2], enable D[6].
 *
 * SETSCP points the scope mux to a set of four pins starting
 * at (D[5:0] AND $3C), with D[6]=1 to enable scope operation.
 *
 */
void P2Doc::doc_setscp(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 00L DDDDDDDDD 001110000");
    m_token.insert(mask_match, t_SETSCP);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Set scope mode.");
    m_instr.insert(mask_match, "SETSCP  {#}D");
    descr += "Pins D[5:2], enable D[6].";
    descr += "SETSCP points the scope mux to a set of four pins starting";
    descr += "at (D[5:0] AND $3C), with D[6]=1 to enable scope operation.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Get scope values.
 *
 * EEEE 1101011 000 DDDDDDDDD 001110001
 *
 * GETSCP  D
 *
 * Any time GETSCP is executed, the lower bytes of those four pins' RDPIN values are returned in D.
 * This feature will mainly be useful on the next silicon, as the FPGAs don't have ADC-capable pins.
 */
void P2Doc::doc_getscp(p2_opsrc_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101011 000 DDDDDDDDD 001110001");
    m_token.insert(mask_match, t_GETSCP);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get four scope values into bytes of D.");
    m_instr.insert(mask_match, "GETSCP  D");
    descr += "Any time GETSCP is executed, the lower bytes of those";
    descr += "four pins' RDPIN values are returned in D.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Jump to A.
 *
 * EEEE 1101100 RAA AAAAAAAAA AAAAAAAAA
 *
 * JMP     #A
 *
 * If R = 1, PC += A, else PC = A.
 *
 */
void P2Doc::doc_jmp_abs(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101100 RAA AAAAAAAAA AAAAAAAAA");
    m_token.insert(mask_match, t_JMP);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Jump to A.");
    m_instr.insert(mask_match, "JMP     #A");
    descr += "If R = 1, PC += A, else PC = A.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Call to A by pushing {C, Z, 10'b0, PC[19:0]} onto stack.
 *
 * EEEE 1101101 RAA AAAAAAAAA AAAAAAAAA
 *
 * CALL    #A
 *
 * If R = 1, PC += A, else PC = A.
 *
 */
void P2Doc::doc_call_abs(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101101 RAA AAAAAAAAA AAAAAAAAA");
    m_token.insert(mask_match, t_CALL);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Call to A by pushing {C, Z, 10'b0, PC[19:0]} onto stack.");
    m_instr.insert(mask_match, "CALL    #A");
    descr += "If R = 1, PC += A, else PC = A.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Call to A by writing {C, Z, 10'b0, PC[19:0]} to hub long at PTRA++.
 *
 * EEEE 1101110 RAA AAAAAAAAA AAAAAAAAA
 *
 * CALLA   #A
 *
 * If R = 1, PC += A, else PC = A.
 *
 */
void P2Doc::doc_calla_abs(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101110 RAA AAAAAAAAA AAAAAAAAA");
    m_token.insert(mask_match, t_CALLA);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Call to A by writing {C, Z, 10'b0, PC[19:0]} to hub long at PTRA++.");
    m_instr.insert(mask_match, "CALLA   #A");
    descr += "If R = 1, PC += A, else PC = A.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Call to A by writing {C, Z, 10'b0, PC[19:0]} to hub long at PTRB++.
 *
 * EEEE 1101111 RAA AAAAAAAAA AAAAAAAAA
 *
 * CALLB   #A
 *
 * If R = 1, PC += A, else PC = A.
 *
 */
void P2Doc::doc_callb_abs(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1101111 RAA AAAAAAAAA AAAAAAAAA");
    m_token.insert(mask_match, t_CALLB);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Call to A by writing {C, Z, 10'b0, PC[19:0]} to hub long at PTRB++.");
    m_instr.insert(mask_match, "CALLB   #A");
    descr += "If R = 1, PC += A, else PC = A.";
    m_descr.insert(mask_match, descr);
}

/**
 * @brief Call to A by writing {C, Z, 10'b0, PC[19:0]} to PA/PB/PTRA/PTRB (per W).
 *
 * EEEE 1110000 RAA AAAAAAAAA AAAAAAAAA
 *
 * CALLD   PA,#A
 *
 * If R = 1, PC += A, else PC = A.
 *
 */
void P2Doc::doc_calld_pa_abs(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1110000 RAA AAAAAAAAA AAAAAAAAA");
    m_token.insert(mask_match, t_CALLD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Call to A by writing {C, Z, 10'b0, PC[19:0]} to PA (per W).");
    m_instr.insert(mask_match, "CALLD   PA,#A");
    descr += "If R = 1, PC += A, else PC = A.";
    m_descr.insert(mask_match, descr);    // t_PA
}

/**
 * @brief Call to A by writing {C, Z, 10'b0, PC[19:0]} to PA/PB/PTRA/PTRB (per W).
 *
 * EEEE 1110001 RAA AAAAAAAAA AAAAAAAAA
 *
 * CALLD   PB,#A
 *
 * If R = 1, PC += A, else PC = A.
 *
 */
void P2Doc::doc_calld_pb_abs(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1110001 RAA AAAAAAAAA AAAAAAAAA");
    m_token.insert(mask_match, t_CALLD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Call to A by writing {C, Z, 10'b0, PC[19:0]} to PB (per W).");
    m_instr.insert(mask_match, "CALLD   PB,#A");
    descr += "If R = 1, PC += A, else PC = A.";
    m_descr.insert(mask_match, descr);    // t_PB
}

/**
 * @brief Call to A by writing {C, Z, 10'b0, PC[19:0]} to PTRA (per W).
 *
 * EEEE 1110010 RAA AAAAAAAAA AAAAAAAAA
 *
 * CALLD   PTRA,#A
 *
 * If R = 1, PC += A, else PC = A.
 *
 */
void P2Doc::doc_calld_ptra_abs(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1110010 RAA AAAAAAAAA AAAAAAAAA");
    m_token.insert(mask_match, t_CALLD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Call to A by writing {C, Z, 10'b0, PC[19:0]} to PTRA (per W).");
    m_instr.insert(mask_match, "CALLD   PTRA,#A");
    descr += "If R = 1, PC += A, else PC = A.";
    m_descr.insert(mask_match, descr);    // t_PTRA
}

/**
 * @brief Call to A by writing {C, Z, 10'b0, PC[19:0]} to PTRB (per W).
 *
 * EEEE 1110011 RAA AAAAAAAAA AAAAAAAAA
 *
 * CALLD   PTRB,#A
 *
 * If R = 1, PC += A, else PC = A.
 *
 */
void P2Doc::doc_calld_ptrb_abs(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1110011 RAA AAAAAAAAA AAAAAAAAA");
    m_token.insert(mask_match, t_CALLD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Call to A by writing {C, Z, 10'b0, PC[19:0]} to PTRB (per W).");
    m_instr.insert(mask_match, "CALLD   PTRB,#A");
    descr += "If R = 1, PC += A, else PC = A.";
    m_descr.insert(mask_match, descr);    // t_PTRB
}

/**
 * @brief Get {12'b0, address[19:0]} into PA/PB/PTRA/PTRB (per W).
 *
 * EEEE 11101WW RAA AAAAAAAAA AAAAAAAAA
 *
 * LOC     PA/PB/PTRA/PTRB,#A
 *
 * If R = 1, address = PC + A, else address = A.
 *
 */
void P2Doc::doc_loc_pa(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1110100 RAA AAAAAAAAA AAAAAAAAA");
    m_token.insert(mask_match, t_LOC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get {12'b0, address[19:0]} into PA/PB/PTRA/PTRB (per W).");
    m_instr.insert(mask_match, "LOC     PA/PB/PTRA/PTRB,#A");
    descr += "If R = 1, address = PC + A, else address = A.";
    m_descr.insert(mask_match, descr);  // t_PA
}

/**
 * @brief Get {12'b0, address[19:0]} into PA/PB/PTRA/PTRB (per W).
 *
 * EEEE 11101WW RAA AAAAAAAAA AAAAAAAAA
 *
 * LOC     PA/PB/PTRA/PTRB,#A
 *
 * If R = 1, address = PC + A, else address = A.
 *
 */
void P2Doc::doc_loc_pb(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1110101 RAA AAAAAAAAA AAAAAAAAA");
    m_token.insert(mask_match, t_LOC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get {12'b0, address[19:0]} into PA/PB/PTRA/PTRB (per W).");
    m_instr.insert(mask_match, "LOC     PA/PB/PTRA/PTRB,#A");
    descr += "If R = 1, address = PC + A, else address = A.";
    m_descr.insert(mask_match, descr);  // t_PB
}

/**
 * @brief Get {12'b0, address[19:0]} into PA/PB/PTRA/PTRB (per W).
 *
 * EEEE 11101WW RAA AAAAAAAAA AAAAAAAAA
 *
 * LOC     PA/PB/PTRA/PTRB,#A
 *
 * If R = 1, address = PC + A, else address = A.
 *
 */
void P2Doc::doc_loc_ptra(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1110110 RAA AAAAAAAAA AAAAAAAAA");
    m_token.insert(mask_match, t_LOC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get {12'b0, address[19:0]} into PA/PB/PTRA/PTRB (per W).");
    m_instr.insert(mask_match, "LOC     PA/PB/PTRA/PTRB,#A");
    descr += "If R = 1, address = PC + A, else address = A.";
    m_descr.insert(mask_match, descr);  // t_PTRA
}

/**
 * @brief Get {12'b0, address[19:0]} into PA/PB/PTRA/PTRB (per W).
 *
 * EEEE 11101WW RAA AAAAAAAAA AAAAAAAAA
 *
 * LOC     PA/PB/PTRA/PTRB,#A
 *
 * If R = 1, address = PC + A, else address = A.
 *
 */
void P2Doc::doc_loc_ptrb(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 1110111 RAA AAAAAAAAA AAAAAAAAA");
    m_token.insert(mask_match, t_LOC);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Get {12'b0, address[19:0]} into PA/PB/PTRA/PTRB (per W).");
    m_instr.insert(mask_match, "LOC     PA/PB/PTRA/PTRB,#A");
    descr += "If R = 1, address = PC + A, else address = A.";
    m_descr.insert(mask_match, descr);  // t_PTRB
}

/**
 * @brief Queue #N[31:9] to be used as upper 23 bits for next #S occurrence, so that the next 9-bit #S will be augmented to 32 bits.
 *
 * EEEE 11110NN NNN NNNNNNNNN NNNNNNNNN
 *
 * AUGS    #N
 *
 *
 */
void P2Doc::doc_augs(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 11110NN SSS SSSSSSSSS SSSSSSSSS");
    m_token.insert(mask_match, t_AUGS);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Queue #N[31:9] to be used as upper 23 bits for next #S occurrence, so that the next 9-bit #S will be augmented to 32 bits.");
    m_instr.insert(mask_match, "AUGS    #N");
}

/**
 * @brief Queue #N[31:9] to be used as upper 23 bits for next #D occurrence, so that the next 9-bit #D will be augmented to 32 bits.
 *
 * EEEE 11111NN NNN NNNNNNNNN NNNNNNNNN
 *
 * AUGD    #N
 *
 *
 */
void P2Doc::doc_augd(p2_inst7_e instr)
{
    MaskMatch mask_match = pattern(__func__, instr, "EEEE 11111NN DDD DDDDDDDDD DDDDDDDDD");
    m_token.insert(mask_match, t_AUGD);
    QList<const char *> descr;
    m_brief.insert(mask_match, "Queue #N[31:9] to be used as upper 23 bits for next #D occurrence, so that the next 9-bit #D will be augmented to 32 bits.");
    m_instr.insert(mask_match, "AUGD    #N");
}
