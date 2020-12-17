 /******************************************************************************
 *
 * Module: RCC
 *
 * File Name: RCC_Init.h
 *
 * Description: header file for the RCC STM32 ARM Processor driver which has:
 * 				- Necessary Included files
 * 				- preprocessor macros
 * 				- Structures and enumerators used with the program
 * 				- Function Prototypes
 *
 * Date: 2/10/2020
 *
 * Author: Islam Ehab
 *
 * Version: 2.0.1
 *
 * Notes: In next version this driver should have
 * 		- Support of reset feature of the RCC
 * 		- Support of Low Power mode operation of the RCC
 * 		- Backup Domain Services
 * 		- Support of enable the interrupt for Peripherals (with callback functions)
 *		- Support of Clock security system feature of the RCC
 *
 * -------------------- THIS DRIVER TESTED ONCE TILL NOW ------------------------
 *
 * This Driver is made with static configuration to be compatible with
 * STM32F429/07 Kits
 *
 *******************************************************************************/
#ifndef RCC_INIT_H_
#define RCC_INIT_H_

/*********************************************************************************
									Includes
**********************************************************************************/
#include <STD_TYPES_OLD.h>
#include "micro_config.h"
#include "BIT_MATH.h"
#include "RCC_Reg.h"
#include "RCC_Init.h"

/*********************************************************************************
								Preprocessor Macros
*********************************************************************************/
#define HSI_CLOCK_VALUE				(16000000U)
#define HSE_CLOCK_VALUE				(8000000U)

#define OSCILLATOR_TYPE_HSI			(0U)
#define OSCILLATOR_TYPE_HSE			(1U)

#define PLL_STATE_MAIN_OFF			(0U)
#define	PLL_STATE_MAIN_ON			(1U)
#define PLL_STATE_I2S_OFF			(2U)
#define PLL_STATE_I2S_ON			(3U)
#define PLL_STATE_SAI_OFF			(4U)
#define PLL_STATE_SAI_ON			(5U)

#define PLL_SOURCE_HSI				(0U)
#define PLL_SOURCE_HSE				(1U)

#define SYSCLK_SOURCE_HSI			(0U)
#define SYSCLK_SOURCE_HSE			(1U)
#define SYSCLK_SOURCE_PLL			(2U)

#define PLLM_MASKING				(0x3F)
#define PLLM_DEFAULT_VALUE			(0x02)

#define PLLN_MASKING				(0x7FC0)
#define PLLN_DEFAULT_VALUE			(0x02)
#define PLLN_MAX_VALUE				(0x1B0)
#define PLLN_MIN_VALUE				(1U)
#define PLLN_FIRST_BIT				(6U)

#define PLLP_MASKING				(0x00030000)
#define PLLP_VALUE_MASKING			(0x03)
#define PLLP_FIRST_BIT				(16U)

#define PLLP_DEFAULT_VALUE			(0x02)
#define PLLP_FIRST_BIT				(16U)

#define PLLQ_MASKING				(0x0F000000)
#define PLLQ_DEFAULT_VALUE			(0x02)
#define PLLQ_VALUE_MASKING			(0x0F)
#define PLLQ_FIRST_BIT				(24U)


#define PLL_ENABLE_VALUE			(1U)
#define PLL_SOURCE_BIT				(22U)
#define PLL_ENABLE_BIT				(24U)
#define PLL_READY_BIT				(25U)


#define PLLI2S_ENABLE_BIT			(26U)
#define PLLI2S_ENABLE_VALUE			(0x01)
#define PLLI2S_READY_BIT			(27U)

#define PLLSAI_ENABLE_BIT			(28U)
#define PLLSAI_ENABLE_VALUE			(0x01)
#define PLLSAI_READY_BIT			(29U)

#define PLLI2SQ_MASKING				(0xF000000)
#define PLLI2SQ_DEFAULT_VALUE		(0x02)
#define PLLI2SQ_FIRST_BIT			(24U)

#define PLLI2SR_MASIKNG				(0x70000000)
#define PLLI2SR_DEFAULT_VALUE		(0x02)
#define PLLI2SR_FIRST_BIT			(28U)

#define PLLSAIQ_MASKING				(0xF000000)
#define PLLSAIQ_DEFAULT_VALUE		(0x02)
#define PLLSAIQ_FIRST_BIT			(24U)

#define PLLSAIR_MASKING				(0x70000000)
#define PLLSAIR_DEFAULT_VALUE		(0x02)
#define PLLSAIR_FIRST_BIT			(28U)

