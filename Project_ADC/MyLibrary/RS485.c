#include "RS485.h"

extern UART_HandleTypeDef huart1;

//int 	trans_spd;
//uint8_t trans_msg[1];

void RS485_Data_Transmit(int trans_spd, uint8_t trans_msg[1])
{
	encode_transmit_data(trans_spd,trans_msg);
	HAL_UART_Transmit(&huart1,trans_msg,1,1);
}

void encode_transmit_data(int input, uint8_t* output)
{
	if(input>=0 && input<10){
		*output = input;
	}
	else if(input>9 && input<100){
		*output = (input/10)<<4 | (input%10);
	}
}
