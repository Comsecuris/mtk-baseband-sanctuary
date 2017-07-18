#ifndef _MT_CLKMGR_H
#define _MT_CLKMGR_H

#include <linux/list.h>
#include "mach/mt_typedefs.h"

#define CONFIG_CLKMGR_STAT

#ifdef CONFIG_ARM64
#define PLL_CLK_LINK
#else
#define PLL_CLK_LINK
#endif

#ifdef CONFIG_OF
extern void __iomem  *clk_apmixed_base;
extern void __iomem  *clk_cksys_base;
extern void __iomem  *clk_infracfg_ao_base;
extern void __iomem  *clk_pericfg_base;
extern void __iomem  *clk_audio_base;
extern void __iomem  *clk_mfgcfg_base;
extern void __iomem  *clk_mmsys_config_base;
extern void __iomem  *clk_imgsys_base;
extern void __iomem  *clk_vdec_gcon_base;
extern void __iomem  *clk_mjc_config_base;
extern void __iomem  *clk_venc_gcon_base;
extern void __iomem  *clk_mcucfg_base;
extern void __iomem  *clk_e3tcm_base;
#endif

#define mcu_dbg (clk_mcucfg_base + 0x64c) 

#define AP_PLL_CON0             (clk_apmixed_base + 0x00)
#define AP_PLL_CON1             (clk_apmixed_base + 0x04)
#define AP_PLL_CON2             (clk_apmixed_base + 0x08)
#define AP_PLL_CON7             (clk_apmixed_base + 0x1C)

#define ARMCA15PLL_CON0         (clk_apmixed_base + 0x200)
#define ARMCA15PLL_CON1         (clk_apmixed_base + 0x204)
#define ARMCA15PLL_CON2         (clk_apmixed_base + 0x208)
#define ARMCA15PLL_PWR_CON0     (clk_apmixed_base + 0x20C)

#define ARMCA7PLL_CON0          (clk_apmixed_base + 0x210)
#define ARMCA7PLL_CON1          (clk_apmixed_base + 0x214)
#define ARMCA7PLL_CON2          (clk_apmixed_base + 0x218)
#define ARMCA7PLL_PWR_CON0      (clk_apmixed_base + 0x21C)

#define MAINPLL_CON0            (clk_apmixed_base + 0x220)
#define MAINPLL_CON1            (clk_apmixed_base + 0x224)
#define MAINPLL_PWR_CON0        (clk_apmixed_base + 0x22C)

#define UNIVPLL_CON0            (clk_apmixed_base + 0x230)
#define UNIVPLL_CON1            (clk_apmixed_base + 0x234)
#define UNIVPLL_PWR_CON0        (clk_apmixed_base + 0x23C)

#define MMPLL_CON0              (clk_apmixed_base + 0x240)
#define MMPLL_CON1              (clk_apmixed_base + 0x244)
#define MMPLL_CON2              (clk_apmixed_base + 0x248)
#define MMPLL_PWR_CON0          (clk_apmixed_base + 0x24C)

#define MSDCPLL_CON0            (clk_apmixed_base + 0x250)
#define MSDCPLL_CON1            (clk_apmixed_base + 0x254)
#define MSDCPLL_PWR_CON0        (clk_apmixed_base + 0x25C)

#define VENCPLL_CON0            (clk_apmixed_base + 0x260)
#define VENCPLL_CON1            (clk_apmixed_base + 0x264)
#define VENCPLL_PWR_CON0        (clk_apmixed_base + 0x26C)

#define TVDPLL_CON0             (clk_apmixed_base + 0x270)
#define TVDPLL_CON1             (clk_apmixed_base + 0x274)
#define TVDPLL_PWR_CON0         (clk_apmixed_base + 0x27C)

#define MPLL_CON0               (clk_apmixed_base + 0x280)
#define MPLL_CON1               (clk_apmixed_base + 0x284)
#define MPLL_PWR_CON0           (clk_apmixed_base + 0x28C)

