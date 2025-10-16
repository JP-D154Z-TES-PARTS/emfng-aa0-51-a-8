/* emfng-pa000-5000-a-M4 */
/*********************************************************************/
/*  Copyright Toyota Motor Corporation                               */
/*********************************************************************/
/*  Version: aa0-51-a (Logic implementation)                         */
/*********************************************************************/

/*********************************************************************/
/* �I�u�W�F�N�g�� |  ���Ό��o�ُ픻�蕔                              */
/* ���ӎ���       | �y����OBD�L�zAND(�y4�C���zOR�y6�C���z)           */
/*-------------------------------------------------------------------*/
/*     �ʕύX���� �i�ʕύX���͈ȉ��ɕύX���A���e���L�����邱�Ɓj */
/*********************************************************************/

/*-------------------------------------------------------------------*/
/* �w�b�_�t�@�C���̃C���N���[�h                                      */
/*-------------------------------------------------------------------*/
#include <../inc/common.h>
#include <../inc/gllib.h>
#include <engsrc/espc/ejcc.h>           /* JEEFI,JEEGTYPE,JEHIPFI_E,JEMAT_OBD2,JEMFFC */
                                        /* JEMFHOUKI,JEMFMETHOD_D,u1g_EJCC_TIME_D,u1g_EJCC_OMEGA_D */
                                        /* JENCYL,JEOOBD,u1g_EJCC_NCYL,JEMFDTC_D */
                                        /* JETCORE_D,JEOBDUDS_D,JERLOK,JENGPF_E */
                                        /* u1g_ejcc_NCYL,u1g_EJCC_DUAL,u1g_EJCC_6CYL,u1g_EJCC_4CYL,u1g_EJCC_USAMF,u1g_EJCC_NOT_USAMF,u1g_EJCC_V6CYL,u1g_EJCC_L6CYL */
#include <engsrc/inc/elsb.h>
#include <engsrc/inc/elib.h>

#include <obd/wfh/wsentivchg.h>         /* u1g_wsentivchg_state,u1g_WSENTIVCHG_IUE,u1g_WSENTIVCHG_LVL2 */
#include <obd/wfh/wdiaginfclr.h>        /* big_wdiaginfclr_xreqclr */
#if JEOBDUDS_D == u1g_EJCC_USE          /*�yOBDonUDS�Ή��L�z*/
#include <obd/wfh/wpsajdg.h>            /* big_wpsajdg_xpsa */
#endif
#if JEMAT_OBD2 == u1g_EJCC_NOT_USE      /*�yOBD2�K�����z*/
#include <obd/wbp/wobd2msk.h>           /* big_wobd2msk_xmfKwp */
#endif
#if JEMFDTC_D == u1g_EJCC_USE           /*�y����OBD DTC�L�z*/
#include <obd/wfd/wmf_fdi.h>            /* big_wmf_fdi_xem_lstpnd,big_wmf_fdi_xot_lstpnd,big_wmf_fdi_xot_warning */
                                        /* big_wmf_fdi_xem_warning,vdg_wmf_fdi_ot_fald_u1(),vdg_wmf_fdi_em_fald_u1(),vdg_wmf_fdi_ot_excmf() */
                                        /* vdg_wmf_fdi_em_excmf(),vdg_wmf_fdi_mil_blink_u1(),vdg_wmf_fdi_ot_imdf(),vdg_wmf_fdi_ot_imdnf() */
                                        /* vdg_wmf_fdi_pas_u2u1(),u1g_WMF_FDI_OUTOF_FTPCYCLE,u1g_WMF_FDI_DURING_FTPCYCLE */
                                        /* u1g_WMF_FDI_WITHIN_FIRST1000RPM,u1g_WMF_FDI_AFTER_FIRST1000RPM,u2g_WMF_FDI_ID_OT */
                                        /* big_wmf_fdi_xot_pnd,big_wmf_fdi_xem_pnd,vdg_wmf_fdi_ot_excmf_u2u1(),vdg_wmf_fdi_em_excmf_u2u1(),u2g_WMF_FDI_ID_EM */
#endif
#if ( JETCORE_D == u1g_EJCC_USE ) && ( JEOBDUDS_D == u1g_EJCC_NOT_USE )  /*�yt-CORE�Ή��L�zAND�yOBDonUDS�Ή����z*/
#include <obd/wspc/wtcif.h>             /* u1g_wtcif_dem_setdtr_u2s4s4s4u1(),u2g_WTCIF_DEM_DTR_ECDMFAEM,u1g_WTCIF_DEM_DTR_CTL_NORMAL */
                                        /* u2g_WTCIF_DEM_DTR_ECDMFEM1,u2g_WTCIF_DEM_DTR_ECDMFEM2,u2g_WTCIF_DEM_DTR_ECDMFEM3 */
                                        /* u2g_WTCIF_DEM_DTR_ECDMFEM4,u2g_WTCIF_DEM_DTR_ECDMFEM5,u2g_WTCIF_DEM_DTR_ECDMFEM6 */
                                        /* u2g_WTCIF_DEM_DTR_ECDMFAV1,u2g_WTCIF_DEM_DTR_ECDMFAV2,u2g_WTCIF_DEM_DTR_ECDMFAV3 */
                                        /* u2g_WTCIF_DEM_DTR_ECDMFAV4,u2g_WTCIF_DEM_DTR_ECDMFAV5,u2g_WTCIF_DEM_DTR_ECDMFAV6,u2g_WTCIF_DEM_DTR_ECDMFAAV */
#endif
#if JENGPF_E != u1g_EJCC_NOT_USE        /*�yGPF�L�z*/
#include <engsrc/efunc/efuncin/egpfrgcnd/egpfrgcnd.h>              /* u1g_egpfrgcnd_exgpfrgsrv */
#include <engsrc/efunc/eemi/egpf/egpfhtum/egpfhtum.h>              /* u1g_egpfhtum_exdth,u1g_egpfhtum_exeff */
 #if JERLOK == u1g_EJCC_USE             /*�yد�ذ݉^�]�z*/
#include <engsrc/efunc/eemi/egpf/egpfrgum.h>                       /* u1g_egpfrgum_exrgact */
 #endif
#endif
#include <engsrc/eserv/emem/ememctr.h>              /* s4g_ememctr_write(),s4g_ememctr_read() */
                                                    /* u2g_EMFNG_EONEMFMLT_U1_ID,u2g_EMFNG_EXRCDMF_U1_ID */
                                                    /* u2g_EMFNG_EOCDMFAE2MX_U1_ID,u2g_EMFNG_EOCJREVEM_U1_ID */
                                                    /* u2g_EMFNG_EOTHWEM_S1_ID,u2g_EMFNG_EOTHAEM_S1_ID */
                                                    /* u2g_EMFNG_EOCDMFEM2MX1_U1_ID,u2g_EMFNG_EOCDMFEM2MX2_U1_ID */
                                                    /* u2g_EMFNG_EOCDMFEM2MX3_U1_ID,u2g_EMFNG_EOCDMFEM2MX4_U1_ID */
                                                    /* u2g_EMFNG_EOCDMFEM2MX5_U1_ID,u2g_EMFNG_EOCDMFEM2MX6_U1_ID */
                                                    /* u2g_EMFNG_EOSPDEMAV_U1_ID,u2g_EMFNG_EONEEMAV_U1_ID */
                                                    /* u2g_EMFNG_EOKLSMEMAV_U1_ID,u2g_EMFNG_EOCJMFNEEMI_U1_ID */
                                                    /* u2g_EMFNG_EOCJMFNEEML_U1_ID,u2g_EMFNG_EOCJMFNEEMH_U1_ID */
                                                    /* u2g_EMFNG_EOCDMFAOTMX_U1_ID,u2g_EMFNG_EOCJREVOT_U1_ID */
                                                    /* u2g_EMFNG_EOTHWOT_S1_ID,u2g_EMFNG_EOTHAOT_S1_ID */
                                                    /* u2g_EMFNG_EOCMFNL_U2_ID,u2g_EMFNG_EOCMFNM_U2_ID */
                                                    /* u2g_EMFNG_EOCMFNH_U2_ID,u2g_EMFNG_EOCMFMLTL_U2_ID */
                                                    /* u2g_EMFNG_EOCMFMLTH_U2_ID,u2g_EMFNG_ECDMFAEMMXTL_U2_ID */
                                                    /* u2g_EMFNG_ECDMFEMMXTL1_U2_ID,u2g_EMFNG_ECDMFEMMXTL2_U2_ID */
                                                    /* u2g_EMFNG_ECDMFEMMXTL3_U2_ID,u2g_EMFNG_ECDMFEMMXTL4_U2_ID */
                                                    /* u2g_EMFNG_ECDMFEMMXTL5_U2_ID,u2g_EMFNG_ECDMFEMMXTL6_U2_ID */
                                                    /* u2g_EMFNG_ECDMFAAVMXTL_U2_ID,u2g_EMFNG_ECDMFAVMXTL1_U2_ID */
                                                    /* u2g_EMFNG_ECDMFAVMXTL2_U2_ID,u2g_EMFNG_ECDMFAVMXTL3_U2_ID */
                                                    /* u2g_EMFNG_ECDMFAVMXTL4_U2_ID,u2g_EMFNG_ECDMFAVMXTL5_U2_ID */
                                                    /* u2g_EMFNG_ECDMFAVMXTL6_U2_ID,u2g_EMFNG_ECDMFAEMTV_U2_ID */
                                                    /* u2g_EMFNG_ECDMFAEMMNTL_U2_ID,u2g_EMFNG_ECDMFAAVTV_U2_ID */
                                                    /* u2g_EMFNG_ECDMFAAVMNTL_U2_ID,u2g_EMFNG_ECDMFEMTV1_U2_ID */
                                                    /* u2g_EMFNG_ECDMFEMTV2_U2_ID,u2g_EMFNG_ECDMFEMTV3_U2_ID */
                                                    /* u2g_EMFNG_ECDMFEMTV4_U2_ID,u2g_EMFNG_ECDMFEMTV5_U2_ID */
                                                    /* u2g_EMFNG_ECDMFEMTV6_U2_ID,u2g_EMFNG_ECDMFEMMNTL1_U2_ID */
                                                    /* u2g_EMFNG_ECDMFEMMNTL2_U2_ID,u2g_EMFNG_ECDMFEMMNTL3_U2_ID */
                                                    /* u2g_EMFNG_ECDMFEMMNTL4_U2_ID,u2g_EMFNG_ECDMFEMMNTL5_U2_ID */
                                                    /* u2g_EMFNG_ECDMFEMMNTL6_U2_ID,u2g_EMFNG_ECDMFAVTV1_U2_ID */
                                                    /* u2g_EMFNG_ECDMFAVTV2_U2_ID,u2g_EMFNG_ECDMFAVTV3_U2_ID */
                                                    /* u2g_EMFNG_ECDMFAVTV4_U2_ID,u2g_EMFNG_ECDMFAVTV5_U2_ID */
                                                    /* u2g_EMFNG_ECDMFAVTV6_U2_ID,u2g_EMFNG_ECDMFAVMNTL1_U2_ID */
                                                    /* u2g_EMFNG_ECDMFAVMNTL2_U2_ID,u2g_EMFNG_ECDMFAVMNTL3_U2_ID */
                                                    /* u2g_EMFNG_ECDMFAVMNTL4_U2_ID,u2g_EMFNG_ECDMFAVMNTL5_U2_ID */
                                                    /* u2g_EMFNG_ECDMFAVMNTL6_U2_ID */
#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE ) /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
#include <engsrc/eactmedi/einj/eminj.h>             /* s2g_eminj_ekpfi */
#endif
#include <engsrc/estate/esin/ene.h>                 /* s2g_ene_ene */
#include <engsrc/estate/esin/espd.h>                /* s2g_espd_espd */
#include <engsrc/estate/esin/etha.h>                /* s2g_etha_etha */
#include <engsrc/estate/estepin/exst.h>             /* u1g_exst_exastnrm */
#include <engsrc/etranfwd/etemp/ethw.h>             /* s2g_ethw_ethw */
#include <engsrc/espc/eengspc.h>                    /* u1g_eengspc_ewcnvt_tbl[] */
#include <eng/ekl/eklset.h>                         /* s2g_eklset_eklsm */

#if ( JEOOBD == u1g_EJCC_USE ) && ( JENCYL == u1g_EJCC_6CYL )   /*�y�s�꒲���L�zAND�y6�C���z*/
#include <eng/eobd/eobdsm.h>            /* s2g_eobdsm_enejsm */
#endif

#include <eng/emf/emfcc.h>              /* s2g_emfcc_edltmaxlh,s2g_emfcc_edltmaxhh */
                                        /* s2g_emfcc_ewmaxl,s2g_emfcc_ewmaxh */
#include <eng/emf/emfccrnk.h>           /* u1g_EMFCCRNK_DLTMFL_TIMMING,s2g_emfccrnk_edltmflxh[] */
                                        /* u1g_EMFCCRNK_DDTCRX_TIMMING,s2g_emfccrnk_eddtcrxh[] */
                                        /* s2g_emfccrnk_ewmfl[],s2g_emfccrnk_ewmfh[],s2g_emfccrnk_ewmfhp[] */
#include <eng/emf/emfcnt.h>             /* u1g_EMFCNT_NOT,big_emfcnt_exptnup,s2g_emfcnt_MFSPD */
                                        /* u1g_EMFCNT_LOW,u1g_EMFCNT_HIGH,u1g_EMFCNT_OPPS */
                                        /* u1g_EMFCNT_MLT,u1g_EMFCNT_CYL() */
#include <eng/emf/emfinftp.h>           /* big_emfinftp_exinftp */
#include <eng/emf/emfne.h>              /* u1g_emfne_ejmfne,u1g_EMFNE_REV_IDLE1,u1g_EMFNE_REV_IDLE2 */
                                        /* u1g_EMFNE_REV_LOW,u1g_EMFNE_REV_HIGH */
#include <eng/emf/emfok.h>              /* s2g_emfok_NGDI,s2g_emfok_NGPFI,emfok_roughcnt() */
                                        /* emfok_mfneld_set(),emfok_mfareacnt_ann_u1u1() */
                                        /* emfok_mfneld_ann(),emfok_mfcmodclr() */

#if JEMFFC == u1g_EJCC_USE              /*�y�G�}OT���Έُ펞FC�L�z*/
#include <eng/emf/emffc.h>              /* u1g_emffc_exfcbi */
#endif

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

#if !defined JEMAT_OBD2
#error "JEMAT_OBD2 is undeclared"
#endif

#if !defined JEMFFC
#error "JEMFFC is undeclared"
#endif

#if !defined JEMFHOUKI
#error "JEMFHOUKI is undeclared"
#endif

#if !defined JEMFMETHOD_D
#error "JEMFMETHOD_D is undeclared"
#endif

#if !defined u1g_EJCC_TIME_D
#error "u1g_EJCC_TIME_D is undeclared"
#endif

#if !defined u1g_EJCC_OMEGA_D
#error "u1g_EJCC_OMEGA_D is undeclared"
#endif

#if !defined JENCYL
#error "JENCYL is undeclared"
#endif

#if !defined JEOOBD
#error "JEOOBD is undeclared"
#endif

#if !defined u1g_EJCC_NCYL
#error "u1g_EJCC_NCYL is undeclared"
#endif

#if !defined JEMFDTC_D
#error "JEMFDTC_D is undeclared"
#endif

#if !defined JETCORE_D
#error "JETCORE_D is undeclared"
#endif

#if !defined JEOBDUDS_D
#error "JEOBDUDS_D is undeclared"
#endif

#if !defined JERLOK
#error "JERLOK is undeclared"
#endif

#if !defined JENGPF_E
#error "JENGPF_E is undeclared"
#endif

#if !defined u1g_EJCC_DUAL
#error "u1g_EJCC_DUAL is undeclared"
#endif

#if !defined u1g_EJCC_6CYL
#error "u1g_EJCC_6CYL is undeclared"
#endif

#if !defined u1g_EJCC_4CYL
#error "u1g_EJCC_4CYL is undeclared"
#endif

#if !defined u1g_EJCC_USAMF
#error "u1g_EJCC_USAMF is undeclared"
#endif

#if !defined u1g_EJCC_NOT_USAMF
#error "u1g_EJCC_NOT_USAMF is undeclared"
#endif

#if !defined u1g_EJCC_V6CYL
#error "u1g_EJCC_V6CYL is undeclared"
#endif

#if !defined u1g_EJCC_L6CYL
#error "u1g_EJCC_L6CYL is undeclared"
#endif

/*-------------------------------------------------------------------*/
/* �K���l                                                            */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* �^��`                                                            */
/*-------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* macro��`                                                           */
/*---------------------------------------------------------------------*/
/* $$$�}�N���萔_�W��_v4.11 */
#define u1s_EMFNG_MFSTOTI ((u1)(((173.)/(1.))+0.5))                     /* m=emfng,lsb=1,ofs=,unit=�� :����ْ��S�C�����Ή񐔔���l��� */

#if (JETCORE_D == u1g_EJCC_USE) && (JEOBDUDS_D == u1g_EJCC_USE)         /* �yt-CORE�Ή��L�zAND�yOBDonUDS�Ή��L�z */
#define u1s_EMFNG_CXMF1PAS ((u1)(((0.)/(1.))+0.5))                      /* m=emfng,lsb=1,ofs=,unit=�� :���f�B�l�X�p �G�}OT���Ή񐔔���l */
#define u1s_EMFNG_CXMFPAS ((u1)(((0.)/(1.))+0.5))                       /* m=emfng,lsb=1,ofs=,unit=�� :���f�B�l�X�p EM�������Ή񐔔���l */
#endif                                                                  /* JETCORE_D JEOBDUDS_D */

/* $$$�}�N���萔_�W��_v4.11 */

#define u1s_EMFNG_NCYLW      ((u1)(u1g_ejcc_NCYL >> 1))       /* �C���Q�� */

/*-------------------------------------------------------------------*/
/* �ϐ���`                                                          */
/*-------------------------------------------------------------------*/
/* �O���[�o���ϐ� */
/* emf���ɂ̂݌��J */
u2 u2g_emfng_ekldmfae;       /* m=emfng,lsb=1,unit=�� :EM�������َ��Δ���l */
u1 u1g_emfng_ecdmfaotbnk[2]; /* m=emfng,lsb=1,unit=�� :��ݸ�ʐG�}OT���َ��ζ��� */
                             /* 1�o���N�ł�2�o���N���̗̈���m�ۂ��� */
#if JEMFFC == u1g_EJCC_USE   /*�y�G�}OT���Έُ펞FC�L�z*/
u1 u1g_emfng_exdmffc;        /* m=emfng,lsb=1 :FC��߼�ݔ���p�G�}OT���وُ�ʒm�׸� */
#endif
u1 u1g_emfng_ecdmfaot;       /* m=emfng,lsb=1,unit=�� :�G�}OT���ّS�C�����ζ��� */
u2 u2g_emfng_ecdmfaoti;      /* m=emfng,lsb=1,unit=�� :����ْ��S�C�����ζ��� */
u2 u2g_emfng_ecdmfae2;       /* m=emfng,lsb=1,unit=�� :EM�������ّS�C�����ζ��� */
u1 u1g_emfng_ecdmfaem;       /* m=emfng,lsb=1,unit=�� :EM�������ّS�C�����ζ��� */
u2 u2g_emfng_ecjmfot;        /* m=emfng,lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev :�G�}OT���َ��Ό��o���¶��� */
u2 u2g_emfng_ecjmfoti;       /* m=emfng,lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev :�G�}OT���ٱ���َ����Ό��o���¶��� */
u2 u2g_emfng_ecjmfem;        /* m=emfng,lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev :EM�������َ��Ό��o���¶��� */
u2 u2g_emfng_ekldmfot;       /* m=emfng,lsb=1,unit=�� :�G�}OT���َ��Ή񐔔���l */
u2 u2g_emfng_ekldmfoth_mcr;  /* m=emfng,lsb=1,unit=�� :�G�}OT���َ��Ή񐔔���l(�v�Z�l) */
u2 u2g_emfng_eldmfaem_mcr;   /* m=emfng,lsb=1,unit=�� :EM�������َ��Ή񐔔���l(�v�Z�l) */

stflag8 stg_emfng_flag1;     /* m=emfng :�O���[�o���t���O�p�\����(16msl,65msl,drvclchg�^�C�~���O) */
#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
stflag8 stg_emfng_flag2;     /* m=emfng :�O���[�o���t���O�p�\����(65msl,drvclchg�^�C�~���O) */
#endif
#if JETCORE_D == u1g_EJCC_USE                           /*�yt-CORE�Ή��L�z*/
stflag8 stg_emfng_flag3;     /* m=emfng :�O���[�o���t���O�p�\����(65msl,drvclchg�^�C�~���O) */
#endif
u1 u1g_emfng_ecdmfem[u1g_EJCC_NCYL];    /* m=emfng,lsb=1,unit=�� :EM�������ًC���ʎ��ζ��� */
u2 u2g_emfng_ecdmfem2[u1g_EJCC_NCYL];   /* m=emfng,lsb=1,unit=�� :EM�������ًC���ʎ��ζ��� */
u1 u1g_emfng_ecdmfemi[u1g_EJCC_NCYL];   /* m=emfng,lsb=1,unit=�� :����ْ��C���ʎ��ζ��� */
u1 u1g_emfng_ecdtmf2;                   /* m=emfng,lsb=1,unit=�� :�G�}OT���ٔ���p���H���� */
u2 u2g_emfng_ecmfot;                    /* m=emfng,lsb=1,unit=�� :�����C�����ζ��� */
u1 u1g_emfng_ecdmfw[u1g_EJCC_NCYL/2];   /* m=emfng,lsb=1,unit=�� :�Ό��C�����ζ��� */

/* �X�^�e�B�b�N�ϐ� */
static u1 u1s_emfng_ecjpmf;    /* lsb=1,unit=�� :��۸۽���� */
static u2 u2s_emfng_ecdtmfwa;  /* lsb=1,unit=�� :EM�������ٔ���p���H���� */
static u1 u1s_emfng_ecxmf1;    /* lsb=1,unit=�� :�G�}OT���وُ팟�o�� */
static u1 u1s_emfng_ecxmf;     /* lsb=1,unit=�� :EM�������وُ팟�o�� */
static u1 u1s_emfng_ecjemrev;  /* lsb=1,unit=�� :�n����EM�������ٔ���� */
#if JEOOBD == u1g_EJCC_USE     /*�y�s�꒲���L�z*/
static s4 s4s_emfng_espdaem;   /* lsb=256/256,unit=km/h :1000rev�Ԃ̎ԑ��ݐϒl */
static s4 s4s_emfng_eneaem;    /* lsb=12800/64/256,unit=rpm :1000rev�Ԃ̴ݼ�݉�]���ݐϒl */
static s4 s4s_emfng_eklsmaem;  /* lsb=320/64/256,unit=% :1000rev�Ԃ̴ݼ�ݕ��חݐϒl */
static u1 u1s_emfng_ecjmfneemi; /* lsb=1,unit=�� :1000rev�Ԃ̱����Ӱ�މ� */
static u1 u1s_emfng_ecjmfneeml; /* lsb=1,unit=�� :1000rev�Ԃ�۰Ӱ�މ� */
static u1 u1s_emfng_ecjmfneemh; /* lsb=1,unit=�� :1000rev�Ԃ�ʲӰ�މ� */
#endif
#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
static u2 u2s_emfng_ecjmfdi;    /* lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev :DI���Ό��o���¶��� */
static u2 u2s_emfng_ecjmfpfi;   /* lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev :PFI���Ό��o���¶��� */
static u1 u1s_emfng_ecdmfdi[u1g_EJCC_NCYL];      /* lsb=1,unit=�� :�C����DI���ζ��� */
static u1 u1s_emfng_ecdmfpfi[u1g_EJCC_NCYL];     /* lsb=1,unit=�� :�C����PFI���ζ��� */
static u1 u1s_emfng_exdmfdim[u1g_EJCC_NCYL];     /* lsb=1 :�C����DI�ُ퐬���׸� */
static u1 u1s_emfng_exdmfpfim[u1g_EJCC_NCYL];    /* lsb=1 :�C����PFI�ُ퐬���׸� */
#endif
static u1 u1s_emfng_ekldmfw1_mcr; /* lsb=1,unit=�� :�Ό��C�����Ή񐔔��艺���l(�v�Z�l) */
#if JENCYL == u1g_EJCC_6CYL       /*�y6�C���z*/
static u1 u1s_emfng_ekldmfw2_mcr; /* lsb=1,unit=�� :�Ό��C�����Ή񐔔������l(�v�Z�l) */
#endif
static u2 u2s_emfng_eldmfst1_mcr; /* lsb=1,unit=�� :����޽��Ď�EM�������َ��Ή񐔔���l(�v�Z�l) */
static u2 u2s_emfng_eldmfst2_mcr; /* lsb=1,unit=�� :ίĽ��Ď�EM�������َ��Ή񐔔���l(�v�Z�l) */
static u2 u2s_emfng_emfk_mcr;     /* lsb=1,unit=�� :DTC�o�͋C������l(�v�Z�l) */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
static u2 u2s_emfng_ecmfnl_mcr;   /* lsb=1,unit=�� :���Ή񐔏��p�x�̔���l(�v�Z�l) */
static u2 u2s_emfng_ecmfnm_mcr;   /* lsb=1,unit=�� :���Ή񐔒��p�x�̔���l(�v�Z�l) */
static u2 u2s_emfng_ecmfnh_mcr;   /* lsb=1,unit=�� :���Ή񐔑�p�x�̔���l(�v�Z�l) */
#endif

static stflag8 sts_emfng_flagi1;   /* �N�����N�p������(ne30m)�^�C�~���O����t���O */
#define bis_emfng_exjmf          (sts_emfng_flagi1.b0)  /* :���΂̉������׸�(TDC) */
#define bis_emfng_exjtmf         (sts_emfng_flagi1.b1)  /* :���΂̉�����֎~�׸�(TDC) */
#define bis_emfng_exjtmf2        (sts_emfng_flagi1.b2)  /* :���΂̖{���苖���׸�(TDC) */
#define bis_emfng_exmfkpl        (sts_emfng_flagi1.b3)  /* :���]��Ԍp���׸�(TDC) */
#define bis_emfng_exmfkpm        (sts_emfng_flagi1.b4)  /* :����]��Ԍp���׸�(TDC) */
#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
#define bis_emfng_exjmfdi        (sts_emfng_flagi1.b5)  /* :ecjmfdi���ı��ߏ��������L���׸�(TDC) */
#define bis_emfng_exjmfpfi       (sts_emfng_flagi1.b6)  /* :ecjmfpfi���ı��ߏ��������L���׸�(TDC) */
#endif

static stflag8 sts_emfng_flagi2;   /* 65msl,drvclchg�^�C�~���O����t���O */
#define bis_emfng_exottd         (sts_emfng_flagi2.b0)  /* :�G�}OT���وُ팟�o���L���׸�(65msl,drvclchg) */
#define bis_emfng_excdmfwclr     (sts_emfng_flagi2.b1)  /* :ecdmfw[]�ر�v���׸�(65msl) */
#define bis_emfng_excdmfaot      (sts_emfng_flagi2.b2)  /* :�G�}OT���ζ����ɂ��G�}OT���萬���׸�(65msl) */
#define bis_emfng_excdmfem2clr   (sts_emfng_flagi2.b3)  /* :ecdmfem2[]�ر�v���׸�(65msl) */
#define bis_emfng_excdmfae2clr   (sts_emfng_flagi2.b4)  /* :ecdmfae2�ر�v���׸�(65msl) */
#define bis_emfng_excntmf        (sts_emfng_flagi2.b5)  /* :�د�ߌp���׸�(65msl,drvclchg) */
#define bis_emfng_exdmf1         (sts_emfng_flagi2.b6)  /* :�G�}OT���ٌ��ُ݈�L���׸�(65msl,drvclchg) */

static stflag8 sts_emfng_flagi3;   /* 65msl�^�C�~���O����t���O */
#define bis_emfng_exdmfot        (sts_emfng_flagi3.b0)  /* :�G�}OT���وُ픻���׸�(65msl) */
#define bis_emfng_exumfot        (sts_emfng_flagi3.b1)  /* :�G�}OT���ِ��픻��ۗ��׸�(65msl) */
#define bis_emfng_exhmfoton      (sts_emfng_flagi3.b2)  /* :�G�}OT�ɂ��MIL�_�ŗv���׸�(65msl) */
#define bis_emfng_exhmfotoff     (sts_emfng_flagi3.b3)  /* :�G�}OT�ɂ��MIL�_�ŷ�ݾٗv���׸�(65msl) */
#define bis_emfng_exdmfem        (sts_emfng_flagi3.b4)  /* :EM�������وُ팟�o�׸�(65msl) */
#define bis_emfng_exumfem        (sts_emfng_flagi3.b5)  /* :EM�������ِ��픻��ۗ��׸�(65msl) */

#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
static stflag8 sts_emfng_flagi4;   /* 65msl�^�C�~���O����t���O */
#define bis_emfng_exdmfdi        (sts_emfng_flagi4.b0)  /* :DI�ُ��׸�(65msl) */
#define bis_emfng_exumfdi        (sts_emfng_flagi4.b1)  /* :DI�ُ�ɂ�鐳�픻��ۗ��׸�(65msl) */
#define bis_emfng_exdmfpfi       (sts_emfng_flagi4.b2)  /* :PFI�ُ��׸�(65msl) */
#define bis_emfng_exumfpfi       (sts_emfng_flagi4.b3)  /* :PFI�ُ�ɂ�鐳�픻��ۗ��׸�(65msl) */
#define bis_emfng_excdmfdiclr    (sts_emfng_flagi4.b4)  /* :exdmfdim[]�ر�p�׸�(65msl) */
#define bis_emfng_excdmfpficlr   (sts_emfng_flagi4.b5)  /* :exdmfpfim[]�ر�p�׸�(65msl) */
#endif

#if JETCORE_D == u1g_EJCC_USE                           /*�yt-CORE�Ή��L�z*/
static stflag8 sts_emfng_flagi5;   /* 65msl�^�C�~���O����t���O */
#define bis_emfng_exoutftp       (sts_emfng_flagi5.b0)  /* :OT���΃��[�h�̈�O�����׸�(65msl) */
#define bis_emfng_exemfst        (sts_emfng_flagi5.b1)  /* :EM�������x������1000rev�����׸�(65msl) */
#endif

static s2 s2s_emfng_ecdmfaotb;  /* lsb=1,unit=�� :ecdmfaot-ecdtmf2�̃��b�`(MODE06�p) */
static s4 s4s_emfng_emfrtotsum; /* lsb=256/128/256,unit=% :�ώZ���Δ���l */
static u2 u2s_emfng_ecmfotcnt;  /* lsb=1,unit=�� :���ώZ�o�p�ώZ�� */
#if JEMFDTC_D == u1g_EJCC_USE  /*�y����OBD DTC�L�z*/
static u1 u1s_emfng_xem_lstpnd_Lch;     /* lsb=1 :�O��ײ��ݸ޻��ى��ُ���(EM)(�����iׯ��p) */
static u1 u1s_emfng_xot_lstpnd_Lch;     /* lsb=1 :�O��ײ��ݸ޻��ى��ُ���(OT)(�����iׯ��p) */
static u1 u1s_emfng_xot_warning_Lch;    /* lsb=1 :OT����MIL���(�����iׯ��p) */
static u1 u1s_emfng_xem_warning_Lch;    /* lsb=1 :EM����MIL���(�����iׯ��p) */
#endif
static u1 u1s_emfng_xreqclr_Lch;        /* lsb=1 :�޲��ޏ��ر�v���׸�(�����iׯ��p) */
static u1 u1s_emfng_state_Lch;          /* lsb=1 :���o���x���(�����iׯ��p) */
#if ( JEMFDTC_D == u1g_EJCC_USE ) && ( JETCORE_D == u1g_EJCC_USE ) && ( JEOBDUDS_D == u1g_EJCC_USE )    /*�y����OBD DTC�L�zAND�yt-CORE�Ή��L�zAND�yOBDonUDS�Ή��L�z*/
static u1 u1s_emfng_pas;                /* EM�������ٔ������ݸސ����׸�(65msl) */
#endif

