#ifndef FRAME_FUNCTION_H
#define FRAME_FUNCTION_H

#include "usart.h"

void frame_function_upload(UART_HandleTypeDef *huart);
void frame_function_download(UART_HandleTypeDef* huart);

#endif // FRAME_FUNCTION_H