#define SYSCLK_CLEAR_CLOCK_SOURCE	(0x03)
#define SYSCLK_ENABLE_VALUE			(1U)
#define SYSCLK_FIRST_BIT			(0U)
#define SYSCLK_READY_BIT			(2U)

#define	HCLK_CLEAR					(0xF0)
#define HCLK_ENSURE_DATA			(0x0F)
#define	HCLK_FIRST_BIT				(4U)

#define PCLK1_CLEAR					(0x1C00)
#define PCLK1_FIRST_BIT				(10U)

#define PCLK2_CLEAR					(0xE000)
#define PCLK2_FIRST_BIT				(13U)

#define AHB1_FIRST_NUMBER			(0U)
#define AHB1_LAST_NUMBER			(32U)

#define AHB2_FIRST_NUMBER			(32U)
#define AHB2_LAST_NUMBER			(64U)

#define AHB3_FIRST_NUMBER			(64U)
#define AHB3_LAST_NUMBER			(128U)

#define APB1_FIRST_NUMBER			(128U)
#define APB1_LAST_NUMBER			(160U)

#define APB2_FIRST_NUMBER			(160U)
#define APB2_LAST_NUMBER			(192U)

#define HSI_CLEAR					(0x00)
#define HSI_ENABLE_VALUE			(1U)
#define HSI_FIRST_BIT				(0U)
#define HSI_READY_BIT				(1U)

#define HSE_CLEAR					(0x400000)
#define HSE_ENABLE_VALUE			(1U)
#define HSE_FIRST_BIT				(16U)
#define HSE_READY_BIT				(17U)

#define PLLP_VALUE_2				(0U)
#define PLLP_VALUE_4				(1U)
#define PLLP_VALUE_6				(2U)
#define PLLP_VALUE_8				(3U)

/********************************************************************************

 [Enumuration Name]:		RCC_AHBDivisor

 [Enumuration Description]:	Used as AHB Divisor values

*********************************************************************************/
typedef enum{

	AHB_NOT_DIVIDED,
	AHB_DIVIDED_BY_2 = 8,
	AHB_DIVIDED_BY_4,
	AHB_DIVIDED_BY_8,
	AHB_DIVIDED_BY_16,
	AHB_DIVIDED_BY_64,
	AHB_DIVIDED_BY_128,
	AHB_DIVIDED_BY_256,
	AHB_DIVIDED_BY_512

}RCC_AHBDivisor;


/********************************************************************************

 [Enumuration Name]:		RCC_APBDivisor

 [Enumuration Description]:	Used as APB Divisor values

*********************************************************************************/
typedef enum{

	APB_NOT_DIVIDED,
	APB_DIVIDED_BY_2 = 4,
	APB_DIVIDED_BY_4,
	APB_DIVIDED_BY_8,
	APB_DIVIDED_BY_16,

}RCC_APBDivisor;