/*-------------------------------------------------------------------*/
/* const data��`                                                    */
/*-------------------------------------------------------------------*/
#pragma ghs startdata
/* �o�b�N�A�b�vRAM-ID */
static volatile const u2 u2s_ECDMFEMTV_U2_ID[u1g_EJCC_NCYL] =  /* :�o�b�N�A�b�vRAM-ID */
{
     u2g_EMFNG_ECDMFEMTV1_U2_ID
    ,u2g_EMFNG_ECDMFEMTV2_U2_ID
    ,u2g_EMFNG_ECDMFEMTV3_U2_ID
    ,u2g_EMFNG_ECDMFEMTV4_U2_ID
#if JENCYL == u1g_EJCC_6CYL          /*�y6�C���z*/
    ,u2g_EMFNG_ECDMFEMTV5_U2_ID
    ,u2g_EMFNG_ECDMFEMTV6_U2_ID
#endif
};
static volatile const u2 u2s_ECDMFEMMNTL_U2_ID[u1g_EJCC_NCYL] =  /* :�o�b�N�A�b�vRAM-ID */
{
     u2g_EMFNG_ECDMFEMMNTL1_U2_ID
    ,u2g_EMFNG_ECDMFEMMNTL2_U2_ID
    ,u2g_EMFNG_ECDMFEMMNTL3_U2_ID
    ,u2g_EMFNG_ECDMFEMMNTL4_U2_ID
#if JENCYL == u1g_EJCC_6CYL          /*�y6�C���z*/
    ,u2g_EMFNG_ECDMFEMMNTL5_U2_ID
    ,u2g_EMFNG_ECDMFEMMNTL6_U2_ID
#endif
};
static volatile const u2 u2s_ECDMFEMMXTL_U2_ID[u1g_EJCC_NCYL] =  /* :�o�b�N�A�b�vRAM-ID */
{
     u2g_EMFNG_ECDMFEMMXTL1_U2_ID
    ,u2g_EMFNG_ECDMFEMMXTL2_U2_ID
    ,u2g_EMFNG_ECDMFEMMXTL3_U2_ID
    ,u2g_EMFNG_ECDMFEMMXTL4_U2_ID
#if JENCYL == u1g_EJCC_6CYL          /*�y6�C���z*/
    ,u2g_EMFNG_ECDMFEMMXTL5_U2_ID
    ,u2g_EMFNG_ECDMFEMMXTL6_U2_ID
#endif
};
static volatile const u2 u2s_ECDMFAVTV_U2_ID[u1g_EJCC_NCYL] =  /* :�o�b�N�A�b�vRAM-ID */
{
     u2g_EMFNG_ECDMFAVTV1_U2_ID
    ,u2g_EMFNG_ECDMFAVTV2_U2_ID
    ,u2g_EMFNG_ECDMFAVTV3_U2_ID
    ,u2g_EMFNG_ECDMFAVTV4_U2_ID
#if JENCYL == u1g_EJCC_6CYL          /*�y6�C���z*/
    ,u2g_EMFNG_ECDMFAVTV5_U2_ID
    ,u2g_EMFNG_ECDMFAVTV6_U2_ID
#endif
};
static volatile const u2 u2s_ECDMFAVMNTL_U2_ID[u1g_EJCC_NCYL] =  /* :�o�b�N�A�b�vRAM-ID */
{
     u2g_EMFNG_ECDMFAVMNTL1_U2_ID
    ,u2g_EMFNG_ECDMFAVMNTL2_U2_ID
    ,u2g_EMFNG_ECDMFAVMNTL3_U2_ID
    ,u2g_EMFNG_ECDMFAVMNTL4_U2_ID
#if JENCYL == u1g_EJCC_6CYL          /*�y6�C���z*/
    ,u2g_EMFNG_ECDMFAVMNTL5_U2_ID
    ,u2g_EMFNG_ECDMFAVMNTL6_U2_ID
#endif
};
static volatile const u2 u2s_ECDMFAVMXTL_U2_ID[u1g_EJCC_NCYL] =  /* :�o�b�N�A�b�vRAM-ID */
{
     u2g_EMFNG_ECDMFAVMXTL1_U2_ID
    ,u2g_EMFNG_ECDMFAVMXTL2_U2_ID
    ,u2g_EMFNG_ECDMFAVMXTL3_U2_ID
    ,u2g_EMFNG_ECDMFAVMXTL4_U2_ID
#if JENCYL == u1g_EJCC_6CYL          /*�y6�C���z*/
    ,u2g_EMFNG_ECDMFAVMXTL5_U2_ID
    ,u2g_EMFNG_ECDMFAVMXTL6_U2_ID
#endif
};

#if JEOOBD == u1g_EJCC_USE           /*�y�s�꒲���L�z*/
static volatile const u2 u2s_EOCDMFEM2MX_U1_ID[u1g_EJCC_NCYL] =  /* :�o�b�N�A�b�vRAM-ID */
{
     u2g_EMFNG_EOCDMFEM2MX1_U1_ID
    ,u2g_EMFNG_EOCDMFEM2MX2_U1_ID
    ,u2g_EMFNG_EOCDMFEM2MX3_U1_ID
    ,u2g_EMFNG_EOCDMFEM2MX4_U1_ID
 #if JENCYL == u1g_EJCC_6CYL         /*�y6�C���z*/
    ,u2g_EMFNG_EOCDMFEM2MX5_U1_ID
    ,u2g_EMFNG_EOCDMFEM2MX6_U1_ID
 #endif
};
#endif

#if ( JETCORE_D == u1g_EJCC_USE ) && ( JEOBDUDS_D == u1g_EJCC_NOT_USE )  /*�yt-CORE�Ή��L�zAND�yOBDonUDS�Ή����z*/
static volatile const u2 u2s_emfng_ecdmfav_tbl[u1g_EJCC_NCYL] =
{
     u2g_WTCIF_DEM_DTR_ECDMFAV1
    ,u2g_WTCIF_DEM_DTR_ECDMFAV2
    ,u2g_WTCIF_DEM_DTR_ECDMFAV3
    ,u2g_WTCIF_DEM_DTR_ECDMFAV4
 #if JENCYL == u1g_EJCC_6CYL         /*�y6�C���z*/
    ,u2g_WTCIF_DEM_DTR_ECDMFAV5
    ,u2g_WTCIF_DEM_DTR_ECDMFAV6
 #endif
};
static volatile const u2 u2s_emfng_ecdmfem_tbl[u1g_EJCC_NCYL] =
{
     u2g_WTCIF_DEM_DTR_ECDMFEM1
    ,u2g_WTCIF_DEM_DTR_ECDMFEM2
    ,u2g_WTCIF_DEM_DTR_ECDMFEM3
    ,u2g_WTCIF_DEM_DTR_ECDMFEM4
 #if JENCYL == u1g_EJCC_6CYL         /*�y6�C���z*/
    ,u2g_WTCIF_DEM_DTR_ECDMFEM5
    ,u2g_WTCIF_DEM_DTR_ECDMFEM6
 #endif
};
#endif
#pragma ghs enddata

/*-------------------------------------------------------------------*/
/* �֐���prototype�錾                                               */
/*-------------------------------------------------------------------*/
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
static void emfng_eocmfmlt_pt( const u1 ptt_ecdmfw[] ); /* :�s�꒲��RAM�X�V���� */
static void emfng_eocmfn_u2( u2 u2t_cdmfae );     /* :�s�꒲��RAM�X�V���� */
#endif
static u1 u1s_emfng_wxreqclr( void );             /* :�s�꒲��RAM�������� */
static void emfng_mcr_cal( void );                /* :�v�Z�l�ϐ��̎Z�o */
static void emfng_xottd_cal( void );              /* :�G�}OT���وُ팟�o���L���׸ނ̑��� */
static void emfng_cdmfi_reset( void );            /* :���Ή񐔔��足��(����ٗp)�̸ر���� */
static void emfng_mf_cnt_u1u1( u1 u1t_mfkind, u1 u1t_mfcyl );             /* :���΃J�E���^�̎Z�o */
static void emfng_ot_detect_ptptptpt( u1 *ptt_xumfot, u1 *ptt_xdmfot, u1 *ptt_xhmfoton, u1 *ptt_xhmfotoff );  /* :�G�}OT���وُ픻�� */
static void emfng_em_detect_u2ptpt( u2 u2t_cdmfae2, u1 *ptt_xdmfem, u1 *ptt_xumfem );  /* :EM�������x���ُ픻�� */
#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
static void emfng_di_detect_ptpt( u1 *ptt_xdmfdi, u1 *ptt_xumfdi );     /* :DI�ُ팟�o */
static void emfng_pfi_detect_ptpt( u1 *ptt_xdmfpfi, u1 *ptt_xumfpfi );  /* :PFI�ُ팟�o */
#endif
#if JEMFDTC_D == u1g_EJCC_USE    /*�y����OBD DTC�L�z*/
static void emfng_wxmf_out( void );               /* :�d�Z�ւ̒ʒm���� */
#endif
static void emfng_emode06_cal( void );            /* :mode$06�Ή����ζ����̑��� */
static u1 u1s_emfng_exrcdmf( void );              /* :EWMA���ζ����v�Z�����׸ގ擾���� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
static void emfng_espdaemclr( void );             /* :�s�꒲��RAM�ر���� */
#endif
static void emfng_roughjdg_u1u1( u1 u1t_xmfne, u1 u1t_mfkind );  /* ���H����֘A���� */

/*-------------------------------------------------------------------*/
/* �֐�                                                              */
/*-------------------------------------------------------------------*/
/*********************************************************************/
/*  �֐���        | emfng_pwon( )                                    */
/*  �������e      | ����������                                       */
/*  ����^�C�~���O| emfcnt_pwon()���R�[��                          */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      |                                                  */
/*********************************************************************/
void
emfng_pwon( void )
{
    /********************/
    /* �v�Z�l�ϐ��̎Z�o */
    /********************/
    emfng_mcr_cal();
}

/*********************************************************************/
/*  �֐���        | emfng_mfptn_ann_u1u1u1( )                        */
/*  �������e      | ���o���¶����̑���                               */
/*  ����^�C�~���O| TDC��(emfcnt_tdcm()���R�[��)                   */
/*  ����          | u1t_mfkind     :lsb=1 ���Ύ��                   */
/*                | u1t_mfcyl      :lsb=1 ���΋C��                   */
/*                | u1t_xmfne      :lsb=1 ���Ζ{����                 */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      | �O������������Ɏ��{(emfcnt)                     */
/*********************************************************************/
void
emfng_mfptn_ann_u1u1u1( u1 u1t_mfkind, u1 u1t_mfcyl, u1 u1t_xmfne )
{
    s4 s4t_ecjmfot;         /* lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev :�G�}OT���َ��Ό��o���¶��� */
    s4 s4t_ecjmfoti;        /* lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev :�G�}OT���ٱ���َ����Ό��o���¶��� */
    s4 s4t_ecjmfem;         /* lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev :EM�������َ��Ό��o���¶��� */
    s4 s4t_ene;             /* lsb=12800/64/256,unit=rpm :�ݼ�݉�]�� */
    s4 s4t_ejmfne;          /* lsb=1 :��]�̈攻��l */
    s4 s4t_emfrtot;         /* lsb=256/128/256,unit=% :�ώZ���Δ���l�␳�W�� */
    s4 s4t_emfrtotsum;      /* lsb=256/128/256,unit=% :�ώZ���Δ���l */
    u2 u2t_ecmfotcnt;       /* lsb=1,unit=�� :���ώZ�o�p�ώZ�� */
#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
    s2 s2t_ekpfi;           /* lsb=(1*4)/128/256,unit=�{ :�߰ĕ��˗ʎZ�o�W�� */
    u2 u2t_ecjmfdi;         /* lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev :DI���Ό��o���¶��� */
    u2 u2t_ecjmfpfi;        /* lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev :PFI���Ό��o���¶��� */
#endif
    s2 s2t_MFNEL3_c;        /* lsb=12800/64/256,unit=rpm :�A�C�h���̈攻��l */
    s2 s2t_eklsm;           /* lsb=320/64/256,unit=% :��C�ʕ��ח��i��Ύ��ʁj */

    /* ���[�N�f�[�^������ */
    s4t_ene      = (s4)s2g_ene_ene;
    s4t_ejmfne   = (s4)u1g_emfne_ejmfne;
#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
    s2t_ekpfi    = s2g_eminj_ekpfi;
#endif
    s2t_MFNEL3_c = s2s_emfng_MFNEL3;
    s2t_eklsm = s2g_eklset_eklsm;

    /***************************************/
    /* �G�}OT���َ��Ό��o���¶����̲ݸ���� */
    /***************************************/
    s4t_ecjmfot = (s4)u2g_emfng_ecjmfot;
    if ( s4t_ecjmfot < (s4)u2g_U2MAX )
    {
        s4t_ecjmfot++;
    }
    /* RAM�f�[�^�Ɋi�[ */
    u2g_emfng_ecjmfot = (u2)s4t_ecjmfot;              /* lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev */

    /**********************************************/
    /* �G�}OT���ٱ���َ����Ό��o���¶����̲ݸ���� */
    /**********************************************/
    s4t_ecjmfoti = (s4)u2g_emfng_ecjmfoti;
    if ( ( ( s4t_ejmfne == (s4)u1g_EMFNE_REV_IDLE2 )
#if JEMFHOUKI == u1g_EJCC_USAMF                                /*�y�ΕĖ@�K�z*/
        || ( s4t_ejmfne == (s4)u1g_EMFNE_REV_IDLE1 )
#endif
         )
      && ( s4t_ene < (s4)s2t_MFNEL3_c ) )
    {
        if ( s4t_ecjmfoti < (s4)u2g_U2MAX )
        {
            s4t_ecjmfoti++;
        }
    }
    /* RAM�f�[�^�Ɋi�[ */
    u2g_emfng_ecjmfoti = (u2)s4t_ecjmfoti;             /* lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev */

    /***************************************/
    /* EM�������َ��Ό��o���¶����̲ݸ���� */
    /***************************************/
    s4t_ecjmfem = (s4)u2g_emfng_ecjmfem;
    if ( s4t_ecjmfem < (s4)u2g_U2MAX )
    {
        s4t_ecjmfem++;
    }
    /* RAM�f�[�^�Ɋi�[ */
    u2g_emfng_ecjmfem = (u2)s4t_ecjmfem;               /* lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev */

#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
    /*******************************/
    /* DI���Ό��o���¶����̲ݸ���� */
    /*******************************/
    u2t_ecjmfdi = u2s_emfng_ecjmfdi;
    if ( s2t_ekpfi <= s2g_emfok_NGDI )
    {
        if ( u2t_ecjmfdi < u2g_U2MAX )
        {
            u2t_ecjmfdi++;
        }
        bis_emfng_exjmfdi = (u1)ON;  /* ecjmfdi���ı��ߏ��������L���׸� */
    }
    else    /* ecjmfdi���ı��ߏ����s���� */
    {
        bis_emfng_exjmfdi = (u1)OFF;
    }
    /* RAM�f�[�^�Ɋi�[ */
    u2s_emfng_ecjmfdi = u2t_ecjmfdi;         /* lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev */

    /********************************/
    /* PFI���Ό��o���¶����̲ݸ���� */
    /********************************/
    u2t_ecjmfpfi = u2s_emfng_ecjmfpfi;
    if ( s2t_ekpfi >= s2g_emfok_NGPFI )
    {
        if ( u2t_ecjmfpfi < u2g_U2MAX )
        {
            u2t_ecjmfpfi++;
        }
        bis_emfng_exjmfpfi = (u1)ON;  /* ecjmfpfi���ı��ߏ��������L���׸� */
    }
    else    /* ecjmfpfi���ı��ߏ����s���� */
    {
        bis_emfng_exjmfpfi = (u1)OFF;
    }
    /* RAM�f�[�^�Ɋi�[ */
    u2s_emfng_ecjmfpfi = u2t_ecjmfpfi;       /* lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev */
#endif

    /**********************/
    /* ���Ή񐔂̐ώZ���� */
    /**********************/
    if ( u1t_mfkind != u1g_EMFCNT_NOT )
    {
        emfng_mf_cnt_u1u1( u1t_mfkind, u1t_mfcyl );
    }

    /********************/
    /* ���H����֘A���� */
    /********************/
    emfng_roughjdg_u1u1( u1t_xmfne, u1t_mfkind );

    /*******************************************/
    /* �ώZ���Δ���l,���ώZ�o�p�ώZ�񐔂̎Z�o */
    /*******************************************/
    s4t_emfrtotsum = s4s_emfng_emfrtotsum;
    u2t_ecmfotcnt = u2s_emfng_ecmfotcnt;

    s4t_emfrtot = (s4)s2g_glmap2h_s2s2pt( s2t_eklsm, (s2)s4t_ene, &s2g_emfng_emfrtot_map[0] );
                                                    /* lsb=256/128/256,unit=% */
#if JENGPF_E != u1g_EJCC_NOT_USE       /*�yGPF�L�z*/
    if ( ( u1g_egpfrgcnd_exgpfrgsrv == (u1)ON )
      || ( u1g_egpfhtum_exdth == (u1)ON )
      || ( u1g_egpfhtum_exeff == (u1)ON )
 #if JERLOK == u1g_EJCC_USE            /*�yد�ذ݉^�]�z*/
      || ( u1g_egpfrgum_exrgact == (u1)ON )
 #endif
       )
    {
        s4t_emfrtot = (s4)s2g_glmap2h_s2s2pt( s2t_eklsm, (s2)s4t_ene, &s2g_emfng_emfrtotgpf_map[0] );
                                                    /* lsb=256/128/256,unit=% */
    }
#endif
    s4t_emfrtotsum = s4g_gladdst_s4s4( s4t_emfrtotsum, s4t_emfrtot );

    if ( u2t_ecmfotcnt < u2g_U2MAX )
    {
        u2t_ecmfotcnt++;
    }

    /* RAM�f�[�^�Ɋi�[ */
    s4s_emfng_emfrtotsum = s4t_emfrtotsum;
    u2s_emfng_ecmfotcnt = u2t_ecmfotcnt;
}

#if JENCYL == u1g_EJCC_6CYL     /*�y6�C���z*/
/*********************************************************************/
/*  �֐���        | emfng_mfmlt_ann_u1u1( )                          */
/*  �������e      | �Ό��C�����Δ��茋�ʒʒm����                     */
/*  ����^�C�~���O| ATDC30CA�^�C�~���O                               */
/*                | (emfcnt_neg_mlt()���R�[��)                     */
/*  ����          | u1t_mfkind     :lsb=1 ���Ύ��                   */
/*                | u1t_mfcyl      :lsb=1 ���΋C��                   */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      | �O������������Ɏ��{(emfcnt)                     */
/*                |�y6�C���z                                         */
/*********************************************************************/
void
emfng_mfmlt_ann_u1u1( u1 u1t_mfkind, u1 u1t_mfcyl )
{
    if ( u1t_mfkind == u1g_EMFCNT_OPPS )
    {
        emfng_mf_cnt_u1u1( u1t_mfkind, u1t_mfcyl );         /* ���Ή񐔂̐ώZ���� */
 #if JEEFI == u1g_EJCC_DUAL      /*�y�ޭ��INJ�z*/
        emfok_mfneld_set();                                 /* �Ό��C�����Δ��莞�̏��� */
        emfok_mfareacnt_ann_u1u1( u1t_mfkind, u1t_mfcyl );  /* �̈�����Ή񐔂̐ώZ */
 #endif
    }
}
#endif

/*********************************************************************/
/*  �֐���        | emfng_tdcm( )                                    */
/*  �������e      | TDC���ݸޏ���                                    */
/*  ����^�C�~���O| TDC��(emfcnt_tdcm()���R�[��)                   */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      |                                                  */
/*********************************************************************/
void
emfng_tdcm( void )
{
    u2 u2t_ekldmfae;       /* lsb=1,unit=�� :EM�������َ��Δ���l */
    s2 s2t_ene;            /* lsb=12800/64/256,unit=rpm :�ݼ�݉�]�� */
    u1 u1t_state;          /* lsb=1 :���o���x��� */
    u1 u1t_exmfkpl;        /* lsb=1 :���]��Ԍp���׸� */
    u1 u1t_exmfkpm;        /* lsb=1 :����]��Ԍp���׸� */

    u1t_state = u1g_wsentivchg_state;

    /************************/
    /* EM�������َ��Δ���l */
    /************************/
    if ( u2g_emfng_ecjmfem == (u2)0U )
    {
        u2t_ekldmfae = u2g_emfng_eldmfaem_mcr;          /* lsb=1,unit=�� */
        if ( ( u1s_emfng_ecjemrev < u1s_emfng_CJEMREV )
          && ( u1t_state != u1g_WSENTIVCHG_LVL2 ) )
        {
            /*****************/
            /*   ίĽ��Ď�   */
            /*****************/
            if ( big_emfng_exhstmf == (u1)ON )                  /* ίĽ��� */
            {
                u2t_ekldmfae = u2s_emfng_eldmfst2_mcr;  /* lsb=1,unit=�� */
            }

            /*******************/
            /*   ����޽��Ď�   */
            /*******************/
            if ( big_emfng_excstmf == (u1)ON )                  /* ����޽��� */
            {
                u2t_ekldmfae = u2s_emfng_eldmfst1_mcr;  /* lsb=1,unit=�� */
            }
        }
        if ( u1t_state == u1g_WSENTIVCHG_IUE )
        {
            u2t_ekldmfae = u2g_glmulst_u2u2u2( u2t_ekldmfae, u2s_emfng_KLEVEL3, (u2)6U );  /* lsb=1*(4/256) �� 1 */
        }
        /* RAM�f�[�^�Ɋi�[ */
        u2g_emfng_ekldmfae = u2t_ekldmfae;          /* lsb=1,unit=�� */
    }

    /********************/
    /* NE�p���׸ނ̑��� */
    /********************/
    if ( u2g_emfng_ecjmfot == (u2)0U )
    {
        /* ���[�N�f�[�^������ */
        s2t_ene = s2g_ene_ene;

        /* ���]��Ԍp���׸�(XMFKPL)�̑��� */
        u1t_exmfkpl = (u1)OFF;
        if ( s2t_ene <= (s2)(((2000.)/(12800./64./256.))+0.5) )
        {
            u1t_exmfkpl = (u1)ON;
        }
        glbitcp_bibi( u1t_exmfkpl, bis_emfng_exmfkpl );

        /* ����]��Ԍp���׸�(XMFKPM)�̑��� */
        u1t_exmfkpm = (u1)OFF;
        if ( s2t_ene <= (s2)(((3000.)/(12800./64./256.))+0.5) )
        {
            u1t_exmfkpm = (u1)ON;
        }
        glbitcp_bibi( u1t_exmfkpm, bis_emfng_exmfkpm );
    }
}

/*********************************************************************/
/*  �֐���        | emfng_xjmf_ann_u1( )                             */
/*  �������e      | ���Ή����茋�ʒʒm����                           */
/*  ����^�C�~���O| TDC��(emfcnt_tdcm()���R�[��)                   */
/*  ����          | u1t_xjmf :lsb=1 �����茋��                       */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      | �������Ɏ��{                                   */
/*********************************************************************/
void
emfng_xjmf_ann_u1( u1 u1t_xjmf )
{
    /* RAM�f�[�^�Ɋi�[ */
    glbitcp_bibi( u1t_xjmf, bis_emfng_exjmf );
}

/*********************************************************************/
/*  �֐���        | emfng_cjpmf_inc_u1( )                            */
/*  �������e      | ��۸۽�����̑���                                 */
/*  ����^�C�~���O| BTDC60CA(emfccrnk���R�[��)�y4�C���z            */
/*                | BTDC30CA(emfccrnk���R�[��)�y6�C���z            */
/*                | ATDC30CA(emfccrnk���R�[��)                     */
/*  ����          | u1t_timming :lsb=1 ecjpmf���ı������ݸ�          */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      | DLTMFL,DDTCR1�Z�o��Ɏ��{                        */
/*********************************************************************/
void
emfng_cjpmf_inc_u1( u1 u1t_timming )
{
    u1 u1t_ecjpmf;      /* lsb=1,unit=�� :��۸۽���� */
    u1 u1t_ejmfne;      /* lsb=1 :��]�̈� */
    u1 u1t_timjdg;      /* lsb=1 :���[�N�ϐ� */
    u1 u1t_exjtmf;      /* lsb=1 :���΂̉�����֎~�׸� */

    /* ���[�N�f�[�^������ */
    u1t_ecjpmf = u1s_emfng_ecjpmf;
    u1t_ejmfne = u1g_emfne_ejmfne;
    u1t_exjtmf = (u1)bis_emfng_exjtmf;

    u1t_timjdg = (u1)OFF;
    if ( ( u1t_timming == u1g_EMFCCRNK_DLTMFL_TIMMING )
      && ( u1t_ejmfne  != u1g_EMFNE_REV_HIGH )
#if JEMFMETHOD_D == u1g_EJCC_TIME_D    /*�y���΃�T�@�z*/
      && ( s2g_emfccrnk_edltmflxh[0] >= (s2)0 )
      && ( s2g_emfccrnk_edltmflxh[1] <  (s2)0 )
#endif
#if JEMFMETHOD_D == u1g_EJCC_OMEGA_D   /*�y���΃��֖@�z*/
      && ( s2g_emfccrnk_ewmfl[0] <= (s2)0 )
      && ( s2g_emfccrnk_ewmfl[1] >  (s2)0 )
#endif
       )
    {
        u1t_timjdg = (u1)ON;
    }
    if ( ( u1t_timming == u1g_EMFCCRNK_DDTCRX_TIMMING )
      && ( u1t_ejmfne  == u1g_EMFNE_REV_HIGH )
#if JEMFMETHOD_D == u1g_EJCC_TIME_D    /*�y���΃�T�@�z*/
      && ( s2g_emfccrnk_eddtcrxh[0] >= (s2)0 )
      && ( s2g_emfccrnk_eddtcrxh[1] <  (s2)0 )
#endif
#if JEMFMETHOD_D == u1g_EJCC_OMEGA_D   /*�y���΃��֖@�z*/
 #if JENCYL == u1g_EJCC_6CYL    /*�y6�C���z*/
      && ( s2g_emfccrnk_ewmfh[0] <= (s2)0 )
      && ( s2g_emfccrnk_ewmfh[1] >  (s2)0 )
 #endif
 #if JENCYL == u1g_EJCC_4CYL    /*�y4�C���z*/
      && ( s2g_emfccrnk_ewmfhp[0] <= (s2)0 )
      && ( s2g_emfccrnk_ewmfhp[1] >  (s2)0 )
 #endif
#endif
       )
    {
        u1t_timjdg = (u1)ON;
    }
    if ( ( u1t_timjdg == (u1)ON )
      && ( bis_emfng_exjmf == (u1)OFF )
      && ( u1t_exjtmf == (u1)ON ) )
    {
        if ( u1t_ecjpmf < u1g_U1MAX )
        {
            u1t_ecjpmf++;
        }
    }
    if ( u1t_exjtmf == (u1)OFF )
    {
        u1t_ecjpmf = (u1)0U;
    }

    /* RAM�f�[�^�Ɋi�[ */
    u1s_emfng_ecjpmf = u1t_ecjpmf;      /* lsb=1,unit=�� */
}

/*********************************************************************/
/*  �֐���        | emfng_mf_cnt_u1u1( )                             */
/*  �������e      | ���΃J�E���^�̎Z�o                               */
/*  ����^�C�~���O| ���Δ��萬����                                   */
/*                | TDC��(emfng_mfptn_ann()���R�[��)               */
/*                | ATDC30CA(emfng_mfmlt_ann()���R�[��)�y6�C���z   */
/*  ����          | u1t_mfkind     :lsb=1 ���Ύ��                   */
/*                | u1t_mfcyl      :lsb=1 ���΋C��                   */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      | �����֐�                                         */
/*********************************************************************/
static void
emfng_mf_cnt_u1u1( u1 u1t_mfkind, u1 u1t_mfcyl )
{
    s4 s4t_i;               /* lsb=1 :for���[�v�p�ϐ� */
    u1 u1t_bit;             /* :���΋C���׸� */
    s4 s4t_ecdmfaotbnk[2];  /* lsb=1,unit=�� :��ݸ�ʐG�}OT���َ��ζ��� */
    s4 s4t_ecdmfaot;        /* lsb=1,unit=�� :�G�}OT���ّS�C�����ζ��� */
    s4 s4t_ecdmfaoti;       /* lsb=1,unit=�� :����ْ��S�C�����ζ��� */
    s4 s4t_ecdmfae2;        /* lsb=1,unit=�� :EM�������ّS�C�����ζ��� */
    s4 s4t_ecdmfaem;        /* lsb=1,unit=�� :EM�������ّS�C�����ζ��� */
    s4 s4t_ecmfot;          /* lsb=1,unit=�� :�����C�����ζ��� */
#if JEOOBD == u1g_EJCC_USE             /*�y�s�꒲���L�z*/
    s2 s2t_espd;            /* lsb=256/256,unit=km/h :�ԑ� */
    s2 s2t_ene;             /* lsb=12800/64/256,unit=rpm :�ݼ�݉�]�� */
    s2 s2t_eklsm;           /* lsb=320/64/256,unit=% :��C�ʕ��ח��i��Ύ��ʁj */
    u1 u1t_ejmfne;          /* lsb=1 :��]�̈� */
#endif
    s4 s4t_idx;             /* lsb=1 :�C���Q�ʂ̗v�f�� */
    s4 s4t_bnk;             /* lsb=1 :���΋C���̑�����o���N */
    s4 s4t_indx;            /* lsb=1 :���΋C���̑�������C���ԍ� */
    u1 u1t_ncyl;            /* ���[�N�ϐ� */
    u1 u1t_ncyl_c;          /* lsb=1 :�C���� */
    u1 u1t_ncylw_c;         /* lsb=1 :�C���Q�� */

    if ( u1t_mfkind == u1g_EMFCNT_MLT )
    {
        /******************************/
        /* �Ό��C���ȊO�̕����C������ */
        /******************************/
        s4t_ecmfot = (s4)u2g_emfng_ecmfot;
        if ( s4t_ecmfot < (s4)u2g_U2MAX )
        {
            s4t_ecmfot++;                           /* CMFOT�̲ݸ���� */
        }
        u2g_emfng_ecmfot = (u2)s4t_ecmfot;          /* lsb=1,unit=�� */
    }
    else if ( u1t_mfkind == u1g_EMFCNT_OPPS )
    {
        /****************/
        /* �Ό��C������ */
        /****************/
        u1t_ncylw_c = u1s_EMFNG_NCYLW;
        for ( s4t_i = (s4)0; s4t_i < (s4)u1t_ncylw_c; s4t_i++ )
        {
            if ( u1g_emfng_mfwcyl_tbl[s4t_i] == u1t_mfcyl )
            {
                s4t_idx = s4t_i;
                if ( u1g_emfng_ecdmfw[s4t_idx] < u1g_U1MAX )
                {
                    u1g_emfng_ecdmfw[s4t_idx]++;   /* �C���Q�ʂ̑Ό��C�����ζ��� */
                }
            }
        }
    }
    else
    {
        /****************************************/
        /* �����/�����/�P��A��/2�A��/�Ԍ� ���� */
        /****************************************/
        s4t_ecdmfaot       = (s4)u1g_emfng_ecdmfaot;
        s4t_ecdmfae2       = (s4)u2g_emfng_ecdmfae2;
        s4t_ecdmfaem       = (s4)u1g_emfng_ecdmfaem;
        s4t_ecdmfaotbnk[0] = (s4)u1g_emfng_ecdmfaotbnk[0];
        s4t_ecdmfaotbnk[1] = (s4)u1g_emfng_ecdmfaotbnk[1];
        s4t_ecdmfaoti      = (s4)u2g_emfng_ecdmfaoti;
#if JEOOBD == u1g_EJCC_USE             /*�y�s�꒲���L�z*/
        s2t_espd           = s2g_espd_espd;
        s2t_ene            = s2g_ene_ene;
        s2t_eklsm          = s2g_eklset_eklsm;
        u1t_ejmfne         = u1g_emfne_ejmfne;
#endif
        u1t_ncyl_c = u1g_ejcc_NCYL;
        u1t_ncyl = u1t_mfcyl;
        for ( s4t_i = (s4)0; s4t_i < (s4)u1t_ncyl_c; s4t_i++ )
        {
            u1t_bit = (u1)(u1t_ncyl & (u1)0x01U);
            if ( u1t_bit != (u1)0x00U )
            {
                s4t_bnk = (s4)u1s_emfng_mfcylbnk_tbl[s4t_i];   /* MFCYL����o���N�����߂� */
                s4t_ecdmfaotbnk[s4t_bnk]++;                    /* ��ݸ�ʐG�}OT���َ��ζ��� */
                s4t_ecdmfaot++;                                /* �G�}OT���ّS�C�����ζ��� */
                s4t_ecdmfaoti++;                               /* ����ْ��S�C�����ζ��� */

                s4t_indx = (s4)u1g_eengspc_ewcnvt_tbl[s4t_i];  /* MFCYL������C���ԍ������߂� */
                if ( u1g_emfng_ecdmfem[s4t_indx] < u1g_U1MAX )
                {
                    u1g_emfng_ecdmfem[s4t_indx]++;             /* EM�������ًC���ʎ��ζ��� */
                }
                if ( u2g_emfng_ecdmfem2[s4t_indx] < u2g_U2MAX )
                {
                    u2g_emfng_ecdmfem2[s4t_indx]++;            /* EM�������ًC���ʎ��ζ��� */
                }
                if ( u1g_emfng_ecdmfemi[s4t_indx] < u1g_U1MAX )
                {
                    u1g_emfng_ecdmfemi[s4t_indx]++;            /* ����ْ��C���ʎ��ζ��� */
                }
                s4t_ecdmfae2++;            /* EM�������ّS�C�����ζ��� */
                s4t_ecdmfaem++;            /* EM�������ّS�C�����ζ��� */
#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
                if ( bis_emfng_exjmfdi == (u1)ON )
                {
                    if ( u1s_emfng_ecdmfdi[s4t_indx] < u1g_U1MAX )
                    {
                        u1s_emfng_ecdmfdi[s4t_indx]++;             /* �C����DI���ζ��� */
                    }
                }
                if ( bis_emfng_exjmfpfi == (u1)ON )
                {
                    if ( u1s_emfng_ecdmfpfi[s4t_indx] < u1g_U1MAX )
                    {
                        u1s_emfng_ecdmfpfi[s4t_indx]++;            /* �C����PFI���ζ��� */
                    }
                }
#endif

#if JEOOBD == u1g_EJCC_USE      /*�y�s�꒲���L�z*/
                s4s_emfng_espdaem  = s4g_gladdst_s4s4( s4s_emfng_espdaem, (s4)s2t_espd );
                s4s_emfng_eneaem   = s4g_gladdst_s4s4( s4s_emfng_eneaem, (s4)s2t_ene );
                s4s_emfng_eklsmaem = s4g_gladdst_s4s4( s4s_emfng_eklsmaem, (s4)s2t_eklsm );

                if ( ( u1t_ejmfne == u1g_EMFNE_REV_IDLE2 )
 #if JEMFHOUKI == u1g_EJCC_USAMF /*�y�ΕĖ@�K�z*/
                  || ( u1t_ejmfne == u1g_EMFNE_REV_IDLE1 )
 #endif
                   )
                {
                    if ( u1s_emfng_ecjmfneemi < u1g_U1MAX )
                    {
                        u1s_emfng_ecjmfneemi++;
                    }
                }
                if ( u1t_ejmfne == u1g_EMFNE_REV_LOW )
                {
                    if ( u1s_emfng_ecjmfneeml < u1g_U1MAX )
                    {
                        u1s_emfng_ecjmfneeml++;
                    }
                }
                if ( u1t_ejmfne == u1g_EMFNE_REV_HIGH )
                {
                    if ( u1s_emfng_ecjmfneemh < u1g_U1MAX )
                    {
                        u1s_emfng_ecjmfneemh++;
                    }
                 }
#endif

            }
            u1t_ncyl = (u1)(u1t_ncyl >> 1);
        }

        /* �K�[�h���� */
        if ( s4t_ecdmfaotbnk[0] > (s4)u1g_U1MAX )
        {
            s4t_ecdmfaotbnk[0] = (s4)u1g_U1MAX;
        }
        if ( s4t_ecdmfaotbnk[1] > (s4)u1g_U1MAX )
        {
            s4t_ecdmfaotbnk[1] = (s4)u1g_U1MAX;
        }
        if ( s4t_ecdmfaot > (s4)u1g_U1MAX )
        {
            s4t_ecdmfaot = (s4)u1g_U1MAX;
        }
        if ( s4t_ecdmfaoti > (s4)u2g_U2MAX )
        {
            s4t_ecdmfaoti = (s4)u2g_U2MAX;
        }
        if ( s4t_ecdmfae2 > (s4)u2g_U2MAX )
        {
            s4t_ecdmfae2 = (s4)u2g_U2MAX;
        }
        if ( s4t_ecdmfaem > (s4)u1g_U1MAX )
        {
            s4t_ecdmfaem = (s4)u1g_U1MAX;
        }

        /* RAM�f�[�^�Ɋi�[ */
        u2g_emfng_ecdmfae2       = (u2)s4t_ecdmfae2;            /* lsb=1,unit=�� */
        u1g_emfng_ecdmfaem       = (u1)s4t_ecdmfaem;            /* lsb=1,unit=�� */
        u1g_emfng_ecdmfaotbnk[0] = (u1)s4t_ecdmfaotbnk[0];      /* lsb=1,unit=�� */
        u1g_emfng_ecdmfaotbnk[1] = (u1)s4t_ecdmfaotbnk[1];      /* lsb=1,unit=�� */
        u1g_emfng_ecdmfaot       = (u1)s4t_ecdmfaot;            /* lsb=1,unit=�� */
        u2g_emfng_ecdmfaoti      = (u2)s4t_ecdmfaoti;           /* lsb=1,unit=�� */

    }   /* (u1t_mfkind == u1g_EMFCNT_MLT) end */
}

/*********************************************************************/
/*  �֐���        | emfng_reset( )                                   */
/*  �������e      | ���Δ���ؾ�ď���                                 */
/*  ����^�C�~���O| TDC��(emfcnt_tdcm()���R�[��)                   */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      | �O������s�������Ɏ��{(emfcnt)                   */
/*********************************************************************/
void
emfng_reset( void )
{
    bis_emfng_exjmf   = (u1)OFF;
    bis_emfng_exjtmf  = (u1)OFF;
    bis_emfng_exjtmf2 = (u1)OFF;
}

/*********************************************************************/
/*  �֐���        | emfng_drvclchg( )                                */
/*  �������e      | �h���C�r���O�T�C�N���ڍs���̏���������           */
/*  ����^�C�~���O| emfcnt_drvclchg()���R�[��                      */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      |                                                  */
/*********************************************************************/
void
emfng_drvclchg( void )
{
    s4 s4t_i;             /* lsb=1 :for loop�p */
    u1 u1t_ncyl_c;        /* lsb=1 :�C���� */
    u1 u1t_ncylw_c;       /* lsb=1 :�C���Q�� */

    /* ������ ���荞�݋֎~ ������ */ /* �R�[����emfcnt_drvclchg()�Ŏ��{ */
    u2g_emfng_ecjmfot        = (u2)0;     /* 0�������̂���LSB�ȗ� */
    u2g_emfng_ecjmfem        = (u2)0;     /* 0�������̂���LSB�ȗ� */
    u2g_emfng_ecjmfoti       = (u2)0;     /* 0�������̂���LSB�ȗ� */
#if JETCORE_D == u1g_EJCC_USE     /*�yt-CORE�Ή��L�z*/
    big_emfng_exdmf     = (u1)OFF;
#endif
#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
    u2s_emfng_ecjmfdi   = (u2)0;     /* 0�������̂���LSB�ȗ� */
    u2s_emfng_ecjmfpfi  = (u2)0;     /* 0�������̂���LSB�ȗ� */
#endif
    u1t_ncyl_c = u1g_ejcc_NCYL;
    u1t_ncylw_c = u1s_EMFNG_NCYLW;

    u2g_emfng_ecmfot         = (u2)0U;
    for ( s4t_i = (s4)0; s4t_i < (s4)u1t_ncylw_c; s4t_i++ )
    {
        u1g_emfng_ecdmfw[s4t_i]    = (u1)0U;
    }
    u1g_emfng_ecdmfaotbnk[0] = (u1)0U;     /* CJMFOT�Ɠ����ɃN���A���� */
    u1g_emfng_ecdmfaotbnk[1] = (u1)0U;     /* CJMFOT�Ɠ����ɃN���A���� */
    u1g_emfng_ecdmfaot       = (u1)0U;     /* CJMFOT�Ɠ����ɃN���A���� */
    u2g_emfng_ecdmfaoti      = (u2)0U;     /* CJMFOTI�Ɠ����ɃN���A���� */
    u2g_emfng_ecdmfae2       = (u2)0U;     /* CJMFEM�Ɠ����ɃN���A���� */
    u1g_emfng_ecdmfaem       = (u1)0U;     /* CJMFEM�Ɠ����ɃN���A���� */
    u1g_emfng_ecdtmf2        = (u1)0U;
    for ( s4t_i = (s4)0; s4t_i < (s4)u1t_ncyl_c ; s4t_i++ )
    {
        u1g_emfng_ecdmfem[s4t_i]   = (u1)0U;
        u2g_emfng_ecdmfem2[s4t_i]  = (u2)0U;
        u1g_emfng_ecdmfemi[s4t_i]  = (u1)0U;     /* CJMFEM�Ɠ����ɃN���A���� */
    }
#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
    for ( s4t_i = (s4)0; s4t_i < (s4)u1t_ncyl_c; s4t_i++ )
    {
        u1s_emfng_ecdmfdi[s4t_i]   = (u1)(((0.)/(1.))+0.5);  /* ecjmfdi�Ɠ����ɃN���A���� */
        u1s_emfng_ecdmfpfi[s4t_i]  = (u1)(((0.)/(1.))+0.5);  /* ecjmfpfi�Ɠ����ɃN���A���� */
    }
#endif
    u2s_emfng_ecdtmfwa      = (u2)0U;

    u1s_emfng_ecxmf         = (u1)0U;
    u1s_emfng_ecxmf1        = (u1)0U;
    big_emfng_exjokmf       = (u1)OFF;
    u1s_emfng_ecjemrev      = (u1)0U;
    bis_emfng_excntmf       = (u1)OFF;
    bis_emfng_exdmf1        = (u1)OFF;
    bis_emfng_exottd        = (u1)OFF;
    s4s_emfng_emfrtotsum    = (s4)(((0.)/(256./128./256.))+0.5);
    u2s_emfng_ecmfotcnt     = (u2)0U;
#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
    big_emfng_exmfddi   = (u1)OFF;
    big_emfng_exmfdied  = (u1)OFF;
    big_emfng_exmfdpfi  = (u1)OFF;
    big_emfng_exmfpfied = (u1)OFF;
#endif

#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    emfng_espdaemclr();
#endif
    /* ������ ���荞�݋��� ������ */ /* �R�[����emfcnt_drvclchg()�Ŏ��{ */
}

/*********************************************************************/
/*  �֐���        | emfng_16msl( )                                   */
/*  �������e      | 16ms���ݸޏ���                                   */
/*  ����^�C�~���O| 16ms��(emfcnt_16msl()���R�[��)                 */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      |                                                  */
/*********************************************************************/
void
emfng_16msl( void )
{
    s4 s4t_ejmfne;         /* lsb=1 :��]�̈� */
    s2 s2t_ethw;           /* lsb=160/256,unit=�� :�ݼ�ݐ���p���� */
    s2 s2t_etha;           /* lsb=160/256,unit=�� :�ݼ�ݐ���p�z�C�� */
    s2 s2t_THA_c;          /* lsb=160/256,unit=�� :�z�b�g�X�^�[�g����z�C�� */
    s2 s2t_THWCSTH_c;      /* lsb=160/256,unit=�� :�R�[���h�X�^�[�g���萅�� */
    s2 s2t_THACST_c;       /* lsb=160/256,unit=�� :�R�[���h�X�^�[�g����z�C�� */
    s2 s2t_MFNEL3_c;       /* lsb=12800/64/256,unit=rpm :�A�C�h���̈攻��l */

    s2t_ethw = s2g_ethw_ethw;
    s2t_etha = s2g_etha_etha;
    s2t_MFNEL3_c = s2s_emfng_MFNEL3;

    if ( u1g_exst_exastnrm == (u1)OFF )
    {
        /***************/
        /* ίĽ��Ĕ��� */
        /***************/
        s2t_THA_c = s2s_emfng_THA;
        if ( ( s2t_ethw >= s2s_emfng_THW )
          && ( s2t_etha >= s2t_THA_c ) )
        {
            big_emfng_exhstmf = (u1)ON;
        }
        else
        {
            big_emfng_exhstmf = (u1)OFF;
        }

        /*****************/
        /* ����޽��Ĕ��� */
        /*****************/
        s2t_THWCSTH_c = s2s_emfng_THWCSTH;
        s2t_THACST_c = s2s_emfng_THACST;
        if ( ( s2t_ethw <= s2s_emfng_THWCSTL )
          || ( ( s2t_ethw <= s2t_THWCSTH_c )
            && ( s2t_etha <= s2t_THACST_c ) ) )
        {
            big_emfng_excstmf = (u1)ON;
        }
        else
        {
            big_emfng_excstmf = (u1)OFF;
        }
    }

    /**********************************************/
    /* �G�}OT���ٱ���َ����Ό��o���¶����̸ر���� */
    /**********************************************/
    /* ���[�N�f�[�^������ */
    s4t_ejmfne = (s4)u1g_emfne_ejmfne;
    if ( ( ( s4t_ejmfne != (s4)u1g_EMFNE_REV_IDLE2 )
#if JEMFHOUKI == u1g_EJCC_USAMF                                /*�y�ΕĖ@�K�z*/
        && ( s4t_ejmfne != (s4)u1g_EMFNE_REV_IDLE1 )
#endif
         )
      || ( s2g_ene_ene >= s2t_MFNEL3_c ) )
    {
        emfng_cdmfi_reset();
    }
}

/*********************************************************************/
/*  �֐���        | emfng_65msl( )                                   */
/*  �������e      | 65ms���ݸޏ���                                   */
/*  ����^�C�~���O| 65ms��(emfcnt_65msl()���R�[��)                 */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      |                                                  */
/*********************************************************************/
void
emfng_65msl( void )
{
    u1 u1t_xdmfem;          /* lsb=1 :EM�������وُ팟�o�׸� */
    u1 u1t_xdmfot;          /* lsb=1 :�G�}OT���وُ팟�o�׸� */
    u1 u1t_xumfot;          /* lsb=1 :�G�}OT���ِ��픻��ۗ��׸� */
    u1 u1t_xhmfoton;        /* lsb=1 :�G�}OT�ɂ��MIL�_�ŗv���׸� */
    u1 u1t_xhmfotoff;       /* lsb=1 :�G�}OT�ɂ��MIL�_�ŷ�ݾٗv���׸� */
    u1 u1t_xumfem;          /* lsb=1 :EM�������ِ��픻��ۗ��׸� */
    u2 u2t_cdtmfwa;         /* lsb=1,unit=�� :EM�������ٔ���p���H���� */
    s4 s4t_cdmfae2;         /* lsb=1,unit=�� :EM�������x���S�C�����΃J�E���^(����p) */
    u4  u4t_cdmfaavTv;      /* lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�S�C��)ܰ� */
    u2  u2t_cdmfaavTv;      /* lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�S�C��)ܰ�(�������ݗp) */
    u2  u2t_ECDMFAAVMNTL_MI_c;  /* lsb=1,unit=�� :�e�X�g���ʏo�͗p�ߋ�10�g���b�vEWMA���΃J�E���^�����l(�S�C��)�����l */
    u2  u2t_cdmfaavMxtl;    /* lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�S�C��)ܰ�(�������ݗp) */
    u4  u4t_cdmfaemTv;      /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�S�C��)ܰ�           �ymode$06-TID$0C�z*/
    u4  u4t_cdmfavTv;       /* lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�C����)ܰ� �ymode$06-TID$0B�z*/
    u2  u2t_cdmfavTv;       /* lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�C����)ܰ�(�������ݗp) �ymode$06-TID$0B�z*/
    u2  u2t_ECDMFAVMNTL_MI_c ;  /* lsb=1,unit=�� :�e�X�g���ʏo�͗p�ߋ�10�g���b�vEWMA���΃J�E���^�����l(�C����)�����l */
    u2  u2t_cdmfavMxtl;     /* lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�C����)ܰ�(�������ݗp) �ymode$06-TID$0B�z*/
    u4  u4t_cdmfemTv;       /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�C����)ܰ�           �ymode$06-TID$0C�z*/
    s4  s4t_cyl;            /* lsb=1,unit=�C�� */
    u1  u1t_exrcdmf;        /* lsb=1 :EWMA���ζ����v�Z�����׸� */
    u2  u2t_ECDMFAEMTV_MI_c;    /* lsb=1,unit=�� :�e�X�g���ʏo�͗p���g���b�v�ݐώ��΃J�E���^(�S�C��)�����l */
    u2  u2t_ECDMFEMTV_MI_c;     /* lsb=1,unit=�� :�e�X�g���ʏo�͗p���g���b�v�ݐώ��΃J�E���^(�C����)�����l */
#if JEMAT_OBD2 == u1g_EJCC_NOT_USE    /*�yOBD2�K�����z*/
    u1  u1t_xmfKwp;         /* lsb=1 :OBD2�޲���Ͻ���� ���� */
#endif

    u1  u1t_xjokmf;         /* lsb=1 : �n���㏊���]�����׸� */
    u1  u1t_cjemrev;        /* lsb=1, unit=�� : �n����Я��݈������ٔ���� */
    u1  u1t_xreqclr;        /* lsb=1 :�ް������v���׸� */
#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
    u1  u1t_xdmfdi;         /* lsb=1 : DI�ُ��׸� */
    u1  u1t_xumfdi;         /* lsb=1 : DI�ُ�ɂ�鐳�픻��ۗ��׸� */
    u1  u1t_xdmfpfi;        /* lsb=1 : PFI�ُ��׸� */
    u1  u1t_xumfpfi;        /* lsb=1 : PFI�ُ�ɂ�鐳�픻��ۗ��׸� */
    s4  s4t_i;              /* lsb=1 :for���[�v�p�ϐ� */
#endif
    u1  u1t_exdisable;      /* lsb=1 :Disable�׸� */
    u1  u1t_excomplete;     /* lsb=1 :Complete�׸� */
    u2  u2t_LJMFOT_c;       /* lsb=2/u1g_EJCC_NCYL,unit=rev :�G�}OT���x���ُ픻����s�^�C�~���O */
    u2  u2t_LJMFEM_c;       /* lsb=2/u1g_EJCC_NCYL,unit=rev :EM�������x���ُ픻����s�^�C�~���O */
    u2  u2t_LJMFOTF_c;      /* lsb=2/u1g_EJCC_NCYL,unit=rev :�G�}OT���x���ُ픻����s�^�C�~���O */
#if ( JETCORE_D == u1g_EJCC_USE ) && ( JEOBDUDS_D == u1g_EJCC_NOT_USE )     /*�yt-CORE�Ή��L�zAND�yOBDonUDS�Ή����z*/
    u2 u2t_ecdmfaavTv;      /* lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�S�C��)(�߂�l�擾�p) */
    u2 u2t_ecdmfaavMntl;    /* lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ��������l(�S�C��)(�߂�l�擾�p) */
    u2 u2t_ecdmfaavMxtl;    /* lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ�������l(�S�C��)(�߂�l�擾�p) */
    u2 u2t_dtrid;           /* lsb=1 :ýČ��ʏo�͂h�c */
    u2 u2t_ecdmfavTv;       /* lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�C����)(�߂�l�擾�p) */
    u2 u2t_ecdmfavMntl;     /* lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ��������l(�C����)(�߂�l�擾�p) */
    u2 u2t_ecdmfavMxtl;     /* lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ�������l(�C����)(�߂�l�擾�p) */
    u2 u2t_ecdmfaemTv;      /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�S�C��)(�߂�l�擾�p) */
    u2 u2t_ecdmfaemMntl;    /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�S�C��)(�߂�l�擾�p) */
    u2 u2t_ecdmfaemMxtl;    /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�S�C��)(�߂�l�擾�p) */
    u2 u2t_ecdmfemTv;       /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�C����)(�߂�l�擾�p) */
    u2 u2t_ecdmfemMntl;     /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�C����)(�߂�l�擾�p) */
    u2 u2t_ecdmfemMxtl;     /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�C����)(�߂�l�擾�p) */
