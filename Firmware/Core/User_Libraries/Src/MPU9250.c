/*
 * MPU9250.c
 *
 *  Created on: 18-Jan-2022
 *      Author: Kunal
 */

#include "MPU9250.h"


/*
 * TEST WHO AM I
 * RUN SELF TEST
 * CALIBRATE MPU9250
 * INITIALIZE MPU9250
 * TEST WHO AM I
 * INITALIZE AK8963
 * CALIBARTE AK8963
 */


/*
 *************************************************** GYROSCOPE ***********************************************
 * BANDWIDTH (Hz): 92
 * DELAY (ms): 3.9
 * Fs (kHz): 1
 * FULL SCALE RANGE: +- 500 DPS
 *************************************************** ACCELEROMETER *******************************************
 * BANDWIDTH (Hz): 92
 * DELAY (ms): 7.8
 * Fs (kHz): 1
 * Noise Density (ug/rtHz): 250
 * FULL SCALE RANGE: +- 4G
 */

static void MPU9250_Self_Test(void)
{
	int32_t accl_avg_x,accl_avg_y,accl_avg_z;
	int32_t gyro_avg_x,gyro_avg_y,gyro_avg_z;

	int32_t accl_self_x, accl_self_y, accl_self_z;
	int32_t gyro_self_x, gyro_self_y, gyro_self_z;

	int32_t accl_self_reg_x, accl_self_reg_y, accl_self_reg_z;
	int32_t gyro_self_reg_x, gyro_self_reg_y, gyro_self_reg_z;

	float  trim_accl_x, trim_accl_y, trim_accl_z;
	float  trim_gyro_x, trim_gyro_y, trim_gyro_z;


	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, SMPLRT_DIV, 0x04);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, CONFIG, 0x02);
	I2C_Master_Write_Register_bits(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_CONFIG, 1, bit_3);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_CONFIG2, 0x02);
	I2C_Master_Write_Register_bits(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_CONFIG, 1, bit_3);

	for(int i = 0; i < 500; i++)
	{
		accl_avg_x += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_XOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_XOUT_L) << 0);
		accl_avg_y += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_YOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_YOUT_L) << 0);
		accl_avg_z += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_ZOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_ZOUT_L) << 0);

		gyro_avg_x += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_XOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_XOUT_L) << 0);
		gyro_avg_y += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_YOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_XOUT_L) << 0);
		gyro_avg_z += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_ZOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_XOUT_L) << 0);

	}

	accl_avg_x /= 500;
	accl_avg_y /= 500;
	accl_avg_z /= 500;

	gyro_avg_x /= 500;
	gyro_avg_y /= 500;
	gyro_avg_z /= 500;

	I2C_Master_Write_Register_bits(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_CONFIG, 1, (bit_7 | bit_6 | bit_5));
	I2C_Master_Write_Register_bits(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_CONFIG, 1, (bit_7 | bit_6 | bit_5));
	Delay_ms(50);

	for(int i = 0; i < 500; i++)
	{
		accl_self_x += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_XOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_XOUT_L) << 0);
		accl_self_y += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_YOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_YOUT_L) << 0);
		accl_self_z += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_ZOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_ZOUT_L) << 0);

		gyro_self_x += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_XOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_XOUT_L) << 0);
		gyro_self_y += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_YOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_XOUT_L) << 0);
		gyro_self_z += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_ZOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_XOUT_L) << 0);

	}

	accl_self_x /= 500;
	accl_self_y /= 500;
	accl_self_z /= 500;

	gyro_self_x /= 500;
	gyro_self_y /= 500;
	gyro_self_z /= 500;

	I2C_Master_Write_Register_bits(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_CONFIG, 0, (bit_7 | bit_6 | bit_5));
	I2C_Master_Write_Register_bits(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_CONFIG, 0, (bit_7 | bit_6 | bit_5));
	Delay_ms(50);

	accl_self_reg_x = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, SELF_TEST_X_ACCEL);
	accl_self_reg_y = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, SELF_TEST_Y_ACCEL);
	accl_self_reg_z = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, SELF_TEST_Z_ACCEL);

	gyro_self_reg_x = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, SELF_TEST_X_GYRO);
	gyro_self_reg_y = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, SELF_TEST_Y_GYRO);
	gyro_self_reg_z = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, SELF_TEST_Z_GYRO);


	trim_accl_x = (float)(2620/1<<1)*(pow( 1.01, ((float)accl_self_reg_x - 1.0)));
	trim_accl_y = (float)(2620/1<<1)*(pow( 1.01, ((float)accl_self_reg_y - 1.0)));
	trim_accl_z = (float)(2620/1<<1)*(pow( 1.01, ((float)accl_self_reg_z - 1.0)));

	trim_gyro_x = (float)(2620/1<<1)*(pow( 1.01, ((float)gyro_self_reg_x - 1.0)));
	trim_gyro_y = (float)(2620/1<<1)*(pow( 1.01, ((float)gyro_self_reg_y - 1.0)));
	trim_gyro_z = (float)(2620/1<<1)*(pow( 1.01, ((float)gyro_self_reg_z - 1.0)));


	MPU9250_Self_Test_Data.SELF_TEST_ACCL_X = 100.0 * ((float)(accl_self_x - accl_avg_x))/trim_accl_x - 100.0;
	MPU9250_Self_Test_Data.SELF_TEST_ACCL_Y = 100.0 * ((float)(accl_self_y - accl_avg_y))/trim_accl_y - 100.0;
	MPU9250_Self_Test_Data.SELF_TEST_ACCL_Z = 100.0 * ((float)(accl_self_z - accl_avg_z))/trim_accl_z - 100.0;

	MPU9250_Self_Test_Data.SELF_TEST_GYRO_X = 100.0 * ((float)(gyro_self_x - gyro_avg_x))/trim_gyro_x - 100.0;
	MPU9250_Self_Test_Data.SELF_TEST_GYRO_Y = 100.0 * ((float)(gyro_self_y - gyro_avg_y))/trim_gyro_y - 100.0;
	MPU9250_Self_Test_Data.SELF_TEST_GYRO_Z = 100.0 * ((float)(gyro_self_z - gyro_avg_z))/trim_gyro_z - 100.0;

