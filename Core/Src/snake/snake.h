/*
 * snake.h
 *
 *  Created on: Apr 24, 2024
 *      Author: yanni
 */

#ifndef SRC_SNAKE_SNAKE_H_
#define SRC_SNAKE_SNAKE_H_


#include "main.h"
#include "stdlib.h"
#include "time.h"



uint8_t board[256] = {0};
/*
 * 0 = empty
 * 1 = fruit
 * 2 = head
 * 3 = tail to top
 * 4 = tail to right
 * 5 = tail to bottom
 * 6 = tail to left
 * */

uint8_t head_rot = 1;
/*
 * 0 UP
 * 1 RIGHT
 * 2 DOWN
 * 3 LEFT
 * */
uint8_t head_row = 7;
uint8_t head_col = 3;
uint8_t tail_end_pos = 7*16 + 2;
uint8_t score = 0;
int skip_tail_movement = 0;

uint8_t head_pos(){
	return head_row * 16 + head_col;
}


int generate_start_board(){
	/// place the snake head
	for (int entry = 0; entry < 256; entry++) board[entry] = 0 ;
	board[head_pos()] = 2;
	board[tail_end_pos] = 4;


	/// place the first fruit randomly on the other side
	board[(rand() % 16)/*random row*/ * 16 + (rand()%8)+8 /*random column on the right side of the board*/] = 1;
	return 1;
}

int render_board(){
	HAL_IWDG_Refresh(&hiwdg);
	BSP_LCD_Clear(LCD_COLOR_BLACK);
	for (uint8_t row = 0; row < 16; row++){
		HAL_IWDG_Refresh(&hiwdg);
		for (uint8_t col = 0; col < 16; col++){
			uint8_t cell = board[row*16+col];
				if ( cell == 0) continue;
				if ( cell == 1) {
					BSP_LCD_SetTextColor(LCD_COLOR_RED);
					BSP_LCD_FillCircle(col*15+7, row*15+7, 7);
				}
				else if ( cell == 2){
					BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGREEN);
					BSP_LCD_FillRect(col*15, row*15, 15, 15);
				}
				else{
					BSP_LCD_SetTextColor(LCD_COLOR_DARKGREEN);
					BSP_LCD_FillRect(col*15, row*15, 15, 15);
				}
			}
	}
	return 1;
}


int you_dieded_lol(){
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);

	BSP_LCD_DisplayStringAt(12, 12, (uint8_t*)"Hello World!", CENTER_MODE);
	char out_str[11];
	sprintf(out_str, "Score: %d", score);
	BSP_LCD_DisplayStringAt(12, 26, (uint8_t*)out_str, CENTER_MODE);
	while (1){}
	return 1;
}

int move_snake(){
	board[head_pos()] = head_rot +3;
	if (head_rot == 0 && head_row > 0) head_row -= 1;
	else if (head_rot == 1 && head_col < 16) head_col += 1;
	else if (head_rot == 2 && head_row < 16) head_row += 1;
	else if (head_rot == 3 && head_col > 0 ) head_col -= 1;
	else you_dieded_lol();


	int tail_pos_change = 0;
	switch (board[tail_end_pos]-3) {

	case 0:
		tail_pos_change = -16;
		break;
	case 1:
		tail_pos_change = 1;
		break;
	case 2:
		tail_pos_change = 16;
		break;
	default:
		tail_pos_change = -1;
		break;
	}
	if (skip_tail_movement)skip_tail_movement = 0;
	else{
		board[tail_end_pos] = 0;
		tail_end_pos += tail_pos_change;
	}

	switch(board[head_pos()]){

	case 0:
		break;
	case 1:
	{
		score++;
		skip_tail_movement = 1;
		uint8_t new_fruit_pos = rand()%256;
		while(board[new_fruit_pos] != 0) new_fruit_pos = rand()%256;
		board[new_fruit_pos] = 1;
		break;
	}
	default:
		you_dieded_lol();
		break;
	}
	board[head_pos()] = 2;

	return 1;
}

