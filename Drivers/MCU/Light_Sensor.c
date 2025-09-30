#include "gpio.h"
uint8_t Light_Sensor_dectect(void)
{
	return HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11);
	
}
