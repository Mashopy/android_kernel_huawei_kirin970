/*
 * rt9748.h
 *
 * rt9748 driver
 *
 * Copyright (c) 2012-2019 Huawei Technologies Co., Ltd.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 */

#ifndef _RT9748_H_
#define _RT9748_H_

#include <linux/i2c.h>
#include <linux/device.h>
#include <linux/workqueue.h>
#include <huawei_platform/power/direct_charger.h>

#ifndef BIT
#define BIT(x)    (1 << (x))
#endif

struct rt9748_device_info {
	struct i2c_client *client;
	struct device *dev;
	struct work_struct irq_work;
	struct nty_data nty_data;
	int gpio_int;
	int irq_int;
	int irq_active;
	int gpio_en;
	int chip_already_init;
	int device_id;
};

enum loadswitch {
	loadswitch_rt9748 = 0,
	loadswitch_bq25870 = 1,
	loadswitch_fair_child = 2,
	loadswitch_nxp = 3,
};
#define LENTH_OF_BYTE                      8
#define LOADSWITCH_DEV_INFO_REG0           0x00

#define RT9748_DEVICE_INFO                 0x0
#define RT9748_EVENT_1_MASK                0x1
#define RT9748_EVENT_1_MASK_INIT           0x06

#define RT9748_EVENT_2_MASK                0x02
#define RT9748_EVENT_2_MASK_INIT           0xcc

#define RT9748_EVENT_1                     0x03
#define RT9748_VBUS_OVP_FLT                BIT(7)
#define RT9748_IBUS_REVERSE_OCP_FLT        BIT(0)

#define RT9748_EVENT_2                     0x04
#define RT9748_VDROP_OVP_FLT               BIT(4)
#define RT9748_OTP_FLT                     BIT(1)
#define RT9748_INPUT_OCP_FLT               BIT(0)

#define RT9748_EVENT_1_EN                  0x05
#define RT9748_EVENT_1_EN_INIT             0xf8
#define RT9748_PD_EN                       0x01
#define RT9748_PD_EN_MASK                  0x01
#define RT9748_PD_EN_SHIFT                 0

#define RT9748_CONTROL                     0x06
#define RT9748_CONTROL_INIT                0x0e
#define RT9748_CHARGE_EN_MASK              BIT(4)
#define RT9748_CHARGE_EN_SHIFT             4

#define RT9748_ADC_CTRL                    0x07
#define RT9748_ADC_CTRL_INIT               0x87
#define RT9748_ADC_EN_MASK                 BIT(3)
#define RT9748_ADC_EN_SHIFT                3

#define RT9748_SAMPLE_EN                   0x08
#define RT9748_SAMPLE_EN_INIT              0xfc

#define BQ25870_EVENT_1_MASK               0x01
#define BQ25870_EVENT_1_MASK_INIT          0x7e

#define BQ25870_EVENT_2_MASK               0x02
#define BQ25870_EVENT_2_MASK_INIT          0x7c

#define BQ25870_EVENT_1                    0x03
#define BQ25870_EVENT_2                    0x04

#define BQ25870_EVENT_1_EN                 0x05
#define BQ25870_EVENT_1_EN_INIT            0xf8

#define BQ25870_CONTROL                    0x06
#define BQ25870_CONTROL_INIT               0x0e
#define BQ25870_CHARGE_EN_MASK             BIT(4)
#define BQ25870_CHARGE_EN_SHIFT            4

#define BQ25870_ADC_CTRL                   0x07
#define BQ25870_ADC_CTRL_INIT              0x87
#define BQ25870_ADC_EN_MASK                BIT(3)
#define BQ25870_ADC_EN_SHIFT               3

#define BQ25870_SAMPLE_EN                  0x08
#define BQ25870_SAMPLE_EN_INIT             0xfc

#define RT9748_PROT_DLY_OCP                0x09
#define RT9748_PROT_DLY_OCP_INIT           0x00
#define RT9748_REG_INIT_MASK               (BIT(0) | BIT(1))
#define RT9748_REG_INIT_SHIFT              0
#define RT9748_IOC_OCP_MAX_6500_MA         6500
#define RT9748_IOC_OCP_MIN_0_MA            0
#define RT9748_IOC_OCP_OFFSET_0_MA         0
#define RT9748_IOC_OCP_STEP                500
#define RT9748_IOC_OCP_SHIFT               4
#define RT9748_IOC_OCP_MASK                (BIT(4) | BIT(5) | BIT(6) | BIT(7))

