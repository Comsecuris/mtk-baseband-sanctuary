#ifndef __ARCH_ARM_MACH_BOARD_H
#define __ARCH_ARM_MACH_BOARD_H

#include <generated/autoconf.h>
#include <linux/pm.h>
#include <board-custom.h>

typedef void (*sdio_irq_handler_t)(void*);  
typedef void (*pm_callback_t)(pm_message_t state, void *data);

#define MSDC_CD_PIN_EN      (1 << 0)  
#define MSDC_WP_PIN_EN      (1 << 1)  
#define MSDC_RST_PIN_EN     (1 << 2)  
#define MSDC_SDIO_IRQ       (1 << 3)  
#define MSDC_EXT_SDIO_IRQ   (1 << 4)  
#define MSDC_REMOVABLE      (1 << 5)  
#define MSDC_SYS_SUSPEND    (1 << 6)  
#define MSDC_HIGHSPEED      (1 << 7)  
#define MSDC_UHS1           (1 << 8)  
#define MSDC_DDR            (1 << 9)  
#define MSDC_INTERNAL_CLK   (1 <<11)  
#ifdef CONFIG_MTK_EMMC_CACHE
#define MSDC_CACHE          (1 <<12)  
#endif
#define MSDC_HS400          (1 <<13)  

#define MSDC_SD_NEED_POWER  (1 << 31) 

#define MSDC_SMPL_RISING    (0)
#define MSDC_SMPL_FALLING   (1)

#define MSDC_CMD_PIN        (0)
#define MSDC_DAT_PIN        (1)
#define MSDC_CD_PIN         (2)
#define MSDC_WP_PIN         (3)
#define MSDC_RST_PIN        (4)

#define MSDC_DATA1_INT      (1)
enum {
    MSDC_CLKSRC_200MHZ = 0, 
    MSDC_CLKSRC_400MHZ = 1, 
    MSDC_CLKSRC_800MHZ = 2
};
#define MSDC_BOOT_EN        (1)
#define MSDC_CD_HIGH        (1)
#define MSDC_CD_LOW         (0)
enum {
    MSDC_EMMC = 0,
    MSDC_SD   = 1,
    MSDC_SDIO = 2
};

struct msdc_ett_settings {
    unsigned int speed_mode; 
#define MSDC_DEFAULT_MODE (0)
#define MSDC_SDR50_MODE   (1)
#define MSDC_DDR50_MODE   (2)
#define MSDC_HS200_MODE   (3)
#define MSDC_HS400_MODE   (4)
    unsigned int reg_addr; 
    unsigned int reg_offset; 
    unsigned int value; 
}; 

struct msdc_hw {
    unsigned char  clk_src;                
    unsigned char  cmd_edge;               
    unsigned char  rdata_edge;             
    unsigned char  wdata_edge;             
    unsigned char  clk_drv;                
    unsigned char  cmd_drv;                
    unsigned char  dat_drv;                
    unsigned char  rst_drv;                
    unsigned char  ds_drv;                 
    unsigned char  clk_drv_sd_18;          
    unsigned char  cmd_drv_sd_18;          
    unsigned char  dat_drv_sd_18;          
    unsigned char  clk_drv_sd_18_sdr50;    
    unsigned char  cmd_drv_sd_18_sdr50;    
    unsigned char  dat_drv_sd_18_sdr50;    
    unsigned char  clk_drv_sd_18_ddr50;    
    unsigned char  cmd_drv_sd_18_ddr50;    
    unsigned char  dat_drv_sd_18_ddr50;    
    unsigned char  clk_drv_sd_18_sdr104;    
    unsigned char  cmd_drv_sd_18_sdr104;    
    unsigned char  dat_drv_sd_18_sdr104;    
    unsigned long  flags;                  
    unsigned long  data_pins;              
    unsigned long  data_offset;            
    
    unsigned char  ddlsel;                 
    unsigned char  rdsplsel;               
    unsigned char  wdsplsel;               

    unsigned char  dat0rddly;              
    unsigned char  dat1rddly;              
    unsigned char  dat2rddly;              
    unsigned char  dat3rddly;              
    unsigned char  dat4rddly;              
    unsigned char  dat5rddly;              
    unsigned char  dat6rddly;              
    unsigned char  dat7rddly;              
    unsigned char  datwrddly;              
    unsigned char  cmdrrddly;              
    unsigned char  cmdrddly;               

	unsigned char  cmdrtactr_sdr50;   
	unsigned char  wdatcrctactr_sdr50;   
	unsigned char  intdatlatcksel_sdr50;   
	unsigned char  cmdrtactr_sdr200;   
	unsigned char  wdatcrctactr_sdr200;   
	unsigned char  intdatlatcksel_sdr200;   

    struct msdc_ett_settings *ett_settings; 
    unsigned int ett_count; 
    unsigned long  host_function;          
    bool           boot;                    
    bool           cd_level;                 
      
    
    void (*config_gpio_pin)(int type, int pull);

    
    void (*ext_power_on)(void);
    void (*ext_power_off)(void);

    
    void (*request_sdio_eirq)(sdio_irq_handler_t sdio_irq_handler, void *data);
    void (*enable_sdio_eirq)(void);
    void (*disable_sdio_eirq)(void);

    
    void (*request_cd_eirq)(sdio_irq_handler_t cd_irq_handler, void *data);
    void (*enable_cd_eirq)(void);
    void (*disable_cd_eirq)(void);
    int  (*get_cd_status)(void);
    
    
    void (*register_pm)(pm_callback_t pm_cb, void *data);
};

extern struct msdc_hw msdc0_hw;
extern struct msdc_hw msdc1_hw;
extern struct msdc_hw msdc2_hw;
extern struct msdc_hw msdc3_hw;

#define GPS_FLAG_FORCE_OFF  0x0001
struct mt3326_gps_hardware {
    int (*ext_power_on)(int);
    int (*ext_power_off)(int);
};
extern struct mt3326_gps_hardware mt3326_gps_hw;

struct mtk_nand_host_hw {
    unsigned int nfi_bus_width;             
    unsigned int nfi_access_timing;          
    unsigned int nfi_cs_num;               
    unsigned int nand_sec_size;            
    unsigned int nand_sec_shift;           
    unsigned int nand_ecc_size;
    unsigned int nand_ecc_bytes;
    unsigned int nand_ecc_mode;
};
extern struct mtk_nand_host_hw mtk_nand_hw;

#endif 

