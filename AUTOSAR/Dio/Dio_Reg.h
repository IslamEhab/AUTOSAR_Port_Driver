 /******************************************************************************
 *
 * Module: 		Dio
 *
 * File Name: 	Dio_Reg.h
 *
 * Description: Header file for STM32F429 Microcontroller - Dio Driver Registers
 *
 * Author: 		Islam Ehab
 *
 * Date:		12/12/2020
 ******************************************************************************/
/*******************************************************************************
 * @file:	Dio_Reg.h
 *
 * @brief:	Header file for STM32F429 Microcontroller - Dio Driver Registers
 *
 * @author:	Islam Ehab
 *
 * @date:	12/12/2020
 ******************************************************************************/

#ifndef DIO_REGS_H
#define DIO_REGS_H

#include "Std_Types.h"


/***********************************************************************************
 *                            Dio Registers Base Address                           *
 **********************************************************************************/
#define GPIO_PORTA_BASE_ADDRESS 			(0x40020000)	/* GPIOA Base Address */
#define GPIO_PORTB_BASE_ADDRESS 			(0x40020400)	/* GPIOB Base Address */
#define GPIO_PORTC_BASE_ADDRESS 			(0x40020800)	/* GPIOC Base Address */
#define GPIO_PORTD_BASE_ADDRESS 			(0x40020C00)	/* GPIOD Base Address */
#define GPIO_PORTE_BASE_ADDRESS 			(0x40021000)	/* GPIOE Base Address */
#define GPIO_PORTF_BASE_ADDRESS 			(0x40021400)	/* GPIOF Base Address */
#define GPIO_PORTG_BASE_ADDRESS 			(0x40021800)	/* GPIOG Base Address */
#define GPIO_PORTH_BASE_ADDRESS 			(0x40021C00)	/* GPIOH Base Address */
/**********************************************************************************/

/***********************************************************************************
 *                           Dio Registers Offset Address                          *
 **********************************************************************************/

/*** Note: BSRR Register (Bit Set Reset Register) is divided her into 2 register ***
 ***        with their offsets (32 bit into 2 16 bit registers)					 ***
 ***        one for Set Bit (Least 16 bit 0x18) and the other					 ***
 ***      	for clear bit (Most 16 Bit 0x1A)									 ***
 **********************************************************************************/
#define DIO_INPUT_DATA_REGISTER_OFFSET		(0x10)	/* Input data register offset */
#define DIO_OUTPUT_DATA_REGISTER_OFFSET		(0x14)	/* Output data register offset*/
#define	DIO_BIT_SET_REGISTER_OFFSET			(0x18)	/* Set Bit register offset	  */
#define DIO_BIT_CLEAR_REGISTER_OFFSET		(0x1A)	/* Clear Bit register offset  */
/**********************************************************************************/


#endif /* DIO_REGS_H */