/********************************************************************************

 [Enumuration Name]:		RCC_EnableClkPeripherals

 [Enumuration Description]: Used to manage Peripherals positioning on RCC Enable/
 	 	 	 	 	 	 	Disable Clock Registers

 Note: This Enum is Portable for Both STM32F429/07 using static configurations
*********************************************************************************/
typedef enum
{
	/******************************** AHB1 ********************************/
	RCC_GPIOA,				//GPIO A 					 (AHB1)
	RCC_GPIOB,				//GPIO B 					 (AHB1)
	RCC_GPIOC,				//GPIO C 					 (AHB1)
	RCC_GPIOD,				//GPIO D 					 (AHB1)
	RCC_GPIOE,				//GPIO E 					 (AHB1)
	RCC_GPIOF,				//GPIO F 				 	 (AHB1)
	RCC_GPIOG,				//GPIO G 					 (AHB1)
	RCC_GPIOH,				//GPIO H 					 (AHB1)
	RCC_GPIOI,				//GPIO I 					 (AHB1)

			/* These Peripherals are only on STM32F429 */
#ifdef STM32F429
	RCC_GPIOJ,				//GPIO J 					 (AHB1)
	RCC_GPIOK,				//GPIO K 					 (AHB1)
#endif
	RCC_CRC = 12,			//CRC						 (AHB1)
	RCC_BKPSRAM = 18,		//Backup SRAM Interface 	 (AHB1)
	RCC_CCMDATARAM = 20,	//CCM Data RAM				 (AHB1)
	RCC_DMA1,				//DMA 1						 (AHB1)
	RCC_DMA2,				//DMA 2						 (AHB1)

			/* This Peripheral is only on STM32F429 */
#ifdef STM32F429
	RCC_DMA2D,				//DMA 2D 					 (AHB1)
#endif
	RCC_ETHMAC =25,			//Ethernet MAC				 (AHB1)
	RCC_ETHMACTX,			//Ethernet Transmission		 (AHB1)
	RCC_ETHMACRX,			//Ethernet Reception		 (AHB1)
	RCC_ETHMACPTP,			//Ethernet PTP			   	 (AHB1)
	RCC_OTGHS,				//USB OTG HS				 (AHB1)
	RCC_OTGHSULPI,			//USB OTG HSULPI			 (AHB1)

	/******************************** AHB2 ********************************/
	RCC_DCMI = 32,			//Camera Interface 			 (AHB2)
	RCC_CRYP = 36,			//Cryptographic Modules		 (AHB2)
	RCC_HASH,				//Hash Modules 				 (AHB2)
	RCC_RNG,				//Random Number Generator 	 (AHB2)
	RCC_OTGFS,				//USB OTG FS				 (AHB2)

	/******************************** AHB3 ********************************/
	RCC_FMCEN = 64,			//Flexible Memory Controller (AHB3)

	/******************************** APB1 ********************************/
	RCC_TIM2  = 128,		//TIMER 2					 (APB1)
	RCC_TIM3,				//TIMER 3					 (APB1)
	RCC_TIM4,				//TIMER 4					 (APB1)
	RCC_TIM5,				//TIMER 5					 (APB1)
	RCC_TIM6,				//TIMER 6					 (APB1)
	RCC_TIM7,				//TIMER 7					 (APB1)
	RCC_TIM12,				//TIMER 12					 (APB1)
	RCC_TIM13,				//TIMER 13					 (APB1)
	RCC_TIM14,				//TIMER 14					 (APB1)
	RCC_WWDG = 139,			//WatchDog Timer			 (APB1)
	RCC_SPI2 = 142,			//SPI 2						 (APB1)
	RCC_SPI3,				//SPI 3						 (APB1)
	RCC_USART2 = 145,		//USART 2					 (APB1)
	RCC_USART3,				//USART 3					 (APB1)
	RCC_USART4,				//USART 4					 (APB1)
	RCC_USART5,				//USART 5					 (APB1)
	RCC_I2C1,				//I2C 1						 (APB1)
	RCC_I2C2,				//I2C 2						 (APB1)
	RCC_I2C3,				//I2C 3						 (APB1)
	RCC_CAN1 = 153,			//CAN 1						 (APB1)
	RCC_CAN2,				//CAN 2						 (APB1)
	RCC_PWR = 156,			//Power Interface 			 (APB1)
	RCC_DAC,				//DAC						 (APB1)

			/* These Peripherals are only on STM32F429 */
#ifdef STM32F429
	RCC_UART7,				//UART 7					 (APB1)
	RCC_UART8,				//UART 8					 (APB1)
#endif

	/******************************** APB2 ********************************/
	RCC_TIM1 = 160,				//TIMER 1					 (APB1)
	RCC_TIM8,				//TIMER 8					 (APB1)
	RCC_USART1 = 164,		//USART 1					 (APB1)
	RCC_USART6,				//USART 6					 (APB1)
	RCC_ADC1   = 168,		//ADC 1  					 (APB1)
	RCC_ADC2,				//ADC 2  					 (APB1)
	RCC_ADC3,				//ADC 3  					 (APB1)
	RCC_SDIO,				//SDIO   					 (APB1)
	RCC_SPI1,				//SPI 1  					 (APB1)

			/* This Peripheral is only on STM32F429 */
#ifdef STM32F429
	RCC_SPI4,				//SPI 4  					 (APB1)
#endif
	RCC_SYSCFG,				//System Configuration Clock (APB1)
	RCC_TIM9 = 176,			//TIMER 9					 (APB1)
	RCC_TIM10,				//TIMER 10					 (APB1)
	RCC_TM11,				//TIMER 11					 (APB1)

			/* These Peripherals are only on STM32F429 */
#ifdef STM32F429
	RCC_SPI5 = 180,			//SPI 5  					 (APB1)
	RCC_SPI6,				//SPI6					     (APB1)
	RCC_SAI1,				//SAI1   					 (APB1)
	RCC_LTDC = 186			//LCD TFT				     (APB1)
#endif

}RCC_EnableClkPeripherals;


