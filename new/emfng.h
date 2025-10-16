/* emfng-pa000-5000-a-M4 */
/***********************************************************************/
/*  Copyright Toyota Motor Corporation                                 */
/***********************************************************************/
/*  Version: aa0-51-a                                                  */

/***********************************************************************/
/* �I�u�W�F�N�g��  | ���Ό��o�ُ픻�蕔                                */
/* ���ӎ���        | �y����OBD�L�zAND(�y4�C���zOR�y6�C���z)            */
/*---------------------------------------------------------------------*/
/*  I/F�ύX����    | aa0-51                                            */
/*                 |  aa0-50�x�[�X                                     */
/*                 |  ���i�S�̃R���p�C��SW�Ɂy4�C���zOR�y6�C���z��ǉ� */
/*                 |  �ȉ��̊֐����폜                                 */
/*                 |   emfng_360cam(),emfng_cigfps_inc_u1()            */
/*                 |  �ȉ��̃o�b�N�A�b�vRAM�擾�֐�����ύX            */
/*                 |   u2g_emfng_ecdmfaemc() �� u2g_emfng_ecdmfaemTv() */
/*                 |   u2g_emfng_ecdmfaeml() �� u2g_emfng_ecdmfaemMntl() */
/*                 |   u2g_emfng_ecdmfaemh() �� u2g_emfng_ecdmfaemMxtl() */
/*                 |   u2g_emfng_ecdmfemc() �� u2g_emfng_ecdmfemTv()   */
/*                 |   u2g_emfng_ecdmfeml() �� u2g_emfng_ecdmfemMntl() */
/*                 |   u2g_emfng_ecdmfemh() �� u2g_emfng_ecdmfemMxtl() */
/*                 |   u2g_emfng_ecdmfaavc() �� u2g_emfng_ecdmfaavTv() */
/*                 |   u2g_emfng_ecdmfaavl() �� u2g_emfng_ecdmfaavMntl() */
/*                 |   u2g_emfng_ecdmfaavh() �� u2g_emfng_ecdmfaavMxtl() */
/*                 |   u2g_emfng_ecdmfavc() �� u2g_emfng_ecdmfavTv()   */
/*                 |   u2g_emfng_ecdmfavl() �� u2g_emfng_ecdmfavMntl() */
/*                 |   u2g_emfng_ecdmfavh() �� u2g_emfng_ecdmfavMxtl() */
/*                 |  �ȉ��̃o�b�N�A�b�vRAM�擾(���ϕ���)�̊֐���,LSB,�P�ʂ�ύX */
/*                 |   u1g_emfng_eognsmemav() �� u1g_emfng_eoklsmemav() */
/*                 |   LSB,�P��:lsb=4/256,unit=g/rev �� lsb=320/256,unit=% */
/*                 |  �ȉ��̕ϐ����폜                                 */
/*                 |   u2g_emfng_ecdigf                                */
/*                 |  �ȉ��̔���J�I�[�g�J�E���^���폜                 */
/*                 |   s1g_emfng_ecigtctmf_4m,s1g_emfng_ecigswmf_8m    */
/*                 |   s1g_emfng_ecstamf_8m,s1g_emfng_ecbatmf_8m       */
/*                 |  �ȉ��̃t���O��ǉ�                               */
/*                 |   big_emfng_exenable,big_emfng_excomplete         */
/*                 |  �ȉ��̃o�b�N�A�b�vRAM�����l�萔��ǉ�            */
/*                 |   u2g_emfng_EOCMFNL_MI,u2g_emfng_EOCMFNM_MI       */
/*                 |   u2g_emfng_EOCMFNH_MI,u2g_emfng_EOCMFMLTL_MI     */
/*                 |   u2g_emfng_EOCMFMLTH_MI,u1g_emfng_EONEMFMLT_MI   */
/*                 |  �o�b�N�A�b�vRAM-ID����ύX(u2g_****_SID �� u2g_****_ID) */
/*                 |  �o�b�N�A�b�vRAM�����l����ύX(u2g_**** �� u2g_****_MI) */
/*                 | aa0-42                                            */
/*                 |  ���J�ϐ�u1g_emfng_ecdmffcbnk[]�y�G�}OT���Έُ펞FC�L�z���폜 */
/*                 | aa0-43                                            */
/*                 | �o�b�N�A�b�vRAM��ID�A�����l�y�ю擾�֐�����       */
/*                 | �y�޲���CAN�Ή��L�z���폜                         */
/*                 |  �ȉ��̌��J�֐����폜                             */
/*                 |   emfng_ecdtmfzn_reset()                          */
/*                 |   emfng_360cam()                                  */
/*                 |  �ȉ��̌��J�ϐ����폜                             */
/*                 |   u1g_emfng_ecdtmfzn                              */
/*                 |  �ȉ��̌��J�t���O���폜                           */
/*                 |   big_emfng_exenable                              */
/*                 |  �ȉ��̌��J�t���O��ǉ�                           */
/*                 |   big_emfng_exdisable                             */
/*                 | aa0-44                                            */
/*                 |  ���i�S�̃R���p�C��SW����y4�C���zOR�y6�C���z���폜 */
/*                 |  �ȉ��̌��J�֐����폜                             */
/*                 |   emfng_igsw_reset()                              */
/*                 |  �ȉ��̌��J�֐���ǉ�                             */
/*                 |   emfng_drvclchg()                                */
/*                 |   emfng_reset_ecwamask() �y6�C���z                */
/*                 |  �ȉ��̌��J�ϐ����폜                             */
/*                 |   s2g_emfng_ekneh�y6�C���z                        */
/*                 | aa0-46                                            */
/*                 |  ���J�֐�emfng_reset_ecwamask()���폜 �y6�C���z   */
/*                 | aa0-47                                            */
/*                 |  ���i�S�̃R���p�C��SW�Ɂy4�C���zOR�y6�C���z��ǉ� */
/*                 | aa0-48                                            */
/*                 |  �y8�C���z����I/F���폜                           */
/*                 | aa0-50                                            */
/*                 |  �ȉ��̌��J�ϐ���ǉ�                             */
/*                 |   big_emfng_exdmf�yt-CORE�Ή��L�z                 */
/*                 |  �ȉ��̕ϐ���static�ϐ�������J�ϐ��ɕύX         */
/*                 |   u1g_emfng_ecdtmf2                               */
/*                 |  �ȉ��̌��Jmap��ǉ�                              */
/*                 |   s2g_emfng_emfrtotgpf_map�yGPF�L�z               */
/*---------------------------------------------------------------------*/
/*  �t�@�C���\��   | emfng_l_mat.c,emfng_4_c_mat.c�y4�C���z            */
/*                 | emfng_6_c_mat.c�y6�C���z                          */
/*---------------------------------------------------------------------*/
/*     �ʕύX���� �i�ʕύX���͈ȉ��ɕύX���A���e���L�����邱�Ɓj   */
/***********************************************************************/

#ifndef EMFNG_H
#define EMFNG_H