#define BQ25870_PROT_DLY_OCP               0x09
#define BQ25870_PROT_DLY_OCP_INIT          0x00
#define BQ25870_REG_INIT_MASK              (BIT(0) | BIT(1))
#define BQ25870_REG_INIT_SHIFT             0
#define BQ25870_IOC_OCP_MAX_7500_MA        7500
#define BQ25870_IOC_OCP_MIN_0_MA           0
#define BQ25870_IOC_OCP_OFFSET_0_MA        0
#define BQ25870_IOC_OCP_STEP               500
#define BQ25870_IOC_OCP_SHIFT              4
#define BQ25870_IOC_OCP_MASK               (BIT(4) | BIT(5) | BIT(6) | BIT(7))

#define RT9748_VBUS_OVP                    0x0a
#define RT9748_VBUS_OVP_MAX_6500_MV        6500
#define RT9748_VBUS_OVP_MIN_4200_MV        4200
#define RT9748_VBUS_OVP_OFFSET_4200_MV     4200
#define RT9748_VBUS_OVP_STEP               25
#define RT9748_VBUS_OVP_SHIFT              0
#define RT9748_VBUS_OVP_MASK               (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4) | BIT(5) | BIT(6))

#define BQ25870_VBUS_OVP                   0x0a
#define BQ25870_VBUS_OVP_MAX_6510_MV       6510
#define BQ25870_VBUS_OVP_MIN_4200_MV       4200
#define BQ25870_VBUS_OVP_OFFSET_4200_MV    4200
#define BQ25870_VBUS_OVP_STEP              30
#define BQ25870_VBUS_OVP_SHIFT             0
#define BQ25870_VBUS_OVP_MASK              (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4) | BIT(5) | BIT(6))

#define RT9748_VOUT_REG                    0x0b
#define RT9748_VOUT_REG_MAX_5000_MV        5000
#define RT9748_VOUT_REG_MIN_4200_MV        4200
#define RT9748_VOUT_REG_OFFSET_4200_MV     4200
#define RT9748_VOUT_REG_STEP               10
#define RT9748_VOUT_REG_SHIFT              0
#define RT9748_VOUT_REG_MASK               (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4) | BIT(5) | BIT(6))

#define BQ25870_VOUT_REG                   0x0b
#define BQ25870_VOUT_REG_MAX_4975_MV       4975
#define BQ25870_VOUT_REG_MIN_4200_MV       4200
#define BQ25870_VOUT_REG_OFFSET_4200_MV    4200
#define BQ25870_VOUT_REG_STEP              25
#define BQ25870_VOUT_REG_SHIFT             1
#define BQ25870_VOUT_REG_MASK              (BIT(1) | BIT(2) | BIT(3) | \
	BIT(4) | BIT(5) | BIT(6))

#define RT9748_VDROP_OVP                   0x0c
#define RT9748_VDROP_OVP_MAX_1000_MV       1000
#define RT9748_VDROP_OVP_MIN_0_MV          0
#define RT9748_VDROP_OVP_OFFSET_0_MV       0
#define RT9748_VDROP_OVP_STEP              10
#define RT9748_VDROP_OVP_SHIFT             0
#define RT9748_VDROP_OVP_MASK              (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4) | BIT(5) | BIT(6))

#define BQ25870_VDROP_OVP                  0x0c
#define BQ25870_VDROP_OVP_MAX_1000_MV      1000
#define BQ25870_VDROP_OVP_MIN_0_MV         0
#define BQ25870_VDROP_OVP_OFFSET_0_MV      0
#define BQ25870_VDROP_OVP_STEP             10
#define BQ25870_VDROP_OVP_SHIFT            1
#define BQ25870_VDROP_OVP_MASK             (BIT(1) | BIT(2) | BIT(3) | \
	BIT(4) | BIT(5) | BIT(6) | BIT(7))

