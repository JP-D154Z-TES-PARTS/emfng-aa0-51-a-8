/* emfng-pa000-5000-a-M4 */
/*********************************************************************/
/*  Copyright Toyota Motor Corporation                               */
/*********************************************************************/
/*  Version: aa0-51-a (6-cylinder)                                   */
/*********************************************************************/

/*********************************************************************/
/* �I�u�W�F�N�g�� |  ���Ό��o�ُ픻�蕔                              */
/* ���ӎ���       | �y����OBD�L�zAND�y6�C���z                        */
/*-------------------------------------------------------------------*/
/*     �ʕύX���� �i�ʕύX���͈ȉ��ɕύX���A���e���L�����邱�Ɓj */
/*********************************************************************/

/*-------------------------------------------------------------------*/
/* �K���萔�̃Z�N�V������`                                          */
/*-------------------------------------------------------------------*/
#pragma ghs section rozdata = ".mat_emfng"

/*-------------------------------------------------------------------*/
/* �w�b�_�t�@�C���̃C���N���[�h                                      */
/*-------------------------------------------------------------------*/
#include <../inc/common.h>
#include <../inc/gllib.h>
#include <engsrc/espc/ejcc.h>           /* JEEFI,JEEGTYPE,JEHIPFI_E,JEMFHOUKI */
                                        /* JEMFOTLV,JEOBDSIMUKE,JEOOBD,u1g_EJCC_NCYL */
                                        /* u1g_EJCC_USAMF,u1g_EJCC_JCUT,u1g_EJCC_ECUT,u1g_EJCC_CCUT,u1g_EJCC_CD34,u1g_EJCC_DUAL,JENGPF_E,u1g_EJCC_V6CYL */
#include <engsrc/inc/elsb.h>

#include <eng/emf/emfng.h>

/*-------------------------------------------------------------------*/
/* �R���p�C���o�[�W������`                                          */
/*-------------------------------------------------------------------*/
#define MK32_ID                         (0x00000040)             /* R9�R���p�C�����g�p */

#ifdef __GHS_VERSION_NUMBER
 #if ( ( __GHS_VERSION_NUMBER >= 201355 ) \
    && ( __GHS_VERSION_NUMBER < 201400 ) )
 #else
  #error "�R���p�C�������R���p�C�����قȂ��Ă��܂��B"
 #endif
#endif

/*-------------------------------------------------------------------*/
/* �R���p�C��SW����`�`�F�b�N                                        */
/*-------------------------------------------------------------------*/
#if !defined JEEFI
#error "JEEFI is undeclared"
#endif

#if !defined JEEGTYPE
#error "JEEGTYPE is undeclared"
#endif

#if !defined JEHIPFI_E
#error "JEHIPFI_E is undeclared"
#endif

#if !defined JEMFHOUKI
#error "JEMFHOUKI is undeclared"
#endif

#if !defined JEMFOTLV
#error "JEMFOTLV is undeclared"
#endif

#if !defined JEOBDSIMUKE
#error "JEOBDSIMUKE is undeclared"
#endif

#if !defined JEOOBD
#error "JEOOBD is undeclared"
#endif

#if !defined u1g_EJCC_NCYL
#error "u1g_EJCC_NCYL is undeclared"
#endif

#if !defined u1g_EJCC_USAMF
#error "u1g_EJCC_USAMF is undeclared"
#endif

#if !defined u1g_EJCC_JCUT
#error "u1g_EJCC_JCUT is undeclared"
#endif

#if !defined u1g_EJCC_ECUT
#error "u1g_EJCC_ECUT is undeclared"
#endif

#if !defined u1g_EJCC_CCUT
#error "u1g_EJCC_CCUT is undeclared"
#endif

#if !defined u1g_EJCC_CD34
#error "u1g_EJCC_CD34 is undeclared"
#endif

#if !defined u1g_EJCC_DUAL
#error "u1g_EJCC_DUAL is undeclared"
#endif

#if !defined JENGPF_E
#error "JENGPF_E is undeclared"
#endif

#if !defined u1g_EJCC_V6CYL
#error "u1g_EJCC_V6CYL is undeclared"
#endif

