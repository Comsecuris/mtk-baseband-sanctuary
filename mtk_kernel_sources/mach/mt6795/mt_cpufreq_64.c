
#define __MT_CPUFREQ_C__


#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cpu.h>
#include <linux/cpufreq.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#include <linux/earlysuspend.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/xlog.h>
#include <linux/jiffies.h>
#include <linux/bitops.h>
#include <linux/uaccess.h>
#include <linux/aee.h>

#ifdef CONFIG_OF
#include <linux/of.h>
#include <linux/of_address.h>
#endif

#include "mach/mt_typedefs.h"
#include "mach/irqs.h"
#include "mach/mt_irq.h"
#include "mach/mt_thermal.h"
#include "mach/mt_spm_idle.h"
#include "mach/mt_pmic_wrap.h"
#include "mach/mt_clkmgr.h"
#include "mach/mt_freqhopping.h"
#include "mach/mt_spm.h"
#include "mach/mt_ptp.h"
#include "mach/upmu_sw.h"
#include "mach/mtk_rtc_hal.h"
#include "mach/mt_rtc_hw.h"
#include "mach/mt_hotplug_strategy.h"

#ifndef __KERNEL__
#include "freqhop_sw.h"
#include <mt_spm.h>
#endif

#include "mach/mt_cpufreq.h"

extern int is_ext_buck_sw_ready(void); 
extern int ext_buck_vosel(unsigned long val); 
extern int da9210_read_byte(kal_uint8 cmd, kal_uint8 *ret_data); 

extern u32 get_devinfo_with_index(u32 index);
extern void (*cpufreq_freq_check)(enum mt_cpu_dvfs_id id);

#ifdef __KERNEL__
extern unsigned int mt_get_cpu_freq(void);
#endif


#define CONFIG_CPU_DVFS_SHOWLOG 1

#define CONFIG_CPU_DVFS_POWER_THROTTLING  1     
#ifdef CONFIG_MTK_RAM_CONSOLE
#define CONFIG_CPU_DVFS_AEE_RR_REC 1              
#endif

#define MAX(a, b) ((a) >= (b) ? (a) : (b))
#define MIN(a, b) ((a) >= (b) ? (b) : (a))

#define PMIC_SETTLE_TIME(old_mv, new_mv) ((((old_mv) > (new_mv)) ? ((old_mv) - (new_mv)) : ((new_mv) - (old_mv))) * 2 / 2500 + 25 + 1)  
#define NORMAL_DIFF_VRSAM_VPROC    10000   
#define MAX_DIFF_VSRAM_VPROC       20000  
#define MIN_VSRAM_VOLT             93000  
#define MAX_VSRAM_VOLT             115000  
#define MAX_VPROC_VOLT             115000  

#define PMIC_CMD_DELAY_TIME     5
#define MIN_PMIC_SETTLE_TIME    25
#define PMIC_VOLT_UP_SETTLE_TIME(old_volt, new_volt)    (((((new_volt) - (old_volt)) + 1250 - 1) / 1250) + PMIC_CMD_DELAY_TIME)
#define PMIC_VOLT_DOWN_SETTLE_TIME(old_volt, new_volt)    (((((old_volt) - (new_volt)) * 2)  / 625) + PMIC_CMD_DELAY_TIME)
#define PLL_SETTLE_TIME         (20)

#define RAMP_DOWN_TIMES         (2)             
#define CPUFREQ_BOUNDARY_FOR_FHCTL   (CPU_DVFS_FREQ5)       

#define DEFAULT_VOLT_VSRAM      (105000)
#define DEFAULT_VOLT_VLTE       (100000)
#define DEFAULT_VOLT_VGPU       (100000)
#define DEFAULT_VOLT_SOC        (100000)


#define CPU_DVFS_FREQ0   (1846000) 
#define CPU_DVFS_FREQ1   (1677000) 
#define CPU_DVFS_FREQ2   (1547000) 
#define CPU_DVFS_FREQ3   (1417000) 
#define CPU_DVFS_FREQ4   (1300000) 
#define CPU_DVFS_FREQ5   (1183000) 
#define CPU_DVFS_FREQ6   (806000) 
#define CPU_DVFS_FREQ7   (403000) 
#define CPUFREQ_LAST_FREQ_LEVEL    (CPU_DVFS_FREQ7)

#define CPU_DVFS_FREQ0_1   (1950000) 
#define CPU_DVFS_FREQ1_1   (1781000) 
#define CPU_DVFS_FREQ2_1   (1625000) 
#define CPU_DVFS_FREQ3_1   (1469000) 
#define CPU_DVFS_FREQ4_1   (1326000) 
#define CPU_DVFS_FREQ5_1   (1183000) 
#define CPU_DVFS_FREQ6_1   (806000) 
#define CPU_DVFS_FREQ7_1   (403000) 
#define CPUFREQ_LAST_FREQ1_LEVEL    (CPU_DVFS_FREQ7_1)

#define CPU_DVFS_FREQ0_2   (2158000) 
#define CPU_DVFS_FREQ1_2   (1885000) 
#define CPU_DVFS_FREQ2_2   (1664000) 
#define CPU_DVFS_FREQ3_2   (1482000) 
#define CPU_DVFS_FREQ4_2   (1326000) 
#define CPU_DVFS_FREQ5_2   (1183000) 
#define CPU_DVFS_FREQ6_2   (806000) 
#define CPU_DVFS_FREQ7_2   (403000) 
#define CPUFREQ_LAST_FREQ2_LEVEL    (CPU_DVFS_FREQ7_2)

#ifdef CONFIG_CPU_DVFS_POWER_THROTTLING
#define PWR_THRO_MODE_LBAT_1183MHZ	BIT(0)
#define PWR_THRO_MODE_BAT_OC_1183MHZ	BIT(1)
#define PWR_THRO_MODE_BAT_PER_1183MHZ	BIT(2)

#define CPU_DVFS_OPPIDX_1183MHZ		5
#define CPU_DVFS_OPPIDX_806MHZ		6
#endif

#ifndef __KERNEL__ 
#define USING_XLOG
#else
#endif

#define HEX_FMT "0x%08x"
#undef TAG

#ifdef USING_XLOG
#include <linux/xlog.h>

#define TAG     "Power/cpufreq"