#define VCODECPLL_CON0          (clk_apmixed_base + 0x290)
#define VCODECPLL_CON1          (clk_apmixed_base + 0x294)
#define VCODECPLL_PWR_CON0      (clk_apmixed_base + 0x29C)

#define APLL1_CON0              (clk_apmixed_base + 0x2A0)
#define APLL1_CON1              (clk_apmixed_base + 0x2A4)
#define APLL1_CON2              (clk_apmixed_base + 0x2A8)
#define APLL1_CON3              (clk_apmixed_base + 0x2AC)
#define APLL1_PWR_CON0          (clk_apmixed_base + 0x2B0)

#define APLL2_CON0              (clk_apmixed_base + 0x2B4)
#define APLL2_CON1              (clk_apmixed_base + 0x2B8)
#define APLL2_CON2              (clk_apmixed_base + 0x2BC)
#define APLL2_CON3              (clk_apmixed_base + 0x2C0)
#define APLL2_PWR_CON0          (clk_apmixed_base + 0x2C4)

#define CLK_CFG_0               (clk_cksys_base + 0x040)
#define CLK_CFG_1               (clk_cksys_base + 0x050)
#define CLK_CFG_2               (clk_cksys_base + 0x060)
#define CLK_CFG_3               (clk_cksys_base + 0x070)
#define CLK_CFG_4               (clk_cksys_base + 0x080)
#define CLK_CFG_5               (clk_cksys_base + 0x090)
#define CLK_CFG_6               (clk_cksys_base + 0x0A0) 
#define CLK_CFG_7               (clk_cksys_base + 0x0B0)
#define CLK_CFG_8               (clk_cksys_base + 0x100)
#define CLK_CFG_9               (clk_cksys_base + 0x104)
#define CLK_CFG_10              (clk_cksys_base + 0x108)
#define CLK_CFG_11              (clk_cksys_base + 0x10C)
#define CLK_SCP_CFG_0           (clk_cksys_base + 0x200)
#define CLK_SCP_CFG_1           (clk_cksys_base + 0x204)
#define CLK_MISC_CFG_0          (clk_cksys_base + 0x210)
#define CLK_MISC_CFG_1          (clk_cksys_base + 0x214)
#define CLK_MISC_CFG_2          (clk_cksys_base + 0x218)
#define CLK26CALI_0             (clk_cksys_base + 0x220)
#define CLK26CALI_1             (clk_cksys_base + 0x224)
#define CLK26CALI_2             (clk_cksys_base + 0x228)
#define CKSTA_REG               (clk_cksys_base + 0x22C)
#define TEST_MODE_CFG           (clk_cksys_base + 0x230)
#define MBIST_CFG_0             (clk_cksys_base + 0x308)
#define MBIST_CFG_1             (clk_cksys_base + 0x30C)
#define RESET_DEGLITCH_KEY      (clk_cksys_base + 0x310)
#define MBIST_CFG_3             (clk_cksys_base + 0x314)

#define TOP_CKMUXSEL            (clk_infracfg_ao_base + 0x00)
#define TOP_CKDIV1              (clk_infracfg_ao_base + 0x08)

#define INFRA_PDN_SET           (clk_infracfg_ao_base + 0x0040)
#define INFRA_PDN_CLR           (clk_infracfg_ao_base + 0x0044)
#define INFRA_PDN_STA           (clk_infracfg_ao_base + 0x0048)

#define TOPAXI_PROT_EN          (clk_infracfg_ao_base + 0x0220)
#define TOPAXI_PROT_STA1        (clk_infracfg_ao_base + 0x0228)


#define PERI_PDN0_SET           (clk_pericfg_base + 0x0008)
#define PERI_PDN0_CLR           (clk_pericfg_base + 0x0010)
#define PERI_PDN0_STA           (clk_pericfg_base + 0x0018)

