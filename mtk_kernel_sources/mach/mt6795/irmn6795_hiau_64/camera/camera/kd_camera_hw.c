#include <linux/videodev2.h>
#include <linux/i2c.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <asm/atomic.h>
#include <linux/xlog.h>
#include <linux/tca6418_ioexpander.h>


#include "kd_camera_hw.h"

#include "kd_imgsensor.h"
#include "kd_imgsensor_define.h"
#include "kd_camera_feature.h"
#include <linux/htc_devices_dtb.h>
#define HTC_SMT 1
static signed int IO_1V8_CNT=0;
static signed int IO_1V2_CNT=0;
#define PFX "[kd_camera_hw]"
#define PK_DBG_NONE(fmt, arg...)    do {} while (0)
#define PK_DBG_FUNC(fmt, arg...)    xlog_printk(ANDROID_LOG_INFO, PFX , fmt, ##arg)

#define DEBUG_CAMERA_HW_K
#ifdef DEBUG_CAMERA_HW_K
#define PK_DBG PK_DBG_FUNC
#define PK_ERR(fmt, arg...)         xlog_printk(ANDROID_LOG_ERR, PFX , fmt, ##arg)
#define PK_XLOG_INFO(fmt, args...) \
                do {    \
                   xlog_printk(ANDROID_LOG_INFO, PFX , fmt, ##arg); \
                } while(0)
#else
#define PK_DBG(a,...)
#define PK_ERR(a,...)
#define PK_XLOG_INFO(fmt, args...)
#endif

#ifndef BOOL
typedef unsigned char BOOL;
#endif

extern void ISP_MCLK1_EN(BOOL En);
extern void ISP_MCLK2_EN(BOOL En);
extern void ISP_MCLK3_EN(BOOL En);

extern int I2C_SEL_PIN_VAL;
int kdCISModulePowerOn(CAMERA_DUAL_CAMERA_SENSOR_ENUM SensorIdx, char *currSensorName, BOOL On, char* mode_name)
{

u32 pinSetIdx = 0;

#define IDX_PS_CMRST 0
#define IDX_PS_CMPDN 4
#define IDX_PS_MODE 1
#define IDX_PS_ON   2
#define IDX_PS_OFF  3


u32 pinSet[3][8] = {
                        
#if HTC_SMT
                     {  GPIO_CAMERA_INVALID,
                        GPIO_CAMERA_INVALID,   
#else
                     {  CAMERA_CMRST_PIN,
                        CAMERA_CMRST_PIN_M_GPIO,   
#endif
                        GPIO_OUT_ONE,              
                        GPIO_OUT_ZERO,             
                        CAMERA_CMPDN_PIN,
                        CAMERA_CMPDN_PIN_M_GPIO,
                        GPIO_OUT_ONE,
                        GPIO_OUT_ZERO,
                     },
                     
                     {
                        CAMERA_CMRST1_PIN,
                        CAMERA_CMRST1_PIN_M_GPIO,
                        GPIO_OUT_ONE,
                        GPIO_OUT_ZERO,
#if HTC_SMT
                        GPIO_CAMERA_INVALID,
                        GPIO_CAMERA_INVALID,
#else

                        CAMERA_CMPDN1_PIN,
                        CAMERA_CMPDN1_PIN_M_GPIO,
#endif
                        GPIO_OUT_ONE,
                        GPIO_OUT_ZERO,
                     },
                     
                     {
                        GPIO_CAMERA_INVALID,
                        GPIO_CAMERA_INVALID,   
                        GPIO_OUT_ONE,               
                        GPIO_OUT_ZERO,              
                        GPIO_CAMERA_INVALID,
                        GPIO_CAMERA_INVALID,
                        GPIO_OUT_ONE,
                        GPIO_OUT_ZERO,
                     }
                   };

    if (DUAL_CAMERA_MAIN_SENSOR == SensorIdx){
#if HTC_SMT
	
#endif
        pinSetIdx = 0;
    }
    else if (DUAL_CAMERA_SUB_SENSOR == SensorIdx) {
        pinSetIdx = 1;
    }
    else if (DUAL_CAMERA_MAIN_2_SENSOR == SensorIdx) {
        pinSetIdx = 2;
    }

    
        if (On) {
        if(pinSetIdx == 0 ) {
            ISP_MCLK1_EN(1);
        }
        else if (pinSetIdx == 1) {
            ISP_MCLK2_EN(1);
        }
        else if (pinSetIdx == 2) {
            ISP_MCLK3_EN(1);
        }
#if HTC_SMT
#define GPIO_CAMERA_1V8_EN_PIN GPIO66
#define GPIO_CAMERA_A2V8_EN_PIN GPIO56
#define GPIO_CAMERA_D1V_EN_PIN GPIO54
#define GPIO_CAMERA_AF_EN_PIN GPIO67
#define GPIO_CAMERA_A2V8_EN_PIN_M_GPIO 0
#define GPIO_CAMERA_D1V_EN_PIN_M_GPIO 0
#define GPIO_CAMERA_1V8_EN_PIN_M_GPIO 0
#define GPIO_CAMERA_AF_EN_PIN_M_GPIO 0

    if(IO_1V8_CNT<0){
        PK_DBG("IO_1V8_CNT=%d. Reset IO_1V8_CNT!\n",IO_1V8_CNT);
        IO_1V8_CNT=0;
    }
    if(IO_1V2_CNT<0){
         PK_DBG("IO_1V2_CNT=%d. Reset IO_1V2_CNT!\n",IO_1V2_CNT);
        IO_1V2_CNT=0;
    }
           if(of_machine_hwid() < 2)
           {
                if(mt_set_gpio_mode(GPIO_CAMERA_AF_EN_PIN,GPIO_CAMERA_AF_EN_PIN_M_GPIO)){PK_DBG("[CAMERA SENSOR] AF_VCC set gpio mode failed!! \n");}
                if(mt_set_gpio_dir(GPIO_CAMERA_AF_EN_PIN,GPIO_DIR_OUT)){PK_DBG("[CAMERA SENSOR] AF_VCC set gpio dir failed!! \n");}
                if(mt_set_gpio_out(GPIO_CAMERA_AF_EN_PIN,GPIO_OUT_ONE)){PK_DBG("[CAMERA SENSOR] AF_VCC set gpio failed!! \n");}
           }
           else
           {
                 ioexp_gpio_set_cfg(GPIO14,	IOEXP_OUTPUT, IOEXP_PULLDOWN, 0);
                 ioexp_gpio_set_value(GPIO14,1);
           }
           
           if (DUAL_CAMERA_MAIN_2_SENSOR == SensorIdx)
           {
               ioexp_gpio_set_value(CAM2_RST, 1);
               mdelay(10);
           }

           PK_DBG("### Hiauml PCB version = %d. ### \n",of_machine_hwid() );
           if(of_machine_hwid() < 2)
           {
	       IO_1V8_CNT++;
	       PK_DBG( "power on : IO_1V8_CNT = %d. \n", IO_1V8_CNT );
               PK_DBG("Hiauml PCB version before XC .\n");
               if(mt_set_gpio_mode(GPIO_CAMERA_1V8_EN_PIN,GPIO_CAMERA_1V8_EN_PIN_M_GPIO)){PK_DBG("[CAMERA SENSOR] VCAM_IO set gpio mode failed!! \n");}
               if(mt_set_gpio_dir(GPIO_CAMERA_1V8_EN_PIN,GPIO_DIR_OUT)){PK_DBG("[CAMERA SENSOR] VCAM_IO set gpio dir failed!! \n");}
               if(mt_set_gpio_out(GPIO_CAMERA_1V8_EN_PIN,GPIO_OUT_ONE)){PK_DBG("[CAMERA SENSOR] VCAM_IO set gpio failed!! \n");}
           }
           else
           {
                if(IO_1V8_CNT==0)
                    ioexp_gpio_set_cfg(GPIO15,	IOEXP_OUTPUT, IOEXP_PULLDOWN, 0);

                IO_1V8_CNT++;
                PK_DBG( "power on : IO_1V8_CNT = %d. \n", IO_1V8_CNT );
                PK_DBG("Hiauml PCB version after XC .\n");
                ioexp_gpio_set_value(GPIO15,1);
           }
           if (DUAL_CAMERA_MAIN_SENSOR == SensorIdx)
           {
               PK_DBG("[kdCISModulePowerOn] Adjust Main cam I2C addr to %s\n",
                       I2C_SEL_PIN_VAL == 1 ? "0x6c" : "0x20");
               ioexp_gpio_set_value(CAM_I2C_ADDR, I2C_SEL_PIN_VAL);
           }
           if(mt_set_gpio_mode(GPIO_CAMERA_A2V8_EN_PIN,GPIO_CAMERA_A2V8_EN_PIN_M_GPIO)){PK_DBG("[CAMERA SENSOR] VCAM_A set gpio mode failed!! \n");}
           if(mt_set_gpio_dir(GPIO_CAMERA_A2V8_EN_PIN,GPIO_DIR_OUT)){PK_DBG("[CAMERA SENSOR] VCAM_A set gpio dir failed!! \n");}
           if(mt_set_gpio_out(GPIO_CAMERA_A2V8_EN_PIN,GPIO_OUT_ONE)){PK_DBG("[CAMERA SENSOR] VCAM_A set gpio failed!! \n");}
           if(mt_set_gpio_mode(GPIO_CAMERA_D1V_EN_PIN,GPIO_CAMERA_D1V_EN_PIN_M_GPIO)){PK_DBG("[CAMERA SENSOR] DVDD set gpio mode failed!! \n");}
           if(mt_set_gpio_dir(GPIO_CAMERA_D1V_EN_PIN,GPIO_DIR_OUT)){PK_DBG("[CAMERA SENSOR] DVDD set gpio dir failed!! \n");}
           if(mt_set_gpio_out(GPIO_CAMERA_D1V_EN_PIN,GPIO_OUT_ONE)){PK_DBG("[CAMERA SENSOR] DVDD set gpio failed!! \n");}

           mdelay(10);

           
           if (DUAL_CAMERA_SUB_SENSOR == SensorIdx ||DUAL_CAMERA_MAIN_2_SENSOR == SensorIdx)
           ioexp_gpio_set_value(CAM2_A2V9_EN	,1);

	   if(IO_1V2_CNT==0)
               ioexp_gpio_set_cfg(CAM2_D1V2_EN,	IOEXP_OUTPUT, IOEXP_PULLDOWN, 0);

           IO_1V2_CNT++;
           PK_DBG( "power on : IO_1V2_CNT = %d. \n", IO_1V2_CNT );
           ioexp_gpio_set_value(CAM2_D1V2_EN,1);

           mdelay(10);
#else
#endif
        if (DUAL_CAMERA_MAIN_2_SENSOR == SensorIdx) {
           ioexp_gpio_set_value(CAM2_RST	,0);
           PK_DBG("[CAMERA SENSOR][CAM2 RST] CAM_RST PULL DOWN, Ov2722 RST to PWR ON!! \n");
           mdelay(1);
           PK_DBG("[CAMERA SENSOR][CAMERA PWR]## OV2722 RST to PWR ON!!!!!!\n");
        } else {

        
        if (GPIO_CAMERA_INVALID != pinSet[pinSetIdx][IDX_PS_CMRST]) {
            PK_DBG("[CAMERA SENSOR][CAMERA PWR]## FRONT RST to PWR ON!!!!!!\n");
            if(mt_set_gpio_mode(GPIO84,0)){PK_DBG("[CAMERA SENSOR] set gpio mode failed!! \n");}
            if(mt_set_gpio_dir(GPIO84,GPIO_DIR_OUT)){PK_DBG("[CAMERA SENSOR] set gpio dir failed!! \n");}
            if(mt_set_gpio_out(GPIO84,0)){PK_DBG("[CAMERA SENSOR] set gpio failed!! \n");}
            mdelay(10);
            if(mt_set_gpio_out(GPIO84,1)){PK_DBG("[CAMERA SENSOR] set gpio failed!! \n");}
            mdelay(1);
        }
        if (GPIO_CAMERA_INVALID != pinSet[pinSetIdx][IDX_PS_CMPDN]) {
            
            if (currSensorName && (0 == strcmp(SENSOR_DRVNAME_OV16825_MIPI_RAW, currSensorName)))
            {
                PK_DBG("[CAMERA SENSOR] 16825 PWDN to PWR ON\n");
                if(mt_set_gpio_mode(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_MODE])){PK_DBG("[CAMERA LENS] set gpio mode failed!! \n");}
                if(mt_set_gpio_dir(pinSet[pinSetIdx][IDX_PS_CMPDN],GPIO_DIR_OUT)){PK_DBG("[CAMERA LENS] set gpio dir failed!! \n");}
                if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_OFF])){PK_DBG("[CAMERA LENS] set gpio failed!! \n");}
                PK_DBG("[CAMERA SENSOR] SENSOR_DRVNAME_OV16825_MIPI_RAW Set IDX_PS_CMPDN low \n");
             }
             else
             {
                PK_DBG("[CAMERA SENSOR][CAMERA PWR]## MAIN CAM PWDN RST to PWR ON\n");
                if(mt_set_gpio_mode(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_MODE])){PK_DBG("[CAMERA LENS] set gpio mode failed!! \n");}
                if(mt_set_gpio_dir(pinSet[pinSetIdx][IDX_PS_CMPDN],GPIO_DIR_OUT)){PK_DBG("[CAMERA LENS] set gpio dir failed!! \n");}
                if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_ON])){PK_DBG("[CAMERA LENS] set gpio failed!! \n");}
             }
        }
      }
    }
    else {
             if (DUAL_CAMERA_MAIN_2_SENSOR == SensorIdx) {
                 ioexp_gpio_set_value(CAM2_RST	,1);
                 PK_DBG("[CAMERA SENSOR][CAM2 RST] CAM_RST PULL HIGH, Ov2722 RST to PWR OFF!! \n");
             } else {
                    
                    if (GPIO_CAMERA_INVALID != pinSet[pinSetIdx][IDX_PS_CMRST]) {
                        PK_DBG("[CAMERA SENSOR][CAMERA PWR]## FRONT RST to PWR OFF\n");
                        if(mt_set_gpio_mode(pinSet[pinSetIdx][IDX_PS_CMRST],pinSet[pinSetIdx][IDX_PS_CMRST+IDX_PS_MODE])){PK_DBG("[CAMERA SENSOR] set gpio mode failed!! \n");}
                        if(mt_set_gpio_dir(pinSet[pinSetIdx][IDX_PS_CMRST],GPIO_DIR_OUT)){PK_DBG("[CAMERA SENSOR] set gpio dir failed!! \n");}
                        if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMRST],pinSet[pinSetIdx][IDX_PS_CMRST+IDX_PS_OFF])){PK_DBG("[CAMERA SENSOR] set gpio failed!! \n");} 
                    }
                    if (GPIO_CAMERA_INVALID != pinSet[pinSetIdx][IDX_PS_CMPDN]) {
                         if(mt_set_gpio_mode(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_MODE])){PK_DBG("[CAMERA LENS] set gpio mode failed!! \n");}
                         if(mt_set_gpio_dir(pinSet[pinSetIdx][IDX_PS_CMPDN],GPIO_DIR_OUT)){PK_DBG("[CAMERA LENS] set gpio dir failed!! \n");}
                         if (currSensorName && (0 == strcmp(SENSOR_DRVNAME_OV16825_MIPI_RAW, currSensorName)))
                         {
                             PK_DBG("[CAMERA SENSOR] 16825 PWRDWN to PWR OFF\n");
                             if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMPDN],GPIO_OUT_ONE)){PK_DBG("[CAMERA LENS] set gpio failed!! \n");} 
                         }
                         else
                         {
                          PK_DBG("[CAMERA SENSOR][CAMERA PWR] MAIN CAM PWRDWN RST to PWR OFF\n");
                          if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_OFF])){PK_DBG("[CAMERA LENS] set gpio failed!! \n");} 
                         }
                    }
             }

        mdelay(10);
        if(pinSetIdx == 0 ) {
            ISP_MCLK1_EN(0);
        }
        else if (pinSetIdx == 1) {
            ISP_MCLK2_EN(0);
        }
        else if (pinSetIdx == 2) {
            ISP_MCLK3_EN(0);
        }

        mdelay(10);