#if MPU9250_Debug
			printConsole(USART1, "Self Test ACCL X: %f \r\n",MPU9250_Self_Test_Data.SELF_TEST_ACCL_X);
			printConsole(USART1, "Self Test ACCL Y: %f \r\n",MPU9250_Self_Test_Data.SELF_TEST_ACCL_Y);
			printConsole(USART1, "Self Test ACCL Z: %f \r\n",MPU9250_Self_Test_Data.SELF_TEST_ACCL_Z);

			printConsole(USART1, "Self Test GYRO X: %f \r\n",MPU9250_Self_Test_Data.SELF_TEST_GYRO_X);
			printConsole(USART1, "Self Test GYRO Y: %f \r\n",MPU9250_Self_Test_Data.SELF_TEST_GYRO_Y);
			printConsole(USART1, "Self Test GYRO Z: %f \r\n",MPU9250_Self_Test_Data.SELF_TEST_GYRO_Z);
#endif

}


/*
 *************************************************** GYROSCOPE ***********************************************
 * BANDWIDTH (Hz): 92
 * DELAY (ms): 3.9
 * Fs (kHz): 1
 * FULL SCALE RANGE: +- 500 DPS
 *************************************************** ACCELEROMETER *******************************************
 * BANDWIDTH (Hz): 92
 * DELAY (ms): 7.8
 * Fs (kHz): 1
 * Noise Density (ug/rtHz): 250
 * FULL SCALE RANGE: +- 4G
 */
