#include "blinky.h"
#include "stm32f10x_conf.h"

ErrorStatus HSEStartUpStatus;

static GPIO_TypeDef* led_port[] = {
  [LED_GREEN] = LED_GPIO_PORT, 
  [LED_RED] = LED_GPIO_PORT,
};
static unsigned int led_pin[] = {
  [LED_GREEN] = LED_GPIO_GREEN, 
  [LED_RED]   = LED_GPIO_RED,
};
static int led_polarity[] = {
  [LED_GREEN] = LED_POL_GREEN, 
  [LED_RED] = LED_POL_RED,
};

// TEST TO SEE IF INTERRUPT IS WORKING
int i;

int main(){
  // Set system clock to external oscillator
  // SetSysClockToHSE();
  // i = 0;

	GPIO_InitTypeDef GPIO_InitStructure;

	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | LED_GPIO_PERIF, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | LED_GPIO_PERIF, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST , ENABLE);

	GPIO_InitStructure.GPIO_Pin = LED_GPIO_GREEN | LED_GPIO_RED;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;


	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// ledSet(LED_GREEN, 1);
}

void ledSet(led_t led, bool value) {
  if (led>LED_NUM)
    return;

  // if (led_polarity[led]==LED_POL_NEG)
  //   value = !value;
  
  if(value)
    GPIO_SetBits(led_port[led], led_pin[led]);
  else
    GPIO_ResetBits(led_port[led], led_pin[led]); 
}

// void SetSysClockToHSE(void){
//   RCC_DeInit();
  
//   RCC_HSEConfig(RCC_HSE_ON);

//   /* Wait till HSE is ready */
//   HSEStartUpStatus = RCC_WaitForHSEStartUp();

//   if (HSEStartUpStatus == SUCCESS)
//   {
//       /* HCLK = SYSCLK */
//     RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
//     /* PCLK2 = HCLK */
//     RCC_PCLK2Config(RCC_HCLK_Div1); 

//     /* PCLK1 = HCLK */
//     RCC_PCLK1Config(RCC_HCLK_Div1);

//     /* Select HSE as system clock source */
//     RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);

//     /* Wait till PLL is used as system clock source */
//     while (RCC_GetSYSCLKSource() != 0x04)
//     {
//     }
//   }
// }
void dummyFunction(void){
  i++;
}

void SysTick_Handler(void){
  dummyFunction();
}