/*
 * BMP280_Reg.h
 *
 *  Created on: 19-Jan-2022
 *      Author: Kunal
 */

#ifndef BMP280_BMP280_REG_H_
#define BMP280_BMP280_REG_H_

#define BMP280_Address	                    0x76
#define BMP280_ID_Register	                0xD0
#define BMP280_Reset_Register	            0xE0
#define BMP280_Status_Register	            0xF3
#define BMP280_Ctrl_Measurement_Register	0xF4
#define BMP280_Config_Register	            0xF5

#define BMP280_Pressure_MSB	                0xF7
#define BMP280_Pressure_LSB	                0xF8
#define BMP280_Pressure_XLSB	            0xF9

#define BMP280_Temperature_MSB	            0xFA
#define BMP280_Temperature_LSB	            0xFB
#define BMP280_Temperature_XLSB	            0xFC


#define BMP280_DIG_T1_LSB                   0x88
#define BMP280_DIG_T1_MSB                   0x89

#define BMP280_DIG_T2_LSB                   0x8A
#define BMP280_DIG_T2_MSB                   0x8B

#define BMP280_DIG_T3_LSB                   0x8C
#define BMP280_DIG_T3_MSB                   0x8D

#define BMP280_DIG_P1_LSB                   0x8E
#define BMP280_DIG_P1_MSB                   0x8F

#define BMP280_DIG_P2_LSB                   0x90
#define BMP280_DIG_P2_MSB                   0x91

#define BMP280_DIG_P3_LSB                   0x92
#define BMP280_DIG_P3_MSB                   0x93

#define BMP280_DIG_P4_LSB                   0x94
#define BMP280_DIG_P4_MSB                   0x95

#define BMP280_DIG_P5_LSB                   0x96
#define BMP280_DIG_P5_MSB                   0x97

#define BMP280_DIG_P6_LSB                   0x98
#define BMP280_DIG_P6_MSB                   0x99

#define BMP280_DIG_P7_LSB                   0x9A
#define BMP280_DIG_P7_MSB                   0x9B

#define BMP280_DIG_P8_LSB                   0x9C
#define BMP280_DIG_P8_MSB                   0x9D

#define BMP280_DIG_P9_LSB                   0x9E
#define BMP280_DIG_P9_MSB                   0x9F

#define BMP280_Sleep_Mode					0x00
#define BMP280_Forced_Mode					0x01
#define BMP280_Normal_Mode					0x03

#endif /* BMP280_BMP280_REG_H_ */
