#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <mach/mt_typedefs.h>
#include <mach/sync_write.h>
#include <mach/mt_dcm.h>
#include <mach/mt_clkmgr.h>
#include <mach/mt_boot.h>                   
#ifdef CONFIG_OF
#include <linux/of.h>
#include <linux/of_address.h>
#endif
#include <linux/aee.h>

#define USING_XLOG

#ifdef USING_XLOG


#ifdef CONFIG_OF
void __iomem  *dcm_USB0_base;
void __iomem  *dcm_MSDC0_base;
void __iomem  *dcm_MSDC1_base;
void __iomem  *dcm_MSDC2_base;
void __iomem  *dcm_MSDC3_base;
void __iomem  *dcm_PMIC_WRAP_base;
void __iomem  *dcm_I2C0_base;
void __iomem  *dcm_I2C1_base;
void __iomem  *dcm_I2C2_base;
void __iomem  *dcm_I2C3_base;
void __iomem  *dcm_I2C4_base;
void __iomem  *dcm_MJC_CONFIG_base;
void __iomem  *dcm_MCUCFG_base;
void __iomem  *dcm_TOPCKGEN_base;
void __iomem  *dcm_INFRACFG_AO_base;
void __iomem  *dcm_M4U_base;
void __iomem  *dcm_PERISYS_IOMMU_base;

void __iomem  *dcm_PERICFG_base;
void __iomem  *dcm_DRAMC0_base;
void __iomem  *dcm_DRAMC1_base;
void __iomem  *dcm_EMI_base;
void __iomem  *dcm_SMI_COMMO_base;


void __iomem  *dcm_SMI_LARB0_base;
void __iomem  *dcm_SMI_LARB1_base;
void __iomem  *dcm_SMI_LARB2_base;
void __iomem  *dcm_SMI_LARB3_base;
void __iomem  *dcm_SMI_LARB5_base;

void __iomem  *dcm_CAM1_base;
void __iomem  *dcm_FDVT_base;
void __iomem  *dcm_JPGENC_base;
void __iomem  *dcm_JPGDEC_base;
void __iomem  *dcm_MMSYS_CONFIG_base;
void __iomem  *dcm_VENC_base;
void __iomem  *dcm_VDEC_GCON_base;

void __iomem  *dcm_E3TCM_base;
#endif

#include <linux/xlog.h>
#define TAG     "Power/dcm"

#define MT6592_DCM_SETTING (1)


