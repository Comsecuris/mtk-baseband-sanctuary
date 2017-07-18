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
 *   kal_public_defs.h
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *   This file provides public and common types definations.
 *   Note this file will inhirit RTOS header file
 *
 *   Data type definitions in this file are visible for KAL Public Users.
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
 ****************************************************************************/

#ifndef _KAL_PUBLIC_DEFS_H
#define _KAL_PUBLIC_DEFS_H

#include "kal_general_types.h"
#ifndef _DEBUG_MSG_SAP_
#include "stack_config.h"               /* module_type & task_indx_type */
#endif
#include "stack_msgs.h"                 /* sap_type & msg_type */
   
/*******************************************************************************
 * Type Definitions
 *******************************************************************************/

/* opaque type for task identity */
typedef struct
{
    kal_uint8 unused;
} kal_taskid_s;
typedef kal_taskid_s* kal_taskid;

/* opaque type for hisr identity */
typedef struct
{
    kal_uint8 unused;
} kal_hisrid_s;
typedef kal_hisrid_s* kal_hisrid;

/* opaque type for semaphore identity */
typedef struct
{
    kal_uint8 unused;
} kal_semid_s;
typedef kal_semid_s* kal_semid;

/* opaque type for message queue identity */
typedef struct 
{
    kal_uint8 unused;
} kal_msgqid_s;
typedef kal_msgqid_s* kal_msgqid;

/* contain message queue information */
typedef struct
{
    /* current number of pending messages in message queue */
    kal_uint32 pending_msgs;
    /* maximum number of pending messages in message queue */
    kal_uint32 max_msgs;
} kal_msgq_info;

/* opaque type for mutex identity */
typedef struct
{
    kal_uint8 unused;
} kal_mutexid_s;

typedef kal_mutexid_s* kal_mutexid;

/* opaque type for event group identity */
typedef struct 
{
    kal_uint8 unused;
} kal_eventgrpid_s;
typedef kal_eventgrpid_s* kal_eventgrpid;

/* opaque type for partition memory pool identity */
typedef struct
{
    kal_uint8 unused;
} kal_poolid_s;

typedef kal_poolid_s* kal_poolid;

/* opaque type for Application Dynamic Memory identity */
typedef struct
{
    kal_uint8 unused;
} KAL_ADM_ID_s;
typedef KAL_ADM_ID_s* KAL_ADM_ID;

/* opaque type for Application Fix Memory identity */
typedef struct
{
    kal_uint8 unused;
} KAL_AFM_ID_s;
typedef KAL_AFM_ID_s* KAL_AFM_ID;

/* opaque type for First Level Memory Manager identity */
typedef struct
{
   kal_uint8 unused;
} KAL_FLMM_ID_s;
typedef KAL_FLMM_ID_s* KAL_FLMM_ID;

/* opaque type for Second Level Memory Manager identity */
typedef struct
{
   kal_uint8 unused;
} KAL_SLMM_ID_s;
typedef KAL_SLMM_ID_s* KAL_SLMM_ID;

/* opaque type for enhance mutex identity */
typedef struct 
{
    kal_uint8 unused;
} kal_enhmutexid_s;
typedef kal_enhmutexid_s* kal_enhmutexid;

/* opaque type for kal timer identity */
typedef struct
{
    kal_uint8 unused;
} kal_timerid_s;

typedef kal_timerid_s* kal_timerid;

/* opaque type for event scheduler identity */
typedef struct event_scheduler
{
    kal_uint8 unused;
} event_scheduler;

/* opaque type for event identity */
typedef void* eventid;

/* task entry function parameter */
typedef struct task_entry_struct
{
    /* paremeter of task main entry*/
    kal_uint32 parameter;
} task_entry_struct;

/* general function pointer prototype */
typedef void (*kal_func_ptr)(void);
/* task entry function prototype */
typedef void (*kal_task_func_ptr)(task_entry_struct *task_entry_ptr);
/* hisr entry function prototype */
typedef void (*kal_hisr_func_ptr)(void);
/* timer (kal timer, stack timer, event scheduler) callback function prototype */
typedef void (*kal_timer_func_ptr)(void *param_ptr);

/*************************************************************************
 * Type Definitions for ILM communication
 *************************************************************************/
 
/* transfer direction flags for local_para & peer_buff, only TD_RESET is meaningful now */
typedef enum {
   TD_UL = 0x01 << 0,   /* Uplink Direction, obsolete */
   TD_DL = 0x01 << 1,   /* Downlink Direction, obsolete */
   TD_CTRL = 0x01 << 2, /* Control Plane. Both directions, obsolete */
   TD_RESET = 0x01 << 3 /* Reset buffer content to 0 */
} transfer_direction;

