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
 *   kal_public_api.h
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *   This file provides KAL public API prototypes
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
 ****************************************************************************/

#ifndef _KAL_PUBLIC_API_H
#define _KAL_PUBLIC_API_H

/*******************************************************************************
 * Common Header File Include
 *******************************************************************************/
#ifndef GEN_FOR_PC
#include <stdio.h>
#include <string.h>
#endif

#include "kal_general_types.h"
#include "kal_public_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/* DOM-NOT_FOR_SDK-BEGIN */
/*******************************************************************************
 * Category 1 : StdLib-like Function
 *******************************************************************************/
INLINE_MODIFIER INLINE void * kal_mem_cpy(void* dest, const void* src, kal_uint32 size)
{
    return memcpy ( dest, src, size );
}

INLINE_MODIFIER INLINE void * kal_mem_set(void* dest, kal_int32 value, kal_uint32 size)
{
    return memset ( dest, value, size );
}

INLINE_MODIFIER INLINE kal_int32 kal_mem_cmp(const void* src1, const void* src2, kal_uint32 size)
{
    return memcmp ( src1, src2, size );
}

INLINE_MODIFIER INLINE void * kal_mem_bwcpy(void* dest, const void* src, kal_uint32 size)
{
    char *destaddr = (char*)dest+(size-1);
    char const *srcaddr = (char*)src+(size-1);
    while (size-- > 0) *destaddr-- = *srcaddr--;
    return destaddr;
}

#if defined(KAL_ON_OSCAR)
#define kal_snprintf _snprintf
#else
#define kal_snprintf snprintf
#endif

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  sprintf
 * DESCRIPTION
 *  sprintf accepts a series of arguments, applies to each a format specifier from *format,
 *  and writes the formatted data to buffer str, and a terminating NUL is output.
 * PARAMETERS
 *  str:             [IN] destination buffer
 *  format:          [IN] specify the arguments output format
 *  ...:             [IN] variable-parameter, a series of arguments
 * NOTE
 *  number of variable-parameters must be less than or equal to 20, if more paramters are checked, will assert.
 *  this limitation is also apply to all sprintf/sscanf family functions, that is sprintf/snprintf/vsprintf/vsnprintf/sscanf/vsscanf
 * RETURN VALUES
 *  the number of bytes in the output string, except the concluding NUL is not counted.  
 ******************************************************************************/
#define kal_sprintf sprintf

extern kal_char *kal_strtok_r(kal_char *string, const kal_char *seperators, kal_char **ppLast);

#define kal_toWCHAR(asciiString) L##asciiString

/*************************************************************************
* FUNCTION
*  kal_itoa
*
* DESCRIPTION
*  converts integers to string in various radixes
*
* PARAMETERS
*  value	-  integer need to convert
*  str      -  buffer to save convert result
*  radix	-  the base of the integer, like 2,10,16
* RETURNS
*  return the str buffer address
*
*************************************************************************/
extern char *kal_itoa(int value, char *str, int radix);

/*
 * 16bits string operations
 */
extern int kal_wstrlen(const WCHAR *wstr);
extern WCHAR *kal_wstrcpy(WCHAR *to, const WCHAR *from);
extern WCHAR *kal_wstrncpy(WCHAR *to, const WCHAR *from, int n);
extern int kal_wstrcmp(const WCHAR *s1, const WCHAR *s2);
extern int kal_wstrncmp(const WCHAR *s1, const WCHAR *s2, int n);
extern WCHAR *kal_wstrcat(WCHAR *s1, const WCHAR *s2);
extern WCHAR *kal_wstrncat(WCHAR *s1, const WCHAR *s2, int n);
extern WCHAR *kal_wstrchr(const WCHAR *s, int c);
extern WCHAR *kal_wstrrchr(const WCHAR *str, int ch);

/*
 * dual 8bits string operations
 */
extern int kal_dchar_strlen(const char *wstr);
extern char *kal_dchar_strcpy(char *to, const char *from);
extern char *kal_dchar_strncpy(char *to, const char *from, int n);
extern int kal_dchar_strcmp(const char *s1, const char *s2);
extern int kal_dchar_strncmp(const char *s1, const char *s2, int n);
extern char *kal_dchar_strcat(char *s1, const char *s2);
extern char *kal_dchar_strncat(char *s1, const char *s2, int n);
extern char *kal_dchar_strchr(const char *s, int c);
extern char *kal_dchar_strrchr(const char *str, int ch);
extern void kal_dchar2char(WCHAR *outstr, char* tostr);
extern void kal_wsprintf(WCHAR *outstr, char *fmt,...);


#if !defined(GEN_FOR_PC)

/*************************************************************************
* FUNCTION
*  time
*
* DESCRIPTION
*  time() return current calendar time as a value of type time_t .It stores the same value at 
*  parameter t unless the argument is NULL.  The value represents the number of seconds 
*  since 00:00 hours, Jan 1, 1970 UTC   (i.e., the current unix timestamp).
*
* PARAMETERS
*  t	-  pointer to an object of type time_t to store the current time.
*         You can just input NULL, the function still return a value of type time_t with the result.
*
* RETURNS
*  The current calendar time as a value of type time_t .
*
* NOTE
*  Only be supported in limited projects. If it is not supported, build fail is happened.
*
*************************************************************************/
extern time_t time(time_t *t);



/*************************************************************************
* FUNCTION
*  gmtime_r
*
* DESCRIPTION
*  Uses the value pointed by tim_p to fill the tm structure pointed by res with the values 
*  that represent the corresponding time, expressed as UTC time (i.e., the time at the 
*  GMT timezone). If tim_p or res is NULL, NULL will be returned and the content of res
*  will not be changed.
*
* PARAMETERS
*  tim_p - pointer to an object of type time_t that contains a time value.
*  res    - pointer to an object of type tm to store the result converted by gmtime_r
*
* RETURNS
*  A pointer to inputted tm structure res with its members filled with the values that 
*  correspond to the UTC time representation of tim_p.
*  Return NULL if tim_p or res is NULL.
*
* NOTE
*  Only be supported in limited projects. If it is not supported, build fail is happened.
*
* SEE ALSO
*  time, localtime_r
*
*************************************************************************/
extern struct tm * gmtime_r(const time_t *tim_p, struct tm *res);



/*************************************************************************
* FUNCTION
*  localtime_r
*
* DESCRIPTION
*  Uses the value pointed by tim_p to fill the tm structure pointed by res with the values that 
*  represent the corresponding time, expressed for the local timezone.
*  Note that localtime() may not available due to timezone is not updated within bootup 10 
*  seconds. If it is happened, the result of localtime_r() is euqal to gmtime_r(). (i.e. the returned
*  tm structure represents the corresponding UTC time.
*
* PARAMETERS
*  tim_p - pointer to an object of type time_t that contains a time value.
*  res    - pointer to an object of type tm to store the result converted by localtime_r()
*
* RETURNS
*  A pointer to inputted tm structure res with its members filled with the values that 
*  correspond to the local time representation of tim_p if localtime_r() is available. if localtime_r()
*  is not available, the tm structure represents the corresponding UTC time.
*  Return NULL if tim_p or res is NULL.
*
* NOTE
*   Only be supported in limited projects. If it is not supported, build fail is happened.
*
* SEE ALSO
*  time, gmtime_r
*
*************************************************************************/
struct tm * localtime_r(const time_t *tim_p, struct tm *res);




/*************************************************************************
* FUNCTION
*  asctime_r
*
* DESCRIPTION
*  Interprets the contents of the tm structure pointed by tim_p as a calendar time and 
*  converts it to a C-string containing a human-readable version of the corresponding 
*  date and time. The returned string has the following format:
*       Www Mmm dd hh:mm:ss yyyy
*  Where Www is the weekday, Mmm the month (in letters), dd the day of the month, 
*  hh:mm:ss the time, and yyyy the year. The string is followed by a new-line character 
*  ('\n') and terminated with a null-character.
*  If tim_p or res is NULL, NULL will be returned and the content of res will not be changed.
*
* PARAMETERS
*  tim_p - pointer to a tm structure that contains a calendar time broken down into its 
*              components (see struct tm).
*  res    - a pointer to the string for containing result converted by asctime_r.
*             The length of the string shouls larger than 26.
*
* RETURNS
*  A pointer to inputted string res containing the date and time information in a 
*  human-readable format.
*  Return NULL if tim_p or res is NULL.
*
* NOTE
*  Only be supported in limited projects. If it is not supported, build fail is happened.
*
* SEE ALSO
*  time, gmtime_r, localtime_r, ctime_r
*
*************************************************************************/
char * asctime_r(const struct tm * tim_p, char *res);


/*************************************************************************
* FUNCTION
*  ctime_r
*
* DESCRIPTION
*  Interprets the contents of the tm structure pointed by tim_p as a calendar time and
*  converts it to a C-string containing a human-readable version of the corresponding
*  date and time, in terms of local time. The returned string has the following format:
*       Www Mmm dd hh:mm:ss yyyy
*  Where Www is the weekday, Mmm the month (in letters), dd the day of the month, 
*  hh:mm:ss the time, and yyyy the year. The string is followed by a new-line character 
*  ('\n') and terminated with a null-character.
*  Note that ctime_r() may not available due to timezone is not updated within bootup 10 
*  seconds. If it is happened, the result of ctime_r(), asctime_r(localtime_r()), is euqal to 
*  asctime_r(gmtime_r()).
* 
* PARAMETERS
*  tim_p - pointer to a tm structure that contains a calendar time broken down into its 
*              components (see struct tm).
*  res    - a pointer to the string for containing result converted by ctime_r.
*             The length of the string shouls larger than 26.
*
* RETURNS
*  A pointer to inputted string res containing the date and time information in a 
*  human-readable format.
*  Return NULL if tim_p or res is NULL.
*
* NOTE
*  Only be supported in limited projects. If it is not supported, build fail is happened.
*
* SEE ALSO
*  time, gmtime_r, localtime_r, asctime_r
*
*************************************************************************/
char * ctime_r(const time_t *tim_p, char *res);

#endif /* !defined(GEN_FOR_PC) */


/*******************************************************************************
 * Category 2 : Query Functions for Initialize and States
 *******************************************************************************/

 /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_query_systemInit
 * DESCRIPTION
 *  query whether the system is in initialization phase.
 * PARAMETERS
 *  N/A
 * RETURN VALUES
 *  KAL_TRUE: system is in initialization phase.
 *  KAL_FALSE: system is not in initialization phase.
 ******************************************************************************/
kal_bool kal_query_systemInit(void);

 /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_query_boot_mode
 * DESCRIPTION
 *  query system boot mode.
 * PARAMETERS
 *  N/A
 * SEE ALSO
 *  boot_mode_type
 ******************************************************************************/
INLINE_MODIFIER INLINE boot_mode_type kal_query_boot_mode(void)
{
    extern boot_mode_type system_boot_mode;
    return system_boot_mode;
}

/* DOM-NOT_FOR_SDK-END */

/*******************************************************************************
 * Category 3 : LISR, HISR and TASK functions
 *******************************************************************************/

 /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_get_current_thread_ID
 * DESCRIPTION
 *  get current thread identity, which is a unique pointer for each thread.
 * PARAMETERS
 *  N/A
 * RETURNS
 *  current thread identity.
 * NOTE
 *  thread is defined as task or HISR.
 ******************************************************************************/
void *kal_get_current_thread_ID(void);
 /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_sleep_task
 * DESCRIPTION
 *  put the task into sleep for a specified duration which is expressed in terms
 *  of system tick.
 * PARAMETERS
 *  time_in_ticks: [IN] how many system ticks to sleep.
 * RETURNS
 *  N/A
 * NOTE
 *  N/A
 * SEE ALSO
 *  KAL_MILLISECS_PER_TICK
 ******************************************************************************/
void kal_sleep_task(kal_uint32 time_in_ticks);
 /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_get_current_task
 * DESCRIPTION
 *  get current task identity.
 * PARAMETERS
 *  N/A
 * RETURNS
 *  current task identity.
 * SEE ALSO
 *  kal_get_current_task_index
 ******************************************************************************/
kal_taskid kal_get_current_task(void);
 /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_get_current_task_priority
 * DESCRIPTION
 *  get current task priority.
 * PARAMETERS
 *  N/A
 * RETURNS
 *  current task priority.
 ******************************************************************************/
kal_uint32 kal_get_current_task_priority(void);
 
 /*************************************************************************
 * FUNCTION
 *	 kal_get_task_status
 *
 * DESCRIPTION
 *	 This routine is to get the task's status.
 *
 * PARAMETERS
 *	 taskid : task id(pointer points to task control block
 *
 * RETURNS
 *	 task's current status
 *
 * GLOBALS AFFECTED
 *
 *************************************************************************/
kal_task_status kal_get_task_status(kal_taskid taskid);

 /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_set_active_module_id
 * DESCRIPTION
 *  set active module in current task.
 * PARAMETERS
 *  module_id: [IN] active module in current task.
 * RETURNS
 *  N/A
 * NOTE
 *  (1)This API must be called before kal_get_active_module_id(). So, the recommended place to call it
 *     is in task main function, immediately after get a ILM message.
 * SEE ALSO
 *  kal_get_active_module_id
 ******************************************************************************/
extern void kal_set_active_module_id(module_type module_id);

 /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_get_active_module_id
 * DESCRIPTION
 *  get active module in current task.
 * PARAMETERS
 *  N/A
 * RETURNS
 *  active module in current task.
 * NOTE
 *  (1)This API return the last value set by kal_set_active_module_id().
 * SEE ALSO
 *  kal_set_active_module_id
 ******************************************************************************/
extern module_type kal_get_active_module_id(void);

 /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_get_task_by_moduleID
 * DESCRIPTION
 *  get taskid from task index.
 * PARAMETERS
 *  index: [IN] target task index.
 * RETURNS
 *  Return corresponding taskid. If the target task doesn't exist, return NULL.
 * SEE ALSO
 *  kal_get_task_index
 ******************************************************************************/
extern kal_taskid kal_get_task_by_moduleID(module_type modele_id);

/* DOM-NOT_FOR_SDK-BEGIN */
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_get_task_total_number
 * DESCRIPTION
 *  query total task index number.
 * PARAMETERS
 *  NA.
 * RETURNS
 *  Return total task index number.
 ******************************************************************************/
extern kal_uint32 kal_get_task_total_number(void);

  /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_get_send_msg_module_id_total_number
 * DESCRIPTION
 *  query total module id number that can send message.
 * PARAMETERS
 *  NA.
 * RETURNS
 *  Return total module id number that can send message.
 ******************************************************************************/
 extern kal_uint32 kal_get_send_msg_module_id_total_number(void);
/* DOM-NOT_FOR_SDK-END */

/* DOM-NOT_FOR_SDK-BEGIN */
 
 /*******************************************************************************
 * <GROUP Functions>
 * 
 * FUNCTION
 *  kal_priority_transfer
 * DESCRIPTION
 *  transfer current task's priority to destination task specified by dummy module 
 *  id.
 * PARAMETERS
 *  dest_mod_id: [IN] specified task's dummy module id.
 * RETURNS
 *  Return KAL_SUCCESS if no error happen.
 ******************************************************************************/
extern kal_status kal_priority_transfer(kal_uint32 dest_mod_id);

 /*******************************************************************************
 * <GROUP Functions>
 * 
 * FUNCTION
 *  kal_priority_revoke
 * DESCRIPTION
 *  revoke current task's priority from destination task specified by dummy module 
 *  id.
 * PARAMETERS
 *  dest_mod_id: [IN] specified task's dummy module id.
 * RETURNS
 *  Return KAL_SUCCESS if no error happen.
 ******************************************************************************/
extern kal_status kal_priority_revoke(kal_uint32 dest_mod_id);

 /*******************************************************************************
 * <GROUP Functions>
 * 
 * FUNCTION
 *  kal_task_mode_register
 * DESCRIPTION
 *  register task information to system before use task mode switch API
 * PARAMETERS
 *  none
 * RETURNS
 *  Return KAL_SUCCESS if no error happen.
 *	Return KAL_ERROR if task has already registered.
 ******************************************************************************/
 extern kal_status kal_task_mode_register(void);

 /*******************************************************************************
 * <GROUP Functions>
 * 
 * FUNCTION
 *  kal_task_mode_switch
 * DESCRIPTION
 *  switch task to the mode specified.
 * PARAMETERS
 *  dest_mod_id:	[IN] specified task's dummy module id
 *	mode:			[IN] specified the mode task switch to.
 *					1: the first priority mode;
 *					0: the second priority mode;
 * RETURNS
 *  Return KAL_SUCCESS if no error happen.
 ******************************************************************************/
extern kal_status kal_task_mode_switch(kal_uint32 dest_mod_id,kal_uint32 mode);


 /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_get_current_hisr_index
 * DESCRIPTION
 *  get current HISR index.
 * PARAMETERS
 *  N/A
 * RETURNS
 *  current HISR index.
 * NOTE
 *  (1)This API must be called from HISR.
 ******************************************************************************/
extern kal_uint32 kal_get_current_hisr_index(void);

/*************************************************************************
* <GROUP Functions>
*
* FUNCTION
*  kal_check_stack
*
* DESCRIPTION
*   This routine is to check whether the start of current thread stack is corrupted.
*   If so, the system enter fatal error handling.
*
* PARAMETERS
*  N/A
* RETURNS
*
* GLOBALS AFFECTED
*
*************************************************************************/
void kal_check_stack(void);

 /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_activate_hisr
 * DESCRIPTION
 *  activate specified HISR.
 * PARAMETERS
 *  ext_hisr_id: [IN] HISR pointer.
 * RETURNS
 *  N/A
 ******************************************************************************/
void kal_activate_hisr(kal_hisrid ext_hisr_id);
 /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_if_hisr
 * DESCRIPTION
 *  Identify if the current execution unit is a HISR.
 * PARAMETERS
 *  N/A
 * RETURNS
 *  KAL_FALSE if the current execution unit is a task, and KAL_TRUE if the current execution unit is a HISR.
 * SEE ALSO
 *  kal_if_lisr
 ******************************************************************************/
kal_bool kal_if_hisr(void);
 /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_if_lisr
 * DESCRIPTION
 *  Identify if the current execution unit is a LISR.
 * PARAMETERS
 *  N/A
 * RETURNS
 *  KAL_FALSE if the current execution unit is a task or HISR, and KAL_TRUE if the current execution unit is a LISR.
 * SEE ALSO
 *  kal_if_hisr
 ******************************************************************************/
kal_bool kal_if_lisr(void);

/* DOM_NOT_FOR_SDK-END */

/*******************************************************************************
 * Category 4 : Message Passing and Queue
 *******************************************************************************/
/* DOM-NOT_FOR_SDK-BEGIN */

extern void* construct_int_local_para(kal_uint16 local_para_size, kal_uint32 auto_reset,
                                      const kal_char* file_ptr, kal_uint32 line);
extern void free_int_local_para(local_para_struct *local_para_ptr, const kal_char* file, kal_uint32 line);
extern void free_int_local_para_r(local_para_struct *local_para_ptr, const kal_char* file, kal_uint32 line);
extern void* construct_int_peer_buff(kal_uint16 pdu_len, kal_uint16 header_len, kal_uint16 tail_len,
                                     const kal_char* file_name_ptr, kal_uint32 line);
extern void free_int_peer_buff(peer_buff_struct *pdu_ptr, const kal_char* file, kal_uint32 line);
extern void free_int_peer_buff_r(peer_buff_struct *pdu_ptr, const kal_char* file, kal_uint32 line);
extern void destroy_int_ilm(ilm_struct *ilm_ptr, const kal_char* file_name, kal_uint32 line);