#define cpufreq_err(fmt, args...)       \
    xlog_printk(ANDROID_LOG_ERROR, TAG, "[ERROR]"fmt, ##args)
#define cpufreq_warn(fmt, args...)      \
    xlog_printk(ANDROID_LOG_WARN, TAG, "[WARNING]"fmt, ##args)
#define cpufreq_info(fmt, args...)      \
    xlog_printk(ANDROID_LOG_INFO, TAG, fmt, ##args)
#define cpufreq_dbg(fmt, args...)       \
    xlog_printk(ANDROID_LOG_DEBUG, TAG, fmt, ##args)
#define cpufreq_ver(fmt, args...)       \
    do {                                \
        if (func_lv_mask)               \
            xlog_printk(ANDROID_LOG_VERBOSE, TAG, fmt, ##args);  \
    } while (0)

#else   

#define TAG     "[Power/cpufreq] "

#define cpufreq_err(fmt, args...)       \
    printk(KERN_ERR TAG KERN_CONT "[ERROR]"fmt, ##args)
#define cpufreq_warn(fmt, args...)      \
    printk(KERN_WARNING TAG KERN_CONT "[WARNING]"fmt, ##args)
#define cpufreq_info(fmt, args...)      \
    printk(KERN_NOTICE TAG KERN_CONT fmt, ##args)
#define cpufreq_dbg(fmt, args...)       \
    printk(KERN_DEBUG TAG KERN_CONT fmt, ##args)
#define cpufreq_ver(fmt, args...)       \
    do {                                \
        if (func_lv_mask)               \
            printk(KERN_DEBUG TAG KERN_CONT fmt, ##args);    \
    } while (0)

#endif  

#define FUNC_LV_MODULE         BIT(0)  
#define FUNC_LV_CPUFREQ        BIT(1)  
#define FUNC_LV_API                BIT(2)  
#define FUNC_LV_LOCAL            BIT(3)  
#define FUNC_LV_HELP              BIT(4)  

static unsigned int func_lv_mask = 0;
static unsigned int do_dvfs_stress_test = 0;

#ifdef CONFIG_CPU_DVFS_SHOWLOG
#define FUNC_ENTER(lv)          do { if ((lv) & func_lv_mask) cpufreq_dbg(">> %s()\n", __func__); } while (0)
#define FUNC_EXIT(lv)           do { if ((lv) & func_lv_mask) cpufreq_dbg("<< %s():%d\n", __func__, __LINE__); } while (0)
#else
#define FUNC_ENTER(lv)
#define FUNC_EXIT(lv)
#endif 

#define _BIT_(_bit_)                    (unsigned)(1 << (_bit_))
#define _BITS_(_bits_, _val_)           ((((unsigned) -1 >> (31 - ((1) ? _bits_))) & ~((1U << ((0) ? _bits_)) - 1)) & ((_val_)<<((0) ? _bits_)))
#define _BITMASK_(_bits_)               (((unsigned) -1 >> (31 - ((1) ? _bits_))) & ~((1U << ((0) ? _bits_)) - 1))
#define _GET_BITS_VAL_(_bits_, _val_)   (((_val_) & (_BITMASK_(_bits_))) >> ((0) ? _bits_))

#define cpufreq_read(addr)                  DRV_Reg32(addr)
#define cpufreq_write(addr, val)            mt_reg_sync_writel(val, addr)
#define cpufreq_write_mask(addr, mask, val) cpufreq_write(addr, (cpufreq_read(addr) & ~(_BITMASK_(mask))) | _BITS_(mask, val))








#if 0    
static DEFINE_SPINLOCK(cpufreq_lock);
#define cpufreq_lock(flags) spin_lock_irqsave(&cpufreq_lock, flags)
#define cpufreq_unlock(flags) spin_unlock_irqrestore(&cpufreq_lock, flags)
#else   
DEFINE_MUTEX(cpufreq_mutex);
bool is_in_cpufreq = 0;
#define cpufreq_lock(flags) \
    do { \
          \
        flags = (unsigned long)&flags; \
        mutex_lock(&cpufreq_mutex); \
        is_in_cpufreq = 1;\
        spm_mcdi_wakeup_all_cores();\
    } while (0)

#define cpufreq_unlock(flags) \
    do { \
          \
        flags = (unsigned long)&flags; \
        is_in_cpufreq = 0;\
        mutex_unlock(&cpufreq_mutex); \
    } while (0)
#endif
int max_power_budget = 9999;
#define CPUFREQ_EFUSE_INDEX     (3)
#define FUNC_CODE_EFUSE_INDEX	(28)

#define CPU_LEVEL_0             (0x0)
#define CPU_LEVEL_1             (0x1)
#define CPU_LEVEL_2             (0x2)

#define CPU_LV_TO_OPP_IDX(lv)   ((lv)) 
unsigned int AllowTurboMode = 0;

#ifdef __KERNEL__
static unsigned int _mt_cpufreq_get_cpu_level(void)
{
	unsigned int lv = 0;
	
#ifdef CONFIG_OF
	{
		struct device_node *node = of_find_node_by_type(NULL, "cpu");
		unsigned int cpu_speed = 0;
		unsigned int seg_code = get_devinfo_with_index(24);
		unsigned int seg2_code = get_devinfo_with_index(25);
		unsigned int seg2_code_result = 0;
		unsigned int turbo_code = get_devinfo_with_index(5);

		if (!of_property_read_u32(node, "clock-frequency", &cpu_speed))
			cpu_speed = cpu_speed / 1000 / 1000;    
		else {
			cpufreq_err("@%s: missing clock-frequency property, use default CPU level\n", __func__);
			return CPU_LEVEL_1;
		}

		

		switch (cpu_speed) {
		case 1846:
			lv = CPU_LEVEL_0;   
			break;

		case 2000:
			lv = CPU_LEVEL_1;   
			break;

		case 2200:
			lv = CPU_LEVEL_2;   
			break;

		default:
			lv = CPU_LEVEL_1;   
			break;
		}

		switch (_GET_BITS_VAL_(31 : 24, seg_code)) {
			case 0x0B:
			case 0x0C:
			case 0x0E:
			case 0x0F:
				lv = CPU_LEVEL_2;   
				break;
			case 0x10:
				lv = CPU_LEVEL_0;   
				break;
			case 0x0:
				seg2_code_result = _GET_BITS_VAL_(25 : 23, seg2_code);
				if (seg2_code_result == 0x01)
				lv = CPU_LEVEL_2;   
				break;
			case 0x06:
			case 0x01:
			case 0x03:
			default:
				break;
		}
#if 0 
		if ((turbo_code >> 29) & 0x1)
			AllowTurboMode = 1;
#endif
	}
#endif

	return lv;
}
#else
static unsigned int _mt_cpufreq_get_cpu_level(void)
{
	return CPU_LEVEL_1;
}
#endif

#ifdef CONFIG_CPU_DVFS_AEE_RR_REC
enum cpu_dvfs_state {
	CPU_DVFS_LITTLE_IS_DOING_DVFS = 0,
	CPU_DVFS_LITTLE_IS_TURBO,
	CPU_DVFS_BIG_IS_DOING_DVFS = 0,
	CPU_DVFS_BIG_IS_TURBO,
};

extern void aee_rr_rec_cpu_dvfs_vproc_big(u8 val);
extern void aee_rr_rec_cpu_dvfs_vproc_little(u8 val);
extern void aee_rr_rec_cpu_dvfs_oppidx(u8 val);
extern u8 aee_rr_curr_cpu_dvfs_oppidx(void);
extern void aee_rr_rec_cpu_dvfs_status(u8 val);
extern u8 aee_rr_curr_cpu_dvfs_status(void);
#ifdef CONFIG_HTC_DEBUG_FOOTPRINT
extern void aee_rr_rec_cpu_freq(u32 val);
extern void aee_rr_rec_dvfs_vproc_volt(u32 val);
extern void aee_rr_rec_dvfs_vsram_volt(u32 val);
#endif

static void _mt_cpufreq_aee_init(void)
{
	aee_rr_rec_cpu_dvfs_vproc_big(0xFF);
	aee_rr_rec_cpu_dvfs_vproc_little(0xFF);
	aee_rr_rec_cpu_dvfs_oppidx(0xFF);
	aee_rr_rec_cpu_dvfs_status(0xFF);
#ifdef CONFIG_HTC_DEBUG_FOOTPRINT
	aee_rr_rec_cpu_freq(0);
	aee_rr_rec_dvfs_vproc_volt(0);
	aee_rr_rec_dvfs_vsram_volt(0);
#endif
}
#endif

#define VOLT_TO_PMIC_VAL(volt)  (((volt) - 70000 + 625 - 1) / 625) 
#define PMIC_VAL_TO_VOLT(pmic)  (((pmic) * 625) + 70000) 

#define VOLT_TO_EXTBUCK_VAL(volt) (((((volt) - 300) + 9) / 10) & 0x7F) 
#define EXTBUCK_VAL_TO_VOLT(val)  (300 + ((val) & 0x7F) * 10)

 
#ifdef CONFIG_OF
extern void __iomem *pwrap_base;
#define PWRAP_BASE_ADDR     ((unsigned long)pwrap_base)
#else
#include "mach/mt_reg_base.h"
#define PWRAP_BASE_ADDR     PWRAP_BASE
#endif
#define PMIC_WRAP_DVFS_ADR0     (PWRAP_BASE_ADDR + 0x0E8)
#define PMIC_WRAP_DVFS_WDATA0   (PWRAP_BASE_ADDR + 0x0EC)
#define PMIC_WRAP_DVFS_ADR1     (PWRAP_BASE_ADDR + 0x0F0)
#define PMIC_WRAP_DVFS_WDATA1   (PWRAP_BASE_ADDR + 0x0F4)
#define PMIC_WRAP_DVFS_ADR2     (PWRAP_BASE_ADDR + 0x0F8)
#define PMIC_WRAP_DVFS_WDATA2   (PWRAP_BASE_ADDR + 0x0FC)
#define PMIC_WRAP_DVFS_ADR3     (PWRAP_BASE_ADDR + 0x100)
#define PMIC_WRAP_DVFS_WDATA3   (PWRAP_BASE_ADDR + 0x104)
#define PMIC_WRAP_DVFS_ADR4     (PWRAP_BASE_ADDR + 0x108)
#define PMIC_WRAP_DVFS_WDATA4   (PWRAP_BASE_ADDR + 0x10C)
#define PMIC_WRAP_DVFS_ADR5     (PWRAP_BASE_ADDR + 0x110)
#define PMIC_WRAP_DVFS_WDATA5   (PWRAP_BASE_ADDR + 0x114)
#define PMIC_WRAP_DVFS_ADR6     (PWRAP_BASE_ADDR + 0x118)
#define PMIC_WRAP_DVFS_WDATA6   (PWRAP_BASE_ADDR + 0x11C)
#define PMIC_WRAP_DVFS_ADR7     (PWRAP_BASE_ADDR + 0x120)
#define PMIC_WRAP_DVFS_WDATA7   (PWRAP_BASE_ADDR + 0x124)

 
#define PMIC_ADDR_VPROC_CA7_VOSEL_ON      0x847C  
#define PMIC_ADDR_VPROC_CA7_VOSEL_SLEEP   0x847E  
#define PMIC_ADDR_VPROC_CA7_EN            0x8476  

#define PMIC_ADDR_VSRAM_CA7_FAST_TRSN_EN	0x8CB4	
#define PMIC_ADDR_VSRAM_CA7_EN            0x8CBC  
#define PMIC_ADDR_VSRAM_VOSEL_ON          0x8492  

#define PMIC_ADDR_VSRAM_CA15L_VOSEL_ON    0x0264  
#define PMIC_ADDR_VSRAM_CA15L_VOSEL_SLEEP 0x0266  
#define PMIC_ADDR_VSRAM_CA15L_FAST_TRSN_EN	0x051C	
#define PMIC_ADDR_VSRAM_CA15L_EN          0x0524  

#define PMIC_ADDR_VGPU_VOSEL_ON           0x02B0  
#define PMIC_ADDR_VGPU_VOSEL_SLEEP        0x02B2  

#define PMIC_ADDR_VCORE_AO_VOSEL_ON       0x036C  
#define PMIC_ADDR_VCORE_AO_VOSEL_SLEEP    0x036E  

#define PMIC_ADDR_VCORE_PDN_VOSEL_ON      0x024E  
#define PMIC_ADDR_VCORE_PDN_VOSEL_SLEEP   0x0250  
#define PMIC_ADDR_VCORE_PDN_EN_CTRL       0x0244  

#define NR_PMIC_WRAP_CMD 8 

struct pmic_wrap_cmd {
	unsigned long cmd_addr;
	unsigned long cmd_wdata;
};

struct pmic_wrap_setting {
	enum pmic_wrap_phase_id phase;
	struct pmic_wrap_cmd addr[NR_PMIC_WRAP_CMD];
	struct {
		struct {
			unsigned long cmd_addr;
			unsigned long cmd_wdata;
		} _[NR_PMIC_WRAP_CMD];
		const int nr_idx;
	} set[NR_PMIC_WRAP_PHASE];
};

static struct pmic_wrap_setting pw = {
	.phase = NR_PMIC_WRAP_PHASE, 
#if 0
	.addr = {
		{ PMIC_WRAP_DVFS_ADR0, PMIC_WRAP_DVFS_WDATA0, },
		{ PMIC_WRAP_DVFS_ADR1, PMIC_WRAP_DVFS_WDATA1, },
		{ PMIC_WRAP_DVFS_ADR2, PMIC_WRAP_DVFS_WDATA2, },
		{ PMIC_WRAP_DVFS_ADR3, PMIC_WRAP_DVFS_WDATA3, },
		{ PMIC_WRAP_DVFS_ADR4, PMIC_WRAP_DVFS_WDATA4, },
		{ PMIC_WRAP_DVFS_ADR5, PMIC_WRAP_DVFS_WDATA5, },
		{ PMIC_WRAP_DVFS_ADR6, PMIC_WRAP_DVFS_WDATA6, },
		{ PMIC_WRAP_DVFS_ADR7, PMIC_WRAP_DVFS_WDATA7, },
	},
#else
	.addr = { {0, 0} },
#endif
	.set[PMIC_WRAP_PHASE_NORMAL] = {
		._[IDX_NM_VSRAM_CA7]          = { PMIC_ADDR_VSRAM_VOSEL_ON,     VOLT_TO_PMIC_VAL(DEFAULT_VOLT_VSRAM),            },
		._[IDX_NM_VPROC_CA7]            = { PMIC_ADDR_VPROC_CA7_VOSEL_ON,       VOLT_TO_PMIC_VAL(DEFAULT_VOLT_VLTE),         },
		._[IDX_NM_VGPU]           = { PMIC_ADDR_VGPU_VOSEL_ON,  VOLT_TO_PMIC_VAL(DEFAULT_VOLT_VGPU),  },
		._[IDX_NM_VCORE_PDN]            = { PMIC_ADDR_VCORE_PDN_VOSEL_ON ,      VOLT_TO_PMIC_VAL(DEFAULT_VOLT_SOC), },
		.nr_idx = NR_IDX_NM,
	},

	.set[PMIC_WRAP_PHASE_SUSPEND] = {
		._[IDX_SP_VSRAM_CA7_PWR_ON]     = { PMIC_ADDR_VSRAM_CA7_EN,             _BITS_(11 : 10, 1) | _BIT_(8), }, 
		._[IDX_SP_VSRAM_CA7_SHUTDOWN]   = { PMIC_ADDR_VSRAM_CA7_EN,             _BITS_(11 : 10, 0) | _BIT_(8), }, 
		.nr_idx = NR_IDX_SP,
	},

	.set[PMIC_WRAP_PHASE_DEEPIDLE] = {
		._[IDX_DI_VSRAM_CA7_NORMAL]     = { PMIC_ADDR_VSRAM_VOSEL_ON,       VOLT_TO_PMIC_VAL(100000), },
		._[IDX_DI_VSRAM_CA7_SLEEP]      = { PMIC_ADDR_VSRAM_VOSEL_ON,       VOLT_TO_PMIC_VAL(93000),  },
		._[IDX_DI_VSRAM_CA7_FAST_TRSN_EN]	= { PMIC_ADDR_VSRAM_CA7_FAST_TRSN_EN,	_BITS_(3 : 3, 0),	},
		._[IDX_DI_VSRAM_CA7_FAST_TRSN_DIS]	= { PMIC_ADDR_VSRAM_CA7_FAST_TRSN_EN,	_BITS_(3 : 3, 1),	},
		._[IDX_DI_VPROC_CA7_NORMAL]      = { PMIC_ADDR_VPROC_CA7_VOSEL_ON,        VOLT_TO_PMIC_VAL(112500), },
		._[IDX_DI_VPROC_CA7_SLEEP]       = { PMIC_ADDR_VPROC_CA7_VOSEL_ON,        VOLT_TO_PMIC_VAL(90000),  },
		._[IDX_DI_VCORE_PDN_NORMAL]     = { PMIC_ADDR_VCORE_PDN_VOSEL_ON,       VOLT_TO_PMIC_VAL(112500), },
		._[IDX_DI_VCORE_PDN_SLEEP]      = { PMIC_ADDR_VCORE_PDN_VOSEL_ON,       VOLT_TO_PMIC_VAL(90000),  },
		.nr_idx = NR_IDX_DI,
	},

	.set[PMIC_WRAP_PHASE_SODI] = {
		._[IDX_SO_VSRAM_CA7_NORMAL]		= { PMIC_ADDR_VSRAM_VOSEL_ON,	VOLT_TO_PMIC_VAL(100000),	},
		._[IDX_SO_VSRAM_CA7_SLEEP]		= { PMIC_ADDR_VSRAM_VOSEL_ON,	VOLT_TO_PMIC_VAL(93000),	},
		._[IDX_SO_VSRAM_CA7_FAST_TRSN_EN]		= { PMIC_ADDR_VSRAM_CA7_FAST_TRSN_EN,	_BITS_(3 : 3, 0),	},
		._[IDX_SO_VSRAM_CA7_FAST_TRSN_DIS]		= { PMIC_ADDR_VSRAM_CA7_FAST_TRSN_EN,	_BITS_(3 : 3, 1),	},
		._[IDX_SO_VPROC_CA7_NORMAL]	= { PMIC_ADDR_VPROC_CA7_VOSEL_ON,	VOLT_TO_PMIC_VAL(112500),	},
		._[IDX_SO_VPROC_CA7_SLEEP]	= { PMIC_ADDR_VPROC_CA7_VOSEL_ON,	VOLT_TO_PMIC_VAL(90000),	},
		._[IDX_SO_VCORE_PDN_NORMAL]	= { PMIC_ADDR_VCORE_PDN_VOSEL_ON,	VOLT_TO_PMIC_VAL(112500),	},
		._[IDX_SO_VCORE_PDN_SLEEP]	= { PMIC_ADDR_VCORE_PDN_VOSEL_ON,	VOLT_TO_PMIC_VAL(90000), 	},
		.nr_idx = NR_IDX_SO,
	},
};

#if 1   
static DEFINE_SPINLOCK(pmic_wrap_lock);
#define pmic_wrap_lock(flags) spin_lock_irqsave(&pmic_wrap_lock, flags)
#define pmic_wrap_unlock(flags) spin_unlock_irqrestore(&pmic_wrap_lock, flags)
#else   
static DEFINE_MUTEX(pmic_wrap_mutex);

#define pmic_wrap_lock(flags) \
    do { \
          \
        flags = (unsigned long)&flags; \
        mutex_lock(&pmic_wrap_mutex); \
    } while (0)

#define pmic_wrap_unlock(flags) \
    do { \
          \
        flags = (unsigned long)&flags; \
        mutex_unlock(&pmic_wrap_mutex); \
    } while (0)
#endif

static int _spm_dvfs_ctrl_volt(u32 value)
{
#define MAX_RETRY_COUNT (100)

	u32 ap_dvfs_con;
	int retry = 0;

	FUNC_ENTER(FUNC_LV_HELP);

	spm_write(SPM_POWERON_CONFIG_SET, (SPM_PROJECT_CODE << 16) | (1U << 0)); 

	ap_dvfs_con = spm_read(SPM_AP_DVFS_CON_SET);
	spm_write(SPM_AP_DVFS_CON_SET, (ap_dvfs_con & ~(0x7)) | value);
	udelay(5);

	while ((spm_read(SPM_AP_DVFS_CON_SET) & (0x1 << 31)) == 0) {
		if (retry >= MAX_RETRY_COUNT) {
			cpufreq_err("FAIL: no response from PMIC wrapper\n");
			return -1;
		}

		retry++;
		

		udelay(5);
	}

	FUNC_EXIT(FUNC_LV_HELP);

	return 0;
}

void _mt_cpufreq_pmic_table_init(void)
{
	struct pmic_wrap_cmd pwrap_cmd_default[NR_PMIC_WRAP_CMD] = {
		{ PMIC_WRAP_DVFS_ADR0, PMIC_WRAP_DVFS_WDATA0, },
		{ PMIC_WRAP_DVFS_ADR1, PMIC_WRAP_DVFS_WDATA1, },
		{ PMIC_WRAP_DVFS_ADR2, PMIC_WRAP_DVFS_WDATA2, },
		{ PMIC_WRAP_DVFS_ADR3, PMIC_WRAP_DVFS_WDATA3, },
		{ PMIC_WRAP_DVFS_ADR4, PMIC_WRAP_DVFS_WDATA4, },
		{ PMIC_WRAP_DVFS_ADR5, PMIC_WRAP_DVFS_WDATA5, },
		{ PMIC_WRAP_DVFS_ADR6, PMIC_WRAP_DVFS_WDATA6, },
		{ PMIC_WRAP_DVFS_ADR7, PMIC_WRAP_DVFS_WDATA7, },
	};

	FUNC_ENTER(FUNC_LV_HELP);

	memcpy(pw.addr, pwrap_cmd_default, sizeof(pwrap_cmd_default));

	FUNC_EXIT(FUNC_LV_HELP);
}

void mt_cpufreq_set_pmic_phase(enum pmic_wrap_phase_id phase)
{
	int i;
	unsigned long flags;

	FUNC_ENTER(FUNC_LV_API);

	BUG_ON(phase >= NR_PMIC_WRAP_PHASE);

#if 0   

	if (pw.phase == phase)
		return;

#endif

	if (pw.addr[0].cmd_addr == 0) {
		cpufreq_warn("pmic table not initialized\n");
		_mt_cpufreq_pmic_table_init();
	}

	pmic_wrap_lock(flags);

	pw.phase = phase;

	for (i = 0; i < pw.set[phase].nr_idx; i++) {
		cpufreq_write(pw.addr[i].cmd_addr, pw.set[phase]._[i].cmd_addr);
		cpufreq_write(pw.addr[i].cmd_wdata, pw.set[phase]._[i].cmd_wdata);
	}

	pmic_wrap_unlock(flags);

	FUNC_EXIT(FUNC_LV_API);
}
EXPORT_SYMBOL(mt_cpufreq_set_pmic_phase);

void mt_cpufreq_set_pmic_cmd(enum pmic_wrap_phase_id phase, int idx, unsigned int cmd_wdata) 
{
	unsigned long flags;

	FUNC_ENTER(FUNC_LV_API);

	BUG_ON(phase >= NR_PMIC_WRAP_PHASE);
	BUG_ON(idx >= pw.set[phase].nr_idx);

	

	pmic_wrap_lock(flags);

	pw.set[phase]._[idx].cmd_wdata = cmd_wdata;

	if (pw.phase == phase)
		cpufreq_write(pw.addr[idx].cmd_wdata, cmd_wdata);

	pmic_wrap_unlock(flags);

	FUNC_EXIT(FUNC_LV_API);
}
EXPORT_SYMBOL(mt_cpufreq_set_pmic_cmd);

void mt_cpufreq_apply_pmic_cmd(int idx) 
{
	unsigned long flags;

	FUNC_ENTER(FUNC_LV_API);

	BUG_ON(idx >= pw.set[pw.phase].nr_idx);

	

	pmic_wrap_lock(flags);

	_spm_dvfs_ctrl_volt(idx);

	pmic_wrap_unlock(flags);

	FUNC_EXIT(FUNC_LV_API);
}
EXPORT_SYMBOL(mt_cpufreq_apply_pmic_cmd);

static cpuVoltsampler_func g_pCpuVoltSampler = NULL;

void mt_cpufreq_setvolt_registerCB(cpuVoltsampler_func pCB)
{
	g_pCpuVoltSampler = pCB;
}
EXPORT_SYMBOL(mt_cpufreq_setvolt_registerCB);

unsigned int mt_get_cur_volt_lte(void)
{
	unsigned int rdata;

	FUNC_ENTER(FUNC_LV_LOCAL);

	pwrap_read(PMIC_ADDR_VPROC_CA7_VOSEL_ON, &rdata);

	rdata = PMIC_VAL_TO_VOLT(rdata);

	FUNC_EXIT(FUNC_LV_LOCAL);

	return rdata; 
}
EXPORT_SYMBOL(mt_get_cur_volt_lte);

unsigned int mt_set_cur_volt_lte(unsigned int pmic_val)
{
	mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_DEEPIDLE, IDX_DI_VPROC_CA7_NORMAL, pmic_val);
	mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_SODI, IDX_SO_VPROC_CA7_NORMAL, pmic_val);

	mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_NORMAL, IDX_NM_VPROC_CA7, pmic_val);
	mt_cpufreq_apply_pmic_cmd(IDX_NM_VPROC_CA7);

	return 0;
}
EXPORT_SYMBOL(mt_set_cur_volt_lte);

unsigned int mt_set_cur_volt_vcore_pdn(unsigned int pmic_val)
{
	mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_DEEPIDLE, IDX_DI_VCORE_PDN_NORMAL, pmic_val);
	mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_SODI, IDX_SO_VCORE_PDN_NORMAL, pmic_val);

	mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_NORMAL, IDX_NM_VCORE_PDN, pmic_val);
	mt_cpufreq_apply_pmic_cmd(IDX_NM_VCORE_PDN);

	return 0;
}
EXPORT_SYMBOL(mt_set_cur_volt_vcore_pdn);

unsigned int mt_get_cur_volt_vcore_pdn(void)
{
	unsigned int rdata;

	FUNC_ENTER(FUNC_LV_LOCAL);

	pwrap_read(PMIC_ADDR_VCORE_PDN_VOSEL_ON, &rdata);

	rdata = PMIC_VAL_TO_VOLT(rdata);

	FUNC_EXIT(FUNC_LV_LOCAL);

	return rdata; 
}
EXPORT_SYMBOL(mt_get_cur_volt_vcore_pdn);

void mt_vcore_dvfs_disable_by_sdio(unsigned int type, bool disabled)
{
	
}

void mt_vcore_dvfs_volt_set_by_sdio(unsigned int volt) 
{
	unsigned int cur_pmic_val_vcore_pdn;
	unsigned int target_pmic_val_vcore_pdn;
	int step;

	FUNC_ENTER(FUNC_LV_LOCAL);

	pwrap_read(PMIC_ADDR_VCORE_PDN_VOSEL_ON, &cur_pmic_val_vcore_pdn);
	target_pmic_val_vcore_pdn = VOLT_TO_PMIC_VAL(volt / 10); 

	step = (target_pmic_val_vcore_pdn > cur_pmic_val_vcore_pdn) ? 1 : -1;

	while (target_pmic_val_vcore_pdn != cur_pmic_val_vcore_pdn) {
		cur_pmic_val_vcore_pdn += step;
		mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_NORMAL, IDX_NM_VCORE_PDN, cur_pmic_val_vcore_pdn);
		mt_cpufreq_apply_pmic_cmd(IDX_NM_VCORE_PDN);
		udelay(4);
	}

	FUNC_EXIT(FUNC_LV_LOCAL);
}

unsigned int mt_vcore_dvfs_volt_get_by_sdio(void) 
{
	return mt_get_cur_volt_vcore_pdn() * 10;
}

#define OP(khz, volt) {            \
        .cpufreq_khz = khz,             \
                       .cpufreq_volt = volt,           \
                                       .cpufreq_volt_org = volt,       \
    }

#define for_each_cpu_dvfs(i, p)        for (i = 0, p = cpu_dvfs; i < NR_MT_CPU_DVFS; i++, p = &cpu_dvfs[i])
#define cpu_dvfs_is(p, id)                 (p == &cpu_dvfs[id])
#define cpu_dvfs_is_availiable(p)      (p->opp_tbl)
#define cpu_dvfs_get_name(p)         (p->name)

#define cpu_dvfs_get_cur_freq(p)                (p->opp_tbl[p->idx_opp_tbl].cpufreq_khz)
#define cpu_dvfs_get_freq_by_idx(p, idx)        (p->opp_tbl[idx].cpufreq_khz)
#define cpu_dvfs_get_max_freq(p)                (p->opp_tbl[0].cpufreq_khz)
#define cpu_dvfs_get_normal_max_freq(p)         (p->opp_tbl[p->idx_normal_max_opp].cpufreq_khz)
#define cpu_dvfs_get_min_freq(p)                (p->opp_tbl[p->nr_opp_tbl - 1].cpufreq_khz)

#define cpu_dvfs_get_cur_volt(p)                (p->opp_tbl[p->idx_opp_tbl].cpufreq_volt)
#define cpu_dvfs_get_volt_by_idx(p, idx)        (p->opp_tbl[idx].cpufreq_volt)

#define cpu_dvfs_is_extbuck_valid()     is_ext_buck_sw_ready()


struct mt_cpu_freq_info {
	const unsigned int cpufreq_khz;
	unsigned int cpufreq_volt;  
	unsigned int cpufreq_volt_org;    
};

struct mt_cpu_power_info {
	unsigned int cpufreq_khz;
	unsigned int cpufreq_ncpu;
	unsigned int cpufreq_power;
};

struct mt_cpu_dvfs {
	const char *name;
	unsigned int cpu_id;                    
	unsigned int cpu_level;
	struct mt_cpu_dvfs_ops *ops;

	
	struct mt_cpu_freq_info *opp_tbl;       
	int nr_opp_tbl;                         
	int idx_opp_tbl;                        
	int idx_normal_max_opp;                 
	int idx_opp_tbl_for_late_resume;	

	struct cpufreq_frequency_table *freq_tbl_for_cpufreq; 

	
	struct mt_cpu_power_info *power_tbl;
	unsigned int nr_power_tbl;

	
	int dvfs_disable_count;
	bool dvfs_disable_by_ptpod;
	bool dvfs_disable_by_suspend;
	bool dvfs_disable_by_early_suspend;
	bool dvfs_disable_by_procfs;

	
	unsigned int limited_max_ncpu;
	unsigned int limited_max_freq;
	unsigned int idx_opp_tbl_for_thermal_thro;
	unsigned int thermal_protect_limited_power;

	
	unsigned int limited_freq_by_hevc;

	
	unsigned int limited_max_freq_by_user;

	
	int ramp_down_count;
	int ramp_down_count_const;

	
	bool downgrade_freq_for_ptpod;

	int over_max_cpu;
	int ptpod_temperature_limit_1;
	int ptpod_temperature_limit_2;
	int ptpod_temperature_time_1;
	int ptpod_temperature_time_2;

	int pre_online_cpu;
	unsigned int pre_freq;
	unsigned int downgrade_freq;

	unsigned int downgrade_freq_counter;
	unsigned int downgrade_freq_counter_return;

	unsigned int downgrade_freq_counter_limit;
	unsigned int downgrade_freq_counter_return_limit;

	
	unsigned int turbo_mode;

	
#ifdef CONFIG_CPU_DVFS_POWER_THROTTLING
	int idx_opp_tbl_for_pwr_thro;           
	int idx_pwr_thro_max_opp;               
	unsigned int pwr_thro_mode;
#endif

};

#define MT6795_CPU_NUM	8
unsigned int cpufreq_thermal_floor_limit_table[MT6795_CPU_NUM]={
	UINT_MAX, 1183000, 1183000, 1183000, 1183000, 1183000, 1183000, 1183000};



struct mt_cpu_dvfs_ops {
	
	void (*protect)(struct mt_cpu_dvfs *p, unsigned int limited_power);       
	unsigned int (*get_temp)(struct mt_cpu_dvfs *p);                          
	int (*setup_power_table)(struct mt_cpu_dvfs *p);

	
	unsigned int (*get_cur_phy_freq)(struct mt_cpu_dvfs *p);                 
	void (*set_cur_freq)(struct mt_cpu_dvfs *p, unsigned int cur_khz, unsigned int target_khz); 

	
	unsigned int (*get_cur_volt)(struct mt_cpu_dvfs *p);             
	int (*set_cur_volt)(struct mt_cpu_dvfs *p, unsigned int volt);   
};


static int setup_power_table(struct mt_cpu_dvfs *p);

static unsigned int get_cur_phy_freq(struct mt_cpu_dvfs *p);
static void set_cur_freq(struct mt_cpu_dvfs *p, unsigned int cur_khz, unsigned int target_khz);

static unsigned int get_cur_volt_extbuck(struct mt_cpu_dvfs *p);
static int set_cur_volt_extbuck(struct mt_cpu_dvfs *p, unsigned int volt); 

static unsigned int max_cpu_num = 8; 

static struct mt_cpu_dvfs_ops dvfs_ops_extbuck = {
	.setup_power_table = setup_power_table,

	.get_cur_phy_freq = get_cur_phy_freq,
	.set_cur_freq = set_cur_freq,

	.get_cur_volt = get_cur_volt_extbuck,
	.set_cur_volt = set_cur_volt_extbuck,
};


static struct mt_cpu_dvfs cpu_dvfs[] = {
	[MT_CPU_DVFS_LITTLE]    = {
		.name                           = __stringify(MT_CPU_DVFS_LITTLE),
		.cpu_id                         = MT_CPU_DVFS_LITTLE, 
		.cpu_level                    = CPU_LEVEL_1,  
		.ops                            = &dvfs_ops_extbuck,

		
		.over_max_cpu                   = 8, 
		.ptpod_temperature_limit_1      = 110000,
		.ptpod_temperature_limit_2      = 120000,
		.ptpod_temperature_time_1       = 1,
		.ptpod_temperature_time_2       = 4,
		.pre_online_cpu                 = 0,
		.pre_freq                       = 0,
		.downgrade_freq                 = 0,
		.downgrade_freq_counter         = 0,
		.downgrade_freq_counter_return  = 0,
		.downgrade_freq_counter_limit   = 0,
		.downgrade_freq_counter_return_limit = 0,

		.ramp_down_count_const		= RAMP_DOWN_TIMES,

		.turbo_mode			= 0,
#ifdef CONFIG_CPU_DVFS_POWER_THROTTLING
		.idx_opp_tbl_for_pwr_thro	= -1,
		.idx_pwr_thro_max_opp = 0,
#endif
	},
};


static struct mt_cpu_dvfs *id_to_cpu_dvfs(enum mt_cpu_dvfs_id id)
{
	return (id < NR_MT_CPU_DVFS) ? &cpu_dvfs[id] : NULL;
}


#define NR_MAX_OPP_TBL  8
#define NR_MAX_CPU      8

#if 0
static struct mt_cpu_freq_info opp_tbl_e1_0[] = {
	OP(CPU_DVFS_FREQ0,  112500),
	OP(CPU_DVFS_FREQ1,  110000),
	OP(CPU_DVFS_FREQ2,  106875),
	OP(CPU_DVFS_FREQ3,  104375),
	OP(CPU_DVFS_FREQ4,  101875),
	OP(CPU_DVFS_FREQ5,  99375),
	OP(CPU_DVFS_FREQ6,  91250),
	OP(CPU_DVFS_FREQ7,  82500),
};
#else
static struct mt_cpu_freq_info opp_tbl_e1_0[] = {
	OP(CPU_DVFS_FREQ0,  115000),
	OP(CPU_DVFS_FREQ1,  111875),
	OP(CPU_DVFS_FREQ2,  108750),
	OP(CPU_DVFS_FREQ3,  106250),
	OP(CPU_DVFS_FREQ4,  103125),
	OP(CPU_DVFS_FREQ5,  100000),
	OP(CPU_DVFS_FREQ6,  91875),
	OP(CPU_DVFS_FREQ7,  90000),
};
#endif

#if 0
static struct mt_cpu_freq_info opp_tbl_e1_1[] = {
	OP(CPU_DVFS_FREQ0_1,  115000),
	OP(CPU_DVFS_FREQ1_1,  111875),
	OP(CPU_DVFS_FREQ2_1,  108125),
	OP(CPU_DVFS_FREQ3_1,  105000),
	OP(CPU_DVFS_FREQ4_1,  101875),
	OP(CPU_DVFS_FREQ5_1,  98750),
	OP(CPU_DVFS_FREQ6_1,  90625),
	OP(CPU_DVFS_FREQ7_1,  82500),
};
#else
static struct mt_cpu_freq_info opp_tbl_e1_1[] = {
	OP(CPU_DVFS_FREQ0_1,  115000),
	OP(CPU_DVFS_FREQ1_1,  111875),
	OP(CPU_DVFS_FREQ2_1,  108125),
	OP(CPU_DVFS_FREQ3_1,  105000),
	OP(CPU_DVFS_FREQ4_1,  101875),
	OP(CPU_DVFS_FREQ5_1,  98750),
	OP(CPU_DVFS_FREQ6_1,  90625),
	OP(CPU_DVFS_FREQ7_1,  90000),
};
#endif

#if 0
static struct mt_cpu_freq_info opp_tbl_e1_2[] = {
	OP(CPU_DVFS_FREQ0_2, 115000),
	OP(CPU_DVFS_FREQ1_2, 110000),
	OP(CPU_DVFS_FREQ2_2, 106250),
	OP(CPU_DVFS_FREQ3_2, 102500),
	OP(CPU_DVFS_FREQ4_2, 99375),
	OP(CPU_DVFS_FREQ5_2, 96875),
	OP(CPU_DVFS_FREQ6_2, 89375),
	OP(CPU_DVFS_FREQ7_2, 81875),
};
#else
static struct mt_cpu_freq_info opp_tbl_e1_2[] = {
	OP(CPU_DVFS_FREQ0_2, 115000),
	OP(CPU_DVFS_FREQ1_2, 110000),
	OP(CPU_DVFS_FREQ2_2, 106250),
	OP(CPU_DVFS_FREQ3_2, 102500),
	OP(CPU_DVFS_FREQ4_2, 99375),
	OP(CPU_DVFS_FREQ5_2, 96875),
	OP(CPU_DVFS_FREQ6_2, 90000),
	OP(CPU_DVFS_FREQ7_2, 90000),
};
#endif

struct opp_tbl_info {
	struct mt_cpu_freq_info *const opp_tbl;
	const int size;
};

#define ARRAY_AND_SIZE(x) (x), ARRAY_SIZE(x)

static struct opp_tbl_info opp_tbls[] = {
	[CPU_LV_TO_OPP_IDX(CPU_LEVEL_0)] = { ARRAY_AND_SIZE(opp_tbl_e1_0), },
	[CPU_LV_TO_OPP_IDX(CPU_LEVEL_1)] = { ARRAY_AND_SIZE(opp_tbl_e1_1), },
	[CPU_LV_TO_OPP_IDX(CPU_LEVEL_2)] = { ARRAY_AND_SIZE(opp_tbl_e1_2), },
};

#define PLL_FREQ_STEP		(13000)		

#define PLL_DIV1_FREQ		(1612000)	
#define PLL_FREQ5_FREQ		(1183000)	
#define PLL_DIV2_FREQ		(806000)	

#define DDS_DIV1_FREQ		(0x000F8000)	
#define DDS_FREQ5_FREQ		(0x000B6000)	
#define DDS_DIV2_FREQ		(0x010F8000)	

#define TURBO_MODE_BOUNDARY_CPU_NUM	2

enum turbo_mode {
	TURBO_MODE_2,
	TURBO_MODE_1,
	TURBO_MODE_NONE,

	NR_TURBO_MODE,
};

struct turbo_mode_cfg {
	int temp;       
	int freq_delta; 
	int volt_delta; 
} turbo_mode_cfg[] = {
	[TURBO_MODE_2] = {
		.temp = 65000,
		.freq_delta = 10,
		.volt_delta = 2500,
	},
	[TURBO_MODE_1] = {
		.temp = 85000,
		.freq_delta = 5,
		.volt_delta = 1250,
	},
	[TURBO_MODE_NONE] = {
		.temp = 125000,
		.freq_delta = 0,
		.volt_delta = 0,
	},
};

#define TURBO_MODE_FREQ(mode, freq) (((freq * (100 + turbo_mode_cfg[mode].freq_delta)) / PLL_FREQ_STEP) / 100 * PLL_FREQ_STEP)
#define TURBO_MODE_VOLT(mode, volt) (volt + turbo_mode_cfg[mode].volt_delta)
int _search_available_freq_idx(struct mt_cpu_dvfs *p, unsigned int target_khz, unsigned int relation);

static unsigned int num_online_cpus_delta = 0;

static enum turbo_mode get_turbo_mode(struct mt_cpu_dvfs *p, unsigned int target_khz)
{
	enum turbo_mode mode = TURBO_MODE_NONE;
	int temp = tscpu_get_temp_by_bank(THERMAL_BANK0);    
	unsigned int online_cpus = num_online_cpus() + num_online_cpus_delta;
	int i;

	if (p->turbo_mode
	    && target_khz == cpu_dvfs_get_freq_by_idx(p, 0)
	    && online_cpus <= TURBO_MODE_BOUNDARY_CPU_NUM
	   ) {
		for (i = 0; i < NR_TURBO_MODE; i++) {
			if (temp < turbo_mode_cfg[i].temp) {
				mode = i;
				break;
			}
		}
	}

	if ((_mt_cpufreq_get_cpu_level() == CPU_LEVEL_2) && (mode == TURBO_MODE_2))
		mode = TURBO_MODE_1;

	
	if (TURBO_MODE_VOLT(mode, cpu_dvfs_get_volt_by_idx(p, 0)) >= MAX_VPROC_VOLT)
		mode = TURBO_MODE_NONE;

#ifdef CONFIG_CPU_DVFS_AEE_RR_REC

	if (TURBO_MODE_NONE != mode)
		aee_rr_rec_cpu_dvfs_status(aee_rr_curr_cpu_dvfs_status() | (1 << CPU_DVFS_LITTLE_IS_TURBO));
	else
		aee_rr_rec_cpu_dvfs_status(aee_rr_curr_cpu_dvfs_status() & ~(1 << CPU_DVFS_LITTLE_IS_TURBO));

#endif

	cpufreq_ver("%s(), mode = %d, temp = %d, target_khz = %d (%d), num_online_cpus = %d\n",
		    __func__,
		    mode,
		    temp,
		    target_khz,
		    TURBO_MODE_FREQ(mode, target_khz),
		    online_cpus
		   ); 

	return mode;
}

static int _set_cur_volt_locked(struct mt_cpu_dvfs *p, unsigned int volt)  
{
	int ret = -1;

	FUNC_ENTER(FUNC_LV_HELP);

	BUG_ON(NULL == p);

	if (!cpu_dvfs_is_availiable(p)) {
		FUNC_EXIT(FUNC_LV_HELP);
		return 0;
	}

	
	ret = p->ops->set_cur_volt(p, volt);

	FUNC_EXIT(FUNC_LV_HELP);

	return ret;
}

static int _restore_default_volt(struct mt_cpu_dvfs *p)
{
	unsigned long flags;
	int i;
	int ret = -1;

	FUNC_ENTER(FUNC_LV_HELP);

	BUG_ON(NULL == p);

	if (!cpu_dvfs_is_availiable(p)) {
		FUNC_EXIT(FUNC_LV_HELP);
		return 0;
	}

	cpufreq_lock(flags);

	
	for (i = 0; i < p->nr_opp_tbl; i++)
		p->opp_tbl[i].cpufreq_volt = p->opp_tbl[i].cpufreq_volt_org;

	
	ret = _set_cur_volt_locked(p,
				   TURBO_MODE_VOLT(get_turbo_mode(p, cpu_dvfs_get_cur_freq(p)),
						   cpu_dvfs_get_cur_volt(p)
						  )
				  );

	cpufreq_unlock(flags);

	FUNC_EXIT(FUNC_LV_HELP);

	return ret;
}

unsigned int mt_cpufreq_get_freq_by_idx(enum mt_cpu_dvfs_id id, int idx)
{
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(id);

	FUNC_ENTER(FUNC_LV_API);

	BUG_ON(NULL == p);

	if (!cpu_dvfs_is_availiable(p)) {
		FUNC_EXIT(FUNC_LV_API);
		return 0;
	}

	BUG_ON(idx >= p->nr_opp_tbl);

	FUNC_EXIT(FUNC_LV_API);

	return cpu_dvfs_get_freq_by_idx(p, idx);
}
EXPORT_SYMBOL(mt_cpufreq_get_freq_by_idx);

int mt_cpufreq_update_volt(enum mt_cpu_dvfs_id id, unsigned int *volt_tbl, int nr_volt_tbl)
{
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(id);
	unsigned long flags;
	int i;
	int ret = -1;
	unsigned int freq;
	int idx;

	FUNC_ENTER(FUNC_LV_API);

	BUG_ON(NULL == p);

	if (!cpu_dvfs_is_availiable(p)) {
		FUNC_EXIT(FUNC_LV_API);
		return 0;
	}

	BUG_ON(nr_volt_tbl > p->nr_opp_tbl);

	cpufreq_lock(flags);

	
	for (i = 0; i < nr_volt_tbl; i++)
		p->opp_tbl[i].cpufreq_volt = PMIC_VAL_TO_VOLT(volt_tbl[i]);

	
	freq = p->ops->get_cur_phy_freq(p);

	if (freq > p->opp_tbl[0].cpufreq_khz)
		freq = p->opp_tbl[0].cpufreq_khz;

	idx = _search_available_freq_idx(p, freq, CPUFREQ_RELATION_L);

	
	ret = _set_cur_volt_locked(p,
				   TURBO_MODE_VOLT(get_turbo_mode(p, freq),
						    p->opp_tbl[idx].cpufreq_volt
						  )
				  );

	cpufreq_unlock(flags);

	FUNC_EXIT(FUNC_LV_API);

	return ret;
}
EXPORT_SYMBOL(mt_cpufreq_update_volt);

void mt_cpufreq_restore_default_volt(enum mt_cpu_dvfs_id id)
{
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(id);

	FUNC_ENTER(FUNC_LV_API);

	BUG_ON(NULL == p);

	if (!cpu_dvfs_is_availiable(p)) {
		FUNC_EXIT(FUNC_LV_API);
		return;
	}

	
	if (p->turbo_mode) {
		cpufreq_info("@%s: Turbo mode disabled!\n", __func__);
		p->turbo_mode = 0;
	}

	_restore_default_volt(p);

	FUNC_EXIT(FUNC_LV_API);
}
EXPORT_SYMBOL(mt_cpufreq_restore_default_volt);

static unsigned int _cpu_freq_calc(unsigned int con1, unsigned int ckdiv1)
{
	unsigned int freq = 0;

	con1 &= _BITMASK_(26 : 0);

	if (con1 >= DDS_DIV2_FREQ) {
		freq = DDS_DIV2_FREQ;
		freq = PLL_DIV2_FREQ + (((con1 - freq) / 0x2000) * PLL_FREQ_STEP / 2);
	} else if (con1 >= DDS_FREQ5_FREQ) {
		freq = DDS_FREQ5_FREQ;
		freq = PLL_FREQ5_FREQ + (((con1 - freq) / 0x2000) * PLL_FREQ_STEP);
	} else if (con1 >= DDS_DIV1_FREQ) {
		freq = DDS_DIV1_FREQ;
		freq = PLL_DIV1_FREQ + (((con1 - freq) / 0x2000) * PLL_FREQ_STEP);
	} else
		BUG();

	FUNC_ENTER(FUNC_LV_HELP);

	switch (ckdiv1) {
	case 10:
		freq = freq * 2 / 4;
		break;

	case 8:
	case 16:
	case 24:
	default:
		break;
	}

	FUNC_EXIT(FUNC_LV_HELP);

	return freq; 
}

static unsigned int get_cur_phy_freq(struct mt_cpu_dvfs *p)
{
	unsigned int con1;
	unsigned int ckdiv1;
	unsigned int cur_khz;

	FUNC_ENTER(FUNC_LV_LOCAL);

	BUG_ON(NULL == p);

	con1 = cpufreq_read(4 + ARMCA15PLL_CON0);

	ckdiv1 = cpufreq_read(TOP_CKDIV1);
	ckdiv1 = _GET_BITS_VAL_(4 : 0, ckdiv1);

	cur_khz = _cpu_freq_calc(con1, ckdiv1);

	cpufreq_ver("@%s: cur_khz = %d, con1 = 0x%x, ckdiv1_val = 0x%x\n", __func__, cur_khz, con1, ckdiv1);

	FUNC_EXIT(FUNC_LV_LOCAL);

	return cur_khz;
}

static unsigned int _mt_cpufreq_get_cur_phy_freq(enum mt_cpu_dvfs_id id)
{
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(id);

	FUNC_ENTER(FUNC_LV_LOCAL);

	BUG_ON(NULL == p);

	FUNC_EXIT(FUNC_LV_LOCAL);

	return p->ops->get_cur_phy_freq(p);
}

static unsigned int _cpu_dds_calc(unsigned int khz) 
{
	unsigned int dds;

	FUNC_ENTER(FUNC_LV_HELP);

	if (khz >= PLL_DIV1_FREQ)
		dds = DDS_DIV1_FREQ + ((khz - PLL_DIV1_FREQ) / PLL_FREQ_STEP) * 0x2000;
	else if (khz >= CPU_DVFS_FREQ5)
		dds = DDS_FREQ5_FREQ + ((khz - CPU_DVFS_FREQ5) / PLL_FREQ_STEP) * 0x2000;
	else if (khz >= PLL_DIV2_FREQ)
		dds = DDS_DIV2_FREQ + ((khz - PLL_DIV2_FREQ) * 2 / PLL_FREQ_STEP) * 0x2000;
	else
		BUG();

	FUNC_EXIT(FUNC_LV_HELP);

	return dds;
}

static void _cpu_clock_switch(struct mt_cpu_dvfs *p, enum top_ckmuxsel sel)
{
	unsigned int val = cpufreq_read(TOP_CKMUXSEL);
	unsigned int mask = _BITMASK_(1 : 0);

	FUNC_ENTER(FUNC_LV_HELP);

	BUG_ON(sel >= NR_TOP_CKMUXSEL);

	cpufreq_write(TOP_CKMUXSEL, (val & ~mask) | sel);

	FUNC_EXIT(FUNC_LV_HELP);
}

static enum top_ckmuxsel _get_cpu_clock_switch(struct mt_cpu_dvfs *p)
{
	unsigned int val = cpufreq_read(TOP_CKMUXSEL);
	unsigned int mask = _BITMASK_(1 : 0);

	FUNC_ENTER(FUNC_LV_HELP);

	val &= mask;                    

	FUNC_EXIT(FUNC_LV_HELP);

	return val;
}

int mt_cpufreq_clock_switch(enum mt_cpu_dvfs_id id, enum top_ckmuxsel sel)
{
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(id);

	if (!p)
		return -1;

	_cpu_clock_switch(p, sel);

	return 0;
}

enum top_ckmuxsel mt_cpufreq_get_clock_switch(enum mt_cpu_dvfs_id id)
{
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(id);

	if (!p)
		return -1;

	return _get_cpu_clock_switch(p);
}

static void set_cur_freq(struct mt_cpu_dvfs *p, unsigned int cur_khz, unsigned int target_khz)
{
	unsigned int dds;
	unsigned int is_fhctl_used;
	unsigned int ckdiv1_val = _GET_BITS_VAL_(4 : 0, cpufreq_read(TOP_CKDIV1));
	unsigned int ckdiv1_mask = _BITMASK_(4 : 0);
	unsigned int sel = 0;
	unsigned int cur_volt = 0;
	unsigned int mainpll_volt_idx = 0;

#define IS_CLKDIV_USED(clkdiv)  (((clkdiv < 8) || ((clkdiv % 8) == 0)) ? 0 : 1)

	FUNC_ENTER(FUNC_LV_LOCAL);

	if (cur_khz == target_khz)
		return;

	

	if (((cur_khz < CPUFREQ_BOUNDARY_FOR_FHCTL) && (target_khz > CPUFREQ_BOUNDARY_FOR_FHCTL))
	    || ((target_khz < CPUFREQ_BOUNDARY_FOR_FHCTL) && (cur_khz > CPUFREQ_BOUNDARY_FOR_FHCTL))) {
		set_cur_freq(p, cur_khz, CPUFREQ_BOUNDARY_FOR_FHCTL);
		cur_khz = CPUFREQ_BOUNDARY_FOR_FHCTL;
	}

	is_fhctl_used = ((target_khz >= CPUFREQ_BOUNDARY_FOR_FHCTL) && (cur_khz >= CPUFREQ_BOUNDARY_FOR_FHCTL)) ? 1 : 0;

	cpufreq_ver("@%s():%d, cur_khz = %d, target_khz = %d, is_fhctl_used = %d\n",
		    __func__,
		    __LINE__,
		    cur_khz,
		    target_khz,
		    is_fhctl_used
		   );

	if (!is_fhctl_used) {
		
		switch (target_khz) {
		case CPU_DVFS_FREQ5:
			dds = _cpu_dds_calc(CPU_DVFS_FREQ5);   
			sel = 8;    
			break;

		case CPU_DVFS_FREQ6:
			dds = _cpu_dds_calc(PLL_DIV2_FREQ);   
			sel = 8;    
			break;

		case CPU_DVFS_FREQ7:
			dds = _cpu_dds_calc(PLL_DIV2_FREQ);   
			sel = 10;    
			break;

		default:
			BUG();
		}

		
		cur_volt = p->ops->get_cur_volt(p);
#if 1
		mainpll_volt_idx = 5; 
#else

		switch (p->cpu_level) {
		case CPU_LEVEL_0:
		case CPU_LEVEL_1:
			mainpll_volt_idx = 4;
			break;

		case CPU_LEVEL_2:
			mainpll_volt_idx = 3;
			break;

		default:
			mainpll_volt_idx = 1;
			break;
		}

#endif

		if (cur_volt < cpu_dvfs_get_volt_by_idx(p, mainpll_volt_idx))
			p->ops->set_cur_volt(p, cpu_dvfs_get_volt_by_idx(p, mainpll_volt_idx));
		else
			cur_volt = 0;

		
		_cpu_clock_switch(p, TOP_CKMUXSEL_MAINPLL);
		cpufreq_write(ARMCA15PLL_CON1, dds | _BIT_(31)); 
		udelay(PLL_SETTLE_TIME);
		cpufreq_write(TOP_CKDIV1, (ckdiv1_val & ~ckdiv1_mask) | sel);
		_cpu_clock_switch(p, TOP_CKMUXSEL_ARMPLL);

		
		if (cur_volt)
			p->ops->set_cur_volt(p, cur_volt);
	} else {
		dds = _cpu_dds_calc(target_khz);
		BUG_ON(dds & _BITMASK_(26 : 24)); 

#if !defined(__KERNEL__) && defined(MTKDRV_FREQHOP)
		freqhopping_dvt_dvfs_enable(ARMCA15PLL_ID, target_khz);
#else  
#if 1
		mt_dfs_armpll(FH_ARMCA15_PLLID, dds);
#else
		_cpu_clock_switch(p, TOP_CKMUXSEL_MAINPLL);
		cpufreq_write(ARMCA15PLL_CON1, dds | _BIT_(31)); 
		udelay(PLL_SETTLE_TIME);
		_cpu_clock_switch(p, TOP_CKMUXSEL_ARMPLL);
#endif
#endif 
	}

	FUNC_EXIT(FUNC_LV_LOCAL);
}

static unsigned int get_cur_vsram(struct mt_cpu_dvfs *p)
{
	unsigned int rdata = 0;
	unsigned int retry_cnt = 5;

	FUNC_ENTER(FUNC_LV_LOCAL);

	pwrap_read(PMIC_ADDR_VSRAM_CA7_EN, &rdata);

	rdata &= _BITMASK_(10 : 10); 

	if (rdata) { 
		do {
			pwrap_read(PMIC_ADDR_VSRAM_VOSEL_ON, &rdata);
		} while (rdata == _BITMASK_(10 : 10) && retry_cnt--);

		rdata &= 0x7F;
		rdata = PMIC_VAL_TO_VOLT(rdata);
	}

	FUNC_EXIT(FUNC_LV_LOCAL);

	return rdata; 
}

static unsigned int get_cur_volt_extbuck(struct mt_cpu_dvfs *p)
{
	unsigned char ret_val;
	unsigned int ret_mv;
	unsigned int retry_cnt = 5;

	FUNC_ENTER(FUNC_LV_LOCAL);

	do {
		if (!da9210_read_byte(0xD8, &ret_val)) { 
			cpufreq_err("%s(), fail to read ext buck volt\n", __func__);
			ret_mv = 0;
		} else
			ret_mv = EXTBUCK_VAL_TO_VOLT(ret_val);
	} while (ret_mv == EXTBUCK_VAL_TO_VOLT(0) && retry_cnt--); 

	FUNC_EXIT(FUNC_LV_LOCAL);

	return ret_mv * 100; 
}

unsigned int mt_cpufreq_get_cur_volt(enum mt_cpu_dvfs_id id)
{
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(id);

	FUNC_ENTER(FUNC_LV_API);

	BUG_ON(NULL == p);
	BUG_ON(NULL == p->ops);

	FUNC_EXIT(FUNC_LV_API);

	return p->ops->get_cur_volt(p);  
}
EXPORT_SYMBOL(mt_cpufreq_get_cur_volt);

#if 0
static unsigned int _calc_pmic_settle_time(unsigned int old_vproc, unsigned int old_vsram, unsigned int new_vproc, unsigned int new_vsram)
{
	unsigned delay = 100;

	if (new_vproc == old_vproc && new_vsram == old_vsram)
		return 0;

	
	if (new_vproc >= old_vproc) {
		
		if (new_vsram >= old_vsram)
			delay = MAX(
					PMIC_VOLT_UP_SETTLE_TIME(old_vsram, new_vsram),
					PMIC_VOLT_UP_SETTLE_TIME(old_vproc, new_vproc)
				);
		
		else
			delay = MAX(
					PMIC_VOLT_DOWN_SETTLE_TIME(old_vsram, new_vsram),
					PMIC_VOLT_UP_SETTLE_TIME(old_vproc, new_vproc)
				);
	}
	
	else {
		
		if (old_vsram >= new_vsram)
			delay = MAX(
					PMIC_VOLT_DOWN_SETTLE_TIME(old_vsram, new_vsram),
					PMIC_VOLT_DOWN_SETTLE_TIME(old_vproc, new_vproc)
				);
		
		else
			delay = MAX(
					PMIC_VOLT_UP_SETTLE_TIME(old_vsram, new_vsram),
					PMIC_VOLT_DOWN_SETTLE_TIME(old_vproc, new_vproc)
				);
	}

	if (delay < MIN_PMIC_SETTLE_TIME)
		delay = MIN_PMIC_SETTLE_TIME;

	return delay;
}
#endif
static void dump_opp_table(struct mt_cpu_dvfs *p)
{
	int i;

	cpufreq_err("[%s/%d]\n"
		    "cpufreq_oppidx = %d\n",
		    p->name, p->cpu_id,
		    p->idx_opp_tbl
		   );

	for (i = 0; i < p->nr_opp_tbl; i++) {
		cpufreq_err("\tOP(%d, %d),\n",
			    cpu_dvfs_get_freq_by_idx(p, i),
			    cpu_dvfs_get_volt_by_idx(p, i)
			   );
	}
}

static int set_cur_volt_extbuck(struct mt_cpu_dvfs *p, unsigned int mv) 
{
	unsigned int cur_vsram_mv = get_cur_vsram(p);
	unsigned int cur_vproc_mv = get_cur_volt_extbuck(p);
	int ret = 0;

	FUNC_ENTER(FUNC_LV_LOCAL);

#ifdef CONFIG_CPU_DVFS_AEE_RR_REC
	aee_rr_rec_cpu_dvfs_vproc_little(VOLT_TO_PMIC_VAL(mv));
#endif

	if (unlikely(!((cur_vsram_mv >= cur_vproc_mv) && (MAX_DIFF_VSRAM_VPROC >= (cur_vsram_mv - cur_vproc_mv))))) {
		unsigned char ret_val;
		int i;

		dump_opp_table(p);

		
		cpufreq_err("@%s():%d, cur_vsram_mv = %d (%d), cur_vproc_mv = %d (%d)\n",
			    __func__,
			    __LINE__,
			    cur_vsram_mv,
			    cpu_dvfs_get_cur_volt(p),
			    cur_vproc_mv,
			    cpu_dvfs_get_cur_volt(p) + NORMAL_DIFF_VRSAM_VPROC
			   );

		for (i = 0; i < 10; i++) {
			extern kal_uint32 da9210_config_interface(kal_uint8 RegNum, kal_uint8 val, kal_uint8 MASK, kal_uint8 SHIFT);
			extern kal_uint32 da9210_read_interface(kal_uint8 RegNum, kal_uint8 * val, kal_uint8 MASK, kal_uint8 SHIFT);
			da9210_config_interface(0x0, 0x1, 0x1, 7); 
			da9210_config_interface(0x0, 0x2, 0xF, 0); 
			da9210_read_interface(0x5, &ret_val, 0xF, 4);
			cpufreq_err("%s(), da9210 ID = %x\n", __func__, ret_val);
		}

		for (i = 0; i < 10; i++) {
			extern kal_uint32 tps6128x_read_byte(kal_uint8 cmd, kal_uint8 * returnData);
			tps6128x_read_byte(0x3, &ret_val); 
			cpufreq_err("%s(), tps6128x ID = %x\n", __func__, ret_val);
		}

		aee_kernel_warning(TAG, "@%s():%d, cur_vsram_mv = %d, cur_vproc_mv = %d\n", __func__, __LINE__, cur_vsram_mv, cur_vproc_mv);

		cur_vproc_mv = cpu_dvfs_get_cur_volt(p);
		cur_vsram_mv = cur_vproc_mv + NORMAL_DIFF_VRSAM_VPROC;
	}

	if (cur_vsram_mv - cur_vproc_mv > NORMAL_DIFF_VRSAM_VPROC) {
		cur_vsram_mv = cur_vproc_mv + NORMAL_DIFF_VRSAM_VPROC;
		mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_DEEPIDLE, IDX_DI_VSRAM_CA7_NORMAL, VOLT_TO_PMIC_VAL(cur_vsram_mv));
		mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_SODI, IDX_SO_VSRAM_CA7_NORMAL, VOLT_TO_PMIC_VAL(cur_vsram_mv));
		mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_NORMAL, IDX_NM_VSRAM_CA7, VOLT_TO_PMIC_VAL(cur_vsram_mv));
		mt_cpufreq_apply_pmic_cmd(IDX_NM_VSRAM_CA7);
	}

	
	if (mv > cur_vproc_mv) {
		unsigned int target_vsram_mv = mv + NORMAL_DIFF_VRSAM_VPROC;
		unsigned int next_vsram_mv;

		do {
			next_vsram_mv = MIN(((MAX_DIFF_VSRAM_VPROC - 2500) + cur_vproc_mv), target_vsram_mv);

			
			cur_vsram_mv = MAX(next_vsram_mv, MIN_VSRAM_VOLT); 
			if (cur_vsram_mv > MAX_VSRAM_VOLT) {
				cur_vsram_mv = MAX_VSRAM_VOLT;
				target_vsram_mv = MAX_VSRAM_VOLT; 
			}

			if (unlikely(!((cur_vsram_mv >= cur_vproc_mv) && (MAX_DIFF_VSRAM_VPROC >= (cur_vsram_mv - cur_vproc_mv))))) {
				dump_opp_table(p);
				cpufreq_err("@%s():%d, cur_vsram_mv = %d, cur_vproc_mv = %d\n", __func__, __LINE__, cur_vsram_mv, cur_vproc_mv);
				BUG();
			}

			mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_DEEPIDLE, IDX_DI_VSRAM_CA7_NORMAL, VOLT_TO_PMIC_VAL(cur_vsram_mv));
			mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_SODI, IDX_SO_VSRAM_CA7_NORMAL, VOLT_TO_PMIC_VAL(cur_vsram_mv));
			mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_NORMAL, IDX_NM_VSRAM_CA7, VOLT_TO_PMIC_VAL(cur_vsram_mv));
			mt_cpufreq_apply_pmic_cmd(IDX_NM_VSRAM_CA7);

			
			if (next_vsram_mv > MAX_VSRAM_VOLT)
				cur_vproc_mv = mv;   
			else
				cur_vproc_mv = next_vsram_mv - NORMAL_DIFF_VRSAM_VPROC;

			if (unlikely(!((cur_vsram_mv >= cur_vproc_mv) && (MAX_DIFF_VSRAM_VPROC >= (cur_vsram_mv - cur_vproc_mv))))) {
				dump_opp_table(p);
				cpufreq_err("@%s():%d, cur_vsram_mv = %d, cur_vproc_mv = %d\n", __func__, __LINE__, cur_vsram_mv, cur_vproc_mv);
				BUG();
			}

			if (!ext_buck_vosel(cur_vproc_mv)) { 
				cpufreq_err("%s(), fail to set ext buck volt\n", __func__);
				ret = -1;
			}

			udelay(PMIC_SETTLE_TIME(cur_vproc_mv - MAX_DIFF_VSRAM_VPROC, cur_vproc_mv)); 

			
		} while (target_vsram_mv > cur_vsram_mv);
	}
	
	else if (mv < cur_vproc_mv) {
		unsigned int next_vproc_mv;
		unsigned int next_vsram_mv = cur_vproc_mv + NORMAL_DIFF_VRSAM_VPROC;

		do {
			next_vproc_mv = MAX((next_vsram_mv - (MAX_DIFF_VSRAM_VPROC - 2500)), mv);

			
			cur_vproc_mv = next_vproc_mv;

			if (unlikely(!((cur_vsram_mv >= cur_vproc_mv) && (MAX_DIFF_VSRAM_VPROC >= (cur_vsram_mv - cur_vproc_mv))))) {
				dump_opp_table(p);
				cpufreq_err("@%s():%d, cur_vsram_mv = %d, cur_vproc_mv = %d\n", __func__, __LINE__, cur_vsram_mv, cur_vproc_mv);
				BUG();
			}

			if (!ext_buck_vosel(cur_vproc_mv)) { 
				cpufreq_err("%s(), fail to set ext buck volt\n", __func__);
				ret = -1;
			}

			
			next_vsram_mv = cur_vproc_mv + NORMAL_DIFF_VRSAM_VPROC;
			cur_vsram_mv = MAX(next_vsram_mv, MIN_VSRAM_VOLT); 
			cur_vsram_mv = MIN(cur_vsram_mv, MAX_VSRAM_VOLT); 

			if (unlikely(!((cur_vsram_mv >= cur_vproc_mv) && (MAX_DIFF_VSRAM_VPROC >= (cur_vsram_mv - cur_vproc_mv))))) {
				dump_opp_table(p);
				cpufreq_err("@%s():%d, cur_vsram_mv = %d, cur_vproc_mv = %d\n", __func__, __LINE__, cur_vsram_mv, cur_vproc_mv);
				BUG();
			}

			mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_DEEPIDLE, IDX_DI_VSRAM_CA7_NORMAL, VOLT_TO_PMIC_VAL(cur_vsram_mv));
			mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_SODI, IDX_SO_VSRAM_CA7_NORMAL, VOLT_TO_PMIC_VAL(cur_vsram_mv));
			mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_NORMAL, IDX_NM_VSRAM_CA7, VOLT_TO_PMIC_VAL(cur_vsram_mv));
			mt_cpufreq_apply_pmic_cmd(IDX_NM_VSRAM_CA7);

			udelay(PMIC_SETTLE_TIME(cur_vproc_mv + MAX_DIFF_VSRAM_VPROC, cur_vproc_mv)); 

			
		} while (cur_vproc_mv > mv);
	}

	if (NULL != g_pCpuVoltSampler)
		g_pCpuVoltSampler(MT_CPU_DVFS_LITTLE, mv / 100); 

	cpufreq_ver("@%s():%d, cur_vsram_mv = %d, cur_vproc_mv = %d\n", __func__, __LINE__, cur_vsram_mv, cur_vproc_mv);

	FUNC_EXIT(FUNC_LV_LOCAL);

	return ret;
}


