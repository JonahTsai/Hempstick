/*
 * Copyright (C) 2013 Jonah Tsai
 *
 * This file is part of Hempstick.
 *
 * Hempstick is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * Hemmpstick is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Hempstick.  If not, see <http://www.gnu.org/licenses/>.
 *
 * rtos_joystick.h
 *
 * Created: 6/9/2013 5:54:24 PM
 *  Author: Jonah Tsai
 */ 


#ifndef RTOS_JOYSTICK_H_
#define RTOS_JOYSTICK_H_

#include <FreeRTOS.h>
#include <semphr.h>


#include "conf_usb.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	xSemaphoreHandle mutex;
	uint8_t joystick_report[UDI_HID_JOYSTICK_REPORT_SIZE];
} rtos_joystick_t;

extern rtos_joystick_t g_rtos_joystick_control;

void rtos_joystick_init(bool is_init_tm_stick);
void joystick_send_report(void);

#ifdef __cplusplus
}
#endif

#endif /* RTOS_JOYSTICK_H_ */