static void MPU9250_Calibration(void)
{
	float gyro_sensitivity =  65.5;
	float accl_sensitivity =  8192.0;
	int fifo_len;

	int fifo_buffer[12];
	float accl_bias_x, accl_bias_y, accl_bias_z;
	float gyro_bias_x, gyro_bias_y, gyro_bias_z;



	//reset
	I2C_Master_Write_Register_bits(MPU9250_I2C_Struct, MPU9250_ADDRESS, PWR_MGMT_1, 1, bit_7);
	Delay_ms(100);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, PWR_MGMT_1, 0x01);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, PWR_MGMT_2, 0x00);
	Delay_ms(200);

	//Bias Calculation
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, INT_ENABLE, 0x00);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, FIFO_EN, 0x00);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, PWR_MGMT_1, 0x00);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, I2C_MST_CTRL, 0x00);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, USER_CTRL, 0x00);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, USER_CTRL, 0x0C);
	Delay_ms(15);

	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, CONFIG, 0x02);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, SMPLRT_DIV, 0x00);
	I2C_Master_Write_Register_bits(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_CONFIG, 1, bit_3);
	I2C_Master_Write_Register_bits(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_CONFIG, 1, bit_3);

	I2C_Master_Write_Register_bits(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_CONFIG, 1, bit_6);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, FIFO_EN, 0x78);
	Delay_ms(100);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, FIFO_EN, 0x00);

	fifo_len = (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, FIFO_COUNTH) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, FIFO_COUNTL));
	int packet_length = fifo_len / 12;


	accl_bias_x = 0;
	accl_bias_y = 0;
	accl_bias_z = 0;


	for(int i = 0; i < packet_length; i++)
	{
		for(int j = 0; j < 12; j++)
		{
			fifo_buffer[i] = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, FIFO_R_W + i);
		}

		accl_bias_x += (float)(fifo_buffer[0] << 8 | fifo_buffer[1]);
		accl_bias_y += (float)(fifo_buffer[2] << 8 | fifo_buffer[3]);
		accl_bias_z += (float)(fifo_buffer[4] << 8 | fifo_buffer[5]);

		gyro_bias_x += (float)(fifo_buffer[6] << 8 | fifo_buffer[7]);
		gyro_bias_y += (float)(fifo_buffer[8] << 8 | fifo_buffer[9]);
		gyro_bias_z += (float)(fifo_buffer[10] << 8 | fifo_buffer[11]);
	}

	accl_bias_x /= packet_length;
	accl_bias_y /= packet_length;
	accl_bias_z /= packet_length;

	gyro_bias_x /= packet_length;
	gyro_bias_y /= packet_length;
	gyro_bias_z /= packet_length;

	if(accl_bias_z > 0)
	{
		accl_bias_z -= accl_sensitivity;
	}
	else
	{
		accl_bias_z += accl_sensitivity;
	}
	fifo_buffer[0] = (-gyro_bias_x / (2 * 256));
	fifo_buffer[1] = (-gyro_bias_x / (2 * 1));
	fifo_buffer[2] = (-gyro_bias_y / (2 * 256));
	fifo_buffer[3] = (-gyro_bias_y / (2 * 1));
	fifo_buffer[4] = (-gyro_bias_z / (2 * 256));
	fifo_buffer[5] = (-gyro_bias_z / (2 * 1));

	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, XG_OFFSET_H, fifo_buffer[0]);

	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, XG_OFFSET_L, fifo_buffer[1]);

	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, YG_OFFSET_H, fifo_buffer[2]);

	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, YG_OFFSET_L, fifo_buffer[3]);

	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ZG_OFFSET_H, fifo_buffer[4]);

	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ZG_OFFSET_L, fifo_buffer[5]);

	MPU9250_Calibration_Data.CALB_GYRO_X = gyro_bias_x / (float) gyro_sensitivity;
	MPU9250_Calibration_Data.CALB_GYRO_Y = gyro_bias_y / (float) gyro_sensitivity;
	MPU9250_Calibration_Data.CALB_GYRO_Z = gyro_bias_z / (float) gyro_sensitivity;

	float accl_offset_reg_x, accl_offset_reg_y, accl_offset_reg_z;
	accl_offset_reg_x = (float)( (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, XA_OFFSET_H) << 8) | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, XA_OFFSET_L) );

	accl_offset_reg_y = (float)( (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, YA_OFFSET_H) << 8) | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, YA_OFFSET_L) );

	accl_offset_reg_z = (float)( (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ZA_OFFSET_H) << 8) | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ZA_OFFSET_L) );

	accl_offset_reg_x -= (accl_bias_x/8.0);
	accl_offset_reg_y -= (accl_bias_y/8.0);
	accl_offset_reg_z -= (accl_bias_z/8.0);

	fifo_buffer[0] = (int)(accl_offset_reg_x /256);
	fifo_buffer[1] = (int)(accl_offset_reg_x );

	fifo_buffer[2] = (int)(accl_offset_reg_x / 256);
	fifo_buffer[3] = (int)(accl_offset_reg_x );

	fifo_buffer[4] = (int)(accl_offset_reg_x / 256);
	fifo_buffer[5] = (int)(accl_offset_reg_x );

	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, XA_OFFSET_H, fifo_buffer[0]);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, XA_OFFSET_L, fifo_buffer[1]);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, YA_OFFSET_H, fifo_buffer[2]);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, YA_OFFSET_L, fifo_buffer[3]);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ZA_OFFSET_H, fifo_buffer[4]);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ZA_OFFSET_L, fifo_buffer[5]);

	MPU9250_Calibration_Data.CALB_ACCL_X = accl_bias_x / (float) accl_sensitivity;
	MPU9250_Calibration_Data.CALB_ACCL_Y = accl_bias_y / (float) accl_sensitivity;
	MPU9250_Calibration_Data.CALB_ACCL_Z = accl_bias_z / (float) accl_sensitivity;

