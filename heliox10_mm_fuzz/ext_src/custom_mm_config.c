/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
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
/*******************************************************************************
 *
 * Filename:
 * ---------
 * custom_mm_config.c
 *
 * Project:
 * --------
 *   MONZA
 *
 * Description:
 * ------------
 *   This file is used to define the MM configuration.
 *
 * Author:
 * -------
 * -------
 *
 *==============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
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
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
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
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 *
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 *
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
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
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *==============================================================================
 *******************************************************************************/

#include "kal_general_types.h"
#include "kal_public_defs.h"
#include "custom_mm_config.h"
#include "ps_public_enum.h"

/*****************************************************************************
* FUNCTION
*  mm_custom_stay_on_la_of_regional_provisional_service
* DESCRIPTION
*  This function is for customize MM behavior when entering forbidden LA of #12
*
* PARAMETERS
*
* RETURNS
*  MM_STAY_ON_LA_OF_REGIONAL_PROVISIONAL_SERVICE
*      follow spec (enter limited service and stay on forbidden LA of #12)
*  MM_STAY_ON_LA_OF_REGIONAL_PROVISIONAL_ONLY_IF_TEST_SIM_TEST_MODE
*      follow spec (enter limited service and stay on forbidden LA of #12) 
*      only when test sim is inserted or test mode(CTA/FTA/Operator) is enabled
*  MM_NOT_STAY_ON_LA_OF_REGINOAL_PROVISIONAL_SERVICE
*      allow MS directly retry other PLMN/RAT for normal service
* GLOBALS AFFECTED
*   None
*****************************************************************************/
mm_rej_12_handle_enum mm_custom_stay_on_la_of_regional_provisional_service(void)
{
    //suggest to use default setting [MM_STAY_ON_LA_OF_REGIONAL_PROVISIONAL_SERVICE]
    //change this setting might affect the result of FTA or IOT.
    //may only be changed on production version of software after pass all lab test
    if (sbp_query_md_feature(SBP_MM_NOT_STAY_ON_FBLA_FOR_REG_PROV) == KAL_TRUE)
    {
        return MM_STAY_ON_LA_OF_REGIONAL_PROVISIONAL_ONLY_IF_TEST_SIM_TEST_MODE;
    }
    else
    {
        return MM_STAY_ON_LA_OF_REGIONAL_PROVISIONAL_SERVICE;
    }
}

/*****************************************************************************
* FUNCTION
*  mm_custom_allow_rplmn_hplmn_combined_search
* DESCRIPTION
*  This function is used to configure whether search RPLMN and HPLMN together.
*
* PARAMETERS
*
* RETURNS
*  kal_bool
* GLOBALS AFFECTED
*  None
*****************************************************************************/
kal_bool mm_custom_allow_rplmn_hplmn_combined_search(void)
{
    /*if search RPLMN and HPLMN together, it is more quickly to camp on HPLMN,
    and no need to do high priority plmn search later.
    But it may disobey test case 6.2.1.1 in spec 34.123. 
    */
    #if defined(__UMTS_TDD128_MODE__) || defined(__TDD_MODEM__)  /*for TDD project, this compile option is open*/
        return KAL_FALSE;
    #else
        return KAL_TRUE;
    #endif
} 


/*****************************************************************************
* FUNCTION
*  mm_custom_registration_related_setting
* DESCRIPTION
*  This function is used to query registration related setting.
*
* PARAMETERS
*  Which setting
* RETURNS
*  kal_bool
* GLOBALS AFFECTED
*  None
*****************************************************************************/
kal_bool mm_custom_registration_related_setting(mm_setting_enum setting)
{

  switch(setting)
  { 
   
   case MM_ENABLE_LR_REJ111_RETRY:
      {
#ifndef __DISABLE_LR_REJ111_RETRY__   
			  return KAL_TRUE;
#else
			  return KAL_FALSE;
#endif
        break;
      } 
   case MM_ENABLE_HPPLMN_SEARCH_FORCE_RELEASE_PCH_CONNECTION:
	  {	 
#ifndef __DISABLE_HPPLMN_SEARCH_FORCE_RELEASE_PCH_CONNECTION__
			  return KAL_TRUE;
#else
			  return KAL_FALSE;
#endif  
		break;
	  } 
 
   default:
   		break;
  }
  
  return KAL_FALSE;
} 