/*-------------------------------------------------------------------*/
/* �w�b�_�t�@�C���̃C���N���[�h                                      */
/*-------------------------------------------------------------------*/
#include <engsrc/espc/ejcc.h>              /* u1g_EJCC_NCYL */

/*-------------------------------------------------------------------*/
/* �R���p�C��SW����`�`�F�b�N                                        */
/*-------------------------------------------------------------------*/
#if !defined u1g_EJCC_NCYL
#error "u1g_EJCC_NCYL is undeclared"
#endif

/*---------------------------------------------------------------------*/
/* �^��`                                                              */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* �֐�                                                                */
/*---------------------------------------------------------------------*/
void emfng_pwon( void );                         /* :���������� */
                                                 /* �R�[���� : emfcnt_pwon() */

void emfng_tdcm( void );                         /* :TDC���ݸޏ���           */
                                                 /* �R�[���� : emfcnt_tdcm() */

void emfng_16msl( void );                        /* :16ms���ݸޏ���           */
                                                 /* �R�[���� : emfcnt_16msl() */

void emfng_65msl( void );                        /* :65ms���ݸޏ���           */
                                                 /* �R�[���� : emfcnt_65msl() */

void emfng_xjmf_ann_u1( u1 u1t_xjmf );           /* :���Ή����茋�ʒʒm����  */
                                                 /* �R�[���� : emfcnt_tdcm() */
                                                 /* ���� u1t_xjmf     :lsb=1 :�����茋�� */

void emfng_mfptn_ann_u1u1u1( u1 u1t_mfkind, u1 u1t_mfcyl, u1 u1t_xmfne ); /* :���o���¶����̑��� */
                                                 /* �R�[���� : emfcnt_tdcm()             */
                                                 /* ���� u1t_mfkind   :lsb=1 :���Ύ��   */
                                                 /* ���� u1t_mfcyl    :lsb=1 :���΋C��   */
                                                 /* ���� u1t_xmfne    :lsb=1 :���Ζ{���� */

void emfng_reset( void );                        /* :���Δ���ؾ�ď���        */
                                                 /* �R�[���� : emfcnt_tdcm() */

void emfng_drvclchg( void );                     /* �h���C�r���O�T�C�N���ڍs���̏��������� */
                                                 /* �R�[���� : emfcnt_drvclchg()           */

void emfng_cjpmf_inc_u1( u1 u1t_timming );       /* :��۸۽�������� */
                                                 /* �R�[���� : emfccrnk_b30mb60m()                           */
                                                 /*          : emfccrnk_atdc30m()                            */
                                                 /* ���� u1t_timming  :lsb=1 :ecjpmf�J�E���g�A�b�v�^�C�~���O */

void emfng_mfmlt_ann_u1u1( u1 u1t_mfkind, u1 u1t_mfcyl );    /* :�Ό��C�����Βʒm����  */
                                                 /* �R�[���� : emfcnt_neg_mlt()        */
                                                 /* ���� u1t_mfkind   :lsb=1 :���Ύ�� */
                                                 /* ���� u1t_mfcyl    :lsb=1 :���΋C�� */
                                                 /* ���ӎ��� : �y6�C���z               */

void emfng_exmfotfc_u1( u1 u1t_flg );            /* :FC��߼�ݔ���p�G�}OT���وُ�ʒm�׸ނ̏��� */
                                                 /* �R�[���� : emffc_65msl()           */
                                                 /* ���� u1t_flg :lsb=1 :�t���O���    */
                                                 /* ���ӎ��� : �y�G�}OT���Έُ펞FC�L�z*/

void emfng_cntclr_65msl( void );                 /* �O���Q�Ǝ��ζ����̸ر���� */
                                                 /* �R�[���� : emfcnt_65msl() */

u2 u2g_emfng_eocmfnl( void );                    /* :�s�꒲��RAM ���Ή�(��)�̕p�x �擾�֐� */
                                                 /* �R�[���� : �C��                          */
                                                 /* �߂�l   :lsb=1 ,unit=�� :���Ή�(��)�̕p�x */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�     */

u2 u2g_emfng_eocmfnm( void );                    /* :�s�꒲��RAM ���Ή�(��)�̕p�x �擾�֐� */
                                                 /* �R�[���� : �C��                          */
                                                 /* �߂�l   :lsb=1 ,unit=�� :���Ή�(��)�̕p�x */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�     */

u2 u2g_emfng_eocmfnh( void );                    /* :�s�꒲��RAM ���Ή�(��)�̕p�x �擾�֐� */
                                                 /* �R�[���� : �C��                          */
                                                 /* �߂�l   :lsb=1 ,unit=�� :���Ή�(��)�̕p�x */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�     */

u2 u2g_emfng_eocmfmltl( void );                  /* :�s�꒲��RAM �Ό��C�����Ή�(��)�̕p�x �擾�֐� */
                                                 /* �R�[���� : �C��                                  */
                                                 /* �߂�l   :lsb=1 ,unit=�� :�Ό��C�����Ή�(��)�̕p�x */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�             */

u2 u2g_emfng_eocmfmlth( void );                  /* :�s�꒲��RAM �Ό��C�����Ή�(��)�̕p�x �擾�֐� */
                                                 /* �R�[���� : �C��                                  */
                                                 /* �߂�l   :lsb=1 ,unit=�� :�Ό��C�����Ή�(��)�̕p�x */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�             */

u1 u1g_emfng_eonemfmlt( void );                  /* :�s�꒲��RAM �Ό��C�����Ύ��̴ݼ�݉�]�Ȃ܂��l �擾�֐� */
                                                 /* �R�[���� : �C��                                 */
                                                 /* �߂�l   :lsb=200/8 ,unit=rpm :�Ό��C�����Ύ��̴ݼ�݉�]�Ȃ܂��l */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�            */

u2 u2g_emfng_ecdmfaemTv( void );                 /* :ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�S�C��)�擾�֐� */
                                                 /* �R�[���� : �C��                                   */
                                                 /* �߂�l   :lsb=1 ,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�S�C��) */
                                                 /* ���ӎ��� : �X�P�[�����OID = 24                    */

u2 u2g_emfng_ecdmfaemMntl( void );               /* :ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�S�C��)�擾�֐� */
                                                 /* �R�[���� : �C��                                         */
                                                 /* �߂�l   :lsb=1 ,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�S�C��) */
                                                 /* ���ӎ��� : �X�P�[�����OID = 24                          */

u2 u2g_emfng_ecdmfaemMxtl( void );               /* :ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�S�C��)�擾�֐� */
                                                 /* �R�[���� : �C��                                         */
                                                 /* �߂�l   :lsb=1 ,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�S�C��) */
                                                 /* ���ӎ��� : �X�P�[�����OID = 24                          */

u2 u2g_emfng_ecdmfemTv( u1 u1t_cyl );            /* :ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�C����)�擾�֐� */
                                                 /* �R�[���� : �C��                                   */
                                                 /* ���� u1t_cyl    :lsb=1 :�C���ԍ�                  */
                                                 /* �߂�l          :lsb=1 ,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�C����) */
                                                 /* ���ӎ��� : �X�P�[�����OID = 24                    */