#endif
    u1 u1t_ncyl_c;          /* lsb=1 :�C���� */

    /* ���[�N�f�[�^������ */
    u1t_xdmfem    = (u1)OFF;
    u1t_xdmfot    = (u1)OFF;
    u1t_xumfot    = (u1)OFF;
    u1t_xhmfoton  = (u1)OFF;
    u1t_xhmfotoff = (u1)OFF;
    u1t_xumfem    = (u1)OFF;
#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
    u1t_xumfdi    = (u1)OFF;
    u1t_xumfpfi   = (u1)OFF;
    u1t_xdmfdi    = (u1)OFF;
    u1t_xdmfpfi   = (u1)OFF;
#endif

    big_emfng_excdmfemclr  = (u1)OFF;                   /* ecdmfem[]�ر�v���׸� */
    bis_emfng_excdmfem2clr = (u1)OFF;                   /* ecdmfem2[]�ر�v���׸� */
    bis_emfng_excdmfwclr   = (u1)OFF;                   /* ecdmfw[]�ر�v���׸� */
    bis_emfng_excdmfae2clr = (u1)OFF;
#if JETCORE_D == u1g_EJCC_USE         /*�yt-CORE�Ή��L�z*/
    bis_emfng_exoutftp     = (u1)OFF;
    bis_emfng_exemfst      = (u1)OFF;
#endif

#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
    bis_emfng_excdmfdiclr  = (u1)OFF;
    bis_emfng_excdmfpficlr = (u1)OFF;
#endif

    u1t_xjokmf  = (u1)big_emfng_exjokmf;
    u1t_cjemrev = u1s_emfng_ecjemrev;
#if JEMAT_OBD2 == u1g_EJCC_NOT_USE    /*�yOBD2�K�����z*/
    u1t_xmfKwp  = (u1)big_wobd2msk_xmfKwp;
#endif
    u2t_LJMFOT_c = u2g_emfng_LJMFOT;
    u2t_LJMFEM_c = u2g_emfng_LJMFEM;
    u2t_LJMFOTF_c = u2s_emfng_LJMFOTF;
#if JEMFDTC_D == u1g_EJCC_USE         /*�y����OBD DTC�L�z*/
    u1s_emfng_xem_lstpnd_Lch = (u1)big_wmf_fdi_xem_lstpnd;
    u1s_emfng_xot_lstpnd_Lch = (u1)big_wmf_fdi_xot_lstpnd;
    u1s_emfng_xot_warning_Lch = (u1)big_wmf_fdi_xot_warning;
    u1s_emfng_xem_warning_Lch = (u1)big_wmf_fdi_xem_warning;
#endif
    u1s_emfng_state_Lch = u1g_wsentivchg_state;
    u1t_ncyl_c = u1g_ejcc_NCYL;
    u1s_emfng_xreqclr_Lch = (u1)big_wdiaginfclr_xreqclr;

    /********************/
    /* �v�Z�l�ϐ��̎Z�o */
    /********************/
    emfng_mcr_cal();

    /*************************************************/
    /* ecdmfaavTv�AecdmfavTv[](mode$06 TID$0B)�̎Z�o */
    /*************************************************/

    u1t_exrcdmf = u1s_emfng_exrcdmf();

    if ( ( bis_emfng_excntmf == (u1)OFF )   /* �د�ߌp�����łȂ� */
      && ( u1t_exrcdmf == (u1)OFF ) )       /* �v�Z�������Ȃ� */
    {
        u4t_cdmfaavTv = (u4)u2g_emfng_ecdmfaavTv();
        u4t_cdmfaavTv = u4g_glmulstngrd_u2u2u2( (u2)u4t_cdmfaavTv, (u2)(((0.9)/(1./256./256.))+0.5), (u2)16U );

        u4t_cdmfaemTv = (u4)u2g_emfng_ecdmfaemTv();
        u4t_cdmfaemTv = u4g_glmulstngrd_u2u2u2( (u2)u4t_cdmfaemTv, (u2)(((0.1)/(1./256./256.))+0.5), (u2)16U );

        /* �O��ecdmfaavTv*0.9 + ecdmfaemTv*0.1 */
        u4t_cdmfaavTv += u4t_cdmfaemTv;
        ELIB_HIGHGD2( u4t_cdmfaavTv, (u4)u2g_U2MAX, u4t_cdmfaavTv );
        u2t_cdmfaavTv = (u2)u4t_cdmfaavTv;

        /* ���񎸉Ή�*0.1�{�O��܂ł̕���*0.9(�S�C��)�ymode$06-TID$0B�z*/
        (void)s4g_ememctr_write( u2g_EMFNG_ECDMFAAVTV_U2_ID, (void *)&u2t_cdmfaavTv );                 /* �߂�l�͎g�p���Ȃ� */
        /* ecdmfaavTv���艺�� */
        u2t_ECDMFAAVMNTL_MI_c = u2g_emfng_ECDMFAAVMNTL_MI;
        (void)s4g_ememctr_write( u2g_EMFNG_ECDMFAAVMNTL_U2_ID, (void *)&u2t_ECDMFAAVMNTL_MI_c );       /* �߂�l�͎g�p���Ȃ� */
        /* ecdmfaavTv������ */
        u2t_cdmfaavMxtl = (u2)0xffffU;
        (void)s4g_ememctr_write( u2g_EMFNG_ECDMFAAVMXTL_U2_ID, (void *)&u2t_cdmfaavMxtl );             /* �߂�l�͎g�p���Ȃ� */

#if ( JETCORE_D == u1g_EJCC_USE ) && ( JEOBDUDS_D == u1g_EJCC_NOT_USE )                                /*�yt-CORE�Ή��L�zAND�yOBDonUDS�Ή����z*/
        u2t_ecdmfaavTv   = u2g_emfng_ecdmfaavTv();
        u2t_ecdmfaavMntl = u2g_emfng_ecdmfaavMntl();
        u2t_ecdmfaavMxtl = u2g_emfng_ecdmfaavMxtl();
        (void)u1g_wtcif_dem_setdtr_u2s4s4s4u1( u2g_WTCIF_DEM_DTR_ECDMFAAV, (s4)u2t_ecdmfaavTv, (s4)u2t_ecdmfaavMntl, (s4)u2t_ecdmfaavMxtl, u1g_WTCIF_DEM_DTR_CTL_NORMAL );  /* �߂�l�͎g�p���Ȃ� */
#endif
        u2t_ECDMFAVMNTL_MI_c = u2g_emfng_ECDMFAVMNTL_MI;
        for ( s4t_cyl = (s4)0; s4t_cyl < (s4)u1t_ncyl_c; s4t_cyl++ )
        {
            u4t_cdmfavTv = (u4)u2g_emfng_ecdmfavTv( (u1)s4t_cyl );
            u4t_cdmfavTv = u4g_glmulstngrd_u2u2u2( (u2)u4t_cdmfavTv, (u2)(((0.9)/(1./256./256.))+0.5), (u2)16U );

            u4t_cdmfemTv = (u4)u2g_emfng_ecdmfemTv( (u1)s4t_cyl );
            u4t_cdmfemTv = u4g_glmulstngrd_u2u2u2( (u2)u4t_cdmfemTv, (u2)(((0.1)/(1./256./256.))+0.5), (u2)16U );

            /* �O��ecdmfavTv[]*0.9 + ecdmfemTv[]*0.1 */
            u4t_cdmfavTv += u4t_cdmfemTv;
            ELIB_HIGHGD2( u4t_cdmfavTv, (u4)u2g_U2MAX, u4t_cdmfavTv );
            u2t_cdmfavTv = (u2)u4t_cdmfavTv;

            /* ���񎸉Ή�*0.1�{�O��܂ł̕���*0.9(�C����) �ymode$06-TID$0B�z */
            (void)s4g_ememctr_write( u2s_ECDMFAVTV_U2_ID[s4t_cyl], (void *)&u2t_cdmfavTv );            /* �߂�l�͎g�p���Ȃ� */
            /* ecdmfavTv[]���艺�� */
            (void)s4g_ememctr_write( u2s_ECDMFAVMNTL_U2_ID[s4t_cyl], (void *)&u2t_ECDMFAVMNTL_MI_c );  /* �߂�l�͎g�p���Ȃ� */
            /* ecdmfavTv[]������ */
            u2t_cdmfavMxtl = (u2)0xffffU;
            (void)s4g_ememctr_write( u2s_ECDMFAVMXTL_U2_ID[s4t_cyl], (void *)&u2t_cdmfavMxtl );        /* �߂�l�͎g�p���Ȃ� */
#if ( JETCORE_D == u1g_EJCC_USE ) && ( JEOBDUDS_D == u1g_EJCC_NOT_USE )                                /*�yt-CORE�Ή��L�zAND�yOBDonUDS�Ή����z*/
            u2t_dtrid = u2s_emfng_ecdmfav_tbl[s4t_cyl];
            u2t_ecdmfavTv   = u2g_emfng_ecdmfavTv( (u1)s4t_cyl );
            u2t_ecdmfavMntl = u2g_emfng_ecdmfavMntl( (u1)s4t_cyl );
            u2t_ecdmfavMxtl = u2g_emfng_ecdmfavMxtl( (u1)s4t_cyl );
            (void)u1g_wtcif_dem_setdtr_u2s4s4s4u1( u2t_dtrid, (s4)u2t_ecdmfavTv, (s4)u2t_ecdmfavMntl, (s4)u2t_ecdmfavMxtl, u1g_WTCIF_DEM_DTR_CTL_NORMAL );  /* �߂�l�͎g�p���Ȃ� */
#endif
        }
        /**************************************/
        /* exrcdmf(mode$06�v�Z�����׸�)�̑��� */
        /**************************************/
        u1t_exrcdmf = (u1)ON;
        (void)s4g_ememctr_write( u2g_EMFNG_EXRCDMF_U1_ID, (void *)&u1t_exrcdmf );                      /* �߂�l�͎g�p���Ȃ� */
    }

    /*******************************/
    /* mode$06�p ���ζ����̸ر���� */
    /*******************************/
    if ( ( bis_emfng_excntmf == (u1)OFF )       /* �د�ߌp�����łȂ� */
#if JEOBDUDS_D == u1g_EJCC_NOT_USE              /*�yOBDonUDS�Ή����z*/
      && ( u1g_exst_exastnrm == (u1)ON )        /* exastnrm OFF->ON */
#else                                           /*�yOBDonUDS�Ή��L�z*/
      && ( big_wpsajdg_xpsa == (u1)ON )         /* xpsa OFF->ON */
#endif
       )
    {   /* �n����A�������������bis_emfng_excntmf=ON�ƂȂ�ׁAu1g_exst_exastnrm/big_wpsajdg_xpsa == ON�Ŕ��肷�� */
        /* ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�S�C��)�ر�ymode$06-TID$0C�z*/
        u2t_ECDMFAEMTV_MI_c = u2g_emfng_ECDMFAEMTV_MI;
        (void)s4g_ememctr_write( u2g_EMFNG_ECDMFAEMTV_U2_ID, (void *)&u2t_ECDMFAEMTV_MI_c );           /* �߂�l�͎g�p���Ȃ� */

        u2t_ECDMFEMTV_MI_c = u2g_emfng_ECDMFEMTV_MI;
#if ( JETCORE_D == u1g_EJCC_USE ) && ( JEOBDUDS_D == u1g_EJCC_NOT_USE )                            /*�yt-CORE�Ή��L�zAND�yOBDonUDS�Ή����z*/
        u2t_ecdmfaemTv   = u2g_emfng_ecdmfaemTv();
        u2t_ecdmfaemMntl = u2g_emfng_ecdmfaemMntl();
        u2t_ecdmfaemMxtl = u2g_emfng_ecdmfaemMxtl();
         (void)u1g_wtcif_dem_setdtr_u2s4s4s4u1( u2g_WTCIF_DEM_DTR_ECDMFAEM, (s4)u2t_ecdmfaemTv, (s4)u2t_ecdmfaemMntl, (s4)u2t_ecdmfaemMxtl, u1g_WTCIF_DEM_DTR_CTL_NORMAL );  /* �߂�l�͎g�p���Ȃ� */
#endif
        for ( s4t_cyl = (s4)0; s4t_cyl < (s4)u1t_ncyl_c; s4t_cyl++ )
        {
            /* ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�C����)�ر�ymode$06-TID$0C�z*/
            (void)s4g_ememctr_write( u2s_ECDMFEMTV_U2_ID[s4t_cyl], (void *)&u2t_ECDMFEMTV_MI_c );      /* �߂�l�͎g�p���Ȃ� */
#if ( JETCORE_D == u1g_EJCC_USE ) && ( JEOBDUDS_D == u1g_EJCC_NOT_USE )                            /*�yt-CORE�Ή��L�zAND�yOBDonUDS�Ή����z*/
            u2t_dtrid       = u2s_emfng_ecdmfem_tbl[s4t_cyl];
            u2t_ecdmfemTv   = u2g_emfng_ecdmfemTv( (u1)s4t_cyl );
            u2t_ecdmfemMntl = u2g_emfng_ecdmfemMntl( (u1)s4t_cyl );
            u2t_ecdmfemMxtl = u2g_emfng_ecdmfemMxtl( (u1)s4t_cyl );
            (void)u1g_wtcif_dem_setdtr_u2s4s4s4u1( u2t_dtrid, (s4)u2t_ecdmfemTv, (s4)u2t_ecdmfemMntl, (s4)u2t_ecdmfemMxtl, u1g_WTCIF_DEM_DTR_CTL_NORMAL );  /* �߂�l�͎g�p���Ȃ� */
#endif
        }

        /* exrcdmf(mode$06�v�Z�����׸�)�̸ر */
        u1t_exrcdmf = (u1)OFF;
        (void)s4g_ememctr_write( u2g_EMFNG_EXRCDMF_U1_ID, (void *)&u1t_exrcdmf );                      /* �߂�l�͎g�p���Ȃ� */

        bis_emfng_excntmf = (u1)ON;     /* �د�ߌp���׸޾�� */
    }

    /**************************************/
    /* �G�}OT���وُ팟�o���L���׸ނ̑��� */
    /**************************************/
    emfng_xottd_cal();

    /**************************/
    /* �G�}OT���قُ̈�̌��o */
    /**************************/
    if ( ( u2g_emfng_ecjmfot >= u2t_LJMFOT_c )      /* lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev */
      || ( ( u2g_emfng_ecjmfem >= u2t_LJMFEM_c )
        && ( u2g_emfng_ecjmfot >= u2t_LJMFOTF_c ) ) )
    {
        /****************/
        /* ���o�������� */
        /****************/
        emfng_ot_detect_ptptptpt( &u1t_xumfot, &u1t_xdmfot, &u1t_xhmfoton, &u1t_xhmfotoff );

#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
        /*******************/
        /* �s�꒲��RAM�X�V */
        /*******************/
        emfng_eocmfmlt_pt( &u1g_emfng_ecdmfw[0] );
#endif

        /*****************************/
        /* mode$06�Ή����ζ����̑��� */
        /*****************************/
        emfng_emode06_cal();

        /**********************************/
        /* �G�}OT���وُ팟�o�I�����̏��� */
        /**********************************/
        glint_di(); /* ������ ���荞�݋֎~ ������ */

        /* �e��J�E���^�̃N���A���� */
        u2g_emfng_ecjmfot        = (u2)0U;
        u1g_emfng_ecdmfaotbnk[0] = (u1)0U;   /* CJMFOT�Ɠ����ɃN���A���� */
        u1g_emfng_ecdmfaotbnk[1] = (u1)0U;   /* CJMFOT�Ɠ����ɃN���A���� */
        u1g_emfng_ecdmfaot       = (u1)0U;   /* CJMFOT�Ɠ����ɃN���A���� */
        u1g_emfng_ecdtmf2        = (u1)0U;   /* CJMFOT�Ɠ����ɃN���A���� */
        u2g_emfng_ecmfot         = (u2)0U;   /* CJMFOT�Ɠ����ɃN���A���� */
        s4s_emfng_emfrtotsum     = (s4)0;    /* CJMFOT�Ɠ����ɃN���A���� */
        u2s_emfng_ecmfotcnt      = (u2)0U;   /* CJMFOT�Ɠ����ɃN���A���� */
        bis_emfng_excdmfwclr  = (u1)ON;      /* CDMFW���޲��޺��ޏ�����ɃN���A���� */
        big_emfng_excdmfemclr = (u1)ON;      /* CDMFEM���޲��޺��ޏ�����ɃN���A���� */

        glint_ei(); /* ������ ���荞�݋��� ������ */
    }   /* �G�}OT���وُ팟�o���ݸ� end */

    /***************************/
    /* ���Ύ���NE,���׍X�V�ʒm */
    /***************************/
    if ( ( u1t_xdmfot == (u1)ON )                  /* �G�}OT���x���ُ� */
      && ( big_emfng_excdmfw == (u1)ON ) )         /* �Ό��C������(�y4�C���z����OFF�Œ�) */
    {
        emfok_mfneld_ann();
    }

    /************************/
    /* EM�������وُ�̌��o */
    /************************/
