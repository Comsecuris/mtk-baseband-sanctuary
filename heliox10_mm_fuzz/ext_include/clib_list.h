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
 *   clib_list.h
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *   C library function support level list 
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
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
 
 
/* Don't direct include this file. You should include kal_release.h. */
/* functions is tagged by:
 *    NOTSUPPORT_FUNCTION: NOT SUPPORT, that function is not allowed to be used
 *    INIT_NOTSUPPORT_FUNCTION: NOT INIT TIME, not used in initialize phase
 *    none of above 2: that functions is safe to be used in MAUI
 *    LINKTIME_CHECKING: this not support function will be check in link time
 */
#ifndef WANT_CLIB_LIST
#error "Do you really want this file"
#endif

#if defined(__GNUC__) 
#define __NOT_USED_SECTION __attribute__((section("SHOULD_NOT_USED_FUNCTION")))
#else
#define __NOT_USED_SECTION
#endif

/* in alloca.h ****************************************************************/
#if defined(__GNUC__)
__NOT_USED_SECTION void *alloca(size_t size) NOTSUPPORT_FUNCTION LINKTIME_CHECKING;
#else
void *__alloca(size_t size) NOTSUPPORT_FUNCTION LINKTIME_CHECKING;
#endif

/* in locale.h ****************************************************************/
#if 0
/* under construction !*/
#endif /* 0 */

/* in signal.h ****************************************************************/
__NOT_USED_SECTION void (*signal (int sig, void (* func )(int)))(int) NOTSUPPORT_FUNCTION LINKTIME_CHECKING;
__NOT_USED_SECTION int raise(int sig) NOTSUPPORT_FUNCTION LINKTIME_CHECKING;

/* in stdio.h *****************************************************************/
__NOT_USED_SECTION int remove(const char * filename) NOTSUPPORT_FUNCTION LINKTIME_CHECKING;
__NOT_USED_SECTION int rename(const char * old, const char * newname) NOTSUPPORT_FUNCTION LINKTIME_CHECKING;
__NOT_USED_SECTION FILE *tmpfile(void) NOTSUPPORT_FUNCTION LINKTIME_CHECKING;
__NOT_USED_SECTION char *tmpnam(char * s) NOTSUPPORT_FUNCTION LINKTIME_CHECKING;


/* in stdlib.h ****************************************************************/
__NOT_USED_SECTION void *calloc(size_t nmemb, size_t size) NOTSUPPORT_FUNCTION;
__NOT_USED_SECTION void free(void * ptr) NOTSUPPORT_FUNCTION;
__NOT_USED_SECTION void *malloc(size_t size) NOTSUPPORT_FUNCTION;
__NOT_USED_SECTION void *realloc(void * ptr, size_t size) NOTSUPPORT_FUNCTION;
__NOT_USED_SECTION int atexit(void (* func)(void)) NOTSUPPORT_FUNCTION; /* C++ library */
/*Yinli: reslove building for GCC: 'noreturn' function does return.*/
#if defined(__GNUC__)
__NOT_USED_SECTION void exit(int status) NOTSUPPORT_FUNCTION;
__NOT_USED_SECTION void _Exit(int status) NOTSUPPORT_FUNCTION;
#else
__NOT_USED_SECTION void exit(int status) NOTSUPPORT_FUNCTION  LINKTIME_CHECKING ;
__NOT_USED_SECTION void _Exit(int status) NOTSUPPORT_FUNCTION   LINKTIME_CHECKING  ;
#endif
__NOT_USED_SECTION char *getenv(const char * name) NOTSUPPORT_FUNCTION; /* C++ library */
__NOT_USED_SECTION int  system(const char * string) NOTSUPPORT_FUNCTION  LINKTIME_CHECKING;

/* in string.h ****************************************************************/
__NOT_USED_SECTION char *strtok(char * __restrict s1, const char * __restrict s2) NOTSUPPORT_FUNCTION LINKTIME_CHECKING;

/* in time.h ******************************************************************/
struct tm;
__NOT_USED_SECTION char *asctime(const struct tm * timeptr) NOTSUPPORT_FUNCTION LINKTIME_CHECKING;
__NOT_USED_SECTION char *ctime(const time_t * timer) NOTSUPPORT_FUNCTION LINKTIME_CHECKING;
__NOT_USED_SECTION struct tm *gmtime(const time_t * timer) NOTSUPPORT_FUNCTION LINKTIME_CHECKING;
__NOT_USED_SECTION struct tm *localtime(const time_t * timer) NOTSUPPORT_FUNCTION LINKTIME_CHECKING;

#if !defined(__SUPPORT_CLIB_TIME__)
__NOT_USED_SECTION time_t time(time_t *t) NOTSUPPORT_FUNCTION LINKTIME_CHECKING;
__NOT_USED_SECTION char * asctime_r(const struct tm * tim_p, char *res) NOTSUPPORT_FUNCTION LINKTIME_CHECKING;
__NOT_USED_SECTION struct tm * gmtime_r(const time_t *tim_p, struct tm *res) NOTSUPPORT_FUNCTION LINKTIME_CHECKING;
__NOT_USED_SECTION struct tm * localtime_r(const time_t *tim_p, struct tm *res) NOTSUPPORT_FUNCTION LINKTIME_CHECKING;
__NOT_USED_SECTION char * ctime_r(const time_t *tim_p, char *res) NOTSUPPORT_FUNCTION LINKTIME_CHECKING;
#endif


