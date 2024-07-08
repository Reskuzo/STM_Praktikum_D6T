/*
 * communication.c
 *
 *  Created on: Jul 8, 2024
 *      Author: yannick
 */
/// generic
#define NO_CONNECTION 0
#define SUCCESS 1


/// The D6T-32L-01A (that i was given measures in a 32x32 = 1024 pattern
#define TEMP_VALUE_COUNT 1024
#define ADDRESS 0x14
#define CONNECTION_TRYS 10


static int is_sensor_connected(){
	for (int i = 0; i< CONNECTION_TRYS; i++){

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
static int read_sensor_data(uint8_t* readbuffer, ){
	 /// Each temperature reading consists of 2 8-Bit value (LOW-/HIGH-bit)
	 /// Additionally one PTAT reading and one Checksuum value is transmitted
	 int size = TEMP_VALUE_COUNT * 2 + 3;

	 /// Command for telling the sensor we want to read data
	 uint8_t cmd = 0x4c;

	 /// applying I2C settings to the external I2C port
	  HAL_StatusTypeDef status = HAL_I2C_Init(&hi2c2);

	  int fails = 0;
	  do {
		  /// send command for preparing transmission
		  status = HAL_I2C_Master_Transmit(&hi2c2, ADDRESS, &cmd, 1, 100);
		  HAL_Delay(10);

		  /// if the connection failed more than 10 times in a row, return connection lost
		  if (status != HAL_OK && fails++ > CONNECTION_TRYS) return NO_CONNECTION;

		  /// receive the data from Sensor at port 0x14
		  status = HAL_I2C_Master_Receive(&hi2c2, ADDRESS, readbuffer, size, HAL_MAX_DELAY);

		  /// if everything was successful, end the function else wait and try again
		  if (status == HAL_OK && !(readbuffer[5] == 0xff && readbuffer[6] == 0xff)) break;
		  HAL_Delay(550);
	  } while(1);
	  return SUCCESS;
  };


