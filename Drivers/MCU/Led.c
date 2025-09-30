#include "stm32f1xx_hal.h"
#include "Led.h"
#include "cmsis_os.h" 
void led_on(void)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
}

void led_off(void)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
}

void led_test(void)
{
    led_on();
    osDelay(1000);
    led_off();
    osDelay(1000);
}
