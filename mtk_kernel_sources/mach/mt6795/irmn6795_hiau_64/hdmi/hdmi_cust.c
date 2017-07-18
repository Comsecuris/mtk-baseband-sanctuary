/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <mach/mt_pm_ldo.h>
#include <pmic_drv.h>

#include <cust_gpio_usage.h>
#include <hdmi_cust.h>
#include <mach/mt_gpio.h>
#include <linux/htc_devices_dtb.h>

#ifndef s32
	#define s32 signed int
#endif
#ifndef s64
	#define s64 signed long long
#endif

static bool cust_power_on = false;
int cust_hdmi_power_on(int on)
{
	if(on > 0)
	{
	    printk("MHL_Power power  \n" );
#ifdef PMIC_APP_MHL_POWER_LDO1
		if(cust_power_on == false)
		{
			hwPowerOn(PMIC_APP_MHL_POWER_LDO1, VOL_1200,"MHL");
			cust_power_on = true;
		}
#else
		printk("Error: PMIC_APP_MHL_POWER_LDO1 not defined -\n" );
#endif
	}
	else
	{
#ifdef PMIC_APP_MHL_POWER_LDO1
		if(cust_power_on == true)
		{
			hwPowerDown(PMIC_APP_MHL_POWER_LDO1, "MHL");
			cust_power_on = false;
		}
#endif
	}
	return 0;
}

int cust_hdmi_dpi_gpio_on(int on)
{
    unsigned int dpi_pin_start = 0;
	if(on > 0)
	{
#ifdef GPIO_EXT_DISP_DPI0_PIN
		for(dpi_pin_start = GPIO_EXT_DISP_DPI0_PIN; dpi_pin_start < GPIO_EXT_DISP_DPI0_PIN + 16; dpi_pin_start++)
		{
			mt_set_gpio_mode(dpi_pin_start, GPIO_MODE_01);
		}
		printk("%s, %d GPIO_EXT_DISP_DPI0_PIN is defined+ %x\n", __func__, __LINE__, GPIO_EXT_DISP_DPI0_PIN);
#else
		printk("%s,%d Error: GPIO_EXT_DISP_DPI0_PIN is not defined\n", __func__, __LINE__);
#endif
	}
	else
	{
#ifdef GPIO_EXT_DISP_DPI0_PIN
		for(dpi_pin_start = GPIO_EXT_DISP_DPI0_PIN; dpi_pin_start < GPIO_EXT_DISP_DPI0_PIN + 16; dpi_pin_start++)
		{
			mt_set_gpio_mode(dpi_pin_start, GPIO_MODE_00);
			
			if ((dpi_pin_start == GPIO_EXT_DISP_DPI0_PIN + 14) || ((dpi_pin_start == GPIO_EXT_DISP_DPI0_PIN + 15)))
				mt_set_gpio_dir(dpi_pin_start, GPIO_DIR_IN);
			else
				mt_set_gpio_dir(dpi_pin_start, GPIO_DIR_OUT);
			mt_set_gpio_pull_enable(dpi_pin_start, GPIO_PULL_ENABLE);
			mt_set_gpio_pull_select(dpi_pin_start, GPIO_PULL_DOWN);
		}
		printk("%s, %d GPIO_EXT_DISP_DPI0_PIN is defined- %x\n", __func__, __LINE__, GPIO_EXT_DISP_DPI0_PIN);
#endif
	}

	return 0;
}

int cust_hdmi_i2s_gpio_on(int on)
{
    if(on > 0)
	{
#ifdef GPIO_MHL_I2S_OUT_WS_PIN
		mt_set_gpio_mode(GPIO_MHL_I2S_OUT_WS_PIN, GPIO_MODE_01);
		mt_set_gpio_mode(GPIO_MHL_I2S_OUT_CK_PIN, GPIO_MODE_01);
		mt_set_gpio_mode(GPIO_MHL_I2S_OUT_DAT_PIN, GPIO_MODE_01);

		mt_set_gpio_dir(GPIO_MHL_I2S_OUT_WS_PIN, GPIO_DIR_OUT);
#else
		printk("%s,%d. GPIO_MHL_I2S_OUT_WS_PIN is not defined\n", __func__, __LINE__);
#endif
	}
	else
	{
#ifdef GPIO_MHL_I2S_OUT_WS_PIN
		mt_set_gpio_mode(GPIO_MHL_I2S_OUT_WS_PIN, GPIO_MODE_01);
		mt_set_gpio_mode(GPIO_MHL_I2S_OUT_CK_PIN, GPIO_MODE_01);
		mt_set_gpio_mode(GPIO_MHL_I2S_OUT_DAT_PIN, GPIO_MODE_01);

		mt_set_gpio_dir(GPIO_MHL_I2S_OUT_WS_PIN, GPIO_DIR_IN);
#endif
	}

	return 0;
}

