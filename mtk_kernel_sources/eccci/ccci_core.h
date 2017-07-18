#ifndef __CCCI_CORE_H__
#define __CCCI_CORE_H__

#include <linux/wait.h>
#include <linux/skbuff.h>
#include <linux/timer.h>
#include <linux/types.h>
#include <linux/ktime.h>
#include <linux/netdevice.h>
#include <linux/platform_device.h>
#include <linux/wakelock.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <mach/mt_ccci_common.h>
#include <mach/ccci_config.h>
#include "ccci_debug.h"

#define CCCI_DEV_NAME "ccci"
#define CCCI_MTU  (3584-128)
#define CCCI_MAGIC_NUM 0xFFFFFFFF

struct ccci_md_attribute
{
	struct attribute attr;
	struct ccci_modem *modem;
	ssize_t (*show)(struct ccci_modem *md, char *buf);
	ssize_t (*store)(struct ccci_modem *md, const char *buf, size_t count);
};

#define CCCI_MD_ATTR(_modem, _name, _mode, _show, _store)	\
static struct ccci_md_attribute ccci_md_attr_##_name = {	\
	.attr = {.name = __stringify(_name), .mode = _mode },	\
	.modem = _modem,					\
	.show = _show,						\
	.store = _store,					\
}

struct ccci_header{
	u32 data[2]; 
#ifdef FEATURE_SEQ_CHECK_EN
	u16 channel:16;
	u16 seq_num:15;
	u16 assert_bit:1;
#else
	u32 channel;
#endif
	u32 reserved;
} __attribute__ ((packed)); 


typedef enum {
	INVALID = 0, 
	GATED, 
	BOOTING, 
	READY, 
	EXCEPTION, 
	RESET, 
	
	RX_IRQ, 
	TX_IRQ, 
	TX_FULL, 
	BOOT_FAIL, 
}MD_STATE; 

typedef enum { 
	MD_BOOT_STAGE_0 = 0, 
	MD_BOOT_STAGE_1 = 1, 
	MD_BOOT_STAGE_2 = 2,
	MD_BOOT_STAGE_EXCEPTION = 3
}MD_BOOT_STAGE; 

typedef enum {
	EX_NONE = 0,
	EX_INIT,
	EX_DHL_DL_RDY,
	EX_INIT_DONE,
	
	MD_NO_RESPONSE,
	MD_WDT,
}MD_EX_STAGE;

typedef struct _exception_record_header_t {
	u8  ex_type;
	u8  ex_nvram;
	u16 ex_serial_num;
} __attribute__ ((packed)) EX_HEADER_T;

typedef struct _ex_environment_info_t {
	u8  boot_mode;  
	u8 reserved1[8];
	u8 execution_unit[8];
	u8 status; 
	u8 ELM_status; 
	u8 reserved2[145];
} __attribute__ ((packed)) EX_ENVINFO_T;

typedef struct _ex_fatalerror_code_t {
	u32 code1;
	u32 code2;
} __attribute__ ((packed)) EX_FATALERR_CODE_T;

typedef struct _ex_fatalerror_t {
	EX_FATALERR_CODE_T error_code;
	u8 reserved1[288];
} __attribute__ ((packed)) EX_FATALERR_T;

typedef struct _ex_assert_fail_t {
	u8 filename[24];
	u32  linenumber;
	u32  parameters[3];
	u8 reserved1[256];
} __attribute__ ((packed)) EX_ASSERTFAIL_T;

typedef union {
	EX_FATALERR_T fatalerr;
	EX_ASSERTFAIL_T assert;
} __attribute__ ((packed)) EX_CONTENT_T;

typedef struct _ex_exception_log_t {
	EX_HEADER_T	header;
	u8	reserved1[12];
	EX_ENVINFO_T	envinfo;
	u8	reserved2[36];
	EX_CONTENT_T	content;
} __attribute__ ((packed)) EX_LOG_T;

typedef struct _ccci_msg {
	union{
		u32 magic;	
		u32 addr;	
		u32 data0;	
	};
	union{
		u32 id;	
		u32 len;	
		u32 data1;	
	};
	u32 channel;
	u32 reserved;
} __attribute__ ((packed)) ccci_msg_t;

