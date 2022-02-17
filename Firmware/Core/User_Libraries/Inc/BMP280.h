
/*
 * BMP280.h
 *
 *  Created on: 14-Dec-2021
 *      Author: Kunal
 */

#ifndef BMP280_BMP280_H_
#define BMP280_BMP280_H_

#include "main.h"
#include "GPIO.h"
#include "I2C.h"
#include "Console.h"
#include "BMP280_Reg.h"



#define BMP280_S32_t int32_t

#define BMP280_SPI	0
#define BMP280_I2C	1

I2C_Config BMP280_I2C_Struct ;
SPI_Config BMP280_SPI_Struct;


struct Temp_Cal
{
	int dig_T1;
	int dig_T2;
	int dig_T3;
}Temp_Cal;

struct Pres_Cal
{
	int dig_P1;
	int dig_P2;
	int dig_P3;
	int dig_P4;
	int dig_P5;
	int dig_P6;
	int dig_P7;
	int dig_P8;
	int dig_P9;
}Pres_Cal;


struct BMP280_Data{
	double temperature_celcius;
	double temperature_fareheit;
	double pressure_pa;
	double pressure_hg;
	double altitude_meter;
	double altitude_feet;
}BMP280_Data;


void BMP280_Init(I2C_TypeDef *PORT);
void BMP280_Get_Data(void);



#endif /* BMP280_BMP280_H_ */