extern int IMM_GetOneChannelValue(int dwChannel, int data[4], int* rawdata);
int get_hdmi_i2c_addr(void)
{
#ifdef GPIO_MHL_I2C_BUS_POWER
	mt_set_gpio_out(GPIO_MHL_I2C_BUS_POWER, GPIO_OUT_ONE);
#endif

#ifdef SII_I2C_ADDR
	int pcbid = of_machine_hwid();
	int bomid = of_machine_bomid();

	
	if ((pcbid < 2) || ((pcbid == 2) && (bomid < 2))) {
		printk("%s SII_I2C_ADDR_ALTERED\n",__func__);
		return (SII_I2C_ADDR_ALTERED);
	} else
		return (SII_I2C_ADDR); 

#else
    printk("dynamic_switch_i2c_address +\n");

	int res;
	int addr = 0x72;
	int data[4];

	res = IMM_GetOneChannelValue(12, data, NULL);
	printk("IMM_GetOneChannelValue - res=%d\n", res);
	if(res == 0)
	{
		printk("data: %d,%d, %d, %d\n", data[0], data[1], data[2], data[3]);
		if((data[1] >= 73 && data[1] <= 81)  ||  
		   (data[1] >= 95 && data[1] <= 103) ||  
		   (data[1] >= 131 && data[1] <= 139))   
		{
			printk("ID 2.5, ID 3, ID 4, Need switch I2C address\n");
			addr = 0x76;
		}
		else
		{
			printk("ID 2, Do not need switch I2C address\n");
		}
	}
	return addr;
#endif

}

#ifdef CONFIG_HTC_MHL_DETECTION
extern struct mhl_dev_context *si_dev_context;
extern int si_mhl_tx_post_initialize(struct mhl_dev_context *dev_context, bool bootup);
static struct  work_struct mhl_notifier_work;
void send_mhl_connect_notify(void)
{
	if (!mhl_notifier || !mhl_notifier->func)
		return;

	
	if(mhl_notifier->isMHL == false)
		mhl_notifier->charging_type = 0;

	printk("%s isMHL=%d, type= %d\n", __func__,mhl_notifier->isMHL, mhl_notifier->charging_type);
	mhl_notifier->func(mhl_notifier->isMHL, mhl_notifier->charging_type);

}
void mhl_detect_register_notifier(struct t_mhl_status_notifier *notifier)
{
	if (!notifier || !notifier->func)
		return;

	mhl_notifier = notifier;

	INIT_WORK(&mhl_notifier_work, send_mhl_connect_notify);
}

void mhl_connect_notify(bool isMHL)
{
	printk("%s isMHL=%d\n", __func__, isMHL);

#if defined(GPIO_USB_MHL_SW_SEL1)
	
	mt_set_gpio_out(GPIO_USB_MHL_SW_SEL1, isMHL);
#endif

	if (!mhl_notifier)
		return;

	if (mhl_notifier->isMHL != isMHL) {
		mhl_notifier->isMHL = isMHL;
		schedule_work(&mhl_notifier_work);
	} else {
		printk("%s skip\n", __func__);
	}
}
void mhl_vbus_notify(int type)
{
	if (!mhl_notifier)
		return;

	
	mhl_notifier->charging_type = type;
	schedule_work(&mhl_notifier_work);
}
void si_reset_mhl(int level)
{
#if defined(GPIO_MHL_RST_B_PIN)
	mt_set_gpio_out(GPIO_MHL_RST_B_PIN, level);
#endif
}
int si_wakeup_mhl(void)
{
	int ret = -1;

	if(!strcmp(htc_get_bootmode(),"download") || !strcmp(htc_get_bootmode(),"meta")) {
		printk("%s, skip in %s\n", __func__, htc_get_bootmode());
		return ret;
	}

	
	ret = si_mhl_tx_post_initialize(si_dev_context, false);

	return ret;
}
#endif

int get_hdmi_i2c_channel(void)
{
    return (HDMI_I2C_CHANNEL);
}