/********************************************************************************

 [Enumuration Name]:		RCC_ResetPeriperhal

 [Enumuration Description]: Used to manage Peripherals positioning on RCC
 	 	 	 	 	 	 	Reset Registers

 Note: This Enum is Portable for Both STM32F429/07 using static configurations
*********************************************************************************/
typedef enum{

	/******************************** AHB1 ********************************/
	RCC_GPIOA_RESET,				//GPIO A 					 (AHB1)
	RCC_GPIOB_RESET,				//GPIO B 					 (AHB1)
	RCC_GPIOC_RESET,				//GPIO C 					 (AHB1)
	RCC_GPIOD_RESET,				//GPIO D 					 (AHB1)
	RCC_GPIOE_RESET,				//GPIO E 					 (AHB1)
	RCC_GPIOF_RESET,				//GPIO F 				 	 (AHB1)
	RCC_GPIOG_RESET,				//GPIO G 					 (AHB1)
	RCC_GPIOH_RESET,				//GPIO H 					 (AHB1)
	RCC_GPIOI_RESET,				//GPIO I 					 (AHB1)

				/* These Peripherals are only on STM32F429 */
#ifdef STM32F429
	RCC_GPIOJ_RESET,				//GPIO J 					 (AHB1)
	RCC_GPIOK_RESET,				//GPIO K 					 (AHB1)
#endif
	RCC_CRC_RESET = 12,				//CRC						 (AHB1)
	RCC_DMA1_RESET = 21,			//DMA 1						 (AHB1)
	RCC_DMA2_RESET,					//DMA 2						 (AHB1)

				/* This Peripherals is only on STM32F429 */
#ifdef STM32F429
	RCC_DMA2D_RESET,				//DMA 2D 					 (AHB1)
#endif

	RCC_ETHMAC_RESET = 25,			//Ethernet MAC				 (AHB1)
	RCC_OTGHS_RESET = 29,			//USB OTG HS				 (AHB1)

	/******************************** AHB2 ********************************/
	RCC_DCMI_RESET = 32,			//Camera Interface 			 (AHB2)
	RCC_CRYP_RESET = 36,			//Cryptographic Modules		 (AHB2)
	RCC_HASH_RESET,					//Hash Modules 				 (AHB2)
	RCC_RNG_RESET,					//Random Number Generator 	 (AHB2)
	RCC_OTGFS_RESET,				//USB OTG FS				 (AHB2)

	/******************************** AHB3 ********************************/
	RCC_FMCEN_RESET = 64,			//Flexible Memory Controller (AHB3)

	/******************************** APB1 ********************************/
	RCC_TIM2_RESET  = 128,			//TIMER 2					 (APB1)
	RCC_TIM3_RESET,					//TIMER 3					 (APB1)
	RCC_TIM4_RESET,					//TIMER 4					 (APB1)
	RCC_TIM5_RESET,					//TIMER 5					 (APB1)
	RCC_TIM6_RESET,					//TIMER 6					 (APB1)
	RCC_TIM7_RESET,					//TIMER 7					 (APB1)
	RCC_TIM12_RESET,				//TIMER 12					 (APB1)
	RCC_TIM13_RESET,				//TIMER 13					 (APB1)
	RCC_TIM14_RESET,				//TIMER 14					 (APB1)
	RCC_WWDG_RESET= 139,			//WatchDog Timer			 (APB1)
	RCC_SPI2_RESET = 142,			//SPI 2						 (APB1)
	RCC_SPI3_RESET,					//SPI 3						 (APB1)
	RCC_USART2_RESET = 145,			//USART 2					 (APB1)
	RCC_USART3_RESET,				//USART 3					 (APB1)
	RCC_USART4_RESET,				//USART 4					 (APB1)
	RCC_USART5_RESET,				//USART 5					 (APB1)
	RCC_I2C1_RESET,					//I2C 1						 (APB1)
	RCC_I2C2_RESET,					//I2C 2						 (APB1)
	RCC_I2C3_RESET,					//I2C 3						 (APB1)
	RCC_CAN1_RESET = 153,			//CAN 1						 (APB1)
	RCC_CAN2_RESET,					//CAN 2						 (APB1)
	RCC_PWR_RESET = 156,			//Power Interface 			 (APB1)
	RCC_DAC_RESET,					//DAC						 (APB1)

				/* These Peripherals are only on STM32F429 */
#ifdef STM32F429
	RCC_UART7_RESET,				//UART 7					 (APB1)
	RCC_UART8_RESET,				//UART 8					 (APB1)
#endif

	/******************************** APB2 ********************************/
	RCC_TIM1_RESET = 160,			//TIMER 1					 (APB2)
	RCC_TIM8_RESET,					//TIMER 8					 (APB2)
	RCC_USART1_RESET = 164,			//USART 1					 (APB2)
	RCC_USART6_RESET,				//USART 6					 (APB2)
	RCC_ADC_RESET    = 168,			//ADC 1  					 (APB2)
	RCC_SDIO_RESET	 = 171,			//SDIO   					 (APB2)
	RCC_SPI1_RESET,					//SPI 1  					 (APB2)

				/* This Peripherals is only on STM32F429 */
#ifdef STM32F429
	RCC_SPI4_RESET,					//SPI 4  					 (APB2)
#endif
	RCC_SYSCFG_RESET,				//System Configuration Clock (APB2)
	RCC_TIM9_RESET = 176,			//TIMER 9					 (APB2)
	RCC_TIM10_RESET,				//TIMER 10					 (APB2)
	RCC_TM11_RESET,					//TIMER 11					 (APB2)

				/* These Peripherals are only on STM32F429 */
#ifdef STM32F429
	RCC_SPI5_RESET = 180,			//SPI 5  					 (APB2)
	RCC_SPI6_RESET,					//SPI6					     (APB2)
	RCC_SAI1_RESET,					//SAI1   					 (APB2)
	RCC_LTDC_RESET = 186			//LCD TFT				     (APB2)
#endif
}RCC_ResetPeriperhal;


