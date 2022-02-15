/*
 * Console.c
 *
 *  Created on: 25-Oct-2021
 *      Author: Kunal
 */

#include "Console.h"


  void Console_Init(USART_TypeDef *port,int32_t baudrate)
{

	if(port == USART1)
	{
		RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
		GPIO_Pin_Setup(GPIOA, 9, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, USART1_TX);
		GPIO_Pin_Setup(GPIOA, 10, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, USART1_RX);
		port ->CR1 |= USART_CR1_UE;
		port->BRR = (int)(SystemCoreClock / (16 * baudrate)) << 4;
		port ->CR1 |= USART_CR1_TE ;
		port ->CR1 |=  USART_CR1_RE  ;
	}
	else if(port == USART2)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
		GPIO_Pin_Setup(GPIOA, 2, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, USART2_TX);
		GPIO_Pin_Setup(GPIOA, 3, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, USART2_RX);
		port ->CR1 |= USART_CR1_UE;
//		port->BRR = (int)(SystemCoreClock / ((16 * baudrate)*2)) << 4;

		port -> BRR = 0x1388;
		port ->CR1 |= USART_CR1_TE ;
		port ->CR1 |=  USART_CR1_RE  ;
	}
	else if(port == USART6)
	{
		RCC -> APB2ENR |= RCC_APB2ENR_USART6EN;
		GPIO_Pin_Setup(GPIOA, 11, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, USART6_TX);
		GPIO_Pin_Setup(GPIOA, 12, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, USART6_RX);
		port ->CR1 |= USART_CR1_UE;
		port->BRR = (int)(SystemCoreClock / (16 * baudrate)) << 4;
		port ->CR1 |= USART_CR1_TE ;
		port ->CR1 |=  USART_CR1_RE  ;
	}




}

  void printConsole(USART_TypeDef *port,char *msg, ...)
{

char buff[100];
//	#ifdef DEBUG_UART

for(int i = 0; i < 100; i++)
{
	buff[i] = 0;
}
	va_list args;
	va_start(args, msg);
	vsprintf(buff, msg, args);

	for(int i = 0; i< strlen(buff); i++)
	{
		port -> DR = buff[i];
		while (!(port->SR & USART_SR_TXE));
	}

}


 static char get_character()
 {
	while (!(USART1->SR & USART_SR_RXNE));
	return USART1 -> DR;
 }



 int scanConsole(USART_TypeDef *port, char *msg, int len)
{
	 char *t = msg;
	 char c;
	 *t = '\0';
	 while((c = get_character()) != '\n')
	 {
		 *t = c;
//		 printConsole(port, c);
		 if((t-msg)<len)
		 {
			 t++;
		 }
		 *t = '\0';
	 }
	 return t - msg;
}

