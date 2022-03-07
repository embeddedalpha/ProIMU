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
	va_list args;
	va_start(args, msg);
	vsprintf(buff, msg, args);
	for(int i = 0; i< strlen(buff); i++)
	{
		port -> DR = buff[i];
		while (!(port->SR & USART_SR_TXE));
	}
}

  int scanConsole(char *msg,...)
{
	int c;
	char buff[10000];

	va_list args;
	va_start(args, msg);
	vscanf(buff,args);
	for(int i = 0; i<= strlen(buff); i++)
	{
//		c = UXR();
	}
	va_end(args);
	return c;
}

  char * Console_Return(char *s)
{
	int ch;
	char *p = s;

	while( (ch = USART1 -> DR) != '\n' && ch != EOF)
	{
		*s = (char)ch;
		s++;
	}
	*s = '\0';
	return p;
}
