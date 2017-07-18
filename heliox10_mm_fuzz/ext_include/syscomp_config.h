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
 *   syscomp_config.h
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *   The file contains declarations of system component module configuration
 *   variables, and routines.
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
 * removed!
 * removed!
 * removed!
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

#ifndef _SYSCOMP_CONFIG_H
#define _SYSCOMP_CONFIG_H

/*************************************************************************
 * Include Header Files
 *************************************************************************/

#include "kal_general_types.h"
#include "kal_public_defs.h"

#include "stack_config.h"
#include "stack_types.h"

#include "hisr_config.h"

#define TASK_NO_CREATE_PATTERN 0xF0F0F0F0
// For FPU enable, we need extra 144 byte stack size for storing FPU context
#ifdef __ARM_FPUV2__
#define VFP_CONTEXT_SAVE_SPACE 144
#else
#define VFP_CONTEXT_SAVE_SPACE 0
#endif
/*On demand page will run some functions on task's stack*/
#define TASK_STACK_COMMON_PLUS (VFP_CONTEXT_SAVE_SPACE + DEMAND_PAGING_STACK_OVERHEAD)
#define HISR_STACK_COMMON_PLUS (VFP_CONTEXT_SAVE_SPACE) 
/*************************************************************************
* STRUCT
*  syscomp_info_struct
*
* DESCRIPTION
*  The structure defines component task configuration information
*
* FIELDS
*  comp_entry_func   -  component task's entry function
*  comp_cfg_func  -  component task's configurantion handler
*  comp_init_func -  component task's initialization handler
*  comp_reset_func   -  component task's reset handler
*  comp_end_func  -  component task's termination handler
*  comp_modmain_func -  component task's module main handler
*
* GLOBALS AFFECTED
*
*************************************************************************/
typedef struct {
   kal_task_func_ptr    comp_entry_func;
   task_init_func_ptr   comp_init_func;
   task_reset_func_ptr  comp_reset_func;
} comptask_handler_struct;

typedef kal_bool (*kal_create_func_ptr)(comptask_handler_struct **);

/*************************************************************************
* STRUCT
*  syscomp_info_struct
*
* DESCRIPTION
*  The structure defines component task configuration information
*
* FIELDS
*  comp_name_ptr  -  pointer to component task name
*  comp_qname_ptr -  pointer to component task's external queue name
*  comp_priority  -  component task's priority
*  comp_stack_size   -  component task's stack size
*  comp_ext_qsize -  component task's external queue size
*  comp_int_qsize -  component task's internal queue size
*  comp_create_func- component entity's create function
*
* GLOBALS AFFECTED
*
*************************************************************************/
typedef struct {
   kal_char             *comp_name_ptr;
   kal_char             *comp_qname_ptr;
   kal_uint32           comp_priority;
   kal_uint32           comp_stack_size;
   kal_create_func_ptr  comp_create_func;
   kal_bool             comp_internal_ram_stack;
   kal_uint8            comp_ext_qsize;
   kal_uint8            comp_int_qsize;
   kal_uint8            comp_boot_mode;
} comptask_info_struct;


typedef struct
{
    kal_hisr            index;
    kal_uint8           priority;
    kal_uint8           options;
    kal_uint32          stack_size;
    kal_hisr_func_ptr   entry_func;
    kal_char            *hisr_name;
}hisr_parameter_s;

typedef struct hisr_intid_map_t
{
	kal_hisr hisr_id;
	interrupt_type int_id;
}hisr_intid_map;
#endif /* _SYSCOMP_CONFIG_H */


