#include "frame_function.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define CRC8_POLYNOMIAL 0x07 // CRC-8 polynomial: x^8 + x^2 + x + 1
#define FRAME_SEND_LENGTH 107 // Fixed frame length for sending
#define DATA_SEND_LENGTH 104  // Fixed data length for sending
#define FRAME_RECE_LENGTH 43  // Fixed frame length for receiving
#define DATA_RECE_LENGTH 40   // Fixed data length for receiving
float pos[10];
float vel[10];
extern float torq[];
extern float kp[];
extern float kd[];
extern float gyro[], accel[], temp;

/**
************************************************************************
* @brief:       crc8_calc: Compute 8-bit CRC checksum
* @param[in]:   data: Pointer to the data
* @param[in]:   length: Length of the data
* @retval:      Calculated CRC value
* @details:     Uses the CRC-8 algorithm to compute the checksum
************************************************************************
**/
uint8_t crc8_calc(const uint8_t *data, size_t length) {
    uint8_t crc = 0xFF;
    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ CRC8_POLYNOMIAL;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

/**
************************************************************************
* @brief:       frame_function_upload: Upload data function
* @param[in]:   huart: Pointer to the UART handle structure
* @retval:      void
* @details:     Sends data over UART
************************************************************************
**/
void frame_function_upload(UART_HandleTypeDef* huart) {
    uint8_t data_send[FRAME_SEND_LENGTH]; // Frame: 1 header + 104 data bytes + 1 CRC + 1 footer
    uint8_t *pbuf;
    uint8_t *vbuf;
    uint8_t *gyrobuf;
    uint8_t *eulerbuf;
    float euler[3];
    
    // Calculate Euler angles from gyro data
    euler[0] = 3 * gyro[0];
    euler[1] = 3 * gyro[1];
    euler[2] = 3 * gyro[2];

    // Fill data
    // Frame header
    data_send[0] = 0xFF;

    // POS[1:10] in float
    for (int i = 0; i < 10; i++) {
        pbuf = (uint8_t*)&pos[i];
        data_send[1 + 4 * i] = *pbuf;
        data_send[2 + 4 * i] = *(pbuf + 1);
        data_send[3 + 4 * i] = *(pbuf + 2);
        data_send[4 + 4 * i] = *(pbuf + 3);
    }

    // VEL[11:20] in float
    for (int i = 0; i < 10; i++) {
        vbuf = (uint8_t*)&vel[i];
        data_send[41 + 4 * i] = *vbuf;
        data_send[42 + 4 * i] = *(vbuf + 1);
        data_send[43 + 4 * i] = *(vbuf + 2);
        data_send[44 + 4 * i] = *(vbuf + 3);
    }

    // Angular velocity
    for (int i = 0; i < 3; i++) {
        gyrobuf = (uint8_t*)&gyro[i];
        data_send[81 + 4 * i] = *gyrobuf;
        data_send[82 + 4 * i] = *(gyrobuf + 1);
        data_send[83 + 4 * i] = *(gyrobuf + 2);
        data_send[84 + 4 * i] = *(gyrobuf + 3);
    }

    // Euler angles
    for (int i = 0; i < 3; i++) {
        eulerbuf = (uint8_t*)&euler[i];
        data_send[93 + 4 * i] = *eulerbuf;
        data_send[94 + 4 * i] = *(eulerbuf + 1);
        data_send[95 + 4 * i] = *(eulerbuf + 2);
        data_send[96 + 4 * i] = *(eulerbuf + 3);
    }

    // Calculate CRC-8 checksum and add to the second to last byte
    data_send[105] = crc8_calc(data_send + 1, DATA_SEND_LENGTH);
    
    // Frame footer
    data_send[106] = 0xFF;

    // Transmit data over UART
    HAL_UART_Transmit(huart, data_send, sizeof(data_send), HAL_MAX_DELAY);
}
    uint8_t data_receive[FRAME_RECE_LENGTH];
/**
************************************************************************
* @brief:       frame_function_download: Download data function
* @param[in]:   huart: Pointer to the UART handle structure
* @retval:      void
* @details:     Receives data over UART and processes it
************************************************************************
**/
void frame_function_download(UART_HandleTypeDef* huart) {

    uint8_t received_crc;
    
    // Receive data over UART
    HAL_UART_Receive_IT(huart, data_receive, sizeof(data_receive));
    
    // Verify frame header and footer
    if (data_receive[0] != 0xFF || data_receive[FRAME_RECE_LENGTH - 1] != 0xFF) {
//        printf("Frame error: Invalid header or footer\n");
//        return 0;
    }
    
    // Extract received CRC
    received_crc = data_receive[FRAME_RECE_LENGTH - 2];
    
    // Calculate expected CRC
    uint8_t expected_crc = crc8_calc(data_receive + 1, DATA_RECE_LENGTH);
    
    // Verify CRC
    if (received_crc != expected_crc) {
//        printf("Frame error: CRC mismatch\n");
//        return 0;
    }
    
    // Extract the 40 data bytes and assign to extern float pos[]
    for (int i = 1; i < 10; i++) {
        pos[i] = *(float*)&data_receive[4 * i - 4];
    }

//    printf("Data received and processed successfully\n");
}
