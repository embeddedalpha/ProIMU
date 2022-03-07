/*
 * MPU9250.h
 *
 *  Created on: 07-Mar-2022
 *      Author: Kunal
 */

#ifndef MPU9250_MPU9250_H_
#define MPU9250_MPU9250_H_

#include "main.h"
#include "I2C/I2C.h"
#include "MPU9250_Reg.h"


//	Accelerometer Structure
struct MPU9250_Accelerometer_Axis
{
	int X;
	int Y;
	int Z;
}
MPU9250_Accelerometer_Axis;

struct MPU9250_Accelerometer_Offset
{
	int X;
	int Y;
	int Z;
}
MPU9250_Accelerometer_Offset;

struct MPU9250_Accelerometer_Self_Test
{
	int X;
	int Y;
	int Z;
}
MPU9250_Accelerometer_Self_Test;

//	Gyroscope Structure
struct MPU9250_Gyroscope_Axis
{
	int X;
	int Y;
	int Z;
}
MPU9250_Gyroscope_Axis;

struct MPU9250_Gyroscope_Offset
{
	int X;
	int Y;
	int Z;
}
MPU9250_Gyroscope_Offset;

struct MPU9250_Gyroscope_Self_Test
{
	int X;
	int Y;
	int Z;
}
MPU9250_Gyroscope_Self_Test;






struct MPU9250_Magnetometer_Axis
{
	float X;
	float Y;
	float Z;
}MPU9250_Magnetometer_Axis;

struct MPU9250_Magnetometer_Offset
{
	int X;
	int Y;
	int Z;
}
MPU9250_Magnetometer_Offset;

struct MPU9250_Magnetometer_Self_Test
{
	int X;
	int Y;
	int Z;
}
MPU9250_Magnetometer_Self_Test;

void MPU9250_Hardware_Init(void);
void MPU9250_Init(void);
void MPU9250_Get_Offset(void);
void MPU9250_Self_Test(void);
void MPU9250_Reset(void);

void MPU9250_Read_Raw_Accelerometer(void);
void MPU9250_Read_Raw_Gyroscope(void);
void MPU9250_Read_Raw_Magnetometer(void);
int MPU9250_Read_Raw_Temperature(void);


#endif /* MPU9250_MPU9250_H_ */