#define LOCAL_PARA_HDR \
   kal_uint8	ref_count; \
   kal_uint8    lp_reserved; \
   kal_uint16	msg_len;
/*  common local_para header */
typedef struct local_para_struct {
    /* ref_count: reference count; 
     * lp_reserved : reserved for future; 
     * msg_len  : total length including this header.
     */
    LOCAL_PARA_HDR
#ifdef __BUILD_DOM__
    ;
#endif
} local_para_struct;

#define PEER_BUFF_HDR \
   kal_uint16	pdu_len; \
   kal_uint8	ref_count; \
   kal_uint8   	pb_resvered; \
   kal_uint16	free_header_space; \
   kal_uint16	free_tail_space;
/* peer buffer header, user should treat it as opaque type */
typedef struct peer_buff_struct {
   PEER_BUFF_HDR 
#ifdef __BUILD_DOM__
    ;
#endif
} peer_buff_struct;

typedef kal_uint16 interrupt_type;
typedef kal_uint16 module_type;
typedef kal_uint16 sap_type;
typedef kal_uint16 msg_type;

/* The Interlayer Message structure, which is exchaged between modules. */
typedef struct ilm_struct {
   module_type       src_mod_id;      /* Source module ID of the message. */
   module_type       dest_mod_id;     /* Destination module ID of the message. */
   sap_type          sap_id;          /* Service Access Pointer Identifier. */
   msg_type          msg_id;          /* Message identifier */
   local_para_struct *local_para_ptr; /* local_para pointer */
   peer_buff_struct  *peer_buff_ptr;  /* peer_buff pointer */
} ilm_struct;

/* maximum payload size in an inline-ILM message */
#define MSG_INLINE_ILM_MAX_PAYLOAD (sizeof(local_para_struct *) + sizeof(peer_buff_struct  *))

/*************************************************************************
 * Type Definitions for stack timer
 *************************************************************************/
 
typedef enum {
	STACK_TIMER_INITIALIZED,
	STACK_TIMER_NOT_RUNNING = STACK_TIMER_INITIALIZED,
	STACK_TIMER_RUNNING,
	STACK_TIMER_NOT_TIMED_OUT = STACK_TIMER_RUNNING,		/* Backward compatiable */
	STACK_TIMER_EXPIRED,
	STACK_TIMER_TIMED_OUT = STACK_TIMER_EXPIRED,				/* Backward compatiable */
	STACK_TIMER_STOPPED
} stack_timer_status_type;

typedef enum {
	STACK_TIMER_USER_VIEW_STOPPED,
	STACK_TIMER_USER_VIEW_RUNNING
}stack_timer_user_view_status_type;

/* opaque type for stack timer, don't reference its member directly */
typedef struct stack_timer_struct_t {
	stack_timer_user_view_status_type timer_user_view_status;
	stack_timer_status_type timer_status;
	kal_uint8               invalid_time_out_count;
    kal_timerid             kal_timer_id;
	kal_uint16              timer_indx;
	module_type             dest_mod_id;
#if defined(KAL_ON_OSCAR)
   kal_uint8               ut_not_send_msg;
#endif
} stack_timer_struct;

/* DOM-NOT_FOR_SDK-BEGIN */
/*******************************************************************************
 * Constant definition
 *******************************************************************************/
#if defined(KAL_ON_NUCLEUS)

#define KAL_CONSUME           1 //NU_OR_CONSUME
#define KAL_AND               2 //NU_AND
#define KAL_AND_CONSUME       3 //NU_AND_CONSUME
#define KAL_OR                0 //NU_OR
#define KAL_OR_CONSUME        1 //NU_OR_CONSUME
#define KAL_NO_SUSPEND        0 //NU_NO_SUSPEND
#define KAL_SUSPEND           0xFFFFFFFF //NU_SUSPEND

#elif defined (KAL_ON_OSCAR)    /* KAL_ON_NUCLEUS */

#define KAL_CONSUME           0x4 //OSC_ACTION_CLS
#define KAL_AND               0x1 //OSC_ACTION_FULL_SET
#define KAL_AND_CONSUME       (KAL_AND | KAL_CONSUME) //OSC_ACTION_FULL_SET | OSC_ACTION_CLS
#define KAL_OR                0x2 //OSC_ACTION_PART_SET
#define KAL_OR_CONSUME        (KAL_OR | KAL_CONSUME) //OSC_ACTION_PART_SET | OSC_ACTION_CLS
#define KAL_NO_SUSPEND        0   //OSC_TIMEOUT_NONE
#define KAL_SUSPEND           0xFFFFFFFF //OSC_TIMEOUT_FOREVER

#elif defined(KAL_ON_THREADX)   /* KAL_ON_NUCLEUS */

