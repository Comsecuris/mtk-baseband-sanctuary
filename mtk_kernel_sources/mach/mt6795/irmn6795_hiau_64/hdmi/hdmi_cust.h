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


#ifndef HDMI_CUSTOMIZATION_H
#define HDMI_CUSTOMIZATION_H

#define USING_SCALE_ADJUSTMENT

#define HDMI_I2C_CHANNEL 3

#define SII_I2C_ADDR 0x72
#define SII_I2C_ADDR_ALTERED 0x76

void ChangeGPIOToI2S();
void ChangeI2SToGPIO();

int cust_hdmi_power_on(int on);

int cust_hdmi_dpi_gpio_on(int on);

int cust_hdmi_i2s_gpio_on(int on);

int get_hdmi_i2c_addr(void);

int get_hdmi_i2c_channel(void);

#ifdef CONFIG_HTC_MHL_DETECTION
struct t_mhl_status_notifier{
	bool isMHL;
	int charging_type;
	void (*func)(bool isMHL, int charging_type);
};
static struct t_mhl_status_notifier *mhl_notifier;
void mhl_detect_register_notifier(struct t_mhl_status_notifier *);
void mhl_connect_notify(bool isMHL);
void mhl_vbus_notify(int type);
void si_reset_mhl(int level);
int si_wakeup_mhl(void);
#endif

#endif