#if ( JEMFDTC_D == u1g_EJCC_USE ) && ( JETCORE_D == u1g_EJCC_USE ) && ( JEOBDUDS_D == u1g_EJCC_USE )    /*�y����OBD DTC�L�zAND�yt-CORE�Ή��L�zAND�yOBDonUDS�Ή��L�z*/
    u1s_emfng_pas = (u1)OFF;                    /* �d�l�������x������^�C�~���O�s�����������׸�OFF */
#endif
    if ( u2g_emfng_ecjmfem >= u2t_LJMFEM_c ) /* lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev ���s���ݸ� */
    {
#if ( JEMFDTC_D == u1g_EJCC_USE ) && ( JETCORE_D == u1g_EJCC_USE ) && ( JEOBDUDS_D == u1g_EJCC_USE )    /*�y����OBD DTC�L�zAND�yt-CORE�Ή��L�zAND�yOBDonUDS�Ή��L�z*/
        u1s_emfng_pas = (u1)ON;                 /* �d�l�������x������^�C�~���O�����������׸�ON */
                                                /* emfng_wxmf_out()�R�[���O�Ɏ��{ */
#endif
#if JEEFI == u1g_EJCC_DUAL   /*�y�ޭ��INJ�z*/
        /**********************************/
        /* �e����Ӱ�޸ر�p1000rev����ʒm */
        /**********************************/
        emfok_mfcmodclr();
#endif

        /* ���H��ԃJ�E���^������񐔈ȏ�ł́u���΃J�E���^-���H�J�E���^�~n�v�ňُ픻�� */
        u2t_cdtmfwa = u2s_emfng_ecdtmfwa;

        s4t_cdmfae2 = (s4)u2g_emfng_ecdmfae2;
        if ( u2t_cdtmfwa >= (u2)u1g_emfng_CDTMFWA )
        {
            s4t_cdmfae2 -= (s4)u4g_glmulstngrd_u2u2u2( u2t_cdtmfwa, (u2)u1s_emfng_KCDTMFWA, (u2)5U );
                                     /* 1*8/256 -> 1(��)  u2*u1�̂��߁As4����̃I�[�o�[�t���[���� */
            ELIB_LOWGD2( s4t_cdmfae2, (s4)0, s4t_cdmfae2 );            /* �����K�[�h */
        }

#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
        /*******************/
        /* �s�꒲��RAM�X�V */
        /*******************/
        emfng_eocmfn_u2( (u2)s4t_cdmfae2 );    /* (u2-u2*u1)�̂��߁Au2�̏�����K�[�h�s�v */
#endif

        /****************/
        /* ���o�������� */
        /****************/
        emfng_em_detect_u2ptpt( (u2)s4t_cdmfae2, &u1t_xdmfem, &u1t_xumfem );

        /**********************************/
        /* EM�������وُ팟�o�I�����̏��� */
        /**********************************/
        glint_di(); /* ������ ���荞�݋֎~ ������ */

        /* �e��J�E���^�̃N���A���� */
        u2g_emfng_ecjmfot        = (u2)0U;
        u1g_emfng_ecdmfaotbnk[0] = (u1)0U;      /* CJMFOT�Ɠ����ɸر���� */
        u1g_emfng_ecdmfaotbnk[1] = (u1)0U;      /* CJMFOT�Ɠ����ɸر���� */
        u1g_emfng_ecdmfaot       = (u1)0U;      /* CJMFOT�Ɠ����ɸر���� */
        bis_emfng_excdmfwclr     = (u1)ON;      /* CDMFW���޲��޺��ޏ�����ɸر���� */
        u2g_emfng_ecjmfem        = (u2)0U;
        bis_emfng_excdmfae2clr   = (u1)ON;      /* CDMFAE2���޲��޺��ޏ�����ɸر���� */
        u1g_emfng_ecdmfaem       = (u1)0U;      /* CJMFEM�Ɠ����ɸر���� */
        u2g_emfng_ecmfot         = (u2)0U;      /* CJMFOT�Ɠ����ɸر���� */
        u2s_emfng_ecdtmfwa       = (u2)0U;      /* CJMFEM�Ɠ����ɸر���� */
        u1g_emfng_ecdtmf2        = (u1)0U;      /* CJMFOT�Ɠ����ɸر���� */
        s4s_emfng_emfrtotsum     = (s4)0;       /* CJMFOT�Ɠ����ɸر���� */
        u2s_emfng_ecmfotcnt      = (u2)0U;      /* CJMFOT�Ɠ����ɸر���� */
        big_emfng_excdmfemclr    = (u1)ON;      /* CDMFEM���޲��޺��ޏ�����ɸر���� */
        bis_emfng_excdmfem2clr   = (u1)ON;      /* CDMFEM2���޲��޺��ޏ�����ɸر���� */

        glint_ei(); /* ������ ���荞�݋��� ������ */

        u1t_xjokmf  = (u1)ON;            /* EM�������وُ픻����1�د�ߔ�����s�׸�ON */
        if ( u1t_cjemrev < u1g_U1MAX )
        {
            u1t_cjemrev++;
        }
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
        /* �s�꒲��RAM�̸ر���� */
        emfng_espdaemclr();
#endif
    }   /* EM�������ٔ������ݸ� end */

#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
    /********************/
    /* DI�ُ�̌��o���� */
    /********************/
    if ( u2s_emfng_ecjmfdi >= u2t_LJMFOT_c )
    {
        emfng_di_detect_ptpt( &u1t_xdmfdi, &u1t_xumfdi );
    }

    /*********************/
    /* PFI�ُ�̌��o���� */
    /*********************/
    if ( u2s_emfng_ecjmfpfi >= u2t_LJMFOT_c )
    {
        emfng_pfi_detect_ptpt( &u1t_xdmfpfi, &u1t_xumfpfi );
    }
#endif

    /* �G�}OT����,EM��������,DI,PFI�ُ̈�����픻��ۗ��MIL�_�ŗv���̌��ʂ�RAM�� */
    /* emfng_wxmf_out()�R�[���O�Ɏ��{ */
    glbitcp_bibi( u1t_xdmfot,    bis_emfng_exdmfot );         /* �G�}OT���وُ픻���׸� */
    glbitcp_bibi( u1t_xumfot,    bis_emfng_exumfot );         /* �G�}OT���ِ��픻��ۗ��׸� */
    glbitcp_bibi( u1t_xhmfoton,  bis_emfng_exhmfoton );       /* �G�}OT�ɂ��MIL�_�ŗv���׸� */
    glbitcp_bibi( u1t_xhmfotoff, bis_emfng_exhmfotoff );      /* �G�}OT�ɂ��MIL�_�ŷ�ݾٗv���׸� */
    glbitcp_bibi( u1t_xdmfem,    bis_emfng_exdmfem );         /* EM�������وُ팟�o�׸� */
    glbitcp_bibi( u1t_xumfem,    bis_emfng_exumfem );         /* EM�������ِ��픻��ۗ��׸� */
#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
    glbitcp_bibi( u1t_xdmfdi,    bis_emfng_exdmfdi );         /* DI�ُ��׸� */
    glbitcp_bibi( u1t_xumfdi,    bis_emfng_exumfdi );         /* DI�ُ�ɂ�鐳�픻��ۗ��׸� */
    glbitcp_bibi( u1t_xdmfpfi,   bis_emfng_exdmfpfi );        /* PFI�ُ��׸� */
    glbitcp_bibi( u1t_xumfpfi,   bis_emfng_exumfpfi );        /* PFI�ُ�ɂ�鐳�픻��ۗ��׸� */
#endif

#if JEMFDTC_D == u1g_EJCC_USE /*�y����OBD DTC�L�z*/
    /********************/
    /* �d�Z�ւ̒ʒm���� */
    /********************/
    emfng_wxmf_out();
#endif

    /**************************/
    /* �_�C�A�O����̏����v�� */
    /**************************/
    u1t_xreqclr = u1s_emfng_wxreqclr();
    if ( u1t_xreqclr == (u1)ON )
    {
        u1t_xjokmf       = (u1)OFF;
        u1t_cjemrev      = (u1)0U;             /* exjokmf�Ɠ����ɸر */
        bis_emfng_exdmf1 = (u1)OFF;
    }

#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
    if ( bis_emfng_excdmfdiclr == (u1)ON )
    {
        for ( s4t_i = (s4)0; s4t_i < (s4)u1t_ncyl_c; s4t_i++ )
        {
            u1s_emfng_exdmfdim[s4t_i] = (u1)OFF;
        }
    }
    if ( bis_emfng_excdmfpficlr == (u1)ON )
    {
        for ( s4t_i = (s4)0; s4t_i < (s4)u1t_ncyl_c; s4t_i++ )
        {
            u1s_emfng_exdmfpfim[s4t_i] = (u1)OFF;
        }
    }
#endif

    /* Disable�׸ނ̑��� */
    u1t_exdisable = (u1)OFF;  /*�yOBD2�K���L�zAND�y�ΕĖ@�K�z����OFF�Œ� */
#if JEMAT_OBD2 == u1g_EJCC_NOT_USE    /*�yOBD2�K�����z*/
    if ( u1t_xmfKwp == (u1)ON )
    {
        u1t_exdisable = (u1)ON;
    }
#endif
#if JEMFHOUKI == u1g_EJCC_NOT_USAMF  /*�y�ΕĖ@�K�ȊO�z*/
    if ( s2g_etha_etha < (s2)(((-10.)/(160./256.)) - 0.5) )
    {
        u1t_exdisable = (u1)ON;
    }
#endif
    if ( u1t_xreqclr == (u1)ON )   /* �f�[�^�����v���� */
    {
        u1t_exdisable = (u1)OFF;
    }

    /* Complete�׸ނ̑��� */
#if JEMAT_OBD2 == u1g_EJCC_NOT_USE    /*�yOBD2�K�����z*/
    u1t_excomplete = (u1)OFF;
    if ( u1t_xmfKwp == (u1)OFF )
#endif
    {
        u1t_excomplete = (u1)ON;  /*�yOBD2�K���L�z����ON�Œ� */
    }

    /* RAM�f�[�^�Ɋi�[ */
    u1s_emfng_ecjemrev = u1t_cjemrev;
    glbitcp_bibi( u1t_xjokmf, big_emfng_exjokmf );
    glbitcp_bibi( u1t_excomplete, big_emfng_excomplete );
    glbitcp_bibi( u1t_exdisable, big_emfng_exdisable );
}

/*********************************************************************/
/*  �֐���        | emfng_mcr_cal( )                                 */
/*  �������e      | �v�Z�l�ϐ��̎Z�o                                 */
/*  ����^�C�~���O| pwon,65ms(emfng_pwon(),emfng_65msl()����R�[��)  */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      | �����֐�                                         */
/*********************************************************************/
static void
emfng_mcr_cal( void )
{
    u4 u4t_ekldmfw1_mcr;        /* lsb=1,unit=�� :�Ό��C�����Ή񐔔��艺���l(�v�Z�l) */
#if JENCYL == u1g_EJCC_6CYL     /*�y6�C���z*/
    u4 u4t_ekldmfw2_mcr;        /* lsb=1,unit=�� :�Ό��C�����Ή񐔔������l(�v�Z�l) */
#endif
    u4 u4t_ekldmfoth_mcr;       /* lsb=1,unit=�� :�G�}OT���َ��Ή񐔔���l(�v�Z�l) */
    u4 u4t_eldmfaem_mcr;        /* lsb=1,unit=�� :EM�������َ��Ή񐔔���l(�v�Z�l) */
    u2 u2t_LJMFOT_c;            /* lsb=2/u1g_EJCC_NCYL,unit=rev :�G�}OT���x���ُ픻����s�^�C�~���O */
    u2 u2t_LJMFEM_c;            /* lsb=2/u1g_EJCC_NCYL,unit=rev :EM�������وُ픻����s���ݸ� */
    u2 u2t_KLDMFOT_c;           /* lsb=1,unit=�� :�G�}OT���َ��Ή񐔔���l(100�_��/1�C���ӂ�) */

    /* ���[�N�f�[�^������ */
    u2t_LJMFOT_c = u2g_emfng_LJMFOT;
    u2t_LJMFEM_c = u2g_emfng_LJMFEM;
    u2t_KLDMFOT_c = u1s_emfng_KLDMFOT;

    /* �Ό��C�����Ή񐔔��艺���l(�v�Z�l)�̎Z�o */
    /* ekldmfw1_mcr �� emfng_LJMFOT �� ((�C�����^2) �^ (�C�����^2)) �� emfng_KLD1 */
    u4t_ekldmfw1_mcr = u4g_glmulstngrd_u2u2u2( u2t_LJMFOT_c, (u2)u1s_emfng_KLD1, (u2)6U );
    u4t_ekldmfw1_mcr = (u4)u2g_gldiv_u4u2( u4t_ekldmfw1_mcr, (u2)u1g_ejcc_NCYL );
                                                /* lsb=(2/NCYL)*(2/256) -> 1,unit=�� */
    ELIB_HIGHGD2( u4t_ekldmfw1_mcr, (u4)u1g_U1MAX, u4t_ekldmfw1_mcr );
    u1s_emfng_ekldmfw1_mcr = (u1)u4t_ekldmfw1_mcr;

#if JENCYL == u1g_EJCC_6CYL     /*�y6�C���z*/
    /* �Ό��C�����Ή񐔔������l(�v�Z�l)�̎Z�o */
    /* ekldmfw2_mcr �� emfng_LJMFOT �� ((�C�����^2) �^ (�C�����^2)) �� emfng_KLD2 */
    u4t_ekldmfw2_mcr = u4g_glmulstngrd_u2u2u2( u2t_LJMFOT_c, (u2)u1s_emfng_KLD2, (u2)6U );
    u4t_ekldmfw2_mcr = (u4)u2g_gldiv_u4u2( u4t_ekldmfw2_mcr, (u2)u1g_ejcc_NCYL );
                                                /* lsb=(2/NCYL)*2/256 -> 1,unit=�� */
    ELIB_HIGHGD2( u4t_ekldmfw2_mcr, (u4)u1g_U1MAX, u4t_ekldmfw2_mcr );
    u1s_emfng_ekldmfw2_mcr = (u1)u4t_ekldmfw2_mcr;
#endif

    /* �G�}OT���َ��Ή񐔔���l(�v�Z�l)�̎Z�o */
    u4t_ekldmfoth_mcr = u4g_glmul_u2u2( (u2)u2t_KLDMFOT_c, (u2)u1g_ejcc_NCYL );
                                                /* lsb=1 * 1 -> 1,unit=�� */
    u4t_ekldmfoth_mcr = (u4)u2g_gldiv_u4u2( u4t_ekldmfoth_mcr, (u2)u1g_emfng_CATN );
                                                /* lsb=1 / 1 -> 1,unit=�� */
    u2g_emfng_ekldmfoth_mcr = (u2)u4t_ekldmfoth_mcr;

    /* EM�������َ��Ή񐔔���l(�v�Z�l)�̎Z�o */
    /* eldmfaem_mcr �� emfng_LJMFEM �� (�C�����^2) �� emfng_MFDD �^ 100 �� emfng_MFD1 */
    u4t_eldmfaem_mcr = u4g_glmul_u2u2( u2t_LJMFEM_c, (u2)s2s_emfng_MFDD );  /* emfng_MFDD(���Η�)�͕K�����̂���u2�L���X�g����OK */
                                                /* lsb=(2/NCYL)*(256/128/256) -> 256/128/256 */
                                                /* emfng_LJMFEM��LSB�ϊ���(�C����/2)�̉��Z���ʂ�1�ɂȂ邽�ߏ����ȗ� */
    u4t_eldmfaem_mcr = u4g_glmulst_u4u4u2( u4t_eldmfaem_mcr, (u4)u2s_emfng_MFD1, (u2)22U );
                                                /* lsb=(256/128/256)*(2/256/256) -> 1 */
    u4t_eldmfaem_mcr = (u4)u2g_gldiv_u4u2( u4t_eldmfaem_mcr, (u2)100U );
    u2g_emfng_eldmfaem_mcr = (u2)u4t_eldmfaem_mcr;

    /* ����޽��Ď�EM�������َ��Ή񐔔���l(�v�Z�l)�̎Z�o */
    u2s_emfng_eldmfst1_mcr = u2g_glmulst_u2u2u2( (u2)u4t_eldmfaem_mcr, (u2)u1s_emfng_ST1RTO, (u2)5U );
                                                /* lsb=1 * (8/256) -> 1,unit=�� */

    /* ίĽ��Ď�EM�������َ��Ή񐔔���l(�v�Z�l)�̎Z�o */
    u2s_emfng_eldmfst2_mcr = u2g_glmulst_u2u2u2( (u2)u4t_eldmfaem_mcr, (u2)u1s_emfng_ST2RTO, (u2)5U );
                                                /* lsb=1 * (8/256) -> 1,unit=�� */

    /* DTC�o�͋C������l(�v�Z�l)�̎Z�o */
    u2s_emfng_emfk_mcr = u2g_glmulst_u2u2u2( (u2)u4t_eldmfaem_mcr, (u2)u1s_emfng_KMFK, (u2)7U );
                                                /* lsb=1 * (2/256) -> 1,unit=�� */

#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    /* ���Ή񐔏��A���A��p�x����񐔂̎Z�o */
    u2s_emfng_ecmfnl_mcr = u2g_glmulst_u2u2u2( (u2)u4t_eldmfaem_mcr, (u2)u1s_emfng_MFLOW, (u2)7U );
    u2s_emfng_ecmfnm_mcr = u2g_glmulst_u2u2u2( (u2)u4t_eldmfaem_mcr, (u2)u1s_emfng_MFMID, (u2)7U );
    u2s_emfng_ecmfnh_mcr = u2g_glmulst_u2u2u2( (u2)u4t_eldmfaem_mcr, (u2)u1s_emfng_MFHI,  (u2)7U );
                                                /* lsb=1 * (2/256) -> 1,unit=�� */
#endif

}

/*********************************************************************/
/*  �֐���        | emfng_xottd_cal( )                               */
/*  �������e      | ����َ��Ό��C�����ΐ�p                          */
/*                | �G�}OT���وُ팟�o���L���׸ނ̑���               */
/*  ����^�C�~���O| 65ms(emfng_65msl()����R�[��)                    */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      | �����֐�                                         */
/*********************************************************************/
static void
emfng_xottd_cal( void )
{
    s4 s4t_i;           /* lsb=1 :for���[�v�ϐ� */
    u1 u1t_ncyl_c;      /* lsb=1 :�C���� */
#if JENCYL == u1g_EJCC_6CYL    /*�y6�C���z*/
    s4 s4t_cnt;         /* lsb=1 :���΋C�������� */
    u1 u1t_ncylw_c;     /* lsb=1 :�C���Q�� */
#endif
    s4 s4t_mfci;        /* lsb=1 :ecdmfemi[] >= emfng_MFSTEMI�����񐔶��� */
    s4 s4t_mfrtot;      /* lsb=256/128/256,unit=% :emfrtotsum/ecmfotcnt */
    s4 s4t_cdmfaot;     /* lsb=1,unit=�� :�G�}OT���x���S�C�����΃J�E���^ */
    s4 s4t_cdmfaotbnk[2];  /* lsb=1,unit=�� :�o���N�ʐG�}OT���x�����΃J�E���^ */
#if JENCYL == u1g_EJCC_6CYL    /*�y6�C���z*/
    s4 s4t_cdmfw;       /* lsb=1,unit=�� :�Ό��C�����ζ��� */
    u1 u1t_excdmfwtmp;  /* lsb=1 :�����ꂩ�̋C���Q�ʑΌ����ζ����ɂ��G�}OT���� */
    u1 u1t_ekldmfw1_mcr; /* lsb=1,unit=�� :�Ό��C�����Ή񐔔��艺���l(�v�Z�l) */
#endif
    u1 u1t_xcdmfaot;    /* lsb=1 :�G�}OT���ζ����ɂ��G�}OT���萬���׸� */
    u1 u1t_excdmfw;     /* lsb=1 :�Ό��C�����Δ��萬���׸� */
    u1 u1t_exottd;      /* lsb=1 :�G�}OT���وُ팟�o���L���׸� */
    u1 u1t_xdtmf2;      /* lsb=1 :�G�}OT����p���H�����l���� */
    s4 s4t_cdtmf2;      /* lsb=1,unit=�� :�G�}OT���ٔ���p���H���� */
    s4 s4t_kcdmfaotb;   /* :ecdtmf2 �� emfng_KCDTMFAOTB */
    s4 s4t_cdmfaotb;    /* lsb=1,unit=�� :ecdmfaot-ecdtmf2�̃��b�`(MODE06�p) */
    s4 s4t_emfrtotsum;  /* lsb=256/128/256,unit=% :�ώZ���Δ���l */
    u2 u2t_ecmfotcnt;   /* lsb=1,unit=�� :���ώZ�o�p�ώZ�� */
    s4 s4t_ekldmfot;    /* lsb=1,unit=�� :�G�}OT���َ��Ή񐔔���l */
#if JENCYL == u1g_EJCC_6CYL    /*�y6�C���z*/
    u1 u1t_ecdmfw[u1g_EJCC_NCYL/2]; /* lsb=1,unit=�� :�Ό��C�����ζ��� */
#endif
    u2 u2t_ecjmfot;     /* lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev :�G�}OT���َ��Ό��o���¶��� */
    u1 u1t_MFSTEMI_c;   /* lsb=1,unit=�� :�A�C�h�����C���ʎ��Ή񐔔���l */
    u2 u2t_LJMFOT_c;    /* lsb=2/u1g_EJCC_NCYL,unit=rev :�G�}OT���x���ُ픻����s�^�C�~���O */
    u2 u2t_LJMFEM_c;    /* lsb=2/u1g_EJCC_NCYL,unit=rev :EM�������x���ُ픻����s�^�C�~���O */
    u2 u2t_LJMFOTF_c;   /* lsb=2/u1g_EJCC_NCYL,unit=rev :�G�}OT���x���ُ픻����s�^�C�~���O */

    /* ���[�N�f�[�^������ */
    u1t_exottd = (u1)bis_emfng_exottd;
#if JENCYL == u1g_EJCC_6CYL    /*�y6�C���z*/
    u1t_ekldmfw1_mcr = u1s_emfng_ekldmfw1_mcr;
#endif
    u2t_ecjmfot   = u2g_emfng_ecjmfot;
    u2t_LJMFOT_c = u2g_emfng_LJMFOT;
    u2t_LJMFEM_c = u2g_emfng_LJMFEM;
    u2t_LJMFOTF_c = u2s_emfng_LJMFOTF;
    u1t_ncyl_c = u1g_ejcc_NCYL;

    if ( u2g_emfng_ecjmfoti >= u2s_emfng_LJMFOTI )  /* lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev */
    {
        /**************************************/
        /* �G�}OT���وُ팟�o���L���׸ނ̑��� */
        /**************************************/
        u1t_MFSTEMI_c = u1s_emfng_MFSTEMI;
        s4t_mfci = (s4)0;
        for ( s4t_i = (s4)0; s4t_i < (s4)u1t_ncyl_c; s4t_i++ )
        {
            if ( u1g_emfng_ecdmfemi[s4t_i] >= u1t_MFSTEMI_c )
            {
                s4t_mfci++;
            }
        }

        u1t_exottd = (u1)OFF;
        if ( ( u2g_emfng_ecdmfaoti <= (u2)u1s_EMFNG_MFSTOTI )
          && ( s4t_mfci == (s4)2 ) )
        {
            u1t_exottd = (u1)ON;
        }
        emfng_cdmfi_reset(); /* �G�}OT���ٱ���َ����Ό��o���¶����̸ر */
    }

    /* �G�}OT���وُ팟�o���ݸ� */
    if ( ( u2t_ecjmfot >= u2t_LJMFOT_c )      /* lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev */
      || ( ( u2g_emfng_ecjmfem >= u2t_LJMFEM_c )
        && ( u2t_ecjmfot >= u2t_LJMFOTF_c ) ) )
    {
        s4t_cdtmf2 = (s4)u1g_emfng_ecdtmf2;  /* ���O���� */
        u1t_xdtmf2 = (u1)OFF;
        if ( s4t_cdtmf2 >= (s4)u1s_emfng_CDTMF2 )
        {
            u1t_xdtmf2 = (u1)ON;
        }

        /*********************************/
        /* ���Ή�CDMFAOT�ɂ��������� */
        /*********************************/
        s4t_cdmfaot       = (s4)u1g_emfng_ecdmfaot;           /* �Q�Ɨp */
        s4t_cdmfaotbnk[0] = (s4)u1g_emfng_ecdmfaotbnk[0];     /* �Q�Ɨp */
        s4t_cdmfaotbnk[1] = (s4)u1g_emfng_ecdmfaotbnk[1];     /* �Q�Ɨp */

        s4t_cdmfaotb = s4t_cdmfaot;

        if ( u1t_xdtmf2 == (u1)ON )
        {
            s4t_kcdmfaotb = s4g_glmulstngrd_s2s2u2( (s2)s4t_cdtmf2, (s2)u1s_emfng_KCDTMFAOTB, (u2)5U );          /* lsb=1*8/256 -> 1(��) */

            s4t_cdmfaot -= s4t_kcdmfaotb;
            s4t_cdmfaotb = s4t_cdmfaot;            /* MODE06�Z�o�p�ɉ����K�[�h�O�Ƀ��b�` */

            s4t_cdmfaotbnk[0] -= s4t_kcdmfaotb;
            s4t_cdmfaotbnk[1] -= s4t_kcdmfaotb;
            if ( s4t_cdmfaot < (s4)0 )        /* �����K�[�h */
            {
                s4t_cdmfaot = (s4)0;
            }
            if ( s4t_cdmfaotbnk[0] < (s4)0 )  /* �����K�[�h */
            {
                s4t_cdmfaotbnk[0] = (s4)0;
            }
            if ( s4t_cdmfaotbnk[1] < (s4)0 )  /* �����K�[�h */
            {
                s4t_cdmfaotbnk[1] = (s4)0;
            }
        }
        s2s_emfng_ecdmfaotb = (s2)s4t_cdmfaotb;  /* (u1 - u1 * KCDTMFAOTB)�̂��߃K�[�h�����s�v */

        glint_di(); /* ������ ���荞�݋֎~ ������ */
        s4t_emfrtotsum = s4s_emfng_emfrtotsum;
        u2t_ecmfotcnt  = u2s_emfng_ecmfotcnt;
        glint_ei(); /* ������ ���荞�݋��� ������ */

        s4t_mfrtot = s4g_gldiv_s4s4( s4t_emfrtotsum, (s4)u2t_ecmfotcnt );
                                                        /* lsb=(256/128/256)/1 -> 256/128/256,unit=% */
        ELIB_LOWGD2( s4t_mfrtot, (s4)s2g_emfng_MFOTL, s4t_mfrtot );
        s4t_ekldmfot = s4g_glmulst_s4s4u2( (s4)u2g_emfng_ekldmfoth_mcr, s4t_mfrtot, (u2)0U );
                                                        /* lsb=1*(256/128/256) -> 256/128/256,unit=% */
        s4t_ekldmfot = s4g_gldiv_s4s4( s4t_ekldmfot, (s4)(((100.)/(256./128./256.))+0.5) );
                                                        /* lsb=(256/128/256)/(256/128/256) -> 1,unit=�� */
        ELIB_HILOGD2( s4t_ekldmfot, (s4)u2g_U2MAX, (s4)u2g_U2MIN, s4t_ekldmfot );
        u2g_emfng_ekldmfot = (u2)s4t_ekldmfot;

        u1t_xcdmfaot = (u1)OFF;
        if ( u1g_emfng_CATN == (u1)1U )         /* �o���N��ʂȂ� */
        {
            if ( s4t_cdmfaot >= s4t_ekldmfot )
            {
                u1t_xcdmfaot = (u1)ON;
            }
        }
        else                                    /* �o���N��ʂ��� */
        {
            if ( ( s4t_cdmfaotbnk[0] >= s4t_ekldmfot )
              || ( s4t_cdmfaotbnk[1] >= s4t_ekldmfot ) )
            {
                u1t_xcdmfaot = (u1)ON;
            }
        }

        /* RAM�f�[�^�Ɋi�[ */
        glbitcp_bibi( u1t_xcdmfaot, bis_emfng_excdmfaot );

        /**********************************/
        /* �Ό��C�����Δ��萬���׸ނ̑��� */
        /**********************************/
        u1t_excdmfw = (u1)OFF;                  /*�y4�C���z��OFF�Œ�(�Ό��C�����Ό��o�Ȃ�) */
#if JENCYL == u1g_EJCC_6CYL    /*�y6�C���z*/
        u1t_excdmfwtmp = (u1)OFF;
        u1t_ncylw_c = u1s_EMFNG_NCYLW;
        for ( s4t_i = (s4)0; s4t_i < (s4)u1t_ncylw_c; s4t_i++ )
        {
            u1t_ecdmfw[s4t_i] = u1g_emfng_ecdmfw[s4t_i];
            if ( u1t_ecdmfw[s4t_i] > u1t_ekldmfw1_mcr )
            {
                u1t_excdmfwtmp = (u1)ON;
            }
        }
        s4t_cdmfw = (s4)u1t_ecdmfw[0];               /* [0]���� */
        for ( s4t_i = (s4)1; s4t_i < (s4)u1t_ncylw_c; s4t_i++ )
        {
            s4t_cdmfw += (s4)u1t_ecdmfw[s4t_i];      /* [1]�`���Z */
        }
        if ( ( ( s4t_cdmfw <= (s4)u1s_emfng_ekldmfw2_mcr )
            && ( s4t_cdmfw >  (s4)u1t_ekldmfw1_mcr ) )
          && ( u1t_excdmfwtmp == (u1)ON ) )
        {
            u1t_excdmfw = (u1)ON;                /* CXMF1�ݸ���ď��� */
        }
#endif
        /* RAM�f�[�^�Ɋi�[ */
        glbitcp_bibi( u1t_excdmfw, big_emfng_excdmfw );

        /**************************************/
        /* �G�}OT���وُ팟�o���L���׸ނ̑��� */
        /**************************************/
#if JENCYL == u1g_EJCC_6CYL    /*�y6�C���z*/
        s4t_cnt = (s4)0;
        for ( s4t_i = (s4)0; s4t_i < (s4)u1t_ncyl_c; s4t_i++ )
        {
            if ( u1g_emfng_ecdmfem[s4t_i] >= u1s_emfng_MFSTOT )
            {
                s4t_cnt++;                       /* ���΋C�����̃J�E���g */
            }
        }

        /* �Z�b�g�������� a */
        if ( ( u1t_xcdmfaot == (u1)ON )
          && ( s4t_cdmfaot <= (s4)204 )
          && ( s4t_cnt == (s4)2 )
          && ( bis_emfng_exmfkpl == (u1)ON ) )
        {
            u1t_exottd = (u1)ON;
        }
#endif

        /* �Z�b�g�������� b */
        if ( ( u1t_excdmfw == (u1)ON )           /*�y4�C���z��OFF�Œ� */
          && ( bis_emfng_exmfkpm == (u1)ON ) )
        {
            u1t_exottd = (u1)ON;
        }
    }   /* �G�}OT���وُ팟�o���ݸ� end */

    /* RAM�f�[�^�Ɋi�[ */
    glbitcp_bibi( u1t_exottd, bis_emfng_exottd );
}

/*********************************************************************/
/*  �֐���        | emfng_cdmfi_reset( )                             */
/*  �������e      | ���Ή񐔔��足��(����ٗp)�̸ر����               */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      | �����֐�                                         */
/*                | �����݊��̍l���K�v                             */
/*********************************************************************/
static void
emfng_cdmfi_reset( void )
{
    s4 s4t_i;
    u1 u1t_ncyl_c;                   /* lsb=1 :�C���� */

    /* ���[�N�f�[�^������ */
    u1t_ncyl_c = u1g_ejcc_NCYL;

    glint_di(); /* ������ ���荞�݋֎~ ������ */
    u2g_emfng_ecjmfoti  = (u2)0U;
    u2g_emfng_ecdmfaoti = (u2)0U;
    for ( s4t_i = (s4)0; s4t_i < (s4)u1t_ncyl_c; s4t_i++ )
    {
        u1g_emfng_ecdmfemi[s4t_i] = (u1)0U;
    }
    glint_ei(); /* ������ ���荞�݋��� ������ */
}

