/**
 * \file
 *
 * \brief SAM4S Xplained Pro board initialization
 *
 * Copyright (C) 2012-2013 Atmel Corporation. All rights reserved.
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
 */

#include <board.h>
#include <gpio.h>
#include <ioport.h>
#include <wdt.h>

/**
 * \addtogroup sam4s_xplained_pro_group
 * @{
 */

void board_init(void)
{
#ifndef CONF_BOARD_KEEP_WATCHDOG_AT_INIT
	wdt_disable(WDT);
#endif

	/* GPIO has been deprecated, the old code just keeps it for compatibility.
	 * In new designs IOPORT is used instead.
	 * Here IOPORT must be initialized for others to use before setting up IO.
	 */
	ioport_init();

	/* Initialize LED0, turned off */
	ioport_set_pin_level(LED_0_PIN, !LED_0_ACTIVE);
	ioport_set_pin_dir(LED_0_PIN, IOPORT_DIR_OUTPUT);

	/* Initialize SW0 */
	ioport_set_pin_dir(BUTTON_0_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(BUTTON_0_PIN, (BUTTON_0_ACTIVE ?
				IOPORT_MODE_PULLDOWN : IOPORT_MODE_PULLUP));

	/* Initialize EXT3 LED0, LED1 & LED2, turned off */
	ioport_set_pin_level(IO1_LED1_PIN, !IO1_LED1_ACTIVE);
	ioport_set_pin_dir(IO1_LED1_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(IO1_LED2_PIN, !IO1_LED2_ACTIVE);
	ioport_set_pin_dir(IO1_LED2_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(IO1_LED3_PIN, !IO1_LED3_ACTIVE);
	ioport_set_pin_dir(IO1_LED3_PIN, IOPORT_DIR_OUTPUT);

#ifdef CONF_BOARD_TWI0
	gpio_configure_pin(TWI0_DATA_GPIO, TWI0_DATA_FLAGS);
	gpio_configure_pin(TWI0_CLK_GPIO, TWI0_CLK_FLAGS);
#endif

	/* Configure SPI pins */
#ifdef CONF_BOARD_SPI
	gpio_configure_pin(SPI_MISO_GPIO, SPI_MISO_FLAGS);
	gpio_configure_pin(SPI_MOSI_GPIO, SPI_MOSI_FLAGS);
	gpio_configure_pin(SPI_SPCK_GPIO, SPI_SPCK_FLAGS);

	/**
	 * For NPCS 1, 2, and 3, different PINs can be used to access the same NPCS line.
	 * Depending on the application requirements, the default PIN may not be available.
	 * Hence a different PIN should be selected using the CONF_BOARD_SPI_NPCS_GPIO and
	 * CONF_BOARD_SPI_NPCS_FLAGS macros.
	 */
#ifdef CONF_BOARD_SPI_NPCS0
	gpio_configure_pin(SPI_NPCS0_GPIO, SPI_NPCS0_FLAGS);
#endif

#ifdef CONF_BOARD_SPI_NPCS1
#if defined(CONF_BOARD_SPI_NPCS1_GPIO) && defined(CONF_BOARD_SPI_NPCS1_FLAGS)
	gpio_configure_pin(CONF_BOARD_SPI_NPCS1_GPIO, CONF_BOARD_SPI_NPCS1_FLAGS);
#else
	gpio_configure_pin(SPI_NPCS1_PA9_GPIO, SPI_NPCS1_PA9_FLAGS);
#endif
#endif

#ifdef CONF_BOARD_SPI_NPCS2
#if defined(CONF_BOARD_SPI_NPCS2_GPIO) && defined(CONF_BOARD_SPI_NPCS2_FLAGS)
	gpio_configure_pin(CONF_BOARD_SPI_NPCS2_GPIO, CONF_BOARD_SPI_NPCS2_FLAGS);
#else
	gpio_configure_pin(SPI_NPCS2_PA10_GPIO, SPI_NPCS2_PA10_FLAGS);
#endif
#endif

#ifdef CONF_BOARD_SPI_NPCS3
#if defined(CONF_BOARD_SPI_NPCS3_GPIO) && defined(CONF_BOARD_SPI_NPCS3_FLAGS)
	gpio_configure_pin(CONF_BOARD_SPI_NPCS3_GPIO, CONF_BOARD_SPI_NPCS3_FLAGS);
#else
	gpio_configure_pin(SPI_NPCS3_PA22_GPIO, SPI_NPCS3_PA22_FLAGS);
#endif
#endif
#endif /* CONF_BOARD_SPI */

#ifdef CONF_BOARD_OLED_UG_2832HSWEG04
	gpio_configure_pin(UG_2832HSWEG04_DATA_CMD_GPIO, UG_2832HSWEG04_DATA_CMD_FLAGS);
	gpio_configure_pin(UG_2832HSWEG04_RESET_GPIO, UG_2832HSWEG04_RESET_FLAGS);
#endif

#ifdef CONF_BOARD_SD_MMC_SPI
	gpio_configure_pin(SD_MMC_0_CD_GPIO, SD_MMC_0_CD_FLAGS);
#endif

  if ( BUTTON_0_ACTIVE ) {
		ioport_set_pin_mode(BUTTON_0_PIN, IOPORT_MODE_PULLDOWN);
	}
  else {
		ioport_set_pin_mode(BUTTON_0_PIN, IOPORT_MODE_PULLUP);
  }
}

/** @} */