#define AUDIO_TOP_CON0          (clk_audio_base + 0x0000)
                                
            
#define MFG_CG_CON              (clk_mfgcfg_base + 0)
#define MFG_CG_SET              (clk_mfgcfg_base + 4)
#define MFG_CG_CLR              (clk_mfgcfg_base + 8)

             
#define DISP_CG_CON0            (clk_mmsys_config_base + 0x100)
#define DISP_CG_SET0            (clk_mmsys_config_base + 0x104)
#define DISP_CG_CLR0            (clk_mmsys_config_base + 0x108)
#define DISP_CG_CON1            (clk_mmsys_config_base + 0x110)
#define DISP_CG_SET1            (clk_mmsys_config_base + 0x114)
#define DISP_CG_CLR1            (clk_mmsys_config_base + 0x118)

#define MMSYS_DUMMY             (clk_mmsys_config_base + 0x890)
#define	SMI_LARB_BWL_EN_REG     (clk_mmsys_config_base + 0x21050)

#define IMG_CG_CON              (clk_imgsys_base + 0x0000)
#define IMG_CG_SET              (clk_imgsys_base + 0x0004)
#define IMG_CG_CLR              (clk_imgsys_base + 0x0008)

                                
#define VDEC_CKEN_SET           (clk_vdec_gcon_base + 0x0000)
#define VDEC_CKEN_CLR           (clk_vdec_gcon_base + 0x0004)
#define LARB_CKEN_SET           (clk_vdec_gcon_base + 0x0008)
#define LARB_CKEN_CLR           (clk_vdec_gcon_base + 0x000C)

#define MJC_CG_CON              (clk_mjc_config_base + 0x0000)
#define MJC_CG_SET              (clk_mjc_config_base + 0x0004)
#define MJC_CG_CLR              (clk_mjc_config_base + 0x0008)

#define VENC_CG_CON             (clk_venc_gcon_base + 0x0)
#define VENC_CG_SET             (clk_venc_gcon_base + 0x4)
#define VENC_CG_CLR             (clk_venc_gcon_base + 0x8)

           
#define IR_ROSC_CTL             (clk_mcucfg_base + 0x030)

#define E3TCM_CG_CON            (clk_e3tcm_base+ 0x0)
#define E3TCM_CG_SET            (clk_e3tcm_base+ 0x4)
#define E3TCM_CG_CLR            (clk_e3tcm_base+ 0x8)

enum {
    CG_PERI  = 0,
    CG_INFRA = 1,
    CG_DISP0 = 2,
    CG_DISP1 = 3,
    CG_IMAGE = 4,
    CG_MFG   = 5,
    CG_AUDIO = 6,
    CG_VDEC0 = 7,
    CG_VDEC1 = 8,
    CG_MJC   = 9,
    CG_VENC  = 10,
    NR_GRPS  = 11,
};

enum cg_clk_id{                                 
    MT_CG_PERI_NFI                  = 0,        
    MT_CG_PERI_THERM                = 1,        
    MT_CG_PERI_PWM1                 = 2,        
    MT_CG_PERI_PWM2                 = 3,        
    MT_CG_PERI_PWM3                 = 4,        
    MT_CG_PERI_PWM4                 = 5,        
    MT_CG_PERI_PWM5                 = 6,        
    MT_CG_PERI_PWM6                 = 7,        
    MT_CG_PERI_PWM7                 = 8,        
    MT_CG_PERI_PWM                  = 9,        
    MT_CG_PERI_USB0                 = 10,       
    MT_CG_PERI_USB1                 = 11,       
    MT_CG_PERI_AP_DMA               = 12,       
    MT_CG_PERI_MSDC30_0             = 13,       
    MT_CG_PERI_MSDC30_1             = 14,       
    MT_CG_PERI_MSDC30_2             = 15,       
    MT_CG_PERI_MSDC30_3             = 16,       
    MT_CG_PERI_NLI                  = 17,       
    MT_CG_PERI_IRDA                 = 18,       
    MT_CG_PERI_UART0                = 19,       
    MT_CG_PERI_UART1                = 20,       
    MT_CG_PERI_UART2                = 21,       
    MT_CG_PERI_UART3                = 22,       
    MT_CG_PERI_I2C0                 = 23,       
    MT_CG_PERI_I2C1                 = 24,       
    MT_CG_PERI_I2C2                 = 25,       
    MT_CG_PERI_I2C3                 = 26,       
    MT_CG_PERI_I2C4                 = 27,       
    MT_CG_PERI_AUXADC               = 28,       
    MT_CG_PERI_SPI0                 = 29,       
    
