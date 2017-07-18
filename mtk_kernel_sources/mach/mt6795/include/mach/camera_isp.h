#ifndef _MT_ISP_H
#define _MT_ISP_H

#include <linux/ioctl.h>

#ifdef CONFIG_COMPAT
#include <linux/fs.h>
#include <linux/compat.h>
#endif

#define ISR_LOG_ON  

#define T_STAMP_2_0 

#define SIG_ERESTARTSYS 512 
#define ISP_DEV_MAJOR_NUMBER    251
#define ISP_MAGIC               'k'
#define ISP_IRQ_P1_STATUS_VS1_INT_ST                ((unsigned int)1<<0)
#define ISP_IRQ_P1_STATUS_TG1_INT1_ST               ((unsigned int)1<<1)
#define ISP_IRQ_P1_STATUS_TG1_INT2_ST               ((unsigned int)1<<2)
#define ISP_IRQ_P1_STATUS_EXPDON1_ST                ((unsigned int)1<<3)
#define ISP_IRQ_P1_STATUS_TG1_ERR_ST                ((unsigned int)1<<4)
#define ISP_IRQ_P1_STATUS_TG1_GBERR                 ((unsigned int)1<<5)
#define ISP_IRQ_P1_STATUS_CQ0_ERR                   ((unsigned int)1<<6)
#define ISP_IRQ_P1_STATUS_CQ0_VS_ERR_ST             ((unsigned int)1<<7)
#define ISP_IRQ_P1_STATUS_IMGO_DROP_FRAME_ST        ((unsigned int)1<<8)
#define ISP_IRQ_P1_STATUS_RRZO_DROP_FRAME_ST        ((unsigned int)1<<9)
#define ISP_IRQ_P1_STATUS_PASS1_DON_ST              ((unsigned int)1<<10)
#define ISP_IRQ_P1_STATUS_rsv_11                    ((unsigned int)1<<11)
#define ISP_IRQ_P1_STATUS_SOF1_INT_ST               ((unsigned int)1<<12)
#define ISP_IRQ_P1_STATUS_rsv_13                    ((unsigned int)1<<13)
#define ISP_IRQ_P1_STATUS_AF_DON_ST                 ((unsigned int)1<<16)
#define ISP_IRQ_P1_STATUS_FLK_DON_ST                ((unsigned int)1<<17)
#define ISP_IRQ_P1_STATUS_rsv_18                    ((unsigned int)1<<18)
#define ISP_IRQ_P1_STATUS_IMGO_ERR_ST               ((unsigned int)1<<20)
#define ISP_IRQ_P1_STATUS_AAO_ERR_ST                ((unsigned int)1<<21)
#define ISP_IRQ_P1_STATUS_LCSO_ERR_ST               ((unsigned int)1<<22)
#define ISP_IRQ_P1_STATUS_RRZO_ERR_ST               ((unsigned int)1<<23)
#define ISP_IRQ_P1_STATUS_ESFKO_ERR_ST              ((unsigned int)1<<24)
#define ISP_IRQ_P1_STATUS_FLK_ERR_ST                ((unsigned int)1<<25)
#define ISP_IRQ_P1_STATUS_LSC_ERR_ST                ((unsigned int)1<<26)
#define ISP_IRQ_P1_STATUS_FBC_RRZO_DON_ST           ((unsigned int)1<<27)
#define ISP_IRQ_P1_STATUS_FBC_IMGO_DON_ST           ((unsigned int)1<<28)
#define ISP_IRQ_P1_STATUS_rsv_29                    ((unsigned int)1<<29)
#define ISP_IRQ_P1_STATUS_DMA_ERR_ST                ((unsigned int)1<<30)
#define ISP_IRQ_P1_STATUS_rsv_31                    ((unsigned int)1<<31)
#define ISP_IRQ_P1_STATUS2_IMGO_DONE_ST              ((unsigned int)1<<0)
#define ISP_IRQ_P1_STATUS2_UFEO_DONE_ST              ((unsigned int)1<<1)
#define ISP_IRQ_P1_STATUS2_RRZO_DONE_ST              ((unsigned int)1<<2)
#define ISP_IRQ_P1_STATUS2_ESFKO_DONE_ST             ((unsigned int)1<<3)
#define ISP_IRQ_P1_STATUS2_LCSO_DONE_ST              ((unsigned int)1<<4)
#define ISP_IRQ_P1_STATUS2_AAO_DONE_ST               ((unsigned int)1<<5)
#define ISP_IRQ_P1_STATUS2_BPCI_DONE_ST              ((unsigned int)1<<6)
#define ISP_IRQ_P1_STATUS2_LSCI_DONE_ST              ((unsigned int)1<<7)
#define ISP_IRQ_P1_STATUS2_AF_TAR_DONE_ST            ((unsigned int)1<<8)
#define ISP_IRQ_P1_STATUS2_AF_FLO1_DONE_ST           ((unsigned int)1<<9)
#define ISP_IRQ_P1_STATUS2_AF_FLO2_DONE_ST           ((unsigned int)1<<10)
#define ISP_IRQ_P1_STATUS2_AF_FLO3_DONE_ST           ((unsigned int)1<<11)
#define ISP_IRQ_P1_STATUS2_rsv_12                    ((unsigned int)1<<12)
#define ISP_IRQ_P1_STATUS_D_VS1_INT_ST                ((unsigned int)1<<0)
#define ISP_IRQ_P1_STATUS_D_TG1_INT1_ST               ((unsigned int)1<<1)
#define ISP_IRQ_P1_STATUS_D_TG1_INT2_ST               ((unsigned int)1<<2)
#define ISP_IRQ_P1_STATUS_D_EXPDON1_ST                ((unsigned int)1<<3)
#define ISP_IRQ_P1_STATUS_D_TG1_ERR_ST                ((unsigned int)1<<4)
#define ISP_IRQ_P1_STATUS_D_TG1_GBERR                 ((unsigned int)1<<5)
#define ISP_IRQ_P1_STATUS_D_CQ0_ERR                   ((unsigned int)1<<6)
#define ISP_IRQ_P1_STATUS_D_CQ0_VS_ERR_ST             ((unsigned int)1<<7)
#define ISP_IRQ_P1_STATUS_D_IMGO_DROP_FRAME_ST        ((unsigned int)1<<8)
#define ISP_IRQ_P1_STATUS_D_RRZO_DROP_FRAME_ST        ((unsigned int)1<<9)
#define ISP_IRQ_P1_STATUS_D_PASS1_DON_ST              ((unsigned int)1<<10)
#define ISP_IRQ_P1_STATUS_D_rsv_11                    ((unsigned int)1<<11)
#define ISP_IRQ_P1_STATUS_D_SOF1_INT_ST               ((unsigned int)1<<12)
#define ISP_IRQ_P1_STATUS_D_rsv_13                    ((unsigned int)1<<13)
#define ISP_IRQ_P1_STATUS_D_AF_DON_ST                 ((unsigned int)1<<16)
#define ISP_IRQ_P1_STATUS_D_rsv_17                    ((unsigned int)1<<17)
#define ISP_IRQ_P1_STATUS_D_IMGO_ERR_ST               ((unsigned int)1<<20)
#define ISP_IRQ_P1_STATUS_D_AAO_ERR_ST                ((unsigned int)1<<21)
#define ISP_IRQ_P1_STATUS_D_LCSO_ERR_ST               ((unsigned int)1<<22)
#define ISP_IRQ_P1_STATUS_D_RRZO_ERR_ST               ((unsigned int)1<<23)
#define ISP_IRQ_P1_STATUS_D_AFO_ERR_ST                ((unsigned int)1<<24)
#define ISP_IRQ_P1_STATUS_D_rsv_25                    ((unsigned int)1<<25)
#define ISP_IRQ_P1_STATUS_D_LSC_ERR_ST                ((unsigned int)1<<26)
#define ISP_IRQ_P1_STATUS_D_FBC_RRZO_DON_ST           ((unsigned int)1<<27)
#define ISP_IRQ_P1_STATUS_D_FBC_IMGO_DON_ST           ((unsigned int)1<<28)
#define ISP_IRQ_P1_STATUS_D_rsv_29                    ((unsigned int)1<<29)
#define ISP_IRQ_P1_STATUS_D_DMA_ERR_ST                ((unsigned int)1<<30)
#define ISP_IRQ_P1_STATUS_D_rsv_31                    ((unsigned int)1<<31)
#define ISP_IRQ_P1_STATUS2_D_IMGO_D_DONE_ST            ((unsigned int)1<<0)
#define ISP_IRQ_P1_STATUS2_D_rsv_1                     ((unsigned int)1<<1)
#define ISP_IRQ_P1_STATUS2_D_RRZO_D_DONE_ST            ((unsigned int)1<<2)
#define ISP_IRQ_P1_STATUS2_D_AFO_D_DONE_ST             ((unsigned int)1<<3)
#define ISP_IRQ_P1_STATUS2_D_LCSO_D_DONE_ST            ((unsigned int)1<<4)
#define ISP_IRQ_P1_STATUS2_D_AAO_D_DONE_ST             ((unsigned int)1<<5)
#define ISP_IRQ_P1_STATUS2_D_BPCI_D_DONE_ST            ((unsigned int)1<<6)
#define ISP_IRQ_P1_STATUS2_D_LSCI_D_DONE_ST            ((unsigned int)1<<7)
#define ISP_IRQ_P1_STATUS2_D_AF_TAR_DONE_ST            ((unsigned int)1<<8)
#define ISP_IRQ_P1_STATUS2_D_AF_FLO1_DONE_ST           ((unsigned int)1<<9)
#define ISP_IRQ_P1_STATUS2_D_AF_FLO2_DONE_ST           ((unsigned int)1<<10)
#define ISP_IRQ_P1_STATUS2_D_AF_FLO3_DONE_ST           ((unsigned int)1<<11)
#define ISP_IRQ_P1_STATUS2_D_rsv_12                    ((unsigned int)1<<12)
#define ISP_CAM_CTL_SEL_P1_IMGO_SEL                    ((unsigned int)1<<6)
#define ISP_CAM_CTL_SEL_P1_D_IMGO_SEL                  ((unsigned int)1<<6)