#if defined(DEBUG_KAL) && defined(DEBUG_BUF2)
#define __construct_local_para(local_para_size, direction) \
            construct_int_local_para(local_para_size, ((kal_uint32)(direction) & (kal_uint32)TD_RESET)? 1 : 0, __FILE__, __LINE__)
#define __free_local_para(local_para) free_int_local_para(local_para, __FILE__, __LINE__)
#define __free_local_para_r(local_para) free_int_local_para_r(local_para, __FILE__, __LINE__)
#define __construct_peer_buff(pdu_len, header_len, tail_len, direction) \
            construct_int_peer_buff(pdu_len, header_len, tail_len, __FILE__, __LINE__)
#define __free_peer_buff(peer_buff) free_int_peer_buff(peer_buff, __FILE__, __LINE__)
#define __free_peer_buff_r(peer_buff) free_int_peer_buff_r(peer_buff, __FILE__, __LINE__)
#else /* !DEBUG_KAL || !DEBUG_BUF2 */
#define __construct_local_para(local_para_size, direction) \
            construct_int_local_para(local_para_size, ((kal_uint32)(direction) & (kal_uint32)TD_RESET)? 1 : 0, NULL, 0)
#define __free_local_para(local_para) free_int_local_para(local_para, NULL, 0)
#define __free_local_para_r(local_para) free_int_local_para_r(local_para, NULL, 0)
#define __construct_peer_buff(pdu_len, header_len, tail_len, direction) \
            construct_int_peer_buff(pdu_len, header_len, tail_len, NULL, 0)
#define __free_peer_buff(peer_buff) free_int_peer_buff(peer_buff, NULL, 0)
#define __free_peer_buff_r(peer_buff) free_int_peer_buff_r(peer_buff, NULL, 0)
#endif
/* DOM-NOT_FOR_SDK-END */
/* DOM-NOT_FOR_SDK-BEGIN */
 /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  construct_local_para
 * DESCRIPTION
 *  allocate a local_para structure which has local_para_size bytes including LOCAL_PARA_HDR.
 * PARAMETERS
 *  local_para_size: [IN] local_para structure size, this size includes LOCAL_PARA_HDR header,
 *                   so the minimum size is sizeof(LOCAL_PARA_HDR) which imply the pdu part is 0 byte.
 *  direction: [IN] a bitmask, each bit is defined as following values:
 *             0 - nothing.
 *             TD_RESET - to zero-initialize the pdu in this local_para structure.
 * RETURNS
 *  a local_para structure pointer. System enter fatal error handling if no enough memory.
 * NOTE
 *  (1) the prototype of this API is:
 *       void* construct_local_para(kal_uint16 local_para_size, transfer_direction direction);
 *  (2) local_para structure is a user-defined structure has a predefined header LOCAL_PARA_HDR
 *      embedded in front of it:
 *          struct bt_connected_info {
 *              LOCAL_PARA_HDR; // this field must be the first elements in structure
 *              // user-defined fields follows, pdu of this local_para structure
 *          };
 *      LOCAL_PARA_HDR is defined as:
 *          #define LOCAL_PARA_HDR       kal_uint8  ref_count; kal_uint8 lp_reserved; kal_uint16  msg_len;
 *      where msg_len is used to record the length of total structre including LOCAL_PARA_HDR,
 *      ref_count is used to record how many pointers reference to this structure, you must
 *      hold it on saving a private copy and free it after clear the private copy.
 *  (3) The initial reference count in local_para structure is 1. It is a common error to
 *      memset the whole structure to 0, if you want to zero-initialize pdu, pass TD_RESET
 *      in direction to do that.
 * SEE ALSO
 *  free_local_para, hold_local_para, destroy_ilm, get_local_para_ptr
 ******************************************************************************/
#define construct_local_para(local_para_size, direction) __construct_local_para(local_para_size, direction)
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  free_local_para
 * DESCRIPTION
 *  decrease the local_para strucutre reference count, free the local_para if it reach 0.
 * PARAMETERS
 *  local_para        : [IN] local_para structure pointer.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1)The prototype of this API is:
 *      void free_local_para(local_para_struct *local_para_ptr);
 *  (2)To pass user-defined local_para structure pointer to it, you need an explicit type-cast:
 *      free_local_para((local_para_struct *)ptr_to_bt_connected_info);
 * SEE ALSO
 *  construct_local_para, hold_local_para, free_local_para_r, destroy_ilm
 ******************************************************************************/
#define free_local_para(local_para) __free_local_para(local_para)
#define free_local_para_set_null(local_para) \
do { __free_local_para(local_para); local_para=NULL; } while(0)
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  free_local_para_r
 * DESCRIPTION
 *  decrease the local_para strucutre reference count, free the local_para if it reach 0.
 *  it's almost identical to free_local_para, except that free_local_para_r will disable irq during
 *  decrease reference count to avoid race condition.
 * PARAMETERS
 *  local_para        : [IN] local_para structure pointer.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1)The prototype of this API is:
 *      void free_local_para_r(local_para_struct *local_para_ptr);
 *  (2)To pass user-defined local_para structure pointer to it, you need an explicit type-cast:
 *      free_local_para_r((local_para_struct *)ptr_to_bt_connected_info);
 * SEE ALSO
 *  construct_local_para, hold_local_para, free_local_para, destroy_ilm
 ******************************************************************************/
#define free_local_para_r(local_para) __free_local_para_r(local_para)
#define free_local_para_r_set_null(local_para) \
do { __free_local_para_r(local_para); local_para=NULL; } while(0)
 /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  construct_peer_buff
 * DESCRIPTION
 *  allocate a peer_buff structure which has specified size in each part.
 * PARAMETERS
 *  pdu_len: [IN] pdu size.
 *  header_len: [IN] reserve size in header.
 *  tail_len: [IN] reserve size in tail.
 *  direction: [IN] ignored, use 0.
 * RETURNS
 *  a peer_buff structure pointer. System enter fatal error handling if no enough memory.
 * NOTE
 *  (1) the prototype of this API is:
 *       void* construct_peer_buff(kal_uint16 pdu_len, kal_uint16 header_len, kal_uint16 tail_len,
 *                                  transfer_direction direction);
 *  (2) peer_buff is a opaque type which has reference count. Please use related API to manipulate it.
 *  (3) The initial reference count in peer_buff structure is 1.
 *  (4) It will use the size (pdu_len + header_len + tail_len + 8) to allocate buffer from control buffer pool.
 * SEE ALSO
 *  free_peer_buff, hold_peer_buff, destroy_ilm, get_peer_buff_pdu, append_to_peer_buff,
 *  prepend_to_peer_buff, remove_head_of_peer_buff, remove_tail_of_peer_buff, update_peer_buff_header
 ******************************************************************************/
#define construct_peer_buff(pdu_len, header_len, tail_len, direction) \
            __construct_peer_buff(pdu_len, header_len, tail_len, direction)
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  free_peer_buff
 * DESCRIPTION
 *  decrease the peer_buff strucutre reference count, free the peer_buff if it reach 0.
 * PARAMETERS
 *  peer_buff        : [IN] peer_buff structure pointer.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1)The prototype of this API is:
 *      void free_peer_buff(peer_buff_struct *peer_buff_ptr);
 * SEE ALSO
 *  construct_peer_buff, free_peer_buff_r, hold_peer_buff, destroy_ilm, get_peer_buff_pdu, append_to_peer_buff,
 *  prepend_to_peer_buff, remove_head_of_peer_buff, remove_tail_of_peer_buff, update_peer_buff_header
 ******************************************************************************/
#define free_peer_buff(peer_buff) __free_peer_buff(peer_buff)
#define free_peer_buff_set_null(peer_buff) \
do { __free_peer_buff(peer_buff); peer_buff=NULL; } while(0)
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  free_peer_buff_r
 * DESCRIPTION
 *  decrease the peer_buff strucutre reference count, free the peer_buff if it reach 0.
 *  it's almost identical to free_peer_buff, except that free_peer_buff_r will disable irq during
 *  decrease reference count to avoid race condition.
 * PARAMETERS
 *  peer_buff        : [IN] peer_buff structure pointer.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1)The prototype of this API is:
 *      void free_peer_buff_r(peer_buff_struct *peer_buff_ptr);
 * SEE ALSO
 *  construct_peer_buff, free_peer_buff, hold_peer_buff, destroy_ilm, get_peer_buff_pdu, append_to_peer_buff,
 *  prepend_to_peer_buff, remove_head_of_peer_buff, remove_tail_of_peer_buff, update_peer_buff_header
 ******************************************************************************/
#define free_peer_buff_r(peer_buff) __free_peer_buff_r(peer_buff)
#define free_peer_buff_r_set_null(peer_buff) \
do { __free_peer_buff_r(peer_buff); peer_buff=NULL; } while(0)

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  hold_local_para
 * DESCRIPTION
 *  If local_para_ptr is not NULL, increment its reference counter by 1.
 * PARAMETERS
 *  local_para_ptr        : [IN] local_para structure pointer.
 * RETURN VALUES
 *  KAL_TRUE if local_para_ptr is not NULL pointer, otherwise, KAL_FALSE.
 * NOTE
 *  (1) To pass user-defined local_para structure pointer to it, you need an explicit type-cast:
 *      hold_local_para((local_para_struct *)ptr_to_bt_connected_info);
 * SEE ALSO
 *  construct_local_para, hold_local_para_r, free_local_para, destroy_ilm
 ******************************************************************************/
extern kal_bool hold_local_para( local_para_struct *local_para_ptr );
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  hold_local_para_r
 * DESCRIPTION
 *  If local_para_ptr is not NULL, increment its reference counter by 1.
 *  it's almost identical to hold_local_para, except that hold_local_para_r will disable irq during
 *  increment reference count to avoid race condition.
 * PARAMETERS
 *  local_para_ptr        : [IN] local_para structure pointer.
 * RETURN VALUES
 *  KAL_TRUE if local_para_ptr is not NULL pointer, otherwise, KAL_FALSE.
 * NOTE
 *  (1) To pass user-defined local_para structure pointer to it, you need an explicit type-cast:
 *      hold_local_para_r((local_para_struct *)ptr_to_bt_connected_info);
 * SEE ALSO
 *  construct_local_para, hold_local_para, free_local_para, free_local_para_r, destroy_ilm
 ******************************************************************************/
extern kal_bool hold_local_para_r(local_para_struct *local_para_ptr);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  get_local_para_ptr
 * DESCRIPTION
 *  retrieving start address & length of user-defined local_para structure.
 * PARAMETERS
 *  local_para_ptr        : [IN] local_para structure pointer.
 *  local_para_len_ptr    : [OUT] to store length. If it is NULL, the length is not stored.
 * RETURN VALUES
 *  start address of user-defined local_para structure, It's equal to local_para_ptr.
 * NOTE
 *  (1)To pass user-defined local_para structure pointer to it, you need an explicit type-cast:
 *      get_local_para_ptr((local_para_struct *)ptr_to_bt_connected_info, &len);
 * SEE ALSO
 *  construct_local_para
 ******************************************************************************/
void* get_local_para_ptr(local_para_struct *local_para_ptr, kal_uint16 *local_para_len_ptr);

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  hold_peer_buff
 * DESCRIPTION
 *  If peer_buff_ptr is not NULL, increment its reference counter by 1.
 * PARAMETERS
 *  peer_buff_ptr        : [IN] peer_buff structure pointer.
 * RETURN VALUES
 *  KAL_TRUE if peer_buff_ptr is not NULL pointer, otherwise, KAL_FALSE.
 * NOTE
 *  N/A
 * SEE ALSO
 *  construct_peer_buff, hold_peer_buff_r, free_peer_buff, destroy_ilm
 ******************************************************************************/
extern kal_bool hold_peer_buff( peer_buff_struct *peer_buff_ptr);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  hold_peer_buff_r
 * DESCRIPTION
 *  If peer_buff_ptr is not NULL, increment its reference counter by 1.
 *  it's almost identical to hold_peer_buff, except that hold_peer_buff_r will disable irq during
 *  increment reference count to avoid race condition.
 * PARAMETERS
 *  peer_buff_ptr        : [IN] peer_buff structure pointer.
 * RETURN VALUES
 *  KAL_TRUE if peer_buff_ptr is not NULL pointer, otherwise, KAL_FALSE.
 * NOTE
 *  N/A
 * SEE ALSO
 *  construct_peer_buff, hold_peer_buff, free_peer_buff, free_peer_buff_r, destroy_ilm
 ******************************************************************************/
extern kal_bool hold_peer_buff_r(peer_buff_struct *peer_buff_ptr);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  get_peer_buff_pdu
 * DESCRIPTION
 *  retrieving start address & length of pdu in peer buffer.
 * PARAMETERS
 *  peer_buff_ptr        : [IN] peer_buff structure pointer.
 *  length_ptr           : [OUT] to store pdu's length. If it is NULL, the length is not stored.
 * RETURN VALUES
 *  start address of pdu in peer buffer.
 * SEE ALSO
 *  construct_peer_buff, free_peer_buff, hold_peer_buff, destroy_ilm, append_to_peer_buff,
 *  prepend_to_peer_buff, remove_head_of_peer_buff, remove_tail_of_peer_buff, update_peer_buff_header
 ******************************************************************************/
void* get_peer_buff_pdu(peer_buff_struct *peer_buff_ptr, kal_uint16 *length_ptr);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  prepend_to_peer_buff
 * DESCRIPTION
 *  prepend data to head of peer_buff. On success, pdu length increases header_len bytes,
 *  and free space at head decreases header_len bytes.
 * PARAMETERS
 *  peer_buff_ptr        : [IN] peer_buff structure pointer.
 *  header_data_ptr      : [IN] data appended.
 *  header_len           : [IN] length of data appended.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  If the free head room is smaller than header_len, system enter fatal error handling.
 * SEE ALSO
 *  construct_peer_buff, free_peer_buff, hold_peer_buff, destroy_ilm, get_peer_buff_pdu,
 *  append_to_peer_buff, remove_head_of_peer_buff, remove_tail_of_peer_buff, update_peer_buff_header
 ******************************************************************************/
extern void prepend_to_peer_buff( peer_buff_struct *peer_buff_ptr,
                                  void *header_data_ptr,
                                  kal_uint16 header_len);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  append_to_peer_buff
 * DESCRIPTION
 *  append data to tail of peer_buff, On success, pdu length increases tail_len bytes,
 *  and free space at tail decreases tail_len bytes.
 * PARAMETERS
 *  peer_buff_ptr        : [IN] peer_buff structure pointer.
 *  tail_data_ptr        : [IN] data appended.
 *  tail_len             : [IN] length of data appended.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  If the free tail room is smaller than tail_len, system enter fatal error handling.
 * SEE ALSO
 *  construct_peer_buff, free_peer_buff, hold_peer_buff, destroy_ilm, get_peer_buff_pdu,
 *  prepend_to_peer_buff, remove_head_of_peer_buff, remove_tail_of_peer_buff, update_peer_buff_header
 ******************************************************************************/
extern void append_to_peer_buff( peer_buff_struct *peer_buff_ptr,
                                 void *tail_data_ptr,
                                 kal_uint16 tail_len);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  remove_head_of_peer_buff
 * DESCRIPTION
 *  remove data at head of peer_buff. On success, pdu length decreases head_len bytes,
 *  and free space at head increases head_len bytes.
 * PARAMETERS
 *  peer_buff_ptr        : [IN] peer_buff structure pointer.
 *  head_len             : [IN] length of data to remove.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1)If the pdu size is smaller than head_len, system enter fatal error handling.
 *  (2)This API replaces remove_hdr_of_peer_buff(). And remove_hdr_of_peer_buff() is deprecated,
 *     it will be removed from next release.
 * SEE ALSO
 *  construct_peer_buff, free_peer_buff, hold_peer_buff, destroy_ilm, get_peer_buff_pdu,
 *  prepend_to_peer_buff, append_to_peer_buff, remove_tail_of_peer_buff, update_peer_buff_header
 ******************************************************************************/
extern void remove_head_of_peer_buff(peer_buff_struct *peer_buff_ptr, kal_uint16 head_len);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  remove_tail_of_peer_buff
 * DESCRIPTION
 *  remove data at tail of peer_buff. On success, pdu length decreases tail_len bytes,
 *  and free space at tail increases tail_len bytes.
 * PARAMETERS
 *  peer_buff_ptr        : [IN] peer_buff structure pointer.
 *  tail_len             : [IN] length of data to remove.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  If the pdu size is smaller than tail_len, system enter fatal error handling.
 * SEE ALSO
 *  construct_peer_buff, free_peer_buff, hold_peer_buff, destroy_ilm, get_peer_buff_pdu,
 *  prepend_to_peer_buff, append_to_peer_buff, remove_head_of_peer_buff, update_peer_buff_header
 ******************************************************************************/
extern void remove_tail_of_peer_buff( peer_buff_struct *peer_buff_ptr,
                                      kal_uint16 tail_len);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  update_peer_buff_header
 * DESCRIPTION
 *  Reinitialize peer buffer, reset size of free header space, pdu, free tail space to new values.
 * PARAMETERS
 *  peer_buff_ptr        : [IN] peer_buff structure pointer.
 *  new_head_len         : [IN] new head size after update.
 *  new_pdu_len          : [IN] new pdu size after update.
 *  new_tail_len         : [IN] new tail size after update.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1)If total size is bigger than original size, system enter fatal error handling.
 * SEE ALSO
 *  construct_peer_buff, free_peer_buff, hold_peer_buff, destroy_ilm, get_peer_buff_pdu,
 *  prepend_to_peer_buff, append_to_peer_buff, remove_head_of_peer_buff, remove_tail_of_peer_buff
 ******************************************************************************/
extern void update_peer_buff_header(peer_buff_struct *peer_buff_ptr, kal_uint16 new_head_len,
                                    kal_uint16 new_pdu_len, kal_uint16 new_tail_len);

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_send_ext_queue
 * DESCRIPTION
 *  send a ILM message to tail of destination task's ext queue.
 * PARAMETERS
 *  ilm_ptr             : [IN] the ILM message to be sent.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1) The ILM messages is appended to tail of the queue.
 *  (2) If the destination queue is full, system enter fatal error handling.
 *  (3) The use of allocate_ilm()/cancel_ilm() is deprecated,
 *  (4) Recommend use msg_send() , msg_send6() series, use this function as 
 *      last choice for special condition
 * SEE ALSO
 *  msg_send_to_head, msg_send6, msg_send_to_head6
 ******************************************************************************/
kal_bool msg_send_ext_queue(ilm_struct *ilm_ptr);

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_send
 * DESCRIPTION
 *  send a ILM message to tail of destination task's queue.
 *  Refer to NOTE about which queue (extq or intq) the message sent to.
 * PARAMETERS
 *  ilm_ptr             : [IN] the ILM message to be sent.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1) This API select queue based on following criteria:
 *        a. If src_mod_id and dest_mod_id in ilm_ptr mapped to same task, and the
 *           internal queue of the task is not NULL, the message is sent to internal queue.
 *        b. Otherwise, the message is sent to external queue.
 *  (2) The ILM messages is appended to tail of the queue.
 *  (3) If the destination queue is full, system enter fatal error handling.
 *  (4) The use of allocate_ilm()/cancel_ilm() is deprecated,
 * SEE ALSO
 *  msg_send_to_head, msg_send6, msg_send_to_head6
 ******************************************************************************/
kal_bool msg_send(ilm_struct *ilm_ptr);

