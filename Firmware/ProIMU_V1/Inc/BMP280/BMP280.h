
/*
 * BMP280.h
 *
 *  Created on: 14-Dec-2021
 *      Author: Kunal
 */

#ifndef BMP280_BMP280_H_
#define BMP280_BMP280_H_

#include "main.h"
#include "GPIO/GPIO.h"
#include "I2C/I2C.h"
#include "SPI/SPI.h"
#include "Console/Console.h"
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


#define BMP280_TEMP_SAMPLING_NONE	    0x00 << 5
#define BMP280_TEMP_SAMPLING_X1		    0x01 << 5
#define BMP280_TEMP_SAMPLING_X2		    0x02 << 5
#define BMP280_TEMP_SAMPLING_X4		    0x03 << 5
#define BMP280_TEMP_SAMPLING_X8		    0x04 << 5
#define BMP280_TEMP_SAMPLING_X16		0x05 << 5

#define BMP280_PRES_SAMPLING_NONE	    0x00 << 2
#define BMP280_PRES_SAMPLING_X1		    0x01 << 2
#define BMP280_PRES_SAMPLING_X2		    0x02 << 2
#define BMP280_PRES_SAMPLING_X4		    0x03 << 2
#define BMP280_PRES_SAMPLING_X8		    0x04 << 2
#define BMP280_PRES_SAMPLING_X16		0x05 << 2

#define BMP280_MODE_SLEEP		0x00
#define BMP280_MODE_FORCED		0x01
#define BMP280_MODE_NORMAL		0x03

#define BMP280_FILTER_OFF	    0x00 << 2
#define BMP280_FILTER_X2		0x01 << 2
#define BMP280_FILTER_X4		0x02 << 2
#define BMP280_FILTER_X8		0x03 << 2
#define BMP280_FILTER_X16		0x04 << 2

#define BMP280_STANDBY_MS_1			0x00 << 5
#define BMP280_STANDBY_MS_63		0x01 << 5
#define BMP280_STANDBY_MS_125		0x02 << 5
#define BMP280_STANDBY_MS_250		0x03 << 5
#define BMP280_STANDBY_MS_500		0x04 << 5
#define BMP280_STANDBY_MS_1000		0x05 << 5
#define BMP280_STANDBY_MS_2000		0x06 << 5
#define BMP280_STANDBY_MS_4000		0x07 << 5

void BMP280_Init(I2C_TypeDef *PORT);
void BMP280_Get_Data(void);



#endif /* BMP280_BMP280_H_ */
