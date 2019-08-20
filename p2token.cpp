#include <QString>
#include "p2token.h"

P2Token Token;

P2Token::P2Token(bool lowercase)
    : m_lowercase(lowercase)
{
    m_token_string.insert(t_invalid,        QStringLiteral("<invalid>"));
    m_token_string.insert(t_nothing,        QStringLiteral(""));
    m_token_string.insert(t_empty,          QStringLiteral("<empty>"));
    m_token_string.insert(t__RET_,          QStringLiteral("_RET_"));
    m_token_string.insert(t_IF_C,           QStringLiteral("IF_C"));
    m_token_string.insert(t_IF_C_AND_NZ,    QStringLiteral("IF_C_AND_NZ"));
    m_token_string.insert(t_IF_C_AND_Z,     QStringLiteral("IF_C_AND_Z"));
    m_token_string.insert(t_IF_C_EQ_Z,      QStringLiteral("IF_C_EQ_Z"));
    m_token_string.insert(t_IF_C_NE_Z,      QStringLiteral("IF_C_NE_Z"));
    m_token_string.insert(t_IF_C_OR_NZ,     QStringLiteral("IF_C_OR_NZ"));
    m_token_string.insert(t_IF_C_OR_Z,      QStringLiteral("IF_C_OR_Z"));
    m_token_string.insert(t_IF_NC,          QStringLiteral("IF_NC"));
    m_token_string.insert(t_IF_NC_AND_NZ,   QStringLiteral("IF_NC_AND_NZ"));
    m_token_string.insert(t_IF_NC_AND_Z,    QStringLiteral("IF_NC_AND_Z"));
    m_token_string.insert(t_IF_NC_OR_NZ,    QStringLiteral("IF_NC_OR_NZ"));
    m_token_string.insert(t_IF_NC_OR_Z,     QStringLiteral("IF_NC_OR_Z"));
    m_token_string.insert(t_IF_NZ,          QStringLiteral("IF_NZ"));
    m_token_string.insert(t_IF_Z,           QStringLiteral("IF_Z"));
    m_token_string.insert(t_ALWAYS,         QStringLiteral(""));        // empty string

    m_token_string.insert(t_ABS,            QStringLiteral("ABS"));
    m_token_string.insert(t_ADD,            QStringLiteral("ADD"));
    m_token_string.insert(t_ADDCT1,         QStringLiteral("ADDCT1"));
    m_token_string.insert(t_ADDCT2,         QStringLiteral("ADDCT2"));
    m_token_string.insert(t_ADDCT3,         QStringLiteral("ADDCT3"));
    m_token_string.insert(t_ADDPIX,         QStringLiteral("ADDPIX"));
    m_token_string.insert(t_ADDS,           QStringLiteral("ADDS"));
    m_token_string.insert(t_ADDSX,          QStringLiteral("ADDSX"));
    m_token_string.insert(t_ADDX,           QStringLiteral("ADDX"));
    m_token_string.insert(t_AKPIN,          QStringLiteral("AKPIN"));
    m_token_string.insert(t_ALLOWI,         QStringLiteral("ALLOWI"));
    m_token_string.insert(t_ALTB,           QStringLiteral("ALTB"));
    m_token_string.insert(t_ALTD,           QStringLiteral("ALTD"));
    m_token_string.insert(t_ALTGB,          QStringLiteral("ALTGB"));
    m_token_string.insert(t_ALTGN,          QStringLiteral("ALTGN"));
    m_token_string.insert(t_ALTGW,          QStringLiteral("ALTGW"));
    m_token_string.insert(t_ALTI,           QStringLiteral("ALTI"));
    m_token_string.insert(t_ALTR,           QStringLiteral("ALTR"));
    m_token_string.insert(t_ALTS,           QStringLiteral("ALTS"));
    m_token_string.insert(t_ALTSB,          QStringLiteral("ALTSB"));
    m_token_string.insert(t_ALTSN,          QStringLiteral("ALTSN"));
    m_token_string.insert(t_ALTSW,          QStringLiteral("ALTSW"));
    m_token_string.insert(t_AND,            QStringLiteral("AND"));
    m_token_string.insert(t_ANDN,           QStringLiteral("ANDN"));
    m_token_string.insert(t_AUGD,           QStringLiteral("AUGD"));
    m_token_string.insert(t_AUGS,           QStringLiteral("AUGS"));
    m_token_string.insert(t_BITC,           QStringLiteral("BITC"));
    m_token_string.insert(t_BITH,           QStringLiteral("BITH"));
    m_token_string.insert(t_BITL,           QStringLiteral("BITL"));
    m_token_string.insert(t_BITNC,          QStringLiteral("BITNC"));
    m_token_string.insert(t_BITNOT,         QStringLiteral("BITNOT"));
    m_token_string.insert(t_BITNZ,          QStringLiteral("BITNZ"));
    m_token_string.insert(t_BITRND,         QStringLiteral("BITRND"));
    m_token_string.insert(t_BITZ,           QStringLiteral("BITZ"));
    m_token_string.insert(t_BLNPIX,         QStringLiteral("BLNPIX"));
    m_token_string.insert(t_BMASK,          QStringLiteral("BMASK"));
    m_token_string.insert(t_BRK,            QStringLiteral("BRK"));
    m_token_string.insert(t_CALL,           QStringLiteral("CALL"));
    m_token_string.insert(t_CALLA,          QStringLiteral("CALLA"));
    m_token_string.insert(t_CALLB,          QStringLiteral("CALLB"));
    m_token_string.insert(t_CALLD,          QStringLiteral("CALLD"));
    m_token_string.insert(t_CALLPA,         QStringLiteral("CALLPA"));
    m_token_string.insert(t_CALLPB,         QStringLiteral("CALLPB"));
    m_token_string.insert(t_CMP,            QStringLiteral("CMP"));
    m_token_string.insert(t_CMPM,           QStringLiteral("CMPM"));
    m_token_string.insert(t_CMPR,           QStringLiteral("CMPR"));
    m_token_string.insert(t_CMPS,           QStringLiteral("CMPS"));
    m_token_string.insert(t_CMPSUB,         QStringLiteral("CMPSUB"));
    m_token_string.insert(t_CMPSX,          QStringLiteral("CMPSX"));
    m_token_string.insert(t_CMPX,           QStringLiteral("CMPX"));
    m_token_string.insert(t_COGATN,         QStringLiteral("COGATN"));
    m_token_string.insert(t_COGBRK,         QStringLiteral("COGBRK"));
    m_token_string.insert(t_COGID,          QStringLiteral("COGID"));
    m_token_string.insert(t_COGINIT,        QStringLiteral("COGINIT"));
    m_token_string.insert(t_COGSTOP,        QStringLiteral("COGSTOP"));
    m_token_string.insert(t_CRCBIT,         QStringLiteral("CRCBIT"));
    m_token_string.insert(t_CRCNIB,         QStringLiteral("CRCNIB"));
    m_token_string.insert(t_DAT,            QStringLiteral("DAT"));
    m_token_string.insert(t_DECMOD,         QStringLiteral("DECMOD"));
    m_token_string.insert(t_DECOD,          QStringLiteral("DECOD"));
    m_token_string.insert(t_DIRC,           QStringLiteral("DIRC"));
    m_token_string.insert(t_DIRH,           QStringLiteral("DIRH"));
    m_token_string.insert(t_DIRL,           QStringLiteral("DIRL"));
    m_token_string.insert(t_DIRNC,          QStringLiteral("DIRNC"));
    m_token_string.insert(t_DIRNOT,         QStringLiteral("DIRNOT"));
    m_token_string.insert(t_DIRNZ,          QStringLiteral("DIRNZ"));
    m_token_string.insert(t_DIRRND,         QStringLiteral("DIRRND"));
    m_token_string.insert(t_DIRZ,           QStringLiteral("DIRZ"));
    m_token_string.insert(t_DJF,            QStringLiteral("DJF"));
    m_token_string.insert(t_DJNF,           QStringLiteral("DJNF"));
    m_token_string.insert(t_DJNZ,           QStringLiteral("DJNZ"));
    m_token_string.insert(t_DJZ,            QStringLiteral("DJZ"));
    m_token_string.insert(t_DRVC,           QStringLiteral("DRVC"));
    m_token_string.insert(t_DRVH,           QStringLiteral("DRVH"));
    m_token_string.insert(t_DRVL,           QStringLiteral("DRVL"));
    m_token_string.insert(t_DRVNC,          QStringLiteral("DRVNC"));
    m_token_string.insert(t_DRVNOT,         QStringLiteral("DRVNOT"));
    m_token_string.insert(t_DRVNZ,          QStringLiteral("DRVNZ"));
    m_token_string.insert(t_DRVRND,         QStringLiteral("DRVRND"));
    m_token_string.insert(t_DRVZ,           QStringLiteral("DRVZ"));
    m_token_string.insert(t_ENCOD,          QStringLiteral("ENCOD"));
    m_token_string.insert(t_EXECF,          QStringLiteral("EXECF"));
    m_token_string.insert(t_FBLOCK,         QStringLiteral("FBLOCK"));
    m_token_string.insert(t_FGE,            QStringLiteral("FGE"));
    m_token_string.insert(t_FGES,           QStringLiteral("FGES"));
    m_token_string.insert(t_FLE,            QStringLiteral("FLE"));
    m_token_string.insert(t_FLES,           QStringLiteral("FLES"));
    m_token_string.insert(t_FLTC,           QStringLiteral("FLTC"));
    m_token_string.insert(t_FLTH,           QStringLiteral("FLTH"));
    m_token_string.insert(t_FLTL,           QStringLiteral("FLTL"));
    m_token_string.insert(t_FLTNC,          QStringLiteral("FLTNC"));
    m_token_string.insert(t_FLTNOT,         QStringLiteral("FLTNOT"));
    m_token_string.insert(t_FLTNZ,          QStringLiteral("FLTNZ"));
    m_token_string.insert(t_FLTRND,         QStringLiteral("FLTRND"));
    m_token_string.insert(t_FLTZ,           QStringLiteral("FLTZ"));
    m_token_string.insert(t_GETBRK,         QStringLiteral("GETBRK"));
    m_token_string.insert(t_GETBYTE,        QStringLiteral("GETBYTE"));
    m_token_string.insert(t_GETCT,          QStringLiteral("GETCT"));
    m_token_string.insert(t_GETNIB,         QStringLiteral("GETNIB"));
    m_token_string.insert(t_GETPTR,         QStringLiteral("GETPTR"));
    m_token_string.insert(t_GETQX,          QStringLiteral("GETQX"));
    m_token_string.insert(t_GETQY,          QStringLiteral("GETQY"));
    m_token_string.insert(t_GETRND,         QStringLiteral("GETRND"));
    m_token_string.insert(t_GETSCP,         QStringLiteral("GETSCP"));
    m_token_string.insert(t_GETWORD,        QStringLiteral("GETWORD"));
    m_token_string.insert(t_GETXACC,        QStringLiteral("GETXACC"));
    m_token_string.insert(t_HUBSET,         QStringLiteral("HUBSET"));
    m_token_string.insert(t_IJNZ,           QStringLiteral("IJNZ"));
    m_token_string.insert(t_IJZ,            QStringLiteral("IJZ"));
    m_token_string.insert(t_INCMOD,         QStringLiteral("INCMOD"));
    m_token_string.insert(t_JATN,           QStringLiteral("JATN"));
    m_token_string.insert(t_JCT1,           QStringLiteral("JCT1"));
    m_token_string.insert(t_JCT2,           QStringLiteral("JCT2"));
    m_token_string.insert(t_JCT3,           QStringLiteral("JCT3"));
    m_token_string.insert(t_JFBW,           QStringLiteral("JFBW"));
    m_token_string.insert(t_JINT,           QStringLiteral("JINT"));
    m_token_string.insert(t_JMP,            QStringLiteral("JMP"));
    m_token_string.insert(t_JMPREL,         QStringLiteral("JMPREL"));
    m_token_string.insert(t_JNATN,          QStringLiteral("JNATN"));
    m_token_string.insert(t_JNCT1,          QStringLiteral("JNCT1"));
    m_token_string.insert(t_JNCT2,          QStringLiteral("JNCT2"));
    m_token_string.insert(t_JNCT3,          QStringLiteral("JNCT3"));
    m_token_string.insert(t_JNFBW,          QStringLiteral("JNFBW"));
    m_token_string.insert(t_JNINT,          QStringLiteral("JNINT"));
    m_token_string.insert(t_JNPAT,          QStringLiteral("JNPAT"));
    m_token_string.insert(t_JNQMT,          QStringLiteral("JNQMT"));
    m_token_string.insert(t_JNSE1,          QStringLiteral("JNSE1"));
    m_token_string.insert(t_JNSE2,          QStringLiteral("JNSE2"));
    m_token_string.insert(t_JNSE3,          QStringLiteral("JNSE3"));
    m_token_string.insert(t_JNSE4,          QStringLiteral("JNSE4"));
    m_token_string.insert(t_JNXFI,          QStringLiteral("JNXFI"));
    m_token_string.insert(t_JNXMT,          QStringLiteral("JNXMT"));
    m_token_string.insert(t_JNXRL,          QStringLiteral("JNXRL"));
    m_token_string.insert(t_JNXRO,          QStringLiteral("JNXRO"));
    m_token_string.insert(t_JPAT,           QStringLiteral("JPAT"));
    m_token_string.insert(t_JQMT,           QStringLiteral("JQMT"));
    m_token_string.insert(t_JSE1,           QStringLiteral("JSE1"));
    m_token_string.insert(t_JSE2,           QStringLiteral("JSE2"));
    m_token_string.insert(t_JSE3,           QStringLiteral("JSE3"));
    m_token_string.insert(t_JSE4,           QStringLiteral("JSE4"));
    m_token_string.insert(t_JXFI,           QStringLiteral("JXFI"));
    m_token_string.insert(t_JXMT,           QStringLiteral("JXMT"));
    m_token_string.insert(t_JXRL,           QStringLiteral("JXRL"));
    m_token_string.insert(t_JXRO,           QStringLiteral("JXRO"));
    m_token_string.insert(t_LOC,            QStringLiteral("LOC"));
    m_token_string.insert(t_LOCKNEW,        QStringLiteral("LOCKNEW"));
    m_token_string.insert(t_LOCKREL,        QStringLiteral("LOCKREL"));
    m_token_string.insert(t_LOCKRET,        QStringLiteral("LOCKRET"));
    m_token_string.insert(t_LOCKTRY,        QStringLiteral("LOCKTRY"));
    m_token_string.insert(t_MERGEB,         QStringLiteral("MERGEB"));
    m_token_string.insert(t_MERGEW,         QStringLiteral("MERGEW"));
    m_token_string.insert(t_MIXPIX,         QStringLiteral("MIXPIX"));
    m_token_string.insert(t_MODCZ,          QStringLiteral("MODCZ"));
    m_token_string.insert(t_MOV,            QStringLiteral("MOV"));
    m_token_string.insert(t_MOVBYTS,        QStringLiteral("MOVBYTS"));
    m_token_string.insert(t_MUL,            QStringLiteral("MUL"));
    m_token_string.insert(t_MULPIX,         QStringLiteral("MULPIX"));
    m_token_string.insert(t_MULS,           QStringLiteral("MULS"));
    m_token_string.insert(t_MUXC,           QStringLiteral("MUXC"));
    m_token_string.insert(t_MUXNC,          QStringLiteral("MUXNC"));
    m_token_string.insert(t_MUXNIBS,        QStringLiteral("MUXNIBS"));
    m_token_string.insert(t_MUXNITS,        QStringLiteral("MUXNITS"));
    m_token_string.insert(t_MUXNZ,          QStringLiteral("MUXNZ"));
    m_token_string.insert(t_MUXQ,           QStringLiteral("MUXQ"));
    m_token_string.insert(t_MUXZ,           QStringLiteral("MUXZ"));
    m_token_string.insert(t_NEG,            QStringLiteral("NEG"));
    m_token_string.insert(t_NEGC,           QStringLiteral("NEGC"));
    m_token_string.insert(t_NEGNC,          QStringLiteral("NEGNC"));
    m_token_string.insert(t_NEGNZ,          QStringLiteral("NEGNZ"));
    m_token_string.insert(t_NEGZ,           QStringLiteral("NEGZ"));
    m_token_string.insert(t_NIXINT1,        QStringLiteral("NIXINT1"));
    m_token_string.insert(t_NIXINT2,        QStringLiteral("NIXINT2"));
    m_token_string.insert(t_NIXINT3,        QStringLiteral("NIXINT3"));
    m_token_string.insert(t_NOP,            QStringLiteral("NOP"));
    m_token_string.insert(t_NOT,            QStringLiteral("NOT"));
    m_token_string.insert(t_ONES,           QStringLiteral("ONES"));
    m_token_string.insert(t_OR,             QStringLiteral("OR"));
    m_token_string.insert(t_OUTC,           QStringLiteral("OUTC"));
    m_token_string.insert(t_OUTH,           QStringLiteral("OUTH"));
    m_token_string.insert(t_OUTL,           QStringLiteral("OUTL"));
    m_token_string.insert(t_OUTNC,          QStringLiteral("OUTNC"));
    m_token_string.insert(t_OUTNOT,         QStringLiteral("OUTNOT"));
    m_token_string.insert(t_OUTNZ,          QStringLiteral("OUTNZ"));
    m_token_string.insert(t_OUTRND,         QStringLiteral("OUTRND"));
    m_token_string.insert(t_OUTZ,           QStringLiteral("OUTZ"));
    m_token_string.insert(t_PA,             QStringLiteral("PA"));
    m_token_string.insert(t_PB,             QStringLiteral("PB"));
    m_token_string.insert(t_POLLATN,        QStringLiteral("POLLATN"));
    m_token_string.insert(t_POLLCT1,        QStringLiteral("POLLCT1"));
    m_token_string.insert(t_POLLCT2,        QStringLiteral("POLLCT2"));
    m_token_string.insert(t_POLLCT3,        QStringLiteral("POLLCT3"));
    m_token_string.insert(t_POLLFBW,        QStringLiteral("POLLFBW"));
    m_token_string.insert(t_POLLINT,        QStringLiteral("POLLINT"));
    m_token_string.insert(t_POLLPAT,        QStringLiteral("POLLPAT"));
    m_token_string.insert(t_POLLQMT,        QStringLiteral("POLLQMT"));
    m_token_string.insert(t_POLLSE1,        QStringLiteral("POLLSE1"));
    m_token_string.insert(t_POLLSE2,        QStringLiteral("POLLSE2"));
    m_token_string.insert(t_POLLSE3,        QStringLiteral("POLLSE3"));
    m_token_string.insert(t_POLLSE4,        QStringLiteral("POLLSE4"));
    m_token_string.insert(t_POLLXFI,        QStringLiteral("POLLXFI"));
    m_token_string.insert(t_POLLXMT,        QStringLiteral("POLLXMT"));
    m_token_string.insert(t_POLLXRL,        QStringLiteral("POLLXRL"));
    m_token_string.insert(t_POLLXRO,        QStringLiteral("POLLXRO"));
    m_token_string.insert(t_POP,            QStringLiteral("POP"));
    m_token_string.insert(t_POPA,           QStringLiteral("POPA"));
    m_token_string.insert(t_POPB,           QStringLiteral("POPB"));
    m_token_string.insert(t_PTRA,           QStringLiteral("PTRA"));
    m_token_string.insert(t_PTRA_predec,    QStringLiteral("--PTRA"));
    m_token_string.insert(t_PTRA_postinc,   QStringLiteral("PTRA++"));
    m_token_string.insert(t_PTRB,           QStringLiteral("PTRB"));
    m_token_string.insert(t_PTRB_predec,    QStringLiteral("--PTRB"));
    m_token_string.insert(t_PTRB_postinc,   QStringLiteral("PTRB++"));
    m_token_string.insert(t_PUSH,           QStringLiteral("PUSH"));
    m_token_string.insert(t_PUSHA,          QStringLiteral("PUSHA"));
    m_token_string.insert(t_PUSHB,          QStringLiteral("PUSHB"));
    m_token_string.insert(t_QDIV,           QStringLiteral("QDIV"));
    m_token_string.insert(t_QEXP,           QStringLiteral("QEXP"));
    m_token_string.insert(t_QFRAC,          QStringLiteral("QFRAC"));
    m_token_string.insert(t_QLOG,           QStringLiteral("QLOG"));
    m_token_string.insert(t_QMUL,           QStringLiteral("QMUL"));
    m_token_string.insert(t_QROTATE,        QStringLiteral("QROTATE"));
    m_token_string.insert(t_QSQRT,          QStringLiteral("QSQRT"));
    m_token_string.insert(t_QVECTOR,        QStringLiteral("QVECTOR"));
    m_token_string.insert(t_RCL,            QStringLiteral("RCL"));
    m_token_string.insert(t_RCR,            QStringLiteral("RCR"));
    m_token_string.insert(t_RCZL,           QStringLiteral("RCZL"));
    m_token_string.insert(t_RCZR,           QStringLiteral("RCZR"));
    m_token_string.insert(t_RDBYTE,         QStringLiteral("RDBYTE"));
    m_token_string.insert(t_RDFAST,         QStringLiteral("RDFAST"));
    m_token_string.insert(t_RDLONG,         QStringLiteral("RDLONG"));
    m_token_string.insert(t_RDLUT,          QStringLiteral("RDLUT"));
    m_token_string.insert(t_RDPIN,          QStringLiteral("RDPIN"));
    m_token_string.insert(t_RDWORD,         QStringLiteral("RDWORD"));
    m_token_string.insert(t_REP,            QStringLiteral("REP"));
    m_token_string.insert(t_RESI0,          QStringLiteral("RESI0"));
    m_token_string.insert(t_RESI1,          QStringLiteral("RESI1"));
    m_token_string.insert(t_RESI2,          QStringLiteral("RESI2"));
    m_token_string.insert(t_RESI3,          QStringLiteral("RESI3"));
    m_token_string.insert(t_RET,            QStringLiteral("RET"));
    m_token_string.insert(t_RETA,           QStringLiteral("RETA"));
    m_token_string.insert(t_RETB,           QStringLiteral("RETB"));
    m_token_string.insert(t_RETI0,          QStringLiteral("RETI0"));
    m_token_string.insert(t_RETI1,          QStringLiteral("RETI1"));
    m_token_string.insert(t_RETI2,          QStringLiteral("RETI2"));
    m_token_string.insert(t_RETI3,          QStringLiteral("RETI3"));
    m_token_string.insert(t_REV,            QStringLiteral("REV"));
    m_token_string.insert(t_RFBYTE,         QStringLiteral("RFBYTE"));
    m_token_string.insert(t_RFLONG,         QStringLiteral("RFLONG"));
    m_token_string.insert(t_RFVAR,          QStringLiteral("RFVAR"));
    m_token_string.insert(t_RFVARS,         QStringLiteral("RFVARS"));
    m_token_string.insert(t_RFWORD,         QStringLiteral("RFWORD"));
    m_token_string.insert(t_RGBEXP,         QStringLiteral("RGBEXP"));
    m_token_string.insert(t_RGBSQZ,         QStringLiteral("RGBSQZ"));
    m_token_string.insert(t_ROL,            QStringLiteral("ROL"));
    m_token_string.insert(t_ROLBYTE,        QStringLiteral("ROLBYTE"));
    m_token_string.insert(t_ROLNIB,         QStringLiteral("ROLNIB"));
    m_token_string.insert(t_ROLWORD,        QStringLiteral("ROLWORD"));
    m_token_string.insert(t_ROR,            QStringLiteral("ROR"));
    m_token_string.insert(t_RQPIN,          QStringLiteral("RQPIN"));
    m_token_string.insert(t_SAL,            QStringLiteral("SAL"));
    m_token_string.insert(t_SAR,            QStringLiteral("SAR"));
    m_token_string.insert(t_SCA,            QStringLiteral("SCA"));
    m_token_string.insert(t_SCAS,           QStringLiteral("SCAS"));
    m_token_string.insert(t_SETBYTE,        QStringLiteral("SETBYTE"));
    m_token_string.insert(t_SETCFRQ,        QStringLiteral("SETCFRQ"));
    m_token_string.insert(t_SETCI,          QStringLiteral("SETCI"));
    m_token_string.insert(t_SETCMOD,        QStringLiteral("SETCMOD"));
    m_token_string.insert(t_SETCQ,          QStringLiteral("SETCQ"));
    m_token_string.insert(t_SETCY,          QStringLiteral("SETCY"));
    m_token_string.insert(t_SETD,           QStringLiteral("SETD"));
    m_token_string.insert(t_SETDACS,        QStringLiteral("SETDACS"));
    m_token_string.insert(t_SETINT1,        QStringLiteral("SETINT1"));
    m_token_string.insert(t_SETINT2,        QStringLiteral("SETINT2"));
    m_token_string.insert(t_SETINT3,        QStringLiteral("SETINT3"));
    m_token_string.insert(t_SETLUTS,        QStringLiteral("SETLUTS"));
    m_token_string.insert(t_SETNIB,         QStringLiteral("SETNIB"));
    m_token_string.insert(t_SETPAT,         QStringLiteral("SETPAT"));
    m_token_string.insert(t_SETPIV,         QStringLiteral("SETPIV"));
    m_token_string.insert(t_SETPIX,         QStringLiteral("SETPIX"));
    m_token_string.insert(t_SETQ,           QStringLiteral("SETQ"));
    m_token_string.insert(t_SETQ2,          QStringLiteral("SETQ2"));
    m_token_string.insert(t_SETR,           QStringLiteral("SETR"));
    m_token_string.insert(t_SETS,           QStringLiteral("SETS"));
    m_token_string.insert(t_SETSCP,         QStringLiteral("SETSCP"));
    m_token_string.insert(t_SETSE1,         QStringLiteral("SETSE1"));
    m_token_string.insert(t_SETSE2,         QStringLiteral("SETSE2"));
    m_token_string.insert(t_SETSE3,         QStringLiteral("SETSE3"));
    m_token_string.insert(t_SETSE4,         QStringLiteral("SETSE4"));
    m_token_string.insert(t_SETWORD,        QStringLiteral("SETWORD"));
    m_token_string.insert(t_SETXFRQ,        QStringLiteral("SETXFRQ"));
    m_token_string.insert(t_SEUSSF,         QStringLiteral("SEUSSF"));
    m_token_string.insert(t_SEUSSR,         QStringLiteral("SEUSSR"));
    m_token_string.insert(t_SHL,            QStringLiteral("SHL"));
    m_token_string.insert(t_SHR,            QStringLiteral("SHR"));
    m_token_string.insert(t_SIGNX,          QStringLiteral("SIGNX"));
    m_token_string.insert(t_SKIP,           QStringLiteral("SKIP"));
    m_token_string.insert(t_SKIPF,          QStringLiteral("SKIPF"));
    m_token_string.insert(t_SPACE,          QStringLiteral("SPACE"));
    m_token_string.insert(t_SPLITB,         QStringLiteral("SPLITB"));
    m_token_string.insert(t_SPLITW,         QStringLiteral("SPLITW"));
    m_token_string.insert(t_STALLI,         QStringLiteral("STALLI"));
    m_token_string.insert(t_SUB,            QStringLiteral("SUB"));
    m_token_string.insert(t_SUBR,           QStringLiteral("SUBR"));
    m_token_string.insert(t_SUBS,           QStringLiteral("SUBS"));
    m_token_string.insert(t_SUBSX,          QStringLiteral("SUBSX"));
    m_token_string.insert(t_SUBX,           QStringLiteral("SUBX"));
    m_token_string.insert(t_SUMC,           QStringLiteral("SUMC"));
    m_token_string.insert(t_SUMNC,          QStringLiteral("SUMNC"));
    m_token_string.insert(t_SUMNZ,          QStringLiteral("SUMNZ"));
    m_token_string.insert(t_SUMZ,           QStringLiteral("SUMZ"));
    m_token_string.insert(t_TEST,           QStringLiteral("TEST"));
    m_token_string.insert(t_TESTB,          QStringLiteral("TESTB"));
    m_token_string.insert(t_TESTBN,         QStringLiteral("TESTBN"));
    m_token_string.insert(t_TESTN,          QStringLiteral("TESTN"));
    m_token_string.insert(t_TESTBN,         QStringLiteral("TESTNB"));
    m_token_string.insert(t_TESTP,          QStringLiteral("TESTP"));
    m_token_string.insert(t_TESTPN,         QStringLiteral("TESTPN"));
    m_token_string.insert(t_TJF,            QStringLiteral("TJF"));
    m_token_string.insert(t_TJNF,           QStringLiteral("TJNF"));
    m_token_string.insert(t_TJNS,           QStringLiteral("TJNS"));
    m_token_string.insert(t_TJNZ,           QStringLiteral("TJNZ"));
    m_token_string.insert(t_TJS,            QStringLiteral("TJS"));
    m_token_string.insert(t_TJV,            QStringLiteral("TJV"));
    m_token_string.insert(t_TJZ,            QStringLiteral("TJZ"));
    m_token_string.insert(t_TRGINT1,        QStringLiteral("TRGINT1"));
    m_token_string.insert(t_TRGINT2,        QStringLiteral("TRGINT2"));
    m_token_string.insert(t_TRGINT3,        QStringLiteral("TRGINT3"));
    m_token_string.insert(t_WAITATN,        QStringLiteral("WAITATN"));
    m_token_string.insert(t_WAITCT1,        QStringLiteral("WAITCT1"));
    m_token_string.insert(t_WAITCT2,        QStringLiteral("WAITCT2"));
    m_token_string.insert(t_WAITCT3,        QStringLiteral("WAITCT3"));
    m_token_string.insert(t_WAITFBW,        QStringLiteral("WAITFBW"));
    m_token_string.insert(t_WAITINT,        QStringLiteral("WAITINT"));
    m_token_string.insert(t_WAITPAT,        QStringLiteral("WAITPAT"));
    m_token_string.insert(t_WAITSE1,        QStringLiteral("WAITSE1"));
    m_token_string.insert(t_WAITSE2,        QStringLiteral("WAITSE2"));
    m_token_string.insert(t_WAITSE3,        QStringLiteral("WAITSE3"));
    m_token_string.insert(t_WAITSE4,        QStringLiteral("WAITSE4"));
    m_token_string.insert(t_WAITX,          QStringLiteral("WAITX"));
    m_token_string.insert(t_WAITXFI,        QStringLiteral("WAITXFI"));
    m_token_string.insert(t_WAITXMT,        QStringLiteral("WAITXMT"));
    m_token_string.insert(t_WAITXRL,        QStringLiteral("WAITXRL"));
    m_token_string.insert(t_WAITXRO,        QStringLiteral("WAITXRO"));
    m_token_string.insert(t_WFBYTE,         QStringLiteral("WFBYTE"));
    m_token_string.insert(t_WFLONG,         QStringLiteral("WFLONG"));
    m_token_string.insert(t_WFWORD,         QStringLiteral("WFWORD"));
    m_token_string.insert(t_WMLONG,         QStringLiteral("WMLONG"));
    m_token_string.insert(t_WRBYTE,         QStringLiteral("WRBYTE"));
    m_token_string.insert(t_WRC,            QStringLiteral("WRC"));
    m_token_string.insert(t_WRFAST,         QStringLiteral("WRFAST"));
    m_token_string.insert(t_WRLONG,         QStringLiteral("WRLONG"));
    m_token_string.insert(t_WRLUT,          QStringLiteral("WRLUT"));
    m_token_string.insert(t_WRNC,           QStringLiteral("WRNC"));
    m_token_string.insert(t_WRNZ,           QStringLiteral("WRNZ"));
    m_token_string.insert(t_WRPIN,          QStringLiteral("WRPIN"));
    m_token_string.insert(t_WRWORD,         QStringLiteral("WRWORD"));
    m_token_string.insert(t_WRZ,            QStringLiteral("WRZ"));
    m_token_string.insert(t_WXPIN,          QStringLiteral("WXPIN"));
    m_token_string.insert(t_WYPIN,          QStringLiteral("WYPIN"));
    m_token_string.insert(t_XCONT,          QStringLiteral("XCONT"));
    m_token_string.insert(t_XINIT,          QStringLiteral("XINIT"));
    m_token_string.insert(t_XOR,            QStringLiteral("XOR"));
    m_token_string.insert(t_XORO32,         QStringLiteral("XORO32"));
    m_token_string.insert(t_XSTOP,          QStringLiteral("XSTOP"));
    m_token_string.insert(t_XZERO,          QStringLiteral("XZERO"));
    m_token_string.insert(t_ZEROX,          QStringLiteral("ZEROX"));

    m_token_string.insert(t_WC,             QStringLiteral("WC"));
    m_token_string.insert(t_WZ,             QStringLiteral("WZ"));
    m_token_string.insert(t_WCZ,            QStringLiteral("WCZ"));
    m_token_string.insert(t_ANDC,           QStringLiteral("ANDC"));
    m_token_string.insert(t_ANDZ,           QStringLiteral("ANDZ"));
    m_token_string.insert(t_ORC,            QStringLiteral("ORC"));
    m_token_string.insert(t_ORZ,            QStringLiteral("ORZ"));
    m_token_string.insert(t_XORC,           QStringLiteral("XORC"));
    m_token_string.insert(t_XORZ,           QStringLiteral("XORZ"));

    m_token_string.insert(t__BYTE,          QStringLiteral("BYTE"));
    m_token_string.insert(t__WORD,          QStringLiteral("WORD"));
    m_token_string.insert(t__LONG,          QStringLiteral("LONG"));
    m_token_string.insert(t__RES,           QStringLiteral("RES"));
    m_token_string.insert(t__FIT,           QStringLiteral("FIT"));
    m_token_string.insert(t__ORG,           QStringLiteral("ORG"));
    m_token_string.insert(t__ORGH,          QStringLiteral("ORGH"));
    m_token_string.insert(t__ASSIGN,        QStringLiteral("="));
    m_token_string.insert(t__DOLLAR,        QStringLiteral("$"));
    m_token_string.insert(t__EQ,            QStringLiteral("=="));
    m_token_string.insert(t__NE,            QStringLiteral("!="));
    m_token_string.insert(t__GE,            QStringLiteral(">="));
    m_token_string.insert(t__GT,            QStringLiteral(">"));
    m_token_string.insert(t__LE,            QStringLiteral("<="));
    m_token_string.insert(t__LT,            QStringLiteral("<"));
    m_token_string.insert(t__ADD,           QStringLiteral("+"));
    m_token_string.insert(t__SUB,           QStringLiteral("-"));
    m_token_string.insert(t__MUL,           QStringLiteral("*"));
    m_token_string.insert(t__DIV,           QStringLiteral("/"));
    m_token_string.insert(t__MOD,           QStringLiteral("MOD"));
    m_token_string.insert(t__NOT,           QStringLiteral("!"));
    m_token_string.insert(t__AND,           QStringLiteral("&"));
    m_token_string.insert(t__OR,            QStringLiteral("|"));
    m_token_string.insert(t__XOR,           QStringLiteral("^"));
    m_token_string.insert(t__INC,           QStringLiteral("++"));
    m_token_string.insert(t__DEC,           QStringLiteral("--"));
    m_token_string.insert(t__SHL,           QStringLiteral("<<"));
    m_token_string.insert(t__SHR,           QStringLiteral(">>"));

    // Build the reverse QMultiHash for string lookup
    foreach(p2_token_e tok, m_token_string.keys())
        foreach(const QString& str, m_token_string.values(tok))
            m_string_token.insert(str, tok);
}

/**
 * @brief Return the current lowercase enable state
 * @return
 */
bool P2Token::lowercase() const
{
    return m_lowercase;
}

/**
 * @brief Set the lowercase enable true or false
 * @param flag lowercase enable (true), disable (false)
 */
void P2Token::setLowercase(bool flag)
{
    m_lowercase = flag;
}

/**
 * @brief Return a QString for the given %token
 * @param token one of p2_toke_e enume
 * @return QString in uppercase or lowercase
 */
QString P2Token::string(p2_token_e token)
{
    QString str = m_token_string.value(token);
    return m_lowercase ? str.toLower() : str;
}

/**
 * @brief Return a p2_token_e enumeration value for the QString %str
 * @param str QString to scan for
 * @return p2_token_e enumeration value, or t_nothing if not a known string
 */
p2_token_e P2Token::token(const QString& str)
{
    const QString token = str.trimmed().toUpper();
    return m_string_token.value(token, t_nothing);
}
