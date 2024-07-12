/*
 * communication.c
 *
 *  Created on: Jul 8, 2024
 *      Author: yannick
 */


#include "communication.h"

/// returns 1 if a connection on ADDRESS is received, else 0
int is_sensor_connected(){
	for (int i = 0; i< CONNECTION_TRYS; i++){
	/// Command for telling the sensor we want to read data
	uint8_t cmd = 0x4c;

	HAL_StatusTypeDef status = HAL_I2C_Init(&hi2c2);
	HAL_Delay(10);
	status = HAL_I2C_Master_Transmit(&hi2c2, ADDRESS, &cmd, 1, 100);

	if (status == HAL_OK) return SUCCESS;
	}

	return NO_CONNECTION;
}

/**
 * reads the raw temperature readings from the sensor into the readbuffer
 * Returns 0 if no sensor could be detected (else 1)
 */
int read_sensor_data(uint8_t* readbuffer){
	 /// Each temperature reading consists of 2 8-Bit value (LOW-/HIGH-bit)
	 /// Additionally one PTAT reading and one Checksuum value is transmitted
	 int size = TEMP_VALUE_COUNT * 2 + 3;
	 /// Command for telling the sensor we want to read data
	 uint8_t cmd = 0x4c;

	 /// applying I2C settings to the external I2C port
	  HAL_StatusTypeDef status = HAL_I2C_Init(&hi2c2);
	  HAL_IWDG_Refresh(&hiwdg);


	  int fails = 0;
	  do {
		  /// send command for preparing transmission
		  status = HAL_I2C_Master_Transmit(&hi2c2, 0x14, &cmd, 1, 100);
		  HAL_Delay(10);

		  /// if the connection failed more than 10 times in a row, return connection lost
		  if (status != HAL_OK && fails++ > CONNECTION_TRYS) return NO_CONNECTION;

		  /// receive the data from Sensor at port 0x14
		  status = HAL_I2C_Master_Receive(&hi2c2, 0x14, readbuffer, size, HAL_MAX_DELAY);

		  /// if everything was successful, end the function else wait and try again
		  if (status == HAL_OK && !(readbuffer[5] == 0xff && readbuffer[6] == 0xff)) break;
		  BSP_LED_On(LED_RED);
		  HAL_Delay(550);
		  BSP_LED_Off(LED_RED);
	  } while(1);
	  return SUCCESS;
  };

/// converts the raw sensor readings into sensor data in 10*degrees celsius
int sensor_data_to_temperatures(uint8_t* sensor_data, int* temperatures){
	/// each reading consists of a high reading and a low reading,
	/// with high reading * 256 (max value 4 Bit) + low bits = temperature * 10
	   int sum = 0, highest=-10, lowest = 80;
	   for (int temp_index = 0; temp_index/2 < TEMP_VALUE_COUNT + 1; temp_index+=2){
		  int temp = sensor_data[temp_index+1] * 256 + sensor_data[temp_index];
	 	  temperatures[temp_index/2+3] = temp;
	 	  sum += temp;
	 	  if(temp > highest)
	 		  highest = temp;
	 	  else if (temp < lowest)
	 		  lowest = temp;
	   }
	   temperatures[2] = (int) (sum / TEMP_VALUE_COUNT);
	   temperatures[0] = highest;
	   temperatures[1] = lowest;
	   return SUCCESS;
};

