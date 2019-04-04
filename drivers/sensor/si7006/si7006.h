/*
 * Copyright (c) 2019 Vaishali Pathak <vaishali@electronut.in>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SI7006_H
#define _SI7006_H

/* Si7006 sensor address */
#define SI7006_ADDR 0x40

/* Si7006 register addresses */
#define Si7006_MEAS_REL_HUMIDITY_MASTER_MODE    0xE5
#define Si7006_MEAS_REL_HUMIDITY_NO_MASTER_MODE 0xF5
#define Si7006_MEAS_TEMP_MASTER_MODE            0xE3
#define Si7006_MEAS_TEMP_NO_MASTER_MODE         0xF3
#define Si7006_READ_OLD_TEMP                    0xE0
#define Si7006_RESET                            0xFE
#define Si7006_WRITE_HUMIDITY_TEMP_CONTR        0xE6
#define Si7006_READ_HUMIDITY_TEMP_CONTR         0xE7
#define Si7006_WRITE_HEATER_CONTR               0x51
#define Si7006_READ_HEATER_CONTR                0x11
#define Si7006_READ_ID_LOW_0                    0xFA
#define Si7006_READ_ID_LOW_1                    0x0F
#define Si7006_READ_ID_HIGH_0                   0xFC
#define Si7006_READ_ID_HIGH_1                   0xC9
#define Si7006_FIRMWARE_0                       0x84
#define Si7006_FIRMWARE_1                       0xB8


#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif /* _SI7006_H */
