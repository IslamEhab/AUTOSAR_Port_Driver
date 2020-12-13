 /******************************************************************************
 *
 * Module:      Port
 *
 * File Name:   Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for
 *              TM4C123GH6PM Microcontroller
 *
 * Note:        Post Build defines added here also
 *              Ex: LED_PORT_NUM, SW_PORT_NUM, etc.
 *
 * Version      1.0.0
 *
 * Author:      Islam Ehab
 *
 * Date:        10/12/2020
 *
 ******************************************************************************/


#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/* Module Version 1.0.0 */
#define PORT_CFG_SW_MAJOR_VERSION               (1U)
#define PORT_CFG_SW_MINOR_VERSION               (0U)
#define PORT_CFG_SW_PATCH_VERSION               (0U)

/* AUTOSAR Version 4.0.3 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION       (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION       (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION       (3U)

/* Pre-compile option for DET Enable/ Disable */
#define PORT_DEV_ERROR_DETECT                   (STD_ON)

/* Pre-compile option for Port_SetPinDirection API */
#define PORT_SET_PIN_DIRECTION_API              (STD_ON)

/* Pre-compile Option for Port_GetVersionInfo API */
#define PORT_VERSION_INFO_API                   (STD_ON)

/* Number of the configured Dio Channels */
#define PORT_CONFIGURED_CHANNLES                (39U)

/* Port Configured Port ID's  */
#define PortConf_LED1_PORT_NUM                  (Port_PortNumEnum)PORTF
#define PortConf_SW1_PORT_NUM                   (Port_PortNumEnum)PORTF

/* Port Configured Pins ID's  */
#define PortConf_LED1_PIN_NUM                   (Port_PinType)PORT_F_PIN_2 /* Pin 3 in PORTF */
#define PortConf_SW1_PIN_NUM                    (Port_PinType)PORT_F_PIN_4 /* Pin 4 in PORTF */

#endif /* PORT_CFG_H_ */