#define KAL_CONSUME           1 //TX_OR_CLEAR
#define KAL_AND               2 //TX_AND
#define KAL_AND_CONSUME       3 //TX_AND_CLEAR
#define KAL_OR                0 //TX_OR
#define KAL_OR_CONSUME        1 //TX_OR_CLEAR
#define KAL_NO_SUSPEND        0 //TX_NO_WAIT
#define KAL_SUSPEND           0xFFFFFFFF //TX_WAIT_FOREVER

#elif defined(KAL_ON_OSABS)

typedef enum 
{
   KAL_CONSUME,
   KAL_AND,
   KAL_AND_CONSUME,
   KAL_OR,
   KAL_OR_CONSUME,
   KAL_NO_SUSPEND,
   KAL_SUSPEND
};

#endif  /* KAL_ON_NUCLEUS */

#define KAL_NILTASK_ID        (kal_taskid)NULL
#define KAL_NILHISR_ID        (kal_hisrid)NULL
#define KAL_NILTIMER_ID       (kal_timerid)NULL
#define KAL_NILPOOL_ID        (kal_poolid)NULL
#define KAL_NILMUTEX_ID       (kal_mutexid)NULL
#define KAL_NILEVENTGRP_ID    (kal_eventgrpid)NULL
#define KAL_NILSEM_ID         (kal_semid)NULL
#define KAL_NILQ_ID           (kal_msgqid)NULL
#define KAL_NILSEC            (kal_uint32)0xffffffff
#define KAL_NILMSEC           (kal_uint16)0xffff
#define KAL_NILTICK           (kal_uint32)0xffffffff
/* DOM-NOT_FOR_SDK-END */

/*******************************************************************************
 * Constant definition Referenced By Public APIs
 *******************************************************************************/

/* boot mode enumeration */
typedef enum
{
    /* factory mode, system boot up to communicate with factory tools */
    FACTORY_BOOT = 0,
    /* normal mode */
    NORMAL_BOOT = 1,
    /* USB mode, system boot up when USB charger connect */
    USBMS_BOOT =  2,
    /* Firmware Update Engine mode, system run inside FUE */
    FUE_BOOT =  3,
    /* number of known boot mode */
    NUM_OF_BOOT_MODE,
    /* unknown mode */
    UNKNOWN_BOOT_MODE = 0xff
} boot_mode_type;

/* adm feature option used in kal_adm_create2 */
/* DOM-NOT_FOR_SDK-BEGIN */
#define KAL_ADM_OLD_ISLOGGING_FLAG  0x1
#define KAL_ADM_PROFILE_FLAG        0x2
/* DOM-NOT_FOR_SDK-END */
#define KAL_ADM_GUARDIAN_FLAG       0x4     /* put a guard word before and after each user buffer to detect memory corruption */
#define KAL_ADM_EXTHEADER_FLAG      0x8     /* has an extensible header immediate before each user buffer */
#define KAL_ADM_CLEANDELETE_FLAG    0x10    /* on kal_adm_delete(), if any user buffer is not free yet, system enter fatal error handling */
#define KAL_ADM_REALLOCFAIL_FATAL_FLAG 0x20 /* if kal_adm_realloc() failed, system enter fatal error handling */
#define KAL_ADM_REALLOCFAIL_FREE_FLAG  0x40 /* if kal_adm_realloc() failed, free old user buffer before return NULL */
#define KAL_ADM_LIGHTCHECK_FREEPATTERN_FLAG   0x80
#define KAL_ADM_FREEPATTERN_FLAG   0x100
/* DOM-NOT_FOR_SDK-BEGIN */
#define KAL_ADM_VALID_FLAG 0x1ff /* OR of all KAL_ADM_*_FLAG, should not used by users */
/* DOM-NOT_FOR_SDK-END */

/* DOM-NOT_FOR_SDK-BEGIN */
/* ADM allocation options */
#define ADM_OPT_ALIGN_ALLOC         (0x01 << 16)
#define ADM_CACHE_1_CHANNEL_COVER   (0x02 << 16)
#define ADM_CACHE_ALL_CHANNEL_COVER (0x04 << 16)
#define ADM_OPT_TOPMOST_ALLOC       (0x08 << 16)
#define ADM_OPT_BOTTOMMOST_ALLOC	(0x10 << 16) /* allocate from the bottom(lower address)*/
#define ADM_OPT_MASK                (0x7fff << 16) /* the highest bit is reserved to avoid signed overflow warning */
/* DOM-NOT_FOR_SDK-END */
/* Calculate how many words needed for an extheader (argument of extheader_size_in_word in kal_adm_create2) */
#define KAL_ADM_EXTHEADER_WORDS(x) (((x) + 3) / sizeof(kal_uint32) * sizeof(kal_uint32))