/*********************************************************************/
/*  �֐���        | emfng_ot_detect_ptptptpt( )                      */
/*  �������e      | �G�}OT���x���ُ픻��                             */
/*  ����^�C�~���O| 65ms��(emfng_65msl()���R�[��)                  */
/*  ����          | ptt_xumfot : �G�}OT���ق̐��픻��ۗ��׸ނ̊i�[�� */
/*                | ptt_xdmfot : �G�}OT���وُ픻���׸ނ̊i�[��      */
/*                | ptt_xhmfoton  : �G�}OT�ɂ��MIL�_�ŗv���׸ނ̊i�[�� */
/*                | ptt_xhmfotoff : �G�}OT�ɂ��MIL�_�ŷ�ݾٗv���׸ނ̊i�[�� */
/*  �߂�l        | �Ȃ�(�����Ŏ󂯓n��)                             */
/*  ���ӎ���      | �����֐�                                         */
/*********************************************************************/
static void
emfng_ot_detect_ptptptpt( u1 *ptt_xumfot, u1 *ptt_xdmfot, u1 *ptt_xhmfoton, u1 *ptt_xhmfotoff )
{
    s4 s4t_ecxmf1;      /* lsb=1,unit=��:�G�}OT���وُ팟�o�� */
    s4 s4t_exmfotfc1;   /* lsb=1:emfng_exmfotfc_u1()�R�[�������P���� */
#if JEMFFC == u1g_EJCC_USE  /*�y�G�}OT���Έُ펞FC�L�z*/
    s4 s4t_exmfotfc2;   /* lsb=1:emfng_exmfotfc_u1()�R�[�������Q���� */
#endif
    s4 s4t_xecxmf1inc;  /* lsb=1:ecxmfc1���ı��ߏ��������׸� */
    s4 s4t_xjdge;       /* lsb=1:�G�}OT���وُ�����Q�����׸� */
    u1 u1t_xdmfot;      /* lsb=1:�G�}OT���وُ퐬���׸� */
    u1 u1t_xumfot;      /* lsb=1:�G�}OT���ِ��픻��ۗ��׸� */
    u1 u1t_xhmfoton;    /* lsb=1:MIL�_�ŗv���׸� */
    u1 u1t_xhmfotoff;   /* lsb=1:MIL�_�ŷ�ݾ��׸� */
    u1 u1t_exottd;      /* lsb=1:�G�}OT���وُ팟�o���L���׸� */
    u1 u1t_CXMF1L_c;    /* lsb=1,unit=�� :�G�}OT���x���ُ팟�o�񐔔���l */
    u1 u1t_exinftp;     /* lsb=1:���[�h���s����t���O */
    u1 u1t_state;       /* lsb=1 :���o���x��� */
#if JETCORE_D == u1g_EJCC_USE  /*�yt-CORE�Ή��L�z*/
    u1 u1t_xoutftp;     /* lsb=1:OT���΃��[�h�̈�O�����׸� */
#endif
#if JEMFDTC_D == u1g_EJCC_USE  /*�y����OBD DTC�L�z*/
    u1 u1t_xem_lstpnd;  /* lsb=1 :�O��ײ��ݸ޻��ى��ُ���(EM)(���b�`�p) */
    u1 u1t_xot_lstpnd;  /* lsb=1 :�O��ײ��ݸ޻��ى��ُ���(OT)(���b�`�p) */
#endif

    /* ���[�N�f�[�^������ */
    s4t_ecxmf1     = (s4)u1s_emfng_ecxmf1;
    u1t_xdmfot     = (u1)OFF;
    s4t_xecxmf1inc = (s4)OFF;
    s4t_xjdge      = (s4)OFF;
    s4t_exmfotfc1  = (s4)OFF;
#if JEMFFC == u1g_EJCC_USE  /*�y�G�}OT���Έُ펞FC�L�z*/
    s4t_exmfotfc2  = (s4)OFF;
#endif
    u1t_xumfot     = (u1)OFF;
    u1t_xhmfoton   = (u1)OFF;
    u1t_xhmfotoff  = (u1)OFF;
    u1t_exottd     = (u1)bis_emfng_exottd;
    u1t_CXMF1L_c = u1s_emfng_CXMF1L;
    u1t_exinftp    = (u1)big_emfinftp_exinftp;
    u1t_state = u1s_emfng_state_Lch;
#if JETCORE_D == u1g_EJCC_USE  /*�yt-CORE�Ή��L�z*/
    u1t_xoutftp    = (u1)OFF;
#endif
#if JEMFDTC_D == u1g_EJCC_USE  /*�y����OBD DTC�L�z*/
    u1t_xem_lstpnd = u1s_emfng_xem_lstpnd_Lch;
    u1t_xot_lstpnd = u1s_emfng_xot_lstpnd_Lch;
#endif

    /********************************/
    /* �G�}OT���وُ팟�o�񐔂̎Z�o */
    /********************************/
    if ( ( bis_emfng_excdmfaot == (u1)ON )
#if JENCYL == u1g_EJCC_6CYL /*�y6�C���z*/
      || ( big_emfng_excdmfw    == (u1)ON )
#endif
       )
    {
        s4t_exmfotfc1 = (s4)ON;
    }

    if ( ( s4t_exmfotfc1 == (s4)ON )
      || ( u1t_exottd  == (u1)ON ) )
    {
        s4t_xecxmf1inc = (s4)ON;
        u1t_xumfot = (u1)ON;                    /* �G�}OT���ِ��픻��ۗ� */
        if ( s4t_ecxmf1 < (s4)u1g_U1MAX )
        {
            s4t_ecxmf1++;
        }
    }

    /************************/
    /* �G�}OT���وُ�̔��� */
    /************************/
    if ( ( s4t_ecxmf1   >= (s4)u1s_emfng_CXMF1H )
      || ( ( s4t_ecxmf1 >= (s4)u1t_CXMF1L_c )
        && ( ( u1t_exinftp == (u1)OFF )
          || ( u1t_state == u1g_WSENTIVCHG_LVL2 )
#if JEMFDTC_D == u1g_EJCC_USE  /*�y����OBD DTC�L�z*/
          || ( u1t_xem_lstpnd == (u1)ON )
          || ( u1t_xot_lstpnd == (u1)ON )
#endif
           ) ) )
    {
#if JEMFFC == u1g_EJCC_USE  /*�y�G�}OT���Έُ펞FC�L�z*/
        s4t_exmfotfc2 = (s4)ON;
#endif
        s4t_xjdge = (s4)ON;
    }

#if ( JENCYL == u1g_EJCC_4CYL ) && ( JEMFHOUKI == u1g_EJCC_NOT_USAMF )  /*�y4�C���zAND�y�ΕĖ@�K�ȊO�z */
    if ( ( s4t_ecxmf1 >= (s4)u1t_CXMF1L_c )
      && ( u1t_exottd  == (u1)ON ) )
    {
        s4t_xjdge = (s4)ON;
    }
#endif

    /* 2-1.(2)�@(c)�)�A)�����ύX���́A���L���������������� */
#if JETCORE_D == u1g_EJCC_USE      /*�yt-CORE�Ή��L�z*/
    if ( ( u1t_exinftp == (u1)OFF )
      || ( u1t_state == u1g_WSENTIVCHG_LVL2 )
 #if JEMFDTC_D == u1g_EJCC_USE     /*�y����OBD DTC�L�z*/
      || ( u1t_xem_lstpnd == (u1)ON )
      || ( u1t_xot_lstpnd == (u1)ON )
 #endif
 #if ( JENCYL == u1g_EJCC_4CYL ) && ( JEMFHOUKI == u1g_EJCC_NOT_USAMF ) /*�y4�C���zAND�y�ΕĖ@�K�ȊO�z*/
      || ( u1t_exottd  == (u1)ON )
 #endif
       )
    {
        u1t_xoutftp = (u1)ON;        /* OT���΃��[�h�̈�O�Ɣ��� */
    }
    /* RAM�f�[�^�Ɋi�[ */
    glbitcp_bibi( u1t_xoutftp, bis_emfng_exoutftp );         /* OT���΃��[�h�̈�O�����׸�(65msl) */
#endif

    if ( s4t_xecxmf1inc == (s4)ON )  /* ecxmf1���ı��ߏ������� */
    {
        if ( s4t_xjdge == (s4)ON )
        {
            u1t_xdmfot       = (u1)ON;                /* �G�}OT���ٌ��ُ݈� */
            bis_emfng_exdmf1 = (u1)ON;
        }
        if ( ( bis_emfng_exdmf1 == (u1)ON )
#if JEMFDTC_D == u1g_EJCC_USE /*�y����OBD DTC�L�z*/
          || ( ( u1s_emfng_xot_warning_Lch == (u1)ON )
            || ( u1s_emfng_xem_warning_Lch == (u1)ON ) )
#endif
#if JEMFFC == u1g_EJCC_USE  /*�y�G�}OT���Έُ펞FC�L�z*/
          || ( u1g_emffc_exfcbi != (u1)0x00U )  /* �G�}OT���Ζh�~FC�v���L�� */
#endif
           )
        {
            u1t_xhmfoton = (u1)ON;              /* MIL�_�� */
        }
        else
        {
            u1t_xhmfotoff = (u1)ON;             /* MIL�_�ŷ�ݾ� */
        }
    }
    else
    {
        if ( ( u1g_emfng_ecdtmf2 < u1s_emfng_CDTMF2 )
#if JEMFFC == u1g_EJCC_USE  /*�y�G�}OT���Έُ펞FC�L�z*/
          && ( u1g_emffc_exfcbi == (u1)0x00U )  /* �G�}OT���Ζh�~FC�v������ */
#endif
           )
        {
            u1t_xhmfotoff = (u1)ON;             /* MIL�_�ŷ�ݾ� */
        }
    }

    /* RAM�f�[�^�Ɋi�[ */
    u1s_emfng_ecxmf1 = (u1)s4t_ecxmf1;

#if JEMFFC == u1g_EJCC_USE          /*�y�G�}OT���Έُ펞FC�L�z*/
    /* emfng_exmfotfc()�̃R�[�� */
    if ( ( s4t_exmfotfc1 == (s4)ON )
      && ( s4t_exmfotfc2 == (s4)ON ) )
    {
        emfng_exmfotfc_u1( (u1)ON );
    }
#endif

    /* �߂�l�̐ݒ� */
    *ptt_xumfot    = u1t_xumfot;
    *ptt_xdmfot    = u1t_xdmfot;
    *ptt_xhmfoton  = u1t_xhmfoton;
    *ptt_xhmfotoff = u1t_xhmfotoff;
}

/***********************************************************************/
/*  �֐���        | emfng_em_detect_u2ptpt( )                          */
/*  �������e      | EM�������x���ُ픻��                               */
/*  ����^�C�~���O| 65ms��(emfng_65msl()���R�[��)                    */
/*  ����          | u2t_cdmfae2  : EM�������x���ُ픻��l              */
/*                | ptt_xdmfem   : EM�������وُ픻���׸ނ̊i�[��      */
/*                | ptt_xumfem   : EM�������ِ��픻��ۗ��׸ނ̊i�[��  */
/*  �߂�l        | �Ȃ�(�����Ŏ󂯓n��)                               */
/*  ���ӎ���      | �����֐�                                           */
/***********************************************************************/
static void
emfng_em_detect_u2ptpt( u2 u2t_cdmfae2, u1 *ptt_xdmfem, u1 *ptt_xumfem )
{
    s4 s4t_ecxmf;       /* lsb=1,unit=�� :EM�������وُ팟�o�� */
    u1 u1t_xdmfem;      /* lsb=1 :EM�������وُ픻���׸� */
    u2 u2t_kldmfae;     /* lsb=1,unit=�� :EM�������َ��Δ���l */
    u1 u1t_xumfem;      /* lsb=1 :EM�������ِ��픻��ۗ��׸� */
    u1 u1t_state;       /* lsb=1 :���o���x��� */
    u1 u1t_CXMFL_c;     /* lsb=1,unit=�� :EM�������x���ُ팟�o�񐔔���l */
#if JETCORE_D == u1g_EJCC_USE                      /*�yt-CORE�Ή��L�z*/
    u1 u1t_xemfst;      /* lsb=1 :EM�������x������1000rev�����׸� */
#endif
#if JEMFHOUKI == u1g_EJCC_USAMF                    /*�y�ΕĖ@�K�z*/
    u2 u2t_ecdmfae2;    /* lsb=1,unit=�� :EM�������ّS�C�����ζ��� */
    u1 u1t_exjokmf;     /* lsb=1 :�n����1000rev�����׸� */
#endif

    /* ���[�N�f�[�^������ */
    s4t_ecxmf   = (s4)u1s_emfng_ecxmf;
    u1t_xdmfem  = *ptt_xdmfem;
    u1t_xumfem  = *ptt_xumfem;
    u2t_kldmfae = u2g_emfng_ekldmfae;
    u1t_state   = u1s_emfng_state_Lch;
    u1t_CXMFL_c = u1s_emfng_CXMFL;
#if JETCORE_D == u1g_EJCC_USE                      /*�yt-CORE�Ή��L�z*/
    u1t_xemfst  = (u1)OFF;
#endif
#if JEMFHOUKI == u1g_EJCC_USAMF                    /*�y�ΕĖ@�K�z*/
    u2t_ecdmfae2 = u2g_emfng_ecdmfae2;
    u1t_exjokmf  = (u1)big_emfng_exjokmf;
#endif

    /********************************/
    /* EM�������وُ팟�o�񐔂̎Z�o */
    /********************************/
    if ( u2t_cdmfae2 >= u2t_kldmfae )                      /* lsb=1,unit=�� */
    {
        u1t_xumfem = (u1)ON;                       /* EM�������ِ��픻��ۗ� */
        if ( s4t_ecxmf < (s4)u1g_U1MAX )
        {
            s4t_ecxmf++;
        }

        /************************/
        /* EM�������وُ�̔��� */
        /************************/
        if ( ( s4t_ecxmf >= (s4)u1s_emfng_CXMFH )
          || ( ( s4t_ecxmf >= (s4)u1t_CXMFL_c )
            && ( ( u1t_state == u1g_WSENTIVCHG_LVL2 )
              || ( u1t_state == u1g_WSENTIVCHG_IUE ) ) )     /* ���x�A�b�v�i�]���p�j */
#if JEMFHOUKI == u1g_EJCC_USAMF                     /*�y�ΕĖ@�K�z*/
          || ( ( u2t_ecdmfae2 >= u2t_kldmfae )
            && ( u1t_exjokmf == (u1)OFF ) )
#endif
           )
        {
            u1t_xdmfem = (u1)ON;                   /* EM�������ٌ��ُ݈� */
        }
    }

    /* 2-2.(2)�@(c)�)�������ͳ)�����ύX���́A���L���������������� */
#if JETCORE_D == u1g_EJCC_USE                        /*�yt-CORE�Ή��L�z*/
    if ( ( ( s4t_ecxmf >= (s4)u1t_CXMFL_c )
      && ( ( u1t_state == u1g_WSENTIVCHG_LVL2 )
        || ( u1t_state == u1g_WSENTIVCHG_IUE ) ) )   /* ���x�A�b�v�i�]���p�j */
 #if JEMFHOUKI == u1g_EJCC_USAMF                     /*�y�ΕĖ@�K�z*/
      || ( ( u2t_ecdmfae2 >= u2t_kldmfae )
        && ( u1t_exjokmf == (u1)OFF ) )
 #endif
       )
    {
        u1t_xemfst = (u1)ON;                         /* EM�������x������1000rev�Ɣ��� */
    }
    /* RAM�f�[�^�Ɋi�[ */
    glbitcp_bibi( u1t_xemfst, bis_emfng_exemfst );   /* EM�������x������1000rev�����׸�(65msl) */
#endif

    /* RAM�f�[�^�Ɋi�[ */
    u1s_emfng_ecxmf = (u1)s4t_ecxmf;

    /* �߂�l�̐ݒ� */
    *ptt_xdmfem = u1t_xdmfem;
    *ptt_xumfem = u1t_xumfem;
}

#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
/***********************************************************************/
/*  �֐���        | emfng_di_detect_ptpt( )                            */
/*  �������e      | DI�ُ팟�o                                         */
/*  ����^�C�~���O| 65ms��(emfng_65msl()���R�[��)                    */
/*  ����          | ptt_xdmfdi   : DI�ُ��׸ނ̊i�[��                  */
/*                | ptt_xumfdi   : DI�ُ�ɂ�鐳�픻��ۗ��׸ނ̊i�[�� */
/*  �߂�l        | �Ȃ�(�����Ŏ󂯓n��)                               */
/*  ���ӎ���      | �����֐�                                           */
/*                |�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z                   */
/***********************************************************************/
static void
emfng_di_detect_ptpt( u1 *ptt_xdmfdi, u1 *ptt_xumfdi )
{
    u1 u1t_xddi;            /* lsb=1 : DI�ُ픻���׸� */
    s4 s4t_cyl;             /* lsb=1,unit=�C�� */
    u1 u1t_xdmfdi;          /* lsb=1 : DI�ُ��׸� */
    u1 u1t_xumfdi;          /* lsb=1 : DI�ُ�ɂ�鐳�픻��ۗ��׸� */
    u1 u1t_ncyl_c;          /* lsb=1 :�C���� */

    /* ���[�N�ϐ��̏����� */
    u1t_xdmfdi = (u1)OFF;
    u1t_xumfdi = (u1)OFF;
    u1t_ncyl_c = u1g_ejcc_NCYL;

    u1t_xddi = (u1)OFF;
    for ( s4t_cyl = (s4)0; s4t_cyl < (s4)u1t_ncyl_c ; s4t_cyl++ )
    {
        if ( u1s_emfng_ecdmfdi[s4t_cyl] >= u1s_emfng_MFDDI )
        {
            u1t_xddi = (u1)ON;
            u1s_emfng_exdmfdim[s4t_cyl] = (u1)ON;
        }
    }

    /********************/
    /* DI�ُ�̌��o���� */
    /********************/
    if ( u1t_xddi == (u1)ON )
    {
        u1t_xdmfdi = (u1)ON;     /* DI�ُ��׸޾�� */
        u1t_xumfdi = (u1)ON;     /* DI�ُ�ɂ�鐳�픻��ۗ��׸޾�� */
        big_emfng_exmfddi = (u1)ON;
    }
    bis_emfng_excdmfdiclr = (u1)ON;  /* exdmfdim�ر�p�׸� */
    /* ���o�����̸ر */
    glint_di(); /* ������ ���荞�݋֎~ ������ */
    u2s_emfng_ecjmfdi = (u2)0;       /* 0�������̂���LSB�ȗ� */
    /* DI���Ό��o�I���׸ނ̾�� */
    big_emfng_exmfdied = (u1)ON;
    for ( s4t_cyl = (s4)0; s4t_cyl < (s4)u1t_ncyl_c ; s4t_cyl++ )
    {
        u1s_emfng_ecdmfdi[s4t_cyl] = (u1)(((0.)/(1.))+0.5);   /* ecjmfdi�Ɠ����ɃN���A���� */
    }
    glint_ei(); /* ������ ���荞�݋��� ������ */
    *ptt_xdmfdi = u1t_xdmfdi;
    *ptt_xumfdi = u1t_xumfdi;
}

/***********************************************************************/
/*  �֐���        | emfng_pfi_detect_ptpt( )                           */
/*  �������e      | PFI�ُ팟�o                                        */
/*  ����^�C�~���O| 65ms��(emfng_65msl()���R�[��)                    */
/*  ����          | ptt_xdmfpfi :PFI�ُ��׸ނ̊i�[��                   */
/*                | ptt_xumfpfi :PFI�ُ�ɂ�鐳�픻��ۗ��׸ނ̊i�[�� */
/*  �߂�l        | �Ȃ�(�����Ŏ󂯓n��)                               */
/*  ���ӎ���      | �����֐�                                           */
/*                |�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z                   */
/***********************************************************************/
static void
emfng_pfi_detect_ptpt( u1 *ptt_xdmfpfi, u1 *ptt_xumfpfi )
{
    u1 u1t_xdpfi;           /* lsb=1 : PFI�ُ픻���׸� */
    s4 s4t_cyl;             /* lsb=1,unit=�C�� */
    u1 u1t_xdmfpfi;         /* lsb=1 : PFI�ُ��׸� */
    u1 u1t_xumfpfi;         /* lsb=1 : PFI�ُ�ɂ�鐳�픻��ۗ��׸� */
    u1 u1t_MFDPFI_c;        /* lsb=1,unit=�� :PFI�ُ팟�o���Ή� */
    u1 u1t_ncyl_c;          /* lsb=1 :�C���� */

    /* ���[�N�ϐ��̏����� */
    u1t_xdmfpfi = (u1)OFF;
    u1t_xumfpfi = (u1)OFF;
    u1t_MFDPFI_c = u1s_emfng_MFDPFI;
    u1t_ncyl_c = u1g_ejcc_NCYL;

    u1t_xdpfi = (u1)OFF;
    for ( s4t_cyl = (s4)0; s4t_cyl < (s4)u1t_ncyl_c; s4t_cyl++ )
    {
        if ( u1s_emfng_ecdmfpfi[s4t_cyl] >= u1t_MFDPFI_c )
        {
            u1t_xdpfi = (u1)ON;
            u1s_emfng_exdmfpfim[s4t_cyl] = (u1)ON;
        }
    }

    /*********************/
    /* PFI�ُ�̌��o���� */
    /*********************/
    if ( u1t_xdpfi == (u1)ON )
    {
        u1t_xdmfpfi = (u1)ON;     /* PFI�ُ��׸޾�� */
        u1t_xumfpfi = (u1)ON;     /* PFI�ُ�ɂ�鐳�픻��ۗ��׸޾�� */
        big_emfng_exmfdpfi = (u1)ON;
    }
    bis_emfng_excdmfpficlr = (u1)ON;  /* exdmfpfim�ر�p�׸� */
    /* ���o�����̸ر */
    glint_di(); /* ������ ���荞�݋֎~ ������ */
    u2s_emfng_ecjmfpfi = (u2)0;       /* 0�������̂���LSB�ȗ� */
    /* PFI���Ό��o�I���׸ނ̾�� */
    big_emfng_exmfpfied = (u1)ON;
    for ( s4t_cyl = (s4)0; s4t_cyl < (s4)u1t_ncyl_c; s4t_cyl++ )
    {
        u1s_emfng_ecdmfpfi[s4t_cyl] = (u1)(((0.)/(1.))+0.5);  /* ecjmfpfi�Ɠ����ɸر���� */
    }
    glint_ei(); /* ������ ���荞�݋��� ������ */
    *ptt_xdmfpfi = u1t_xdmfpfi;
    *ptt_xumfpfi = u1t_xumfpfi;
}
#endif /* JEEFI,JEHIPFI_E */

#if JEMFDTC_D == u1g_EJCC_USE /*�y����OBD DTC�L�z*/
/*********************************************************************/
/*  �֐���        | emfng_wxmf_out( )                                */
/*  �������e      | �d�Z�ւ̒ʒm����                                 */
/*  ����^�C�~���O| 65ms��(emfng_65msl()���R�[��)                  */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      | �����֐��y����OBD DTC�L�z                        */
/*                | �G�}OT����,EM��������,DI,PFI�ُ픻����call���� */
/*********************************************************************/
static void
emfng_wxmf_out( void )
{
    static volatile u1 u1s_emfng_emfk;       /* lsb=1 :DTC�o�͋C�� */
 #pragma ghs startdata
 #if ( JENCYL == u1g_EJCC_4CYL )      /*�y4�C���z*/
    static volatile const u1 u1s_emfng_cylwtocyl_tbl[2] = /* :cylw �� cylw�ɑΉ�������C���r�b�g�� �ϊ��e�[�u�� */
    { (u1)0x06U, (u1)0x09U };                             /* 0,1 �� #2#3,#1#4 */
 #endif
 #if ( JENCYL == u1g_EJCC_6CYL )      /*�y6�C���z*/
  #if JEEGTYPE == u1g_EJCC_V6CYL       /*�yV6�z*/
    static volatile const u1 u1s_emfng_cylwtocyl_tbl[3] = /* :cylw �� cylw�ɑΉ�������C���r�b�g�� �ϊ��e�[�u�� */
    { (u1)0x24U, (u1)0x09U, (u1)0x12U };                  /* 0,1,2 �� #3#6,#1#4,#2#5 */
  #elif JEEGTYPE == u1g_EJCC_L6CYL     /*�yL6�z*/
    static volatile const u1 u1s_emfng_cylwtocyl_tbl[3] = /* :cylw �� cylw�ɑΉ�������C���r�b�g�� �ϊ��e�[�u�� */
    { (u1)0x0cU, (u1)0x21U, (u1)0x12U };                  /* 0,1,2 �� #3#4,#1#6,#2#5 */
  #endif
 #endif
 #pragma ghs enddata

    u1 u1t_i;
    s4 s4t_cnt;
    u1 u1t_xemfk;                    /* lsb=1 : �C���ɑΉ�������C���r�b�g */
    u1 u1t_xemfkw;                   /* lsb=1 : �C���Q�ɑΉ�������C���r�b�g(�Ό��C���p) */
    u1 u1t_xemfk_opps;               /* lsb=1 : �C���Q�ɑΉ�������C���r�b�g(�Ό��C���p���[�N�ϐ�) */
    u4 u4t_ecdmfem2mx;               /* lsb=1,unit=�� : ecdmfem2[]�ő�l */
    u4 u4t_ecdmfem2[u1g_EJCC_NCYL];  /* lsb=1,unit=�� : EM�������ًC���ʎ��ζ��� */
    s4 s4t_ecdmfae2;                 /* lsb=1,unit=�� : �����Ή񐔁~0.9 */
    u1  u1t_xdmfot;                  /* lsb=1 :�G�}OT���وُ픻���׸� */
    u1  u1t_xumfot;                  /* lsb=1 :�G�}OT���ِ��픻��ۗ��׸� */
    u1  u1t_xhmfoton;                /* lsb=1 :�G�}OT�ɂ��MIL�_�ŗv���׸� */
    u1  u1t_xhmfotoff;               /* lsb=1 :�G�}OT�ɂ��MIL�_�ŷ�ݾٗv���׸� */
    u1  u1t_xdmfem;                  /* lsb=1 :EM�������وُ팟�o�׸� */
    u1  u1t_xumfem;                  /* lsb=1 :EM�������ِ��픻��ۗ��׸� */
 #if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
    u1  u1t_xdmfdi;                  /* lsb=1 :DI�ُ��׸� */
    u1  u1t_xumfdi;                  /* lsb=1 :DI�ُ�ɂ�鐳�픻��ۗ��׸� */
    u1  u1t_xdmfpfi;                 /* lsb=1 :PFI�ُ��׸� */
    u1  u1t_xumfpfi;                 /* lsb=1 :PFI�ُ�ɂ�鐳�픻��ۗ��׸� */
 #endif
    u1  u1t_excdmfw;                 /* lsb=1:�Ό��C�����Δ��萬���׸� */
 #if JETCORE_D == u1g_EJCC_USE       /*�yt-CORE�Ή��L�z*/
    u1  u1t_otcnd;                   /* lsb=1 :OT���Ώ������ʎq */
    u1  u1t_emcnd;                   /* lsb=1 :EM���Ώ������ʎq */
    u1  u1t_exdmf;                   /* lsb=1 :����OBD���ُ݈��׸� */
 #endif
    u1 u1t_ncyl_c;                   /* lsb=1 :�C���� */
    u1 u1t_ncylw_c;                  /* lsb=1 :�C���Q�� */

    /* ���[�N�f�[�^������ */
    u1t_ncyl_c = u1g_ejcc_NCYL;
    u1t_excdmfw = (u1)big_emfng_excdmfw;
    u4t_ecdmfem2[0] = (u4)u2g_emfng_ecdmfem2[0];    /* ������Q�Ƃ̂��߃��b�` */

    for ( u1t_i = (u1)1; u1t_i < u1t_ncyl_c; u1t_i++ )
    {
        u4t_ecdmfem2[u1t_i] = (u4)u2g_emfng_ecdmfem2[u1t_i];   /* ������Q�Ƃ̂��߃��b�` */
    }

    /* �f�[�^�l�擾 */
    u1t_xdmfot    = (u1)bis_emfng_exdmfot;         /* �G�}OT���وُ픻���׸� */
    u1t_xumfot    = (u1)bis_emfng_exumfot;         /* �G�}OT���ِ��픻��ۗ��׸� */
    u1t_xhmfoton  = (u1)bis_emfng_exhmfoton;       /* �G�}OT�ɂ��MIL�_�ŗv���׸� */
    u1t_xhmfotoff = (u1)bis_emfng_exhmfotoff;      /* �G�}OT�ɂ��MIL�_�ŷ�ݾٗv���׸� */
    u1t_xdmfem    = (u1)bis_emfng_exdmfem;         /* EM�������وُ팟�o�׸� */
    u1t_xumfem    = (u1)bis_emfng_exumfem;         /* EM�������ِ��픻��ۗ��׸� */
 #if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
    u1t_xdmfdi    = (u1)bis_emfng_exdmfdi;         /* DI�ُ��׸� */
    u1t_xumfdi    = (u1)bis_emfng_exumfdi;         /* DI�ُ�ɂ�鐳�픻��ۗ��׸� */
    u1t_xdmfpfi   = (u1)bis_emfng_exdmfpfi;        /* PFI�ُ��׸� */
    u1t_xumfpfi   = (u1)bis_emfng_exumfpfi;        /* PFI�ُ�ɂ�鐳�픻��ۗ��׸� */
 #endif
 #if JETCORE_D == u1g_EJCC_USE                                      /*�yt-CORE�Ή��L�z*/
    u1t_exdmf     = (u1)big_emfng_exdmf;           /* ����OBD���ُ݈��׸� */
 #endif

    /* ���[�N�f�[�^������ */
    u1t_xemfk = (u1)0x00U;

    /*************************/
    /* �d�Z�ւ�DTC�o�͂̒ʒm */
    /*************************/

 #if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
    /*******************/
    /* PFI�ُ펞�̏��� */
    /*******************/
    if ( u1t_xdmfpfi == (u1)ON )
    {
        /* PFI�ُ펞�̊e�C���̎��ΗL������ */
        for ( u1t_i = (u1)0; u1t_i < u1t_ncyl_c; u1t_i++ )
        {
            if ( u1s_emfng_exdmfpfim[u1t_i] == (u1)ON )
            {
                u1t_xemfk |= u1g_EMFCNT_CYL(u1t_i);
            }
        }
    }
    /******************/
    /* DI�ُ펞�̏��� */
    /******************/
    else if ( u1t_xdmfdi == (u1)ON )
    {
        /* DI�ُ펞�̊e�C���̎��ΗL������ */
        for ( u1t_i = (u1)0; u1t_i < u1t_ncyl_c; u1t_i++ )
        {
            if ( u1s_emfng_exdmfdim[u1t_i] == (u1)ON )
            {
                u1t_xemfk |= u1g_EMFCNT_CYL(u1t_i);
            }
        }
    }
    else
 #endif
    {
        /******************************/
        /* �G�}OT���وُ팟�o���A     */
        /* EM�������وُ팟�o���̏��� */
        /******************************/
        if ( ( u1t_xdmfem == (u1)ON )       /* EM�������وُ� */
          || ( u1t_xdmfot == (u1)ON ) )     /* �G�}OT���وُ� */
        {
            /***************************/
            /* �����Ή񐔂� 90% �̎Z�o */
            /***************************/
            s4t_ecdmfae2 = (s4)u2g_emfng_ecdmfae2;
            s4t_ecdmfae2 = s4g_glmulst_s4s4u2( s4t_ecdmfae2, (s4)(((0.9)/(1./128./256.))+0.5), (u2)15U );
                                                            /* lsb= 1 * 1/128/256 -> 1(��) */

            if ( u1t_excdmfw == (u1)OFF )             /* �Ό��C�����΂ł͂Ȃ� */
            {
                /* �Ό��C�����Ύ���ecdmfem2[],ecdmfae2���ɃJ�E���g�A�b�v���ꂸ            */
                /* 0(��)��0(��)*90%�ƂȂ�A�펞�������Ă��܂����ߑΌ��C�����͔�������Ȃ� */

                for ( u1t_i = (u1)0; u1t_i < u1t_ncyl_c; u1t_i++ )
                {
                    /****************************************************************/
                    /* �����Ή񐔂�90%�ȏオ1�̋C���ɏW�����Ă��� �� P0301�`P0308 */
                    /****************************************************************/
                    if ( (s4)u4t_ecdmfem2[u1t_i] >= s4t_ecdmfae2 )
                    {
                        u1t_xemfk |= u1g_EMFCNT_CYL(u1t_i);
                    }
                } /* ٰ��end */
            }

            /***********************************************/
            /* �P�̋C���Ɏ��ΏW�����Ă��Ȃ��ꍇ �� P0300 */
            /***********************************************/
            if ( u1t_xemfk == (u1)0x00U )
            {
                /***************************************/
                /* �C���ʎ��Ή񐔂̍ő�l * 0.1 �̎Z�o */
                /***************************************/
                u4t_ecdmfem2mx = u4t_ecdmfem2[0];
                for ( u1t_i = (u1)1; u1t_i < u1t_ncyl_c; u1t_i++ )
                {
                    if ( u4t_ecdmfem2mx < u4t_ecdmfem2[u1t_i] )  /* Max�l�I�� */
                    {
                        u4t_ecdmfem2mx = u4t_ecdmfem2[u1t_i];
                    }
                }
                u4t_ecdmfem2mx = (u4)u2g_glmulst_u2u2u2( (u2)u4t_ecdmfem2mx, (u2)(((0.1)/(1./128./256.))+0.5), (u2)15U );
                                                                     /* lsb= 1 * 1/128/256 -> 1(��) */

                /* �C���ʎ��Ή񐔂� ����l�ȏ� */
                /* ��Ԏ��Ή񐔂������C���̎��Ή񐔁~0.1 �� ���� */
                s4t_cnt   = (s4)0;
                for ( u1t_i = (u1)0; u1t_i < u1t_ncyl_c; u1t_i++ )
                {
                    if ( ( u4t_ecdmfem2[u1t_i] >= (u4)u2s_emfng_emfk_mcr )   /* ����(a) */
                      && ( u4t_ecdmfem2[u1t_i] >= u4t_ecdmfem2mx ) )
                    {
                        u1t_xemfk |= u1g_EMFCNT_CYL(u1t_i);
                        s4t_cnt++;
                    }
                } /* ٰ��end */

                if ( ( s4t_cnt == (s4)1 )              /* 1�C��������L�������������Ȃ������B                  */
                  && ( u1t_excdmfw == (u1)OFF ) )      /* ���A�Ό��C�����΂ł͂Ȃ�(4�C���͏펞OFF�̂��ߐ���) */
                {
                    u1t_xemfk = (u1)0x00U;      /* u1t_xemfk�ɒl���c���Ă����P0301�`P0308 ���Z�b�g�����̂ŃN���A */
                }
            }   /* �����Ή񐔂�90%�ȏオ1�̋C���ɏW�����Ă��Ȃ������P�[�X */

            u1t_xemfkw = (u1)0x00U;
            if ( u1t_excdmfw == (u1)ON )                          /* �Ό��C������ */
            {
                u1t_ncylw_c = u1s_EMFNG_NCYLW;
                for ( u1t_i = (u1)0; u1t_i < u1t_ncylw_c; u1t_i++ )
                {
                    if ( u1g_emfng_ecdmfw[u1t_i] > u1s_emfng_ekldmfw1_mcr )    /* ����(b) */
                    {
                        u1t_xemfk_opps = u1s_emfng_cylwtocyl_tbl[u1t_i];   /* �C���Q�ɑΉ�������C���r�b�g */
 #if JENCYL == u1g_EJCC_6CYL    /*�y6�C���z*/
                        if ( ( u1t_xemfk_opps & u1t_xemfk ) == (u1)0x00U )
                                                                /* ecdmfem[](ecdmfem2[])�ɂ�锻��Ŋ��Ƀr�b�g�Z�b�g */
 #endif
                        {                                           /* ����Ă���ꍇ�̓r�b�g�Z�b�g���Ȃ� */
                            u1t_xemfkw |= u1t_xemfk_opps;           /* �C���Q�ɑΉ�������C���r�b�g��1 */
                        }
                    }
                }
            }
            u1t_xemfk |= u1t_xemfkw;                                /* ����(a)��(b)��OR���Ƃ� */
        } /* EM�������وُ� or �G�}OT���وُ�̔���I�� */
    } /* DI,PFI�ُ팟�o�ȊO�̔���I�� */

    /* DTC�o�͋C���̎Z�o */
    u1s_emfng_emfk = u1t_xemfk;

    /***************************/
    /* �d�Z�ւ̎���OBD�ُ�ʒm */
    /***************************/
 #if JETCORE_D == u1g_EJCC_NOT_USE                 /*�yt-CORE�Ή����z*/
    /* �G�}OT���ٌ��ُ݈�ʒm */
    if ( u1t_xdmfot == (u1)ON )
    {
        vdg_wmf_fdi_ot_fald_u1( u1t_xemfk );     /* �G�}OT���ٌ��ُ݈�ʒm */
    }

    /* EM�������ٌ��ُ݈�ʒm */
    if ( ( u1t_xdmfem == (u1)ON )
  #if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
      || ( u1t_xdmfdi == (u1)ON )
      || ( u1t_xdmfpfi == (u1)ON )
  #endif
       )
    {
        vdg_wmf_fdi_em_fald_u1( u1t_xemfk );       /* EM�������ٌ��ُ݈�ʒm */
    }
 #endif

    /* �G�}OT���ٖ{�د�߈ُ�ʒm �yt-CORE�Ή����z*/
    /* �G�}OT���Η����ߒʒm �yt-CORE�Ή��L�z*/
    if ( u1t_xumfot == (u1)ON )
    {
 #if JETCORE_D == u1g_EJCC_NOT_USE    /*�yt-CORE�Ή����z*/
        vdg_wmf_fdi_ot_excmf();     /* �G�}OT���ِ��픻��ۗ��ʒm */
 #else                                /*�yt-CORE�Ή��L�z*/
        u1t_otcnd = u1g_WMF_FDI_DURING_FTPCYCLE;
        if ( bis_emfng_exoutftp == (u1)ON )
        {
            u1t_otcnd = u1g_WMF_FDI_OUTOF_FTPCYCLE;
        }
        vdg_wmf_fdi_ot_excmf_u2u1( (u2)u1t_xemfk, u1t_otcnd );    /* �G�}OT���Η����ߒʒm */
 #endif
    }

    /* EM�������ٖ{�د�߈ُ�ʒm �yt-CORE�Ή����z*/
    /* EM�������Η����ߒʒm �yt-CORE�Ή��L�z*/
    if ( ( u1t_xumfem == (u1)ON )
 #if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
      || ( u1t_xumfdi == (u1)ON )
      || ( u1t_xumfpfi == (u1)ON )
 #endif
       )
    {
 #if JETCORE_D == u1g_EJCC_NOT_USE      /*�yt-CORE�Ή����z*/
        vdg_wmf_fdi_em_excmf();       /* EM�������ِ��픻��ۗ� */
 #else                                  /*�yt-CORE�Ή��L�z*/
        u1t_emcnd = u1g_WMF_FDI_AFTER_FIRST1000RPM;
        if ( bis_emfng_exemfst == (u1)ON )
        {
            u1t_emcnd = u1g_WMF_FDI_WITHIN_FIRST1000RPM;
        }
        vdg_wmf_fdi_em_excmf_u2u1( (u2)u1t_xemfk, u1t_emcnd );    /* EM�������Η����ߒʒm */
 #endif
    }

    /* �G�}OT�ɂ��MIL�_�Œʒm */
    if ( u1t_xhmfoton == (u1)ON )
    {
 #if JETCORE_D == u1g_EJCC_NOT_USE               /*�yt-CORE�Ή����z*/
        vdg_wmf_fdi_mil_blink_u1( (u1)ON );    /* MIL�_�Œʒm */
 #endif
        vdg_wmf_fdi_ot_imdf();                 /* �G�}OT����̪�پ�̏�񌻍ُ݈�ʒm */
    }

    /* �G�}OT�ɂ��MIL�_�ŷ�ݾْʒm */
    if ( u1t_xhmfotoff == (u1)ON )
    {
 #if JETCORE_D == u1g_EJCC_NOT_USE               /*�yt-CORE�Ή����z*/
        vdg_wmf_fdi_mil_blink_u1( (u1)OFF );   /* MIL�_�ŷ�ݾْʒm */
 #else                                           /*�yt-CORE�Ή��L�z*/
        vdg_wmf_fdi_pas_u2u1( u2g_WMF_FDI_ID_OT,(u1)ON );   /* OT���ΐ��픻�� */
 #endif
        vdg_wmf_fdi_ot_imdnf();                /* �G�}OT����̪�پ�̏�񌻍ُ݈�O�ʒm */
    }

 #if JETCORE_D == u1g_EJCC_USE                  /*�yt-CORE�Ή��L�z*/
    /* ����OBD���ُ݈�t���O�̎Z�o */
    if ( ( u1t_xdmfot == (u1)ON )
      || ( u1t_xdmfem == (u1)ON )
  #if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )   /*�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
      || ( u1t_xdmfdi == (u1)ON )
      || ( u1t_xdmfpfi == (u1)ON )
  #endif
       )
    {
        u1t_exdmf = (u1)ON;
    }

    if ( u1s_emfng_xreqclr_Lch == (u1)ON )
    {
        u1t_exdmf = (u1)OFF;
    }
    /* RAM�f�[�^�Ɋi�[ */
    glbitcp_bibi( u1t_exdmf, big_emfng_exdmf );               /* ����OBD���ُ݈��׸� */

  #if JEOBDUDS_D == u1g_EJCC_USE                /*�yOBDonUDS�Ή��L�z*/
    /* ��ިȽ��Ă̂��߂�1000rev������ʒm */
    if ( ( u1s_emfng_pas == (u1)ON )
      && ( ( u1t_exdmf == (u1)OFF )
        && ( ( big_wmf_fdi_xot_pnd == (u1)OFF )
          && ( big_wmf_fdi_xem_pnd == (u1)OFF ) )
        && ( ( u1s_emfng_xot_lstpnd_Lch == (u1)OFF )
          && ( u1s_emfng_xem_lstpnd_Lch == (u1)OFF ) )
        && ( ( u1s_emfng_xot_warning_Lch == (u1)OFF )
          && ( u1s_emfng_xem_warning_Lch == (u1)OFF ) )
        && ( ( u1s_emfng_ecxmf1 == u1s_EMFNG_CXMF1PAS )
          && ( u1s_emfng_ecxmf == u1s_EMFNG_CXMFPAS ) ) ) )
    {
        vdg_wmf_fdi_pas_u2u1( u2g_WMF_FDI_ID_EM,(u1)ON );    /* EM���ΐ��픻�� */
    }
  #endif
 #endif

}
#endif /* JEMFDTC_D */