typedef struct dump_debug_info {
	unsigned int type;
	char *name;
	unsigned int more_info;
	union {
		struct {
			char file_name[30];
			int line_num;
			unsigned int parameters[3];
		} assert;	
		struct {
			int err_code1;
    		int err_code2;
			char offender[9];
		}fatal_error;
		ccci_msg_t data;
		struct {
			unsigned char execution_unit[9]; 
			char file_name[30];
			int line_num;
			unsigned int parameters[3];
		}dsp_assert;
		struct {
			unsigned char execution_unit[9];
			unsigned int  code1;
		}dsp_exception;
		struct {
			unsigned char execution_unit[9];
			unsigned int  err_code[2];
		}dsp_fatal_err;
	};
	void *ext_mem;
	size_t ext_size;
	void *md_image;
	size_t md_size;
	void *platform_data;
	void (*platform_call)(void *data);
}DEBUG_INFO_T;

typedef enum {
	IDLE = 0,
	FLYING,
	PARTIAL_READ,
	ERROR,
}REQ_STATE;

typedef enum {
	IN = 0,
	OUT
}DIRECTION;

typedef enum {
	NOOP = 0, 
	RECYCLE, 
	FREE, 
}DATA_POLICY;

#define CCCI_REQUEST_TRACE_DEPTH 3
struct ccci_request{
	struct sk_buff *skb;
	void *gpd; 
	
	struct list_head entry;
	char policy;
	char blocking; 
	char state; 
#ifdef CONFIG_HTC_FEATURES_RIL_PCN0004_HTC_GARBAGE_FILTER
	unsigned char ioc_override; 
#endif

	char dir;
	dma_addr_t gpd_addr; 
	dma_addr_t data_buffer_ptr_saved;
};

struct ccci_modem;
struct ccci_port;

struct ccci_port_ops {
	
	int (*init)(struct ccci_port *port);
	int (*recv_request)(struct ccci_port *port, struct ccci_request* req);
	
	int (*req_match)(struct ccci_port *port, struct ccci_request* req);
	void (*md_state_notice)(struct ccci_port *port, MD_STATE state);
};

struct ccci_port {
	
	
	CCCI_CH tx_ch;
	CCCI_CH rx_ch;
	unsigned char txq_index;
	unsigned char rxq_index;
	unsigned char txq_exp_index;
	unsigned char rxq_exp_index;
	unsigned char flags;
	struct ccci_port_ops *ops;
	
	unsigned int minor;
	char *name;
	
	struct ccci_modem *modem;
	void *private_data;
	atomic_t usage_cnt;
	struct list_head entry;
	struct list_head rx_req_list;
	spinlock_t rx_req_lock;
	wait_queue_head_t rx_wq; 
	int rx_length;
	int rx_length_th;
	struct wake_lock rx_wakelock;
	unsigned int tx_busy_count;
	unsigned int rx_busy_count;
};
#define PORT_F_ALLOW_DROP 	(1<<0) 
#define PORT_F_RX_FULLED 	(1<<1) 
#define PORT_F_USER_HEADER 	(1<<2) 
#define PORT_F_RX_EXCLUSIVE	(1<<3) 

struct ccci_modem_cfg {
	unsigned int load_type;
	unsigned int load_type_saving;
	unsigned int setting;
};
#define MD_SETTING_ENABLE (1<<0)
#define MD_SETTING_RELOAD (1<<1)
#define MD_SETTING_FIRST_BOOT (1<<2) 
#define MD_SETTING_STOP_RETRY_BOOT (1<<3)
#define MD_SETTING_DUMMY  (1<<7)

struct ccci_mem_layout 
{
	
	void __iomem*	md_region_vir;
	phys_addr_t		md_region_phy;
	unsigned int	md_region_size;
	
	void __iomem*	dsp_region_vir;
	phys_addr_t		dsp_region_phy;
	unsigned int	dsp_region_size;
	
	void __iomem*	smem_region_vir;
	phys_addr_t		smem_region_phy;
	unsigned int	smem_region_size;
	unsigned int	smem_offset_AP_to_MD; 
};

