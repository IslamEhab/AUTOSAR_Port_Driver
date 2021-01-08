/******************************************************************************
 *
 * Module: 		Test Module for Dio & Port drivers
 *
 * File Name: 	main.c
 *
 * Description: Source file for testing Dio & Port Drivers
 *
 * Author: 		Islam Ehab
 *
 * Date:		16/12/2020
 ******************************************************************************/

/*******************************************************************************
 * @file:	main.c
 *
 * @brief:	Source file for testing Dio & Port Drivers
 *
 * @author:	Islam Ehab
 *
 * @date:	16/12/2020
 ******************************************************************************/


/*******************************************************************************
 * 								Includes Required							   *
 *******************************************************************************/
#include "main.h"

/*******************************************************************************
 * 								Global Variable used						   *
 *******************************************************************************/
RCC_clockValues				clock_values 		= {0};				/* RCC Clock Structure 							  */
USART_Config 				husart				= {0};				/* USART Configuration structure				  */


/********************************************************************************
 * 							Static Function Definition							*
 ********************************************************************************/
static void Hardware_Init(void);
static void USART_Configuration(void);
/********************************************************************************/
/**
 * @fn	main function
 */
int main (void)
{
	/* Variable used as Flag to check debouncing */
	uint8 flag = 0;

	uint8 test;
	/* Initialize HW (Clocks, Clocks for GPIO Ports & USART Used) */
	Hardware_Init();

	/* Port Initialization */
	Port_Init(&Port_Configuration);

	/* USARTS Initialization */
	USART_Configuration();

	/* Testing USART1 */
	vidUSART_SendString(USART1, (u8*)"Hello", 6);

	/* Test Dio_WriteChannel With PG13 */
	Dio_WriteChannel(DioConf_LED2_CHANNEL_ID_INDEX, STD_HIGH);


	while(1)
	{
		/* Test Dio_ReadChannel With PA0  */
		if(Dio_ReadChannel(DioConf_SW1_CHANNEL_ID_INDEX))
		{
			/* Denouncing Delay */
			_delay_ms(50);

			/* Check again for Button Pressing */
			if(Dio_ReadChannel(DioConf_SW1_CHANNEL_ID_INDEX))
			{

				/* Test Dio_WriteChannel With PG14 */
				//Dio_WriteChannel(DioConf_LED2_CHANNEL_ID_INDEX, STD_HIGH);

				/* Test Writing Low in Dio_WriteChannel with PG13 */
				//Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX, STD_LOW);

				if(flag == 0)
				{
					/* Test Flip Channel API */
					Dio_FlipChannel(DioConf_LED1_CHANNEL_ID_INDEX);

					/* Test Flip Channel API */
					Dio_FlipChannel(DioConf_LED2_CHANNEL_ID_INDEX);

					flag = 1;
				}

			}
		}
		else
		{
			flag = 0;

		}

	}
}

/*********************************************************************************************
 [Function Name]:	Hardware_Init
 [Description]:		Function to initiate Peripheral used:
 	 	 	 	 	- RCC			- NVIC		- SYSTICK 		- GPIO
 	 	 	 	 	- Enable Clock for GPIOA & GPIOB
 	 	 	 	 	- Enable Clock for USART2 & 3
 [Args]:			None
 [in]				None
 [out]				None
 [in/out]			None
 [Returns]:			None
 **********************************************************************************************/

/**
 * @fn 		static void Hardware_Init(void)
 * @brief	Function to initiate Peripheral used:
 *	 	 	- RCC			- GPIO
 *	 	 	- Enable Clock for GPIOA & GPIOC & GPIOG
 *	 	 	- Enable Clock for USART1, 2 & 4
 *
 */
