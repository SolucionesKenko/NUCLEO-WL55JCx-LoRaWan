/*
 * mcu_comm_encoder.h
 *
 *  Created on: Apr 9, 2024
 *      Author: snaiderbautista
 */

#ifndef SRC_MCU_COMM_ENCODER_H_
#define SRC_MCU_COMM_ENCODER_H_

#include <stdint.h>

//#include "gps.h"

typedef struct __attribute__((packed))
{
	uint32_t dummy1;
	uint32_t dummy2;
}mcu_comm_encoder_status_t;

typedef struct __attribute__((packed))
{
	uint32_t dummy1;
	uint32_t dummy2;
}mcu_comm_encoder_sensors_t;

typedef struct __attribute__((packed))
{
	uint8_t fix;
	uint8_t satellites;
	uint32_t time;
	uint8_t day;
	uint8_t month;
	uint8_t year;
	int32_t latitude;
	int32_t longitude;
	int32_t altitude;
}mcu_comm_encoder_position_t;

typedef struct __attribute__((packed))
{
	uint16_t origin_packet_type;
	uint32_t origin_token;
	uint16_t response_code;
}mcu_comm_encoder_reply_t;

typedef struct __attribute__((packed))
{
	uint32_t dummy1;
	uint32_t dummy2;
}mcu_comm_encoder_event_t;

void mcu_comm_encode_status_telemetry(uint8_t* pbuffer, uint16_t* size);
void mcu_comm_encode_sensors_telemetry(uint8_t* pbuffer, uint16_t* size);
//void mcu_comm_encode_position_telemetry(uint8_t* pbuffer,uint16_t* size, gps_t* gps);
void mcu_comm_encode_reply(uint8_t* pbuffer, uint16_t* size, uint16_t origin_type, uint32_t origin_token, uint16_t code);
void mcu_comm_encode_event(uint8_t* pbuffer, uint16_t* size);




#endif /* SRC_MCU_COMM_ENCODER_H_ */
