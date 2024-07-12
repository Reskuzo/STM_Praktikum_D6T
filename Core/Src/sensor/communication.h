/*
 * communication.h
 *
 *  Created on: Jul 8, 2024
 *      Author: yannick
 */

#ifndef SRC_SENSOR_COMMUNICATION_H_
#define SRC_SENSOR_COMMUNICATION_H_

/// generic
#include "main.h"
#define NO_CONNECTION 0
#define SUCCESS 1


/// The D6T-32L-01A (that i was given measures in a 32x32 = 1024 pattern
#define TEMP_VALUE_COUNT 1024
#define ADDRESS (uint8_t)0x14
#define CONNECTION_TRYS 5


int is_sensor_connected();

int read_sensor_data(uint8_t* readbuffer);

int sensor_data_to_temperatures(uint8_t* sensor_data, int* temperatures);

#endif /* SRC_SENSOR_COMMUNICATION_H_ */
