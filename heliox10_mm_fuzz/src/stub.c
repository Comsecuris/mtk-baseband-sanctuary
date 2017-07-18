#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "kal_public_defs.h"
//void bit_stream_init() { puts("bit_stream_init hit!");return;}
int check_sim_card_status() { puts("check_sim_card_status hit!"); return 2;} // normal sim}
int check_sim_status() { return 3;} //ready return 0;//not ready}
//void construct_int_local_para() { puts("construct_int_local_para hit!");exit(1);}
//void construct_int_peer_buff() { puts("construct_int_peer_buff hit!");exit(1);}
#define CUSTOM_TEST_PLMN_SET_END "FFFFFF"
const char *CUSTOM_TEST_PLMN[] = 
    {"00101", "00211", "00321", "00431", "00541", "00651",
     "00761", "00871", "00902", "01012", "01122", "01232" , CUSTOM_TEST_PLMN_SET_END};

const uint32_t CUSTOM_TEST_PLMN_NUM = sizeof(CUSTOM_TEST_PLMN)/sizeof(char *);

//void destroy_int_ilm() { puts("destroy_int_ilm hit!");exit(1);}
//void dhl_brief_trace() { puts("dhl_brief_trace hit!");exit(1);}
void dhl_EM_logger() { puts("dhl_EM_logger hit!");}
void dhl_peer_trace() { puts("dhl_peer_trace hit!");}
#define DISABLE_SRVCC_IE_PLMN_SET_END "FFFFFF"
const char *DISABLE_SRVCC_IE_PLMN[] = {"40468F", DISABLE_SRVCC_IE_PLMN_SET_END};
const uint32_t DISABLE_SRVCC_IE_PLMN_NUM = sizeof(DISABLE_SRVCC_IE_PLMN)/sizeof(char *);

const uint32_t ECC_IMSI_MCC_LIST[] = {234, 235};
const uint32_t ECC_IMSI_MCC_NUM = sizeof(ECC_IMSI_MCC_LIST)/sizeof(uint32_t);


//void evshed_cancel_event() { puts("evshed_cancel_event hit!");exit(1);}
//void evshed_create() { puts("evshed_create hit!");exit(1);}
uint32_t evshed_get_index() { puts("evshed_get_index hit!");return 0;}
//void evshed_get_remaining_time() { puts("evshed_get_remaining_time hit!");exit(1);}
//void evshed_set_event() { puts("evshed_set_event hit!");exit(1);}
void evshed_set_index() { puts("evshed_set_index hit!");}
//void evshed_timer_handler() { puts("evshed_timer_handler hit!");exit(1);}
//void _exit() { puts("_exit hit!");exit(1);}
//void free_ctrl_buffer_ext() { puts("free_ctrl_buffer_ext hit!");exit(1);}
//void free_int_local_para() { puts("free_int_local_para hit!");exit(1);}
//void free_int_peer_buff() { puts("free_int_peer_buff hit!");exit(1);}
//void get_ctrl_buffer_ext() { puts("get_ctrl_buffer_ext hit!");exit(1);}
//void get_peer_buff_pdu() { puts("get_peer_buff_pdu hit!");exit(1);}
//void hold_local_para() { puts("hold_local_para hit!");exit(1);}
//void hold_peer_buff() { puts("hold_peer_buff hit!");exit(1);}
#define IGNORE_GPRS_SERVICE_NOT_ALLOWED_WHEN_ROAMING_OPERATOR_SET_END "FFFFFF"
const char *IGNORE_GPRS_SERVICE_NOT_ALLOWED_WHEN_ROAMING_OPERATOR[] = {"50219F", IGNORE_GPRS_SERVICE_NOT_ALLOWED_WHEN_ROAMING_OPERATOR_SET_END};
const uint32_t IGNORE_GPRS_SERVICE_NOT_ALLOWED_WHEN_ROAMING_OPERATOR_NUM = sizeof(IGNORE_GPRS_SERVICE_NOT_ALLOWED_WHEN_ROAMING_OPERATOR)/sizeof(char *);