#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
/*********************************************************************/
/*  �֐���        | emfng_eocmfmlt_pt()                              */
/*  �������e      | �s�꒲��RAM�X�V����                              */
/*  ����^�C�~���O| 65ms��(emfng_65msl()���R�[��)                  */
/*  ����          | ptt_ecdmfw[](�擪�A�h���X)                       */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      | �����֐��y�s�꒲���L�z                           */
/*********************************************************************/
static void
emfng_eocmfmlt_pt( const u1 ptt_ecdmfw[] )
{
 #if JENCYL == u1g_EJCC_6CYL    /*�y6�C���z*/
    s4 s4t_i;               /* lsb=1 :for���[�v�p�ϐ� */
    u2 u2t_ocmfmlth;        /* lsb=1,unit=�� :�Ό��C�����Ή�(��)�̕p�x */
    u2 u2t_ocmfmltl;        /* lsb=1,unit=�� :�Ό��C�����Ή�(��)�̕p�x */
    s4 s4t_ecdmfw[3];       /* lsb=1,unit=�� :�C���Q�ő吔�� */
    s4 s4t_enejsm;          /* lsb=200/8,unit=rpm :NE�Ȃ܂��l */
    u1 u1t_onemfmlt;        /* lsb=200/8,unit=rpm :�Ό��C�����Ύ��̴ݼ�݉�]�Ȃ܂��l */
    u1 u1t_jdg;
    u1 u1t_ncylw_c;         /* lsb=1 :�C���Q�� */
 #endif
    u1 u1t_cdmfaot;         /* lsb=1,unit=�� :�G�}OT���ّS�C�����ζ��� */
    u1 u1t_ocdmfaotmx;      /* lsb=1,unit=�� :200rev���̍ő呍���Ή� */
    s2 s2t_thw;             /* lsb=160/128,unit=�� :�ݼ�ݐ���p���� */
    s1 s1t_othwot;          /* lsb=160/128,unit=�� :�ő厸�ζ����X�V���̐��� */
    s2 s2t_tha;             /* lsb=160/128,unit=�� :�ݼ�ݐ���p�z�C�� */
    s1 s1t_othaot;          /* lsb=160/128,unit=�� :�ő厸�ζ����X�V���̋z�C�� */
    u1 u1t_ecjemrev;        /* lsb=1,unit=�� :�n����EM�������x�������(�c�[���x������̈�) */

    /* ���[�N�f�[�^������ */
 #if JENCYL == u1g_EJCC_6CYL    /*�y6�C���z*/
    u1t_jdg = (u1)OFF;
    u1t_ncylw_c = u1s_EMFNG_NCYLW;
    for ( s4t_i = (s4)0; s4t_i < (s4)u1t_ncylw_c; s4t_i++ )
    {
        s4t_ecdmfw[s4t_i] = (s4)ptt_ecdmfw[s4t_i];
    }
    if ( ( s4t_ecdmfw[0] >= (s4)50 )
      || ( s4t_ecdmfw[1] >= (s4)50 )
      || ( s4t_ecdmfw[2] >= (s4)50 ) )
    {
        u2t_ocmfmlth = u2g_emfng_eocmfmlth();         /* eocmfmlth�擾 */
        if ( u2t_ocmfmlth < u2g_U2MAX )
        {
            u2t_ocmfmlth++;                               /* lsb=1,unit=�� :�Ό��C�����Ή񐔑�̕p�x */
        }
        (void)s4g_ememctr_write( u2g_EMFNG_EOCMFMLTH_U2_ID, (void *)&u2t_ocmfmlth );   /* �߂�l�͎g�p���Ȃ� */
        u1t_jdg = (u1)ON;
    }
    else if ( ( s4t_ecdmfw[0] >= (s4)20 )
           || ( s4t_ecdmfw[1] >= (s4)20 )
           || ( s4t_ecdmfw[2] >= (s4)20 ) )
    {
        u2t_ocmfmltl = u2g_emfng_eocmfmltl();         /* eocmfmltl�擾 */
        if ( u2t_ocmfmltl < u2g_U2MAX )
        {
            u2t_ocmfmltl++;                               /* lsb=1,unit=�� :�Ό��C�����Ή񐔏��̕p�x */
        }
        (void)s4g_ememctr_write( u2g_EMFNG_EOCMFMLTL_U2_ID, (void *)&u2t_ocmfmltl );   /* �߂�l�͎g�p���Ȃ� */
        u1t_jdg = (u1)ON;
    }
    else
    {
        /* �����Ȃ� */
    }

    if ( u1t_jdg == (u1)ON )
    {
        s4t_enejsm = s4g_glbitcal_s4sftr_s4u1( (s4)s2g_eobdsm_enejsm, (u1)5U );
        ELIB_HILOGD2( s4t_enejsm, (s4)u1g_U1MAX, (s4)u1g_U1MIN, s4t_enejsm );
        u1t_onemfmlt = (u1)s4t_enejsm;
        (void)s4g_ememctr_write( u2g_EMFNG_EONEMFMLT_U1_ID, (void *)&u1t_onemfmlt );   /* �߂�l�͎g�p���Ȃ� */
                                                 /* lsb=200/256��200/8,unit=rpm :�s�꒲��RAM�X�V����enejsm */
    }
 #endif

    /**********************/
    /*     ����������     */
    /**********************/
    u1t_cdmfaot = u1g_emfng_ecdmfaot;

    /* �o�b�N�A�b�vRAM�擾 */
    u1t_ocdmfaotmx = u1g_emfng_eocdmfaotmx();        /* lsb=1, unit=�� */

    if ( u1t_ocdmfaotmx < u1t_cdmfaot )
    {
        s2t_thw = s2g_glbitcal_s2sftr_s2u1( s2g_ethw_ethw, (u1)1U );
        ELIB_HILOGD2( s2t_thw, (s2)s1g_S1MAX, (s2)s1g_S1MIN, s2t_thw );
        s1t_othwot = (s1)s2t_thw;
        s2t_tha = s2g_glbitcal_s2sftr_s2u1( s2g_etha_etha, (u1)1U );
        ELIB_HILOGD2( s2t_tha, (s2)s1g_S1MAX, (s2)s1g_S1MIN, s2t_tha );
        s1t_othaot = (s1)s2t_tha;

        /****************************************************/
        /* 200rev���̎��Ή񐔂��ő厞�A�o�b�N�A�b�vRAM�X�V  */
        /****************************************************/
        (void)s4g_ememctr_write( u2g_EMFNG_EOCDMFAOTMX_U1_ID, (void *)&u1t_cdmfaot );  /* �߂�l�͎g�p���Ȃ� */
        u1t_ecjemrev = u1s_emfng_ecjemrev;
        (void)s4g_ememctr_write( u2g_EMFNG_EOCJREVOT_U1_ID, (void *)&u1t_ecjemrev );   /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOTHWOT_S1_ID, (void *)&s1t_othwot );       /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOTHAOT_S1_ID, (void *)&s1t_othaot );       /* �߂�l�͎g�p���Ȃ� */
    }
}

/*********************************************************************/
/*  �֐���        | emfng_eocmfn_u2()                                */
/*  �������e      | �s�꒲��RAM�X�V����                              */
/*  ����^�C�~���O| 65ms��(emfng_65msl()���R�[��)                  */
/*  ����          | u2t_cdmfae lsb=1 :EM�������َ��Ή�             */
/*                |                   (�S�C����)����(CDMFAE2)        */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      | �����֐��y�s�꒲���L�z                           */
/*********************************************************************/
static void
emfng_eocmfn_u2( u2 u2t_cdmfae )
{
    u2  u2t_ocmfnh;         /* lsb=1,unit=�� :���Ή�(��)�̕p�x */
    u2  u2t_ocmfnm;         /* lsb=1,unit=�� :���Ή�(��)�̕p�x */
    u2  u2t_ocmfnl;         /* lsb=1,unit=�� :���Ή�(��)�̕p�x */
    s4  s4t_i;              /* lsb=1 :for���[�v�p�ϐ� */
    u2  u2t_cdmfae2;        /* lsb=1,unit=�� :EM�������ّS�C�����ζ��� */
    u2  u2t_cdmfae2gd;      /* lsb=1,unit=�� :EM�������ّS�C�����ζ����ް�ޒl */
    u1  u1t_cdmfae2gd;      /* lsb=1,unit=�� :EM�������ّS�C�����ζ����ް�ޒl(�������ݗp) */
    u1  u1t_ocdmfae2mx;     /* lsb=1,unit=�� :1000rev���̍ő呍���Ή� */
    s2  s2t_thw;            /* lsb=160/128,unit=�� :�ݼ�ݐ���p���� */
    s1  s1t_othwem;         /* lsb=160/128,unit=�� :�ő厸�ζ����X�V���̐��� */
    s2  s2t_tha;            /* lsb=160/128,unit=�� :�ݼ�ݐ���p�z�C�� */
    s1  s1t_othaem;         /* lsb=160/128,unit=�� :�ő厸�ζ����X�V���̋z�C�� */
    u2  u2t_ecdmfem2;       /* lsb=1,unit=�� :EM�������ًC���ʎ��ζ��� */
    u1  u1t_ocdmfem2mx;     /* lsb=1,unit=�� :�ő厸�ζ����X�V���̋C���ʎ��ζ��� */
    s4  s4t_spdav;          /* lsb=256/256,unit=km/h :1000rev���̎��Ή񐔍ő厞�̎��Ή񐔱��ߎ����ώԑ� */
    u1  u1t_ospdemav;       /* lsb=256/256,unit=km/h :1000rev���̎��Ή񐔍ő厞�̎��Ή񐔱��ߎ����ώԑ�(�������ݗp) */
    s4  s4t_neemav;         /* lsb=12800/256,unit=rpm :���Ή�UP���̕��ϴݼ�݉�]�� */
    u1  u1t_oneemav;        /* lsb=12800/256,unit=rpm :���Ή�UP���̕��ϴݼ�݉�]��(�������ݗp) */
    s4  s4t_klsmemav;       /* lsb=320/256,unit=% :���Ή�UP���̕��ϕ��� */
    u1  u1t_oklsmemav;      /* lsb=320/256,unit=% :���Ή�UP���̕��ϕ���(�������ݗp) */
    u1  u1t_ecjmfneemi;     /* lsb=1,unit=�� :1000rev�Ԃ̱����Ӱ�މ�(�c�[���x������̈�) */
    u1  u1t_ecjmfneeml;     /* lsb=1,unit=�� :1000rev�Ԃ�۰Ӱ�މ�(�c�[���x������̈�) */
    u1  u1t_ecjmfneemh;     /* lsb=1,unit=�� :1000rev�Ԃ�ʲӰ�މ�(�c�[���x������̈�) */
    u1  u1t_ecjemrev;       /* lsb=1,unit=�� :�n����EM�������x�������(�c�[���x������̈�) */
    u1  u1t_ncyl_c;         /* lsb=1 :�C���� */

    if ( u2t_cdmfae >= u2s_emfng_ecmfnh_mcr )
    {
        u2t_ocmfnh = u2g_emfng_eocmfnh();         /* eocmfnh�擾 */
        if ( u2t_ocmfnh < u2g_U2MAX )
        {
            u2t_ocmfnh++;                             /* lsb=1,unit=�� :���Ή�(��)�̕p�x */
        }
        (void)s4g_ememctr_write( u2g_EMFNG_EOCMFNH_U2_ID, (void *)&u2t_ocmfnh );               /* �߂�l�͎g�p���Ȃ� */
    }
    else if ( u2t_cdmfae >= u2s_emfng_ecmfnm_mcr )
    {
        u2t_ocmfnm = u2g_emfng_eocmfnm();         /* eocmfnm�擾 */
        if ( u2t_ocmfnm < u2g_U2MAX )
        {
            u2t_ocmfnm++;                             /* lsb=1,unit=�� :���Ή�(��)�̕p�x */
        }
        (void)s4g_ememctr_write( u2g_EMFNG_EOCMFNM_U2_ID, (void *)&u2t_ocmfnm );               /* �߂�l�͎g�p���Ȃ� */
    }
    else if ( u2t_cdmfae >= u2s_emfng_ecmfnl_mcr )
    {
        u2t_ocmfnl = u2g_emfng_eocmfnl();         /* eocmfnl�擾 */
        if ( u2t_ocmfnl < u2g_U2MAX )
        {
            u2t_ocmfnl++;                             /* lsb=1,unit=�� :���Ή�(��)�̕p�x */
        }
        (void)s4g_ememctr_write( u2g_EMFNG_EOCMFNL_U2_ID, (void *)&u2t_ocmfnl );               /* �߂�l�͎g�p���Ȃ� */
    }
    else
    {
        /* �����Ȃ� */
    }

    /**********************/
    /*     ����������     */
    /**********************/
    u2t_cdmfae2 = u2g_emfng_ecdmfae2;
    ELIB_HIGHGD2( u2t_cdmfae2, (u2)u1g_U1MAX, u2t_cdmfae2gd );
    /* �o�b�N�A�b�vRAM�擾 */
    u1t_ocdmfae2mx = u1g_emfng_eocdmfae2mx();        /* lsb=1, unit=�� */

    if ( u1t_ocdmfae2mx < (u1)u2t_cdmfae2gd )
    {
        s2t_thw = s2g_glbitcal_s2sftr_s2u1( s2g_ethw_ethw, (u1)1U );
        ELIB_HILOGD2( s2t_thw, (s2)s1g_S1MAX, (s2)s1g_S1MIN, s2t_thw );
        s1t_othwem = (s1)s2t_thw;
        s2t_tha = s2g_glbitcal_s2sftr_s2u1( s2g_etha_etha, (u1)1U );
        ELIB_HILOGD2( s2t_tha, (s2)s1g_S1MAX, (s2)s1g_S1MIN, s2t_tha );
        s1t_othaem = (s1)s2t_tha;

        s4t_spdav = s4g_gldiv_s4s4( s4s_emfng_espdaem, (s4)u2t_cdmfae2 );
        ELIB_HILOGD2( s4t_spdav, (s4)u1g_U1MAX, (s4)u1g_U1MIN, s4t_spdav );
        u1t_ospdemav = (u1)s4t_spdav;
        s4t_neemav = s4g_glbitcal_s4sftr_s4u1( s4s_emfng_eneaem, (u1)6U );  /* lsb=12800/64/256 -> 12800/256 */
        s4t_neemav = s4g_gldiv_s4s4( s4t_neemav, (s4)u2t_cdmfae2 );
        ELIB_HILOGD2( s4t_neemav, (s4)u1g_U1MAX, (s4)u1g_U1MIN, s4t_neemav );
        u1t_oneemav = (u1)s4t_neemav;
        s4t_klsmemav = s4g_glbitcal_s4sftr_s4u1( s4s_emfng_eklsmaem, (u1)6U );  /* lsb=320/64/256 -> 320/256 */
        s4t_klsmemav = s4g_gldiv_s4s4( s4t_klsmemav, (s4)u2t_cdmfae2 );
        ELIB_HILOGD2( s4t_klsmemav, (s4)u1g_U1MAX, (s4)u1g_U1MIN, s4t_klsmemav );
        u1t_oklsmemav = (u1)s4t_klsmemav;

        /****************************************************/
        /* 1000rev���̎��Ή񐔂��ő厞�A�o�b�N�A�b�vRAM�X�V */
        /****************************************************/
        u1t_cdmfae2gd = (u1)u2t_cdmfae2gd;
        (void)s4g_ememctr_write( u2g_EMFNG_EOCDMFAE2MX_U1_ID, (void *)&u1t_cdmfae2gd );        /* �߂�l�͎g�p���Ȃ� */
        u1t_ecjemrev = u1s_emfng_ecjemrev;
        (void)s4g_ememctr_write( u2g_EMFNG_EOCJREVEM_U1_ID, (void *)&u1t_ecjemrev );           /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOTHWEM_S1_ID, (void *)&s1t_othwem );               /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOTHAEM_S1_ID, (void *)&s1t_othaem );               /* �߂�l�͎g�p���Ȃ� */

        u1t_ncyl_c = u1g_ejcc_NCYL;
        for ( s4t_i = (s4)0; s4t_i < (s4)u1t_ncyl_c; s4t_i++ )
        {
            u2t_ecdmfem2 = u2g_emfng_ecdmfem2[s4t_i];
            ELIB_HIGHGD2( u2t_ecdmfem2, (u2)u1g_U1MAX, u2t_ecdmfem2 );
            u1t_ocdmfem2mx = (u1)u2t_ecdmfem2;
            (void)s4g_ememctr_write( u2s_EOCDMFEM2MX_U1_ID[s4t_i], (void *)&u1t_ocdmfem2mx );  /* �߂�l�͎g�p���Ȃ� */
        }

        (void)s4g_ememctr_write( u2g_EMFNG_EOSPDEMAV_U1_ID, (void *)&u1t_ospdemav );           /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EONEEMAV_U1_ID, (void *)&u1t_oneemav );             /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOKLSMEMAV_U1_ID, (void *)&u1t_oklsmemav );         /* �߂�l�͎g�p���Ȃ� */

        u1t_ecjmfneemi = u1s_emfng_ecjmfneemi;
        (void)s4g_ememctr_write( u2g_EMFNG_EOCJMFNEEMI_U1_ID, (void *)&u1t_ecjmfneemi );       /* �߂�l�͎g�p���Ȃ� */
        u1t_ecjmfneeml = u1s_emfng_ecjmfneeml;
        (void)s4g_ememctr_write( u2g_EMFNG_EOCJMFNEEML_U1_ID, (void *)&u1t_ecjmfneeml );       /* �߂�l�͎g�p���Ȃ� */
        u1t_ecjmfneemh = u1s_emfng_ecjmfneemh;
        (void)s4g_ememctr_write( u2g_EMFNG_EOCJMFNEEMH_U1_ID, (void *)&u1t_ecjmfneemh );       /* �߂�l�͎g�p���Ȃ� */
    }
}
#endif /* JEOOBD */

/*********************************************************************/
/*  �֐���        | emfng_cntclr_65msl( )                            */
/*  �������e      | �O���Q�Ǝ��ζ����̸ر����                        */
/*  ����^�C�~���O| 65ms��(emfcnt_65msl���R�[��)                   */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      |                                                  */
/*********************************************************************/
void
emfng_cntclr_65msl( void )
{
    s4 s4t_i;           /* lsb=1 :for���[�v�p�ϐ� */
    u1 u1t_ncyl_c;      /* lsb=1 :�C���� */
    u1 u1t_ncylw_c;     /* lsb=1 :�C���Q�� */

    /* ���[�N�f�[�^������ */
    u1t_ncyl_c = u1g_ejcc_NCYL;
    /***************/
    /* �����ر���� */
    /***************/
    glint_di(); /* ������ ���荞�݋֎~ ������ */
    if ( big_emfng_excdmfemclr == (u1)ON )      /* ecdmfem[]�ر�v���L�� */
    {
        for ( s4t_i = (s4)0; s4t_i < (s4)u1t_ncyl_c; s4t_i++ )
        {
            u1g_emfng_ecdmfem[s4t_i] = (u1)0U;
        }
    }
    if ( bis_emfng_excdmfem2clr == (u1)ON )     /* ecdmfem2[]�ر�v���L�� */
    {
        for ( s4t_i = (s4)0; s4t_i < (s4)u1t_ncyl_c; s4t_i++ )
        {
            u2g_emfng_ecdmfem2[s4t_i] = (u2)0U;
        }
    }
    if ( bis_emfng_excdmfwclr == (u1)ON )       /* ecdmfw[]�ر�v���L�� */
    {
        u1t_ncylw_c = u1s_EMFNG_NCYLW;
        for ( s4t_i = (s4)0; s4t_i < (s4)u1t_ncylw_c; s4t_i++ )
        {
            u1g_emfng_ecdmfw[s4t_i] = (u1)0U;
        }
    }

    if ( bis_emfng_excdmfae2clr == (u1)ON )     /* ecdmfae2�ر�v���L�� */
    {
        u2g_emfng_ecdmfae2 = (u2)0U;
    }

    glint_ei(); /* ������ ���荞�݋��� ������ */
}

/*********************************************************************/
/*  �֐���        | u2g_emfng_eocmfnl( )                             */
/*  �������e      | �s�꒲��RAM ���Ή�(��)�̕p�x �擾�֐�          */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | ���Ή�(��)�̕p�x lsb=1,unit=��                 */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
u2
u2g_emfng_eocmfnl( void )
{
    u2 u2t_eocmfnl;     /* lsb=1,unit=�� :���Ή�(��)�̕p�x */

    u2t_eocmfnl = (u2)0U;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EOCMFNL_U2_ID, (void *)&u2t_eocmfnl );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( u2t_eocmfnl );
}

/*********************************************************************/
/*  �֐���        | u2g_emfng_eocmfnm( )                             */
/*  �������e      | �s�꒲��RAM ���Ή�(��)�̕p�x �擾�֐�          */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | ���Ή�(��)�̕p�x lsb=1,unit=��                 */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
u2
u2g_emfng_eocmfnm( void )
{
    u2 u2t_eocmfnm;     /* lsb=1,unit=�� :���Ή�(��)�̕p�x */

    u2t_eocmfnm = (u2)0U;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EOCMFNM_U2_ID, (void *)&u2t_eocmfnm );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( u2t_eocmfnm );
}

/*********************************************************************/
/*  �֐���        | u2g_emfng_eocmfnh( )                             */
/*  �������e      | �s�꒲��RAM ���Ή�(��)�̕p�x �擾�֐�          */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | ���Ή�(��)�̕p�x lsb=1,unit=��                 */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
u2
u2g_emfng_eocmfnh( void )
{
    u2 u2t_eocmfnh;     /* lsb=1,unit=�� :���Ή�(��)�̕p�x */

    u2t_eocmfnh = (u2)0U;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EOCMFNH_U2_ID, (void *)&u2t_eocmfnh );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( u2t_eocmfnh );
}

/*********************************************************************/
/*  �֐���        | u2g_emfng_eocmfmltl( )                           */
/*  �������e      | �s�꒲��RAM �Ό��C�����Ή�(��)�̕p�x �擾�֐�  */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �Ό��C�����Ή�(��)�̕p�x lsb=1,unit=��         */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
u2
u2g_emfng_eocmfmltl( void )
{
    u2 u2t_eocmfmltl;   /* lsb=1,unit=�� :�Ό��C�����Ή�(��)�̕p�x */

    u2t_eocmfmltl = (u2)0U;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EOCMFMLTL_U2_ID, (void *)&u2t_eocmfmltl );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( u2t_eocmfmltl );
}

/*********************************************************************/
/*  �֐���        | u2g_emfng_eocmfmlth( )                           */
/*  �������e      | �s�꒲��RAM �Ό��C�����Ή�(��)�̕p�x �擾�֐�  */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �Ό��C�����Ή�(��)�̕p�x lsb=1,unit=��         */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
u2
u2g_emfng_eocmfmlth( void )
{
    u2 u2t_eocmfmlth;   /* lsb=1,unit=�� :�Ό��C�����Ή�(��)�̕p�x */

    u2t_eocmfmlth = (u2)0U;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EOCMFMLTH_U2_ID, (void *)&u2t_eocmfmlth );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( u2t_eocmfmlth );
}

/*********************************************************************/
/*  �֐���        | u1g_emfng_eonemfmlt( )                           */
/*  �������e      | �s�꒲��RAM �Ό��C�����Ύ��̴ݼ�݉�]�Ȃ܂��l �擾�֐� */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �Ό��C�����Ύ��̴ݼ�݉�]�Ȃ܂��l                */
/*                | lsb=200/8, unit=rpm                              */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
u1
u1g_emfng_eonemfmlt( void )
{
    u1 u1t_eonemfmlt;   /* lsb=200/8,unit=rpm :�Ό��C�����Ύ��̴ݼ�݉�]�Ȃ܂��l */

    u1t_eonemfmlt = (u1)0U;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EONEMFMLT_U1_ID, (void *)&u1t_eonemfmlt );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( u1t_eonemfmlt );        /* lsb=200/8,unit=rpm */
}

/*********************************************************************/
/*  �֐���        | u2g_emfng_ecdmfaemTv( )                          */
/*  �������e      | ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�S�C��)�擾�֐� */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�S�C��)         */
/*                |                        lsb=1,unit=��             */
/*  ���ӎ���      |  �X�P�[�����OID =24(ISO 15031-5)                 */
/*********************************************************************/
u2
u2g_emfng_ecdmfaemTv( void )
{
    u2 u2t_ecdmfaemTv;   /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�S�C��) */

    u2t_ecdmfaemTv = (u2)0U;  /* �_�~�[�ݒ� */
    (void)s4g_ememctr_read( u2g_EMFNG_ECDMFAEMTV_U2_ID, (void *)&u2t_ecdmfaemTv );  /* �߂�l�͎g�p���Ȃ� */

    return( u2t_ecdmfaemTv );
}