/*******************************************************************************
 * <GROUP Functions>
 * 
 * FUNCTION
 *  msg_send_adt
 * DESCRIPTION
 *  send a ILM message to tail of destination task's queue. 
 *  sender provide translator callback to translate user defined structure
 *  in ILM local/peer parameter to ADT for logging.
 *  sender provide free callback to free user defined structure in ILM 
 *  local/peer parameter when the ILM is trapped during UT.
 *  Refer to NOTE about which queue (extq or intq) the message sent to.
 * PARAMETERS
 *  ilm_ptr             : [IN] the ILM message to be sent.
 *  translator_cb       : [IN] translator callback to translate user defined structure to ADT
 *  free_cb             : [IN] free callback to free user defined structure
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1) This API select queue based on following criteria:
 *        a. If src_mod_id and dest_mod_id in ilm_ptr mapped to same task, and the 
 *           internal queue of the task is not NULL, the message is sent to internal queue.
 *        b. Otherwise, the message is sent to external queue.
 *  (2) The ILM messages is appended to tail of the queue.
 *  (3) If the destination queue is full, system enter fatal error handling.
 *  (4) This API replaces msg_send_ext_queue/msg_send_int_queue(). 
 *      They will be removed from next release.
 *  (5) The use of allocate_ilm()/cancel_ilm() is deprecated, 
 *      They will be removed from next release.
 *  (6) If using the msg_send_adt has error, replace msg_send_adt with msg_send
 *      and test again. If the msg_send is OK but msg_send_adt is not, please
 *      contact the adt provider(TST/DHL module owner)
 * SEE ALSO
 *  msg_send_to_head, msg_send6, msg_send_to_head6
 ******************************************************************************/
#ifdef __TST_MODULE__
kal_bool msg_send_adt(ilm_struct *ilm_ptr, translator_adt_enc_callback_t translator_cb, ilm_free_callback_t free_cb);
#else  /* else of __TST_MODULE__ */
#define msg_send_adt(ilm_ptr, translator_cb, free_cb) msg_send(ilm_ptr)
#endif /* end of "else of __TST_MODULE__" */

/******************************************************************************* 
 * <GROUP Functions> 
 * 
 * FUNCTION 
 *  msg_send_to_int_head 
 * DESCRIPTION 
 *  send a ILM message to head of destination task's internal queue. 
 * PARAMETERS 
 *  ilm_ptr             : [IN] the ILM message to be sent. 
 * RETURN VALUES 
 *  N/A 
 * NOTE 
 *  (1) If the ILM is sent to external queue, system enter fatal error handling.
 *      It uses similar logic as msg_send to select queue based on following criteria:
 *        a. If src_mod_id and dest_mod_id in ilm_ptr mapped to different tasks, 
 *           then enter error handling.
 *        b. Otherwise, the message is sent to head of internal queue.
 *  (2) If the destination queue is full, system enter fatal error handling.
 * SEE ALSO 
 *  msg_send_to_int_head6 
 ******************************************************************************/ 
kal_bool msg_send_to_int_head(ilm_struct *ilm_ptr); 

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_send_to_head
 * DESCRIPTION
 *  send a ILM message to head of destination task's external queue.
 * PARAMETERS
 *  ilm_ptr             : [IN] the ILM message to be sent.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1) If the ILM is sent to internal queue, system enter fatal error handling.
 *      It uses similar logic as msg_send to select queue based on following criteria:
 *        a. If src_mod_id and dest_mod_id in ilm_ptr mapped to same task, and the
 *           internal queue of the task is not NULL, then enter error handling.
 *        b. Otherwise, the message is sent to head of external queue.
 *  (2) If the destination queue is full, system enter fatal error handling.
 * SEE ALSO
 *  msg_send, msg_send6, msg_send_to_head6
 ******************************************************************************/
kal_bool msg_send_to_head(ilm_struct *ilm_ptr);

/******************************************************************************* 
 * <GROUP Functions> 
 * 
 * FUNCTION 
 *  msg_send_to_int_head6 
 * DESCRIPTION 
 *  send a ILM message to head of destination task's internal queue. 
 *  this function is the same as msg_send_to_int_head except assigning content of ilm directly.
 * PARAMETERS 
 *  src_mod_id           : [IN] source module id. 
 *  dest_mod_id          : [IN] destination module id. 
 *  sap_id               : [IN] service access point id. 
 *  msg_id               : [IN] message id. 
 *  local_para_ptr       : [IN] local_para structure pointer. 
 *  peer_buff_ptr        : [IN] peer_buff structure pointer. 
 * RETURN VALUES 
 *  N/A 
 * NOTE
 * SEE ALSO 
 *  msg_send_to_int_head 
 ******************************************************************************/ 
kal_bool msg_send_to_int_head6(module_type _src_mod_id, module_type _dest_mod_id, sap_type _sap_id, msg_type _msg_id, 
                           local_para_struct *_local_para_ptr, peer_buff_struct *_peer_buff_ptr);

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_send6
 * DESCRIPTION
 *  send a ILM message to tail of destination task's queue.
 *  Refer to NOTE about which queue (extq or intq) the message sent to.
 * PARAMETERS
 *  src_mod_id           : [IN] source module id.
 *  dest_mod_id          : [IN] destination module id.
 *  sap_id               : [IN] service access point id.
 *  msg_id               : [IN] message id.
 *  local_para_ptr       : [IN] local_para structure pointer.
 *  peer_buff_ptr        : [IN] peer_buff structure pointer.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1) This API select queue based on following criteria:
 *        a. If src_mod_id and dest_mod_id in ilm_ptr mapped to same task, and the
 *           internal queue of the task is not NULL, the message is sent to internal queue.
 *        b. Otherwise, the message is sent to external queue.
 *  (2) The ILM messages is appended to tail of the queue.
 *  (3) If the destination queue is full, system enter fatal error handling.
 *  (4) This API replaces msg_send_ext_queue/msg_send_int_queue().
 *  (5) The use of allocate_ilm()/cancel_ilm() is deprecated,
 * SEE ALSO
 *  msg_send, msg_send4, msg_send5, msg_send_to_head, msg_send_to_head6
 ******************************************************************************/
kal_bool msg_send6(module_type _src_mod_id, module_type _dest_mod_id, sap_type _sap_id, msg_type _msg_id,
                   local_para_struct *_local_para_ptr, peer_buff_struct *_peer_buff_ptr);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_send5
 * DESCRIPTION
 *  same with msg_send6 with _peer_buff_ptr = NULL.
 * NOTE
 * SEE ALSO
 *  msg_send, msg_send4, msg_send6
 ******************************************************************************/
kal_bool msg_send5(module_type _src_mod_id, module_type _dest_mod_id, sap_type _sap_id, msg_type _msg_id,
                   local_para_struct *_local_para_ptr);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_send4
 * DESCRIPTION
 *  same with msg_send6 with _local_para_ptr = NULL & _peer_buff_ptr = NULL.
 * SEE ALSO
 *  msg_send, msg_send5, msg_send6
 ******************************************************************************/
kal_bool msg_send4(module_type _src_mod_id, module_type _dest_mod_id, sap_type _sap_id, msg_type _msg_id);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_send_to_head6
 * DESCRIPTION
 *  send a ILM message to head of destination task's queue.
 * PARAMETERS
 *  src_mod_id           : [IN] source module id.
 *  dest_mod_id          : [IN] destination module id.
 *  sap_id               : [IN] service access point id.
 *  msg_id               : [IN] message id.
 *  local_para_ptr       : [IN] local_para structure pointer.
 *  peer_buff_ptr        : [IN] peer_buff structure pointer.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1) If the ILM is sent to internal queue, system enter fatal error handling.
 *      It uses same logic as msg_send to select queue based on following criteria:
 *        a. If src_mod_id and dest_mod_id in ilm_ptr mapped to same task, and the
 *           internal queue of the task is not NULL, the message is sent to internal queue.
 *        b. Otherwise, the message is sent to external queue.
 *  (2) If the destination queue is full, system enter fatal error handling.
 *  (3) This API replaces msg_send_ext_queue_to_head().
 *  (4) The use of allocate_ilm()/cancel_ilm() is deprecated,
 * SEE ALSO
 *  msg_send, msg_send6, msg_send_to_head
 ******************************************************************************/
kal_bool msg_send_to_head6(module_type _src_mod_id, module_type _dest_mod_id, sap_type _sap_id, msg_type _msg_id,
                           local_para_struct *_local_para_ptr, peer_buff_struct *_peer_buff_ptr);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_send_to_head5
 * DESCRIPTION
 *  same with msg_send_to_head6 with _peer_buff_ptr = NULL.
 * NOTE
 * SEE ALSO
 *  msg_send_to_head, msg_send_to_head4, msg_send_to_head6
 ******************************************************************************/
kal_bool msg_send_to_head5(module_type _src_mod_id, module_type _dest_mod_id, sap_type _sap_id, msg_type _msg_id,
                           local_para_struct *_local_para_ptr);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_send_to_head4
 * DESCRIPTION
 *  same with msg_send_to_head6 with _local_para_ptr = NULL & _peer_buff_ptr = NULL.
 * NOTE
 * SEE ALSO
 *  msg_send_to_head, msg_send_to_head5, msg_send_to_head6
 ******************************************************************************/
kal_bool msg_send_to_head4(module_type _src_mod_id, module_type _dest_mod_id, sap_type _sap_id, msg_type _msg_id);

/******************************************************************************
*
 * <GROUP Functions>
 * 
 * FUNCTION
 *  msg_send_inline6
 * DESCRIPTION
 *  send a inline-ILM message to tail of destination task's queue. 
 *  Refer to NOTE about which queue (extq or intq) the message sent to.
 * PARAMETERS
 *  src_mod_id           : [IN] source module id.
 *  dest_mod_id          : [IN] destination module id.
 *  sap_id               : [IN] service access point id.
 *  msg_id               : [IN] message id.
 *  data                 : [IN] data to be copy in inline-ILM. 
 *  datalen              : [IN] data length, it's maximum value is MSG_INLINE_ILM_MAX_PAYLOAD.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1) This API select queue based on following criteria:
 *        a. If src_mod_id and dest_mod_id in ilm_ptr mapped to same task, and the 
 *           internal queue of the task is not NULL, the message is sent to internal queue.
 *        b. Otherwise, the message is sent to external queue.
 *  (2) The ILM messages is appended to tail of the queue.
 *  (3) If the destination queue is full, system enter fatal error handling.
 *  (4) The inline data length specified by datalen is not recorded in destination ILM messages.
 *      Its user's responsibility to know what the inline data is.
 *  (5) The use of allocate_ilm()/cancel_ilm() is deprecated, 
 * SEE ALSO
 *  msg_send, msg_send6, msg_send_to_head6, msg_send_inline5, msg_send_inline_tp_head5, 
 *	msg_is_inline, msg_get_inline_data
 *  msg_send_inline6, msg_send_inline_to_head6, msg_send_8bytes_inline6, msg_send_8bytes_inline_to_head6
 *  msg_get_inline_4bytes_data1, msg_get_inline_4bytes_data2
 
******************************************************************************/
kal_bool msg_send_inline6(module_type src_mod, module_type dest_mod, sap_type sap_id, msg_type msg_id, void *data, kal_uint32 datalen);

/******************************************************************************
*
 * <GROUP Functions>
 * 
 * FUNCTION
 *  msg_send_inline_to_head6
 * DESCRIPTION
 *  send a ILM message to head of destination task's queue. 
 * PARAMETERS
 *  src_mod_id           : [IN] source module id.
 *  dest_mod_id          : [IN] destination module id.
 *  sap_id               : [IN] service access point id.
 *  msg_id               : [IN] message id.
 *  data                 : [IN] data to be copy in inline-ILM. 
 *  datalen              : [IN] data length, it's maximum value is MSG_INLINE_ILM_MAX_PAYLOAD.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1) If the ILM is sent to internal queue, system enter fatal error handling.
 *      It uses same logic as msg_send to select queue based on following criteria:
 *        a. If src_mod_id and dest_mod_id in ilm_ptr mapped to same task, and the 
 *           internal queue of the task is not NULL, the message is sent to internal queue.
 *        b. Otherwise, the message is sent to external queue.
 *  (2) If the destination queue is full, system enter fatal error handling.
 *  (3) The inline data length specified by datalen is not recorded in destination ILM messages.
 *      Its user's responsibility to know what the inline data is.
 *  (4) The use of allocate_ilm()/cancel_ilm() is deprecated, 
 * SEE ALSO
 *  msg_send, msg_send6, msg_send_to_head6, msg_send_inline5, msg_send_inline_tp_head5, 
 *	msg_is_inline, msg_get_inline_data
 *  msg_send_inline6, msg_send_inline_to_head6, msg_send_8bytes_inline6,msg_send_8bytes_inline_to_head6
 *  msg_get_inline_4bytes_data1, msg_get_inline_4bytes_data2
 
******************************************************************************/
kal_bool msg_send_inline_to_head6(module_type src_mod, module_type dest_mod, sap_type sap_id, msg_type msg_id, void *data, kal_uint32 datalen);


/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_send_inline5
 * DESCRIPTION
 *  send a inline-ILM message to tail of destination task's queue.
 *  Refer to NOTE about which queue (extq or intq) the message sent to.
 * PARAMETERS
 *  src_mod_id           : [IN] source module id.
 *  dest_mod_id          : [IN] destination module id.
 *  msg_id               : [IN] message id.
 *  data                 : [IN] data to be copy in inline-ILM.
 *  datalen              : [IN] data length, it's maximum value is MSG_INLINE_ILM_MAX_PAYLOAD.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1) This API select queue based on following criteria:
 *        a. If src_mod_id and dest_mod_id in ilm_ptr mapped to same task, and the
 *           internal queue of the task is not NULL, the message is sent to internal queue.
 *        b. Otherwise, the message is sent to external queue.
 *  (2) The ILM messages is appended to tail of the queue.
 *  (3) If the destination queue is full, system enter fatal error handling.
 *  (4) The inline data length specified by datalen is not recorded in destination ILM messages.
 *      Its user's responsibility to know what the inline data is.
 *  (5) The use of allocate_ilm()/cancel_ilm() is deprecated,
 * SEE ALSO
 *  msg_send, msg_send6, msg_send_to_head6, msg_send_inline5, msg_send_inline_tp_head5, 
 *	msg_is_inline, msg_get_inline_data
 *  msg_send_inline6, msg_send_inline_to_head6, msg_send_8bytes_inline6, msg_send_8bytes_inline_to_head6
 *  msg_get_inline_4bytes_data1, msg_get_inline_4bytes_data2
 
******************************************************************************/
#define msg_send_inline5(src_mod, dest_mod, msg_id, data, datalen) \
	msg_send_inline6(src_mod, dest_mod, INLINE_ILM_SAP, msg_id, data, datalen)
	
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_send_inline_to_head5
 * DESCRIPTION
 *  send a ILM message to head of destination task's queue.
 * PARAMETERS
 *  src_mod_id           : [IN] source module id.
 *  dest_mod_id          : [IN] destination module id.
 *  msg_id               : [IN] message id.
 *  data                 : [IN] data to be copy in inline-ILM.
 *  datalen              : [IN] data length, it's maximum value is MSG_INLINE_ILM_MAX_PAYLOAD.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1) If the ILM is sent to internal queue, system enter fatal error handling.
 *      It uses same logic as msg_send to select queue based on following criteria:
 *        a. If src_mod_id and dest_mod_id in ilm_ptr mapped to same task, and the
 *           internal queue of the task is not NULL, the message is sent to internal queue.
 *        b. Otherwise, the message is sent to external queue.
 *  (2) If the destination queue is full, system enter fatal error handling.
 *  (3) The inline data length specified by datalen is not recorded in destination ILM messages.
 *      Its user's responsibility to know what the inline data is.
 *  (4) The use of allocate_ilm()/cancel_ilm() is deprecated,
 * SEE ALSO
 *  msg_send, msg_send6, msg_send_to_head6, msg_send_inline5, msg_send_inline_tp_head5, 
 *	msg_is_inline, msg_get_inline_data
 *  msg_send_inline6, msg_send_inline_to_head6, msg_send_8bytes_inline6, msg_send_8bytes_inline_to_head6
 *  msg_get_inline_4bytes_data1, msg_get_inline_4bytes_data2
 
******************************************************************************/
#define msg_send_inline_to_head5(src_mod, dest_mod, sap_id, msg_id, data,datalen) \
	msg_send_inline_to_head6(src_mod, dest_mod, INLINE_ILM_SAP, msg_id, data, datalen)

/******************************************************************************
*
 * <GROUP Functions>
 * 
 * FUNCTION
 *  msg_send_8bytes_inline6
 * DESCRIPTION
 *  send a inline-ILM message to tail of destination task's queue. 
 *  Refer to NOTE about which queue (extq or intq) the message sent to.
 * PARAMETERS
 *  src_mod_id           : [IN] source module id.
 *  dest_mod_id          : [IN] destination module id.
 *  sap_id               : [IN] service access point id.
 *  msg_id               : [IN] message id.
 *  data1                : [IN] first 4-byte data to be copy in inline-ILM. 
 *  data2                : [IN] second 4-byte data to be copy in inline-ILM. 
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1) This API select queue based on following criteria:
 *        a. If src_mod_id and dest_mod_id in ilm_ptr mapped to same task, and the 
 *           internal queue of the task is not NULL, the message is sent to internal queue.
 *        b. Otherwise, the message is sent to external queue.
 *  (2) The ILM messages is appended to tail of the queue.
 *  (3) If the destination queue is full, system enter fatal error handling.
 *  (4) The use of allocate_ilm()/cancel_ilm() is deprecated, 
 *  (5) The inline data length is not recorded in destination ILM messages.
 *      Its user's responsibility to know what the inline data is.
 * SEE ALSO
 *  msg_send, msg_send6, msg_send_to_head6, msg_send_inline5,msg_send_inline_tp_head5, 
 *	msg_is_inline, msg_get_inline_data
 *  msg_send_inline6, msg_send_inline_to_head6, msg_send_8bytes_inline6, msg_send_8bytes_inline_to_head6
 *  msg_get_inline_4bytes_data1, msg_get_inline_4bytes_data2
 
******************************************************************************/
kal_bool msg_send_8bytes_inline6(module_type src_mod, module_type dest_mod,sap_type sap_id, msg_type msg_id, kal_uint32 data1, kal_uint32 data2);

/******************************************************************************
*
 * <GROUP Functions>
 * 
 * FUNCTION
 *  msg_send_8bytes_inline_to_head6
 * DESCRIPTION
 *  send a ILM message to head of destination task's queue. 
 * PARAMETERS
 *  src_mod_id           : [IN] source module id.
 *  dest_mod_id          : [IN] destination module id.
 *  sap_id               : [IN] service access point id.
 *  msg_id               : [IN] message id.
 *  data1                : [IN] first 4-byte data to be copy in inline-ILM. 
 *  data2                : [IN] second 4-byte data to be copy in inline-ILM. 
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1) If the ILM is sent to internal queue, system enter fatal error handling.
 *      It uses same logic as msg_send to select queue based on following criteria:
 *        a. If src_mod_id and dest_mod_id in ilm_ptr mapped to same task,and the 
 *           internal queue of the task is not NULL, the message is sent to internal queue.
 *        b. Otherwise, the message is sent to external queue.
 *  (2) If the destination queue is full, system enter fatal error handling.
 *  (3) The use of allocate_ilm()/cancel_ilm() is deprecated, 
 *  (4) The inline data length is not recorded in destination ILM messages.
 *      Its user's responsibility to know what the inline data is.
 * SEE ALSO
 *  msg_send, msg_send6, msg_send_to_head6, msg_send_inline5, msg_send_inline_tp_head5, 
 *	msg_is_inline, msg_get_inline_data
 *  msg_send_inline6, msg_send_inline_to_head6, msg_send_8bytes_inline6, msg_send_8bytes_inline_to_head6
 *  msg_get_inline_4bytes_data1, msg_get_inline_4bytes_data2
  
******************************************************************************/
kal_bool msg_send_8bytes_inline_to_head6(module_type src_mod, module_type dest_mod, sap_type sap_id, msg_type msg_id, kal_uint32 data1, kal_uint32 data2);

