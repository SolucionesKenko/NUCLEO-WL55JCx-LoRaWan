/*
 * lorawan_comm_bridge.c
 *
 *  Created on: May 22, 2024
 *      Author: Marco Ciau
 */

#include "lorawan_comm_bridge.h"
#include "mcu_comm_defs.h"

// Helper function to split uint32_t into bytes
void splitUint32(uint32_t value, uint8_t* buffer) {
    buffer[0] = (value >> 24) & 0xFF;
    buffer[1] = (value >> 16) & 0xFF;
    buffer[2] = (value >> 8) & 0xFF;
    buffer[3] = value & 0xFF;
}

// Helper function to split float into bytes
void splitFloat(float value, uint8_t* buffer) {
    uint32_t temp = (uint32_t)(value * 10);
    splitUint32(temp, buffer);
}

uint16_t lorawan_comm_buildCommonHeader(lorawan_comm_packet_main_header_t* headerData, uint8_t * outputBuff)
{
	outputBuff[0] = (headerData->type >> 8) & 0xFF; // TYPE MSB
	outputBuff[1] = headerData->type & 0xFF; // TYPE LSB
	outputBuff[2] = (headerData->size >> 8) & 0xFF; // PAYLOAD_SIZE MSB
	outputBuff[3] = headerData->size & 0xFF; // PAYLOAD_SIZE LSB
	return 4;
}

uint16_t lorawan_comm_buildTelemetryHeader(lorawan_comm_packet_telemetry_header_t* headerData, uint8_t * outputBuff)
{
	outputBuff[0] = (headerData->sequence >> 8) & 0xFF; // SEQUENCE MSB
	outputBuff[1] = headerData->sequence & 0xFF; // SEQUENCE LSB
	return 2;
}

uint16_t lorawan_comm_buildTelemetrySensorsPacket(uint16_t sequence, telemetry_sensor_data_t payload, uint8_t* outputBuff)
{
	lorawan_comm_packet_main_header_t mainHeader;
	lorawan_comm_packet_telemetry_header_t telemetryHeader;
	mainHeader.type = (uint16_t)MCU_COMM_TYPE_TELE_SENSORS;
	mainHeader.size = sizeof(telemetry_sensor_data_t);
	telemetryHeader.sequence = sequence;
	// Fill buffer with headers
    uint8_t* payloadPtr = outputBuff;
	lorawan_comm_buildCommonHeader(&mainHeader, payloadPtr);
    payloadPtr += MAIN_HEADER_SIZE;
    lorawan_comm_buildTelemetryHeader(&telemetryHeader, outputBuff + MAIN_HEADER_SIZE);
    // Append telemetry sensor data to the buffer
    payloadPtr += TELEMETRY_HEADER_SIZE;
    splitUint32(payload.timestamp, payloadPtr);
    payloadPtr += 4;
    splitFloat(payload.temperature, payloadPtr);
    payloadPtr += 4;
    splitFloat(payload.flow, payloadPtr);
    payloadPtr += 4;
    splitFloat(payload.consumption, payloadPtr);
    payloadPtr += 4;
    splitFloat(payload.pressure, payloadPtr);
    payloadPtr += 4;
    splitFloat(payload.humidity, payloadPtr);
    payloadPtr += 4;
    splitFloat(payload.vBatLevel, payloadPtr);
    #ifdef ADD_GPS_TO_SENSORS
    payloadPtr += 1;
    splitUint32(payload.latitude, payloadPtr);
    payloadPtr += 4;
    splitUint32(payload.longitude, payloadPtr);
    payloadPtr += 4;
    splitUint32(payload.altitude, payloadPtr);
    #endif
	return (MAIN_HEADER_SIZE + TELEMETRY_HEADER_SIZE + mainHeader.size);
}

uint16_t lorawan_comm_buildTelemetryPositionPacket(uint16_t sequence, mcu_comm_encoder_position_t payload, uint8_t* outputBuff)
{
    lorawan_comm_packet_main_header_t mainHeader;
	lorawan_comm_packet_telemetry_header_t telemetryHeader;
	mainHeader.type = (uint16_t)MCU_COMM_TYPE_TELE_POSITION;
	mainHeader.size = sizeof(telemetry_sensor_data_t);
	telemetryHeader.sequence = sequence;
	// Fill buffer with headers
    uint8_t* payloadPtr = outputBuff;
	lorawan_comm_buildCommonHeader(&mainHeader, payloadPtr);
    payloadPtr += MAIN_HEADER_SIZE;
    lorawan_comm_buildTelemetryHeader(&telemetryHeader, outputBuff + MAIN_HEADER_SIZE);
    payloadPtr += TELEMETRY_HEADER_SIZE;
    // Append telemetry position data to the buffer
    payloadPtr[0] = payload.fix;
    payloadPtr[1] = payload.satellites;
    payloadPtr[2] = payload.day;
    payloadPtr[3] = payload.month;
    payloadPtr[4] = payload.year;
    payloadPtr += 5;
    splitUint32(payload.time, payloadPtr);
    payloadPtr += 4;
    splitUint32(payload.latitude, payloadPtr);
    payloadPtr += 4;
    splitUint32(payload.longitude, payloadPtr);
    payloadPtr += 4;
    splitUint32(payload.altitude, payloadPtr);
    return (MAIN_HEADER_SIZE + TELEMETRY_HEADER_SIZE + mainHeader.size);
}