#if MPU9250_Debug
			printConsole(USART1, "Calibration Data: \r\n");
			printConsole(USART1, "Acclerometer X: %f \r\n",MPU9250_Calibration_Data.CALB_ACCL_X);
			printConsole(USART1, "Acclerometer Y: %f \r\n",MPU9250_Calibration_Data.CALB_ACCL_Y);
			printConsole(USART1, "Acclerometer Z: %f \r\n",MPU9250_Calibration_Data.CALB_ACCL_Z);

			printConsole(USART1, "Gyroscope X:    %f \r\n",MPU9250_Calibration_Data.CALB_GYRO_X);
			printConsole(USART1, "Gyroscope Y:    %f \r\n",MPU9250_Calibration_Data.CALB_GYRO_Y);
			printConsole(USART1, "Gyroscope Z:    %f \r\n",MPU9250_Calibration_Data.CALB_GYRO_Z);
#endif

}

static void MPU9250_Init(void)
{
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, PWR_MGMT_1, 0x00);
	Delay_ms(100);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, PWR_MGMT_1, 0x01);
	Delay_ms(100);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, PWR_MGMT_1, 0x02);
	Delay_ms(100);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, SMPLRT_DIV, 0x04);
	Delay_ms(100);
	I2C_Master_Write_Register_bits(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_CONFIG, 1, bit_3);
	Delay_ms(100);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_CONFIG2, 0x02);
	Delay_ms(100);
	I2C_Master_Write_Register_bits(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_CONFIG, 1, bit_3);
	Delay_ms(100);
}

static void AK8963_Init(void)
{
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, AK8963_CNTL, 0x00);
	Delay_ms(100);
	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, AK8963_CNTL, 0x0F);
	Delay_ms(100);
	MPU9250_Calibration_Data.CALB_MAGN_X = (float)(I2C_Master_Read_Register(MPU9250_I2C_Struct, AK8963_ADDRESS, AK8963_ASAX) - 128)/256.0 + 1.0;
	MPU9250_Calibration_Data.CALB_MAGN_Y = (float)(I2C_Master_Read_Register(MPU9250_I2C_Struct, AK8963_ADDRESS, AK8963_ASAY) - 128)/256.0 + 1.0;
	MPU9250_Calibration_Data.CALB_MAGN_Z = (float)(I2C_Master_Read_Register(MPU9250_I2C_Struct, AK8963_ADDRESS, AK8963_ASAZ) - 128)/256.0 + 1.0;

	I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, AK8963_CNTL, 0x16);
	Delay_ms(10);
}