/*********************************************************************/
/*  �֐���        | u2g_emfng_ecdmfaemMntl( )                        */
/*  �������e      | ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�S�C��)�擾�֐� */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�S�C��)   */
/*                |                        lsb=1,unit=��             */
/*  ���ӎ���      |  �X�P�[�����OID =24(ISO 15031-5)                 */
/*********************************************************************/
u2
u2g_emfng_ecdmfaemMntl( void )
{
    u2 u2t_ecdmfaemMntl;   /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�S�C��) */

    u2t_ecdmfaemMntl = (u2)0U;  /* �_�~�[�ݒ� */
    (void)s4g_ememctr_read( u2g_EMFNG_ECDMFAEMMNTL_U2_ID, (void *)&u2t_ecdmfaemMntl );  /* �߂�l�͎g�p���Ȃ� */

    return( u2t_ecdmfaemMntl );
}

/*********************************************************************/
/*  �֐���        | u2g_emfng_ecdmfaemMxtl( )                        */
/*  �������e      | ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�S�C��)�擾�֐� */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�S�C��)   */
/*                |                        lsb=1,unit=��             */
/*  ���ӎ���      |  �X�P�[�����OID =24(ISO 15031-5)                 */
/*********************************************************************/
u2
u2g_emfng_ecdmfaemMxtl( void )
{
    u2 u2t_ecdmfaemMxtl;   /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�S�C��) */

    u2t_ecdmfaemMxtl = (u2)0U;  /* �_�~�[�ݒ� */
    (void)s4g_ememctr_read( u2g_EMFNG_ECDMFAEMMXTL_U2_ID, (void *)&u2t_ecdmfaemMxtl );  /* �߂�l�͎g�p���Ȃ� */

    return( u2t_ecdmfaemMxtl );
}

/*********************************************************************/
/*  �֐���        | u2g_emfng_ecdmfemTv( )                           */
/*  �������e      | ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�C����)�擾�֐� */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | u1t_cyl  :lsb=1 �C��                             */
/*  �߂�l        | ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�C����)         */
/*                |                        lsb=1,unit=��             */
/*  ���ӎ���      |  �X�P�[�����OID =24(ISO 15031-5)                 */
/*********************************************************************/
u2
u2g_emfng_ecdmfemTv( u1 u1t_cyl )
{
    u2 u2t_ecdmfemTv;    /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�C����) */

    u2t_ecdmfemTv = u2g_emfng_ECDMFEMTV_MI;
    if ( u1t_cyl < u1g_ejcc_NCYL )
    {
        (void)s4g_ememctr_read( u2s_ECDMFEMTV_U2_ID[u1t_cyl], (void *)&u2t_ecdmfemTv );  /* �߂�l�͎g�p���Ȃ� */
    }

    return( u2t_ecdmfemTv );
}

/*********************************************************************/
/*  �֐���        | u2g_emfng_ecdmfemMntl( )                         */
/*  �������e      | ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�C����)�擾�֐� */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | u1t_cyl   :lsb=1 �C��                            */
/*  �߂�l        | ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�C����)   */
/*                |                        lsb=1,unit=��             */
/*  ���ӎ���      |  �X�P�[�����OID =24(ISO 15031-5)                 */
/*********************************************************************/
u2
u2g_emfng_ecdmfemMntl( u1 u1t_cyl )
{
    u2 u2t_ecdmfemMntl;    /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�C����) */

    u2t_ecdmfemMntl = u2g_emfng_ECDMFEMMNTL_MI;
    if ( u1t_cyl < u1g_ejcc_NCYL )
    {
        (void)s4g_ememctr_read( u2s_ECDMFEMMNTL_U2_ID[u1t_cyl], (void *)&u2t_ecdmfemMntl );  /* �߂�l�͎g�p���Ȃ� */
    }

    return( u2t_ecdmfemMntl );
}

/*********************************************************************/
/*  �֐���        | u2g_emfng_ecdmfemMxtl( )                         */
/*  �������e      | ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�C����)�擾�֐� */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | u1t_cyl   :lsb=1 �C��                            */
/*  �߂�l        | ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�C����)   */
/*                |                        lsb=1,unit=��             */
/*  ���ӎ���      |  �X�P�[�����OID =24(ISO 15031-5)                 */
/*********************************************************************/
u2
u2g_emfng_ecdmfemMxtl( u1 u1t_cyl )
{
    u2 u2t_ecdmfemMxtl;    /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�C����) */

    u2t_ecdmfemMxtl = u2g_emfng_ECDMFEMMXTL_MI;
    if ( u1t_cyl < u1g_ejcc_NCYL )
    {
        (void)s4g_ememctr_read( u2s_ECDMFEMMXTL_U2_ID[u1t_cyl], (void *)&u2t_ecdmfemMxtl );  /* �߂�l�͎g�p���Ȃ� */
    }

    return( u2t_ecdmfemMxtl );
}

/*********************************************************************/
/*  �֐���        | u2g_emfng_ecdmfaavTv( )                          */
/*  �������e      | ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�S�C��)�擾�֐� */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�S�C��)     */
/*                |                        lsb=1,unit=��             */
/*  ���ӎ���      |  �X�P�[�����OID =24(ISO 15031-5)                 */
/*********************************************************************/
u2
u2g_emfng_ecdmfaavTv( void )
{
    u2 u2t_ecdmfaavTv;   /* lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�S�C��) */

    u2t_ecdmfaavTv = (u2)0U;  /* �_�~�[�ݒ� */
    (void)s4g_ememctr_read( u2g_EMFNG_ECDMFAAVTV_U2_ID, (void *)&u2t_ecdmfaavTv );  /* �߂�l�͎g�p���Ȃ� */

    return( u2t_ecdmfaavTv );
}

/*********************************************************************/
/*  �֐���        | u2g_emfng_ecdmfaavMntl( )                        */
/*  �������e      | ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ��������l(�S�C��)�擾�֐� */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ��������l(�S�C��) */
/*                |                        lsb=1,unit=��             */
/*  ���ӎ���      |  �X�P�[�����OID =24(ISO 15031-5)                 */
/*********************************************************************/
u2
u2g_emfng_ecdmfaavMntl( void )
{
    u2 u2t_ecdmfaavMntl;   /* lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ��������l(�S�C��) */

    u2t_ecdmfaavMntl = (u2)0U;  /* �_�~�[�ݒ� */
    (void)s4g_ememctr_read( u2g_EMFNG_ECDMFAAVMNTL_U2_ID, (void *)&u2t_ecdmfaavMntl );  /* �߂�l�͎g�p���Ȃ� */

    return( u2t_ecdmfaavMntl );
}

/*********************************************************************/
/*  �֐���        | u2g_emfng_ecdmfaavMxtl( )                        */
/*  �������e      | ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ�������l(�S�C��)�擾�֐� */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ�������l(�S�C��) */
/*                |                        lsb=1,unit=��             */
/*  ���ӎ���      |  �X�P�[�����OID =24(ISO 15031-5)                 */
/*********************************************************************/
u2
u2g_emfng_ecdmfaavMxtl( void )
{
    u2 u2t_ecdmfaavMxtl;   /* lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ�������l(�S�C��) */

    u2t_ecdmfaavMxtl = (u2)0U;  /* �_�~�[�ݒ� */
    (void)s4g_ememctr_read( u2g_EMFNG_ECDMFAAVMXTL_U2_ID, (void *)&u2t_ecdmfaavMxtl );  /* �߂�l�͎g�p���Ȃ� */

    return( u2t_ecdmfaavMxtl );
}

/*********************************************************************/
/*  �֐���        | u2g_emfng_ecdmfavTv( )                           */
/*  �������e      | ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�C����)�擾�֐� */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | u1t_cyl   :lsb=1 �C��                            */
/*  �߂�l        | ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�C����)     */
/*                |                        lsb=1,unit=��             */
/*  ���ӎ���      |  �X�P�[�����OID =24(ISO 15031-5)                 */
/*********************************************************************/
u2
u2g_emfng_ecdmfavTv( u1 u1t_cyl )
{
    u2 u2t_ecdmfavTv;    /* lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�C����) */

    u2t_ecdmfavTv = u2g_emfng_ECDMFAVTV_MI;
    if ( u1t_cyl < u1g_ejcc_NCYL )
    {
        (void)s4g_ememctr_read( u2s_ECDMFAVTV_U2_ID[u1t_cyl], (void *)&u2t_ecdmfavTv );  /* �߂�l�͎g�p���Ȃ� */
    }

    return( u2t_ecdmfavTv );
}

/*********************************************************************/
/*  �֐���        | u2g_emfng_ecdmfavMntl( )                         */
/*  �������e      | ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ��������l(�C����)�擾�֐� */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | u1t_cyl   :lsb=1 �C��                            */
/*  �߂�l        | ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ��������l(�C����) */
/*                |                        lsb=1,unit=��             */
/*  ���ӎ���      |  �X�P�[�����OID =24(ISO 15031-5)                 */
/*********************************************************************/
u2
u2g_emfng_ecdmfavMntl( u1 u1t_cyl )
{
    u2 u2t_ecdmfavMntl;    /* lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ��������l(�C����) */

    u2t_ecdmfavMntl = u2g_emfng_ECDMFAVMNTL_MI;
    if ( u1t_cyl < u1g_ejcc_NCYL )
    {
        (void)s4g_ememctr_read( u2s_ECDMFAVMNTL_U2_ID[u1t_cyl], (void *)&u2t_ecdmfavMntl );  /* �߂�l�͎g�p���Ȃ� */
    }

    return( u2t_ecdmfavMntl );
}

/*********************************************************************/
/*  �֐���        | u2g_emfng_ecdmfavMxtl( )                         */
/*  �������e      | ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ�������l(�C����)�擾�֐� */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | u1t_cyl   :lsb=1 �C��                            */
/*  �߂�l        | ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ�������l(�C����) */
/*                |                        lsb=1,unit=��             */
/*  ���ӎ���      |  �X�P�[�����OID =24(ISO 15031-5)                 */
/*********************************************************************/
u2
u2g_emfng_ecdmfavMxtl( u1 u1t_cyl )
{
    u2 u2t_ecdmfavMxtl;    /* lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ�������l(�C����) */

    u2t_ecdmfavMxtl = u2g_emfng_ECDMFAVMXTL_MI;
    if ( u1t_cyl < u1g_ejcc_NCYL )
    {
        (void)s4g_ememctr_read( u2s_ECDMFAVMXTL_U2_ID[u1t_cyl], (void *)&u2t_ecdmfavMxtl );  /* �߂�l�͎g�p���Ȃ� */
    }

    return( u2t_ecdmfavMxtl );
}

/*********************************************************************/
/*  �֐���        | u1s_emfng_exrcdmf( )                             */
/*  �������e      | EWMA���ζ����v�Z�����׸ގ擾����                 */
/*  ����^�C�~���O| emfng_65msl( )                                   */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | EWMA���ζ����v�Z�����׸�                         */
/*  ���ӎ���      | �����֐�                                         */
/*********************************************************************/
static u1
u1s_emfng_exrcdmf( void )
{
    u1 u1t_exrcdmf;     /* lsb=1 :EWMA���ζ����v�Z�����׸� */

    u1t_exrcdmf = (u1)0U;  /* �_�~�[�ݒ� */
    (void)s4g_ememctr_read( u2g_EMFNG_EXRCDMF_U1_ID, (void *)&u1t_exrcdmf );  /* �߂�l�͎g�p���Ȃ� */

    return( u1t_exrcdmf );
}

/*********************************************************************/
/*  �֐���        | u1g_emfng_eocdmfae2mx( )                         */
/*  �������e      | �s�꒲��RAM 1000rev���̍ő呍���Ή� �擾�֐�   */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | 1000rev���̍ő呍���Ή� lsb=1,unit=��          */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
u1
u1g_emfng_eocdmfae2mx( void )
{
    u1  u1t_eocdmfae2mx;    /* lsb=1,unit=�� :1000rev���̍ő呍���Ή� */

    u1t_eocdmfae2mx = (u1)0U;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EOCDMFAE2MX_U1_ID, (void *)&u1t_eocdmfae2mx );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( u1t_eocdmfae2mx );
}

/*********************************************************************/
/*  �֐���        | u1g_emfng_eocjrevem( )                           */
/*  �������e      | �s�꒲��RAM 1000rev���̎n����1000rev�� �擾�֐� */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | 1000rev���̎n����1000rev�� lsb=1,unit=��       */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
u1
u1g_emfng_eocjrevem( void )
{
    u1 u1t_eocjrevem;   /* lsb=1,unit=�� :1000rev���̎n����1000rev�� */

    u1t_eocjrevem = (u1)0U;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EOCJREVEM_U1_ID, (void *)&u1t_eocjrevem );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( u1t_eocjrevem );
}

/*********************************************************************/
/*  �֐���        | s1g_emfng_eothwem( )                             */
/*  �������e      | �s�꒲��RAM 1000rev���̐��� �擾�֐�             */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | 1000rev���̐��� lsb=160/128,unit=��              */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
s1
s1g_emfng_eothwem( void )
{
    s1 s1t_eothwem;     /* lsb=160/128,unit=�� :1000rev���̐��� */

    s1t_eothwem = (s1)0;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EOTHWEM_S1_ID, (void *)&s1t_eothwem );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( s1t_eothwem );
}

/*********************************************************************/
/*  �֐���        | s1g_emfng_eothaem( )                             */
/*  �������e      | �s�꒲��RAM 1000rev���̋z�C�� �擾�֐�           */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | 1000rev���̋z�C�� lsb=160/128,unit=��            */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
s1
s1g_emfng_eothaem( void )
{
    s1 s1t_eothaem;     /* lsb=160/128,unit=�� :1000rev���̋z�C�� */

    s1t_eothaem = (s1)0;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EOTHAEM_S1_ID, (void *)&s1t_eothaem );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( s1t_eothaem );
}

/*********************************************************************/
/*  �֐���        | u1g_emfng_eocdmfem2mx( )                         */
/*  �������e      | �s�꒲��RAM 1000rev���̋C���ʎ��Ή� �擾�֐�   */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | u1t_cyl   :lsb=1 �C��                            */
/*  �߂�l        | 1000rev���̋C���ʎ��Ή� lsb=1,unit=��          */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
u1
u1g_emfng_eocdmfem2mx( u1 u1t_cyl )
{
    u1 u1t_eocdmfem2mx;     /* lsb=1,unit=�� :1000rev���̋C���ʎ��Ή� */

#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    u1t_eocdmfem2mx = u1g_emfng_EOCDMFEM2MX_MI;
    if ( u1t_cyl < u1g_ejcc_NCYL )
    {
        (void)s4g_ememctr_read( u2s_EOCDMFEM2MX_U1_ID[u1t_cyl], (void *)&u1t_eocdmfem2mx );  /* �߂�l�͎g�p���Ȃ� */
    }
#else                             /*�y�s�꒲�����z*/
    u1t_eocdmfem2mx = (u1)0U;  /*�y�s�꒲�����z����0�Œ� */
#endif
    return( u1t_eocdmfem2mx );
}

/*********************************************************************/
/*  �֐���        | u1g_emfng_eospdemav( )                           */
/*  �������e      | �s�꒲��RAM ���ζ��Ď��̕��ώԑ� �擾�֐�        */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | ���ζ��Ď��̕��ώԑ� lsb=256/256,unit=km/h       */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
u1
u1g_emfng_eospdemav( void )
{
    u1 u1t_eospdemav;   /* lsb=256/256,unit=km/h :���ζ��Ď��̕��ώԑ� */

    u1t_eospdemav = (u1)0U;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EOSPDEMAV_U1_ID, (void *)&u1t_eospdemav );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( u1t_eospdemav );
}

/*********************************************************************/
/*  �֐���        | u1g_emfng_eoneemav( )                            */
/*  �������e      | �s�꒲��RAM ���ζ��Ď��̕��ϴݼ�݉�]�� �擾�֐� */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | ���ζ��Ď��̕��ϴݼ�݉�]�� lsb=12800/256,unit=rpm */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
u1
u1g_emfng_eoneemav( void )
{
    u1 u1t_eoneemav;    /* lsb=12800/256,unit=rpm :���ζ��Ď��̕��ϴݼ�݉�]�� */

    u1t_eoneemav = (u1)0U;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EONEEMAV_U1_ID, (void *)&u1t_eoneemav );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( u1t_eoneemav );
}

/*********************************************************************/
/*  �֐���        | u1g_emfng_eoklsmemav( )                          */
/*  �������e      | �s�꒲��RAM ���ζ��Ď��̕��ϕ��� �擾�֐�        */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | ���ζ��Ď��̕��ϕ��� lsb=320/256,unit=%          */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
u1
u1g_emfng_eoklsmemav( void )
{
    u1 u1t_eoklsmemav;      /* lsb=320/256,unit=% :���ζ��Ď��̕��ϕ��� */

    u1t_eoklsmemav = (u1)0U;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EOKLSMEMAV_U1_ID, (void *)&u1t_eoklsmemav );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( u1t_eoklsmemav );
}

/*********************************************************************/
/*  �֐���        | u1g_emfng_eocjmfneemi( )                         */
/*  �������e      | �s�꒲��RAM ���ζ��Ď��̱����Ӱ�މ� �擾�֐�   */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | ���ζ��Ď��̱����Ӱ�މ� lsb=1,unit=��          */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
u1
u1g_emfng_eocjmfneemi( void )
{
    u1 u1t_eocjmfneemi;     /* lsb=1,unit=�� :���ζ��Ď��̱����Ӱ�މ� */

    u1t_eocjmfneemi = (u1)0U;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EOCJMFNEEMI_U1_ID, (void *)&u1t_eocjmfneemi );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( u1t_eocjmfneemi );
}

/*********************************************************************/
/*  �֐���        | u1g_emfng_eocjmfneeml( )                         */
/*  �������e      | �s�꒲��RAM ���ζ��Ď���۰Ӱ�މ� �擾�֐�      */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | ���ζ��Ď���۰Ӱ�މ� lsb=1,unit=��             */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
u1
u1g_emfng_eocjmfneeml( void )
{
    u1 u1t_eocjmfneeml;     /* lsb=1,unit=�� :���ζ��Ď���۰Ӱ�މ� */

    u1t_eocjmfneeml = (u1)0U;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EOCJMFNEEML_U1_ID, (void *)&u1t_eocjmfneeml );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( u1t_eocjmfneeml );
}

/*********************************************************************/
/*  �֐���        | u1g_emfng_eocjmfneemh( )                         */
/*  �������e      | �s�꒲��RAM ���ζ��Ď���ʲӰ�މ� �擾�֐�      */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | ���ζ��Ď���ʲӰ�މ� lsb=1,unit=��             */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
u1
u1g_emfng_eocjmfneemh( void )
{
    u1 u1t_eocjmfneemh;     /* lsb=1,unit=�� :���ζ��Ď���ʲӰ�މ� */

    u1t_eocjmfneemh = (u1)0U;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EOCJMFNEEMH_U1_ID, (void *)&u1t_eocjmfneemh );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( u1t_eocjmfneemh );
}

/*********************************************************************/
/*  �֐���        | u1g_emfng_eocdmfaotmx( )                         */
/*  �������e      | �s�꒲��RAM 200rev�����ζ����̍ő�l �擾�֐�    */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | 200rev�����ζ����̍ő�l lsb=1,unit=��           */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
u1
u1g_emfng_eocdmfaotmx( void )
{
    u1 u1t_eocdmfaotmx;     /* lsb=1,unit=�� :200rev�����ζ����̍ő�l */

    u1t_eocdmfaotmx = (u1)0U;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EOCDMFAOTMX_U1_ID, (void *)&u1t_eocdmfaotmx );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( u1t_eocdmfaotmx );
}

/*********************************************************************/
/*  �֐���        | u1g_emfng_eocjrevot( )                           */
/*  �������e      | �s�꒲��RAM �ő厸�ζ����X�V����1000rev�� �擾�֐� */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �ő厸�ζ����X�V����1000rev�� lsb=1,unit=��    */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
u1
u1g_emfng_eocjrevot( void )
{
    u1 u1t_eocjrevot;       /* lsb=1,unit=�� :�ő厸�ζ����X�V����1000rev�� */

    u1t_eocjrevot = (u1)0U;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EOCJREVOT_U1_ID, (void *)&u1t_eocjrevot );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( u1t_eocjrevot );
}

/*********************************************************************/
/*  �֐���        | s1g_emfng_eothwot( )                             */
/*  �������e      | �s�꒲��RAM �ő厸�ζ����X�V���̐��� �擾�֐�    */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �ő厸�ζ����X�V���̐��� lsb=160/128,unit=��     */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
s1
s1g_emfng_eothwot( void )
{
    s1 s1t_eothwot;     /* lsb=160/128,unit=�� :�ő厸�ζ����X�V���̐��� */

    s1t_eothwot = (s1)0;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EOTHWOT_S1_ID, (void *)&s1t_eothwot );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( s1t_eothwot );
}

/*********************************************************************/
/*  �֐���        | s1g_emfng_eothaot( )                             */
/*  �������e      | �s�꒲��RAM �ő厸�ζ����X�V���̋z�C�� �擾�֐�  */
/*  ����^�C�~���O| �����v����                                       */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �ő厸�ζ����X�V���̋z�C�� lsb=160/128,unit=��   */
/*  ���ӎ���      | �y�s�꒲�����z����0��Ԃ�                        */
/*********************************************************************/
s1
s1g_emfng_eothaot( void )
{
    s1 s1t_eothaot;     /* lsb=160/128,unit=�� :�ő厸�ζ����X�V���̋z�C�� */

    s1t_eothaot = (s1)0;  /*�y�s�꒲�����z����0�Œ� */
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    (void)s4g_ememctr_read( u2g_EMFNG_EOTHAOT_S1_ID, (void *)&s1t_eothaot );  /* �߂�l�͎g�p���Ȃ� */
#endif
    return( s1t_eothaot );
}

/*********************************************************************/
/*  �֐���        | u1s_emfng_wxreqclr( )                            */
/*  �������e      | �s�꒲��RAM��������                              */
/*  ����^�C�~���O| 65ms��(emfng_65msl()���R�[��)                  */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �_�C�A�O����̏����v��(ON:�����v���L��)          */
/*  ���ӎ���      | �����֐�                                         */
/*********************************************************************/
static u1
u1s_emfng_wxreqclr( void )
{
    u1 u1t_xreqclr;
    s4 s4t_i;
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
    u2 u2t_EOCMFMLTH_MI_c;        /* lsb=1,unit=�� :�Ό��C�����Ή�(��)�̕p�x �����l */
    u2 u2t_EOCMFMLTL_MI_c;        /* lsb=1,unit=�� :�Ό��C�����Ή�(��)�̕p�x �����l */
    u1 u1t_EONEMFMLT_MI_c;        /* lsb=200/8,unit=rpm :�Ό��C�����Ύ��̃G���W����]�Ȃ܂��l �����l */
    u2 u2t_EOCMFNH_MI_c;          /* lsb=1,unit=�� :���Ή�(��)�̕p�x �����l */
    u2 u2t_EOCMFNM_MI_c;          /* lsb=1,unit=�� :���Ή�(��)�̕p�x �����l */
    u2 u2t_EOCMFNL_MI_c;          /* lsb=1,unit=�� :���Ή�(��)�̕p�x �����l */
    u1 u1t_EOCDMFAE2MX_MI_c;      /* lsb=1,unit=�� :1000rev�����΃J�E���^�̍ő�l �����l */
    u1 u1t_EOCJREVEM_MI_c;        /* lsb=1,unit=�� :�ő厸�΃J�E���^�X�V����1000rev�� �����l */
    s1 s1t_EOTHWEM_MI_c;          /* lsb=160/128,unit=�� :�ő厸�΃J�E���^�X�V���̐��� �����l */
    s1 s1t_EOTHAEM_MI_c;          /* lsb=160/128,unit=�� :�ő厸�΃J�E���^�X�V���̋z�C�� �����l */
    u1 u1t_EOCDMFEM2MX_MI_c;      /* lsb=1,unit=�� :�ő厸�΃J�E���^�X�V���̋C���ʎ��΃J�E���^ �����l */
    u1 u1t_EOSPDEMAV_MI_c;        /* lsb=256/256,unit=km/h :���΃J�E���g���̕��ώԑ� �����l */
    u1 u1t_EONEEMAV_MI_c;         /* lsb=12800/256,unit=rpm :���΃J�E���g���̕��σG���W����]�� �����l */
    u1 u1t_EOKLSMEMAV_MI_c;       /* lsb=320/256,unit=% :���΃J�E���g���̕��ϕ��� �����l */
    u1 u1t_EOCJMFNEEMI_MI_c;      /* lsb=1,unit=�� :���΃J�E���g���̃A�C�h�����[�h�� �����l */
    u1 u1t_EOCJMFNEEML_MI_c;      /* lsb=1,unit=�� :���΃J�E���g���̃��[���[�h�� �����l */
    u1 u1t_EOCJMFNEEMH_MI_c;      /* lsb=1,unit=�� :���΃J�E���g���̃n�C���[�h�� �����l */
    u1 u1t_EOCDMFAOTMX_MI_c;      /* lsb=1,unit=�� :200rev���ő�J�E���^�ő�l  �����l */
    u1 u1t_EOCJREVOT_MI_c;        /* lsb=1,unit=�� :�ő厸�΃J�E���^�X�V����1000rev�� �����l */
    s1 s1t_EOTHWOT_MI_c;          /* lsb=160/128,unit=�� :�ő厸�΃J�E���^�X�V���̐��� �����l */
    s1 s1t_EOTHAOT_MI_c;          /* lsb=160/128,unit=�� :�ő厸�΃J�E���^�X�V���̋z�C�� �����l */
#endif
    u2 u2t_ECDMFAEMTV_MI_c;       /* lsb=1,unit=�� :�e�X�g���ʏo�͗p���g���b�v�ݐώ��΃J�E���^(�S�C��)�����l */
    u2 u2t_ECDMFAEMMNTL_MI_c;     /* lsb=1,unit=�� :�e�X�g���ʏo�͗p���g���b�v�ݐώ��΃J�E���^�����l(�S�C��)�����l */
    u2 u2t_ECDMFAEMMXTL_MI_c;     /* lsb=1,unit=�� :�e�X�g���ʏo�͗p���g���b�v�ݐώ��΃J�E���^����l(�S�C��)�����l */
    u2 u2t_ECDMFAAVTV_MI_c;       /* lsb=1,unit=�� :�e�X�g���ʏo�͗p�ߋ�10�g���b�vEWMA���΃J�E���^(�S�C��)�����l */
    u2 u2t_ECDMFAAVMNTL_MI_c;     /* lsb=1,unit=�� :�e�X�g���ʏo�͗p�ߋ�10�g���b�vEWMA���΃J�E���^�����l(�S�C��)�����l */
    u2 u2t_ECDMFAAVMXTL_MI_c;     /* lsb=1,unit=�� :�e�X�g���ʏo�͗p�ߋ�10�g���b�vEWMA���΃J�E���^����l(�S�C��)�����l */
    u2 u2t_ECDMFEMTV_MI_c;        /* lsb=1,unit=�� :�e�X�g���ʏo�͗p���g���b�v�ݐώ��΃J�E���^(�C����)�����l */
    u2 u2t_ECDMFEMMNTL_MI_c;      /* lsb=1,unit=�� :�e�X�g���ʏo�͗p���g���b�v�ݐώ��΃J�E���^�����l(�C����)�����l */
    u2 u2t_ECDMFEMMXTL_MI_c;      /* lsb=1,unit=�� :�e�X�g���ʏo�͗p���g���b�v�ݐώ��΃J�E���^����l(�C����)�����l */
    u2 u2t_ECDMFAVTV_MI_c;        /* lsb=1,unit=�� :�e�X�g���ʏo�͗p�ߋ�10�g���b�vEWMA���΃J�E���^(�C����)�����l */
    u2 u2t_ECDMFAVMNTL_MI_c;      /* lsb=1,unit=�� :�e�X�g���ʏo�͗p�ߋ�10�g���b�vEWMA���΃J�E���^�����l(�C����)�����l */
    u2 u2t_ECDMFAVMXTL_MI_c;      /* lsb=1,unit=�� :�e�X�g���ʏo�͗p�ߋ�10�g���b�vEWMA���΃J�E���^����l(�C����)�����l */
    u1 u1t_ncyl_c;                /* lsb=1 :�C���� */

    /* ���[�N�f�[�^������ */
    u1t_xreqclr = u1s_emfng_xreqclr_Lch;

    if ( u1t_xreqclr == (u1)ON )
    {
        u1t_ncyl_c = u1g_ejcc_NCYL;
#if JEOOBD == u1g_EJCC_USE        /*�y�s�꒲���L�z*/
        u2t_EOCMFMLTH_MI_c = u2g_emfng_EOCMFMLTH_MI;
        u2t_EOCMFMLTL_MI_c = u2g_emfng_EOCMFMLTL_MI;
        u1t_EONEMFMLT_MI_c = u1g_emfng_EONEMFMLT_MI;
        u2t_EOCMFNH_MI_c = u2g_emfng_EOCMFNH_MI;
        u2t_EOCMFNM_MI_c = u2g_emfng_EOCMFNM_MI;
        u2t_EOCMFNL_MI_c = u2g_emfng_EOCMFNL_MI;
        u1t_EOCDMFAE2MX_MI_c = u1g_emfng_EOCDMFAE2MX_MI;
        u1t_EOCJREVEM_MI_c = u1g_emfng_EOCJREVEM_MI;
        s1t_EOTHWEM_MI_c = s1g_emfng_EOTHWEM_MI;
        s1t_EOTHAEM_MI_c = s1g_emfng_EOTHAEM_MI;
        u1t_EOCDMFEM2MX_MI_c = u1g_emfng_EOCDMFEM2MX_MI;
        u1t_EOSPDEMAV_MI_c = u1g_emfng_EOSPDEMAV_MI;
        u1t_EONEEMAV_MI_c = u1g_emfng_EONEEMAV_MI;
        u1t_EOKLSMEMAV_MI_c = u1g_emfng_EOKLSMEMAV_MI;
        u1t_EOCJMFNEEMI_MI_c = u1g_emfng_EOCJMFNEEMI_MI;
        u1t_EOCJMFNEEML_MI_c = u1g_emfng_EOCJMFNEEML_MI;
        u1t_EOCJMFNEEMH_MI_c = u1g_emfng_EOCJMFNEEMH_MI;
        u1t_EOCDMFAOTMX_MI_c = u1g_emfng_EOCDMFAOTMX_MI;
        u1t_EOCJREVOT_MI_c = u1g_emfng_EOCJREVOT_MI;
        s1t_EOTHWOT_MI_c = s1g_emfng_EOTHWOT_MI;
        s1t_EOTHAOT_MI_c = s1g_emfng_EOTHAOT_MI;

        /* �s�꒲��RAM���� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOCMFMLTH_U2_ID, (void *)&u2t_EOCMFMLTH_MI_c );           /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOCMFMLTL_U2_ID, (void *)&u2t_EOCMFMLTL_MI_c );           /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EONEMFMLT_U1_ID, (void *)&u1t_EONEMFMLT_MI_c );           /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOCMFNH_U2_ID,   (void *)&u2t_EOCMFNH_MI_c );             /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOCMFNM_U2_ID,   (void *)&u2t_EOCMFNM_MI_c );             /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOCMFNL_U2_ID,   (void *)&u2t_EOCMFNL_MI_c );             /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOCDMFAE2MX_U1_ID, (void *)&u1t_EOCDMFAE2MX_MI_c );       /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOCJREVEM_U1_ID, (void *)&u1t_EOCJREVEM_MI_c );           /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOTHWEM_S1_ID, (void *)&s1t_EOTHWEM_MI_c );               /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOTHAEM_S1_ID, (void *)&s1t_EOTHAEM_MI_c );               /* �߂�l�͎g�p���Ȃ� */
        for ( s4t_i = (s4)0; s4t_i < (s4)u1t_ncyl_c; s4t_i++ )
        {
            (void)s4g_ememctr_write( u2s_EOCDMFEM2MX_U1_ID[s4t_i], (void *)&u1t_EOCDMFEM2MX_MI_c );  /* �߂�l�͎g�p���Ȃ� */
        }
        (void)s4g_ememctr_write( u2g_EMFNG_EOSPDEMAV_U1_ID, (void *)&u1t_EOSPDEMAV_MI_c );           /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EONEEMAV_U1_ID, (void *)&u1t_EONEEMAV_MI_c );             /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOKLSMEMAV_U1_ID, (void *)&u1t_EOKLSMEMAV_MI_c );         /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOCJMFNEEMI_U1_ID, (void *)&u1t_EOCJMFNEEMI_MI_c );       /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOCJMFNEEML_U1_ID, (void *)&u1t_EOCJMFNEEML_MI_c );       /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOCJMFNEEMH_U1_ID, (void *)&u1t_EOCJMFNEEMH_MI_c );       /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOCDMFAOTMX_U1_ID, (void *)&u1t_EOCDMFAOTMX_MI_c );       /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOCJREVOT_U1_ID, (void *)&u1t_EOCJREVOT_MI_c );           /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOTHWOT_S1_ID, (void *)&s1t_EOTHWOT_MI_c );               /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_EOTHAOT_S1_ID, (void *)&s1t_EOTHAOT_MI_c );               /* �߂�l�͎g�p���Ȃ� */
