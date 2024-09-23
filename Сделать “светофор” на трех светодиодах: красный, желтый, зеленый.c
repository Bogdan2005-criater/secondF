/*
Сделать “светофор” на трех светодиодах: красный, желтый, зеленый
Светофор работает в строгой последовательности цветов сигналов
1.Зеленый сигнал — разрешает движение в данном направлении.
2.Зеленый мигающий сигнал 3 раза — разрешает движение и предупреждает, что будет смена сигнала.
3.Желтый сигнал — запрещает движение и предупреждает, что будет красный сигнал.
4.Красный сигнал — запрещает движение в данном направлении
*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stm32l0xx_hal.h>

#define LED_PORT                GPIOA
#define LED_PIN                 GPIO_PIN_0
#define YELLOW_PIN              GPIO_PIN_1
#define GREEN_PIN               GPIO_PIN_3
#define LED_PORT_CLK_ENABLE     __HAL_RCC_GPIOB_CLK_ENABLE
#define VCP_TX_Pin GPIO_PIN_2
#define VCP_RX_Pin GPIO_PIN_15


void initGPIO(int led)
{
  GPIO_InitTypeDef GPIO_Config;

  GPIO_Config.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Config.Pull = GPIO_NOPULL;
  GPIO_Config.Speed = GPIO_SPEED_FREQ_HIGH;

  
  GPIO_Config.Pin = led;

  LED_PORT_CLK_ENABLE();
  HAL_GPIO_Init(LED_PORT, &GPIO_Config);

  __HAL_RCC_GPIOB_CLK_ENABLE();
}

void SwitchLight(int led, int time)
{
  HAL_GPIO_WritePin(LED_PORT, led, GPIO_PIN_SET);
  HAL_Delay(time);
  HAL_GPIO_WritePin(LED_PORT, led, GPIO_PIN_RESET);
}

void ToggleLight(int led, int time)
{
  for (int i = 1; i < 3; i++)
  {
    HAL_Delay(time);
    HAL_GPIO_WritePin(LED_PORT, led, GPIO_PIN_SET);
    HAL_Delay(time);
    HAL_GPIO_WritePin(LED_PORT, led, GPIO_PIN_RESET);
  }
}

int main(void)
{
  HAL_Init();
  SystemClock_Config();

  initGPIO(LED_PIN);
  initGPIO(YELLOW_PIN);
  initGPIO(GREEN_PIN);

  while (1)
  {
    SwitchLight(LED_PIN, 1000);
    SwitchLight(YELLOW_PIN, 1000);
    SwitchLight(GREEN_PIN, 1000);
    ToggleLight(GREEN_PIN, 400);
    SwitchLight(YELLOW_PIN, 1000);
  };

  return 0;
}