u2 u2g_emfng_ecdmfemMntl( u1 u1t_cyl );          /* :ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�C����)�擾�֐� */
                                                 /* �R�[���� : �C��                                         */
                                                 /* ���� u1t_cyl    :lsb=1 :�C���ԍ�                        */
                                                 /* �߂�l          :lsb=1 ,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�C����) */
                                                 /* ���ӎ��� : �X�P�[�����OID = 24                          */

u2 u2g_emfng_ecdmfemMxtl( u1 u1t_cyl );          /* :ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�C����)�擾�֐� */
                                                 /* �R�[���� : �C��                                         */
                                                 /* ���� u1t_cyl    :lsb=1 :�C���ԍ�                        */
                                                 /* �߂�l          :lsb=1 ,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�C����) */
                                                 /* ���ӎ��� : �X�P�[�����OID = 24                          */

u2 u2g_emfng_ecdmfaavTv( void );                 /* :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�S�C��)�擾�֐� */
                                                 /* �R�[���� : �C��                                       */
                                                 /* �߂�l   :lsb=1 ,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�S�C��) */
                                                 /* ���ӎ��� : �X�P�[�����OID = 24                        */

u2 u2g_emfng_ecdmfaavMntl( void );               /* :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ��������l(�S�C��)�擾�֐� */
                                                 /* �R�[���� : �C��                                             */
                                                 /* �߂�l   :lsb=1 ,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ��������l(�S�C��) */
                                                 /* ���ӎ��� : �X�P�[�����OID = 24                              */

u2 u2g_emfng_ecdmfaavMxtl( void );               /* :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ�������l(�S�C��)�擾�֐� */
                                                 /* �R�[���� : �C��                                             */
                                                 /* �߂�l   :lsb=1 ,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ�������l(�S�C��) */
                                                 /* ���ӎ��� : �X�P�[�����OID = 24                              */

u2 u2g_emfng_ecdmfavTv( u1 u1t_cyl );            /* :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�C����)�擾�֐� */
                                                 /* �R�[���� : �C��                                       */
                                                 /* ���� u1t_cyl    :lsb=1 :�C���ԍ�                      */
                                                 /* �߂�l          :lsb=1 ,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�C����) */
                                                 /* ���ӎ��� : �X�P�[�����OID = 24                        */

u2 u2g_emfng_ecdmfavMntl( u1 u1t_cyl );          /* :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ��������l(�C����)�擾�֐� */
                                                 /* �R�[���� : �C��                                             */
                                                 /* ���� u1t_cyl    :lsb=1 :�C���ԍ�                            */
                                                 /* �߂�l          :lsb=1 ,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ��������l(�C����) */
                                                 /* ���ӎ��� : �X�P�[�����OID = 24                              */

u2 u2g_emfng_ecdmfavMxtl( u1 u1t_cyl );          /* :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ�������l(�C����)�擾�֐� */
                                                 /* �R�[���� : �C��                                             */
                                                 /* ���� u1t_cyl    :lsb=1 :�C���ԍ�                            */
                                                 /* �߂�l          :lsb=1 ,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ�������l(�C����) */
                                                 /* ���ӎ��� : �X�P�[�����OID = 24                              */

u1  u1g_emfng_eocdmfae2mx( void );               /* :�s�꒲��RAM 1000rev���̍ő呍���Ή� �擾�֐�     */
                                                 /* �R�[���� : �C��                                     */
                                                 /* �߂�l   :lsb=1 ,unit=�� :1000rev���̍ő呍���Ή� */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�                */

u1  u1g_emfng_eocjrevem( void );                 /* :�s�꒲��RAM 1000rev���̎n����1000rev�� �擾�֐�     */
                                                 /* �R�[���� : �C��                                        */
                                                 /* �߂�l   :lsb=1 ,unit=�� :1000rev���̎n����1000rev�� */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�                   */

s1  s1g_emfng_eothwem( void );                   /* :�s�꒲��RAM 1000rev���̐��� �擾�֐�          */
                                                 /* �R�[���� : �C��                                */
                                                 /* �߂�l   :lsb=160/128,unit=�� :1000rev���̐��� */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�           */

s1  s1g_emfng_eothaem( void );                   /* :�s�꒲��RAM 1000rev���̋z�C�� �擾�֐�          */
                                                 /* �R�[���� : �C��                                  */
                                                 /* �߂�l   :lsb=160/128,unit=�� :1000rev���̋z�C�� */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�             */

u1  u1g_emfng_eocdmfem2mx( u1 u1t_cyl );         /* :�s�꒲��RAM 1000rev���̋C���ʎ��Ή� �擾�֐�    */
                                                 /* �R�[���� : �C��                                    */
                                                 /* ���� u1t_cyl    :lsb=1 :�C���ԍ�                   */
                                                 /*  �߂�l  :1000rev���̋C���ʎ��Ή� lsb=1,unit=��  */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�               */

u1  u1g_emfng_eospdemav( void );                 /* :�s�꒲��RAM ���ζ��Ď��̕��ώԑ� �擾�֐�            */
                                                 /* �R�[���� : �C��                                       */
                                                 /* �߂�l   :lsb=256/256,unit=km/h :���ζ��Ď��̕��ώԑ� */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�                  */

u1  u1g_emfng_eoneemav( void );                  /* :�s�꒲��RAM ���ζ��Ď��̕��ϴݼ�݉�]�� �擾�֐�             */
                                                 /* �R�[���� : �C��                                               */
                                                 /* �߂�l   :lsb=12800/256,unit=rpm :���ζ��Ď��̕��ϴݼ�݉�]�� */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�                          */

u1  u1g_emfng_eoklsmemav( void );                /* :�s�꒲��RAM ���ζ��Ď��̕��ϕ��� �擾�֐�           */
                                                 /* �R�[���� : �C��                                      */
                                                 /* �߂�l   :lsb=320/256,unit=% :���ζ��Ď��̕��ϕ���   */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�                 */

u1  u1g_emfng_eocjmfneemi( void );               /* :�s�꒲��RAM ���ζ��Ď��̱����Ӱ�މ� �擾�֐�    */
                                                 /* �R�[���� : �C��                                    */
                                                 /* �߂�l   :lsb=1,unit=�� :���ζ��Ď��̱����Ӱ�މ� */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�               */

u1  u1g_emfng_eocjmfneeml( void );               /* :�s�꒲��RAM ���ζ��Ď���۰Ӱ�މ� �擾�֐�    */
                                                 /* �R�[���� : �C��                                 */
                                                 /* �߂�l   :lsb=1,unit=�� :���ζ��Ď���۰Ӱ�މ� */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�            */

u1  u1g_emfng_eocjmfneemh( void );               /* :�s�꒲��RAM ���ζ��Ď���ʲӰ�މ� �擾�֐�    */
                                                 /* �R�[���� : �C��                                 */
                                                 /* �߂�l   :lsb=1,unit=�� :���ζ��Ď���ʲӰ�މ� */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�            */