/********************************************************************************

 [Structure Name]:			RCC_PLL_config

 [Structure Description]:	Used to handle PLL Configuration and multipliers

*********************************************************************************/
typedef struct{

	u8		PLLStateMain;					/* You can find this parameter @PLL_STATE_MAIN
	 	 	 	 	 	 	 	 	 	 	   Used to know if Main PLL is enabled or not */

	u8 		PLLStateI2S;					/* You can find this parameter @PLL_STATE_I2S
	 	 	 	 	 	 	 	 	 	 	   Used to know if I2S PLL is enabled or not */

	/************************* PLL SAI is only available on STM32F429 ***************************/
#ifdef STM32F429
	u8		PLLStateSAI;					/* You can find this parameter @PLL_STATE_SAI
	 	 	 	 	 	 	 	 	 	 	   Used to know if SAI PLL is enabled or not */
#endif
	/********************************************************************************************/

	u8		PLLSource;						/* You can find this parameter @PLL_SOURCE
	 	 	 	 	 	 	 	 	 	 	   Used to know which clock is used as source
	 	 	 	 	 	 	 	 	 	 	   clock for PLL Engine */

	u8		PLLM;							/* Value of PLLM which is used in main PLL
											   this value should be set in the main program
	 	 	 	 	 	 	 	 	 	 	   Note: PLLM = 0 or 1 is a wrong configuration */

	u8		PLLP;							/* You can find this parameter @PLLP_VALUE
											   Value of PLLP which is used in main PLL
											   this value should be set in the main program
	 	 	 	 	 	 	 	 	 	 	   Note: PLLP should equal 2 or 4 or 6 or 8 */

	u8		PLLQ;							/* Value of PLLP which is used in main PLL
											   this value should be set in the main program
	 	 	 	 	 	 	 	 	 	 	   Note: PLLQ = 0 or 1 is a wrong configuration */

	u8		PLLI2SR;						/* Value of PLLI2SR which is used in PLL I2S
	 	 	 	 	 	 	 	 	 	 	   this value should be set on the main program
	 	 	 	 	 	 	 	 	 	 	   Note: This value should be from 2 till 7 */

	/************************* PLL SAI is only available on STM32F429 ***************************/
#ifdef STM32F429

	u8		PLLI2SQ;						/* Value of PLLI2SQ which is used in PLL SAI1 Clock
	 	 	 	 	 	 	 	 	 	 	   this value should be set on the main program
	 	 	 	 	 	 	 	 	 	 	   Note: This value should be from 2 till 15 */

	u8		PLLSAIQ;						/* Value of PLLSAIQ which is used in PLL SAI1
	 	 	 	 	 	 	 	 	 	 	   this value should be set on the main program
	 	 	 	 	 	 	 	 	 	 	   Note: This value should be from 2 till 15 */

	u8		PLLSAIR;						/* Value of PLLSAIR which is used in PLL SAI1
	 	 	 	 	 	 	 	 	 	 	   this value should be set on the main program
	 	 	 	 	 	 	 	 	 	 	   Note: This value should be from 2 till 7 */
#endif
	/********************************************************************************************/

	u16		PLLN;							/* Value of PLLN which is used in main PLL
											   this value should be set in the main program
	 	 	 	 	 	 	 	 	 	 	   Note: PLLN = 0 or 1 or from 433 till 511
	 	 	 	 	 	 	 	 	 	 	   is a wrong configuration */

	u16		PLLI2SN;						/* Value of PLLI2SN which is used in PLL I2S
	 	 	 	 	 	 	 	 	 	 	   this value should be set on the main program
	 	 	 	 	 	 	 	 	 	 	   Note: PLLI2SN =0 or 1 or from 433 till 511
	 	 	 	 	 	 	 	 	 	 	   is a wrong configuration */

	/************************* PLL SAI is only available on STM32F429 ***************************/
#ifdef STM32F429
	u16		PLLSAIN;						/* Value of PLLSAIN: which is used in PLL SAI1
	 	 	 	 	 	 	 	 	 	 	   this value should be set on the main program
	 	 	 	 	 	 	 	 	 	 	   Note: PLLI2SN =0 or 1 or from 433 till 511
	 	 	 	 	 	 	 	 	 	 	   is a wrong configuration */
#endif
	/********************************************************************************************/

}RCC_PLL_config;


