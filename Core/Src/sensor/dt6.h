
#ifndef __D6T_H
#define __D6T_H

#ifdef __cplusplus
extern "C" {
#endif


#include "render.h"
#include "communication.h"



static void d6t_reading_to_lcd(I2C_HandleTypeDef* hi2c2){
	/// set configuration
	BSP_LCD_Init();
	BSP_LCD_Clear(0xffff);

	// create buffer for temperature values (raw, processed)
	uint8_t buffer[TEMP_VALUE_COUNT*2 + 3];
	int temp[TEMP_VALUE_COUNT+1];

	while (1){
		 read_sensor_data(buffer, hi2c2);
	     sensor_data_to_temperatures(buffer, temp);
	     display_data_on_lcd(temp);
	}
}
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