u1  u1g_emfng_eocdmfaotmx( void );               /* :�s�꒲��RAM 200rev�����ζ����̍ő�l �擾�֐�    */
                                                 /* �R�[���� : �C��                                   */
                                                 /* �߂�l   :lsb=1,unit=�� :200rev�����ζ����̍ő�l */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�              */

u1  u1g_emfng_eocjrevot( void );                 /* :�s�꒲��RAM �ő厸�ζ����X�V����1000rev�� �擾�֐� */
                                                 /* �R�[���� : �C��                               */
                                                 /* �߂�l   :lsb=1,unit=�� :�ő厸�ζ����X�V����1000rev�� */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�          */

s1  s1g_emfng_eothwot( void );                   /* :�s�꒲��RAM �ő厸�ζ����X�V���̐��� �擾�֐�          */
                                                 /* �R�[���� : �C��                                         */
                                                 /* �߂�l   :lsb=160/128,unit=�� :�ő厸�ζ����X�V���̐��� */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�                    */

s1  s1g_emfng_eothaot( void );                   /* :�s�꒲��RAM �ő厸�ζ����X�V���̋z�C�� �擾�֐�          */
                                                 /* �R�[���� : �C��                                           */
                                                 /* �߂�l   :lsb=160/128,unit=�� :�ő厸�ζ����X�V���̋z�C�� */
                                                 /* ���ӎ��� : �y�s�꒲�����z����0��Ԃ�                      */

/*---------------------------------------------------------------------*/
/* ���J�ϐ�                                                            */
/*---------------------------------------------------------------------*/
extern u2 u2g_emfng_ekldmfae;        /* m=emfng,lsb=1,unit=�� :EM�������َ��Δ���l */
                                     /* �X�V�^�C�~���O : tdcm */

extern u1 u1g_emfng_ecdmfem[u1g_EJCC_NCYL];       /* m=emfng,lsb=1,unit=�� :EM�������ًC���ʎ��ζ��� */
                                                  /* �X�V�^�C�~���O : tdcm,ne30m(atdc30m�y6�C���z),65msl,drvclchg */

extern u2 u2g_emfng_ecdmfem2[u1g_EJCC_NCYL];      /* m=emfng,lsb=1,unit=�� :EM�������ًC���ʎ��ζ��� */
                                                  /* �X�V�^�C�~���O : tdcm,ne30m(atdc30m�y6�C���z),65msl,drvclchg */

extern u1 u1g_emfng_ecdmfemi[u1g_EJCC_NCYL];      /* m=emfng,lsb=1,unit=�� :����ْ��C���ʎ��ζ��� */
                                                  /* �X�V�^�C�~���O : tdcm,ne30m(atdc30m�y6�C���z),16msl,65msl,drvclchg */
    /* ecdmfem[],ecdmfem2[],ecdmfemi[]�̃C���f�b�N�X�͋C���� [0]-[5]:#1#2#3#4#5#6    �yV6�z     */
    /*                                                       [0]-[5]:#1#2#3#4#5#6    �yL6�z     */
    /*                                                       [0]-[3]:#1#2#3#4        �y4�C���z  */

extern u2 u2g_emfng_ecdmfae2;        /* m=emfng,lsb=1,unit=�� :EM�������ّS�C�����ζ��� */
                                     /* �X�V�^�C�~���O : tdcm,ne30m(atdc30m�y6�C���z),65msl,drvclchg */

extern u1 u1g_emfng_ecdmfaem;        /* m=emfng,lsb=1,unit=�� :EM�������ّS�C�����ζ��� */
                                     /* �X�V�^�C�~���O : tdcm,ne30m(atdc30m�y6�C���z),65msl,drvclchg */

extern u1 u1g_emfng_ecdmfaotbnk[2];  /* m=emfng,lsb=1,unit=�� :��ݸ�ʐG�}OT���َ��ζ��� */
                                     /* �X�V�^�C�~���O : tdcm,ne30m(atdc30m�y6�C���z),65msl,drvclchg */

extern u1 u1g_emfng_ecdmfaot;        /* m=emfng,lsb=1,unit=�� :�G�}OT���ّS�C�����ζ��� */
                                     /* �X�V�^�C�~���O : tdcm,ne30m(atdc30m�y6�C���z),65msl,drvclchg */

extern u2 u2g_emfng_ecdmfaoti;       /* m=emfng,lsb=1,unit=�� :����ْ��S�C�����ζ��� */
                                     /* �X�V�^�C�~���O : tdcm,ne30m(atdc30m�y6�C���z),16msl,65msl,drvclchg */

extern u2 u2g_emfng_ecjmfot;         /* m=emfng,lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev :�G�}OT���َ��Ό��o���¶��� */
                                     /* �X�V�^�C�~���O : tdcm,65msl,drvclchg */

extern u2 u2g_emfng_ecjmfoti;        /* m=emfng,lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev :�G�}OT���ٱ���َ����Ό��o���¶��� */
                                     /* �X�V�^�C�~���O : tdcm,16msl,65msl,drvclchg */

extern u2 u2g_emfng_ecjmfem;         /* m=emfng,lsb=1/3�y6�C���z1/2�y4�C���z,unit=rev :EM�������َ��Ό��o���¶��� */
                                     /* �X�V�^�C�~���O : tdcm,65msl,drvclchg */

extern u2 u2g_emfng_ecmfot;          /* m=emfng,lsb=1,unit=�� :�����C�����ζ��� */
                                     /* �X�V�^�C�~���O : tdcm,ne30m(atdc30m�y6�C���z),65msl,drvclchg */

extern u1 u1g_emfng_ecdmfw[u1g_EJCC_NCYL/2];      /* m=emfng,lsb=1,unit=�� :�Ό��C�����ζ��� */
                                                  /* �X�V�^�C�~���O : tdcm,ne30m(atdc30m�y6�C���z),65msl,drvclchg */

extern u1 u1g_emfng_exdmffc;         /* m=emfng,lsb=1 :FC��߼�ݔ���p�G�}OT���وُ�ʒm�׸� */
                                     /* �X�V�^�C�~���O : 65msl */
                                     /* ���ӎ��� : ON=�ُ� */
                                     /*          :�y�G�}OT���Έُ펞FC�L�z*/

extern u1 u1g_emfng_ecdtmf2;         /* m=emfng,lsb=1,unit=�� :�G�}OT���ٔ���p���H���� */
                                     /* �X�V�^�C�~���O : tdcm,65ms,drvclchg */

extern u2 u2g_emfng_ekldmfot;        /* m=emfng,lsb=1,unit=�� :�G�}OT���َ��Ή񐔔���l */
                                     /* �X�V�^�C�~���O : 65ms */

extern u2 u2g_emfng_ekldmfoth_mcr;   /* m=emfng,lsb=1,unit=�� :�G�}OT���َ��Ή񐔔���l(�v�Z�l) */
                                     /* �X�V�^�C�~���O : pwon,65ms */