/* DOM-NOT_FOR_SDK-BEGIN */
/* ADM POOL SIZE CALCULATE MACROS BEGIN */
/* NOTE:															*/
/* following sizes are hard size for ADM structure, user must not 	*/
/* use it directly. and it must be sync with kal_adm.h when ADM 	*/
/* structure has been changed.										*/
/* macros internal begin */
#define ADM_CB_SIZE							16
#define ADM_BL_SIZE							16
#define ADM_MB_MINI_HEAD_SIZE				8
#define ADM_MB_HEAD_SIZE					16
#define ADM_MB_HEADGUARD_SIZE				4	
#define ADM_MB_FOOTGUARD_SIZE				4
#define ADM_MB_OLDLOGGING_EXTHEADER_SIZE	8
/* macros internal end */

/* macros external begin */
#define ADM_DEFAULT_BL_NUM					7
#define	ADM_MB_OVERHEAD(flags, extheader_size_in_word)	\
		(ADM_MB_MINI_HEAD_SIZE + \
		((flags) & KAL_ADM_OLD_ISLOGGING_FLAG ? (ADM_MB_HEADGUARD_SIZE+ADM_MB_FOOTGUARD_SIZE+ADM_MB_OLDLOGGING_EXTHEADER_SIZE):0) + \
		((flags) & KAL_ADM_GUARDIAN_FLAG ? (ADM_MB_HEADGUARD_SIZE+ADM_MB_FOOTGUARD_SIZE):0) + \
		((flags) & KAL_ADM_EXTHEADER_FLAG ? (extheader_size_in_word)*4:0))
		
#define ADM_POOLSIZE_CALC(bl_num,user_pool_size) \
		(ADM_CB_SIZE + \
		ADM_BL_SIZE * (bl_num) + \
		ADM_MB_MINI_HEAD_SIZE+ADM_MB_HEADGUARD_SIZE+ADM_MB_FOOTGUARD_SIZE + \
		ADM_MB_MINI_HEAD_SIZE+ADM_MB_HEADGUARD_SIZE+ADM_MB_FOOTGUARD_SIZE + \
		(user_pool_size))
/* macros external end */
/* ADM POOL SIZE CALCULATE MACROS END */
/* DOM-NOT_FOR_SDK-END */

/* DOM-NOT_FOR_SDK-BEGIN */
/* AFM allocation options */
#define AFM_OPT_NONE         0x0000
#define AFM_OPT_ALIGN_ALLOC  0x0001 /* user buffers in this AFM is aligned to CPU cache line (32 bytes) */
#define AFM_OPT_DBG          0x0002
#define AFM_OPT_CUSLOG       0x0004
#define AFM_OPT_NOFALLBACK_ALLOC 0x0008 /* when search avaiable user buffer, don't try to search subpools bigger than fittest subpool */
#define AFM_OPT_DBG_FREEPATTERN  0x0010
#define AFM_OPT_VALID 0x1F /* OR of all AFM_OPT_*, should not used by users */

#define AFM_LOG_PAUSE 0x01
#define AFM_LOG_CLEAR 0x02
#define AFM_LOG_CLR   AFM_LOG_CLEAR /* for compatible only */
#define AFM_LOG_START 0x04
#define AFM_LOG_STR   AFM_LOG_START /* for compatible only */
/* DOM-NOT_FOR_SDK-END */

/* DOM-NOT_FOR_SDK-BEGIN */
/* AFM POOL SIZE CALCULATE MACROS BEGIN*/
/* NOTE:															*/
/* following sizes are hard size for AFM structure, user MUST NOT 	*/
/* use it directly. and it must be sync with kal_afm.h when AFM 	*/
/* structure has been changed.										*/
/* macros internal begin*/
#define AFM_CB_T_SIZE						16
#define AFM_POOL_CB_T_SIZE					20
#define AFM_POOL_CUSLOG_T_SIZE				4
#define AFM_MB_HEAD_T_SIZE					8
#define AFM_MB_HEADGUD_T_SIZE				16
#define AFM_MB_FOOTGUD_T_SIZE				4
#define ALIGNTO4(sz) (((sz) + 3) & ~3)
#define ALIGNTOCACHELINE(sz) (((sz) + CPU_CACHE_LINE_SIZE-1) & ~(CPU_CACHE_LINE_SIZE-1))
/* macros internal end*/

