#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdint.h>
//#define _POSIX_C_SOURCE 200112L
//#define _POSIX_C_SOURCE 199309L
#include <time.h>

#include "libdefined.h"
#include "kal_public_defs.h"

void dummy(void){
    printf("dummy\n");
}

#define CANARY 0x44332211
void *alloc_canary(uint32_t size)
{
    int rsize = size < 8 ? 20: size + 12;
    if (rsize%4)
    {
        rsize = ((rsize>>2) + 1)*4;
    }
    uint32_t *ptr = calloc(rsize, 1);
    if (!ptr)
    {
        printf("[LMERR] Failed to allocate %u bytes\n", rsize);
        raise(SIGSEGV);
        return NULL;
    }
    ptr[0] = rsize;
    ptr[1] = CANARY;
    ptr[((rsize-8)>>2) +1] = CANARY;
    printf("[LMDBG] lower canary: %p value: %x return %p index: %u rsize: %u\n", &ptr[1], ptr[1], &ptr[2], ((rsize-8)>>2) +1, rsize);
    return &ptr[2];
}

void free_canary(void* aptr)
{
    uint32_t *ptr = aptr - 8;
    if (ptr[1] != CANARY)
    {
        printf("[LMFAULT] Underflow detected %p %x\n", ptr, ptr[1]);
        raise(SIGSEGV);
    }
    uint32_t rsize = ptr[0];
    if (ptr[((rsize-8)>>2) +1] != CANARY)
    {
        printf("[LMFAULT] Overflow detected %p %x\n", ptr, ptr[((rsize-8)>>2) +1]);
        raise(SIGSEGV);
    }
    free(ptr);
}

void destroy_int_ilm(ilm_struct *ilm_ptr, const kal_char* file_name, kal_uint32 line)
{
    printf("[LMINFO] %s: ptr %p, %s:%u\n", __func__, ilm_ptr, file_name, line);
	if (ilm_ptr->local_para_ptr)
    {
        free_canary(ilm_ptr->local_para_ptr);
    }
    if (ilm_ptr->peer_buff_ptr)
    {
        free_canary(ilm_ptr->peer_buff_ptr);
    }
}

void *get_ctrl_buffer_ext(uint32_t size, const char *file_name, uint32_t line)
{
    printf("[LMINFO] %s: size %u, %s:%u\n", __func__, size, file_name, line);
    return alloc_canary(size);
}
void free_ctrl_buffer_ext(void *buff_ptr, const char *file_name, uint32_t line)
{
    printf("[LMINFO] %s: buffer %p, %s:%u\n", __func__, buff_ptr, file_name, line);
    return free_canary(buff_ptr);
}

void *construct_int_local_para(uint16_t size, uint32_t auto_reset, const char* file_name, uint32_t line)
{
    printf("[LMINFO] %s: size %u, %s:%u\n", __func__, size, file_name, line);
    local_para_struct* lp =alloc_canary(size);
    lp-> msg_len = size;
    lp->ref_count = 1;
    return lp;
}

void free_int_local_para(local_para_struct *local_para_ptr, const char* file, uint32_t line)
{
    printf("[LMINFO] %s: %s:%u\n", __func__, file, line);
    if (local_para_ptr)
    {
        free_canary(local_para_ptr);
    }
    else
    {
        printf("[LMINFO] %s: warning local para already NULL\n", __func__);
    }
}

int hold_local_para(local_para_struct *lp)
{
    printf("[LMINFO] %s:\n", __func__);
    if (!lp)
        return 0;
    lp->ref_count++;
    return 1;
}

void *construct_int_peer_buff(uint16_t pdu_len, uint16_t header_len, uint16_t tail_len, uint32_t auto_reset, const char* file_name, uint32_t line)
{
    // cant print file name because of clowniest bug ever
    printf("[LMINFO] %s: size %u\n", __func__, pdu_len);
    peer_buff_struct *pb =alloc_canary(pdu_len+header_len+tail_len+8);
    pb->free_header_space = header_len;
    pb->pdu_len = pdu_len;
    pb->free_tail_space = tail_len;
    pb->ref_count = 1;
    return pb;
}

void free_int_peer_buff(peer_buff_struct *pdu_ptr, const char* file, uint32_t line)
{
    printf("[LMINFO] %s: %s:%u\n", __func__, file, line);
    if (pdu_ptr)
    {
        free_canary(pdu_ptr);
    }
    else
    {
        printf("[LMINFO] %s: warning local para already NULL\n", __func__);
    }
}