#define RT9748_VDROP_ALM                   0x0d
#define RT9748_VDROP_ALM_MAX_1000_MV       1000
#define RT9748_VDROP_ALM_MIN_0_MV          0
#define RT9748_VDROP_ALM_OFFSET_0_MV       0
#define RT9748_VDROP_ALM_STEP              10
#define RT9748_VDROP_ALM_SHIFT             0
#define RT9748_VDROP_ALM_MASK              (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4) | BIT(5) | BIT(6))


#define BQ25870_VDROP_ALM                  0x0d
#define BQ25870_VDROP_ALM_MAX_1000_MV      1000
#define BQ25870_VDROP_ALM_MIN_0_MV         0
#define BQ25870_VDROP_ALM_OFFSET_0_MV      0
#define BQ25870_VDROP_ALM_STEP             10
#define BQ25870_VDROP_ALM_SHIFT            1
#define BQ25870_VDROP_ALM_MASK             (BIT(1) | BIT(2) | BIT(3) | \
	BIT(4) | BIT(5) | BIT(6) | BIT(7))

#define RT9748_VBAT_REG                    0x0e
#define RT9748_VBAT_REG_MAX_5000_MV        5000
#define RT9748_VBAT_REG_MIN_4200_MV        4200
#define RT9748_VBAT_REG_OFFSET_4200_MV     4200
#define RT9748_VBAT_REG_STEP               10
#define RT9748_VBAT_REG_SHIFT              0
#define RT9748_VBAT_REG_MASK               (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4) | BIT(5) | BIT(6))

#define BQ25870_VBAT_REG                   0x0e
#define BQ25870_VBAT_REG_MAX_4975_MV       4975
#define BQ25870_VBAT_REG_MIN_4200_MV       4200
#define BQ25870_VBAT_REG_OFFSET_4200_MV    4200
#define BQ25870_VBAT_REG_STEP              12.5
#define BQ25870_VBAT_REG_SHIFT             0
#define BQ25870_VBAT_REG_MASK              (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4) | BIT(5) | BIT(6))

#define RT9748_IBAT_OCP                    0x0f
#define RT9748_IBAT_OCP_MAX_6350_MA        6350
#define RT9748_IBAT_OCP_MIN_400_MA         400
#define RT9748_IBAT_OCP_OFFSET_0_MA        0
#define RT9748_IBAT_OCP_STEP               50
#define RT9748_IBAT_OCP_SHIFT              0
#define RT9748_IBAT_OCP_MASK               (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4) | BIT(5) | BIT(6))

#define BQ25870_IBAT_OCP                   0x0f
#define BQ25870_IBAT_OCP_MAX_6350_MA       6350
#define BQ25870_IBAT_OCP_MIN_0_MA          0
#define BQ25870_IBAT_OCP_OFFSET_0_MA       0
#define BQ25870_IBAT_OCP_STEP              50
#define BQ25870_IBAT_OCP_SHIFT             0
#define BQ25870_IBAT_OCP_MASK              (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4) | BIT(5) | BIT(6))

#define RT9748_IBUS_OCP                    0x10
#define RT9748_IBUS_OCP_MAX_6350_MA        6350
#define RT9748_IBUS_OCP_MIN_400_MA         400
#define RT9748_IBUS_OCP_OFFSET_0_MA        0
#define RT9748_IBUS_OCP_STEP               50
#define RT9748_IBUS_OCP_SHIFT              0
#define RT9748_IBUS_OCP_MASK               (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4) | BIT(5) | BIT(6))

#define BQ25870_IBUS_OCP                   0x10
#define BQ25870_IBUS_OCP_MAX_6300_MA       6300
#define BQ25870_IBUS_OCP_MIN_0_MA          0
#define BQ25870_IBUS_OCP_OFFSET_0_MA       0
#define BQ25870_IBUS_OCP_STEP              100
#define BQ25870_IBUS_OCP_SHIFT             1
#define BQ25870_IBUS_OCP_MASK              (BIT(1) | BIT(2) | BIT(3) | \
	BIT(4) | BIT(5) | BIT(6))

#define RT9748_TBUS_OTP                    0x11
#define RT9748_TBAT_OTP                    0x12

#define RT9748_VBUS_ADC2                   0x13
#define RT9748_VBUS_ADC1                   0x14
#define RT9748_VBUS_HIGH_LSB               256
#define RT9748_VBUS_LOW_LSB                1
#define RT9748_VBUS_ADC_MASK               (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4))
#define RT9748_VBUS_POLARITY_MASK          BIT(7)