    MT_CG_INFRA_DBGCLK              = 32,       
    MT_CG_INFRA_SMI                 = 33,       
    MT_CG_INFRA_SLICE               = 34,
    MT_CG_INFRA_AUDIO               = 37,       
    MT_CG_INFRA_GCE                 = 38,       
    MT_CG_INFRA_L2C_SRAM            = 39,       
    MT_CG_INFRA_M4U                 = 40,       
    MT_CG_INFRA_MD1MCU              = 41,       
    MT_CG_INFRA_MD1BUS              = 42,       
    MT_CG_INFRA_MD1DBB              = 43,       
    MT_CG_INFRA_DEVICE_APC          = 44,       
    MT_CG_INFRA_TRNG				= 45,       
    MT_CG_INFRA_MD1LTE              = 46,       
    MT_CG_INFRA_CPUM                = 47,       
    MT_CG_INFRA_KP                  = 48,       
    MT_CG_INFRA_PMICSPI             = 54,       
    MT_CG_INFRA_PMICWRAP            = 55,       
    
    
    MT_CG_DISP0_SMI_COMMON          = 64,       
    MT_CG_DISP0_SMI_LARB0           = 65,       
    MT_CG_DISP0_CAM_MDP             = 66,       
    MT_CG_DISP0_MDP_RDMA0           = 67,       
    MT_CG_DISP0_MDP_RDMA1           = 68,       
    MT_CG_DISP0_MDP_RSZ0            = 69,       
    MT_CG_DISP0_MDP_RSZ1            = 70,       
    MT_CG_DISP0_MDP_RSZ2            = 71,       
    MT_CG_DISP0_MDP_TDSHP0          = 72,       
    MT_CG_DISP0_MDP_TDSHP1          = 73,       
    MT_CG_DISP0_MDP_CROP            = 74,       
    MT_CG_DISP0_MDP_WDMA            = 75,       
    MT_CG_DISP0_MDP_WROT0           = 76,       
    MT_CG_DISP0_MDP_WROT1           = 77,       
    MT_CG_DISP0_FAKE_ENG            = 78,       
    MT_CG_DISP0_MUTEX_32K           = 79,       
    MT_CG_DISP0_DISP_OVL0           = 80,       
    MT_CG_DISP0_DISP_OVL1           = 81,       
    MT_CG_DISP0_DISP_RDMA0          = 82,       
    MT_CG_DISP0_DISP_RDMA1          = 83,       
    MT_CG_DISP0_DISP_RDMA2          = 84,       
    MT_CG_DISP0_DISP_WDMA0          = 85,       
    MT_CG_DISP0_DISP_WDMA1          = 86,       
    MT_CG_DISP0_DISP_COLOR0         = 87,       
    MT_CG_DISP0_DISP_COLOR1         = 88,       
    MT_CG_DISP0_DISP_AAL            = 89,       
    MT_CG_DISP0_DISP_GAMMA          = 90,       
    MT_CG_DISP0_DISP_UFOE           = 91,       
    MT_CG_DISP0_DISP_SPLIT0         = 92,       
    MT_CG_DISP0_DISP_SPLIT1         = 93,       
    MT_CG_DISP0_DISP_MERGE          = 94,       
    MT_CG_DISP0_DISP_OD             = 95,       
    