struct ccci_smem_layout
{
	
	void __iomem*		ccci_exp_smem_base_vir;
	phys_addr_t			ccci_exp_smem_base_phy;
	unsigned int		ccci_exp_smem_size;
	unsigned int        ccci_exp_dump_size;

	
	void __iomem*		ccci_exp_smem_ccci_debug_vir;
	unsigned int		ccci_exp_smem_ccci_debug_size;
	void __iomem*		ccci_exp_smem_mdss_debug_vir;
	unsigned int		ccci_exp_smem_mdss_debug_size;

	
	void __iomem*		ccci_exp_rec_base_vir;
};

typedef enum {
	DUMP_FLAG_CCIF = (1<<0),
	DUMP_FLAG_CLDMA = (1<<1),
	DUMP_FLAG_REG = (1<<2),
	DUMP_FLAG_SMEM = (1<<3),
	DUMP_FLAG_IMAGE = (1<<4),
	DUMP_FLAG_LAYOUT = (1<<5),
} MODEM_DUMP_FLAG;

typedef enum {
	EE_FLAG_ENABLE_WDT = (1<<0),
	EE_FLAG_DISABLE_WDT = (1<<1),
} MODEM_EE_FLAG;

#define MD_IMG_DUMP_SIZE (1<<8)
#define DSP_IMG_DUMP_SIZE (1<<9)

typedef enum {
	LOW_BATTERY,
	BATTERY_PERCENT,
} LOW_POEWR_NOTIFY_TYPE;

typedef enum {
	CCCI_MESSAGE,
	CCIF_INTERRUPT,
	CCIF_INTR_SEQ,
} MD_COMM_TYPE;

typedef enum {
	MD_STATUS_POLL_BUSY = (1<<0),
	MD_STATUS_ASSERTED = (1<<1),
} MD_STATUS_POLL_FLAG;

struct ccci_modem_ops {
	
	int (*init)(struct ccci_modem *md);
	int (*start)(struct ccci_modem *md);
	int (*reset)(struct ccci_modem *md); 
	int (*stop)(struct ccci_modem *md, unsigned int timeout);
	int (*send_request)(struct ccci_modem *md, unsigned char txqno, struct ccci_request *req);
	int (*give_more)(struct ccci_modem *md, unsigned char rxqno);
	int (*write_room)(struct ccci_modem *md, unsigned char txqno);
	int (*start_queue)(struct ccci_modem *md, unsigned char qno, DIRECTION dir);
	int (*stop_queue)(struct ccci_modem *md, unsigned char qno, DIRECTION dir);
	int (*napi_poll)(struct ccci_modem *md, unsigned char rxqno, struct napi_struct *napi ,int weight);
	int (*send_runtime_data)(struct ccci_modem *md, unsigned int sbp_code);
	int (*broadcast_state)(struct ccci_modem *md, MD_STATE state);
	int (*force_assert)(struct ccci_modem *md, MD_COMM_TYPE type);
	int (*dump_info)(struct ccci_modem *md, MODEM_DUMP_FLAG flag, void *buff, int length);
	struct ccci_port* (*get_port_by_minor)(struct ccci_modem *md, int minor);
	struct ccci_port* (*get_port_by_channel)(struct ccci_modem *md, CCCI_CH ch);
	int (*low_power_notify)(struct ccci_modem *md, LOW_POEWR_NOTIFY_TYPE type, int level);
	int (*ee_callback)(struct ccci_modem *md, MODEM_EE_FLAG flag);
};

struct ccci_modem {
	unsigned char index;
	unsigned char *private_data;
	struct list_head rx_ch_ports[CCCI_MAX_CH_NUM]; 
	short seq_nums[2][CCCI_MAX_CH_NUM];
	unsigned int capability;
	volatile MD_STATE md_state; 
	struct ccci_modem_ops *ops;
	atomic_t wakeup_src;
	struct ccci_port *ports;

