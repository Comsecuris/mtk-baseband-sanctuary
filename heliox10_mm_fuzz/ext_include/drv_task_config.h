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
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

#ifdef TASK_PRIORITY_MACRO
/*Put tasks for debug and test purpose only together to save priority*/

#define TASK_PRIORITY_AUDH              (KAL_PRIORITY_CLASS6 + 3)
#define TASK_PRIORITY_L1AUDIO           (KAL_PRIORITY_CLASS12+ 4)
#define TASK_PRIORITY_L1AUDIO_SPH_SRV   (KAL_PRIORITY_CLASS12+ 5)
#define TASK_PRIORITY_USB               (KAL_PRIORITY_CLASS12+ 6)
#define TASK_PRIORITY_SDIOCORE          (KAL_PRIORITY_CLASS13+ 7)
#define TASK_PRIORITY_CMUX              (KAL_PRIORITY_CLASS15+ 8)
#define TASK_PRIORITY_MED               (KAL_PRIORITY_CLASS16+ 9)
#define TASK_PRIORITY_DRIVER_TEST       (KAL_PRIORITY_CLASS17+ 7)
#define TASK_PRIORITY_BMT               (KAL_PRIORITY_CLASS18+ 9)
#define TASK_PRIORITY_IDLER             (KAL_PRIORITY_CLASS25+ 2)
#define TASK_PRIORITY_IDLE              (KAL_PRIORITY_CLASS25+ 5)


#if defined(ATEST_ENABLE) && defined(ATEST_DRV_ENABLE) && defined(__MTK_TARGET__)
    #include "drvtest_task_config.h"
#endif /* end of __MTK_DRVTEST_ENABLE__ */

#else
/*module id are divided into 3 parts. 
 * 1: module id that maps to task
 * 2: module id that maps to no task but can be used as src module id
 *  to allocate ilm, like HISR's module id
 * 3: module id that is used to print trace only.  * */

/********************* Driver Start  ************************/
/*************************Task CFG Begin****************/
/*task_indx_type*/
/* this is a fake task for task id grouping*/
task_index(INDX_DRV_START = TASK_ID_DRV_CODE_BEGIN)

/*module_type and mod_task_g*/
task_module_map(INDX_DRV_START, MOD_DRV_DUMMY_BEGIN = MOD_ID_DRV_CODE_BEGIN)
/*task's parameters*/
task_name("")
task_queue_name("")
task_priority(KAL_TASK_INITIAL_PRIORITY , KAL_TASK_INITIAL_PRIORITY)
task_stack_size(0)
null_task_create_entry(NULL)
task_stack_internalRAM(KAL_FALSE)
task_external_queue_size(0)
task_internal_queue_size(0)
task_boot_mode(NORMAL_M)
/*************************Task CFG END******************/

/*************************Task CFG Begin****************/
/*For smart phone and modem interaction*/
/*task_indx_type*/
task_index(INDX_CMUX)            /*WAP ps task*/ 
/*dummy mod is specified to get task id by mod id, use mod_task_g*/
task_module_map(INDX_CMUX,MOD_DUMMY_CMUX)
/*module_type and mod_task_g*/
task_module_map(INDX_CMUX, MOD_CMUX)
task_module_map(INDX_CMUX, MOD_CMUXUH)
task_module_map(INDX_CMUX, MOD_UPS_HIGH)

/*task's parameters*/
task_name("CMUX")
task_queue_name("CMUX Q")
task_priority(TASK_PRIORITY_CMUX , KAL_TASK_INITIAL_PRIORITY )
task_stack_size(2048)
#if (defined(__CMUX_SUPPORT__) || defined(__USB_TETHERING__) || defined(__MBIM_SUPPORT__)) && !defined(__CMUX_TASK_DISABLE__)
task_create_function(cmux_create)
#else
null_task_create_entry(NULL)
#endif
task_stack_internalRAM(KAL_FALSE)
task_external_queue_size(10)
task_internal_queue_size(INT_Q_LEN)
task_boot_mode(NORMAL_M)
/*************************Task CFG END******************/

