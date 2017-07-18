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
 *   sysconf_statistics.h
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *   This file provides the stack statistics definition
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
 * removed!
 * removed!
 * removed!
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

#ifndef _SYSCONF_STATISTICS_H
#define _SYSCONF_STATISTICS_H

#define DSPSYS_STAT_DATA_LEN            512
/*RHR*/
#include "kal_general_types.h"
#include "stack_config.h"
#include "ctrl_buff_pool.h"

#if defined(DEBUG_KAL) && (defined(__UMTS_RAT__) || defined(__LTE_RAT__))
/* sizeof(stack_statistics_struct) is over 4K, so using compile option to control it */
/* in case of 2G, no 8k control buffer no further statistic info */
#define FURTHER_STATISTIC
#endif
/*************************************************************************
 * System Statistics 
 *************************************************************************/
enum {
	STACK_STATS_NONE,
	STACK_STATS_UPDATE,
	STACK_STATS_END
};

enum
{
    STACK_STATS_HISR_NAME = 0,
    STACK_STATS_HISR_MAX_NAME = 8
};

typedef struct clib_heap_statistics_t {
    kal_uint32 curr_alloc_mem;
    kal_uint32 max_alloc_mem;
    kal_uint32 alloc_count;
    kal_uint32 alloc_fail_count;
    kal_uint32 config_size;
} clib_heap_statistics_struct;


#define KAL_TIMER_COUNT_STAT  10

struct kal_mod_res_cnt
{
    module_type owner_module;
    kal_uint16 count;
}; 

#ifdef DEBUG_KAL
/*DEBUG_TIMER2 is off usually to save memory*/
typedef struct all_timers_stat_s
{
#if defined(DEBUG_TIMER2)
    struct kal_mod_res_cnt kal_all_timers_stat[KAL_TIMER_COUNT_STAT];
#endif
    kal_uint32           stack_timer_no;
    kal_uint32           kal_timer_no;
    kal_uint32           es_timer_no;
}all_timer_stat_s;
#endif

typedef struct runtime_sysmem_size
{
	kal_uint16 evshed;	
	kal_uint16 mutex;	
	kal_uint16 sem;	
	kal_uint16 event_group;	
	kal_uint16 stack_timer;	
	kal_uint16 kal_timer;	
	kal_uint16 enh_mutex;	
} runtime_sysmem_size_s;

typedef struct runtime_max_amount
{
	kal_uint32 task_name;
	kal_uint8 evshed;	
	kal_uint8 mutex;	
	kal_uint8 sem;	
	kal_uint8 event_group;	
	kal_uint8 stack_timer;	
	kal_uint8 kal_timer;	
	kal_uint8 enh_mutex;	
} runtime_max_amount_s;

typedef struct stack_statistics_t {
	kal_uint16 stack_stats_status;													/* Statistics record status */
	kal_uint32 max_sys_mem_used;														/* Maximum system dynamic memory used */
	kal_uint32 max_sysdebug_mem_used;												/* Maximum system debug dynamic memory used */	
#ifdef DEBUG_KAL
    kal_uint32 max_mutex_number;
    kal_uint32 max_event_number;
    kal_uint32 max_eventgroup_number;
#endif	
    clib_heap_statistics_struct clib_heap_stats;
	kal_uint16 max_task_stack_used[KAL_MAX_NUM_TASKS];		/*RPS_TOTAL_STACK_TASKS*/			/* Maximum tasks' stack used */
	kal_uint16 max_hisr_stack_used[KAL_MAX_NUM_HISRS];							/* Maximum hisrs' stack used */
#ifdef DEBUG_ITC
	kal_uint8 max_task_extq_enqued[KAL_MAX_NUM_TASKS];		/*RPS_TOTAL_STACK_TASKS*/				/* Maximum external messages enqued */
    kal_uint8 max_task_intq_enqued[KAL_MAX_NUM_TASKS];		/*RPS_TOTAL_STACK_TASKS*/				/* Maximum internal messages enqued */
#endif /* DEBUG_ITC */
#if defined(DEBUG_BUF1) || defined(DEBUG_BUF2)
	kal_uint16 max_ctrl_buff_num_allocated[RPS_CREATED_CTRL_BUFF_POOLS];	/* Maximum number control buffers allocated */
#endif /* DEBUG_BUF1 || DEBUG_BUF2 */
#if defined(__TST_MODULE__) && defined(__DSP_FCORE4__)
   /*tst need to know me and pass me to dsp*/
    kal_uint8 dspsys_stat[DSPSYS_STAT_DATA_LEN];
#endif
#if defined(DEBUG_BUF_MOD_USAGE) && !defined(__MTK_TARGET__)	
    kal_uint16 mod_ctrlBuf_peak_count[RPS_CREATED_CTRL_BUFF_POOLS][MOD_ID_CODE_END];
#endif /* end of DEBUG_BUF_MOD_USAGE && !__MTK_TARGET__ */

#ifdef DEBUG_KAL
    all_timer_stat_s   timers_stat;
#endif

#if defined(FURTHER_STATISTIC)
    runtime_sysmem_size_s runtime_sysmem_size;	
    runtime_max_amount_s system_runtime_max_amount;
    runtime_max_amount_s task_runtime_max_amount[KAL_MAX_NUM_TASKS];
#endif
} stack_statistics_struct;


/*************************************************************************
 * Define function prototype.
 *************************************************************************/

extern kal_int32 stack_get_stats_info(kal_uint32 stats, void *buff, kal_uint32 buff_size);
extern void clib_get_heap_statistics(clib_heap_statistics_struct *pstat);

#endif /* _SYSCONF_STATISTICS_H */

