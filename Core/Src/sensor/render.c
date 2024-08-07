/*
 * render.c
 *
 *  Created on: Jul 8, 2024
 *      Author: yannick
 */

#include "main.h"
#include "render.h"


// perform linear uint16_terpolation between two colors
// source stackoverflow (with own adjustments, so no GPL License  needed)
uint16_t pick_gradient_color(uint16_t color1, uint16_t color2, float temperature_gradient) {

	/// convert rgb uint16_to rgb565:
	/// as in rgb the always 2 digit are one color #rrggbb,
	// but here the second and third bit overlapp from r-g and g-b
	uint16_t r1 = (color1 >> 11) & 0x1F;
    uint16_t g1 = (color1 >> 5) & 0x3F;
    uint16_t b1 = color1 & 0x1F;

    uint16_t r2 = (color2 >> 11) & 0x1F;
    uint16_t g2 = (color2 >> 5) & 0x3F;
    uint16_t b2 = color2 & 0x1F;

    /// apply ratios between the two colors by using the temperature gradient
    uint16_t r = (uint16_t)(r1 + temperature_gradient * (r2 - r1));
    uint16_t g = (uint16_t)(g1 + temperature_gradient * (g2 - g1));
    uint16_t b = (uint16_t)(b1 + temperature_gradient * (b2 - b1));

    return ((r & 0x1F) << 11) | ((g & 0x3F) << 5) | (b & 0x1F);
}

/// convert the temperature values of the sensor [-10,70] to a color in the spectrum
///[-10,22]-> [blue, white],
///[ 22,36]-> [white, orange], (high change in color as its the mainly used area)
///[ 36,70]-> [orange, red]
uint16_t convert_temp_to_color_spec(float temp, float HIGH, float LOW, float ROOM, float HIGHLIGHT) {
	// the sensor can operate with temperatures in [-10, 70]

    if (temp <= LOW)
        return DARK_BLUE;

    if (temp >= HIGH)
    	return DARK_RED;

    if (temp < ROOM) {
    	// map temperature from ]-10, 22[ to [0, 1] for the blue to white gradient
    	float temp_gradient = (temp - LOW) / (ROOM-LOW);
    	return pick_gradient_color(DARK_BLUE, WHITE, temp_gradient);
    }

    if (temp < HIGHLIGHT) {
        	// map temperature from [-22, 36[ to [0, 1] for the blue to white gradient
        	float temp_gradient = (temp - ROOM) / (HIGHLIGHT-ROOM);
        	return pick_gradient_color(WHITE, ORANGE, temp_gradient);
        }


    // map temperature from [36, 70] to [0, 1] for the orange to red gradient
    float temp_gradient = (temp - HIGHLIGHT) / (HIGH-HIGHLIGHT);
    return pick_gradient_color(ORANGE, DARK_RED, temp_gradient);

}

uint16_t convert_temp_to_color(float temp){
	return convert_temp_to_color_spec(temp, 70.f, -10.f, ROOM_TEMP, BODY_TEMP);
}

/// display the temperature values as an image on the LCD screen
/// make sure to initiate BSP_lcd before calling
void display_data_on_lcd(int* temperatures){
	  /// get params of the screen
	  int width = BSP_LCD_GetXSize()+10; // +10 for rounding errors
	  int height = BSP_LCD_GetYSize() +10;

	  /// calculate Height / with of cells

	  int cell_width = width / H_CELL_COUNT;
	  int cell_hight = height/ V_CELL_COUNT;

	  /// iterate over rows/columns
	  for (int row = 0; row < V_CELL_COUNT; row++ )
		  for (int col = 0; col < H_CELL_COUNT; col++){
			  BSP_LCD_SetTextColor(
					  convert_temp_to_color(
							  /// +4 because of the PTAT temperature value at temperatures[3], and highest, lowest, avg temp at 0, 1, 2
							  (float)temperatures[row * 32 + col+4] / 10.f
										   )
							  );
			  BSP_LCD_FillRect(col * cell_width+10, row * cell_hight+10, cell_width, cell_hight);
			  // +20 = centering as the screen doesn't start by 0 and its better with a border on every side
		  }
}

void display_data_on_lcd_rel_mode(int* temperatures){
	/// get params of the screen
		  int width = BSP_LCD_GetXSize()+10; // +10 for rounding errors
		  int height = BSP_LCD_GetYSize() +10;

		  /// calculate Height / with of cells

		  int cell_width = width / H_CELL_COUNT;
		  int cell_hight = height/ V_CELL_COUNT;

		  /// iterate over rows/columns
		  for (int row = 0; row < V_CELL_COUNT; row++ )
			  for (int col = 0; col < H_CELL_COUNT; col++){
				  BSP_LCD_SetTextColor(
						  convert_temp_to_color_spec(
								  /// +4 because of the PTAT temperature value at temperatures[3], and highest, lowest, avg temp at 0, 1, 2
								  (float)temperatures[row * 32 + col+4] / 10.f,
								  (float) temperatures[0] / 10.f+5,
								  (float) temperatures[1] / 10.f-5,
								  (float) temperatures[2] / 10.f,
								  (float) temperatures[2] / 10.f+2.5
											   )
								  );
				  BSP_LCD_FillRect(col * cell_width+10, row * cell_hight+10, cell_width, cell_hight);
				  // +20 = centering as the screen doesn't start by 0 and its better with a border on every side
			  }
}


