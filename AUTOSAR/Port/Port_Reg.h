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
 * Date:        10/12/2020
 *
 ******************************************************************************/



#ifndef PORT_REG_H_
#define PORT_REG_H_

#include "Std_Types.h"
#include "Common_Macros.h"

/*******************************************************************************
 *                         Port Registers Base Address                          *
 *******************************************************************************/

#define GPIO_PORTA_BASE_ADDRESS           0x40004000        /* GPIOA(APB) Base Address */
#define GPIO_PORTB_BASE_ADDRESS           0x40005000        /* GPIOB(APB) Base Address */
#define GPIO_PORTC_BASE_ADDRESS           0x40006000        /* GPIOC(APB) Base Address */
#define GPIO_PORTD_BASE_ADDRESS           0x40007000        /* GPIOD(APB) Base Address */
#define GPIO_PORTE_BASE_ADDRESS           0x40024000        /* GPIOE(APB) Base Address */
#define GPIO_PORTF_BASE_ADDRESS           0x40025000        /* GPIOF(APB) Base Address */

/*******************************************************************************/


/*******************************************************************************
 *                       Port Registers Offset Address                          *
 *******************************************************************************/

#define PORT_DATA_REG_OFFSET              0x3FC             /* Data Register Offset                  */
#define PORT_DIR_REG_OFFSET               0x400             /* Direction Register Offset             */
#define PORT_ALT_FUNC_REG_OFFSET          0x420             /* Alternative Function Register Offset  */
#define PORT_PULL_UP_REG_OFFSET           0x510             /* Pull Up Register Offset               */
#define PORT_PULL_DOWN_REG_OFFSET         0x514             /* Pull Down Register Offset             */
#define PORT_SLEW_RATE_CONTROL_OFFSET     0x518             /* Slew Rate control register offset     */
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C             /* Digital Enable Register Offset        */
#define PORT_LOCK_REG_OFFSET              0x520             /* Lock Register Offset                  */
#define PORT_COMMIT_REG_OFFSET            0x524             /* Commit Register Offset                */
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528             /* Analog mode selection Register Offset */
#define PORT_CTL_REG_OFFSET               0x52C             /* Control Register Offset               */

/* RCCG2 Register to enable clocks to ports */
#define SYSCTL_REGCGC2_REG              (*((volatile uint32 *)0x400FE108))


#endif /* PORT_REG_H_ */