/*---------------------------------------------------------------------*/
/* �Œ�萔                                                            */
/*---------------------------------------------------------------------*/
/* $$$�Œ�萔_�W��_v4.11 */
/* �Œ�萔 EMFNG_MFSTOTI�́Aemfng_l_mat.c�t�@�C���ɒ�`���܂����B */
/* #if (JETCORE_D == u1g_EJCC_USE) && (JEOBDUDS_D == u1g_EJCC_USE) */   /* �yt-CORE�Ή��L�zAND�yOBDonUDS�Ή��L�z */
/* �Œ�萔 EMFNG_CXMF1PAS�́Aemfng_l_mat.c�t�@�C���ɒ�`���܂����B */
/* �Œ�萔 EMFNG_CXMFPAS�́Aemfng_l_mat.c�t�@�C���ɒ�`���܂����B */
/* #endif */                                                            /* JETCORE_D JEOBDUDS_D */
/* $$$�Œ�萔_�W��_v4.11 */

/*-------------------------------------------------------------------*/
/* �K���萔                                                          */
/*-------------------------------------------------------------------*/
/* $$$�K���萔_�W��_v4.11 */

#if JEMFOTLV == u1g_EJCC_NOT_USE                                        /* �y�G�}OT���ٌ��薳�z */
  #if JEMFHOUKI == u1g_EJCC_USAMF                                       /* �y�G�}OT���ٌ��薳�zAND�y�ΕĖ@�K�z */
volatile const s2 s2s_emfng_MFDD = s2g_glround((1.5)/(256./128./256.)); /* m=emfng,lsb=256/128/256,ofs=,unit=% :EM�������َ��Η� */
volatile const u2 u2s_emfng_MFD1 = (u2)(((0.9)/(2./256./256.))+0.5);    /* m=emfng,lsb=2/256/256,ofs=,unit= :EM�������َ��Ό��o�� */

  #else                                                                 /* �y�G�}OT���ٌ��薳�zAND�y�ΕĖ@�K�ȊO�z */
volatile const s2 s2s_emfng_MFDD = s2g_glround((1.5)/(256./128./256.)); /* m=emfng,lsb=256/128/256,ofs=,unit=% :EM�������َ��Η� */
volatile const u2 u2s_emfng_MFD1 = (u2)(((0.9)/(2./256./256.))+0.5);    /* m=emfng,lsb=2/256/256,ofs=,unit= :EM�������َ��Ό��o�� */
  #endif                                                                /* JEMFHOUKI */
#else                                                                   /* �y�G�}OT���ٌ���L�z */
volatile const s2 s2s_emfng_MFDD = s2g_glround((16.6)/(256./128./256.));    /* m=emfng,lsb=256/128/256,ofs=,unit=% :EM�������َ��Η� */
volatile const u2 u2s_emfng_MFD1 = (u2)(((0.9)/(2./256./256.))+0.5);    /* m=emfng,lsb=2/256/256,ofs=,unit= :EM�������َ��Ό��o�� */
#endif                                                                  /* JEMFOTLV */