extern u2 u2g_emfng_eldmfaem_mcr;    /* m=emfng,lsb=1,unit=�� :EM�������َ��Ή񐔔���l(�v�Z�l) */
                                     /* �X�V�^�C�~���O : pwon,65ms */

extern stflag8 stg_emfng_flag1;                     /* m=emfng :�O���[�o���t���O�p�\���� */
#define big_emfng_exjokmf     (stg_emfng_flag1.b0)  /* m=emfng :�n����1000rev�����׸�  */
                                                    /* �X�V�^�C�~���O : 65msl,drvclchg */
                                                    /* ���ӎ���       : ON=����        */
#define big_emfng_excdmfw     (stg_emfng_flag1.b1)  /* m=emfng :�Ό��C�����Δ��萬���׸� */
                                                    /* �X�V�^�C�~���O : 65msl            */
                                                    /* ���ӎ���       : ON=����          */
                                                    /*                :�y4�C���z��OFF�Œ�*/
#define big_emfng_excdmfemclr (stg_emfng_flag1.b2)  /* m=emfng :ecdmfem�ر�v���׸� */
                                                    /* �X�V�^�C�~���O : 65msl      */
                                                    /* ���ӎ���       : ON=����    */
#define big_emfng_exhstmf     (stg_emfng_flag1.b3)  /* m=emfng :ίĽ��ċL���׸� */
                                                    /* �X�V�^�C�~���O : 16msl   */
                                                    /* ���ӎ���       : ON=���� */
#define big_emfng_excstmf     (stg_emfng_flag1.b4)  /* m=emfng :����޽��ċL���׸� */
                                                    /* �X�V�^�C�~���O : 16msl     */
                                                    /* ���ӎ���       : ON=����   */
#define big_emfng_exdisable   (stg_emfng_flag1.b5)  /* m=emfng :���� Disable�׸� */
                                                    /* �X�V�^�C�~���O : 65msl    */
                                                    /* ���ӎ���       : ON=����  */
#define big_emfng_excomplete  (stg_emfng_flag1.b6)  /* m=emfng :���� Complete�׸� */
                                                    /* �X�V�^�C�~���O : 65msl     */
                                                    /* ���ӎ���       : ON=����   */

extern stflag8 stg_emfng_flag2;                     /* m=emfng :�O���[�o���t���O�p�\���� */
#define big_emfng_exmfddi     (stg_emfng_flag2.b0)  /* m=emfng :DI�ُ��׸�             */
                                                    /* �X�V�^�C�~���O : 65msl,drvclchg */
                                                    /* ���ӎ���       : ON=�ُ�        */
                                                    /*                :�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
#define big_emfng_exmfdied    (stg_emfng_flag2.b1)  /* m=emfng :DI���Ό��o�I���׸�     */
                                                    /* �X�V�^�C�~���O : 65msl,drvclchg */
                                                    /* ���ӎ���       : ON=����        */
                                                    /*                :�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
#define big_emfng_exmfdpfi    (stg_emfng_flag2.b2)  /* m=emfng :PFI�ُ��׸�            */
                                                    /* �X�V�^�C�~���O : 65msl,drvclchg */
                                                    /* ���ӎ���       : ON=�ُ�        */
                                                    /*                :�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
#define big_emfng_exmfpfied   (stg_emfng_flag2.b3)  /* m=emfng :PFI���Ό��o�I���׸� */
                                                    /* �X�V�^�C�~���O : 65msl,drvclchg */
                                                    /* ���ӎ���       : ON=����        */
                                                    /*                :�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/

extern stflag8 stg_emfng_flag3;                     /* m=emfng :�O���[�o���t���O�p�\���� */
#define big_emfng_exdmf       (stg_emfng_flag3.b0)  /* m=emfng :����OBD���ُ݈��׸� */
                                                    /* �X�V�^�C�~���O : 65msl,drvclchg */
                                                    /* ���ӎ���       : ON=�ُ� */
                                                    /*                :�yt-CORE�Ή��L�z*/

/*---------------------------------------------------------------------*/
/* ���J�K���萔                                                        */
/*---------------------------------------------------------------------*/
/* �K���萔 */
extern volatile const u1 u1g_emfng_CDTMFWA;     /* m=emfng,lsb=1,unit=�� :EM��������p���H��������l */
extern volatile const u1 u1g_emfng_CATN;        /* m=emfng,lsb=1 :�o���N����ʂ̗L��(��:1,�L:2) */
extern volatile const s2 s2g_emfng_MFOTL;       /* m=emfng,lsb=256/128/256,unit=% :�G�}OT���َ��Δ��艺���l */

/* �Œ�萔 */
extern volatile const u2 u2g_emfng_LJMFOT;      /* m=emfng,lsb=2/u1g_EJCC_NCYL,unit=rev :�G�}OT���وُ픻����s���ݸ� */
extern volatile const u2 u2g_emfng_LJMFEM;      /* m=emfng,lsb=2/u1g_EJCC_NCYL,unit=rev :EM�������وُ픻����s���ݸ� */