    MT_CG_DISP1_DISP_PWM0_MM        = 96 ,      
    MT_CG_DISP1_DISP_PWM0_26M       = 97 ,      
    MT_CG_DISP1_DISP_PWM1_MM        = 98 ,      
    MT_CG_DISP1_DISP_PWM1_26M       = 99 ,      
    MT_CG_DISP1_DSI0_ENGINE         = 100,      
    MT_CG_DISP1_DSI0_DIGITAL        = 101,      
    MT_CG_DISP1_DSI1_ENGINE         = 102,      
    MT_CG_DISP1_DSI1_DIGITAL        = 103,      
    MT_CG_DISP1_DPI_PIXEL           = 104,      
    MT_CG_DISP1_DPI_ENGINE          = 105,      
    
    MT_CG_IMAGE_LARB2_SMI           = 128,      
    MT_CG_IMAGE_CAM_SMI             = 133,      
    MT_CG_IMAGE_CAM_CAM             = 134,      
    MT_CG_IMAGE_SEN_TG              = 135,      
    MT_CG_IMAGE_SEN_CAM             = 136,      
    MT_CG_IMAGE_CAM_SV              = 137,      
    MT_CG_IMAGE_FD                  = 139,      
    
    MT_CG_MFG_AXI					= 160,      
    MT_CG_MFG_MEM					= 161,      
    MT_CG_MFG_G3D					= 162,      
    MT_CG_MFG_26M					= 163,      
    
    MT_CG_AUDIO_AFE                 = 194,      
    MT_CG_AUDIO_I2S                 = 198,      
    MT_CG_AUDIO_22M                 = 200,      
    MT_CG_AUDIO_24M                 = 201,      
    MT_CG_AUDIO_APLL2_TUNER         = 210,      
    MT_CG_AUDIO_APLL_TUNER          = 211,      
    MT_CG_AUDIO_HDMI                = 212,      
    MT_CG_AUDIO_ADDA3               = 214,      
    MT_CG_AUDIO_ADDA2               = 215,      
    
    MT_CG_VDEC0_VDEC				= 224,      
                                                
    MT_CG_VDEC1_LARB				= 256,      
                                                
    MT_CG_MJC_SMI_LARB              = 288,      
    MT_CG_MJC_TOP_GROUP0            = 289,      
    MT_CG_MJC_TOP_GROUP1            = 290,      
    MT_CG_MJC_TOP_GROUP2            = 291,      
    MT_CG_MJC_LARB4_AXI_ASIF        = 293,      
                                                
    MT_CG_VENC_LARB                 = 320,      
    MT_CG_VENC_VENC                 = 324,      
    MT_CG_VENC_JPGENC               = 328,      
    MT_CG_VENC_JPGDEC               = 332,      
    
    MT_CG_E3TCM_CORE                = 352, 
    MT_CG_E3TCM_MEM0                = 353,  
    MT_CG_E3TCM_MEM1                = 354,
    MT_CG_E3TCM_MEM2                = 355,
    MT_CG_E3TCM_MEM3                = 356,
    MT_CG_E3TCM_MEM4                = 357,  
    MT_CG_MD32_CORE                 = 358,

    CG_PERI_FROM					= MT_CG_PERI_NFI,
    CG_PERI_TO						= MT_CG_PERI_SPI0,
    NR_PERI_CLKS					= 30,
    
    CG_INFRA_FROM                   = MT_CG_INFRA_DBGCLK,
    CG_INFRA_TO                     = MT_CG_INFRA_PMICWRAP,
    NR_INFRA_CLKS                   = 16,
    
    CG_DISP0_FROM                   = MT_CG_DISP0_SMI_COMMON,
    CG_DISP0_TO                     = MT_CG_DISP0_DISP_OD,
    NR_DISP0_CLKS                   = 32,
    
    CG_DISP1_FROM                   = MT_CG_DISP1_DISP_PWM0_MM,
    CG_DISP1_TO                     = MT_CG_DISP1_DPI_ENGINE,
    NR_DISP1_CLKS                   = 10,
    