#define BQ25870_VBUS_ADC2                  0x13
#define BQ25870_VBUS_ADC1                  0x14
#define BQ25870_VBUS_HIGH_LSB              256
#define BQ25870_VBUS_LOW_LSB               1
#define BQ25870_VBUS_ADC_MASK              (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4) | BIT(5) | BIT(6))
#define BQ25870_VBUS_POLARITY_MASK         BIT(7)

#define RT9748_IBUS_ADC2                   0x15
#define RT9748_IBUS_HIGH_LSB               256
#define RT9748_IBUS_LOW_LSB                1
#define RT9748_IBUS_ADC_MASK               (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4))
#define RT9748_IBUS_POLARITY_MASK          BIT(7)
#define RT9748_IBUS_ADC1                   0x16

#define BQ25870_IBUS_ADC2                  0x15
#define BQ25870_IBUS_HIGH_LSB              256
#define BQ25870_IBUS_LOW_LSB               1
#define BQ25870_IBUS_ADC_MASK              (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4) | BIT(5) | BIT(6))
#define BQ25870_IBUS_POLARITY_MASK         BIT(7)
#define BQ25870_IBUS_ADC1                  0x16

#define RT9748_VOUT_ADC2                   0x17
#define RT9748_VOUT_ADC1                   0x18
#define RT9748_VDROP_ADC2                  0x19
#define RT9748_VDROP_POLARITY_MASK         BIT(7)
#define RT9748_VDROP_ADC_MASK              (BIT(0) | BIT(1))
#define RT9748_VDROP_HIGH_LSB              256
#define RT9748_VDROP_LOW_LSB               1
#define RT9748_VDROP_ADC1                  0x1a

#define BQ25870_VOUT_ADC2                  0x17
#define BQ25870_VOUT_ADC1                  0x18
#define BQ25870_VDROP_ADC2                 0x19
#define BQ25870_VDROP_POLARITY_MASK        BIT(7)
#define BQ25870_VDROP_ADC_MASK             (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4) | BIT(5) | BIT(6))
#define BQ25870_VDROP_HIGH_LSB             256
#define BQ25870_VDROP_LOW_LSB              1
#define BQ25870_VDROP_ADC1                 0x1a

#define RT9748_VBAT_ADC2                   0x1b
#define RT9748_VBAT_ADC1                   0x1c
#define RT9748_VBAT_HIGH_LSB               256
#define RT9748_VBAT_LOW_LSB                1
#define RT9748_VBAT_ADC_MASK               (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4))
#define RT9748_VBAT_POLARITY_MASK          BIT(7)

#define BQ25870_VBAT_ADC2                  0x1b
#define BQ25870_VBAT_ADC1                  0x1c
#define BQ25870_VBAT_HIGH_LSB              256
#define BQ25870_VBAT_LOW_LSB               1
#define BQ25870_VBAT_ADC_MASK              (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4) | BIT(5) | BIT(6))
#define BQ25870_VBAT_POLARITY_MASK         BIT(7)

#define RT9748_IBAT_ADC2                   0x1d
#define RT9748_IBAT_ADC1                   0x1e
#define RT9748_IBAT_HIGH_LSB               256
#define RT9748_IBAT_LOW_LSB                1
#define RT9748_IBAT_ADC_MASK               (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4))
#define RT9748_IBAT_POLARITY_MASK          BIT(7)

#define BQ25870_IBAT_ADC2                  0x1d
#define BQ25870_IBAT_ADC1                  0x1e
#define BQ25870_IBAT_HIGH_LSB              256
#define BQ25870_IBAT_LOW_LSB               1
#define BQ25870_IBAT_ADC_MASK              (BIT(0) | BIT(1) | BIT(2) | \
	BIT(3) | BIT(4) | BIT(5) | BIT(6))
#define BQ25870_IBAT_POLARITY_MASK         BIT(7)

#define RT9748_TDIE_ADC1                   0x23
#define RT9748_EVENT_STATUS                0x24

#define RT9748_REV_CURRENT_SELECT          0x26
#define RT9748_REV_CURRENT_SELECT_INIT     0x06

#define LS_GET_DEV_ID_SHIFT                3

#endif /* _RT9748_H_ */