int is_ps_conf_test_xta_mode() { puts("is_ps_conf_test_xta_mode hit!");return 0;}
int is_vsim_on() { puts("is_vsim_on hit!");return 0;}
void kal_assert_fail_ext() { puts("kal_assert_fail_ext hit!");exit(1);}
void kal_assert_fail_line() { puts("kal_assert_fail_line hit!");exit(1);}
//void kal_itoa() { puts("kal_itoa hit!");exit(1);}
int kal_retrieve_eg_events() { puts("kal_retrieve_eg_events hit!");return 0;}
void kal_set_active_module_id(uint16_t id) { puts("kal_set_active_module_id hit!");}

uint32_t l4c_gemini_get_actual_sim_id(uint32_t sim) { puts("l4c_gemini_get_actual_sim_id hit!");return 0;}

// arbitrary sized linear queue
// uses bins to store same sized object
// could be reimplemented to detect overflows to other bins
//void lcd_lqueue_index() { puts("lcd_lqueue_index hit!");exit(1);}
//void lcd_lqueue_init() { puts("lcd_lqueue_init hit!");exit(1);}
//void lcd_lqueue_insert_at_front() { puts("lcd_lqueue_insert_at_front hit!");exit(1);}
//void lcd_lqueue_insert_at_rear() { puts("lcd_lqueue_insert_at_rear hit!");exit(1);}
//void lcd_lqueue_is_empty() { puts("lcd_lqueue_is_empty hit!");exit(1);}
//void lcd_lqueue_num_of_items() { puts("lcd_lqueue_num_of_items hit!");exit(1);}
//void lcd_lqueue_remove() { puts("lcd_lqueue_remove hit!");exit(1);}
//void lcd_lqueue_remove_rear() { puts("lcd_lqueue_remove_rear hit!");exit(1);}


#define ALL_MCC_ALLOWED 0xfff
const uint32_t LR_BEFORE_ECC_MCC_LIST[] = {ALL_MCC_ALLOWED};
const uint32_t LR_BEFORE_ECC_MCC_NUM = sizeof(LR_BEFORE_ECC_MCC_LIST)/sizeof(uint32_t);
//void LR_BEFORE_ECC_MCC_LIST() { puts("LR_BEFORE_ECC_MCC_LIST hit!");exit(1);}
//void LR_BEFORE_ECC_MCC_NUM() { puts("LR_BEFORE_ECC_MCC_NUM hit!");exit(1);}

// mediatech coding/decoding engine
// need to pull in libmcd.a we want to fuzz this
//void mcd_init() { puts("mcd_init hit!");exit(1);}
//void mcd_pack() { puts("mcd_pack hit!");exit(1);}
//void mcd_pseudo_alloc() { puts("mcd_pseudo_alloc hit!");exit(1);}
//void mcd_unpack() { puts("mcd_unpack hit!");exit(1);}
//void mcd_update_plmn() { puts("mcd_update_plmn hit!");exit(1);}

