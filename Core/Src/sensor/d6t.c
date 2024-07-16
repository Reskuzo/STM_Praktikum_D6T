#include "dt6.h"


void d6t_reading_to_lcd(){
	/// set configuration
	BSP_LCD_Init();
	BSP_JOY_Init(JOY_MODE_GPIO);
	BSP_LCD_Clear(0xffff);

	// create buffer for temperature values (raw, processed)
	uint8_t buffer[TEMP_VALUE_COUNT*2 + 3];
	int temp[TEMP_VALUE_COUNT+4];
	int mode = 0;
	char meta_data_line[54];
	while (1){

		 // check for mode switch
		 if (BSP_JOY_GetState() == JOY_RIGHT) mode = REF_MODE;
		 else if (BSP_JOY_GetState() == JOY_LEFT)mode = ABS_MODE;

		  if (read_sensor_data(buffer)){
			  sensor_data_to_temperatures(buffer, temp);

			 if( mode == ABS_MODE){
				 BSP_LED_On(LED_ORANGE);
				 BSP_LED_Off(LED_BLUE);
					 sprintf(meta_data_line,"Mode:ABS HIGH:%dC LOW:%dC REF:%dC",
							 temp[0],
							 temp[1],
							 (int)(ROOM_TEMP*10));
					 display_data_on_lcd(temp);
			 }else{
				 BSP_LED_On(LED_BLUE);
				 BSP_LED_Off(LED_ORANGE);
					 sprintf(meta_data_line,"Mode:REF AVG:%iC HIGH:%iC LOW:%iC",
							 temp[2],
							 temp[0],
							 temp[1]);
					 display_data_on_lcd_rel_mode(temp);
			 }
			 BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			 BSP_LCD_ClearStringLine(0);
			 BSP_LCD_DisplayStringAtLine(0, (uint8_t*)(meta_data_line));

		  } else {
			 BSP_LCD_Clear(LCD_COLOR_WHITE);
			 BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			 BSP_LCD_ClearStringLine(0);
			 BSP_LCD_DisplayStringAtLine(2, (uint8_t*)("The Sensor is not connected,"));
			 BSP_LCD_DisplayStringAtLine(3, (uint8_t*)(" or not responding."));
			 BSP_LCD_DisplayStringAtLine(5, (uint8_t*)("Try connecting a D6T-32L-01A to"));
			 BSP_LCD_DisplayStringAtLine(6, (uint8_t*)("the I2C Port over there ->"));
			 BSP_LCD_DisplayStringAtLine(7, (uint8_t*)("If you already have one connected,"));
			 BSP_LCD_DisplayStringAtLine(8, (uint8_t*)("try disconnecting and reconnecting it"));
			 BSP_LCD_DisplayStringAtLine(9, (uint8_t*)("(it might be in a timeout state)"));
			 BSP_LCD_DisplayStringAtLine(12, (uint8_t*)("Pin Connection:"));
			 BSP_LCD_DisplayStringAtLine(13, (uint8_t*)("D6T: SCL(y) SDA(b) VCC(r) GND(g) "));
			 BSP_LCD_DisplayStringAtLine(14, (uint8_t*)("STM: SDL(b) SCL(y) VCC(r) GND(g) "));
			 BSP_LCD_DisplayStringAtLine(18, (uint8_t*)("y:ellow, b:lue, r:ed, g:ray(black) "));
		  }

	}
}