#endif
        /* mode$06�Ή����΃J�E���^���� */
        u2t_ECDMFAEMTV_MI_c = u2g_emfng_ECDMFAEMTV_MI;
        u2t_ECDMFAEMMNTL_MI_c = u2g_emfng_ECDMFAEMMNTL_MI;
        u2t_ECDMFAEMMXTL_MI_c = u2g_emfng_ECDMFAEMMXTL_MI;
        u2t_ECDMFAAVTV_MI_c = u2g_emfng_ECDMFAAVTV_MI;
        u2t_ECDMFAAVMNTL_MI_c = u2g_emfng_ECDMFAAVMNTL_MI;
        u2t_ECDMFAAVMXTL_MI_c = u2g_emfng_ECDMFAAVMXTL_MI;
        u2t_ECDMFEMTV_MI_c = u2g_emfng_ECDMFEMTV_MI;
        u2t_ECDMFEMMNTL_MI_c = u2g_emfng_ECDMFEMMNTL_MI;
        u2t_ECDMFEMMXTL_MI_c = u2g_emfng_ECDMFEMMXTL_MI;
        u2t_ECDMFAVTV_MI_c = u2g_emfng_ECDMFAVTV_MI;
        u2t_ECDMFAVMNTL_MI_c = u2g_emfng_ECDMFAVMNTL_MI;
        u2t_ECDMFAVMXTL_MI_c = u2g_emfng_ECDMFAVMXTL_MI;

        (void)s4g_ememctr_write( u2g_EMFNG_ECDMFAEMTV_U2_ID, (void *)&u2t_ECDMFAEMTV_MI_c );         /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_ECDMFAEMMNTL_U2_ID, (void *)&u2t_ECDMFAEMMNTL_MI_c );     /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_ECDMFAEMMXTL_U2_ID, (void *)&u2t_ECDMFAEMMXTL_MI_c );     /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_ECDMFAAVTV_U2_ID, (void *)&u2t_ECDMFAAVTV_MI_c );         /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_ECDMFAAVMNTL_U2_ID, (void *)&u2t_ECDMFAAVMNTL_MI_c );     /* �߂�l�͎g�p���Ȃ� */
        (void)s4g_ememctr_write( u2g_EMFNG_ECDMFAAVMXTL_U2_ID, (void *)&u2t_ECDMFAAVMXTL_MI_c );     /* �߂�l�͎g�p���Ȃ� */

        for ( s4t_i = (s4)0 ; s4t_i < (s4)u1t_ncyl_c ; s4t_i++ )
        {
            (void)s4g_ememctr_write( u2s_ECDMFEMTV_U2_ID[s4t_i], (void *)&u2t_ECDMFEMTV_MI_c );      /* �߂�l�͎g�p���Ȃ� */
            (void)s4g_ememctr_write( u2s_ECDMFEMMNTL_U2_ID[s4t_i], (void *)&u2t_ECDMFEMMNTL_MI_c );  /* �߂�l�͎g�p���Ȃ� */
            (void)s4g_ememctr_write( u2s_ECDMFEMMXTL_U2_ID[s4t_i], (void *)&u2t_ECDMFEMMXTL_MI_c );  /* �߂�l�͎g�p���Ȃ� */
            (void)s4g_ememctr_write( u2s_ECDMFAVTV_U2_ID[s4t_i], (void *)&u2t_ECDMFAVTV_MI_c );      /* �߂�l�͎g�p���Ȃ� */
            (void)s4g_ememctr_write( u2s_ECDMFAVMNTL_U2_ID[s4t_i], (void *)&u2t_ECDMFAVMNTL_MI_c );  /* �߂�l�͎g�p���Ȃ� */
            (void)s4g_ememctr_write( u2s_ECDMFAVMXTL_U2_ID[s4t_i], (void *)&u2t_ECDMFAVMXTL_MI_c );  /* �߂�l�͎g�p���Ȃ� */
        }
        /* u2g_EMFNG_EXRCDMF_U1_ID�̓N���A�s�v */
    }
    return( u1t_xreqclr );
}

/*********************************************************************/
/*  �֐���        | emfng_emode06_cal( )                             */
/*  �������e      | mode$06�Ή����ζ����̑���                        */
/*  ����^�C�~���O| emfng_65msl( )                                   */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      | �����֐�                                         */
/*********************************************************************/
static void
emfng_emode06_cal( void )
{
#pragma ghs startdata
#if ( JENCYL == u1g_EJCC_6CYL )      /*�y6�C���z*/
 #if ( JEEGTYPE == u1g_EJCC_V6CYL )   /*�yV6�z*/
    /*-----------------------------------------------------------------*/
    /*                         t_cyl=0,    1,    2,    3,    4,    5   */
    /* u1s_emfng_CYLMODTBL[t_cyl] �� 1,    2,    0,    1,    2,    0   */
    /*                              #1#4, #2#5, #3#6, #1#4, #2#5, #3#6 */
    /*-----------------------------------------------------------------*/
    static volatile const u1 u1s_emfng_CYLMODTBL[u1g_EJCC_NCYL] =        /* :�C���Q(ecdmfw[]) �� �C���ϊ��e�[�u��  */
    { (u1)1U, (u1)2U, (u1)0U, (u1)1U, (u1)2U, (u1)0U };                  /* #3#6, #1#4, #2#5  �� #1,#2,#3,#4,#5,#6 */
 #endif
 #if ( JEEGTYPE == u1g_EJCC_L6CYL )   /*�yL6�z*/
    /*-----------------------------------------------------------------*/
    /*                         t_cyl=0,    1,    2,    3,    4,    5   */
    /* u1s_emfng_CYLMODTBL[t_cyl] �� 1,    2,    0,    0,    2,    1   */
    /*                              #1#6, #2#5, #3#4, #3#4, #2#5, #1#6 */
    /*-----------------------------------------------------------------*/
    static volatile const u1 u1s_emfng_CYLMODTBL[u1g_EJCC_NCYL] =        /* :�C���Q(ecdmfw[]) �� �C���ϊ��e�[�u��  */
    { (u1)1U, (u1)2U, (u1)0U, (u1)0U, (u1)2U, (u1)1U };                  /* #3#4, #1#6, #2#5  �� #1,#2,#3,#4,#5,#6 */
 #endif
 #if ( JEEGTYPE == u1g_EJCC_V6CYL )   /*�yV6�z*/
    static volatile const u1 u1s_emfng_CYLWTBL[2][3] = /* :�C���Q(t_cylw) �� �C���ϊ��e�[�u��  */
    {{ (u1)2U, (u1)0U, (u1)1U },              /* #3, #1, #2 */
     { (u1)5U, (u1)3U, (u1)4U }};             /* #6, #4, #5 */
 #elif ( JEEGTYPE == u1g_EJCC_L6CYL ) /*�yL6�z*/
    static volatile const u1 u1s_emfng_CYLWTBL[2][3] = /* :�C���Q(t_cylw) �� �C���ϊ��e�[�u��  */
    {{ (u1)2U, (u1)0U, (u1)1U },              /* #3, #1, #2 */
     { (u1)3U, (u1)5U, (u1)4U }};             /* #4, #6, #5 */
 #endif
#endif
#pragma ghs enddata

    s4  s4t_ecdmfaemTv;     /* ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�S�C��) */
    u2  u2t_ecdmfaemTv;     /* ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�S�C��)(�������ݗp) */
    u2  u2t_ECDMFAEMMNTL_MI_c;  /* lsb=1,unit=�� :�e�X�g���ʏo�͗p���g���b�v�ݐώ��΃J�E���^�����l(�S�C��)�����l */
    u2  u2t_ecdmfaemMxtl;   /* ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�S�C��)(�������ݗp) */
    s4  s4t_ecdmfaemTvo;    /* ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�S�C��)(�O��l) */
    s4  s4t_ecdmfemTv;      /* ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�C����) */
    u2  u2t_ecdmfemTv;      /* ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�C����)(�������ݗp) */
    u2  u2t_ECDMFEMMNTL_MI_c;   /* lsb=1,unit=�� :�e�X�g���ʏo�͗p���g���b�v�ݐώ��΃J�E���^�����l(�C����)�����l */
    u2  u2t_ecdmfemMxtl;    /* ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�C����)(�������ݗp) */
    s4  s4t_cyl;
    s4  s4t_cdmfwa;         /* lsb=1,unit=��:�Ό��C�����΃J�E���^�ώZ�l */
#if JENCYL == u1g_EJCC_6CYL     /*�y6�C���z*/
    s4  s4t_i;              /* lsb=1 :for���[�v�ϐ� */
    u1  u1t_tblidx;         /* :�C���Q(ecdmfw[]) �� �C���ϊ�ð��� �擾�l */
    s4  s4t_cdmfwtmp;       /* lsb=1,unit=��:�C���ʎ��΃J�E���^�̋C���Q���v�l */
    s4  s4t_ecdmfw2;        /* lsb=1,unit=��:�Ό��C�����ζ���(���Z�l) */
    s4  s4t_cdmfemTvtmp[u1g_EJCC_NCYL/2];   /*  lsb=1,unit=�� :�Ό��C�����΃J�E���^�̂P�C�������莸�Ή� */
    s4  s4t_ecdmfw;         /* lsb=1,unit=�� :�Ό��C�����ζ��� */
    u1  u1t_excdmfw;        /* lsb=1 :�Ό��C�����Δ��萬���׸� */
    u1  u1t_idx1;           /* lsb=1 :�C���Q->�C��1�ϊ��pܰ��ϐ� */
    u1  u1t_idx2;           /* lsb=1 :�C���Q->�C��2�ϊ��pܰ��ϐ� */
    u1 u1t_ncylw_c;         /* lsb=1 :�C���Q�� */
#endif
    s4  s4t_ecdmfem[u1g_EJCC_NCYL];         /* lsb=1,unit=��:EM�������ًC���ʎ��ζ��� */
#if ( JETCORE_D == u1g_EJCC_USE ) && ( JEOBDUDS_D == u1g_EJCC_NOT_USE )                            /*�yt-CORE�Ή��L�zAND�yOBDonUDS�Ή����z*/
    u2  u2t_ecdmfaemTv_get; /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�S�C��)(�߂�l�擾�p) */
    u2  u2t_ecdmfaemMntl_get;  /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�S�C��)(�߂�l�擾�p) */
    u2  u2t_ecdmfaemMxtl_get;  /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�S�C��)(�߂�l�擾�p) */
    u2  u2t_dtrid;          /* lsb=1 :ýČ��ʏo�͂h�c */
    u2  u2t_ecdmfemTv_get;  /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�C����)(�߂�l�擾�p) */
    u2  u2t_ecdmfemMntl_get;   /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�C����)(�߂�l�擾�p) */
    u2  u2t_ecdmfemMxtl_get;   /* lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�C����)(�߂�l�擾�p) */
#endif
    u1  u1t_ncyl_c;         /* lsb=1 :�C���� */

    /* ���[�N�f�[�^������ */
    u1t_ncyl_c = u1g_ejcc_NCYL;
    s4t_ecdmfem[0] = (s4)u1g_emfng_ecdmfem[0];
    for ( s4t_cyl = (s4)1; s4t_cyl < (s4)u1t_ncyl_c; s4t_cyl++ )
    {
        s4t_ecdmfem[s4t_cyl] = (s4)u1g_emfng_ecdmfem[s4t_cyl];
    }
    u2t_ECDMFAEMMNTL_MI_c = u2g_emfng_ECDMFAEMMNTL_MI;
    u2t_ECDMFEMMNTL_MI_c = u2g_emfng_ECDMFEMMNTL_MI;

    /**************************/
    /* �C���Q�̑����Ή񐔎Z�o */
    /**************************/
    s4t_cdmfwa = (s4)0;
#if JENCYL == u1g_EJCC_6CYL     /*�y6�C���z*/
    u1t_excdmfw = (u1)big_emfng_excdmfw;
    s4t_cdmfemTvtmp[0] = (s4)0; /* ��а�ݒ�(�����x�����) */
    u1t_ncylw_c = u1s_EMFNG_NCYLW;
    for ( s4t_i = (s4)0; s4t_i < (s4)u1t_ncylw_c ; s4t_i++  )
    {
        s4t_cdmfemTvtmp[s4t_i] = (s4)0;

        if ( u1t_excdmfw == (u1)ON )                      /* �Ό��C������ */
        {
            s4t_ecdmfw = (s4)u1g_emfng_ecdmfw[s4t_i];

            u1t_idx1 = u1s_emfng_CYLWTBL[0][s4t_i];
            u1t_idx2 = u1s_emfng_CYLWTBL[1][s4t_i];

            s4t_cdmfwtmp =  s4t_ecdmfem[u1t_idx1];  /* ����C���Q�̋C��1 */
            s4t_cdmfwtmp += s4t_ecdmfem[u1t_idx2];  /* ����C���Q�̋C��2 */

            s4t_ecdmfw2 = (s4)s2g_glmulst_s2s2u2( (s2)s4t_ecdmfw, s2s_emfng_KCDMFWL, (u2)13U );   /* lsb=1*(2/64/256) -> 1 */
            if ( s4t_cdmfwtmp < s4t_ecdmfw2 )
            {
                s4t_cdmfwa += s4t_ecdmfw;
                /* �Ό��C���p�̃J�E���^���S��255��ł��I�[�o�[�t���[�Ȃ�  */
                s4t_cdmfemTvtmp[s4t_i] = s4g_glbitcal_s4sftr_s4u1( s4t_ecdmfw, (u1)1U );     /* (ecdmfw[]�̊Y���C����)���Q */
            }
        }
    }
#endif

    /* ecdmfaem�O��l */
    s4t_ecdmfaemTvo = (s4)u2g_emfng_ecdmfaemTv();

    /************************************/
    /* �S�C�����Ή�(ecdmfaemTv)�̎Z�o */
    /************************************/
    s4t_ecdmfaemTv = s4t_ecdmfaemTvo            /* �O��l */
                  + s4t_cdmfwa                  /* + EMFCNT_OPPS���̎��Ή񐔁y6�C���z*/
                  + (s4)s2s_emfng_ecdmfaotb;    /* + (ecdmfaot - (ecdtmf2 * KCDTMFAOTB)) */

    /* �㉺���K�[�h���� */
    ELIB_HILOGD2( s4t_ecdmfaemTv, (s4)u2g_U2MAX, s4t_ecdmfaemTvo, s4t_ecdmfaemTv );
    u2t_ecdmfaemTv = (u2)s4t_ecdmfaemTv;

    /* ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�S�C��) */
    (void)s4g_ememctr_write( u2g_EMFNG_ECDMFAEMTV_U2_ID, (void *)&u2t_ecdmfaemTv );                /* �߂�l�͎g�p���Ȃ� */
    /* ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�S�C��) */
    (void)s4g_ememctr_write( u2g_EMFNG_ECDMFAEMMNTL_U2_ID, (void *)&u2t_ECDMFAEMMNTL_MI_c );       /* �߂�l�͎g�p���Ȃ� */
    /* ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�S�C��) */
    u2t_ecdmfaemMxtl = (u2)0xffffU;
    (void)s4g_ememctr_write( u2g_EMFNG_ECDMFAEMMXTL_U2_ID, (void *)&u2t_ecdmfaemMxtl );            /* �߂�l�͎g�p���Ȃ� */
#if ( JETCORE_D == u1g_EJCC_USE ) && ( JEOBDUDS_D == u1g_EJCC_NOT_USE )                            /*�yt-CORE�Ή��L�zAND�yOBDonUDS�Ή����z*/
    u2t_ecdmfaemTv_get   = u2g_emfng_ecdmfaemTv();
    u2t_ecdmfaemMntl_get = u2g_emfng_ecdmfaemMntl();
    u2t_ecdmfaemMxtl_get = u2g_emfng_ecdmfaemMxtl();
    (void)u1g_wtcif_dem_setdtr_u2s4s4s4u1( u2g_WTCIF_DEM_DTR_ECDMFAEM, (s4)u2t_ecdmfaemTv_get, (s4)u2t_ecdmfaemMntl_get, (s4)u2t_ecdmfaemMxtl_get, u1g_WTCIF_DEM_DTR_CTL_NORMAL );  /* �߂�l�͎g�p���Ȃ� */
#endif

    /**************************************************/
    /* ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�C����)�̎Z�o */
    /**************************************************/
    for ( s4t_cyl = (s4)0; s4t_cyl < (s4)u1t_ncyl_c ; s4t_cyl++ )
    {
#if JENCYL == u1g_EJCC_6CYL     /*�y6�C���z*/
        u1t_tblidx = u1s_emfng_CYLMODTBL[ s4t_cyl ];

        /* �Ό��C���� */
        s4t_ecdmfemTv = s4t_cdmfemTvtmp[u1t_tblidx];

        s4t_ecdmfemTv += (s4)u2g_emfng_ecdmfemTv( (u1)s4t_cyl );
#else                           /*�y6�C���ȊO�z*/
        s4t_ecdmfemTv = (s4)u2g_emfng_ecdmfemTv( (u1)s4t_cyl );
#endif
        /* �e�C�����Ƃ̎��Ή� */
        s4t_ecdmfemTv += s4t_ecdmfem[s4t_cyl];

        /* ����K�[�h���� */
        ELIB_HIGHGD2( s4t_ecdmfemTv,(s4)u2g_U2MAX, s4t_ecdmfemTv );
        u2t_ecdmfemTv = (u2)s4t_ecdmfemTv;

        /* ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�C����) */
        (void)s4g_ememctr_write( u2s_ECDMFEMTV_U2_ID[s4t_cyl], (void *)&u2t_ecdmfemTv );           /* �߂�l�͎g�p���Ȃ� */
        /* ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�C����) */
        (void)s4g_ememctr_write( u2s_ECDMFEMMNTL_U2_ID[s4t_cyl], (void *)&u2t_ECDMFEMMNTL_MI_c );  /* �߂�l�͎g�p���Ȃ� */
        /* ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�C����) */
        u2t_ecdmfemMxtl = (u2)0xffffU;
        (void)s4g_ememctr_write( u2s_ECDMFEMMXTL_U2_ID[s4t_cyl], (void *)&u2t_ecdmfemMxtl );       /* �߂�l�͎g�p���Ȃ� */
#if ( JETCORE_D == u1g_EJCC_USE ) && ( JEOBDUDS_D == u1g_EJCC_NOT_USE )                            /*�yt-CORE�Ή��L�zAND�yOBDonUDS�Ή����z*/
        u2t_dtrid = u2s_emfng_ecdmfem_tbl[s4t_cyl];
        u2t_ecdmfemTv_get   = u2g_emfng_ecdmfemTv( (u1)s4t_cyl );
        u2t_ecdmfemMntl_get = u2g_emfng_ecdmfemMntl( (u1)s4t_cyl );
        u2t_ecdmfemMxtl_get = u2g_emfng_ecdmfemMxtl( (u1)s4t_cyl );
        (void)u1g_wtcif_dem_setdtr_u2s4s4s4u1( u2t_dtrid, (s4)u2t_ecdmfemTv_get, (s4)u2t_ecdmfemMntl_get, (s4)u2t_ecdmfemMxtl_get, u1g_WTCIF_DEM_DTR_CTL_NORMAL );  /* �߂�l�͎g�p���Ȃ� */
#endif
    }
}

#if JEMFFC == u1g_EJCC_USE  /*�y�G�}OT���Έُ펞FC�L�z*/
/*********************************************************************/
/*  �֐���        | emfng_exmfotfc_u1( )                             */
/*  �������e      | FC��߼�ݔ���p�G�}OT���وُ�ʒm�׸ނ̏���       */
/*  ����^�C�~���O| emfng_65msl( )                                   */
/*  ����          | u1t_flg   :lsb=1 �t���O���                      */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      | �y�G�}OT���Έُ펞FC�L�z                         */
/*********************************************************************/
void
emfng_exmfotfc_u1( u1 u1t_flg )
{
    s4 s4t_exdmffc;   /* lsb=1:FC��߼�ݔ���p�G�}OT���وُ�ʒm�׸� */

    s4t_exdmffc = (s4)OFF;
    if ( u1t_flg == (u1)ON )
    {
        s4t_exdmffc = (s4)ON;
    }
    u1g_emfng_exdmffc = (u1)s4t_exdmffc;
}
#endif

#if JEOOBD == u1g_EJCC_USE      /*�y�s�꒲���L�z*/
/*********************************************************************/
/*  �֐���        | emfng_espdaemclr( )                              */
/*  �������e      | �s�꒲��RAM�̸ر                                 */
/*  ����^�C�~���O| �����v����                                       */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      | �����֐��y�s�꒲���L�z                           */
/*********************************************************************/
static void
emfng_espdaemclr( void )
{
    /* �N���A���� */
    s4s_emfng_espdaem  = (s4)0;
    s4s_emfng_eneaem   = (s4)0;
    s4s_emfng_eklsmaem = (s4)0;
    u1s_emfng_ecjmfneemi = (u1)0U;
    u1s_emfng_ecjmfneeml = (u1)0U;
    u1s_emfng_ecjmfneemh = (u1)0U;
}
#endif

/*********************************************************************/
/*  �֐���        | emfng_roughjdg_u1u1( )                           */
/*  �������e      | ���H����֘A����                                 */
/*  ����^�C�~���O| TDC��(emfng_mfptn_ann_u1u1u1()����R�[��)        */
/*  ����          | u1t_xmfne      :lsb=1 ���Ζ{����                 */
/*                | u1t_mfkind     :lsb=1 ���Ύ��                   */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      | �����֐�                                         */
/*********************************************************************/
static void
emfng_roughjdg_u1u1( u1 u1t_xmfne, u1 u1t_mfkind )
{
#if JEMFMETHOD_D == u1g_EJCC_TIME_D    /*�y���΃�T�@�z*/
    static volatile s2 s2s_emfng_edltmaxlho; /* lsb=1/8,unit=us :���]���]�ϓ��ʃs�[�N�l�L�� */
    static volatile s2 s2s_emfng_edltmaxhho; /* lsb=1/8,unit=us :����]���]�ϓ��ʃs�[�N�l�L�� */
#endif
#if JEMFMETHOD_D == u1g_EJCC_OMEGA_D   /*�y���΃��֖@�z*/
    static volatile s2 s2s_emfng_ewmaxlo;    /* lsb=32/128/256,unit=CA/ms :���]���]�ϓ��ʃs�[�N�l�L�� */
    static volatile s2 s2s_emfng_ewmaxho;    /* lsb=32/128/256,unit=CA/ms :����]���]�ϓ��ʃs�[�N�l�L�� */
#endif

    u2 u2t_ecdtmfwa;        /* lsb=1,unit=�� :EM�������x������p���H�J�E���^ */
    u1 u1t_ecdtmf2;         /* lsb=1,unit=�� :�G�}OT���x������p���H�J�E���^ */
    u1 u1t_exjtmf;          /* lsb=1 :���΂̉�����֎~�t���O */
    u1 u1t_exjtmf2;         /* lsb=1 :���΂̖{���苖�t���O */
#if JEMFMETHOD_D == u1g_EJCC_TIME_D    /*�y���΃�T�@�z*/
    s2 s2t_edltmaxlo;       /* lsb=1/8,unit=us :���]���]�ϓ��ʃs�[�N�l�L�� */
    s2 s2t_edltmaxho;       /* lsb=1/8,unit=us :����]���]�ϓ��ʃs�[�N�l�L�� */
    s2 s2t_edltmaxl;        /* lsb=1/8,unit=us :��]�ϓ��ʃs�[�N�l(Low���[�h) */
    s2 s2t_edltmaxh;        /* lsb=1/8,unit=us :��]�ϓ��ʃs�[�N�l(High���[�h) */
#endif
#if JEMFMETHOD_D == u1g_EJCC_OMEGA_D   /*�y���΃��֖@�z*/
    s2 s2t_ewmaxlo;         /* lsb=32/128/256,unit=CA/ms :���]���]�ϓ��ʃs�[�N�l�L�� */
    s2 s2t_ewmaxho;         /* lsb=32/128/256,unit=CA/ms :����]���]�ϓ��ʃs�[�N�l�L�� */
    s2 s2t_ewmaxl;          /* lsb=32/128/256,unit=CA/ms :��]�ϓ��ʃs�[�N�l(Low���[�h) */
    s2 s2t_ewmaxh;          /* lsb=32/128/256,unit=CA/ms :��]�ϓ��ʃs�[�N�l(High���[�h) */
#endif
    s2 s2t_espd;            /* lsb=256/256,unit=km/h :�ԑ� */
    u1 u1t_ejmfne;          /* lsb=1 :��]�̈攻��l */
    s2 s2t_MFSPD_c;         /* lsb=256/256,unit=km/h :���s��Ԕ���l */
    u1 u1t_CJPMF_c;         /* lsb=1,unit=�� :�[���N���X�J�E���^����l */

    /* ���[�N�f�[�^������ */
    u1t_exjtmf = (u1)bis_emfng_exjtmf;
    u1t_exjtmf2 = (u1)bis_emfng_exjtmf2;
#if JEMFMETHOD_D == u1g_EJCC_TIME_D    /*�y���΃�T�@�z*/
    s2t_edltmaxlo = s2s_emfng_edltmaxlho;
    s2t_edltmaxho = s2s_emfng_edltmaxhho;
    s2t_edltmaxl = s2g_emfcc_edltmaxlh;
    s2t_edltmaxh = s2g_emfcc_edltmaxhh;
#endif
#if JEMFMETHOD_D == u1g_EJCC_OMEGA_D   /*�y���΃��֖@�z*/
    s2t_ewmaxlo = s2s_emfng_ewmaxlo;
    s2t_ewmaxho = s2s_emfng_ewmaxho;
    s2t_ewmaxl = s2g_emfcc_ewmaxl;
    s2t_ewmaxh = s2g_emfcc_ewmaxh;
#endif
    s2t_espd = s2g_espd_espd;
    u1t_ejmfne = u1g_emfne_ejmfne;
    s2t_MFSPD_c = s2g_emfcnt_MFSPD;
    u1t_CJPMF_c = u1s_emfng_CJPMF;

    if ( u1t_xmfne == (u1)ON )                             /* �{����^�C�~���O */
    {
        /**********************************************/
        /* EM�������x������p���H�J�E���^�A           */
        /* �G�}OT���x������p���H�J�E���^�A           */
        /* ���픻��p���H�J�E���^�̃J�E���g�A�b�v�ʒm */
        /**********************************************/
        u2t_ecdtmfwa = u2s_emfng_ecdtmfwa;
        u1t_ecdtmf2 = u1g_emfng_ecdtmf2;
        if ( ( u1t_mfkind == u1g_EMFCNT_NOT )          /* ���Δ���s���� */
          && ( u1t_exjtmf == (u1)OFF )                 /* ���Ή����苖�� */
#if JEMFHOUKI == u1g_EJCC_USAMF /*�y�ΕĖ@�K�z*/
          && ( big_emfcnt_exptnup == (u1)OFF )
#endif
          && ( s2t_espd >= s2t_MFSPD_c ) )
        {
            if ( u2t_ecdtmfwa < u2g_U2MAX )
            {
                u2t_ecdtmfwa++;
            }
            if ( u1t_ecdtmf2 < u1g_U1MAX )
            {
                u1t_ecdtmf2++;
            }
            emfok_roughcnt();
        }
        /* RAM�f�[�^�Ɋi�[ */
        u2s_emfng_ecdtmfwa = u2t_ecdtmfwa;
        u1g_emfng_ecdtmf2 = u1t_ecdtmf2;

        /*******************************************************/
        /* ���΂̉�����֎~�t���O,���΂̖{���苖�t���O�̑��� */
        /*******************************************************/
        if ( ( s2t_espd >= s2t_MFSPD_c )
          && ( ( u1t_mfkind == u1g_EMFCNT_LOW )        /* ���]�������_������ */
            || ( u1t_mfkind == u1g_EMFCNT_HIGH ) ) )   /* ����]�������_������ */
        {
            u1t_exjtmf = (u1)ON;
            u1t_exjtmf2 = (u1)ON;                      /* XJTMF�Ɠ�����ON */
            u1s_emfng_ecjpmf = (u1)0U;                 /* �[���N���X�J�E���^���N���A */
        }

        /**************************************/
        /* ��]�ϓ��ʃs�[�N�l�̗����̍X�V���� */
        /**************************************/
        if ( ( u1t_mfkind == u1g_EMFCNT_NOT )          /* ���Δ���s���� */
          && ( u1t_exjtmf == (u1)ON ) )                /* ���Ή�����֎~ */
        {
            if ( u1t_exjtmf2 == (u1)ON )
            {
#if JEMFMETHOD_D == u1g_EJCC_TIME_D    /*�y���΃�T�@�z*/
                s2t_edltmaxlo = s2t_edltmaxl;
                s2t_edltmaxho = s2t_edltmaxh;
#endif
#if JEMFMETHOD_D == u1g_EJCC_OMEGA_D   /*�y���΃��֖@�z*/
                s2t_ewmaxlo = s2t_ewmaxl;
                s2t_ewmaxho = s2t_ewmaxh;
#endif
                u1t_exjtmf2 = (u1)OFF;            /* ��]�ϓ��ʃs�[�N�l�̗����̍X�V��XJTMF2��OFF */
            }
            if ( ( u1t_ejmfne == u1g_EMFNE_REV_LOW )
#if JEMFMETHOD_D == u1g_EJCC_TIME_D    /*�y���΃�T�@�z*/
              && ( s2t_edltmaxlo >= s2t_edltmaxl )     /* ���Ζ{���苖�� */
#endif
#if JEMFMETHOD_D == u1g_EJCC_OMEGA_D   /*�y���΃��֖@�z*/
              && ( s2t_ewmaxlo <= s2t_ewmaxl )         /* ���Ζ{���苖�� */
#endif
               )
            {
#if JEMFMETHOD_D == u1g_EJCC_TIME_D    /*�y���΃�T�@�z*/
                s2t_edltmaxlo = s2t_edltmaxl;
#endif
#if JEMFMETHOD_D == u1g_EJCC_OMEGA_D   /*�y���΃��֖@�z*/
                s2t_ewmaxlo = s2t_ewmaxl;
#endif
                u1t_exjtmf2 = (u1)OFF;            /* ��]�ϓ��ʃs�[�N�l�̗����̍X�V��XJTMF2��OFF */
            }
            if ( ( u1t_ejmfne == u1g_EMFNE_REV_HIGH )
#if JEMFMETHOD_D == u1g_EJCC_TIME_D    /*�y���΃�T�@�z*/
              && ( s2t_edltmaxho >= s2t_edltmaxh )     /* ���Ζ{���苖�� */
#endif
#if JEMFMETHOD_D == u1g_EJCC_OMEGA_D   /*�y���΃��֖@�z*/
              && ( s2t_ewmaxho <= s2t_ewmaxh )         /* ���Ζ{���苖�� */
#endif
               )
            {
#if JEMFMETHOD_D == u1g_EJCC_TIME_D    /*�y���΃�T�@�z*/
                s2t_edltmaxho = s2t_edltmaxh;
#endif
#if JEMFMETHOD_D == u1g_EJCC_OMEGA_D   /*�y���΃��֖@�z*/
                s2t_ewmaxho = s2t_ewmaxh;
#endif
                u1t_exjtmf2 = (u1)OFF;            /* ��]�ϓ��ʃs�[�N�l�̗����̍X�V��XJTMF2��OFF */
            }
        }
    }   /* (t_xmfne �� ON) end */

    /*******************************************************/
    /* ���΂̉�����֎~�t���O,���΂̖{���苖�t���O�̑��� */
    /*******************************************************/
    if ( ( s2t_espd < s2t_MFSPD_c )
      || ( u1s_emfng_ecjpmf >= u1t_CJPMF_c )
      || ( ( u1t_exjtmf2 == (u1)OFF )
        && ( ( ( u1t_ejmfne == u1g_EMFNE_REV_LOW )
#if JEMFMETHOD_D == u1g_EJCC_TIME_D    /*�y���΃�T�@�z*/
            && ( s2t_edltmaxlo < s2t_edltmaxl )
#endif
#if JEMFMETHOD_D == u1g_EJCC_OMEGA_D   /*�y���΃��֖@�z*/
            && ( s2t_ewmaxlo > s2t_ewmaxl )
#endif
             )
          || ( ( u1t_ejmfne == u1g_EMFNE_REV_HIGH )
#if JEMFMETHOD_D == u1g_EJCC_TIME_D    /*�y���΃�T�@�z*/
            && ( s2t_edltmaxho < s2t_edltmaxh )
#endif
#if JEMFMETHOD_D == u1g_EJCC_OMEGA_D   /*�y���΃��֖@�z*/
            && ( s2t_ewmaxho > s2t_ewmaxh )
#endif
             ) )
        && ( u1t_xmfne == (u1)ON )                     /* �{����^�C�~���O */
        && ( u1t_mfkind == u1g_EMFCNT_NOT ) ) )        /* ���]or����]���Δ���s���� */
    {
        u1t_exjtmf = (u1)OFF;                          /* ���Ή����苖�� */
        u1s_emfng_ecjpmf = (u1)0U;                     /* �[���N���X�J�E���^���N���A */
    }
    if ( s2t_espd < s2t_MFSPD_c )
    {
        u1t_exjtmf2 = (u1)OFF;                         /* ���Ζ{����֎~ */
    }

    /* RAM�f�[�^�Ɋi�[ */
    glbitcp_bibi( u1t_exjtmf, bis_emfng_exjtmf );
    glbitcp_bibi( u1t_exjtmf2, bis_emfng_exjtmf2 );
#if JEMFMETHOD_D == u1g_EJCC_TIME_D    /*�y���΃�T�@�z*/
    s2s_emfng_edltmaxlho = s2t_edltmaxlo;
    s2s_emfng_edltmaxhho = s2t_edltmaxho;
#endif
#if JEMFMETHOD_D == u1g_EJCC_OMEGA_D   /*�y���΃��֖@�z*/
    s2s_emfng_ewmaxlo = s2t_ewmaxlo;
    s2s_emfng_ewmaxho = s2t_ewmaxho;
#endif
}
/**** End of File ****************************************************/
