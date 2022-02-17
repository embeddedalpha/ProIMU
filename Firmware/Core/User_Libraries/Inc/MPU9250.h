/*
 * MPU9250.h
 *
 *  Created on: 18-Jan-2022
 *      Author: Kunal
 */

#ifndef MPU9250_MPU9250_H_
#define MPU9250_MPU9250_H_

#include "main.h"
#include "I2C.h"
#include "Console.h"
#include "MPU9250_Reg.h"

I2C_Config MPU9250;

#define MPU9250_Debug 1
#define MPU9250_I2C	1
#define MPU9250_SPI	0

I2C_Config MPU9250_I2C_Struct ;
//SPI_Config MPU9250_SPI_Struct;

struct MPU9250_Self_Test_Data
{
	int SELF_TEST_ACCL_X;
	int SELF_TEST_ACCL_Y;
	int SELF_TEST_ACCL_Z;

	int SELF_TEST_GYRO_X;
	int SELF_TEST_GYRO_Y;
	int SELF_TEST_GYRO_Z;

	int SELF_TEST_MAGN_X;
	int SELF_TEST_MAGN_Y;
	int SELF_TEST_MAGN_Z;

}MPU9250_Self_Test_Data;

struct MPU9250_Calibration_Data
{
	int CALB_ACCL_X;
	int CALB_ACCL_Y;
	int CALB_ACCL_Z;

	int CALB_GYRO_X;
	int CALB_GYRO_Y;
	int CALB_GYRO_Z;

	int CALB_MAGN_X;
	int CALB_MAGN_Y;
	int CALB_MAGN_Z;

}MPU9250_Calibration_Data;


struct MPU9250_Accelerometer
{
	float X;
	float Y;
	float Z;
}MPU9250_Accelerometer;

struct MPU9250_Gyroscope
{
	float X;
	float Y;
	float Z;
}MPU9250_Gyroscope;

struct MPU9250_Magnetometer
{
	float X;
	float Y;
	float Z;
}MPU9250_Magnetometer;

struct MPU9250_Angle
{
	float pitch;
	float roll;
	float yaw;
}MPU9250_Angle;


#if MPU9250_I2C
	void IMU_Init();
	void IMU_Get_Data();
#endif


#if MPU9250_SPI
	void MPU9250_Init();
	void MP9250_Get_Data();
#endif



#endif /* MPU9250_MPU9250_H_ */