/*************************Task CFG Begin****************/
/*task_indx_type*/
task_index(INDX_IDLER)  /*file system disk space reclaim*/ 
/*dummy mod is specified to get task id by mod id, use mod_task_g*/
task_module_map(INDX_IDLER,MOD_DUMMY_IDLER)
task_module_map(INDX_IDLER, MOD_IDLER)
/*task's parameters*/
task_name("IDLR")
task_queue_name("IDLER Q")
task_priority(TASK_PRIORITY_IDLER , KAL_TASK_INITIAL_PRIORITY )
#if defined(__LOW_COST_SUPPORT_ULC__)
task_stack_size(1024)
#else /* __LOW_COST_SUPPORT_ULC__ */
task_stack_size(2048)
#endif /* __LOW_COST_SUPPORT_ULC__ */
#if defined(__NOR_FDM5__) && defined(__MTK_TARGET__) && !defined(__IDLERECL_TASK_DISABLE__) && !defined(ATEST_DRV_ENVIRON)
task_create_function(idlerecl_create)
#elif (defined(__SINGLE_BANK_NOR_FLASH_SUPPORT__) || defined(__NOR_IDLE_SWEEP__)) && defined(__MTK_TARGET__) && !defined(__IDLERECL_TASK_DISABLE__) && !defined(ATEST_DRV_ENVIRON)
task_create_function(idle_recl_create)
#else /* __NOR_FDM5__ */
null_task_create_entry(NULL)
#endif /* __NOR_FDM5__ && __MTK_TARGET__ */
task_stack_internalRAM(KAL_FALSE)
task_external_queue_size(0)
task_internal_queue_size(0)
task_boot_mode(NORMAL_M)
/*************************Task CFG END******************/

/*************************Task CFG Begin****************/
/*task_indx_type*/
task_index(INDX_BMT)
/*dummy mod is specified to get task id by mod id, use mod_task_g*/
task_module_map(INDX_BMT,MOD_DUMMY_BMT)
/*module_type and mod_task_g*/
task_module_map(INDX_BMT, MOD_BMT)

    /*task's parameters*/
task_name("DRVBMT")
task_queue_name("DRVBMT Q")
task_priority(TASK_PRIORITY_BMT , KAL_TASK_INITIAL_PRIORITY )
#if defined(__TC01__)
task_stack_size(1024)
#elif defined(__LOW_COST_SUPPORT_ULC__)
task_stack_size(768)
#else /* __LOW_COST_SUPPORT_ULC__ */
task_stack_size(800)
#endif /* __LOW_COST_SUPPORT_ULC__ */

#if defined(KAL_ON_OSCAR) || defined(IC_BURNIN_TEST) || defined(__LTE_SM__) || !defined(__SMART_PHONE_MODEM__) || defined(__BMT_TASK_DISABLE__)
null_task_create_entry(NULL)
#else
task_create_function(bmt_create)
#endif
task_stack_internalRAM(KAL_FALSE)
task_external_queue_size(10)
task_internal_queue_size(0)
task_boot_mode(NORMAL_M)
/*************************Task CFG END******************/
    
/*************************Task CFG Begin****************/
/*task_indx_type*/
task_index(INDX_USB) 
/*dummy mod is specified to get task id by mod id, use mod_task_g*/
task_module_map(INDX_USB,MOD_DUMMY_USB)
/*module_type and mod_task_g*/
task_module_map(INDX_USB, MOD_USB)

/*task's parameters*/
task_name("USB")
task_queue_name("USB Q")
task_priority(TASK_PRIORITY_USB , KAL_TASK_INITIAL_PRIORITY )
#if defined(PICTBRIDGE_SUPPORT)
task_stack_size(3800)
#elif defined(__USB_IN_NORMAL_MODE__)
task_stack_size(2680)
#else    /* PICTBRIDGE_SUPPORT */
task_stack_size(2680)
#endif   /* PICTBRIDGE_SUPPORT */
#if defined(__USB_ENABLE__) && !defined(__MEUT__) && !defined(__USB_TASK_DISABLE__)
task_create_function(usb_create)
#else
null_task_create_entry(NULL)
#endif
task_stack_internalRAM(KAL_FALSE)
task_external_queue_size(10)
task_internal_queue_size(0)
task_boot_mode(NORMAL_M | FACTORY_M)
/*************************Task CFG END******************/