/* MAUI_03014009 Russia Operator BeeLine request to use ECC with IMEI */
/*****************************************************************************
* FUNCTION
*  mm_custom_force_ecc_with_imei
* DESCRIPTION
*  This function configures emergency call force to use IMEI during phone lock period.
*  default: KAL_FALSE (using TMSI->IMSI->IMEI)
*
* PARAMETERS
*
* RETURNS
*  kal_bool
* GLOBALS AFFECTED
*  None
*****************************************************************************/
kal_bool mm_custom_force_ecc_with_imei(void)
{
    return KAL_FALSE;
}

/* ALPS01451877 UK should be allowed to make emergency calls with expired SIM cards */
const kal_uint32 ECC_IMSI_MCC_LIST[] = {234, 235};
const kal_uint32 ECC_IMSI_MCC_NUM = sizeof(ECC_IMSI_MCC_LIST)/sizeof(kal_uint32);
/*****************************************************************************
* FUNCTION
*   mm_custom_is_try_abnormal_lai_once_more
* DESCRIPTION
*   If abnormal LU 4 times happen, MS will try to search other available and allowable PLMNs. If no other PLMN is found,
*   MS will go back to the abnormal-4-times PLMN and do registration with another 4 attempts.
	(CC) -I./ext_include/ -I./include -c $(CFLAGS) -o $@ $<
*
* PARAMETERS
*   none
* RETURNS
*   kal_bool - indicate if "try abnormal lai once more" is enabled.
* GLOBALS AFFECTED
*   none
*****************************************************************************/
kal_bool mm_custom_is_try_abnormal_lai_once_more(void)
{
    return sbp_query_md_feature(SBP_MM_TRY_ABNORMAL_LAI_ONCE_MORE);
}

/*****************************************************************************
* FUNCTION
*  mm_custom_start_timer_for_mt_mm_conn
* DESCRIPTION
*  This function is used to configure whether start T3240 for page.
*
* PARAMETERS
*
* RETURNS
*  kal_bool
* GLOBALS AFFECTED
*  None
*****************************************************************************/
kal_bool mm_custom_start_timer_for_mt_mm_conn(void)
{
    /*work around CMCC 3G network issue
    1. PS signaling exist, receive page for CS domain
    2. send page response, enter MM_WAIT_FOR_NETWORK_COMMAND
    3. handover to another LA, then no MM or CM message from network
    4. can not process CM request until cs signaling or RRC release
    */
    return KAL_TRUE;
}

/*For Customer Default test plmn. Follows TS34.123 Table 6.2  */
const char *CUSTOM_TEST_PLMN[] = 
    {"00101", "00211", "00321", "00431", "00541", "00651",
     "00761", "00871", "00902", "01012", "01122", "01232" , CUSTOM_TEST_PLMN_SET_END};

const kal_uint32 CUSTOM_TEST_PLMN_NUM = sizeof(CUSTOM_TEST_PLMN)/sizeof(char *);

/*****************************************************************************
* FUNCTION
*  mm_custom_get_erase_forbidden_la_list_timer_period
* DESCRIPTION
*  This function is used to get ERASE_FORBIDDEN_LA_LIST timer period.
*
* PARAMETERS
*  None
*
* RETURNS
*  kal_uint32
*
* GLOBALS AFFECTED
*  None
*
*****************************************************************************/
kal_uint32 mm_custom_get_erase_forbidden_la_list_timer_period(void)
{
    // TS24.008 specifies this timer should be 12~24hr.
    // Default 12hr.
    // Set 0 to disable this timer
    return 12*60*KAL_TICKS_1_MIN;
}

