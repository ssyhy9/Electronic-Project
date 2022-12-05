#ifndef RS485_H_
#define RS485_H_

#include "stm32l4xx_hal.h"
#include "string.h"
#include "stdio.h"
#include "main.h"

void encode_transmit_data(int input, uint8_t* output);
void RS485_Data_Transmit(int trans_spd, uint8_t trans_msg[1]);

#endif /* LCD_H_ */