#if MPU9250_I2C
	void IMU_Init(I2C_TypeDef *PORT)
	{
		float accl_x_avg, accl_y_avg, accl_z_avg;
		float gyro_x_avg, gyro_y_avg, gyro_z_avg;

		float accl_x_slf, accl_y_slf, accl_z_slf;
		float gyro_x_slf, gyro_y_slf, gyro_z_slf;

		int fact_accl_x, fact_accl_y,fact_accl_z;
		int fact_gyro_x, fact_gyro_y,fact_gyro_z;

		float fact_trim_accl_x, fact_trim_accl_y, fact_trim_accl_z;
		float fact_trim_gyro_x, fact_trim_gyro_y, fact_trim_gyro_z;

		float percent_accl_x, percent_accl_y, percent_accl_z;
		float percent_gyro_x, percent_gyro_y, percent_gyro_z;



		int read = 0;
		MPU9250_I2C_Struct.I2C = PORT;
		MPU9250_I2C_Struct.mode = I2C_Fast_Mode;
		I2C_Master_Init(MPU9250_I2C_Struct);

		read = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, WHO_AM_I_MPU9250);
		if(read == 113)
		{
			printConsole(USART1, "Communication established with MPU9250 1: \r\n");
		}
		else
		{
			printConsole(USART1, "Check Connection or State of MPU9250 1: \r\n");
		}
		//Exit sleep mode
		I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, PWR_MGMT_1, 0x00);
		Delay_ms(100);

		//Select Internal Oscillator
		I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, PWR_MGMT_1, 0x01);
		Delay_ms(100);

		//Set Gyroscope digital low pass filter to Bandwidth = 92Hz & Sampling Frequency = 1kHz
		//Set Temperature Sensor DLPF to Bandwidth = 98Hz
		I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, CONFIG, 0x02);
		Delay_ms(100);

		//Set Sample rate at 256Hz
		I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, SMPLRT_DIV, 0x00);
		Delay_ms(100);

		//Set Gyroscope Full Scale Range to 500 dps
		I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_CONFIG, 0x08);
		Delay_ms(100);

		//Set Accelerometer Full Scale Range to 4 G
		I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_CONFIG, 0x08);
		Delay_ms(100);

		//Set Accelerometer DLPF to Bandwidth = 92Hz & Sampling Frequency = 1kHz
		I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_CONFIG2, 0x02);
		Delay_ms(100);

		//Set Accelerometer DLPF to Bandwidth = 92Hz & Sampling Frequency = 1kHz
		I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, INT_PIN_CFG, 0x22);
		Delay_ms(100);

		read = I2C_Master_Read_Register(MPU9250_I2C_Struct, AK8963_ADDRESS, AK8963_WHO_AM_I);
		if(read == 72)
		{
			printConsole(USART1, "Communication established with AK8963 1: \r\n");
		}
		else
		{
			printConsole(USART1, "Check Connection or State of AK8963 1: \r\n");
		}


		accl_x_avg = 0;
		accl_y_avg = 0;
		accl_z_avg = 0;

		gyro_x_avg = 0;
		gyro_y_avg = 0;
		gyro_z_avg = 0;

		//Calibration MPU9250
		for(int i = 0; i < 200; i++)
		{
			accl_x_avg += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_XOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_XOUT_L));
			accl_y_avg += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_YOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_YOUT_L));
			accl_z_avg += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_ZOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_ZOUT_L));

			gyro_x_avg += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_XOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_XOUT_L));
			gyro_y_avg += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_YOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_YOUT_L));
			gyro_z_avg += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_ZOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_ZOUT_L));
		}

		accl_x_avg = (float)accl_x_avg / 200.0;
		accl_y_avg = (float)accl_y_avg / 200.0;
		accl_z_avg = (float)accl_z_avg / 200.0;

		gyro_x_avg = (float)gyro_x_avg / 200.0;
		gyro_y_avg = (float)gyro_y_avg / 200.0;
		gyro_z_avg = (float)gyro_z_avg / 200.0;


		printConsole(USART1, "Average Values : \r\n");
		printConsole(USART1, "ACCL X %f : \r\n",accl_x_avg);
		printConsole(USART1, "ACCL Y %f : \r\n",accl_y_avg);
		printConsole(USART1, "ACCL Z %f : \r\n",accl_z_avg);

		printConsole(USART1, "GYRO X %f : \r\n",gyro_x_avg);
		printConsole(USART1, "GYRO Y %f : \r\n",gyro_y_avg);
		printConsole(USART1, "GYRO Z %f : \r\n",gyro_z_avg);

		//Enable Self Test of Accelerometer and Gyroscope:
		I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_CONFIG, 0xE0);
		I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_CONFIG,  0xE0);
		Delay_ms(20);


		accl_x_slf = 0;
		accl_y_slf = 0;
		accl_z_slf = 0;

		gyro_x_slf = 0;
		gyro_y_slf = 0;
		gyro_z_slf = 0;

		//Calibration MPU9250
		for(int i = 0; i < 200; i++)
		{
			accl_x_slf += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_XOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_XOUT_L));
			accl_y_slf += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_YOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_YOUT_L));
			accl_z_slf += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_ZOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_ZOUT_L));

			gyro_x_slf += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_XOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_XOUT_L));
			gyro_y_slf += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_YOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_YOUT_L));
			gyro_z_slf += (I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_ZOUT_H) << 8 | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_ZOUT_L));
		}

		accl_x_slf = (float)accl_x_slf / 200.0;
		accl_y_slf = (float)accl_y_slf / 200.0;
		accl_z_slf = (float)accl_z_slf / 200.0;

		gyro_x_slf = (float)gyro_x_slf / 200.0;
		gyro_y_slf = (float)gyro_y_slf / 200.0;
		gyro_z_slf = (float)gyro_z_slf / 200.0;

		printConsole(USART1, "Self Test Values : \r\n");
		printConsole(USART1, "ACCL X %f : \r\n",accl_x_slf);
		printConsole(USART1, "ACCL Y %f : \r\n",accl_y_slf);
		printConsole(USART1, "ACCL Z %f : \r\n",accl_z_slf);

		printConsole(USART1, "GYRO X %f : \r\n",gyro_x_slf);
		printConsole(USART1, "GYRO Y %f : \r\n",gyro_y_slf);
		printConsole(USART1, "GYRO Z %f : \r\n",gyro_z_slf);

		//Set Gyroscope Full Scale Range to 500 dps
		I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_CONFIG, 0x08);

		//Set Accelerometer Full Scale Range to 4 G
		I2C_Master_Write_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_CONFIG, 0x08);

		fact_accl_x = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, SELF_TEST_X_ACCEL);
		fact_accl_y = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, SELF_TEST_Y_ACCEL);
		fact_accl_z = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, SELF_TEST_Z_ACCEL);

		fact_gyro_x = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, SELF_TEST_X_GYRO);
		fact_gyro_y = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, SELF_TEST_Y_GYRO);
		fact_gyro_z = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, SELF_TEST_Z_GYRO);

		printConsole(USART1, "Factory Self Test Values : \r\n");
		printConsole(USART1, "ACCL X %f : \r\n",fact_accl_x);
		printConsole(USART1, "ACCL Y %f : \r\n",fact_accl_y);
		printConsole(USART1, "ACCL Z %f : \r\n",fact_accl_z);

		printConsole(USART1, "GYRO X %f : \r\n",fact_gyro_x);
		printConsole(USART1, "GYRO Y %f : \r\n",fact_gyro_y);
		printConsole(USART1, "GYRO Z %f : \r\n",fact_gyro_z);


		fact_trim_accl_x = (float)(2620/1<<1)*(pow( 1.01 , ((float)fact_accl_x - 1.0) ));
		fact_trim_accl_y = (float)(2620/1<<1)*(pow( 1.01 , ((float)fact_accl_y - 1.0) ));
		fact_trim_accl_z = (float)(2620/1<<1)*(pow( 1.01 , ((float)fact_accl_z - 1.0) ));
		fact_trim_gyro_x = (float)(2620/1<<1)*(pow( 1.01 , ((float)fact_gyro_x - 1.0) ));
		fact_trim_gyro_y = (float)(2620/1<<1)*(pow( 1.01 , ((float)fact_gyro_y - 1.0) ));
		fact_trim_gyro_z = (float)(2620/1<<1)*(pow( 1.01 , ((float)fact_gyro_z - 1.0) ));

		printConsole(USART1, "Trim Values : \r\n");
		printConsole(USART1, "ACCL X %f : \r\n",fact_trim_accl_x);
		printConsole(USART1, "ACCL Y %f : \r\n",fact_trim_accl_y);
		printConsole(USART1, "ACCL Z %f : \r\n",fact_trim_accl_z);

		printConsole(USART1, "GYRO X %f : \r\n",fact_trim_gyro_x);
		printConsole(USART1, "GYRO Y %f : \r\n",fact_trim_gyro_y);
		printConsole(USART1, "GYRO Z %f : \r\n",fact_trim_gyro_z);

		percent_accl_x = 100.0*(accl_x_slf - accl_x_avg)/fact_trim_accl_x -  100.0;
		percent_accl_y = 100.0*(accl_y_slf - accl_y_avg)/fact_trim_accl_y -  100.0;
		percent_accl_z = 100.0*(accl_z_slf - accl_z_avg)/fact_trim_accl_z -  100.0;

		percent_gyro_x = 100.0*(gyro_x_slf - gyro_x_avg)/fact_trim_gyro_x -  100.0;
		percent_gyro_y = 100.0*(gyro_y_slf - gyro_y_avg)/fact_trim_gyro_y -  100.0;
		percent_gyro_z = 100.0*(gyro_z_slf - gyro_z_avg)/fact_trim_gyro_z -  100.0;

		printConsole(USART1, "Percentage Difference : \r\n");
		printConsole(USART1, "ACCL X %f : \r\n",percent_accl_x);
		printConsole(USART1, "ACCL Y %f : \r\n",percent_accl_y);
		printConsole(USART1, "ACCL Z %f : \r\n",percent_accl_z);

		printConsole(USART1, "GYRO X %f : \r\n",percent_gyro_x);
		printConsole(USART1, "GYRO Y %f : \r\n",percent_gyro_y);
		printConsole(USART1, "GYRO Z %f : \r\n",percent_gyro_z);
















	}


	void IMU_Get_Data()
	{

		int mag_sens_x , mag_sens_y, mag_sens_z;
		float mag_x, mag_y, mag_z;

/**************************************************************************************************************/

		MPU9250_Accelerometer.X = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_XOUT_H) * 256 + I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_XOUT_L) / 1.0;
		MPU9250_Accelerometer.Y = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_YOUT_H) * 256 + I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_YOUT_L) / 1.0;
		MPU9250_Accelerometer.Z = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_ZOUT_H) * 256 + I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, ACCEL_ZOUT_L) / 1.0;

		MPU9250_Gyroscope.X = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_XOUT_H) * 256 + I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_XOUT_L) / 1.0;
		MPU9250_Gyroscope.Y = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_YOUT_H) * 256 + I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_YOUT_L) / 1.0;
		MPU9250_Gyroscope.Z = I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_ZOUT_H) * 256 + I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, GYRO_ZOUT_L) / 1.0;

