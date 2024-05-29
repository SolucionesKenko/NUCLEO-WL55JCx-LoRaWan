/*
 * lorawan_comm_bridge.c
 *
 *  Created on: May 22, 2024
 *      Author: Marco Ciau
 */

#include "lorawan_comm_bridge.h"
#include "mcu_comm_defs.h"
#include "sys_app.h"
// Helper function to split uint16_t into bytes
void splitUint16(uint16_t value, uint8_t* buffer) {
    buffer[0] = (value >> 8) & 0xFF;
    buffer[1] = value & 0xFF;
}

// Helper function to merge bytes into a uint16_t
uint16_t mergeUint16(uint8_t* buffer) {
   return (uint16_t)((buffer[0] << 8) | (buffer[1])) ;
}

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

// Helper function to merge bytes into a uint32_t
uint32_t mergeUint32(uint8_t* buffer) {
   return (uint32_t)((buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8)  | (buffer[3])) ;
}

uint16_t lorawan_comm_handleGetCommands(uint8_t * inputBuff, uint16_t inputBuffSize, uint8_t * outputBuff)
{

/*

+----------+----------+----------+----------+
| TYPE MSB | TYPE LSB | SIZE MSB | SIZE LSB |
+----------+----------+----------+----------+
+-----------+-----------+-----------+-----------+
| Token MSB | Token B3  | Token B2  | Token LSB |
+-----------+-----------+-----------+-----------+

*/
    if (inputBuffSize < 7) return 0;
    uint8_t * inputBuff_ptr = inputBuff;
    uint16_t packetType = mergeUint16(inputBuff_ptr);
    inputBuff_ptr += 2;
    uint16_t payloadSize = mergeUint16(inputBuff_ptr);
    inputBuff_ptr += 2;
    uint32_t incomingToken = mergeUint32(inputBuff_ptr);
    lorawan_comm_packet_commandResponse_header_t responseHeader;
    responseHeader.originPacketType = packetType;
    responseHeader.originToken = incomingToken;
    responseHeader.responseCode = 0x0001;
    uint16_t outputSize = 0;
    APP_LOG(TS_ON, VLEVEL_M, "inputBuff:\r\n");
    for (uint8_t i = 0; i < inputBuffSize; i++)
    {
        APP_LOG(TS_ON, VLEVEL_M, "%d\r\n", inputBuff[i]);
    }
    APP_LOG(TS_ON, VLEVEL_M, "Packet size: %d\r\n", payloadSize);
    APP_LOG(TS_ON, VLEVEL_M, "Packet type: %d\r\n", packetType);
    APP_LOG(TS_ON, VLEVEL_M, "IncomingToken: %d\r\n", incomingToken);
    switch (packetType)
    {
    case (uint16_t)MCU_COMM_TYPE_CMD_GET_VALVES:
        outputSize = lorawan_comm_buildCommandGetValvesResponsePacket(&responseHeader, 0xFFFE, outputBuff);
        APP_LOG(TS_ON, VLEVEL_M, "outputBuff:\r\n");
        for (uint8_t i = 0; i < outputSize; i++)
        {
            APP_LOG(TS_ON, VLEVEL_M, "%d\r\n", outputBuff[i]);
        }
        break;
        case (uint16_t)MCU_COMM_TYPE_CMD_GET_IRRIGATION:
        /* code */
        break;
        case (uint16_t)MCU_COMM_TYPE_CMD_GET_AREAS:
        /* code */
        break;
        case (uint16_t)MCU_COMM_TYPE_CMD_GET_IRRIGATION_TIME:
        /* code */
        break;
    default:
        responseHeader.responseCode = 0x0004;
        outputSize = 0;
        break;
    }
    return outputSize;
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


uint16_t lorawan_comm_buildCommandResponseHeader(lorawan_comm_packet_commandResponse_header_t* headerData, uint8_t * outputBuff)
{
    outputBuff[0] = (headerData->originPacketType >> 8) & 0xFF; // ORIGIN_PACKET_TYPE MSB
	outputBuff[1] = headerData->originPacketType & 0xFF; // ORIGIN_PACKET_TYPE LSB
    outputBuff[2] = (headerData->originToken >> 24) & 0xFF;  // ORIGIN_TOKEN MSB
    outputBuff[3] = (headerData->originToken >> 16) & 0xFF; // ORIGIN_TOKEN B3
    outputBuff[4] = (headerData->originToken >> 8) & 0xFF;// ORIGIN_TOKEN B2
    outputBuff[5] = headerData->originToken & 0xFF;// ORIGIN_TOKEN LSB
    outputBuff[6] = (headerData->responseCode >> 8) & 0xFF; // RESPONSE_CODE MSB
	outputBuff[7] = headerData->responseCode & 0xFF; // RESPONSE_CODE LSB
    return 8;
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

uint16_t lorawan_comm_buildCommandGetValvesResponsePacket(lorawan_comm_packet_commandResponse_header_t* headerData, uint16_t valvesState, uint8_t* outputBuff)
{
    lorawan_comm_packet_main_header_t mainHeader;
	mainHeader.type = (uint16_t)MCU_COMM_TYPE_CMD_REPLY;
	mainHeader.size = 2;
	// Start filling the buffer with main header
    uint8_t* payloadPtr = outputBuff;
	lorawan_comm_buildCommonHeader(&mainHeader, payloadPtr);
    payloadPtr += MAIN_HEADER_SIZE;
    // Then, append command response header
    lorawan_comm_buildCommandResponseHeader(headerData, payloadPtr);
    payloadPtr += COMMAND_RESPONSE_HEADER_SIZE;
    //Append payload
    splitUint16(valvesState, payloadPtr);
    return (MAIN_HEADER_SIZE + COMMAND_RESPONSE_HEADER_SIZE + mainHeader.size);
}
