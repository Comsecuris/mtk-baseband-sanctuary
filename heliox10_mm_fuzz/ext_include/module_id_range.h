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
 *   stack_config.h
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *   This file provides the task index and module index configuration.
 *
 * Author:
 * -------
 * -------
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
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
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

#ifndef MODULE_ID_RANGE_H
#define MODULE_ID_RANGE_H

typedef enum {
	
	MOD_ID_SRV_CODE_BEGIN, MOD_ID_SRV_CODE_TAIL = MOD_ID_SRV_CODE_BEGIN + 50,
	
	MOD_ID_MODEM_2G3G_CODE_BEGIN, MOD_ID_MODEM_2G3G_CODE_TAIL = MOD_ID_MODEM_2G3G_CODE_BEGIN + 340,

    MOD_ID_MODEM_4G_CODE_BEGIN, MOD_ID_MODEM_4G_CODE_TAIL = MOD_ID_MODEM_4G_CODE_BEGIN + 230,	
	
	MOD_ID_MIDDLEWARE_CODE_BEGIN, MOD_ID_MIDDLEWARE_CODE_TAIL = MOD_ID_MIDDLEWARE_CODE_BEGIN + 90,
	
	MOD_ID_DRV_CODE_BEGIN, MOD_ID_DRV_CODE_TAIL = MOD_ID_DRV_CODE_BEGIN + 150,  //tmp for add null task & print 40 + 50 

	MOD_ID_HISR_CODE_BEGIN, MOD_ID_HISR_CODE_TAIL = MOD_ID_HISR_CODE_BEGIN + 148 +1,  //follow MOD_APP_BEGIN = (MOD_HISR_BEGIN + KAL_MAX_NUM_HISRS + 1)
		
  	MOD_ID_CODE_END,  
  	
	MOD_ID_END = MOD_ID_CODE_END,
	
/* DHL needs control buffer with size in ((END_OF_MOD_ID_TAIL+1)*2),
   so END_OF_MOD_ID_BEGIN can be 1022 if max control buffer size is 2k */
/* TST needs control buffer with size in 
   (((END_OF_MOD_ID+7)/8) + (LAST_SAP_CODE+1) + (2*(END_OF_MOD_ID+1)) + NVRAM_DUAL_RECORD*TST_L1TRC_FILTER_NUM*5),
   so END_OF_MOD_ID_BEGIN can be 383 if max control buffer size is 2k */
	END_OF_MOD_ID_BEGIN = 1023, END_OF_MOD_ID_TAIL,
	
}MODULE_ID_TYPE;

typedef unsigned int module_id_boundary_check1[END_OF_MOD_ID_BEGIN - MOD_ID_CODE_END];

/**************************************************************
**********  Should not change the following MACROS defines  *************
**********  Should not define MODULE ID with "MOD_TAG_"     *************
***************************************************************/
#ifdef GEN_FOR_PC
    #define MODULE_MOD_BEGIN(BEGIN_POS)  typedef enum __cgen_module_type_id_##BEGIN_POS{MODULE_TAG_##BEGIN_POS = BEGIN_POS,
    #define MODULE_MOD_END(END_POS) MODULE_ID_CGEN_PARSE_LAST_ID=END_POS }_cgen_module_type_id_##END_POS;
#else
    #define MODULE_MOD_BEGIN(BEGIN_POS)   enum { MODULE_TAG_##BEGIN_POS = BEGIN_POS,
    #define MODULE_MOD_END(END_POS)     };    
#endif /* GEN_FOR_PC */


MODULE_MOD_BEGIN(END_OF_MOD_ID_BEGIN)
	END_OF_MOD_ID,
MODULE_MOD_END(END_OF_MOD_ID_TAIL)


#endif /* MODULE_ID_RANGE_H */