static void Hardware_Init(void)
{
	/* RCC Configuration structure */
	RCC_config rcc_configurations = {0};

	/*------------------------ RCC Clock Configurations ------------------*/
	/*********************************************************************
	 * - HSE used as a main oscillator 	 								 *
	 * - By using PLL, SYSCLK = 72 MHz									 *
	 * - SYSCLK Source is PLL											 *
	 * - AHB  Clock = SYSCLK											 *
	 * - APB1 Clock = AHB Clock / 2									     *
	 * - APB2 Clock = AHB Clock									         *
	 *********************************************************************/
	rcc_configurations.OscillatorType 	= OSCILLATOR_TYPE_HSE;
	rcc_configurations.SYSCLKSource		= SYSCLK_SOURCE_PLL;
	rcc_configurations.AHBDivisor		= AHB_NOT_DIVIDED;
	rcc_configurations.APB1Divisor		= APB_DIVIDED_BY_2;
	rcc_configurations.APB2Divisor		= APB_NOT_DIVIDED;
	rcc_configurations.PLL.PLLStateMain	= PLL_STATE_MAIN_ON;

	rcc_configurations.PLL.PLLSource	= PLL_SOURCE_HSE;
	rcc_configurations.PLL.PLLM			= 4;
	rcc_configurations.PLL.PLLN			= 80;
	rcc_configurations.PLL.PLLP			= PLLP_VALUE_2;
	rcc_configurations.PLL.PLLQ			= 3;
	/*---------------------------------------------------------------------*/

	/* Initialize Registers */
	xRCC_regInit();

	/* Initialize RCC & Config PLLs */
	xRCC_init(&rcc_configurations);

	/* Get Clock Values */
	xRCC_getClocks(&clock_values);

	/* Initialize SYSTICK with Freq - 1 (Step) */
	vidSYSTICK_Init(( (clock_values.SYSCLKFrequency) / 1000) );

	/* Enable GPIOA Clock (For USART2) */
	xRCC_EnableClock(RCC_GPIOA);

	/* Enable GPIOC Clock (For UART4)*/
	xRCC_EnableClock(RCC_GPIOC);

	/* Enable GPIOG Clock for F429 on board Kits LEDs */
	xRCC_EnableClock(RCC_GPIOG);

	/* Enable USART1 Clock */
	xRCC_EnableClock(RCC_USART1);

	/* Enable USART2 Clock */
	xRCC_EnableClock(RCC_USART2);

	/* Enable USART3 Clock */
	xRCC_EnableClock(RCC_USART3);

	/* Enable USART6 Clock */
	xRCC_EnableClock(RCC_USART4);

}

/*********************************************************************************************
 [Function Name]:	USART_Configuration
 [Description]:		Function to Configure USART2 & 3
 	 	 	 	 	- Parity bit disables
 	 	 	 	 	- No Oversampling 	(Default of UART)
 	 	 	 	 	- Data Length 8 bit (Default of UART)
 	 	 	 	 	- Stop Bit = 1		(Default of UART)
 	 	 	 	 	- Enable Receiver & Transmitter
 	 	 	 	 	- BaudRate = 115200
 [Args]:			None
 [in]				None
 [out]				None
 [in/out]			None
 [Returns]:			None
 **********************************************************************************************/
static void USART_Configuration(void)
{

	/* works on APB2 Clock = 72 MHz */
	husart.Parity   		= NO;
	husart.OverSampling		= NO;
	husart.WordLength 		= Data_Bits_8;
	husart.StopBit			= One_Bit;
	husart.Mode				= (Receiver | Transmitter);
	//husart.BaudRate 		= 0x271;	/* Baud Rate Calculations with APB2 = 72 MHz */
	husart.BaudRate 		= 0x2B7;	/* Baud Rate Calculations with APB2 = 80 MHz */

	vidUSART_Init(USART1, &husart);


	/* USART6 Configurations */
	husart.Parity   		= NO;
	husart.OverSampling		= NO;
	husart.WordLength 		= Data_Bits_8;
	husart.StopBit			= One_Bit;
	husart.Mode				= (Receiver | Transmitter);
	//husart.BaudRate 		= 0x271;	/* Baud Rate Calculations with APB2 = 72 MHz */
	husart.BaudRate 		= 0x15C;	/* Baud Rate Calculations with APB1 = 40 MHz */
	/* Set USART6 with same Configurations */
	vidUSART_Init(UART4, &husart);

}