/* �o�b�N�A�b�vRAM�����l */
extern volatile const u2 u2g_emfng_ECDMFAEMTV_MI;       /* m=emfng,lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�S�C��)�����l */
extern volatile const u2 u2g_emfng_ECDMFAEMMXTL_MI;     /* m=emfng,lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�S�C��)�����l */
extern volatile const u2 u2g_emfng_ECDMFAEMMNTL_MI;     /* m=emfng,lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�S�C��)�����l */
extern volatile const u2 u2g_emfng_ECDMFEMTV_MI;        /* m=emfng,lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ���(�C����)�����l */
extern volatile const u2 u2g_emfng_ECDMFEMMXTL_MI;      /* m=emfng,lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ�������l(�C����)�����l */
extern volatile const u2 u2g_emfng_ECDMFEMMNTL_MI;      /* m=emfng,lsb=1,unit=�� :ýČ��ʏo�͗p���د�ߗݐώ��ζ��������l(�C����)�����l */
extern volatile const u2 u2g_emfng_ECDMFAAVTV_MI;       /* m=emfng,lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�S�C��)�����l */
extern volatile const u2 u2g_emfng_ECDMFAAVMXTL_MI;     /* m=emfng,lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ�������l(�S�C��)�����l */
extern volatile const u2 u2g_emfng_ECDMFAAVMNTL_MI;     /* m=emfng,lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ��������l(�S�C��)�����l */
extern volatile const u2 u2g_emfng_ECDMFAVTV_MI;        /* m=emfng,lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ���(�C����)�����l */
extern volatile const u2 u2g_emfng_ECDMFAVMXTL_MI;      /* m=emfng,lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ�������l(�C����)�����l */
extern volatile const u2 u2g_emfng_ECDMFAVMNTL_MI;      /* m=emfng,lsb=1,unit=�� :ýČ��ʏo�͗p�ߋ�10�د��EWMA���ζ��������l(�C����)�����l */
extern volatile const u1 u1g_emfng_EXRCDMFI_MI;         /* m=emfng :EWMA���ζ����v�Z�����t���O�����l */
extern volatile const u2 u2g_emfng_EOCMFNL_MI;          /* m=emfng,lsb=1,unit=�� :���Ή�(��)�̕p�x �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const u2 u2g_emfng_EOCMFNM_MI;          /* m=emfng,lsb=1,unit=�� :���Ή�(��)�̕p�x �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const u2 u2g_emfng_EOCMFNH_MI;          /* m=emfng,lsb=1,unit=�� :���Ή�(��)�̕p�x �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const u2 u2g_emfng_EOCMFMLTL_MI;        /* m=emfng,lsb=1,unit=�� :�Ό��C�����Ή�(��)�̕p�x �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const u2 u2g_emfng_EOCMFMLTH_MI;        /* m=emfng,lsb=1,unit=�� :�Ό��C�����Ή�(��)�̕p�x �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const u1 u1g_emfng_EONEMFMLT_MI;        /* m=emfng,lsb=200/8,unit=rpm :�Ό��C�����Ύ��̴ݼ�݉�]�Ȃ܂��l �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const u1 u1g_emfng_EOCDMFAE2MX_MI;      /* m=emfng,lsb=1,unit=�� :1000rev�����ζ����̍ő�l �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const u1 u1g_emfng_EOCJREVEM_MI;        /* m=emfng,lsb=1,unit=�� :�ő厸�ζ����X�V����1000rev�� �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const s1 s1g_emfng_EOTHWEM_MI;          /* m=emfng,lsb=160/128,unit=�� :�ő厸�ζ����X�V���̐��� �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const s1 s1g_emfng_EOTHAEM_MI;          /* m=emfng,lsb=160/128,unit=�� :�ő厸�ζ����X�V���̋z�C�� �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const u1 u1g_emfng_EOCDMFEM2MX_MI;      /* m=emfng,lsb=1,unit=�� :�ő厸�ζ����X�V���̋C���ʎ��ζ��� �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const u1 u1g_emfng_EOSPDEMAV_MI;        /* m=emfng,lsb=256/256,unit=km/h :���ζ��Ď��̕��ώԑ� �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const u1 u1g_emfng_EONEEMAV_MI;         /* m=emfng,lsb=12800/256,unit=rpm :���ζ��Ď��̕��ϴݼ�݉�]�� �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const u1 u1g_emfng_EOKLSMEMAV_MI;       /* m=emfng,lsb=320/256,unit=% :���ζ��Ď��̕��ϕ��� �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const u1 u1g_emfng_EOCJMFNEEMI_MI;      /* m=emfng,lsb=1,unit=�� :���ζ��Ď��̱����Ӱ�މ� �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const u1 u1g_emfng_EOCJMFNEEML_MI;      /* m=emfng,lsb=1,unit=�� :���ζ��Ď���۰Ӱ�މ� �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const u1 u1g_emfng_EOCJMFNEEMH_MI;      /* m=emfng,lsb=1,unit=�� :���ζ��Ď���ʲӰ�މ� �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const u1 u1g_emfng_EOCDMFAOTMX_MI;      /* m=emfng,lsb=1,unit=�� :200rev���ő嶳���ő�l  �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const u1 u1g_emfng_EOCJREVOT_MI;        /* m=emfng,lsb=1,unit=�� :�ő厸�ζ����X�V����1000rev�� �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const s1 s1g_emfng_EOTHWOT_MI;          /* m=emfng,lsb=160/128,unit=�� :�ő厸�ζ����X�V���̐��� �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/
extern volatile const s1 s1g_emfng_EOTHAOT_MI;          /* m=emfng,lsb=160/128,unit=�� :�ő厸�ζ����X�V���̋z�C�� �����l */
                                                        /* ���ӎ��� : �y�s�꒲���L�z*/