/******************************************************************************
*
 * <GROUP Functions>
 * 
 * FUNCTION
 *  msg_get_inline_4bytes_data1
 * DESCRIPTION
 *  Get the inline first 4-byte data value in ILM message. 
 * PARAMETERS
 *  ilm_ptr              : [IN] ILM message pointer.
 * RETURN VALUES
 *  First 4-byte data value. If it's not an inline-ILM, system enter fatal error handling.
 * NOTE
 *  (1) Users must pass a inline-ILM to this function.
 *  (2) The inline data length is not recorded in ILM messages.
 *      Its user's responsibility to know what the inline data is.
 *
 * SEE ALSO
 *  msg_send, msg_send6, msg_send_to_head6, msg_send_inline5, msg_send_inline_tp_head5, 
 *	msg_is_inline, msg_get_inline_data
 *  msg_send_inline6, msg_send_inline_to_head6, msg_send_8bytes_inline6,msg_send_8bytes_inline_to_head6
 *  msg_get_inline_4bytes_data1, msg_get_inline_4bytes_data2
 
******************************************************************************/
kal_uint32 msg_get_inline_4bytes_data1(ilm_struct *ilm_ptr);

/******************************************************************************
*
 * <GROUP Functions>
 * 
 * FUNCTION
 *  msg_get_inline_4bytes_data2
 * DESCRIPTION
 *  Get the inline second 4-byte data value in ILM message. 
 * PARAMETERS
 *  ilm_ptr              : [IN] ILM message pointer.
 * RETURN VALUES
 *  Second 4-byte data value. If it's not an inline-ILM, system enter fatal error handling.
 * NOTE
 *  (1) Users must pass a inline-ILM to this function.
 *  (2) The inline data length is not recorded in ILM messages.
 *      Its user's responsibility to know what the inline data is.
 *
 * SEE ALSO
 *  msg_send, msg_send6, msg_send_to_head6, msg_send_inline5, msg_send_inline_tp_head5, 
 *	msg_is_inline, msg_get_inline_data
 *  msg_send_inline6, msg_send_inline_to_head6, msg_send_8bytes_inline6, msg_send_8bytes_inline_to_head6
 *  msg_get_inline_4bytes_data1, msg_get_inline_4bytes_data2
 
******************************************************************************/
kal_uint32 msg_get_inline_4bytes_data2(ilm_struct *ilm_ptr);

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_is_inline
 * DESCRIPTION
 *  judge whether is a inline-ILM or not.
 * PARAMETERS
 *  ilm_ptr              : [IN] ILM message pointer.
 * RETURN VALUES
 *  KAL_TRUE : this is a inline-ILM.
 *  KAL_FALSE : this isn't a inline-ILM.
 * NOTE
 *  (1) The prototype of this API is:
 *       kal_bool msg_is_inline(ilm_struct *ilm_ptr);
 *  (2) inline-ILM is identified by sap_id, always use this API to do this, never use
 *      sap_id comparison directly since this will change in future.
 * SEE ALSO
 *  msg_send, msg_send6, msg_send_to_head6, msg_send_inline5, msg_send_inline_tp_head5, 
 *	msg_is_inline, msg_get_inline_data
 *  msg_send_inline6, msg_send_inline_to_head6, msg_send_8bytes_inline6, msg_send_8bytes_inline_to_head6
 *  msg_get_inline_4bytes_data1, msg_get_inline_4bytes_data2
 
******************************************************************************/
#define msg_is_inline(ilm_ptr) (((ilm_ptr)->sap_id & INLINE_ILM_FLAG_SAP) ? KAL_TRUE : KAL_FALSE)

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_get_inline_data
 * DESCRIPTION
 *  Get the inline data pointer in ILM message.
 * PARAMETERS
 *  ilm_ptr              : [IN] ILM message pointer.
 * RETURN VALUES
 *  inline data pointer. If it's not an inline-ILM, system enter fatal error handling.
 * NOTE
 *  (1) Users must pass a inline-ILM to this function.
 *  (2) The inline data length is not recorded in ILM messages.
 *      Its user's responsibility to know what the inline data is.
 *
 * SEE ALSO
 *  msg_send, msg_send6, msg_send_to_head6, msg_send_inline5, msg_send_inline_tp_head5, 
 *	msg_is_inline, msg_get_inline_data
 *  msg_send_inline6, msg_send_inline_to_head6, msg_send_8bytes_inline6, msg_send_8bytes_inline_to_head6
 *  msg_get_inline_4bytes_data1, msg_get_inline_4bytes_data2
 ******************************************************************************/
void *msg_get_inline_data(ilm_struct *ilm_ptr);


#if defined(DEBUG_KAL) && defined(DEBUG_ITC)
#define __destroy_ilm(ilm_ptr) \
      destroy_int_ilm((ilm_ptr), (kal_char*)__FILE__, __LINE__ );
#else
#define __destroy_ilm(ilm_ptr) \
      destroy_int_ilm((ilm_ptr), NULL, 0);
#endif
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  destroy_ilm
 * DESCRIPTION
 *  destroy an ILM. It will free the local_para structure and peer_buff structure
 *  associated with this ILM.
 * PARAMETERS
 *  ilm_ptr        : [IN] ILM message pointer.
 * RETURN VALUES
 *  N/A
 * NOTE
 *  (1) The content pointed by ilm_ptr is not free.
 *  (2) This API replaces free_ilm(). And free_ilm() is deprecated,
 *     it will be removed from next release.
 * SEE ALSO
 *  msg_send, msg_receive_extq, msg_receive_intq
 ******************************************************************************/
#define destroy_ilm(ilm_ptr) __destroy_ilm(ilm_ptr)

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_receive_extq
 * DESCRIPTION
 *  receive a ILM message from current task's external queue.
 * PARAMETERS
 *  ilm_ptr        : [OUT] ILM message pointer.
 * RETURN VALUES
 *  KAL_TRUE: to indicate this operation finish successfully.
 * NOTE
 *  (1) If the external queue is not empty, this API return immediately.
 *      Otherwise, it will suspend to wait for the arrival of ILM message.
 *  (2) This API replaces receive_msg_ext_q(). And receive_msg_ext_q() is deprecated,
 *     it will be removed from next release.
 * SEE ALSO
 *  msg_send, msg_receive_intq, destroy_ilm
 ******************************************************************************/
kal_bool msg_receive_extq(ilm_struct *ilm_ptr);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_receive_extq_for_stack
 * DESCRIPTION
 *  receive a ILM message from current task's external queue used for stack sharing.
 * PARAMETERS
 *  ilm_ptr        : [OUT] ILM message pointer.
 * RETURN VALUES
 *  KAL_TRUE: to indicate this operation finish successfully.
 * NOTE
 *  (1) If the external queue is not empty, this API return immediately. 
 *      Otherwise, it will suspend to wait for the arrival of ILM message.
 *  (2) This API replaces receive_msg_ext_q(). And receive_msg_ext_q() is deprecated,
 *     it will be removed from next release.
 * SEE ALSO
 *  msg_send, msg_receive_intq, destroy_ilm
 ******************************************************************************/
kal_bool msg_receive_extq_for_stack(ilm_struct *ilm_ptr);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_receive_intq
 * DESCRIPTION
 *  receive a ILM message from current task's internal queue.
 * PARAMETERS
 *  ilm_ptr        : [OUT] ILM message pointer.
 * RETURN VALUES
 *  KAL_TRUE: ILM fetched.
 *  KAL_FALSE: internal queue is empty and no ILM is fetched.
 * NOTE
 *  This API replaces receive_msg_int_q(). And receive_msg_int_q() is deprecated,
 *     it will be removed from next release.
 * SEE ALSO
 *  msg_send, msg_receive_extq, destroy_ilm
 ******************************************************************************/
kal_bool msg_receive_intq(ilm_struct *ilm_ptr);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_get_task_extq_messages
 * DESCRIPTION
 *  get messages count in external queue of specified task by task index.
 * PARAMETERS
 *  tindex        : [IN] task index.
 * RETURN VALUES
 *  messages count, -1 if error happens.
 * NOTE
 *  (1)This API replaces msg_get_ext_queue_info(). And msg_get_ext_queue_info() is deprecated,
 *     it will be removed from next release.
 * SEE ALSO
 *  msg_get_extq_messages, msg_get_task_extq_capacity, msg_get_extq_capacity
 ******************************************************************************/
kal_int32 msg_get_task_extq_messages(module_type module_id);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_get_extq_messages
 * DESCRIPTION
 *  get messages count in external queue of current task.
 * PARAMETERS
 *  N/A
 * RETURN VALUES
 *  messages count, -1 if error happens.
 * SEE ALSO
 *  msg_get_task_extq_messages, msg_get_task_extq_capacity, msg_get_extq_capacity
 ******************************************************************************/
kal_int32 msg_get_extq_messages(void);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_get_task_extq_capacity
 * DESCRIPTION
 *  get capacity of external queue of specified task by task index.
 * PARAMETERS
 *  tindex        : [IN] task index.
 * RETURN VALUES
 *  capacity of target external queue, -1 if error happens.
 * NOTE
 *  (1)This API replaces msg_get_ext_queue_length(). And msg_get_ext_queue_length() is deprecated,
 *     it will be removed from next release.
 * SEE ALSO
 *  msg_get_task_extq_messages, msg_get_extq_messages, msg_get_extq_capacity
 ******************************************************************************/
kal_int32 msg_get_task_extq_capacity(module_type tmod);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  msg_get_extq_capacity
 * DESCRIPTION
 *  get capacity of external queue of current task.
 * PARAMETERS
 *  N/A
 * RETURN VALUES
 *  capacity of current task external queue, -1 if error happens.
 * SEE ALSO
 *  msg_get_task_extq_messages, msg_get_extq_messages, msg_get_task_extq_capacity
 ******************************************************************************/
kal_int32 msg_get_extq_capacity(void);

/* DOM-NOT_FOR_SDK-END */

/*******************************************************************************
 * Category 5 : Synchronous Mechanism : Mutex , Enhance Mutex , Semaphore and Event Group
 *******************************************************************************/


/*******************************************************************************
 * <GROUP Synchronous>
 *
 * FUNCTION
 *  kal_create_mutex
 * DESCRIPTION
 *  create a mutex.
 * PARAMETERS
 *  mutex_name  : [IN] mutex name. it's used for debug only, and only the
 *                first 8 characters retain.
 * RETURNS
 *  Success:        mutex pointer.
 *  Error:          system enter fatal error handling.
 * NOTE
 *  It is strongly suggested to call this function only in system initialization
 *  time, and the related data allocated for the mutex could not be freed
 *  once it is created.
 * SEE ALSO
 *  kal_take_mutex kal_give_mutex
 ******************************************************************************/
kal_mutexid kal_create_mutex(kal_char* mutex_name);
/*******************************************************************************
 * <GROUP Synchronous>
 *
 * FUNCTION
 *  kal_take_mutex
 * DESCRIPTION
 *  Obtains an instance of the specified mutex. If the mutex is taken already
 *  before this call, the function cannot be immediately satisfied, and caller
 *  task will be suspended until other task give the ownership to caller task.
 *  After the function returns, caller task is the only task held this mutex.
 * PARAMETERS
 *  mutex_ptr        : [IN] mutex pointer.
 * RETURNS
 *  N/A
 * NOTE
 *  (1)Mutex is not a recursive lock. If caller task already held this mutex,
 *     then caller task will suspend forever because any task won^t and can^t
 *     give up mutex^s ownership.
 *  (2)Mutex is a FIFO queue. If multiple tasks are waiting on a mutex, the
 *     first waiting task is selected to be the next owner.
 * SEE ALSO
 *  kal_create_mutex kal_give_mutex
 ******************************************************************************/
void kal_take_mutex(kal_mutexid mutex_ptr);
/*******************************************************************************
 * <GROUP Synchronous>
 *
 * FUNCTION
 *  kal_give_mutex
 * DESCRIPTION
 *  Give up mutex ownership. If any task is waiting on this mutex, the first
 *  waiting task is selected to be the next owner.
 * PARAMETERS
 *  mutex_ptr        : [IN] mutex pointer.
 * RETURNS
 *  N/A
 * NOTE
 *  Mutex ownership is private to task. That means, give can be done at the same
 *  task of take, otherwise fatal error handling takes place.
 * SEE ALSO
 *  kal_create_mutex kal_take_mutex
 ******************************************************************************/
void kal_give_mutex(kal_mutexid mutex_ptr);
/*******************************************************************************
 * <GROUP Synchronous>
 *
 * FUNCTION
 *  kal_mutex_waiting_count
 * DESCRIPTION
 *  This routine returns the numbers of task waiting on the mutex. 
 * PARAMETERS
 *  mutex_ptr        : [IN] mutex pointer.
 *  waiting_count   : [OUT] waiting count.
 * RETURNS
 *  N/A
 * NOTE
 *  This function is not in any critical section, e.g disable/enable interrupt, user should guarantee the atomic.
 * SEE ALSO
 *  kal_create_mutex kal_take_mutex 
 ******************************************************************************/
void kal_mutex_waiting_count(kal_mutexid mutex_ptr, kal_uint32 *waiting_count);
/*******************************************************************************
 * <GROUP Synchronous>
 * 
 * FUNCTION
 *  kal_create_enh_mutex
 * DESCRIPTION
 *  create an enhmutex which implements Priority Inheritance Protocol(PIP) to
 *  avoid priority inversion.
 * PARAMETERS
 *  mutex_name  : [IN] enhmutex name. it's used for debug only, and only the
 *                    first 8 characters retain.
 * RETURNS
 *  Success:        enhmutex pointer.
 *  Error:          system enter fatal error handling.
 * NOTE
 *  It is strongly suggested to call this function only in system initialization
 *  time, and the related data allocated for the enhmutex could not be freed
 *  once it is created.
 * SEE ALSO
 *  kal_take_enh_mutex kal_give_enh_mutex
 ******************************************************************************/
kal_enhmutexid kal_create_enh_mutex(kal_char *mutex_name);
/*******************************************************************************
 * <GROUP Synchronous>
 *
 * FUNCTION
 *  kal_take_enh_mutex
 * DESCRIPTION
 *  Obtain an instance of the specified enhmutex. If the enhmutex is taken
 *  already before this call, the function cannot be immediately satisfied,
 *  caller task propogates its priority to the owner task if caller task has
 *  higher priority than owner task, and caller task will be suspended until
 *  other task give the ownership to caller task. After the function returns,
 *  caller task is the only task held this enhmutex.
 * PARAMETERS
 *  mutex_ptr        : [IN] enhmutex pointer.
 * RETURNS
 *  N/A
 * NOTE
 *  (1)Enhmutex is not a recursive lock. If caller task already held this
 *     enhmutex, then caller task will suspend forever because any task will not
 *     give up ehnmutex's ownership.
 *  (2)No promise of enhmutex's queue type. If multiple tasks is waiting on a
 *     mutex, no promise made which task will selected to run first.
 * SEE ALSO
 *  kal_create_enh_mutex kal_give_enh_mutex
 ******************************************************************************/
void kal_take_enh_mutex(kal_enhmutexid mutex_ptr);
/*******************************************************************************
 * <GROUP Synchronous>
 *
 * FUNCTION
 *  kal_give_enh_mutex
 * DESCRIPTION
 *  Give up enhmutex ownership. If any task is waiting on this mutex, give the
 *  ownership to any task based on its judge.
 * PARAMETERS
 *  mutex_ptr        : [IN] mutex pointer.
 * RETURNS
 *  N/A
 * NOTE
 *  Enhmutex ownership is private to task. That means, give can be done at the
 *  same task of take, otherwise fatal error handling takes place.
 * SEE ALSO
 *  kal_create_enh_mutex kal_take_enh_mutex
 ******************************************************************************/
void kal_give_enh_mutex(kal_enhmutexid mutex_ptr);
/*******************************************************************************
 * <GROUP Synchronous>
 *
 * FUNCTION
 *  kal_create_sem
 * DESCRIPTION
 *  create a couting semaphore.
 * PARAMETERS
 *  sem_name  : [IN] semaphore name. it's used for debug only, and only the
 *                    first 8 characters retain.
 *  initial_count : [IN] semaphore initial count.
 * RETURNS
 *  Success:        semaphore pointer.
 *  Error:          system enter fatal error handling.
 * NOTE
 *  (1)It is strongly suggested to call this function only in system initialization
 *     time, and the related data allocated for the semaphore could not be freed
 *     once it is created.
 *  (2)Semaphore values can range from 0 through 4,294,967,294 (2^32 - 2).
 * SEE ALSO
 *  kal_take_sem kal_give_sem
 ******************************************************************************/
kal_semid kal_create_sem(kal_char *sem_name, kal_uint32 initial_count);
/*******************************************************************************
 * <GROUP Synchronous>
 *
 * FUNCTION
 *  kal_take_sem
 * DESCRIPTION
 *  Obtains an instance of the specified semaphore.
 * PARAMETERS
 *  sem_ptr        : [IN] semaphore pointer.
 *  wait_mode      : [IN] wait mode, specify the behavior when the semaphore is
 *                   not ready immediately, it can be one the the following values:
 *                   KAL_NO_WAIT - don't wait for other task gives ownership to it
 *                   KAL_INFINITE_WAIT - wait until ownership can be satisfied
 * RETURN VALUES
 *  KAL_SUCCESS    : the operation is done successfully
 *  KAL_SEM_NOT_AVAILABLE : the semaphore is unavailable immediately
 * NOTE
 *  (1)Semaphore is a FIFO queue. If multiple tasks is waiting on a semaphore,
 *     the first waiting task is selected to be the next owner.
 * SEE ALSO
 *  kal_create_sem kal_give_sem
 ******************************************************************************/
kal_status kal_take_sem(kal_semid sem_ptr, kal_wait_mode wait_mode);
/*******************************************************************************
 * <GROUP Synchronous>
 *
 * FUNCTION
 *  kal_give_sem
 * DESCRIPTION
 *  Give up 1 semaphore ownership. If any task is waiting on this semaphore,
 *  give the ownership to first waiting task.
 * PARAMETERS
 *  sem_ptr        : [IN] semaphore pointer.
 * RETURNS
 *  N/A
 * NOTE
 *  N/A
 * SEE ALSO
 *  kal_create_sem kal_take_sem
 ******************************************************************************/
void kal_give_sem(kal_semid sem_ptr);
/*******************************************************************************
 * <GROUP Communication>
 *
 * FUNCTION
 *  kal_create_event_group
 * DESCRIPTION
 *  create an event group.
 * PARAMETERS
 *  eventgrp_name  : [IN] event group name. it's used for debug only, and only
 *                    the first 8 characters retain.
 * RETURNS
 *  Success:        event group pointer.
 *  Error:          system enter fatal error handling.
 * NOTE
 *  (1)It is strongly suggested to call this function only in system initialization
 *     time, and the related data allocated for the event group could not be freed
 *     once it is created.
 *  (2)Each event group contains 32 event flags, all event flags are initially
 *     set to 0.
 * SEE ALSO
 *  kal_set_eg_events kal_retrieve_eg_events kal_retrieve_eg_events_timeout
 ******************************************************************************/
kal_eventgrpid kal_create_event_group(kal_char *eventgrp_name);
/*******************************************************************************
 * <GROUP Communication>
 *
 * FUNCTION
 *  kal_set_eg_events
 * DESCRIPTION
 *  sets the specified event flags in the specified event group. Any task waiting
 *  on the event group whose event flag request is satisfied by this service is resumed.
 * PARAMETERS
 *  eg_ptr  : [IN] event group pointer.
 *  events  : [IN] event flags to be set.
 *  operation : [IN] specify the operation, which can be one of following values:
 *              KAL_AND - events in event group is AND with events argument,
 *                     that is, mask out bits not set in events argument
 *              KAL_OR - events in event group is OR with events argument
 * RETURNS
 *  Success:        return KAL_SUCCESS
 *  Error:          system enter fatal error handling.
 * NOTE
 *  N/A
 * SEE ALSO
 *  kal_create_event_group kal_retrieve_eg_events kal_retrieve_eg_events_timeout
 ******************************************************************************/
