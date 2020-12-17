 /******************************************************************************
 *
 * Module: RCC
 *
 * File Name: RCC_Prog.c
 *
 * Description: source file for the RCC STM32 ARM Processor driver
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



#include "RCC_Init.h"

/********************************************************************************
								PLL Clock Calculations
	Main Pll:
		F(VCO) 			  = F(PLL Clock Source) * (PLLN / PLLM)
		F(Main PLL) 	  = F(VCO) / PLLP
		F(USB, SDIO, RNG) = F(VCO) / PLLQ

	PLL I2S:
		F(VCO)			  = F(PLL I2S Clock Source) * (PLLI2SN / PLLM)
		F(PLL I2S)		  = F(VCO) / PLLI2SR

	PLL SAI:
		F(VCO) 			  = F(PLL SAI Clock Source) * (PLLSAIN / PLLM)
		F(PLL SAI1) 	  = F(VCO) / PLLSAIQ (which is PLLI2SQ in PLL struct)
		F(PLL LCD)		  = F(VCO) / PLLSAIR

*********************************************************************************/

/***********************************************************************************
					Notes for portability of code between 2 kits

	-------------------------------------------------------------------------------
	|			STM32F429				  |				STM32F407				  |
	-------------------------------------------------------------------------------
	| 	-	PCLK1 (F(APB1)) <= 45MHz 	  |		-	PCLK1 (F(APB1)) <= 42MHz	  |
	-------------------------------------------------------------------------------
	|	-	PCLK2 (F(APB2)) <= 90MHz 	  |		-	PCLK2 (F(APB2)) <= 84MHz	  |
	-------------------------------------------------------------------------------
	|			PLLSAI Available		  |			PLLSAI Not Available		  |
	|									  |									  	  |
	|									  |									  	  |
	|									  |									      |
	|									  |									  	  |
	|									  |									      |
	|									  | 									  |

***********************************************************************************/

/********************************************************************************
 	 	 	 	 	 	 	 Private Public Variables
*********************************************************************************/

