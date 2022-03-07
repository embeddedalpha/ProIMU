/*
 * BMP280.c
 *
 *  Created on: 14-Dec-2021
 *      Author: Kunal
 */


#include "BMP280.h"


void BMP280_Init(I2C_TypeDef *PORT)
{
	int read = 0;
	BMP280_I2C_Struct.I2C = PORT;
	BMP280_I2C_Struct.mode = I2C_Fast_Mode;
	I2C_Master_Init(BMP280_I2C_Struct);

	I2C_Master_Write_Register(BMP280_I2C_Struct, BMP280_Address, BMP280_Reset_Register, 0xb6);

	do{
		read = I2C_Master_Read_Register_bit(BMP280_I2C_Struct, BMP280_Address, BMP280_Status_Register, bit_0);
	}while((read && (bit_0)));


	Temp_Cal.dig_T1 = I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, BMP280_DIG_T1_MSB) << 8 | I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, BMP280_DIG_T1_LSB);
	Temp_Cal.dig_T2 = I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, BMP280_DIG_T2_MSB) << 8 | I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, BMP280_DIG_T2_LSB);
	if(Temp_Cal.dig_T2 > 32767)
	{
		Temp_Cal.dig_T2 -= 65536;
	}
	Temp_Cal.dig_T3 = I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, BMP280_DIG_T3_MSB) << 8 | I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, BMP280_DIG_T3_LSB);
	if(Temp_Cal.dig_T3 > 32767)
	{
		Temp_Cal.dig_T3 -= 65536;
	}


	Pres_Cal.dig_P1 = (I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0x8F) << 8 | I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0x8E));
	Pres_Cal.dig_P2 = (I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0x91) << 8 | I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0x90));
	if(Pres_Cal.dig_P2 > 32767)
	{
		Pres_Cal.dig_P2 -= 65536;
	}

	Pres_Cal.dig_P3 = (I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0x93) << 8 | I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0x92));
	if(Pres_Cal.dig_P3 > 32767)
	{
		Pres_Cal.dig_P3 -= 65536;
	}

	Pres_Cal.dig_P4 = (I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0x95) << 8 | I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0x94));
	if(Pres_Cal.dig_P4 > 32767)
	{
		Pres_Cal.dig_P4 -= 65536;
	}

	Pres_Cal.dig_P5 = (I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0x97) << 8 | I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0x96));
	if(Pres_Cal.dig_P5 > 32767)
	{
		Pres_Cal.dig_P5 -= 65536;
	}

	Pres_Cal.dig_P6 = (I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0x99) << 8 | I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0x98));
	if(Pres_Cal.dig_P6 > 32767)
	{
		Pres_Cal.dig_P6 -= 65536;
	}

	Pres_Cal.dig_P7 = (I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0x9B) << 8 | I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0x9A));
	if(Pres_Cal.dig_P7 > 32767)
	{
		Pres_Cal.dig_P7 -= 65536;
	}

	Pres_Cal.dig_P8 = (I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0x9D) << 8 | I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0x9C));
	if(Pres_Cal.dig_P8 > 32767)
	{
		Pres_Cal.dig_P8 -= 65536;
	}

	Pres_Cal.dig_P9 = (I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0x9F) << 8 | I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0x9E));
	if(Pres_Cal.dig_P9 > 32767)
	{
		Pres_Cal.dig_P9 -= 65536;
	}


	I2C_Master_Write_Register(BMP280_I2C_Struct, BMP280_Address, BMP280_Ctrl_Measurement_Register, BMP280_TEMP_SAMPLING_X2
																								 | BMP280_PRES_SAMPLING_X16);

	I2C_Master_Write_Register(BMP280_I2C_Struct, BMP280_Address, BMP280_Config_Register, BMP280_STANDBY_MS_63 | BMP280_FILTER_X4);
	I2C_Master_Write_Register_bits(BMP280_I2C_Struct, BMP280_Address, BMP280_Ctrl_Measurement_Register, 1,  bit_1);





}


void BMP280_Get_Data(void)
{
	int32_t t_fine;
	int32_t temp_xlsb, temp_lsb, temp_msb;
	int32_t adc_T;
	int32_t var1, var2;
	double T;

	int64_t pres_xlsb, pres_lsb, pres_msb;
	int64_t adc_p;
	double p;
	int read;

	do{
		read = I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, BMP280_Status_Register);
	}while(((read&0b00001000)==8));

	temp_xlsb = I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, BMP280_Temperature_XLSB);
	temp_lsb = I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, BMP280_Temperature_LSB);
	temp_msb = I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, BMP280_Temperature_MSB);

	adc_T = (temp_msb << 12) + (temp_lsb << 4) + (temp_xlsb >> 4);

	var1 = (((double)adc_T)/16384.0 - ((double)Temp_Cal.dig_T1)/1024.0)*((double)Temp_Cal.dig_T2);
	var2 = ((((double)adc_T)/131072.0 - ((double)Temp_Cal.dig_T1)/8192.0)*(((double)adc_T)/131072.0-((double)Temp_Cal.dig_T1)/8192.0))*((double)Temp_Cal.dig_T3);
	t_fine = var1 + var2;
	T = (double)(var1 + var2)/5120.0;


	pres_xlsb = (int64_t)I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0xF9);
	pres_lsb = (int64_t)I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0xF8);
	pres_msb = (int64_t)I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, 0xF7);

	adc_p = (pres_msb << 12) + (pres_lsb << 4) + (pres_xlsb >> 4);

	var1 = ((double)t_fine/2.0)-64000.0;
	var2 = var1*var1*(Pres_Cal.dig_P6)/32768.0;
	var2 = var2+var1*(Pres_Cal.dig_P5)*2.0;
	var2 = (var2/4.0)+((Pres_Cal.dig_P4)*65536.0);
	var1 = ((Pres_Cal.dig_P3)*var1*var1/524288.0 + (Pres_Cal.dig_P2)*var1)/524288.0;
	var1 = (1.0 + var1/32768.0)*(Pres_Cal.dig_P1);
	p = 1048576.0-adc_p;
	p = (p - (var2/4096.0))*6250.0/var1;
	var1 = (Pres_Cal.dig_P9)*p*p/2147483648.0;
	var2 = p*(Pres_Cal.dig_P8)/32768.0;
	p = p + (var1 + var2 +(Pres_Cal.dig_P7))/16.0;

	float altitude = 0.0;
	altitude =  44330.0 * (1.0 - pow( (((p)/100) / 1013.2500), 0.1903));


	BMP280_Data.temperature_celcius = T/1.0;
	BMP280_Data.temperature_fareheit = ((T/1.0)*1.8)+32;
	BMP280_Data.pressure_pa = p;
	BMP280_Data.pressure_hg = (p)*0.0002953;
	BMP280_Data.altitude_meter = altitude;
	BMP280_Data.altitude_feet = altitude*3.28084;


}



