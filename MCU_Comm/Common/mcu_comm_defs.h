/*
 * mcu_comm_defs.h
 *
 *  Created on: Apr 16, 2024
 *      Author: snaiderbautista
 */

#ifndef SRC_MCU_COMM_DEFS_H_
#define SRC_MCU_COMM_DEFS_H_

#define BIT0	0x01
#define BIT1	0x02
#define BIT2	0x04
#define BIT3	0x08
#define BIT4	0x10
#define BIT5	0x20
#define BIT6	0x40
#define BIT7	0x80

#define BIT8	0x0100
#define BIT9	0x0200
#define BIT10	0x0400
#define BIT11	0x0800
#define BIT12	0x1000
#define BIT13	0x2000
#define BIT14	0x4000
#define BIT15	0x8000

// Union for uint16_t
typedef union {
    uint16_t value; // Access the whole 16-bit unsigned integer
    uint8_t bytes[2]; // Access individual bytes
} Uint16_u;

// Union for int16_t
typedef union {
    int16_t value; // Access the whole 16-bit integer
    uint8_t bytes[2]; // Access individual bytes
} Int16_u;

// Union for uint32_t
typedef union {
    uint32_t value; // Access the whole 32-bit unsigned integer
    uint8_t bytes[4]; // Access individual bytes
} Uint32_u;

// Union for int32_t
typedef union {
    int32_t value; // Access the whole 32-bit integer
    uint8_t bytes[4]; // Access individual bytes
} Int32_u;


#define MCU_COMM_SYNC1 0xA5
#define MCU_COMM_SYNC2 0x5A

#define MCU_COMM_TX_BUFFER_SIZE 100
#define MCU_COMM_RX_BUFFER_SIZE 100


#define MCU_COMM_FLAGS_NEW_FRAME BIT0

#define MCU_COMM_TYPE_TELE_STATUS 0xA001
#define MCU_COMM_TYPE_TELE_SENSORS 0xA002
#define MCU_COMM_TYPE_TELE_POSITION 0xA003
#define MCU_COMM_TYPE_CMD_VERSION 0xB010
#define MCU_COMM_TYPE_CMD_GET_VALVES 0xB011
#define MCU_COMM_TYPE_CMD_SET_VALVES 0xB012
#define MCU_COMM_TYPE_CMD_SET_VALVE 0xB013
#define MCU_COMM_TYPE_CMD_GET_IRRIGATION 0xB014
#define MCU_COMM_TYPE_CMD_SET_IRRIGATION 0xB015
#define MCU_COMM_TYPE_CMD_GET_AREAS 0xB016
#define MCU_COMM_TYPE_CMD_SET_AREAS 0xB017
#define MCU_COMM_TYPE_CMD_SET_AREA 0xB018
#define MCU_COMM_TYPE_CMD_GET_IRRIGATION_TIME 0xB019
#define MCU_COMM_TYPE_CMD_SET_IRRIGATION_TIME 0xB020
#define MCU_COMM_TYPE_CMD_REPLY 0xB100
#define MCU_COMM_TYPE_EVENT 0xC020

#endif /* SRC_MCU_COMM_DEFS_H_ */