static unsigned int _search_available_volt(struct mt_cpu_dvfs *p, unsigned int target_khz)
{
	int i;

	FUNC_ENTER(FUNC_LV_HELP);

	BUG_ON(NULL == p);

	
	for (i = p->nr_opp_tbl - 1; i >= 0; i--) {
		if (target_khz <= cpu_dvfs_get_freq_by_idx(p, i))
			break;
	}

	BUG_ON(i < 0); 

	FUNC_EXIT(FUNC_LV_HELP);

	return cpu_dvfs_get_volt_by_idx(p, i); 
}

static int _cpufreq_set_locked(struct mt_cpu_dvfs *p, unsigned int cur_khz, unsigned int target_khz, struct cpufreq_policy *policy)
{
	unsigned int volt; 
	int ret = 0;

#ifdef CONFIG_CPU_FREQ
	struct cpufreq_freqs freqs;
	unsigned int cpu;
	unsigned int target_khz_orig = target_khz;
#endif

	enum turbo_mode mode = get_turbo_mode(p, target_khz);

	FUNC_ENTER(FUNC_LV_HELP);

	volt = _search_available_volt(p, target_khz);

	if (cur_khz != TURBO_MODE_FREQ(mode, target_khz))
		cpufreq_ver("@%s(), target_khz = %d (%d), volt = %d (%d), num_online_cpus = %d, cur_khz = %d\n",
			    __func__,
			    target_khz,
			    TURBO_MODE_FREQ(mode, target_khz),
			    volt,
			    TURBO_MODE_VOLT(mode, volt),
			    num_online_cpus(),
			    cur_khz
			   );

	volt = TURBO_MODE_VOLT(mode, volt);
	target_khz = TURBO_MODE_FREQ(mode, target_khz);

	if (cur_khz == target_khz)
		goto out;

	
	if (cur_khz < target_khz) {
		ret = p->ops->set_cur_volt(p, volt);

		if (ret) 
			goto out;
	}

#ifdef CONFIG_CPU_FREQ
	freqs.old = p->ops->get_cur_phy_freq(p);
	freqs.new = target_khz_orig;

	if (policy) {
		for_each_online_cpu(cpu) {
			freqs.cpu = cpu;
			cpufreq_notify_transition(policy, &freqs, CPUFREQ_PRECHANGE);
		}
	}

#endif

	
	if (cur_khz != target_khz)
		p->ops->set_cur_freq(p, cur_khz, target_khz);

#ifdef CONFIG_CPU_FREQ

	if (policy) {
		for_each_online_cpu(cpu) {
			freqs.cpu = cpu;
			cpufreq_notify_transition(policy, &freqs, CPUFREQ_POSTCHANGE);
		}
	}

#endif

	
	if (cur_khz > target_khz) {
		ret = p->ops->set_cur_volt(p, volt);

		if (ret) 
			goto out;
	}

#if defined(CONFIG_CPU_DVFS_AEE_RR_REC) && defined(CONFIG_HTC_DEBUG_FOOTPRINT)
	aee_rr_rec_cpu_freq(p->ops->get_cur_phy_freq(p));
	aee_rr_rec_dvfs_vproc_volt((p->ops->get_cur_volt(p)) / 100);
	aee_rr_rec_dvfs_vsram_volt(get_cur_vsram(p) / 100);
#else
	cpufreq_dbg("@%s(): Vproc = %dmv, Vsram = %dmv, freq = %d KHz\n",
		    __func__,
		    (p->ops->get_cur_volt(p)) / 100,
		    (get_cur_vsram(p) / 100),
		    p->ops->get_cur_phy_freq(p)
		   );
#endif

	
	if (do_dvfs_stress_test && (!p->dvfs_disable_by_suspend)) {
		BUG_ON(p->ops->get_cur_volt(p) < volt);
		BUG_ON(p->ops->get_cur_phy_freq(p) != target_khz);
	}

	FUNC_EXIT(FUNC_LV_HELP);
out:
	return ret;
}