#define ISP_IRQ_P2_STATUS_CQ_ERR_ST                 ((unsigned int)1<<0)
#define ISP_IRQ_P2_STATUS_PASS2_DON_ST              ((unsigned int)1<<1)
#define ISP_IRQ_P2_STATUS_TILE_DON_ST               ((unsigned int)1<<2)
#define ISP_IRQ_P2_STATUS_CQ_DON_ST                 ((unsigned int)1<<3)
#define ISP_IRQ_P2_STATUS_TDR_ERR_ST                ((unsigned int)1<<4)
#define ISP_IRQ_P2_STATUS_PASS2A_DON_ST             ((unsigned int)1<<5)
#define ISP_IRQ_P2_STATUS_PASS2B_DON_ST             ((unsigned int)1<<6)
#define ISP_IRQ_P2_STATUS_PASS2C_DON_ST             ((unsigned int)1<<7)
#define ISP_IRQ_P2_STATUS_CQ1_DONE_ST               ((unsigned int)1<<8)
#define ISP_IRQ_P2_STATUS_CQ2_DONE_ST               ((unsigned int)1<<9)
#define ISP_IRQ_P2_STATUS_CQ3_DONE_ST               ((unsigned int)1<<10)
#define ISP_IRQ_P2_STATUS_PASS2A_ERR_TRIG_ST        ((unsigned int)1<<11)
#define ISP_IRQ_P2_STATUS_PASS2B_ERR_TRIG_ST        ((unsigned int)1<<12)
#define ISP_IRQ_P2_STATUS_PASS2C_ERR_TRIG_ST        ((unsigned int)1<<13)
#define ISP_IRQ_P2_STATUS_IMGI_DONE_ST              ((unsigned int)1<<15)
#define ISP_IRQ_P2_STATUS_UFDI_DONE_ST              ((unsigned int)1<<16)
#define ISP_IRQ_P2_STATUS_VIPI_DONE_ST              ((unsigned int)1<<17)
#define ISP_IRQ_P2_STATUS_VIP2I_DONE_ST             ((unsigned int)1<<18)
#define ISP_IRQ_P2_STATUS_VIP3I_DONE_ST             ((unsigned int)1<<19)
#define ISP_IRQ_P2_STATUS_LCEI_DONE_ST              ((unsigned int)1<<20)
#define ISP_IRQ_P2_STATUS_MFBO_DONE_ST              ((unsigned int)1<<21)
#define ISP_IRQ_P2_STATUS_IMG2O_DONE_ST             ((unsigned int)1<<22)
#define ISP_IRQ_P2_STATUS_IMG3O_DONE_ST             ((unsigned int)1<<23)
#define ISP_IRQ_P2_STATUS_IMG3BO_DONE_ST            ((unsigned int)1<<24)
#define ISP_IRQ_P2_STATUS_IMG3CO_DONE_ST            ((unsigned int)1<<25)
#define ISP_IRQ_P2_STATUS_FEO_DONE_ST               ((unsigned int)1<<26)
#define ISP_IRQ_P2_STATUS_rsv_27                    ((unsigned int)1<<27)
#define ISP_IRQ_STATUSX_VS1_INT_ST                ((unsigned int)1<<0)
#define ISP_IRQ_STATUSX_TG1_INT1_ST               ((unsigned int)1<<1)
#define ISP_IRQ_STATUSX_TG1_INT2_ST               ((unsigned int)1<<2)
#define ISP_IRQ_STATUSX_EXPDON1_ST                ((unsigned int)1<<3)
#define ISP_IRQ_STATUSX_TG1_ERR_ST                ((unsigned int)1<<4)
#define ISP_IRQ_STATUSX_TG1_GBERR                 ((unsigned int)1<<5)
#define ISP_IRQ_STATUSX_CQ0_ERR                   ((unsigned int)1<<6)
#define ISP_IRQ_STATUSX_CQ0_VS_ERR_ST             ((unsigned int)1<<7)
#define ISP_IRQ_STATUSX_IMGO_DROP_FRAME_ST        ((unsigned int)1<<8)
#define ISP_IRQ_STATUSX_RRZO_DROP_FRAME_ST        ((unsigned int)1<<9)
#define ISP_IRQ_STATUSX_PASS1_DON_ST              ((unsigned int)1<<10)
#define ISP_IRQ_STATUSX_rsv_11                    ((unsigned int)1<<11)
#define ISP_IRQ_STATUSX_SOF1_INT_ST               ((unsigned int)1<<12)
#define ISP_IRQ_STATUSX_CQ_ERR_ST                 ((unsigned int)1<<13)
#define ISP_IRQ_STATUSX_PASS2_DON_ST              ((unsigned int)1<<14)
#define ISP_IRQ_STATUSX_TILE_DON_ST               ((unsigned int)1<<15)
#define ISP_IRQ_STATUSX_AF_DON_ST                 ((unsigned int)1<<16)
#define ISP_IRQ_STATUSX_FLK_DON_ST                ((unsigned int)1<<17)
#define ISP_IRQ_STATUSX_rsv_18					  ((unsigned int)1<<18)
#define ISP_IRQ_STATUSX_CQ_DON_ST                 ((unsigned int)1<<19)
#define ISP_IRQ_STATUSX_IMGO_ERR_ST               ((unsigned int)1<<20)
#define ISP_IRQ_STATUSX_AAO_ERR_ST                ((unsigned int)1<<21)
#define ISP_IRQ_STATUSX_LCSO_ERR_ST               ((unsigned int)1<<22)
#define ISP_IRQ_STATUSX_RRZO_ERR_ST               ((unsigned int)1<<23)
#define ISP_IRQ_STATUSX_ESFKO_ERR_ST              ((unsigned int)1<<24)
#define ISP_IRQ_STATUSX_FLK_ERR_ST                ((unsigned int)1<<25)
#define ISP_IRQ_STATUSX_LSC_ERR_ST                ((unsigned int)1<<26)
#define ISP_IRQ_STATUSX_FBC_RRZO_DON_ST           ((unsigned int)1<<27)
#define ISP_IRQ_STATUSX_FBC_IMGO_DON_ST           ((unsigned int)1<<28)
#define ISP_IRQ_STATUSX_rsv_29                    ((unsigned int)1<<29)
#define ISP_IRQ_STATUSX_DMA_ERR_ST                ((unsigned int)1<<30)
#define ISP_IRQ_STATUSX_rsv_31                    ((unsigned int)1<<31)
#define ISP_IRQ_STATUS2X_VS1_INT_ST                ((unsigned int)1<<0)
#define ISP_IRQ_STATUS2X_TG1_INT1_ST               ((unsigned int)1<<1)
#define ISP_IRQ_STATUS2X_TG1_INT2_ST               ((unsigned int)1<<2)
#define ISP_IRQ_STATUS2X_EXPDON1_ST                ((unsigned int)1<<3)
#define ISP_IRQ_STATUS2X_TG1_ERR_ST                ((unsigned int)1<<4)
#define ISP_IRQ_STATUS2X_TG1_GBERR                 ((unsigned int)1<<5)
#define ISP_IRQ_STATUS2X_CQ0_ERR                   ((unsigned int)1<<6)
#define ISP_IRQ_STATUS2X_CQ0_VS_ERR_ST             ((unsigned int)1<<7)
#define ISP_IRQ_STATUS2X_IMGO_DROP_FRAME_ST        ((unsigned int)1<<8)
#define ISP_IRQ_STATUS2X_RRZO_DROP_FRAME_ST        ((unsigned int)1<<9)
#define ISP_IRQ_STATUS2X_PASS1_DON_ST              ((unsigned int)1<<10)
#define ISP_IRQ_STATUS2X_rsv_11                    ((unsigned int)1<<11)
#define ISP_IRQ_STATUS2X_SOF1_INT_ST               ((unsigned int)1<<12)
#define ISP_IRQ_STATUS2X_rsv_13                    ((unsigned int)1<<13)
#define ISP_IRQ_STATUS2X_rsv_14                    ((unsigned int)1<<14)
#define ISP_IRQ_STATUS2X_rsv_15                    ((unsigned int)1<<15)
#define ISP_IRQ_STATUS2X_AF_DON_ST                 ((unsigned int)1<<16)
#define ISP_IRQ_STATUS2X_rsv_17                    ((unsigned int)1<<17)
#define ISP_IRQ_STATUS2X_rsv_18					   ((unsigned int)1<<18)
#define ISP_IRQ_STATUS2X_rsv_19                    ((unsigned int)1<<19)
#define ISP_IRQ_STATUS2X_IMGO_ERR_ST               ((unsigned int)1<<20)
#define ISP_IRQ_STATUS2X_AAO_ERR_ST                ((unsigned int)1<<21)
#define ISP_IRQ_STATUS2X_LCSO_ERR_ST               ((unsigned int)1<<22)
#define ISP_IRQ_STATUS2X_RRZO_ERR_ST               ((unsigned int)1<<23)
#define ISP_IRQ_STATUS2X_AFO_ERR_ST                ((unsigned int)1<<24)
#define ISP_IRQ_STATUS2X_rsv_25                    ((unsigned int)1<<25)
#define ISP_IRQ_STATUS2X_LSC_ERR_ST                ((unsigned int)1<<26)
#define ISP_IRQ_STATUS2X_FBC_RRZO_DON_ST           ((unsigned int)1<<27)
#define ISP_IRQ_STATUS2X_FBC_IMGO_DON_ST           ((unsigned int)1<<28)
#define ISP_IRQ_STATUS2X_rsv_29                    ((unsigned int)1<<29)
#define ISP_IRQ_STATUS2X_DMA_ERR_ST                ((unsigned int)1<<30)
#define ISP_IRQ_STATUS2X_rsv_31                    ((unsigned int)1<<31)
#define ISP_IRQ_STATUS3X_IMGO_DONE_ST              ((unsigned int)1<<0)
#define ISP_IRQ_STATUS3X_UFEO_DONE_ST              ((unsigned int)1<<1)
#define ISP_IRQ_STATUS3X_RRZO_DONE_ST              ((unsigned int)1<<2)
#define ISP_IRQ_STATUS3X_ESFKO_DONE_ST             ((unsigned int)1<<3)
#define ISP_IRQ_STATUS3X_LCSO_DONE_ST              ((unsigned int)1<<4)
#define ISP_IRQ_STATUS3X_AAO_DONE_ST               ((unsigned int)1<<5)
#define ISP_IRQ_STATUS3X_BPCI_DONE_ST              ((unsigned int)1<<6)
#define ISP_IRQ_STATUS3X_LSCI_DONE_ST              ((unsigned int)1<<7)
#define ISP_IRQ_STATUS3X_IMGO_D_DONE_ST            ((unsigned int)1<<8)
#define ISP_IRQ_STATUS3X_RRZO_D_DONE_ST            ((unsigned int)1<<9)
#define ISP_IRQ_STATUS3X_AFO_D_DONE_ST             ((unsigned int)1<<10)
#define ISP_IRQ_STATUS3X_LCSO_D_DONE_ST            ((unsigned int)1<<11)
#define ISP_IRQ_STATUS3X_AAO_D_DONE_ST             ((unsigned int)1<<12)
#define ISP_IRQ_STATUS3X_BPCI_D_DONE_ST            ((unsigned int)1<<13)
#define ISP_IRQ_STATUS3X_LCSI_D_DONE_ST            ((unsigned int)1<<14)
#define ISP_IRQ_STATUS3X_IMGI_DONE_ST              ((unsigned int)1<<15)
#define ISP_IRQ_STATUS3X_UFDI_DONE_ST              ((unsigned int)1<<16)
#define ISP_IRQ_STATUS3X_VIPI_DONE_ST              ((unsigned int)1<<17)
#define ISP_IRQ_STATUS3X_VIP2I_DONE_ST			   ((unsigned int)1<<18)
#define ISP_IRQ_STATUS3X_VIP3I_DONE_ST             ((unsigned int)1<<19)
#define ISP_IRQ_STATUS3X_LCEI_DONE_ST              ((unsigned int)1<<20)
#define ISP_IRQ_STATUS3X_MFBO_DONE_ST              ((unsigned int)1<<21)
#define ISP_IRQ_STATUS3X_IMG2O_DONE_ST             ((unsigned int)1<<22)
#define ISP_IRQ_STATUS3X_IMG3O_DONE_ST             ((unsigned int)1<<23)
#define ISP_IRQ_STATUS3X_IMG3BO_DONE_ST            ((unsigned int)1<<24)
#define ISP_IRQ_STATUS3X_IMG3CO_DONE_ST            ((unsigned int)1<<25)
#define ISP_IRQ_STATUS3X_FEO_DONE_ST               ((unsigned int)1<<26)
#define ISP_IRQ_STATUS3X_rsv_27                    ((unsigned int)1<<27)
#define ISP_IRQ_STATUS3X_rsv_28                    ((unsigned int)1<<28)
#define ISP_IRQ_STATUS3X_rsv_29                    ((unsigned int)1<<29)
#define ISP_IRQ_STATUS3X_rsv_30                    ((unsigned int)1<<30)
#define ISP_IRQ_STATUS3X_rsv_31                    ((unsigned int)1<<31)
#define SENINF1_IRQ_OVERRUN_IRQ_STA					   ((unsigned int)1<<0)
#define SENINF1_IRQ_CRCERR_IRQ_STA					   ((unsigned int)1<<1)
#define SENINF1_IRQ_FSMERR_IRQ_STA					   ((unsigned int)1<<2)
#define SENINF1_IRQ_VSIZEERR_IRQ_STA				   ((unsigned int)1<<3)
#define SENINF1_IRQ_HSIZEERR_IRQ_STA				   ((unsigned int)1<<4)
#define SENINF1_IRQ_SENSOR_VSIZEERR_IRQ_STA			   ((unsigned int)1<<5)
#define SENINF1_IRQ_SENSOR_HSIZEERR_IRQ_STA			   ((unsigned int)1<<6)
#define SENINF2_IRQ_OVERRUN_IRQ_STA					   ((unsigned int)1<<0)
#define SENINF2_IRQ_CRCERR_IRQ_STA					   ((unsigned int)1<<1)
#define SENINF2_IRQ_FSMERR_IRQ_STA					   ((unsigned int)1<<2)
#define SENINF2_IRQ_VSIZEERR_IRQ_STA				   ((unsigned int)1<<3)
#define SENINF2_IRQ_HSIZEERR_IRQ_STA				   ((unsigned int)1<<4)
#define SENINF2_IRQ_SENSOR_VSIZEERR_IRQ_STA			   ((unsigned int)1<<5)
#define SENINF2_IRQ_SENSOR_HSIZEERR_IRQ_STA			   ((unsigned int)1<<6)
#define SENINF3_IRQ_OVERRUN_IRQ_STA					   ((unsigned int)1<<0)
#define SENINF3_IRQ_CRCERR_IRQ_STA					   ((unsigned int)1<<1)
#define SENINF3_IRQ_FSMERR_IRQ_STA					   ((unsigned int)1<<2)
#define SENINF3_IRQ_VSIZEERR_IRQ_STA				   ((unsigned int)1<<3)
#define SENINF3_IRQ_HSIZEERR_IRQ_STA				   ((unsigned int)1<<4)
#define SENINF3_IRQ_SENSOR_VSIZEERR_IRQ_STA			   ((unsigned int)1<<5)
#define SENINF3_IRQ_SENSOR_HSIZEERR_IRQ_STA			   ((unsigned int)1<<6)
#define SENINF4_IRQ_OVERRUN_IRQ_STA					   ((unsigned int)1<<0)
#define SENINF4_IRQ_CRCERR_IRQ_STA					   ((unsigned int)1<<1)
#define SENINF4_IRQ_FSMERR_IRQ_STA					   ((unsigned int)1<<2)
#define SENINF4_IRQ_VSIZEERR_IRQ_STA				   ((unsigned int)1<<3)
#define SENINF4_IRQ_HSIZEERR_IRQ_STA				   ((unsigned int)1<<4)
#define SENINF4_IRQ_SENSOR_VSIZEERR_IRQ_STA			   ((unsigned int)1<<5)
#define SENINF4_IRQ_SENSOR_HSIZEERR_IRQ_STA			   ((unsigned int)1<<6)
#define ISP_IRQ_CAMSV_STATUS_VS1_ST						((unsigned int)1<<0)
#define ISP_IRQ_CAMSV_STATUS_TG_ST1						((unsigned int)1<<1)
#define ISP_IRQ_CAMSV_STATUS_TG_ST2						((unsigned int)1<<2)
#define ISP_IRQ_CAMSV_STATUS_EXPDON1_ST					((unsigned int)1<<3)
#define ISP_IRQ_CAMSV_STATUS_TG_ERR_ST					((unsigned int)1<<4)
#define ISP_IRQ_CAMSV_STATUS_TG_GBERR_ST				((unsigned int)1<<5)
#define ISP_IRQ_CAMSV_STATUS_TG_DROP_ST					((unsigned int)1<<6)
#define ISP_IRQ_CAMSV_STATUS_TG_SOF1_ST					((unsigned int)1<<7)
#define ISP_IRQ_CAMSV_STATUS_rsv_8						((unsigned int)1<<8)
#define ISP_IRQ_CAMSV_STATUS_rsv_9						((unsigned int)1<<9)
#define ISP_IRQ_CAMSV_STATUS_PASS1_DON_ST				((unsigned int)1<<10)
#define ISP_IRQ_CAMSV_STATUS_rsv_11						((unsigned int)1<<11)
#define ISP_IRQ_CAMSV_STATUS_rsv_12						((unsigned int)1<<12)
#define ISP_IRQ_CAMSV_STATUS_rsv_13						((unsigned int)1<<13)
#define ISP_IRQ_CAMSV_STATUS_rsv_14						((unsigned int)1<<14)
#define ISP_IRQ_CAMSV_STATUS_rsv_15						((unsigned int)1<<15)
#define ISP_IRQ_CAMSV_STATUS_IMGO_ERR_ST				((unsigned int)1<<16)
#define ISP_IRQ_CAMSV_STATUS_IMGO_OVERR_ST				((unsigned int)1<<17)
#define ISP_IRQ_CAMSV_STATUS_rsv_18						((unsigned int)1<<18)
#define ISP_IRQ_CAMSV_STATUS_IMGO_DROP_ST				((unsigned int)1<<19)
#define ISP_IRQ_CAMSV2_STATUS_VS1_ST					((unsigned int)1<<0)
#define ISP_IRQ_CAMSV2_STATUS_TG_ST1					((unsigned int)1<<1)
#define ISP_IRQ_CAMSV2_STATUS_TG_ST2					((unsigned int)1<<2)
#define ISP_IRQ_CAMSV2_STATUS_EXPDON1_ST				((unsigned int)1<<3)
#define ISP_IRQ_CAMSV2_STATUS_TG_ERR_ST					((unsigned int)1<<4)
#define ISP_IRQ_CAMSV2_STATUS_TG_GBERR_ST				((unsigned int)1<<5)
#define ISP_IRQ_CAMSV2_STATUS_TG_DROP_ST				((unsigned int)1<<6)
#define ISP_IRQ_CAMSV2_STATUS_TG_SOF1_ST				((unsigned int)1<<7)
#define ISP_IRQ_CAMSV2_STATUS_rsv_8						((unsigned int)1<<8)
#define ISP_IRQ_CAMSV2_STATUS_rsv_9						((unsigned int)1<<9)
#define ISP_IRQ_CAMSV2_STATUS_PASS1_DON_ST				((unsigned int)1<<10)
#define ISP_IRQ_CAMSV2_STATUS_rsv_11					((unsigned int)1<<11)
#define ISP_IRQ_CAMSV2_STATUS_rsv_12					((unsigned int)1<<12)
#define ISP_IRQ_CAMSV2_STATUS_rsv_13					((unsigned int)1<<13)
#define ISP_IRQ_CAMSV2_STATUS_rsv_14					((unsigned int)1<<14)
#define ISP_IRQ_CAMSV2_STATUS_rsv_15					((unsigned int)1<<15)
#define ISP_IRQ_CAMSV2_STATUS_IMGO_ERR_ST				((unsigned int)1<<16)
#define ISP_IRQ_CAMSV2_STATUS_IMGO_OVERR_ST				((unsigned int)1<<17)
#define ISP_IRQ_CAMSV2_STATUS_rsv_18					((unsigned int)1<<18)
#define ISP_IRQ_CAMSV2_STATUS_IMGO_DROP_ST				((unsigned int)1<<19)


