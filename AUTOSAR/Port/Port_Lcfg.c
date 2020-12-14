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
                                            /* In this application, 2 Pins (PF4 & PF1) only used */

                                            /* Configure PF2 as output for LED */
                                             PortConf_LED1_PIN_NUM, PortConf_LED1_PORT_NUM, PORT_PIN_OUT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_HIGH, SLEW_RATE_DISABLE,

                                            /* Configure PF4 as input for SW1 */
                                              PortConf_SW1_PIN_NUM, PortConf_SW1_PORT_NUM, PORT_PIN_IN,
                                              DIO_PIN, PULL_UP, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                            /**************************** All incoming pins are unused. They set on default mode (OFF) ***************************/

                                            /*-------------------------------------------------- PORT F Pins ----------------------------------------------------*/

                                             /*  Note: Pins From PF5 till PF7 are not physically available on TivaC Development Kit , so they did not appear here */

                                                          /*  Note: PF2 and PF4 are used for The application, they defined at the first of array */
                                              PORT_F_PIN_0, PORTF, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_F_PIN_1, PORTF, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_F_PIN_3, PORTF, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,
                                           /*-------------------------------------------------------------------------------------------------------------------*/ 
                                              
                                            /*-------------------------------------------------- PORT A Pins ----------------------------------------------------*/
                                              PORT_A_PIN_0, PORTA, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_A_PIN_1, PORTA, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_A_PIN_2, PORTA, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_A_PIN_3, PORTA, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_A_PIN_4, PORTA, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_A_PIN_5, PORTA, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_A_PIN_6, PORTA, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_A_PIN_7, PORTA, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,
                                             /*-------------------------------------------------------------------------------------------------------------------*/

                                             /*-------------------------------------------------- PORT B Pins ----------------------------------------------------*/
                                              PORT_B_PIN_0, PORTB, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_B_PIN_1, PORTB, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_B_PIN_2, PORTB, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_B_PIN_3, PORTB, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_B_PIN_4, PORTB, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_B_PIN_5, PORTB, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_B_PIN_6, PORTB, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_B_PIN_7, PORTB, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                             /*-------------------------------------------------------------------------------------------------------------------*/

                                             /*-------------------------------------------------- PORT C Pins ----------------------------------------------------*/

                                                                  /* Note: PortC from PC0 -> PC3 are used as JTAG Pins so they did not appear here */

                                              PORT_C_PIN_4, PORTC, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_C_PIN_5, PORTC, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_C_PIN_6, PORTC, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_C_PIN_7, PORTC, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                            /*-------------------------------------------------------------------------------------------------------------------*/

                                            /*-------------------------------------------------- PORT D Pins ----------------------------------------------------*/
                                              PORT_D_PIN_0, PORTD, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_D_PIN_1, PORTD, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_D_PIN_2, PORTD, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_D_PIN_3, PORTD, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_D_PIN_4, PORTD, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_D_PIN_5, PORTD, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_D_PIN_6, PORTD, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_D_PIN_7, PORTD, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                             /*-------------------------------------------------------------------------------------------------------------------*/

                                             /*-------------------------------------------------- PORT E Pins ----------------------------------------------------*/

                                                      /* Note: PE6 and PE7 are not physically available on TivaC Development Kit , so they did not appear here */

                                              PORT_E_PIN_0, PORTE, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_E_PIN_1, PORTE, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_E_PIN_2, PORTE, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_E_PIN_3, PORTE, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_E_PIN_4, PORTE, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                              PORT_E_PIN_5, PORTE, PORT_PIN_DEFAULT,
                                              DIO_PIN, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF, INITIAL_VALUE_LOW, SLEW_RATE_DISABLE,

                                             /*-------------------------------------------------------------------------------------------------------------------*/


                                           };


