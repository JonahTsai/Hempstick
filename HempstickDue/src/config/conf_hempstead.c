/*
 * conf_hempstead.c
 *
 * Created: 6/21/2013 10:07:41 PM
 *  Author: Jonah Tsai
 */ 

#include "rtos_hw_pin_configuration.h"
#include "rtos_button.h"
#include "rtos_adc.h"

#ifdef __cplusplus
extern "C" {
#endif

hw_pin_configuration_table g_hw_pin_conf_table = {
		.mutex = NULL,
#ifdef CONF_BOARD_SAM4S_XPLAIN_PRO
		.pin = {
			{.pin = PIO_PC23_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT)}, // Amber LED0 on SAM4S XPLAIN Pro board
			{.pin = PIO_PA0_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_B}, // TIOA0 (TC0, channel 0) for ADC triggering, this does not have to be configured, only if you also use it to trigger other stuff, like TM stick, like we hardwire this pin to the SSC RF pin so TIOA0 triggers both ADC conversion and SSC receiver.
			
			
			// SPI
			{.pin = PIO_PA12_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A}, // MISO
			{.pin = PIO_PA13_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A}, // MOSI
			{.pin = PIO_PA14_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A}, // SCLK
			{.pin = PIO_PA11_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A}, // NPCS0
			{.pin = PIO_PA9_IDX,  .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_B}, // NPCS1
			{.pin = PIO_PA10_IDX,  .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_B}, // NPCS2
			{.pin = PIO_PA22_IDX,  .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_B}, // NPCS3, PA5 is not routed out on SAM4S XPLAIN Pro.
		
			// SSC
			{.pin = PIO_PC26_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_B}, // TIOA5 (TC1, channel 2) for SSC RF triggering, must be hardwired to the RF ping
			{.pin = PIO_PA20_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A}, // SSC RF, same as ADC 3 Since we use these three pins for SSC to read TM sticks, you may not use them for ADC. Do NOT configure these three pins in the ADC conversion (or you will get crap).
			{.pin = PIO_PA18_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A}, // SSC RD, same as ADC 1
			{.pin = PIO_PA19_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A},  // SSC RK, same as ADC 2

			
			// {.pin = PIO_PB26_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE)}, // Hard button on PIO pin. SAM Cortex M series of MCUs have the default to be input on reset. We want the debounce on, so we need to list it here, aside from being explicit.
			
		},
#elif defined(CONF_BOARD_ARDUINO_DUE)
	.pin = {

		{.pin = 0, .conf = 0, .mode = 0}, // This is an example of disabled entry.
		// {.pin = PIO_PA12_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT)}, // Blue LED on SAM3X_ek Evaluation board.
		{.pin = PIO_PA12_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_PERIPH_B | PIO_DEFAULT)}, 
		{.pin = PIO_PB13_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT)}, // Green LED on SAM3X_ek Evaluation board.
		{.pin = PIO_PB12_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT)}, // Amber LED on SAM3X_ek Evaluation board.
		{.pin = PIO_PB25_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_B}, // TIOA Channel 0 for ADC triggering, this does not have to be configured, only if you also use it to trigger other stuff, like TM stick, like we hardwire this pin to the SSC RF pin so TIOA0 triggers both ADC conversion and SSC receiver. We are no loger using this to trigger SSC b/c we are doing oversampling of ADC, which might run way faster than SSC requires.
		{.pin = PIO_PA25_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A}, // MISO
		{.pin = PIO_PA26_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A}, // MOSI
		{.pin = PIO_PA27_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A}, // SCLK
		{.pin = PIO_PA28_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A}, // NPCS0
		{.pin = PIO_PC29_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_INPUT | PIO_DEFAULT)}, // On Arduino Due, PC29 and PA28 are hooked up together.
		
		// SSC for TM stick
		{.pin = PIO_PD7_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_PERIPH_B | PIO_DEFAULT)}, // TC2's channel 2 is used to trigger SSC's RF pin. Must be hardwired to the RF pin
		{.pin = PIO_PB17_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A}, // SSC RF, same as ADC 10. Since we use these three pins for SSC to read TM sticks, you may not use them for ADC. Do NOT configure these three pins in the ADC conversion (or you will get crap).
		{.pin = PIO_PB18_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A}, // SSC RD, same as ADC 11
		{.pin = PIO_PB19_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A},  // SSC RK, same as ADC 12
			
		{.pin = PIO_PB26_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE)}, // Arduino Due, Digital pin 22, hard button on PIO pin. SAM Cortex M series of MCUs have the default to be input on reset. We want the debounce on, so we need to list it here, aside from being explicit.
		{.pin = PIO_PA14_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE)}, // Arduino Due, Digital pin 23
		{.pin = PIO_PA15_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE)}, // Arduino Due, Digital pin 24
		{.pin = PIO_PD0_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE)}, // Arduino Due, Digital pin 25
		{.pin = PIO_PD1_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE)}, // Arduino Due, Digital pin 26
		
		{.pin = PIO_PB27_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)}, // On Arduino Due, this is the Amber LED
			
		{.pin = PIO_PB10_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A | PIO_DEFAULT}, // USB ID. The USB device pins, no need to explicitly define it, but we like to be explicit.
		{.pin = PIO_PB11_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A | PIO_DEFAULT} // USB VBOF. The USB device pins, no need to explicitly define it, but we like to be explicit.
			
		/* No need to configure these ADC pins, b/c on SAM3X these are extra function and the extra functions are all inputs, and GPIO configuration only affects the output line
		 " Note that multiplexing of peripheral lines A and B only affects the output line. The peripheral input lines are always connected to the pin input.", see, doc11057.pdf, pp. 645 of the SAM3X spec.
		{.pin = PIO_PA2_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 0
		{.pin = PIO_PA3_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 1
		{.pin = PIO_PA4_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 2
		{.pin = PIO_PA6_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 3
		{.pin = PIO_PA22_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 4
		{.pin = PIO_PA23_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 5
		{.pin = PIO_PA24_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 6
		{.pin = PIO_PA16_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 7
		{.pin = PIO_PB12_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 8
		{.pin = PIO_PB13_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 9
		{.pin = PIO_PB17_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 10
		{.pin = PIO_PB18_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 11
		{.pin = PIO_PB19_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 12
		{.pin = PIO_PB20_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 13
		{.pin = PIO_PB21_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 14
		{.pin = PIO_PA4_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 2
		{.pin = PIO_PA4_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 2
		{.pin = PIO_PA4_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 2
		{.pin = PIO_PA4_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 2
		{.pin = PIO_PA4_IDX, .conf = .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_PERIPH_B  | PIO_INPUT | PIO_DEFAULT)}, // ADC channel 2
		*/
	},
