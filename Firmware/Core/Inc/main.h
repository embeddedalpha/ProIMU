/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f412cx.h"
#include "stdbool.h"
#include "stdint.h"
#include "system_stm32f4xx.h"
#include "string.h"
#include "stdlib.h"
#include "stdarg.h"
#include <stdio.h>
#include "math.h"
#include "inttypes.h"
#include "Console.h"
#include "stm32f4xx.h"


int baud;
#define NONE 0
#define Success 1
#define Failure 2


#define bit_0  (1 << 0)
#define bit_1  (1 << 1)
#define bit_2  (1 << 2)
#define bit_3  (1 << 3)
#define bit_4  (1 << 4)
#define bit_5  (1 << 5)
#define bit_6  (1 << 6)
#define bit_7  (1 << 7)
#define bit_8  (1 << 8)
#define bit_9  (1 << 9)
#define bit_10 (1 << 10)
#define bit_11 (1 << 11)
#define bit_12 (1 << 12)
#define bit_13 (1 << 13)
#define bit_14 (1 << 14)
#define bit_15 (1 << 15)


uint32_t APB1CLK_SPEED;
uint32_t APB2CLK_SPEED;



__STATIC_INLINE int32_t SystemAPB1_Clock_Speed(void)
{
	return (SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1)>> RCC_CFGR_PPRE1_Pos]);
}

__STATIC_INLINE int32_t SystemAPB2_Clock_Speed(void)
{
	return (SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2)>> RCC_CFGR_PPRE2_Pos]);
}

__STATIC_INLINE void MCU_Clock_Setup(void)
{
	SystemInit();
	uint8_t pll_m = 25;
	uint8_t pll_n = 192; //192
	uint8_t pll_p = 0;
	uint8_t pll_q = 4;

//	uint8_t pll_m = 8;
//	uint8_t pll_n = 96; //192
//	uint8_t pll_p = 0;
//	uint8_t pll_q = 4;

	RCC->PLLCFGR = 0x00000000;

	RCC -> CR |= RCC_CR_HSEON;
	while(!(RCC -> CR & RCC_CR_HSERDY)){}
	RCC -> APB1ENR |= RCC_APB1ENR_PWREN;
	PWR ->CR |= PWR_CR_VOS;
	FLASH -> ACR |= FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_DCEN |
			FLASH_ACR_LATENCY_3WS;
	RCC->PLLCFGR |= (pll_q << 24) | (pll_p << 16) | (pll_n << 6) | (pll_m << 0);
	RCC ->PLLCFGR |= 1 << 22;
//    RCC->PLLCFGR = 0x4403019;
	RCC -> CFGR |= RCC_CFGR_HPRE_DIV1;
	RCC -> CFGR |= RCC_CFGR_PPRE1_DIV2;
	RCC -> CFGR |= RCC_CFGR_PPRE2_DIV1;
//	RCC -> APB2ENR |= 0x4000;
	RCC -> CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY)){}
//	RCC -> CR |= RCC_CR_PLLI2SON;
//	while(!(RCC->CR & RCC_CR_PLLI2SRDY)){}
	RCC -> CFGR |= RCC_CFGR_SW_PLL;
	while((RCC -> CFGR & RCC_CFGR_SWS_PLL) != RCC_CFGR_SWS_PLL);
SystemCoreClockUpdate();
//SysTick_Config(SystemCoreClock/1000);
//APB1CLK_SPEED = SystemAPB1_Clock_Speed();
//APB2CLK_SPEED = SystemAPB2_Clock_Speed();
RCC -> APB2ENR |= RCC_APB2ENR_SYSCFGEN;

}



__STATIC_INLINE int I2S_Clock_Init()
{
	int plli2s_m = 25; //25 25
	int plli2s_n = 344; //344 192
	int plli2s_r = 2; //2 5

//		int plli2s_m = 16; //25 25
//		int plli2s_n = 108; //344 192
//		int plli2s_r = 7; //2 5

	RCC -> PLLI2SCFGR = (plli2s_m << 0) | (plli2s_n << 6) | (plli2s_r << 28);
	RCC -> CR |= RCC_CR_PLLI2SON;
	while(!(RCC -> CR & RCC_CR_PLLI2SRDY));
	return (0UL);
}



__STATIC_INLINE uint32_t Delay_Config(void)
{

	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL = 5;
	return (0UL);                                                     /* Function successful */
}

__STATIC_INLINE uint32_t Delay_ns500(void)
{

	SysTick->LOAD = 96;
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
	return (0UL);                                                     /* Function successful */
}


__STATIC_INLINE uint32_t Delay_us(float us)
{

	SysTick->LOAD = (SystemCoreClock / 1000000) * us;
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
	return (0UL);                                                     /* Function successful */
}

__STATIC_INLINE uint32_t Delay_ms(unsigned long ms)
{
	unsigned long x = (0x17ed0) * (ms);
	SysTick->LOAD = x ;
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
	return (0UL);                                                     /* Function successful */
}


__STATIC_INLINE uint32_t Delay_s(unsigned long s)
{
	s = s * 1000;
	for (; s>0; s--)
	{
		Delay_ms(1);
	}
	return (0UL);
}





void Error_Handler(void);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
