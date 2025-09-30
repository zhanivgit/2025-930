#include "cmsis_os.h" 
#include "gpio.h"
#include "stm32f1xx_hal.h"
uint8_t red_avoid_dectect(void)
{
    return HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
}
