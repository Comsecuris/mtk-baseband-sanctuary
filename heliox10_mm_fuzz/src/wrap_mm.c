#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "kal_public_defs.h"

int mm_main(ilm_struct*);
int mm_init(void);
void *alloc_canary(uint32_t size);
void free_canary(void* ptr);
// Sequence to split afl input into two parts, should be part of AFL dict
// AFL can figure out the rest
#define SPLITTER "!SPL1T*"
#define SPLIT_CMP "!SPL1T"

int readAll(int* length1, char** buf1, int* length2, char** buf2, char* ilm)
{
    int c;
    size_t p4kB = 4096, i = 0;
    void *newPtr = NULL;
    //char *ptrString = malloc(p4kB * sizeof (char));
    char* ptrString = ilm;
    int first = 1, header = 1;

    while (ptrString != NULL && (c = getchar()) != EOF)
    {
        if (i == p4kB * sizeof (char))
        {
            p4kB += 4096;
            if ((newPtr = realloc(ptrString, p4kB * sizeof (char))) != NULL)
                ptrString = (char*) newPtr;
            else
            {
                free(ptrString);
                return -1;
            }
        }
        ptrString[i++] = c;
        if (header && i < 8) continue;
        if (header && i == 8)
        {
            header = 0;
            i = 0;
            ptrString = malloc(p4kB * sizeof (char));
            continue;

        }
        if (first && c=='*' && i>=strlen(SPLIT_CMP))
        {
            ptrString[i-1] = '\0';
            if (!strcmp(ptrString + (i-1) - strlen(SPLIT_CMP), SPLIT_CMP))
            {
                *buf1 = ptrString;
                *length1 = (i-1) - strlen(SPLIT_CMP);
                i = 0;
                p4kB = 4096;
                ptrString = malloc(p4kB * sizeof (char));
                first = 0;
            }
        }
    }


    if (ptrString != NULL)
    {
        if (first || header)
        {
            return -1;
        }
        else
        {
            *buf2 = ptrString;
            *length2 = i;
        }
    } 
    else return -1;

    return 0;
}

int main(int argc, char** argv)
{
    printf("[INFO] program started\n");
    ilm_struct ilm;
    unsigned length1 = 0, length2=0;
    char *buf1 = NULL, *buf2 = NULL;
    int err = readAll(&length1, &buf1, &length2, &buf2, (char*)&ilm);
    if (err)
    {
        printf("Input invalid!\n");
        exit(1);
    }
    // setup ILM
    printf("[INFO] ilm: %hu, %hu, lp len: %u, pb len %u\n", ilm.msg_id, ilm.sap_id, length1, length2);
    // construct local para + peer buffer
    // ilm header + lpara header, lpara data + pb header+ pb head, data, tail
    ilm.local_para_ptr = alloc_canary(length1+4);
    int rsize = ((uint32_t*)ilm.local_para_ptr)[-2];
    int idx = ((rsize - 8)>>2) + 1;
    printf ("[DBG] %x local para high: %x, rsize: %d, idx: %d\n", ((uint32_t*)ilm.local_para_ptr)[-1], ((uint32_t*)ilm.local_para_ptr)[idx -2], rsize, idx);
    printf ("[DBG] %p local para high: %p, diff: %d, offed: %p\n", &((uint32_t*)ilm.local_para_ptr)[0], &((uint32_t*)ilm.local_para_ptr)[idx -2], (void*)&((uint32_t*)ilm.local_para_ptr)[idx-2]-(void*)&((uint32_t*)ilm.local_para_ptr)[0], (char*)ilm.local_para_ptr + 4);

    ilm.local_para_ptr->ref_count = 1;
    ilm.local_para_ptr->msg_len = length1;
    memcpy((char*)ilm.local_para_ptr + 4, buf1, length1);
    //printf ("[DBG] %x local para\n", ((uint32_t*)ilm.local_para_ptr)[-1]);
    // construct peer buffer s0 and s1 will be free header/tail space
    rsize = ((uint32_t*)ilm.local_para_ptr)[-2];
    idx = ((rsize - 8)>>2) + 1;
    printf ("[DBG] %x local para high: %x, rsize: %d, idx: %d\n", ((uint32_t*)ilm.local_para_ptr)[-1], ((uint32_t*)ilm.local_para_ptr)[idx -2], rsize, idx);

    unsigned short rlength = 0;
    unsigned short freehead = 0;
    unsigned short freetail = 0;

    if (length2 >=4)
    {
        rlength = length2 - 4;
        freehead = ((unsigned short*)buf2)[0];
        freetail = ((unsigned short*)buf2)[1];
    } 
    
    ilm.peer_buff_ptr = alloc_canary(freehead+freetail+rlength+8);
    if(!ilm.peer_buff_ptr)
    {
        printf("Failed to allocate memory!\n");
        exit(1);
    }
    //printf ("[DBG] %x peer buff1 loc: %p/%p\n", ((uint32_t*)ilm.peer_buff_ptr)[-1], ((uint32_t*)ilm.peer_buff_ptr)[-1], ilm.peer_buff_ptr);
    printf ("[INFO] peer buff rlength: %hx head: %hx tail: %hx\n", rlength, freehead, freetail);
    ilm.peer_buff_ptr->ref_count = 1;
    ilm.peer_buff_ptr->pdu_len = rlength;
    ilm.peer_buff_ptr->free_header_space = freehead;
    ilm.peer_buff_ptr->free_tail_space = freetail;
    memcpy((char*)ilm.peer_buff_ptr + 8 + freehead, buf2+4, rlength);
    //printf ("[DBG] %x peer buff2\n", ((uint32_t*)ilm.peer_buff_ptr)[-1]);
    free(buf1);
    free(buf2);

    mm_init();
    printf("Init done!\n");
    mm_main(&ilm);
    printf("Main done!\n");
    rsize = ((uint32_t*)ilm.local_para_ptr)[-2];
    idx = ((rsize - 8)>>2) + 1;
    printf ("[DBG] %x local para high: %x, rsize: %d, idx: %d\n", ((uint32_t*)ilm.local_para_ptr)[-1], ((uint32_t*)ilm.local_para_ptr)[idx -2], rsize, idx);
    printf ("[DBG] %x peer buff\n", ((uint32_t*)ilm.peer_buff_ptr)[-1]);
    //free_canary(ilm.local_para_ptr);

    printf ("[DBG] free local para done\n");
    //free_canary(ilm.peer_buff_ptr);
    return 0;
}