// custom_mm_config.c either compiled from tree, mangled or emitted
// values taken from idb
int mm_custom_csmt_flag_in_3g_paging_response() { puts("mm_custom_csmt_flag_in_3g_paging_response hit!");return 0;}
int mm_custom_enable_early_oos_ind() { puts("mm_custom_enable_early_oos_ind hit!");return 0;}
int mm_custom_force_ecc_with_imei() { puts("mm_custom_force_ecc_with_imei hit!");return 0;}
uint32_t mm_custom_get_erase_forbidden_la_list_timer_period() { puts("mm_custom_get_erase_forbidden_la_list_timer_period hit!");return 0x83d600;}
int mm_custom_reattach_for_mt_gprs_detach_other_cause() { puts("mm_custom_reattach_for_mt_gprs_detach_other_cause hit!");return 0;}
int mm_custom_registration_related_setting(char val) { puts("mm_custom_registration_related_setting hit!");if(val==1)return 1;else return 0;}
int mm_custom_report_cell_global_identity() { puts("mm_custom_report_cell_global_identity hit!");return 0;}
int mm_custom_report_reg_when_csfb_ecc_lu_delayed(char val) { puts("mm_custom_report_reg_when_csfb_ecc_lu_delayed hit!");if(val==1  || val==2)return 1;else return 0;}
int mm_custom_start_timer_for_mt_mm_conn() { puts("mm_custom_start_timer_for_mt_mm_conn hit!");return 1;}
int mm_custom_stay_on_la_of_regional_provisional_service() { puts("mm_custom_stay_on_la_of_regional_provisional_service hit!");return 2;}
// pulled from libmrs.a
/*
void mrs_afr_get_csfb_status() { puts("mrs_afr_get_csfb_status hit!");exit(1);}
void mrs_afr_set_csfb_status() { puts("mrs_afr_set_csfb_status hit!");exit(1);}
void mrs_emm_get_srcvv() { puts("mrs_emm_get_srcvv hit!");exit(1);}
void mrs_emm_get_ue_nw_cap() { puts("mrs_emm_get_ue_nw_cap hit!");exit(1);}
void mrs_gas_get_2g4_ps_ho_cap() { puts("mrs_gas_get_2g4_ps_ho_cap hit!");exit(1);}
void mrs_gas_get_classmark2() { puts("mrs_gas_get_classmark2 hit!");exit(1);}
void mrs_gas_get_classmark3() { puts("mrs_gas_get_classmark3 hit!");exit(1);}
void mrs_gas_get_classmark3msg_len() { puts("mrs_gas_get_classmark3msg_len hit!");exit(1);}
void mrs_gas_get_radio_access_cap() { puts("mrs_gas_get_radio_access_cap hit!");exit(1);}
void mrs_get_as_band_setting() { puts("mrs_get_as_band_setting hit!");exit(1);}
void mrs_get_csfb_enhancement_status() { puts("mrs_get_csfb_enhancement_status hit!");exit(1);}
void mrs_mm_get_ms_nw_cap() { puts("mrs_mm_get_ms_nw_cap hit!");exit(1);}
void mrs_mm_get_supported_codec_list() { puts("mrs_mm_get_supported_codec_list hit!");exit(1);}
void mrs_mm_set_epc_cap() { puts("mrs_mm_set_epc_cap hit!");exit(1);}
void mrs_uas_get_irat_ho_info() { puts("mrs_uas_get_irat_ho_info hit!");exit(1);}
*/
// wait for a message to this task, be required to return afl input
int32_t msg_receive_extq() { puts("msg_receive_extq hit!");exit(1);}
// send a message to another layer if srcmod == dst mod send to internal queue
int32_t msg_send6() { puts("msg_send6 hit!");return 1;}


int32_t RRCE_Is_Capability_Enable() { puts("RRCE_Is_Capability_Enable hit!");return 1;}
int32_t RRC_IsConnectedState() { puts("RRC_IsConnectedState hit!");return 1;}

// init with kal_create_event_grp("RSVA_EVG")
void* rsva_evg;
void rsva_evg_free_slot() { puts("rsva_evg_free_slot hit!");}
uint32_t rsva_evg_get_available_ack_slot() { puts("rsva_evg_get_available_ack_slot hit!");return 2;}

uint32_t sbp_query_md_feature() { puts("sbp_query_md_feature hit!");return 1;}
// support everyting
uint32_t sim_service_table_query() { puts("sim_service_table_query hit!");return 1;}
void tst_sys_trace(char* info) { printf("tst_sys_trace hit: %s\n", info);}
uint32_t upcm_get_pending_ul_data_status() { puts("upcm_get_pending_ul_data_status hit!");return 0;}

//more

//void destroy_int_ilm() { puts("destroy_int_ilm hit!");exit(1);}
// static bss var, pulled from object file
//void mcd_table_l4() { puts("mcd_table_l4 hit!");exit(1);}