kal_status kal_set_eg_events(kal_eventgrpid eg_ptr, kal_uint32 events, kal_uint8 operation);
/*******************************************************************************
 * <GROUP Communication>
 *
 * FUNCTION
 *  kal_retrieve_eg_events
 * DESCRIPTION
 *  retrieves the specified event-flag combination from the specified event-flag group.
 * PARAMETERS
 *  eg_ptr  : [IN] event group pointer.
 *  requested_events  : [IN] requested event flags
 *  operation : [IN] specify the operation, which can be one of following values:
 *              KAL_AND - all of the requested event flags are required
 *              KAL_AND_CONSUME - all of requested event flags are required, and
 *                                automatically clears the event flags present on a successful request
 *              KAL_OR - one or more of the requested event flags is sufficient
 *              KAL_OR_CONSUME - one or more of the requested event flags is sufficient, and
 *                               automatically clears the event flags present on a successful request
 *  retrieved_events: [OUT] actual events present in event group.
 *  suspend:  [IN] whether to wait for the event flags set when they can be satisfied immediately,
 *                 it can be one of following values:
 *                 0: don't wait and return KAL_NOT_PRESENT
 *                 KAL_SUSPEND: wait until they can be satisfied
 * RETURN VALUES
 *  KAL_SUCCESS:     the operation is done successfully
 *  KAL_NOT_PRESENT: the request event flags are not present immediately
 *  Error:          system enter fatal error handling.
 * NOTE
 *  N/A
 * SEE ALSO
 *  kal_create_event_group kal_set_eg_events kal_retrieve_eg_events_timeout
 ******************************************************************************/
kal_status kal_retrieve_eg_events(kal_eventgrpid eg_ptr, kal_uint32 requested_events, kal_uint8 operation,
                                  kal_uint32 *retrieved_events, kal_uint32 suspend);
/*******************************************************************************
 * <GROUP Communication>
 *
 * FUNCTION
 *  kal_retrieve_eg_events_timeout
 * DESCRIPTION
 *  retrieves the specified event-flag combination from the specified event-flag group.
 * PARAMETERS
 *  eg_ptr  : [IN] event group pointer.
 *  requested_events  : [IN] requested event flags
 *  operation : [IN] specify the operation, which can be one of following values:
 *              KAL_AND - all of the requested event flags are required
 *              KAL_AND_CONSUME - all of requested event flags are required, and
 *                                automatically clears the event flags present on a successful request
 *              KAL_OR - one or more of the requested event flags is sufficient
 *              KAL_OR_CONSUME - one or more of the requested event flags is sufficient, and
 *                               automatically clears the event flags present on a successful request
 *  retrieved_events: [OUT] actual events present in event group.
 *  timeout:  [IN] how long to wait for the event flags set when they can be satisfied immediately,
 *                 it can be one of following values:
 *                 0 - don't wait and return KAL_NOT_PRESENT
 *                 KAL_SUSPEND - wait until they can be satisfied
 *                 other values - wait at most timeout ticks, return KAL_NOT_PRESENT if timeout happens
 * RETURN VALUES
 *  KAL_SUCCESS:     the operation is done successfully
 *  KAL_NOT_PRESENT: the request event flags are not present immediately
 *  Error:          system enter fatal error handling.
 * NOTE
 *  This API's availability is dependent on a macro HAS_KAL_RETRIEVE_EG_EVENTS_TIMEOUT.
 *  If it's not defined, then this API is not available.
 * SEE ALSO
 *  kal_create_event_group kal_set_eg_events kal_retrieve_eg_events
 ******************************************************************************/
kal_status kal_retrieve_eg_events_timeout(kal_eventgrpid eg_ptr, kal_uint32 requested_events, kal_uint8 operation,
                                          kal_uint32 *retrieved_events, kal_uint32 timeout);
#define HAS_KAL_RETRIEVE_EG_EVENTS_TIMEOUT 1


/*******************************************************************************
 * Category 6 : Application Memory Management  ADM , AFM
 *******************************************************************************/

extern KAL_ADM_ID (kal_adm_create)(void *mem_addr, kal_uint32 size, kal_uint32 *subpool_size, kal_bool islogging);

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_adm_create2
 * DESCRIPTION
 *  Create a ADM pool.
 * PARAMETERS
 *  mem_addr: [IN] starting address of the memory pool. It should be 4-byte alignment, or it will be aligned to next 4-aligned address.
 *  size: [IN] total size in byte of the memory pool.
 *  subpool_size: [IN] is an array, which describe size of each sub-pool.
 *  flags: [IN] new ADM pool extra flags, which is a combination of following values
 *         KAL_ADM_GUARDIAN_FLAG - RECOMMENDED! put a guard word before and after each user buffer to detect memory corruption
 *                                 it also enable some other error detections on this ADM pool.
 *         KAL_ADM_EXTHEADER_FLAG - has an extensible header immediate before each user buffer,
 *                                  whose size is specified by extheader_size_in_word
 *         KAL_ADM_CLEANDELETE_FLAG - on kal_adm_delete(), if any user buffer is not free yet,
 *                                    system enter fatal error handling
 *         KAL_ADM_REALLOCFAIL_FATAL_FLAG - if kal_adm_realloc() failed, system enter fatal error handling
 *         KAL_ADM_REALLOCFAIL_FREE_FLAG - if kal_adm_realloc() failed, free old user buffer before return NULL
 *  extheader_size_in_word: [IN] specified the extensible header size, only takes effect when KAL_ADM_EXTHEADER_FLAG is specified.
 *                          this argument specified in unit of word, you can use KAL_ADM_EXTHEADER_WORDS(sizeof(struct A)) if you want
 *                          to put a struct A in extensible header.
 * RETURNS
 *  ADM id. If memory is too small to create a ADM, return NULL.
 * NOTE
 *  (1)This API replaces kal_adm_create(). And kal_adm_create() is deprecated,
 *     it will be removed from next release.
 *  (2)subpool_size must be monotonic increasing and ends with {0xffffffff, 0}.
 *     If it's NULL, the default subpool size setting is used: { 16, 32, 64, 128, 256, 512, 0xffffffff, 0 }.
 *     Default subpool size has 7 subpools.
 *  (3)The ADM overhead for control block is divided into 2 parts:
 *     Static - that is (16*3+16*subpool_count}. subpool_count is element count in subpool_size except last element 0.
 *     Dynamic - Each user block has an extra: (8+extheader_size_in_word*4)
 * SEE ALSO
 *  kal_adm_delete KAL_ADM_EXTHEADER_WORDS
 ******************************************************************************/
extern KAL_ADM_ID kal_adm_create2(void *mem_addr, kal_uint32 size, kal_uint32 *subpool_size, kal_uint32 flags, kal_int8 extheader_size_in_word);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_adm_delete
 * DESCRIPTION
 *  delete a ADM pool.
 * PARAMETERS
 *  adm_id: [IN] ADM pool identity.
 * RETURN VALUES
 *  KAL_SUCCESS: the operation succeeded.
 *  KAL_MEMORY_NOT_RELEASE: some user buffer is not free yet.
 * NOTE
 *  if KAL_ADM_CLEANDELETE_FLAG is specified on creation and any user buffer is not free yet,
 *  system enter fatal error handling
 * SEE ALSO
 *  kal_adm_create2
 ******************************************************************************/
extern kal_status kal_adm_delete(KAL_ADM_ID adm_id);

extern void *__kal_adm_alloc(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 *actual_size, kal_uint32 opt, char *filename, kal_uint32 line);
extern void *__kal_adm_alloc_nc(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 *actual_size, kal_uint32 option, char *filename, kal_uint32 line);
extern void *__kal_adm_alloc_c(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 *actual_size, kal_uint32 option, char *filename, kal_uint32 line);

extern void *__kal_adm_realloc(KAL_ADM_ID adm_id, void *ptr, kal_uint32 size, kal_uint32 *actual_size, kal_uint32 opt, char *filename, kal_uint32 line);
extern void *__kal_adm_realloc_nc(KAL_ADM_ID adm_id, void *ptr, kal_uint32 size, kal_uint32 *actual_size, kal_uint32 opt, char *filename, kal_uint32 line);
extern void *__kal_adm_realloc_c(KAL_ADM_ID adm_id, void *ptr, kal_uint32 size, kal_uint32 *actual_size, kal_uint32 opt, char *filename, kal_uint32 line);


/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_adm_alloc
 * DESCRIPTION
 *  allocate a memory buffer from ADM.
 * PARAMETERS
 *  adm_id: [IN] ADM pool identity.
 *  size: [IN] request memory size.
 * RETURNS
 *  allocated memory buffer pointer. return NULL if no memory available.
 * NOTE
 *  the prototype of this API is:
 *   void *kal_adm_alloc(KAL_ADM_ID adm_id, kal_uint32 size);
 * SEE ALSO
 *  kal_adm_create2 kal_adm_alloc_with_info kal_adm_free
 ******************************************************************************/
#define kal_adm_alloc(adm_id, size) __kal_adm_alloc((adm_id), (size), NULL, 0, __FILE__, __LINE__)
#define kal_adm_alloc_dbg(adm_id, size, f, l) __kal_adm_alloc((adm_id), (size), NULL, 0, (f), (l))
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_adm_alloc_with_info
 * DESCRIPTION
 *  allocate a memory buffer from ADM, return the actually size (including any ADM overhead) of this memory block also.
 * PARAMETERS
 *  adm_id: [IN] ADM pool identity.
 *  size: [IN] request memory size.
 *  actual_size: [OUT] return the actually size in it.
 * RETURNS
 *  allocated memory buffer pointer. return NULL if no memory available.
 * NOTE
 *  the prototype of this API is:
 *   void *kal_adm_alloc_with_info(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 *actual_size);
 * SEE ALSO
 *  kal_adm_create2 kal_adm_alloc kal_adm_free
 ******************************************************************************/
#define kal_adm_alloc_with_info(adm_id, size, actual_size) __kal_adm_alloc((adm_id), (size), (actual_size), 0x0, __FILE__, __LINE__)
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_adm_alloc_align
 * DESCRIPTION
 *  allocate a memory buffer which satisfy the alignment requirement from ADM.
 * PARAMETERS
 *  adm_id: [IN] ADM pool identity.
 *  size: [IN] request memory size.
 *  align: [IN] alignment requirement, which must be a multiple of 4.
 * RETURNS
 *  allocated memory buffer pointer. return NULL if no memory available.
 * NOTE
 *  the prototype of this API is:
 *   void *kal_adm_alloc_align(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 alignment);
 * SEE ALSO
 *  kal_adm_create2 kal_adm_free
 ******************************************************************************/
#define kal_adm_alloc_align(adm_id, size, alignment) __kal_adm_alloc((adm_id), (size), NULL, (alignment) & ~ADM_OPT_MASK, __FILE__, __LINE__)
#define kal_adm_alloc_align_dbg(adm_id, size, alignment, f, l) __kal_adm_alloc((adm_id), (size), NULL, (alignment) & ~ADM_OPT_MASK, (f), (l))


#if defined(__MTK_TARGET__) && (defined(__ARM9_MMU__) || defined(__DYNAMIC_SWITCH_CACHEABILITY__))
#define __kal_adm_alloc_cacheable(adm_id, size, option) __kal_adm_alloc_c((adm_id), (size), NULL, 0, __FILE__, __LINE__)
#define __kal_adm_alloc_cacheable_with_info(adm_id, size, option, actual_size) __kal_adm_alloc_c((adm_id), (size), (actual_size), 0x0, __FILE__, __LINE__)
#define __kal_adm_alloc_cacheable_dbg(adm_id, size, option, f, l) __kal_adm_alloc_c((adm_id), (size), NULL, 0, (f), (l))
#else
#define __kal_adm_alloc_cacheable(adm_id, size, option) __kal_adm_alloc((adm_id), (size), NULL, 0, __FILE__, __LINE__)
#define __kal_adm_alloc_cacheable_with_info(adm_id, size, option, actual_size) __kal_adm_alloc((adm_id), (size), (actual_size), 0x0, __FILE__, __LINE__)
#define __kal_adm_alloc_cacheable_dbg(adm_id, size, option, f, l) __kal_adm_alloc((adm_id), (size), NULL, 0, (f), (l))
#endif
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_adm_alloc_cacheable
 * DESCRIPTION
 *  allocate a memory buffer which is cacheable from ADM.
 * PARAMETERS
 *  adm_id: [IN] ADM pool identity.
 *  size: [IN] request memory size.
 *  option_notused: [IN] useless, ignored.
 * RETURNS
 *  allocated memory buffer pointer. return NULL if no memory available.
 * NOTE
 *  (1)the prototype of this API is:
 *   void *kal_adm_alloc_cacheable(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 option_notused);
 *  (2)The pointer is cacheable only on platform that has ARM MMU (such as ARM9/ARM11 platform).
 *     If not, the pointer is still noncacheable.
 * SEE ALSO
 *  kal_adm_create2 kal_adm_alloc_cacheable_with_info kal_adm_alloc_noncacheable kal_adm_free
 ******************************************************************************/
#define kal_adm_alloc_cacheable(adm_id, size, option_notused) __kal_adm_alloc_cacheable(adm_id, size, option_notused)
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_adm_alloc_cacheable_with_info
 * DESCRIPTION
 *  allocate a memory buffer which is cacheable from ADM, return the actually size (including any ADM overhead) of this memory block also.
 * PARAMETERS
 *  adm_id: [IN] ADM pool identity.
 *  size: [IN] request memory size.
 *  option_notused: [IN] useless, ignored.
 *  actual_size: [OUT] return the actually size in it.
 * RETURNS
 *  allocated memory buffer pointer. return NULL if no memory available.
 * NOTE
 *  (1)the prototype of this API is:
 *   void *kal_adm_alloc_cacheable_with_info(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 option_notused, kal_uint32 *actual_size);
 *  (2)The pointer is cacheable only on platform that has ARM MMU (such as ARM9/ARM11 platform).
 *     If not, the pointer is still noncacheable.
 * SEE ALSO
 *  kal_adm_create2 kal_adm_alloc_cacheable kal_adm_alloc_noncacheable kal_adm_free
 ******************************************************************************/
#define kal_adm_alloc_cacheable_with_info(adm_id, size, option_notused, actual_size) __kal_adm_alloc_cacheable_with_info(adm_id, size, option_notused, actual_size)
#define kal_adm_alloc_cacheable_dbg(adm_id, size, option_notused, f, l) __kal_adm_alloc_cacheable_dbg(adm_id, size, option_notused, f, l)

#if defined(__MTK_TARGET__) && (defined(__ARM9_MMU__) || defined(__DYNAMIC_SWITCH_CACHEABILITY__))
#define __kal_adm_alloc_noncacheable(adm_id, size, option) __kal_adm_alloc_nc((adm_id), (size), NULL, 0, __FILE__, __LINE__)
#define __kal_adm_alloc_noncacheable_with_info(adm_id, size, option, actual_size) __kal_adm_alloc_nc((adm_id), (size), (actual_size), 0x0, __FILE__, __LINE__)
#define __kal_adm_alloc_noncacheable_dbg(adm_id, size, option, f, l) __kal_adm_alloc_nc((adm_id), (size), NULL, 0, (f), (l))
#else
#define __kal_adm_alloc_noncacheable(adm_id, size, option) __kal_adm_alloc((adm_id), (size), NULL, 0, __FILE__, __LINE__)
#define __kal_adm_alloc_noncacheable_with_info(adm_id, size, option, actual_size) __kal_adm_alloc((adm_id), (size), (actual_size), 0x0, __FILE__, __LINE__)
#define __kal_adm_alloc_noncacheable_dbg(adm_id, size, option, f, l) __kal_adm_alloc((adm_id), (size), NULL, 0, (f), (l))
#endif
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_adm_alloc_noncacheable
 * DESCRIPTION
 *  allocate a memory buffer which is noncacheable from ADM.
 * PARAMETERS
 *  adm_id: [IN] ADM pool identity.
 *  size: [IN] request memory size.
 *  option_notused: [IN] useless, ignored.
 * RETURNS
 *  allocated memory buffer pointer. return NULL if no memory available.
 * NOTE
 *  (1)the prototype of this API is:
 *   void *kal_adm_alloc_noncacheable(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 option_notused);
 * SEE ALSO
 *  kal_adm_create2 kal_adm_alloc_noncacheable_with_info kal_adm_alloc_cacheable kal_adm_free
 ******************************************************************************/
#define kal_adm_alloc_noncacheable(adm_id, size, option_notused) __kal_adm_alloc_noncacheable(adm_id, size, option_notused)
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_adm_alloc_noncacheable_with_info
 * DESCRIPTION
 *  allocate a memory buffer which is noncacheable from ADM, return the actually size (including any ADM overhead) of this memory block also.
 * PARAMETERS
 *  adm_id: [IN] ADM pool identity.
 *  size: [IN] request memory size.
 *  option_notused: [IN] useless, ignored.
 *  actual_size: [OUT] return the actually size in it.
 * RETURNS
 *  allocated memory buffer pointer. return NULL if no memory available.
 * NOTE
 *  (1)the prototype of this API is:
 *   void *kal_adm_alloc_noncacheable_with_info(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 option_notused, kal_uint32 *actual_size);
 * SEE ALSO
 *  kal_adm_create2 kal_adm_alloc_noncacheable kal_adm_alloc_cacheable kal_adm_free
 ******************************************************************************/
#define kal_adm_alloc_noncacheable_with_info(adm_id, size, option_notused, actual_size) __kal_adm_alloc_noncacheable_with_info(adm_id, size, option_notused, actual_size)
#define kal_adm_alloc_noncacheable_dbg(adm_id, size, option_notused, f, l) __kal_adm_alloc_noncacheable_dbg(adm_id, size, option_notused, f, l)


/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_adm_realloc
 * DESCRIPTION
 *  re-allocate a memory buffer from ADM.
 * PARAMETERS
 *  adm_id: [IN] ADM pool identity.
 *  ptr: [IN] old memory buffer pointer.
 *  size: [IN] request memory size.
 * RETURNS
 *  re-allocated memory buffer pointer. return NULL if no memory available.
 * SEE ALSO
 *  kal_adm_create2 kal_adm_free kal_adm_alloc KAL_ADM_REALLOCFAIL_FATAL_FLAG KAL_ADM_REALLOCFAIL_FREE_FLAG
 ******************************************************************************/
#define kal_adm_realloc(adm_id, ptr, size) __kal_adm_realloc((adm_id), (ptr), (size), NULL, 0, __FILE__, __LINE__)
#define kal_adm_realloc_dbg(adm_id, ptr, size, f, l) __kal_adm_realloc((adm_id), (ptr), (size), NULL, 0, (f), (l))
#if defined(__MTK_TARGET__) && defined(__DYNAMIC_SWITCH_CACHEABILITY__)
#define __kal_adm_realloc_noncacheable(adm_id, ptr, size) __kal_adm_realloc_nc((adm_id), (ptr), (size), NULL, 0, __FILE__, __LINE__)
#define __kal_adm_realloc_cacheable(adm_id, ptr, size) __kal_adm_realloc_c((adm_id), (ptr), (size), NULL, 0, __FILE__, __LINE__)
#else
#define __kal_adm_realloc_noncacheable(adm_id, ptr, size) kal_adm_realloc(adm_id, ptr, size)
#define __kal_adm_realloc_cacheable(adm_id, ptr, size) kal_adm_realloc(adm_id, ptr, size)
#endif

