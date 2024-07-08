/*
 * render.h
 *
 *  Created on: Jul 8, 2024
 *      Author: yannick
 */

#ifndef SRC_SENSOR_RENDER_H_
#define SRC_SENSOR_RENDER_H_

#define DARK_BLUE (uint16_t)0x001F
#define ORANGE 	  (uint16_t)0xFDA0
#define WHITE     (uint16_t)0xffff
#define DARK_RED  (uint16_t)0xF800
#define H_CELL_COUNT 32
#define V_CELL_COUNT 32

uint16_t pick_gradient_color(uint16_t color1, uint16_t color2, float temperature_gradient);

uint16_t convert_temp_to_color(float temp) ;

void display_data_on_lcd(int* temperatures);

#endif /* SRC_SENSOR_RENDER_H_ */