#endif

};



rtos_button_data_t g_rtos_button_data = {
	.data = NULL,
	.num_button = 0,
	.mutex = NULL,
	.rtos_internal_task_semaphore = NULL,
	.rtos_task_semaphore = NULL,
#ifdef ID_PIOA
	.ports[0].button_conf[0].flags =  0x0000,
	.ports[0].button_conf[1].flags =  0x0000,
	.ports[0].button_conf[2].flags =  0x0000,
	.ports[0].button_conf[3].flags =  0x0000,
	.ports[0].button_conf[4].flags =  0x0000,
	.ports[0].button_conf[5].flags =  0x0000,
	.ports[0].button_conf[6].flags =  0x0000,
	.ports[0].button_conf[7].flags =  0x0000,
	.ports[0].button_conf[8].flags =  0x0000,
	.ports[0].button_conf[9].flags =  0x0000,
	.ports[0].button_conf[10].flags =  0x0000,
	.ports[0].button_conf[11].flags =  0x0000,
	.ports[0].button_conf[12].flags =  0x0000,
	.ports[0].button_conf[13].flags =  0x0000,
	.ports[0].button_conf[14].flags =  RTOS_BUTTON_PIN_ENABLED_MASK, .ports[0].button_conf[14].data_position = 25,
	.ports[0].button_conf[15].flags =  RTOS_BUTTON_PIN_ENABLED_MASK, .ports[0].button_conf[15].data_position = 26,
	.ports[0].button_conf[16].flags =  0x0000,
	.ports[0].button_conf[17].flags =  0x0000,
	.ports[0].button_conf[18].flags =  0x0000,
	.ports[0].button_conf[19].flags =  0x0000,
	.ports[0].button_conf[20].flags =  0x0000,
	.ports[0].button_conf[21].flags =  0x0000,
	.ports[0].button_conf[22].flags =  0x0000,
	.ports[0].button_conf[23].flags =  0x0000,
	.ports[0].button_conf[24].flags =  0x0000,
	.ports[0].button_conf[25].flags =  0x0000,
	.ports[0].button_conf[26].flags =  0x0000,
	.ports[0].button_conf[27].flags =  0x0000,
	.ports[0].button_conf[28].flags =  0x0000,
	.ports[0].button_conf[29].flags =  0x0000,
	.ports[0].button_conf[30].flags =  0x0000,
	.ports[0].button_conf[31].flags =  0x0000,
#endif

#ifdef ID_PIOB
	.ports[1].button_conf[0].flags =  0x0000,
	.ports[1].button_conf[1].flags =  0x0000,
	.ports[1].button_conf[2].flags =  0x0000,
	.ports[1].button_conf[3].flags =  0x0000,
	.ports[1].button_conf[4].flags =  0x0000,
	.ports[1].button_conf[5].flags =  0x0000,
	.ports[1].button_conf[6].flags =  0x0000,
	.ports[1].button_conf[7].flags =  0x0000,
	.ports[1].button_conf[8].flags =  0x0000,
	.ports[1].button_conf[9].flags =  0x0000,
	.ports[1].button_conf[10].flags =  0x0000,
	.ports[1].button_conf[11].flags =  0x0000,
	.ports[1].button_conf[12].flags =  0x0000,
	.ports[1].button_conf[13].flags =  0x0000,
	.ports[1].button_conf[14].flags =  0x0000,
	.ports[1].button_conf[15].flags =  0x0000,
	.ports[1].button_conf[16].flags =  0x0000,
	.ports[1].button_conf[17].flags =  0x0000,
	.ports[1].button_conf[18].flags =  0x0000,
	.ports[1].button_conf[19].flags =  0x0000,
	.ports[1].button_conf[20].flags =  0x0000,
	.ports[1].button_conf[21].flags =  0x0000,
	.ports[1].button_conf[22].flags =  0x0000,
	.ports[1].button_conf[23].flags =  0x0000,
	.ports[1].button_conf[24].flags =  0x0000,
	.ports[1].button_conf[25].flags =  0x0000,
	.ports[1].button_conf[26].flags = RTOS_BUTTON_PIN_ENABLED_MASK, .ports[1].button_conf[26].data_position = 24,
	//.ports[1].button_conf[26].flags =  0x0000,
	.ports[1].button_conf[27].flags =  0x0000,
	.ports[1].button_conf[28].flags =  0x0000,
	.ports[1].button_conf[29].flags =  0x0000,
	.ports[1].button_conf[30].flags =  0x0000,
	.ports[1].button_conf[31].flags =  0x0000,
#endif

#ifdef ID_PIOC
	.ports[2].button_conf[0].flags =  0x0000,
	.ports[2].button_conf[1].flags =  0x0000,
	.ports[2].button_conf[2].flags =  0x0000,
	.ports[2].button_conf[3].flags =  0x0000,
	.ports[2].button_conf[4].flags =  0x0000,
	.ports[2].button_conf[5].flags =  0x0000,
	.ports[2].button_conf[6].flags =  0x0000,
	.ports[2].button_conf[7].flags =  0x0000,
	.ports[2].button_conf[8].flags =  0x0000,
	.ports[2].button_conf[9].flags =  0x0000,
	.ports[2].button_conf[10].flags =  0x0000,
	.ports[2].button_conf[11].flags =  0x0000,
	.ports[2].button_conf[12].flags =  0x0000,
	.ports[2].button_conf[13].flags =  0x0000,
	.ports[2].button_conf[14].flags =  0x0000,
	.ports[2].button_conf[15].flags =  0x0000,
	.ports[2].button_conf[16].flags =  0x0000,
	.ports[2].button_conf[17].flags =  0x0000,
	.ports[2].button_conf[18].flags =  0x0000,
	.ports[2].button_conf[19].flags =  0x0000,
	.ports[2].button_conf[20].flags =  0x0000,
	.ports[2].button_conf[21].flags =  0x0000,
	.ports[2].button_conf[22].flags =  0x0000,
	.ports[2].button_conf[23].flags =  0x0000,
	.ports[2].button_conf[24].flags =  0x0000,
	.ports[2].button_conf[25].flags =  0x0000,
	.ports[2].button_conf[26].flags =  0x0000,
	.ports[2].button_conf[27].flags =  0x0000,
	.ports[2].button_conf[28].flags =  0x0000,
	.ports[2].button_conf[29].flags =  0x0000,
	.ports[2].button_conf[30].flags =  0x0000,
	.ports[2].button_conf[31].flags =  0x0000,
#endif

#ifdef ID_PIOD
	.ports[3].button_conf[0].flags =  RTOS_BUTTON_PIN_ENABLED_MASK, .ports[3].button_conf[0].data_position = 27,
	.ports[3].button_conf[1].flags =  RTOS_BUTTON_PIN_ENABLED_MASK, .ports[3].button_conf[1].data_position = 28,
	.ports[3].button_conf[2].flags =  0x0000,
	.ports[3].button_conf[3].flags =  0x0000,
	.ports[3].button_conf[4].flags =  0x0000,
	.ports[3].button_conf[5].flags =  0x0000,
	.ports[3].button_conf[6].flags =  0x0000,
	.ports[3].button_conf[7].flags =  0x0000,
	.ports[3].button_conf[8].flags =  0x0000,
	.ports[3].button_conf[9].flags =  0x0000,
	.ports[3].button_conf[10].flags =  0x0000,
	.ports[3].button_conf[11].flags =  0x0000,
	.ports[3].button_conf[12].flags =  0x0000,
	.ports[3].button_conf[13].flags =  0x0000,
	.ports[3].button_conf[14].flags =  0x0000,
	.ports[3].button_conf[15].flags =  0x0000,
	.ports[3].button_conf[16].flags =  0x0000,
	.ports[3].button_conf[17].flags =  0x0000,
	.ports[3].button_conf[18].flags =  0x0000,
	.ports[3].button_conf[19].flags =  0x0000,
	.ports[3].button_conf[20].flags =  0x0000,
	.ports[3].button_conf[21].flags =  0x0000,
	.ports[3].button_conf[22].flags =  0x0000,
	.ports[3].button_conf[23].flags =  0x0000,
	.ports[3].button_conf[24].flags =  0x0000,
	.ports[3].button_conf[25].flags =  0x0000,
	.ports[3].button_conf[26].flags =  0x0000,
	.ports[3].button_conf[27].flags =  0x0000,
	.ports[3].button_conf[28].flags =  0x0000,
	.ports[3].button_conf[29].flags =  0x0000,
	.ports[3].button_conf[30].flags =  0x0000,
	.ports[3].button_conf[31].flags =  0x0000,
#endif

#ifdef ID_PIOE
	.ports[4].button_conf[0].flags =  0x0000,
	.ports[4].button_conf[1].flags =  0x0000,
	.ports[4].button_conf[2].flags =  0x0000,
	.ports[4].button_conf[3].flags =  0x0000,
	.ports[4].button_conf[4].flags =  0x0000,
	.ports[4].button_conf[5].flags =  0x0000,
	.ports[4].button_conf[6].flags =  0x0000,
	.ports[4].button_conf[7].flags =  0x0000,
	.ports[4].button_conf[8].flags =  0x0000,
	.ports[4].button_conf[9].flags =  0x0000,
	.ports[4].button_conf[10].flags =  0x0000,
	.ports[4].button_conf[11].flags =  0x0000,
	.ports[4].button_conf[12].flags =  0x0000,
	.ports[4].button_conf[13].flags =  0x0000,
	.ports[4].button_conf[14].flags =  0x0000,
	.ports[4].button_conf[15].flags =  0x0000,
	.ports[4].button_conf[16].flags =  0x0000,
	.ports[4].button_conf[17].flags =  0x0000,
	.ports[4].button_conf[18].flags =  0x0000,
	.ports[4].button_conf[19].flags =  0x0000,
	.ports[4].button_conf[20].flags =  0x0000,
	.ports[4].button_conf[21].flags =  0x0000,
	.ports[4].button_conf[22].flags =  0x0000,
	.ports[4].button_conf[23].flags =  0x0000,
	.ports[4].button_conf[24].flags =  0x0000,
	.ports[4].button_conf[25].flags =  0x0000,
	.ports[4].button_conf[26].flags =  0x0000,
	.ports[4].button_conf[27].flags =  0x0000,
	.ports[4].button_conf[28].flags =  0x0000,
	.ports[4].button_conf[29].flags =  0x0000,
	.ports[4].button_conf[30].flags =  0x0000,
	.ports[4].button_conf[31].flags =  0x0000,
#endif

#ifdef ID_PIOF
	.ports[5].button_conf[0].flags =  0x0000,
	.ports[5].button_conf[1].flags =  0x0000,
	.ports[5].button_conf[2].flags =  0x0000,
	.ports[5].button_conf[3].flags =  0x0000,
	.ports[5].button_conf[4].flags =  0x0000,
	.ports[5].button_conf[5].flags =  0x0000,
	.ports[5].button_conf[6].flags =  0x0000,
	.ports[5].button_conf[7].flags =  0x0000,
	.ports[5].button_conf[8].flags =  0x0000,
	.ports[5].button_conf[9].flags =  0x0000,
	.ports[5].button_conf[10].flags =  0x0000,
	.ports[5].button_conf[11].flags =  0x0000,
	.ports[5].button_conf[12].flags =  0x0000,
	.ports[5].button_conf[13].flags =  0x0000,
	.ports[5].button_conf[14].flags =  0x0000,
	.ports[5].button_conf[15].flags =  0x0000,
	.ports[5].button_conf[16].flags =  0x0000,
	.ports[5].button_conf[17].flags =  0x0000,
	.ports[5].button_conf[18].flags =  0x0000,
	.ports[5].button_conf[19].flags =  0x0000,
	.ports[5].button_conf[20].flags =  0x0000,
	.ports[5].button_conf[21].flags =  0x0000,
	.ports[5].button_conf[22].flags =  0x0000,
	.ports[5].button_conf[23].flags =  0x0000,
	.ports[5].button_conf[24].flags =  0x0000,
	.ports[5].button_conf[25].flags =  0x0000,
	.ports[5].button_conf[26].flags =  0x0000,
	.ports[5].button_conf[27].flags =  0x0000,
	.ports[5].button_conf[28].flags =  0x0000,
	.ports[5].button_conf[29].flags =  0x0000,
	.ports[5].button_conf[30].flags =  0x0000,
	.ports[5].button_conf[31].flags =  0x0000,
#endif
};


rtos_adc_data_type g_adc_data = {
	.data = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
#ifdef CONF_BOARD_SAM4S_XPLAIN_PRO
	.channel_flags = {0, 0, 0, 0, ADC_CHANNEL_ENABLE_MASK, ADC_CHANNEL_ENABLE_MASK, 0, 0, 0, ADC_CHANNEL_ENABLE_MASK, 0, 0, 0, 0, 0, 0},
#elif defined(CONF_BOARD_ARDUINO_DUE)
	.channel_flags = {0, ADC_CHANNEL_ENABLE_MASK, ADC_CHANNEL_ENABLE_MASK, ADC_CHANNEL_ENABLE_MASK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
#endif
	.num_channel_enabled = 0,
	.adc_config = 0,
	.mutex = NULL,
	.rtos_task_semaphore = NULL,
	.pdc_sample_data = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};


#ifdef __cplusplus
}
#endif