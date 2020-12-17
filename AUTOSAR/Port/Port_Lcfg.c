 /******************************************************************************
 *
 * Module:      Port
 *
 * File Name:   Port_Lcfg.c
 *
 * Description: Link time (Post Build) Configuration Source file for
 * 				STM32F429 Microcontroller - Port Driver
 *
 *              This file contains an array of structures used to initialize
 *              Port module with configured values using tools
 *
 * Note:        Unused pins initialized with initial value
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
 * @file        Port_Lcfg.c
 *
 * @brief       Link time (Post Build) Configuration Source file for
 * 				STM32F429 Microcontroller - Port Driver
 *
 *              This file contains an array of structures used to initialize
 *              Port module with configured values using tools
 *
 * @note        Unused pins initialized with initial value
 *
 * @version     1.0.0
 *
 * @author      Islam Ehab
 *
 * @date        13/12/2020
 *
 *******************************************************************************/

#include "Port.h"
/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (3U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (1U)

/* AUTOSAR Version checking between PORT_PBcfg.c and PORT.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between PORT_PBcfg.c and PORT.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with PORT_Init API */
const Port_ConfigType Port_Configuration = {
                                            /* In this application, 3 Pins (PG13, PG14 & PA0) only used */

                                            /* Configure PG13 as output for LED */
                                             PortConf_LED1_PIN_NUM, PortConf_LED1_PORT_NUM, PORT_PIN_OUT, DIO_PIN, INTERNAL_RESISTOR_OFF,
                                             PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, MEDIUM_SPEED, OUTPUT_TYPE_PUSH_PULL,

											/* Configure PG14 as output for LED */
											 PortConf_LED2_PIN_NUM, PortConf_LED2_PORT_NUM, PORT_PIN_OUT, DIO_PIN, INTERNAL_RESISTOR_OFF,
											 PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, MEDIUM_SPEED, OUTPUT_TYPE_PUSH_PULL,

                                            /* Configure PA0 as input for SW1 */
                                              PortConf_SW1_PIN_NUM, PortConf_SW1_PORT_NUM, PORT_PIN_IN, DIO_PIN, PULL_UP,
                                              PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, NO_SPEED ,OUTPUT_TYPE_OFF,


											/***************************************** All incoming pins are used for testing ************************************/
											  PortConf_USART1_TX_PIN_NUM, PortConf_USART1_PORT_NUM, PORT_PIN_OUT, PORT_A_PIN_9_AF7_USART1_TX, INTERNAL_RESISTOR_OFF,
											  PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, VERY_HIGH_SPEED, OUTPUT_TYPE_PUSH_PULL,

											  PortConf_USART1_RX_PIN_NUM, PortConf_USART1_PORT_NUM, PORT_PIN_OUT, PORT_A_PIN_10_AF7_USART1_RX, INTERNAL_RESISTOR_OFF,
											  PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, VERY_HIGH_SPEED, OUTPUT_TYPE_PUSH_PULL,

											  PortConf_UART4_TX_PIN_NUM, PortConf_UART4_PORT_NUM, PORT_PIN_OUT, PORT_C_PIN_10_AF8_UART4_TX, INTERNAL_RESISTOR_OFF,
											  PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, VERY_HIGH_SPEED, OUTPUT_TYPE_PUSH_PULL,

											  PortConf_UART4_RX_PIN_NUM, PortConf_UART4_PORT_NUM, PORT_PIN_OUT, PORT_C_PIN_11_AF8_UART4_RX, INTERNAL_RESISTOR_OFF,
											  PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, VERY_HIGH_SPEED, OUTPUT_TYPE_PUSH_PULL,



                                            /**************************** All incoming pins are unused. They set on default mode (OFF) ***************************/
											/*
											 * Note: There should be another elements in the structure to holds the initial values of the unused Pins, but due to
											 * Memory & Time limitation they won't be implemented
											*/
                                           };


