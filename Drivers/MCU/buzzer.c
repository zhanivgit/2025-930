#include "gpio.h"
#include "cmsis_os.h" 
void buzzer_on(void)
{
     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
}
void buzzer_off(void)
{
     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);

}
void buzzer_test(void)
{
    buzzer_on();
    osDelay(200);
    buzzer_off();
    osDelay(200);

}