#define _rtbc_buf_que_2_0_


typedef enum
{
    ISP_IRQ_CLEAR_NONE,
    ISP_IRQ_CLEAR_WAIT,
    ISP_IRQ_CLEAR_STATUS,
    ISP_IRQ_CLEAR_ALL
}ISP_IRQ_CLEAR_ENUM;

typedef enum
{
	ISP_IRQ_TYPE_INT_P1_ST,		
	ISP_IRQ_TYPE_INT_P1_ST2,	
	ISP_IRQ_TYPE_INT_P1_ST_D,	
	ISP_IRQ_TYPE_INT_P1_ST2_D,	
	ISP_IRQ_TYPE_INT_P2_ST,		
	ISP_IRQ_TYPE_INT_STATUSX,	
	ISP_IRQ_TYPE_INT_STATUS2X,	
	ISP_IRQ_TYPE_INT_STATUS3X,	
	ISP_IRQ_TYPE_ISP_AMOUNT,
	ISP_IRQ_TYPE_INT_SENINF1=ISP_IRQ_TYPE_ISP_AMOUNT,
	ISP_IRQ_TYPE_INT_SENINF2,
	ISP_IRQ_TYPE_INT_SENINF3,
	ISP_IRQ_TYPE_INT_SENINF4,
	ISP_IRQ_TYPE_SENINF_AMOUNT,
	ISP_IRQ_TYPE_INT_CAMSV=ISP_IRQ_TYPE_SENINF_AMOUNT,
	ISP_IRQ_TYPE_INT_CAMSV2,
    ISP_IRQ_TYPE_AMOUNT
}ISP_IRQ_TYPE_ENUM;


