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
 *   kal_general_types.h
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *   This file provides general fundemental types definations.
 *   Independent with underlaying RTOS.
 *
 *   User who include this file may not require KAL API at all.
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

#ifndef _KAL_GENERAL_TYPES_H
#define _KAL_GENERAL_TYPES_H

#include "clib.h"

/*******************************************************************************
 * Type Definitions
 *******************************************************************************/
 
/* portable character for multichar character set */
typedef char                    kal_char;
/* portable wide character for unicode character set */
typedef unsigned short          kal_wchar;

/* portable 8-bit unsigned integer */
typedef unsigned char           kal_uint8;
/* portable 8-bit signed integer */
typedef signed char             kal_int8;
/* portable 16-bit unsigned integer */
typedef unsigned short int      kal_uint16;
/* portable 16-bit signed integer */
typedef signed short int        kal_int16;
/* portable 32-bit unsigned integer */
typedef unsigned int            kal_uint32;
/* portable 32-bit signed integer */
typedef signed int              kal_int32;

/* portable 64-bit unsigned integer */
#if defined(__ARMCC_VERSION) || defined(__GNUC__) || defined(__MINGW32__) || defined(GEN_FOR_PC)
   typedef unsigned long long   kal_uint64;
#elif defined(_MSC_VER)
   typedef unsigned __int64     kal_uint64;
#endif /* Cross RVCT/GCC/VC9 Compiler marco definition */

/* portable 64-bit signed integer */
#if defined(__ARMCC_VERSION) || defined(__GNUC__) || defined(__MINGW32__) || defined(GEN_FOR_PC)
   typedef signed long long     kal_int64;
#elif defined(_MSC_VER)
   typedef __int64              kal_int64;
#endif /* Cross RVCT/GCC/VC9 Compiler marco definition */


#if !defined(_WINNT_H) && !defined(_WINNT_)
typedef unsigned short WCHAR;
#endif


/* boolean representation */
typedef enum 
{
    /* FALSE value */
    KAL_FALSE,
    /* TRUE value */
    KAL_TRUE
} kal_bool;

/*******************************************************************************
 * Constant definition
 *******************************************************************************/
#ifndef NULL
#define NULL               0
#endif

/*******************************************************************************
 * ALIGN and PACK macro definition
 *******************************************************************************/

#if defined(__ARMCC_VERSION)
	#define DECLARE_ALIGN_BEGIN(n)      __align(n)
    #define DECLARE_ALIGN_END(n)
#elif defined(__MINGW32__) 				/* end of __ARMCC_VERSION */
    #define DECLARE_ALIGN_BEGIN(n)
    #define DECLARE_ALIGN_END(n)        __attribute__ ((aligned (n)))
#elif defined(__GNUC__) 				/* end of __MINGW32__ */
    #define DECLARE_ALIGN_BEGIN(n)
    #define DECLARE_ALIGN_END(n)        __attribute__ ((aligned (n)))
#elif defined(_MSC_VER) && (_MSC_VER >= 1500)	/* end of __GNUC__ */
    #define DECLARE_ALIGN_BEGIN(n)      __declspec(align(n))
    #define DECLARE_ALIGN_END(n)        /* end of _MSC_VER */
#else  															
    #error "Unsupported Compiler in Simulator"
#endif

#if defined(__ARMCC_VERSION)
    #define PRAGMA_BEGIN_PACK_STRUCT    _Pragma("push")\
                                        _Pragma("pack(1)")
    #define PRAGMA_END_PACK_STRUCT      _Pragma("pop")
#elif defined(__MINGW32__)              /* end of __ARMCC_VERSION */
    #define PRAGMA_BEGIN_PACK_STRUCT    _Pragma("pack(push, 1)")
    #define PRAGMA_END_PACK_STRUCT      _Pragma("pack(pop)")
#elif defined(__GNUC__)                 /* end of _MINGW32_ */
    #define PRAGMA_BEGIN_PACK_STRUCT    _Pragma("pack(push, 1)")
    #define PRAGMA_END_PACK_STRUCT      _Pragma("pack(pop)")
#elif defined(_MSC_VER) && (_MSC_VER >= 1500)	/* end of __GNUC__ */
    #define PRAGMA_BEGIN_PACK_STRUCT    __pragma(pack(push, 1))
    #define PRAGMA_END_PACK_STRUCT      __pragma(pack(pop))
#else                                   /* end of _MSC_VER */
    #error "Unsupported Compiler in Simulator"
#endif


#endif  /* _KAL_GENERAL_TYPES_H */