    CG_IMAGE_FROM                   = MT_CG_IMAGE_LARB2_SMI,
    CG_IMAGE_TO                     = MT_CG_IMAGE_FD,
    NR_IMAGE_CLKS                   = 7,
    
    CG_MFG_FROM                     = MT_CG_MFG_AXI,
    CG_MFG_TO                       = MT_CG_MFG_26M,
    NR_MFG_CLKS                     = 4,
    
    CG_AUDIO_FROM                   = MT_CG_AUDIO_AFE,
    CG_AUDIO_TO                     = MT_CG_AUDIO_ADDA2,
    NR_AUDIO_CLKS                   = 9,
    
    CG_VDEC0_FROM                   = MT_CG_VDEC0_VDEC,
    CG_VDEC0_TO                     = MT_CG_VDEC0_VDEC,
    NR_VDEC0_CLKS                   = 1,
    
    CG_VDEC1_FROM                   = MT_CG_VDEC1_LARB,
    CG_VDEC1_TO                     = MT_CG_VDEC1_LARB,
    NR_VDEC1_CLKS                   = 1,
    
    CG_MJC_FROM                     = MT_CG_MJC_SMI_LARB,
    CG_MJC_TO                       = MT_CG_MJC_LARB4_AXI_ASIF,
    NR_MJC_CLKS                     = 5,
    
    CG_VENC_FROM                    = MT_CG_VENC_LARB,
    CG_VENC_TO                      = MT_CG_VENC_JPGDEC,
    NR_VENC_CLKS                    = 4,
    
    NR_CLKS                         = 333,
};

enum {
	
    MT_MUX_MM           = 0,
    MT_MUX_DDRPHY       = 1,
    MT_MUX_MEM          = 2,
    MT_MUX_AXI          = 3,

    
    MT_MUX_MFG          = 4,
    MT_MUX_VENC         = 5,
    MT_MUX_VDEC         = 6,
    MT_MUX_PWM          = 7,

    
    MT_MUX_USB20        = 8,
    MT_MUX_SPI          = 9,
    MT_MUX_UART         = 10,
    MT_MUX_CAMTG        = 11,

    
    MT_MUX_MSDC30_1     = 12,
    MT_MUX_MSDC50_0     = 13,
    MT_MUX_MSDC50_0_hclk = 14,
    MT_MUX_USB30        = 15,

    
    MT_MUX_AUDINTBUS    = 16,
    MT_MUX_AUDIO        = 17,
    MT_MUX_MSDC30_3     = 18,
    MT_MUX_MSDC30_2     = 19,
    
    
    MT_MUX_MJC          = 20,
    MT_MUX_SCP          = 21,
    MT_MUX_PMICSPI      = 22,
    
    
    MT_MUX_AUD1         = 23,
    MT_MUX_CCI400       = 24,
    MT_MUX_IRDA         = 25,
    MT_MUX_DPI0         = 26,

    
    MT_MUX_SCAM          = 27,
    MT_MUX_AXI_MFG_IN_AS = 28,
    MT_MUX_MEM_MFG_IN_AS = 29,
    MT_MUX_AUD2          = 30,

    NR_MUXS             = 31,
};

enum {
    ARMCA15PLL = 0,
    ARMCA7PLL  = 1,
    MAINPLL    = 2,
    MSDCPLL    = 3,
    UNIVPLL    = 4,
    MMPLL      = 5,
    VENCPLL    = 6,
    TVDPLL     = 7,
    MPLL       = 8,
    VCODECPLL  = 9,
    APLL1      = 10,
    APLL2      = 11,
    NR_PLLS    = 12,
};

enum {
    SYS_MD1       = 0,
    SYS_DIS       = 1,
    SYS_MFG       = 2,
    SYS_ISP       = 3,
    SYS_VDE       = 4,
    SYS_MJC       = 5,
    SYS_VEN       = 6,
    SYS_AUD       = 7,
    NR_SYSS       = 8,
};

