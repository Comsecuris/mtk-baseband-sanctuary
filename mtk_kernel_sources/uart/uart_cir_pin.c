/*
 * drivers/misc/mediatek/uart/uart_cir_pin.c -
 *    Driver for Consumer IR related pins controlling
 *
 * Copyright (C) 2014 HTC Corporation.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/async.h>

#include <linux/delay.h>
#include <mach/mt_gpio.h>
#include <linux/of.h>

#include <linux/htc_cir.h>
#include <linux/tca6418_ioexpander.h>
#include <mach/mt_gpio.h>
#include <mach/mt_gpio_core.h>

#include <linux/htc_devices_dtb.h>

#define D(x...) printk("[CIR] " x)
#define E(x...) printk("[CIR][ERR]" x)

struct mtk_uart_port {
	uint32_t rst_pin;
	uint32_t cir_ls_en;
	uint32_t uart_tx_gpio;
	uint32_t uart_rx_gpio;
	uint32_t *uart_tx_config;
	uint32_t *uart_rx_config;
	uint32_t *uart_tx_sleep_config;
	uint32_t *uart_rx_sleep_config;
	struct class *cir_class;
	struct device *cir_dev;
	bool cir_power_save;
};

static struct mtk_uart_port *htc_cir_port;

static ssize_t enable_ls_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	return 0;
}

static ssize_t enable_ls_store(struct device *dev,
			struct device_attribute *attr, const char *buf,size_t count)
{
	int enable = 0;
	struct mtk_uart_port *mtk_cir_port = htc_cir_port;

	sscanf(buf, "%d", &enable);
	D("%s trigger cir ls, input = %d.\n", __func__, enable);
	if ((enable == 1) && (mtk_cir_port->cir_ls_en)){
		
		ioexp_gpio_set_cfg(mtk_cir_port->cir_ls_en,
						IOEXP_OUTPUT, IOEXP_PULLDOWN, 1);
	} else if ((enable == 0) && (mtk_cir_port->cir_ls_en)) {
		
		ioexp_gpio_set_cfg(mtk_cir_port->cir_ls_en,
						IOEXP_OUTPUT, IOEXP_PULLDOWN, 0);
	}
	return count;
}
static DEVICE_ATTR(enable_ls, 0644, enable_ls_show, enable_ls_store);

static ssize_t reset_cir_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	return 0;
}
static ssize_t reset_cir_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct mtk_uart_port *mtk_cir_port = htc_cir_port;
	int reset;

	sscanf(buf, "%d", &reset);
	D("%s trigger cir reset, input = %d.\n", __func__, reset);

	if (reset == 1) {
		if (mtk_cir_port->rst_pin) {
			
			ioexp_gpio_set_cfg(mtk_cir_port->rst_pin,
						IOEXP_OUTPUT, IOEXP_PULLDOWN, 0);
			msleep(2);
			
			
			
			ioexp_gpio_set_cfg(mtk_cir_port->rst_pin,
						IOEXP_OUTPUT, IOEXP_NOPULL, 1);

		}
	}

	return count;
}
static DEVICE_ATTR(reset_cir, 0600, reset_cir_show, reset_cir_store);

static int gpio_config_cir(struct mtk_uart_port *mtk_cir_port, int value)
{
	int ret = 0;
	mtk_cir_port->rst_pin = CIR_RST;
	mtk_cir_port->cir_ls_en = CIR_LS_EN;
	D("%s: %d; rst_pin=%d, cir_ls_en=%d, 3v3_en=%d\n",
		__func__, value, mtk_cir_port->rst_pin, mtk_cir_port->cir_ls_en, CIR_3V3_EN);

	ioexp_gpio_set_cfg(CIR_3V3_EN, IOEXP_OUTPUT, IOEXP_PULLDOWN, 1);

	if (value) {
		if (mtk_cir_port->rst_pin) {
			ret = ioexp_gpio_set_cfg(mtk_cir_port->rst_pin,
						IOEXP_OUTPUT, IOEXP_PULLDOWN, 0);
			if (unlikely(ret)) {
				E("ioexp_gpio_set_cfg failed for:%d, ret=%d\n",
						mtk_cir_port->rst_pin, ret);
				goto exit_gpio_config;
			}
			
		}

		if (mtk_cir_port->cir_ls_en) {
			ret = ioexp_gpio_set_cfg(mtk_cir_port->cir_ls_en,
						IOEXP_OUTPUT, IOEXP_PULLDOWN, 1);
			if (unlikely(ret)) {
				E("ioexp_gpio_set_cfg failed for:%d, ret=%d\n",
						mtk_cir_port->cir_ls_en, ret);
				goto exit_gpio_config;
			}
			
		}

		if (mtk_cir_port->rst_pin)
			ioexp_gpio_set_cfg(mtk_cir_port->rst_pin,
						IOEXP_OUTPUT, IOEXP_NOPULL, 1);
			if (unlikely(ret)) {
				E("ioexp_gpio_set_cfg failed for:%d, ret=%d\n",
						mtk_cir_port->rst_pin, ret);
				goto exit_gpio_config;
			}
			
	} else {
		if (mtk_cir_port->rst_pin) {
			ioexp_gpio_set_cfg(mtk_cir_port->rst_pin,
						IOEXP_OUTPUT, IOEXP_PULLDOWN, 0);
			
		}
		if (mtk_cir_port->cir_ls_en) {
			ioexp_gpio_set_cfg(mtk_cir_port->cir_ls_en,
						IOEXP_OUTPUT, IOEXP_PULLDOWN, 0);
			
		}

		ioexp_gpio_set_cfg(CIR_3V3_EN, IOEXP_OUTPUT, IOEXP_PULLDOWN, 0);
	}

exit_gpio_config:
	return ret;
}
static int uart_gpio_control(int gpio, uint32_t *config)
{
	D("%s, GPIO=%d\n", __func__, gpio);
	gpio |= 0x80000000;
	mt_set_gpio_mode(gpio, config[0]);
	mt_set_gpio_dir(gpio, config[1]);
	mt_set_gpio_pull_enable(gpio, config[2]);
	mt_set_gpio_pull_select(gpio, config[3]);
	mt_set_gpio_out(gpio, config[4]);

	return 0;
}

static struct cir_platform_data *mtk_dt_to_pdata(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct cir_platform_data *pdata;
	struct property *prop;
	uint32_t idx;
	uint32_t gpio[2], config[5];

	D("%s\n", __func__);
	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata) {
		E("unable to allocate memory for platform data\n");
		return ERR_PTR(-ENOMEM);
	}

	if (node) {
		
		if (of_property_read_u32(node, "cell-index", &idx)) {
			E("[UART] get uart index from DTS fail!!\n");
			return NULL;
		}

		
		if (of_property_read_u32_array(node, "gpio", gpio, ARRAY_SIZE(gpio))) {
			E("[UART%d] get gpio from DTS fail!!\n", idx);
			return NULL;
		}
		pdata->uart_tx_gpio = gpio[0];
		pdata->uart_rx_gpio = gpio[1];

		
		if (of_property_read_u32_array(node, "uart_tx_config",
					config, ARRAY_SIZE(config))) {
			E("[UART%d] get uart_tx_config from DTS fail!!\n", idx);
			return NULL;
		}
		memcpy(pdata->uart_tx_config, config, sizeof(config));
		
		if (of_property_read_u32_array(node, "uart_rx_config",
					config, ARRAY_SIZE(config))) {
			E("[UART%d] get uart_rx_config from DTS fail!!\n", idx);
			return NULL;
		}
		memcpy(pdata->uart_rx_config, config, sizeof(config));

		pdata->cir_power_save = of_property_read_bool(node, "power_save");
		D("%s: cir_power_save=%d\n", __func__, pdata->cir_power_save);

		if (pdata->cir_power_save) {
			prop = of_find_property(node, "uart_tx_sleep_config", NULL);
			if (prop) {
				if (of_property_read_u32_array(node, "uart_tx_sleep_config",
					config, ARRAY_SIZE(config))) {
					E("[UART%d] get uart_tx_sleep_config from DTS fail!!\n", idx);
					return NULL;
				}
				memcpy(pdata->uart_tx_sleep_config, config, sizeof(config));
			}

			prop = of_find_property(node, "uart_rx_sleep_config", NULL);
			if (prop) {
				if (of_property_read_u32_array(node, "uart_rx_sleep_config",
					config, ARRAY_SIZE(config))) {
					E("[UART%d] get uart_rx_sleep_config from DTS fail!!\n", idx);
					return NULL;
				}
				memcpy(pdata->uart_rx_sleep_config, config, sizeof(config));
			}
		}
	} else {
		E("[UART] can not get DTS node!!\n");
		return NULL;
	}

	return pdata;
}

static int htc_uart_cir_probe(struct platform_device *pdev)
{
	struct mtk_uart_port *mtk_cir_port;
	struct cir_platform_data *pdata;
	int err, ret;

	if(strcmp(htc_get_bootmode(), "charger") == 0) {
		D("%s: offmode_charging, do not probe htc_uart_cir\n", __func__);
		return -EACCES;
	}

	D("%s: +++\n", __func__);

	if (pdev->dev.of_node || !pdev->dev.platform_data) {
		D("%s: get pdev->dev.of_node or pdata unexist\n", __func__);
		pdata = mtk_dt_to_pdata(pdev);
		pdev->dev.platform_data = pdata;
	}

	mtk_cir_port = devm_kzalloc(&pdev->dev, sizeof(*mtk_cir_port), GFP_KERNEL);
	if (!mtk_cir_port) {
		E("%s: unable to allocate memory for platform data\n", __func__);
		return -ENOMEM;
	}

	mtk_cir_port->uart_tx_gpio = pdata->uart_tx_gpio;
	mtk_cir_port->uart_rx_gpio = pdata->uart_rx_gpio;
	mtk_cir_port->uart_tx_config = pdata->uart_tx_config;
	mtk_cir_port->uart_rx_config = pdata->uart_rx_config;
	mtk_cir_port->uart_tx_sleep_config = pdata->uart_tx_sleep_config;
	mtk_cir_port->uart_rx_sleep_config = pdata->uart_rx_sleep_config;
	mtk_cir_port->cir_power_save = pdata->cir_power_save;

	htc_cir_port = mtk_cir_port;
	uart_gpio_control(mtk_cir_port->uart_tx_gpio, mtk_cir_port->uart_tx_config);
	uart_gpio_control(mtk_cir_port->uart_rx_gpio, mtk_cir_port->uart_rx_config);
	gpio_config_cir(mtk_cir_port, 1);

	mtk_cir_port->cir_class = class_create(THIS_MODULE, "htc_cir");
	if (IS_ERR(mtk_cir_port->cir_class)) {
		ret = PTR_ERR(mtk_cir_port->cir_class);
		mtk_cir_port->cir_class = NULL;
		goto err_create_class;
	}
	mtk_cir_port->cir_dev = device_create(mtk_cir_port->cir_class,
				NULL, 0, "%s", "cir");
	if (unlikely(IS_ERR(mtk_cir_port->cir_dev))) {
		ret = PTR_ERR(mtk_cir_port->cir_dev);
		mtk_cir_port->cir_dev = NULL;
		goto err_create_ls_device;
	}

	
	ret = device_create_file(mtk_cir_port->cir_dev, &dev_attr_reset_cir);
	if (ret)
		goto err_create_ls_device_file;
	ret = device_create_file(mtk_cir_port->cir_dev, &dev_attr_enable_ls);
	if (ret)
		goto err_create_ls_device_file;

	D("%s: ---\n", __func__);
	return err;

err_create_ls_device_file:
	device_unregister(mtk_cir_port->cir_dev);
err_create_ls_device:
	class_destroy(mtk_cir_port->cir_class);
err_create_class:
	gpio_config_cir(mtk_cir_port, 0);
	return ret;
}
static int htc_uart_cir_remove(struct platform_device *pdev)
{
	struct mtk_uart_port *mtk_cir_port = htc_cir_port;
	D("%s: +++\n", __func__);

	gpio_config_cir(mtk_cir_port, 0);
	device_remove_file(mtk_cir_port->cir_dev, &dev_attr_reset_cir);
	device_remove_file(mtk_cir_port->cir_dev, &dev_attr_enable_ls);
	device_unregister(mtk_cir_port->cir_dev);
	class_destroy(mtk_cir_port->cir_class);

	devm_kfree(&pdev->dev, htc_cir_port);

	if (pdev->dev.of_node || !pdev->dev.platform_data) {
		devm_kfree(&pdev->dev, pdev->dev.platform_data);
	}
	D("%s: ---\n", __func__);
	return 0;
}

#ifdef CONFIG_PM
static int htc_uart_cir_suspend(struct device *dev)
{
	struct mtk_uart_port *mtk_cir_port = htc_cir_port;
	D("%s:\n", __func__);
	if (mtk_cir_port->cir_power_save) {
		uart_gpio_control(mtk_cir_port->uart_tx_gpio, mtk_cir_port->uart_tx_sleep_config);
		uart_gpio_control(mtk_cir_port->uart_rx_gpio, mtk_cir_port->uart_rx_sleep_config);
	}
}

static int htc_uart_cir_resume(struct device *dev)
{
	struct mtk_uart_port *mtk_cir_port = htc_cir_port;
	D("%s\n", __func__);
	if (mtk_cir_port->cir_power_save) {
		uart_gpio_control(mtk_cir_port->uart_tx_gpio, mtk_cir_port->uart_tx_config);
		uart_gpio_control(mtk_cir_port->uart_rx_gpio, mtk_cir_port->uart_rx_config);
	}
}
#endif
struct platform_device htc_uart_cir_device = {
	.name= "CIR",
	.id= -1,
};

#ifdef CONFIG_OF
static const struct of_device_id htc_uart_cir_of_ids[] = {
	{ .compatible = "CIR", },
	{}
};
#endif

#ifdef CONFIG_PM
static struct dev_pm_ops htc_uart_cir_dev_pm_ops = {
	.suspend_noirq = htc_uart_cir_suspend,
	.resume_noirq = htc_uart_cir_resume,
};
#endif

static struct platform_driver mtk_uart_dev_drv =
{
	.probe	= htc_uart_cir_probe,
	.remove	= htc_uart_cir_remove,
	.driver	= {
		.name	= "CIR",
		.owner	= THIS_MODULE,
#ifdef CONFIG_OF
		.of_match_table = htc_uart_cir_of_ids,
#endif
#ifdef CONFIG_PM
		.pm = &htc_uart_cir_dev_pm_ops,
#endif
	}
};

static void __init htc_uart_cir_init_async(void *unused, async_cookie_t cookie)
{
	D("%s:\n", __func__);
	
	
	platform_driver_register(&mtk_uart_dev_drv);
}

static int __init htc_uart_cir_init(void)
{
	D("%s: +++\n", __func__);
	async_schedule(htc_uart_cir_init_async, NULL);
	return 0;
}


static void __exit htc_uart_cir_exit(void)
{
	D("%s:\n", __func__);
	platform_driver_unregister(&mtk_uart_dev_drv);
	platform_device_unregister(&htc_uart_cir_device);
}

late_initcall(htc_uart_cir_init);
module_exit(htc_uart_cir_exit);
MODULE_AUTHOR("HTC");
MODULE_DESCRIPTION("HTC Consumer IR Driver");
MODULE_LICENSE("GPL");