/* �o�b�N�A�b�vRAM-ID�Ə����l�͈ȉ��̂悤�ɐݒ肷�邱�� */
/* �P�o�C�g�o�b�N�A�b�vRAM */
/* u2g_EMFNG_EONEMFMLT_U1_ID       u1g_emfng_EONEMFMLT_MI     �y�s�꒲���L�z                           */
/* u2g_EMFNG_EXRCDMF_U1_ID         u1g_emfng_EXRCDMFI_MI                                               */
/* u2g_EMFNG_EOCDMFAE2MX_U1_ID     u1g_emfng_EOCDMFAE2MX_MI   �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOCJREVEM_U1_ID       u1g_emfng_EOCJREVEM_MI     �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOTHWEM_S1_ID         s1g_emfng_EOTHWEM_MI       �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOTHAEM_S1_ID         s1g_emfng_EOTHAEM_MI       �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOCDMFEM2MX1_U1_ID    u1g_emfng_EOCDMFEM2MX_MI   �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOCDMFEM2MX2_U1_ID    u1g_emfng_EOCDMFEM2MX_MI   �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOCDMFEM2MX3_U1_ID    u1g_emfng_EOCDMFEM2MX_MI   �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOCDMFEM2MX4_U1_ID    u1g_emfng_EOCDMFEM2MX_MI   �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOCDMFEM2MX5_U1_ID    u1g_emfng_EOCDMFEM2MX_MI   �y�s�꒲���L�zAND�y6�C���z               */
/* u2g_EMFNG_EOCDMFEM2MX6_U1_ID    u1g_emfng_EOCDMFEM2MX_MI   �y�s�꒲���L�zAND�y6�C���z               */
/* u2g_EMFNG_EOSPDEMAV_U1_ID       u1g_emfng_EOSPDEMAV_MI     �y�s�꒲���L�z                           */
/* u2g_EMFNG_EONEEMAV_U1_ID        u1g_emfng_EONEEMAV_MI      �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOKLSMEMAV_U1_ID      u1g_emfng_EOKLSMEMAV_MI    �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOCJMFNEEMI_U1_ID     u1g_emfng_EOCJMFNEEMI_MI   �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOCJMFNEEML_U1_ID     u1g_emfng_EOCJMFNEEML_MI   �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOCJMFNEEMH_U1_ID     u1g_emfng_EOCJMFNEEMH_MI   �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOCDMFAOTMX_U1_ID     u1g_emfng_EOCDMFAOTMX_MI   �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOCJREVOT_U1_ID       u1g_emfng_EOCJREVOT_MI     �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOTHWOT_S1_ID         s1g_emfng_EOTHWOT_MI       �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOTHAOT_S1_ID         s1g_emfng_EOTHAOT_MI       �y�s�꒲���L�z                           */
/* �Q�o�C�g�o�b�N�A�b�vRAM */
/* u2g_EMFNG_EOCMFNL_U2_ID         u2g_emfng_EOCMFNL_MI       �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOCMFNM_U2_ID         u2g_emfng_EOCMFNM_MI       �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOCMFNH_U2_ID         u2g_emfng_EOCMFNH_MI       �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOCMFMLTL_U2_ID       u2g_emfng_EOCMFMLTL_MI     �y�s�꒲���L�z                           */
/* u2g_EMFNG_EOCMFMLTH_U2_ID       u2g_emfng_EOCMFMLTH_MI     �y�s�꒲���L�z                           */
/* u2g_EMFNG_ECDMFAEMMXTL_U2_ID    u2g_emfng_ECDMFAEMMXTL_MI                                           */
/* u2g_EMFNG_ECDMFEMMXTL1_U2_ID    u2g_emfng_ECDMFEMMXTL_MI                                            */
/* u2g_EMFNG_ECDMFEMMXTL2_U2_ID    u2g_emfng_ECDMFEMMXTL_MI                                            */
/* u2g_EMFNG_ECDMFEMMXTL3_U2_ID    u2g_emfng_ECDMFEMMXTL_MI                                            */
/* u2g_EMFNG_ECDMFEMMXTL4_U2_ID    u2g_emfng_ECDMFEMMXTL_MI                                            */
/* u2g_EMFNG_ECDMFEMMXTL5_U2_ID    u2g_emfng_ECDMFEMMXTL_MI   �y6�C���z                                */
/* u2g_EMFNG_ECDMFEMMXTL6_U2_ID    u2g_emfng_ECDMFEMMXTL_MI   �y6�C���z                                */
/* u2g_EMFNG_ECDMFAAVMXTL_U2_ID    u2g_emfng_ECDMFAAVMXTL_MI                                           */
/* u2g_EMFNG_ECDMFAVMXTL1_U2_ID    u2g_emfng_ECDMFAVMXTL_MI                                            */
/* u2g_EMFNG_ECDMFAVMXTL2_U2_ID    u2g_emfng_ECDMFAVMXTL_MI                                            */
/* u2g_EMFNG_ECDMFAVMXTL3_U2_ID    u2g_emfng_ECDMFAVMXTL_MI                                            */
/* u2g_EMFNG_ECDMFAVMXTL4_U2_ID    u2g_emfng_ECDMFAVMXTL_MI                                            */
/* u2g_EMFNG_ECDMFAVMXTL5_U2_ID    u2g_emfng_ECDMFAVMXTL_MI   �y6�C���z                                */
/* u2g_EMFNG_ECDMFAVMXTL6_U2_ID    u2g_emfng_ECDMFAVMXTL_MI   �y6�C���z                                */
/* u2g_EMFNG_ECDMFAEMTV_U2_ID      u2g_emfng_ECDMFAEMTV_MI                                             */
/* u2g_EMFNG_ECDMFAEMMNTL_U2_ID    u2g_emfng_ECDMFAEMMNTL_MI                                           */
/* u2g_EMFNG_ECDMFAAVTV_U2_ID      u2g_emfng_ECDMFAAVTV_MI                                             */
/* u2g_EMFNG_ECDMFAAVMNTL_U2_ID    u2g_emfng_ECDMFAAVMNTL_MI                                           */
/* u2g_EMFNG_ECDMFEMTV1_U2_ID      u2g_emfng_ECDMFEMTV_MI                                              */
/* u2g_EMFNG_ECDMFEMTV2_U2_ID      u2g_emfng_ECDMFEMTV_MI                                              */
/* u2g_EMFNG_ECDMFEMTV3_U2_ID      u2g_emfng_ECDMFEMTV_MI                                              */
/* u2g_EMFNG_ECDMFEMTV4_U2_ID      u2g_emfng_ECDMFEMTV_MI                                              */
/* u2g_EMFNG_ECDMFEMTV5_U2_ID      u2g_emfng_ECDMFEMTV_MI     �y6�C���z                                */
/* u2g_EMFNG_ECDMFEMTV6_U2_ID      u2g_emfng_ECDMFEMTV_MI     �y6�C���z                                */
/* u2g_EMFNG_ECDMFEMMNTL1_U2_ID    u2g_emfng_ECDMFEMMNTL_MI                                            */
/* u2g_EMFNG_ECDMFEMMNTL2_U2_ID    u2g_emfng_ECDMFEMMNTL_MI                                            */
/* u2g_EMFNG_ECDMFEMMNTL3_U2_ID    u2g_emfng_ECDMFEMMNTL_MI                                            */
/* u2g_EMFNG_ECDMFEMMNTL4_U2_ID    u2g_emfng_ECDMFEMMNTL_MI                                            */
/* u2g_EMFNG_ECDMFEMMNTL5_U2_ID    u2g_emfng_ECDMFEMMNTL_MI   �y6�C���z                                */
/* u2g_EMFNG_ECDMFEMMNTL6_U2_ID    u2g_emfng_ECDMFEMMNTL_MI   �y6�C���z                                */
/* u2g_EMFNG_ECDMFAVTV1_U2_ID      u2g_emfng_ECDMFAVTV_MI                                              */
/* u2g_EMFNG_ECDMFAVTV2_U2_ID      u2g_emfng_ECDMFAVTV_MI                                              */
/* u2g_EMFNG_ECDMFAVTV3_U2_ID      u2g_emfng_ECDMFAVTV_MI                                              */
/* u2g_EMFNG_ECDMFAVTV4_U2_ID      u2g_emfng_ECDMFAVTV_MI                                              */
/* u2g_EMFNG_ECDMFAVTV5_U2_ID      u2g_emfng_ECDMFAVTV_MI     �y6�C���z                                */
/* u2g_EMFNG_ECDMFAVTV6_U2_ID      u2g_emfng_ECDMFAVTV_MI     �y6�C���z                                */
/* u2g_EMFNG_ECDMFAVMNTL1_U2_ID    u2g_emfng_ECDMFAVMNTL_MI                                            */
/* u2g_EMFNG_ECDMFAVMNTL2_U2_ID    u2g_emfng_ECDMFAVMNTL_MI                                            */
/* u2g_EMFNG_ECDMFAVMNTL3_U2_ID    u2g_emfng_ECDMFAVMNTL_MI                                            */
/* u2g_EMFNG_ECDMFAVMNTL4_U2_ID    u2g_emfng_ECDMFAVMNTL_MI                                            */
/* u2g_EMFNG_ECDMFAVMNTL5_U2_ID    u2g_emfng_ECDMFAVMNTL_MI   �y6�C���z                                */
/* u2g_EMFNG_ECDMFAVMNTL6_U2_ID    u2g_emfng_ECDMFAVMNTL_MI   �y6�C���z                                */