/*************************Task CFG Begin****************/
/*task_indx_type*/
task_index(INDX_L1SP) 
/*dummy mod is specified to get task id by mod id, use mod_task_g*/
task_module_map(INDX_L1SP,MOD_DUMMY_L1SP)
/*module_type and mod_task_g*/
task_module_map(INDX_L1SP, MOD_L1SP)

/*task's parameters*/
task_name("AUDIO")
task_queue_name("AUDIO Q")
task_priority(TASK_PRIORITY_L1AUDIO , KAL_TASK_INITIAL_PRIORITY )
#if defined(__DRM_SUPPORT__) && defined(MIDFILE_PLAY_SUPPORT)
task_stack_size(3072)
#else
#if defined(__DRM_SUPPORT__) && defined(__DRM_V02__)
task_stack_size(2176)
#else  /* __DRM_SUPPORT__ && __DRM_V02__ */
#if defined(__LOW_COST_SUPPORT_ULC__)
task_stack_size(1024)
#else /* __LOW_COST_SUPPORT_ULC__ */
task_stack_size(2048)
#endif /* __LOW_COST_SUPPORT_ULC__ */
#endif /* __DRM_SUPPORT__ && __DRM_V02__ */
#endif /*__DRM_SUPPORT__ && MIDFILE_PLAY_SUPPORT*/                                   
#if defined (L1_NOT_PRESENT) || defined (__UE_SIMULATOR__) || defined(__L1SP_TASK_DISABLE__)
null_task_create_entry(NULL)
#else
task_create_function(l1sp_create)
#endif
task_stack_internalRAM(KAL_FALSE)
#ifdef __SMART_PHONE_MODEM__
task_external_queue_size(10)
#else
task_external_queue_size(0)
#endif
task_internal_queue_size(0)
task_boot_mode(NORMAL_M | FACTORY_M)
/*************************Task CFG END******************/

/*************************Task CFG Begin****************/
/*task_indx_type*/
task_index(INDX_L1AUDIO_SPH_SRV)
/*dummy mod is specified to get task id by mod id, use mod_task_g*/
task_module_map(INDX_L1AUDIO_SPH_SRV,MOD_DUMMY_L1AUDIO_SPH_SRV)
/*module_type and mod_task_g*/
task_module_map(INDX_L1AUDIO_SPH_SRV, MOD_L1AUDIO_SPH_SRV)

/*task's parameters*/
task_name("L1AUDIO_SPH_SRV")
task_queue_name("L1AUDIO_SPH_SRV Q")
task_priority(TASK_PRIORITY_L1AUDIO_SPH_SRV , KAL_TASK_INITIAL_PRIORITY )
task_stack_size(1024)
#if defined(L1_NOT_PRESENT) || defined (__UE_SIMULATOR__) || defined(__L1AUDIO_SPH_SRV_TASK_DISABLE__)
null_task_create_entry(NULL)
#else
task_create_function(l1audio_sph_srv_create)
#endif
task_stack_internalRAM(KAL_FALSE)
task_external_queue_size(10)
task_internal_queue_size(0)
task_boot_mode(NORMAL_M | FACTORY_M)
/*************************Task CFG END******************/

/*************************Task CFG Begin****************/
task_index(INDX_MED) 
/*dummy mod is specified to get task id by mod id, use mod_task_g*/
task_module_map(INDX_MED,MOD_DUMMY_MED)
/*module_type and mod_task_g*/
task_module_map(INDX_MED, MOD_MED)
compatible_code(MOD_AUD=MOD_MED)    
/* MOD_MED is used by HAL file, please don't delete or modify it */

/*task's parameters*/
task_name("MED")
task_queue_name("MED Q")
task_priority(TASK_PRIORITY_MED , KAL_TASK_INITIAL_PRIORITY )