typedef enum
{
    ISP_IRQ_USER_ISPDRV =   0,
    ISP_IRQ_USER_MW     =   1,
    ISP_IRQ_USER_3A     =   2,
    ISP_IRQ_USER_HWSYNC =   3,
    ISP_IRQ_USER_ACDK   =   4,
    ISP_IRQ_USER_EIS    =   5,
    ISP_IRQ_USER_VHDR   =   6,
    ISP_IRQ_USER_MAX
}ISP_IRQ_USER_ENUM;
typedef enum    
{
    ISP_IRQ_WAITIRQ_SPEUSER_NONE = 0,
    ISP_IRQ_WAITIRQ_SPEUSER_EIS = 1,
    ISP_IRQ_WAITIRQ_SPEUSER_NUM
}ISP_IRQ_WAITIRQ_SPEUSER_ENUM;

typedef struct
{
     unsigned int    tLastSig_sec;                       
    unsigned int    tLastSig_usec;                  
}ISP_IRQ_TIME_STRUCT;

typedef struct
{
    unsigned int       tLastSOF2P1done_sec;                       
    unsigned int       tLastSOF2P1done_usec;                  
}ISP_EIS_META_STRUCT;


typedef struct
{
    ISP_IRQ_CLEAR_ENUM  Clear;		
    ISP_IRQ_TYPE_ENUM   Type;
    unsigned int        Status;
    int                 UserNumber;
    unsigned int        Timeout;
	char*			    UserName;
	unsigned int        irq_TStamp;
    unsigned int        bDumpReg;
    ISP_IRQ_TIME_STRUCT  TimeInfo;  
     ISP_EIS_META_STRUCT EisMeta;
    ISP_IRQ_WAITIRQ_SPEUSER_ENUM SpecUser;
}ISP_WAIT_IRQ_STRUCT;

