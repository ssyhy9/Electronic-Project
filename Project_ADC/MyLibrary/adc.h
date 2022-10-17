#ifndef __ADC_H
#define __ADC_H

#include "stm32l4xx_hal.h"

extern ADC_HandleTypeDef hadc1;

uint16_t Get_Adc();

#endif /* __ADC_H */