volatile const s2 s2s_emfng_MFNEL3 = s2g_ELSB_NE(1050.);                /* m=emfng,lsb=12800/64/256,ofs=,unit=rpm :�A�C�h���̈攻��l */
volatile const u2 u2g_emfng_LJMFOT = (u2)(((200.)/(2./u1g_EJCC_NCYL))+0.5); /* m=emfng,lsb=2/u1g_EJCC_NCYL,ofs=,unit=rev :�G�}OT���وُ픻����s���ݸ� */
volatile const u2 u2s_emfng_LJMFOTI = (u2)(((170.)/(2./u1g_EJCC_NCYL))+0.5);    /* m=emfng,lsb=2/u1g_EJCC_NCYL,ofs=,unit=rev :�G�}OT���ٱ���َ��ُ픻����s���ݸ� */
volatile const u2 u2s_emfng_LJMFOTF = (u2)(((190.)/(2./u1g_EJCC_NCYL))+0.5);    /* m=emfng,lsb=2/u1g_EJCC_NCYL,ofs=,unit=rev :�G�}OT���وُ픻����s���ݸ� */
volatile const u1 u1s_emfng_CXMFH = (u1)(((4.)/(1.))+0.5);              /* m=emfng,lsb=1,ofs=,unit=�� :EM�������وُ팟�o�񐔔���l */
volatile const u1 u1s_emfng_CXMFL = (u1)(((1.)/(1.))+0.5);              /* m=emfng,lsb=1,ofs=,unit=�� :EM�������وُ팟�o�񐔔���l */
volatile const u1 u1s_emfng_CXMF1H = (u1)(((3.)/(1.))+0.5);             /* m=emfng,lsb=1,ofs=,unit=�� :�G�}OT���وُ팟�o�񐔔���l */
volatile const u1 u1s_emfng_CXMF1L = (u1)(((1.)/(1.))+0.5);             /* m=emfng,lsb=1,ofs=,unit=�� :�G�}OT���وُ팟�o�񐔔���l */
volatile const u1 u1s_emfng_MFSTOT = (u1)(((70.)/(1.))+0.5);            /* m=emfng,lsb=1,ofs=,unit=�� :�C���ʎ��Ή񐔔���l */
volatile const u1 u1s_emfng_MFSTEMI = (u1)(((72.)/(1.))+0.5);           /* m=emfng,lsb=1,ofs=,unit=�� :����ْ��C���ʎ��Ή񐔔���l */
volatile const u2 u2g_emfng_LJMFEM = (u2)(((1000.)/(2./u1g_EJCC_NCYL))+0.5);    /* m=emfng,lsb=2/u1g_EJCC_NCYL,ofs=,unit=rev :EM�������وُ픻����s���ݸ� */
volatile const u1 u1s_emfng_CJPMF = (u1)(((3.)/(1.))+0.5);              /* m=emfng,lsb=1,ofs=,unit=�� :��۸۽��������l */
volatile const u1 u1g_emfng_CDTMFWA = (u1)(((10.)/(1.))+0.5);           /* m=emfng,lsb=1,ofs=,unit=�� :EM��������p���H��������l */
volatile const u1 u1s_emfng_CDTMF2 = (u1)(((3.)/(1.))+0.5);             /* m=emfng,lsb=1,ofs=,unit=�� :�G�}OT����p���H��������l */
volatile const u1 u1s_emfng_KLDMFOT = (u1)(((90.)/(1.))+0.5);           /* m=emfng,lsb=1,ofs=,unit=�� :�G�}OT���َ��Ή񐔔���l(100�_��/1�C���ӂ�) */
volatile const u1 u1g_emfng_CATN = (u1)(((2.)/(1.))+0.5);               /* m=emfng,lsb=1,ofs=,unit= :�o���N����ʂ̗L��(��:1,�L:2) */
volatile const u1 u1s_emfng_KLD1 = (u1)(((0.75)/(2./256.))+0.5);        /* m=emfng,lsb=2/256,ofs=,unit= :�Ό��C�����Ό��o������ */
volatile const u1 u1s_emfng_KLD2 = (u1)(((1.1)/(2./256.))+0.5);         /* m=emfng,lsb=2/256,ofs=,unit= :�Ό��C�����Ό��o����� */

#if (JEOBDSIMUKE == u1g_EJCC_JCUT) || (JEOBDSIMUKE == u1g_EJCC_ECUT) || (JEOBDSIMUKE == u1g_EJCC_CCUT)  /* �yJPN��āzOR�yEuro��āzOR�yCARB��āz */
volatile const s2 s2g_emfng_MFOTL = s2g_glround((33.3)/(256./128./256.));   /* m=emfng,lsb=256/128/256,ofs=,unit=% :�G�}OT���َ��Δ��艺���l */

#elif (JEMFHOUKI == u1g_EJCC_USAMF) || (JEOBDSIMUKE == u1g_EJCC_CD34)   /* (�yJPN��āzOR�yEuro��āzOR�yCARB��āz)�ȊO AND(�y�ΕĖ@�K�zOR�y���x�J-OBD�z) */
volatile const s2 s2g_emfng_MFOTL = s2g_glround((5.)/(256./128./256.)); /* m=emfng,lsb=256/128/256,ofs=,unit=% :�G�}OT���َ��Δ��艺���l */

#else                                                                   /* ((�yJPN��āzOR�yEuro��āzOR�yCARB��āz)OR (�y�ΕĖ@�K�zOR�y���x�J-OBD�z))�ȊO */
volatile const s2 s2g_emfng_MFOTL = s2g_glround((0.)/(256./128./256.)); /* m=emfng,lsb=256/128/256,ofs=,unit=% :�G�}OT���َ��Δ��艺���l */
#endif                                                                  /* JEOBDSIMUKE JEMFHOUKI */