#define kal_adm_realloc_cacheable(adm_id, ptr, size) __kal_adm_realloc_cacheable(adm_id, ptr, size)
#define kal_adm_realloc_noncacheable(adm_id, ptr, size) __kal_adm_realloc_noncacheable(adm_id, ptr, size)

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_adm_free
 * DESCRIPTION
 *  free a memory buffer to dedicated ADM.
 * PARAMETERS
 *  adm_id: [IN] ADM pool identity.
 *  ptr: [IN] memory buffer pointer to be free. This pointer must be allocated from adm_id.
 * RETURNS
 *  N/A
 * SEE ALSO
 *  kal_adm_create2 kal_adm_alloc kal_adm_realloc
 ******************************************************************************/
extern void kal_adm_free(KAL_ADM_ID adm_id, void *ptr);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_adm_get_extheader
 * DESCRIPTION
 *  get the extensible header associated with ptr, which is immediate before ptr.
 * PARAMETERS
 *  adm_id: [IN] ADM pool identity.
 *  ptr: [IN] memory buffer pointer to query. This pointer must be returned from kal_adm_alloc*() functions.
 * RETURNS
 *  associated extensible header pointer.
 * NOTE
 *  (1)This ADM pool must has KAL_ADM_EXTHEADER_FLAG on creation.
 *  (2)The size of this extensible header is (extheader_size_in_word*4)
 * SEE ALSO
 *  kal_adm_create2 KAL_ADM_EXTHEADER_FLAG
 ******************************************************************************/
extern void *kal_adm_get_extheader(KAL_ADM_ID adm_id, void *ptr);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_adm_get_max_alloc_size
 * DESCRIPTION
 *  get maximal available memory size to be allocated in a single kal_adm_alloc*().
 * PARAMETERS
 *  adm_id: [IN] ADM pool identity.
 * RETURNS
 *  maximal available memory size to be allocated.
 * NOTE
 *  (1)This size is guaranteed to allocated without considering any other requirement.
 *     For example, kal_adm_alloc(adm_id, kal_adm_get_max_alloc_size(adm_id)) can succeed.
 *     But kal_adm_alloc_align() is not guaranteed to succeed.
 * SEE ALSO
 *  kal_adm_get_total_left_size
 ******************************************************************************/
extern kal_uint32 kal_adm_get_max_alloc_size(KAL_ADM_ID adm_id);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_adm_get_total_left_size
 * DESCRIPTION
 *  get total un-allocated memory size.
 * PARAMETERS
 *  adm_id: [IN] ADM pool identity.
 * RETURNS
 *  get total un-allocated memory size.
 * NOTE
 *  (1)Total un-allocated memory size may be splitted in many blocks(fragmentation).
 * SEE ALSO
 *  kal_adm_get_max_alloc_size
 ******************************************************************************/
extern kal_uint32 kal_adm_get_total_left_size(KAL_ADM_ID adm_id);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_adm_check_integrity
 * DESCRIPTION
 *  Check the healthy of ADM pool.
 * PARAMETERS
 *  adm_id: [IN] ADM pool identity.
 * RETURNS
 *  return bad memory block first found. If the ADM pool is healthy, return NULL to indicate
 *  nothing wrong.
 ******************************************************************************/
extern void *kal_adm_check_integrity(KAL_ADM_ID adm_id);

/* DOM-NOT_FOR_SDK-BEGIN */
extern void kal_adm_print_log(KAL_ADM_ID adm_id);
extern kal_uint32 kal_adm_calc_worst_alloc_size(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 option);
extern void *kal_adm_get_prev_block_ptr(KAL_ADM_ID adm_id,void *mem_addr);
extern void *kal_adm_get_next_block_ptr(KAL_ADM_ID adm_id,void *mem_addr);
extern void *kal_adm_get_trans_ptr(KAL_ADM_ID adm_id,void *mem_addr);


/*
 * Function prototype: void *kal_adm_alloc_mtkL1_cacheable(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 option)
 * Note: Allocate a MTKL1-cacheable memory block.
 */
#if defined(__MTK_TARGET__) && defined(__MTK_L1CACHEABLE__)
#define kal_adm_alloc_mtkL1_cacheable(adm_id, size, option) __kal_adm_alloc_c((adm_id), (size), NULL, (option), __FILE__, __LINE__)
#else /* __MTK_TARGET__ && __MTK_L1CACHEABLE__ */
#define kal_adm_alloc_mtkL1_cacheable(adm_id, size, option) __kal_adm_alloc((adm_id), (size), NULL, 0, __FILE__, __LINE__)
#endif /* __MTK_TARGET__ && __MTK_L1CACHEABLE__ */

/*
 * Function prototype: void *kal_adm_alloc_mtkL1_noncacheable(KAL_ADM_ID adm_id, kal_uint32 option)
 * Note: Allocate a memory block. This is for RFU only.
 */
#define kal_adm_alloc_mtkL1_noncacheable(adm_id, size, option) __kal_adm_alloc((adm_id), (size), NULL, 0, __FILE__, __LINE__)

/*
 * Function prototype: void *kal_adm_alloc_nc_align(KAL_ADM_ID adm_id, kal_uint32 align_size)
 * Note: Allocate a non-cacheable and aligned memory block.
 */
#if defined(__MTK_TARGET__) && (defined(__ARM9_MMU__) || defined(__DYNAMIC_SWITCH_CACHEABILITY__))
#define kal_adm_alloc_nc_align(adm_id, size, a) __kal_adm_alloc_nc((adm_id), (size), NULL, (a) & ~ADM_OPT_MASK, __FILE__, __LINE__)
#define kal_adm_alloc_nc_align_dbg(adm_id, size, a, f, l) __kal_adm_alloc_nc((adm_id), (size), NULL, (a) & ~ADM_OPT_MASK, (f), (l))
#else /* __MTK_TARGET__ && (__ARM9_MMU__ || __DYNAMIC_SWITCH_CACHEABILITY__) */
#define kal_adm_alloc_nc_align(adm_id, size, a) __kal_adm_alloc((adm_id), (size), NULL, (a) & ~ADM_OPT_MASK, __FILE__, __LINE__)
#define kal_adm_alloc_nc_align_dbg(adm_id, size, a, f, l) __kal_adm_alloc((adm_id), (size), NULL, (a) & ~ADM_OPT_MASK, (f), (l))
#endif /* __MTK_TARGET__ && (__ARM9_MMU__ || __DYNAMIC_SWITCH_CACHEABILITY__) */

/*
 * Function prototype: void *kal_adm_alloc_topmost(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 align_size)
 *                     void *kal_adm_alloc_topmost_dbg(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 align_size, kal_char *filename, kal_uint32 linenumber)
 * Note: Allocate a memory block from the topmost address of the pool.
 *       The start address of the allocated memory will be aligned to the input parameter align_size.
 *       kal_adm_alloc_topmost_dbg() is the debug verion.
 *       The input parameters filename and line will be used for logging if logging is enabled.
 */
#define kal_adm_alloc_topmost(adm_id, size, a) __kal_adm_alloc((adm_id), (size), NULL, ((a) & ~ADM_OPT_MASK) | ADM_OPT_TOPMOST_ALLOC, __FILE__, __LINE__)
#define kal_adm_alloc_topmost_dbg(adm_id, size, a, f, l) __kal_adm_alloc((adm_id), (size), NULL, ((a) & ~ADM_OPT_MASK) | ADM_OPT_TOPMOST_ALLOC, (f), (l))

/*
 * Function prototype: void *kal_adm_alloc_c_topmost(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 align_size)
 *                     void *kal_adm_alloc_c_topmost_dbg(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 align_size, kal_char *filename, kal_uint32 line)
 * Note: Allocate a cacheable memory block from the topmost address of the pool.
 *       The start address of the allocated memory will be aligned to the input parameter align_size.
 */
#if defined(__MTK_TARGET__) && (defined(__ARM9_MMU__) || defined(__DYNAMIC_SWITCH_CACHEABILITY__))
#define kal_adm_alloc_c_topmost(adm_id, size, a) __kal_adm_alloc_c((adm_id), (size), NULL, ((a) & ~ADM_OPT_MASK) | ADM_OPT_TOPMOST_ALLOC, __FILE__, __LINE__)
#define kal_adm_alloc_c_topmost_dbg(adm_id, size, a, f, l) __kal_adm_alloc_c((adm_id), (size), NULL, ((a) & ~ADM_OPT_MASK) | ADM_OPT_TOPMOST_ALLOC, (f), (l))
#else /* __MTK_TARGET__ && (__ARM9_MMU__ || __DYNAMIC_SWITCH_CACHEABILITY__)*/
#define kal_adm_alloc_c_topmost(adm_id, size, a) __kal_adm_alloc((adm_id), (size), NULL, ((a) & ~ADM_OPT_MASK) | ADM_OPT_TOPMOST_ALLOC, __FILE__, __LINE__)
#define kal_adm_alloc_c_topmost_dbg(adm_id, size, a, f, l) __kal_adm_alloc((adm_id), (size), NULL, ((a) & ~ADM_OPT_MASK) | ADM_OPT_TOPMOST_ALLOC, (f), (l))
#endif /* __MTK_TARGET__ && (__ARM9_MMU__ || __DYNAMIC_SWITCH_CACHEABILITY__)*/

/*
 * Function prototype: void *kal_adm_alloc_nc_topmost(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 align_size)
 *                     void *kal_adm_alloc_nc_topmost_dbg(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 align_size, kal_char *filename, kal_uint32 line)
 * Note: Allocate a non-cacheable memory block from the topmost address of the pool.
 *       The start address of the allocated memory will be aligned to the input parameter align_size.
 *       kal_adm_alloc_nc_topmost_dbg() is the debug version.
 */
#if defined(__MTK_TARGET__) && (defined(__ARM9_MMU__) || defined(__DYNAMIC_SWITCH_CACHEABILITY__))
#define kal_adm_alloc_nc_topmost(adm_id, size, a) __kal_adm_alloc_nc((adm_id), (size), NULL, ((a) & ~ADM_OPT_MASK) | ADM_OPT_TOPMOST_ALLOC, __FILE__, __LINE__)
#define kal_adm_alloc_nc_topmost_dbg(adm_id, size, a, f, l) __kal_adm_alloc_nc((adm_id), (size), NULL, ((a) & ~ADM_OPT_MASK) | ADM_OPT_TOPMOST_ALLOC, (f), (l))
#else /* __MTK_TARGET__ && (__ARM9_MMU__ || __DYNAMIC_SWITCH_CACHEABILITY__)*/
#define kal_adm_alloc_nc_topmost(adm_id, size, a) __kal_adm_alloc((adm_id), (size), NULL, ((a) & ~ADM_OPT_MASK) | ADM_OPT_TOPMOST_ALLOC, __FILE__, __LINE__)
#define kal_adm_alloc_nc_topmost_dbg(adm_id, size, a, f, l) __kal_adm_alloc((adm_id), (size), NULL, ((a) & ~ADM_OPT_MASK) | ADM_OPT_TOPMOST_ALLOC, (f), (l))
#endif /* __MTK_TARGET__ && (__ARM9_MMU__ || __DYNAMIC_SWITCH_CACHEABILITY__)*/
/* DOM-NOT_FOR_SDK-END */


/*
 * AFM Section
 */

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_afm_create
 * DESCRIPTION
 *  Create a AFM pool.
 * PARAMETERS
 *  mem_addr: [IN] starting address of the memory pool. It should be 4-byte alignment, or it will be aligned to next 4-aligned address.
 *  size: [IN] total size in byte of the memory pool.
 *  subpool_size: [IN] is an array, which describe size of each sub-pool.
 *  subpool_nr: [IN] is an array, which describe element count of each sub-pool.
 *  flags: [IN] new AFM pool extra flags, which is a combination of following values
 *         AFM_OPT_ALIGN_ALLOC - user buffers in this AFM is aligned to CPU cache line (32 bytes)
 *                               only available on platform which has a ARM MMU (ARM9+ chips).
 *         AFM_OPT_NOFALLBACK_ALLOC - when search avaiable user buffer, don't try to search subpools bigger than fittest subpool.
 *  left_mem: [OUT] get how many memory is not used by this AFM pool and can be used by app freely.
 * RETURNS
 *  AFM id. If memory is too small to create a AFM, system enters fatal error handling.
 * NOTE
 *  subpool_size must be monotonic increasing and ends with {0xffffffff, 0}.
 *   subpool_nr must has same elements as subpool_size.
 * SEE ALSO
 *  kal_afm_delete
 ******************************************************************************/
extern KAL_AFM_ID kal_afm_create(void *mem_addr, kal_uint32 size, kal_uint32 *subpool_size,kal_uint32 *subpool_nr, kal_uint32 flags, kal_uint32 *left_mem);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_afm_delete
 * DESCRIPTION
 *  delete a AFM pool.
 * PARAMETERS
 *  afm_id: [IN] AFM pool identity.
 * RETURN VALUES
 *  KAL_SUCCESS: the operation succeeded.
 *  KAL_MEMORY_NOT_RELEASE: some user buffer is not freed yet.
 * SEE ALSO
 *  kal_afm_create
 ******************************************************************************/
extern kal_status kal_afm_delete(KAL_AFM_ID afm_id);

extern void *kal_afm_internal_alloc(KAL_AFM_ID afm_id, kal_uint32 size, kal_uint32 *actual_size, char *filename, kal_uint32 line);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_afm_alloc
 * DESCRIPTION
 *  allocate a memory buffer from AFM.
 * PARAMETERS
 *  afm_id: [IN] AFM pool identity.
 *  size: [IN] request memory size.
 * RETURNS
 *  allocated memory buffer pointer. return NULL if no memory available.
 * NOTE
 *  the prototype of this API is:
 *   void *kal_afm_alloc(KAL_AFM_ID afm_id, kal_uint32 size);
 * SEE ALSO
 *  kal_afm_create kal_afm_free
 ******************************************************************************/
#define kal_afm_alloc(afm_id, size) kal_afm_internal_alloc(afm_id, size, NULL, __FILE__, __LINE__)
#define kal_afm_alloc_dbg(afm_id, size, actual_size, filename, line) kal_afm_internal_alloc(afm_id, size, actual_size, filename, line)
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_afm_free
 * DESCRIPTION
 *  free a memory buffer to dedicated AFM.
 * PARAMETERS
 *  afm_id: [IN] AFM pool identity.
 *  ptr: [IN] memory buffer pointer to be freed. This pointer must be allocated from afm_id.
 * RETURNS
 *  N/A
 * SEE ALSO
 *  kal_afm_create kal_afm_alloc
 ******************************************************************************/
extern void kal_afm_free(KAL_AFM_ID afm_id, void *ptr);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_afm_check_integrity
 * DESCRIPTION
 *  Check the healthy of AFM pool.
 * PARAMETERS
 *  afm_id: [IN] AFM pool identity.
 * RETURNS
 *  return bad memory block first found. If the AFM pool is healthy, return NULL to indicate
 *  nothing wrong found.
 ******************************************************************************/
extern kal_int32 kal_afm_check_integrity(KAL_AFM_ID afm_id);

extern void *kal_afm_internal_alloc_cacheable(KAL_AFM_ID adm_id, kal_uint32 size, kal_uint32 *actual_size, char *filename, kal_uint32 line);
#if defined(__MTK_TARGET__) && (defined(__ARM9_MMU__) || defined(__DYNAMIC_SWITCH_CACHEABILITY__))
#define __kal_afm_alloc_cacheable(afm_id, size, option_notused) kal_afm_internal_alloc_cacheable(afm_id, size, NULL, __FILE__, __LINE__)
#define __kal_afm_alloc_cacheable_dbg(afm_id, size, option_notused, actual_size, filename, line) kal_afm_internal_alloc_cacheable(afm_id, size, actual_size, filename, line)
#else
#define __kal_afm_alloc_cacheable(afm_id, size, option_notused) kal_afm_internal_alloc(afm_id, size, NULL, __FILE__, __LINE__)
#define __kal_afm_alloc_cacheable_dbg(afm_id, size, option_notused, actual_size, filename, line) kal_afm_internal_alloc(afm_id, size, actual_size, filename, line)
#endif
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_afm_alloc_cacheable
 * DESCRIPTION
 *  allocate a memory buffer which is cacheable from AFM.
 * PARAMETERS
 *  afm_id: [IN] AFM pool identity.
 *  size: [IN] request memory size.
 *  option_notused: [IN] useless, ignored.
 * RETURNS
 *  allocated memory buffer pointer. return NULL if no memory available.
 * NOTE
 *  (1)the prototype of this API is:
 *   void *kal_afm_alloc_cacheable(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 option_notused);
 *  (2)This AFM must be created using AFM_OPT_ALIGN_ALLOC in kal_afm_create.
 *  (3)The pointer is cacheable only on platform that has ARM MMU (such as ARM9/ARM11 platform).
 *     If not, the pointer is still noncacheable.
 * SEE ALSO
 *  kal_afm_create kal_afm_alloc_noncacheable kal_afm_free
 ******************************************************************************/
#define kal_afm_alloc_cacheable(afm_id, size, option_notused) __kal_afm_alloc_cacheable(afm_id, size, option_notused)
#define kal_afm_alloc_cacheable_dbg(afm_id, size, option_notused, actual_size, filename, line) __kal_afm_alloc_cacheable_dbg(afm_id, size, option_notused, actual_size, filename, line)

extern void *kal_afm_internal_alloc_noncacheable(KAL_AFM_ID afm_id, kal_uint32 size, kal_uint32 *actual_size, char *filename, kal_uint32 line);
#if defined(__MTK_TARGET__) && (defined(__ARM9_MMU__) || defined(__DYNAMIC_SWITCH_CACHEABILITY__))
#define __kal_afm_alloc_noncacheable(afm_id, size, option_notused) kal_afm_internal_alloc_noncacheable(afm_id, size, NULL, __FILE__, __LINE__)
#define __kal_afm_alloc_noncacheable_dbg(afm_id, size, option_notused, actual_size, filename, line) kal_afm_internal_alloc_noncacheable(afm_id, size, actual_size, filename, line)
#else
#define __kal_afm_alloc_noncacheable(afm_id, size, option_notused) kal_afm_internal_alloc(afm_id, size, NULL, __FILE__, __LINE__)
#define __kal_afm_alloc_noncacheable_dbg(afm_id, size, option_notused, actual_size, filename, line) kal_afm_internal_alloc(afm_id, size, actual_size, filename, line)
#endif
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_afm_alloc_noncacheable
 * DESCRIPTION
 *  allocate a memory buffer which is noncacheable from AFM.
 * PARAMETERS
 *  adm_id: [IN] ADM pool identity.
 *  size: [IN] request memory size.
 *  option_notused: [IN] useless, ignored.
 * RETURNS
 *  allocated memory buffer pointer. return NULL if no memory available.
 * NOTE
 *  (1)the prototype of this API is:
 *   void *kal_afm_alloc_noncacheable(KAL_ADM_ID adm_id, kal_uint32 size, kal_uint32 option_notused);
 *  (2)This AFM must be created using AFM_OPT_ALIGN_ALLOC in kal_afm_create.
 * SEE ALSO
 *  kal_afm_create kal_afm_alloc_cacheable kal_afm_free
 ******************************************************************************/
#define kal_afm_alloc_noncacheable(afm_id, size, option_notused) __kal_afm_alloc_noncacheable(afm_id, size, option_notused)
#define kal_afm_alloc_noncacheable_dbg(afm_id, size, option_notused, actual_size, filename, line) __kal_afm_alloc_noncacheable_dbg(afm_id, size, option_notused, actual_size, filename, line)