/*************************************************************************
 * In Japan, UE can not perform MO emergency call if UE has not completed registration procedure 
 * (so, MSC does not know MSISDN of mobile originating user), because transferring MSISDN of
 * mobile originating user to emergency authority is mandatory
 *
 * Example:
 * 1.
 * const kal_uint32 LR_BEFORE_ECC_MCC_LIST[] = {440}; // Only in Japan does UE need perform LR before ECC
 * 2.
 * const kal_uint32 LR_BEFORE_ECC_MCC_LIST[] = {NO_MCC_ALLOWED}; // UE shall perform ECC before LR regardless of MCC
 * 3.
 * const kal_uint32 LR_BEFORE_ECC_MCC_LIST[] = {ALL_MCC_ALLOWED}; // UE shall perform LR before ECC regardless of MCC
 *
 *************************************************************************/
#ifdef __MM_PERFORM_LU_BEFORE_ECC__
const kal_uint32 LR_BEFORE_ECC_MCC_LIST[] = {ALL_MCC_ALLOWED};
#else
const kal_uint32 LR_BEFORE_ECC_MCC_LIST[] = {NO_MCC_ALLOWED};
#endif
const kal_uint32 LR_BEFORE_ECC_MCC_NUM = sizeof(LR_BEFORE_ECC_MCC_LIST)/sizeof(kal_uint32);

/*****************************************************************************
* FUNCTION
*  mm_custom_enable_early_oos_ind
* DESCRIPTION
*  If enabled, AP will display OOS when lost coverage and AS start cell reselection
*  If disabled, AP will display OOS after lost coverage and cell reselection failure
*
* PARAMETERS
*
* RETURNS
*  kal_bool
* GLOBALS AFFECTED
*  None
*****************************************************************************/
kal_bool mm_custom_enable_early_oos_ind(void)
{
#ifdef __OOS_EARLY_IND__
    return KAL_TRUE;
#else
    return KAL_FALSE;
#endif
}


/*****************************************************************************
* FUNCTION
*  mm_custom_reattach_for_mt_gprs_detach_other_cause
*
* DESCRIPTION
*  If the UE receives network initiated GPRS detach request of type "re-attach not required",
*  and the reject cause is not defined in SPEC (not one of #2/#3/#6/#7/#8/#11/#12/#13/#14/#15/#25),
*  according to the SPEC, further actions of MS are implementation dependent.
*
* PARAMETERS
*
* RETURNS
*   KAL_TRUE:
*    - The UE will re-attach immediatedly after performing GPRS detach 
*   KAL_FALSE:
*    - The UE will not re-attach immediately after performing GPRS detach
*    - The UE will re-attach when user starts a new data transmission
*
* GLOBALS AFFECTED
*  None
*****************************************************************************/
kal_bool mm_custom_reattach_for_mt_gprs_detach_other_cause(void)
{
#ifdef __GMM_REATTACH_FOR_NW_DETACH_OTHER_CAUSE__
    return KAL_TRUE;
#else
    return KAL_FALSE;
#endif
}

/*****************************************************************************
* FUNCTION
*  mm_custom_report_cell_global_identity
* DESCRIPTION
*  If enabled, modem will update PLMN id, LAC, cell id in 2G connected mode
*  If disabled, modem will not update PLMN id, LAC, cell id in 2G connected mode
*
* PARAMETERS
*
* RETURNS
*  kal_bool
* GLOBALS AFFECTED
*  None
*****************************************************************************/
kal_bool mm_custom_report_cell_global_identity(void)
{
    return KAL_FALSE;
}

/*****************************************************************************
* FUNCTION
*  mm_custom_csmt_flag_in_3g_paging_response
* DESCRIPTION
*  If TRUE, modem encode Additional Parameter in 3G Paging Response and turn on CSMT flag
*  If FALSE, modem not encode Additional Paramter in 3G Paging Response.
*
* PARAMETERS
*
* RETURNS
*  kal_bool
* GLOBALS AFFECTED
*  None
*****************************************************************************/
kal_bool mm_custom_csmt_flag_in_3g_paging_response(void)
{
#if defined(__DISABLE_CSFB_PAGE_CSMT__)
    return KAL_FALSE;
#elif defined(__UMTS_TDD128_MODE__)
    return KAL_TRUE;
#else
    return KAL_FALSE; // default off in FDD
#endif
}