#if JEMFOTLV == u1g_EJCC_NOT_USE                                        /* �y�G�}OT���ٌ��薳�z */
  #if JEMFHOUKI == u1g_EJCC_USAMF                                       /* �y�G�}OT���ٌ��薳�zAND�y�ΕĖ@�K�z */
volatile const u1 u1s_emfng_ST1RTO = (u1)(((1.)/(8./256.))+0.5);        /* m=emfng,lsb=8/256,ofs=,unit=�{ :����޽��Ď�EM�������َ��Ή񐔔���l�Z�o�W�� */
volatile const u1 u1s_emfng_ST2RTO = (u1)(((5.)/(8./256.))+0.5);        /* m=emfng,lsb=8/256,ofs=,unit=�{ :ίĽ��Ď�EM�������َ��Ή񐔔���l�Z�o�W�� */

  #else                                                                 /* �y�G�}OT���ٌ��薳�zAND�y�ΕĖ@�K�ȊO�z */
volatile const u1 u1s_emfng_ST1RTO = (u1)(((5.)/(8./256.))+0.5);        /* m=emfng,lsb=8/256,ofs=,unit=�{ :����޽��Ď�EM�������َ��Ή񐔔���l�Z�o�W�� */
volatile const u1 u1s_emfng_ST2RTO = (u1)(((5.)/(8./256.))+0.5);        /* m=emfng,lsb=8/256,ofs=,unit=�{ :ίĽ��Ď�EM�������َ��Ή񐔔���l�Z�o�W�� */
  #endif                                                                /* JEMFHOUKI */
#else                                                                   /* �y�G�}OT���ٌ���L�z */
volatile const u1 u1s_emfng_ST1RTO = (u1)(((2.)/(8./256.))+0.5);        /* m=emfng,lsb=8/256,ofs=,unit=�{ :����޽��Ď�EM�������َ��Ή񐔔���l�Z�o�W�� */
volatile const u1 u1s_emfng_ST2RTO = (u1)(((2.)/(8./256.))+0.5);        /* m=emfng,lsb=8/256,ofs=,unit=�{ :ίĽ��Ď�EM�������َ��Ή񐔔���l�Z�o�W�� */
#endif                                                                  /* JEMFOTLV */

volatile const u1 u1s_emfng_KMFK = (u1)(((0.7)/(2./256.))+0.5);         /* m=emfng,lsb=2/256,ofs=,unit=�{ :DTC�o�͋C������W�� */
volatile const u1 u1s_emfng_KCDTMFWA = (u1)(((1.)/(8./256.))+0.5);      /* m=emfng,lsb=8/256,ofs=,unit=�{ :EM��������p���H�������Z�W�� */
volatile const u1 u1s_emfng_KCDTMFAOTB = (u1)(((1.)/(8./256.))+0.5);    /* m=emfng,lsb=8/256,ofs=,unit=�{ :�G�}OT����p���H�������Z�W��(��ݸ��) */
volatile const u2 u2s_emfng_KLEVEL3 = (u2)(((1.)/(4./256.))+0.5);       /* m=emfng,lsb=4/256,ofs=,unit=�{ :LEVEL3�v�����̎��Ή񐔔��f�W�� */

#if (JEEFI == u1g_EJCC_DUAL) && (JEHIPFI_E == u1g_EJCC_USE)             /* �y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z */
volatile const u1 u1s_emfng_MFDDI = (u1)(((85.)/(1.))+0.5);             /* m=emfng,lsb=1,ofs=,unit=�� :DI�ُ팟�o���Ή� */
volatile const u1 u1s_emfng_MFDPFI = (u1)(((85.)/(1.))+0.5);            /* m=emfng,lsb=1,ofs=,unit=�� :PFI�ُ팟�o���Ή� */
#endif                                                                  /* JEEFI JEHIPFI_E */

#if JEMFOTLV == u1g_EJCC_NOT_USE                                        /* �y�G�}OT���ٌ��薳�z */
  #if JEMFHOUKI == u1g_EJCC_USAMF                                       /* �y�G�}OT���ٌ��薳�zAND�y�ΕĖ@�K�z */