#if HTC_SMT
           if(mt_set_gpio_mode(GPIO_CAMERA_A2V8_EN_PIN,GPIO_CAMERA_A2V8_EN_PIN_M_GPIO)){PK_DBG("[CAMERA SENSOR] VCAM_A set gpio mode failed!! \n");}
           if(mt_set_gpio_dir(GPIO_CAMERA_A2V8_EN_PIN,GPIO_DIR_OUT)){PK_DBG("[CAMERA SENSOR] VCAM_A set gpio dir failed!! \n");}
           if(mt_set_gpio_out(GPIO_CAMERA_A2V8_EN_PIN,GPIO_OUT_ZERO)){PK_DBG("[CAMERA SENSOR] VCAM_A set gpio failed!! \n");}
           if(IO_1V2_CNT > 0)
           IO_1V2_CNT--;
           PK_DBG("IO_1V2_CNT= %d .\n" , IO_1V2_CNT);
           if(IO_1V2_CNT ==0)
           {
	       PK_DBG(" IO_1V2 set 0 , because cnt=0. .\n");
               ioexp_gpio_set_value(CAM2_D1V2_EN,0);
           }
           else
               PK_DBG("IO_1V2 did not set 0 , because cnt.\n");

           ioexp_gpio_set_value(CAM2_A2V9_EN,0);
           if(mt_set_gpio_mode(GPIO_CAMERA_D1V_EN_PIN,GPIO_CAMERA_D1V_EN_PIN_M_GPIO)){PK_DBG("[CAMERA SENSOR] DVDD set gpio mode failed!! \n");}
           if(mt_set_gpio_dir(GPIO_CAMERA_D1V_EN_PIN,GPIO_DIR_OUT)){PK_DBG("[CAMERA SENSOR] DVDD set gpio dir failed!! \n");}
           if(mt_set_gpio_out(GPIO_CAMERA_D1V_EN_PIN,GPIO_OUT_ZERO)){PK_DBG("[CAMERA SENSOR] DVDD set gpio failed!! \n");}
           mdelay(1);  

           
           if ((currSensorName && (0 == strcmp(currSensorName, SENSOR_DRVNAME_T4KA7_MIPI_RAW)))
                   && (0 != ioexp_gpio_get_value(CAM_I2C_ADDR)))
           {
               PK_DBG("[CAMERA SENSOR][CAM2 RST] CAMERA_I2C_ADDR_PIN PULL DOWN FOR AVOID PWR LEAK (T4KA7)!!\n");
               ioexp_gpio_set_value(CAM_I2C_ADDR, 0);
           }

          if(of_machine_hwid() < 2)
          {
		if(IO_1V8_CNT > 0)
		IO_1V8_CNT--;
		PK_DBG("IO_1V8_CNT= %d .\n" , IO_1V8_CNT);
		if(IO_1V8_CNT ==0)
		{
		    PK_DBG("Hiauml PCB version before XC , IO_1V8_CNT  set 0 , because cnt=0. .\n");
		    if(mt_set_gpio_mode(GPIO_CAMERA_1V8_EN_PIN,GPIO_CAMERA_1V8_EN_PIN_M_GPIO)){PK_DBG("[CAMERA SENSOR] VCAM_IO set gpio mode failed!! \n");}
		    if(mt_set_gpio_dir(GPIO_CAMERA_1V8_EN_PIN,GPIO_DIR_OUT)){PK_DBG("[CAMERA SENSOR] VCAM_IO set gpio dir failed!! \n");}
		    if(mt_set_gpio_out(GPIO_CAMERA_1V8_EN_PIN,GPIO_OUT_ZERO)){PK_DBG("[CAMERA SENSOR] VCAM_IO set gpio failed!! \n");}
		}
		else
		PK_DBG("IO_1V8_CNT did not set 0 , because cnt.\n" );
          }
          else
          {
		if(IO_1V8_CNT > 0)
		IO_1V8_CNT--;
		PK_DBG("IO_1V8_CNT= %d .\n" , IO_1V8_CNT);
		if(IO_1V8_CNT ==0)
		{
		    PK_DBG("Hiauml PCB version after XC , IO_1V8_CNT  set 0 , because cnt=0. .\n");
		    ioexp_gpio_set_value(GPIO15,0);
		}
		else
		PK_DBG("IO_1V8_CNT did not set 0 , because cnt.\n" );
          }
           if(of_machine_hwid() < 2)
           {
               if(mt_set_gpio_mode(GPIO_CAMERA_AF_EN_PIN,GPIO_CAMERA_AF_EN_PIN_M_GPIO)){PK_DBG("[CAMERA SENSOR] AF_VCC set gpio mode failed!! \n");}
               if(mt_set_gpio_dir(GPIO_CAMERA_AF_EN_PIN,GPIO_DIR_OUT)){PK_DBG("[CAMERA SENSOR] AF_VCC set gpio dir failed!! \n");}
               if(mt_set_gpio_out(GPIO_CAMERA_AF_EN_PIN,GPIO_OUT_ZERO)){PK_DBG("[CAMERA SENSOR] AF_VCC set gpio failed!! \n");}
           }
           else
           {
                ioexp_gpio_set_value(GPIO14,0);
           }
#else
#endif
    }
    return 0;
_kdCISModulePowerOn_exit_:
    return -EIO;
}

EXPORT_SYMBOL(kdCISModulePowerOn);