typedef struct
{
    ISP_IRQ_TYPE_ENUM   Type;
    ISP_IRQ_USER_ENUM   UserNumber;
    unsigned int       Status;
}ISP_READ_IRQ_STRUCT;

typedef struct
{
    ISP_IRQ_TYPE_ENUM   Type;
    ISP_IRQ_USER_ENUM   UserNumber;
    unsigned int       Status;
}ISP_CLEAR_IRQ_STRUCT;

typedef enum
{
    ISP_HOLD_TIME_VD,
    ISP_HOLD_TIME_EXPDONE
}ISP_HOLD_TIME_ENUM;

typedef struct
{
    unsigned int Addr;   
    unsigned int Val;    
}ISP_REG_STRUCT;

typedef struct
{
    
    ISP_REG_STRUCT* pData;   
    unsigned int Count;  
}ISP_REG_IO_STRUCT;

typedef void (*pIspCallback)(void);

typedef enum
{
    
    ISP_CALLBACK_WORKQUEUE_VD,
    ISP_CALLBACK_WORKQUEUE_EXPDONE,
    
    ISP_CALLBACK_TASKLET_VD,
    ISP_CALLBACK_TASKLET_EXPDONE,
    ISP_CALLBACK_AMOUNT
}ISP_CALLBACK_ENUM;

typedef struct
{
    ISP_CALLBACK_ENUM   Type;
    pIspCallback        Func;
}ISP_CALLBACK_STRUCT;