volatile const s2 s2s_emfng_THW = s2g_ELSB_THW(95.);                    /* m=emfng,lsb=160/256,ofs=,unit=�� :ίĽ��Ĕ��萅�� */
volatile const s2 s2s_emfng_THA = s2g_ELSB_THW(75.);                    /* m=emfng,lsb=160/256,ofs=,unit=�� :ίĽ��Ĕ���z�C�� */

  #else                                                                 /* �y�G�}OT���ٌ��薳�zAND�y�ΕĖ@�K�ȊO�z */
volatile const s2 s2s_emfng_THW = s2g_ELSB_THW(90.);                    /* m=emfng,lsb=160/256,ofs=,unit=�� :ίĽ��Ĕ��萅�� */
volatile const s2 s2s_emfng_THA = s2g_ELSB_THW(50.);                    /* m=emfng,lsb=160/256,ofs=,unit=�� :ίĽ��Ĕ���z�C�� */
  #endif                                                                /* JEMFHOUKI */
#else                                                                   /* �y�G�}OT���ٌ���L�z */
volatile const s2 s2s_emfng_THW = s2g_S2MIN;                            /* m=emfng,lsb=160/256,ofs=,unit=�� :ίĽ��Ĕ��萅�� */
volatile const s2 s2s_emfng_THA = s2g_S2MIN;                            /* m=emfng,lsb=160/256,ofs=,unit=�� :ίĽ��Ĕ���z�C�� */
#endif                                                                  /* JEMFOTLV */

/* emfng_THW�Aemfng_THA �͖@�K�v���̂��߁A�ύX���鎞��OBD�O���[�v�܂ŘA�����邱�ƁB */
/* CARB�F�̒l�� emfng_THW��95���Aemfng_THA��65�� */
/* �y�R��OBD�L�z�̏ꍇ��emfng_THW�Aemfng_THA��efkgd_THW�Aefkgd_THA�Ƃ��ꂼ�ꓯ���l�Ƃ��邱�ƁB */

#if JEMFHOUKI == u1g_EJCC_USAMF                                         /* �y�ΕĖ@�K�z */
volatile const s2 s2s_emfng_THWCSTL = s2g_ELSB_THW(-40.);               /* m=emfng,lsb=160/256,ofs=,unit=�� :����޽��Ĕ��萅�� */
volatile const s2 s2s_emfng_THWCSTH = s2g_ELSB_THW(-40.);               /* m=emfng,lsb=160/256,ofs=,unit=�� :����޽��Ĕ��萅�� */
volatile const s2 s2s_emfng_THACST = s2g_ELSB_THW(-40.);                /* m=emfng,lsb=160/256,ofs=,unit=�� :����޽��Ĕ���z�C�� */
volatile const u1 u1s_emfng_CJEMREV = (u1)(((1.)/(1.))+0.5);            /* m=emfng,lsb=1,ofs=,unit=�� :EM�������َ��Ή񐔐��グ1000rev�� */

#else                                                                   /* �y�ΕĖ@�K�ȊO�z */
volatile const s2 s2s_emfng_THWCSTL = s2g_ELSB_THW(10.);                /* m=emfng,lsb=160/256,ofs=,unit=�� :����޽��Ĕ��萅�� */
volatile const s2 s2s_emfng_THWCSTH = s2g_ELSB_THW(60.);                /* m=emfng,lsb=160/256,ofs=,unit=�� :����޽��Ĕ��萅�� */
volatile const s2 s2s_emfng_THACST = s2g_ELSB_THW(10.);                 /* m=emfng,lsb=160/256,ofs=,unit=�� :����޽��Ĕ���z�C�� */
volatile const u1 u1s_emfng_CJEMREV = (u1)(((2.)/(1.))+0.5);            /* m=emfng,lsb=1,ofs=,unit=�� :EM�������َ��Ή񐔐��グ1000rev�� */
#endif                                                                  /* JEMFHOUKI */

