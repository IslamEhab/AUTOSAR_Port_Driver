 /******************************************************************************
 *
 * Module:      Port
 *
 * File Name:   Port_Reg.h
 *
 * Description: Header file for Port Registers on STM32F429 Microcontroller
 * 				Port Driver Register
 *
 * Version      1.0.0
 *
 * Author:      Islam Ehab
 *
 * Date:        13/12/2020
 *
 ******************************************************************************/

/*******************************************************************************
 *
 * @file        Port_Reg.h
 *
 * @brief       Header file for Port Registers on STM32F4 Microcontroller Family
 * 				Port Driver
 *
 * @version     1.0.0
 *
 * @author      Islam Ehab
 *
 * @date        13/12/2020
 *
 *******************************************************************************/


#ifndef PORT_REG_H_
#define PORT_REG_H_

#include "Std_Types.h"
#include "Common_Macros.h"

/*******************************************************************************
 *                       Port Registers Offset Address                          *
 *******************************************************************************/


/**
 * @struct GPIO_REG
 *
 * @brief  Used to hold register with their offsets by saving them
 * 		   in the struct with their order from data sheet
 *
 * @note   BSRR divided into 2 registers BSRRL (Least significant 16 bit)
 * 		   which used to set certain bit with '1'
 * 		   & BSRRH (Most significant 16 bit) Which used to clear certain bit
 */
typedef struct{
											/*Register Name													   Offset*/
	volatile uint32 MODER;					/* Port Mode Register												0x00 */
	volatile uint32 OTYPER;					/* Port O/P Type													0x04 */
	volatile uint32 OSPEEDR;				/* Port O/P Speed													0x08 */
	volatile uint32 PUPDR;					/* Port Pull-Up/Down Register										0x0C */
	volatile uint32 IDR;					/* Port I/P Data Register											0x10 */
	volatile uint32 ODR;					/* Port O/P Data Register											0x14 */
	volatile uint16 BSRRL;					/* Port Bit Set Register											0x16 */
	volatile uint16 BSRRH;					/* Port Bit Reset Register											0x18 */
	volatile uint32 LCKR;					/* Port Configuration Lock Register									0x1C */
	volatile uint32 AFRL;					/* Alternate Function Low Register									0x20 */
	volatile uint32 AFRH;					/* Alternate Function High Register									0x24 */

}GPIO_REG;

/*******************************************************************************
 *                         Port Registers Base Address                          *
 *******************************************************************************/

#define GPIO_PORTA_BASE_ADDRESS           (0x40020000)        /* GPIOA(AHB1) Base Address */
#define GPIO_PORTB_BASE_ADDRESS           (0x40020400)        /* GPIOB(AHB1) Base Address */
#define GPIO_PORTC_BASE_ADDRESS           (0x40020800)        /* GPIOC(AHB1) Base Address */
#define GPIO_PORTD_BASE_ADDRESS           (0x40020C00)        /* GPIOD(AHB1) Base Address */
#define GPIO_PORTE_BASE_ADDRESS           (0x40021000)        /* GPIOE(AHB1) Base Address */
#define GPIO_PORTF_BASE_ADDRESS           (0x40021400)        /* GPIOF(AHB1) Base Address */
#define GPIO_PORTG_BASE_ADDRESS			  (0x40021800)        /* GPIOG(AHB1) Base Address */
#define GPIO_PORTH_BASE_ADDRESS			  (0x40021C00)        /* GPIOH(AHB1) Base Address */

/*******************************************************************************/

/*******************************************************************************
 * 					Pointer to Port Registers Base Address 						*
 * Note: Used only to initialize Port Registers in Port_RegInit()				*
 *******************************************************************************/

#define GPIOA_BASE_ADDRESS 				 ((GPIO_REG*) 0x40020000)	/* Pointer to GPIOA Base Address of type GPIO_REG */
#define GPIOB_BASE_ADDRESS				 ((GPIO_REG*) 0x40020400)	/* Pointer to GPIOB Base Address of type GPIO_REG */
#define GPIOC_BASE_ADDRESS				 ((GPIO_REG*) 0x40020800)	/* Pointer to GPIOC Base Address of type GPIO_REG */
#define GPIOD_BASE_ADDRESS 			     ((GPIO_REG*) 0x40020C00)	/* Pointer to GPIOD Base Address of type GPIO_REG */
#define GPIOE_BASE_ADDRESS				 ((GPIO_REG*) 0x40021000)	/* Pointer to GPIOE Base Address of type GPIO_REG */
#define GPIOF_BASE_ADDRESS				 ((GPIO_REG*) 0x40021400)	/* Pointer to GPIOF Base Address of type GPIO_REG */
#define GPIOG_BASE_ADDRESS				 ((GPIO_REG*) 0x40021800)	/* Pointer to GPIOG Base Address of type GPIO_REG */
#define GPIOH_BASE_ADDRESS				 ((GPIO_REG*) 0x40021C00)	/* Pointer to GPIOH Base Address of type GPIO_REG */

#endif /* PORT_REG_H_ */