/*-------------------------------------------------------------------*/
/* ����J�K���萔�i���i���f�[�^�j                                    */
/*-------------------------------------------------------------------*/
extern volatile const s2 s2s_emfng_MFDD;           /* m=emfng,lsb=256/128/256,unit=% :EM�������َ��Η� */
extern volatile const u2 u2s_emfng_MFD1;           /* m=emfng,lsb=2/256/256 :EM�������َ��Ό��o�� */
extern volatile const s2 s2s_emfng_MFNEL3;         /* m=emfng,lsb=12800/64/256,unit=rpm :�A�C�h���̈攻��l */
extern volatile const u2 u2s_emfng_LJMFOTI;        /* m=emfng,lsb=2/u1g_EJCC_NCYL,unit=rev :�G�}OT���ٱ���َ��ُ픻����s���ݸ� */
extern volatile const u2 u2s_emfng_LJMFOTF;        /* m=emfng,lsb=2/u1g_EJCC_NCYL,unit=rev :�G�}OT���وُ픻����s���ݸ� */
extern volatile const u1 u1s_emfng_CXMFH;          /* m=emfng,lsb=1,unit=�� :EM�������وُ팟�o�񐔔���l */
extern volatile const u1 u1s_emfng_CXMFL;          /* m=emfng,lsb=1,unit=�� :EM�������وُ팟�o�񐔔���l */
extern volatile const u1 u1s_emfng_CXMF1H;         /* m=emfng,lsb=1,unit=�� :�G�}OT���وُ팟�o�񐔔���l */
extern volatile const u1 u1s_emfng_CXMF1L;         /* m=emfng,lsb=1,unit=�� :�G�}OT���وُ팟�o�񐔔���l */
extern volatile const u1 u1s_emfng_MFSTOT;         /* m=emfng,lsb=1,unit=�� :�C���ʎ��Ή񐔔���l */
extern volatile const u1 u1s_emfng_MFSTEMI;        /* m=emfng,lsb=1,unit=�� :����ْ��C���ʎ��Ή񐔔���l */
extern volatile const u1 u1s_emfng_CJPMF;          /* m=emfng,lsb=1,unit=�� :��۸۽��������l */
extern volatile const u1 u1s_emfng_CDTMF2;         /* m=emfng,lsb=1,unit=�� :�G�}OT����p���H��������l */
extern volatile const u1 u1s_emfng_KLDMFOT;        /* m=emfng,lsb=1,unit=�� :�G�}OT���َ��Ή񐔔���l(100�_��/1�C���ӂ�) */
extern volatile const u1 u1s_emfng_KLD1;           /* m=emfng,lsb=2/256 :�Ό��C�����Ό��o������ */
extern volatile const u1 u1s_emfng_KLD2;           /* m=emfng,lsb=2/256 :�Ό��C�����Ό��o����� */
                                                   /* ���ӎ��� :�y6�C���z*/
extern volatile const u1 u1s_emfng_ST1RTO;         /* m=emfng,lsb=8/256,unit=�{ :����޽��Ď�EM�������َ��Ή񐔔���l�Z�o�W�� */
extern volatile const u1 u1s_emfng_ST2RTO;         /* m=emfng,lsb=8/256,unit=�{ :ίĽ��Ď�EM�������َ��Ή񐔔���l�Z�o�W�� */
extern volatile const u1 u1s_emfng_KMFK;           /* m=emfng,lsb=2/256,unit=�{ :DTC�o�͋C������W�� */
extern volatile const u1 u1s_emfng_KCDTMFWA;       /* m=emfng,lsb=8/256,unit=�{ :EM��������p���H�������Z�W�� */
extern volatile const u1 u1s_emfng_KCDTMFAOTB;     /* m=emfng,lsb=8/256,unit=�{ :�G�}OT����p���H�������Z�W��(��ݸ��) */
extern volatile const u2 u2s_emfng_KLEVEL3;        /* m=emfng,lsb=4/256,unit=�{ :LEVEL3�v�����̎��Ή񐔔��f�W�� */
extern volatile const u1 u1s_emfng_MFDDI;          /* m=emfng,lsb=1,unit=�� :DI�ُ팟�o���Ή� */
                                                   /* ���ӎ��� :�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
extern volatile const u1 u1s_emfng_MFDPFI;         /* m=emfng,lsb=1,unit=�� :PFI�ُ팟�o���Ή� */
                                                   /* ���ӎ��� :�y�ޭ��INJ�zAND�y�����߰ĕ��˗L�z*/
extern volatile const s2 s2s_emfng_THW;            /* m=emfng,lsb=160/256,unit=�� :ίĽ��Ĕ��萅�� */
extern volatile const s2 s2s_emfng_THA;            /* m=emfng,lsb=160/256,unit=�� :ίĽ��Ĕ���z�C�� */
extern volatile const s2 s2s_emfng_THWCSTL;        /* m=emfng,lsb=160/256,unit=�� :����޽��Ĕ��萅�� */
extern volatile const s2 s2s_emfng_THWCSTH;        /* m=emfng,lsb=160/256,unit=�� :����޽��Ĕ��萅�� */
extern volatile const s2 s2s_emfng_THACST;         /* m=emfng,lsb=160/256,unit=�� :����޽��Ĕ���z�C�� */
extern volatile const u1 u1s_emfng_CJEMREV;        /* m=emfng,lsb=1,unit=�� :EM�������َ��Ή񐔐��グ1000rev�� */
extern volatile const s2 s2s_emfng_KCDMFWL;        /* m=emfng,lsb=2/64/256 :ýČ��ʏo�͗p �Ό��C�����ζ������Z����l */
                                                   /* ���ӎ��� :�y6�C���z*/
extern volatile const u1 u1s_emfng_MFLOW;          /* m=emfng,lsb=2/256 :���Ή񐔏�����W�� */
                                                   /* ���ӎ��� :�y�s�꒲���L�z*/
extern volatile const u1 u1s_emfng_MFMID;          /* m=emfng,lsb=2/256 :���Ή񐔒�����W�� */
                                                   /* ���ӎ��� :�y�s�꒲���L�z*/
extern volatile const u1 u1s_emfng_MFHI;           /* m=emfng,lsb=2/256 :���Ή񐔑唻��W�� */
                                                   /* ���ӎ��� :�y�s�꒲���L�z*/

/*---------------------------------------------------------------------*/
/* ���J�}�b�v                                                          */
/*---------------------------------------------------------------------*/
/* �e�[�u�� */
extern volatile const u1 u1g_emfng_mfwcyl_tbl[u1g_EJCC_NCYL/2]; /* m=emfng:cylw�ɑΉ�����mfcyl ���� cylw�ϊ��e�[�u�� */
/* �}�b�v */
extern volatile const s2 s2g_emfng_emfrtot_map[];  /* m=emfng,lsb=256/128/256,unit=% :�ώZ���Δ���l�␳�W���}�b�v */
extern volatile const s2 s2g_emfng_emfrtotgpf_map[];    /* m=emfng,lsb=256/128/256,unit=% :�ώZ���Δ���l�␳�W���}�b�v */
                                                        /* ���ӎ���:�yGPF�L�z*/

/*-------------------------------------------------------------------*/
/* ����J�}�b�v�i���i���f�[�^�j                                      */
/*-------------------------------------------------------------------*/
extern volatile const u1 u1s_emfng_mfcylbnk_tbl[u1g_EJCC_NCYL]; /* m=emfng:mfcyl �� �o���N �ϊ��e�[�u�� */

/*---------------------------------------------------------------------*/
/* �I�[�g�J�E���^                                                      */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* �}�N����`                                                          */
/*---------------------------------------------------------------------*/
/* $$$�}�N���萔_�W��_v4.11 */
/* $$$�}�N���萔_�W��_v4.11 */

#endif /* EMFNG_H */
/**** End of File ****************************************************/