int move_snake_renderned(){
	BSP_LCD_SetTextColor(LCD_COLOR_DARKGREEN);
	BSP_LCD_FillRect(head_col*15, head_row*15, 15, 15);
	board[head_pos()] = head_rot +3;
		if (head_rot == 0 && head_row > 0) head_row -= 1;
		else if (head_rot == 1 && head_col < 16) head_col += 1;
		else if (head_rot == 2 && head_row < 16) head_row += 1;
		else if (head_rot == 3 && head_col > 0 ) head_col -= 1;
		else you_dieded_lol();


		int tail_pos_change = 0;
		switch (board[tail_end_pos]-3) {

		case 0:
			tail_pos_change = -16;
			break;
		case 1:
			tail_pos_change = 1;
			break;
		case 2:
			tail_pos_change = 16;
			break;
		default:
			tail_pos_change = -1;
			break;
		}
		if (skip_tail_movement)skip_tail_movement = 0;
		else{
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			uint8_t col = tail_end_pos % 16;
			BSP_LCD_FillRect(col*15,(tail_end_pos-col)/16*15, 15, 15);
			board[tail_end_pos] = 0;
			tail_end_pos += tail_pos_change;
		}

		switch(board[head_pos()]){

		case 0:
			break;
		case 1:
		{
			score++;
			skip_tail_movement = 1;
			uint8_t new_fruit_pos = rand()%256;
			while(board[new_fruit_pos] != 0) new_fruit_pos = rand()%256;
			board[new_fruit_pos] = 1;
			BSP_LCD_SetTextColor(LCD_COLOR_RED);
			uint8_t col = new_fruit_pos % 16;
			BSP_LCD_FillCircle(col*15+7, (new_fruit_pos-col)/16*15+7, 7);
			break;
		}
		default:
			you_dieded_lol();
			break;
		}
		board[head_pos()] = 2;

		BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGREEN);
		BSP_LCD_FillRect(head_col*15, head_row*15, 15, 15);


		return 1;

}

uint8_t get_controller_input(){
	if (BSP_JOY_GetState() == JOY_UP) return 0;
	if (BSP_JOY_GetState() == JOY_RIGHT) return 1;
	if (BSP_JOY_GetState() == JOY_DOWN) return 2;
	if (BSP_JOY_GetState() == JOY_LEFT) return 3;
	if (BSP_JOY_GetState() == JOY_SEL) return 4;
	return 5; // idle
}

int snake(){
	generate_start_board();
	uint8_t game_tick_time = 1000 - rand()%500;
	while(1){
		render_board();
		char out_str[4];
		sprintf(out_str, "%d", score);
		BSP_LCD_DisplayStringAt(0, 15, (uint8_t*)out_str, RIGHT_MODE);
		uint32_t start = HAL_GetTick();
 		uint8_t input = get_controller_input();
		while(HAL_GetTick() - start< game_tick_time){
			if (get_controller_input() != 5)
				input = get_controller_input();
		}
		if (input == 4){
			continue;
		}
		else if(input == 5)
			move_snake();
		else {
			head_rot = input;
			move_snake();
		}
	}
	return 1;
}

uint8_t pause_indicator = 0;

int snake2(){
	BSP_LED_On(LED_GREEN);
	HAL_IWDG_Refresh(&hiwdg);
	BSP_LCD_Init();
	generate_start_board();
	render_board();
		while(1){
			HAL_IWDG_Refresh(&hiwdg);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
			char out_str[5];
			sprintf(out_str, "%d", score);
			BSP_LCD_DisplayStringAt(0, 0, (uint8_t*)out_str, CENTER_MODE);


			uint32_t start = HAL_GetTick();
	 		uint8_t input = get_controller_input();
	 		HAL_IWDG_Refresh(&hiwdg);
			while(HAL_GetTick() - start< 700 - rand()%300){
				if (get_controller_input() != 5)
					input = get_controller_input();
			}
			HAL_IWDG_Refresh(&hiwdg);
			if (input == 4){
				if (pause_indicator++ >= 2){
					BSP_LCD_Clear(LCD_COLOR_BLACK);
					BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
					BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
					BSP_LCD_DisplayStringAt(0, 110, (uint8_t*)"Pause", CENTER_MODE);
					HAL_IWDG_Refresh(&hiwdg);
					while (input > 3) input = get_controller_input();
					render_board();
				} else
				continue;
			}else {
				pause_indicator = 0;
			}
			HAL_IWDG_Refresh(&hiwdg);
			if(input == 5)
				move_snake_renderned();
			else {
				head_rot = input;
				move_snake_renderned();
			}
		}
		return 1;
}



#endif /* SRC_SNAKE_SNAKE_H_ */
