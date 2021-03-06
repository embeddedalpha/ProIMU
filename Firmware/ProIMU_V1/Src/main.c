/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
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

#include <stdint.h>
#include "main.h"
#include "Console/Console.h"
#include "I2C/I2C.h"
#include "GPIO/GPIO.h"
#include "MPU9250/MPU9250.h"





//
//void MPU9250_Self_Test(void)
//{
//	int accl_offset_x,accl_offset_y,accl_offset_z;
//	int fifo_len;
//	printConsole(USART1, "****************************************** Self Test ******************************************\r\n");
//	I2C_Master_
//
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, SMPLRT_DIV, 7);
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//	printConsole(USART1, "Offset= %d,%d,%d\r\n",accl_offset_x,accl_offset_y,accl_offset_z);
//
//	int fifo_len;
////	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, ACCEL_CONFIG, 0x01);
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, SMPLRT_DIV, 7);
//	I2C_Master_Write_Register_bits(MPU9250, MPU9250_ADDRESS, CONFIG, 1, bit_7 | bit_0 | bit_1);
//	I2C_Master_Write_Register_bits(MPU9250, MPU9250_ADDRESS, ACCEL_CONFIG, 1, bit_7 | bit_6 | bit_5);
//	I2C_Master_Write_Register_bits(MPU9250, MPU9250_ADDRESS, ACCEL_CONFIG2, 1,bit_1 | bit_0);
//	I2C_Master_Write_Register_bits(MPU9250, MPU9250_ADDRESS, FIFO_EN, 1, bit_3);
//	Delay_ms(100);
//	fifo_len = I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_COUNTH) << 8 |
//			   I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_COUNTL) ;
//	printConsole(USART1, "FIFO Length = %d\r\n",fifo_len);
//	Delay_ms(100);
//	int32_t accl_x_sf = 0;
//	int32_t accl_y_sf = 0;
//	int32_t accl_z_sf = 0;
//
//	int j;
//	fifo_len = fifo_len / 6;
//	for(int i = 0; i < fifo_len; i++)
//	{
//		accl_x_sf += I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+0)) << 8 |
//				     I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+1));
//		accl_y_sf += I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+2)) << 8 |
//				     I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+3));
//		accl_z_sf += I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+4)) << 8 |
//				     I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+5));
////		printConsole(USART1, "%d\r\n",I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+0)));
//	}
//
//	accl_x_sf = accl_x_sf / fifo_len;
//	accl_y_sf = accl_y_sf / fifo_len;
//	accl_z_sf = accl_z_sf / fifo_len;
//
//	printConsole(USART1, "%d\r\n",j);
//	printConsole(USART1, "Self Test Accl X = %"PRId32"\r\n",accl_x_sf);
//	printConsole(USART1, "Self Test Accl Y = %"PRId32"\r\n",accl_y_sf);
//	printConsole(USART1, "Self Test Accl Z = %"PRId32"\r\n",accl_z_sf);
//
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, XA_OFFSET_H, (( accl_x_sf & 0xFF00 ) >> 8));
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, XA_OFFSET_L, (( accl_x_sf & 0x00FF ) >> 0));
//
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, YA_OFFSET_H, (( accl_y_sf & 0xFF00 ) >> 8));
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, YA_OFFSET_L, (( accl_y_sf & 0x00FF ) >> 0));
//
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, ZA_OFFSET_H, (( accl_z_sf & 0xFF00 ) >> 8));
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, ZA_OFFSET_L, (( accl_z_sf & 0x00FF ) >> 0));
//
//	accl_offset_x = I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, XA_OFFSET_H) << 8 |
//			                  I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, XA_OFFSET_L) ;
//	accl_offset_y = I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, YA_OFFSET_H) << 8 |
//			                  I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, YA_OFFSET_L) ;
//	accl_offset_z = I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, ZA_OFFSET_H) << 8 |
//			                  I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, ZA_OFFSET_L) ;
//	printConsole(USART1, "Offset= %d,%d,%d\r\n",accl_offset_x,accl_offset_y,accl_offset_z);
//
//	MPU9250_Accelerometer_Offset.X = accl_offset_x;
//	MPU9250_Accelerometer_Offset.Y = accl_offset_y;
//	MPU9250_Accelerometer_Offset.Z = accl_offset_z;
//
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, CONFIG, 0x03);
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, ACCEL_CONFIG, 0x00);
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, ACCEL_CONFIG2, 0x03);
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, FIFO_EN, 0x00);
////	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, GYRO_CONFIG, 0x02);
//
//
////	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, CONFIG, 0x02);
////	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, FIFO_EN, 0x00);
//
//
//
//
//}
//
//
//
//void MPU9250_Accelerometer_Calibrate(void)
//{
//	uint16_t  accelsensitivity = 16384;  // = 16384 LSB/g
//	int fifo_length;
//	int packet_count;
//	int32_t accl_x_sf,accl_y_sf,accl_z_sf;
//
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, PWR_MGMT_1, 0x80);
//	Delay_ms(1);
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, PWR_MGMT_1, 0x01);
//	Delay_ms(1);
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, CONFIG, 0x42);
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, SMPLRT_DIV, 0x03);
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, ACCEL_CONFIG, 0xE0);
//
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, USER_CTRL, 0x40);
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, FIFO_EN, 0x08);
//	Delay_ms(1);
//
//
//	fifo_length = I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_COUNTH) << 8 |
//				   I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_COUNTL) ;
//
//	packet_count = fifo_length/6;
//
//	accl_x_sf = 0;
//	accl_y_sf = 0;
//	accl_z_sf = 0;
//
//	for(int i = 0; i < packet_count; i++)
//	{
//		accl_x_sf += I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+0)) << 8 |
//				     I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+1));
//		accl_y_sf += I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+2)) << 8 |
//				     I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+3));
//		accl_z_sf += I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+4)) << 8 |
//				     I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+5));
//	}
//	accl_x_sf = accl_x_sf / packet_count;
//	accl_y_sf = accl_y_sf / packet_count;
//	accl_z_sf = accl_z_sf / packet_count;
//
//	printConsole(USART1, "%d\r\n",fifo_length);
//	printConsole(USART1, "%d\r\n",accl_x_sf);
//	printConsole(USART1, "%d\r\n",accl_y_sf);
//	printConsole(USART1, "%d\r\n",accl_z_sf);
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, FIFO_EN, 0x00);
//
//
//}



int main(void)
{

	MCU_Clock_Setup();
	Console_Init(USART1, 9600);
	Delay_Config();
	MPU9250_Hardware_Init();
	MPU9250_Init();
	MPU9250_Read_Raw_Accelerometer();
	printConsole(USART1, "%d,%d,%d\r\n",MPU9250_Accelerometer_Axis.X,MPU9250_Accelerometer_Axis.Y,MPU9250_Accelerometer_Axis.Z);
	MPU9250_Self_Test();
	MPU9250_Read_Raw_Accelerometer();
	printConsole(USART1, "%d,%d,%d\r\n",MPU9250_Accelerometer_Axis.X,MPU9250_Accelerometer_Axis.Y,MPU9250_Accelerometer_Axis.Z);




    /* Loop forever */
	for(;;)
	{


	}
}