enum {
    MT_LARB_DISP = 0,
    MT_LARB_VDEC = 1,
    MT_LARB_IMG  = 2,
    MT_LARB_VENC = 3,
    MT_LARB_MJC  = 4,
};

enum {
    LARB_MONITOR_LEVEL_HIGH     = 10,
    LARB_MONITOR_LEVEL_MEDIUM   = 20,
    LARB_MONITOR_LEVEL_LOW      = 30,
};

struct larb_monitor {
    struct list_head link;
    int level;
    void (*backup)(struct larb_monitor *h, int larb_idx);       
    void (*restore)(struct larb_monitor *h, int larb_idx);      
};

enum monitor_clk_sel_0{
    no_clk_0             = 0,
    AD_UNIV_624M_CK      = 5,
    AD_UNIV_416M_CK      = 6,
    AD_UNIV_249P6M_CK    = 7,
    AD_UNIV_178P3M_CK_0  = 8,
    AD_UNIV_48M_CK       = 9,
    AD_USB_48M_CK        = 10,
    rtc32k_ck_i_0        = 20,
    AD_SYS_26M_CK_0      = 21,
};
enum monitor_clk_sel{
    no_clk               = 0,
    AD_SYS_26M_CK        = 1,
    rtc32k_ck_i          = 2,
    clkph_MCLK_o         = 7,
    AD_DPICLK            = 8,
    AD_MSDCPLL_CK        = 9,
    AD_MMPLL_CK          = 10,
    AD_UNIV_178P3M_CK    = 11,
    AD_MAIN_H156M_CK     = 12,
    AD_VENCPLL_CK        = 13,
};

enum ckmon_sel{
    clk_ckmon0           = 0,
    clk_ckmon1           = 1,
    clk_ckmon2           = 2,
    clk_ckmon3           = 3,
};

extern void register_larb_monitor(struct larb_monitor *handler);
extern void unregister_larb_monitor(struct larb_monitor *handler);

extern int enable_clock(enum cg_clk_id id, char *mod_name);
extern int disable_clock(enum cg_clk_id id, char *mod_name);
extern int mt_enable_clock(enum cg_clk_id id, char *mod_name);
extern int mt_disable_clock(enum cg_clk_id id, char *mod_name);

extern int enable_clock_ext_locked(int id, char *mod_name);
extern int disable_clock_ext_locked(int id, char *mod_name);

extern int clock_is_on(int id);

extern int clkmux_sel(int id, unsigned int clksrc, char *name);
extern void enable_mux(int id, char *name);
extern void disable_mux(int id, char *name);

extern void clk_set_force_on(int id);
extern void clk_clr_force_on(int id);
extern int clk_is_force_on(int id);

extern int enable_pll(int id, char *mod_name);
extern int disable_pll(int id, char *mod_name);

extern int pll_hp_switch_on(int id, int hp_on);
extern int pll_hp_switch_off(int id, int hp_off);

extern int pll_fsel(int id, unsigned int value);
extern int pll_is_on(int id);

extern int enable_subsys(int id, char *mod_name);
extern int disable_subsys(int id, char *mod_name);

extern int subsys_is_on(int id);
extern int md_power_on(int id);
extern int md_power_off(int id, unsigned int timeout);


extern void set_mipi26m(int en);
extern void set_ada_ssusb_xtal_ck(int en);

const char* grp_get_name(int id);
extern int clkmgr_is_locked(void);


extern int clk_monitor_0(enum ckmon_sel ckmon, enum monitor_clk_sel_0 sel, int div);
extern int clk_monitor(enum ckmon_sel ckmon, enum monitor_clk_sel sel, int div);

extern void cci400_sel_for_ddp(void);
extern void clk_stat_check(int id);

extern u32 get_axi_khz(void);
extern void clkmux_sel_for_vcorefs(bool mode);
extern void iomap_infra(void);

extern void slp_check_pm_mtcmos_pll(void);
extern void e3tcm_pwr_ctrl(int state);

#endif
