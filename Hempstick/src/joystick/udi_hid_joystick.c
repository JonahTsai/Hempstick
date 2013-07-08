/**
 * \file
 *
 * \brief USB Device Human Interface Device (HID) mouse interface.
 *
 * Copyright (c) 2009-2012 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include "conf_usb.h"
#include "usb_protocol.h"
#include "udd.h"
#include "udc.h"
#include "udi_hid.h"
#include "udi_hid_joystick.h"
#include <string.h>

// #include "rtos_adc.h"

/**
 * \ingroup udi_hid_joystick_group
 * \defgroup udi_hid_joystick_group_udc Interface with USB Device Core (UDC)
 *
 * Structures and functions required by UDC.
 *
 * @{
 */
bool udi_hid_joystick_enable(void);
void udi_hid_joystick_disable(void);
bool udi_hid_joystick_setup(void);
uint8_t udi_hid_joystick_getsetting(void);

//! Global structure which contains standard UDI interface for UDC
UDC_DESC_STORAGE udi_api_t udi_api_hid_joystick = {
	.enable = (bool(*)(void))udi_hid_joystick_enable,
	.disable = (void (*)(void))udi_hid_joystick_disable,
	.setup = (bool(*)(void))udi_hid_joystick_setup,
	.getsetting = (uint8_t(*)(void))udi_hid_joystick_getsetting,
	.sof_notify = NULL,
};
//@}


/**
 * \ingroup udi_hid_joystick_group
 * \defgroup udi_hid_joystick_group_internal Implementation of UDI HID Joystick
 *
 * Class internal implementation
 * @{
 */

/**
 * \name Internal defines and variables to manage HID mouse
 */
//@{

//! Size of report for standard HID mouse
// #define UDI_HID_JOYSTICK_REPORT_SIZE   6
//! To store current rate of HID mouse
static uint8_t udi_hid_joystick_rate;
//! To store current protocol of HID mouse
static uint8_t udi_hid_joystick_protocol;
//! To signal if a valid report is ready to send
static bool udi_hid_joystick_b_report_valid;
//! Report ready to send
static uint8_t udi_hid_joystick_report[UDI_HID_JOYSTICK_REPORT_SIZE];
//! Signal if a report transfer is on going
volatile static bool udi_hid_joystick_report_trans_ongoing;
//! Buffer used to send report
COMPILER_WORD_ALIGNED
		static uint8_t
		udi_hid_joystick_report_trans[UDI_HID_JOYSTICK_REPORT_SIZE];


/**
 * \brief Callback for set report setup request
 *
 * \return \c 1 always, because it is not used on joystick interface
 */
static bool udi_hid_joystick_setreport(void);

//@}



/**
 * \name Internal routines
 */
//@{


/**
 * \brief Send the report
 *
 * \return \c 1 if send on going, \c 0 if delay.
 */
// bool udi_hid_joystick_send_report(uint8_t*);

/**
 * \brief Callback called when the report is sent
 *
 * \param status     UDD_EP_TRANSFER_OK, if transfer finish
 * \param status     UDD_EP_TRANSFER_ABORT, if transfer aborted
 * \param nb_sent    number of data transfered
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
static void udi_hid_joystick_report_sent(udd_ep_status_t status,
		iram_size_t nb_sent, udd_ep_id_t ep);

//@}


//--------------------------------------------
//------ Interface for UDI HID level

bool udi_hid_joystick_enable(void)
{
	// Initialize internal value
	udi_hid_joystick_rate = 0;
	udi_hid_joystick_protocol = 0;
	udi_hid_joystick_report_trans_ongoing = false;
	memset(udi_hid_joystick_report, 0, UDI_HID_JOYSTICK_REPORT_SIZE);
	udi_hid_joystick_b_report_valid = false;
	return UDI_HID_JOYSTICK_ENABLE_EXT();
}


void udi_hid_joystick_disable(void)
{
	UDI_HID_JOYSTICK_DISABLE_EXT();
}


bool udi_hid_joystick_setup(void)
{
	return udi_hid_setup(&udi_hid_joystick_rate,
								&udi_hid_joystick_protocol,
								(uint8_t *) &udi_hid_joystick_report_desc,
								udi_hid_joystick_setreport);
}


uint8_t udi_hid_joystick_getsetting(void)
{
	return 0;
}


static bool udi_hid_joystick_setreport(void)
{
	return false;
}


// This will be called from an interrupt handler.
// Also, make sure you have exclusive access to the incoming_report
bool udi_hid_joystick_send_report(uint8_t* incoming_report)
{
	static uint8_t* last_report = NULL;
	if(incoming_report != NULL) {
		last_report =  incoming_report;
	}
	
	if (udi_hid_joystick_report_trans_ongoing || last_report == NULL) {
		return false;	// Transfer on going then send this one after transfer complete
	}
	

	bool rc = false;
	irqflags_t flags = cpu_irq_save();
	size_t report_size = UDI_HID_JOYSTICK_REPORT_SIZE;

	memcpy(udi_hid_joystick_report_trans, last_report, UDI_HID_JOYSTICK_REPORT_SIZE);
	udi_hid_joystick_b_report_valid = true;
	rc = udi_hid_joystick_report_trans_ongoing = udd_ep_run(UDI_HID_JOYSTICK_EP_IN,	false,	udi_hid_joystick_report_trans,	UDI_HID_JOYSTICK_REPORT_SIZE, udi_hid_joystick_report_sent);

	cpu_irq_restore(flags);
	
	return rc;
}

//--------------------------------------------
//------ Internal routines


static void udi_hid_joystick_report_sent(udd_ep_status_t status,
		iram_size_t nb_sent, udd_ep_id_t ep)
{
	UNUSED(ep);
	UNUSED(status);
	UNUSED(nb_sent);
	// Valid report sending
	udi_hid_joystick_report_trans_ongoing = false;
	// Our report trans is always valid, except at start up.
	if (udi_hid_joystick_b_report_valid) {
		// Send new valid report
		udi_hid_joystick_send_report(NULL);
	}
}

//@}