#define P1_DEQUE_CNT    1
#define RT_BUF_TBL_NPAGES 16
#define ISP_RT_BUF_SIZE 16
#define ISP_RT_CQ0C_BUF_SIZE (ISP_RT_BUF_SIZE)
#define ISP_REG_P1_CFG_IDX 0x4090
typedef enum
{
    _cam_tg_  = 0,
    _cam_tg2_ ,     
    _camsv_tg_,     
    _camsv2_tg_,    
    _cam_tg_max_
}_isp_tg_enum_;

typedef enum
{
    _imgi_  = 0,
    _vipi_ ,    
    _vip2i_,    
    _vip3i_,    
    _imgo_,     
    _ufdi_,     
    _lcei_,     
    _ufeo_,     
    _rrzo_,     
    _imgo_d_,   
    _rrzo_d_,   
    _img2o_,    
    _img3o_,    
    _img3bo_,   
    _img3co_,   
    _camsv_imgo_,  
    _camsv2_imgo_,
    _mfbo_,     
    _feo_,      
    _wrot_,    
    _wdma_,     
    _jpeg_,     
    _venc_stream_,     
    _rt_dma_max_
}_isp_dma_enum_;
typedef struct {
    unsigned int   w;       
    unsigned int   h;
    unsigned int   xsize;   
    unsigned int   stride;  
    unsigned int   fmt;
    unsigned int   pxl_id;
    unsigned int   wbn;
    unsigned int   ob;
    unsigned int   lsc;
    unsigned int   rpg;
    unsigned int   m_num_0;
    unsigned int   frm_cnt;
    unsigned int   bus_size;
}ISP_RT_IMAGE_INFO_STRUCT;

typedef struct {
    unsigned int   srcX;    
    unsigned int   srcY;    
    unsigned int   srcW;    
    unsigned int   srcH;
    unsigned int   dstW;    
    unsigned int   dstH;
}ISP_RT_RRZ_INFO_STRUCT;

typedef struct{
    unsigned int x; 
    unsigned int y; 
    unsigned int w; 
    unsigned int h; 
}ISP_RT_DMAO_CROPPING_STRUCT;

typedef struct {
    unsigned int   memID;
    unsigned int   size;
    long long      base_vAddr;
    unsigned int   base_pAddr;
    unsigned int   timeStampS;
    unsigned int   timeStampUs;
    unsigned int   bFilled;
    unsigned int   bProcessRaw;
    ISP_RT_IMAGE_INFO_STRUCT image;
    ISP_RT_RRZ_INFO_STRUCT rrzInfo;
    ISP_RT_DMAO_CROPPING_STRUCT dmaoCrop;   
    unsigned int          bDequeued;
    signed int         bufIdx;
}ISP_RT_BUF_INFO_STRUCT;
typedef struct  {
    unsigned int           count;
    unsigned int           sof_cnt;         
    unsigned int           img_cnt;         
    
    
    ISP_RT_BUF_INFO_STRUCT  data[P1_DEQUE_CNT];
}ISP_DEQUE_BUF_INFO_STRUCT;
typedef struct  {
    unsigned int           start;          
    unsigned int           total_count;    
    unsigned int           empty_count;    
    unsigned int           pre_empty_count;
    unsigned int           active;
    unsigned int           read_idx;
    unsigned int           img_cnt;         
    ISP_RT_BUF_INFO_STRUCT  data[ISP_RT_BUF_SIZE];
}ISP_RT_RING_BUF_INFO_STRUCT;
typedef enum
{
    ISP_RT_BUF_CTRL_ENQUE,      
#ifdef _rtbc_buf_que_2_0_    
    ISP_RT_BUF_CTRL_ENQUE_IMD,  
#else
    ISP_RT_BUF_CTRL_ENQUE_IMD = ISP_RT_BUF_CTRL_ENQUE,
#endif    
    ISP_RT_BUF_CTRL_EXCHANGE_ENQUE, 
    ISP_RT_BUF_CTRL_DEQUE,          
    ISP_RT_BUF_CTRL_IS_RDY,         
#ifdef _rtbc_buf_que_2_0_
    ISP_RT_BUF_CTRL_DMA_EN,           
#endif
    ISP_RT_BUF_CTRL_GET_SIZE,       
    ISP_RT_BUF_CTRL_CLEAR,          
    ISP_RT_BUF_CTRL_CUR_STATUS,     
    ISP_RT_BUF_CTRL_MAX
}ISP_RT_BUF_CTRL_ENUM;
typedef enum
{
    ISP_RTBC_STATE_INIT, 
    ISP_RTBC_STATE_SOF,
    ISP_RTBC_STATE_DONE,
    ISP_RTBC_STATE_MAX
}ISP_RTBC_STATE_ENUM;
typedef enum
{
    ISP_RTBC_BUF_EMPTY, 
    ISP_RTBC_BUF_FILLED,
    ISP_RTBC_BUF_LOCKED,
}ISP_RTBC_BUF_STATE_ENUM;
typedef enum
{
    ISP_RROCESSED_RAW,
    ISP_PURE_RAW, 
}ISP_RAW_TYPE_ENUM;
typedef struct  {
    ISP_RTBC_STATE_ENUM state;
    unsigned long dropCnt;
    ISP_RT_RING_BUF_INFO_STRUCT  ring_buf[_rt_dma_max_];
}ISP_RT_BUF_STRUCT;
typedef struct  {
    ISP_RT_BUF_CTRL_ENUM    ctrl;
    _isp_dma_enum_          buf_id;
    
    
    ISP_RT_BUF_INFO_STRUCT*  data_ptr;
    ISP_RT_BUF_INFO_STRUCT*  ex_data_ptr; 
    unsigned char* pExtend;
}ISP_BUFFER_CTRL_STRUCT;
#define _use_kernel_ref_cnt_
typedef enum
{
    ISP_REF_CNT_GET,    
    ISP_REF_CNT_INC,    
    ISP_REF_CNT_DEC,    
    ISP_REF_CNT_DEC_AND_RESET_P1_P2_IF_LAST_ONE,    
    ISP_REF_CNT_DEC_AND_RESET_P1_IF_LAST_ONE,    
    ISP_REF_CNT_DEC_AND_RESET_P2_IF_LAST_ONE,    
    ISP_REF_CNT_MAX
}ISP_REF_CNT_CTRL_ENUM;
typedef enum
{
    ISP_REF_CNT_ID_IMEM,    
    ISP_REF_CNT_ID_ISP_FUNC,
    ISP_REF_CNT_ID_GLOBAL_PIPE, 
    ISP_REF_CNT_ID_P1_PIPE,     
    ISP_REF_CNT_ID_P2_PIPE,     
    ISP_REF_CNT_ID_MAX,
}ISP_REF_CNT_ID_ENUM;
typedef struct  {
    ISP_REF_CNT_CTRL_ENUM   ctrl;
    ISP_REF_CNT_ID_ENUM     id;
    signed int*            data_ptr;
}ISP_REF_CNT_CTRL_STRUCT;

typedef enum
{
    ISP_ED_BUFQUE_CTRL_ENQUE_FRAME=0,          
    ISP_ED_BUFQUE_CTRL_WAIT_DEQUE,             
    ISP_ED_BUFQUE_CTRL_DEQUE_SUCCESS,          
    ISP_ED_BUFQUE_CTRL_DEQUE_FAIL,             
    ISP_ED_BUFQUE_CTRL_WAIT_FRAME,             
    ISP_ED_BUFQUE_CTRL_WAKE_WAITFRAME,         
    ISP_ED_BUFQUE_CTRL_CLAER_ALL,              
    ISP_ED_BUFQUE_CTRL_MAX
}ISP_ED_BUFQUE_CTRL_ENUM;