void* get_peer_buff_pdu(peer_buff_struct *peer_buff_ptr, uint16_t *length_ptr)
{
    
    printf("[LMINFO] %s: %p\n", __func__, peer_buff_ptr);
    if (length_ptr)
    {
        *length_ptr = peer_buff_ptr->pdu_len;
    }
    return (char*)peer_buff_ptr + peer_buff_ptr->free_header_space + 8;
}

int hold_peer_buff(peer_buff_struct *lp)
{
    printf("[LMINFO] %s:\n", __func__);
    if (!lp)
        return 0;
    lp->ref_count++;
    return 1;
}

typedef struct _ev_node{
    struct _ev_node *next;
    uint32_t** eid;
} evnode;
evnode events = {0, 0};



/** EVENT SCHEDULE**/
void *evshed_create(char* name, uint16_t mod_type, uint32_t allowed_time_shift, uint16_t allowed_time_shift_sleep)
{
    printf("[LMINFO] %s: name %s\n", __func__, name);
    int32_t *es = alloc_canary(32);
    //struct timespec req;
    //clock_gettime(CLOCK_REALTIME, &req);
    es[3] = clock() & 0xffffffff;//systicks on original
    es[4] = 0x545645;
    es[5] = (unsigned)alloc_canary(12);
    es[6] = allowed_time_shift;
    printf("[LMINFO] %s: event create\n", __func__);
    
    return es;
}

uint32_t evshed_get_remaining_time(uint32_t* es, uint32_t eid)
{
    printf("[LMINFO] %s: \n", __func__);
    //struct timespec req;
    //clock_gettime(CLOCK_REALTIME, &req);
    return (clock() & 0xffffffff) - es[3];

}

void evshed_timer_handler(uint32_t *es)
{
    
    printf("[LMINFO] %s: \n", __func__);
    // This would do the actual event scheduling and timing
    // it is omitted on purpose

}

uint32_t evshed_cancel_event(uint32_t *es, uint32_t **eid)
{
    
    printf("[LMINFO] %s: \n", __func__);
    //struct timespec req;
    //clock_gettime(CLOCK_REALTIME, &req);
    if ( !(es && eid))
    {
        return -1;
    }
    // basically this is what it returns (next events elapsed time), it does a bunch of other things we dont care about
    uint32_t retval = 0;
    //if (*eid)
    //    retval = (*eid)[4] - ((req.tv_nsec & 0xffffffff) - es[3]);
    //unlink
    for (evnode *prev=&events, *ev=events.next; ev; prev=ev, ev=ev->next)
    {
        if (ev->eid == eid)
        {
            prev->next = ev->next;
            if (ev->next)
                retval = (uint32_t)((ev->next->eid)[4]) - ((clock() & 0xffffffff) - es[3]);

            free(ev);
            break;

        }
    }
    //free_canary(eid);
    return retval;
}

void* evshed_set_event(uint32_t **es, uint32_t event_hf_fptr, void *event_hf_param, uint32_t elapse_time)
{
    printf("[LMINFO] %s: func ptr: %p\n", __func__, event_hf_fptr);
    uint32_t* eid = alloc_canary(28);
    eid[6] = *(es[5]+8);
    eid[5] = (unsigned)es;
    eid[4] = elapse_time;
    eid[3] = (unsigned)event_hf_param;
    eid[2] = event_hf_fptr;
    // eid 0 and 1 are used for the linked list of events
    evnode* ev;
    if (events.next)
    {
        for (ev = events.next; ev->next; ev = ev->next)
        {}
        ev->next = calloc(sizeof(evnode), 1);
        ev->next->eid = (uint32_t**) eid;
    }
    else
    {
        events.next = calloc(sizeof(evnode), 1);
        events.next->eid =(uint32_t**) eid;
    }
    return eid;

}

// yeah this is stackoverflow's itoa
char* itoa(int val,char* str,  int base){
	
    char buf[32] = {0};	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
    strcpy(str, &buf[i+1]);
	
	return str;
	
}

char *kal_itoa(int value, char *str, int radix)
{
    return itoa(value, str, radix);
}


void dhl_brief_trace(int trc_class, uint32_t user_flag, uint32_t msg_index, const char *arg_type, ...)
{
    printf("[LMINFO] %s: class %d, idx: %u\n", __func__, trc_class, msg_index);
}

