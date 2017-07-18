#ifndef LIB_MISSING_H
#define LIB_MISSING_H
#include "kal_public_defs.h"
typedef void * * lcd_lqueue_bin;

typedef enum {
    NOT_SET,
    BY_FN_P,
    BY_USR_MEM
}mem_for_items;


typedef void * (*malloc_fp_t)(unsigned int size);
typedef void (*free_fp_t)(void *ptr);

typedef struct lcd_lqueue {
    unsigned int       bin_size;
         /* The first bin. */
    lcd_lqueue_bin     start;
         /* The position of the head within the bin. */
    unsigned int       head;
         /* The last bin. */
    lcd_lqueue_bin     end;
         /* The position of the tail within the bin. */
    unsigned int       tail;
         /* Number of bins allocated so far. */
    unsigned int       bin_count;
         /* Indicates the type of memory for items. */
    mem_for_items      item_mem;
    kal_bool           is_empty;
    malloc_fp_t        alloc_fn_p;
    free_fp_t          free_fn_p;
} lcd_lqueue;


void *get_ctrl_buffer_ext(uint32_t size, const char *file_name, uint32_t line);
void free_ctrl_buffer_ext(void *buff_ptr, const char *file_name, uint32_t line);


#endif
