 /******************************************************************************
 *
 * Module:      Port
 *
 * File Name:   Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for
 *              STM32F4 Microcontroller Family
 *
 * Note:        Post Build defines added here also
 *              Ex: LED_PORT_NUM, SW_PORT_NUM, etc.
 *
 * Version      1.0.0
 *
 * Author:      Islam Ehab
 *
 * Date:        13/12/2020
 ******************************************************************************/


/*******************************************************************************
 *
 * @file        Port
 *
 * @brief       Link Time (Pre-Compile) Configuration Header file for
 *              STM32F4 Microcontroller Family - Port Driver
 *
 * @note:       Post Build defines added here also
 *              Ex: LED_PORT_NUM, SW_PORT_NUM, etc.
 *
 * @version     1.0.0
 *
 * @author      Islam Ehab
 *
 * @date        13/12/2020
 *******************************************************************************/

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/* Module Version 1.0.0 */
#define PORT_CFG_SW_MAJOR_VERSION               (1U)
#define PORT_CFG_SW_MINOR_VERSION               (0U)
#define PORT_CFG_SW_PATCH_VERSION               (0U)

/* AUTOSAR Version 4.0.3 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION       (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION       (3U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION       (1U)

/* Pre-compile option for DET Enable/ Disable 		*/
#define PORT_DEV_ERROR_DETECT                   (STD_ON)

/* Pre-compile option for Port_SetPinDirection API 	*/
#define PORT_SET_PIN_DIRECTION_API              (STD_ON)

/* Pre-compile Option for Port_GetVersionInfo API 	*/
#define PORT_VERSION_INFO_API                   (STD_ON)

/* Number of the configured Dio Channels 			*/
#define PORT_CONFIGURED_CHANNLES                (39U)

/* Port Configured Port ID's  */
#define PortConf_LED1_PORT_NUM                  (Port_PortNumEnum)PORTG
#define PortConf_LED2_PORT_NUM                  (Port_PortNumEnum)PORTG
#define PortConf_SW1_PORT_NUM                   (Port_PortNumEnum)PORTA

/* These USARTs used for Testing Only 				*/
#define PortConf_USART1_PORT_NUM				(Port_PortNumEnum)PORTA
#define PortConf_UART4_PORT_NUM					(Port_PortNumEnum)PORTC

/* Port Configured Pins ID's  */
#define PortConf_LED1_PIN_NUM                   (Port_PinType)PORT_G_PIN_13 /* Pin 13 in PORTG */
#define PortConf_LED2_PIN_NUM                   (Port_PinType)PORT_G_PIN_14 /* Pin 14 in PORTG */
#define PortConf_SW1_PIN_NUM                    (Port_PinType)PORT_A_PIN_0  /* Pin 0  in PORTA */

/* These USARTs used for Testing Only 				*/
#define PortConf_USART1_TX_PIN_NUM				(Port_PinType)PORT_A_PIN_9	/* Pin 9 in PORTA  */
#define PortConf_USART1_RX_PIN_NUM				(Port_PinType)PORT_A_PIN_10 /* Pin 10 in PORTA */

#define PortConf_UART4_TX_PIN_NUM				(Port_PinType)PORT_C_PIN_10 /* Pin 10 in PORTC */
#define PortConf_UART4_RX_PIN_NUM				(Port_PinType)PORT_C_PIN_11 /* Pin 11 in PORTC */




#endif /* PORT_CFG_H_ */