#ifdef __LOW_COST_SUPPORT_ULC__
task_stack_size(2048)
#elif defined( __CMMB_SUPPORT__ )
task_stack_size(4096)
#else
task_stack_size(3072)
#endif /* __CMMB_SUPPORT__ */
#if defined(__LTE_SM__)||defined(__MED_TASK_DISABLE__)
null_task_create_entry(NULL)
#else /* __LTE_SM__ */
task_create_function(med_create)
#endif /* __LTE_SM__ */
task_stack_internalRAM(KAL_FALSE)
task_external_queue_size(50)
task_internal_queue_size(0)
task_boot_mode(NORMAL_M | FACTORY_M)
/*************************Task CFG END******************/

/*************************Task CFG Begin****************/
/* now it's only enabled in 6575 */
#if defined(__DSP_FCORE4__)
/*task_indx_type*/
task_index(INDX_AUDH) 
/*dummy mod is specified to get task id by mod id, use mod_task_g*/
task_module_map(INDX_AUDH,MOD_DUMMY_AUDH)
/*module_type and mod_task_g*/
task_module_map(INDX_AUDH, MOD_AUDH)

/*task's parameters*/
task_name("AUDH")
task_queue_name("AUDH Q")
task_priority(TASK_PRIORITY_AUDH , KAL_TASK_INITIAL_PRIORITY )
task_stack_size(1024)

#if defined(__MTK_TARGET__) && !defined(__AUDH_TASK_DISABLE__)
task_create_function(audh_create)
#else
null_task_create_entry(NULL)
#endif
task_stack_internalRAM(KAL_FALSE)
task_external_queue_size(0)
task_internal_queue_size(0)
task_boot_mode(NORMAL_M | FACTORY_M)
#endif
/*************************Task CFG END******************/

/*************************Task CFG Begin****************/
task_index(INDX_IDLE) 
/*dummy mod is specified to get task id by mod id, use mod_task_g*/
task_module_map(INDX_IDLE,MOD_DUMMY_IDLE)
/*module_type and mod_task_g*/
task_module_map(INDX_IDLE, MOD_IDLE)

/*task's parameters*/
task_name("IDLE")
task_queue_name("IDLE Q")
task_priority(TASK_PRIORITY_IDLE , KAL_TASK_INITIAL_PRIORITY )
task_stack_size(512)
#if defined(__MTK_TARGET__) && (!defined(__IDLE_TASK_DISABLE__))
task_create_function(idle_create)
#else
null_task_create_entry(NULL)
#endif
task_stack_internalRAM(KAL_FALSE)
task_external_queue_size(0)
task_internal_queue_size(0)
task_boot_mode(NORMAL_M)
/*************************Task CFG END******************/

/*************************Task CFG Begin****************/
#if defined(DEVDRV_TEST)  && defined(__MTK_TARGET__)
/*task_indx_type*/
task_index(INDX_DRIVER_TEST)
/*dummy mod is specified to get task id by mod id, use mod_task_g*/
task_module_map(INDX_DRIVER_TEST,MOD_DUMMY_DRIVER_TEST)
/*module_type and mod_task_g*/
task_module_map(INDX_DRIVER_TEST, MOD_DRIVER_TEST)

/*task's parameters*/
task_name("DRVTEST")
task_queue_name("DRVTEST Q")
task_priority(TASK_PRIORITY_DRIVER_TEST , KAL_TASK_INITIAL_PRIORITY )
task_stack_size(2048)
task_create_function(drvtest_create)
task_stack_internalRAM(KAL_FALSE)
task_external_queue_size(10)
task_internal_queue_size(0)
task_boot_mode(NORMAL_M | FACTORY_M)
#endif
/*************************Task CFG END******************/

/*************************Task CFG Begin****************/
/*task_indx_type*/
task_index(INDX_SDIOCORE)

/*dummy mod is specified to get task id by mod id, use mod_task_g*/
task_module_map(INDX_SDIOCORE, MOD_DUMMY_SDIOCORE)
/*module_type and mod_task_g*/
task_module_map(INDX_SDIOCORE, MOD_SDIOCORE)

