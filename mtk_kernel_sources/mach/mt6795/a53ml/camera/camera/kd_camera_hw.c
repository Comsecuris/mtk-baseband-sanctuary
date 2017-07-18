#include <linux/videodev2.h>
#include <linux/i2c.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <asm/atomic.h>
#include <linux/xlog.h>

#include "kd_camera_hw.h"

#include "kd_imgsensor.h"
#include "kd_imgsensor_define.h"
#include "kd_camera_feature.h"

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

int kdCISModulePowerOn(CAMERA_DUAL_CAMERA_SENSOR_ENUM SensorIdx, char *currSensorName, BOOL On, char* mode_name)
{

    u32 pinSetIdx = 0;

#define IDX_PS_CMRST 0
#define IDX_PS_CMPDN 4
#define IDX_PS_MODE 1
#define IDX_PS_ON   2
#define IDX_PS_OFF  3


    u32 pinSet[3][8] = {
        
        {   GPIO_CAMERA_INVALID,
            GPIO_CAMERA_INVALID,   
            GPIO_OUT_ONE,              
            GPIO_OUT_ZERO,             
            65,
            0,
            GPIO_OUT_ONE,
            GPIO_OUT_ZERO,
        },
        
        {   GPIO_CAMERA_INVALID,
            GPIO_CAMERA_INVALID,
            GPIO_OUT_ONE,
            GPIO_OUT_ZERO,
            84, 
            0,
            GPIO_OUT_ONE,
            GPIO_OUT_ZERO,
        },
        
        {   GPIO_CAMERA_INVALID,
            GPIO_CAMERA_INVALID,   
            GPIO_OUT_ONE,               
            GPIO_OUT_ZERO,              
            GPIO_CAMERA_INVALID,
            GPIO_CAMERA_INVALID,
            GPIO_OUT_ONE,
            GPIO_OUT_ZERO,
        }
    };

    if (DUAL_CAMERA_MAIN_SENSOR == SensorIdx) {
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
        if ( pinSetIdx == 0)
        {
            
            mt_set_gpio_mode(3,0);
            mt_set_gpio_dir(3,GPIO_DIR_OUT);
            mt_set_gpio_out(3, GPIO_OUT_ONE);
        }

        
        if(TRUE != hwPowerOn(CAMERA_POWER_VCAM_D2, VOL_1800,mode_name))
        {
            PK_DBG("[CAMERA SENSOR] Fail to enable digital power\n");
            goto _kdCISModulePowerOn_exit_;
        }

        
        if ( pinSetIdx == 1)
        {
            
            mt_set_gpio_mode(93,0);
            mt_set_gpio_dir(93,GPIO_DIR_OUT);
            mt_set_gpio_out(93, GPIO_OUT_ONE);
        }
        {
            
            if(TRUE != hwPowerOn(CAMERA_POWER_VCAM_A, VOL_2800,mode_name))
            {
                PK_DBG("[CAMERA SENSOR] Fail to enable analog power\n");
                goto _kdCISModulePowerOn_exit_;
            }

            
            if ((currSensorName && (0 == strcmp(currSensorName,"imx135mipiraw")))||
                    (currSensorName && (0 == strcmp(currSensorName,"imx220mipiraw")))||
                    (currSensorName && (0 == strcmp(currSensorName,"imx214mipiraw"))))
            {
                if(TRUE != hwPowerOn(CAMERA_POWER_VCAM_D, VOL_1000,mode_name))
                {
                    PK_DBG("[CAMERA SENSOR] Fail to enable digital power\n");
                    goto _kdCISModulePowerOn_exit_;
                }
            }
            else if( (currSensorName && (0 == strcmp(SENSOR_DRVNAME_OV13850_MIPI_RAW, currSensorName))) || (currSensorName && (0 == strcmp(SENSOR_DRVNAME_OV13850MAIN_MIPI_RAW, currSensorName))) )
            {
                if(TRUE != hwPowerOn(CAMERA_POWER_VCAM_D, VOL_1200,mode_name))
                {
                    PK_DBG("[CAMERA SENSOR] Fail to enable digital power\n");
                    goto _kdCISModulePowerOn_exit_;
                }
            }
            else if(currSensorName && (0 == strcmp(SENSOR_DRVNAME_OV4688_MIPI_RAW, currSensorName)))
            {
                if(TRUE != hwPowerOn(SUB_CAMERA_POWER_VCAM_D, VOL_1200,mode_name))
                {
                    PK_DBG("[CAMERA SENSOR] Fail to enable digital power\n");
                    goto _kdCISModulePowerOn_exit_;
                }
            }
            else if(currSensorName && (0 == strcmp(SENSOR_DRVNAME_OV5648_MIPI_RAW, currSensorName)))
            {
                if(TRUE != hwPowerOn(SUB_CAMERA_POWER_VCAM_D, VOL_1500,mode_name))
                {
                    PK_DBG("[CAMERA SENSOR] Fail to enable digital power\n");
                    goto _kdCISModulePowerOn_exit_;
                }
            }
            else {
                if(TRUE != hwPowerOn(CAMERA_POWER_VCAM_D, VOL_1800,mode_name))
                {
                    PK_DBG("[CAMERA SENSOR] Fail to enable digital power\n");
                    goto _kdCISModulePowerOn_exit_;
                }
            }
            
            if(TRUE != hwPowerOn(CAMERA_POWER_VCAM_A2, VOL_2800,mode_name))
            {
                PK_DBG("[CAMERA SENSOR] Fail to enable analog power\n");
                
                goto _kdCISModulePowerOn_exit_;
            }
            mdelay(10);
            
            if(currSensorName && (0 == strcmp(currSensorName,"ov13850mipiraw"))) {
                if (GPIO_CAMERA_INVALID != pinSet[pinSetIdx][IDX_PS_CMPDN])
                {
                    if(mt_set_gpio_mode(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_MODE])) {
                        PK_DBG("[CAMERA LENS] set gpio mode failed!! (CMPDN)\n");
                    }
                    if(mt_set_gpio_dir(pinSet[pinSetIdx][IDX_PS_CMPDN],GPIO_DIR_OUT)) {
                        PK_DBG("[CAMERA LENS] set gpio dir failed!! (CMPDN)\n");
                    }
                    if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_OFF])) {
                        PK_DBG("[CAMERA LENS] set gpio failed!! (CMPDN)\n");
                    }
                }
                if (GPIO_CAMERA_INVALID != pinSet[pinSetIdx][IDX_PS_CMRST])
                {
                    if(mt_set_gpio_mode(pinSet[pinSetIdx][IDX_PS_CMRST],pinSet[pinSetIdx][IDX_PS_CMRST+IDX_PS_MODE])) {
                        PK_DBG("[CAMERA SENSOR] set gpio mode failed!! (CMRST)\n");
                    }
                    if(mt_set_gpio_dir(pinSet[pinSetIdx][IDX_PS_CMRST],GPIO_DIR_OUT)) {
                        PK_DBG("[CAMERA SENSOR] set gpio dir failed!! (CMRST)\n");
                    }
                    if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMRST],pinSet[pinSetIdx][IDX_PS_CMRST+IDX_PS_OFF])) {
                        PK_DBG("[CAMERA SENSOR] set gpio failed!! (CMRST)\n");
                    }
                }
                mdelay(2);
                if (GPIO_CAMERA_INVALID != pinSet[pinSetIdx][IDX_PS_CMRST])
                {
                    if(mt_set_gpio_mode(pinSet[pinSetIdx][IDX_PS_CMRST],pinSet[pinSetIdx][IDX_PS_CMRST+IDX_PS_MODE])) {
                        PK_DBG("[CAMERA SENSOR] set gpio mode failed!! (CMRST)\n");
                    }
                    if(mt_set_gpio_dir(pinSet[pinSetIdx][IDX_PS_CMRST],GPIO_DIR_OUT)) {
                        PK_DBG("[CAMERA SENSOR] set gpio dir failed!! (CMRST)\n");
                    }
                    if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMRST],pinSet[pinSetIdx][IDX_PS_CMRST+IDX_PS_ON])) {
                        PK_DBG("[CAMERA SENSOR] set gpio failed!! (CMRST)\n");
                    }
                }
                mdelay(2);
                if (GPIO_CAMERA_INVALID != pinSet[pinSetIdx][IDX_PS_CMPDN])
                {
                    if(mt_set_gpio_mode(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_MODE])) {
                        PK_DBG("[CAMERA LENS] set gpio mode failed!! (CMPDN)\n");
                    }
                    if(mt_set_gpio_dir(pinSet[pinSetIdx][IDX_PS_CMPDN],GPIO_DIR_OUT)) {
                        PK_DBG("[CAMERA LENS] set gpio dir failed!! (CMPDN)\n");
                    }
                    if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_ON])) {
                        PK_DBG("[CAMERA LENS] set gpio failed!! (CMPDN)\n");
                    }
                }
                mdelay(20);
            }
            else if(currSensorName && (0 == strcmp(SENSOR_DRVNAME_OV4688_MIPI_RAW, currSensorName))) {
                if (GPIO_CAMERA_INVALID != pinSet[pinSetIdx][IDX_PS_CMPDN])
                {
                    if(mt_set_gpio_mode(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_MODE])) {
                        PK_DBG("[CAMERA LENS] set gpio mode failed!! (CMPDN)\n");
                    }
                    if(mt_set_gpio_dir(pinSet[pinSetIdx][IDX_PS_CMPDN],GPIO_DIR_OUT)) {
                        PK_DBG("[CAMERA LENS] set gpio dir failed!! (CMPDN)\n");
                    }
                    if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_OFF])) {
                        PK_DBG("[CAMERA LENS] set gpio failed!! (CMPDN)\n");
                    }
                }
                if (GPIO_CAMERA_INVALID != pinSet[pinSetIdx][IDX_PS_CMRST])
                {
                    if(mt_set_gpio_mode(pinSet[pinSetIdx][IDX_PS_CMRST],pinSet[pinSetIdx][IDX_PS_CMRST+IDX_PS_MODE])) {
                        PK_DBG("[CAMERA SENSOR] set gpio mode failed!! (CMRST)\n");
                    }
                    if(mt_set_gpio_dir(pinSet[pinSetIdx][IDX_PS_CMRST],GPIO_DIR_OUT)) {
                        PK_DBG("[CAMERA SENSOR] set gpio dir failed!! (CMRST)\n");
                    }
                    if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMRST],pinSet[pinSetIdx][IDX_PS_CMRST+IDX_PS_OFF])) {
                        PK_DBG("[CAMERA SENSOR] set gpio failed!! (CMRST)\n");
                    }
                }
                mdelay(2);
                if (GPIO_CAMERA_INVALID != pinSet[pinSetIdx][IDX_PS_CMRST])
                {
                    if(mt_set_gpio_mode(pinSet[pinSetIdx][IDX_PS_CMRST],pinSet[pinSetIdx][IDX_PS_CMRST+IDX_PS_MODE])) {
                        PK_DBG("[CAMERA SENSOR] set gpio mode failed!! (CMRST)\n");
                    }
                    if(mt_set_gpio_dir(pinSet[pinSetIdx][IDX_PS_CMRST],GPIO_DIR_OUT)) {
                        PK_DBG("[CAMERA SENSOR] set gpio dir failed!! (CMRST)\n");
                    }
                    if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMRST],pinSet[pinSetIdx][IDX_PS_CMRST+IDX_PS_ON])) {
                        PK_DBG("[CAMERA SENSOR] set gpio failed!! (CMRST)\n");
                    }
                }
                mdelay(2);
                if (GPIO_CAMERA_INVALID != pinSet[pinSetIdx][IDX_PS_CMPDN])
                {
                    if(mt_set_gpio_mode(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_MODE])) {
                        PK_DBG("[CAMERA LENS] set gpio mode failed!! (CMPDN)\n");
                    }
                    if(mt_set_gpio_dir(pinSet[pinSetIdx][IDX_PS_CMPDN],GPIO_DIR_OUT)) {
                        PK_DBG("[CAMERA LENS] set gpio dir failed!! (CMPDN)\n");
                    }
                    if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_ON])) {
                        PK_DBG("[CAMERA LENS] set gpio failed!! (CMPDN)\n");
                    }
                }
                mdelay(20);
            }
            else
            {
                if (GPIO_CAMERA_INVALID != pinSet[pinSetIdx][IDX_PS_CMRST]) {
                    if(mt_set_gpio_mode(pinSet[pinSetIdx][IDX_PS_CMRST],pinSet[pinSetIdx][IDX_PS_CMRST+IDX_PS_MODE])) {
                        PK_DBG("[CAMERA SENSOR] set gpio mode failed!! \n");
                    }
                    if(mt_set_gpio_dir(pinSet[pinSetIdx][IDX_PS_CMRST],GPIO_DIR_OUT)) {
                        PK_DBG("[CAMERA SENSOR] set gpio dir failed!! \n");
                    }
                    if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMRST],pinSet[pinSetIdx][IDX_PS_CMRST+IDX_PS_OFF])) {
                        PK_DBG("[CAMERA SENSOR] set gpio failed!! \n");
                    }
                    mdelay(10);
                    if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMRST],pinSet[pinSetIdx][IDX_PS_CMRST+IDX_PS_ON])) {
                        PK_DBG("[CAMERA SENSOR] set gpio failed!! \n");
                    }
                    mdelay(1);
                    
                 }
                if (GPIO_CAMERA_INVALID != pinSet[pinSetIdx][IDX_PS_CMPDN]) {
                    if (currSensorName && (0 == strcmp(SENSOR_DRVNAME_OV16825_MIPI_RAW, currSensorName)))
                    {
                        if(mt_set_gpio_mode(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_MODE])) {
                            PK_DBG("[CAMERA LENS] set gpio mode failed!! \n");
                        }
                        if(mt_set_gpio_dir(pinSet[pinSetIdx][IDX_PS_CMPDN],GPIO_DIR_OUT)) {
                            PK_DBG("[CAMERA LENS] set gpio dir failed!! \n");
                        }
                        if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_OFF])) {
                            PK_DBG("[CAMERA LENS] set gpio failed!! \n");
                        }
                        PK_DBG("[CAMERA SENSOR] SENSOR_DRVNAME_OV16825_MIPI_RAW Set IDX_PS_CMPDN low \n");
                    }
                    else
                    {
                        if(mt_set_gpio_mode(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_MODE])) {
                            PK_DBG("[CAMERA LENS] set gpio mode failed!! \n");
                        }
                        if(mt_set_gpio_dir(pinSet[pinSetIdx][IDX_PS_CMPDN],GPIO_DIR_OUT)) {
                            PK_DBG("[CAMERA LENS] set gpio dir failed!! \n");
                        }
                        if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_ON])) {
                            PK_DBG("[CAMERA LENS] set gpio failed!! \n");
                        }
                    }
                }
            }
        }
    }
    else {
        if(pinSetIdx == 0 ) {
            ISP_MCLK1_EN(0);
        }
        else if (pinSetIdx == 1) {
            ISP_MCLK2_EN(0);
        }
        else if (pinSetIdx == 2) {
            ISP_MCLK3_EN(0);
        }
        
        if (GPIO_CAMERA_INVALID != pinSet[pinSetIdx][IDX_PS_CMRST]) {
            if(mt_set_gpio_mode(pinSet[pinSetIdx][IDX_PS_CMRST],pinSet[pinSetIdx][IDX_PS_CMRST+IDX_PS_MODE])) {
                PK_DBG("[CAMERA SENSOR] set gpio mode failed!! \n");
            }
            if(mt_set_gpio_dir(pinSet[pinSetIdx][IDX_PS_CMRST],GPIO_DIR_OUT)) {
                PK_DBG("[CAMERA SENSOR] set gpio dir failed!! \n");
            }
            if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMRST],pinSet[pinSetIdx][IDX_PS_CMRST+IDX_PS_OFF])) {
                PK_DBG("[CAMERA SENSOR] set gpio failed!! \n");   
            }
        }
        if (GPIO_CAMERA_INVALID != pinSet[pinSetIdx][IDX_PS_CMPDN]) {
            if(mt_set_gpio_dir(pinSet[pinSetIdx][IDX_PS_CMPDN],GPIO_DIR_OUT)) {
                PK_DBG("[CAMERA LENS] set gpio dir failed!! \n");
            }
            if(mt_set_gpio_mode(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_MODE])) {
                PK_DBG("[CAMERA LENS] set gpio mode failed!! \n");
            }

            if (currSensorName && (0 == strcmp(SENSOR_DRVNAME_OV16825_MIPI_RAW, currSensorName)))
            {
                if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMPDN],GPIO_OUT_ONE)) {
                    PK_DBG("[CAMERA LENS] set gpio failed!! \n");   
                }
            }
            else
            {
                if(mt_set_gpio_out(pinSet[pinSetIdx][IDX_PS_CMPDN],pinSet[pinSetIdx][IDX_PS_CMPDN+IDX_PS_OFF])) {
                    PK_DBG("[CAMERA LENS] set gpio failed!! \n");   
                }
            }
        }

        if ( pinSetIdx == 0)
        {
            
            mt_set_gpio_mode(3,0);
            mt_set_gpio_dir(3,GPIO_DIR_OUT);
            mt_set_gpio_out(3, GPIO_OUT_ZERO);
        }
        if(TRUE != hwPowerDown(CAMERA_POWER_VCAM_A2,mode_name))
        {
            PK_DBG("[CAMERA SENSOR] Fail to OFF AF power(%d)\n",CAMERA_POWER_VCAM_A2);
            
            goto _kdCISModulePowerOn_exit_;
        }
        mdelay(1);
        
        if (currSensorName && (0 == strcmp(currSensorName,"imx135mipiraw")))
        {
            if(TRUE != hwPowerDown(CAMERA_POWER_VCAM_D,mode_name))
            {
                PK_DBG("[CAMERA SENSOR] Fail to OFF core power(%d)\n",CAMERA_POWER_VCAM_D);
                goto _kdCISModulePowerOn_exit_;
            }
        }
        else if(currSensorName && (0 == strcmp(SENSOR_DRVNAME_OV5648_MIPI_RAW, currSensorName)) || currSensorName && (0 == strcmp(SENSOR_DRVNAME_OV4688_MIPI_RAW, currSensorName)))
        {
            if(TRUE != hwPowerDown(SUB_CAMERA_POWER_VCAM_D,mode_name))
            {
                PK_DBG("[CAMERA SENSOR] Fail to OFF core power(%d)\n",SUB_CAMERA_POWER_VCAM_D);
                goto _kdCISModulePowerOn_exit_;
            }
        }
        else {
            if(TRUE != hwPowerDown(CAMERA_POWER_VCAM_D,mode_name))
            {
                PK_DBG("[CAMERA SENSOR] Fail to OFF core power(%d)\n",CAMERA_POWER_VCAM_D);
                goto _kdCISModulePowerOn_exit_;
            }

        }
        mdelay(1);
        if ( pinSetIdx == 1)
        {
            
            mt_set_gpio_mode(93,0);
            mt_set_gpio_dir(93,GPIO_DIR_OUT);
            mt_set_gpio_out(93, GPIO_OUT_ZERO);
        }
        if(TRUE != hwPowerDown(CAMERA_POWER_VCAM_A,mode_name)) {
            PK_DBG("[CAMERA SENSOR] Fail to OFF analog power(%d)\n",CAMERA_POWER_VCAM_A);
            
            goto _kdCISModulePowerOn_exit_;
        }
        
        if(TRUE != hwPowerDown(CAMERA_POWER_VCAM_D2, mode_name)) {
            PK_DBG("[CAMERA SENSOR] Fail to OFF digital power(%d)\n",CAMERA_POWER_VCAM_D2);
            
            goto _kdCISModulePowerOn_exit_;
        }
    }
    return 0;

_kdCISModulePowerOn_exit_:
    return -EIO;

}

EXPORT_SYMBOL(kdCISModulePowerOn);



