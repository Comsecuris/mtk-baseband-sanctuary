/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE. 
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

/*****************************************************************************
 *
 * Filename:
 * ---------
 *   hisr_config.h
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *   This file generate the enum value and extern function name
 *
 * Author:
 * -------
 * -------
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 * removed!
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#include "module_hisrid_range.h"

#if !defined(__HISR_CONFIG_H__)
#define __HISR_CONFIG_H__

#undef MODULE_ID_FOR_PRINT_TRACE
#if defined(__UNIFIED_ISR_LEVEL__)
typedef enum{
    KAL_INTID_NIL = 0,
    KAL_INTID_1, KAL_INTID_2, KAL_INTID_3, KAL_INTID_4, KAL_INTID_5,
    KAL_INTID_6, KAL_INTID_7, KAL_INTID_8, KAL_INTID_9, KAL_INTID_10,
    KAL_INTID_11, KAL_INTID_12, KAL_INTID_13, KAL_INTID_14, KAL_INTID_15,
    KAL_INTID_16, KAL_INTID_17, KAL_INTID_18, KAL_INTID_19, KAL_INTID_20,
    KAL_INTID_21, KAL_INTID_22, KAL_INTID_23, KAL_INTID_24, KAL_INTID_25,
    KAL_INTID_26, KAL_INTID_27, KAL_INTID_28, KAL_INTID_29, KAL_INTID_30,
    KAL_INTID_31, KAL_INTID_32, KAL_INTID_33, KAL_INTID_34, KAL_INTID_35,
    KAL_INTID_36, KAL_INTID_37, KAL_INTID_38, KAL_INTID_39, KAL_INTID_40,
    KAL_INTID_41, KAL_INTID_42, KAL_INTID_43, KAL_INTID_44, KAL_INTID_45,
    KAL_INTID_46, KAL_INTID_47, KAL_INTID_48, KAL_INTID_49, KAL_INTID_50,
    KAL_INTID_51, KAL_INTID_52, KAL_INTID_53, KAL_INTID_54, KAL_INTID_55,
    KAL_INTID_56, KAL_INTID_57, KAL_INTID_58, KAL_INTID_59, KAL_INTID_60,
    KAL_INTID_61, KAL_INTID_62, KAL_INTID_63, KAL_INTID_64, KAL_INTID_65,
    KAL_INTID_66, KAL_INTID_67, KAL_INTID_68, KAL_INTID_69, KAL_INTID_70,
    KAL_INTID_71, KAL_INTID_72, KAL_INTID_73, KAL_INTID_74, KAL_INTID_75,
    KAL_INTID_76, KAL_INTID_77, KAL_INTID_78, KAL_INTID_79, KAL_INTID_80,
    KAL_INTID_81, KAL_INTID_82, KAL_INTID_83, KAL_INTID_84, KAL_INTID_85,
    KAL_INTID_86, KAL_INTID_87, KAL_INTID_88, KAL_INTID_89, KAL_INTID_90,
    KAL_INTID_91, KAL_INTID_92, KAL_INTID_93, KAL_INTID_94, KAL_INTID_95,
    KAL_INTID_96, KAL_INTID_97, KAL_INTID_98, KAL_INTID_99, KAL_INTID_100,
    KAL_INTID_101, KAL_INTID_102, KAL_INTID_103, KAL_INTID_104, KAL_INTID_105,
    KAL_INTID_106, KAL_INTID_107, KAL_INTID_108, KAL_INTID_109, KAL_INTID_110,
    KAL_INTID_111, KAL_INTID_112, KAL_INTID_113, KAL_INTID_114, KAL_INTID_115,
    KAL_INTID_116, KAL_INTID_117, KAL_INTID_118, KAL_INTID_119, KAL_INTID_120,
    KAL_INTID_121, KAL_INTID_122, KAL_INTID_123, KAL_INTID_124, KAL_INTID_125,
    KAL_INTID_126, KAL_INTID_127, KAL_INTID_128,
    KAL_INTID_MAX,
}KAL_INTID_TYPE;
/* kal_intid_max_num_check is used to check KAL_INTID_TYPE */
typedef unsigned int kal_intid_max_num_check1[(KAL_INTID_MAX-1) - KAL_MAX_NUM_LISR2HISRS];
typedef unsigned int kal_intid_max_num_check2[KAL_MAX_NUM_LISR2HISRS - (KAL_INTID_MAX-1)];
#define X_HISR_CONST_WITH_INTID(a,b,c,d,e,f,g,i) b=a, 
#define X_HISR_INTID(a,j)
#endif
#define X_HISR_CONST(a,b,c,d,e,f,g) b=a,
#define X_HISR_MOD(a,h) 
#define MODULE_ID_FOR_PRINT_TRACE(mod)

typedef enum {
	  HISR_NIL = 0,
    #include "hisr_config_internal.h"
    HISR_END,
    RPS_TOTAL_STACK_HISRS = HISR_END
}kal_hisr;
#undef X_HISR_CONST

extern kal_hisrid kal_init_hisr(kal_hisr e_hirs);

#if defined(__UNIFIED_ISR_LEVEL__)
#undef X_HISR_CONST_WITH_INTID
#define X_HISR_CONST_WITH_INTID(a,b,c,d,e,f,g,i) extern void f(void); 
#endif
#define X_HISR_CONST(a,b,c,d,e,f,g) extern void f(void);
    #include "hisr_config_internal.h"
#undef MODULE_ID_FOR_PRINT_TRACE
#undef X_HISR_MOD
#undef X_HISR_CONST
#if defined(__UNIFIED_ISR_LEVEL__)
#undef X_HISR_CONST_WITH_INTID
#undef X_HISR_INTID
#endif

#endif /* __HISR_CONFIG_H__ */