volatile const s2 s2s_emfng_KCDMFWL = s2g_glround((0.5)/(2./64./256.)); /* m=emfng,lsb=2/64/256,ofs=,unit= :ýČ��ʏo�͗p �Ό��C�����ζ������Z����l */
volatile const u2 u2g_emfng_ECDMFAEMTV_MI = u2g_U2MIN;                  /* m=emfng,lsb=1,ofs=,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�S�C��)�����l */
volatile const u2 u2g_emfng_ECDMFAEMMXTL_MI = u2g_U2MIN;                /* m=emfng,lsb=1,ofs=,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�S�C��)�����l */
volatile const u2 u2g_emfng_ECDMFAEMMNTL_MI = u2g_U2MIN;                /* m=emfng,lsb=1,ofs=,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�S�C��)�����l */
volatile const u2 u2g_emfng_ECDMFEMTV_MI = u2g_U2MIN;                   /* m=emfng,lsb=1,ofs=,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�C����)�����l */
volatile const u2 u2g_emfng_ECDMFEMMXTL_MI = u2g_U2MIN;                 /* m=emfng,lsb=1,ofs=,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�C����)�����l */
volatile const u2 u2g_emfng_ECDMFEMMNTL_MI = u2g_U2MIN;                 /* m=emfng,lsb=1,ofs=,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�C����)�����l */
volatile const u2 u2g_emfng_ECDMFAAVTV_MI = u2g_U2MIN;                  /* m=emfng,lsb=1,ofs=,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�S�C��)�����l */
volatile const u2 u2g_emfng_ECDMFAAVMXTL_MI = u2g_U2MIN;                /* m=emfng,lsb=1,ofs=,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ�������l(�S�C��)�����l */
volatile const u2 u2g_emfng_ECDMFAAVMNTL_MI = u2g_U2MIN;                /* m=emfng,lsb=1,ofs=,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ��������l(�S�C��)�����l */
volatile const u2 u2g_emfng_ECDMFAVTV_MI = u2g_U2MIN;                   /* m=emfng,lsb=1,ofs=,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�C����)�����l */
volatile const u2 u2g_emfng_ECDMFAVMXTL_MI = u2g_U2MIN;                 /* m=emfng,lsb=1,ofs=,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ�������l(�C����)�����l */
volatile const u2 u2g_emfng_ECDMFAVMNTL_MI = u2g_U2MIN;                 /* m=emfng,lsb=1,ofs=,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ��������l(�C����)�����l */
volatile const u1 u1g_emfng_EXRCDMFI_MI = (u1)(OFF);                    /* m=emfng,lsb=,ofs=,unit= :EWMA���ζ����v�Z�����t���O�����l */