static unsigned int _calc_new_opp_idx(struct mt_cpu_dvfs *p, int new_opp_idx);

static void _mt_cpufreq_set(enum mt_cpu_dvfs_id id, int new_opp_idx)
{
	unsigned long flags;
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(id);
	unsigned int cur_freq;
	unsigned int target_freq;
#ifdef CONFIG_CPU_FREQ
	struct cpufreq_policy *policy;
#endif

	FUNC_ENTER(FUNC_LV_LOCAL);

	BUG_ON(NULL == p);
	BUG_ON(new_opp_idx >= p->nr_opp_tbl);

#ifdef CONFIG_CPU_FREQ
	policy = cpufreq_cpu_get(p->cpu_id);
#endif

	cpufreq_lock(flags);	

	
	if (new_opp_idx == -1)
		new_opp_idx = p->idx_opp_tbl;

	if (do_dvfs_stress_test && (!p->dvfs_disable_by_suspend))
		new_opp_idx = jiffies & 0x7; 
	else {
#if defined(CONFIG_CPU_DVFS_BRINGUP)
		new_opp_idx = id_to_cpu_dvfs(id)->idx_normal_max_opp;
#else
		new_opp_idx = _calc_new_opp_idx(id_to_cpu_dvfs(id), new_opp_idx);
#endif
	}

	cur_freq = p->ops->get_cur_phy_freq(p);
	target_freq = cpu_dvfs_get_freq_by_idx(p, new_opp_idx);
#ifdef CONFIG_CPU_FREQ
	_cpufreq_set_locked(p, cur_freq, target_freq, policy);
#else
	_cpufreq_set_locked(p, cur_freq, target_freq, NULL);
#endif
	p->idx_opp_tbl = new_opp_idx;

	cpufreq_unlock(flags);	

#ifdef CONFIG_CPU_FREQ

	if (policy)
		cpufreq_cpu_put(policy);

#endif

	FUNC_EXIT(FUNC_LV_LOCAL);
}

static int __cpuinit turbo_mode_cpu_callback(struct notifier_block *nfb,
		unsigned long action, void *hcpu)
{
#if 1
	unsigned int cpu = (unsigned long)hcpu;
	unsigned int online_cpus = num_online_cpus();
	struct device *dev;
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(0); 

	cpufreq_ver("@%s():%d, cpu = %d, action = %lu, oppidx = %d, num_online_cpus = %d, num_online_cpus_delta = %d\n",
		    __func__,
		    __LINE__,
		    cpu,
		    action,
		    p->idx_opp_tbl,
		    online_cpus,
		    num_online_cpus_delta
		   ); 

	dev = get_cpu_device(cpu);

	if (dev) {
		if (TURBO_MODE_BOUNDARY_CPU_NUM == online_cpus) {
			switch (action) {
			case CPU_UP_PREPARE:
			case CPU_UP_PREPARE_FROZEN:
				num_online_cpus_delta = 1;

			case CPU_DEAD:
			case CPU_DEAD_FROZEN:
				_mt_cpufreq_set(MT_CPU_DVFS_LITTLE, -1);
				break;
			}
		} else {
			switch (action) {
			case CPU_ONLINE:    
			case CPU_ONLINE_FROZEN:
			case CPU_UP_CANCELED:   
			case CPU_UP_CANCELED_FROZEN:
				num_online_cpus_delta = 0;
				break;
			}
		}

		cpufreq_ver("@%s():%d, cpu = %d, action = %lu, oppidx = %d, num_online_cpus = %d, num_online_cpus_delta = %d\n",
			    __func__,
			    __LINE__,
			    cpu,
			    action,
			    p->idx_opp_tbl,
			    online_cpus,
			    num_online_cpus_delta
			   ); 
	}

#else	
	struct cpufreq_policy *policy;
	unsigned int cpu = (unsigned long)hcpu;
	struct device *dev;
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(0); 

	cpufreq_ver("@%s():%d, cpu = %d, action = %d, oppidx = %d, num_online_cpus = %d\n", __func__, __LINE__, cpu, action, p->idx_opp_tbl, num_online_cpus()); 

	dev = get_cpu_device(cpu);

	if (dev
	    && 0 == p->idx_opp_tbl
	    && TURBO_MODE_BOUNDARY_CPU_NUM == num_online_cpus()
	   ) {
		switch (action) {
		case CPU_UP_PREPARE:
		case CPU_DEAD:

			policy = cpufreq_cpu_get(p->cpu_id);

			if (policy) {
				cpufreq_driver_target(policy, cpu_dvfs_get_cur_freq(p), CPUFREQ_RELATION_L);
				cpufreq_cpu_put(policy);
			}

			cpufreq_ver("@%s():%d, cpu = %d, action = %d, oppidx = %d, num_online_cpus = %d\n", __func__, __LINE__, cpu, action, p->idx_opp_tbl, num_online_cpus()); 
			break;
		}
	}

#endif
	return NOTIFY_OK;
}

static struct notifier_block __refdata turbo_mode_cpu_notifier = {
	.notifier_call = turbo_mode_cpu_callback,
};

static void _set_no_limited(struct mt_cpu_dvfs *p)
{
	FUNC_ENTER(FUNC_LV_HELP);

	BUG_ON(NULL == p);

	p->limited_max_freq = cpu_dvfs_get_max_freq(p);
	p->limited_max_ncpu = max_cpu_num;
	p->thermal_protect_limited_power = 0;

	FUNC_EXIT(FUNC_LV_HELP);
}

#ifdef CONFIG_CPU_DVFS_DOWNGRADE_FREQ
static void _downgrade_freq_check(enum mt_cpu_dvfs_id id)
{
	struct cpufreq_policy *policy;
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(id);
	int temp = 0;

	FUNC_ENTER(FUNC_LV_API);

	BUG_ON(NULL == p);

	
	if (p->cpu_level != CPU_LEVEL_0)
		goto out;

	
#if 0 

	if (mt_ptp_status((MT_CPU_DVFS_LITTLE == id) ? PTP_DET_LITTLE : PTP_DET_BIG) == 1)
		temp = (((DRV_Reg32(PTP_TEMP) & 0xff)) + 25) * 1000; 
	else
		temp = mtktscpu_get_Tj_temp(); 

#else
	temp = tscpu_get_temp_by_bank(THERMAL_BANK0);    
#endif


	if (temp < 0 || 125000 < temp) {
		
		goto out;
	}

	{
		static enum turbo_mode pre_mode = TURBO_MODE_NONE;
		enum turbo_mode cur_mode = get_turbo_mode(p, cpu_dvfs_get_cur_freq(p));

		if (pre_mode != cur_mode) {
			_mt_cpufreq_set(MT_CPU_DVFS_LITTLE, -1);
			cpufreq_ver("@%s():%d, oppidx = %d, num_online_cpus = %d, pre_mode = %d, cur_mode = %d\n",
				    __func__,
				    __LINE__,
				    p->idx_opp_tbl,
				    num_online_cpus(),
				    pre_mode,
				    cur_mode
				   ); 
			pre_mode = cur_mode;
		}
	}

	if (temp <= p->ptpod_temperature_limit_1) {
		p->downgrade_freq_for_ptpod  = false;
		
		goto out;
	} else if ((temp > p->ptpod_temperature_limit_1) && (temp < p->ptpod_temperature_limit_2)) {
		p->downgrade_freq_counter_return_limit = p->downgrade_freq_counter_limit * p->ptpod_temperature_time_1;
		
	} else {
		p->downgrade_freq_counter_return_limit = p->downgrade_freq_counter_limit * p->ptpod_temperature_time_2;
		
	}

	if (p->downgrade_freq_for_ptpod == false) {
		if ((num_online_cpus() == p->pre_online_cpu) && (cpu_dvfs_get_cur_freq(p) == p->pre_freq)) {
			if ((num_online_cpus() >= p->over_max_cpu) && (p->idx_opp_tbl == 0)) {
				p->downgrade_freq_counter++;
				
				

				if (p->downgrade_freq_counter >= p->downgrade_freq_counter_limit) {
					p->downgrade_freq = cpu_dvfs_get_freq_by_idx(p, 1);

					p->downgrade_freq_for_ptpod = true;
					p->downgrade_freq_counter = 0;

					cpufreq_info("freq limit, downgrade_freq_for_ptpod = %d\n", p->downgrade_freq_for_ptpod);

					policy = cpufreq_cpu_get(p->cpu_id);

					if (!policy)
						goto out;

					cpufreq_driver_target(policy, p->downgrade_freq, CPUFREQ_RELATION_L);

					cpufreq_cpu_put(policy);
				}
			} else
				p->downgrade_freq_counter = 0;
		} else {
			p->pre_online_cpu = num_online_cpus();
			p->pre_freq = cpu_dvfs_get_cur_freq(p);

			p->downgrade_freq_counter = 0;
		}
	} else {
		p->downgrade_freq_counter_return++;

		
		

		if (p->downgrade_freq_counter_return >= p->downgrade_freq_counter_return_limit) {
			p->downgrade_freq_for_ptpod  = false;
			p->downgrade_freq_counter_return = 0;

			
		}
	}

out:
	FUNC_EXIT(FUNC_LV_API);
}

static void _init_downgrade(struct mt_cpu_dvfs *p, unsigned int cpu_level)
{
	FUNC_ENTER(FUNC_LV_HELP);

	switch (cpu_level) {
	case CPU_LEVEL_0:
	case CPU_LEVEL_1:
	case CPU_LEVEL_2:
	default:
#if 0 
		p->downgrade_freq_counter_limit = cpu_dvfs_is(p, MT_CPU_DVFS_LITTLE) ? 10 : 10;
		p->ptpod_temperature_time_1     = cpu_dvfs_is(p, MT_CPU_DVFS_LITTLE) ? 2  : 1;
		p->ptpod_temperature_time_2     = cpu_dvfs_is(p, MT_CPU_DVFS_LITTLE) ? 8  : 4;
#else
		p->downgrade_freq_counter_limit = 10;
		p->ptpod_temperature_time_1     = 2;
		p->ptpod_temperature_time_2     = 8;
#endif
		break;
	}

#ifdef __KERNEL__
	
	cpufreq_freq_check = _downgrade_freq_check;
#endif

	FUNC_EXIT(FUNC_LV_HELP);
}
#endif

static int _sync_opp_tbl_idx(struct mt_cpu_dvfs *p)
{
	int ret = -1;
	unsigned int freq;
	int i;

	FUNC_ENTER(FUNC_LV_HELP);

	BUG_ON(NULL == p);
	BUG_ON(NULL == p->opp_tbl);
	BUG_ON(NULL == p->ops);

	freq = p->ops->get_cur_phy_freq(p);

	for (i = p->nr_opp_tbl - 1; i >= 0; i--) {
		if (freq <= cpu_dvfs_get_freq_by_idx(p, i)) {
			p->idx_opp_tbl = i;
			break;
		}

	}

	if (i >= 0) {
		cpufreq_info("%s freq = %d\n", cpu_dvfs_get_name(p), cpu_dvfs_get_cur_freq(p));

		

		ret = 0;
	} else
		cpufreq_warn("%s can't find freq = %d\n", cpu_dvfs_get_name(p), freq);

	FUNC_EXIT(FUNC_LV_HELP);

	return ret;
}