typedef struct
{
    ISP_ED_BUFQUE_CTRL_ENUM ctrl;
    unsigned int            processID;
    unsigned int            callerID;
    int                     p2burstQIdx;
    int                     p2dupCQIdx;
    unsigned int            timeoutUs;
}ISP_ED_BUFQUE_STRUCT;

typedef enum
{
    ISP_ED_BUF_STATE_NONE  =-1,
    ISP_ED_BUF_STATE_ENQUE=0,
    ISP_ED_BUF_STATE_RUNNING,
    ISP_ED_BUF_STATE_WAIT_DEQUE_FAIL,
    ISP_ED_BUF_STATE_DEQUE_SUCCESS,
    ISP_ED_BUF_STATE_DEQUE_FAIL
}ISP_ED_BUF_STATE_ENUM;
#define _rtbc_use_cq0c_

#define _MAGIC_NUM_ERR_HANDLING_


#if defined(_rtbc_use_cq0c_)
typedef struct _cq_cmd_st_
{
    unsigned int inst;
    unsigned int data_ptr_pa;
}CQ_CMD_ST;
typedef struct _cq_info_rtbc_st_
{
    CQ_CMD_ST imgo;
    CQ_CMD_ST rrzo;
    CQ_CMD_ST next_cq0ci;
    CQ_CMD_ST end;
    unsigned int imgo_base_pAddr;
    unsigned int rrzo_base_pAddr;
    signed int imgo_buf_idx; 
    signed int rrzo_buf_idx; 
}CQ_INFO_RTBC_ST;
typedef struct _cq_ring_cmd_st_
{
    CQ_INFO_RTBC_ST cq_rtbc;
    unsigned long next_pa;
    struct _cq_ring_cmd_st_ *pNext;
}CQ_RING_CMD_ST;
typedef struct _cq_rtbc_ring_st_
{
    CQ_RING_CMD_ST rtbc_ring[ISP_RT_CQ0C_BUF_SIZE];
    unsigned int   imgo_ring_size;
    unsigned int   rrzo_ring_size;
}CQ_RTBC_RING_ST;
#endif

typedef struct _cq0b_info_rtbc_st_
{
    CQ_CMD_ST ob;
    CQ_CMD_ST end;
}CQ0B_INFO_RTBC_ST;

typedef struct _cq0b_ring_cmd_st_
{
    CQ0B_INFO_RTBC_ST cq0b_rtbc;
    unsigned long next_pa;
    struct _cq0b_ring_cmd_st_ *pNext;
}CQ0B_RING_CMD_ST;

typedef struct _cq0b_rtbc_ring_st_
{
    CQ0B_RING_CMD_ST rtbc_ring;
}CQ0B_RTBC_RING_ST;

typedef volatile union _CQ_RTBC_FBC_
{
    volatile struct
    {
        unsigned int FBC_CNT                   : 4;
        unsigned int rsv_4                     : 7;
        unsigned int RCNT_INC                  : 1;
        unsigned int rsv_12                    : 2;
        unsigned int FBC_EN                    : 1;
        unsigned int LOCK_EN                   : 1;
        unsigned int FB_NUM                    : 4;
        unsigned int RCNT                      : 4;
        unsigned int WCNT                      : 4;
        unsigned int DROP_CNT                  : 4;
    } Bits;
    unsigned int Reg_val;
}CQ_RTBC_FBC;


#ifdef CONFIG_COMPAT

typedef struct
{
    ISP_IRQ_CLEAR_ENUM  Clear;		
    ISP_IRQ_TYPE_ENUM   Type;
    unsigned int        Status;
    int                 UserNumber;
    unsigned int        Timeout;
    compat_uptr_t       UserName;
    unsigned int        irq_TStamp;
    unsigned int        bDumpReg;
    ISP_IRQ_TIME_STRUCT  TimeInfo;  
    ISP_EIS_META_STRUCT EisMeta;
    ISP_IRQ_WAITIRQ_SPEUSER_ENUM SpecUser;
}compat_ISP_WAIT_IRQ_STRUCT;


typedef struct
{
    ISP_IRQ_TYPE_ENUM   Type;
    ISP_IRQ_USER_ENUM   UserNumber;
    unsigned int       Status;
}compat_ISP_READ_IRQ_STRUCT;

typedef struct
{
    ISP_IRQ_TYPE_ENUM   Type;
    ISP_IRQ_USER_ENUM   UserNumber;
    unsigned int       Status;
}compat_ISP_CLEAR_IRQ_STRUCT;


typedef struct
{
    compat_uptr_t pData;
    unsigned int Count;  
}compat_ISP_REG_IO_STRUCT;

typedef struct  {
    ISP_RT_BUF_CTRL_ENUM    ctrl;
    _isp_dma_enum_          buf_id;
    compat_uptr_t           data_ptr;
    compat_uptr_t           ex_data_ptr; 
    compat_uptr_t           pExtend;
}compat_ISP_BUFFER_CTRL_STRUCT;


typedef struct  {
    ISP_REF_CNT_CTRL_ENUM   ctrl;
    ISP_REF_CNT_ID_ENUM     id;
    compat_uptr_t         data_ptr;
}compat_ISP_REF_CNT_CTRL_STRUCT;


#endif


