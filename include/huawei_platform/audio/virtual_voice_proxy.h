/*
 * virtual_voice_proxy.h
 *
 * virtual voice proxy header file
 *
 * Copyright (c) 2019 Huawei Technologies Co., Ltd.
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

#ifndef __VIRTUAL_VOICE_PROXY_H__
#define __VIRTUAL_VOICE_PROXY_H__

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/proc_fs.h>
#include <linux/semaphore.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/unistd.h>
#include <linux/uaccess.h>
#include <linux/list.h>
#include <linux/io.h>
#ifdef CONFIG_COMPAT
#include <linux/compat.h>
#endif
#include <linux/of.h>
#include <asm/memory.h>
#include <asm/types.h>

#include "drv_mailbox_cfg.h"
#include "audio_hifi.h"
#include "hifi_om.h"

enum virtual_call_status {
	VIRTUAL_CALL_STATUS_OFF = 0,
	VIRTUAL_CALL_STATUS_ON,
};

enum virtual_proxy_status {
	VIRTUAL_PROXY_STATUS_NOT_REGISTER = 0,
	VIRTUAL_CALL_STATUS_REGISTER,
};

/* 48k 20ms 2channel 2byte */
#define VOICE_PROXY_LIMIT_PARAM_SIZE 3840

#define VOICE_PROXY_QUEUE_SIZE_MAX 60

/* handle the reply message from hifi,record msg_id and data */
struct virtual_voice_proxy_rev_msg {
	unsigned short msg_id;
	unsigned short date_len;
	unsigned short voice_status;
	unsigned short result;
};

struct virtual_voice_proxy_confirm {
	uint16_t msg_id;
	uint32_t result;
};

struct virtual_voice_proxy_cnf_cmd_code {
	struct list_head list_node;
	uint16_t msg_id;
};

struct virtual_voice_proxy_cmd_node {
	struct list_head list_node;
	uint16_t msg_id;
};

struct virtual_voice_proxy_data_buf {
	uint32_t id;
	int32_t size;
	int8_t data[4];
};

struct virtual_voice_proxy_data_node {
	struct list_head list_node;
	struct virtual_voice_proxy_data_buf list_data;
};

typedef void (*register_mailbox_cb)(mb_msg_cb mail_cb);
typedef int32_t (*read_mailbox_msg_cb)(void *mail_handle,
		int8_t *buf, int32_t *size);
typedef int32_t (*mailbox_send_msg_cb)(uint32_t mailcode, uint16_t msg_id,
		const void *buf, uint32_t size);
typedef void (*voice_proxy_sign_init_cb)(void);
typedef void (*voice_proxy_msg_cb)(int8_t *rev_buf, uint32_t buf_size);
typedef void (*voice_proxy_cmd_cb)(uint32_t *size, uint16_t *msg_id);
typedef int32_t (*voice_proxy_add_data_cb)(int8_t *data, uint32_t size);

struct voice_proxy_msg_handle {
	uint16_t msg_id;
	voice_proxy_msg_cb callback;
};

struct voice_proxy_cmd_handle {
	uint16_t msg_id;
	voice_proxy_cmd_cb callback;
};

struct voice_proxy_sign_init {
	voice_proxy_sign_init_cb callback;
};

struct virtual_voice_proxy_mode {
	uint16_t msg_id;
	uint32_t mode;
};

struct virtual_voice_proxy_driver_status {
	uint16_t msg_id;
	uint32_t status;
};

void virtual_voice_proxy_register_msg_callback(uint16_t msg_id,
					voice_proxy_msg_cb callback);
void virtual_voice_proxy_deregister_msg_callback(uint16_t msg_id);
void virtual_voice_proxy_register_cmd_callback(uint16_t msg_id,
					voice_proxy_cmd_cb callback);
void virtual_voice_proxy_deregister_cmd_callback(uint16_t msg_id);
void virtual_voice_proxy_register_sign_init_callback(
	voice_proxy_sign_init_cb cb);
void virtual_voice_proxy_deregister_sign_init_callback(
	voice_proxy_sign_init_cb cb);
void virtual_voice_proxy_set_send_sign(bool first,
	bool *cnf, int64_t *timestamp);
int64_t virtual_voice_proxy_get_time_ms(void);
int32_t virtual_voice_proxy_add_work_queue_cmd(uint16_t msg_id);
int32_t virtual_voice_proxy_create_data_node(
	struct virtual_voice_proxy_data_node **node,
	int8_t *data, int32_t size);
int32_t virtual_voice_proxy_add_cmd(uint16_t msg_id);
int32_t virtual_voice_proxy_add_data(voice_proxy_add_data_cb callback,
	int8_t *data, uint32_t size, uint16_t msg_id);
int32_t voice_proxy_mailbox_send_msg_cb(uint32_t mailcode, uint16_t msg_id,
	const void *buf, uint32_t size);
#endif /* end of virtual_voice_proxy.h */