#if JEOOBD == u1g_EJCC_USE                                              /* �y�s�꒲���L�z */
volatile const u1 u1s_emfng_MFLOW = (u1)(((0.15)/(2./256.))+0.5);       /* m=emfng,lsb=2/256,ofs=,unit= :���Ή񐔏�����W�� */
volatile const u1 u1s_emfng_MFMID = (u1)(((0.3)/(2./256.))+0.5);        /* m=emfng,lsb=2/256,ofs=,unit= :���Ή񐔒�����W�� */
volatile const u1 u1s_emfng_MFHI = (u1)(((0.5)/(2./256.))+0.5);         /* m=emfng,lsb=2/256,ofs=,unit= :���Ή񐔑唻��W�� */
volatile const u2 u2g_emfng_EOCMFNL_MI = u2g_U2MIN;                     /* m=emfng,lsb=1,ofs=,unit=�� :���Ή�(��)�̕p�x �����l */
volatile const u2 u2g_emfng_EOCMFNM_MI = u2g_U2MIN;                     /* m=emfng,lsb=1,ofs=,unit=�� :���Ή�(��)�̕p�x �����l */
volatile const u2 u2g_emfng_EOCMFNH_MI = u2g_U2MIN;                     /* m=emfng,lsb=1,ofs=,unit=�� :���Ή�(��)�̕p�x �����l */
volatile const u2 u2g_emfng_EOCMFMLTL_MI = u2g_U2MIN;                   /* m=emfng,lsb=1,ofs=,unit=�� :�Ό��C�����Ή�(��)�̕p�x �����l */
volatile const u2 u2g_emfng_EOCMFMLTH_MI = u2g_U2MIN;                   /* m=emfng,lsb=1,ofs=,unit=�� :�Ό��C�����Ή�(��)�̕p�x �����l */
volatile const u1 u1g_emfng_EONEMFMLT_MI = u1g_U1MIN;                   /* m=emfng,lsb=200/8,ofs=,unit=rpm :�Ό��C�����Ύ��̴ݼ�݉�]�Ȃ܂��l �����l */
volatile const u1 u1g_emfng_EOCDMFAE2MX_MI = u1g_U1MIN;                 /* m=emfng,lsb=1,ofs=,unit=�� :1000rev�����ζ����̍ő�l �����l */
volatile const u1 u1g_emfng_EOCJREVEM_MI = u1g_U1MIN;                   /* m=emfng,lsb=1,ofs=,unit=�� :�ő厸�ζ����X�V����1000rev�� �����l */
volatile const s1 s1g_emfng_EOTHWEM_MI = s1g_glround((0.)/(160./128.)); /* m=emfng,lsb=160/128,ofs=,unit=�� :�ő厸�ζ����X�V���̐��� �����l */
volatile const s1 s1g_emfng_EOTHAEM_MI = s1g_glround((0.)/(160./128.)); /* m=emfng,lsb=160/128,ofs=,unit=�� :�ő厸�ζ����X�V���̋z�C�� �����l */
volatile const u1 u1g_emfng_EOCDMFEM2MX_MI = u1g_U1MIN;                 /* m=emfng,lsb=1,ofs=,unit=�� :�ő厸�ζ����X�V���̋C���ʎ��ζ��� �����l */
volatile const u1 u1g_emfng_EOSPDEMAV_MI = u1g_U1MIN;                   /* m=emfng,lsb=256/256,ofs=,unit=km/h :���ζ��Ď��̕��ώԑ� �����l */
volatile const u1 u1g_emfng_EONEEMAV_MI = u1g_U1MIN;                    /* m=emfng,lsb=12800/256,ofs=,unit=rpm :���ζ��Ď��̕��ϴݼ�݉�]�� �����l */
volatile const u1 u1g_emfng_EOKLSMEMAV_MI = u1g_U1MIN;                  /* m=emfng,lsb=320/256,ofs=,unit=% :���ζ��Ď��̕��ϕ��� �����l */
volatile const u1 u1g_emfng_EOCJMFNEEMI_MI = u1g_U1MIN;                 /* m=emfng,lsb=1,ofs=,unit=�� :���ζ��Ď��̱����Ӱ�މ� �����l */
volatile const u1 u1g_emfng_EOCJMFNEEML_MI = u1g_U1MIN;                 /* m=emfng,lsb=1,ofs=,unit=�� :���ζ��Ď���۰Ӱ�މ� �����l */
volatile const u1 u1g_emfng_EOCJMFNEEMH_MI = u1g_U1MIN;                 /* m=emfng,lsb=1,ofs=,unit=�� :���ζ��Ď���ʲӰ�މ� �����l */
volatile const u1 u1g_emfng_EOCDMFAOTMX_MI = u1g_U1MIN;                 /* m=emfng,lsb=1,ofs=,unit=�� :200rev���ő嶳���ő�l  �����l */
volatile const u1 u1g_emfng_EOCJREVOT_MI = u1g_U1MIN;                   /* m=emfng,lsb=1,ofs=,unit=�� :�ő厸�ζ����X�V����1000rev�� �����l */
volatile const s1 s1g_emfng_EOTHWOT_MI = s1g_glround((0.)/(160./128.)); /* m=emfng,lsb=160/128,ofs=,unit=�� :�ő厸�ζ����X�V���̐��� �����l */
volatile const s1 s1g_emfng_EOTHAOT_MI = s1g_glround((0.)/(160./128.)); /* m=emfng,lsb=160/128,ofs=,unit=�� :�ő厸�ζ����X�V���̋z�C�� �����l */
#endif                                                                  /* JEOOBD */

/* $$$�K���萔_�W��_v4.11 */

