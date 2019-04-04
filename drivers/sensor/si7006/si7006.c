/*
 * Copyright (c) 2019 Vaishali Pathak <vaishali@electronut.in>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <sensor.h>
#include <kernel.h>
#include <device.h>
#include <init.h>
#include <string.h>
#include <misc/byteorder.h>
#include <misc/__assert.h>
#include <logging/log.h>
#include <i2c.h>
#include <logging/log.h>
#include <stdio.h>
#include "si7006.h"

#define LOG_LEVEL CONFIG_SENSOR_LOG_LEVEL
LOG_MODULE_REGISTER(si7006);

struct si7006_data {
	struct device *i2c_dev;
	float temperature;
	float humidity;
};

/**
 * @brief function to get relative humidity
 *
 * @return float
 */
static float si7006_get_humidity(struct device *i2c_dev)
{
	uint8_t hum[2];

	if (i2c_burst_read(i2c_dev, SI7006_ADDR,
			Si7006_MEAS_REL_HUMIDITY_MASTER_MODE, hum, sizeof(hum)) != 0) {
		LOG_ERR("read register err");
	}

	uint16_t relative_humidity_code = (hum[0] << 8) | (hum[1]);

	float relative_humidity =
		((125 * (float)relative_humidity_code) / ((float)65536)) - 6;

	LOG_DBG("humidity= %d.%2d", (s32_t)relative_humidity,
		((s32_t)relative_humidity * 100) % 100);

	return relative_humidity;
}

/**
 * @brief function to get temperature
 *
 * @return float
 */

static float si7006_get_temperature(struct device *i2c_dev)
{
	uint8_t temp[2];

	if (i2c_burst_read(i2c_dev, SI7006_ADDR, Si7006_MEAS_TEMP_MASTER_MODE, temp,
			sizeof(temp)) != 0) {
		LOG_ERR("read register err");
	}

	uint16_t temperature_code = (temp[0] << 8) | (temp[1]);

	float temperature =
		((175.72 * (float)temperature_code) / (float)65536) - 46.85;

	LOG_DBG("temperature = %d", (s32_t)temperature);

	return temperature;
}

/**
 * @brief fetch a sample from the sensor
 *
 * @return 0
 */
static int si7006_sample_fetch(struct device *dev, enum sensor_channel chan)
{
	struct si7006_data *si_data = dev->driver_data;

	float cal_temperature = si7006_get_temperature(si_data->i2c_dev);

	si_data->temperature = cal_temperature;

	float cal_humidity = si7006_get_humidity(si_data->i2c_dev);

	si_data->humidity = cal_humidity;

	return 0;
}

/**
 * @brief sensor value get
 *
 * @return -ENOTSUP for unsupported channels
 */
static int si7006_channel_get(struct device *dev, enum sensor_channel chan,
				  struct sensor_value *val)
{
	struct si7006_data *si_data = dev->driver_data;

	if (chan == SENSOR_CHAN_AMBIENT_TEMP) {
		float si_temp = si_data->temperature;

		val->val1 = si_temp;
		val->val2 = (s64_t)(si_temp * 1000000) % 1000000;
		return 0;
	} else if (chan == SENSOR_CHAN_HUMIDITY) {
		float si_hum = si_data->humidity;

		val->val1 = si_hum;
		val->val2 = (s64_t)(si_hum * 1000000) % 1000000;
		return 0;
	} else {
		return -ENOTSUP;
	}
}

static const struct sensor_driver_api si7006_api = {
	.sample_fetch = &si7006_sample_fetch,
	.channel_get = &si7006_channel_get,
};

/**
 * @brief initiasize the sensor
 *
 * @return 0 for success
 */

static int si7006_init(struct device *dev)
{
	struct si7006_data *drv_data = dev->driver_data;
	drv_data->i2c_dev = device_get_binding("I2C_0");

	if (!drv_data->i2c_dev) {
		LOG_ERR("i2c master not found.");
		return -EINVAL;
	}

	LOG_DBG("si7006 init ok");

	return 0;
}

struct si7006_data si_data;

DEVICE_AND_API_INIT(si7006, "SI7006_0", si7006_init, &si_data, NULL,
			POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY, &si7006_api);