//LIB mrs deps

//most likely in libuas (asn) 
//linking libuas pulls in waay to much crap

//this 2 functions could be interesting but the cost of pulling it in is too high
void AsnEncode_RRC_InterRATHandoverInfo() { puts("AsnEncode_RRC_InterRATHandoverInfo hit!");exit(1);}
void AsnEncode_RRC_UE_RadioAccessCapabilityInfo() { puts("AsnEncode_RRC_UE_RadioAccessCapabilityInfo hit!");exit(1);}
int int_DB_INTER_RAT_V390NCE_exists() { puts("int_DB_INTER_RAT_V390NCE_exists hit!");return 0;}
void int_DB_INTER_RAT_V390NCE_get() { puts("int_DB_INTER_RAT_V390NCE_get hit!");exit(1);}
int int_DB_RADIO_ACCESS_CAP_exists() { puts("int_DB_RADIO_ACCESS_CAP_exists hit!");return 0;}
void int_DB_RADIO_ACCESS_CAP_get() { puts("int_DB_RADIO_ACCESS_CAP_get hit!");exit(1);}
int int_DB_USIMSECURITY_exists() { puts("int_DB_USIMSECURITY_exists hit!");return 0;}
void int_DB_USIMSECURITY_getRef() { puts("int_DB_USIMSECURITY_getRef hit!");exit(1);}
int RRC_DB_Radio_Access_Capability_ue_RadioAccessCapability_v370ext_isValid(uint32_t* a) { puts("RRC_DB_Radio_Access_Capability_ue_RadioAccessCapability_v370ext_isValid hit!");return *a & 1;}
int RRC_DB_USIMSecurity_startCS_isValid(uint32_t* a) { puts("RRC_DB_USIMSecurity_startCS_isValid hit!");return (*a &0x100)==1;}
int RRC_DB_USIMSecurity_startPS_isValid(uint32_t *a) { puts("RRC_DB_USIMSecurity_startPS_isValid hit!");return (*a &0x80)==1;}
int RRC_Handle_NetworkIssue() { puts("RRC_Handle_NetworkIssue hit!");return 1;}
int RRC_InterRATHandoverInfo_v590ext_IEs_ue_RadioAccessCapabilityComp_isValid(uint32_t* a) { puts("RRC_InterRATHandoverInfo_v590ext_IEs_ue_RadioAccessCapabilityComp_isValid hit!");return *a & 1;}
int RRC_InterRATHandoverInfo_v690ext_IEs_ue_RadioAccessCapabilityComp_isValid(uint32_t* a) { puts("RRC_InterRATHandoverInfo_v690ext_IEs_ue_RadioAccessCapabilityComp_isValid hit!");return *a & 1;}
int RRC_InterRATHandoverInfo_v770ext_IEs_ue_RadioAccessCapabilityComp_isValid(uint32_t* a) { puts("RRC_InterRATHandoverInfo_v770ext_IEs_ue_RadioAccessCapabilityComp_isValid hit!");return (*a &2)==1;}
// this could also be interesting
uint32_t usime_set_classmark2_and_3(uint32_t a) { puts("usime_set_classmark2_and_3 hit!");return a;}
uint32_t usime_set_UAS_capability() { puts("usime_set_UAS_capability hit!");return 0;}

