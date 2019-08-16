/****************************************************************************
 *
 * Propeller2 token (instruction mnemonics) to QString function
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
#include <QString>
#include <QMap>
#include "p2defs.h"

/**
 * @brief enumeration of tokens used in mnemonics for the P2 assembler and disassembler
 */
typedef enum {
    t_invalid,
    t_nothing,
    t_empty,
    t_ABS,
    t_ADD,
    t_ADDCT1,
    t_ADDCT2,
    t_ADDCT3,
    t_ADDPIX,
    t_ADDS,
    t_ADDSX,
    t_ADDX,
    t_AKPIN,
    t_ALLOWI,
    t_ALTB,
    t_ALTD,
    t_ALTGB,
    t_ALTGN,
    t_ALTGW,
    t_ALTI,
    t_ALTR,
    t_ALTS,
    t_ALTSB,
    t_ALTSN,
    t_ALTSW,
    t_AND,
    t_ANDN,
    t_AUGD,
    t_AUGS,
    t_BITC,
    t_BITH,
    t_BITL,
    t_BITNC,
    t_BITNOT,
    t_BITNZ,
    t_BITRND,
    t_BITZ,
    t_BLNPIX,
    t_BMASK,
    t_BRK,
    t_C,
    t_CALL,
    t_CALLA,
    t_CALLB,
    t_CALLD,
    t_CALLPA,
    t_CALLPB,
    t_CMP,
    t_CMPM,
    t_CMPR,
    t_CMPS,
    t_CMPSUB,
    t_CMPSX,
    t_CMPX,
    t_COGATN,
    t_COGBRK,
    t_COGID,
    t_COGINIT,
    t_COGSTOP,
    t_CRCBIT,
    t_CRCNIB,
    t_CZ,
    t_DECMOD,
    t_DECOD,
    t_DIRC,
    t_DIRH,
    t_DIRL,
    t_DIRNC,
    t_DIRNOT,
    t_DIRNZ,
    t_DIRRND,
    t_DIRZ,
    t_DJF,
    t_DJNF,
    t_DJNZ,
    t_DJZ,
    t_DRVC,
    t_DRVH,
    t_DRVL,
    t_DRVNC,
    t_DRVNOT,
    t_DRVNZ,
    t_DRVRND,
    t_DRVZ,
    t_ENCOD,
    t_EXECF,
    t_FBLOCK,
    t_FGE,
    t_FGES,
    t_FLE,
    t_FLES,
    t_FLTC,
    t_FLTH,
    t_FLTL,
    t_FLTNC,
    t_FLTNOT,
    t_FLTNZ,
    t_FLTRND,
    t_FLTZ,
    t_GETBRK,
    t_GETBYTE,
    t_GETCT,
    t_GETNIB,
    t_GETPTR,
    t_GETQX,
    t_GETQY,
    t_GETRND,
    t_GETSCP,
    t_GETWORD,
    t_GETXACC,
    t_HUBSET,
    t_IF_C,
    t_IF_C_AND_NZ,
    t_IF_C_AND_Z,
    t_IF_C_EQ_Z,
    t_IF_C_NE_Z,
    t_IF_C_OR_NZ,
    t_IF_C_OR_Z,
    t_IF_NC,
    t_IF_NC_AND_NZ,
    t_IF_NC_AND_Z,
    t_IF_NC_OR_NZ,
    t_IF_NC_OR_Z,
    t_IF_NZ,
    t_IF_Z,
    t_IJNZ,
    t_IJZ,
    t_INCMOD,
    t_JATN,
    t_JCT1,
    t_JCT2,
    t_JCT3,
    t_JFBW,
    t_JINT,
    t_JMP,
    t_JMPREL,
    t_JNATN,
    t_JNCT1,
    t_JNCT2,
    t_JNCT3,
    t_JNFBW,
    t_JNINT,
    t_JNPAT,
    t_JNQMT,
    t_JNSE1,
    t_JNSE2,
    t_JNSE3,
    t_JNSE4,
    t_JNXFI,
    t_JNXMT,
    t_JNXRL,
    t_JNXRO,
    t_JPAT,
    t_JQMT,
    t_JSE1,
    t_JSE2,
    t_JSE3,
    t_JSE4,
    t_JXFI,
    t_JXMT,
    t_JXRL,
    t_JXRO,
    t_LOC,
    t_LOCKNEW,
    t_LOCKREL,
    t_LOCKRET,
    t_LOCKTRY,
    t_MERGEB,
    t_MERGEW,
    t_MIXPIX,
    t_MODCZ,
    t_MOV,
    t_MOVBYTS,
    t_MUL,
    t_MULPIX,
    t_MULS,
    t_MUXC,
    t_MUXNC,
    t_MUXNIBS,
    t_MUXNITS,
    t_MUXNZ,
    t_MUXQ,
    t_MUXZ,
    t_NEG,
    t_NEGC,
    t_NEGNC,
    t_NEGNZ,
    t_NEGZ,
    t_ALWAYS,
    t_NIXINT1,
    t_NIXINT2,
    t_NIXINT3,
    t_NOP,
    t_NOT,
    t_ONES,
    t_OR,
    t_OUTC,
    t_OUTH,
    t_OUTL,
    t_OUTNC,
    t_OUTNOT,
    t_OUTNZ,
    t_OUTRND,
    t_OUTZ,
    t_PA,
    t_PB,
    t_POLLATN,
    t_POLLCT1,
    t_POLLCT2,
    t_POLLCT3,
    t_POLLFBW,
    t_POLLINT,
    t_POLLPAT,
    t_POLLQMT,
    t_POLLSE1,
    t_POLLSE2,
    t_POLLSE3,
    t_POLLSE4,
    t_POLLXFI,
    t_POLLXMT,
    t_POLLXRL,
    t_POLLXRO,
    t_POP,
    t_POPA,
    t_POPB,
    t_PTRA,
    t_PTRB,
    t_PUSH,
    t_PUSHA,
    t_PUSHB,
    t_QDIV,
    t_QEXP,
    t_QFRAC,
    t_QLOG,
    t_QMUL,
    t_QROTATE,
    t_QSQRT,
    t_QVECTOR,
    t_RCL,
    t_RCR,
    t_RCZL,
    t_RCZR,
    t_RDBYTE,
    t_RDFAST,
    t_RDLONG,
    t_RDLUT,
    t_RDPIN,
    t_RDWORD,
    t_REP,
    t_RESI0,
    t_RESI1,
    t_RESI2,
    t_RESI3,
    t_RET,
    t_RETA,
    t_RETB,
    t_RETI0,
    t_RETI1,
    t_RETI2,
    t_RETI3,
    t_REV,
    t_RFBYTE,
    t_RFLONG,
    t_RFVAR,
    t_RFVARS,
    t_RFWORD,
    t_RGBEXP,
    t_RGBSQZ,
    t_ROL,
    t_ROLBYTE,
    t_ROLNIB,
    t_ROLWORD,
    t_ROR,
    t_RQPIN,
    t_SAL,
    t_SAR,
    t_SCA,
    t_SCAS,
    t_SETBYTE,
    t_SETCFRQ,
    t_SETCI,
    t_SETCMOD,
    t_SETCQ,
    t_SETCY,
    t_SETD,
    t_SETDACS,
    t_SETINT1,
    t_SETINT2,
    t_SETINT3,
    t_SETLUTS,
    t_SETNIB,
    t_SETPAT,
    t_SETPIV,
    t_SETPIX,
    t_SETQ,
    t_SETQ2,
    t_SETR,
    t_SETS,
    t_SETSCP,
    t_SETSE1,
    t_SETSE2,
    t_SETSE3,
    t_SETSE4,
    t_SETWORD,
    t_SETXFRQ,
    t_SEUSSF,
    t_SEUSSR,
    t_SHL,
    t_SHR,
    t_SIGNX,
    t_SKIP,
    t_SKIPF,
    t_SPLITB,
    t_SPLITW,
    t_STALLI,
    t_SUB,
    t_SUBR,
    t_SUBS,
    t_SUBSX,
    t_SUBX,
    t_SUMC,
    t_SUMNC,
    t_SUMNZ,
    t_SUMZ,
    t_TEST,
    t_TESTB,
    t_TESTBN,
    t_TESTN,
    t_TESTNB,
    t_TESTP,
    t_TESTPN,
    t_TJF,
    t_TJNF,
    t_TJNS,
    t_TJNZ,
    t_TJS,
    t_TJV,
    t_TJZ,
    t_TRGINT1,
    t_TRGINT2,
    t_TRGINT3,
    t_W,
    t_WAITATN,
    t_WAITCT1,
    t_WAITCT2,
    t_WAITCT3,
    t_WAITFBW,
    t_WAITINT,
    t_WAITPAT,
    t_WAITSE1,
    t_WAITSE2,
    t_WAITSE3,
    t_WAITSE4,
    t_WAITX,
    t_WAITXFI,
    t_WAITXMT,
    t_WAITXRL,
    t_WAITXRO,
    t_WFBYTE,
    t_WFLONG,
    t_WFWORD,
    t_WMLONG,
    t_WRBYTE,
    t_WRC,
    t_WRFAST,
    t_WRLONG,
    t_WRLUT,
    t_WRNC,
    t_WRNZ,
    t_WRPIN,
    t_WRWORD,
    t_WRZ,
    t_WXPIN,
    t_WYPIN,
    t_XCONT,
    t_XINIT,
    t_XOR,
    t_XORO32,
    t_XSTOP,
    t_XZERO,
    t_Z,
    t_ZEROX,
    t__RET_
}   p2_token_e;

class P2Token
{
public:
    P2Token(bool lowercase = false);
    QString str(p2_token_e token);

    bool lowercase() const;
    void setLowercase(bool lowercase = true);

private:
    bool m_lowercase;
    QMap<p2_token_e, QString> m_token;
};
