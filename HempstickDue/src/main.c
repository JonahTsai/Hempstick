/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */

#include <FreeRTOS.h>
#include <asf.h>

#include "rtos_hw_pin_configuration.h"
#include "joystick/rtos_joystick.h"

/*
#include "rtos_adc.h"
#include "mlx90363.h"
#include "tm_stick.h"
#include "rtos_button.h"
*/

static void setup_hardware(void);
static void ledTimerTask(void *parameters);

static volatile bool main_b_joystick_enable = false;


/*
 * FreeRTOS hook (or callback) functions that are defined in this file.
 */
void vApplicationMallocFailedHook(void);
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char *pcTaskName);
void vApplicationTickHook(void);





int main (void)
{
	xTimerHandle ledTimer = NULL;
	setup_hardware();
	
	
	ledTimer = xTimerCreate((const signed char* const) "LED Timer Task", (200 / portTICK_RATE_MS), pdTRUE, NULL, ledTimerTask);
	xTimerStart(ledTimer, 0);
	
	udc_start();
	
	vTaskStartScheduler();
	
}


static void setup_hardware(void)
{
	/* ASF function to setup clocking. */
	sysclk_init();

	/* Ensure all priority bits are assigned as preemption priority bits. */
	NVIC_SetPriorityGrouping(0);

	/* Atmel library function to setup for the evaluation kit being used. */
	board_init();
	
	configure_pins();
	
	rtos_joystick_init(true);
	/*
	rtos_button_init(1);
	
	
	tm_stick_init(1000000);
	
	mlx90363_init(2); // 500Hz so we not only conforms to MLX90363's timing, we get as much data rate as we can push it.
	
	// configure_time_trigger_for_adc(2000);
	uint8_t adc_channel_flags[MAX_ADC_CHANNEL] = {ADC_CHANNEL_ENABLE_MASK, ADC_CHANNEL_ENABLE_MASK, ADC_CHANNEL_ENABLE_MASK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	init_adc_data(ADC_PDC_ENABLE_MASK, adc_channel_flags);
	start_adc(2000);
	*/

	/* Perform any initialization required by the partest LED IO functions. */
	// vParTestInitialise();
}



static void ledTimerTask(void *parameters) {
	/* Toggle an LED to show the system is executing. */
	taskENTER_CRITICAL();
	{
		gpio_toggle_pin(LED0_GPIO);
	}
	taskEXIT_CRITICAL();
}


void vApplicationMallocFailedHook(void)
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
	for (;;) {
	}
}

/*-----------------------------------------------------------*/

void vApplicationIdleHook(void)
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function (as this demo application does) then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. */
}

/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook(xTaskHandle pxTask,
		signed char *pcTaskName)
{
	(void) pcTaskName;
	(void) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for (;;) {
	}
}

/*-----------------------------------------------------------*/

void vApplicationTickHook(void)
{
	/* This function will be called by each tick interrupt if
	configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
	added here, but the tick hook is called from an interrupt context, so
	code must not attempt to block, and only the interrupt safe FreeRTOS API
	functions can be used (those that end in FromISR()). */
}



/*
void main_suspend_action(void)
{
	// ui_powerdown();
}

void main_resume_action(void)
{
	// ui_wakeup();
}
*/

void user_callback_sof_action(void) {
	if(!main_b_joystick_enable) {
		return;
	}
	
	joystick_send_report();
}

/*
void main_sof_action(void)
{
	if (!main_b_joystick_enable)
	return;
	// ui_process(udd_get_frame_number());
}

void main_remotewakeup_enable(void)
{
	// ui_wakeup_enable();
}

void main_remotewakeup_disable(void)
{
	// ui_wakeup_disable();
}
*/

bool user_callback_joystick_enable(void)
{
	main_b_joystick_enable = true;
	return true;
}

void user_callback_joystick_disable(void)
{
	main_b_joystick_enable = false;
}