// TODO custom ASN
//compiled from the source files
/*
void AsnDecodeFree() { puts("AsnDecodeFree hit!");exit(1);}
void AsnEncodeAlloc() { puts("AsnEncodeAlloc hit!");exit(1);}
void AsnEncodeFree() { puts("AsnEncodeFree hit!");exit(1);}
void AsnError() { puts("AsnError hit!");exit(1);}
void AsnFreeDecoded() { puts("AsnFreeDecoded hit!");exit(1);}
void AsnRootDecodeAlloc() { puts("AsnRootDecodeAlloc hit!");exit(1);}
//?
void getBits() { puts("getBits hit!");exit(1);}
void getLongBits() { puts("getLongBits hit!");exit(1);}
void getShortBits() { puts("getShortBits hit!");exit(1);}
void flushFifo() { puts("flushFifo hit!");exit(1);}
void initFifo() { puts("initFifo hit!");exit(1);}
void putBits() { puts("putBits hit!");exit(1);}
void putLongBits() { puts("putLongBits hit!");exit(1);}
void putShortBits() { puts("putShortBits hit!");exit(1);}
void AsnDecodeAlloc() { puts("AsnDecodeAlloc hit!");exit(1);}
void asnMemAlloc() { puts("asnMemAlloc hit!");exit(1);}
void asnMemCopy() { puts("asnMemCopy hit!");exit(1);}
void asnMemFree() { puts("asnMemFree hit!");exit(1);}
void asnMemGetMaxSizeTolerance() { puts("asnMemGetMaxSizeTolerance hit!");exit(1);}
void asnMemSetMaxSizeTolerance() { puts("asnMemSetMaxSizeTolerance hit!");exit(1);}
*/
// these are from libscsi.a
/*
void Scsi_FreqRepositoryInitFromNVRAM() { puts("Scsi_FreqRepositoryInitFromNVRAM hit!");exit(1);}
void Scsi_initFromNVRAM() { puts("Scsi_initFromNVRAM hit!");exit(1);}
void Scsi_prevVisitedCellInitFromNVRAM() { puts("Scsi_prevVisitedCellInitFromNVRAM hit!");exit(1);}
void Scsi_SE_ComposeGsmBandBitmask() { puts("Scsi_SE_ComposeGsmBandBitmask hit!");exit(1);}
void Scsi_SE_ComposeLteBandBitmask() { puts("Scsi_SE_ComposeLteBandBitmask hit!");exit(1);}
void Scsi_SE_ComposeUmtsBandBitmask() { puts("Scsi_SE_ComposeUmtsBandBitmask hit!");exit(1);}
void Scsi_SE_retrieveGsmBandBitmask() { puts("Scsi_SE_retrieveGsmBandBitmask hit!");exit(1);}
void Scsi_SE_retrieveLteBandBitmask() { puts("Scsi_SE_retrieveLteBandBitmask hit!");exit(1);}
void Scsi_SE_retrieveUmtsBandBitmask() { puts("Scsi_SE_retrieveUmtsBandBitmask hit!");exit(1);}
void Scsi_SE_retrieveUmtsBandListInfo() { puts("Scsi_SE_retrieveUmtsBandListInfo hit!");exit(1);}
*/

void assert_bypass_sys_trace() { puts("assert_bypass_sys_trace hit!");exit(1);}

// pulled in from object files
//void bit_stream_move_back() { puts("bit_stream_move_back hit!");exit(1);}
//void bit_stream_read() { puts("bit_stream_read hit!");exit(1);}
//void bit_stream_write() { puts("bit_stream_write hit!");exit(1);}
void custom_check_white_list(kal_bool * is_gsm_white_list,kal_bool * is_umts_white_list,kal_uint32 plmn_id)
{puts("custom_check_white_list hit!"); *is_gsm_white_list = KAL_TRUE; *is_umts_white_list=KAL_TRUE;}
    
void dhl_internal_trace() { puts("dhl_internal_trace hit!");}
kal_bool EL1_IS_4G_FDD_EXIST() { puts("EL1_IS_4G_FDD_EXIST hit!");return 1;}
kal_bool EL1_IS_4G_TDD_EXIST() { puts("EL1_IS_4G_TDD_EXIST hit!");return 1;}

// in libephy implemented
//void EPHY_RF_GET_BAND_SUPPORT_MASK() { puts("EPHY_RF_GET_BAND_SUPPORT_MASK hit!");exit(1);}