	struct list_head entry;
	unsigned char port_number;
	char post_fix[IMG_POSTFIX_LEN];
	unsigned int major;
	unsigned int minor_base;
	struct kobject kobj;
	struct ccci_mem_layout mem_layout;
	struct ccci_smem_layout smem_layout;
	struct ccci_image_info img_info[IMG_NUM];
	unsigned int sim_type;
	unsigned int sbp_code;
	unsigned int sbp_code_default;
	unsigned char critical_user_active[4];
	unsigned int md_img_exist[MAX_IMG_NUM]; 
	struct platform_device *plat_dev;
	volatile MD_BOOT_STAGE boot_stage;
	MD_EX_STAGE ex_stage; 
	struct ccci_modem_cfg config;
	struct timer_list bootup_timer;
	struct timer_list ex_monitor;
	struct timer_list ex_monitor2;
	struct timer_list md_status_poller;
	struct timer_list md_status_timeout;
	unsigned int md_status_poller_flag;
	spinlock_t ctrl_lock;
	volatile unsigned int ee_info_flag;
	DEBUG_INFO_T debug_info;
	unsigned char ex_type;
	EX_LOG_T ex_info;
	
	
};

extern void ccci_free_req(struct ccci_request *req);
extern void ccci_md_exception_notify(struct ccci_modem *md, MD_EX_STAGE stage);

static inline void ccci_setup_channel_mapping(struct ccci_modem *md)
{
	int i;
	struct ccci_port *port = NULL;
	
	for(i=0; i<ARRAY_SIZE(md->rx_ch_ports); i++) {
		INIT_LIST_HEAD(&md->rx_ch_ports[i]); 
	}
	for(i=0; i<md->port_number; i++) {
		list_add_tail(&md->ports[i].entry, &md->rx_ch_ports[md->ports[i].rx_ch]);
	}
	for(i=0; i<ARRAY_SIZE(md->rx_ch_ports); i++) {
		if(!list_empty(&md->rx_ch_ports[i])) {
			CCCI_INF_MSG(md->index, CORE, "CH%d ports:", i);
			list_for_each_entry(port, &md->rx_ch_ports[i], entry) {
				printk("%s(%d/%d) ", port->name, port->rx_ch, port->tx_ch);
			}
			printk("\n");
		}
	}
}

static inline void ccci_reset_seq_num(struct ccci_modem *md)
{
	
	memset(md->seq_nums[OUT], 0, sizeof(md->seq_nums[OUT]));
	memset(md->seq_nums[IN], -1, sizeof(md->seq_nums[IN]));
}

static inline void ccci_inc_tx_seq_num(struct ccci_modem *md, struct ccci_request *req)
{
#ifdef FEATURE_SEQ_CHECK_EN
	struct ccci_header *ccci_h = (struct ccci_header *)req->skb->data;
	if(ccci_h->channel>=sizeof(md->seq_nums[OUT]) || ccci_h->channel<0) {
		CCCI_INF_MSG(md->index, CORE, "ignore seq inc on channel %x\n", *(((u32 *)ccci_h)+2));
			return;  
	}
	ccci_h->seq_num = md->seq_nums[OUT][ccci_h->channel]++;
	ccci_h->assert_bit = 1;

	
	
	if ((ccci_h->channel==CCCI_RPC_TX || ccci_h->channel==CCCI_FS_TX) && md->boot_stage!=MD_BOOT_STAGE_1)
		ccci_h->assert_bit = 0;

#endif
}

#define PORT_TXQ_INDEX(p) ((p)->modem->md_state==EXCEPTION?(p)->txq_exp_index:(p)->txq_index)
#define PORT_RXQ_INDEX(p) ((p)->modem->md_state==EXCEPTION?(p)->rxq_exp_index:(p)->rxq_index)

static inline int ccci_port_send_request(struct ccci_port *port, struct ccci_request *req)
{
	struct ccci_modem *md = port->modem;
	return md->ops->send_request(md, PORT_TXQ_INDEX(port), req);
}

