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
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

#ifndef _STACK_CONFIG_H
#define _STACK_CONFIG_H

#include "hisr_modid.h"
#include "srv_modid.h"
#include "modem_2g3g_modid.h"
#include "modem_4g_modid.h"
#include "middleware_modid.h"
#include "drv_modid.h"

/*************************************************************************
 * Constant Definition
 *************************************************************************/
#define MAX_CUSTOM_TASKS   16          /* Maximum custom tasks number */
#define MAX_CUSTOM_MODS    16          /* Maximum custom modules number */
#define KAL_MAX_NUM_NORMAL_HISRS  (20)    /* Maximum system HISR number */ /* 20 is normal HISR, 128 is LISR2HISR */
#define KAL_MAX_NUM_LISR2HISRS  (128)    /* Maximum system HISR number */ /* 20 is normal HISR, 128 is LISR2HISR */
#define KAL_MAX_NUM_HISRS  (KAL_MAX_NUM_NORMAL_HISRS+KAL_MAX_NUM_LISR2HISRS)
#define KAL_MAX_NUM_TASKS  255         /* Maximum tasks number: remember that this macro is defined for ftl_task_bitmap[] */
#define KAL_TASK_INITIAL_PRIORITY	256	 /* KAL_TASK_INITIAL_PRIORITY is used for configuration task's minus priority for task mode switch.*/

#define NORMAL_M	         1
#define FACTORY_M          2
#define USB_M              4

typedef enum
{
    KAL_PRIORITY_CLASS0        =     0,
    KAL_PRIORITY_CLASS1        =     10,
    KAL_PRIORITY_CLASS2        =     20,
    KAL_PRIORITY_CLASS3        =     30,
    KAL_PRIORITY_CLASS4        =     40,
    KAL_PRIORITY_CLASS5        =     50,
    KAL_PRIORITY_CLASS6        =     60,
    KAL_PRIORITY_CLASS7        =     70,
    KAL_PRIORITY_CLASS8        =     80,
    KAL_PRIORITY_CLASS9        =     90,
    KAL_PRIORITY_CLASS10       =     100,
    KAL_PRIORITY_CLASS11       =     110,
    KAL_PRIORITY_CLASS12       =     120,
    KAL_PRIORITY_CLASS13       =     130,
    KAL_PRIORITY_CLASS14       =     140,
    KAL_PRIORITY_CLASS15       =     150,
    KAL_PRIORITY_CLASS16       =     160,
    KAL_PRIORITY_CLASS17       =     170,
    KAL_PRIORITY_CLASS18       =     180,
    KAL_PRIORITY_CLASS19       =     190,
    KAL_PRIORITY_CLASS20       =     200,
    KAL_PRIORITY_CLASS21       =     210,
    KAL_PRIORITY_CLASS22       =     220,
    KAL_PRIORITY_CLASS23       =     230,
    KAL_PRIORITY_CLASS24       =     240,
    KAL_PRIORITY_CLASS25       =     250
} kal_priority_type;

/*Expand Task priority macro here*/
#define TASK_PRIORITY_MACRO

#include "srv_task_config.h"
#include "modem_2g3g_task_config.h"
#include "modem_4g_task_config.h"
#include "middleWare_task_config.h"
#include "drv_task_config.h"

#undef TASK_PRIORITY_MACRO

#define RPS_MAX_MODULES_IN_TASK     12
#define RPS_NO_TASK_NAME            ""
#define RPS_QNAME_NIL               ""
#define RPS_TASK_PRIORITY_NIL       0
#define RPS_STACK_SIZE_NIL          0
#define RPS_QSIZE_NIL               0

/*************************************************************************
 * Total HISR number boundary check
 * Don't use this array in your code
 *************************************************************************/
/* if you change maximum system HISR number(NOW is 20), please also modify INDX_NIL number in mod_task_g[]*/
typedef unsigned int hisr_max_num_check[(KAL_MAX_NUM_HISRS - 147) * (149 - KAL_MAX_NUM_HISRS)]; 
/************************************************************************/

#endif /* _STACK_CONFIG_H */