// mutex api
int dummy;
int* kal_create_mutex() { puts("kal_create_mutex hit!");return &dummy;}
uint32_t kal_get_systicks() { puts("kal_get_systicks hit!");clock();}
void kal_give_mutex() { puts("kal_give_mutex hit!");}
uint32_t kal_milli_secs_to_ticks(uint32_t secs) { puts("kal_milli_secs_to_ticks hit!");return secs*(CLOCKS_PER_SEC/1000);}
void kal_take_mutex() { puts("kal_take_mutex hit!");}

// ps conformance test mode
uint32_t query_ps_conf_test_mode() { puts("query_ps_conf_test_mode hit!");return 0;}
//
//void rr_arfcn_PCS_band_tag() { puts("rr_arfcn_PCS_band_tag hit!");exit(1);}
uint32_t rr_mrs_is_arfcn_band_supported() { puts("rr_mrs_is_arfcn_band_supported hit!");return 1;}
// this is used to querry modem config 
char sbpconfig[16] = {0};
uint8_t sbp_query_md_feature_data(uint32_t in) { puts("sbp_query_md_feature_data hit!");if (in > 8)exit(1);else return sbpconfig[in+4];}
// return 4 as USIM
uint32_t sim_query_type() { puts("sim_query_type hit!");return 4;}
void UL1D_UeBandCapabilityEx() { puts("UL1D_UeBandCapabilityEx hit!");return;}

// enh mutex
int enhdummy;
int* kal_create_enh_mutex() { puts("kal_create_enh_mutex hit!");return &enhdummy;}
void kal_give_enh_mutex() { puts("kal_give_enh_mutex hit!");}
void kal_take_enh_mutex() { puts("kal_take_enh_mutex hit!");}