static void _mt_cpufreq_sync_opp_tbl_idx(void)
{
	struct mt_cpu_dvfs *p;
	int i;

	FUNC_ENTER(FUNC_LV_LOCAL);

	for_each_cpu_dvfs(i, p) {
		if (cpu_dvfs_is_availiable(p))
			_sync_opp_tbl_idx(p);
	}

	FUNC_EXIT(FUNC_LV_LOCAL);
}

static enum mt_cpu_dvfs_id _get_cpu_dvfs_id(unsigned int cpu_id)
{
#if 1
	
	return MT_CPU_DVFS_LITTLE;
#else
#if 1	
	return (enum mt_cpu_dvfs_id)((cpu_id < 4) ? 0 : 1);
#else	
	struct mt_cpu_dvfs *p;
	int i;

	for_each_cpu_dvfs(i, p) {
		if (p->cpu_id == cpu_id)
			break;
	}

	BUG_ON(i >= NR_MT_CPU_DVFS);

	return i;
#endif	
#endif
}

int mt_cpufreq_state_set(int enabled) 
{
#if 0
	bool set_normal_max_opp = false;
	struct mt_cpu_dvfs *p;
	int i;
	unsigned long flags;
#endif
	int ret = 0;

	FUNC_ENTER(FUNC_LV_API);

#if 0
	for_each_cpu_dvfs(i, p) {
		if (!cpu_dvfs_is_availiable(p))
			continue;

		cpufreq_lock(flags);

		if (enabled) {
			
			if (p->dvfs_disable_by_suspend) {
				p->dvfs_disable_count--;
				cpufreq_dbg("enable %s DVFS: dvfs_disable_count = %d\n", p->name, p->dvfs_disable_count);

				if (p->dvfs_disable_count <= 0)
					p->dvfs_disable_by_suspend = false;
				else
					cpufreq_dbg("someone still disable %s DVFS and cant't enable it\n", p->name);
			} else
				cpufreq_dbg("%s DVFS already enabled\n", p->name);
		} else {
			
			p->dvfs_disable_count++;

			if (p->dvfs_disable_by_suspend)
				cpufreq_dbg("%s DVFS already disabled\n", p->name);
			else {
				p->dvfs_disable_by_suspend = true;
				set_normal_max_opp = true;
			}
		}

		cpufreq_unlock(flags);

		if (set_normal_max_opp) {
			struct cpufreq_policy *policy = cpufreq_cpu_get(p->cpu_id);

			if (policy) {
				cpufreq_driver_target(policy, cpu_dvfs_get_normal_max_freq(p), CPUFREQ_RELATION_L);
				cpufreq_cpu_put(policy);
			} else {
				cpufreq_warn("can't get cpufreq policy to disable %s DVFS\n", p->name);
				ret = -1;
			}
		}

		set_normal_max_opp = false;
	}
#endif
	FUNC_EXIT(FUNC_LV_API);

	return ret;
}
EXPORT_SYMBOL(mt_cpufreq_state_set);

#if 0
#define P_MCU_L         (1243)  
#define P_MCU_T         (2900)  
#define P_CA7_L         (110)   
#define P_CA7_T         (305)   

#define P_MCL99_105C_L  (1243)  
#define P_MCL99_25C_L   (93)    
#define P_MCL50_105C_L  (587)   
#define P_MCL50_25C_L   (35)    

#define T_105           (105)   
#define T_65            (65)    
#define T_25            (25)    

#define P_MCU_D ((P_MCU_T - P_MCU_L) - 8 * (P_CA7_T - P_CA7_L)) 

#define P_TOTAL_CORE_L ((P_MCL99_105C_L  * 27049) / 100000) 
#define P_EACH_CORE_L  ((P_TOTAL_CORE_L * ((P_CA7_L * 1000) / P_MCU_L)) / 1000) 

#define P_CA7_D_1_CORE ((P_CA7_T - P_CA7_L) * 1) 
#define P_CA7_D_2_CORE ((P_CA7_T - P_CA7_L) * 2) 
#define P_CA7_D_3_CORE ((P_CA7_T - P_CA7_L) * 3) 
#define P_CA7_D_4_CORE ((P_CA7_T - P_CA7_L) * 4) 

#define A_1_CORE (P_MCU_D + P_CA7_D_1_CORE) 
#define A_2_CORE (P_MCU_D + P_CA7_D_2_CORE) 
#define A_3_CORE (P_MCU_D + P_CA7_D_3_CORE) 
#define A_4_CORE (P_MCU_D + P_CA7_D_4_CORE) 

static void _power_calculation(struct mt_cpu_dvfs *p, int idx, int ncpu)
{
	int multi = 0, p_dynamic = 0, p_leakage = 0, freq_ratio = 0, volt_square_ratio = 0;
	int possible_cpu = 0;

	FUNC_ENTER(FUNC_LV_HELP);

	possible_cpu = num_possible_cpus(); 

	volt_square_ratio = (((p->opp_tbl[idx].cpufreq_volt * 100) / 1000) *
			     ((p->opp_tbl[idx].cpufreq_volt * 100) / 1000)) / 100;
	freq_ratio = (p->opp_tbl[idx].cpufreq_khz / 1700);

	cpufreq_dbg("freq_ratio = %d, volt_square_ratio %d\n", freq_ratio, volt_square_ratio);

	multi = ((p->opp_tbl[idx].cpufreq_volt * 100) / 1000) *
		((p->opp_tbl[idx].cpufreq_volt * 100) / 1000) *
		((p->opp_tbl[idx].cpufreq_volt * 100) / 1000);

	switch (ncpu) {
	case 0:
		
		p_dynamic = (((A_1_CORE * freq_ratio) / 1000) * volt_square_ratio) / 100;
		p_leakage = ((P_TOTAL_CORE_L - 7 * P_EACH_CORE_L) * (multi)) / (100 * 100 * 100);
		cpufreq_dbg("p_dynamic = %d, p_leakage = %d\n", p_dynamic, p_leakage);
		break;

	case 1:
		
		p_dynamic = (((A_2_CORE * freq_ratio) / 1000) * volt_square_ratio) / 100;
		p_leakage = ((P_TOTAL_CORE_L - 6 * P_EACH_CORE_L) * (multi)) / (100 * 100 * 100);
		cpufreq_dbg("p_dynamic = %d, p_leakage = %d\n", p_dynamic, p_leakage);
		break;

	case 2:
		
		p_dynamic = (((A_3_CORE * freq_ratio) / 1000) * volt_square_ratio) / 100;
		p_leakage = ((P_TOTAL_CORE_L - 5 * P_EACH_CORE_L) * (multi)) / (100 * 100 * 100);
		cpufreq_dbg("p_dynamic = %d, p_leakage = %d\n", p_dynamic, p_leakage);
		break;

	case 3:
		
		p_dynamic = (((A_4_CORE * freq_ratio) / 1000) * volt_square_ratio) / 100;
		p_leakage = ((P_TOTAL_CORE_L - 4 * P_EACH_CORE_L) * (multi)) / (100 * 100 * 100);
		cpufreq_dbg("p_dynamic = %d, p_leakage = %d\n", p_dynamic, p_leakage);
		break;

	default:
		break;
	}

	p->power_tbl[idx * possible_cpu + ncpu].cpufreq_ncpu    = ncpu + 1;
	p->power_tbl[idx * possible_cpu + ncpu].cpufreq_khz     = p->opp_tbl[idx].cpufreq_khz;
	p->power_tbl[idx * possible_cpu + ncpu].cpufreq_power   = p_dynamic + p_leakage;

	cpufreq_dbg("p->power_tbl[%d]: cpufreq_ncpu = %d, cpufreq_khz = %d, cpufreq_power = %d\n",
		    (idx * possible_cpu + ncpu),
		    p->power_tbl[idx * possible_cpu + ncpu].cpufreq_ncpu,
		    p->power_tbl[idx * possible_cpu + ncpu].cpufreq_khz,
		    p->power_tbl[idx * possible_cpu + ncpu].cpufreq_power
		   );

	FUNC_EXIT(FUNC_LV_HELP);
}

static int setup_power_table(struct mt_cpu_dvfs *p)
{
	static const unsigned int pwr_tbl_cgf[] = { 0, 0, 1, 0, 1, 0, 1, 0, };
	unsigned int pwr_eff_tbl[NR_MAX_OPP_TBL][NR_MAX_CPU];
	unsigned int pwr_eff_num;
	int possible_cpu;
	int i, j;
	int ret = 0;

	FUNC_ENTER(FUNC_LV_LOCAL);

	BUG_ON(NULL == p);

	if (p->power_tbl)
		goto out;

	cpufreq_dbg("P_MCU_D = %d\n", P_MCU_D);
	cpufreq_dbg("P_CA7_D_1_CORE = %d, P_CA7_D_2_CORE = %d, P_CA7_D_3_CORE = %d, P_CA7_D_4_CORE = %d\n", P_CA7_D_1_CORE, P_CA7_D_2_CORE, P_CA7_D_3_CORE, P_CA7_D_4_CORE);
	cpufreq_dbg("P_TOTAL_CORE_L = %d, P_EACH_CORE_L = %d\n", P_TOTAL_CORE_L, P_EACH_CORE_L);
	cpufreq_dbg("A_1_CORE = %d, A_2_CORE = %d, A_3_CORE = %d, A_4_CORE = %d\n", A_1_CORE, A_2_CORE, A_3_CORE, A_4_CORE);

	possible_cpu = num_possible_cpus(); 

	
	memset((void *)pwr_eff_tbl, 0, sizeof(pwr_eff_tbl));
	p->power_tbl = kzalloc(p->nr_opp_tbl * possible_cpu * sizeof(struct mt_cpu_power_info), GFP_KERNEL);

	if (NULL == p->power_tbl) {
		ret = -ENOMEM;
		goto out;
	}

	
	for (i = 0, pwr_eff_num = 0; i < possible_cpu; i++) {
		if (1 == pwr_tbl_cgf[i])
			pwr_eff_num++;
	}

	for (i = 0; i < p->nr_opp_tbl; i++) {
		for (j = 0; j < possible_cpu; j++) {
			if (1 == pwr_tbl_cgf[j])
				pwr_eff_tbl[i][j] = 1;
		}
	}

	p->nr_power_tbl = p->nr_opp_tbl * (possible_cpu - pwr_eff_num);

	
	for (i = 0; i < p->nr_opp_tbl; i++) {
		for (j = 0; j < possible_cpu; j++) {
			if (0 == pwr_eff_tbl[i][j])
				_power_calculation(p, i, j);
		}
	}

	
	for (i = p->nr_opp_tbl * possible_cpu; i > 0; i--) {
		for (j = 1; j <= i; j++) {
			if (p->power_tbl[j - 1].cpufreq_power < p->power_tbl[j].cpufreq_power) {
				struct mt_cpu_power_info tmp;

				tmp.cpufreq_khz                 = p->power_tbl[j - 1].cpufreq_khz;
				tmp.cpufreq_ncpu                = p->power_tbl[j - 1].cpufreq_ncpu;
				tmp.cpufreq_power               = p->power_tbl[j - 1].cpufreq_power;

				p->power_tbl[j - 1].cpufreq_khz   = p->power_tbl[j].cpufreq_khz;
				p->power_tbl[j - 1].cpufreq_ncpu  = p->power_tbl[j].cpufreq_ncpu;
				p->power_tbl[j - 1].cpufreq_power = p->power_tbl[j].cpufreq_power;

				p->power_tbl[j].cpufreq_khz     = tmp.cpufreq_khz;
				p->power_tbl[j].cpufreq_ncpu    = tmp.cpufreq_ncpu;
				p->power_tbl[j].cpufreq_power   = tmp.cpufreq_power;
			}
		}
	}

	
	for (i = 0; i < p->nr_opp_tbl * possible_cpu; i++) {
		cpufreq_dbg("[%d] = { .khz = %d, .ncup = %d, .power = %d }\n",
			    p->power_tbl[i].cpufreq_khz,
			    p->power_tbl[i].cpufreq_ncpu,
			    p->power_tbl[i].cpufreq_power
			   );
	}

out:
	FUNC_EXIT(FUNC_LV_LOCAL);

	return ret;
}
#else
static void _power_calculation(struct mt_cpu_dvfs *p, int oppidx, int ncpu)
{
#define CA53_REF_POWER	2286	
#define CA53_REF_FREQ	1690000 
#define CA53_REF_VOLT	100000	

	int p_dynamic = 0, p_leakage = 0, ref_freq, ref_volt;
	int possible_cpu = max_cpu_num;

	FUNC_ENTER(FUNC_LV_HELP);

	p_dynamic = CA53_REF_POWER;
	ref_freq  = CA53_REF_FREQ;
	ref_volt  = CA53_REF_VOLT;

	
#if 0
	p_leakage = mt_spower_get_leakage(MT_SPOWER_CA7, p->opp_tbl[oppidx].cpufreq_volt / 100, 65);
#else
	p_leakage = 262; 
#endif

	p_dynamic = p_dynamic *
		    (p->opp_tbl[oppidx].cpufreq_khz / 1000) / (ref_freq / 1000) *
		    p->opp_tbl[oppidx].cpufreq_volt / ref_volt *
		    p->opp_tbl[oppidx].cpufreq_volt / ref_volt +
		    p_leakage;

	p->power_tbl[NR_MAX_OPP_TBL * (possible_cpu - 1 - ncpu) + oppidx].cpufreq_ncpu  = ncpu + 1;
	p->power_tbl[NR_MAX_OPP_TBL * (possible_cpu - 1 - ncpu) + oppidx].cpufreq_khz   = p->opp_tbl[oppidx].cpufreq_khz;
	p->power_tbl[NR_MAX_OPP_TBL * (possible_cpu - 1 - ncpu) + oppidx].cpufreq_power = p_dynamic * (ncpu + 1) / possible_cpu;

	FUNC_EXIT(FUNC_LV_HELP);
}

static int setup_power_table(struct mt_cpu_dvfs *p)
{
	static const unsigned int pwr_tbl_cgf[NR_MAX_CPU] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	unsigned int pwr_eff_tbl[NR_MAX_OPP_TBL][NR_MAX_CPU];
	unsigned int pwr_eff_num;
	int possible_cpu = max_cpu_num;
	int i, j;
	int ret = 0;

	FUNC_ENTER(FUNC_LV_LOCAL);

	BUG_ON(NULL == p);

	if (p->power_tbl)
		goto out;

	
	memset((void *)pwr_eff_tbl, 0, sizeof(pwr_eff_tbl));
	p->power_tbl = kzalloc(p->nr_opp_tbl * possible_cpu * sizeof(struct mt_cpu_power_info), GFP_KERNEL);

	if (NULL == p->power_tbl) {
		ret = -ENOMEM;
		goto out;
	}

	
	for (i = 0, pwr_eff_num = 0; i < possible_cpu; i++) {
		if (1 == pwr_tbl_cgf[i])
			pwr_eff_num++;
	}

	for (i = 0; i < p->nr_opp_tbl; i++) {
		for (j = 0; j < possible_cpu; j++) {
			if (1 == pwr_tbl_cgf[j])
				pwr_eff_tbl[i][j] = 1;
		}
	}

	p->nr_power_tbl = p->nr_opp_tbl * (possible_cpu - pwr_eff_num);

	
	for (i = 0; i < p->nr_opp_tbl; i++) {
		for (j = 0; j < possible_cpu; j++) {
			if (0 == pwr_eff_tbl[i][j])
				_power_calculation(p, i, j);
		}
	}

	
	for (i = p->nr_opp_tbl * possible_cpu; i > 0; i--) {
		for (j = 1; j <= i; j++) {
			if (p->power_tbl[j - 1].cpufreq_power < p->power_tbl[j].cpufreq_power) {
				struct mt_cpu_power_info tmp;

				tmp.cpufreq_khz                 = p->power_tbl[j - 1].cpufreq_khz;
				tmp.cpufreq_ncpu                = p->power_tbl[j - 1].cpufreq_ncpu;
				tmp.cpufreq_power               = p->power_tbl[j - 1].cpufreq_power;

				p->power_tbl[j - 1].cpufreq_khz   = p->power_tbl[j].cpufreq_khz;
				p->power_tbl[j - 1].cpufreq_ncpu  = p->power_tbl[j].cpufreq_ncpu;
				p->power_tbl[j - 1].cpufreq_power = p->power_tbl[j].cpufreq_power;

				p->power_tbl[j].cpufreq_khz     = tmp.cpufreq_khz;
				p->power_tbl[j].cpufreq_ncpu    = tmp.cpufreq_ncpu;
				p->power_tbl[j].cpufreq_power   = tmp.cpufreq_power;
			}
		}
	}

	max_power_budget = p->power_tbl[0].cpufreq_power;
	cpufreq_info("max_power_budget = %d\n", max_power_budget);

	
	for (i = 0; i < p->nr_opp_tbl * possible_cpu; i++) {
		cpufreq_info("[%d] = { .cpufreq_khz = %d,\t.cpufreq_ncpu = %d,\t.cpufreq_power = %d }\n",
			     i,
			     p->power_tbl[i].cpufreq_khz,
			     p->power_tbl[i].cpufreq_ncpu,
			     p->power_tbl[i].cpufreq_power
			    );
	}

	
		for (j = 0; j < p->nr_power_tbl; j++) {
			if (p->power_tbl[j].cpufreq_khz <
					cpufreq_thermal_floor_limit_table[p->power_tbl[j].cpufreq_ncpu - 1]){
				p->power_tbl[j].cpufreq_khz  =
					p->power_tbl[j-1].cpufreq_khz;
				p->power_tbl[j].cpufreq_ncpu =
					p->power_tbl[j-1].cpufreq_ncpu;
				p->power_tbl[j].cpufreq_power =
					p->power_tbl[j-1].cpufreq_power;
			}
        }


#if 0 
	mtk_cpufreq_register(p->power_tbl, p->nr_power_tbl);
#endif

out:
	FUNC_EXIT(FUNC_LV_LOCAL);

	return ret;
}
#endif

static int _mt_cpufreq_setup_freqs_table(struct cpufreq_policy *policy, struct mt_cpu_freq_info *freqs, int num)
{
	struct mt_cpu_dvfs *p;
	struct cpufreq_frequency_table *table;
	int i, ret = 0;

	FUNC_ENTER(FUNC_LV_LOCAL);

	BUG_ON(NULL == policy);
	BUG_ON(NULL == freqs);

	p = id_to_cpu_dvfs(_get_cpu_dvfs_id(policy->cpu));

	if (NULL == p->freq_tbl_for_cpufreq) {
		table = kzalloc((num + 1) * sizeof(*table), GFP_KERNEL);

		if (NULL == table) {
			ret = -ENOMEM;
			goto out;
		}

		for (i = 0; i < num; i++) {
			table[i].index = i;
			table[i].frequency = freqs[i].cpufreq_khz;
		}

		table[num].index = i; 
		table[num].frequency = CPUFREQ_TABLE_END;

		p->opp_tbl = freqs;
		p->nr_opp_tbl = num;
		p->freq_tbl_for_cpufreq = table;
	}

#ifdef CONFIG_CPU_FREQ
	ret = cpufreq_frequency_table_cpuinfo(policy, p->freq_tbl_for_cpufreq);

	if (!ret)
		cpufreq_frequency_table_get_attr(p->freq_tbl_for_cpufreq, policy->cpu);

#endif

	if (NULL == p->power_tbl)
		p->ops->setup_power_table(p);

out:
	FUNC_EXIT(FUNC_LV_LOCAL);

	return 0;
}

void mt_cpufreq_enable_by_ptpod(enum mt_cpu_dvfs_id id)
{
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(id);

	FUNC_ENTER(FUNC_LV_API);

	BUG_ON(NULL == p);

	p->dvfs_disable_by_ptpod = false;

	if (AllowTurboMode) {
		cpufreq_info("@%s: Turbo mode enabled!\n", __func__);
		p->turbo_mode = 1;
	}

	if (!cpu_dvfs_is_availiable(p)) {
		FUNC_EXIT(FUNC_LV_API);
		return;
	}

	_mt_cpufreq_set(id, p->idx_opp_tbl_for_late_resume);

	FUNC_EXIT(FUNC_LV_API);
}
EXPORT_SYMBOL(mt_cpufreq_enable_by_ptpod);

unsigned int mt_cpufreq_disable_by_ptpod(enum mt_cpu_dvfs_id id)
{
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(id);

	FUNC_ENTER(FUNC_LV_API);

	BUG_ON(NULL == p);

	p->dvfs_disable_by_ptpod = true;

	if (!cpu_dvfs_is_availiable(p)) {
		FUNC_EXIT(FUNC_LV_API);
		return 0;
	}

#if 0 
	{
		struct cpufreq_policy *policy;
		policy = cpufreq_cpu_get(p->cpu_id);

		if (policy) {
			cpufreq_driver_target(policy, cpu_dvfs_get_normal_max_freq(p), CPUFREQ_RELATION_L);
			cpufreq_cpu_put(policy);
		} else
			cpufreq_warn("can't get cpufreq policy to disable %s DVFS\n", p->name);
	}
#else
	p->idx_opp_tbl_for_late_resume = p->idx_opp_tbl;
	_mt_cpufreq_set(id, p->idx_normal_max_opp); 
#endif

	FUNC_EXIT(FUNC_LV_API);

	return cpu_dvfs_get_cur_freq(p);
}
EXPORT_SYMBOL(mt_cpufreq_disable_by_ptpod);

#define THERMAL_LOG_POWER_LIMITED_COUNT	150