/* macros external begin*/
#define AFM_MB_OVERHEAD(option) (AFM_MB_HEAD_T_SIZE + (option & AFM_OPT_DBG ? AFM_MB_HEADGUD_T_SIZE + AFM_MB_FOOTGUD_T_SIZE : 0))
#if defined(__MTK_TARGET__) && (defined(__ARM9_MMU__) || defined(__DYNAMIC_SWITCH_CACHEABILITY__))
#define AFM_POOL_OVERHEAD(option, subpool_count) \
    (AFM_CB_T_SIZE + AFM_POOL_CB_T_SIZE * subpool_count \
        + (((option) & AFM_OPT_CUSLOG) ? AFM_POOL_CUSLOG_T_SIZE * (subpool_count) : 0) + 4 \
        + (((option) & AFM_OPT_ALIGN_ALLOC) ? CPU_CACHE_LINE_SIZE : 0))
#define AFM_SUBPOOL_OVERHEAD(option, sz, nr) \
    (option & AFM_OPT_ALIGN_ALLOC ? \
        (nr) * (ALIGNTOCACHELINE(sz) + ALIGNTOCACHELINE(AFM_MB_OVERHEAD(option))) \
        : (nr) * (ALIGNTO4(sz) + AFM_MB_OVERHEAD(option))) 
#else
#define AFM_POOL_OVERHEAD(option, subpool_count) \
    AFM_CB_T_SIZE + AFM_POOL_CB_T_SIZE * (subpool_count) \
        + ((option & AFM_OPT_CUSLOG) ? AFM_POOL_CUSLOG_T_SIZE * subpool_count : 0) + 4 
#define AFM_SUBPOOL_OVERHEAD(option, sz, nr) \
    (nr) * (ALIGNTO4(sz) + AFM_MB_OVERHEAD(option))
#endif
/* macros external end*/
/* AFM POOL SIZE CALCULATE MACROS END*/		
#define AFM_SUBPOOL_END_PATTERN 0xFFFFFFFF
/* DOM-NOT_FOR_SDK-END */

#if defined(__MTK_TARGET__) && defined(__KAL_STACK_ISOLATION__)

#define KAL_VM_PAGESIZE (4096)  /* KAL VM page size */

#ifdef __ARM9_MMU__
#define KAL_VM_STACK_PAGESIZE 1024
#else //!__ARM9_MMU__
#define KAL_VM_STACK_PAGESIZE 4096
#endif //__ARM9_MMU__
#define KAL_VM_STACK_UPALIGN(x) ( ((x) + KAL_VM_STACK_PAGESIZE - 1) / KAL_VM_STACK_PAGESIZE * KAL_VM_STACK_PAGESIZE)
#define KAL_VM_STACK_ALIGNED(x) ( (x) & ~(KAL_VM_STACK_PAGESIZE - 1) == 0 )
#define kal_vm_stack_begin() (custom_get_FLMM_STACKSPACE_Base())
#define kal_vm_stack_end()   (custom_get_FLMM_STACKSPACE_End())

#define KAL_VM_PAGE_ALIGNED(x) (!( ((kal_uint32)(x)) & (KAL_VM_PAGESIZE - 1))) /* is KAL VM page size aligned */
#define KAL_VM_PAGE_UPALIGN(x) (( ((kal_uint32)(x)) + KAL_VM_PAGESIZE - 1) & ~(KAL_VM_PAGESIZE - 1)) /* align to next KAL VM page size */
#define KAL_VM_PAGE_DOWNALIGN(x) ( ((kal_uint32)(x)) & ~(KAL_VM_PAGESIZE - 1)) /* align to KAL VM page size */
#define KAL_VM_PAGE_MARGIN(x) (KAL_VM_PAGE_UPALIGN(x) - (x))                   /* how many bytes needed to align to next KAL VM page size */

#endif /* #if defined(__MTK_TARGET__) && defined(__KAL_STACK_ISOLATION__) */

/* define maximum memory region number can be dump via catcher on EXT_ASSERT_DUMP */
#define ASSERT_DUMP_PARAM_MAX 10

/* memory regions dump via catcher */
typedef struct ASSERT_DUMP_PARAM
{
    kal_uint32 addr[ASSERT_DUMP_PARAM_MAX]; /* start address of this memory region */
    kal_uint32 len[ASSERT_DUMP_PARAM_MAX];  /* length of this memory region */
} ASSERT_DUMP_PARAM_T;

/* keys of assert specific */
typedef enum
{
    ASSERT_NONE,
    ASSERT_SPECIFIC_CALLBACK,
    ASSERT_SPECIFIC_WITH_LR,
    ASSERT_LINE,
    ASSERT_EXT,
    ASSERT_EXT_DUMP,
    ASSERT_NATIVE
} assert_specific_key;

/* callback function of ASSERT_SPECIFIC_CALLBACK */
typedef void (*Assert_Specific_Callback)(void* para_ptr);


/* define wait mode */
typedef enum {
    KAL_NO_WAIT,       /* don't wait if the condition is not satisfied and return error code */
    KAL_INFINITE_WAIT  /* wait until the condition is satisfied */
} kal_wait_mode;

