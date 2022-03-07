/*
 * MPU9250.c
 *
 *  Created on: 07-Mar-2022
 *      Author: Kunal
 */

#include "MPU9250.h"

I2C_Config MPU9250;


void MPU9250_Hardware_Init(void)
{
	MPU9250.I2C = I2C1;
	MPU9250.mode = I2C_Fast_Mode;
	I2C_Master_Init(MPU9250);
}

void MPU9250_Init(void)
{
	MPU9250_Reset();
	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, PWR_MGMT_1, 0x02);
	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, CONFIG, 0x02);
	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, SMPLRT_DIV, 0x04);
//	I2C_Master_Write_Register_bits(MPU9250, MPU9250_ADDRESS, GYRO_CONFIG, 0, bit_4 | bit_3);
//	I2C_Master_Write_Register_bits(MPU9250, MPU9250_ADDRESS, ACCEL_CONFIG, 0, bit_4 | bit_3);
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, INT_PIN_CFG, 0x22);
//	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, INT_ENABLE, 0x01);
}

void MPU9250_Get_Offset(void)
{
	MPU9250_Accelerometer_Offset.X = I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, XA_OFFSET_H) << 8 |
									 I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, XA_OFFSET_L) ;
	MPU9250_Accelerometer_Offset.Y = I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, YA_OFFSET_H) << 8 |
									 I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, YA_OFFSET_L) ;
	MPU9250_Accelerometer_Offset.Z = I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, ZA_OFFSET_H) << 8 |
									 I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, ZA_OFFSET_L) ;
}

void MPU9250_Reset(void)
{
	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, PWR_MGMT_1, 0x80);
	Delay_ms(1);
	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, PWR_MGMT_1, 0x00);
}

void MPU9250_Self_Test(void)
{
	int32_t accl_offset_x,accl_offset_y,accl_offset_z;
	accl_offset_x = 0;
	accl_offset_y = 0;
	accl_offset_z = 0;

	int fifo_len, packet_len;
	printConsole(USART1, "****************************************** Self Test ******************************************\r\n");
	MPU9250_Reset();
	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, PWR_MGMT_1, 0x02);
	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, CONFIG, 0x40); //Enable FiFo Mode
	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, ACCEL_CONFIG, 0xE0); //Activate Self Test for Accelerometer

	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, USER_CTRL, 0x40);
	I2C_Master_Write_Register(MPU9250, MPU9250_ADDRESS, FIFO_EN, 0x08);
	Delay_ms(100);
	fifo_len = I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_COUNTH) << 8 |
			   I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_COUNTL) ;

	printConsole(USART1, "FIFO Length: %d\r\n",fifo_len);

	packet_len = fifo_len/6;
	printConsole(USART1, "Packet Length: %d\r\n",packet_len);

	for(int i = 0; i < packet_len; i++)
	{
		accl_offset_x += (I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+0)) << 8) |
				          I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+1));
		accl_offset_y += (I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+2)) << 8) |
				          I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+3));
		accl_offset_z += (I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+4)) << 8) |
				          I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, FIFO_R_W+(i+5));
	}

	accl_offset_x = accl_offset_x / packet_len;
	accl_offset_y = accl_offset_y / packet_len;
	accl_offset_z = accl_offset_z / packet_len;
	printConsole(USART1, "%d,%d,%d\r\n",accl_offset_x,accl_offset_y,accl_offset_z);
//	MPU9250_Reset();
	MPU9250_Init();
}

void MPU9250_Read_Raw_Accelerometer(void)
{
	MPU9250_Accelerometer_Axis.X = I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, 0x3B) << 8 |
			                  I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, 0x3C) ;
	MPU9250_Accelerometer_Axis.Y = I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, 0x3D) << 8 |
			                  I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, 0x3E) ;
	MPU9250_Accelerometer_Axis.Z = I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, 0x3F) << 8 |
			                  I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, 0x40) ;
}

void MPU9250_Read_Raw_Gyroscope(void)
{
	MPU9250_Gyroscope_Axis.X = (I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, 0x43) << 8) |
			              I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, 0x44) ;
	MPU9250_Gyroscope_Axis.Y = (I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, 0x45) << 8) |
			              I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, 0x46) ;
	MPU9250_Gyroscope_Axis.Z = (I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, 0x47) << 8) |
			              I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, 0x48) ;
}

void MPU9250_Read_Raw_Magnetometer(void)
{
	MPU9250_Magnetometer_Axis.X = I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, AK8963_XOUT_H) << 8 |
			              	 I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, AK8963_XOUT_L) ;
	MPU9250_Magnetometer_Axis.Y = I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, AK8963_YOUT_H) << 8 |
			                 I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, AK8963_YOUT_L) ;
	MPU9250_Magnetometer_Axis.Z = I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, AK8963_ZOUT_H) << 8 |
			                 I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, AK8963_ZOUT_L) ;
}

int MPU9250_Read_Raw_Temperature(void)
{
	return(
			I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, TEMP_OUT_H) << 8 |
			I2C_Master_Read_Register(MPU9250, MPU9250_ADDRESS, TEMP_OUT_L)
		  );
}