void mt_cpufreq_thermal_protect(unsigned int limited_power)
{
	static int log_count_1 = 0; 

	FUNC_ENTER(FUNC_LV_API);

	
	if (log_count_1-- % (THERMAL_LOG_POWER_LIMITED_COUNT + 1) == 0) {
		log_count_1 = THERMAL_LOG_POWER_LIMITED_COUNT;
		cpufreq_dbg("%s(): limited_power = %d\n", __func__, limited_power);
	}

#ifdef CONFIG_CPU_FREQ
	{
		struct cpufreq_policy *policy;
		struct mt_cpu_dvfs *p;
		int possible_cpu;
		int ncpu;
		int found = 0;
		unsigned long flag;
		int i;

		policy = cpufreq_cpu_get(0);    

		if (NULL == policy)
			goto no_policy;

		p = id_to_cpu_dvfs(_get_cpu_dvfs_id(policy->cpu));

		BUG_ON(NULL == p);

		cpufreq_lock(flag);                                     

		
		if (!p->thermal_protect_limited_power)
			p->idx_opp_tbl_for_thermal_thro = p->idx_opp_tbl;

		p->thermal_protect_limited_power = limited_power;
		possible_cpu = max_cpu_num;

		
		if (0 == limited_power) {
			p->limited_max_ncpu = possible_cpu;
			p->limited_max_freq = cpu_dvfs_get_max_freq(p);
			
			p->idx_opp_tbl = p->idx_opp_tbl_for_thermal_thro;
		} else {
			for (ncpu = possible_cpu; ncpu > 0; ncpu--) {
				for (i = 0; i < p->nr_opp_tbl * possible_cpu; i++) {
					if (p->power_tbl[i].cpufreq_power <= limited_power) { 
						p->limited_max_ncpu = p->power_tbl[i].cpufreq_ncpu;
						p->limited_max_freq = p->power_tbl[i].cpufreq_khz;
						found = 1;
						ncpu = 0; 
						break;
					}
				}
			}

			
			if (!found) {
				p->limited_max_ncpu = p->power_tbl[p->nr_power_tbl - 1].cpufreq_ncpu;
				p->limited_max_freq = p->power_tbl[p->nr_power_tbl - 1].cpufreq_khz;
			}
		}

		cpufreq_dbg("found = %d, limited_max_freq = %d, limited_max_ncpu = %d\n", found, p->limited_max_freq, p->limited_max_ncpu);

		cpufreq_unlock(flag);                                   
		hps_set_cpu_num_limit(LIMIT_THERMAL, p->limited_max_ncpu, 0);
		
		_mt_cpufreq_set(MT_CPU_DVFS_LITTLE, -1);
		cpufreq_cpu_put(policy);                                
	}
no_policy:
#endif

	FUNC_EXIT(FUNC_LV_API);
}
EXPORT_SYMBOL(mt_cpufreq_thermal_protect);

void mt_cpufreq_set_ramp_down_count_const(enum mt_cpu_dvfs_id id, int count)
{
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(id);

	BUG_ON(NULL == p);

	p->ramp_down_count_const = count;
}
EXPORT_SYMBOL(mt_cpufreq_set_ramp_down_count_const);

#ifdef CONFIG_CPU_DVFS_RAMP_DOWN
static int _keep_max_freq(struct mt_cpu_dvfs *p, unsigned int freq_old, unsigned int freq_new) 
{
	int ret = 0;

	FUNC_ENTER(FUNC_LV_HELP);

	if (RAMP_DOWN_TIMES < p->ramp_down_count_const)
		p->ramp_down_count_const--;
	else
		p->ramp_down_count_const = RAMP_DOWN_TIMES;

	if (freq_new < freq_old && p->ramp_down_count < p->ramp_down_count_const) {
		ret = 1;
		p->ramp_down_count++;
	} else
		p->ramp_down_count = 0;

	FUNC_ENTER(FUNC_LV_HELP);

	return ret;
}
#endif

int _search_available_freq_idx(struct mt_cpu_dvfs *p, unsigned int target_khz, unsigned int relation) 
{
	int new_opp_idx = -1;
	int i;

	FUNC_ENTER(FUNC_LV_HELP);

	if (CPUFREQ_RELATION_L == relation) {
		for (i = (signed)(p->nr_opp_tbl - 1); i >= 0; i--) {
			if (cpu_dvfs_get_freq_by_idx(p, i) >= target_khz) {
				new_opp_idx = i;
				break;
			}
		}
	} else { 
		for (i = 0; i < (signed)p->nr_opp_tbl; i++) {
			if (cpu_dvfs_get_freq_by_idx(p, i) <= target_khz) {
				new_opp_idx = i;
				break;
			}
		}
	}

	FUNC_EXIT(FUNC_LV_HELP);

	return new_opp_idx;
}

#define THERMAL_LOG_COUNT	200

static int _thermal_limited_verify(struct mt_cpu_dvfs *p, int new_opp_idx)
{
	unsigned int target_khz = cpu_dvfs_get_freq_by_idx(p, new_opp_idx);
	int possible_cpu = 0;
	unsigned int online_cpu = 0;
	int found = 0;
	int i;
	static int log_count_1 = 0; 
	static int log_count_2 = 0; 

	FUNC_ENTER(FUNC_LV_HELP);

	possible_cpu = max_cpu_num; 
	online_cpu = num_online_cpus(); 

	

	
	if (0 == p->thermal_protect_limited_power)
		return new_opp_idx;

	for (i = 0; i < p->nr_opp_tbl * possible_cpu; i++) {
		if (p->power_tbl[i].cpufreq_ncpu == p->limited_max_ncpu
		    && p->power_tbl[i].cpufreq_khz  == p->limited_max_freq
		   )
			break;
	}

	
	if (log_count_1-- % (THERMAL_LOG_COUNT + 1) == 0) {
		log_count_1 = THERMAL_LOG_COUNT;
		cpufreq_dbg("%s(): idx = %d, limited_max_ncpu = %d, limited_max_freq = %d\n", __func__, i, p->limited_max_ncpu, p->limited_max_freq);
	}

	for (; i < p->nr_opp_tbl * possible_cpu; i++) {
		if (p->power_tbl[i].cpufreq_ncpu == online_cpu) {
			if (target_khz >= p->power_tbl[i].cpufreq_khz) {
				found = 1;
				break;
			}
		}
	}

	if (found) {
		target_khz = p->power_tbl[i].cpufreq_khz;

		
		if (log_count_2-- % (THERMAL_LOG_COUNT + 1) == 0) {
			log_count_2 = THERMAL_LOG_COUNT;
			cpufreq_dbg("%s(): freq found, idx = %d, target_khz = %d, online_cpu = %d\n", __func__, i, target_khz, online_cpu);
		}
	} else {
		target_khz = p->limited_max_freq;
		cpufreq_dbg("%s(): freq not found, set to limited_max_freq = %d\n", __func__, target_khz);
	}

	i = _search_available_freq_idx(p, target_khz, CPUFREQ_RELATION_H); 

	FUNC_EXIT(FUNC_LV_HELP);

	return i;
}

#define THERMAL_LOG_OPP_COUNT	150

static unsigned int _calc_new_opp_idx(struct mt_cpu_dvfs *p, int new_opp_idx)
{
	int idx;
	static int log_count_1 = 0; 

	FUNC_ENTER(FUNC_LV_HELP);

	BUG_ON(NULL == p);

	
#ifdef CONFIG_CPU_DVFS_RAMP_DOWN

	if (_keep_max_freq(p, cpu_dvfs_get_cur_freq(p), cpu_dvfs_get_freq_by_idx(p, new_opp_idx))) {
		cpufreq_dbg("%s(): ramp down, idx = %d, freq_old = %d, freq_new = %d\n",
			     __func__,
			     new_opp_idx,
			     cpu_dvfs_get_cur_freq(p),
			     cpu_dvfs_get_freq_by_idx(p, new_opp_idx)
			    );
		new_opp_idx = p->idx_opp_tbl;
	}

#endif

	
	if (p->limited_freq_by_hevc) {
		idx = _search_available_freq_idx(p, p->limited_freq_by_hevc, CPUFREQ_RELATION_L);

		if ((idx != -1) && (new_opp_idx > idx)) {
			new_opp_idx = idx;
		}
	}

#ifdef CONFIG_CPU_DVFS_DOWNGRADE_FREQ

	if (true == p->downgrade_freq_for_ptpod) {
		if (cpu_dvfs_get_freq_by_idx(p, new_opp_idx) > p->downgrade_freq) {
			idx = _search_available_freq_idx(p, p->downgrade_freq, CPUFREQ_RELATION_H);

			if (idx != -1) {
				new_opp_idx = idx;
				cpufreq_dbg("%s(): downgrade freq, idx = %d\n", __func__, new_opp_idx);
			}
		}
	}

#endif 

	
	idx = _thermal_limited_verify(p, new_opp_idx);

	if (idx != -1 && idx != new_opp_idx) {
		new_opp_idx = idx;

		
		if (log_count_1-- % (THERMAL_LOG_OPP_COUNT + 1) == 0) {
			log_count_1 = THERMAL_LOG_OPP_COUNT;
			cpufreq_dbg("%s(): thermal limited freq, idx = %d\n", __func__, new_opp_idx);
		}
	}

	
	if (p->dvfs_disable_by_early_suspend) {
		if (new_opp_idx > p->idx_normal_max_opp)
			new_opp_idx = p->idx_normal_max_opp;

		cpufreq_dbg("%s(): for early suspend, idx = %d\n", __func__, new_opp_idx);
	}

	
	if (p->dvfs_disable_by_suspend)
		new_opp_idx = p->idx_normal_max_opp;

	
#ifdef  CONFIG_CPU_DVFS_POWER_THROTTLING

	if (p->pwr_thro_mode & (PWR_THRO_MODE_BAT_OC_1183MHZ)) {
		if (new_opp_idx < CPU_DVFS_OPPIDX_1183MHZ)
			cpufreq_dbg("%s(): for power throttling = %d\n", __func__, CPU_DVFS_OPPIDX_1183MHZ);

		new_opp_idx = (new_opp_idx < CPU_DVFS_OPPIDX_1183MHZ) ? CPU_DVFS_OPPIDX_1183MHZ : new_opp_idx;
	} else if (p->pwr_thro_mode & (PWR_THRO_MODE_LBAT_1183MHZ | PWR_THRO_MODE_BAT_PER_1183MHZ)) {
		if (new_opp_idx < CPU_DVFS_OPPIDX_1183MHZ)
			cpufreq_dbg("%s(): for power throttling = %d\n", __func__, CPU_DVFS_OPPIDX_1183MHZ);

		new_opp_idx = (new_opp_idx < CPU_DVFS_OPPIDX_1183MHZ) ? CPU_DVFS_OPPIDX_1183MHZ : new_opp_idx;
	}

#endif

	
	if (p->limited_max_freq_by_user) {
		idx = _search_available_freq_idx(p, p->limited_max_freq_by_user, CPUFREQ_RELATION_H);

		if (idx != -1 && new_opp_idx < idx) {
			new_opp_idx = idx;
			cpufreq_dbg("%s(): limited max freq by user, idx = %d\n", __func__, new_opp_idx);
		}
	}

	
	if (p->dvfs_disable_by_ptpod) {
		
		idx = _search_available_freq_idx(p, CPU_DVFS_FREQ5, CPUFREQ_RELATION_L);

		if (idx != -1) {
			new_opp_idx = idx;
			cpufreq_info("%s(): for ptpod init, idx = %d\n", __func__, new_opp_idx);
		}
	}

#ifdef CONFIG_CPU_DVFS_AEE_RR_REC
	aee_rr_rec_cpu_dvfs_oppidx((aee_rr_curr_cpu_dvfs_oppidx() & 0xF0) | new_opp_idx);
#endif

	FUNC_EXIT(FUNC_LV_HELP);

	return new_opp_idx;
}

#ifdef  CONFIG_CPU_DVFS_POWER_THROTTLING
static void bat_per_protection_powerlimit(BATTERY_PERCENT_LEVEL level)
{
	struct mt_cpu_dvfs *p;
	int i;
	unsigned long flags;

	for_each_cpu_dvfs(i, p) {
		if (!cpu_dvfs_is_availiable(p))
			continue;

		cpufreq_lock(flags);

		if (!p->pwr_thro_mode)
			p->idx_opp_tbl_for_pwr_thro = p->idx_opp_tbl;

		switch (level) {
		case BATTERY_PERCENT_LEVEL_1:
			
			p->pwr_thro_mode |= PWR_THRO_MODE_BAT_PER_1183MHZ;
			break;

		default:
			
			p->pwr_thro_mode &= ~PWR_THRO_MODE_BAT_PER_1183MHZ;
			break;
		}

		if (!p->pwr_thro_mode)
			p->idx_opp_tbl = p->idx_opp_tbl_for_pwr_thro;

		cpufreq_unlock(flags);

		_mt_cpufreq_set(MT_CPU_DVFS_LITTLE, p->idx_opp_tbl);

		switch (level) {
		case BATTERY_PERCENT_LEVEL_1:
			
			hps_set_cpu_num_limit(LIMIT_LOW_BATTERY, 4, 0); 
			break;

		default:
			
			hps_set_cpu_num_limit(LIMIT_LOW_BATTERY, max_cpu_num, 0); 
			break;
		}
	}
}

static void bat_oc_protection_powerlimit(BATTERY_OC_LEVEL level)
{
	struct mt_cpu_dvfs *p;
	int i;
	unsigned long flags;

	for_each_cpu_dvfs(i, p) {
		if (!cpu_dvfs_is_availiable(p)) 
			continue;

		cpufreq_lock(flags);

		if (!p->pwr_thro_mode)
			p->idx_opp_tbl_for_pwr_thro = p->idx_opp_tbl;

		switch (level) {
		case BATTERY_OC_LEVEL_1:
			
			p->pwr_thro_mode |= PWR_THRO_MODE_BAT_OC_1183MHZ;
			break;

		default:
			
			p->pwr_thro_mode &= ~PWR_THRO_MODE_BAT_OC_1183MHZ;
			break;
		}

		if (!p->pwr_thro_mode)
			p->idx_opp_tbl = p->idx_opp_tbl_for_pwr_thro;

		cpufreq_unlock(flags);

		_mt_cpufreq_set(MT_CPU_DVFS_LITTLE, p->idx_opp_tbl);
	}
}

void Lbat_protection_powerlimit(LOW_BATTERY_LEVEL level)
{
	struct mt_cpu_dvfs *p;
	int i;
	unsigned long flags;

	for_each_cpu_dvfs(i, p) {
		if (!cpu_dvfs_is_availiable(p))
			continue;

		cpufreq_lock(flags);

		if (!p->pwr_thro_mode)
			p->idx_opp_tbl_for_pwr_thro = p->idx_opp_tbl;

		switch (level) {
		case LOW_BATTERY_LEVEL_1:
			
			p->pwr_thro_mode |= PWR_THRO_MODE_LBAT_1183MHZ;
			break;

		case LOW_BATTERY_LEVEL_2:
			
			p->pwr_thro_mode |= PWR_THRO_MODE_LBAT_1183MHZ;
			break;

		default:
			
			p->pwr_thro_mode &= ~PWR_THRO_MODE_LBAT_1183MHZ;
			break;
		}

		if (!p->pwr_thro_mode)
			p->idx_opp_tbl = p->idx_opp_tbl_for_pwr_thro;

		cpufreq_unlock(flags);

		_mt_cpufreq_set(MT_CPU_DVFS_LITTLE , p->idx_opp_tbl);

		switch (level) {
		case LOW_BATTERY_LEVEL_1:
			
			hps_set_cpu_num_limit(LIMIT_LOW_BATTERY, 4, 0); 
			break;

		case LOW_BATTERY_LEVEL_2:
			
			hps_set_cpu_num_limit(LIMIT_LOW_BATTERY, 4, 0); 
			break;

		default:
			
			hps_set_cpu_num_limit(LIMIT_LOW_BATTERY, max_cpu_num, 0); 
			break;
		}
	}
}
#endif

unsigned int mt_get_clk_mem_sel(void)
{
	unsigned int val;

	
	
	
	
	
	val = (*(volatile unsigned int *)(CLK_CFG_0));
	val = (val >> 8) & 0x3;

	return val;
}
EXPORT_SYMBOL(mt_get_clk_mem_sel);

static int _mt_cpufreq_verify(struct cpufreq_policy *policy)
{
	struct mt_cpu_dvfs *p;
	int ret = 0; 

	FUNC_ENTER(FUNC_LV_MODULE);

	p = id_to_cpu_dvfs(_get_cpu_dvfs_id(policy->cpu));

	BUG_ON(NULL == p);

#ifdef CONFIG_CPU_FREQ
	ret = cpufreq_frequency_table_verify(policy, p->freq_tbl_for_cpufreq);
#endif

	FUNC_EXIT(FUNC_LV_MODULE);

	return ret;
}

static int _mt_cpufreq_target(struct cpufreq_policy *policy, unsigned int target_freq, unsigned int relation)
{
	
	
	unsigned int new_opp_idx;

	enum mt_cpu_dvfs_id id = _get_cpu_dvfs_id(policy->cpu);

	
	int ret = 0; 

	FUNC_ENTER(FUNC_LV_MODULE);

	if (policy->cpu >= max_cpu_num
	    || cpufreq_frequency_table_target(policy, id_to_cpu_dvfs(id)->freq_tbl_for_cpufreq, target_freq, relation, &new_opp_idx)
	    || (id_to_cpu_dvfs(id) && id_to_cpu_dvfs(id)->dvfs_disable_by_procfs)
	   )
		return -EINVAL;

	
	
	

	
	
	
	

	

#ifdef CONFIG_CPU_DVFS_AEE_RR_REC
	aee_rr_rec_cpu_dvfs_status(aee_rr_curr_cpu_dvfs_status() | (1 << CPU_DVFS_LITTLE_IS_DOING_DVFS));
#endif

	_mt_cpufreq_set(id, new_opp_idx);

#ifdef CONFIG_CPU_DVFS_AEE_RR_REC
	aee_rr_rec_cpu_dvfs_status(aee_rr_curr_cpu_dvfs_status() & ~(1 << CPU_DVFS_LITTLE_IS_DOING_DVFS));
#endif

	

	
	
	
	

	FUNC_EXIT(FUNC_LV_MODULE);

	return ret;
}

static int _mt_cpufreq_init(struct cpufreq_policy *policy)
{
	int ret = -EINVAL;

	FUNC_ENTER(FUNC_LV_MODULE);

	max_cpu_num = num_possible_cpus();

	if (policy->cpu >= max_cpu_num) 
		return -EINVAL;

	cpufreq_dbg("@%s: max_cpu_num: %d\n", __func__, max_cpu_num);

	policy->shared_type = CPUFREQ_SHARED_TYPE_ANY;
	cpumask_setall(policy->cpus);

	policy->cpuinfo.transition_latency = 1000;

	{
#define DORMANT_MODE_VOLT   80000

		enum mt_cpu_dvfs_id id = _get_cpu_dvfs_id(policy->cpu);
		struct mt_cpu_dvfs *p = id_to_cpu_dvfs(id);
		unsigned int lv = _mt_cpufreq_get_cpu_level();
		struct opp_tbl_info *opp_tbl_info = &opp_tbls[CPU_LV_TO_OPP_IDX(lv)];
		unsigned int lock_code = get_devinfo_with_index(23);

		if ((lock_code & 0x1) == 0) {
			opp_tbl_info->opp_tbl[0].cpufreq_volt = 112500;
			opp_tbl_info->opp_tbl[0].cpufreq_volt_org = 112500;
		}

		BUG_ON(NULL == p);
		BUG_ON(!(lv == CPU_LEVEL_0 || lv == CPU_LEVEL_1 || lv == CPU_LEVEL_2));

		p->cpu_level = lv;

		
		
		

		pwrap_write(0x8490, 0x1);
		pwrap_write(0x8424, 0x0);

		ret = _mt_cpufreq_setup_freqs_table(policy,
						    opp_tbl_info->opp_tbl,
						    opp_tbl_info->size
						   );

		policy->cpuinfo.max_freq = cpu_dvfs_get_max_freq(id_to_cpu_dvfs(id));
		policy->cpuinfo.min_freq = cpu_dvfs_get_min_freq(id_to_cpu_dvfs(id));

		policy->cur = _mt_cpufreq_get_cur_phy_freq(id); 
		policy->max = cpu_dvfs_get_max_freq(id_to_cpu_dvfs(id));
		policy->min = cpu_dvfs_get_min_freq(id_to_cpu_dvfs(id));

		if (_sync_opp_tbl_idx(p) >= 0) 
			p->idx_normal_max_opp = p->idx_opp_tbl;

		
		if (cpu_dvfs_is_extbuck_valid())
			_restore_default_volt(p);

		_set_no_limited(p);
#ifdef CONFIG_CPU_DVFS_DOWNGRADE_FREQ
		_init_downgrade(p, _mt_cpufreq_get_cpu_level());
#endif
#ifdef  CONFIG_CPU_DVFS_POWER_THROTTLING
		register_battery_percent_notify(&bat_per_protection_powerlimit, BATTERY_PERCENT_PRIO_CPU_L);
		register_battery_oc_notify(&bat_oc_protection_powerlimit, BATTERY_OC_PRIO_CPU_L);
		register_low_battery_notify(&Lbat_protection_powerlimit, LOW_BATTERY_PRIO_CPU_L);
#endif
	}

	if (ret)
		cpufreq_err("failed to setup frequency table\n");

	FUNC_EXIT(FUNC_LV_MODULE);

	return ret;
}

static unsigned int _mt_cpufreq_get(unsigned int cpu)
{
	struct mt_cpu_dvfs *p;

	FUNC_ENTER(FUNC_LV_MODULE);

	p = id_to_cpu_dvfs(_get_cpu_dvfs_id(cpu));

	BUG_ON(NULL == p);

	FUNC_EXIT(FUNC_LV_MODULE);

	return cpu_dvfs_get_cur_freq(p);
}

static bool _allow_dpidle_ctrl_vproc = false;

bool mt_cpufreq_earlysuspend_status_get(void)
{
	return _allow_dpidle_ctrl_vproc;
}
EXPORT_SYMBOL(mt_cpufreq_earlysuspend_status_get);

#ifdef CONFIG_HAS_EARLYSUSPEND
static void _mt_cpufreq_early_suspend(struct early_suspend *h)
{
	struct cpufreq_policy *policy;
	struct mt_cpu_dvfs *p;
	int i;

	FUNC_ENTER(FUNC_LV_MODULE);

	

	

	for_each_cpu_dvfs(i, p) {
		if (!cpu_dvfs_is_availiable(p))
			continue;

		p->dvfs_disable_by_early_suspend = true;

		p->idx_opp_tbl_for_late_resume = p->idx_opp_tbl;

#ifdef CONFIG_CPU_FREQ
		policy = cpufreq_cpu_get(p->cpu_id);

		if (policy) {
			cpufreq_driver_target(policy, cpu_dvfs_get_normal_max_freq(p), CPUFREQ_RELATION_L);
			cpufreq_cpu_put(policy);
		}

#endif
	}

	_allow_dpidle_ctrl_vproc = true;

	FUNC_EXIT(FUNC_LV_MODULE);
}

static void _mt_cpufreq_late_resume(struct early_suspend *h)
{
	struct cpufreq_policy *policy;
	struct mt_cpu_dvfs *p;
	int i;

	FUNC_ENTER(FUNC_LV_MODULE);

	_allow_dpidle_ctrl_vproc = false;

	for_each_cpu_dvfs(i, p) {
		if (!cpu_dvfs_is_availiable(p))
			continue;

		p->dvfs_disable_by_early_suspend = false;

#ifdef CONFIG_CPU_FREQ
		policy = cpufreq_cpu_get(p->cpu_id);

		if (policy) {
			cpufreq_driver_target(policy, cpu_dvfs_get_freq_by_idx(p, p->idx_opp_tbl_for_late_resume), CPUFREQ_RELATION_L);
			cpufreq_cpu_put(policy);
		}

#endif
	}

	

	

	FUNC_EXIT(FUNC_LV_MODULE);
}