static inline int ccci_port_recv_request(struct ccci_modem *md, struct ccci_request *req)
{
	struct ccci_header *ccci_h = (struct ccci_header *)req->skb->data;
	struct ccci_port *port = NULL;
	struct list_head *port_list = NULL;
	int ret = -CCCI_ERR_CHANNEL_NUM_MIS_MATCH;
#ifdef FEATURE_SEQ_CHECK_EN
	u16 channel, seq_num, assert_bit;
#endif
	char matched = 0;

	if(unlikely(ccci_h->channel >= CCCI_MAX_CH_NUM)) {
		ret = -CCCI_ERR_CHANNEL_NUM_MIS_MATCH;
		goto err_exit;
	}
	
	port_list = &md->rx_ch_ports[ccci_h->channel];
	list_for_each_entry(port, port_list, entry) {
		matched = (port->ops->req_match==NULL)?(ccci_h->channel == port->rx_ch):port->ops->req_match(port, req);
		if(matched) {
#ifdef FEATURE_SEQ_CHECK_EN
			channel = ccci_h->channel;
			seq_num = ccci_h->seq_num;
			assert_bit = ccci_h->assert_bit;
#endif
			ret = port->ops->recv_request(port, req);
#ifdef FEATURE_SEQ_CHECK_EN
			if(ret>=0 || ret==-CCCI_ERR_DROP_PACKET) {
				if(assert_bit && ((seq_num - md->seq_nums[IN][channel]) & 0x7FFF) != 1) {
					CCCI_ERR_MSG(md->index, CORE, "port %s seq number out-of-order %d->%d\n",
						port->name, seq_num, md->seq_nums[IN][channel]);
					md->ops->force_assert(md, CCIF_INTR_SEQ);
				} else {
					
					md->seq_nums[IN][channel] = seq_num;
				}
			}
#endif
			if(ret == -CCCI_ERR_PORT_RX_FULL)
				port->rx_busy_count++;
			break;
		}
	}

err_exit:
	if(ret == -CCCI_ERR_CHANNEL_NUM_MIS_MATCH) {
		CCCI_ERR_MSG(md->index, CORE, "drop on not supported channel %d\n", ccci_h->channel);
		list_del(&req->entry); 
		req->policy = RECYCLE;
		ccci_free_req(req);
		ret = -CCCI_ERR_DROP_PACKET;
	}
	return ret;
}

static inline int ccci_port_ask_more_request(struct ccci_port *port)
{
	struct ccci_modem *md = port->modem;
	int ret;
	
	if(port->flags & PORT_F_RX_FULLED)
		ret = md->ops->give_more(port->modem, PORT_RXQ_INDEX(port));
	else
		ret = -1;
	return ret;
}

static inline void ccci_port_struct_init(struct ccci_port *port, struct ccci_modem *md)
{
	INIT_LIST_HEAD(&port->rx_req_list);
	spin_lock_init(&port->rx_req_lock);
	INIT_LIST_HEAD(&port->entry);
	init_waitqueue_head(&port->rx_wq);
	port->rx_length = 0;
	port->tx_busy_count = 0;
	port->rx_busy_count = 0;
	atomic_set(&port->usage_cnt, 0);
	port->modem = md;
	wake_lock_init(&port->rx_wakelock, WAKE_LOCK_SUSPEND, port->name);
}

static inline void ccci_request_struct_init(struct ccci_request *req)
{
	req->skb = NULL;
	req->state = IDLE;
	req->policy = FREE;
#ifdef CONFIG_HTC_FEATURES_RIL_PCN0004_HTC_GARBAGE_FILTER
	req->ioc_override = 0;
#endif
	req->entry.next = LIST_POISON1;
	req->entry.prev = LIST_POISON2;
}

struct ccci_modem *ccci_allocate_modem(int private_size);
int ccci_register_modem(struct ccci_modem *modem);
int ccci_register_dev_node(const char *name, int major_id, int minor);
struct ccci_port *ccci_get_port_for_node(int major, int minor);
int ccci_send_msg_to_md(struct ccci_modem *md, CCCI_CH ch, CCCI_MD_MSG msg, u32 resv, int blocking);
int ccci_send_virtual_md_msg(struct ccci_modem *md, CCCI_CH ch, CCCI_MD_MSG msg, u32 resv);
struct ccci_modem *ccci_get_modem_by_id(int md_id);
int exec_ccci_kern_func_by_md_id(int md_id, unsigned int id, char *buf, unsigned int len);

#endif 
