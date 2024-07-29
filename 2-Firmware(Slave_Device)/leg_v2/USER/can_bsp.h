#ifndef __CAN_BSP_H__
#define __CAN_BSP_H__
#include "main.h"

void can_bsp_init(void);
void can_filter_init(void);
uint8_t canx_bsp_send_data(FDCAN_HandleTypeDef *hcan, uint16_t id, uint8_t *data, uint32_t len);
uint8_t fdcanx_receive(FDCAN_HandleTypeDef *hfdcan, uint8_t *buf);
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs);
void fdcan2_rx_callback(void);
void fdcan1_rx_callback(void);
#endif