/*-------------------------------------------------------------------*/
/* �K���}�b�v                                                        */
/*-------------------------------------------------------------------*/
/* $$$�K���}�b�v_�W��_v4.11 */
/*---- emfng_emfrtot_map -------------------------------------------*/
#define X(x) (s2g_ELSB_KL(x))                                           /* m=emfng,lsb=320/64/256,ofs=,unit=% :eklset_eklsm */
#define Y(y) (s2g_ELSB_NE(y))                                           /* m=emfng,lsb=12800/64/256,ofs=,unit=rpm :ene_ene */
#define Z(z) (s2g_glround((z)/(256./128./256.)))                        /* m=emfng,lsb=256/128/256,ofs=,unit=% : */
volatile const s2 s2g_emfng_emfrtot_map[] =
{
    6,7,0,
              X(15.),   X(30.),   X(40.),   X(55.),   X(70.),   X(85.),
    Y(800.),  Z(50.),   Z(50.),   Z(47.06), Z(44.44), Z(32.),   Z(25.81),
    Y(1600.), Z(40.),   Z(32.),   Z(29.63), Z(28.57), Z(25.),   Z(24.24),
    Y(2400.), Z(36.36), Z(30.77), Z(26.67), Z(22.86), Z(18.18), Z(17.02),
    Y(3200.), Z(32.),   Z(21.05), Z(18.18), Z(14.04), Z(10.),   Z(11.94),
    Y(4000.), Z(24.24), Z(17.02), Z(14.04), Z(14.04), Z(11.94), Z(11.94),
    Y(4800.), Z(21.05), Z(15.09), Z(12.9),  Z(12.9),  Z(14.04), Z(16.),
    Y(5600.), Z(18.18), Z(11.94), Z(11.94), Z(14.04), Z(18.18), Z(18.18)
};
#undef X
#undef Y
#undef Z

#if JENGPF_E != u1g_EJCC_NOT_USE                                        /* �yGPF�L�z */
/*---- emfng_emfrtotgpf_map ----------------------------------------*/
#define X(x) (s2g_ELSB_KL(x))                                           /* m=emfng,lsb=320/64/256,ofs=,unit=% :eklset_eklsm */
#define Y(y) (s2g_ELSB_NE(y))                                           /* m=emfng,lsb=12800/64/256,ofs=,unit=rpm :ene_ene */
#define Z(z) (s2g_glround((z)/(256./128./256.)))                        /* m=emfng,lsb=256/128/256,ofs=,unit=% : */
volatile const s2 s2g_emfng_emfrtotgpf_map[] =                          /* �yGPF�L�z */
{
    6,7,0,
              X(15.),   X(30.),   X(40.),   X(55.),   X(70.),   X(85.),
    Y(800.),  Z(50.),   Z(50.),   Z(47.06), Z(44.44), Z(32.),   Z(25.81),
    Y(1600.), Z(40.),   Z(32.),   Z(29.63), Z(28.57), Z(25.),   Z(24.24),
    Y(2400.), Z(36.36), Z(30.77), Z(26.67), Z(22.86), Z(18.18), Z(17.02),
    Y(3200.), Z(32.),   Z(21.05), Z(18.18), Z(14.04), Z(10.),   Z(11.94),
    Y(4000.), Z(24.24), Z(17.02), Z(14.04), Z(14.04), Z(11.94), Z(11.94),
    Y(4800.), Z(21.05), Z(15.09), Z(12.9),  Z(12.9),  Z(14.04), Z(16.),
    Y(5600.), Z(18.18), Z(11.94), Z(11.94), Z(14.04), Z(18.18), Z(18.18)
};
#undef X
#undef Y
#undef Z

#endif                                                                  /* JENGPF_E */

#if JEEGTYPE == u1g_EJCC_V6CYL                                          /* �yV6�z */
/*---- emfng_mfcylbnk_tbl ------------------------------------------*/
#define X(x) ((u1)(((x)/(1.))+0.5))                                     /* m=emfng,lsb=1,ofs=,unit= : */
volatile const u1 u1s_emfng_mfcylbnk_tbl[] =                            /* �yV6�z */
{
    /* t_mfcyl    0      1      2      3      4      5     */
    /* t_bnk */   X(0.), X(1.), X(0.), X(1.), X(0.), X(1.)
};
#undef X

/*---- emfng_mfwcyl_tbl --------------------------------------------*/
#define X(x) ((u1)(x))                                                  /* m=emfng,lsb=,ofs=,unit= : */
volatile const u1 u1g_emfng_mfwcyl_tbl[] =                              /* �yV6�z */
{
    /* t_cylw     0            1            2           */
    /* t_bnk */   (u1)(0x24U), (u1)(0x09U), (u1)(0x12U)
};
#undef X

#endif                                                                  /* JEEGTYPE */

/* $$$�K���}�b�v_�W��_v4.11 */

/**** End of File ****************************************************/