#define dcm_err(fmt, args...)       \
    xlog_printk(ANDROID_LOG_ERROR, TAG, fmt, ##args)
#define dcm_warn(fmt, args...)      \
    xlog_printk(ANDROID_LOG_WARN, TAG, fmt, ##args)
#define dcm_info(fmt, args...)      \
    xlog_printk(ANDROID_LOG_INFO, TAG, fmt, ##args)
#define dcm_dbg(fmt, args...)       \
    xlog_printk(ANDROID_LOG_DEBUG, TAG, fmt, ##args)
#define dcm_ver(fmt, args...)       \
    xlog_printk(ANDROID_LOG_VERBOSE, TAG, fmt, ##args)

#else 

#define TAG     "[Power/dcm] "

#define dcm_err(fmt, args...)       \
    printk(KERN_ERR TAG);           \
    printk(KERN_CONT fmt, ##args)
#define dcm_warn(fmt, args...)      \
    printk(KERN_WARNING TAG);       \
    printk(KERN_CONT fmt, ##args)
#define dcm_info(fmt, args...)      \
    printk(KERN_NOTICE TAG);        \
    printk(KERN_CONT fmt, ##args)
#define dcm_dbg(fmt, args...)       \
    printk(KERN_INFO TAG);          \
    printk(KERN_CONT fmt, ##args)
#define dcm_ver(fmt, args...)       \
    printk(KERN_DEBUG TAG);         \
    printk(KERN_CONT fmt, ##args)

#endif


#define dcm_readl(addr)         DRV_Reg32(addr)


#define dcm_writel(addr, val)   mt_reg_sync_writel((val), ((void *)addr))

#define dcm_setl(addr, val)     mt_reg_sync_writel(dcm_readl(addr) | (val), ((void *)addr))

#define dcm_clrl(addr, val)     mt_reg_sync_writel(dcm_readl(addr) & ~(val), ((void *)addr))


static DEFINE_MUTEX(dcm_lock);

static unsigned int dcm_sta = 0;
static unsigned int dcm_initiated = 0;

void dcm_dump_regs(unsigned int type)
{
#if 1 
	dcm_info("\ndcm_dump_regs(0x%x)\n", type);

    mutex_lock(&dcm_lock);

    if (type & CPU_DCM) {
        
        dcm_info("[CPU_DCM]L2C_SRAM_CTRL         :0x%08x, (0x%08x)\n",L2C_SRAM_CTRL, dcm_readl(L2C_SRAM_CTRL));
        dcm_info("[CPU_DCM]CCI_CLK_CTRL          :0x%08x, (0x%08x)\n",CCI_CLK_CTRL, dcm_readl(CCI_CLK_CTRL));
        dcm_info("[CPU_DCM]BUS_FABRIC_DCM_CTRL   :0x%08x, (0x%08x)\n",BUS_FABRIC_DCM_CTRL, dcm_readl(BUS_FABRIC_DCM_CTRL));
    }

#if 1
	if (1) {
	    
        dcm_info("[TOPCKGEN_DCM]DCM_CFG          :0x%08x, (0x%08x)\n",DCM_CFG, dcm_readl(DCM_CFG));
    }
#endif

    if (type & IFR_DCM) {
        
        dcm_info("[IFR_DCM]CA7_CKDIV1            :0x%08x, (0x%08x)\n", CA7_CKDIV1, dcm_readl(CA7_CKDIV1));
        dcm_info("[IFR_DCM]INFRA_TOPCKGEN_DCMCTL :0x%08x, (0x%08x)\n", INFRA_TOPCKGEN_DCMCTL, dcm_readl(INFRA_TOPCKGEN_DCMCTL));
#ifndef CONFIG_ARM64        
        dcm_info("[IFR_DCM]INFRA_TOPCKGEN_DCMDBC :0x%08x, (0x%08x)\n", INFRA_TOPCKGEN_DCMDBC, dcm_readl(INFRA_TOPCKGEN_DCMDBC));
#endif        
        dcm_info("[IFR_DCM]INFRA_GLOBALCON_DCMCTL:0x%08x, (0x%08x)\n", INFRA_GLOBALCON_DCMCTL, dcm_readl(INFRA_GLOBALCON_DCMCTL));
        dcm_info("[IFR_DCM]INFRA_GLOBALCON_DCMDBC:0x%08x, (0x%08x)\n", INFRA_GLOBALCON_DCMDBC, dcm_readl(INFRA_GLOBALCON_DCMDBC));
        dcm_info("[IFR_DCM]INFRA_GLOBALCON_DCMFSEL:0x%08x,(0x%08x)\n", INFRA_GLOBALCON_DCMFSEL, dcm_readl(INFRA_GLOBALCON_DCMFSEL));
		dcm_info("[IFR_DCM]MM_MMU_DCM_DIS        :0x%08x, (0x%08x)\n", MM_MMU_DCM_DIS, dcm_readl(MM_MMU_DCM_DIS));
		dcm_info("[IFR_DCM]PERISYS_MMU_DCM_DIS   :0x%08x, (0x%08x)\n", PERISYS_MMU_DCM_DIS, dcm_readl(PERISYS_MMU_DCM_DIS));
    }

    if (type & PER_DCM) {
        
        volatile unsigned int peri_globalcon_dcmctl;
        volatile unsigned int peri_globalcon_dcmdbc, peri_globalcon_dcmsel;
		volatile unsigned int msdc0_dcm,msdc1_dcm,msdc2_dcm,msdc3_dcm;
		volatile unsigned int usb0_dcm,pmic_wrap_dcm_en;
        volatile unsigned int i2c0_i2creg_hw_cg_en,i2c1_i2creg_hw_cg_en,i2c2_i2creg_hw_cg_en,i2c3_i2creg_hw_cg_en,i2c4_i2creg_hw_cg_en;

        peri_globalcon_dcmctl = dcm_readl(PERI_GLOBALCON_DCMCTL);
        peri_globalcon_dcmdbc = dcm_readl(PERI_GLOBALCON_DCMDBC);
        peri_globalcon_dcmsel = dcm_readl(PERI_GLOBALCON_DCMFSEL);

		
		enable_clock(MT_CG_PERI_MSDC30_0, "DCM");
		enable_clock(MT_CG_PERI_MSDC30_1, "DCM");
		enable_clock(MT_CG_PERI_MSDC30_2, "DCM");
        enable_clock(MT_CG_PERI_MSDC30_3, "DCM");
        
		msdc0_dcm=dcm_readl(MSDC0_PATCH_BIT1); 
		msdc1_dcm=dcm_readl(MSDC1_PATCH_BIT1); 
        msdc2_dcm=dcm_readl(MSDC2_PATCH_BIT1); 
        msdc3_dcm=dcm_readl(MSDC3_PATCH_BIT1); 

        disable_clock(MT_CG_PERI_MSDC30_0, "DCM");
		disable_clock(MT_CG_PERI_MSDC30_1, "DCM");
		disable_clock(MT_CG_PERI_MSDC30_2, "DCM");
        disable_clock(MT_CG_PERI_MSDC30_3, "DCM");
        
        
        enable_clock(MT_CG_PERI_USB1, "DCM");
		usb0_dcm = dcm_readl(USB0_DCM);
		disable_clock(MT_CG_PERI_USB1, "DCM");

		pmic_wrap_dcm_en = dcm_readl(PMIC_WRAP_DCM_EN);

		i2c0_i2creg_hw_cg_en = dcm_readl(I2C0_I2CREG_HW_CG_EN);
		i2c1_i2creg_hw_cg_en = dcm_readl(I2C1_I2CREG_HW_CG_EN);
		i2c2_i2creg_hw_cg_en = dcm_readl(I2C2_I2CREG_HW_CG_EN);
		i2c3_i2creg_hw_cg_en = dcm_readl(I2C3_I2CREG_HW_CG_EN);
		if (dcm_I2C4_base)
		{
		    i2c4_i2creg_hw_cg_en = dcm_readl(I2C4_I2CREG_HW_CG_EN);
        }
        
        dcm_info("[PER_DCM]PERI_GLOBALCON_DCMCTL  :0x%08x, (0x%08x)\n", PERI_GLOBALCON_DCMCTL,peri_globalcon_dcmctl);
        dcm_info("[PER_DCM]PERI_GLOBALCON_DCMDBC  :0x%08x, (0x%08x)\n", PERI_GLOBALCON_DCMDBC,peri_globalcon_dcmdbc);
        dcm_info("[PER_DCM]PERI_GLOBALCON_DCMFSEL :0x%08x, (0x%08x)\n", PERI_GLOBALCON_DCMFSEL,peri_globalcon_dcmsel);

        dcm_info("[PER_DCM]MSDC0_PATCH_BIT1       :0x%08x, (0x%08x)\n", MSDC0_PATCH_BIT1,msdc0_dcm);
        dcm_info("[PER_DCM]MSDC1_PATCH_BIT1       :0x%08x, (0x%08x)\n", MSDC1_PATCH_BIT1,msdc1_dcm);
        dcm_info("[PER_DCM]MSDC2_PATCH_BIT1       :0x%08x, (0x%08x)\n", MSDC2_PATCH_BIT1,msdc2_dcm);
        dcm_info("[PER_DCM]MSDC3_PATCH_BIT1       :0x%08x, (0x%08x)\n", MSDC3_PATCH_BIT1,msdc3_dcm);

        dcm_info("[PER_DCM]USB0_DCM               :0x%08x, (0x%08x)\n", USB0_DCM,usb0_dcm);

        dcm_info("[PER_DCM]PMIC_WRAP_DCM_EN       :0x%08x, (0x%08x)\n", PMIC_WRAP_DCM_EN,pmic_wrap_dcm_en);

        dcm_info("[PER_DCM]I2C0_I2CREG_HW_CG_EN   :0x%08x, (0x%08x)\n", I2C0_I2CREG_HW_CG_EN,i2c0_i2creg_hw_cg_en);
        dcm_info("[PER_DCM]I2C1_I2CREG_HW_CG_EN   :0x%08x, (0x%08x)\n", I2C1_I2CREG_HW_CG_EN,i2c1_i2creg_hw_cg_en);
        dcm_info("[PER_DCM]I2C2_I2CREG_HW_CG_EN   :0x%08x, (0x%08x)\n", I2C2_I2CREG_HW_CG_EN,i2c2_i2creg_hw_cg_en);
        dcm_info("[PER_DCM]I2C2_I3CREG_HW_CG_EN   :0x%08x, (0x%08x)\n", I2C3_I2CREG_HW_CG_EN,i2c3_i2creg_hw_cg_en);
        if (dcm_I2C4_base)
        {
            dcm_info("[PER_DCM]I2C2_I4CREG_HW_CG_EN   :0x%08x, (0x%08x)\n", I2C4_I2CREG_HW_CG_EN,i2c4_i2creg_hw_cg_en);
        }
    }
	
    if (1) {

     	volatile unsigned int smi_larb0_sta,smi_larb0_con;
     	volatile unsigned int smi_larb1_sta,smi_larb1_con;
     	volatile unsigned int smi_larb2_sta,smi_larb2_con;
     	volatile unsigned int smi_larb3_sta,smi_larb3_con;
     	volatile unsigned int smi_larb4_sta,smi_larb4_con;

    	smi_larb0_sta = dcm_readl(SMI_LARB0_STA);
    	smi_larb0_con = dcm_readl(SMI_LARB0_CON);

		dcm_info("[SMILARB_DCM]SMI_LARB0_STA      :0x%08x, (0x%08x)\n",SMI_LARB0_STA, smi_larb0_sta);
		dcm_info("[SMILARB_DCM]SMI_LARB0_CON      :0x%08x, (0x%08x)\n",SMI_LARB0_CON ,smi_larb0_con);

    	smi_larb1_sta = dcm_readl(SMI_LARB1_STAT);
    	smi_larb1_con = dcm_readl(SMI_LARB1_CON);

		dcm_info("[SMILARB_DCM]SMI_LARB1_STA      :0x%08x, (0x%08x)\n",SMI_LARB1_STAT,smi_larb1_sta);
		dcm_info("[SMILARB_DCM]SMI_LARB1_CON      :0x%08x, (0x%08x)\n",SMI_LARB1_CON,smi_larb1_con);

    	smi_larb2_sta = dcm_readl(SMI_LARB2_STAT);
    	smi_larb2_con = dcm_readl(SMI_LARB2_CON);

		dcm_info("[SMILARB_DCM]SMI_LARB2_STA      :0x%08x, (0x%08x)\n",SMI_LARB2_STAT,smi_larb2_sta);
		dcm_info("[SMILARB_DCM]SMI_LARB2_CON      :0x%08x, (0x%08x)\n",SMI_LARB2_CON,smi_larb2_con);

    	smi_larb3_sta = dcm_readl(SMI_LARB3_STAT);
    	smi_larb3_con = dcm_readl(SMI_LARB3_CON);

		dcm_info("[SMILARB_DCM]SMI_LARB3_STA      :0x%08x, (0x%08x)\n",SMI_LARB3_STAT,smi_larb3_sta);
		dcm_info("[SMILARB_DCM]SMI_LARB3_CON      :0x%08x, (0x%08x)\n",SMI_LARB3_CON,smi_larb3_con);

    	smi_larb4_sta = dcm_readl(SMI_LARB4_STAT);
    	smi_larb4_con = dcm_readl(SMI_LARB4_CON);

		dcm_info("[SMILARB_DCM]SMI_LARB4_STA      :0x%08x, (0x%08x)\n",SMI_LARB4_STAT,smi_larb4_sta);
		dcm_info("[SMILARB_DCM]SMI_LARB4_CON      :0x%08x, (0x%08x)\n",SMI_LARB4_CON,smi_larb4_con);
	}

    if (type & SMI_DCM) {

        dcm_info("[SMI_DCM]SMI_COMMON_SMI_DCM     :0x%08x, (0x%08x)\n", SMI_COMMON_SMI_DCM, dcm_readl(SMI_COMMON_SMI_DCM));
	}

    if (type & EMI_DCM) {
        volatile unsigned int emi_conm;

		emi_conm = dcm_readl(EMI_CONM);
		dcm_info("[EMI_DCM]EMI_CONM :0x%08x, (0x%08x)\n", EMI_CONM,emi_conm);
    }

    if (type & DIS_DCM) {
        if (1){
        	dcm_info("[DIS_DCM]MMSYS_HW_DCM_DIS0     :0x%08x, (0x%08x)\n", MMSYS_HW_DCM_DIS0, dcm_readl(MMSYS_HW_DCM_DIS0));
        	dcm_info("[DIS_DCM]MMSYS_HW_DCM_DIS1     :0x%08x, (0x%08x)\n", MMSYS_HW_DCM_DIS1, dcm_readl(MMSYS_HW_DCM_DIS1));
        } else {
            dcm_info("[DIS_DCM]subsys DIS is off\n");
        }
    }
    
    if (type & VDE_DCM) {
        if (1){
        	volatile unsigned int vdec;
        
        	vdec = dcm_readl(VDEC_DCM_CON);
			dcm_info("[VDE_DCM]VDEC_DCM_CON  :0x%08x, (0x%08x)\n",VDEC_DCM_CON, vdec);
        } else {
            dcm_info("[VDE_DCM]subsys VDE is off\n");
        }
    }

    if (1) {
        if (1){
        	volatile unsigned int lv_VENC_CLK_CG_CTRL ,lv_VENC_CLK_DCM_CTRL,lv_JPGENC_DCM_CTRL,lv_JPGDEC_DCM_CTRL;
        
        	lv_VENC_CLK_CG_CTRL  = dcm_readl   (VENC_CLK_CG_CTRL      ); 
			lv_VENC_CLK_DCM_CTRL = dcm_readl   (VENC_CLK_DCM_CTRL     ); 
			lv_JPGENC_DCM_CTRL   = dcm_readl   (JPGENC_DCM_CTRL       ); 
			lv_JPGDEC_DCM_CTRL   = dcm_readl   (JPGDEC_DCM_CTRL       ); 
		
        	dcm_info("[VEN_DCM]VENC_CLK_CG_CTRL  :0x%08x, (0x%08x)\n", VENC_CLK_CG_CTRL,lv_VENC_CLK_CG_CTRL);
        	dcm_info("[VEN_DCM]VENC_CLK_DCM_CTRL :0x%08x, (0x%08x)\n", VENC_CLK_DCM_CTRL,lv_VENC_CLK_DCM_CTRL);
        	dcm_info("[VEN_DCM]JPGENC_DCM_CTRL   :0x%08x, (0x%08x)\n", JPGENC_DCM_CTRL,lv_JPGENC_DCM_CTRL);
        	dcm_info("[VEN_DCM]JPGDEC_DCM_CTRL   :0x%08x, (0x%08x)\n", JPGDEC_DCM_CTRL,lv_JPGDEC_DCM_CTRL);
        } else {
            dcm_info("[ISP_DCM]subsys ISP is off\n");
        }
    }

    if (type & ISP_DCM) {
        if (1){
            volatile unsigned int lv_CTL_RAW_DCM_DIS, lv_CTL_RAW_D_DCM_DIS, lv_CTL_DMA_DCM_DIS,lv_CTL_RGB_DCM_DIS,lv_CTL_YUV_DCM_DIS,lv_CTL_TOP_DCM_DIS;
            volatile unsigned int lv_FDVT_CTRL;
    		volatile unsigned int lv_SMI_LARB2_CON_SET,lv_SMI_LARB3_CON_SET;
    
    		lv_CTL_RAW_DCM_DIS  = dcm_readl   (CTL_RAW_DCM_DIS         ); 
    		lv_CTL_RAW_D_DCM_DIS= dcm_readl   (CTL_RAW_D_DCM_DIS       ); 
    		lv_CTL_DMA_DCM_DIS  = dcm_readl   (CTL_DMA_DCM_DIS         ); 
    		lv_CTL_RGB_DCM_DIS  = dcm_readl   (CTL_RGB_DCM_DIS         ); 
    		lv_CTL_YUV_DCM_DIS  = dcm_readl   (CTL_YUV_DCM_DIS         ); 
    		lv_CTL_TOP_DCM_DIS  = dcm_readl   (CTL_TOP_DCM_DIS         ); 
    
    		lv_FDVT_CTRL= dcm_readl   (FDVT_CTRL               ); 
    
    		lv_SMI_LARB2_CON_SET = dcm_readl   (SMI_LARB2_CON_SET     ); 
    		lv_SMI_LARB3_CON_SET = dcm_readl   (SMI_LARB3_CON_SET     ); 
    
            
            dcm_info("[ISP_DCM]CTL_RAW_D_DCM_DIS :0x%08x, (0x%08x)\n", CTL_RAW_D_DCM_DIS,lv_CTL_RAW_D_DCM_DIS);
            dcm_info("[ISP_DCM]CTL_DMA_DCM_DIS   :0x%08x, (0x%08x)\n", CTL_DMA_DCM_DIS,lv_CTL_DMA_DCM_DIS);
            dcm_info("[ISP_DCM]CTL_RGB_DCM_DIS   :0x%08x, (0x%08x)\n", CTL_RGB_DCM_DIS,lv_CTL_RGB_DCM_DIS);
            dcm_info("[ISP_DCM]CTL_YUV_DCM_DIS   :0x%08x, (0x%08x)\n", CTL_YUV_DCM_DIS,lv_CTL_YUV_DCM_DIS);
            dcm_info("[ISP_DCM]CTL_TOP_DCM_DIS   :0x%08x, (0x%08x)\n", CTL_TOP_DCM_DIS,lv_CTL_TOP_DCM_DIS);
    
            dcm_info("[ISP_DCM]FDVT_CTRL         :0x%08x, (0x%08x)\n", FDVT_CTRL,lv_FDVT_CTRL);
        
        } else {
            dcm_info("[ISP_DCM]subsys ISP is off\n");
        }
    }

	if (type & MJC_DCM) {
        if (1){
			volatile unsigned int mjc_hw_dcm_dis;
			mjc_hw_dcm_dis 	   = dcm_readl(MJC_HW_DCM_DIS);
		dcm_info("[MJC_DCM]MJC_HW_DCM_DIS  	 :0x%08x, (0x%08x)\n", MJC_HW_DCM_DIS,mjc_hw_dcm_dis);
   	 	}else {
            dcm_info("[SYS_MJC]subsys MJC is off\n");
        }
    }

    if (1) {

        dcm_info("[E3TCM_DCM]E3TCM_HW_DCM_DIS  	 :0x%08x, (0x%08x)\n", E3TCM_HW_DCM_DIS, dcm_readl(E3TCM_HW_DCM_DIS));
    }

    if (1) {

        dcm_info("[IFR_DCM]INFRA_TOPCKGEN_DCMCTL :0x%08x, (0x%08x)\n", INFRA_TOPCKGEN_DCMCTL, dcm_readl(INFRA_TOPCKGEN_DCMCTL));
    }

    mutex_unlock(&dcm_lock);
#endif
}

void dcm_enable(unsigned int type)
{
	mt_dcm_init();
    dcm_info("[%s]type:0x%08x\n", __func__, type);

    mutex_lock(&dcm_lock);

    if (type & CPU_DCM) {
        dcm_info("[%s][CPU_DCM     ]=0x%08x\n", __func__,CPU_DCM);

#ifndef CONFIG_ARM64
		dcm_clrl   (DCM_MCUSYS_CONFIG     , 0x0F9C0000); 

        dcm_setl   (CACHE_CONFIG          , 0x00000B00); 
		dcm_clrl   (CACHE_CONFIG          , 0x00000400); 
		dcm_setl   (ARMPLL_CTL            , 0x00000010); 
#else
		dcm_setl   (L2C_SRAM_CTRL         , 0x00000001); 
        dcm_setl   (CCI_CLK_CTRL          , 0x00000100); 
		dcm_setl   (BUS_FABRIC_DCM_CTRL   , 0x00011F0F); 
#endif
        dcm_sta |= CPU_DCM;
    }

#if 0 
	if (type & TOPCKGEN_DCM) {
        dcm_info("[%s][TOPCKGEN_DCM]=0x%08x\n", __func__,TOPCKGEN_DCM);

        #ifdef DCM_ENABLE_DCM_CFG 
        
        dcm_setl(DCM_CFG, 0x1 << 7);
        #endif
        
    	dcm_sta |= TOPCKGEN_DCM;
    }
#endif

	
    if (type & IFR_DCM) {
        dcm_info("[%s][IFR_DCM     ]=0x%08x\n", __func__,IFR_DCM);

		dcm_clrl   (CA7_CKDIV1            , 0x0000001F); 
#ifndef CONFIG_ARM64
		if(CHIP_SW_VER_02 == mt_get_chip_sw_ver()){
			dcm_setl   (INFRA_TOPCKGEN_DCMCTL , 0x00000001); 
			dcm_clrl   (INFRA_TOPCKGEN_DCMCTL , 0x00000770); 
		}
		else{
		    dcm_setl   (INFRA_TOPCKGEN_DCMCTL , 0x00000771); 
		}
#else
		dcm_setl   (INFRA_TOPCKGEN_DCMCTL , 0x00000071); 
#endif
#if 0 
		dcm_setl   (INFRA_GLOBALCON_DCMCTL, 0x00000303); 

		dcm_setl   (INFRA_GLOBALCON_DCMDBC ,0x01000100); 
		dcm_clrl   (INFRA_GLOBALCON_DCMDBC ,0x007F007F); 

		dcm_setl   (INFRA_GLOBALCON_DCMFSEL,0x10100000); 
		dcm_clrl   (INFRA_GLOBALCON_DCMFSEL,0x0F0F0F07); 
#endif
		dcm_clrl   (MM_MMU_DCM_DIS         , 0x0000007F); 

		dcm_clrl   (PERISYS_MMU_DCM_DIS    , 0x0000007F); 

	    
		dcm_setl   (channel_A_DRAMC_PD_CTRL, 0xC3000000); 
		dcm_clrl   (channel_A_DRAMC_PD_CTRL, 0x00000008); 

		dcm_setl   (channel_B_DRAMC_PD_CTRL, 0xC3000000); 
		dcm_clrl   (channel_B_DRAMC_PD_CTRL, 0x00000008); 

		dcm_sta |= IFR_DCM;
    }

    if (type & PER_DCM) {
        dcm_info("[%s][PER_DCM     ]=0x%08x\n", __func__,PER_DCM);

		dcm_setl   (PERI_GLOBALCON_DCMCTL , 0x000000F3); 
		dcm_clrl   (PERI_GLOBALCON_DCMCTL , 0x00001F00); 

		dcm_clrl   (PERI_GLOBALCON_DCMDBC , 0x0000000F); 
		dcm_setl   (PERI_GLOBALCON_DCMDBC , 0x000000F0); 

		dcm_clrl   (PERI_GLOBALCON_DCMFSEL, 0x001F0F07); 
        
		
		enable_clock(MT_CG_PERI_MSDC30_0, "DCM");
		enable_clock(MT_CG_PERI_MSDC30_1, "DCM");
		enable_clock(MT_CG_PERI_MSDC30_2, "DCM");
        enable_clock(MT_CG_PERI_MSDC30_3, "DCM");
        
		dcm_setl   (MSDC0_PATCH_BIT1       , 0x00200000); 
		dcm_clrl   (MSDC0_PATCH_BIT1       , 0xFF800000); 

		dcm_setl   (MSDC1_PATCH_BIT1       , 0x00200000); 
		dcm_clrl   (MSDC1_PATCH_BIT1       , 0xFF800000); 

        dcm_setl   (MSDC2_PATCH_BIT1       , 0x00200000); 
		dcm_clrl   (MSDC2_PATCH_BIT1       , 0xFF800000); 

        dcm_setl   (MSDC3_PATCH_BIT1       , 0x00200000); 
		dcm_clrl   (MSDC3_PATCH_BIT1       , 0xFF800000); 

        disable_clock(MT_CG_PERI_MSDC30_0, "DCM");
		disable_clock(MT_CG_PERI_MSDC30_1, "DCM");
		disable_clock(MT_CG_PERI_MSDC30_2, "DCM");
        disable_clock(MT_CG_PERI_MSDC30_3, "DCM");
        
		
		enable_clock(MT_CG_PERI_USB1, "DCM");
		dcm_clrl   (USB0_DCM              , 0x00070000); 
        disable_clock(MT_CG_PERI_USB1, "DCM");
        
        
		dcm_setl   (PMIC_WRAP_DCM_EN      , 0x00000001); 

		
        dcm_setl   (I2C0_I2CREG_HW_CG_EN  , 0x00000001); 
		dcm_setl   (I2C1_I2CREG_HW_CG_EN  , 0x00000001); 
		dcm_setl   (I2C2_I2CREG_HW_CG_EN  , 0x00000001); 
		dcm_setl   (I2C3_I2CREG_HW_CG_EN  , 0x00000001); 
		if (dcm_I2C4_base)
		{
			dcm_setl   (I2C4_I2CREG_HW_CG_EN  , 0x00000001); 
		}

        dcm_sta |= PER_DCM;

    }
    
    if (type & SMI_DCM) {

        dcm_info("[%s][SMI_DCM     ]=0x%08x\n", __func__,SMI_DCM);

        dcm_setl   (SMI_COMMON_SMI_DCM       , 0x00000001); 

#ifdef CONFIG_ARM64
        
		dcm_setl   (E3TCM_HW_DCM_DIS_CLR  , 0x0000003F); 
#endif

        dcm_sta |= SMI_DCM;
    }


    if (type & EMI_DCM) {
		dcm_info("[%s][EMI_DCM     ]=0x%08x\n", __func__,EMI_DCM);

		dcm_setl   (EMI_CONM          , 0x40000000); 
		dcm_clrl   (EMI_CONM          , 0xBF000000); 

        dcm_sta |= EMI_DCM;
    }

    if (type & DIS_DCM) {
		dcm_info("[%s][DIS_DCM     ]=0x%08x, subsys_is_on(SYS_DIS)=%d\n", __func__, DIS_DCM,subsys_is_on(SYS_DIS));

        if (subsys_is_on(SYS_DIS)) {

			dcm_writel (MMSYS_HW_DCM_DIS_CLR0 , 0xFFFFFFFF); 
			dcm_writel (MMSYS_HW_DCM_DIS_CLR1 , 0xFFFFFFFF); 

			dcm_setl   (SMI_LARB0_CON_SET     , 0x00000010); 



            dcm_sta |= DIS_DCM;
        }

    }

    if (type & ISP_DCM) { 

        dcm_info("[%s][ISP_DCM     ]=0x%08x, subsys_is_on(SYS_ISP)=%d, subsys_is_on(SYS_VEN)=%d\n", __func__, ISP_DCM, subsys_is_on(SYS_ISP), subsys_is_on(SYS_VEN));

        if (subsys_is_on(SYS_ISP) && subsys_is_on(SYS_VEN)) {

			
			dcm_clrl   (CTL_RAW_D_DCM_DIS       , 0x024EAFE8); 
			dcm_clrl   (CTL_DMA_DCM_DIS         , 0x07FFFFFF); 
			dcm_clrl   (CTL_RGB_DCM_DIS         , 0x0000007F); 
			dcm_clrl   (CTL_YUV_DCM_DIS         , 0x000FFFFF); 
			dcm_clrl   (CTL_TOP_DCM_DIS         , 0x0000000F); 

			dcm_clrl   (FDVT_CTRL               , 0x0000001F); 

			dcm_setl   (VENC_CLK_CG_CTRL      , 0xFFFFFFFF); 
			dcm_setl   (VENC_CLK_DCM_CTRL     , 0x00000001); 
			dcm_clrl   (JPGENC_DCM_CTRL       , 0x00000001); 
			dcm_clrl   (JPGDEC_DCM_CTRL       , 0x00000001); 

			dcm_setl   (SMI_LARB2_CON_SET     , 0x00000010); 
			dcm_setl   (SMI_LARB3_CON_SET     , 0x00000010); 

            dcm_sta |= ISP_DCM;

        }

    }

    if (type & VDE_DCM) {

		dcm_info("[%s][VDE_DCM     ]=0x%08x, subsys_is_on(SYS_VDE)=%d\n", __func__, VDE_DCM, subsys_is_on(SYS_VDE));

        if (subsys_is_on(SYS_VDE)) {

			dcm_clrl   (VDEC_DCM_CON          , 0x00000001); 

			dcm_setl   (SMI_LARB1_CON_SET     , 0x00000010); 

            dcm_sta |= VDE_DCM;
        }

    }

    if (type & MJC_DCM) { 
        
        dcm_info("[%s][MJC_DCM     ]=0x%08x, subsys_is_on(SYS_MJC)=%d\n", __func__, MJC_DCM, subsys_is_on(SYS_MJC));
        
        if (subsys_is_on(SYS_MJC)) {
            
            dcm_setl   (MJC_HW_DCM_DIS_CLR    , 0xFFFFFFFF); 

            dcm_setl   (SMI_LARB4_CON_SET     , 0x00000010); 

			dcm_sta |= MJC_DCM;
       	}
	}


    mutex_unlock(&dcm_lock);
}

void dcm_disable(unsigned int type)
{
	mt_dcm_init();
    dcm_info("[%s]type:0x%08x\n", __func__, type);

    mutex_lock(&dcm_lock);
 
    if (type & CPU_DCM) {

        dcm_info("[%s][CPU_DCM     ]=0x%08x\n", __func__,CPU_DCM);

#ifndef CONFIG_ARM64
		dcm_setl   (DCM_MCUSYS_CONFIG     , 0x0F9C0000); 
		dcm_setl   (CACHE_CONFIG          , 0x00000300); 
		dcm_clrl   (CACHE_CONFIG          , 0x00000C00); 
		dcm_clrl   (ARMPLL_CTL            , 0x00000010); 
#else
		dcm_clrl   (L2C_SRAM_CTRL         , 0x00000001); 
        dcm_clrl   (CCI_CLK_CTRL          , 0x00000100); 
		dcm_clrl   (BUS_FABRIC_DCM_CTRL   , 0x00011F0F); 

#endif

        dcm_sta &= ~CPU_DCM;
    }
    
#if 0 
	if (type & TOPCKGEN_DCM) {

        dcm_info("[%s][TOPCKGEN_DCM]=0x%08x\n", __func__,TOPCKGEN_DCM);
        
        #ifdef DCM_ENABLE_DCM_CFG 
        
        dcm_clrl(DCM_CFG, (0x1 <<7));
        #endif

    	dcm_sta &= ~TOPCKGEN_DCM;
    }
#endif

    if (type & PER_DCM) {
        
        dcm_info("[%s][PER_DCM     ]=0x%08x\n", __func__,PER_DCM);

		dcm_clrl   (PERI_GLOBALCON_DCMCTL , 0x00001FF3); 

		dcm_clrl   (PERI_GLOBALCON_DCMDBC , 0x0000000F); 
		dcm_setl   (PERI_GLOBALCON_DCMDBC , 0x000000F0); 

		dcm_clrl   (PERI_GLOBALCON_DCMFSEL, 0x001F0F07); 

		
		enable_clock(MT_CG_PERI_MSDC30_0, "DCM");
		enable_clock(MT_CG_PERI_MSDC30_1, "DCM");
		enable_clock(MT_CG_PERI_MSDC30_2, "DCM");
        enable_clock(MT_CG_PERI_MSDC30_3, "DCM");
        
		dcm_clrl   (MSDC0_PATCH_BIT1       , 0x00200000); 
		dcm_setl   (MSDC0_PATCH_BIT1       , 0xFF800000); 

		dcm_clrl   (MSDC1_PATCH_BIT1       , 0x00200000); 
		dcm_setl   (MSDC1_PATCH_BIT1       , 0xFF800000); 

        dcm_clrl   (MSDC2_PATCH_BIT1       , 0x00200000); 
		dcm_setl   (MSDC2_PATCH_BIT1       , 0xFF800000); 

        dcm_clrl   (MSDC3_PATCH_BIT1       , 0x00200000); 
		dcm_setl   (MSDC3_PATCH_BIT1       , 0xFF800000); 
		
		disable_clock(MT_CG_PERI_MSDC30_0, "DCM");
		disable_clock(MT_CG_PERI_MSDC30_1, "DCM");
		disable_clock(MT_CG_PERI_MSDC30_2, "DCM");
        disable_clock(MT_CG_PERI_MSDC30_3, "DCM");

        
        enable_clock(MT_CG_PERI_USB1, "DCM");
		dcm_setl   (USB0_DCM              , 0x00070000); 
		disable_clock(MT_CG_PERI_USB1, "DCM");

		
		dcm_clrl   (PMIC_WRAP_DCM_EN      , 0x00000001); 

		
		dcm_clrl   (I2C0_I2CREG_HW_CG_EN  , 0x00000001); 
		dcm_clrl   (I2C1_I2CREG_HW_CG_EN  , 0x00000001); 
		dcm_clrl   (I2C2_I2CREG_HW_CG_EN  , 0x00000001); 
		dcm_clrl   (I2C3_I2CREG_HW_CG_EN  , 0x00000001); 
		if (dcm_I2C4_base)
		{
		    dcm_clrl   (I2C4_I2CREG_HW_CG_EN  , 0x00000001); 
        }

        dcm_sta &= ~PER_DCM;
    }

	
    if (type & IFR_DCM) {
        
		dcm_info("[%s][IFR_DCM     ]=0x%08x\n", __func__,IFR_DCM);

		
	    
		dcm_setl   (channel_A_DRAMC_PD_CTRL, 0x01000000); 
		dcm_clrl   (channel_A_DRAMC_PD_CTRL, 0xC2000008); 

		dcm_setl   (channel_B_DRAMC_PD_CTRL, 0x01000000); 
		dcm_clrl   (channel_B_DRAMC_PD_CTRL, 0xC2000008); 


		dcm_clrl   (INFRA_TOPCKGEN_DCMCTL , 0x00000771); 
#ifndef CONFIG_ARM64
		dcm_clrl   (INFRA_TOPCKGEN_DCMDBC , 0x00000001); 
#endif
		dcm_clrl   (INFRA_GLOBALCON_DCMCTL, 0x00000303); 

		dcm_setl   (MM_MMU_DCM_DIS         , 0x0000007F); 

		dcm_setl   (PERISYS_MMU_DCM_DIS    , 0x0000007F); 

		dcm_sta &= ~IFR_DCM;

    }
    
    if (type & SMI_DCM) {
		dcm_info("[%s][SMI_DCM     ]=0x%08x\n", __func__,SMI_DCM);

		dcm_clrl   (SMI_COMMON_SMI_DCM    , 0x00000001); 

#ifdef CONFIG_ARM64
        
		dcm_setl   (E3TCM_HW_DCM_DIS_SET  , 0x0000003F); 
#endif

        dcm_sta &= ~SMI_DCM;
    }

    if (type & DIS_DCM) {

		dcm_info("[%s][DIS_DCM     ]=0x%08x\n", __func__,DIS_DCM);

        dcm_writel (MMSYS_HW_DCM_DIS_SET0 , 0xFFFFFFFF); 
        dcm_writel (MMSYS_HW_DCM_DIS_SET1 , 0xFFFFFFFF); 

		
		dcm_setl   (SMI_LARB0_CON_CLR     , 0x00000010); 

        dcm_sta &= ~DIS_DCM;
    }

    if (type & ISP_DCM) {

		dcm_info("[%s][ISP_DCM     ]=0x%08x\n", __func__,ISP_DCM);

		
		dcm_setl   (CTL_RAW_D_DCM_DIS       , 0x024EAFE8); 
		dcm_setl   (CTL_DMA_DCM_DIS         , 0x07FFFFFF); 
		dcm_setl   (CTL_RGB_DCM_DIS         , 0x0000007F); 
		dcm_setl   (CTL_YUV_DCM_DIS         , 0x000FFFFF); 
        dcm_setl   (CTL_TOP_DCM_DIS         , 0x0000000F); 

		dcm_setl   (FDVT_CTRL               , 0x0000001F); 

		dcm_setl   (JPGENC_DCM_CTRL       , 0x00000001); 
		dcm_setl   (JPGDEC_DCM_CTRL       , 0x00000001); 
		dcm_writel (VENC_CLK_CG_CTRL      , 0x00000000); 
		dcm_clrl   (VENC_CLK_DCM_CTRL     , 0x00000001); 

        
		dcm_setl   (SMI_LARB2_CON_CLR     , 0x00000010); 
		
		dcm_setl   (SMI_LARB3_CON_CLR     , 0x00000010); 


        dcm_sta &= ~ISP_DCM;
    }

    if (type & VDE_DCM) {

    	dcm_info("[%s][VDE_DCM     ]=0x%08x\n", __func__,VDE_DCM);

		dcm_setl   (VDEC_DCM_CON          , 0x00000001); 

		
		dcm_setl   (SMI_LARB1_CON_CLR     , 0x00000010); 

        

        dcm_sta &= ~VDE_DCM;
    }

	if (type & MJC_DCM) {

		dcm_setl   (MJC_HW_DCM_DIS_SET    , 0xFFFFFFFF); 

		
		dcm_setl   (SMI_LARB4_CON_CLR     , 0x00000010); 

		dcm_sta &= ~MJC_DCM;
	}

    if (type & EMI_DCM) {
		dcm_info("[%s][EMI_DCM     ]=0x%08x\n", __func__,EMI_DCM);

		dcm_setl   (EMI_CONM          , 0xFF000000); 

        dcm_sta &= ~EMI_DCM;
    }

    mutex_unlock(&dcm_lock);
}

#ifndef CONFIG_ARM64
void dcm_CA7_L2_share_256K_to_external_enable(bool enable)
{
    dcm_info("dcm_CA7_L2_share_256K_to_external_enable=%d\r\n",enable);

    dcm_clrl   (CACHE_CONFIG          , 0x00000700); 

    if(enable==true){
		dcm_setl   (CACHE_CONFIG  , 0x00000900);
	}
    else{
		dcm_setl   (CACHE_CONFIG  , 0x00000B00); 
	}
}
#endif

void disable_cpu_dcm(void)
{
	mt_dcm_init();
	dcm_setl   (INFRA_TOPCKGEN_DCMCTL , 0x00000001); 
	dcm_clrl   (INFRA_TOPCKGEN_DCMCTL , 0x00000770); 
}

void enable_cpu_dcm(void)
{
	mt_dcm_init();
	dcm_setl   (INFRA_TOPCKGEN_DCMCTL , 0x00000771); 
}

void bus_dcm_enable(void)
{
	mt_dcm_init();
    dcm_setl(DCM_CFG, 0x1 << 7);
}

void bus_dcm_disable(void)
{
	mt_dcm_init();
    dcm_clrl(DCM_CFG, 0x1 << 7);
}

static unsigned int infra_dcm = 0;
void disable_infra_dcm(void)
{
#if 0 
    infra_dcm = dcm_readl(INFRA_GLOBALCON_DCMCTL);
    dcm_clrl(INFRA_GLOBALCON_DCMCTL, 0x100);
#endif
}

void restore_infra_dcm(void)
{
#if 0 
    dcm_writel(INFRA_GLOBALCON_DCMCTL, infra_dcm);
#endif
}

static unsigned int peri_dcm = 0;
void disable_peri_dcm(void)
{
	mt_dcm_init();
    peri_dcm = dcm_readl(PERI_GLOBALCON_DCMCTL);
    dcm_clrl(PERI_GLOBALCON_DCMCTL, 0x1);
}

void restore_peri_dcm(void)
{
	mt_dcm_init();
    dcm_writel(PERI_GLOBALCON_DCMCTL, peri_dcm);
}

#define dcm_attr(_name)                         \
static struct kobj_attribute _name##_attr = {   \
    .attr = {                                   \
        .name = __stringify(_name),             \
        .mode = 0644,                           \
    },                                          \
    .show = _name##_show,                       \
    .store = _name##_store,                     \
}

static const char *dcm_name[NR_DCMS] = {
    "CPU_DCM",
    "IFR_DCM",
    "PER_DCM",
    "SMI_DCM",
    "EMI_DCM",
    "DIS_DCM",
    "ISP_DCM",
    "VDE_DCM",
    "MJC_DCM",
};

void dcm_iomap(void);
void dcm_dump_base_reg(void);
static ssize_t dcm_state_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int len = 0;
    char *p = buf;

    int i;
    unsigned int sta;

    p += sprintf(p, "********** dcm_state dump **********\n");
    mutex_lock(&dcm_lock);

    for (i = 0; i < NR_DCMS; i++) {
        sta = dcm_sta & (0x1 << i);
        p += sprintf(p, "[%d][%s]%s\n", i, dcm_name[i], sta ? "on" : "off");
    }

    mutex_unlock(&dcm_lock);

	
	dcm_dump_base_reg();

    p += sprintf(p, "\n********** dcm_state help *********\n");
    p += sprintf(p, "enable dcm:    echo enable mask(dec) > /sys/power/dcm_state\n");
    p += sprintf(p, "disable dcm:   echo disable mask(dec) > /sys/power/dcm_state\n");
    p += sprintf(p, "dump reg:      echo dump mask(dec) > /sys/power/dcm_state\n");


    len = p - buf;
    return len;
}

static ssize_t dcm_state_store(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t n)
{
    char cmd[10];
    unsigned int mask;

    if (sscanf(buf, "%s %x", cmd, &mask) == 2) {
        mask &= ALL_DCM;

        enable_mux(MT_MUX_MM, "DCM");

        if (!strcmp(cmd, "enable")) {
            
            dcm_enable(mask);
            
        } else if (!strcmp(cmd, "disable")) {
            
            dcm_disable(mask);
            
        } else if (!strcmp(cmd, "dump")) {
            dcm_dump_regs(mask);
        }

	    disable_mux(MT_MUX_MM, "DCM");

        return n;
    }

    return -EINVAL;
}
dcm_attr(dcm_state);



#ifdef CONFIG_OF
void dcm_iomap(void)
{
    struct device_node *node;

    node = of_find_compatible_node(NULL, NULL, "mediatek,USB0");
    if(node){
		
		dcm_USB0_base = of_iomap(node, 0);
		printk("[DCM_USB0] dcm_USB0_base=0x%p\n",dcm_USB0_base);
    }
    else{
       	printk("[DCM_USB0] dcm_USB0_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,USB0\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,MSDC0");
    if(node){
		
		dcm_MSDC0_base = of_iomap(node, 0);
		printk("[DCM_MSDC0] dcm_MSDC0_base=0x%p\n",dcm_MSDC0_base);
    }
    else{
       	printk("[DCM_MSDC0] dcm_MSDC0_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,MSDC0\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,MSDC1");
    if(node){
		
		dcm_MSDC1_base = of_iomap(node, 0);
		printk("[DCM_MSDC1] dcm_MSDC1_base=0x%p\n",dcm_MSDC1_base);
    }
    else{
       	printk("[DCM_MSDC1] dcm_MSDC1_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,MSDC1\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,MSDC2");
    if(node){
		
		dcm_MSDC2_base = of_iomap(node, 0);
		printk("[DCM_MSDC2] dcm_MSDC2_base=0x%p\n",dcm_MSDC2_base);
    }
    else{
       	printk("[DCM_MSDC2] dcm_MSDC2_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,MSDC2\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,MSDC3");
    if(node){
		
		dcm_MSDC3_base = of_iomap(node, 0);
		printk("[DCM_MSDC3] dcm_MSDC3_base=0x%p\n",dcm_MSDC3_base);
    }
    else{
       	printk("[DCM_MSDC3] dcm_MSDC3_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,MSDC3\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,PMIC_WRAP");
    if(node){
		
		dcm_PMIC_WRAP_base = of_iomap(node, 0);
		printk("[DCM_PMIC_WRAP] dcm_PMIC_WRAP_base=0x%p\n",dcm_PMIC_WRAP_base);
    }
    else{
       	printk("[DCM_PMIC_WRAP] dcm_PMIC_WRAP_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,PMIC_WRAP\n", __func__, __LINE__);
    }


    node = of_find_compatible_node(NULL, NULL, "mediatek,I2C0");
    if(node){
		
		dcm_I2C0_base = of_iomap(node, 0);
		printk("[DCM_I2C0] dcm_I2C0_base=0x%p\n",dcm_I2C0_base);
    }
    else{
       	printk("[DCM_I2C0] dcm_I2C0_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,I2C0\n", __func__, __LINE__);
    }


    node = of_find_compatible_node(NULL, NULL, "mediatek,I2C1");
    if(node){
		
		dcm_I2C1_base = of_iomap(node, 0);
		printk("[DCM_I2C1] dcm_I2C1_base=0x%p\n",dcm_I2C1_base);
    }
    else{
       	printk("[DCM_I2C1] dcm_I2C1_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,I2C1\n", __func__, __LINE__);
    }


    node = of_find_compatible_node(NULL, NULL, "mediatek,I2C2");
    if(node){
		
		dcm_I2C2_base = of_iomap(node, 0);
		printk("[DCM_I2C2] dcm_I2C2_base=0x%p\n",dcm_I2C2_base);
    }
    else{
       	printk("[DCM_I2C2] dcm_I2C2_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,I2C2\n", __func__, __LINE__);
    }


    node = of_find_compatible_node(NULL, NULL, "mediatek,I2C3");
    if(node){
		
		dcm_I2C3_base = of_iomap(node, 0);
		printk("[DCM_I2C3] dcm_I2C3_base=0x%p\n",dcm_I2C3_base);
    }
    else{
       	printk("[DCM_I2C3] dcm_I2C3_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,I2C3\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,I2C4");
    if(node){
		
		dcm_I2C4_base = of_iomap(node, 0);
		printk("[DCM_I2C4] dcm_I2C4_base=0x%p\n",dcm_I2C4_base);
    }
    else{
        dcm_I2C4_base = 0;
       	printk("[DCM_I2C4] dcm_I2C4_base error\n");
#if 0 
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,I2C4\n", __func__, __LINE__);
#endif
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,MJC_CONFIG");
    if(node){
		
		dcm_MJC_CONFIG_base = of_iomap(node, 0);
		printk("[DCM_MJC_CONFIG] dcm_MJC_CONFIG_base=0x%p\n",dcm_MJC_CONFIG_base);
    }
    else{
       	printk("[DCM_MJC_CONFIG] dcm_MJC_CONFIG_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,MJC_CONFIG\n", __func__, __LINE__);
    }


    node = of_find_compatible_node(NULL, NULL, "mediatek,MCUCFG");
    if(node){
		
		dcm_MCUCFG_base = of_iomap(node, 0);
		printk("[DCM_MCUCFG] dcm_MCUCFG_base=0x%p\n",dcm_MCUCFG_base);
    }
    else{
       	printk("[DCM_MCUCFG] dcm_MCUCFG_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,MCUCFG\n", __func__, __LINE__);
    }

#ifdef CONFIG_ARM64
    node = of_find_compatible_node(NULL, NULL, "mediatek,CKSYS");
#else
    node = of_find_compatible_node(NULL, NULL, "mediatek,TOPCKGEN");
#endif    
    if(node){
		
		dcm_TOPCKGEN_base = of_iomap(node, 0);
		printk("[DCM_TOPCKGEN] dcm_TOPCKGEN_base=0x%p\n",dcm_TOPCKGEN_base);
    }
    else{
       	printk("[DCM_TOPCKGEN] dcm_TOPCKGEN_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,TOPCKGEN\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,INFRACFG_AO");
    if(node){
		
		dcm_INFRACFG_AO_base = of_iomap(node, 0);
		printk("[DCM_INFRACFG_AO] dcm_INFRACFG_AO_base=0x%p\n",dcm_INFRACFG_AO_base);
    }
    else{
       	printk("[DCM_INFRACFG_AO] dcm_INFRACFG_AO_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,INFRACFG_AO\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,M4U");
    if(node){
		
		dcm_M4U_base = of_iomap(node, 0);
		printk("[DCM_M4U] dcm_M4U_base=0x%p\n",dcm_M4U_base);
    }
    else{
       	printk("[DCM_M4U] dcm_M4U_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,M4U\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,PERISYS_IOMMU");
    if(node){
		
		dcm_PERISYS_IOMMU_base = of_iomap(node, 0);
		printk("[DCM_PERISYS_IOMMU] dcm_PERISYS_IOMMU_base=0x%p\n",dcm_PERISYS_IOMMU_base);
    }
    else{
       	printk("[DCM_PERISYS_IOMMU] dcm_PERISYS_IOMMU_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,PERISYS_IOMMU\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,PERICFG");
    if(node){
		
		dcm_PERICFG_base = of_iomap(node, 0);
		printk("[DCM_PERICFG] dcm_PERICFG_base=0x%p\n",dcm_PERICFG_base);
    }
    else{
       	printk("[DCM_PERICFG] dcm_PERICFG_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,PERICFG\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,DRAMC0");
    if(node){
		
		dcm_DRAMC0_base = of_iomap(node, 0);
		printk("[DCM_DRAMC0] dcm_DRAMC0_base=0x%p\n",dcm_DRAMC0_base);
    }
    else{
       	printk("[DCM_DRAMC0] dcm_DRAMC0_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,DRAMC0\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,DRAMC1");
    if(node){
		
		dcm_DRAMC1_base = of_iomap(node, 0);
		printk("[DCM_DRAMC1] dcm_DRAMC1_base=0x%p\n",dcm_DRAMC1_base);
    }
    else{
       	printk("[DCM_DRAMC1] dcm_DRAMC1_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,DRAMC1\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,EMI");
    if(node){
		
		dcm_EMI_base = of_iomap(node, 0);
		printk("[DCM_EMI] dcm_EMI_base=0x%p\n",dcm_EMI_base);
    }
    else{
       	printk("[DCM_EMI] dcm_EMI_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,EMI\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,SMI_COMMON");
    if(node){
		
		dcm_SMI_COMMO_base = of_iomap(node, 0);
		printk("[DCM_SMI_COMMON] dcm_SMI_COMMO_base=0x%p\n",dcm_SMI_COMMO_base);
    }
    else{
       	printk("[DCM_SMI_COMMON] dcm_SMI_COMMO_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,SMI_COMMON\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,SMI_LARB0");
    if(node){
		
		dcm_SMI_LARB0_base = of_iomap(node, 0);
		printk("[DCM_SMI_LARB0] dcm_SMI_LARB0_base=0x%p\n",dcm_SMI_LARB0_base);
    }
    else{
       	printk("[DCM_SMI_LARB0] dcm_SMI_LARB0_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,SMI_LARB0\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,SMI_LARB1");
    if(node){
		
		dcm_SMI_LARB1_base = of_iomap(node, 0);
		printk("[DCM_SMI_LARB1 dcm_SMI_LARB1_base=0x%p\n",dcm_SMI_LARB1_base);
    }
    else{
       	printk("[DCM_SMI_LARB1 dcm_SMI_LARB1_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,SMI_LARB1\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,SMI_LARB2");
    if(node){
		
		dcm_SMI_LARB2_base = of_iomap(node, 0);
		printk("[DCM_SMI_LARB2] dcm_SMI_LARB2_base=0x%p\n",dcm_SMI_LARB2_base);
    }
    else{
       	printk("[DCM_SMI_LARB2] dcm_SMI_LARB2_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,SMI_LARB2\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,SMI_LARB3");
    if(node){
		
		dcm_SMI_LARB3_base = of_iomap(node, 0);
		printk("[DCM_SMI_LARB3] dcm_SMI_LARB3_base=0x%p\n",dcm_SMI_LARB3_base);
    }
    else{
       	printk("[DCM_SMI_LARB3] dcm_SMI_LARB3_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,SMI_LARB3\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,SMI_LARB5");
    if(node){
		
		dcm_SMI_LARB5_base = of_iomap(node, 0);
		printk("[DCM_SMI_LARB5] dcm_SMI_LARB5_base=0x%p\n",dcm_SMI_LARB5_base);
    }
    else{
       	printk("[DCM_SMI_LARB5] dcm_SMI_LARB5_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,SMI_LARB5\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,CAM1");
    if(node){
		
		dcm_CAM1_base = of_iomap(node, 0);
		printk("[DCM_CAM1] dcm_CAM1_base=0x%p\n",dcm_CAM1_base);
    }
    else{
       	printk("[DCM_CAM1] dcm_CAM1_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,CAM1\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,FDVT");
    if(node){
		
		dcm_FDVT_base = of_iomap(node, 0);
		printk("[DCM_FDVT] dcm_FDVT_base=0x%p\n",dcm_FDVT_base);
    }
    else{
       	printk("[DCM_FDVT] dcm_FDVT_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,FDVT\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,JPGENC");
    if(node){
		
		dcm_JPGENC_base = of_iomap(node, 0);
		printk("[DCM_JPGENC] dcm_JPGENC_base=0x%p\n",dcm_JPGENC_base);
    }
    else{
       	printk("[DCM_JPGENC] dcm_JPGENC_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,JPGENC\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,JPGDEC");
    if(node){
		
		dcm_JPGDEC_base = of_iomap(node, 0);
		printk("[DCM_JPGDEC] dcm_JPGDEC_base=0x%p\n",dcm_JPGDEC_base);
    }
    else{
       	printk("[DCM_JPGDEC] dcm_JPGDEC_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,JPGDEC\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,MMSYS_CONFIG");
    if(node){
		
		dcm_MMSYS_CONFIG_base = of_iomap(node, 0);
		printk("[DCM_MMSYS_CONFIG] dcm_MMSYS_CONFIG_base=0x%p\n",dcm_MMSYS_CONFIG_base);
    }
    else{
       	printk("[DCM_MMSYS_CONFIG] dcm_MMSYS_CONFIG_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,MMSYS_CONFIG\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,VENC_GCON");
    if(node){
		
		dcm_VENC_base = of_iomap(node, 0);
		printk("[DCM_VENC] dcm_VENC_base=0x%p\n",dcm_VENC_base);
    }
    else{
       	printk("[DCM_VENC] dcm_VENC_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,VENC\n", __func__, __LINE__);
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,VDEC_GCON");
    if(node){
		
		dcm_VDEC_GCON_base = of_iomap(node, 0);
		printk("[DCM_VDEC_GCON] dcm_VDEC_GCON_base=0x%p\n",dcm_VDEC_GCON_base);
    }
    else{
       	printk("[DCM_VDEC_GCON] dcm_VDEC_GCON_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,VDEC_GCON\n", __func__, __LINE__);
    }

#ifdef CONFIG_ARM64
    node = of_find_compatible_node(NULL, NULL, "mediatek,E3TCM");
    if(node){
		
		dcm_E3TCM_base = of_iomap(node, 0);
		printk("[DCM_E3TCM] dcm_E3TCM_base=0x%p\n",dcm_E3TCM_base);
    }
    else{
       	printk("[DCM_E3TCM] dcm_E3TCM_base error\n");
        aee_kernel_warning("mt_dcm", "@%s():%d, mediatek,E3TCM\n", __func__, __LINE__);
    }
#endif
}

#define dcm_org(fmt, args...)   

void dcm_dump_base_reg(void)
{
	
	printk("[DCM_USB0] dcm_USB0_base=0x%p\n",dcm_USB0_base);
    dcm_org("[DCM_USB0] USB0_DCM=0x%x\n",USB0_DCM);

	
	printk("[DCM_MSDC0] dcm_MSDC0_base=0x%p\n",dcm_MSDC0_base);
    dcm_org("[DCM_MSDC0] MSDC0_PATCH_BIT1=0x%x\n",MSDC0_PATCH_BIT1);

	
	printk("[DCM_MSDC1] dcm_MSDC1_base=0x%p\n",dcm_MSDC1_base);
    dcm_org("[DCM_MSDC1] MSDC1_PATCH_BIT1=0x%x\n",MSDC1_PATCH_BIT1);

	
	printk("[DCM_MSDC2] dcm_MSDC2_base=0x%p\n",dcm_MSDC2_base);
    dcm_org("[DCM_MSDC2] MSDC2_PATCH_BIT1=0x%x\n",MSDC2_PATCH_BIT1);

	
	printk("[DCM_MSDC3] dcm_MSDC3_base=0x%p\n",dcm_MSDC3_base);
    dcm_org("[DCM_MSDC3] MSDC3_PATCH_BIT1=0x%x\n",MSDC3_PATCH_BIT1);

	
	printk("[DCM_PMIC_WRAP] dcm_PMIC_WRAP_base=0x%p\n",dcm_PMIC_WRAP_base);
	dcm_org("[DCM_PMIC_WRAP] PMIC_WRAP_DCM_EN=0x%x\n",PMIC_WRAP_DCM_EN);

	
	printk("[DCM_I2C0] dcm_I2C0_base=0x%p\n",dcm_I2C0_base);
	dcm_org("[DCM_I2C0] I2C0_I2CREG_HW_CG_EN=0x%x\n",I2C0_I2CREG_HW_CG_EN);

	
	printk("[DCM_I2C1] dcm_I2C1_base=0x%p\n",dcm_I2C1_base);
	dcm_org("[DCM_I2C1] I2C1_I2CREG_HW_CG_EN=0x%x\n",I2C1_I2CREG_HW_CG_EN);

	
	printk("[DCM_I2C2] dcm_I2C2_base=0x%p\n",dcm_I2C2_base);
	dcm_org("[DCM_I2C2] I2C2_I2CREG_HW_CG_EN=0x%x\n",I2C2_I2CREG_HW_CG_EN);

	
	printk("[DCM_I2C3] dcm_I2C3_base=0x%p\n",dcm_I2C3_base);
	dcm_org("[DCM_I2C3] I2C3_I2CREG_HW_CG_EN=0x%x\n",I2C3_I2CREG_HW_CG_EN);

	
	printk("[DCM_I2C4] dcm_I2C4_base=0x%p\n",dcm_I2C4_base);
	dcm_org("[DCM_I2C4] I2C4_I2CREG_HW_CG_EN=0x%x\n",I2C4_I2CREG_HW_CG_EN);

	
	printk("[DCM_MJC_CONFIG] dcm_MJC_CONFIG_base=0x%p\n",dcm_MJC_CONFIG_base);
	dcm_org("[DCM_MJC_CONFIG] MJC_HW_DCM_DIS=0x%x\n",MJC_HW_DCM_DIS);

	
	printk("[DCM_MCUCFG] dcm_MCUCFG_base=0x%p\n",dcm_MCUCFG_base);
	dcm_org("[DCM_MCUCFG] DCM_MCUSYS_CONFIG=0x%x\n",DCM_MCUSYS_CONFIG);

	
	printk("[DCM_TOPCKGEN] dcm_TOPCKGEN_base=0x%p\n",dcm_TOPCKGEN_base);
	dcm_org("[DCM_TOPCKGEN] DCM_CFG=0x%x\n",DCM_CFG);

	
	printk("[DCM_INFRACFG_AO] dcm_INFRACFG_AO_base=0x%p\n",dcm_INFRACFG_AO_base);
	dcm_org("[DCM_INFRACFG_AO] CA7_CKDIV1=0x%x\n",CA7_CKDIV1);

	
	printk("[DCM_M4U] dcm_M4U_base=0x%p\n",dcm_M4U_base);
	dcm_org("[DCM_M4U] MM_MMU_DCM_DIS=0x%x\n",MM_MMU_DCM_DIS);

	
	printk("[DCM_PERISYS_IOMMU] dcm_PERISYS_IOMMU_base=0x%p\n",dcm_PERISYS_IOMMU_base);
	dcm_org("[DCM_PERISYS_IOMMU] PERISYS_MMU_DCM_DIS=0x%x\n",PERISYS_MMU_DCM_DIS);

	
	printk("[DCM_PERICFG] dcm_PERICFG_base=0x%p\n",dcm_PERICFG_base);
	dcm_org("[DCM_PERICFG] PERI_GLOBALCON_DCMCTL=0x%x\n",PERI_GLOBALCON_DCMCTL);

	
	printk("[DCM_DRAMC0] dcm_DRAMC0_base=0x%p\n",dcm_DRAMC0_base);
	dcm_org("[DCM_DRAMC0] channel_A_DRAMC_PD_CTRL=0x%x\n",channel_A_DRAMC_PD_CTRL);


    
	printk("[DCM_DRAMC1] dcm_DRAMC1_base=0x%p\n",dcm_DRAMC1_base);
	dcm_org("[DCM_DRAMC1] channel_B_DRAMC_PD_CTRL=0x%x\n",channel_B_DRAMC_PD_CTRL);

	
	printk("[DCM_EMI] dcm_EMI_base=0x%p\n",dcm_EMI_base);
	dcm_org("[DCM_EMI] EMI_CONM=0x%x\n",EMI_CONM);

	
	printk("[DCM_SMI_COMMON] dcm_SMI_COMMO_base=0x%p\n",dcm_SMI_COMMO_base);
	dcm_org("[DCM_SMI_COMMON] SMI_COMMON_SMI_DCM=0x%x\n",SMI_COMMON_SMI_DCM);

	
	printk("[DCM_SMI_LARB0] dcm_SMI_LARB0_base=0x%p\n",dcm_SMI_LARB0_base);
	dcm_org("[DCM_SMI_LARB0] SMI_LARB0_STA=0x%x\n",SMI_LARB0_STA);

	
	printk("[DCM_SMI_LARB1 dcm_SMI_LARB1_base=0x%p\n",dcm_SMI_LARB1_base);
	dcm_org("[DCM_SMI_LARB1 SMI_LARB1_STAT=0x%x\n",SMI_LARB1_STAT);

	
	printk("[DCM_SMI_LARB2] dcm_SMI_LARB2_base=0x%p\n",dcm_SMI_LARB2_base);
	dcm_org("[DCM_SMI_LARB2] SMI_LARB2_STAT=0x%x\n",SMI_LARB2_STAT);

	
	printk("[DCM_SMI_LARB3] dcm_SMI_LARB3_base=0x%p\n",dcm_SMI_LARB3_base);
	dcm_org("[DCM_SMI_LARB3] SMI_LARB3_STAT=0x%x\n",SMI_LARB3_STAT);

	
	printk("[DCM_SMI_LARB5] dcm_SMI_LARB5_base=0x%p\n",dcm_SMI_LARB5_base);
	dcm_org("[DCM_SMI_LARB5] SMI_LARB4_STAT=0x%x\n",SMI_LARB4_STAT);

	
	printk("[DCM_CAM1] dcm_CAM1_base=0x%p\n",dcm_CAM1_base);
	dcm_org("[DCM_CAM1] CTL_RAW_DCM_DIS=0x%x\n",CTL_RAW_DCM_DIS);

	
	printk("[DCM_FDVT] dcm_FDVT_base=0x%p\n",dcm_FDVT_base);
	dcm_org("[DCM_FDVT] FDVT_CTRL=0x%x\n",FDVT_CTRL);

	
	printk("[DCM_JPGENC] dcm_JPGENC_base=0x%p\n",dcm_JPGENC_base);
	dcm_org("[DCM_JPGENC] JPGENC_DCM_CTRL=0x%x\n",JPGENC_DCM_CTRL);

	
	printk("[DCM_JPGDEC] dcm_JPGDEC_base=0x%p\n",dcm_JPGDEC_base);
	dcm_org("[DCM_JPGDEC] JPGDEC_DCM_CTRL=0x%x\n",JPGDEC_DCM_CTRL);

	
	printk("[DCM_MMSYS_CONFIG] dcm_MMSYS_CONFIG_base=0x%p\n",dcm_MMSYS_CONFIG_base);
	dcm_org("[DCM_MMSYS_CONFIG] MMSYS_HW_DCM_DIS0=0x%x\n",MMSYS_HW_DCM_DIS0);

	
	printk("[DCM_VENC] dcm_VENC_base=0x%p\n",dcm_VENC_base);
	dcm_org("[DCM_VENC] VENC_CLK_CG_CTRL=0x%x\n",VENC_CLK_CG_CTRL);

	
	printk("[DCM_VDEC_GCON] dcm_VDEC_GCON_base=0x%p\n",dcm_VDEC_GCON_base);
	dcm_org("[DCM_VDEC_GCON] VDEC_DCM_CON=0x%x\n",VDEC_DCM_CON);

}

#endif




void mt_dcm_init(void)
{
    int err = 0;

	if (dcm_initiated)
		return 0;

	dcm_initiated = 1;

    dcm_info("[%s]entry!!,ALL_DCM=%d\n", __func__,ALL_DCM);
#ifdef CONFIG_OF
	dcm_iomap();
#endif

    
    dcm_enable(ALL_DCM);
    dcm_dump_regs(ALL_DCM);

    err = sysfs_create_file(power_kobj, &dcm_state_attr.attr);

    if (err) {
        dcm_err("[%s]: fail to create sysfs\n", __func__);
    }
}