/* define kal status */
typedef enum {
    KAL_SUCCESS,            /* the operation is succeeded */
    KAL_ERROR,              /* general error */
    KAL_Q_FULL,             /* queue is full */
    KAL_Q_EMPTY,            /* queue is empty */
    KAL_SEM_NOT_AVAILABLE,  /* semaphore is not available at the moment */
    KAL_WOULD_BLOCK,        /* the operation would block but requester don't want */
    KAL_MESSAGE_TOO_BIG,    /* message is too big */
    KAL_INVALID_ID,         /* an invalid identity */
    KAL_NOT_INITIALIZED,    /* the resource is not initialized */
    KAL_INVALID_LENGHT,     /* an invalid length */
    KAL_NULL_ADDRESS,       /* the address is NULL */
    KAL_NOT_RECEIVE,        /* no receiver want this message */
    KAL_NOT_SEND,           /* can't send this message out */
    KAL_MEMORY_NOT_VALID,   /* memory is corrupted */
    KAL_NOT_PRESENT,        /* the request resource is not present */
    KAL_MEMORY_NOT_RELEASE, /* some memory is not released */
    KAL_TIMEOUT             /* the opearation time out */
} kal_status;

/* define kal task status */
typedef enum {
/*------- error cases -------*/
    KAL_ERROR_RESERVE1,   /**/
    KAL_ERROR_RESERVE2,   /**/
    KAL_ERROR_RESERVE3,   /**/
    KAL_ERROR_TCB,        /* incorrect task control block */
/*------- running case -------*/
    KAL_READY,            /* ready to execute */
/*------- suspend cases -------*/
    KAL_SLEEP_SUSPEND,    /* waiting for sleep timeout */
    KAL_SEMA_SUSPEND,     /* waiting for semaphore */
    KAL_ENHMUTEX_SUSPEND, /* waiting for enhanced mutex */
    KAL_OTHER_SUSPEND,    /* waiting for other resource */
    KAL_EVENT_SUSPEND,    /* waiting for event */
    KAL_QUEUE_SUSPEND,    /* waiting for queue */
    KAL_RESERVE1_SUSPEND, /*  */
    KAL_RESERVE2_SUSPEND, /*  */
    KAL_RESERVE3_SUSPEND, /*  */
/*------- end case -------*/
    KAL_TERMINATED,       /* task is terminated */
} kal_task_status;

#define KAL_MAX_TICKS           (2048*26*51)
#define ALIGNED_TIMER_MAX_DELAY  (255)
#ifdef __STACK_ALIGN_MPU__
#define KAL_TASK_STACK_ALIGN     (__STACK_ALIGN_MPU__)
#else
#define KAL_TASK_STACK_ALIGN     (8U)
#endif
#define KAL_TASK_STACK_ALIGNMASK (KAL_TASK_STACK_ALIGN-1)
#define KAL_STACK_ALIGN(SIZE)    (((SIZE + KAL_TASK_STACK_ALIGNMASK) / KAL_TASK_STACK_ALIGN) * KAL_TASK_STACK_ALIGN)


#ifdef KAL_ON_NUCLEUS
/* define how many miliseconds per system tick represent */
#ifdef OS_TICK_PERIOD_US
#define KAL_MICROSECS_PER_TICK     OS_TICK_PERIOD_US
#define KAL_MILLISECS_PER_TICK     ((float)KAL_MICROSECS_PER_TICK/1000)

/* +(KAL_MICROSECS_PER_TICK/2)/KAL_MICROSECS_PER_TICK:
 *    round the number to the nearest whole number
 */
