/*
 * lorawan_comm_bridge.h
 *
 *  Created on: May 22, 2024
 *      Author: Marco Ciau
 */

#ifndef LORRAWANBRIDGE_LORAWAN_COMM_BRIDGE_H_
#define LORRAWANBRIDGE_LORAWAN_COMM_BRIDGE_H_
#include <stdint.h>
#include "mcu_comm_encoder.h"
#define MAIN_HEADER_SIZE 4
#define TELEMETRY_HEADER_SIZE 2
#define ADD_GPS_TO_SENSORS 1
typedef struct __attribute__((packed)) {
    uint32_t timestamp;
    float temperature;
    float flow;
    float consumption;
    float pressure;
    float humidity;
    uint8_t vBatLevel;
    #ifdef ADD_GPS_TO_SENSORS
    int32_t latitude;       
    int32_t longitude;     
    int16_t altitude;    
    #endif
} telemetry_sensor_data_t;

typedef struct
{
	uint16_t type;
	uint16_t size;
}lorawan_comm_packet_main_header_t;

typedef struct
{
	uint16_t sequence;
}lorawan_comm_packet_telemetry_header_t;

uint16_t lorawan_comm_buildCommonHeader(lorawan_comm_packet_main_header_t* headerData, uint8_t * outputBuff);
uint16_t lorawan_comm_buildTelemetryHeader(lorawan_comm_packet_telemetry_header_t* headerData, uint8_t * outputBuff);
uint16_t lorawan_comm_buildTelemetrySensorsPacket(uint16_t sequence, telemetry_sensor_data_t payload, uint8_t* outputBuff);
uint16_t lorawan_comm_buildTelemetryPositionPacket(uint16_t sequence, mcu_comm_encoder_position_t payload, uint8_t* outputBuff);

#endif /* LORRAWANBRIDGE_LORAWAN_COMM_BRIDGE_H_ */
