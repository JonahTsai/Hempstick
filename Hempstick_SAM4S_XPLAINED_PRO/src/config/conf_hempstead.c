/*
 * conf_hempstead.c
 *
 * Created: 6/21/2013 10:07:41 PM
 *  Author: Jonah Tsai
 */ 
#include "conf_hempstead.h"
#include "rtos_hw_pin_configuration.h"
#include "rtos_button.h"
#include "rtos_adc.h"

#ifdef __cplusplus
extern "C" {
#endif

hw_pin_configuration_table g_hw_pin_conf_table = {
		.mutex = NULL,
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
			{.pin = PIO_PC26_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_B}, // TIOA5 (TC1, channel 2) for SSC RF triggering, must be hardwired to the RF pin. On the SAM4S Pro board, this is Ext 2: pin 9
			{.pin = PIO_PA20_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A}, // SSC RF, same as ADC 3 Since we use these three pins for SSC to read TM sticks, you may not use them for ADC. Do NOT configure these three pins in the ADC conversion (or you will get crap). On the SAM4S Pro board, this is Ext 2, pin 8. Connect Ext2:8 and Ext2:9 together and then connect to the Red wire of the Warthog stick (pin #3).
			{.pin = PIO_PA18_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A}, // SSC RD, same as ADC 1. On the SAM4S, this is Ext1:4. On the TM stick, this is the Orange wire, pin 4.
			{.pin = PIO_PA19_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = PIO_PERIPH_A},  // SSC RK, same as ADC 2. On the SAM4S, this is Ext1:8. On the TM stick, this is the Red wire, pin 3.

			
			// {.pin = PIO_PB26_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE)}, // Hard button on PIO pin. SAM Cortex M series of MCUs have the default to be input on reset. We want the debounce on, so we need to list it here, aside from being explicit.
			{.pin = PIO_PA24_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE)},
			{.pin = PIO_PA25_IDX, .conf = HW_PIN_ENABLE_MASK, .mode = (PIO_TYPE_PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE)}
		},
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
	.ports[0].button_conf[14].flags =  0x0000,
	.ports[0].button_conf[15].flags =  0x0000,
	.ports[0].button_conf[16].flags =  0x0000,
	.ports[0].button_conf[17].flags =  0x0000,
	.ports[0].button_conf[18].flags =  0x0000,
	.ports[0].button_conf[19].flags =  0x0000,
	.ports[0].button_conf[20].flags =  0x0000,
	.ports[0].button_conf[21].flags =  0x0000,
	.ports[0].button_conf[22].flags =  0x0000,
	.ports[0].button_conf[23].flags =  0x0000,
	.ports[0].button_conf[24].flags =  RTOS_BUTTON_PIN_ENABLED_MASK, .ports[0].button_conf[24].data_position = 30,
	.ports[0].button_conf[25].flags =  RTOS_BUTTON_PIN_ENABLED_MASK, .ports[0].button_conf[25].data_position = 31,
	/*
	.ports[0].button_conf[24].flags =  0x0000,
	.ports[0].button_conf[25].flags =  0x0000,
	*/
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
	.ports[1].button_conf[26].flags =  0x0000,
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
	.ports[3].button_conf[0].flags =  0x0000,
	.ports[3].button_conf[1].flags =  0x0000,
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
	.channel_flags = {ADC_CHANNEL_ENABLE_MASK, 0, 0, 0, ADC_CHANNEL_ENABLE_MASK, ADC_CHANNEL_ENABLE_MASK, 0, ADC_CHANNEL_ENABLE_MASK, ADC_CHANNEL_ENABLE_MASK, ADC_CHANNEL_ENABLE_MASK, 0, 0, 0, ADC_CHANNEL_ENABLE_MASK, ADC_CHANNEL_ENABLE_MASK, 0},
#elif defined(CONF_BOARD_ARDUINO_DUE)
	.channel_flags = {0, ADC_CHANNEL_ENABLE_MASK, ADC_CHANNEL_ENABLE_MASK, ADC_CHANNEL_ENABLE_MASK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
#endif
	.channel_mapping = {0, UINT8_MAX,  UINT8_MAX,  UINT8_MAX, 1, 2,  UINT8_MAX, 3, 4, 5,  UINT8_MAX,  UINT8_MAX,  UINT8_MAX, 6, 7,  UINT8_MAX},
	.num_channel_enabled = 0,
	.adc_config = 0,
	.mutex = NULL,
	.rtos_task_semaphore = NULL,
	.pdc_sample_data = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};


#ifdef __cplusplus
}
#endif