#define KAL_TICKS_10_MSEC          ((     10000+(KAL_MICROSECS_PER_TICK/2))/KAL_MICROSECS_PER_TICK)  /* 10 msec */
#define KAL_TICKS_50_MSEC          ((     50000+(KAL_MICROSECS_PER_TICK/2))/KAL_MICROSECS_PER_TICK)  /* 50 msec */
#define KAL_TICKS_100_MSEC         ((    100000+(KAL_MICROSECS_PER_TICK/2))/KAL_MICROSECS_PER_TICK)  /* 100 msec */
#define KAL_TICKS_500_MSEC         ((    500000+(KAL_MICROSECS_PER_TICK/2))/KAL_MICROSECS_PER_TICK)  /* 500 msec */
#define KAL_TICKS_1024_MSEC        ((   1024000+(KAL_MICROSECS_PER_TICK/2))/KAL_MICROSECS_PER_TICK)  /* 1024 msec */
#define KAL_TICKS_1_SEC            ((   1000000+(KAL_MICROSECS_PER_TICK/2))/KAL_MICROSECS_PER_TICK)  /* 1 sec */
#define KAL_TICKS_2_SEC            ((   2000000+(KAL_MICROSECS_PER_TICK/2))/KAL_MICROSECS_PER_TICK)  /* 2 sec */
#define KAL_TICKS_3_SEC            ((   3000000+(KAL_MICROSECS_PER_TICK/2))/KAL_MICROSECS_PER_TICK)  /* 3 sec */
#define KAL_TICKS_5_SEC            ((   5000000+(KAL_MICROSECS_PER_TICK/2))/KAL_MICROSECS_PER_TICK)  /* 5 sec */
#define KAL_TICKS_30_SEC           ((  30000000+(KAL_MICROSECS_PER_TICK/2))/KAL_MICROSECS_PER_TICK)  /* 30 sec */
#define KAL_TICKS_1_MIN            ((  60000000+(KAL_MICROSECS_PER_TICK/2))/KAL_MICROSECS_PER_TICK)  /* 1 min */
#define KAL_MSEC_64_TICKS          ((KAL_MICROSECS_PER_TICK*64+(1000/2))   /1000)  /* 64 ticks */
#define KAL_MSEC_256_TICKS         ((KAL_MICROSECS_PER_TICK*256+(1000/2))  /1000)  /* 256 ticks */


#else  /* else of OS_TICK_PERIOD_US */
#define KAL_MICROSECS_PER_TICK      4615
#define KAL_MILLISECS_PER_TICK      4.615

/* DOM-NOT_FOR_SDK-BEGIN */
/* Following defines are internal to the KAL */
#define KAL_TICKS_10_MSEC           (2)         /* 10 msec */
#define KAL_TICKS_50_MSEC           (10)        /* 50 msec */
#define KAL_TICKS_100_MSEC          (21)        /* 100 msec */
#define KAL_TICKS_500_MSEC          (108)       /* 500 msec */
#define KAL_TICKS_1024_MSEC         (221)       /* 1024 msec */
#define KAL_TICKS_1_SEC             (216)       /* 1 sec */
#define KAL_TICKS_2_SEC				(433)       /* 2 sec */
#define KAL_TICKS_3_SEC             (650)       /* 3 sec */
#define KAL_TICKS_5_SEC             (1083)      /* 5 sec */
#define KAL_TICKS_30_SEC            (6500)      /* 30 sec */
#define KAL_TICKS_1_MIN             (13000)     /* 1 min */
#define KAL_MSEC_64_TICKS           (295)       /* 64 ticks */
#define KAL_MSEC_256_TICKS          (1181)      /* 256 ticks */
/* DOM-NOT_FOR_SDK-END */


#endif /* end of "else of OS_TICK_PERIOD_US" */
#endif /* KAL_ON_NUCLEUS */


#ifdef KAL_ON_OSCAR
/* define how many miliseconds per system tick represent */
#define KAL_MILLISECS_PER_TICK      5
#define KAL_MICROSECS_PER_TICK      5000


/* DOM-NOT_FOR_SDK-BEGIN */
/* Following defines are internal to the KAL */
#define KAL_SIM_MSECS_PER_TICK      KAL_MILLISECS_PER_TICK
#define KAL_TICKS_10_MSEC           (10/KAL_SIM_MSECS_PER_TICK)   /* 10 msec */
#define KAL_TICKS_50_MSEC           (50/KAL_SIM_MSECS_PER_TICK)   /* 50 msec */
#define KAL_TICKS_100_MSEC          (100/KAL_SIM_MSECS_PER_TICK)  /* 100 msec */
#define KAL_TICKS_500_MSEC          (500/KAL_SIM_MSECS_PER_TICK)  /* 500 msec */
#define KAL_TICKS_1024_MSEC         (1024/KAL_SIM_MSECS_PER_TICK)  /* 1024 msec */
#define KAL_TICKS_1_SEC             (1000/KAL_SIM_MSECS_PER_TICK) /* 1 sec */
#define KAL_TICKS_2_SEC				(2000/KAL_SIM_MSECS_PER_TICK) /* 2 sec */
#define KAL_TICKS_3_SEC             (3000/KAL_SIM_MSECS_PER_TICK) /* 3 sec */
#define KAL_TICKS_5_SEC             (5000/KAL_SIM_MSECS_PER_TICK) /* 5 sec */
#define KAL_TICKS_30_SEC            (30000/KAL_SIM_MSECS_PER_TICK)/* 30 sec */
#define KAL_TICKS_1_MIN             (60000/KAL_SIM_MSECS_PER_TICK)/* 1 min */
#define KAL_MSEC_64_TICKS           (64*KAL_SIM_MSECS_PER_TICK)       /* 64 ticks */
#define KAL_MSEC_256_TICKS          (256*KAL_SIM_MSECS_PER_TICK)      /* 256 ticks */
/* DOM-NOT_FOR_SDK-END */
#endif /* KAL_ON_OSCAR */