/* DOM-NOT_FOR_SDK-BEGIN */
extern kal_int32 kal_afm_print_log(KAL_AFM_ID afm_id);
extern kal_int32 kal_afm_get_subpool_num(KAL_AFM_ID afm_id);
extern kal_int32 kal_afm_info_get(KAL_AFM_ID afm_id, kal_uint32 *option, kal_uint32 *buff_size, kal_uint32 *buff_nr, kal_uint32 *left_buf_nr, kal_uint32 *total_left_mem_sz);
extern kal_int32 kal_afm_custom_performance_info_get(KAL_AFM_ID afm_id, kal_uint32 *option, kal_uint32 *buff_size, kal_uint32 *buff_nr, kal_uint32 *alloc_cnt, kal_uint32 *min_left_buf_nr);
extern kal_int32 kal_afm_set_cuslogging(KAL_AFM_ID afm_id, kal_uint32 cus_log_opt);
extern kal_int32 kal_afm_get_cuslogging(KAL_AFM_ID afm_id, kal_uint32 *cus_log_opt);
extern kal_int32 kal_afm_get_left_subpool_num(KAL_AFM_ID afm_id, kal_uint32 size);
/* DOM-NOT_FOR_SDK-END */

/* DOM-NOT_FOR_SDK-BEGIN */
/*******************************************************************************
 * Category 7 : System and Modem Memory Management
 *******************************************************************************/
extern void *get_ctrl_buffer_ext(kal_uint32 size, const kal_char *file_name, kal_uint32 line);
extern void free_ctrl_buffer_ext(void *buff_ptr, const kal_char *file_name, kal_uint32 line);

#if defined(DEBUG_KAL) && defined(DEBUG_BUF2)
#define __get_ctrl_buffer(size) get_ctrl_buffer_ext(size, __FILE__, __LINE__)
#define __free_ctrl_buffer(ptr) free_ctrl_buffer_ext(ptr, __FILE__, __LINE__)
#else   /* DEBUG_KAL && DEBUG_BUF2 */
#define __get_ctrl_buffer(size) get_ctrl_buffer_ext(size, NULL, 0)
#define __free_ctrl_buffer(ptr) free_ctrl_buffer_ext(ptr, NULL, 0)
#endif   /* DEBUG_KAL && DEBUG_BUF2 */

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  get_ctrl_buffer
 * DESCRIPTION
 *  get a memory block at least size bytes from ctrl buffer.
 * PARAMETERS
 *  size: [IN] request memory block.
 * RETURNS
 *  memory block pointer. If all memory blocks used in corresponding ctrl buffer
 *  used up, system enter fatal error handling.
 * NOTE
 *  (1)This API should be used in protocol stack only.
 * SEE ALSO
 *  free_ctrl_buffer
 ******************************************************************************/
#define get_ctrl_buffer(size) __get_ctrl_buffer(size)
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  free_ctrl_buffer
 * DESCRIPTION
 *  free a memory block allocated from ctrl buffer.
 * PARAMETERS
 *  ptr: [IN] memory block pointer.
 * RETURNS
 *  N/A
 * NOTE
 *  (1)This API should be used in protocol stack only.
 * SEE ALSO
 *  get_ctrl_buffer
 ******************************************************************************/
#define free_ctrl_buffer(ptr) __free_ctrl_buffer(ptr)
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  free_ctrl_buffer_set_null
 * DESCRIPTION
 *  free a memory block allocated from ctrl buffer. then set pointer as null
 * PARAMETERS
 *  ptr: [IN] memory block pointer.
 * RETURNS
 *  N/A
 * NOTE
 *  (1)This API should be used in protocol stack only.
 * SEE ALSO
 *  get_ctrl_buffer
 ******************************************************************************/
#define free_ctrl_buffer_set_null(ptr) \
do {__free_ctrl_buffer(ptr); ptr=NULL;} while(0)
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *	kal_debug_cbs_leakage_check_start
 * DESCRIPTION
 *	enable control buffer leakage check.
 * PARAMETERS
 *	N/A
 * RETURNS
 *	N/A
 * SEE ALSO
 *	 
 ******************************************************************************/
void kal_debug_cbs_leakage_check_start(void);
void kal_debug_cbs_leakage_check_stop(void);

/* DOM-NOT_FOR_SDK-END */
/*******************************************************************************
 * Category 8 : Timer Service
 *******************************************************************************/

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_get_systicks
 * DESCRIPTION
 *  return elapsed system ticks from boot up
 * PARAMETERS
 *  N/A
 * RETURNS
 *  elapsed system ticks from boot up
 * NOTE
 *  (1)Each tick is KAL_MILLISECS_PER_TICK miliseconds.
 * SEE ALSO
 *  KAL_MILLISECS_PER_TICK
 ******************************************************************************/
kal_uint32 kal_get_systicks(void);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_secs_to_ticks
 * DESCRIPTION
 *  convert seconds to system ticks
 * PARAMETERS
 *  secs : [IN] seconds
 * RETURNS
 *  corresponding system ticks
 * NOTE
 *  This functions is equvilent to (secs * 1000 / KAL_MILLISECS_PER_TICK).
 *  It uses table lookup to avoid floating division to speed up.
 * SEE ALSO
 *  kal_milli_secs_to_ticks KAL_MILLISECS_PER_TICK
 ******************************************************************************/
kal_uint32 kal_secs_to_ticks(kal_uint32 secs);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_milli_secs_to_ticks
 * DESCRIPTION
 *  convert milliseconds to system ticks
 * PARAMETERS
 *  milli_secs : [IN] milliseconds
 * RETURNS
 *  corresponding system ticks
 * NOTE
 *  This functions is equvilent to ( ( milli_secs + KAL_MILLISECS_PER_TICK / 2 ) / KAL_MILLISECS_PER_TICK).
 *  It uses table lookup to avoid floating division to speed up.
 * SEE ALSO
 *  kal_milli_secs_to_ticks KAL_MILLISECS_PER_TICK
 ******************************************************************************/
kal_uint32 kal_milli_secs_to_ticks(kal_uint32 milli_secs);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_ticks_to_secs
 * DESCRIPTION
 *  convert system ticks to seconds
 * PARAMETERS
 *  ticks : [IN] ticks count
 * RETURNS
 *  corresponding seconds
 * NOTE
 *  This functions is equvilent to (ticks * KAL_MILLISECS_PER_TICK / 1000).
 *  It uses table lookup to avoid floating multiplication to speed up.
 * SEE ALSO
 *  kal_ticks_to_milli_secs KAL_MILLISECS_PER_TICK
 ******************************************************************************/
kal_uint32 kal_ticks_to_secs(kal_uint32 ticks);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_ticks_to_milli_secs
 * DESCRIPTION
 *  convert system ticks to milliseconds
 * PARAMETERS
 *  ticks : [IN] ticks count
 * RETURNS
 *  corresponding milliseconds
 * NOTE
 *  This functions is equvilent to (ticks * KAL_MILLISECS_PER_TICK).
 *  It uses table lookup to avoid floating multiplication to speed up.
 * SEE ALSO
 *  kal_ticks_to_secs KAL_MILLISECS_PER_TICK
 ******************************************************************************/
kal_uint32 kal_ticks_to_milli_secs(kal_uint32 ticks);


/*******************************************************************************
 * Category 8 : Timer Service
 *******************************************************************************/
/*************************************************************************
 * Exported Function Prototypes for KAL timer
 *************************************************************************/

/* DOM-NOT_FOR_SDK-BEGIN */
 /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_create_timer
 * DESCRIPTION
 *  create a kal timer.
 * PARAMETERS
 *  timer_name : [IN] timer name. It's used for debug only, and only the
 *                first 8 characters retain.
 * RETURNS
 *  Success:        timer pointer.
 *  Error:          system enter fatal error handling.
 * NOTE
 *  (1)It is strongly suggested to call this function only at system initialization stage,
 *     and the related data allocated for the timer could not be freed once it is created.
 *  (2)kal timer API is not thread safe and it's strongly suggested to use it
 *     in single task/HISR only.
 * SEE ALSO
 *  kal_set_timer kal_cancel_timer kal_get_remaining_time
 ******************************************************************************/
kal_timerid kal_create_timer(kal_char* timer_name);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_set_timer
 * DESCRIPTION
 *  start a kal timer.
 * PARAMETERS
 *  timer_ptr : [IN] timer pointer.
 *  handler_func_ptr: [IN] pointer of timeout handler, it will be called after
 *                    timeout happens
 *  handler_param_ptr: [IN] user supply argument for handler_func_ptr
 *  delay: [IN] timeout duration in terms of time ticks, the maximum value is 0xFFFFFFFF
 *  reschedule_time: [IN] reset delay to reschedule_time after timeout happens.
 *                   If it's zero, no reschedule happens and the timer is one-shot.
 *                   Otherwise, it's a periodic timer.
 * RETURNS
 *  N/A
 * NOTE
 *  kal_set_timer will cancel previous set timeout event on this timer, and
 *  start a new one.
 * SEE ALSO
 *  kal_create_timer kal_cancel_timer kal_get_remaining_time
 ******************************************************************************/
void kal_set_timer(kal_timerid timer_ptr,
                   kal_timer_func_ptr handler_func_ptr, void* handler_param_ptr,
                   kal_uint32 delay, kal_uint32 reschedule_time);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_cancel_timer
 * DESCRIPTION
 *  cancel a kal timer.
 * PARAMETERS
 *  timer_ptr : [IN] timer pointer.
 * RETURNS
 *  N/A
 * NOTE
 *  Please note that canceling timer inside HISR may cancel a timer which is
 *  in expired stage but the callback function not yet been serviced.
 * SEE ALSO
 *  kal_create_timer kal_set_timer kal_get_remaining_time
 ******************************************************************************/
void kal_cancel_timer(kal_timerid timer_ptr);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_get_remaining_time
 * DESCRIPTION
 *  retrieve the remaining timeout period in units of time ticks
 * PARAMETERS
 *  timer_ptr : [IN] timer pointer.
 * RETURNS
 *  N/A
 * SEE ALSO
 *  kal_create_timer kal_set_timer kal_cancel_timer
 ******************************************************************************/
kal_uint32 kal_get_remaining_time(kal_timerid timer_ptr);

/* DOM-NOT_FOR_SDK-END */

/* DOM-NOT_FOR_SDK-BEGIN */
/*************************************************************************
 * Exported Function Prototypes for stack timer
 *************************************************************************/

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  stack_init_timer
 * DESCRIPTION
 *  initialize a stack timer, user is response for provide stack timer control
 *  block memory.
 * PARAMETERS
 *  stack_timer: [OUT] stack timer control block provided by the users
 *  timer_name: [IN] stack timer name. it's used for debug only, and only the
 *              first 8 characters retain.
 *  module_id: [IN] module ID of the owner, to which an expiry ILM will be delivered.
 * RETURNS
 *  If stack_init_timer fails, system enter fatal error handling.
 * NOTE
 *  (1)It is strongly suggested to call this function only at system initialization stage,
 *     and the related data allocated for the stack timer could not be freed once it is created.
 *  (2)This API is deprecated and will be removed from next release. Please use stack_create_timer instead.
 * SEE ALSO
 *  stack_create_timer stack_start_timer stack_stop_timer stack_is_time_out_valid stack_process_time_out
 ******************************************************************************/
extern void stack_init_timer(stack_timer_struct *stack_timer,
                            kal_char *timer_name,
                            module_type module_id);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  stack_create_timer
 * DESCRIPTION
 *  create a stack timer.
 * PARAMETERS
 *  timer_name: [IN] stack timer name. it's used for debug only, and only the
 *              first 8 characters retain.
 *  module_id: [IN] module ID of the owner, to which an expiry ILM will be delivered.
 * RETURNS
 *  If stack_create_timer fails, system enter fatal error handling.
 * NOTE
 *  (1)It is strongly suggested to call this function only at system initialization stage,
 *     and the related data allocated for the stack timer could not be freed once it is created.
 *  (2)This API replaces stack_init_timer(). And stack_init_timer() is deprecated,
 *     it will be removed from next release.
 *  (3)The inaccuracy of stack timer comes from
 *        schedule delay - the time from MSG_ID_TIMER_EXPIRY ILM sent to the task runs, more high priority
 *                         tasks preempt target task, more longer.
 *        Task handling message delay - the time until the MSG_ID_TIMER_EXPIRY ILM handled, more ILM messages before it, more longer.
 * SEE ALSO
 *  stack_init_timer stack_start_timer stack_stop_timer stack_is_time_out_valid stack_process_time_out
 ******************************************************************************/
extern stack_timer_struct *stack_create_timer(kal_char *timer_name, module_type module_id);
#define HAS_STACK_CREATE_TIMER 1
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  stack_start_timer
 * DESCRIPTION
 *  start a stack timer. After the timer is expired, system send a MSG_ID_TIMER_EXPIRY ILM message
 *  to task of module specified by module_id in stack_create_timer.
 * PARAMETERS
 *  stack_timer : [IN] stack timer pointer.
 *  timer_indx: [IN] timer index, this index can be retrieved using stack_timer_get_index
 *  init_time: [IN] timeout duration in terms of time ticks, the maximum value is 0xFFFFFFFF
 * RETURNS
 *  N/A
 * NOTE
 *  (1)stack_start_timer will cancel previous set timeout event on this timer, and
 *     start a new one.
 *  (2)stack timer is a one-shot event, it will automatically stop after first expire.
 *  (3)It's highly recommanded to ensure the stack timer is stopped before start a new one.
 *     Please call stack_stop_timer() to do that.
 * SEE ALSO
 *  stack_create_timer stack_stop_timer stack_is_time_out_valid stack_process_time_out
 ******************************************************************************/
extern void stack_start_timer(stack_timer_struct *stack_timer,
                              kal_uint16 timer_indx,
                              kal_uint32 init_time);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  stack_stop_timer
 * DESCRIPTION
 *  stop a stack timer.
 * PARAMETERS
 *  stack_timer : [IN] stack timer pointer.
 * RETURNS
 *  stack timer status before it's stopped.
 * NOTE
 *  Please note that canceling timer inside HISR may cancel a timer which is
 *  in expired stage but the callback function not yet been serviced.
 * SEE ALSO
 *  stack_create_timer stack_start_timer stack_is_time_out_valid stack_process_time_out
 ******************************************************************************/
extern stack_timer_status_type stack_stop_timer(stack_timer_struct *stack_timer);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  stack_timer_status
 * DESCRIPTION
 *  query current status of the stack timer. And if timer_remaing is not NULL,
 *  return remaining time before this stack timer in it.
 * PARAMETERS
 *  stack_timer : [IN] stack timer pointer.
 *  time_remaining: [OUT] return return remaining time before this stack timer in it.
 * RETURNS
 *  Current status of the stack timer.
 * SEE ALSO
 *  stack_create_timer stack_start_timer stack_stop_timer
 ******************************************************************************/
extern stack_timer_status_type stack_timer_status(stack_timer_struct *stack_timer,
                                                    kal_uint32 *time_remaining);
 /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  stack_timer_get_remaining_time
 * DESCRIPTION
 *  retrieve the remaining timeout period in units of time ticks
 * PARAMETERS
 *  stack_timer : [IN] stack timer pointer.
 * RETURNS
 *  remaining timeout period in units of time ticks
 * SEE ALSO
 *  stack_create_timer stack_start_timer stack_stop_timer
 ******************************************************************************/
INLINE_MODIFIER INLINE kal_uint32 stack_timer_get_remaining_time(stack_timer_struct *stack_timer)
{
    kal_uint32 remaining = 0;

    stack_timer_status(stack_timer, &remaining);

    return remaining;
}
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  stack_is_time_out_valid
 * DESCRIPTION
 *  query whether current MSG_ID_TIMER_EXPIRY ILM message is cancelled(valid). A cancelled
 *  MSG_ID_TIMER_EXPIRY ILM message should not be processed.
 * PARAMETERS
 *  stack_timer : [IN] stack timer pointer.
 * RETURN VALUES:
 *  KAL_TRUE: this MSG_ID_TIMER_EXPIRY ILM message is valid and not cancelled yet, it should be handled.
 *  KAL_FALSE: this MSG_ID_TIMER_EXPIRY ILM message is cancelled, it should not be handled.
 * NOTE
 *  (1)Before every MSG_ID_TIMER_EXPIRY ILM message can be handled, this API must be called
 *     to identify whether it's cancelled.
 * SEE ALSO
 *  stack_create_timer stack_start_timer stack_stop_timer stack_process_time_out
 ******************************************************************************/
extern kal_bool stack_is_time_out_valid(stack_timer_struct *stack_timer);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  stack_process_time_out
 * DESCRIPTION
 *  Claim a MSG_ID_TIMER_EXPIRY ILM message is processed.
 * PARAMETERS
 *  stack_timer : [IN] stack timer pointer.
 * RETURNS
 *  N/A
 * NOTE
 *  (1)After every valid MSG_ID_TIMER_EXPIRY ILM message is handled, this API must
 *     be called to correctly maintain the control element in stack timer.
 * SEE ALSO
 *  stack_create_timer stack_start_timer stack_stop_timer stack_is_time_out_valid
 ******************************************************************************/
extern void stack_process_time_out(stack_timer_struct *stack_timer);

extern kal_uint8 stack_time_out_messages_in_queue(stack_timer_struct *stack_timer);

extern stack_timer_user_view_status_type
stack_timer_user_view_status(stack_timer_struct *stack_timer,
                              kal_uint32 *time_remaining);
/* DOM-NOT_FOR_SDK-END */

/*************************************************************************
 * Exported Function Prototypes for event scheduler
 *************************************************************************/

/*******************************************************************************
 * <GROUP CallBackFunctions>
 *
 * FUNCTION
 *  malloc_fp_t
 * DESCRIPTION
 *  pointer to a function that can allocation memory like malloc.
 * PARAMETERS
 *  size: [IN] request memory size in byte.
 * RETURNS
 *  Successful: memory pointer.
 *  Fail:       NULL.
 ******************************************************************************/
typedef void * (*malloc_fp_t)(unsigned int size);
/*******************************************************************************
 * <GROUP CallBackFunctions>
 *
 * FUNCTION
 *  realloc_fp_t
 * DESCRIPTION
 *  pointer to a function that can re-allocation memory like realloc.
 * PARAMETERS
 *  ptr: [IN] old pointer.
 *  new_size: [IN] new request memory size in byte.
 * RETURNS
 *  Successful: memory pointer.
 *  Fail:       NULL.
 ******************************************************************************/
typedef void * (*realloc_fp_t)(void *ptr, unsigned int new_size);
/*******************************************************************************
 * <GROUP CallBackFunctions>
 *
 * FUNCTION
 *  free_fp_t
 * DESCRIPTION
 *  pointer to a function that can free memory like free.
 * PARAMETERS
 *  ptr: [IN] memory pointer to be free.
 * RETURNS
 *  N/A
 ******************************************************************************/