/*task's parameters*/
task_name("SDIOCORE")
task_queue_name("SDIOCORE Q")
task_priority(TASK_PRIORITY_SDIOCORE, KAL_TASK_INITIAL_PRIORITY)
task_stack_size(4096)
#if defined(__SDIOCORE_SUPPORT__) && !defined(SDIOCORE_NOT_PRESENT) && !defined(__SDIOCORE_TASK_DISABLE__)
task_create_function(sdioc_create)
#else
null_task_create_entry(NULL)
#endif
task_stack_internalRAM(KAL_FALSE)
task_external_queue_size(10)
task_internal_queue_size(0)
task_boot_mode(NORMAL_M | FACTORY_M)
/*************************Task CFG END******************/

/*************************Task CFG Begin****************/
/*
will use a file to record this 

the customer will define task id at this file
*/
/*************************Task CFG END******************/

/* drv*/
MODULE_ID_MAP_TO_NULL_TASK_CAN_ALLOCATE_ILM(MOD_EINT_HISR)
MODULE_ID_MAP_TO_NULL_TASK_CAN_ALLOCATE_ILM(MOD_UART1_HISR)  
MODULE_ID_MAP_TO_NULL_TASK_CAN_ALLOCATE_ILM(MOD_UART2_HISR) 
MODULE_ID_MAP_TO_NULL_TASK_CAN_ALLOCATE_ILM(MOD_UART3_HISR) 
MODULE_ID_MAP_TO_NULL_TASK_CAN_ALLOCATE_ILM(MOD_RTC_HISR) 
MODULE_ID_MAP_TO_NULL_TASK_CAN_ALLOCATE_ILM(MOD_MSDC_HISR) 
#if defined(__MEUT__)
MODULE_ID_MAP_TO_NULL_TASK_CAN_ALLOCATE_ILM(MOD_GPTA_HISR1)
#endif

MODULE_ID_FOR_PRINT_TRACE(MOD_DP_ENGINE)
MODULE_ID_FOR_PRINT_TRACE(MOD_PPP_HW)
MODULE_ID_FOR_PRINT_TRACE(MOD_SIM_DRV)
MODULE_ID_FOR_PRINT_TRACE(MOD_PMU)
MODULE_ID_FOR_PRINT_TRACE(MOD_PMIC)
MODULE_ID_FOR_PRINT_TRACE(MOD_LPWR)
MODULE_ID_FOR_PRINT_TRACE(MOD_F32K)
MODULE_ID_FOR_PRINT_TRACE(MOD_PWM)
MODULE_ID_FOR_PRINT_TRACE(MOD_UART)

MODULE_ID_MAP_TO_NULL_TASK_CAN_ALLOCATE_ILM(MOD_DRV_DBG)
MODULE_ID_FOR_PRINT_TRACE(MOD_TTY)
MODULE_ID_FOR_PRINT_TRACE(MOD_DSPFM)
MODULE_ID_FOR_PRINT_TRACE(MOD_DEVDRV)
MODULE_ID_FOR_PRINT_TRACE(MOD_EMI)

MODULE_ID_MAP_TO_NULL_TASK_CAN_ALLOCATE_ILM(MOD_VISUAL_HISR)
/**** customer added task or module id is started  *****/

/**** customer added task or module id is ended    *****/

#if defined(ATEST_ENABLE) && defined(ATEST_DRV_ENABLE) && defined(__MTK_TARGET__)
    #include "drvtest_task_config.h"
#endif /* end of __MTK_DRVTEST_ENABLE__ */



/*************************Task CFG Begin****************/
/*task_indx_type*/
/* this is a fake task for task id grouping*/
task_index(TASK_ID_DRV_CODE_TAIL)
/*module_type and mod_task_g*/
task_module_map(TASK_ID_DRV_CODE_TAIL, MODULE_TAG_DRV_DUMMY_TAIL)

/*task's parameters*/
task_name("")
task_queue_name("")
task_priority(KAL_TASK_INITIAL_PRIORITY , KAL_TASK_INITIAL_PRIORITY)
task_stack_size(0)
null_task_create_entry(NULL)
task_stack_internalRAM(KAL_FALSE)
task_external_queue_size(0)
task_internal_queue_size(0)
task_boot_mode(NORMAL_M)
/*************************Task CFG END******************/
/********************** Driver End **************************/

#endif /*TASK_PRIORITY_MACRO*/