#if defined(KAL_ON_OSABS)
#define KAL_TICKS_10_MSEC           (2)         /* 10 msec */
#define KAL_TICKS_50_MSEC           (10)        /* 50 msec */
#define KAL_TICKS_100_MSEC          (21)        /* 100 msec */
#define KAL_TICKS_500_MSEC          (108)       /* 500 msec */
#define KAL_TICKS_1024_MSEC         (221)       /* 1024 msec */
#define KAL_TICKS_1_SEC             (216)       /* 1 sec */
#define KAL_TICKS_5_SEC             (1083)      /* 5 sec */
#define KAL_TICKS_30_SEC            (6500)      /* 30 sec */
#define KAL_TICKS_1_MIN             (13001)     /* 1 min */
#define KAL_MSEC_64_TICKS           (295)       /* 64 ticks */
#define KAL_MSEC_256_TICKS          (1181)      /* 256 ticks */
#endif

#ifndef INLINE
#if defined(__ARMCC_VERSION)
    #define INLINE              __inline
    #define INLINE_MODIFIER     extern
#elif defined (__GNUC__) && !defined(__MINGW32__)
    #define INLINE              inline
    #define INLINE_MODIFIER     extern
#elif defined (_MSC_VER) || defined(__MINGW32__)
    #define INLINE              __inline
    #define INLINE_MODIFIER     static
#endif /* Cross RVCT/GCC/VC9 Compiler marco definition */
#endif
//#define INLINE inline
//#define INLINE_MODIFIER  static

#if defined(__ARMCC_VERSION)
    #define GET_RETURN_ADDRESS(a) a=__return_address()
#elif defined (__GNUC__)
    #define GET_RETURN_ADDRESS(a) a=(kal_uint32)__builtin_return_address(0)
#elif defined (_MSC_VER)
    #define GET_RETURN_ADDRESS(a) a=_ReturnAddress()
#endif /* Cross RVCT/GCC/VC9 Compiler marco definition */
#if defined(__ARMCC_VERSION)
    #define GET_STACK_POINTER(a) a= __current_sp()
#elif defined (__GNUC__)
    #define GET_STACK_POINTER(a) a= (kal_uint32)__builtin_frame_address(0)
#elif defined (_MSC_VER)
    #define GET_STACK_POINTER(a) __asm mov a,ESP
#endif /* Cross RVCT/GCC/VC9 Compiler marco definition */

#if defined(__ARMCC_VERSION) && defined(__MTK_TARGET__)
    #define PRAGMA_BEGIN_COMPILER_OPTIMIZE_DISABLE	_Pragma("push")\
													_Pragma("O0")
	#define PRAGMA_END_COMPILER_OPTIMIZE_DISABLE	_Pragma("pop")
	#define PRAGMA_BEGIN_COMPILER_OPTIMIZE_TIME		_Pragma("push")\
													_Pragma("Otime")
	#define PRAGMA_END_COMPILER_OPTIMIZE_TIME		_Pragma("pop")
#elif defined(__GNUC__) && defined(__MTK_TARGET__)
    #define PRAGMA_BEGIN_COMPILER_OPTIMIZE_DISABLE	_Pragma("GCC push_options")\
													_Pragma("GCC optimize(\"-O0\")")
	#define PRAGMA_END_COMPILER_OPTIMIZE_DISABLE	_Pragma("GCC pop_options")
	#define PRAGMA_BEGIN_COMPILER_OPTIMIZE_TIME		_Pragma("GCC push_options")\
													_Pragma("GCC optimize(\"-O3\")")
	#define PRAGMA_END_COMPILER_OPTIMIZE_TIME		_Pragma("GCC pop_options")
#else
	#define PRAGMA_BEGIN_COMPILER_OPTIMIZE_DISABLE
	#define PRAGMA_END_COMPILER_OPTIMIZE_DISABLE
	#define PRAGMA_BEGIN_COMPILER_OPTIMIZE_TIME
	#define PRAGMA_END_COMPILER_OPTIMIZE_TIME
#endif /* Cross RVCT/GCC/VC9 Compiler marco definition */

#define CBS_SCAN_EVENT_INDEX (1)

/*******************************************************************************
 * Defines for ADT
 *******************************************************************************/
/* ADT */
struct adt_node;

/* ilm free callback function prototype */
typedef void (*ilm_free_callback_t)(ilm_struct *ilm_ptr);
/* ilm ADT translator callback function prototype */
typedef void (*translator_adt_enc_callback_t)(const ilm_struct *ilm_ptr, struct adt_node **adt);

#endif  /* _KAL_PUBLIC_DEFS_H */
