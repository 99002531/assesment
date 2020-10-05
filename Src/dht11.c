/*
 * dht11.c
 *
 *  Created on: Oct 5, 2020
 *      Author: Training
 */


#include "main.h"
#include <stdint.h>




void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void DHT11_Start (void)
{
	Set_Pin_Output (dht11_GPIO_Port, dht11_Pin);
	HAL_GPIO_WritePin (dht11_GPIO_Port, dht11_Pin, DISABLE);
	delay_microsecond(18000);
	HAL_GPIO_WritePin(dht11_GPIO_Port, dht11_Pin, ENABLE);
	delay_microsecond(20);
	Set_Pin_Input(dht11_GPIO_Port, dht11_Pin);
}

uint8_t DHT11_Check_Response (void)
{
	uint8_t Response = 0;
	delay_microsecond (40);
	if (!(HAL_GPIO_ReadPin (dht11_GPIO_Port, dht11_Pin)))
	{
		delay_microsecond (80);
		if ((HAL_GPIO_ReadPin (dht11_GPIO_Port, dht11_Pin)))
			Response = 1;
		else
			Response = -1;
	}
	while ((HAL_GPIO_ReadPin (dht11_GPIO_Port, dht11_Pin)));
	return Response;
}

uint8_t DHT11_Read (void)
{
	uint8_t i,j;
	for (j=0;j<8;j++)
	{
		while (!(HAL_GPIO_ReadPin (dht11_GPIO_Port, dht11_Pin)));
		delay_microsecond (40);
		if (!(HAL_GPIO_ReadPin (dht11_GPIO_Port, dht11_Pin)))
		{
			i&= ~(1<<(7-j));
		}
		else
		{
			i|= (1<<(7-j));
		}
		while ((HAL_GPIO_ReadPin (dht11_GPIO_Port, dht11_Pin)));
	}
	return i;
}