typedef enum
{
    ISP_CMD_RESET_CAM_P1,          
    ISP_CMD_RESET_CAM_P2,
    ISP_CMD_RESET_CAMSV,
    ISP_CMD_RESET_CAMSV2,
    ISP_CMD_RESET_BUF,
    ISP_CMD_READ_REG,       
    ISP_CMD_WRITE_REG,      
    ISP_CMD_HOLD_TIME,
    ISP_CMD_HOLD_REG,       
    ISP_CMD_WAIT_IRQ,       
    ISP_CMD_READ_IRQ,       
    ISP_CMD_CLEAR_IRQ,      
    ISP_CMD_DUMP_REG,       
    ISP_CMD_SET_USER_PID,   
    ISP_CMD_RT_BUF_CTRL,   
    ISP_CMD_REF_CNT,        
    ISP_CMD_DEBUG_FLAG,      
    ISP_CMD_REGISTER_IRQ,    
    ISP_CMD_UNREGISTER_IRQ,  
    ISP_CMD_ED_QUEBUF_CTRL,
    ISP_CMD_UPDATE_REGSCEN,
    ISP_CMD_QUERY_REGSCEN,
    ISP_CMD_UPDATE_BURSTQNUM,
    ISP_CMD_QUERY_BURSTQNUM,
    ISP_CMD_DUMP_ISR_LOG,   
    ISP_CMD_GET_CUR_SOF,
    ISP_CMD_GET_DMA_ERR,
    ISP_CMD_GET_INT_ERR,
    ISP_CMD_GET_DROP_FRAME,         
#ifdef T_STAMP_2_0
    ISP_CMD_SET_FPS,
#endif
    ISP_CMD_WAKELOCK_CTRL,          
}ISP_CMD_ENUM;
#define ISP_RESET_CAM_P1    _IO  (ISP_MAGIC, ISP_CMD_RESET_CAM_P1)
#define ISP_RESET_CAM_P2    _IO  (ISP_MAGIC, ISP_CMD_RESET_CAM_P2)
#define ISP_RESET_CAMSV     _IO  (ISP_MAGIC, ISP_CMD_RESET_CAMSV)
#define ISP_RESET_CAMSV2    _IO  (ISP_MAGIC, ISP_CMD_RESET_CAMSV2)
#define ISP_RESET_BUF       _IO  (ISP_MAGIC, ISP_CMD_RESET_BUF)
#define ISP_READ_REGISTER   _IOWR(ISP_MAGIC, ISP_CMD_READ_REG,      ISP_REG_IO_STRUCT)
#define ISP_WRITE_REGISTER  _IOWR(ISP_MAGIC, ISP_CMD_WRITE_REG,     ISP_REG_IO_STRUCT)
#define ISP_HOLD_REG_TIME   _IOW (ISP_MAGIC, ISP_CMD_HOLD_TIME,     ISP_HOLD_TIME_ENUM)
#define ISP_HOLD_REG        _IOW (ISP_MAGIC, ISP_CMD_HOLD_REG,      bool)
#define ISP_WAIT_IRQ        _IOW (ISP_MAGIC, ISP_CMD_WAIT_IRQ,      ISP_WAIT_IRQ_STRUCT)
#define ISP_READ_IRQ        _IOR (ISP_MAGIC, ISP_CMD_READ_IRQ,      ISP_READ_IRQ_STRUCT)
#define ISP_CLEAR_IRQ       _IOW (ISP_MAGIC, ISP_CMD_CLEAR_IRQ,     ISP_CLEAR_IRQ_STRUCT)
#define ISP_DUMP_REG        _IO  (ISP_MAGIC, ISP_CMD_DUMP_REG)
#define ISP_SET_USER_PID    _IOW (ISP_MAGIC, ISP_CMD_SET_USER_PID,    unsigned int)
#define ISP_BUFFER_CTRL     _IOWR(ISP_MAGIC, ISP_CMD_RT_BUF_CTRL,    ISP_BUFFER_CTRL_STRUCT)
#define ISP_REF_CNT_CTRL    _IOWR(ISP_MAGIC, ISP_CMD_REF_CNT,       ISP_REF_CNT_CTRL_STRUCT)
#define ISP_DEBUG_FLAG      _IOW (ISP_MAGIC, ISP_CMD_DEBUG_FLAG,    unsigned char*)
#define ISP_REGISTER_IRQ    _IOW (ISP_MAGIC, ISP_CMD_REGISTER_IRQ,  ISP_WAIT_IRQ_STRUCT)
#define ISP_UNREGISTER_IRQ    _IOW (ISP_MAGIC, ISP_CMD_UNREGISTER_IRQ,  ISP_WAIT_IRQ_STRUCT)
#define ISP_ED_QUEBUF_CTRL     _IOWR (ISP_MAGIC, ISP_CMD_ED_QUEBUF_CTRL, ISP_ED_BUFQUE_STRUCT)
#define ISP_UPDATE_REGSCEN     _IOWR (ISP_MAGIC, ISP_CMD_UPDATE_REGSCEN, unsigned int)
#define ISP_QUERY_REGSCEN     _IOR (ISP_MAGIC, ISP_CMD_QUERY_REGSCEN, unsigned int)
#define ISP_UPDATE_BURSTQNUM _IOW(ISP_MAGIC,ISP_CMD_UPDATE_BURSTQNUM, int)
#define ISP_QUERY_BURSTQNUM _IOR (ISP_MAGIC,ISP_CMD_QUERY_BURSTQNUM, int)
#define ISP_DUMP_ISR_LOG    _IO  (ISP_MAGIC, ISP_CMD_DUMP_ISR_LOG)
#define ISP_GET_CUR_SOF     _IOR (ISP_MAGIC, ISP_CMD_GET_CUR_SOF,      unsigned int)
#define ISP_GET_DMA_ERR     _IOWR (ISP_MAGIC, ISP_CMD_GET_DMA_ERR,      unsigned char*)
#define ISP_GET_INT_ERR     _IOR    (ISP_MAGIC, ISP_CMD_GET_INT_ERR,      unsigned char*)
#define ISP_GET_DROP_FRAME  _IOWR    (ISP_MAGIC, ISP_CMD_GET_DROP_FRAME,      unsigned int)
#ifdef T_STAMP_2_0
    #define ISP_SET_FPS     _IOW (ISP_MAGIC, ISP_CMD_SET_FPS,    unsigned int)
#endif
#define ISP_WAKELOCK_CTRL     _IOWR (ISP_MAGIC, ISP_CMD_WAKELOCK_CTRL,      unsigned int)

#ifdef CONFIG_COMPAT

#define COMPAT_ISP_READ_REGISTER   _IOWR(ISP_MAGIC, ISP_CMD_READ_REG,      compat_ISP_REG_IO_STRUCT)
#define COMPAT_ISP_WRITE_REGISTER  _IOWR(ISP_MAGIC, ISP_CMD_WRITE_REG,     compat_ISP_REG_IO_STRUCT)
#define COMPAT_ISP_DEBUG_FLAG     _IOW (ISP_MAGIC, ISP_CMD_DEBUG_FLAG,     compat_uptr_t)
#define COMPAT_ISP_GET_DMA_ERR     _IOWR (ISP_MAGIC, ISP_CMD_GET_DMA_ERR,  compat_uptr_t)
#define COMPAT_ISP_GET_INT_ERR     _IOR   (ISP_MAGIC, ISP_CMD_GET_INT_ERR, compat_uptr_t)

#define COMPAT_ISP_WAIT_IRQ        _IOW (ISP_MAGIC, ISP_CMD_WAIT_IRQ,      compat_ISP_WAIT_IRQ_STRUCT)
#define COMPAT_ISP_READ_IRQ        _IOR (ISP_MAGIC, ISP_CMD_READ_IRQ,      compat_ISP_READ_IRQ_STRUCT)
#define COMPAT_ISP_BUFFER_CTRL     _IOWR(ISP_MAGIC, ISP_CMD_RT_BUF_CTRL,    compat_ISP_BUFFER_CTRL_STRUCT)
#define COMPAT_ISP_REF_CNT_CTRL    _IOWR(ISP_MAGIC, ISP_CMD_REF_CNT,       compat_ISP_REF_CNT_CTRL_STRUCT)

#endif
bool ISP_RegCallback(ISP_CALLBACK_STRUCT* pCallback);
bool ISP_UnregCallback(ISP_CALLBACK_ENUM   Type);
int32_t ISP_MDPClockOnCallback(uint64_t engineFlag);
int32_t ISP_MDPDumpCallback(uint64_t engineFlag,
                            int level);
int32_t ISP_MDPResetCallback(uint64_t engineFlag);

int32_t ISP_MDPClockOffCallback(uint64_t engineFlag);

int32_t ISP_BeginGCECallback(uint32_t taskID, uint32_t *regCount, uint32_t **regAddress);
int32_t ISP_EndGCECallback(uint32_t taskID, uint32_t regCount, uint32_t *regValues);

#endif