/********************************************************************************

 [Structure Name]:			RCC_config

 [Structure Description]:	Used to hold RCC Configurations:
 	 	 	 	 	 	 	- Main Oscillator type (HSE or HSI)
 	 	 	 	 	 	 	- Sysclck source (HSE, HSI or PLL)
 	 	 	 	 	 	 	- Buses Divisors
 	 	 	 	 	 	 	- PLL Configurations

*********************************************************************************/
typedef struct{

	u8					OscillatorType;		/* You can find this parameter @OSCILLATOR_TYPE
	 	 	 	 	 	 	 	 	 	 	   Used to decide which Oscillator will be used
	 	 	 	 	 	 	 	 	 	 	   (Internal RC Circuit 16MHz or
	 	 	 	 	 	 	 	 	 	 	   External Oscillator 8MHz */

	u8					SYSCLKSource;		/* You can find this parameter @SYSCLK_SOURCE
	 	 	 	 	 	 	 	 	 	 	   Used to decide which clock used as SYSCLK
	 	 	 	 	 	 	 	 	 	 	   (HSI , HSE or PLL) */


	RCC_AHBDivisor		AHBDivisor;			/* You can find this parameter @RCC_AHBDivisor
	 	 	 	 	 	 	 	 	 	 	   Used to decide what is AHB Divisor */



	RCC_APBDivisor 		APB1Divisor;		/* You can find this parameter @RCC_APBDivisor
	 	 	 	 	 	 	 	 	 	 	   Used to decide what is APB1 Divisor
	 	 	 	 	 	 	 	 	 	 	   Note: in STM32F429, APB1 Max value = 45MHz
	 	 	 	 	 	 	 	 	 	 	   but,  in STM32F407, APB1 Max value = 42 MHz */


	RCC_APBDivisor 		APB2Divisor;		/* You can find this parameter @RCC_APBDivisor
	 	 	 	 	 	 	 	 	 	 	   Used to decide what is APB2 Divisor
	 	 	 	 	 	 	 	 	 	 	   Note: in STM32F429, APB2 Max value = 90 MHz
	 	 	 	 	 	 	 	 	 	 	   but,  in STM32F407, APB2 Max value = 84 MHz */


	RCC_PLL_config		PLL;				/* Used to Set PLL Configurations */


}RCC_config;


/********************************************************************************

 [Structure Name]:			RCC_clockValues

 [Structure Description]:	Used to save clock values when xRCC_getClocks()
 	 	 	 	 	 	 	called

*********************************************************************************/
typedef struct{

	u32		SYSCLKFrequency;

	u32		HCLKFrequency;

	u32		PCLK1Frequency;

	u32		PCLK2Frequency;

}RCC_clockValues;

/*********************************************************************************
							Function Prototypes
*********************************************************************************/
Return_status xRCC_regInit(void);
Return_status xRCC_init(const RCC_config * config_Ptr);
Return_status xRCC_getClocks(RCC_clockValues * rcc_Clocks);
Return_status xRCC_EnableClock(u8 u8Peripheral);
Return_status xRCC_DisableClock(u8 u8Peripheral);



#endif /* RCC_INIT_H_ */
