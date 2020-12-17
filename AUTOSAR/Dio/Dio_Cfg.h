 /******************************************************************************
 *
 * Module: 		Dio
 *
 * File Name: 	Dio_Cfg.h
 *
 * Description: Link Time (Pre-Compile) Configuration Header file
 * 				for STM32F429 Microcontroller - Dio Driver
 *
 * Version      1.0.0
 *
 * Author: 		Islam Ehab
 *
 * Date:		12/12/2020
 ******************************************************************************/
/*******************************************************************************
 * @file:	Dio_Cfg.h
 *
 * @brief:	Link Time (Pre-Compile) Configuration Header file
 * 			for STM32F429 Microcontroller - Dio Driver
 *
 * @author:	Islam Ehab
 *
 * @date:	12/12/2020
 ******************************************************************************/

#ifndef DIO_CFG_H
#define DIO_CFG_H

/*
 * Module Version 1.0.0
 */
#define DIO_CFG_SW_MAJOR_VERSION              (1U)
#define DIO_CFG_SW_MINOR_VERSION              (0U)
#define DIO_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.3.1
 */
#define DIO_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_CFG_AR_RELEASE_MINOR_VERSION     (3U)
#define DIO_CFG_AR_RELEASE_PATCH_VERSION     (1U)

/* Pre-compile option for Development Error Detect */
#define DIO_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define DIO_VERSION_INFO_API                (STD_ON)

/* Pre-compile option for presence of Dio_FlipChannel API */
#define DIO_FLIP_CHANNEL_API                (STD_ON)

/* Number of the configured Dio Channels */
#define DIO_CONFIGURED_CHANNLES             (7U)

/* Channel Index in the array of structures in Dio_PBcfg.c */
#define DioConf_LED1_CHANNEL_ID_INDEX        (uint8)0x00
#define DioConf_LED2_CHANNEL_ID_INDEX        (uint8)0x01
#define DioConf_SW1_CHANNEL_ID_INDEX         (uint8)0x02
#define DioConf_USART1_TX_CHANNEL_ID_INDEX   (uint8)0x03
#define DioConf_USART1_RX_CHANNEL_ID_INDEX   (uint8)0x04
#define DioConf_UART4_TX_CHANNEL_ID_INDEX    (uint8)0x05
#define DioConf_UART4_RX_CHANNEL_ID_INDEX    (uint8)0x06


/* These USARTs used for Testing Only 					   */
#define DioConf_USART1_PORT_NUM				 (Dio_PortType)DIO_PORTA
#define DioConf_UART4_PORT_NUM				 (Dio_PortType)DIO_PORTC


/* DIO Configured Port ID's  							   */
#define DioConf_LED1_PORT_NUM                (Dio_PortType)DIO_PORTG /* DIO_PORTG */
#define DioConf_LED2_PORT_NUM                (Dio_PortType)DIO_PORTG /* DIO_PORTG */
#define DioConf_SW1_PORT_NUM                 (Dio_PortType)DIO_PORTA /* DIO_PORTG */

/* DIO Configured Channel ID's 							   */
#define DioConf_LED1_CHANNEL_NUM             (Dio_ChannelType)DIO_PORT_G_PIN_13 /* Pin 13 in PORTG */
#define DioConf_LED2_CHANNEL_NUM             (Dio_ChannelType)DIO_PORT_G_PIN_14 /* Pin 14 in PORTG */
#define DioConf_SW1_CHANNEL_NUM              (Dio_ChannelType)DIO_PORT_A_PIN_0  /* Pin 0  in PORTA */

/* These USARTs used for Testing Only 				*/
#define DioConf_USART1_TX_CHANNEL_NUM		 (Dio_ChannelType)DIO_PORT_A_PIN_9	/* Pin 9 in PORTA  */
#define DioConf_USART1_RX_CHANNEL_NUM		 (Dio_ChannelType)DIO_PORT_A_PIN_10 /* Pin 10 in PORTA */

#define DioConf_UART4_TX_CHANNEL_NUM		 (Dio_ChannelType)DIO_PORT_C_PIN_10 /* Pin 10 in PORTC */
#define DioConf_UART4_RX_CHANNEL_NUM		 (Dio_ChannelType)DIO_PORT_C_PIN_11 /* Pin 11 in PORTC */




#endif /* DIO_CFG_H */
