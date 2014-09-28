#ifndef __BLINKY_H__
#define __BLINKY_H__

#include <stdio.h>
#include <stdbool.h>

#define LED_POL_POS 0
#define LED_POL_NEG 1

#define LED_GPIO_PERIF   RCC_APB2Periph_GPIOB
#define LED_GPIO_PORT    GPIOB
#define LED_GPIO_GREEN   GPIO_Pin_5
#define LED_POL_GREEN    LED_POL_NEG
#define LED_GPIO_RED     GPIO_Pin_4
#define LED_POL_RED      LED_POL_NEG

#define LED_NUM 2

typedef enum {LED_RED=0, LED_GREEN} led_t;

void ledSet(led_t led, bool value);
void SetSysClockToHSE(void);

#endif //__BLINKY_H__