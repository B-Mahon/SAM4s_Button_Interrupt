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
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to board_init()
 * -# Basic usage of on-board LED and button
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

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
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to board_init()
 * -# Basic usage of on-board LED and button
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include <led.h>


void pioHandler(uint32_t id, uint32_t index);
void Button_Setup(void);

void Button_Setup(void)
{
	//Disable watchdog timer
	wdt_disable(WDT);
	
	//Set PC23 (Yellow LED) as an output	
	pio_set_output(PIOC, PIO_PC23, PIO_TYPE_PIO_OUTPUT_0, PIO_DEFAULT, PIO_DEFAULT);

	//Enable PIOA clock
	pmc_enable_periph_clk(ID_PIOA); 
	
	//Enable PA2 (SW0) as an input
	pio_set_input(PIOA, PIO_PA2, PIO_PULLUP | PIO_DEBOUNCE);
	
	//Set debounce filter 
	pio_set_debounce_filter(PIOA, PIO_PA2, 25);
	
	//Configure interrupt handler
	pio_handler_set(PIOA, ID_PIOA, PIO_PA2,  PIO_IT_EDGE, pioHandler);
	
	//Enable interrupts on PA2 pin
	pio_enable_interrupt(PIOA, PIO_PA2);
	
	//Enable interrupt on MCU 
	NVIC_EnableIRQ(PIOA_IRQn);
	
}

void pioHandler(uint32_t id, uint32_t mask)
{
	if ((id == ID_PIOA) && (mask == PIO_PA2))
	{
		if(ioport_get_pin_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE)
		{
			ioport_toggle_pin_level(LED0);	
		}
		
	}
}


int main (void)
{
	board_init();
	Button_Setup();
	while(1){}
}