/* Used to hold AHB Presalers */
static volatile u8 g_busesPreScaler[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

/*********************************************************************************


*********************************************************************************
								Function Definitions
********************************************************************************/

/**********************************************************************************
 [Function Name]:	xRCC_regInit
 [Description]:		Used to initialize registers with its reset values
 [Args]:			None
 [in]				None
 [out]				None
 [in/out]			None
 [Returns]:			Retrun Status (OK if everything is okay)
**********************************************************************************/
Return_status xRCC_regInit(void){

	RCC -> CR 			= 0x00000083;
	RCC -> PLLCFGR		= 0x24003010;
	RCC -> CFGR			= 0x00000000;
	RCC -> CIR			= 0x00000000;
	RCC -> AHB1RSTR		= 0x00000000;
	RCC -> AHB2RSTR		= 0x00000000;
	RCC -> AHB3RSTR		= 0x00000000;
	RCC -> APB1RSTR		= 0x00000000;
	RCC -> APB2RSTR		= 0x00000000;
	RCC -> AHB1ENR		= 0x00100000;
	RCC -> AHB2ENR		= 0x00000000;
	RCC -> AHB3ENR		= 0x00000000;
	RCC -> APB1ENR		= 0x00000000;
	RCC -> APB2ENR		= 0x00000000;
	RCC -> AHB1LPENR	= 0x7EEF97FF;
	RCC -> AHB2LPENR	= 0x000000F1;
	RCC -> AHB3LPENR	= 0x00000001;
	RCC -> APB1LPENR	= 0xF6FEC9FF;
	RCC -> APB2LPENR	= 0x04777F33;
	RCC -> BDCR			= 0x00000000;
	RCC -> CSR			= 0x0E000000;
	RCC -> SSCGR		= 0x00000000;
	RCC -> PLLI2SCFGR	= 0x24003000;
	RCC -> PLLSAICFGR	= 0x24003000;
	RCC -> DCKCFGR		= 0x00000000;

	return OK;
}

/********************************************************************************
 [Function Name]:	xRCC_init
 [Description]:		Used to initialize RCC Peripheral with programmer configuration
 	 	 	 	 	- Clock Source (HSI, HSE)
 	 	 	 	 	- PLL State (On, OFF)
 	 	 	 	 	- PLL Calculations
 	 	 	 	 	- SYSCLK Source clock
 	 	 	 	 	- HCLK, PCLK1, PCLK2 Divisors

 [Args]:			config_Ptr

 [in]				config_Ptr: Pointer to RCC_config const structure to configure RCC

 [out]				None

 [in/out]			None

 [Returns]:			Retrun Status (OK if everything is okay)
**********************************************************************************/
Return_status xRCC_init(const RCC_config * config_Ptr){

	/* At first enable HSI Clock */
	RCC -> CR = ((RCC -> CR & (~(HSI_CLEAR)) ) | (HSI_ENABLE_VALUE << HSI_FIRST_BIT));

	/* Wait till HSI is Ready */
	while( BIT_IS_CLEAR( (RCC -> CR), HSI_READY_BIT) );

	/* Choose what is oscillator type */
	if(config_Ptr -> OscillatorType == OSCILLATOR_TYPE_HSE){
		/* HSE Chosed as the main oscillator */

		/* clear HSE Enable bit first then Enable it */
		RCC -> CR = ((RCC -> CR & (~(HSE_CLEAR))) | (HSE_ENABLE_VALUE << HSE_FIRST_BIT) );

		/* wait till HSE is Ready */
		while( BIT_IS_CLEAR((RCC -> CR), HSE_READY_BIT) );

		/* Clear SYSCLK Bits then Set SYSCLK with HSE Clock */
		RCC -> CFGR = ( (RCC -> CFGR & (~(SYSCLK_CLEAR_CLOCK_SOURCE))) | (SYSCLK_ENABLE_VALUE << SYSCLK_FIRST_BIT) );

		/* Wait till SYSCLK is Ready */
		while( BIT_IS_CLEAR((RCC -> CFGR) , SYSCLK_READY_BIT) );

		/*------------------------- Disable all PLLs ------------------------*/

		/* Disable Main PLL */
		RCC -> CR &= (~( PLL_ENABLE_VALUE << PLL_ENABLE_BIT) );

		/*Disable I2S PLL */
		RCC -> CR &= (~( PLLI2S_ENABLE_VALUE << PLLI2S_ENABLE_BIT ) );

		/* PLL SAI only available on STM32F429 */
#ifdef STM32F429
		/* Disable SAI PLL */
		RCC -> CR &= (~( PLLSAI_ENABLE_VALUE << PLLSAI_ENABLE_VALUE) );
#endif

	}
		/*--------------------- Put PLL Configurations ---------------------*/

	/* Check if PLL is needed to be enabled or not */
	if(config_Ptr -> PLL.PLLStateMain == PLL_STATE_MAIN_ON){
		/* Main PLL Configurations */

		/*
		 * Clear PLLM then Put it (From Bit 0 till bit 5)
		 * Max Value = 63 (0x3F)
		 * PLLM = 0 or 1 is wrong
		*/

		/* check if PLLM = 0 or 1 because it is a wrong configuration */
		if( ((config_Ptr->PLL.PLLM) & (PLLM_MASKING)) < 1 ){
			/* Put PLLM = 2 */
			RCC -> PLLCFGR = ( ((RCC -> PLLCFGR) & (~(PLLM_MASKING)) ) |  PLLM_DEFAULT_VALUE );
		}

		else{
			/* PLLM given is > 1 */
			RCC -> PLLCFGR = ( ((RCC -> PLLCFGR) & (~(PLLM_MASKING)) ) | ( (config_Ptr -> PLL.PLLM) & (PLLM_MASKING)) );
		}

		/* check if PLLN = 0 or 1 because it is a wrong configuration */
		if( ( (config_Ptr -> PLL.PLLN) < PLLN_MIN_VALUE ) ){
			/* Put PLLN = 2 */
			RCC -> PLLCFGR = ( ((RCC -> PLLCFGR) & (~(PLLN_MASKING)) ) |  (PLLN_DEFAULT_VALUE << PLLN_FIRST_BIT) );
		}
		/* Check if PLLM > 432 because it is a wrong configuration */
		if( ( (config_Ptr -> PLL.PLLN) > PLLN_MAX_VALUE )  ) {

			/*
			 * PLLN Given is in the proper margins
			 * Clear PLLN then Put it (From Bit 6 till bit 14)
			 * PLLN = 0 or 1 or from 433 till 511 is a wrong configuration
			 * so, max value = 432 (0x1B0)
			*/
			RCC -> PLLCFGR = ( ((RCC -> PLLCFGR) & (~(PLLN_MASKING)) ) |  (PLLN_MAX_VALUE << PLLN_FIRST_BIT) );
		}
		else{
			/*
			 * PLLN Given is in the proper margins
			 * Clear PLLN then Put it (From Bit 6 till bit 14)
			 * PLLN = 0 or 1 or from 433 till 511 is a wrong configuration
			 * so, max value = 432 (0x1B0)
			 * Put PLLN = 432
			*/
			RCC -> PLLCFGR = ( ((RCC -> PLLCFGR) & (~(PLLN_MASKING)) ) |  ( (config_Ptr -> PLL.PLLN) << PLLN_FIRST_BIT) );
		}

		 /*
		  * Clear PLLP then Put it (Bits 16 and 17)
		 */
			RCC -> PLLCFGR = ( ((RCC -> PLLCFGR) & (~(PLLP_MASKING)) ) |  ( ( (config_Ptr -> PLL.PLLP) ) << PLLP_FIRST_BIT) );

		/* check if PLLQ = 0 or 1 because it is a wrong configuration */
		if( ( (config_Ptr -> PLL.PLLQ) < 1 ) ){
			/*
			 * Clear PLLQ then Put it (From bit 24 till 27)
			 * Put PLLQ = 2
			*/
			RCC -> PLLCFGR = ( ((RCC -> PLLCFGR) & (~(PLLQ_MASKING)) ) |  (PLLQ_DEFAULT_VALUE << PLLQ_FIRST_BIT) );
		}
		else{
			/*
			 * PLLQ Given is in the proper margins
			 * Clear PLLQ then Put it (From Bit 24 till bit 27)
			*/
			RCC -> PLLCFGR = ( ((RCC -> PLLCFGR) & (~(PLLQ_MASKING)) ) |  ( ( (config_Ptr -> PLL.PLLQ) << PLLQ_FIRST_BIT) & (PLLQ_MASKING) ) );

		}

		/* Choose Main PLL & PLL I2S entry clock source */
		if( (config_Ptr -> OscillatorType == OSCILLATOR_TYPE_HSE) && ( (config_Ptr -> PLL.PLLSource) == PLL_SOURCE_HSE)  )
		{
			/* clear choosing bit then choose HSE as main PLL & I2S PLL entry clock */
			RCC -> PLLCFGR = ( ( (RCC -> PLLCFGR) & (~(PLL_SOURCE_HSE << PLL_SOURCE_BIT) ) ) | (PLL_SOURCE_HSE << PLL_SOURCE_BIT) );
		}
		else
		{
			/* clear choosing bit which means choose HSI as main PLL & I2S PLL entry clock */
			RCC -> PLLCFGR = (  (RCC -> PLLCFGR) & (~(PLL_SOURCE_HSE << PLL_SOURCE_BIT) ) );
		}

		/* Clear enabling bit of PLL then Enable the Main PLL Engine */
		RCC -> CR = ( ( (RCC -> CR) & (~(PLL_STATE_MAIN_ON << PLL_ENABLE_BIT) ) ) | (PLL_STATE_MAIN_ON << PLL_ENABLE_BIT) );

		/* Wait till PLL is Ready */
		while( BIT_IS_CLEAR( (RCC -> CR), PLL_READY_BIT) );

		/* Check if PLL I2S is needed or not */
		if(config_Ptr -> PLL.PLLStateI2S == PLL_STATE_I2S_ON){

			/*
			 * I2S is needed to be Enabled
			 * PLLM Previosly edited in the main PLL
			*/

			/* check if PLLI2SN = 0 or 1 because it is a wrong configuration */
			if( ( (config_Ptr -> PLL.PLLI2SN) < 1 ) ){
				/* Put PLLNI2SN = 2 */
				RCC -> PLLI2SCFGR = ( ((RCC -> PLLI2SCFGR) & (~(PLLN_MASKING)) ) |  (PLLN_DEFAULT_VALUE << PLLN_FIRST_BIT) );
			}
			/* Check if PLLM > 432 because it is a wrong configuration */
			if( ( (config_Ptr -> PLL.PLLI2SN) > PLLN_MAX_VALUE )  ) {

				/*
				 * Clear PLLI2SN then Put it with max value (432) (From Bit 6 till bit 14)
				*/
				RCC -> PLLI2SCFGR = ( ((RCC -> PLLI2SCFGR) & (~(PLLN_MASKING)) ) |  (PLLN_MAX_VALUE << PLLN_FIRST_BIT) );
			}
			else{
				/*
				 * PLLI2SN Given is in the proper margins
				 * Clear PLLI2SN then Put it (From Bit 6 till bit 14)
				 * PLLN = 0 or 1 or from 433 till 511 is a wrong configuration
				 * so, max value = 432 (0x1B0)
				 * Put PLLN = 432
				*/
				RCC -> PLLI2SCFGR = ( ((RCC -> PLLI2SCFGR) & (~(PLLN_MASKING)) ) |  ( (config_Ptr -> PLL.PLLI2SN) << PLLN_FIRST_BIT) );
			}

			/* PLL SAI is only available on STM32F429 */
#ifdef STM32F429
			/* check if PLLI2SQ = 0 or 1 because it is a wrong configuration */
			if( ( (config_Ptr -> PLL.PLLI2SQ) < 1 ) ){
				/*
				 * Clear PLLI2SQ then Put it (From bit 24 till 27)
				 * Put PLLI2SQ = 2
				*/
				RCC -> PLLI2SCFGR = ( ((RCC -> PLLI2SCFGR) & (~(PLLI2SQ_MASKING)) ) |  (PLLI2SQ_DEFAULT_VALUE << PLLI2SQ_FIRST_BIT) );
			}
			else{
				/*
				 * PLLI2SQ Given is in the proper margins
				 * Clear PLLI2SQ then Put it (From Bit 24 till bit 27)
				*/
				RCC -> PLLI2SCFGR = ( ((RCC -> PLLI2SCFGR) & (~(PLLI2SQ_MASKING)) ) |  ( ( (config_Ptr -> PLL.PLLI2SQ) << PLLI2SQ_FIRST_BIT) & (PLLI2SQ_DEFAULT_VALUE) ) );

			}
#endif
			/* check if PLLI2SR = 0 or 1 because it is a wrong configuration */
			if( ( (config_Ptr -> PLL.PLLI2SR) < 1 ) ){
				/*
				 * Clear PLLI2SR then Put it (From bit 28 till 30)
				 * Put PLLI2SR = 2
				*/
				RCC -> PLLI2SCFGR = ( ((RCC -> PLLI2SCFGR) & (~(PLLI2SR_MASIKNG)) ) |  (PLLI2SR_DEFAULT_VALUE << PLLI2SR_FIRST_BIT) );
			}
			else{
				/*
				 * PLLI2SR Given is in the proper margins
				 * Clear PLLI2SR then Put it (From Bit 28 till bit 30)
				*/
				RCC -> PLLI2SCFGR = ( ((RCC -> PLLI2SCFGR) & (~(PLLI2SR_MASIKNG)) ) |  ( ( (config_Ptr -> PLL.PLLI2SR) << PLLI2SR_FIRST_BIT) & (PLLI2SR_MASIKNG) ) );

			}

			/*
			 * Clock entry source for I2S PLL Previously chosen when
			 * enabling the Main PLL Engine
			*/

			/* Enable I2S PLL Engine */

			/* Clear enabling bit of PLL then Enable the I2S PLL Engine */
			RCC -> CR = ( ( (RCC -> CR) & (~(PLLI2S_ENABLE_VALUE << PLLI2S_ENABLE_BIT) ) ) | (PLLI2S_ENABLE_VALUE << PLLI2S_ENABLE_BIT) );

			/* Wait till PLL is Ready */
			while( BIT_IS_CLEAR( (RCC -> CR), PLLI2S_READY_BIT) );


		}

		/* PLL SAI is only available on STM32F429 */
#ifdef STM32F429
		/* Check if PLL SAI is needed or not */
		if(config_Ptr -> PLL.PLLStateSAI == PLL_STATE_SAI_ON){

			/*
			 * SAI is needed to be Enabled
			 * PLLM Previosly edited in the main PLL
			*/

			/* check if PLLSAIN = 0 or 1 because it is a wrong configuration */
			if( ( (config_Ptr -> PLL.PLLSAIN) < 1 ) ){
				/* Put PLLNI2SN = 2 */
				RCC -> PLLSAICFGR = ( ((RCC -> PLLSAICFGR) & (~(PLLN_MASKING)) ) |  (PLLN_DEFAULT_VALUE << PLLN_FIRST_BIT) );
			}
			/* Check if PLLM > 432 because it is a wrong configuration */
			if( ( (config_Ptr -> PLL.PLLSAIN) > PLLN_MAX_VALUE )  ) {

				/*
				 * Clear PLLSAIN then Put it with max value (432) (From Bit 6 till bit 14)
				*/
				RCC -> PLLSAICFGR = ( ((RCC -> PLLSAICFGR) & (~(PLLN_MASKING)) ) |  (PLLN_MAX_VALUE << PLLN_FIRST_BIT) );
			}
			else{
				/*
				 * PLLSAIN Given is in the proper margins
				 * Clear PLLSAIN then Put it (From Bit 6 till bit 14)
				 * PLLN = 0 or 1 or from 433 till 511 is a wrong configuration
				 * so, max value = 432 (0x1B0)
				 * Put PLLN = 432
				*/
				RCC -> PLLSAICFGR = ( ((RCC -> PLLSAICFGR) & (~(PLLN_MASKING)) ) |  ( (config_Ptr -> PLL.PLLSAIN) << PLLN_FIRST_BIT) );
			}

			/* check if PLLSAIQ = 0 or 1 because it is a wrong configuration */
			if( ( (config_Ptr -> PLL.PLLSAIQ) < 1 ) ){
				/*
				 * Clear PLLSAIQ then Put it (From bit 24 till 27)
				 * Put PLLSAIQ = 2
				*/
				RCC -> PLLSAICFGR = ( ((RCC -> PLLSAICFGR) & (~(PLLSAIQ_MASKING)) ) |  (PLLSAIQ_DEFAULT_VALUE << PLLSAIQ_FIRST_BIT) );
			}
			else{
				/*
				 * PLLSAIQ Given is in the proper margins
				 * Clear PLLSAIQ then Put it (From Bit 24 till bit 27)
				*/
				RCC -> PLLSAICFGR = ( ((RCC -> PLLSAICFGR) & (~(PLLSAIQ_MASKING)) ) |  ( ( (config_Ptr -> PLL.PLLSAIQ) << PLLSAIQ_FIRST_BIT) & (PLLSAIQ_MASKING) ) );

			}

			/* check if PLLSAIR = 0 or 1 because it is a wrong configuration */
			if( ( (config_Ptr -> PLL.PLLSAIR) < 1 ) ){
				/*
				 * Clear PLLSAIR then Put it (From bit 28 till 30)
				 * Put PLLSAIR = 2
				*/
				RCC -> PLLSAICFGR = ( ((RCC -> PLLSAICFGR) & (~(PLLSAIR_MASKING)) ) |  (PLLSAIR_DEFAULT_VALUE << PLLSAIR_FIRST_BIT) );
			}
			else{
				/*
				 * PLLSAIR Given is in the proper margins
				 * Clear PLLSAIR then Put it (From Bit 28 till bit 30)
				*/
				RCC -> PLLSAICFGR = ( ((RCC -> PLLSAICFGR) & (~(PLLSAIR_MASKING)) ) |  ( ( (config_Ptr -> PLL.PLLSAIR) << PLLSAIR_FIRST_BIT) & (PLLSAIR_MASKING) ) );

			}

			/*
			 * Clock entry source for SAI PLL Previously chosen when
			 * enabling the Main PLL Engine
			*/

			/* Clear enabling bit of SAI PLL then Enable the Main PLL Engine */
			RCC -> CR = ( ( (RCC -> CR) & (~(PLLSAI_ENABLE_VALUE << PLLSAI_ENABLE_BIT) ) ) | (PLLSAI_ENABLE_VALUE << PLLSAI_ENABLE_BIT) );

			/* Wait till SAI PLL is Ready */
			while( BIT_IS_CLEAR( (RCC -> CR), PLLSAI_READY_BIT) );

		}

	}
#endif

	/*
	 * PLL is Disabled
	 * HSI is the main clock now
	*/

	/* Clear SYSCLK Bits then choose SYSCLK clock source */
	RCC -> CFGR = ( ( (RCC -> CFGR) & (~(SYSCLK_CLEAR_CLOCK_SOURCE)) ) | ( (config_Ptr -> SYSCLKSource) & SYSCLK_CLEAR_CLOCK_SOURCE));

	/* Wait till SYSCLK is ready */
	while( BIT_IS_CLEAR( (RCC -> CFGR) , (1 + (config_Ptr -> SYSCLKSource) ) ) );

	/* Clear HCLK Divisor Bits ( AHB Prescaler bits ) then Set it */
	RCC -> CFGR = ( ( (RCC -> CFGR) & (~(HCLK_CLEAR)) ) | ( ( (config_Ptr -> AHBDivisor) << HCLK_FIRST_BIT) & HCLK_ENSURE_DATA) );

	/* Clear PCLK1 Divisor Bits ( APB1 Prescaler bits ) then Set it */
	RCC -> CFGR = ( ( (RCC -> CFGR) & (~(PCLK1_CLEAR)) ) | ( ( (config_Ptr -> APB1Divisor) << PCLK1_FIRST_BIT) & PCLK1_CLEAR) );

	/* Clear PCLK2 Divisor Bits ( APB2 Prescaler bits ) then Set it */
	RCC -> CFGR = ( ( (RCC -> CFGR) & (~(PCLK2_CLEAR)) ) | ( ( (config_Ptr -> APB2Divisor) << PCLK2_FIRST_BIT) & PCLK2_CLEAR) );

	return OK;
}

/********************************************************************************
 [Function Name]:	xRCC_getClocks

 [Description]:		Used to get Microcontroller Various clocks
 	 	 	 	 	-SYSCLK
 	 	 	 	 	-HCLK
 	 	 	 	 	-PCLK1
 	 	 	 	 	-PCLK2

 [Args]:			rcc_Clocks

 [in]				config_Ptr: Pointer to RCC_clockValues structure
 	 	 	 	 	Which clock values will be saved on it

 [out]				None

 [in/out]			None

 [Returns]:			Retrun Status (OK if everything is okay)
**********************************************************************************/

Return_status xRCC_getClocks(RCC_clockValues * rcc_Clocks){

	u32 temp = 0, fvco = 0, prescaler = 0;
	u32 pllSource = 0, pllp = 0, pllm = 0, plln = 0;

	/* Get SYSCLK Clock Source from its status bits */
	temp = ( (RCC -> CFGR) & 0xC );

	/* Decide What is SYSCLK Value with switch */
	switch(temp){
		case 0x00:
			/* if SYSCLK Stats is 0, so it is equal to HSI */
			rcc_Clocks -> SYSCLKFrequency = HSI_CLOCK_VALUE;
		break;

		case 0x04:
			/* if SYSCLK Stats is 1, so it is equal to HSE */
			rcc_Clocks -> SYSCLKFrequency = HSE_CLOCK_VALUE;
		break;

		case 0x08:
			/*
			 * if SYSCLK Stats is 1, so it is equal to PLL
			 * SO, We need to get PLL Value from its equations
			 * 	Main Pll:
			 *		F(VCO) 			  = F(PLL Clock Source) * (PLLN / PLLM)
			 *		F(Main PLL) 	  = F(VCO) / PLLP
			 *		F(USB, SDIO, RNG) = F(VCO) / PLLQ
		    */

			/* First, Getting PLL Source */
			pllSource = ( ( (RCC -> PLLCFGR) & ( (PLL_ENABLE_VALUE << PLL_SOURCE_BIT) ) ) >> PLL_SOURCE_BIT);

			/* Second, Getting PLLN */
			plln = ( ( (RCC -> PLLCFGR) & ( (PLLN_MASKING) ) ) >> PLLN_FIRST_BIT);

			/* Third, Getting PLLM */
		    pllm = ( ( (RCC -> PLLCFGR) & ( (PLLM_MASKING) ) ) );

		    /* Check if pll source != 0 which is HSE */
		    if(pllSource != 0){

		    	/* Fourth, getting Fvco, clock input is HSE */
		    	fvco = ( ( HSE_CLOCK_VALUE / pllm) * (plln) );

		    }
		    /* Pll source is HSI  */
		    else{

		       	/* Fourth, getting Fvco, clock input is HSE */
		    	fvco = ( ( HSI_CLOCK_VALUE / pllm) * (plln) );

		    }
		    /*
		     * Fifth, getting PLLP
		     * +1 because first value might be 00 which is 2
		     * *2 because every value multiplied by 2
		    */
		    pllp = ( ( (RCC -> PLLCFGR & PLLP_MASKING) >> PLLP_FIRST_BIT ) + 1 ) *2 ;

		    /* set SYSCLKFreunecy to struct */
		    rcc_Clocks -> SYSCLKFrequency = fvco / pllp;
		    break;

		default:
			rcc_Clocks -> SYSCLKFrequency = HSI_CLOCK_VALUE;
			break;
	}
		temp = 0;

		/*
		 * Getting HCLK prescaler by anding CFGR Value
		 * with HCLK prescaler Bits
		 * then right shift the value with 4 to get the actual value of bits
		*/
		temp = ( ( (RCC -> CFGR) & HCLK_CLEAR) >> 4);

		/* Get prescaler value */
		prescaler = g_busesPreScaler[temp];

		/*
		 * Get HCLK Clock Frequency by dividing the SYSCLK Frequency
		 *  with AHB Prescaler (Right Shifting it)
		 */
		rcc_Clocks -> HCLKFrequency = ( (rcc_Clocks -> SYSCLKFrequency) >> prescaler );

		/* Clearing buffers */
		temp = 0;
		prescaler = 0;

		/*
		 * Getting PCLK1 prescaler by anding CFGR Value
		 * with PCLK1 prescaler Bits
		 * then right shift the value with 10 to get the actual value of bits
		*/
		temp = ( ( (RCC -> CFGR) & PCLK1_CLEAR) >> 10);

		/* Get prescaler value */
		prescaler = g_busesPreScaler[temp];

		/*
		 * Get PCLK1 Clock Frequency by dividing the HCLK Frequency
		 *  with APB1 Prescaler (Right Shifting it)
		 */
		rcc_Clocks -> PCLK1Frequency = ( (rcc_Clocks -> HCLKFrequency) >> prescaler );

		/* Clearing buffers */
		temp = 0;
		prescaler = 0;

		/*
		 * Getting PCLK1 prescaler by anding CFGR Value
		 * with PCLK1 prescaler Bits
		 * then right shift the value with 13 to get the actual value of bits
		*/
		temp = ( ( (RCC -> CFGR) & PCLK2_CLEAR) >> 13);

		/* Get prescaler value */
		prescaler = g_busesPreScaler[temp];

		/*
		 * Get PCLK1 Clock Frequency by dividing the HCLK Frequency
		 *  with APB1 Prescaler (Right Shifting it)
		 */
		rcc_Clocks -> PCLK2Frequency = ( (rcc_Clocks -> HCLKFrequency) >> prescaler );

		return OK;
}

/********************************************************************************
 [Function Name]:	xRCC_EnableClock

 [Description]:		Used to enable Clock for various peripherals

 [Args]:			u8Peripheral

 [in]				u8Peripheral: Number of the peripheral

 [out]				None

 [in/out]			None

 [Returns]:			Retrun Status (OK if everything is okay)
**********************************************************************************/
Return_status xRCC_EnableClock(u8 u8Peripheral)
{
	/* Check if peripheral number is within AHB1 Margins */
	if ((u8Peripheral >= AHB1_FIRST_NUMBER) && (u8Peripheral < AHB1_LAST_NUMBER))
	{
		/* Enable Clock */
		SET_BIT(RCC -> AHB1ENR, u8Peripheral);
	}

	/* Check if peripheral number is within AHB2 Margins */
	else if ((u8Peripheral >= AHB2_FIRST_NUMBER) && (u8Peripheral < AHB2_LAST_NUMBER))
	{
		/* Minus 32 of the value to operate with the register bits */
		u8Peripheral -=32;

		/* Enable Clock */
		SET_BIT(RCC -> AHB2ENR, u8Peripheral);
	}

	/* Check if peripheral number is within AHB3 Margins */
	else if ((u8Peripheral >= AHB3_FIRST_NUMBER) && (u8Peripheral < AHB3_LAST_NUMBER))
	{
		/* Minus 64 of the value to operate with the register bits */
		u8Peripheral -=64;

		/* Enable Clock */
		SET_BIT(RCC -> AHB3ENR, u8Peripheral);

	}

	/* Check if peripheral number is within APB1 Margins */
	else if((u8Peripheral >= APB1_FIRST_NUMBER) && (u8Peripheral < APB1_LAST_NUMBER))
	{
		/* Minus 128 of the value to operate with the register bits */
		u8Peripheral -= 128;

		/* Enable Clock */
		SET_BIT(RCC -> APB1ENR, u8Peripheral);
	}

	/* Check if peripheral number is within APB2 Margins */
	else if((u8Peripheral >= APB2_FIRST_NUMBER) && (u8Peripheral < APB2_LAST_NUMBER))
	{
		/* Minus 160 of the value to operate with the register bits */
		u8Peripheral -= 160;

		/* Enable Clock */
		SET_BIT(RCC -> APB2ENR, u8Peripheral);
	}

	else
	{
		/* Number is invalid */
		return NOK;
	}
	/* code is executed succesfully */
	return OK;
}

/********************************************************************************
 [Function Name]:	xRCC_DisableClock

 [Description]:		Used to disable Clock for various peripherals

 [Args]:			u8Peripheral

 [in]				u8Peripheral: Number of the peripheral

 [out]				None

 [in/out]			None

 [Returns]:			Retrun Status (OK if everything is okay)
**********************************************************************************/
Return_status xRCC_DisableClock(u8 u8Peripheral)
{
	switch(u8Peripheral)
	{
	/* Check if peripheral number is within AHB1 Margins */
	case AHB1_FIRST_NUMBER ... (AHB1_LAST_NUMBER - 1):

	/* Enable Clock */
	SET_BIT(RCC -> AHB1RSTR, u8Peripheral);
	break;

	/* Check if peripheral number is within AHB2 Margins */
	case AHB2_FIRST_NUMBER ... (AHB2_LAST_NUMBER - 1):

	/* Minus 32 of the value to operate with the register bits */
	u8Peripheral -=32;

	/* Enable Clock */
	SET_BIT(RCC -> AHB2RSTR, u8Peripheral);
	break;

	/* Check if peripheral number is within AHB3 Margins */
	case AHB3_FIRST_NUMBER ... (AHB3_LAST_NUMBER - 1):

	/* Minus 64 of the value to operate with the register bits */
	u8Peripheral -=64;

	/* Enable Clock */
	SET_BIT(RCC -> AHB3RSTR, u8Peripheral);
	break;

	/* Check if peripheral number is within APB1 Margins */
	case APB1_FIRST_NUMBER ... (APB1_LAST_NUMBER - 1):

	/* Minus 64 of the value to operate with the register bits */
	u8Peripheral -=128;

	/* Enable Clock */
	SET_BIT(RCC -> APB1RSTR, u8Peripheral);
	break;

	/* Check if peripheral number is within APB2 Margins */
	case APB2_FIRST_NUMBER ... (APB2_LAST_NUMBER - 1):

	/* Minus 64 of the value to operate with the register bits */
	u8Peripheral -=160;

	/* Enable Clock */
	SET_BIT(RCC -> APB2RSTR, u8Peripheral);
	break;

	default:
		/* Invalid Peripheral Number */
		return NOK;
	break;
	}

	return OK;
}

/***************Function Definition***************/
/*               Choose HSE as I/P               */
/*      Generate CLK 72Mhz & For USB 48MHz       */
/*Open CLK To PLLSAI & PLLI2S For Audio Interface*/
/*         and LCD Display with FREQ 72MHz       */
/*PLL Calculations:                              */
//void vidRCC_Init(void)
//{
//	SET_BIT(RCC -> CR, 0);   			//Enable High Speed Interal CLK  16MHz
//	while(!((RCC -> CR)& 0x00000002));	//Wait Until HSI is Stable
////	CLR_BIT(RCC -> PLLCFGR,22);			//HSE I\P To PLL & PLLI2S
////
////	RCC -> PLLCFGR    |= 0x0300168A;
////	RCC -> PLLI2SCFGR |= 0x22001680;
////	RCC -> PLLSAICFGR |= 0x22001680;
//
//
//}