static struct early_suspend _mt_cpufreq_early_suspend_handler = {
	.level    = EARLY_SUSPEND_LEVEL_DISABLE_FB + 200,
	.suspend  = _mt_cpufreq_early_suspend,
	.resume   = _mt_cpufreq_late_resume,
};
#endif 

#ifdef CONFIG_CPU_FREQ
static struct freq_attr *_mt_cpufreq_attr[] = {
	&cpufreq_freq_attr_scaling_available_freqs,
	NULL,
};

static struct cpufreq_driver _mt_cpufreq_driver = {
	.verify = _mt_cpufreq_verify,
	.target = _mt_cpufreq_target,
	.init   = _mt_cpufreq_init,
	.get    = _mt_cpufreq_get,
	.name   = "mt-cpufreq",
	.attr   = _mt_cpufreq_attr,
};
#endif

static int _mt_cpufreq_suspend(struct device *dev)
{
	
	struct mt_cpu_dvfs *p;
	int i;

	FUNC_ENTER(FUNC_LV_MODULE);

	

	for_each_cpu_dvfs(i, p) {
		if (!cpu_dvfs_is_availiable(p))
			continue;

		p->dvfs_disable_by_suspend = true;

#if 0 
		policy = cpufreq_cpu_get(p->cpu_id);

		if (policy) {
			cpufreq_driver_target(policy, cpu_dvfs_get_normal_max_freq(p), CPUFREQ_RELATION_L);
			cpufreq_cpu_put(policy);
		}

#else
		_mt_cpufreq_set(MT_CPU_DVFS_LITTLE, p->idx_normal_max_opp); 
#endif
	}

	FUNC_EXIT(FUNC_LV_MODULE);

	return 0;
}

static int _mt_cpufreq_resume(struct device *dev)
{
	struct mt_cpu_dvfs *p;
	int i;

	FUNC_ENTER(FUNC_LV_MODULE);

	

	for_each_cpu_dvfs(i, p) {
		if (!cpu_dvfs_is_availiable(p))
			continue;

		p->dvfs_disable_by_suspend = false;
	}

	FUNC_EXIT(FUNC_LV_MODULE);

	return 0;
}

static int _mt_cpufreq_pm_restore_early(struct device *dev)  
{
	FUNC_ENTER(FUNC_LV_MODULE);

	_mt_cpufreq_sync_opp_tbl_idx();

	FUNC_EXIT(FUNC_LV_MODULE);

	return 0;
}

static int _mt_cpufreq_pdrv_probe(struct platform_device *pdev)
{
	FUNC_ENTER(FUNC_LV_MODULE);

	

	if (pw.addr[0].cmd_addr == 0)
		_mt_cpufreq_pmic_table_init();

# if 0 
	
	mt_spower_init();
#endif

#ifdef CONFIG_CPU_DVFS_AEE_RR_REC
	_mt_cpufreq_aee_init();
#endif

	
#ifdef CONFIG_HAS_EARLYSUSPEND
	register_early_suspend(&_mt_cpufreq_early_suspend_handler);
#endif

	
	mt_cpufreq_set_pmic_phase(PMIC_WRAP_PHASE_NORMAL);
#if 0 
	
	{
		struct mt_cpu_dvfs *p;
		int i;

		for_each_cpu_dvfs(i, p) {
			if (!cpu_dvfs_is_availiable(p))
				continue;

			_restore_default_volt(p);

			if (_sync_opp_tbl_idx(p) >= 0)
				p->idx_normal_max_opp = p->idx_opp_tbl;

			_set_no_limited(p);

#if defined(CONFIG_CPU_DVFS_DOWNGRADE_FREQ)
			_init_downgrade(p, read_efuse_cpu_speed());
#endif
		}
	}
#endif

#ifdef CONFIG_CPU_FREQ
	cpufreq_register_driver(&_mt_cpufreq_driver);
#endif
	register_hotcpu_notifier(&turbo_mode_cpu_notifier); 

	FUNC_EXIT(FUNC_LV_MODULE);

	return 0;
}

static int _mt_cpufreq_pdrv_remove(struct platform_device *pdev)
{
	FUNC_ENTER(FUNC_LV_MODULE);

	unregister_hotcpu_notifier(&turbo_mode_cpu_notifier); 
#ifdef CONFIG_CPU_FREQ
	cpufreq_unregister_driver(&_mt_cpufreq_driver);
#endif

	FUNC_EXIT(FUNC_LV_MODULE);

	return 0;
}

static const struct dev_pm_ops _mt_cpufreq_pm_ops = {
	.suspend	= _mt_cpufreq_suspend,
	.resume		= _mt_cpufreq_resume,
	.restore_early	= _mt_cpufreq_pm_restore_early,
	.freeze		= _mt_cpufreq_suspend,
	.thaw		= _mt_cpufreq_resume,
	.restore	= _mt_cpufreq_resume,
};

struct platform_device _mt_cpufreq_pdev = {
	.name   = "mt-cpufreq",
	.id     = -1,
};

static struct platform_driver _mt_cpufreq_pdrv = {
	.probe      = _mt_cpufreq_pdrv_probe,
	.remove     = _mt_cpufreq_pdrv_remove,
	.driver     = {
		.name   = "mt-cpufreq",
		.pm     = &_mt_cpufreq_pm_ops,
		.owner  = THIS_MODULE,
	},
};

#ifndef __KERNEL__
int mt_cpufreq_pdrv_probe(void)
{
	static struct cpufreq_policy policy;

	_mt_cpufreq_pdrv_probe(NULL);

	policy.cpu = cpu_dvfs[MT_CPU_DVFS_LITTLE].cpu_id;
	_mt_cpufreq_init(&policy);

	return 0;
}

int mt_cpufreq_set_opp_volt(enum mt_cpu_dvfs_id id, int idx)
{
	int ret = 0;
	static struct opp_tbl_info *info;
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(id);

	info = &opp_tbls[CPU_LV_TO_OPP_IDX(p->cpu_level)];

	if (idx >= info->size)
		return -1;

	return _set_cur_volt_locked(p, info->opp_tbl[idx].cpufreq_volt);
}

int mt_cpufreq_set_freq(enum mt_cpu_dvfs_id id, int idx)
{
	unsigned int cur_freq;
	unsigned int target_freq;
	int ret;
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(id);

	cur_freq = p->ops->get_cur_phy_freq(p);
	target_freq = cpu_dvfs_get_freq_by_idx(p, idx);

#ifdef CONFIG_CPU_FREQ
	ret = _cpufreq_set_locked(p, cur_freq, target_freq, policy);
#else
	ret = _cpufreq_set_locked(p, cur_freq, target_freq, NULL);
#endif

	if (ret < 0)
		return ret;

	return target_freq;
}

#include "dvfs.h"


#define CA15L_CONFIG_BASE (0x10200200)

#define IR_ROSC_CTL             (MCUCFG_BASE + 0x030)
#define pminit_write(addr, val) mt65xx_reg_sync_writel((val), ((void *)addr))

static unsigned int _mt_get_cpu_freq(enum top_ckmuxsel sel)
{
	int output = 0;
	unsigned int temp, clk26cali_0, clk_cfg_8, clk_misc_cfg_1, clk26cali_1;
	unsigned int top_ckmuxsel, top_ckdiv1, ir_rosc_ctl;
	unsigned int ckdiv1;

	clk26cali_0 = DRV_Reg32(CLK26CALI_0);
	pminit_write(CLK26CALI_0, clk26cali_0 | 0x80); 

	clk_misc_cfg_1 = DRV_Reg32(CLK_MISC_CFG_1);
	pminit_write(CLK_MISC_CFG_1, 0xFFFFFF00); 

	clk_cfg_8 = DRV_Reg32(CLK_CFG_8);
	pminit_write(CLK_CFG_8, (46 << 8)); 

	top_ckmuxsel = DRV_Reg32(TOP_CKMUXSEL);
	pminit_write(TOP_CKMUXSEL, (top_ckmuxsel & 0xFFFFFFFC) | sel);

	top_ckdiv1 = DRV_Reg32(TOP_CKDIV1);
	ckdiv1 = _GET_BITS_VAL_(4 : 0, top_ckdiv1);
	pminit_write(TOP_CKDIV1, (top_ckdiv1 & 0xFFFFFFE0) | 0xb);

	ir_rosc_ctl = DRV_Reg32(IR_ROSC_CTL);
	pminit_write(IR_ROSC_CTL, ir_rosc_ctl | 0x08100000);

	temp = DRV_Reg32(CLK26CALI_0);
	pminit_write(CLK26CALI_0, temp | 0x1); 

	
	while (DRV_Reg32(CLK26CALI_0) & 0x1) {
		printf("wait for frequency meter finish, CLK26CALI = 0x%x\n", DRV_Reg32(CLK26CALI_0));
		
	}

	temp = DRV_Reg32(CLK26CALI_1) & 0xFFFF;

	output = ((temp * 26000) / 1024) * 4; 
	output = _cpu_freq_calc(output, ckdiv1);

	pminit_write(CLK_CFG_8, clk_cfg_8);
	pminit_write(CLK_MISC_CFG_1, clk_misc_cfg_1);
	pminit_write(CLK26CALI_0, clk26cali_0);
	pminit_write(TOP_CKMUXSEL, top_ckmuxsel);
	pminit_write(TOP_CKDIV1, top_ckdiv1);
	pminit_write(IR_ROSC_CTL, ir_rosc_ctl);

	

	return output;
}

unsigned int dvfs_get_cpu_freq(enum mt_cpu_dvfs_id id, enum top_ckmuxsel sel)
{
	
	return (MT_CPU_DVFS_LITTLE == id) ? _mt_get_cpu_freq(sel) : 0;
}

void dvfs_set_cpu_freq_FH(enum mt_cpu_dvfs_id id, int freq)
{
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(id);
	int idx;

	if (!p) {
		cpufreq_err("%s(%d, %d), id is wrong\n", __func__, id, freq);
		return;
	}

	idx = _search_available_freq_idx(p, freq, CPUFREQ_RELATION_H);

	if (-1 == idx) {
		cpufreq_err("%s(%d, %d), freq is wrong\n", __func__, id, freq);
		return;
	}

	mt_cpufreq_set_freq(id, idx);
}

unsigned int cpu_frequency_output_slt(enum mt_cpu_dvfs_id id, enum top_ckmuxsel sel)
{
	return (MT_CPU_DVFS_LITTLE == id) ? _mt_get_cpu_freq(sel) : 0;
}

void dvfs_set_cpu_volt(enum mt_cpu_dvfs_id id, int volt)  
{
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(id);

	cpufreq_dbg("%s(%d, %d)\n", __func__, id, volt);

	if (!p) {
		cpufreq_err("%s(%d, %d), id is wrong\n", __func__, id, volt);
		return;
	}

	if (_set_cur_volt_locked(p, volt))
		cpufreq_err("%s(%d, %d), set volt fail\n", __func__, id, volt);

	cpufreq_dbg("%s(%d, %d) Vproc = %d, Vsram = %d\n",
		    __func__,
		    id,
		    volt,
		    p->ops->get_cur_volt(p),
		    get_cur_vsram(p)
		   );
}

void dvfs_set_gpu_volt(int pmic_val)
{
	cpufreq_dbg("%s(%d)\n", __func__, pmic_val);
	mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_NORMAL, IDX_NM_VGPU, pmic_val);
	mt_cpufreq_apply_pmic_cmd(IDX_NM_VGPU);
}
#if 0
void dvfs_set_vcore_ao_volt(int pmic_val)
{
	cpufreq_dbg("%s(%d)\n", __func__, pmic_val);
	mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_NORMAL, IDX_NM_VCORE, pmic_val);
	mt_cpufreq_apply_pmic_cmd(IDX_NM_VCORE);
}
#endif
void dvfs_set_vcore_pdn_volt(int pmic_val)
{
	cpufreq_dbg("%s(%d)\n", __func__, pmic_val);
	mt_cpufreq_set_pmic_phase(PMIC_WRAP_PHASE_DEEPIDLE);
	mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_DEEPIDLE, IDX_DI_VCORE_PDN_NORMAL, pmic_val);
	mt_cpufreq_apply_pmic_cmd(IDX_DI_VCORE_PDN_NORMAL);
	mt_cpufreq_set_pmic_phase(PMIC_WRAP_PHASE_SODI);
	mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_SODI, IDX_SO_VCORE_PDN_NORMAL, pmic_val);
	mt_cpufreq_apply_pmic_cmd(IDX_SO_VCORE_PDN_NORMAL);
	mt_cpufreq_set_pmic_phase(PMIC_WRAP_PHASE_NORMAL);
}

void dvfs_set_vlte_volt(int pmic_val)
{
	cpufreq_dbg("%s(%d)\n", __func__, pmic_val);
	mt_cpufreq_set_pmic_phase(PMIC_WRAP_PHASE_DEEPIDLE);
	mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_DEEPIDLE, IDX_DI_VPROC_CA7_NORMAL, pmic_val);
	mt_cpufreq_apply_pmic_cmd(IDX_DI_VPROC_CA7_NORMAL);
	mt_cpufreq_set_pmic_phase(PMIC_WRAP_PHASE_SODI);
	mt_cpufreq_set_pmic_cmd(PMIC_WRAP_PHASE_SODI, IDX_SO_VPROC_CA7_NORMAL, pmic_val);
	mt_cpufreq_apply_pmic_cmd(IDX_SO_VPROC_CA7_NORMAL);
	mt_cpufreq_set_pmic_phase(PMIC_WRAP_PHASE_NORMAL);
}
static unsigned int vcpu_backup;
static unsigned int vlte_backup;
static unsigned int vgpu_backup;
static unsigned int vcore_pdn_backup;

typedef enum {
	PTP_CTRL_CPU   	= 0,
	PTP_CTRL_LTE   	= 1,
	PTP_CTRL_GPU   	= 2,
	PTP_CTRL_SOC   	= 3,
	PTP_CTRL_ALL    = 4,
	NR_PTP_CTRL,
} ptp_ctrl_id;

void dvfs_disable_by_ptpod(int id)
{
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(MT_CPU_DVFS_LITTLE);

	cpufreq_dbg("%s()\n", __func__); 

	
	switch (id) {
	case PTP_CTRL_CPU:
		vcpu_backup = cpu_dvfs_get_cur_volt(p);
		dvfs_set_cpu_volt(MT_CPU_DVFS_LITTLE, 100000);    
		break;

	case PTP_CTRL_GPU:
		pmic_read_interface(PMIC_ADDR_VGPU_VOSEL_ON, &vgpu_backup, 0x7F, 0);
		dvfs_set_gpu_volt(VOLT_TO_PMIC_VAL(100000));      
		break;

	case PTP_CTRL_LTE:
		pmic_read_interface(PMIC_ADDR_VPROC_CA7_VOSEL_ON, &vlte_backup, 0x7F, 0);
		dvfs_set_vlte_volt(VOLT_TO_PMIC_VAL(100000));      
		break;

	case PTP_CTRL_SOC:
		
		pmic_read_interface(PMIC_ADDR_VCORE_PDN_VOSEL_ON, &vcore_pdn_backup, 0x7F, 0);
		
		dvfs_set_vcore_pdn_volt(VOLT_TO_PMIC_VAL(112500)); 
		break;

	case PTP_CTRL_ALL:
		vcpu_backup = cpu_dvfs_get_cur_volt(p);
		pmic_read_interface(PMIC_ADDR_VPROC_CA7_VOSEL_ON, &vlte_backup, 0x7F, 0);
		pmic_read_interface(PMIC_ADDR_VGPU_VOSEL_ON, &vgpu_backup, 0x7F, 0);
		
		pmic_read_interface(PMIC_ADDR_VCORE_PDN_VOSEL_ON, &vcore_pdn_backup, 0x7F, 0);
		dvfs_set_cpu_volt(MT_CPU_DVFS_LITTLE, 100000);    
		dvfs_set_vlte_volt(VOLT_TO_PMIC_VAL(100000));      
		dvfs_set_gpu_volt(VOLT_TO_PMIC_VAL(100000));      
		
		dvfs_set_vcore_pdn_volt(VOLT_TO_PMIC_VAL(100000)); 
		break;

	default:
		break;
	}
}

void dvfs_enable_by_ptpod(int id)
{
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(MT_CPU_DVFS_LITTLE);

	cpufreq_dbg("%s()\n", __func__); 

	switch (id) {
	case PTP_CTRL_CPU:
		dvfs_set_cpu_volt(MT_CPU_DVFS_LITTLE, vcpu_backup);
		break;

	case PTP_CTRL_LTE:
		dvfs_set_vlte_volt(vlte_backup);
		break;

	case PTP_CTRL_GPU:
		dvfs_set_gpu_volt(vgpu_backup);
		break;

	case PTP_CTRL_SOC:
		
		dvfs_set_vcore_pdn_volt(vcore_pdn_backup);
		break;

	case PTP_CTRL_ALL:
		dvfs_set_cpu_volt(MT_CPU_DVFS_LITTLE, vcpu_backup);
		dvfs_set_vlte_volt(vlte_backup);
		dvfs_set_gpu_volt(vgpu_backup);
		
		dvfs_set_vcore_pdn_volt(vcore_pdn_backup);
		break;

	default:
		break;
	}
}
#endif 

#ifdef CONFIG_PROC_FS

static char *_copy_from_user_for_proc(const char __user *buffer, size_t count)
{
	char *buf = (char *)__get_free_page(GFP_USER);

	if (!buf)
		return NULL;

	if (count >= PAGE_SIZE)
		goto out;

	if (copy_from_user(buf, buffer, count))
		goto out;

	buf[count] = '\0';

	return buf;

out:
	free_page((unsigned long)buf);

	return NULL;
}

static int cpufreq_debug_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "cpufreq debug (log level) = %d\n", func_lv_mask);

	return 0;
}

static ssize_t cpufreq_debug_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
	unsigned int dbg_lv;

	char *buf = _copy_from_user_for_proc(buffer, count);

	if (!buf)
		return -EINVAL;

	if (sscanf(buf, "%d", &dbg_lv) == 1)
		func_lv_mask = dbg_lv;
	else
		cpufreq_err("echo dbg_lv (dec) > /proc/cpufreq/cpufreq_debug\n");

	free_page((unsigned long)buf);
	return count;
}

static int cpufreq_downgrade_freq_info_proc_show(struct seq_file *m, void *v)
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)m->private;

	seq_printf(m, "downgrade_freq_counter_limit = %d\n"
		   "ptpod_temperature_limit_1 = %d\n"
		   "ptpod_temperature_limit_2 = %d\n"
		   "ptpod_temperature_time_1 = %d\n"
		   "ptpod_temperature_time_2 = %d\n"
		   "downgrade_freq_counter_return_limit 1 = %d\n"
		   "downgrade_freq_counter_return_limit 2 = %d\n"
		   "over_max_cpu = %d\n",
		   p->downgrade_freq_counter_limit,
		   p->ptpod_temperature_limit_1,
		   p->ptpod_temperature_limit_2,
		   p->ptpod_temperature_time_1,
		   p->ptpod_temperature_time_2,
		   p->ptpod_temperature_limit_1 * p->ptpod_temperature_time_1,
		   p->ptpod_temperature_limit_2 * p->ptpod_temperature_time_2,
		   p->over_max_cpu
		  );

	return 0;
}

static int cpufreq_downgrade_freq_counter_limit_proc_show(struct seq_file *m, void *v)
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)m->private;

	seq_printf(m, "%d\n", p->downgrade_freq_counter_limit);

	return 0;
}

static ssize_t cpufreq_downgrade_freq_counter_limit_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)PDE_DATA(file_inode(file));
	int downgrade_freq_counter_limit;

	char *buf = _copy_from_user_for_proc(buffer, count);

	if (!buf)
		return -EINVAL;

	if (sscanf(buf, "%d", &downgrade_freq_counter_limit) == 1)
		p->downgrade_freq_counter_limit = downgrade_freq_counter_limit;
	else
		cpufreq_err("echo downgrade_freq_counter_limit (dec) > /proc/cpufreq/cpufreq_downgrade_freq_counter_limit\n");

	free_page((unsigned long)buf);
	return count;
}

static int cpufreq_downgrade_freq_counter_return_limit_proc_show(struct seq_file *m, void *v)
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)m->private;

	seq_printf(m, "%d\n", p->downgrade_freq_counter_return_limit);

	return 0;
}

static ssize_t cpufreq_downgrade_freq_counter_return_limit_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)PDE_DATA(file_inode(file));
	int downgrade_freq_counter_return_limit;

	char *buf = _copy_from_user_for_proc(buffer, count);

	if (!buf)
		return -EINVAL;

	if (sscanf(buf, "%d", &downgrade_freq_counter_return_limit) == 1)
		p->downgrade_freq_counter_return_limit = downgrade_freq_counter_return_limit; 
	else
		cpufreq_err("echo downgrade_freq_counter_return_limit (dec) > /proc/cpufreq/cpufreq_downgrade_freq_counter_return_limit\n");

	free_page((unsigned long)buf);
	return count;
}

#include <linux/sched_clock.h>

static unsigned long _delay_us;
static unsigned long _delay_us_buf;

static int cpufreq_fftt_test_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%lu\n", _delay_us);

	if (_delay_us < _delay_us_buf)
		cpufreq_err("@%s(), %lu < %lu, loops_per_jiffy = %lu\n", __func__, _delay_us, _delay_us_buf, loops_per_jiffy);

	return 0;
}

static ssize_t cpufreq_fftt_test_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
	char *buf = _copy_from_user_for_proc(buffer, count);

	if (!buf)
		return -EINVAL;

	if (sscanf(buf, "%lu", &_delay_us_buf) == 1) {
		unsigned long start;

		start = (unsigned long)sched_clock();
		udelay(_delay_us_buf);
		_delay_us = ((unsigned long)sched_clock() - start) / 1000;

		cpufreq_ver("@%s(%lu), _delay_us = %lu, loops_per_jiffy = %lu\n", __func__, _delay_us_buf, _delay_us, loops_per_jiffy);
	}

	free_page((unsigned long)buf);

	return count;
}

static int cpufreq_stress_test_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%d\n", do_dvfs_stress_test);

	return 0;
}

