 /******************************************************************************
 *
 * Module: RCC
 *
 * File Name: RCC_Reg.h
 *
 * Description: Header file for the RCC STM32 ARM Processor driver which includes:
 * 				- Hardware Register mapping in the struct
 * 				- preprocessor macro which is pointer to the
 * 				  struct to use these registers
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


#ifndef RCC_REG_H_
#define RCC_REG_H_


/********************************************************************************

 [Structure Name]:			RCC_REG

 [Structure Description]:	Structure holds registers of RCC Peripherals
 	 	 	 	 	 	 	to interact with them using pointer to struct

*********************************************************************************/

typedef struct{
											/*Register Name															Offset */
	volatile u32 CR;						//Control Register														0x00
	volatile u32 PLLCFGR;					//PLL Configuration Register											0x04
	volatile u32 CFGR;						//Clock Configuration Register											0x08
	volatile u32 CIR;						//Clock Interrupt Register												0x0C
	volatile u32 AHB1RSTR;					//AHB1 Peripheral Reset Register										0x10
	volatile u32 AHB2RSTR;					//AHB2 Peripheral Reset Register										0x14
	volatile u32 AHB3RSTR;					//AHB3 Peripheral Reset Register										0x18
	volatile u32 RES1;						//RESERVED																0x1C
	volatile u32 APB1RSTR;					//APB1 Peripheral Reset Register										0x20
	volatile u32 APB2RSTR;					//APB2 Peripheral Reset Register										0x24
	volatile u32 RES2[2];					//RESERVED															0x28 -> 0x2C
	volatile u32 AHB1ENR;					//AHB1 Peripheral Clock Register										0x30
	volatile u32 AHB2ENR;					//AHB2 Peripheral Clock Register										0x34
	volatile u32 AHB3ENR;					//AHB3 Peripheral Clock Register										0x38
	volatile u32 RES3;						//RESERVED																0x3C
	volatile u32 APB1ENR;					//APB1 Peripheral Clock Register										0x40
	volatile u32 APB2ENR;					//AHB2 Peripheral Clock Register										0x44
	volatile u32 RES4[2];					//RESERVED															0x48 -> 0x4C
	volatile u32 AHB1LPENR;					//AHB1 peripheral clock enable in low power mode register				0x50
	volatile u32 AHB2LPENR;					//AHB2 peripheral clock enable in low power mode register				0x54
	volatile u32 AHB3LPENR;					//AHB3 peripheral clock enable in low power mode register				0x58
	volatile u32 RES5;						//RESERVED																0x5C
	volatile u32 APB1LPENR;					//APB1 peripheral clock enable in low power mode register				0x60
	volatile u32 APB2LPENR;					//APB2 peripheral clock enable in low power mode register				0x64
	volatile u32 RES6[2];					//RESERVED															0x68 -> 0x6C
	volatile u32 BDCR;						//Backup Domain Control Register										0x70
	volatile u32 CSR;						//Clock Control & Status Register										0x74
	volatile u32 RES7[2];					//RESERVED															0x78 -> 0x7C
	volatile u32 SSCGR;						//spread spectrum clock generation register								0x80
	volatile u32 PLLI2SCFGR;					//PLLI2S configuration register											0x84

	/*
	 * These 2 registers are only on STM32F429 not in STM32F407
	 * You should define STM32F429 to use these 2 registers
	*/
	#ifdef STM32F429
	volatile u32 PLLSAICFGR;					//PLL configuration register											0x88
	volatile u32 DCKCFGR;					//Dedicated Clock Configuration Register								0x8C
	#endif

}RCC_REG;

/*
 * Pointer to struct used to interact with RCC Reigester by -> Operator
 * Base address is the same for all STM32F4xx Family
*/
#define RCC ((RCC_REG*) 0x40023800)

#endif /* RCC_REG_H_ */