void dhl_trace(int trc_class, uint32_t user_flag, uint32_t msg_index, const char *arg_type, ...)
{
    printf("[LMINFO] %s: class %d, idx: %u\n", __func__, trc_class, msg_index);
}

// LTE Band mask
typedef enum
{
   LTE_BandNone = 0,
   LTE_Band1    = 1,
   LTE_Band2    = 2,
   LTE_Band3    = 3,
   LTE_Band4    = 4,
   LTE_Band5    = 5,
   LTE_Band6    = 6,
   LTE_Band7    = 7,
   LTE_Band8    = 8,
   LTE_Band9    = 9,
   LTE_Band10   = 10,
   LTE_Band11   = 11,
   LTE_Band12   = 12,
   LTE_Band13   = 13,
   LTE_Band14   = 14,
   LTE_Band15   = 15,
   LTE_Band16   = 16,
   LTE_Band17   = 17,
   LTE_Band18   = 18,
   LTE_Band19   = 19,
   LTE_Band20   = 20,
   LTE_Band21   = 21,
   LTE_Band22   = 22,
   LTE_Band23   = 23,
   LTE_Band24   = 24,
   LTE_Band25   = 25,
   LTE_Band26   = 26,
   LTE_Band27   = 27,
   LTE_Band28   = 28,
   LTE_Band29   = 29,
   LTE_Band30   = 30,
   LTE_Band31   = 31,
   LTE_Band32   = 32,
   LTE_Band33   = 33,
   LTE_Band34   = 34,
   LTE_Band35   = 35,
   LTE_Band36   = 36,
   LTE_Band37   = 37,
   LTE_Band38   = 38,
   LTE_Band39   = 39,
   LTE_Band40   = 40,
   LTE_Band41   = 41,
   LTE_Bandcount,
   LTE_BandMax  = 0xFFFE
}  LTE_Band;
#define    BAND_INDICATOR1  LTE_Band1
#define    BAND_INDICATOR2  LTE_Band3
#define    BAND_INDICATOR3  LTE_Band7
#define    BAND_INDICATOR4  LTE_Band17 
#define    BAND_INDICATOR5  LTE_Band38 
#define    BAND_INDICATOR6  LTE_Band39
#define    BAND_INDICATOR7  LTE_Band40
#define    BAND_INDICATOR8  LTE_Band41
#define    BAND_INDICATOR9  LTE_Band8
#define    BAND_INDICATOR10 LTE_Band5
#define    BAND_INDICATOR11 LTE_BandNone
#define    BAND_INDICATOR12 LTE_BandNone
#define    BAND_INDICATOR13 LTE_BandNone
#define    BAND_INDICATOR14 LTE_BandNone


#define LTE_AUGMENTED_BAND_ARRAY_NUM 15
LTE_Band lteBandIndArray[LTE_AUGMENTED_BAND_ARRAY_NUM] =
{
   LTE_BandNone,
   BAND_INDICATOR1,
   BAND_INDICATOR2,
   BAND_INDICATOR3,
   BAND_INDICATOR4,
   BAND_INDICATOR5,
   BAND_INDICATOR6,
   BAND_INDICATOR7,
   BAND_INDICATOR8,
   BAND_INDICATOR9,
   BAND_INDICATOR10,
   BAND_INDICATOR11,
   BAND_INDICATOR12,
   BAND_INDICATOR13,
   BAND_INDICATOR14,
};
int is_mask_calculated = 0;
uint32_t mask_buffer[4];

int EPHY_RF_GET_BAND_SUPPORT_MASK(uint32_t **out)
{
    printf("EPHY_RF_GET_BAND_SUPPORT_MASK hit!");
    if (is_mask_calculated)
    {
        int i = 0;
        do
        {
            if(lteBandIndArray[i])
            {
                mask_buffer[(lteBandIndArray[i]-1)>>5] |= 1 << ((lteBandIndArray[i]-1)&0x1F);
            }
            i += 2;
        }while (i != 30);
        is_mask_calculated = 1;
    }
    *out = mask_buffer;
    return 2;
}

uint32_t rr_arfcn_PCS_band_tag(uint32_t in)
{
    printf("rr_arfcn_PCS_band_tag hit!");
    if (in <= 0x32a)
    {
        return in | 0x400;
    }
    return in;
}
