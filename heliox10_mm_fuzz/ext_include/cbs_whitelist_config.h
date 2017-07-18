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
 *   cbs_whitelist_config.h
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *   This file contains the function prototypes of the buffer allocation module.
 *
 * Author:
 * -------
 *   
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * removed!
 * removed!
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

/*********************************************************************
   (C) _____ (year of first publication) Sasken communication
   Technologies Limited, All rights reserved.
*   This file provides a template for .c files. This space
*   should be used to describe the file contents
*   Component-specific prefix : xxxx
*********************************************************************/

#ifndef _CBS_WHITELIST_CONFIG_H
#define _CBS_WHITELIST_CONFIG_H

#if defined(DEBUG_BUF3) && defined(__MTK_TARGET__)
#include "kal_general_types.h"
#include "kal_public_defs.h"

/*************************************************************************
 * Type Definitions
 *************************************************************************/
#define MAX_TOLERANCE (0xFFFF)
#define BUFFER_LEAKAGE_DISPLAY_NUMBER (16)

typedef struct buff_whitelist_trace_struct {
   struct kal_int_task_struct *owner_task;
   kal_char                   *task_name;
   const kal_char             *file_name;
   void                       *user_ptr;
   kal_uint32                 line;
   kal_uint32                 size;
   kal_uint32                 ticks_stamp;
   kal_uint16                 alloc_id;
} buff_whitelist_trace_s;
 
/* file /owner task/module */
typedef struct buff_leakage_whitelist {
    const kal_char *file;            // file of buffer alloc
    const kal_char *owner_task_name; // task of buffer alloc
    module_type module;              // module of buffer alloc
    kal_uint16 tolerance;            // amount of ignored exceptions
} buff_leakage_whitelist_struct;
/*************************************************************************
 * Exported Function Prototypes
 *************************************************************************/
extern buff_whitelist_trace_s * kal_debug_get_whitelis_trace(kal_uint32* trace_no);
extern buff_whitelist_trace_s * kal_debug_get_leakage(kal_uint32* trace_no);

#endif
#endif /* _CBS_WHITELIST_CONFIG_H */

/*************************************************************************
 * Global Data
 *************************************************************************/
#if defined(DEBUG_BUF3) && defined(__MTK_TARGET__)
#if defined(CBS_WHITELIST_DATA)
BUFFER_WHITELIST_DECLARE("mrs_gas_capability.c", "MRS", MOD_MRS, 1)
BUFFER_WHITELIST_DECLARE("scsi.c", "URR", MOD_MEME, MAX_TOLERANCE)
#endif
#endif