/*****************************************************************************
* FUNCTION
*  mm_custom_enable_dynamic_set_modem2_imei
* DESCRIPTION
*  CMCC requires: Two Modems of TDD GEMINI UE shall use the same IMEI in CMCC Network.
*  And by FT experience, Core Network may reject UE if two modems use the same IMEi.
*  The feature implement: 
*      In China network, two modems use the same IMEI.
*      In other network, two modems use different IMEI.
*
* PARAMETERS
*
* RETURNS
*  KAL_TRUE: The feature is enabled.
    KAL_FALSE: The feature is disabled. In all networks, two modems use the SAME IMEI.
*  None
*****************************************************************************/
kal_bool mm_custom_enable_dynamic_set_modem2_imei(void)
{
#if defined(__UMTS_TDD128_MODE__)||defined(__TDD_2G_OP01__) 
    return KAL_TRUE;
#else
    return KAL_FALSE;
#endif
}

/*****************************************************************************
* FUNCTION
*  mm_custom_report_reg_when_csfb_ecc_lu_needed
* DESCRIPTION
*  For 4G23 CSFB ECC and LU needed, UE may delay LU until ECC end.
*  During ECC, no registration result will report to AP due to LU is pending.
*  AP will keep displaying 4G icon.
*  To solve this problem, we provide this function for RAT icon display when registration status is unknown.
* PARAMETERS
*   current_plmn_type  PLMN type of current camp on cell.
* RETURNS
*   KAL_TRUE:  Display registered on 2/3G.
*   KAL_FALSE: Display network lost.
*  None
*****************************************************************************/
kal_bool mm_custom_report_reg_when_csfb_ecc_lu_delayed(mm_custom_plmn_type current_plmn_type)
{
    switch (current_plmn_type)
    {
        case MM_CUSTOM_HPLMN:
        case MM_CUSTOM_R_E_PLMN:
            return KAL_TRUE;
        case MM_CUSTOM_UNKNOWN_PLMN_TYPE:
        default:
            return KAL_FALSE;
    }
}

/*************************************************************************
 * Ignore Reject cause 7, GPRS serive not allowed, in ATTACH REJECT or 
 * in ROUTING AREA UPDATING REJECT message when roaming. Reject Cause 
 * 14, GPRS serive not allowed in this PLMN, insteads of.
 * 
 * - IGNORE_GPRS_SERVICE_NOT_ALLOWED_WHEN_ROAMING_OPERATOR
 *     - If PLMN is defined in the list, UE take action as receiving reject
 *        cause 14 when UE receive ATTACH REJECT or ROUTING AREA UPDATING
 *        REJECT message with cause 7 and roaming.
 * 
 *************************************************************************/
#ifdef __GMM_CELCOM_IGNORE_GPRS_SERVICE_NOT_ALLOWED_WHEN_ROAMING__
const char *IGNORE_GPRS_SERVICE_NOT_ALLOWED_WHEN_ROAMING_OPERATOR[] = {"50219F", IGNORE_GPRS_SERVICE_NOT_ALLOWED_WHEN_ROAMING_OPERATOR_SET_END};
#else
const char *IGNORE_GPRS_SERVICE_NOT_ALLOWED_WHEN_ROAMING_OPERATOR[] = {IGNORE_GPRS_SERVICE_NOT_ALLOWED_WHEN_ROAMING_OPERATOR_SET_END};
#endif

const kal_uint32 IGNORE_GPRS_SERVICE_NOT_ALLOWED_WHEN_ROAMING_OPERATOR_NUM = sizeof(IGNORE_GPRS_SERVICE_NOT_ALLOWED_WHEN_ROAMING_OPERATOR)/sizeof(char *);

/*************************************************************************
 * Some operators cannot decode IEs for SRVCC correctly brought in attach/RAU request
 * (i.e. MS Classmark2/MS Classmark3/Supported Codecs)
 *
 * - DISABLE_SRVCC_IE_PLMN
 *   - Do not bring new IEs for SRVCC in Attach/RAU request while trying registration on PLMNs specified in this array
 * 
 *************************************************************************/
const char *DISABLE_SRVCC_IE_PLMN[] = {"40468F", DISABLE_SRVCC_IE_PLMN_SET_END};
const kal_uint32 DISABLE_SRVCC_IE_PLMN_NUM = sizeof(DISABLE_SRVCC_IE_PLMN)/sizeof(char *);