typedef void (*free_fp_t)(void *ptr);

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  evshed_create
 * DESCRIPTION
 *  create a new event scheduler.
 * PARAMETERS
 *  evshed_name: [IN] event scheduler name. it's used for debug only, and only the
 *                    first 8 characters retain.
 *  module_id: [IN] the module this event scheduler belongs to. When event scheduler
 *              timeout happens, system sent timeout message to task of this module.
 *  allowed_time_shift: [IN]
 *      Timer inaccuracy in ticks that the event scheduler allow, regardless of sleep mode.
 *      If set, the event may delay or prematurely timeout for maximum allowed_time_shift ticks.
 *      If don't like it, just set it to 0.
 *
 *      Advantage -
 *      Set this argument will save you a lot of CPU resource if the events are frequent and close to each other.
 *
 *  allowed_time_shift_sleep_mode: [IN]
 *      Behaviour -
 *      Time inaccuracy in ticks the event scheduler allow, due to target enters sleep mode.
 *      The event may delay for max allowed_time_shift_sleep_mode tick if the target enters sleep mode,
 *      so that the target can sleep longer. The event will suffer no delay if the target doesn't enter sleep mode.
 *
 *      Advantage -
 *      Set this argument will save the target a lot of power. You are encouraged to set this value for the sake of power.
 *
 *      Note -
 *      0<=allowed_time_error_shift_mode<=255
 *
 * RETURNS
 *  Successful: created event scheduler pointer.
 *  Fail: system enter fatal error handling.
 * NOTE
 *  (1)This API replaces new_evshed(). And new_evshed() is deprecated,
 *     it will be removed from next release.
 *  (2)It is strongly suggested to call this function only at system initialization stage.
 *     and This is no way to free the event schedule data structure once allocated.
 *  (3)Event scheduler is not thread safe, if you want to share it in multi-task/hisr,
 *     please use lock to protect it.
 *  (4)To reduce power consumption, it's strongly suggested to set allowed_time_error_sleep_mode.
 *  (5)The inaccuracy of event scheduler comes from
 *       schedule delay -  Time lisr, Time HISR, the owner task may be preempted.
 *       Task handling message delay - There may be many ILMs to handle before the event expired ILM gets handled
 *       allowed_time_shift
 *       allowed_time_shift_sleep_mode
 * SEE ALSO
 *  evshed_set_event evshed_cancel_event evshed_timer_handler
 ******************************************************************************/
extern event_scheduler *evshed_create(kal_char *evshed_name, module_type module_id,
                                      kal_uint32 allowed_time_shift, kal_uint16 allowed_time_shift_sleep_mode);
#define HAS_EVSHED_CREATE 1

 /*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *      evshed_set_index
 * DESCRIPTION
 *      Set timer_index to distinguish many event schedulers.
 *      The default timer index is 0.
 * PARAMETERS
 *      es_usr: [IN] event scheduler id returned by evshed_create
 *      timer_index: [IN] timer index given by user
 * RETURNS
 *      None
 ******************************************************************************/
extern void evshed_set_index(event_scheduler *es_usr, kal_uint16 timer_index);
#define HAS_EVSHED_SET_INDEX 1

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *      evshed_get_index
 * DESCRIPTION
 *      Get the index set by evshed_set_index
 * PARAMETERS
 *      expired_ilm: [IN] The ilm sent by expired event and got from task queue
 * RETURNS
 *      Sucessful: The timer index of kal_uint32
 *      Fail: Fatal error if wrong ilm input
 ******************************************************************************/
extern kal_uint16 evshed_get_index(ilm_struct *expired_ilm);
#define HAS_EVSHED_GET_INDEX 1
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  evshed_set_event
 * DESCRIPTION
 *  set an event on event scheduler.
 * PARAMETERS
 *  es: [IN] event scheduler pointer.
 *  event_hf: [IN] the callback function when event timeout.
 *  event_hf_param: [IN] the user supplied argument for event_hf.
 *  elapse_time: [IN] how many system ticks elapses before this event timeout.
 * RETURNS
 *  Successful: return set eventid.
 *  Fail: return NULL.
 * NOTE
 *  System will allocate memory for event id, it will be freed automatically when
 *      a. event is cancelled
 *      b. event expired
 *   It's not allowed to use the event id after above cases.
 *   If the event id is saved, please be careful to reset it.
 * SEE ALSO
 *  evshed_create evshed_cancel_event evshed_timer_handler
 ******************************************************************************/
extern eventid evshed_set_event(event_scheduler *es,
                                kal_timer_func_ptr event_hf,
                                void *event_hf_param,
                                kal_uint32 elapse_time);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  evshed_set_event_userid
 * DESCRIPTION
 *  set an event on event scheduler, and give this event an user id
 * PARAMETERS
 *  es: [IN] event scheduler pointer.
 *  event_hf: [IN] the callback function when event timeout.
 *  event_hf_param: [IN] the user supplied argument for event_hf.
 *  elapse_time: [IN] how many system ticks elapses before this event timeout.
 *  event_user_id: [IN] User can input an id to distinct the events.
 * RETURNS
 *  Successful: return set eventid.
 *  Fail: return NULL.
 * NOTE
 *  System will allocate memory for event id, it will be freed automatically when
 *      a. event is cancelled
 *      b. event expired
 *   It's not allowed to use the event id after above cases.
 *   If the event id is saved, please be careful to reset it.
 * SEE ALSO
 *  evshed_create evshed_cancel_event evshed_timer_handler
 ******************************************************************************/
extern eventid evshed_set_event_userid(event_scheduler *es,
                                kal_timer_func_ptr event_hf,
                                void *event_hf_param,
                                kal_uint32 elapse_time,
                                kal_uint32 event_user_id);
#define HAS_EVSHED_SET_EVENT_USERID 1

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  evshed_get_event_userid
 * DESCRIPTION
 * Get the user id, inputted in evshed_set_event_userid
 * PARAMETERS
 *  user_eventid: [IN] eventid returned by evshed_set_event_userid
 * RETURNS
 *  Successful: returns kal_uint32
 *  Fail: If user_eventid is NULL, fatal error
 * SEE ALSO
 *  evshed_create evshed_cancel_event evshed_timer_handler
 ******************************************************************************/
extern kal_uint32 evshed_get_event_userid(eventid user_eventid);
#define HAS_EVSHED_GET_EVENT_USERID 1
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  evshed_cancel_event
 * DESCRIPTION
 *  cancel a event on event scheduler.
 * PARAMETERS
 *  es: [IN] event scheduler pointer.
 *  eid: [IN,OUT] pointer to event id.
 * RETURNS
 *  Successful: remain ticks before this event expires.
 *  Fail: -1.
 * NOTE
 *  (1)system would reset the event ID (eid) to NULL before returning; however,
 *     caller should pay attention to its privately saved event id
 * SEE ALSO
 *  evshed_create evshed_set_event evshed_timer_handler evshed_delete_all_events
 ******************************************************************************/
extern kal_int32 evshed_cancel_event(event_scheduler *es, eventid *eid);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  evshed_get_remaining_time
 * DESCRIPTION
 *  get remain ticks before this event expires.
 * PARAMETERS
 *  es: [IN] event scheduler pointer.
 *  eid: [IN] event id.
 * RETURNS
 *  Successful: remain ticks before this event expires.
 ******************************************************************************/
extern kal_uint32 evshed_get_remaining_time(event_scheduler *es, eventid eid);

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  evshed_delete_all_events
 * DESCRIPTION
 *  delete and cancel all events on event scheduler.
 * PARAMETERS
 *  es: [IN] event scheduler pointer.
 * RETURNS
 *  N/A
 * SEE ALSO
 *  evshed_create evshed_set_event evshed_timer_handler evshed_delete_all_events
 *****************************************************************************/
extern void evshed_delete_all_events(event_scheduler *es);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  evshed_timer_handler
 * DESCRIPTION
 *  event scheduler main function. It will check all set events status, and call
 *  the callback function if they are expired.
 *
 * PARAMETERS
 *  es: [IN] event scheduler pointer.
 * RETURNS
 *  N/A
 * NOTE
 *  (1)it's not thread-safe. Don't use in parallel.
 *  (2)If an event is expired, the eventid is freed automatically and don't use it any more.
 *     In evshed_timer_handler(), system would execute event registered timeout callback function.
 *     Caller should reset saved event id in registered timeout callback function,
 *     or cause potential bug to cancel wrong timer event.
 * SEE ALSO
 *  evshed_create evshed_set_event evshed_cancel_event evshed_delete_all_events
 *****************************************************************************/
extern void evshed_timer_handler(event_scheduler *es);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  evshed_has_pending_events
 * DESCRIPTION
 *  query there is any event pending (not yet expired).
 * PARAMETERS
 *  es: [IN] event scheduler pointer.
 * RETURNS
 *  return KAL_TRUE or KAL_FALSE.
 * NOTE
 *****************************************************************************/
extern kal_bool evshed_has_pending_events(event_scheduler *es);

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  evshed_suspend_all_events
 * DESCRIPTION
 *  suspend all of the events set on an event scheduler.
 * PARAMETERS
 *  es: [IN] event scheduler pointer.
 * RETURNS
 *  N/A
 * SEE ALSO
 *  evshed_resume_all_events
 *****************************************************************************/
extern void evshed_suspend_all_events(event_scheduler *es);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  evshed_resume_all_events
 * DESCRIPTION
 *  resume all of the events set on an event scheduler.
 * PARAMETERS
 *  es: [IN] event scheduler pointer.
 * RETURNS
 *  N/A
 * SEE ALSO
 *  evshed_suspend_all_events
 *****************************************************************************/
extern void evshed_resume_all_events(event_scheduler *es);

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  evshed_enable_protect_property
 * DESCRIPTION
 *  using mutex to protect the operation of event seheduler to avoid race condition whiler it is 
 *  shared by multi-task
 * PARAMETERS
 *  es: [IN] event scheduler pointer.
 * RETURNS
 *  N/A
 * NOTE
 *  (1) Event scheduler is not thread safe, if you want to share it in multi-task,
 *      Tou can use lock to protect it while using operation of event scheduler.
 *      This API is designed for it. Please call this function after calling evshed_create,
 *      then event scheduler is thread safe without using lock.
 *  (2) If this is called, the "expired" event could not be deleted by evshed_cancel_event()
 * SEE ALSO
 *  evshed_create
 *****************************************************************************/
extern void evshed_enable_protect_property(event_scheduler *es);



/* DOM-NOT_FOR_SDK-BEGIN */
/*******************************************************************************
 * Category 9 : Error Handling
 *******************************************************************************/


/*
 * These functions has been duplicated to several files - .\bootloader\src\bl_portingfunc.c
 * If there's any modification to these functions, please remember to update above file.
 * If you need to duplicate these functions, please update above file list.
 */
#if defined(__UBL__) 

extern void kal_assert_fail(char* expr, char* file, kal_uint32 line, kal_bool isext, kal_uint32 ex1, kal_uint32 ex2, kal_uint32 ex3, ASSERT_DUMP_PARAM_T *dump_param);

#else /* __UBL__ */

#if defined(__MTK_TARGET__)

#if defined(__KAL_ASSERT_LEVEL0__)
extern void kal_assert_fail(void);
#else /* __KAL_ASSERT_LEVEL0__ */

#if defined(__KAL_ASSERT_LEVEL4__)
extern void INT_ExceptionSaveCpuReg(void);
#endif /* __KAL_ASSERT_LEVEL4__ */

#if defined(__KAL_ASSERT_LEVEL2__) || defined(__KAL_ASSERT_LEVEL1__)
extern void kal_assert_fail_line(kal_uint32 line);
extern void kal_assert_fail_ext(kal_uint32 line, kal_uint32 ex1, kal_uint32 ex2, kal_uint32 ex3);
extern void kal_assert_fail_dump(kal_uint32 line, kal_uint32 ex1, kal_uint32 ex2, kal_uint32 ex3, ASSERT_DUMP_PARAM_T *dump_param);
#else
extern void kal_assert_fail_line(char* expr, char* file, kal_uint32 line);
extern void kal_assert_fail_ext(char* expr, char* file, kal_uint32 line, kal_uint32 ex1, kal_uint32 ex2, kal_uint32 ex3);
extern void kal_assert_fail_dump(char* expr, char* file, kal_uint32 line, kal_uint32 ex1, kal_uint32 ex2, kal_uint32 ex3, ASSERT_DUMP_PARAM_T *dump_param);
#endif /* __KAL_ASSERT_LEVEL2__ || __KAL_ASSERT_LEVEL1__ */

#endif /* __KAL_ASSERT_LEVEL0__ */

#else /* __MTK_TARGET__ */

extern void kal_assert_fail(char* expr, char* file, kal_uint32 line, kal_bool isext, kal_uint32 ex1, kal_uint32 ex2, kal_uint32 ex3, ASSERT_DUMP_PARAM_T *dump_param);

#endif /* __MTK_TARGET__  */

#endif /* __UBL__ */

/*
 * Error Handling
 */
/* NOTE: Module Controlled ASSERT Interface, it will be removed from next release.  */
#define DEBUG_ASSERT(expr) do {if(!(expr)) {} } while (0)

/* NOTE : ASSERT() , EXT_ASSERT() is public ,
 * While EXT_ASSERT_DUMP() is auxiliary  
 */
#if defined(__MTK_TARGET__) && !defined(__UBL__)

#if defined(__KAL_ASSERT_LEVEL4__)
#define ASSERT(expr) do {if(!(expr)) { \
                             INT_ExceptionSaveCpuReg(); \
                             kal_assert_fail_line((kal_char *)#expr, (kal_char *)__FILE__, __LINE__); \
                         } \
                     } while (0)
#define EXT_ASSERT(expr, e1, e2, e3) do {if(!(expr)) { \
                                             INT_ExceptionSaveCpuReg(); \
                                             kal_assert_fail_ext((kal_char *)#expr, (kal_char *)__FILE__, __LINE__, (e1), (e2), (e3)); \
                                         } \
                                     } while (0)
#define EXT_ASSERT_DUMP(expr, e1, e2, e3, param) do {if(!(expr)) { \
                                                         INT_ExceptionSaveCpuReg(); \
                                                         kal_assert_fail_dump((kal_char *)#expr, (kal_char *)__FILE__, __LINE__, (e1), (e2), (e3), (param)); \
                                                     } \
                                                 } while (0)
#elif defined(__KAL_ASSERT_LEVEL3__)
#define ASSERT(expr) do {if(!(expr)) kal_assert_fail_line((kal_char *)#expr, (kal_char *)__FILE__, __LINE__); } while (0)
#define EXT_ASSERT(expr, e1, e2, e3) do {if(!(expr)) kal_assert_fail_ext((kal_char *)#expr, (kal_char *)__FILE__, __LINE__, (e1), (e2), (e3)); } while (0)
#define EXT_ASSERT_DUMP(expr, e1, e2, e3, param) do {if(!(expr)) kal_assert_fail_dump((kal_char *)#expr, (kal_char *)__FILE__, __LINE__, (e1), (e2), (e3), (param)); } while (0)
#elif defined(__KAL_ASSERT_LEVEL2__)
#define ASSERT(expr) do {if(!(expr)) kal_assert_fail_line(__LINE__); } while (0)
#define EXT_ASSERT(expr, e1, e2, e3) do {if(!(expr)) kal_assert_fail_ext(__LINE__, (e1), (e2), (e3)); } while (0)
#define EXT_ASSERT_DUMP(expr, e1, e2, e3, param) do {if(!(expr)) kal_assert_fail_dump(__LINE__, (e1), (e2), (e3), (param)); } while (0)
#elif defined(__KAL_ASSERT_LEVEL1__)
#define ASSERT(expr) do {if(!(expr)) kal_assert_fail_line(__LINE__); } while (0)
#define EXT_ASSERT(expr, e1, e2, e3) do {if(!(expr)) kal_assert_fail_line(__LINE__); } while (0)
#define EXT_ASSERT_DUMP(expr, e1, e2, e3, param) do {if(!(expr)) kal_assert_fail_line(__LINE__); } while (0)
#else
#define ASSERT(expr) do {if(!(expr)) {} } while (0)
#define EXT_ASSERT(expr, e1, e2, e3) do {if(!(expr)) kal_assert_fail(); } while (0)
#define EXT_ASSERT_DUMP(expr, e1, e2, e3, param) do {if(!(expr)) kal_assert_fail(); } while (0)
#endif

#else  /* __MTK_TARGET__ && !__UBL__ */

/* align to the highest assert level in MoDIS, no shrinking requirement */
#define ASSERT(expr) do {if(!(expr)) kal_assert_fail((kal_char *)#expr, (kal_char *)__FILE__, __LINE__, KAL_FALSE, 0, 0, 0, NULL); } while (0)
#define EXT_ASSERT(expr, e1, e2, e3) do {if(!(expr)) kal_assert_fail((kal_char *)#expr, (kal_char *)__FILE__, __LINE__, KAL_TRUE, (e1), (e2), (e3), NULL); } while (0)
#define EXT_ASSERT_DUMP(expr, e1, e2, e3, param) do {if(!(expr)) kal_assert_fail((kal_char *)#expr, (kal_char *)__FILE__, __LINE__, KAL_TRUE, (e1), (e2), (e3), (param)); } while (0)

#endif /* __MTK_TARGET__ && !__UBL__ */

/* DOM-NOT_FOR_SDK-END */

#ifdef __BUILD_DOM__
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  ASSERT
 * DESCRIPTION
 *  assert the condition is true, otherwise enter system exception handling.
 * PARAMETERS
 *  expr: [IN] the condition to be evaluated
 * RETURNS
 *  N/A
 * NOTE
 *  (1)The assertion only takes effect when DEBUG_KAL is defined.
 *  (2)No matter DEBUG_KAL is defined or not, the expr will be evaluated.
 * SEE ALSO
 *   EXT_ASSERT EXT_ASSERT_DUMP
 ******************************************************************************/
#define ASSERT(expr) __ASSERT(expr)
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  EXT_ASSERT
 * DESCRIPTION
 *  external assert the condition is true, otherwise enter system exception handling.
 * PARAMETERS
 *  expr: [IN] the condition to be evaluated.
 *  e1: [IN] first extra expression recorded.
 *  e2: [IN] second extra expression recorded.
 *  e3: [IN] third extra expression recorded.
 * RETURNS
 *  N/A
 * NOTE
 *  (1)The assertion takes effect all the time, both DEBUG_KAL and RELEASE_KAL.
 * SEE ALSO
 *   ASSERT EXT_ASSERT_DUMP
 ******************************************************************************/
#define EXT_ASSERT(expr, e1, e2, e3) __EXT_ASSERT(expr, e1, e2, e3)
#endif /*__BUILD_DOM__*/

/* DOM-NOT_FOR_SDK-BEGIN */

/*******************************************************************************
 * Category 10 --- Profiling
 *******************************************************************************/

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_profile_enable
 * DESCRIPTION
 *  enable cpu usage profile.
 * PARAMETERS
 *  N/A
 * RETURNS
 *  N/A
 * SEE ALSO
 *   kal_profile_get_cpu_usage
 ******************************************************************************/
void kal_profile_enable(void);
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_profile_get_cpu_usage
 * DESCRIPTION
 *  get cpu usage percentage, which is a float number at [0.0, 1.0].
 * PARAMETERS
 *  N/A
 * RETURNS
 *  cpu usage percentage.
 * SEE ALSO
 *   kal_profile_enable
 ******************************************************************************/
float kal_profile_get_cpu_usage(void);

/* DOM-NOT_FOR_SDK-END */

/* DOM-NOT_FOR_SDK-BEGIN */
/*******************************************************************************
 * Category 11 : stack sharing
 *******************************************************************************/
/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_lock_current_stack
 * DESCRIPTION
  *  to lock current stack to avoid sharing its memory with other tasks.
 * PARAMETERS
 *  N/A
 * RETURNS
 *  KAL_SUCCESS.
 * NOTE
 *  this API is used when KAL_STACK_SHARING is enable,
 ******************************************************************************/
extern kal_uint32 kal_lock_current_stack();

/*******************************************************************************
 * <GROUP Functions>
 *
 * FUNCTION
 *  kal_unlock_current_stack
 * DESCRIPTION
 *  to unlock current task's stack to sharing its memory with other tasks.
 * PARAMETERS
 *  N/A
 * RETURNS
 *  KAL_SUCCESS.
 * NOTE
 *  this API is used when KAL_STACK_SHARING is enable,
 ******************************************************************************/
extern kal_uint32 kal_unlock_current_stack();
 

/*******************************************************************************
 * Category Last ---
 *******************************************************************************/

/* DOM-NOT_FOR_SDK-END */

#ifdef __cplusplus
}
#endif

#endif  /* _KAL_PUBLIC_API_H */
