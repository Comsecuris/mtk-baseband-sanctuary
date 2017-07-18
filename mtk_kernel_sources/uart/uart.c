/* mediatek/kernel/drivers/uart/uart.c
 *
 * (C) Copyright 2008 
 * MediaTek <www.mediatek.com>
 * MingHsien Hsieh <minghsien.hsieh@mediatek.com>
 *
 * MTK UART Driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#if defined(CONFIG_MTK_SERIAL_CONSOLE) && defined(CONFIG_MAGIC_SYSRQ)
#define SUPPORT_SYSRQ   
#endif
#include <generated/autoconf.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/ioport.h>
#include <linux/init.h>
#include <linux/console.h>
#include <linux/sysrq.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/tty_flip.h>
#include <linux/serial_core.h>
#include <linux/serial.h>
#include <linux/timer.h>
#include <linux/dma-mapping.h>
#include <linux/scatterlist.h>
#include <linux/platform_device.h>
#include <linux/hrtimer.h>
#include <linux/uaccess.h>
#include <asm/atomic.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <linux/irq.h>
#include <asm/scatterlist.h>
#include <mach/dma.h>
#include <mach/mt_typedefs.h>
#include <mach/irqs.h>
#include <linux/slab.h>
#include "linux/delay.h"
#include <linux/syscore_ops.h>
#include <linux/uart/mtk_uart.h>
#include <linux/uart/mtk_uart_intf.h>
#include <linux/version.h>
#include <linux/suspend.h>
#ifdef CONFIG_OF
#include <linux/of.h>
#endif

#if defined(CONFIG_MTK_HDMI_SUPPORT)
#include "hdmi_cust.h"
extern bool is_hdmi_active(void);
extern void hdmi_force_on(int from_uart_drv);
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
#define TTY_FLIP_ARG(a)  (a)
#else
#define TTY_FLIP_ARG(a)  ((a)->port)
#endif

spinlock_t		 mtk_console_lock;
spinlock_t		 mtk_uart_bt_lock;

#include <linux/htc_devices_dtb.h>

static int htc_console_enable =0;

struct mtk_uart *console_port;
struct mtk_uart *bt_port = NULL;
#define HW_FLOW_CTRL_PORT(uart) (uart->setting->hw_flow)
#if defined(ENABLE_VFIFO)
static DEFINE_SPINLOCK(mtk_uart_vfifo_port_lock);
#ifdef CONFIG_OF
#define VFIFO_INIT_RX(c, i, n) \
    {.ch = (c), .size = (n), .trig = VFF_RX_THRE(n), .type = UART_RX_VFIFO, \
     .port = NULL, .addr = NULL,             \
     .entry = ATOMIC_INIT(0), .reg_cb = ATOMIC_INIT(0), .iolock=__SPIN_LOCK_UNLOCKED(mtk_uart_vfifo_port[i].lock)} 
#define VFIFO_INIT_TX(c, i, n) \
    {.ch = (c), .size = (n), .trig = VFF_TX_THRE(n), .type = UART_TX_VFIFO, \
     .port = NULL,         \
     .addr = NULL, .entry = ATOMIC_INIT(0), .reg_cb = ATOMIC_INIT(0), .iolock=__SPIN_LOCK_UNLOCKED(mtk_uart_vfifo_port[i].lock)}
static struct mtk_uart_vfifo mtk_uart_vfifo_port[] = {
    VFIFO_INIT_TX(P_DMA_UART1_TX, 0, C_UART1_VFF_TX_SIZE),
    VFIFO_INIT_RX(P_DMA_UART1_RX, 1, C_UART1_VFF_RX_SIZE),
    VFIFO_INIT_TX(P_DMA_UART2_TX, 2, C_UART2_VFF_TX_SIZE),
    VFIFO_INIT_RX(P_DMA_UART2_RX, 3, C_UART2_VFF_RX_SIZE),
    VFIFO_INIT_TX(P_DMA_UART3_TX, 4, C_UART3_VFF_TX_SIZE),
    VFIFO_INIT_RX(P_DMA_UART3_RX, 5, C_UART3_VFF_RX_SIZE),
#if 0 
    VFIFO_INIT_TX(P_DMA_UART4_TX, 6, C_UART4_VFF_TX_SIZE),
    VFIFO_INIT_RX(P_DMA_UART4_RX, 7, C_UART4_VFF_RX_SIZE),
#endif
};
#else
#define VFIFO_INIT_RX(c, i, n, id) \
    {.ch = (c), .size = (n), .trig = VFF_RX_THRE(n), .type = UART_RX_VFIFO, \
     .base = (void*)VFF_BASE_CH(i), .port = NULL, .addr = NULL,             \
     .entry = ATOMIC_INIT(0), .reg_cb = ATOMIC_INIT(0), .iolock=__SPIN_LOCK_UNLOCKED(mtk_uart_vfifo_port[i].lock), \
     .irq_id = id} 
#define VFIFO_INIT_TX(c, i, n, id) \
    {.ch = (c), .size = (n), .trig = VFF_TX_THRE(n), .type = UART_TX_VFIFO, \
     .base = (void*)VFF_BASE_CH(i), .port = NULL,         \
     .addr = NULL, .entry = ATOMIC_INIT(0), .reg_cb = ATOMIC_INIT(0), .iolock=__SPIN_LOCK_UNLOCKED(mtk_uart_vfifo_port[i].lock), \
     .irq_id = id}
static struct mtk_uart_vfifo mtk_uart_vfifo_port[] = {
    VFIFO_INIT_TX(P_DMA_UART1_TX, 0, C_UART1_VFF_TX_SIZE, UART1_VFF_TX_IRQ_ID),
    VFIFO_INIT_RX(P_DMA_UART1_RX, 1, C_UART1_VFF_RX_SIZE, UART1_VFF_RX_IRQ_ID),
    VFIFO_INIT_TX(P_DMA_UART2_TX, 2, C_UART2_VFF_TX_SIZE, UART2_VFF_TX_IRQ_ID),
    VFIFO_INIT_RX(P_DMA_UART2_RX, 3, C_UART2_VFF_RX_SIZE, UART2_VFF_RX_IRQ_ID),
    VFIFO_INIT_TX(P_DMA_UART3_TX, 4, C_UART3_VFF_TX_SIZE, UART3_VFF_TX_IRQ_ID),
    VFIFO_INIT_RX(P_DMA_UART3_RX, 5, C_UART3_VFF_RX_SIZE, UART3_VFF_RX_IRQ_ID),
#if 0 
    VFIFO_INIT_TX(P_DMA_UART4_TX, 6, C_UART4_VFF_TX_SIZE),
    VFIFO_INIT_RX(P_DMA_UART4_RX, 7, C_UART4_VFF_RX_SIZE),
#endif
};
#endif 
#endif 
static struct mtk_uart mtk_uarts[UART_NR];
static unsigned int uart_freeze_enable[UART_NR] = {0};
static int  mtk_uart_init_ports(void);
static void mtk_uart_stop_tx(struct uart_port *port);
#if defined(ENABLE_SYSFS)
ssize_t mtk_uart_attr_show(struct kobject *kobj, struct attribute *attr, char *buffer);
ssize_t mtk_uart_attr_store(struct kobject *kobj, struct attribute *attr, const char *buffer, size_t size);
ssize_t mtk_uart_debug_show(struct kobject *kobj, char *page);
ssize_t mtk_uart_debug_store(struct kobject *kobj, const char *page, size_t size);
ssize_t mtk_uart_sysrq_show(struct kobject *kobj, char *page);
ssize_t mtk_uart_sysrq_store(struct kobject *kobj, const char *page, size_t size);
ssize_t mtk_uart_vffsz_show(struct kobject *kobj, char *page);
ssize_t mtk_uart_vffsz_store(struct kobject *kobj, const char *page, size_t size);
ssize_t mtk_uart_conse_show(struct kobject *kobj, char *page);
ssize_t mtk_uart_conse_store(struct kobject *kobj, const char *page, size_t size);
ssize_t mtk_uart_vff_en_show(struct kobject *kobj, char *page);
ssize_t mtk_uart_vff_en_store(struct kobject *kobj, const char *page, size_t size);
ssize_t mtk_uart_lsr_status_show(struct kobject *kobj, char *page);
ssize_t mtk_uart_lsr_status_store(struct kobject *kobj, const char *page, size_t size);
struct sysfs_ops mtk_uart_sysfs_ops = {
    .show   = mtk_uart_attr_show,
    .store  = mtk_uart_attr_store,
};
struct mtuart_entry {
    struct attribute attr;
    ssize_t (*show)(struct kobject *kobj, char *page);
    ssize_t (*store)(struct kobject *kobj, const char *page, size_t size);
};
struct mtuart_entry debug_entry = {
    { .name = "debug", .mode = S_IRUGO | S_IWUSR },
    mtk_uart_debug_show,
    mtk_uart_debug_store,
};
struct mtuart_entry sysrq_entry = {
    { .name = "sysrq", .mode = S_IRUGO | S_IWUSR },
    mtk_uart_sysrq_show,
    mtk_uart_sysrq_store,
};
struct mtuart_entry vffsz_entry = {
    { .name = "vffsz", .mode = S_IRUGO | S_IWUSR },
    mtk_uart_vffsz_show,
    mtk_uart_vffsz_store,
};
struct mtuart_entry conse_entry = {
    { .name = "conse", .mode = S_IRUGO | S_IWUSR },
    mtk_uart_conse_show,
    mtk_uart_conse_store,
};
struct mtuart_entry vff_en_entry = {
    { .name = "vff_en", .mode = S_IRUGO | S_IWUSR },
    mtk_uart_vff_en_show,
    mtk_uart_vff_en_store,
};
struct mtuart_entry lsr_status_entry = {
    { .name = "lsr_status", .mode = S_IRUGO | S_IWUSR },
    mtk_uart_lsr_status_show,
    mtk_uart_lsr_status_store,
};
struct attribute *mtk_uart_attributes[] = {
    &conse_entry.attr,  
#if defined(ENABLE_DEBUG)        
    &debug_entry.attr,
    &sysrq_entry.attr,
    &vffsz_entry.attr,
    &vff_en_entry.attr,
    &lsr_status_entry.attr,
#endif     
    NULL,
};
struct kobj_type mtk_uart_ktype = {
    .sysfs_ops = &mtk_uart_sysfs_ops,
    .default_attrs = mtk_uart_attributes,
};
struct mtuart_sysobj {
    struct kobject kobj;
    atomic_t sysrq;
    atomic_t vffLen[UART_NR*UART_VFIFO_NUM];
    atomic_t console_enable;
} mtk_uart_sysobj = {
    .console_enable = ATOMIC_INIT(1),
};
int mtk_uart_sysfs(void) 
{
    struct mtuart_sysobj *obj = &mtk_uart_sysobj;
    int idx;

    memset(&obj->kobj, 0x00, sizeof(obj->kobj));
#if defined(CONFIG_MAGIC_SYSRQ)
    atomic_set(&obj->sysrq, 1);
#else
    atomic_set(&obj->sysrq, 0);    
#endif
#if defined(ENABLE_VFIFO)
    for (idx = 0; idx < ARRAY_SIZE(obj->vffLen) && idx < ARRAY_SIZE(mtk_uart_vfifo_port); idx++)
        atomic_set(&obj->vffLen[idx], mtk_uart_vfifo_port[idx].size);
#endif
    atomic_set(&obj->console_enable, 1);
    
    obj->kobj.parent = kernel_kobj;
    if (kobject_init_and_add(&obj->kobj, &mtk_uart_ktype, NULL, "mtuart")) {
        kobject_put(&obj->kobj);
        return -ENOMEM;
    }
    kobject_uevent(&obj->kobj, KOBJ_ADD);
    return 0;
}
ssize_t mtk_uart_attr_show(struct kobject *kobj, struct attribute *attr, char *buffer) 
{
    struct mtuart_entry *entry = container_of(attr, struct mtuart_entry, attr);
    return entry->show(kobj, buffer);
}
ssize_t mtk_uart_attr_store(struct kobject *kobj, struct attribute *attr, const char *buffer, size_t size) 
{
    struct mtuart_entry *entry = container_of(attr, struct mtuart_entry, attr);
    return entry->store(kobj, buffer, size);
}
ssize_t mtk_uart_debug_show(struct kobject *kobj, char *buffer) 
{
    int remain = PAGE_SIZE;
    int len;
    char *ptr = buffer;
    int idx;
    unsigned int evt_mask;

    for (idx = 0; idx < UART_NR; idx++) {
	evt_mask = (unsigned int)get_uart_evt_mask(idx);
        len = scnprintf(ptr, remain, "0x%2x\n", evt_mask);
        ptr += len;
        remain -= len;
    }
    return (PAGE_SIZE-remain);
}
ssize_t mtk_uart_debug_store(struct kobject *kobj, const char *buffer, size_t size) 
{
    int a, b, c, d;
    int res = sscanf(buffer, "0x%x 0x%x 0x%x 0x%x", &a, &b, &c, &d);

    if (res != 4) {
        MSG_ERR("%s: expect 4 numbers\n", __FUNCTION__);
    } else {
	set_uart_evt_mask(0, a);
	set_uart_evt_mask(1, b);
	set_uart_evt_mask(2, c);
	set_uart_evt_mask(3, d);
    }
    return size;
}
ssize_t mtk_uart_sysrq_show(struct kobject *kobj, char *buffer) 
{
    struct mtuart_sysobj *obj = container_of(kobj, struct mtuart_sysobj, kobj);    
    return scnprintf(buffer, PAGE_SIZE, "%d\n", atomic_read(&obj->sysrq));
}
ssize_t mtk_uart_sysrq_store(struct kobject *kobj, const char *buffer, size_t size) 
{
    struct mtuart_sysobj *obj = container_of(kobj, struct mtuart_sysobj, kobj);    
    int a;
    int res = sscanf(buffer, "%d\n", &a);

    if (res != 1) {
        MSG_ERR("%s: expect 1 number\n", __FUNCTION__);
    } else {
        atomic_set(&obj->sysrq, a);    
    }
    return size;
}
ssize_t mtk_uart_vffsz_show(struct kobject *kobj, char *buffer) 
{
    ssize_t len = 0;
#if defined(ENABLE_VFIFO)
    struct mtuart_sysobj *obj = container_of(kobj, struct mtuart_sysobj, kobj);    
    int idx;

    for (idx = 0; idx < ARRAY_SIZE(obj->vffLen); idx++)
        len += scnprintf(buffer+len, PAGE_SIZE-len, "[%02d] %4d\n", idx, 
               atomic_read(&obj->vffLen[idx]));
#endif
    return len;
}
ssize_t mtk_uart_vffsz_store(struct kobject *kobj, const char *buffer, size_t size) 
{
#if defined(ENABLE_VFIFO)
    struct mtuart_sysobj *obj = container_of(kobj, struct mtuart_sysobj, kobj);    
    int idx, sz;

    if (2 != sscanf(buffer, "%d %d", &idx, &sz)) {
        MSG_ERR("%s: expect 2 variables\n", __FUNCTION__);    
    } else if (idx >= ARRAY_SIZE(obj->vffLen) || (sz%8 != 0)) {
        MSG_ERR("%s: invalid args %d, %d\n", __FUNCTION__, idx, sz);        
    } else {
        atomic_set(&obj->vffLen[idx], sz);    
    }
#endif
    return size;
}
ssize_t mtk_uart_conse_show(struct kobject *kobj, char *buffer) 
{
    struct mtuart_sysobj *obj = container_of(kobj, struct mtuart_sysobj, kobj);    
    return scnprintf(buffer, PAGE_SIZE, "%d\n", atomic_read(&obj->console_enable));
}
ssize_t mtk_uart_conse_store(struct kobject *kobj, const char *buffer, size_t size) 
{
    struct mtuart_sysobj *obj = container_of(kobj, struct mtuart_sysobj, kobj);    
    int enable;

    if (1 != sscanf(buffer, "%d", &enable)) {
        MSG_ERR("%s: expect 1 variables\n", __FUNCTION__);    
    } else {
        atomic_set(&obj->console_enable, enable);    
    }
    return size;
}
#endif 
ssize_t mtk_uart_vff_en_show(struct kobject *kobj, char *buffer) 
{
    int remain = PAGE_SIZE;
    int len;
    char *ptr = buffer;
    int idx;
    struct mtk_uart_setting *uart_setting;

    for (idx = 0; idx < UART_NR; idx++) {
	uart_setting = get_uart_default_settings(idx);
        len = scnprintf(ptr, 
        		remain, 
        		"tx%d_m:%2x rx%d_m:%2x\n",
			idx, 
        		(unsigned int)uart_setting->tx_mode,
			idx,
        		(unsigned int)uart_setting->rx_mode);
        ptr += len;
        remain -= len;
    }
    return (PAGE_SIZE-remain);
}
ssize_t mtk_uart_vff_en_store(struct kobject *kobj, const char *buffer, size_t size) 
{
    int u1_tx, u1_rx, u2_tx, u2_rx, u3_tx, u3_rx, u4_tx, u4_rx;
    struct mtk_uart_setting *uart_setting;
    int res = sscanf(buffer, "%x %x %x %x %x %x %x %x", 
    			&u1_tx, &u1_rx, &u2_tx, &u2_rx, &u3_tx, &u3_rx, &u4_tx, &u4_rx);

    if (res != 8) {
        MSG_ERR("%s: expect 8 numbers\n", __FUNCTION__);
    } else {
	uart_setting = get_uart_default_settings(0);
        uart_setting->tx_mode = u1_tx;
        uart_setting->rx_mode = u1_rx;
	uart_setting = get_uart_default_settings(1);
        uart_setting->tx_mode = u2_tx;
        uart_setting->rx_mode = u2_rx;
	uart_setting = get_uart_default_settings(2);
        uart_setting->tx_mode = u3_tx;
        uart_setting->rx_mode = u3_rx;
	uart_setting = get_uart_default_settings(3);
        uart_setting->tx_mode = u4_tx;
        uart_setting->rx_mode = u4_rx;
    }
    return size;
}
ssize_t mtk_uart_lsr_status_show(struct kobject *kobj, char *buffer) 
{
    int remain = PAGE_SIZE;
    int len;
    char *ptr = buffer;
    int idx;
    unsigned long lsr_status;

    for (idx = 0; idx < UART_NR; idx++) {
	lsr_status = get_uart_lsr_status(idx);
        len = scnprintf(ptr, 
        		remain, 
        		"%04x ",
        		(unsigned int)lsr_status);
        ptr += len;
        remain -= len;
	set_uart_lsr_status(idx, 0);
    }
    len = scnprintf(ptr, remain, "\n");
    ptr += len;
    remain -= len;
    return (PAGE_SIZE-remain);
}
ssize_t mtk_uart_lsr_status_store(struct kobject *kobj, const char *buffer, size_t size) 
{
    int u1_lsr, u2_lsr, u3_lsr, u4_lsr;
    int res = sscanf(buffer, "%x %x %x %x", 
    			&u1_lsr, &u2_lsr, &u3_lsr, &u4_lsr);

    if (res != 4) {
        MSG_ERR("%s: expect 4 numbers\n", __FUNCTION__);
    } else {
	set_uart_lsr_status(0, u1_lsr);
	set_uart_lsr_status(1, u2_lsr);
	set_uart_lsr_status(2, u3_lsr);
	set_uart_lsr_status(3, u4_lsr);
    }
    return size;
}
#if (defined(CONFIG_FIQ_DEBUGGER_CONSOLE) && defined(CONFIG_FIQ_DEBUGGER))
#define DEFAULT_FIQ_UART_PORT           (3)
int fiq_console_port = DEFAULT_FIQ_UART_PORT;
struct mtk_uart *mt_console_uart = &(mtk_uarts[DEFAULT_FIQ_UART_PORT]);
#endif
static int find_string(char str[], const char* fingerprint, int *offset)
{
        char *curr=str;
        int i = 0;
        int str_len;
        int fingerprint_len;
        if( (NULL == str)||(NULL == fingerprint) )
                return 0;
        str_len = strlen(str);
        fingerprint_len = strlen(fingerprint);
        if(str_len < fingerprint_len)
                return 0;
        for(i=0; i<=(str_len-fingerprint_len); i++){
                if( strncmp(curr, fingerprint, fingerprint_len) == 0 ){
                        if(NULL != offset)
                                *offset = i;
                        return 1;
                }
                curr++;
        }
        return 0;
}

static int find_fingerprint(char str[], int *offset)
{
        const char* fingerprint[] =
        {
                "console=/dev/null",
                "console=ttyMT0",
                "console=ttyMT1",
                "console=ttyMT2",
                "console=ttyMT3",
        };
        int i;
        for(i=0; i<sizeof(fingerprint)/sizeof(char*); i++){
                if(find_string(str, fingerprint[i], offset) != 0)
                        return i; 
        }
        return -1; 
}

static int modify_fingerprint(char str[], int offset, char new_val)
{
        if(NULL == str)
                return 0;
        str[offset+14-1] = new_val; 
        return 1;
}

void adjust_kernel_cmd_line_setting_for_console(char *u_boot_cmd_line, char *kernel_cmd_line)
{
        int offset = 0;
        int kernel_console_port_setting = -1;
        int u_boot_console_port_setting = -1;

        
        u_boot_console_port_setting = find_fingerprint(u_boot_cmd_line, 0);
        if(-1 == u_boot_console_port_setting){
                
                return;
        }

        
        kernel_console_port_setting = find_fingerprint(kernel_cmd_line, &offset);
        if(-1 == kernel_console_port_setting){
                
                goto _Exit;
        }

        if(u_boot_console_port_setting == kernel_console_port_setting){
                
                goto _Exit;
        }
        if(0 == kernel_console_port_setting){
                
                goto _Exit;
        }
        if(0 == u_boot_console_port_setting){
                
                goto _Exit;
        }
        
        switch(u_boot_console_port_setting){
        case 1: 
                modify_fingerprint(kernel_cmd_line, offset, '0');
                break;
        case 2: 
                modify_fingerprint(kernel_cmd_line, offset, '1');
                break;
        case 3: 
                modify_fingerprint(kernel_cmd_line, offset, '2');
                break;
        case 4: 
                modify_fingerprint(kernel_cmd_line, offset, '3');
                break;
        default:
                
                break;
        }

_Exit:
#if (defined(CONFIG_FIQ_DEBUGGER_CONSOLE) && defined(CONFIG_FIQ_DEBUGGER))
        kernel_console_port_setting = find_fingerprint(kernel_cmd_line, &offset);
        if(-1 == kernel_console_port_setting){
                
                return;
        }

        if(kernel_console_port_setting > 0) {
                fiq_console_port = (kernel_console_port_setting-1);
                mt_console_uart = &(mtk_uarts[fiq_console_port]);
        }
#endif
        return;
}
unsigned int mtk_uart_pdn_enable(char *port, int enable)
{
    int str_len;
    int port_num;
	
    if (port == NULL)
	return -1;
    
    str_len = strlen(port);
    if (str_len != 6) {
	MSG_ERR( "Length mismatch! len=%d\n", str_len);
	return -1;
    }

    if(find_string(port, "ttyMT", 0) == 0) {
	MSG_ERR( "Format mismatch! str=%s\n", port);
	return -1;
    }

    port_num = port[str_len-1]-'0';
    if (port_num >= UART_NR) {
        MSG_ERR( "wrong port:%d\n", port_num);
	return -1;
    }
    bt_port = &mtk_uarts[port_num];
    if (enable)
	mtk_uart_enable_dpidle(bt_port);
    else
	mtk_uart_disable_dpidle(bt_port);
    return 0;
}

unsigned int mtk_uart_freeze_enable(char *port, int enable)
{
    int str_len;
    int port_num;
	
    if (port == NULL)
	return -1;
    
    str_len = strlen(port);
    if (str_len != 6) {
	MSG_ERR( "Length mismatch! len=%d\n", str_len);
	return -1;
    }

    if(find_string(port, "ttyMT", 0) == 0) {
	MSG_ERR( "Format mismatch! str=%s\n", port);
	return -1;
    }

    port_num = port[str_len-1]-'0';
    if (port_num >= UART_NR) {
        MSG_ERR( "wrong port:%d\n", port_num);
	return -1;
    }

    if (enable)
		uart_freeze_enable[port_num] = 1;
    else
		uart_freeze_enable[port_num] = 0;
    return 0;
}
EXPORT_SYMBOL(mtk_uart_freeze_enable);

#ifdef CONFIG_MTK_SERIAL_CONSOLE
static void mtk_uart_console_write(struct console *co, const char *s,
    unsigned int count)
{
    #define CONSOLE_RETRY (5000)
    int i;
    struct mtk_uart *uart;
    u32 cnt = 0;
	unsigned long flags;


    if (co->index >= UART_NR || !(co->flags & CON_ENABLED) || !atomic_read(&mtk_uart_sysobj.console_enable) || !htc_console_enable)
        return;

    uart = &mtk_uarts[co->index];    
    for (i = 0; i < (int)count; i++) {
        cnt = 0;
        while (!mtk_uart_write_allow(uart)) {
            barrier();
            if (cnt++ >= CONSOLE_RETRY) {
                uart->timeout_count++;
                return;
            }
        }
	spin_lock_irqsave(&mtk_console_lock, flags);
        mtk_uart_write_byte(uart, s[i]);
	spin_unlock_irqrestore(&mtk_console_lock, flags);

        if (s[i] == '\n') {
            cnt = 0;
            while (!mtk_uart_write_allow(uart)) {
                barrier();
                if (cnt++ >= CONSOLE_RETRY) {
                    uart->timeout_count++;
                    return;
                }
            }
	    	spin_lock_irqsave(&mtk_console_lock, flags);
            mtk_uart_write_byte(uart, '\r');
	    	spin_unlock_irqrestore(&mtk_console_lock, flags);
        }
    }
}
static int __init mtk_uart_console_setup(struct console *co, char *options)
{
    struct mtk_uart *uart;
    struct uart_port *port;
    int baud    = 115200;
    int bits    = 8;
    int parity  = 'n';
    int flow    = 'n';
    int ret;

    printk(KERN_ALERT DBG_TAG "mtk console setup : co->index %d options:%s\n",
        co->index, options);

    if (co->index >= UART_NR)
        co->index = 0;

    uart = &mtk_uarts[co->index];
    port = (struct uart_port *)uart;

    console_port = uart;

    mtk_uart_console_setting_switch(uart);

    if (options)
        uart_parse_options(options, &baud, &parity, &bits, &flow);

    ret = uart_set_options(port, co, baud, parity, bits, flow);
    printk(KERN_ALERT DBG_TAG "mtk console setup : uart_set_option port(%d) "
          "baud(%d) parity(%c) bits(%d) flow(%c) - ret(%d)\n",
           co->index, baud, parity, bits, flow, ret);
    
    printk(KERN_ALERT DBG_TAG "mtk setting: (%d, %d, %d, %lu, %lu)\n", 
           uart->tx_mode, uart->rx_mode,
           uart->dma_mode,uart->tx_trig,
           uart->rx_trig);
    
    return ret;
}
static struct uart_driver mtk_uart_drv;
static struct console mtk_uart_console =
{
    .name       = "ttyMT",
#if !defined(CONFIG_MTK_SERIAL_MODEM_TEST)    
    
    .write      = mtk_uart_console_write,
    .setup      = mtk_uart_console_setup,
#endif     
    .device     = uart_console_device,
    .flags      = CON_PRINTBUFFER,
    .index      = -1,
    .data       = &mtk_uart_drv,
};
static int __init mtk_uart_console_init(void)
{
    int err = mtk_uart_init_ports();
   
    if(get_kernel_flag() & KERNEL_FLAG_SERIAL_HSL_ENABLE)
		htc_console_enable = 1;
    else
		htc_console_enable = 0;;

    if (!err)
        register_console(&mtk_uart_console);
    return err;
}
console_initcall(mtk_uart_console_init);
static int __init mtk_late_console_init(void)
{
    if (!(mtk_uart_console.flags & CON_ENABLED))
    {
        register_console(&mtk_uart_console);
    }
    return 0;
}
late_initcall(mtk_late_console_init);
#endif 
#if defined(ENABLE_VFIFO) 
static int mtk_uart_vfifo_del_dbgbuf(struct mtk_uart_vfifo *vfifo)
{
#if defined(ENABLE_VFIFO_DEBUG)    
    int idx;
    for (idx = 0; idx < ARRAY_SIZE(vfifo->dbg); idx++) {
        if (vfifo->dbg[idx].dat != 0)
            kfree(vfifo->dbg[idx].dat);
        vfifo->dbg[idx].dat = NULL;
        vfifo->dbg[idx].idx = 0;
        vfifo->dbg[idx].len = 0;
    }
#endif     
    return 0;
}
static int mtk_uart_vfifo_new_dbgbuf(struct mtk_uart_vfifo *vfifo)
{
#if defined(ENABLE_VFIFO_DEBUG)        
    int idx;
    for (idx = 0; idx < ARRAY_SIZE(vfifo->dbg); idx++) {
        if (vfifo->dbg[idx].dat != 0)
            kfree(vfifo->dbg[idx].dat);
        vfifo->dbg[idx].idx = 0;
        vfifo->dbg[idx].len = vfifo->size;
        vfifo->dbg[idx].dat = kzalloc(vfifo->dbg[idx].len, GFP_ATOMIC);
        if (!vfifo->dbg[idx].dat) {
            mtk_uart_vfifo_del_dbgbuf(vfifo);
            return -ENOMEM;
        }                   
    }
#endif
    return 0;
}
static int mtk_uart_vfifo_create(struct mtk_uart *uart)
{   
    struct mtk_uart_vfifo *vfifo;
    int idx, err = 0;

    MSG_FUNC_ENTRY();

    if(!uart->setting->vff){
        MSG_RAW("[UART%2d] not support VFF, Cancel alloc\n", uart->nport);
        return err;
    }

    MSG_RAW("[UART%2d] create\n", uart->nport);

    for (idx = uart->nport*2; idx < uart->nport*2 + 2; idx++) {
        vfifo = &mtk_uart_vfifo_port[idx];
        MSG_RAW("[UART%2d] idx=%2d\n", uart->nport, idx);
        if (vfifo->size){
            vfifo->addr = dma_alloc_coherent(uart->port.dev, vfifo->size, &vfifo->dmahd, GFP_DMA);
	    
	}
        else
            vfifo->addr = NULL;
        if (vfifo->size && !vfifo->addr) {
            err = -ENOMEM;
            break;
        } else if ((err = mtk_uart_vfifo_new_dbgbuf(vfifo))) {
            break;
        }
        MSG_RAW("[%2d] %p (%04d) ;\n", idx, vfifo->addr, vfifo->size);        
    }
    MSG_RAW("\n");
    return err;
}
static int mtk_uart_vfifo_delete(struct mtk_uart *uart)
{
    struct mtk_uart_vfifo *vfifo;
    int idx;

    MSG_FUNC_ENTRY();

    if(!uart->setting->vff){
        MSG_RAW("[UART%2d] not support VFF, Cancel free\n", uart->nport);
        return 0;
    }
    
    MSG_RAW("[UART%2d] delete", uart->nport);
    for (idx = uart->nport*2; idx < uart->nport*2 + 2; idx++) {
        vfifo = &mtk_uart_vfifo_port[idx];
        if (vfifo->addr)
            dma_free_coherent(NULL, vfifo->size, vfifo->addr, vfifo->dmahd);
        mtk_uart_vfifo_del_dbgbuf(vfifo);
        MSG_RAW("[%2d] %p (%04d) ;", idx, vfifo->addr, vfifo->size);        
        vfifo->addr = NULL;
    }
    MSG_RAW("\n");
    return 0;
}
int mtk_uart_vfifo_prepare(struct mtk_uart *uart)
{
    struct mtuart_sysobj *obj = &mtk_uart_sysobj;
    struct mtk_uart_vfifo *tport, *rport;
    int tx = uart->nport << 1;
    int rx = tx + 1;
    
    MSG_FUNC_ENTRY();

    if (uart->nport >= UART_NR) {
        MSG_ERR( "wrong port:%d\n", uart->nport);
        return -EINVAL;
    } else if(FALSE ==uart->setting->vff){
        MSG_ERR( "Port :%d not support vfifo\n", uart->nport);
        return -EINVAL;
    }else {
        tport = &mtk_uart_vfifo_port[tx];
        rport = &mtk_uart_vfifo_port[rx];
    }
    if ((atomic_read(&obj->vffLen[tx]) == tport->size) &&
        (atomic_read(&obj->vffLen[rx]) == rport->size))
        return 0;
    MSG_RAW("re-alloc +\n");
    mtk_uart_vfifo_delete(uart);
    tport->size = atomic_read(&obj->vffLen[tx]);
    tport->trig = VFF_TX_THRE(tport->size);
    rport->size = atomic_read(&obj->vffLen[rx]);
    rport->trig = VFF_RX_THRE(rport->size);
    mtk_uart_vfifo_create(uart);
    MSG_RAW("re-alloc -\n");
    return 0;
}
static struct mtk_uart_vfifo *mtk_uart_vfifo_alloc(struct mtk_uart *uart, UART_VFF_TYPE type)
{
    struct mtk_uart_vfifo *vfifo = NULL;
    unsigned long flags;
    spin_lock_irqsave(&mtk_uart_vfifo_port_lock, flags);
    
    MSG(INFO, "(%d, %d)", uart->nport, type);        

    if ((uart->nport >= UART_NR) || (type >= UART_VFIFO_NUM))
        vfifo = NULL;
    else {
        vfifo = &mtk_uart_vfifo_port[2*uart->nport+type];
    }

    if (vfifo && vfifo->addr == NULL)
        vfifo = NULL;
    MSG(INFO, "alloc vfifo-%d[%d](%p)\n", uart->nport, vfifo->size, vfifo->addr);        

    spin_unlock_irqrestore(&mtk_uart_vfifo_port_lock, flags);
    return vfifo;

}
static void mtk_uart_vfifo_free(struct mtk_uart *uart,
                                   struct mtk_uart_vfifo *vfifo)
{
    unsigned long flags;
    if (vfifo) {
        spin_lock_irqsave(&mtk_uart_vfifo_port_lock, flags);
        vfifo->dma = NULL;
        vfifo->cur = NULL;
        vfifo->dbgidx = 0;
        spin_unlock_irqrestore(&mtk_uart_vfifo_port_lock, flags);
    }
}
static unsigned int mtk_uart_vfifo_write_allow(struct mtk_uart *uart)
{
    return !mtk_uart_vfifo_is_full(uart->tx_vfifo);
}
static unsigned int mtk_uart_vfifo_read_allow(struct mtk_uart *uart)
{
    return !mtk_uart_vfifo_is_empty(uart->rx_vfifo);
}
inline static unsigned short mtk_uart_vfifo_get_trig(
                                        struct mtk_uart *uart, 
                                        struct mtk_uart_vfifo *vfifo)
{
    return vfifo->trig;
}
#define get_mtk_uart(ptr, type, member) (type *)( (char *)ptr - offsetof(type,member))
static enum hrtimer_restart mtk_uart_tx_vfifo_timeout(struct hrtimer *hrt)
{
    struct mtk_uart_vfifo *vfifo = container_of(hrt, struct mtk_uart_vfifo, flush);
    struct mtk_uart_dma *dma = (struct mtk_uart_dma*)vfifo->dma;
    struct mtk_uart *uart = dma->uart;
#if defined(ENABLE_VFIFO_DEBUG)    
    ktime_t cur = ktime_get();
    struct timespec a = ktime_to_timespec(cur);

    MSG(MSC, "flush timeout [%ld %ld]\n", a.tv_sec, a.tv_nsec);
#endif    
    mtk_uart_tx_vfifo_flush(uart, 1);
    return HRTIMER_NORESTART;
}
static void mtk_uart_dma_vfifo_callback(void *data)
{
    struct mtk_uart_dma *dma = (struct mtk_uart_dma*)data;
    struct mtk_uart *uart = dma->uart;
        
    MSG(DMA, "%s VFIFO CB: %4d/%4d\n", dma->dir == DMA_TO_DEVICE ? "TX" : "RX",
        mtk_uart_vfifo_get_counts(dma->vfifo), dma->vfifo->size);

    if (dma->dir == DMA_FROM_DEVICE) {
        mtk_uart_dma_vfifo_rx_tasklet((unsigned long)uart);
        
    } else if (dma->dir == DMA_TO_DEVICE) {
    }
    tasklet_schedule(&dma->tasklet);
}
static irqreturn_t mtk_vfifo_irq_handler(int irq, void *dev_id)
{
    struct mtk_uart_vfifo *vfifo;
    vfifo = (struct mtk_uart_vfifo *)dev_id;

    if (!vfifo){
	printk(KERN_ERR "mtk_vfifo_irq_handler: vfifo is NULL\n");
	return IRQ_NONE;
    }
    if (!vfifo->dma){
	printk(KERN_ERR "mtk_vfifo_irq_handler: dma is NULL\n");
	return IRQ_NONE;
    }

    
    mtk_uart_dma_vfifo_callback(vfifo->dma);

    
    if(vfifo->type == UART_RX_VFIFO)
		mtk_uart_vfifo_clear_rx_intr(vfifo);
	else
		mtk_uart_vfifo_clear_tx_intr(vfifo);

    return IRQ_HANDLED;
}
static int mtk_uart_dma_alloc(struct mtk_uart *uart, 
                                 struct mtk_uart_dma *dma, int mode,
                                 struct mtk_uart_vfifo *vfifo)
{
    int ret = 0;

    MSG_FUNC_ENTRY();

    if (mode == UART_NON_DMA)
        return -1;
    
    switch (mode) {
    case UART_TX_VFIFO_DMA:
        if (!vfifo) {
            MSG(ERR, "fail due to NULL tx_vfifo\n");
            ret = -1;
            break;
        }

        vfifo->dma = dma;
        dma->dir   = DMA_TO_DEVICE;   
        dma->mode  = mode;
        dma->vfifo = vfifo;
        dma->uart  = uart;

        init_completion(&dma->done);        
        tasklet_init(&dma->tasklet, mtk_uart_dma_vfifo_tx_tasklet, (unsigned long)uart);

        if (!atomic_read(&vfifo->reg_cb)) {
            
            
            mtk_uart_vfifo_disable_tx_intr(uart);

            ret = request_irq(vfifo->irq_id, (irq_handler_t)mtk_vfifo_irq_handler, IRQF_LEVEL_TRIGGER_POLARITY, DRV_NAME, vfifo); 
            if (ret)
                return ret;
            atomic_set(&vfifo->reg_cb, 1);
        } 

        atomic_set(&dma->free, 1);

        break;
        
    case UART_RX_VFIFO_DMA:
        if (!vfifo) {
            MSG(ERR, "fail due to NULL rx_vfifo\n");
            ret = -1;
            break;
        }

        vfifo->dma = dma;
        dma->dir   = DMA_FROM_DEVICE;
        dma->mode  = mode;
        dma->vfifo = vfifo;
        dma->uart  = uart;

        init_completion(&dma->done);        
        tasklet_init(&dma->tasklet, mtk_uart_dma_vfifo_rx_tasklet, (unsigned long)uart);

        if (!atomic_read(&vfifo->reg_cb)) {
            
            mtk_uart_vfifo_disable_rx_intr(uart);

            ret = request_irq(vfifo->irq_id, (irq_handler_t)mtk_vfifo_irq_handler, IRQF_LEVEL_TRIGGER_POLARITY, DRV_NAME, vfifo); 
            if (ret)
                return ret;
            atomic_set(&vfifo->reg_cb, 1);
        }
            
        atomic_set(&dma->free, 1);
      
        break;
    }
    return ret;
}
void mtk_uart_dma_stop(struct mtk_uart *uart, 
                                 struct mtk_uart_dma *dma)
{
    MSG_FUNC_ENTRY();
    if (!dma)
        return;

    mtk_uart_stop_dma(dma);
    atomic_set(&dma->free, 1);
    complete(&dma->done);
}
static void mtk_uart_dma_free(struct mtk_uart *uart, 
                                 struct mtk_uart_dma *dma)
{
    unsigned long flags;
    
    MSG_FUNC_ENTRY();

    if (!dma)
        return;

    if (dma->mode == UART_NON_DMA)
        return; 
    
    if ((dma->mode == UART_RX_VFIFO_DMA || dma->mode == UART_TX_VFIFO_DMA) && (!dma->vfifo))
        return;

    if (dma->vfifo && !mtk_uart_vfifo_is_empty(dma->vfifo)) {
        tasklet_schedule(&dma->tasklet);
        MSG(DMA, "wait for %s vfifo dma completed!!!\n", 
            dma->dir == DMA_TO_DEVICE ? "TX" : "RX");    
        wait_for_completion(&dma->done);          
    }
    spin_lock_irqsave(&uart->port.lock, flags);
    mtk_uart_stop_dma(dma);
    if (dma->vfifo && timer_pending(&dma->vfifo->timer))
        del_timer_sync(&dma->vfifo->timer);
    if (dma->vfifo && hrtimer_active(&dma->vfifo->flush))
        hrtimer_cancel(&dma->vfifo->flush);
    spin_unlock_irqrestore(&uart->port.lock, flags); 
    tasklet_kill(&dma->tasklet);
    spin_lock_irqsave(&uart->port.lock, flags); 
    mtk_uart_reset_dma(dma);
    mtk_uart_vfifo_disable(uart, dma->vfifo);    
    mtk_uart_vfifo_free(uart, dma->vfifo);      
    MSG(INFO, "free %s dma completed!!!\n", 
        dma->dir == DMA_TO_DEVICE ? "TX" : "RX");  
    memset(dma, 0, sizeof(struct mtk_uart_dma));
    spin_unlock_irqrestore(&uart->port.lock, flags);   

}
#endif 
static void mtk_uart_set_baud(struct mtk_uart *uart , int baudrate)
{ 
    if (uart->port.flags & ASYNC_SPD_CUST) {
    	if(uart->port.custom_divisor & (1<<31) ){
    	    baudrate = uart->port.custom_divisor&(~(1<<31));
    	    if( baudrate > (uart->sysclk>>2) ) 
    	    	baudrate = 9600;
    	}else{
            if (!uart->custom_baud) {
                baudrate = uart->sysclk/16; 
                baudrate = baudrate/uart->port.custom_divisor;
            } else {
                baudrate = uart->custom_baud;
            }
    	 
        }
        MSG(CFG, "CUSTOM, baudrate = %d, divisor = %d\n", baudrate, uart->port.custom_divisor);
    }

    if (uart->auto_baud)
        mtk_uart_set_auto_baud(uart); 
        
    mtk_uart_baud_setting(uart, baudrate);

    uart->baudrate = baudrate;
}
static inline bool mtk_uart_enable_sysrq(struct mtk_uart *uart) 
{
    return uart->setting->sysrq;
}
static void mtk_uart_rx_chars(struct mtk_uart *uart)
{
    struct uart_port *port = &uart->port;
    struct tty_struct *tty = uart->port.state->port.tty;
    int max_count = UART_FIFO_SIZE;
    unsigned int data_byte, status;
    unsigned int flag;
    unsigned long flags;

    spin_lock_irqsave(&port->lock, flags);  
    
    while (max_count-- > 0) {

        
        if (!mtk_uart_data_ready(uart))
            break;
#if 0
        if (tty->flip.count >= TTY_FLIPBUF_SIZE) {
            if (tty->low_latency) {
                tty_flip_buffer_push(tty);
            }
        }
#endif
        
        data_byte = uart->read_byte(uart);
        port->icount.rx++;
        flag = TTY_NORMAL;

        status = mtk_uart_filter_line_status(uart);
        
        
        if (status & UART_LSR_BI) {
            MSG(INFO, "Break interrupt!!\n");
            port->icount.brk++;
            if (uart_handle_break(port))
                continue;
            flag = TTY_BREAK;
        } else if (status & UART_LSR_PE) {
            MSG(INFO, "Parity Error!!\n");
            port->icount.parity++;
            flag = TTY_PARITY;
        } else if (status & UART_LSR_FE) {
            MSG(INFO, "Frame Error!!\n");
            port->icount.frame++;
            flag = TTY_FRAME;
        } else if (status & UART_LSR_OE) {
            MSG(INFO, "Overrun!!\n");
            port->icount.overrun++;
            flag = TTY_OVERRUN;
        }

#ifdef CONFIG_MAGIC_SYSRQ        
        if (mtk_uart_enable_sysrq(uart))
        {
            if (uart_handle_sysrq_char(port, data_byte))
                continue;

            
        #if defined(CONFIG_MAGIC_SYSRQ) && defined(CONFIG_SERIAL_CORE_CONSLE)
            if (data_byte == 0)
                uart->port.sysrq = 1;
        #endif
            
        }
#endif         

        if (!tty_insert_flip_char(TTY_FLIP_ARG(tty), data_byte, flag))
            MSG(ERR, "tty_insert_flip_char: no space");
    }
    tty_flip_buffer_push(TTY_FLIP_ARG(tty));
    spin_unlock_irqrestore(&port->lock, flags);  
    MSG(FUC, "%s (%2d)\n", __FUNCTION__, UART_FIFO_SIZE - max_count - 1);
#if defined(CONFIG_MTK_HDMI_SUPPORT)
#ifdef MHL_UART_SHARE_PIN
    if((UART_FIFO_SIZE - max_count - 1) > 0)
    {
	    hdmi_force_on(UART_FIFO_SIZE - max_count - 1);
    }
#endif
#endif
}
static void mtk_uart_tx_chars(struct mtk_uart *uart)
{
    
    struct uart_port *port = &uart->port;
    struct circ_buf *xmit = &port->state->xmit;
    int count;

    
    if (unlikely(port->x_char)) {
        MSG(INFO, "detect x_char!!\n");
        uart->write_byte(uart, port->x_char);
        port->icount.tx++;
        port->x_char = 0;
        return;
    }

    
    if (uart_circ_empty(xmit) || uart_tx_stopped(port)) 
    {
        struct tty_struct *tty = port->state->port.tty;
        if (!uart_circ_empty(xmit))
            MSG(ERR, "\t\tstopped: empty: %d %d %d\n", uart_circ_empty(xmit), tty->stopped, tty->hw_stopped);
        mtk_uart_stop_tx(port);
        return;
    }

    count = port->fifosize - 1;

    do {
        if (uart_circ_empty(xmit))
            break;
         if ((count == 1) || (!uart->write_allow(uart))) {
            
            mtk_uart_enable_intrs(uart, UART_IER_ETBEI);
            break;
        }
        uart->write_byte(uart, xmit->buf[xmit->tail]);
        xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
        port->icount.tx++;

    } while (--count > 0);

    MSG(INFO, "TX %d chars\n", port->fifosize - 1 - count);

    if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
        uart_write_wakeup(port);

    if (uart_circ_empty(xmit))
        mtk_uart_stop_tx(port);
}
static void mtk_uart_rx_handler(struct mtk_uart *uart, int intrs)
{
    if (uart->rx_mode == UART_NON_DMA) {
        mtk_uart_rx_chars(uart);
    } else if (uart->rx_mode == UART_RX_VFIFO_DMA) {
#if defined(ENABLE_VFIFO)
	mtk_uart_rx_pre_handler(uart, intrs);
        mtk_uart_dma_vfifo_rx_tasklet((unsigned long)uart);        
#endif
    }
}
void mtk_uart_tx_handler(struct mtk_uart *uart)
{
    struct uart_port *port = &uart->port;
    unsigned long flags;
    if (uart->tx_mode == UART_NON_DMA) {
	spin_lock_irqsave(&port->lock, flags);
        mtk_uart_tx_chars(uart);
        spin_unlock_irqrestore(&port->lock, flags);
    } else if (uart->tx_mode == UART_TX_VFIFO_DMA) {
        tasklet_schedule(&uart->dma_tx.tasklet);
    }
}
#ifdef ENABLE_DEBUG
static const char *fifo[] = {"No FIFO", "Unstable FIFO", 
                             "Unknown", "FIFO Enabled"};
static const char *intrrupt[] = {"Modem Status Chg", "Tx Buffer Empty",
                                 "Rx Data Received", "BI, FE, PE, or OE",
                                 "0x04", "0x05", "Rx Data Timeout", "0x07",
                                 "SW Flow Control", "0x09", "0x10", "0x11", "0x12",
                                 "0x13", "0x14", "0x15", "HW Flow Control"};
#endif

#ifndef CONFIG_FIQ_DEBUGGER
#ifdef CONFIG_MT_PRINTK_UART_CONSOLE
extern bool printk_disable_uart;
extern int mt_need_uart_console;
#endif
#endif

static irqreturn_t mtk_uart_irq(int irq, void *dev_id)
{
    unsigned int intrs, timeout = 0;
    struct mtk_uart *uart = (struct mtk_uart *)dev_id; 

#ifndef CONFIG_FIQ_DEBUGGER
#ifdef CONFIG_MT_PRINTK_UART_CONSOLE
	unsigned long base;
	base = uart->base;
	if ((uart == console_port) && (UART_READ32(UART_LSR) & 0x01))
   		printk_disable_uart = 0;
#endif
#endif

    intrs = mtk_uart_get_interrupt(uart);

#ifdef ENABLE_DEBUG
    {
        UART_IIR_REG *iir = (UART_IIR_REG *)&intrs;
        if (iir->NINT)
            MSG(INT, "No interrupt (%s)\n", fifo[iir->FIFOE]);        
        else if (iir->ID < ARRAY_SIZE(intrrupt))
            MSG(INT, "%02x %s (%s)\n", iir->ID, intrrupt[iir->ID], fifo[iir->FIFOE]);
        else
            MSG(INT, "%2x\n", iir->ID);
    }
#endif
    intrs &= UART_IIR_INT_MASK;
    
    if (intrs == UART_IIR_NO_INT_PENDING)
        return IRQ_HANDLED;

    if (intrs == UART_IIR_RLS) {
        
    } else if (intrs == UART_IIR_RDA) {
    } else if (intrs == UART_IIR_CTI) {
        timeout = 1;
    } else if (intrs == UART_IIR_THRE) {
        mtk_uart_tx_handler(uart);
    } else if (intrs == UART_IIR_MS) {
        mtk_uart_get_modem_status(uart);
    } else if (intrs == UART_IIR_SW_FLOW_CTRL) {
        
    } else if (intrs == UART_IIR_HW_FLOW_CTRL) {
        
    }
    mtk_uart_intr_last_check(uart, intrs);
    mtk_uart_rx_handler(uart, intrs);        
    return IRQ_HANDLED;
}
static unsigned int mtk_uart_tx_empty(struct uart_port *port)
{
    struct mtk_uart *uart = (struct mtk_uart *)port;

    MSG_FUNC_ENTRY();

#if defined(ENABLE_VFIFO)
    if (uart->tx_mode == UART_TX_VFIFO_DMA)
        return mtk_uart_vfifo_is_empty(uart->dma_tx.vfifo) ? TIOCSER_TEMT : 0;
    else
#endif
        return uart->write_allow(uart) ? TIOCSER_TEMT : 0;
}
static void mtk_uart_stop_tx(struct uart_port *port)
{
    struct mtk_uart *uart = (struct mtk_uart *)port;

    MSG_FUNC_ENTRY();
#if defined(ENABLE_VFIFO)
    if (uart->tx_mode == UART_TX_VFIFO_DMA){
        
        
    } else
#endif
        
        mtk_uart_disable_intrs(uart, UART_IER_ETBEI);
    uart->tx_stop = 1;
}
static void mtk_uart_start_tx(struct uart_port *port)
{
    struct mtk_uart *uart = (struct mtk_uart *)port;
    struct circ_buf    *xmit = &port->state->xmit;    
    unsigned long size;
    
    size = CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);

    if (!size)
        return;

    uart->tx_stop = 0;
    reset_tx_raw_data(uart);

#if defined(ENABLE_VFIFO)
    if (uart->tx_mode == UART_TX_VFIFO_DMA) {
	if (UART_DEBUG_EVT(DBG_EVT_BUF))
    	    printk("[UART%d] mtk_uart_start_tx\n", uart->nport);
        if (!uart->write_allow(uart))
            mtk_uart_vfifo_enable_tx_intr(uart);
        else 
            mtk_uart_dma_vfifo_tx_tasklet((unsigned long)uart);
    }
    else {
#else
    {
#endif
        if (uart->write_allow(uart))
            mtk_uart_tx_chars(uart);
    }
}
static void mtk_uart_send_xchar(struct uart_port *port, char ch)
{
    struct mtk_uart *uart = (struct mtk_uart *)port;
    unsigned long flags;

    MSG_FUNC_ENTRY();
    
    if (uart->tx_stop)
        return;

    spin_lock_irqsave(&port->lock, flags);
    while (!mtk_uart_write_allow(uart)); 
    mtk_uart_write_byte(uart, (unsigned char)ch);
    port->icount.tx++; 
    spin_unlock_irqrestore(&port->lock, flags);   
    return;
}
static void mtk_uart_enable_ms(struct uart_port *port)
{
    struct mtk_uart *uart = (struct mtk_uart *)port;

    MSG_FUNC_ENTRY();
    uart->ms_enable = 1;
}
static int mtk_uart_startup(struct uart_port *port)
{
    struct mtk_uart *uart = (struct mtk_uart *)port;
    int ret;
    long mask = UART_IER_HW_NORMALINTS;
    
    MSG_FUNC_ENTRY();

    
    
    
    

    
    #ifdef ATE_FACTORY_ENABLE
    mtk_uart_is_ate_factory_mode(uart);
    #endif 

    uart->fctl_mode     = UART_FC_NONE;
    
    
    mtk_uart_disable_intrs(uart, UART_IER_ALL_INTS);

    
    
#ifdef CONFIG_OF
    ret = request_irq(port->irq, (irq_handler_t)mtk_uart_irq, uart->setting->irq_flags, DRV_NAME, uart); 
#else
    ret = request_irq(port->irq, (irq_handler_t)mtk_uart_irq, IRQF_LEVEL_TRIGGER_POLARITY, DRV_NAME, uart); 
#endif
    if (ret)
        return ret;

#if defined(ENABLE_VFIFO)
#if defined(ENABLE_VFIFO_DEBUG)
    mtk_uart_vfifo_prepare(uart);
    uart->dma_mode      = uart->setting->dma_mode;
    uart->tx_mode       = uart->setting->tx_mode;
    uart->rx_mode       = uart->setting->rx_mode;
    uart->tx_trig       = uart->setting->tx_trig;
    uart->rx_trig       = uart->setting->rx_trig;
#endif
    
    if (uart->rx_mode == UART_RX_VFIFO_DMA) {
        uart->rx_vfifo = mtk_uart_vfifo_alloc(uart, UART_RX_VFIFO);  
        ret = mtk_uart_dma_alloc(uart, &uart->dma_rx, uart->rx_mode, uart->rx_vfifo);
        if (!uart->rx_vfifo || ret) {
            uart->rx_mode = UART_NON_DMA;
            MSG(ERR, "RX DMA alloc fail [%d]\n", ret);
        }
    }
    if (uart->tx_mode == UART_TX_VFIFO_DMA) {
        uart->tx_vfifo = mtk_uart_vfifo_alloc(uart, UART_TX_VFIFO);
        ret = mtk_uart_dma_alloc(uart, &uart->dma_tx, uart->tx_mode, uart->tx_vfifo);
        if (!uart->tx_vfifo || ret) {
            uart->tx_mode = UART_NON_DMA;
            MSG(ERR, "TX DMA alloc fail [%d]\n", ret);        
        }    
    }
    
    
    if (uart->tx_mode == UART_TX_VFIFO_DMA) {
        uart->write_allow = mtk_uart_vfifo_write_allow;
        uart->write_byte  = mtk_uart_vfifo_write_byte;
        mtk_uart_vfifo_enable(uart, uart->tx_vfifo);
        mtk_uart_dma_setup(uart, &uart->dma_tx);
        if (mtk_uart_dma_start(uart, &uart->dma_tx))
            MSG(ERR,"mtk_uart_dma_start fails\n");

        hrtimer_init(&uart->tx_vfifo->flush, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
        uart->tx_vfifo->flush.function   = mtk_uart_tx_vfifo_timeout;
    } else if (uart->tx_mode == UART_NON_DMA) {
        uart->write_allow = mtk_uart_write_allow;
        uart->write_byte  = mtk_uart_write_byte;
    }
    if (uart->rx_mode == UART_RX_VFIFO_DMA) {
        uart->read_allow = mtk_uart_vfifo_read_allow;
        uart->read_byte  = mtk_uart_vfifo_read_byte;  
        mtk_uart_vfifo_enable(uart, uart->rx_vfifo);
        mtk_uart_dma_setup(uart, &uart->dma_rx);
        if (mtk_uart_dma_start(uart, &uart->dma_rx))
            MSG(ERR,"mtk_uart_dma_start fails\n");        
    } else if (uart->rx_mode == UART_NON_DMA) {
        uart->read_allow = mtk_uart_read_allow;
        uart->read_byte  = mtk_uart_read_byte;  
    }
#endif
    if (uart->tx_mode == UART_TX_VFIFO_DMA || uart->rx_mode == UART_RX_VFIFO_DMA){
		if (!bt_port || (bt_port && (uart != bt_port)))
			mtk_uart_disable_dpidle(uart);
    } else if (uart->tx_mode == UART_NON_DMA && uart->rx_mode == UART_NON_DMA){
	mtk_uart_enable_dpidle(uart);
    }

    uart->tx_stop = 0;
    uart->rx_stop = 0;

    mtk_uart_fifo_set_trig(uart, uart->tx_trig, uart->rx_trig);
    mtk_uart_enable_sleep(uart);

    
    mtk_uart_enable_intrs(uart, mask);
    return 0;
}
static void mtk_uart_shutdown(struct uart_port *port)
{
    struct mtk_uart *uart = (struct mtk_uart *)port;

    MSG_FUNC_ENTRY();

    
    mtk_uart_disable_intrs(uart, UART_IER_ALL_INTS);

#if defined(ENABLE_VFIFO)
    
    mtk_uart_dma_free(uart, &uart->dma_tx);
    mtk_uart_dma_free(uart, &uart->dma_rx);
#endif

    mdelay(1);
    mtk_uart_fifo_flush(uart);

    
    free_irq(port->irq, port);

    mtk_uart_enable_dpidle(uart);
    
}
static void	mtk_uart_flush_buffer(struct uart_port *port)
{
#if defined(ENABLE_DEBUG)    
    struct mtk_uart *uart = (struct mtk_uart *)port;

    MSG_FUNC_ENTRY();
#endif    
    
}
void mtk_uart_update_sysclk(void)
{
	int i;
	unsigned long flags;
	struct mtk_uart *uart;
	struct uart_port *port;
	unsigned int baud;

	for (i = 0; i < UART_NR; i++) {
		uart = &mtk_uarts[i]; 
		port = &uart->port;
		baud = uart->baudrate;
		port->uartclk  		= UART_SYSCLK;  
		uart->sysclk        = UART_SYSCLK;  
		if(baud == 0) continue;	
		spin_lock_irqsave(&port->lock, flags);
		mtk_uart_set_baud(uart, baud);
		spin_unlock_irqrestore(&port->lock, flags);
	}
}
EXPORT_SYMBOL(mtk_uart_update_sysclk);
static void mtk_uart_set_termios(struct uart_port *port,
                                   struct ktermios *termios, struct ktermios *old)
{
    struct mtk_uart *uart = (struct mtk_uart *)port;
    unsigned long flags;
    unsigned int baud;
    int datalen, mode;
    int parity = 0;
    int stopbit = 1;

    MSG_FUNC_ENTRY();

    
    switch (termios->c_cflag & CSIZE) {
    case CS5:
        datalen = 5;
        break;
    case CS6:
        datalen = 6;
        break;
    case CS7:
        datalen = 7;
        break;
    case CS8:
    default:
        datalen = 8;
        break;
    }
    
    
    if (termios->c_cflag & CSTOPB)
        stopbit = 2;

    
    if (termios->c_cflag & PARENB) {
        if (termios->c_cflag & PARODD)
            parity = 1; 
        else
            parity = 2; 
    }

    spin_lock_irqsave(&port->lock, flags);
    
    
    port->read_status_mask = 0;    
    if (termios->c_iflag & INPCK) {
        
        port->read_status_mask |= UART_LSR_FE | UART_LSR_PE;
    }
    if (termios->c_iflag & (BRKINT | PARMRK)) {
        
        port->read_status_mask |= UART_LSR_BI;
    }
    
    port->ignore_status_mask = 0;
    if (termios->c_iflag & IGNPAR) {
        
        port->ignore_status_mask |= UART_LSR_FE | UART_LSR_PE;
    }
    if (termios->c_iflag & IGNBRK) {
        
        port->ignore_status_mask |= UART_LSR_BI;
        if (termios->c_iflag & IGNPAR) {
            
            port->ignore_status_mask |= UART_LSR_OE;
        }
    }

    
    if ((termios->c_cflag & CREAD) == 0) {
        uart->ignore_rx = 1;
    }

    
    baud = uart_get_baud_rate(port, termios, old, 0, uart->sysclk);     
    uart_update_timeout(port, termios->c_cflag, baud);    
    mtk_uart_config(uart, datalen, stopbit, parity);
    mtk_uart_set_baud(uart, baud);

    
    mtk_uart_fifo_set_trig(uart, uart->tx_trig, uart->rx_trig);

    
    MSG(CFG, "c_lflag:%X, c_iflag:%X, c_oflag:%X, c_cflag:%X\n", termios->c_lflag, termios->c_iflag, termios->c_oflag, termios->c_cflag);
    if (HW_FLOW_CTRL_PORT(uart) && (termios->c_cflag & CRTSCTS) && (!(termios->c_iflag&0x80000000))) {
        printk(KERN_NOTICE "Hardware Flow Control\n");
        mode = UART_FC_HW;
    } else if (termios->c_iflag & 0x80000000) {
        printk(KERN_NOTICE "MTK Software Flow Control\n");
        mode = UART_FC_SW;
    } else if (termios->c_iflag & (IXON | IXOFF | IXANY)) {
        printk(KERN_NOTICE "Linux default SW Flow Control\n");
        mode = UART_FC_NONE;    
    } else {
        printk(KERN_NOTICE "No Flow Control\n");
        mode = UART_FC_NONE;
    }
    mtk_uart_set_flow_ctrl(uart, mode);

    
    if (UART_ENABLE_MS(port, termios->c_cflag)) 
        uart->ms_enable = 1;
    else
        uart->ms_enable = 0;

    if (console_port && (uart == console_port) && uart->port.cons)
    {
        uart->port.cons->cflag = termios->c_cflag;
    }

    spin_unlock_irqrestore(&port->lock, flags);
}
static void mtk_uart_power_mgnt(struct uart_port *port, unsigned int state,
                                   unsigned int oldstate)
{
    struct mtk_uart *uart = (struct mtk_uart *)port;

    MSG(FUC, "%s(%d->%d)\n", __func__, oldstate, state);

	switch (state) {
	case 0:
        mtk_uart_power_up(uart);
		break;
	case 3:
        mtk_uart_power_down(uart);
		break;
	default:
		MSG(ERR, "unkown pm: %d\n", state);
	}
}
static int mtk_uart_set_wake(struct uart_port *port, unsigned int state)
{
    return 0; 
}
static const char *mtk_uart_type(struct uart_port *port)
{
    return "MTK UART";
}
static void mtk_uart_release_port(struct uart_port *port)
{
    return;
}
static int mtk_uart_request_port(struct uart_port *port)
{
    return 0;
}
static void mtk_uart_config_port(struct uart_port *port, int flags)
{ 
    struct mtk_uart* uart = (struct mtk_uart*)port;
    if (flags & UART_CONFIG_TYPE) {
        if (mtk_uart_request_port(port))
            MSG(ERR, "mtk_uart_request_port fail\n");
        port->type = PORT_MTK;
    }
}
 
static int mtk_uart_verify_port(struct uart_port *port,
    struct serial_struct *ser)
{
#if ( defined(ENABLE_DEBUG)||defined(SERIAL_STRUCT_EXT) ) 
    struct mtk_uart* uart = (struct mtk_uart*)port;
#endif        
    int ret = 0;
    MSG(FUC, "%s: %8x, %d, %d\n", __func__, ser->flags, ser->custom_divisor, uart->custom_baud);
    if (ser->type != PORT_UNKNOWN && ser->type != PORT_MTK)
        ret = -EINVAL;
    if (ser->irq != port->irq)
        ret = -EINVAL;
    if (ser->baud_base < 110)
        ret = -EINVAL;
#if defined(SERIAL_STRUCT_EXT)        
    
    uart->custom_baud = ser->reserved[0];
#endif    
    return ret;
}
static int mtk_uart_ioctl(struct uart_port *port, unsigned int cmd, 
                             unsigned long arg)
{
#if defined(ENABLE_DEBUG)    
    struct mtk_uart* uart = (struct mtk_uart*)port;        
    MSG(FUC, "IOCTL: %8X\n", cmd);    
#endif    
    return -ENOIOCTLCMD;
}
#ifdef CONFIG_CONSOLE_POLL
static int mtk_uart_get_poll_char(struct uart_port *port)
{   
    struct mtk_uart *uart = (struct mtk_uart *)port;
    
    #if 0
    while (!(uart->read_status(uart) & UART_LSR_DR))
        cpu_relax();
    #else
    if (!mtk_uart_data_ready(uart))
        return NO_POLL_CHAR;
    #endif
    

    return mtk_uart_read_byte(uart);
}
static void mtk_uart_put_poll_char(struct uart_port *port, unsigned char c)
{   
    struct mtk_uart *uart = (struct mtk_uart *)port;
    while (!mtk_uart_write_allow(uart)) 
        barrier();
    mtk_uart_write_byte(uart, c);    
}
#endif 
static struct uart_ops mtk_uart_ops =
{
    .tx_empty       = mtk_uart_tx_empty,
    .set_mctrl      = mtk_uart_set_mctrl,
    .get_mctrl      = mtk_uart_get_mctrl,
    .stop_tx        = mtk_uart_stop_tx,
    .start_tx       = mtk_uart_start_tx,
    .stop_rx        = mtk_uart_stop_rx,
    .send_xchar     = mtk_uart_send_xchar,
    .enable_ms      = mtk_uart_enable_ms,
    .break_ctl      = mtk_uart_break_ctl,
    .startup        = mtk_uart_startup,
    .shutdown       = mtk_uart_shutdown,
    .flush_buffer   = mtk_uart_flush_buffer,
    .set_termios    = mtk_uart_set_termios,
    .pm             = mtk_uart_power_mgnt,
    .set_wake       = mtk_uart_set_wake,
    .type           = mtk_uart_type,
    .release_port   = mtk_uart_release_port,
    .request_port   = mtk_uart_request_port,
    .config_port    = mtk_uart_config_port,
    .verify_port    = mtk_uart_verify_port,
    .ioctl          = mtk_uart_ioctl,
#ifdef CONFIG_CONSOLE_POLL
    .poll_get_char  = mtk_uart_get_poll_char,
    .poll_put_char  = mtk_uart_put_poll_char,
#endif    
};
static struct uart_driver mtk_uart_drv =
{
    .owner          = THIS_MODULE,
    .driver_name    = DRV_NAME,
    .dev_name       = "ttyMT",
    .major          = UART_MAJOR,
    .minor          = UART_MINOR,
    .nr             = UART_NR,
#if defined(CONFIG_MTK_SERIAL_CONSOLE) && !defined(CONFIG_MTK_SERIAL_MODEM_TEST)
    .cons           = &mtk_uart_console,
#endif
};
static int mtk_uart_probe(struct platform_device *pdev)
{
    struct mtk_uart     *uart;
    int err;

#ifdef CONFIG_OF
    if (pdev->dev.of_node) {
	struct device_node *node = pdev->dev.of_node;
	err = of_property_read_u32(node, "cell-index", &pdev->id);
	if (err){
		printk("[DTS] get uart platform_device id fail!!\n");
	}
    }
#endif

    uart = &mtk_uarts[pdev->id];
    

    MSG_FUNC_ENTRY();

    if(mtk_uart_plat_info_query("ADD_DMA_BIT_MASK_32"))
        pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);

    uart->port.dev = &pdev->dev;
    err = uart_add_one_port(&mtk_uart_drv, &uart->port);
    if (!err)
        platform_set_drvdata(pdev, uart);
    
#if defined(ENABLE_VFIFO)
    if ((err = mtk_uart_vfifo_create(uart))) {
        mtk_uart_vfifo_delete(uart);
        DEV_ERR("create vff buffer fail:%d\n", err);
    }
#endif
    return err;
}
static int mtk_uart_remove(struct platform_device *pdev)
{
    struct mtk_uart *uart = platform_get_drvdata(pdev);
    int err;

    platform_set_drvdata(pdev, NULL);

    if (!uart)
        return -EINVAL;
    
    err = uart_remove_one_port(&mtk_uart_drv, &uart->port);
    
#if defined(ENABLE_VFIFO)
    mtk_uart_vfifo_delete(uart);
#endif
    return err;
}
#ifdef CONFIG_PM 
static int mtk_uart_syscore_suspend(void)
{
    int ret = 0;
    unsigned long flags;
    if (bt_port)
    {
	struct mtk_uart *uart = bt_port;
	spin_lock_irqsave(&mtk_uart_bt_lock, flags);
        ret = uart_suspend_port(&mtk_uart_drv, &uart->port);
	
	
	mtk_uart_switch_tx_to_gpio(uart);
	spin_unlock_irqrestore(&mtk_uart_bt_lock, flags);
	printk(KERN_NOTICE "[UART%d] Suspend(%d)!\n", uart->nport, ret);
    }
    return ret;
}
static void mtk_uart_syscore_resume(void)
{
    int ret = 0;
    unsigned long flags;
    if (bt_port)
    {
	struct mtk_uart *uart = bt_port;
	spin_lock_irqsave(&mtk_uart_bt_lock, flags);
	mtk_uart_switch_to_tx(uart);
	ret = uart_resume_port(&mtk_uart_drv, &uart->port);
	spin_unlock_irqrestore(&mtk_uart_bt_lock, flags);
	disable_irq(uart->port.irq);
	printk(KERN_NOTICE "[UART%d] Resume(%d)!\n", uart->nport, ret);
    }
}
static int mtk_uart_suspend(struct platform_device *pdev, pm_message_t state)
{
    int ret = 0;
    struct mtk_uart *uart = platform_get_drvdata(pdev);
    if (console_suspend_enabled == 0 && uart == console_port && uart->poweron_count > 0)     
    	mtk_uart_save(uart);
    if(uart && (uart->nport < UART_NR) && (uart != bt_port)){
        ret = uart_suspend_port(&mtk_uart_drv, &uart->port);
        printk(KERN_NOTICE "[UART%d] Suspend(%d)!\n", uart->nport, ret);
	mtk_uart_switch_rx_to_gpio(uart);
    }
    return ret;
}
static int mtk_uart_resume(struct platform_device *pdev)
{
    int ret = 0;
    struct mtk_uart *uart = platform_get_drvdata(pdev);
    if (uart && (uart->nport < UART_NR) && (uart != bt_port)) {
	mtk_uart_switch_to_rx(uart);
        ret = uart_resume_port(&mtk_uart_drv, &uart->port);
        printk(KERN_NOTICE "[UART%d] Resume(%d)!\n", uart->nport, ret);
    }
    return ret;
}
static int mtk_uart_pm_suspend(struct device *device)
{
    struct platform_device *pdev;
    pr_debug("calling %s()\n", __func__);

    pdev = to_platform_device(device);
    BUG_ON(pdev == NULL);

    return mtk_uart_suspend(pdev, PMSG_SUSPEND);
}

static int mtk_uart_pm_resume(struct device *device)
{
    struct platform_device *pdev;
    pr_debug("calling %s()\n", __func__);

    pdev = to_platform_device(device);
    BUG_ON(pdev == NULL);

    return mtk_uart_resume(pdev);
}


static int mtk_uart_pm_freeze(struct device *device)
{
	struct platform_device *pdev;
	struct mtk_uart *uart = NULL;
	int ret = 0;
	int port_idx = 0;

	pdev = to_platform_device(device);
	BUG_ON(pdev == NULL);
	uart = platform_get_drvdata(pdev);

	port_idx = uart->nport;
	if (uart_freeze_enable[port_idx])
	{
		ret = uart_suspend_port(&mtk_uart_drv, &uart->port);
		pr_warn("[%s] here.\n", __func__);
		
		
		mtk_uart_switch_tx_to_gpio(uart);
		pr_warn("[%s] done.\n", __func__);
	}

	return 0;
}

static int mtk_uart_pm_restore(struct device *device)
{
	struct platform_device *pdev;
	struct mtk_uart *uart;
	int ret = 0;
	int port_idx = 0;

	pdev = to_platform_device(device);
	BUG_ON(pdev == NULL);
	uart = platform_get_drvdata(pdev);

	port_idx = uart->nport;
	if (uart_freeze_enable[port_idx])
	{
		mtk_uart_switch_to_tx(uart);
		ret = uart_resume_port(&mtk_uart_drv, &uart->port);
		pr_warn("[%s] uart (%p) base: 0x%lx, nport %d, dma mode: %d\n", __func__,
			uart, uart->base, uart->nport, uart->dma_mode);
	}

	return mtk_uart_resume(pdev);
}

static int mtk_uart_pm_restore_noirq(struct device *device)
{
#ifndef CONFIG_OF
    unsigned int gic_pending;
#endif
    struct mtk_uart *uart;
    
    
    uart = dev_get_drvdata(device);
    if (!uart || !uart->setting) {
        pr_warn("[%s] uart (%p) or uart->setting (%p) is null!!\n", __func__, uart, uart->setting);
        return 0;
    }
    mtk_uart_fifo_set_trig(uart, uart->tx_trig, uart->rx_trig);
#ifdef CONFIG_OF
    irq_set_irq_type(uart->setting->irq_num, uart->setting->irq_flags);
#else
    if (uart->setting->irq_sen == MT_EDGE_SENSITIVE) {
        irq_set_irq_type(uart->setting->irq_num, IRQF_TRIGGER_FALLING);
    } else {
        irq_set_irq_type(uart->setting->irq_num, IRQF_LEVEL_TRIGGER_POLARITY);
    }
#endif
    
#define GIC_DIST_PENDING_SET 0x200
    if (uart->tx_vfifo && uart->tx_mode == UART_TX_VFIFO_DMA) {
        irq_set_irq_type(uart->tx_vfifo->irq_id, IRQF_LEVEL_TRIGGER_POLARITY);
#ifndef CONFIG_OF
        gic_pending = DRV_Reg32(GIC_DIST_BASE + GIC_DIST_PENDING_SET + uart->tx_vfifo->irq_id/32*4);
        pr_warn("[%s] tx_vfifo(%p) gic_pending_mask(0x%08x)\n",
                __func__, uart->tx_vfifo->base, gic_pending);
#endif
    }
    if (uart->rx_vfifo && uart->rx_mode == UART_RX_VFIFO_DMA) {
        irq_set_irq_type(uart->rx_vfifo->irq_id, IRQF_LEVEL_TRIGGER_POLARITY);
#ifndef CONFIG_OF
        gic_pending = DRV_Reg32(GIC_DIST_BASE + GIC_DIST_PENDING_SET + uart->rx_vfifo->irq_id/32*4);
        pr_warn("[%s] rx_vfifo(%p) gic_pending_mask(0x%08x)\n",
                __func__, uart->rx_vfifo->base, gic_pending);
#endif
    }
    return 0;
}

#else 
#define mtk_uart_pm_suspend    NULL
#define mtk_uart_pm_resume NULL
#define mtk_uart_pm_freeze NULL
#define mtk_uart_pm_restore NULL
#define mtk_uart_pm_restore_noirq NULL
#endif 
struct dev_pm_ops mtk_uart_pm_ops = {
    .suspend = mtk_uart_pm_suspend,
    .resume = mtk_uart_pm_resume,
    .freeze = mtk_uart_pm_freeze,
    .thaw = mtk_uart_pm_restore,
    .poweroff = mtk_uart_pm_suspend,
    .restore = mtk_uart_pm_restore,
    .restore_noirq = mtk_uart_pm_restore_noirq,
};


static int mtk_uart_init_ports(void)
{
    int i;
#ifdef CONFIG_OF
    int idx;
    void __iomem *apdma_uart0_base=0;
    struct mtk_uart_vfifo *vfifo;
#endif
    struct mtk_uart *uart;
    unsigned long base;

    spin_lock_init(&mtk_console_lock);

#ifdef CONFIG_OF
    apdma_uart0_base = get_apdma_uart0_base();
#endif
    for (i = 0; i < UART_NR; i++) {
#ifdef CONFIG_OF
        set_uart_default_settings(i);
#endif
        uart = &mtk_uarts[i];        
        uart->setting = get_uart_default_settings(i);
#ifdef CONFIG_OF
#if defined(ENABLE_VFIFO)
	if(uart->setting->vff){
		if(i*2 < sizeof(mtk_uart_vfifo_port)/sizeof(mtk_uart_vfifo_port[0])){
			for (idx = i*2; idx < i*2 + 2; idx++) {
			    vfifo = &mtk_uart_vfifo_port[idx];
			    vfifo->base = (apdma_uart0_base+0x0080*idx);
			    vfifo->irq_id = get_uart_vfifo_irq_id(idx);
			}
		}
	}
#endif
#endif
        base = uart->setting->uart_base;        
        uart->port.iotype   = UPIO_MEM;
#ifdef CONFIG_OF
        uart->port.mapbase  = uart->setting->uart_phys_base;   
#else
        uart->port.mapbase  = IO_VIRT_TO_PHYS(base);   
#endif
        uart->port.membase  = (unsigned char __iomem *)base;
        uart->port.irq      = uart->setting->irq_num;
        uart->port.fifosize = UART_FIFO_SIZE;
        uart->port.ops      = &mtk_uart_ops;
        uart->port.flags    = UPF_BOOT_AUTOCONF;
        uart->port.line     = i;
        uart->port.uartclk  = UART_SYSCLK;
        
        
        spin_lock_init(&uart->port.lock);
        uart->base          = base;
        uart->auto_baud     = CFG_UART_AUTOBAUD;
        uart->nport         = i;
        uart->sysclk        = UART_SYSCLK; 
        
        uart->dma_mode      = uart->setting->dma_mode;
        uart->tx_mode       = uart->setting->tx_mode;
        uart->rx_mode       = uart->setting->rx_mode;
        uart->tx_trig       = uart->setting->tx_trig;
        uart->rx_trig       = uart->setting->rx_trig;
        uart->write_allow   = mtk_uart_write_allow;
        uart->read_allow    = mtk_uart_read_allow;
        uart->write_byte    = mtk_uart_write_byte;
        uart->read_byte     = mtk_uart_read_byte;
        uart->read_status   = mtk_uart_read_status;
        uart->poweron_count = 0;
        uart->timeout_count = 0;
        uart->baudrate      = 0;
        uart->custom_baud   = 0;
 	uart->registers.dll = 1;
	uart->registers.dlh = 0;
	uart->registers.ier = 0;
	uart->registers.lcr = 0;
	uart->registers.mcr = 0;
	uart->registers.fcr = 0;
	uart->registers.lsr = 0x60;
	uart->registers.efr = 0;
	uart->registers.highspeed = 0;
	uart->registers.sample_count = 0;
	uart->registers.sample_point = 0xff;
	uart->registers.fracdiv_l = 0;
	uart->registers.fracdiv_m = 0;
	uart->registers.escape_en = 0;
	uart->registers.guard = 0;
     	uart->registers.rx_sel = 0;
		uart->evt_mask = (unsigned int)get_uart_evt_mask(i);

#if defined(CONFIG_MTK_SERIAL_MODEM_TEST)
        if (get_modem_uart(i)) {            
            
            mtk_uart_power_up(uart); 
            
            continue;
        }
#else        
        
        mtk_uart_disable_intrs(uart, UART_IER_ALL_INTS);

#ifdef CONFIG_OF
        irq_set_irq_type(uart->setting->irq_num, uart->setting->irq_flags);
#else
        if (uart->setting->irq_sen == MT_EDGE_SENSITIVE) {
            irq_set_irq_type(uart->setting->irq_num, IRQF_EDGE_TRIGGER_POLARITY);
        } else {
            irq_set_irq_type(uart->setting->irq_num, IRQF_LEVEL_TRIGGER_POLARITY);
        }
#endif

        mtk_uart_fifo_init(uart);
        mtk_uart_set_mode(uart, uart->dma_mode);
        
#endif        
    }
#if defined(CONFIG_MTK_SERIAL_MODEM_TEST)
    
#endif 
    return 0;
}
#ifdef CONFIG_OF
static const struct of_device_id apuart_of_ids[] = {
	{ .compatible = "mediatek,AP_UART0", },
	{ .compatible = "mediatek,AP_UART1", },
#ifndef CONFIG_MTK_FPGA
	{ .compatible = "mediatek,AP_UART2", },
	{ .compatible = "mediatek,AP_UART3", },
#endif
	{}
};
#endif

static struct platform_driver mtk_uart_dev_drv =
{
    .probe   = mtk_uart_probe,
    .remove  = mtk_uart_remove,
#ifdef CONFIG_PM    
    .suspend = mtk_uart_suspend,
    .resume  = mtk_uart_resume,
#endif    
    .driver = {
        .name    = DRV_NAME,
        .owner   = THIS_MODULE,   
#ifdef CONFIG_OF
        .of_match_table = apuart_of_ids,
#endif
#ifdef CONFIG_PM
        .pm      = &mtk_uart_pm_ops,
#endif
 
    }
};

#ifdef CONFIG_PM   
static struct syscore_ops mtk_uart_syscore_ops = {
	.suspend	= mtk_uart_syscore_suspend,
	.resume		= mtk_uart_syscore_resume,
};

static int __init mtk_uart_init_ops(void)
{
    register_syscore_ops(&mtk_uart_syscore_ops);
    return 0;
}
#endif 
static int __init mtk_uart_init(void)
{
    int ret = 0;

#ifndef CONFIG_MTK_SERIAL_CONSOLE
    mtk_uart_init_ports();
#endif

#if defined(ENABLE_SYSFS)
    mtk_uart_sysfs();
#endif 

    ret = uart_register_driver(&mtk_uart_drv);

    if (ret) return ret;
    
    ret = platform_driver_register(&mtk_uart_dev_drv);

    if (ret) {
        uart_unregister_driver(&mtk_uart_drv);
        return ret;
    }
#ifdef CONFIG_PM
    mtk_uart_init_ops();
#endif
    mtk_uart_init_debug_spinlock();
    spin_lock_init(&mtk_uart_bt_lock);
    return ret;
}
static void __exit mtk_uart_exit(void)
{
    platform_driver_unregister(&mtk_uart_dev_drv);
    uart_unregister_driver(&mtk_uart_drv);
}
#ifdef ENABLE_UART_SLEEP
int request_uart_to_sleep(void)
{
    u32 val1;
    int i = 0;
	int uart_idx = 0;
	struct mtk_uart *uart;
	unsigned long base;

	for (uart_idx = 0; uart_idx < UART_NR; uart_idx++)
	{
		#if defined(CONFIG_MTK_HDMI_SUPPORT)
		#ifdef MHL_UART_SHARE_PIN
		{
			if((is_hdmi_active()== 0)  && (uart_idx == 1))		
				continue;
		}	
		#endif
		#endif
	
		uart = &mtk_uarts[uart_idx];
        base = uart->base; 
		if (uart->poweron_count > 0)
		{
    		
    		val1 = UART_READ32(UART_SLEEP_REQ);
    		reg_sync_writel(val1 | UART_CLK_OFF_REQ, UART_SLEEP_REQ);
    		
	    	
	    	while (!(UART_READ32(UART_SLEEP_ACK) & UART_CLK_OFF_ACK)) {
	        	if (i++ >= WAIT_UART_ACK_TIMES) {
	            	reg_sync_writel(val1, UART_SLEEP_REQ);
	            	printk(KERN_ERR "CANNOT GET UART[%d] SLEEP ACK\n", uart_idx);
	            	
	            	return -EBUSY;
	        	}
	        	udelay(10);
	    	}
		}
		else
		{
			
		}
	}

	return 0;
}
EXPORT_SYMBOL(request_uart_to_sleep);


int request_uart_to_wakeup(void)
{
	
    u32 val1;
    int i = 0;
	int uart_idx = 0;
	struct mtk_uart *uart;
	unsigned long base;

	for (uart_idx = 0; uart_idx < UART_NR; uart_idx++)
	{
		uart = &mtk_uarts[uart_idx];
        base = uart->base; 
		if (uart->poweron_count > 0)
		{
    		
    		val1 = UART_READ32(UART_SLEEP_REQ);
    		reg_sync_writel(val1 & (~UART_CLK_OFF_REQ), UART_SLEEP_REQ);

	    	
	    	while ((UART_READ32(UART_SLEEP_ACK) & UART_CLK_OFF_ACK)) {
	        	if (i++ >= WAIT_UART_ACK_TIMES) {
	            	reg_sync_writel(val1, UART_SLEEP_REQ);
	            	printk(KERN_ERR "CANNOT GET UART[%d] WAKE ACK\n", uart_idx);
	            	
	            	return -EBUSY;
	        	}
	        	udelay(10);
	    	}
		}
		else
		{
			
		}
	}

	return 0;
}
EXPORT_SYMBOL(request_uart_to_wakeup);

#endif
module_init(mtk_uart_init);
module_exit(mtk_uart_exit);
MODULE_AUTHOR("MTK");
MODULE_DESCRIPTION("MTK Serial Port Driver $Revision$");
MODULE_LICENSE("GPL");