/**************************************************************************************************************/
//		mag_sens_x = I2C_Master_Read_Register(MPU9250_I2C_Struct, AK8963_ADDRESS, AK8963_ASAX);
//		mag_sens_y = I2C_Master_Read_Register(MPU9250_I2C_Struct, AK8963_ADDRESS, AK8963_ASAY);
//		mag_sens_z = I2C_Master_Read_Register(MPU9250_I2C_Struct, AK8963_ADDRESS, AK8963_ASAZ);
//
//		mag_x = (float)( (I2C_Master_Read_Register(MPU9250_I2C_Struct, AK8963_ADDRESS, AK8963_XOUT_H) << 8) | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, AK8963_XOUT_L) );
//		mag_y = (float)( (I2C_Master_Read_Register(MPU9250_I2C_Struct, AK8963_ADDRESS, AK8963_YOUT_H) << 8) | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, AK8963_YOUT_L) );
//		mag_z = (float)( (I2C_Master_Read_Register(MPU9250_I2C_Struct, AK8963_ADDRESS, AK8963_ZOUT_H) << 8) | I2C_Master_Read_Register(MPU9250_I2C_Struct, MPU9250_ADDRESS, AK8963_ZOUT_L) );
//
//		MPU9250_Magnetometer.X = mag_x * ( ((mag_sens_x - 128)*0.5)/128 + 1);
//		MPU9250_Magnetometer.Y = mag_x * ( ((mag_sens_y - 128)*0.5)/128 + 1);
//		MPU9250_Magnetometer.Z = mag_x * ( ((mag_sens_z - 128)*0.5)/128 + 1);
/**************************************************************************************************************/

	}
#endif


#if MPU9250_SPI
	void MPU9250_Init();
	void MP9250_Get_Data();
#endif
