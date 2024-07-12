
#ifndef __D6T_H
#define __D6T_H

#ifdef __cplusplus
extern "C" {
#endif


#include "render.h"
#include "communication.h"

typedef enum{
	ABS_MODE = 0,
	REF_MODE = 1,
};


static void d6t_reading_to_lcd(){
	/// set configuration
	BSP_LCD_Init();
	BSP_JOY_Init(JOY_MODE_GPIO);
	BSP_LCD_Clear(0xffff);

	// create buffer for temperature values (raw, processed)
	uint8_t buffer[TEMP_VALUE_COUNT*2 + 3];
	int temp[TEMP_VALUE_COUNT+4];
	int mode = 0;
	char* meta_data_line[54];
	while (1){
		 if (BSP_JOY_GetState() == JOY_RIGHT) mode = REF_MODE;
		 else if (BSP_JOY_GetState() == JOY_LEFT)mode = ABS_MODE;
		 read_sensor_data(buffer);
	     sensor_data_to_temperatures(buffer, temp);

	     if( mode == ABS_MODE){
				 sprintf(&meta_data_line,"Mode:ABS HIGH:%dC LOW:%dC REF:%dC",
						 temp[0],
						 temp[1],
						 (int)(ROOM_TEMP*10));
				 display_data_on_lcd(temp);
	     }else{
				 sprintf(&meta_data_line,"Mode:REF AVG:%iC HIGH:%iC LOW:%iC",
						 temp[2],
						 temp[0],
						 temp[1]);
				 display_data_on_lcd_rel_mode(temp);
	     }
	     BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	     BSP_LCD_ClearStringLine(0);
	     BSP_LCD_DisplayStringAtLine(0, (uint8_t*)(meta_data_line));


	}
}
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
