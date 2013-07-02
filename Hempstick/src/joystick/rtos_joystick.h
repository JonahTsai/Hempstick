/*
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