//################ LIBUAS #################
/*
int array[0x100] = {0};
// pointer from rsvas context return valid pointer and hope for the best 
int* as_etws_owner_query() { puts("as_etws_owner_query hit!");return array;}

void as_service_sem_occupy() { puts("as_service_sem_occupy hit!");}
void as_service_sem_query() { puts("as_service_sem_query hit!");}
void as_service_sem_release() { puts("as_service_sem_release hit!");}
void as_service_sem_transfer() { puts("as_service_sem_transfer hit!");}
int as_update_etws_channel_priority() { puts("as_update_etws_channel_priority hit!");return 1;}

// supposed to be in bitops.obj
//void copy_bits16() { puts("copy_bits16 hit!");exit(1);}
//arm specific
void cp15_drain_write_buffer() { puts("cp15_drain_write_buffer hit!");}

//in libul2.a TODO
void Crlc_QuerryDLPduSize() { puts("Crlc_QuerryDLPduSize hit!");}
void dhl_log_primitive6() { puts("dhl_log_primitive6 hit!");exit(1);}
void DlistCount() { puts("DlistCount hit!");exit(1);}
void DlistDelete() { puts("DlistDelete hit!");exit(1);}
void DlistFirst() { puts("DlistFirst hit!");exit(1);}
void DlistInit() { puts("DlistInit hit!");exit(1);}
void DlistInsertAtEnd() { puts("DlistInsertAtEnd hit!");exit(1);}
void DlistNext() { puts("DlistNext hit!");exit(1);}
void eSM_AddPermanentInstance() { puts("eSM_AddPermanentInstance hit!");exit(1);}
void eSM_EventLookup() { puts("eSM_EventLookup hit!");exit(1);}
void eSM_ExecuteContext() { puts("eSM_ExecuteContext hit!");exit(1);}
void eSM_GetInstanceCurrentState() { puts("eSM_GetInstanceCurrentState hit!");exit(1);}
void eSM_GetInstancePointer() { puts("eSM_GetInstancePointer hit!");exit(1);}
void eSM_IgnoreEvent() { puts("eSM_IgnoreEvent hit!");exit(1);}
void eSM_InitContext() { puts("eSM_InitContext hit!");exit(1);}
void eSM_InvalidEvent() { puts("eSM_InvalidEvent hit!");exit(1);}
void eSM_PopulateProcessServiceSM() { puts("eSM_PopulateProcessServiceSM hit!");exit(1);}
void eSM_ResetFSM() { puts("eSM_ResetFSM hit!");exit(1);}
void eSM_SavedEvent() { puts("eSM_SavedEvent hit!");exit(1);}
void eSM_WarningEvent() { puts("eSM_WarningEvent hit!");exit(1);}
void evshed_delete_all_events() { puts("evshed_delete_all_events hit!");exit(1);}
void evshed_set_event_userid() { puts("evshed_set_event_userid hit!");exit(1);}
void fSM_ClearSavedEventQueue() { puts("fSM_ClearSavedEventQueue hit!");exit(1);}
void fSM_DeleteSpecificSavedEvent() { puts("fSM_DeleteSpecificSavedEvent hit!");exit(1);}
void fSM_HandleSavedEvents() { puts("fSM_HandleSavedEvents hit!");exit(1);}
void fSM_LookUpSpecificSavedEvent() { puts("fSM_LookUpSpecificSavedEvent hit!");exit(1);}
void get_COUNT_C_ActivationTimeFromMAC() { puts("get_COUNT_C_ActivationTimeFromMAC hit!");exit(1);}
void Get_CountC_with_CountC_status() { puts("Get_CountC_with_CountC_status hit!");exit(1);}
void GetUperLengthDeterminant() { puts("GetUperLengthDeterminant hit!");exit(1);}
void is_as_service_occupy_this_domain() { puts("is_as_service_occupy_this_domain hit!");exit(1);}
void is_sim1_test_sim() { puts("is_sim1_test_sim hit!");exit(1);}
void is_test_sim() { puts("is_test_sim hit!");exit(1);}
void __kal_adm_alloc() { puts("__kal_adm_alloc hit!");exit(1);}
void kal_adm_create() { puts("kal_adm_create hit!");exit(1);}
void kal_adm_delete() { puts("kal_adm_delete hit!");exit(1);}
void kal_adm_free() { puts("kal_adm_free hit!");exit(1);}
void kal_adm_get_total_left_size() { puts("kal_adm_get_total_left_size hit!");exit(1);}
void kal_get_active_module_id() { puts("kal_get_active_module_id hit!");exit(1);}
void kal_get_remaining_time() { puts("kal_get_remaining_time hit!");exit(1);}
void kal_internal_trace() { puts("kal_internal_trace hit!");exit(1);}
void kal_secs_to_ticks() { puts("kal_secs_to_ticks hit!");exit(1);}
void kal_ticks_to_milli_secs() { puts("kal_ticks_to_milli_secs hit!");exit(1);}
void kal_ticks_to_secs() { puts("kal_ticks_to_secs hit!");exit(1);}
void lcd_cqueue_delete_all() { puts("lcd_cqueue_delete_all hit!");exit(1);}
void lcd_cqueue_index() { puts("lcd_cqueue_index hit!");exit(1);}
void lcd_cqueue_init() { puts("lcd_cqueue_init hit!");exit(1);}
void lcd_cqueue_insert() { puts("lcd_cqueue_insert hit!");exit(1);}
void lcd_cqueue_insert_front() { puts("lcd_cqueue_insert_front hit!");exit(1);}
void lcd_cqueue_num_of_items() { puts("lcd_cqueue_num_of_items hit!");exit(1);}
void lcd_cqueue_remove() { puts("lcd_cqueue_remove hit!");exit(1);}
void msg_receive_intq() { puts("msg_receive_intq hit!");exit(1);}
void msg_send_to_int_head6() { puts("msg_send_to_int_head6 hit!");exit(1);}
void prepend_to_peer_buff() { puts("prepend_to_peer_buff hit!");exit(1);}
void PutUperLengthDeterminant() { puts("PutUperLengthDeterminant hit!");exit(1);}
void query_is_noncached_ram() { puts("query_is_noncached_ram hit!");exit(1);}
void query_ps_conf_test_profile_setting() { puts("query_ps_conf_test_profile_setting hit!");exit(1);}
void stack_init_timer() { puts("stack_init_timer hit!");exit(1);}
void stack_is_time_out_valid() { puts("stack_is_time_out_valid hit!");exit(1);}
void stack_process_time_out() { puts("stack_process_time_out hit!");exit(1);}
void stack_start_timer() { puts("stack_start_timer hit!");exit(1);}
void stack_stop_timer() { puts("stack_stop_timer hit!");exit(1);}
void stack_timer_status() { puts("stack_timer_status hit!");exit(1);}
void stack_timer_user_view_status() { puts("stack_timer_user_view_status hit!");exit(1);}
void tst_log_primitive() { puts("tst_log_primitive hit!");exit(1);}
void uas_custom_get_specific_channel() { puts("uas_custom_get_specific_channel hit!");exit(1);}
void uas_custom_is_specific_channel_srch() { puts("uas_custom_is_specific_channel_srch hit!");exit(1);}
void uas_dch_em_umts_cell_info_ind_period() { puts("uas_dch_em_umts_cell_info_ind_period hit!");exit(1);}
void uas_get_power_ind_period_fachdch() { puts("uas_get_power_ind_period_fachdch hit!");exit(1);}
void uas_get_power_ind_period_idlepch() { puts("uas_get_power_ind_period_idlepch hit!");exit(1);}
void uas_nbr_cell_info_ind_period() { puts("uas_nbr_cell_info_ind_period hit!");exit(1);}
void uas_nbr_cell_info_rep_cell_num() { puts("uas_nbr_cell_info_rep_cell_num hit!");exit(1);}
void uas_ul_signaling_get_peer_buff() { puts("uas_ul_signaling_get_peer_buff hit!");exit(1);}
void UL1_CEDCH_Check_Started() { puts("UL1_CEDCH_Check_Started hit!");exit(1);}
void UL1_Compare_CFN_SFN() { puts("UL1_Compare_CFN_SFN hit!");exit(1);}
void UL1_CurrAndPendingConfigTGPS() { puts("UL1_CurrAndPendingConfigTGPS hit!");exit(1);}
void UL1_CurrAndPendingTGPS_Status_byTGMP() { puts("UL1_CurrAndPendingTGPS_Status_byTGMP hit!");exit(1);}
void UL1D_Check_ASU() { puts("UL1D_Check_ASU hit!");exit(1);}
void UL1D_Get_FDD_HSPA_Phy_Category() { puts("UL1D_Get_FDD_HSPA_Phy_Category hit!");exit(1);}
void UL1D_Get_FDD_HSPA_Phy_Category_Extension() { puts("UL1D_Get_FDD_HSPA_Phy_Category_Extension hit!");exit(1);}
void UL1D_MEAS_Check_Adjacent_Freq() { puts("UL1D_MEAS_Check_Adjacent_Freq hit!");exit(1);}
void UL1D_OTD_Calculation() { puts("UL1D_OTD_Calculation hit!");exit(1);}
void UL1D_RRC_UlUarfcnToFrequency() { puts("UL1D_RRC_UlUarfcnToFrequency hit!");exit(1);}
void UL1D_RxDualCarrier_Check() { puts("UL1D_RxDualCarrier_Check hit!");exit(1);}
void UL1_GetCurrentTime() { puts("UL1_GetCurrentTime hit!");exit(1);}
void UL1_IS_3G_FDD_EXIST() { puts("UL1_IS_3G_FDD_EXIST hit!");exit(1);}
void UL1_PendingConfigTGPS_byTGPSI() { puts("UL1_PendingConfigTGPS_byTGPSI hit!");exit(1);}
*/

//###### Custom ASN #####
void kal_assert_fail() { puts("kal_assert_fail hit!");exit(1);}
int stack_timer_status(int in, int* out) { puts("stack_timer_status hit!");*out = 5000;return 2;}
int system_boot_mode =1; //normal boot