static ssize_t cpufreq_stress_test_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
	unsigned int do_stress;

	char *buf = _copy_from_user_for_proc(buffer, count);

	if (!buf)
		return -EINVAL;

	if (sscanf(buf, "%d", &do_stress) == 1)
		do_dvfs_stress_test = do_stress;
	else
		cpufreq_err("echo 0/1 > /proc/cpufreq/cpufreq_stress_test\n");

	free_page((unsigned long)buf);
	return count;
}

static int cpufreq_limited_by_hevc_proc_show(struct seq_file *m, void *v)
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)m->private;

	seq_printf(m, "%d\n", p->limited_freq_by_hevc);

	return 0;
}

static ssize_t cpufreq_limited_by_hevc_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)PDE_DATA(file_inode(file));
	int limited_freq_by_hevc;

	char *buf = _copy_from_user_for_proc(buffer, count);

	if (!buf)
		return -EINVAL;

	if (sscanf(buf, "%d", &limited_freq_by_hevc) == 1) {
		p->limited_freq_by_hevc = limited_freq_by_hevc;

		if (cpu_dvfs_is_availiable(p) && (p->limited_freq_by_hevc > cpu_dvfs_get_cur_freq(p))) {
			struct cpufreq_policy *policy = cpufreq_cpu_get(p->cpu_id);

			if (policy) {
				cpufreq_driver_target(policy, p->limited_freq_by_hevc, CPUFREQ_RELATION_L);
				cpufreq_cpu_put(policy);
			}
		}
	} else
		cpufreq_err("echo limited_freq_by_hevc (dec) > /proc/cpufreq/cpufreq_limited_by_hevc\n");

	free_page((unsigned long)buf);
	return count;
}

static int cpufreq_limited_max_freq_by_user_proc_show(struct seq_file *m, void *v)
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)m->private;

	seq_printf(m, "%d\n", p->limited_max_freq_by_user);

	return 0;
}

static ssize_t cpufreq_limited_max_freq_by_user_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)PDE_DATA(file_inode(file));
	int limited_max_freq;

	char *buf = _copy_from_user_for_proc(buffer, count);

	if (!buf)
		return -EINVAL;

	if (sscanf(buf, "%d", &limited_max_freq) == 1) {

		p->limited_max_freq_by_user = limited_max_freq;

		if (cpu_dvfs_is_availiable(p) && (p->limited_max_freq_by_user < cpu_dvfs_get_cur_freq(p))) {
			struct cpufreq_policy *policy = cpufreq_cpu_get(p->cpu_id);

			if (policy) {
				cpufreq_driver_target(policy, p->limited_max_freq_by_user, CPUFREQ_RELATION_H);
				cpufreq_cpu_put(policy);
			}
		}
	} else
		cpufreq_err("echo limited_max_freq (dec) > /proc/cpufreq/%s/cpufreq_limited_max_freq_by_user\n", p->name);

	free_page((unsigned long)buf);
	return count;
}

static int cpufreq_limited_power_proc_show(struct seq_file *m, void *v)
{
	struct mt_cpu_dvfs *p;
	int i;

	for_each_cpu_dvfs(i, p) {
		seq_printf(m, "[%s/%d] %d\n"
			   "limited_max_freq = %d\n"
			   "limited_max_ncpu = %d\n",
			   p->name, i, p->thermal_protect_limited_power,
			   p->limited_max_freq,
			   p->limited_max_ncpu
			  );
	}

	return 0;
}

static ssize_t cpufreq_limited_power_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
	int limited_power;

	char *buf = _copy_from_user_for_proc(buffer, count);

	if (!buf)
		return -EINVAL;

	if (sscanf(buf, "%d", &limited_power) == 1)
		mt_cpufreq_thermal_protect(limited_power); 
	else
		cpufreq_err("echo limited_power (dec) > /proc/cpufreq/cpufreq_limited_power\n");

	free_page((unsigned long)buf);
	return count;
}

static int cpufreq_over_max_cpu_proc_show(struct seq_file *m, void *v)
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)m->private;

	seq_printf(m, "%d\n", p->over_max_cpu);

	return 0;
}

static ssize_t cpufreq_over_max_cpu_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)PDE_DATA(file_inode(file));
	int over_max_cpu;

	char *buf = _copy_from_user_for_proc(buffer, count);

	if (!buf)
		return -EINVAL;

	if (sscanf(buf, "%d", &over_max_cpu) == 1)
		p->over_max_cpu = over_max_cpu;
	else
		cpufreq_err("echo over_max_cpu (dec) > /proc/cpufreq/cpufreq_over_max_cpu\n");

	free_page((unsigned long)buf);
	return count;
}

static int cpufreq_power_dump_proc_show(struct seq_file *m, void *v)
{
	struct mt_cpu_dvfs *p;
	int i, j;

	for_each_cpu_dvfs(i, p) {
		seq_printf(m, "[%s/%d]\n", p->name, i);

		for (j = 0; j < p->nr_power_tbl; j++) {
			seq_printf(m, "[%d] = { .cpufreq_khz = %d,\t.cpufreq_ncpu = %d,\t.cpufreq_power = %d, },\n",
				   j,
				   p->power_tbl[j].cpufreq_khz,
				   p->power_tbl[j].cpufreq_ncpu,
				   p->power_tbl[j].cpufreq_power
				  );
		}
	}

	return 0;
}

static int cpufreq_ptpod_freq_volt_proc_show(struct seq_file *m, void *v)
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)m->private;
	int j;

	for (j = 0; j < p->nr_opp_tbl; j++) {
		seq_printf(m, "[%d] = { .cpufreq_khz = %d,\t.cpufreq_volt = %d,\t.cpufreq_volt_org = %d, },\n",
			   j,
			   p->opp_tbl[j].cpufreq_khz,
			   p->opp_tbl[j].cpufreq_volt,
			   p->opp_tbl[j].cpufreq_volt_org
			  );
	}

	return 0;
}

static int cpufreq_ptpod_temperature_limit_proc_show(struct seq_file *m, void *v)
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)m->private;

	seq_printf(m, "ptpod_temperature_limit_1 = %d\n"
		   "ptpod_temperature_limit_2 = %d\n",
		   p->ptpod_temperature_limit_1,
		   p->ptpod_temperature_limit_2
		  );

	return 0;
}

static ssize_t cpufreq_ptpod_temperature_limit_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)PDE_DATA(file_inode(file));
	int ptpod_temperature_limit_1;
	int ptpod_temperature_limit_2;

	char *buf = _copy_from_user_for_proc(buffer, count);

	if (!buf)
		return -EINVAL;

	if (sscanf(buf, "%d %d", &ptpod_temperature_limit_1, &ptpod_temperature_limit_2) == 2) {
		p->ptpod_temperature_limit_1 = ptpod_temperature_limit_1;
		p->ptpod_temperature_limit_2 = ptpod_temperature_limit_2;
	} else
		cpufreq_err("echo ptpod_temperature_limit_1 (dec) ptpod_temperature_limit_2 (dec) > /proc/cpufreq/cpufreq_ptpod_temperature_limit\n");

	free_page((unsigned long)buf);
	return count;
}

static int cpufreq_ptpod_temperature_time_proc_show(struct seq_file *m, void *v)
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)m->private;

	seq_printf(m, "ptpod_temperature_time_1 = %d\n"
		   "ptpod_temperature_time_2 = %d\n",
		   p->ptpod_temperature_time_1,
		   p->ptpod_temperature_time_2
		  );

	return 0;
}

static ssize_t cpufreq_ptpod_temperature_time_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)PDE_DATA(file_inode(file));
	int ptpod_temperature_time_1;
	int ptpod_temperature_time_2;

	char *buf = _copy_from_user_for_proc(buffer, count);

	if (!buf)
		return -EINVAL;

	if (sscanf(buf, "%d %d", &ptpod_temperature_time_1, &ptpod_temperature_time_2) == 2) {
		p->ptpod_temperature_time_1 = ptpod_temperature_time_1;
		p->ptpod_temperature_time_2 = ptpod_temperature_time_2;
	} else
		cpufreq_err("echo ptpod_temperature_time_1 (dec) ptpod_temperature_time_2 (dec) > /proc/cpufreq/cpufreq_ptpod_temperature_time\n");

	free_page((unsigned long)buf);
	return count;
}

static int cpufreq_ptpod_test_proc_show(struct seq_file *m, void *v)
{
	return 0;
}

static ssize_t cpufreq_ptpod_test_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
	return count;
}

static int cpufreq_state_proc_show(struct seq_file *m, void *v) 
{
	struct mt_cpu_dvfs *p;
	int i;

	for_each_cpu_dvfs(i, p) {
		seq_printf(m, "[%s/%d]\n"
			   "dvfs_disable_by_suspend = %d\n"
			   "dvfs_disable_by_early_suspend = %d\n"
			   "dvfs_disable_by_ptpod = %d\n"
			   "dvfs_disable_by_procfs = %d\n",
			   p->name, i,
			   p->dvfs_disable_by_suspend,
			   p->dvfs_disable_by_early_suspend,
			   p->dvfs_disable_by_ptpod,
			   p->dvfs_disable_by_procfs
			  );
	}

	return 0;
}

static ssize_t cpufreq_state_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos) 
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)PDE_DATA(file_inode(file));
	char *buf = _copy_from_user_for_proc(buffer, count);
	int enable;

	if (!buf)
		return -EINVAL;

	if (sscanf(buf, "%d", &enable) == 1) {
		if (enable == 0)
			p->dvfs_disable_by_procfs = true;
		else
			p->dvfs_disable_by_procfs = false;
	} else
		cpufreq_err("echo 1/0 > /proc/cpufreq/cpufreq_state\n");

	free_page((unsigned long)buf);
	return count;
}

static int cpufreq_oppidx_proc_show(struct seq_file *m, void *v) 
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)m->private;
	int j;

	seq_printf(m, "[%s/%d]\n"
		   "cpufreq_oppidx = %d\n",
		   p->name, p->cpu_id,
		   p->idx_opp_tbl
		  );

	for (j = 0; j < p->nr_opp_tbl; j++) {
		seq_printf(m, "\tOP(%d, %d),\n",
			   cpu_dvfs_get_freq_by_idx(p, j),
			   cpu_dvfs_get_volt_by_idx(p, j)
			  );
	}

	return 0;
}

static ssize_t cpufreq_oppidx_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos) 
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)PDE_DATA(file_inode(file));
	int oppidx;

	char *buf = _copy_from_user_for_proc(buffer, count);

	if (!buf)
		return -EINVAL;

	BUG_ON(NULL == p);

	if (sscanf(buf, "%d", &oppidx) == 1
	    && 0 <= oppidx && oppidx < p->nr_opp_tbl
	   ) {
		p->dvfs_disable_by_procfs = true;
		_mt_cpufreq_set(MT_CPU_DVFS_LITTLE, oppidx);
	} else {
		p->dvfs_disable_by_procfs = false; 
		cpufreq_err("echo oppidx > /proc/cpufreq/cpufreq_oppidx (0 <= %d < %d)\n", oppidx, p->nr_opp_tbl);
	}

	free_page((unsigned long)buf);

	return count;
}

static int cpufreq_freq_proc_show(struct seq_file *m, void *v) 
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)m->private;

	seq_printf(m, "%d KHz\n", p->ops->get_cur_phy_freq(p));

	return 0;
}

static ssize_t cpufreq_freq_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos) 
{
	unsigned long flags;
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)PDE_DATA(file_inode(file));
	unsigned int cur_freq;
	int freq, i, found;

	char *buf = _copy_from_user_for_proc(buffer, count);

	if (!buf)
		return -EINVAL;

	BUG_ON(NULL == p);

	if (sscanf(buf, "%d", &freq) == 1) {
		if (freq < CPUFREQ_LAST_FREQ_LEVEL) {
			if (freq != 0)
				cpufreq_err("frequency should higher than %dKHz!\n", CPUFREQ_LAST_FREQ_LEVEL);

			p->dvfs_disable_by_procfs = false;
			goto end;
		} else {
			for (i = 0; i < p->nr_opp_tbl; i++) {
				if (freq == p->opp_tbl[i].cpufreq_khz) {
					found = 1;
					break;
				}
			}

			if (found == 1) {
				p->dvfs_disable_by_procfs = true; 
				cpufreq_lock(flags);	
				cur_freq = p->ops->get_cur_phy_freq(p);

				if (freq != cur_freq)
					p->ops->set_cur_freq(p, cur_freq, freq);

				cpufreq_unlock(flags);	
			} else {
				p->dvfs_disable_by_procfs = false;
				cpufreq_err("frequency %dKHz! is not found in CPU opp table\n", freq);
			}
		}
	} else {
		p->dvfs_disable_by_procfs = false; 
		cpufreq_err("echo khz > /proc/cpufreq/cpufreq_freq\n");
	}

end:
	free_page((unsigned long)buf);

	return count;
}

static int cpufreq_volt_proc_show(struct seq_file *m, void *v) 
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)m->private;

	if (cpu_dvfs_is_extbuck_valid()) {
		seq_printf(m, "Vproc: %d mv\n", p->ops->get_cur_volt(p) / 100);  
		seq_printf(m, "Vsram: %d mv\n", get_cur_vsram(p) / 100);  
	} else
		seq_printf(m, "%d mv\n", p->ops->get_cur_volt(p) / 100);  

	return 0;
}

static ssize_t cpufreq_volt_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos) 
{
	unsigned long flags;
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)PDE_DATA(file_inode(file));
	int mv;

	char *buf = _copy_from_user_for_proc(buffer, count);

	if (!buf)
		return -EINVAL;

	if (sscanf(buf, "%d", &mv) == 1) {
		p->dvfs_disable_by_procfs = true; 
		cpufreq_lock(flags);
		_set_cur_volt_locked(p, mv * 100);
		cpufreq_unlock(flags);
	} else {
		p->dvfs_disable_by_procfs = false; 
		cpufreq_err("echo mv > /proc/cpufreq/cpufreq_volt\n");
	}

	free_page((unsigned long)buf);

	return count;
}

static int cpufreq_turbo_mode_proc_show(struct seq_file *m, void *v) 
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)m->private;
	int i;

	seq_printf(m, "turbo_mode = %d\n", p->turbo_mode);

	for (i = 0; i < NR_TURBO_MODE; i++) {
		seq_printf(m, "[%d] = { .temp = %d, .freq_delta = %d, .volt_delta = %d }\n",
			   i,
			   turbo_mode_cfg[i].temp,
			   turbo_mode_cfg[i].freq_delta,
			   turbo_mode_cfg[i].volt_delta
			  );
	}

	return 0;
}

static ssize_t cpufreq_turbo_mode_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos) 
{
	struct mt_cpu_dvfs *p = (struct mt_cpu_dvfs *)PDE_DATA(file_inode(file));
	unsigned int turbo_mode;
	int temp;
	int freq_delta;
	int volt_delta;

	char *buf = _copy_from_user_for_proc(buffer, count);

	if (!buf)
		return -EINVAL;

	if ((sscanf(buf, "%d %d %d %d", &turbo_mode, &temp, &freq_delta, &volt_delta) == 4) && turbo_mode < NR_TURBO_MODE) {
		turbo_mode_cfg[turbo_mode].temp = temp;
		turbo_mode_cfg[turbo_mode].freq_delta = freq_delta;
		turbo_mode_cfg[turbo_mode].volt_delta = volt_delta;
	} else if (sscanf(buf, "%d", &turbo_mode) == 1)
		p->turbo_mode = turbo_mode; 
	else {
		cpufreq_err("echo 0/1 > /proc/cpufreq/cpufreq_turbo_mode\n");
		cpufreq_err("echo idx temp freq_delta volt_delta > /proc/cpufreq/cpufreq_turbo_mode\n");
	}

	free_page((unsigned long)buf);

	return count;
}

#define PROC_FOPS_RW(name)							\
    static int name ## _proc_open(struct inode *inode, struct file *file)	\
    {									\
        return single_open(file, name ## _proc_show, PDE_DATA(inode));	\
    }									\
    static const struct file_operations name ## _proc_fops = {		\
        .owner          = THIS_MODULE,					\
                          .open           = name ## _proc_open,				\
                                            .read           = seq_read,					\
                                                    .llseek         = seq_lseek,					\
                                                            .release        = single_release,				\
                                                                    .write          = name ## _proc_write,				\
    }

#define PROC_FOPS_RO(name)							\
    static int name ## _proc_open(struct inode *inode, struct file *file)	\
    {									\
        return single_open(file, name ## _proc_show, PDE_DATA(inode));	\
    }									\
    static const struct file_operations name ## _proc_fops = {		\
        .owner          = THIS_MODULE,					\
                          .open           = name ## _proc_open,				\
                                            .read           = seq_read,					\
                                                    .llseek         = seq_lseek,					\
                                                            .release        = single_release,				\
    }

#define PROC_ENTRY(name)	{__stringify(name), &name ## _proc_fops}

PROC_FOPS_RW(cpufreq_debug);
PROC_FOPS_RW(cpufreq_fftt_test);
PROC_FOPS_RW(cpufreq_stress_test);
PROC_FOPS_RW(cpufreq_limited_power);
PROC_FOPS_RO(cpufreq_power_dump);
PROC_FOPS_RW(cpufreq_ptpod_test);
PROC_FOPS_RW(cpufreq_state);

PROC_FOPS_RO(cpufreq_downgrade_freq_info);
PROC_FOPS_RW(cpufreq_downgrade_freq_counter_limit);
PROC_FOPS_RW(cpufreq_downgrade_freq_counter_return_limit);
PROC_FOPS_RW(cpufreq_limited_by_hevc);
PROC_FOPS_RW(cpufreq_limited_max_freq_by_user);
PROC_FOPS_RW(cpufreq_over_max_cpu);
PROC_FOPS_RO(cpufreq_ptpod_freq_volt);
PROC_FOPS_RW(cpufreq_ptpod_temperature_limit);
PROC_FOPS_RW(cpufreq_ptpod_temperature_time);
PROC_FOPS_RW(cpufreq_oppidx); 
PROC_FOPS_RW(cpufreq_freq); 
PROC_FOPS_RW(cpufreq_volt); 
PROC_FOPS_RW(cpufreq_turbo_mode); 

static int _create_procfs(void)
{
	struct proc_dir_entry *dir = NULL;
	
	struct mt_cpu_dvfs *p = id_to_cpu_dvfs(0);
	int i; 

	struct pentry {
		const char *name;
		const struct file_operations *fops;
	};

	const struct pentry entries[] = {
		PROC_ENTRY(cpufreq_debug),
		PROC_ENTRY(cpufreq_fftt_test),
		PROC_ENTRY(cpufreq_stress_test),
		PROC_ENTRY(cpufreq_limited_power),
		PROC_ENTRY(cpufreq_power_dump),
		PROC_ENTRY(cpufreq_ptpod_test),
	};

	const struct pentry cpu_entries[] = {
		PROC_ENTRY(cpufreq_downgrade_freq_info),
		PROC_ENTRY(cpufreq_downgrade_freq_counter_limit),
		PROC_ENTRY(cpufreq_downgrade_freq_counter_return_limit),
		PROC_ENTRY(cpufreq_limited_by_hevc),
		PROC_ENTRY(cpufreq_limited_max_freq_by_user),
		PROC_ENTRY(cpufreq_over_max_cpu),
		PROC_ENTRY(cpufreq_ptpod_freq_volt),
		PROC_ENTRY(cpufreq_ptpod_temperature_limit),
		PROC_ENTRY(cpufreq_ptpod_temperature_time),
		PROC_ENTRY(cpufreq_state),
		PROC_ENTRY(cpufreq_oppidx), 
		PROC_ENTRY(cpufreq_freq), 
		PROC_ENTRY(cpufreq_volt), 
		PROC_ENTRY(cpufreq_turbo_mode), 
	};

	dir = proc_mkdir("cpufreq", NULL);

	if (!dir) {
		cpufreq_err("fail to create /proc/cpufreq @ %s()\n", __func__);
		return -ENOMEM;
	}

	for (i = 0; i < ARRAY_SIZE(entries); i++) {
		if (!proc_create(entries[i].name, S_IRUGO | S_IWUSR | S_IWGRP, dir, entries[i].fops))
			cpufreq_err("%s(), create /proc/cpufreq/%s failed\n", __func__, entries[i].name);
	}

	for (i = 0; i < ARRAY_SIZE(cpu_entries); i++) {
		if (!proc_create_data(cpu_entries[i].name, S_IRUGO | S_IWUSR | S_IWGRP, dir, cpu_entries[i].fops, p))
			cpufreq_err("%s(), create /proc/cpufreq/%s failed\n", __func__, cpu_entries[i].name);
	}

#if 0  
	for_each_cpu_dvfs(j, p) {
		cpu_dir = proc_mkdir(p->name, dir);

		if (!cpu_dir) {
			cpufreq_err("fail to create /proc/cpufreq/%s @ %s()\n", p->name, __func__);
			return -ENOMEM;
		}

		for (i = 0; i < ARRAY_SIZE(cpu_entries); i++) {
			if (!proc_create_data(cpu_entries[i].name, S_IRUGO | S_IWUSR | S_IWGRP, cpu_dir, cpu_entries[i].fops, p))
				cpufreq_err("%s(), create /proc/cpufreq/%s/%s failed\n", __func__, p->name, entries[i].name);
		}
	}
#endif

	return 0;
}
#endif 

static int __init _mt_cpufreq_pdrv_init(void)
{
	int ret = 0;

	FUNC_ENTER(FUNC_LV_MODULE);

	
#ifdef CONFIG_PROC_FS

	
	if (_create_procfs())
		goto out;

#endif 

	
	ret = platform_device_register(&_mt_cpufreq_pdev);

	if (ret) {
		cpufreq_err("fail to register cpufreq device @ %s()\n", __func__);
		goto out;
	}

	ret = platform_driver_register(&_mt_cpufreq_pdrv);

	if (ret) {
		cpufreq_err("fail to register cpufreq driver @ %s()\n", __func__);
		platform_device_unregister(&_mt_cpufreq_pdev);
	}

out:
	FUNC_EXIT(FUNC_LV_MODULE);

	return ret;
}

static void __exit _mt_cpufreq_pdrv_exit(void)
{
	FUNC_ENTER(FUNC_LV_MODULE);

	platform_driver_unregister(&_mt_cpufreq_pdrv);
	platform_device_unregister(&_mt_cpufreq_pdev);

	FUNC_EXIT(FUNC_LV_MODULE);
}

late_initcall(_mt_cpufreq_pdrv_init);
module_exit(_mt_cpufreq_pdrv_exit);

MODULE_DESCRIPTION("MediaTek CPU DVFS Driver v0.3");
MODULE_LICENSE("GPL");

