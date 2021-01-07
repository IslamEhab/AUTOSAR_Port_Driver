 /******************************************************************************
 *
 * Module:      Port
 *
 * File Name:   Port.h
 *
 * Description: Header file for Port Module on STM32F4 Microcontroller Family
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
 * @file        Port.h
 *
 * @brief       Header file for Port Module on STM32F4 Microcontroller Family
 *
 * @version    	1.0.0
 *
 * @author      Islam Ehab
 *
 * @date        13/12/2020
 *
 *******************************************************************************/


#ifndef PORT_H_
#define PORT_H_

/*
 * ID of Company in AUTOSAR Website
 * Islam Ehab's ID = 1024
*/
#define PORT_VENDOR_ID                          (1024U)

/* Port Module ID from AUTOSAR BSW Document */
#define PORT_MODULE_ID                          (124U)

/*
 * Port Instance ID
 * Note: ID = 0 because there are no other HW
 * For this instance
*/
#define PORT_INSTANCE_ID                        (0U)

/* Module Version 1.0.0 */
#define PORT_SW_MAJOR_VERSION                   (1U)
#define PORT_SW_MINOR_VERSION                   (0U)
#define PORT_SW_PATCH_VERSION                   (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION           (4U)
#define PORT_AR_RELEASE_MINOR_VERSION           (3U)
#define PORT_AR_RELEASE_PATCH_VERSION           (1U)


/* Macros for Port Status */
#define PORT_INITIALIZED                        (1U)
#define PORT_NOT_INITIALIZED                    (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and PORT Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* PORT Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PORT_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PORT_Cfg.h does not match the expected version"
#endif

/*
 * Non AUTOSAR files
 * Note: No checking for versions
 * because it is not an AUTOSAR File
*/
#include "Common_Macros.h"

/******************************************************************************
 *                          API Service Id Macros                              *
 *              Note: You can get them from Ch8 from PORT SWS                  *
 ******************************************************************************/
/* Service ID for Port Init Function                             */
#define PORT_INIT_SID                           (uint8)0x00

/* Service ID for Port Set Pin Direction Function                */
#define PORT_SET_PIN_DIRECTION_SID              (uint8)0x01

/* Service ID for Port Refresh Direction Function                */
#define PORT_REFRESH_PORT_DIRECTION_SID         (uint8)0x02

/* Service ID for Port Get Version Info Function                 */
#define PORT_GET_VERSION_INFO_SID               (uint8)0x03

/* Service ID for Port Set Pin Mode Function                     */
#define PORT_SET_PIN_MODE_SID                   (uint8)0x04

/*******************************************************************************/

/*******************************************************************************
 *                            DET Error Codes                                   *
 *                  Note: You can get them from Ch7 from PORT SWS               *
 *******************************************************************************/
/* DET Code for invalid Port Pin ID Request                      */
#define PORT_E_PARAM_PIN                        (uint8)0x0A

/* DET Code for Port Pin not configured as changeable            */
#define PORT_E_DIRECTION_UNCHANGEABLE           (uint8)0x0B

/*
 * DET Code for Port_Init called with wrong Parameter
 * Note: This error is removed from AUTOSAR 4.3.1
*/

/* API Port_Init service called with wrong parameter 			 */
#define PORT_E_INIT_FAILED                     	(uint8)0x0C

/* DET Code for Invalid Mode                                     */
#define PORT_E_PARAM_INVALID_MODE               (uint8)0x0D

/* DET Code for Port_SetPinMode called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE                (uint8)0x0E

/* DET Code for service called without module initialization     */
#define PORT_E_UNINIT                           (uint8)0x0F

/* DET Code for API called with NULL Pointer                     */
#define PORT_E_PARAM_POINTER                    (uint8)0x10

/* Added Error Code from Me when trying to change a
 * direction of pin which is unchangeable                        */
#define PORT_E_DIRECTON_UNCHANGEABLE            (uint8)0x12
/********************************************************************************/

/********************************************************************************
 *                              Module Data Types                                *
 ********************************************************************************/

/**
 * @enum	Port_PinDirectionType
 *
 * @brief	Type definition for Port_PinDirectionType used by PORT APIs
 */
typedef enum{

    PORT_PIN_IN,    //!< PORT_PIN_IN
    PORT_PIN_OUT,   //!< PORT_PIN_OUT
    PORT_PIN_DEFAULT//!< PORT_PIN_DEFAULT

}Port_PinDirectionType;

/* */
/**
 * @enum	Port_InternalResistor
 *
 * @brief	Used to decide the mode of internal pull up or to disable it at all
 */
typedef enum{

    INTERNAL_RESISTOR_OFF,     //!< INTERNAL_RESISTOR_OFF
    PULL_UP,                   //!< PULL_UP
    PULL_DOWN                  //!< PULL_DOWN

}Port_InternalResistor;



/**
 * @enum  Port_PinModeEnum
 * @brief This enum has all the alternative function values of the TM4C123GH6PM
 * 		  to be used with Port_PinModeType data type
 */
#ifdef STM32F429
typedef enum{

/********* Alternative function = 0 For all Pins that have it **************/
	PORT_A_PIN_8_AF0_MCO1					= 0,                                               //!< PORT_A_PIN_8_AF0_MCO1
	PORT_A_PIN_13_AF0_JTMS_SWDIO			= 0,                                          //!< PORT_A_PIN_13_AF0_JTMS_SWDIO
	PORT_A_PIN_14_AF0_JTCK_SWCLK			= 0,                                          //!< PORT_A_PIN_14_AF0_JTCK_SWCLK
	PORT_A_PIN_15_AF0_JTDI					= 0,                                              //!< PORT_A_PIN_15_AF0_JTDI

	PORT_B_PIN_3_AF0_JTDO_TRAC_ESWO			= 0,                                       //!< PORT_B_PIN_3_AF0_JTDO_TRAC_ESWO
	PORT_B_PIN_4_AF0_NTJRST					= 0,                                             //!< PORT_B_PIN_4_AF0_NTJRST
	PORT_B_PIN_15_AF0_RTC_REFIN				= 0,                                          //!< PORT_B_PIN_15_AF0_RTC_REFIN

	PORT_C_PIN_9_AF0_MCO2					= 0,                                               //!< PORT_C_PIN_9_AF0_MCO2

	PORT_E_PIN_2_AF0_TRAC_ECLK				= 0,                                           //!< PORT_E_PIN_2_AF0_TRAC_ECLK
	PORT_E_PIN_3_AF0_TRAC_ED0				= 0,                                            //!< PORT_E_PIN_3_AF0_TRAC_ED0
	PORT_E_PIN_4_AF0_TRAC_ED1				= 0,                                            //!< PORT_E_PIN_4_AF0_TRAC_ED1
	PORT_E_PIN_5_AF0_TRAC_ED2				= 0,                                            //!< PORT_E_PIN_5_AF0_TRAC_ED2
	PORT_E_PIN_6_AF0_TRAC_ED3				= 0,                                            //!< PORT_E_PIN_6_AF0_TRAC_ED3

/***************************************************************************/

/*********** Alternative Function  = 1 For all Pins that have it ***********/
    PORT_A_PIN_0_AF1_TMI2_CH1		     	= 1, /* Note: PA0 AF0 has 2 modes*/      //!< PORT_A_PIN_0_AF1_TMI2_CH1
	PORT_A_PIN_0_AF1_TIM2_ETR				= 1, /* For TIM2 (CH1 & TIM2 ETR)*/             //!< PORT_A_PIN_0_AF1_TIM2_ETR
	PORT_A_PIN_1_AF1_TIM2_CH2				= 1,                                            //!< PORT_A_PIN_1_AF1_TIM2_CH2
	PORT_A_PIN_2_AF1_TIM2_CH3				= 1,                                            //!< PORT_A_PIN_2_AF1_TIM2_CH3
	PORT_A_PIN_3_AF1_TIM2_CH4				= 1,                                            //!< PORT_A_PIN_3_AF1_TIM2_CH4
	PORT_A_PIN_5_AF1_TIM2_CH1				= 1, /* Note: PA5 AF5 has 2 modes*/             //!< PORT_A_PIN_5_AF1_TIM2_CH1
	PORT_A_PIN_5_AF1_TIM2_ETR				= 1, /* TIM2 (CH1 & ETR) (as PA0)*/             //!< PORT_A_PIN_5_AF1_TIM2_ETR
	PORT_A_PIN_6_AF1_TIM1_BKIN				= 1,                                           //!< PORT_A_PIN_6_AF1_TIM1_BKIN
	PORT_A_PIN_7_AF1_TIM1_CH1N				= 1,                                           //!< PORT_A_PIN_7_AF1_TIM1_CH1N
	PORT_A_PIN_8_AF1_TIM1_CH1				= 1,                                            //!< PORT_A_PIN_8_AF1_TIM1_CH1
	PORT_A_PIN_9_AF1_TIM1_CH2				= 1,                                            //!< PORT_A_PIN_9_AF1_TIM1_CH2
	PORT_A_PIN_10_AF1_TIM1_CH3				= 1,                                           //!< PORT_A_PIN_10_AF1_TIM1_CH3
	PORT_A_PIN_11_AF1_TIM1_CH4				= 1,                                           //!< PORT_A_PIN_11_AF1_TIM1_CH4
	PORT_A_PIN_12_AF1_TIM1_ETR				= 1,                                           //!< PORT_A_PIN_12_AF1_TIM1_ETR
	PORT_A_PIN_15_AF1_TIM2_CH1				= 1, /* Note: PA15 AF0 has 2modes*/            //!< PORT_A_PIN_15_AF1_TIM2_CH1
	PORT_A_PIN_15_AF1_TIM2_ETR				= 1, /* TIM2 (CH1 & ETR) (as PA0)*/            //!< PORT_A_PIN_15_AF1_TIM2_ETR

	PORT_B_PIN_0_AF1_TIM1_CH2N				= 1,                                           //!< PORT_B_PIN_0_AF1_TIM1_CH2N
	PORT_B_PIN_1_AF1_TIM1_CH3N				= 1,                                           //!< PORT_B_PIN_1_AF1_TIM1_CH3N
	PORT_B_PIN_3_AF1_TIM1_CH2				= 1,                                            //!< PORT_B_PIN_3_AF1_TIM1_CH2
	PORT_B_PIN_10_AF1_TIM2_CH3				= 1,                                          //!< PORT_B_PIN_10_AF1_TIM12_CH3
	PORT_B_PIN_11_AF1_TIM2_CH4				= 1,                                           //!< PORT_B_PIN_11_AF1_TIM2_CH4
	PORT_B_PIN_12_AF1_TIM1_BKIN				= 1,                                          //!< PORT_B_PIN_12_AF1_TIM1_BKIN
	PORT_B_PIN_13_AF1_TIM1_CH1N				= 1,                                          //!< PORT_B_PIN_13_AF1_TIM1_CH1N
	PORT_B_PIN_14_AF1_TIM1_CH2N			 	= 1,                                         //!< PORT_B_PIN_14_AF1_TIM1_CH2N
	PORT_B_PIN_15_AF1_TIM1_CH3N				= 1,                                          //!< PORT_B_PIN_15_AF1_TIM1_CH3N

	/*--------------------------- No AF1 In Port C ------------------------*/

	/*--------------------------- No AF1 In Port D ------------------------*/

	PORT_E_PIN_7_AF1_TIM1_ETR				= 1,                                            //!< PORT_E_PIN_7_AF1_TIM1_ETR
	PORT_E_PIN_8_AF1_TIM1_CH1N 				= 1,                                          //!< PORT_E_PIN_8_AF1_TIM1_CH1N
	PORT_E_PIN_9_AF1_TIM1_CH1 				= 1,                                           //!< PORT_E_PIN_9_AF1_TIM1_CH1
	PORT_E_PIN_10_AF1_TIM1_CH2N				= 1,                                          //!< PORT_E_PIN_10_AF1_TIM1_CH2N
	PORT_E_PIN_11_AF1_TIM1_CH2 				= 1,                                          //!< PORT_E_PIN_11_AF1_TIM1_CH2
	PORT_E_PIN_12_AF1_TIM1_CH3N	 			= 1,                                         //!< PORT_E_PIN_12_AF1_TIM1_CH3N
	PORT_E_PIN_13_AF1_TIM1_CH3 				= 1,                                          //!< PORT_E_PIN_13_AF1_TIM1_CH3
	PORT_E_PIN_14_AF1_TIM1_CH4 				= 1,                                          //!< PORT_E_PIN_14_AF1_TIM1_CH4
	PORT_E_PIN_15_AF1_TIM1_BKIN 			= 1,                                          //!< PORT_E_PIN_15_AF1_TIM1_BKIN

	/*--------------------------- No AF1 In Port F ------------------------*/

	/*--------------------------- No AF1 In Port G ------------------------*/

	/*--------------------------- No AF1 In Port H ------------------------*/


/***************************************************************************/

/*********** Alternative Function  = 2 For all Pins that have it ***********/
    PORT_A_PIN_0_AF2_TIM5_CH1				= 2,                                         //!< PORT_A_PIN_0_AF2_TIM5_CH1
	PORT_A_PIN_1_AF2_TIM5_CH2				= 2,                                            //!< PORT_A_PIN_1_AF2_TIM5_CH2
	PORT_A_PIN_2_AF2_TIM5_CH3				= 2,                                            //!< PORT_A_PIN_2_AF2_TIM5_CH3
	PORT_A_PIN_3_AF2_TIM5_CH4				= 2,                                            //!< PORT_A_PIN_3_AF2_TIM5_CH4
	PORT_A_PIN_6_AF2_TIM3_CH1				= 2,                                            //!< PORT_A_PIN_6_AF2_TIM3_CH1
	PORT_A_PIN_6_AF2_TIM3_CH2				= 2,                                            //!< PORT_A_PIN_6_AF2_TIM3_CH2

	PORT_B_PIN_0_AF2_TIM3_CH3				= 2,                                            //!< PORT_B_PIN_0_AF2_TIM3_CH3
	PORT_B_PIN_1_AF2_TIM3_CH4				= 2,                                            //!< PORT_B_PIN_1_AF2_TIM3_CH4
	PORT_B_PIN_4_AF2_TIM3_CH1				= 2,                                            //!< PORT_B_PIN_4_AF2_TIM3_CH1
	PORT_B_PIN_5_AF2_TIM3_CH2				= 2,                                            //!< PORT_B_PIN_5_AF2_TIM3_CH2
	PORT_B_PIN_6_AF2_TIM4_CH1				= 2,                                            //!< PORT_B_PIN_6_AF2_TIM4_CH1
	PORT_B_PIN_7_AF2_TIM4_CH2				= 2,                                            //!< PORT_B_PIN_7_AF2_TIM4_CH2
	PORT_B_PIN_8_AF2_TIM4_CH3				= 2,                                            //!< PORT_B_PIN_8_AF2_TIM4_CH3
	PORT_B_PIN_9_AF2_TIM4_CH4				= 2,                                            //!< PORT_B_PIN_9_AF2_TIM4_CH4

	PORT_C_PIN_6_AF2_TIM3_CH1 				= 2,                                           //!< PORT_C_PIN_6_AF2_TIM3_CH1
	PORT_C_PIN_7_AF2_TIM3_CH2 				= 2,                                           //!< PORT_C_PIN_7_AF2_TIM3_CH2
	PORT_C_PIN_8_AF2_TIM3_CH3 				= 2,                                           //!< PORT_C_PIN_8_AF2_TIM3_CH3
	PORT_C_PIN_9_AF2_TIM3_CH4 				= 2,                                           //!< PORT_C_PIN_9_AF2_TIM3_CH4

	PORT_D_PIN_2_AF2_TIM3_ETR 				= 2,                                           //!< PORT_D_PIN_2_AF2_TIM3_ETR
	PORT_D_PIN_12_AF2_TIM4_CH1 				= 2,                                          //!< PORT_D_PIN_12_AF2_TIM4_CH1
	PORT_D_PIN_13_AF2_TIM4_CH2 				= 2,                                          //!< PORT_D_PIN_13_AF2_TIM4_CH2
	PORT_D_PIN_14_AF2_TIM4_CH3 				= 2,                                          //!< PORT_D_PIN_14_AF2_TIM4_CH3
	PORT_D_PIN_15_AF2_TIM4_CH4 				= 2,                                          //!< PORT_D_PIN_15_AF2_TIM4_CH4

	PORT_E_PIN_0_AF2_TIM4_ETR 				= 2,                                           //!< PORT_E_PIN_0_AF2_TIM4_ETR

	/*--------------------------- No AF2 In Port F ------------------------*/

	/*--------------------------- No AF2 In Port G ------------------------*/

	/*--------------------------- No AF2 In Port H ------------------------*/

/***************************************************************************/

/*********** Alternative Function  = 3 For all Pins that have it ***********/
    PORT_A_PIN_0_AF3_TIM8_ETR    		    = 3,                                   //!< PORT_A_PIN_0_AF3_TIM8_ETR
	PORT_A_PIN_2_AF3_TIM9_CH1				= 3,                                            //!< PORT_A_PIN_2_AF3_TIM9_CH1
	PORT_A_PIN_3_AF3_TIM9_CH2				= 3,                                            //!< PORT_A_PIN_3_AF3_TIM9_CH2
	PORT_A_PIN_5_AF3_TIM8_CH1N				= 3,                                           //!< PORT_A_PIN_5_AF3_TIM8_CH1N
	PORT_A_PIN_6_AF3_TIM8_BKIN				= 3,                                           //!< PORT_A_PIN_6_AF3_TIM8_BKIN
	PORT_A_PIN_7_AF3_TIM8_CH1N				= 3,                                           //!< PORT_A_PIN_7_AF3_TIM8_CH1N

	PORT_B_PIN_0_AF3_TIM8_CH2N				= 3,                                           //!< PORT_B_PIN_0_AF3_TIM8_CH2N
	PORT_B_PIN_1_AF3_TIM8_CH3N				= 3,                                           //!< PORT_B_PIN_1_AF3_TIM8_CH3N
	PORT_B_PIN_8_AF3_TIM10_CH1				= 3,                                           //!< PORT_B_PIN_8_AF3_TIM10_CH1
	PORT_B_PIN_9_AF3_TIM11_CH1				= 3,                                           //!< PORT_B_PIN_9_AF3_TIM11_CH1
	PORT_B_PIN_14_AF3_TIM8_CH2N 			= 3,                                          //!< PORT_B_PIN_14_AF3_TIM8_CH2N
	PORT_B_PIN_15_AF3_TIM8_CH3N 			= 3,                                          //!< PORT_B_PIN_15_AF3_TIM8_CH3N

	PORT_C_PIN_6_AF3_TIM8_CH1 				= 3,                                           //!< PORT_C_PIN_6_AF3_TIM8_CH1
	PORT_C_PIN_7_AF3_TIM8_CH2 				= 3,                                           //!< PORT_C_PIN_7_AF3_TIM8_CH2
	PORT_C_PIN_8_AF3_TIM8_CH3			 	= 3,                                           //!< PORT_C_PIN_8_AF3_TIM8_CH3
	PORT_C_PIN_9_AF3_TIM8_CH4				= 3,                                            //!< PORT_C_PIN_9_AF3_TIM8_CH4

	/*--------------------------- No AF3 In Port D ------------------------*/

	PORT_E_PIN_5_AF3_TIM9_CH1 				= 3,                                           //!< PORT_E_PIN_5_AF3_TIM9_CH1
	PORT_E_PIN_6_AF3_TIM9_CH2 				= 3,                                           //!< PORT_E_PIN_6_AF3_TIM9_CH2

	PORT_F_PIN_6_AF3_TIM10_CH1 				= 3,                                          //!< PORT_F_PIN_6_AF3_TIM10_CH1
	PORT_F_PIN_7_AF3_TIM11_CH1 				= 3,                                          //!< PORT_F_PIN_7_AF3_TIM11_CH1

	/*--------------------------- No AF3 In Port G ------------------------*/

	/*--------------------------- No AF3 In Port H ------------------------*/

/***************************************************************************/

/*********** Alternative Function  = 4 For all Pins that have it ***********/
    PORT_A_PIN_8_AF4_I2C3_SCL     			= 4,                                     //!< PORT_A_PIN_8_AF4_I2C3_SCL
	PORT_A_PIN_9_AF4_I2C3_SMBA				= 4,                                           //!< PORT_A_PIN_9_AF4_I2C3_SMBA

	PORT_B_PIN_5_AF4_I2C1_SMBA				= 4,                                           //!< PORT_B_PIN_5_AF4_I2C1_SMBA
	PORT_B_PIN_6_AF4_I2C1_SCL				= 4,                                            //!< PORT_B_PIN_6_AF4_I2C1_SCL
	PORT_B_PIN_7_AF4_I2C1_SDA			 	= 4,                                           //!< PORT_B_PIN_7_AF4_I2C1_SDA
	PORT_B_PIN_8_AF4_I2C1_SCL				= 4,                                            //!< PORT_B_PIN_8_AF4_I2C1_SCL
	PORT_B_PIN_9_AF4_I2C1_SDA				= 4,                                            //!< PORT_B_PIN_9_AF4_I2C1_SDA
	PORT_B_PIN_10_AF4_I2C2_SCL				= 4,                                           //!< PORT_B_PIN_10_AF4_I2C2_SCL
	PORT_B_PIN_11_AF4_I2C2_SDA				= 4,                                           //!< PORT_B_PIN_11_AF4_I2C2_SDA
	PORT_B_PIN_12_AF4_I2C2_SMBA				= 4,                                          //!< PORT_B_PIN_12_AF4_I2C2_SMBA

	PORT_C_PIN_9_AF4_I2C3_SDA				= 4,                                            //!< PORT_C_PIN_9_AF4_I2C3_SDA

	/*--------------------------- No AF4 In Port D ------------------------*/

	/*--------------------------- No AF4 In Port E ------------------------*/

	PORT_F_PIN_0_AF4_I2C2_SDA 				= 4,                                           //!< PORT_F_PIN_0_AF4_I2C2_SDA
	PORT_F_PIN_1_AF4_I2C2_SCL 				= 4,                                           //!< PORT_F_PIN_1_AF4_I2C2_SCL
	PORT_F_PIN_2_AF4_I2C2_SMBA 				= 4,                                          //!< PORT_F_PIN_2_AF4_I2C2_SMBA

	/*--------------------------- No AF4 In Port G ------------------------*/

	/*--------------------------- No AF4 In Port H ------------------------*/


/***************************************************************************/

/*********** Alternative Function  = 5 For all Pins that have it ***********/
    PORT_A_PIN_4_AF5_SPI1_NSS     			= 5,                                     //!< PORT_A_PIN_4_AF5_SPI1_NSS
	PORT_A_PIN_5_AF5_SPI1_SCK				= 5,                                            //!< PORT_A_PIN_5_AF5_SPI1_SCK
	PORT_A_PIN_6_AF5_SPI1_MISO				= 5,                                           //!< PORT_A_PIN_6_AF5_SPI1_MISO
	PORT_A_PIN_7_AF5_SPI1_MOSI				= 5,                                           //!< PORT_A_PIN_7_AF5_SPI1_MOSI
	PORT_A_PIN_15_AF5_SPI1_NSS				= 5,                                           //!< PORT_A_PIN_15_AF5_SPI1_NSS

	PORT_B_PIN_3_AF5_SPI1_SCK				= 5,                                            //!< PORT_B_PIN_3_AF5_SPI1_SCK
	PORT_B_PIN_4_AF5_SPI1_MISO				= 5,                                           //!< PORT_B_PIN_4_AF5_SPI1_MISO
	PORT_B_PIN_5_AF5_SPI1_MOSI				= 5,                                           //!< PORT_B_PIN_5_AF5_SPI1_MOSI
	PORT_B_PIN_9_AF5_SPI2_NSS				= 5, /* Note: PB9 AF5 Has 2 modes */            //!< PORT_B_PIN_9_AF5_SPI2_NSS
	PORT_B_PIN_9_AF5_I2S2_WS				= 5, /* SPI2 NSS & I2S2 WS	      */              //!< PORT_B_PIN_9_AF5_I2S2_WS
	PORT_B_PIN_10_AF5_SPI2_SCK				= 5, /* Note: PB10 AF5 Has 2 modes*/           //!< PORT_B_PIN_10_AF5_SPI2_SCK
	PORT_B_PIN_10_AF5_I2S2_CK				= 5, /* SPI2 SCK & I2S2 CK	      */             //!< PORT_B_PIN_10_AF5_I2S2_CK
	PORT_B_PIN_12_AF5_SPI2_NSS 				= 5, /* Note: PB12 AF5 has 2 modes*/          //!< PORT_B_PIN_12_AF5_SPI2_NSS
	PORT_B_PIN_12_AF5_I2S2_WS 				= 5, /* SPI2 NSS & I2S2 WS 		  */              //!< PORT_B_PIN_12_AF5_I2S2_WS
	PORT_B_PIN_13_AF5_SPI2_SCK			 	= 5, /* NoteL PB13 AF5 has 2 modes*/          //!< PORT_B_PIN_13_AF5_SPI2_SCK
	PORT_B_PIN_13_AF5_I2S2_CK 				= 5, /* SPI2 SCK & I2S2 CK 		  */              //!< PORT_B_PIN_13_AF5_I2S2_CK
	PORT_B_PIN_14_AF5_SPI2_MISO 			= 5,                                          //!< PORT_B_PIN_14_AF5_SPI2_MISO
	PORT_B_PIN_15_AF5_SPI2_MOSI 			= 5, /*Note: PB15 AF5 has 2 modes */          //!< PORT_B_PIN_15_AF5_SPI2_MOSI
	PORT_B_PIN_15_AF5_I2S2_SD 				= 5, /* SPI2 MOSI & I2S2 SD 	  */              //!< PORT_B_PIN_15_AF5_I2S2_SD

	PORT_C_PIN_2_AF5_SPI2_MISO 				= 5,                                          //!< PORT_C_PIN_2_AF5_SPI2_MISO
	PORT_C_PIN_3_AF5_SPI2_MOSI			 	= 5, /* Note: PC3 AF5 has 2 modes */          //!< PORT_C_PIN_3_AF5_SPI2_MOSI
	PORT_C_PIN_3_AF5_I2S2_SD 				= 5, /* SPI2 MOSI & I2S2 SD 	  */               //!< PORT_C_PIN_3_AF5_I2S2_SD

	PORT_C_PIN_6_AF5_I2S2_MCK			 	= 5,                                           //!< PORT_C_PIN_6_AF5_I2S2_MCK
	PORT_C_PIN_9_AF5_I2S_CKIN 				= 5,                                           //!< PORT_C_PIN_9_AF5_I2S_CKIN
	PORT_C_PIN_11_AF5_I2S3_EXT_SD 			= 5,                                        //!< PORT_C_PIN_11_AF5_I2S3_EXT_SD

	PORT_D_PIN_3_AF5_SPI2_SCK 				= 5, /* Note: PD3 AF5 has 2 modes */           //!< PORT_D_PIN_3_AF5_SPI2_SCK
	PORT_D_PIN_3_AF5_I2S2_CK 				= 5, /* SPI2 SCK & I2S2 CK 		  */               //!< PORT_D_PIN_3_AF5_I2S2_CK
	PORT_D_PIN_6_AF5_SPI3_MOSI 				= 5, /* Note: PD6 AF5 has 2 modes */          //!< PORT_D_PIN_6_AF5_SPI3_MOSI
	PORT_D_PIN_6_AF5_I2S3_SD 				= 5, /* SPI3 MOSI & I2S3 SD 	  */               //!< PORT_D_PIN_6_AF5_I2S3_SD

	PORT_E_PIN_2_AF5_SPI4_SCK 				= 5,                                           //!< PORT_E_PIN_2_AF5_SPI4_SCK
	PORT_E_PIN_4_AF5_SPI4_NSS 				= 5,                                           //!< PORT_E_PIN_4_AF5_SPI4_NSS
	PORT_E_PIN_5_AF5_SPI4_MISO			 	= 5,                                          //!< PORT_E_PIN_5_AF5_SPI4_MISO
	PORT_E_PIN_6_AF5_SPI4_MOSI 				= 5,                                          //!< PORT_E_PIN_6_AF5_SPI4_MOSI
	PORT_E_PIN_11_AF5_SPI4_NSS 				= 5,                                          //!< PORT_E_PIN_11_AF5_SPI4_NSS
	PORT_E_PIN_12_AF5_SPI4_SCK 				= 5,                                          //!< PORT_E_PIN_12_AF5_SPI4_SCK
	PORT_E_PIN_13_AF5_SPI4_MISO 			= 5,                                          //!< PORT_E_PIN_13_AF5_SPI4_MISO
	PORT_E_PIN_14_AF5_SPI4_MOSI 			= 5,                                          //!< PORT_E_PIN_14_AF5_SPI4_MOSI

	PORT_F_PIN_6_AF5_SPI5_NSS 				= 5,                                           //!< PORT_F_PIN_6_AF5_SPI5_NSS
	PORT_F_PIN_7_AF5_SPI5_SCK 				= 5,                                           //!< PORT_F_PIN_7_AF5_SPI5_SCK
	PORT_F_PIN_8_AF5_SPI5_MISO 				= 5,                                          //!< PORT_F_PIN_8_AF5_SPI5_MISO
	PORT_F_PIN_9_AF5_SPI5_MOSI 				= 5,                                          //!< PORT_F_PIN_9_AF5_SPI5_MOSI
	PORT_F_PIN_11_AF5_SPI5_MOSI 			= 5,                                          //!< PORT_F_PIN_11_AF5_SPI5_MOSI

	PORT_G_PIN_8_AF5_SPI5_NSS 				= 5,                                           //!< PORT_G_PIN_8_AF5_SPI5_NSS
	PORT_G_PIN_12_AF5_SPI6_MISO 			= 5,                                          //!< PORT_G_PIN_12_AF5_SPI6_MISO
	PORT_G_PIN_13_AF5_SPI6_SCK 				= 5,                                          //!< PORT_G_PIN_13_AF5_SPI6_SCK
	PORT_G_PIN_14_AF5_SPI6_MOSI 			= 5,                                          //!< PORT_G_PIN_14_AF5_SPI6_MOSI

	/*--------------------------- No AF5 In Port H ------------------------*/

/***************************************************************************/

/************ Alternative Function  = 6 For all Pins that have it *************/
    PORT_A_PIN_4_AF6_SPI3_NSS				= 6, /* Note: PA6 AF6 Has 2 modes */         //!< PORT_A_PIN_4_AF6_SPI3_NSS
	PORT_A_PIN_4_AF6_I2S3_WS				= 6, /* SPI3 NSS & I2S3 WS 		  */                //!< PORT_A_PIN_4_AF6_I2S3_WS
	PORT_A_PIN_15_AF6_SPI3_NSS 				= 6, /* Note: PA15 AF6 Has 2 modes*///!< PORT_A_PIN_15_AF6_SPI3_NSS
	PORT_A_PIN_15_AF6_I2S3_WS 				= 6, /* SPI3 NSS & I2S3 WS 		  */    //!< PORT_A_PIN_15_AF6_I2S3_WS

	PORT_B_PIN_3_AF6_SPI3_SCK				= 6, /* Note: PB3 AF6 Has 2 modes */            //!< PORT_B_PIN_3_AF6_SPI3_SCK
	PORT_B_PIN_3_AF6_I2S3_CK				= 6, /* SPI3 SCK & I2S3 CK	      */              //!< PORT_B_PIN_3_AF6_I2S3_CK
	PORT_B_PIN_4_AF6_SPI3_MISO				= 6,                                           //!< PORT_B_PIN_4_AF6_SPI3_MISO
	PORT_B_PIN_5_AF6_SPI3_MOSI				= 6, /* Note: PB5 AF6 has 2 modes */           //!< PORT_B_PIN_5_AF6_SPI3_MOSI
	PORT_B_PIN_5_AF6_I2S3_SD			    = 6, /* SPI3 MOSI & I2S3 SD	      */          //!< PORT_B_PIN_5_AF6_I2S3_SD
	PORT_B_PIN_14_AF6_I2S2_EXT_SD 			= 6,                                         //!< PORT_B_PIN_14_AF6_I2S2_EXT_SD

	PORT_C_PIN_2_AF6_I2S2_EXT_SD 			= 6,                                         //!< PORT_C_PIN_2_AF6_I2S2_EXT_SD
	PORT_C_PIN_7_AF6_I2S3_MCK 				= 6,                                           //!< PORT_C_PIN_7_AF6_I2S3_MCK
	PORT_C_PIN_10_AF6_SPI3_SCK 				= 6, /* Note: PC10 AF6 has 2 modes*/          //!< PORT_C_PIN_10_AF6_SPI3_SCK
	PORT_C_PIN_10_AF6_I2S3_CK 				= 6, /* SPI3 SCK & I2S3 CK 		  */              //!< PORT_C_PIN_10_AF6_I2S3_CK
	PORT_C_PIN_11_AF6_SPI3_MISO 			= 6,                                          //!< PORT_C_PIN_11_AF6_SPI3_MISO
	PORT_C_PIN_12_AF6_SPI3_MOSI 			= 6, /* Note: PC12 AF6 has 2 modes*/          //!< PORT_C_PIN_12_AF6_SPI3_MOSI
	PORT_C_PIN_12_AF6_I2S3_SD 				= 6, /* SPI3 MOSI & I2S3 SD	 	  */             //!< PORT_C_PIN_12_AF6_I2S3_SD

	PORT_D_PIN_6_AF6_SAI1_SD_A 				= 6,                                          //!< PORT_D_PIN_6_AF6_SAI1_SD_A

	PORT_E_PIN_2_AF6_SAI1_MCLK_A 			= 6,                                         //!< PORT_E_PIN_2_AF6_SAI1_MCLK_A
	PORT_E_PIN_3_AF6_SAI1_SD_B 				= 6,                                          //!< PORT_E_PIN_3_AF6_SAI1_SD_B
	PORT_E_PIN_4_AF6_SAI1_FS_A 				= 6,                                          //!< PORT_E_PIN_4_AF6_SAI1_FS_A
	PORT_E_PIN_5_AF6_SAI1_SCK_A 			= 6,                                          //!< PORT_E_PIN_5_AF6_SAI1_SCK_A
	PORT_E_PIN_6_AF6_SAI1_SD_A 				= 6,                                          //!< PORT_E_PIN_6_AF6_SAI1_SD_A

	PORT_F_PIN_6_AF6_SAI1_SD_B 				= 6,                                          //!< PORT_F_PIN_6_AF6_SAI1_SD_B
	PORT_F_PIN_7_AF6_SAI1_MCLK_B 			= 6,                                         //!< PORT_F_PIN_7_AF6_SAI1_MCLK_B
	PORT_F_PIN_8_AF6_SAI1_SCK_B 			= 6,                                          //!< PORT_F_PIN_8_AF6_SAI1_SCK_B
	PORT_F_PIN_9_AF6_SAI1_FS_B 				= 6,                                          //!< PORT_F_PIN_9_AF6_SAI1_FS_B

	/*--------------------------- No AF6 In Port G ------------------------*/

	/*--------------------------- No AF6 In Port H ------------------------*/


/***************************************************************************/

/*********** Alternative Function  = 7 For all Pins that have it ***********/
    PORT_A_PIN_0_AF7_USART2_CTS				= 7,                                       //!< PORT_A_PIN_0_AF7_USART2_CTS
	PORT_A_PIN_1_AF7_USART2_RTS			    = 7,                                       //!< PORT_A_PIN_1_AF7_USART2_RTS
	PORT_A_PIN_2_AF7_USART2_TX				= 7,                                           //!< PORT_A_PIN_2_AF7_USART2_TX
	PORT_A_PIN_3_AF7_USART2_RX				= 7,                                           //!< PORT_A_PIN_3_AF7_USART2_RX
	PORT_A_PIN_4_AF7_USART2_CK				= 7,                                           //!< PORT_A_PIN_4_AF7_USART2_CK
	PORT_A_PIN_8_AF7_USART1_CK				= 7,                                           //!< PORT_A_PIN_8_AF7_USART1_CK
	PORT_A_PIN_9_AF7_USART1_TX				= 7,                                           //!< PORT_A_PIN_9_AF7_USART1_TX
	PORT_A_PIN_10_AF7_USART1_RX				= 7,                                          //!< PORT_A_PIN_10_AF7_USART1_RX
	PORT_A_PIN_11_AF7_USART1_CTS			= 7,                                          //!< PORT_A_PIN_11_AF7_USART1_CTS
	PORT_A_PIN_12_AF7_USART1_RTS			= 7,                                          //!< PORT_A_PIN_12_AF7_USART1_RTS

	PORT_B_PIN_4_AF7_I2S3_EXT_SD			= 7,                                          //!< PORT_B_PIN_4_AF7_I2S3_EXT_SD
	PORT_B_PIN_6_AF7_USART1_TX				= 7,                                           //!< PORT_B_PIN_6_AF7_USART1_TX
	PORT_B_PIN_7_AF7_USART1_RX				= 7,                                           //!< PORT_B_PIN_7_AF7_USART1_RX
	PORT_B_PIN_10_AF7_USART3_TX				= 7,                                          //!< PORT_B_PIN_10_AF7_USART3_TX
	PORT_B_PIN_11_AF7_USART3_RX				= 7,                                          //!< PORT_B_PIN_11_AF7_USART3_RX
	PORT_B_PIN_12_AF7_USART3_CK 			= 7,                                          //!< PORT_B_PIN_12_AF7_USART3_CK
	PORT_B_PIN_13_AF7_USART3_CTS 			= 7,                                         //!< PORT_B_PIN_13_AF7_USART3_CTS
	PORT_B_PIN_14_AF7_USART3_RTS 			= 7,                                         //!< PORT_B_PIN_14_AF7_USART3_RTS

	PORT_C_PIN_10_AF7_USART3_TX 			= 7,                                          //!< PORT_C_PIN_10_AF7_USART3_TX
	PORT_C_PIN_11_AF7_USART3_RX 			= 7,                                          //!< PORT_C_PIN_11_AF7_USART3_RX
	PORT_C_PIN_12_AF7_USART3_CK 			= 7,                                          //!< PORT_C_PIN_12_AF7_USART3_CK

	PORT_D_PIN_3_AF7_USART2_CTS 			= 7,                                          //!< PORT_D_PIN_3_AF7_USART2_CTS
	PORT_D_PIN_4_AF7_USART2_RTS 			= 7,                                          //!< PORT_D_PIN_4_AF7_USART2_RTS
	PORT_D_PIN_5_AF7_USART2_TX 				= 7,                                          //!< PORT_D_PIN_5_AF7_USART2_TX
	PORT_D_PIN_6_AF7_USART2_RX 				= 7,                                          //!< PORT_D_PIN_6_AF7_USART2_RX
	PORT_D_PIN_7_AF7_USART2_CK			 	= 7,                                          //!< PORT_D_PIN_7_AF7_USART2_CK
	PORT_D_PIN_8_AF7_USART3_TX 				= 7,                                          //!< PORT_D_PIN_8_AF7_USART3_TX
	PORT_D_PIN_9_AF7_USART3_RX 				= 7,                                          //!< PORT_D_PIN_9_AF7_USART3_RX
	PORT_D_PIN_10_AF7_USART3_CK 			= 7,                                          //!< PORT_D_PIN_10_AF7_USART3_CK
	PORT_D_PIN_11_AF7_USART3_CTS 			= 7,                                         //!< PORT_D_PIN_11_AF7_USART3_CTS
	PORT_D_PIN_12_AF7_USART3_RTS			= 7,                                          //!< PORT_D_PIN_12_AF7_USART3_RTS

	/*--------------------------- No AF7 In Port G ------------------------*/

	/*--------------------------- No AF7 In Port H ------------------------*/



/***************************************************************************/

/*********** Alternative Function  = 8 For all Pins that have it ***********/
    PORT_A_PIN_0_AF8_UART4_TX				= 8,                                         //!< PORT_A_PIN_0_AF8_UART4_TX
	PORT_A_PIN_1_AF8_UART4_RX				= 8,                                            //!< PORT_A_PIN_1_AF8_UART4_RX

	/*--------------------------- No AF8 In Port B ------------------------*/

	PORT_C_PIN_6_AF8_USART6_TX				= 8,                                           //!< PORT_C_PIN_6_AF8_USART6_TX
	PORT_C_PIN_7_AF8_USART6_RX 				= 8,                                          //!< PORT_C_PIN_7_AF8_USART6_RX
	PORT_C_PIN_8_AF8_USART6_CK 				= 8,                                          //!< PORT_C_PIN_8_AF8_USART6_CK
	PORT_C_PIN_10_AF8_UART4_TX 				= 8,                                          //!< PORT_C_PIN_10_AF8_UART4_TX
	PORT_C_PIN_11_AF8_UART4_RX 				= 8,                                          //!< PORT_C_PIN_11_AF8_UART4_RX
	PORT_C_PIN_12_AF8_UART5_TX 				= 8,                                          //!< PORT_C_PIN_12_AF8_UART5_TX

	PORT_D_PIN_2_AF8_UART5_RX 				= 8,                                           //!< PORT_D_PIN_2_AF8_UART5_RX

	PORT_E_PIN_0_AF8_UART8_RX 				= 8,                                           //!< PORT_E_PIN_0_AF8_UART8_RX
	PORT_E_PIN_1_AF8_UART8_TX 				= 8,                                           //!< PORT_E_PIN_1_AF8_UART8_TX
	PORT_E_PIN_7_AF8_UART7_RX 				= 8,                                           //!< PORT_E_PIN_7_AF8_UART7_RX
	PORT_E_PIN_8_AF8_UART7_TX 				= 8,                                           //!< PORT_E_PIN_8_AF8_UART7_TX

	PORT_F_PIN_6_AF8_UART7_RX 				= 8,                                           //!< PORT_F_PIN_6_AF8_UART7_RX
	PORT_F_PIN_7_AF8_UART7_TX 				= 8,                                           //!< PORT_F_PIN_7_AF8_UART7_TX

	PORT_G_PIN_7_AF8_USART6_CK 				= 8,                                          //!< PORT_G_PIN_7_AF8_USART6_CK
	PORT_G_PIN_8_AF8_USART6_RTS 			= 8,                                          //!< PORT_G_PIN_8_AF8_USART6_RTS
	PORT_G_PIN_9_AF8_USART6_RX 				= 8,                                          //!< PORT_G_PIN_9_AF8_USART6_RX
	PORT_G_PIN_12_AF8_USART6_RTS 			= 8,                                         //!< PORT_G_PIN_12_AF8_USART6_RTS
	PORT_G_PIN_13_AF8_USART6_CTS 			= 8,                                         //!< PORT_G_PIN_13_AF8_USART6_CTS
	PORT_G_PIN_14_AF8_USART6_TX 			= 8,                                          //!< PORT_G_PIN_14_AF8_USART6_TX
	PORT_G_PIN_15_AF8_USART6_CTS			= 8,                                          //!< PORT_G_PIN_15_AF8_USART6_CTS

	/*--------------------------- No AF8 In Port H ------------------------*/


/***************************************************************************/

/*********** Alternative Function  = 9 For all Pins that have it ***********/
    PORT_A_PIN_6_AF9_TIM13_CH1				= 9,                                        //!< PORT_A_PIN_6_AF9_TIM13_CH1
	PORT_A_PIN_7_AF9_TIM14_CH1				= 9,                                           //!< PORT_A_PIN_7_AF9_TIM14_CH1
	PORT_A_PIN_11_AF9_CAN1_RX				= 9,                                            //!< PORT_A_PIN_11_AF9_CAN1_RX
	PORT_A_PIN_12_AF9_CAN1_TX				= 9,                                            //!< PORT_A_PIN_12_AF9_CAN1_TX

	PORT_B_PIN_0_AF9_LCD_R3					= 9,                                             //!< PORT_B_PIN_0_AF9_LCD_R3
	PORT_B_PIN_1_AF9_LCD_R6					= 9,                                             //!< PORT_B_PIN_1_AF9_LCD_R6
	PORT_B_PIN_5_AF9_CAN2_RX				= 9,                                             //!< PORT_B_PIN_5_AF9_CAN2_RX
	PORT_B_PIN_6_AF9_CAN2_TX				= 9,                                             //!< PORT_B_PIN_6_AF9_CAN2_TX
	PORT_B_PIN_8_AF9_CAN1_RX				= 9,                                             //!< PORT_B_PIN_8_AF9_CAN1_RX
	PORT_B_PIN_9_AF9_CAN1_TX				= 9,                                             //!< PORT_B_PIN_9_AF9_CAN1_TX
	PORT_B_PIN_12_AF9_CAN2_RX 				= 9,                                           //!< PORT_B_PIN_12_AF9_CAN2_RX
	PORT_B_PIN_13_AF9_CAN2_TX 				= 9,                                           //!< PORT_B_PIN_13_AF9_CAN2_TX
	PORT_B_PIN_14_AF9_TIM12_CH1				= 9,                                          //!< PORT_B_PIN_14_AF9_TIM12_CH1
	PORT_B_PIN_15_AF9_TIM12_CH2				= 9,                                          //!< PORT_B_PIN_15_AF9_TIM12_CH2

	/*--------------------------- No AF9 In Port C ------------------------*/

	PORT_D_PIN_0_AF9_CAN1_RX				= 9,                                             //!< PORT_D_PIN_0_AF9_CAN1_RX
	PORT_D_PIN_1_AF9_CAN1_TX 				= 9,                                            //!< PORT_D_PIN_1_AF9_CAN1_TX

	/*--------------------------- No AF9 In Port E ------------------------*/

	PORT_F_PIN_8_AF9_TIM13_CH1				= 9,                                           //!< PORT_F_PIN_8_AF9_TIM13_CH1
	PORT_F_PIN_9_AF9_TIM14_CH1				= 9,                                           //!< PORT_F_PIN_9_AF9_TIM14_CH1


	PORT_G_PIN_10_AF9_LCD_G3				= 9,                                             //!< PORT_G_PIN_10_AF9_LCD_G3
	PORT_G_PIN_12_AF9_LCD_B4				= 9,                                             //!< PORT_G_PIN_12_AF9_LCD_B4

	/*--------------------------- No AF9 In Port H ------------------------*/



/***************************************************************************/

/*********** Alternative Function  = 10 For all Pins that have it **********/
	PORT_A_PIN_3_AF10_OTG_HS_ULPI_D0		= 10,                                      //!< PORT_A_PIN_3_AF10_OTG_HS_ULPI_D0
	PORT_A_PIN_5_AF10_OTG_HS_ULPI_CK		= 10,                                      //!< PORT_A_PIN_5_AF10_OTG_HS_ULPI_CK
	PORT_A_PIN_8_AF10_OTG_FS_SOF			= 10,                                         //!< PORT_A_PIN_8_AF10_OTG_FS_SOF
	PORT_A_PIN_10_AF10_OTG_FS_ID			= 10,                                         //!< PORT_A_PIN_10_AF10_OTG_FS_ID
	PORT_A_PIN_11_AF10_OTG_FS_DM			= 10,                                         //!< PORT_A_PIN_11_AF10_OTG_FS_DM
	PORT_A_PIN_12_AF10_OTG_FS_DP			= 10,                                         //!< PORT_A_PIN_12_AF10_OTG_FS_DP

	PORT_B_PIN_0_AF10_OTG_HS_ULPI_D1		= 10,                                      //!< PORT_B_PIN_0_AF10_OTG_HS_ULPI_D1
	PORT_B_PIN_1_AF10_OTG_HS_ULPI_D2		= 10,                                      //!< PORT_B_PIN_1_AF10_OTG_HS_ULPI_D2
	PORT_B_PIN_5_AF10_OTG_HS_ULPI_D7		= 10,                                      //!< PORT_B_PIN_5_AF10_OTG_HS_ULPI_D7
	PORT_B_PIN_10_AF10_OTG_HS_ULPI_D3		= 10,                                     //!< PORT_B_PIN_10_AF10_OTG_HS_ULPI_D3
	PORT_B_PIN_11_AF10_OTG_HS_ULPI_D4		= 10,                                     //!< PORT_B_PIN_11_AF10_OTG_HS_ULPI_D4
	PORT_B_PIN_12_AF10_OTG_HS_ULPI_D5		= 10,                                     //!< PORT_B_PIN_12_AF10_OTG_HS_ULPI_D5
	PORT_B_PIN_13_AF10_OTG_HS_ULPI_D6		= 10,                                     //!< PORT_B_PIN_13_AF10_OTG_HS_ULPI_D6

	PORT_C_PIN_0_AF10_OTG_HS_ULPI_STP		= 10,                                     //!< PORT_C_PIN_0_AF10_OTG_HS_ULPI_STP
	PORT_C_PIN_2_AF10_OTG_HS_ULPI_DIR		= 10,                                     //!< PORT_C_PIN_2_AF10_OTG_HS_ULPI_DIR
	PORT_C_PIN_3_AF10_OTG_HS_ULPI_NXT		= 10,                                     //!< PORT_C_PIN_3_AF10_OTG_HS_ULPI_NXT

	/*--------------------------- No AF10 In Port D ------------------------*/

	/*--------------------------- No AF10 In Port E ------------------------*/

	/*--------------------------- No AF10 In Port F ------------------------*/

	/*--------------------------- No AF10 In Port G ------------------------*/

	/*--------------------------- No AF10 In Port H ------------------------*/



/***************************************************************************/

/*********** Alternative Function  = 11 For all Pins that have it **********/
	PORT_A_PIN_0_AF11_ETH_MII_CRS			= 11,                                        //!< PORT_A_PIN_0_AF11_ETH_MII_CRS
	PORT_A_PIN_1_AF11_ETH_MII_RX_CLK		= 11, /* Note: PA1 AF11 has 2 modes  */    //!< PORT_A_PIN_1_AF11_ETH_MII_RX_CLK
	PORT_A_PIN_1_AF11_ETH_RMII_REF_CLK		= 11, /* ETH (MII RX & RMII REF)CLK  */  //!< PORT_A_PIN_1_AF11_ETH_RMII_REF_CLK
	PORT_A_PIN_2_AF11_ETH_MDIO				= 11,                                          //!< PORT_A_PIN_2_AF11_ETH_MDIO
	PORT_A_PIN_3_AF11_ETH_MII_COL			= 11,                                        //!< PORT_A_PIN_3_AF11_ETH_MII_COL
	PORT_A_PIN_7_AF11_ETH_MII_RX_DV			= 11, /* Note: PA7 AF11 has 2 modes  */    //!< PORT_A_PIN_7_AF11_ETH_MII_RX_DV
	PORT_A_PIN_7_AF11_ETH_RMII_CRS_DV		= 11, /* ETH(MII RX DV & RMII CRS DV)*/   //!< PORT_A_PIN_7_AF11_ETH_RMII_CRS_DV

	PORT_B_PIN_0_AF11_ETH_MII_RXD2			= 11,                                       //!< PORT_B_PIN_0_AF11_ETH_MII_RXD2
	PORT_B_PIN_1_AF11_ETH_MII_RXD3			= 11,                                       //!< PORT_B_PIN_1_AF11_ETH_MII_RXD3
	PORT_B_PIN_5_AF11_ETH_PPS_OUT			= 11,                                        //!< PORT_B_PIN_5_AF11_ETH_PPS_OUT
	PORT_B_PIN_8_AF11_ETH_MII_TXD3			= 11,                                       //!< PORT_B_PIN_8_AF11_ETH_MII_TXD3
	PORT_B_PIN_10_AF11_ETH_MII_RX_ER		= 11,                                      //!< PORT_B_PIN_10_AF11_ETH_MII_RX_ER
	PORT_B_PIN_11_AF11_ETH_MII_TX_EN 		= 11, /* Note: PB11 AF11 has 2 modes */   //!< PORT_B_PIN_11_AF11_ETH_MII_TX_EN
	PORT_B_PIN_11_AF11_ETH_RMII_TX_EN 		= 11, /* ETH (MII TX & RMII TX )EN   */  //!< PORT_B_PIN_11_AF11_ETH_RMII_TX_EN
	PORT_B_PIN_12_AF11_ETH_MII_TXD0 		= 11, /* Note: PB12 AF11 has 2 modes */    //!< PORT_B_PIN_12_AF11_ETH_MII_TXD0
	PORT_B_PIN_12_AF11_ETH_RMII_TXD0 		= 11, /* ETH (MII TXD0 & RMII TXD0)  */   //!< PORT_B_PIN_12_AF11_ETH_RMII_TXD0
	PORT_B_PIN_12_AF11_ETH_MII_TXD1 		= 11, /* Note: PB13 AF11 has 2 modes */    //!< PORT_B_PIN_12_AF11_ETH_MII_TXD
	PORT_B_PIN_12_AF11_ETH_RMII_TXD1 		= 11, /* ETH (MII TXD1 & RMII TXD1    */   //!< PORT_B_PIN_12_AF11_ETH_RMII_TXD1

	PORT_C_PIN_1_AF11_ETH_MDC 				= 11,                                          //!< PORT_C_PIN_1_AF11_ETH_MDC
	PORT_C_PIN_2_AF11_ETH_MII_TXD2 			= 11,                                      //!< PORT_C_PIN_2_AF11_ETH_MII_TXD2
	PORT_C_PIN_3_AF11_ETH_MII_CLK 			= 11,                                       //!< PORT_C_PIN_3_AF11_ETH_MII_CLK
	PORT_C_PIN_4_AF11_ETH_MII_RXD0 			= 11, /* Note: PC4 AF11 has 2 modes  */    //!< PORT_C_PIN_4_AF11_ETH_MII_RXD0
	PORT_C_PIN_4_AF11_ETH_RMII_RXD0			= 11, /* ETH (MII RXD0 & RMII RXD0)  */    //!< PORT_C_PIN_4_AF11_ETH_RMII_RXD0
	PORT_C_PIN_5_AF11_ETH_MII_RXD1 			= 11, /* Note: PC5 AF11 has 2 modes  */    //!< PORT_C_PIN_5_AF11_ETH_MII_RXD1
	PORT_C_PIN_5_AF11_ETH_RMII_RXD1			= 11, /* ETH (MII RXD1 & RMII RXD1)  */    //!< PORT_C_PIN_5_AF11_ETH_RMII_RXD1

	/*------------------------------ No AF11 In Port D --------------------------*/

	PORT_E_PIN_2_AF11_ETH_MII_TXD3			= 11,                                       //!< PORT_E_PIN_2_AF11_ETH_MII_TXD3

	PORT_G_PIN_8_AF11_ETH_PPS_OUT			= 11,                                        //!< PORT_G_PIN_8_AF11_ETH_PPS_OUT
	PORT_G_PIN_11_AF11_ETH_MII_TX_EN 		= 11, /* Note: PG11 AF11 has 2 modes  */  //!< PORT_G_PIN_11_AF11_ETH_MII_TX_EN
	PORT_G_PIN_11_AF11_ETH_RMII_TX_EN 		= 11, /* ETH (MII TX EN & RMII TX EN) */ //!< PORT_G_PIN_11_AF11_ETH_RMII_TX_EN
	PORT_G_PIN_13_AF11_ETH_MII_TXD0_EN 		= 11, /* Note: PG12 AF11 has 2 modes  *///!< PORT_G_PIN_13_AF11_ETH_MII_TXD0_EN
	PORT_G_PIN_13_AF11_ETH_RMII_TXD0_EN 	= 11, /* ETH (MII TXD0 & RMII TXD0)   *///!< PORT_G_PIN_13_AF11_ETH_RMII_TXD0_EN
	PORT_G_PIN_14_AF11_ETH_MII_TXD1_EN 		= 11, /* Note: PG13 AF11 has 2 modes  *///!< PORT_G_PIN_14_AF11_ETH_MII_TXD1_EN
	PORT_G_PIN_14_AF11_ETH_RMII_TXD1_EN 	= 11, /* ETH (MII TXD1 & RMII TXD1)   *///!< PORT_G_PIN_14_AF11_ETH_RMII_TXD1_EN

	/*------------------------------ No AF11 In Port H --------------------------*/



/***************************************************************************/

/*********** Alternative Function  = 12 For all Pins that have it **********/
	PORT_A_PIN_4_AF12_OTG_HS_SOF			= 12,                                         //!< PORT_A_PIN_4_AF12_OTG_HS_SOF

	PORT_B_PIN_5_AF12_FMC_SDCKE1			= 12,                                         //!< PORT_B_PIN_5_AF12_FMC_SDCKE1
	PORT_B_PIN_6_AF12_FMC_SDNE1				= 12,                                         //!< PORT_B_PIN_6_AF12_FMC_SDNE1
	PORT_B_PIN_7_AF12_FMC_NL				= 12,                                            //!< PORT_B_PIN_7_AF12_FMC_NL
	PORT_B_PIN_8_AF12_SDIO_D4				= 12,                                           //!< PORT_B_PIN_8_AF12_SDIO_D4
	PORT_B_PIN_9_AF12_SDIO_D5				= 12,                                           //!< PORT_B_PIN_9_AF12_SDIO_D5
	PORT_B_PIN_12_AF12_OTG_HS_ID 			= 12,                                        //!< PORT_B_PIN_12_AF12_OTG_HS_ID
	PORT_B_PIN_14_AF12_OTG_HS_DM 			= 12,                                        //!< PORT_B_PIN_14_AF12_OTG_HS_DM
	PORT_B_PIN_15_AF12_OTG_HS_DP 			= 12,                                        //!< PORT_B_PIN_15_AF12_OTG_HS_DP

	PORT_C_PIN_0_AF12_FMC_SDNWE 			= 12,                                         //!< PORT_C_PIN_0_AF12_FMC_SDNWE
	PORT_C_PIN_2_AF12_FMC_SDNE0 			= 12,                                         //!< PORT_C_PIN_2_AF12_FMC_SDNE0
	PORT_C_PIN_3_AF12_FMC_SDCKE0 			= 12,                                        //!< PORT_C_PIN_3_AF12_FMC_SDCKE0
	PORT_C_PIN_6_AF12_SDIO_D6 				= 12,                                          //!< PORT_C_PIN_6_AF12_SDIO_D6
	PORT_C_PIN_7_AF12_SDIO_D7 				= 12,                                          //!< PORT_C_PIN_7_AF12_SDIO_D7
	PORT_C_PIN_8_AF12_SDIO_D0 				= 12,                                          //!< PORT_C_PIN_8_AF12_SDIO_D0
	PORT_C_PIN_9_AF12_SDIO_D1 				= 12,                                          //!< PORT_C_PIN_9_AF12_SDIO_D1
	PORT_C_PIN_10_AF12_SDIO_D2 				= 12,                                         //!< PORT_C_PIN_10_AF12_SDIO_D2
	PORT_C_PIN_11_AF12_SDIO_D3 				= 12,                                         //!< PORT_C_PIN_11_AF12_SDIO_D3
	PORT_C_PIN_12_AF12_SDIO_CK 				= 12,                                         //!< PORT_C_PIN_12_AF12_SDIO_CK

	PORT_D_PIN_0_AF12_FMC_D2				= 12,                                            //!< PORT_D_PIN_0_AF12_FMC_D2
	PORT_D_PIN_1_AF12_FMC_D3				= 12,                                            //!< PORT_D_PIN_1_AF12_FMC_D3
	PORT_D_PIN_2_AF12_SDIO_CMD	 			= 12,                                         //!< PORT_D_PIN_2_AF12_SDIO_CMD
	PORT_D_PIN_3_AF12_FMC_CLK 				= 12,                                          //!< PORT_D_PIN_3_AF12_FMC_CLK
	PORT_D_PIN_4_AF12_FMC_NOE 				= 12,                                          //!< PORT_D_PIN_4_AF12_FMC_NOE
	PORT_D_PIN_5_AF12_FMC_NWE 				= 12,                                          //!< PORT_D_PIN_5_AF12_FMC_NWE
	PORT_D_PIN_6_AF12_FMC_NWAIT 			= 12,                                         //!< PORT_D_PIN_6_AF12_FMC_NWAIT
	PORT_D_PIN_7_AF12_FMC_NE1 				= 12, /* Note: PD7 AF12 has 2 modes */         //!< PORT_D_PIN_7_AF12_FMC_NE1
	PORT_D_PIN_7_AF12_FMC_NCE2 				= 12, /* FMC (NE1 & NCE2)		    */             //!< PORT_D_PIN_7_AF12_FMC_NCE2
	PORT_D_PIN_8_AF12_FMC_D13 				= 12,                                          //!< PORT_D_PIN_8_AF12_FMC_D13
	PORT_D_PIN_9_AF12_FMC_D14 				= 12,                                          //!< PORT_D_PIN_9_AF12_FMC_D14
	PORT_D_PIN_10_AF12_FMC_D15 				= 12,                                         //!< PORT_D_PIN_10_AF12_FMC_D15
	PORT_D_PIN_11_AF12_FMC_A16 				= 12,                                         //!< PORT_D_PIN_11_AF12_FMC_A16
	PORT_D_PIN_12_AF12_FMC_A17 				= 12,                                         //!< PORT_D_PIN_12_AF12_FMC_A17
	PORT_D_PIN_13_AF12_FMC_A18 				= 12,                                         //!< PORT_D_PIN_13_AF12_FMC_A18
	PORT_D_PIN_14_AF12_FMC_D0 				= 12,                                          //!< PORT_D_PIN_14_AF12_FMC_D0
	PORT_D_PIN_15_AF12_FMC_D1 				= 12,                                          //!< PORT_D_PIN_15_AF12_FMC_D1


	PORT_E_PIN_0_AF12_FMC_NBL0 				= 12,                                         //!< PORT_E_PIN_0_AF12_FMC_NBL0
	PORT_E_PIN_1_AF12_FMC_NBL1 				= 12,                                         //!< PORT_E_PIN_1_AF12_FMC_NBL1
	PORT_E_PIN_2_AF12_FMC_A23 				= 12,                                          //!< PORT_E_PIN_2_AF12_FMC_A23
	PORT_E_PIN_3_AF12_FMC_A19 				= 12,                                          //!< PORT_E_PIN_3_AF12_FMC_A19
	PORT_E_PIN_4_AF12_FMC_A20 				= 12,                                          //!< PORT_E_PIN_4_AF12_FMC_A20
	PORT_E_PIN_5_AF12_FMC_A21 				= 12,                                          //!< PORT_E_PIN_5_AF12_FMC_A21
	PORT_E_PIN_6_AF12_FMC_A22 				= 12,                                          //!< PORT_E_PIN_6_AF12_FMC_A22
	PORT_E_PIN_7_AF12_FMC_D4				= 12,                                            //!< PORT_E_PIN_7_AF12_FMC_D4
	PORT_E_PIN_8_AF12_FMC_D5				= 12,                                            //!< PORT_E_PIN_8_AF12_FMC_D5
	PORT_E_PIN_9_AF12_FMC_D6				= 12,                                            //!< PORT_E_PIN_9_AF12_FMC_D6
	PORT_E_PIN_10_AF12_FMC_D7				= 12,                                           //!< PORT_E_PIN_10_AF12_FMC_D7
	PORT_E_PIN_11_AF12_FMC_D8				= 12,                                           //!< PORT_E_PIN_11_AF12_FMC_D8
	PORT_E_PIN_12_AF12_FMC_D9				= 12,                                           //!< PORT_E_PIN_12_AF12_FMC_D9
	PORT_E_PIN_13_AF12_FMC_D10				= 12,                                          //!< PORT_E_PIN_13_AF12_FMC_D10
	PORT_E_PIN_14_AF12_FMC_D11				= 12,                                          //!< PORT_E_PIN_14_AF12_FMC_D11
	PORT_E_PIN_15_AF12_FMC_D12				= 12,                                          //!< PORT_E_PIN_15_AF12_FMC_D12

	PORT_F_PIN_0_AF12_FMC_A0				= 12,                                            //!< PORT_F_PIN_0_AF12_FMC_A0
	PORT_F_PIN_1_AF12_FMC_A1				= 12,                                            //!< PORT_F_PIN_1_AF12_FMC_A1
	PORT_F_PIN_2_AF12_FMC_A2				= 12,                                            //!< PORT_F_PIN_2_AF12_FMC_A2
	PORT_F_PIN_3_AF12_FMC_A3				= 12,                                            //!< PORT_F_PIN_3_AF12_FMC_A3
	PORT_F_PIN_4_AF12_FMC_A4				= 12,                                            //!< PORT_F_PIN_4_AF12_FMC_A4
	PORT_F_PIN_5_AF12_FMC_A5				= 12,                                            //!< PORT_F_PIN_5_AF12_FMC_A5
	PORT_F_PIN_6_AF12_FMC_NIORD				= 12,                                         //!< PORT_F_PIN_6_AF12_FMC_NIORD
	PORT_F_PIN_7_AF12_FMC_NREG				= 12,                                          //!< PORT_F_PIN_7_AF12_FMC_NREG
	PORT_F_PIN_8_AF12_FMC_NIOWR				= 12,                                         //!< PORT_F_PIN_8_AF12_FMC_NIOWR
	PORT_F_PIN_9_AF12_FMC_CD				= 12,                                            //!< PORT_F_PIN_9_AF12_FMC_CD
	PORT_F_PIN_10_AF12_FMC_INTR				= 12,                                         //!< PORT_F_PIN_10_AF12_FMC_INTR
	PORT_F_PIN_11_AF12_FMC_SDNRAS			= 12,                                        //!< PORT_F_PIN_11_AF12_FMC_SDNRAS
	PORT_F_PIN_12_AF12_FMC_A6				= 12,                                           //!< PORT_F_PIN_12_AF12_FMC_A6
	PORT_F_PIN_13_AF12_FMC_A7				= 12,                                           //!< PORT_F_PIN_13_AF12_FMC_A7
	PORT_F_PIN_14_AF12_FMC_A8				= 12,                                           //!< PORT_F_PIN_14_AF12_FMC_A8
	PORT_F_PIN_15_AF12_FMC_A9				= 12,                                           //!< PORT_F_PIN_15_AF12_FMC_A9

	PORT_G_PIN_0_AF12_FMC_A10				= 12,                                           //!< PORT_G_PIN_0_AF12_FMC_A10
	PORT_G_PIN_1_AF12_FMC_A11				= 12,                                           //!< PORT_G_PIN_1_AF12_FMC_A11
	PORT_G_PIN_2_AF12_FMC_A12				= 12,                                           //!< PORT_G_PIN_2_AF12_FMC_A12
	PORT_G_PIN_3_AF12_FMC_A13				= 12,                                           //!< PORT_G_PIN_3_AF12_FMC_A13
	PORT_G_PIN_4_AF12_FMC_A14				= 12, /* Note: PG4 AF12 Has 2 modes */          //!< PORT_G_PIN_4_AF12_FMC_A14
	PORT_G_PIN_4_AF12_FMC_BA0				= 12, /* FMC (A14 & BA0)		    */                //!< PORT_G_PIN_4_AF12_FMC_BA0
	PORT_G_PIN_5_AF12_FMC_A15				= 12, /* Note: PG5 AF12 Has 2 modes */          //!< PORT_G_PIN_5_AF12_FMC_A15
	PORT_G_PIN_5_AF12_FMC_BA1				= 12, /* FMC (A15 & BA1)		    */                //!< PORT_G_PIN_5_AF12_FMC_BA1
	PORT_G_PIN_6_AF12_FMC_INT2				= 12,                                          //!< PORT_G_PIN_6_AF12_FMC_INT2
	PORT_G_PIN_7_AF12_FMC_INT3				= 12,                                          //!< PORT_G_PIN_7_AF12_FMC_INT3
	PORT_G_PIN_8_AF12_FMC_SDCLK				= 12,                                         //!< PORT_G_PIN_8_AF12_FMC_SDCLK
	PORT_G_PIN_9_AF12_FMC_NE2				= 12, /* Note: PG9 AF12 Has 2 modes */          //!< PORT_G_PIN_9_AF12_FMC_NE2
	PORT_G_PIN_9_AF12_FMC_NCE3				= 12, /* FMC (NE2 & NCE3)		 	*/                //!< PORT_G_PIN_9_AF12_FMC_NCE3
	PORT_G_PIN_10_AF12_FMC_NCE4_1			= 12, /* Note: PG10 AF12 Has 2 modes */      //!< PORT_G_PIN_10_AF12_FMC_NCE4_1
	PORT_G_PIN_10_AF12_FMC_NCE3				= 12, /* FMC (NCE4_1 & NCE3)		 	*/            //!< PORT_G_PIN_10_AF12_FMC_NCE3
	PORT_G_PIN_11_AF12_FMC_NCE4				= 12,                                         //!< PORT_G_PIN_11_AF12_FMC_NCE4
	PORT_G_PIN_12_AF12_FMC_NE4				= 12,                                          //!< PORT_G_PIN_12_AF12_FMC_NE4
	PORT_G_PIN_13_AF12_FMC_A24				= 12,                                          //!< PORT_G_PIN_13_AF12_FMC_A24
	PORT_G_PIN_14_AF12_FMC_A25				= 12,                                          //!< PORT_G_PIN_14_AF12_FMC_A25
	PORT_G_PIN_15_AF12_FMC_SDNCAS			= 12,                                        //!< PORT_G_PIN_15_AF12_FMC_SDNCAS

	/*------------------------------ No AF12 In Port H --------------------------*/


/***************************************************************************/

/*********** Alternative Function  = 13 For all Pins that have it **********/
	PORT_A_PIN_4_AF13_DCMI_HSYNC			= 13,                                         //!< PORT_A_PIN_4_AF13_DCMI_HSYNC
	PORT_A_PIN_6_AF13_DCMI_PIXCLK			= 13,                                        //!< PORT_A_PIN_6_AF13_DCMI_PIXCLK
	PORT_A_PIN_9_AF13_DCMI_D0				= 13,                                           //!< PORT_A_PIN_9_AF13_DCMI_D0
	PORT_A_PIN_10_AF13_DCMI_D1				= 13,                                          //!< PORT_A_PIN_10_AF13_DCMI_D1

	PORT_B_PIN_5_AF13_DCMI_D10				= 13,                                          //!< PORT_B_PIN_5_AF13_DCMI_D10
	PORT_B_PIN_6_AF13_DCMI_D5				= 13,                                           //!< PORT_B_PIN_6_AF13_DCMI_D5
	PORT_B_PIN_7_AF13_DCMI_VSYNC			= 13,                                         //!< PORT_B_PIN_7_AF13_DCMI_VSYNC
	PORT_B_PIN_8_AF13_DCMI_D6				= 13,                                           //!< PORT_B_PIN_8_AF13_DCMI_D6
	PORT_B_PIN_9_AF13_DCMI_D7				= 13,                                           //!< PORT_B_PIN_9_AF13_DCMI_D7

	PORT_C_PIN_6_AF13_DCMI_D0				= 13,                                           //!< PORT_C_PIN_6_AF13_DCMI_D0
	PORT_C_PIN_7_AF13_DCMI_D1				= 13,                                           //!< PORT_C_PIN_7_AF13_DCMI_D1
	PORT_C_PIN_8_AF13_DCMI_D2				= 13,                                           //!< PORT_C_PIN_8_AF13_DCMI_D2
	PORT_C_PIN_9_AF13_DCMI_D3				= 13,                                           //!< PORT_C_PIN_9_AF13_DCMI_D3
	PORT_C_PIN_10_AF13_DCMI_D8				= 13,                                          //!< PORT_C_PIN_10_AF13_DCMI_D8
	PORT_C_PIN_11_AF13_DCMI_D4				= 13,                                          //!< PORT_C_PIN_11_AF13_DCMI_D4
	PORT_C_PIN_12_AF13_DCMI_D9				= 13,                                          //!< PORT_C_PIN_12_AF13_DCMI_D9

	PORT_D_PIN_2_AF13_DCMI_D11				= 13,                                          //!< PORT_D_PIN_2_AF13_DCMI_D11
	PORT_D_PIN_3_AF13_DCMI_D5				= 13,                                           //!< PORT_D_PIN_3_AF13_DCMI_D5
	PORT_D_PIN_6_AF13_DCMI_D10				= 13,                                          //!< PORT_D_PIN_6_AF13_DCMI_D10

	PORT_E_PIN_0_AF13_DCMI_D2				= 13,                                           //!< PORT_E_PIN_0_AF13_DCMI_D2
	PORT_E_PIN_1_AF13_DCMI_D3				= 13,                                           //!< PORT_E_PIN_1_AF13_DCMI_D3
	PORT_E_PIN_4_AF13_DCMI_D4				= 13,                                           //!< PORT_E_PIN_4_AF13_DCMI_D4
	PORT_E_PIN_5_AF13_DCMI_D6				= 13,                                           //!< PORT_E_PIN_5_AF13_DCMI_D6
	PORT_E_PIN_6_AF13_DCMI_D7				= 13,                                           //!< PORT_E_PIN_6_AF13_DCMI_D7

	PORT_F_PIN_10_AF13_DCMI_D11				= 13,                                         //!< PORT_F_PIN_10_AF13_DCMI_D11
	PORT_F_PIN_11_AF13_DCMI_D12				= 13,                                         //!< PORT_F_PIN_11_AF13_DCMI_D12

	PORT_G_PIN_6_AF13_DCMI_D12				= 13,                                          //!< PORT_G_PIN_6_AF13_DCMI_D12
	PORT_G_PIN_7_AF13_DCMI_D13				= 13,                                          //!< PORT_G_PIN_7_AF13_DCMI_D13
	PORT_G_PIN_9_AF13_DCMI_VSYNC1			= 13,                                        //!< PORT_G_PIN_9_AF13_DCMI_VSYNC1
	PORT_G_PIN_10_AF13_DCMI_D2				= 13,                                          //!< PORT_G_PIN_10_AF13_DCMI_D2
	PORT_G_PIN_11_AF13_DCMI_D3				= 13,                                          //!< PORT_G_PIN_11_AF13_DCMI_D3
	PORT_G_PIN_15_AF13_DCMI_D13				= 13,                                         //!< PORT_G_PIN_15_AF13_DCMI_D13

	/*------------------------------ No AF13 In Port H --------------------------*/


/***************************************************************************/

/*********** Alternative Function  = 14 For all Pins that have it **********/
	PORT_A_PIN_3_AF14_LCD_B5				= 14,                                            //!< PORT_A_PIN_3_AF14_LCD_B5
	PORT_A_PIN_4_AF14_LCD_VSYNC				= 14,                                         //!< PORT_A_PIN_4_AF14_LCD_VSYNC
	PORT_A_PIN_6_AF14_LCD_G2				= 14,                                            //!< PORT_A_PIN_6_AF14_LCD_G2
	PORT_A_PIN_8_AF14_LCD_R6				= 14,                                            //!< PORT_A_PIN_8_AF14_LCD_R6
	PORT_A_PIN_11_AF14_LCD_R4				= 14,                                           //!< PORT_A_PIN_11_AF14_LCD_R4
	PORT_A_PIN_12_AF14_LCD_R5				= 14,                                           //!< PORT_A_PIN_12_AF14_LCD_R5

	PORT_B_PIN_8_AF14_LCD_B6				= 14,                                            //!< PORT_B_PIN_8_AF14_LCD_B6
	PORT_B_PIN_9_AF14_LCD_B7				= 14,                                            //!< PORT_B_PIN_9_AF14_LCD_B7
	PORT_B_PIN_10_AF14_LCD_G4				= 14,                                           //!< PORT_B_PIN_10_AF14_LCD_G4
	PORT_B_PIN_11_AF14_LCD_G5				= 14,                                           //!< PORT_B_PIN_11_AF14_LCD_G5

	PORT_C_PIN_6_AF14_LCD_HSYNC				= 14,                                         //!< PORT_C_PIN_6_AF14_LCD_HSYNC
	PORT_C_PIN_7_AF14_LCD_G6				= 14,                                            //!< PORT_C_PIN_7_AF14_LCD_G6
	PORT_C_PIN_10_AF14_LCD_R2				= 14,                                           //!< PORT_C_PIN_10_AF14_LCD_R2

	PORT_D_PIN_3_AF14_LCD_G7				= 14,                                            //!< PORT_D_PIN_3_AF14_LCD_G7
	PORT_D_PIN_6_AF14_LCD_B2				= 14,                                            //!< PORT_D_PIN_6_AF14_LCD_B2
	PORT_D_PIN_10_AF14_LCD_B3				= 14,                                           //!< PORT_D_PIN_10_AF14_LCD_B3

	PORT_E_PIN_4_AF14_LCD_B0				= 14,                                            //!< PORT_E_PIN_4_AF14_LCD_B0
	PORT_E_PIN_5_AF14_LCD_G0				= 14,                                            //!< PORT_E_PIN_5_AF14_LCD_G0
	PORT_E_PIN_6_AF14_LCD_G1				= 14,                                            //!< PORT_E_PIN_6_AF14_LCD_G1
	PORT_E_PIN_11_AF14_LCD_G3				= 14,                                           //!< PORT_E_PIN_11_AF14_LCD_G3
	PORT_E_PIN_12_AF14_LCD_B4				= 14,                                           //!< PORT_E_PIN_12_AF14_LCD_B4
	PORT_E_PIN_13_AF14_LCD_DE				= 14,                                           //!< PORT_E_PIN_13_AF14_LCD_DE
	PORT_E_PIN_14_AF14_LCD_CLK				= 14,                                          //!< PORT_E_PIN_14_AF14_LCD_CLK
	PORT_E_PIN_15_AF14_LCD_R7				= 14,                                           //!< PORT_E_PIN_15_AF14_LCD_R7

	PORT_F_PIN_10_AF14_LCD_DE				= 14,                                           //!< PORT_F_PIN_10_AF14_LCD_DE

	PORT_G_PIN_6_AF14_LCD_R7				= 14,                                            //!< PORT_G_PIN_6_AF14_LCD_R7
	PORT_G_PIN_7_AF14_LCD_CLK				= 14,                                           //!< PORT_G_PIN_7_AF14_LCD_CLK
	PORT_G_PIN_10_AF14_LCD_B2				= 14,                                           //!< PORT_G_PIN_10_AF14_LCD_B2
	PORT_G_PIN_11_AF14_LCD_B3				= 14,                                           //!< PORT_G_PIN_11_AF14_LCD_B3
	PORT_G_PIN_12_AF14_LCD_B1				= 14,                                           //!< PORT_G_PIN_12_AF14_LCD_B1

	/*------------------------------ No AF14 In Port H --------------------------*/


/***************************************************************************/

/*********** Alternative Function  = 15 For all Pins that have it **********/
	PORT_A_PIN_0_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_0_AF15_EVENT_OUT
	PORT_A_PIN_1_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_1_AF15_EVENT_OUT
	PORT_A_PIN_2_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_2_AF15_EVENT_OUT
	PORT_A_PIN_3_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_3_AF15_EVENT_OUT
	PORT_A_PIN_4_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_4_AF15_EVENT_OUT
	PORT_A_PIN_5_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_5_AF15_EVENT_OUT
	PORT_A_PIN_6_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_6_AF15_EVENT_OUT
	PORT_A_PIN_7_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_7_AF15_EVENT_OUT
	PORT_A_PIN_8_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_8_AF15_EVENT_OUT
	PORT_A_PIN_9_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_9_AF15_EVENT_OUT
	PORT_A_PIN_10_AF15_EVENT_OUT			= 15,                                         //!< PORT_A_PIN_10_AF15_EVENT_OUT
	PORT_A_PIN_11_AF15_EVENT_OUT			= 15,                                         //!< PORT_A_PIN_11_AF15_EVENT_OUT
	PORT_A_PIN_12_AF15_EVENT_OUT			= 15,                                         //!< PORT_A_PIN_12_AF15_EVENT_OUT
	PORT_A_PIN_13_AF15_EVENT_OUT			= 15,                                         //!< PORT_A_PIN_13_AF15_EVENT_OUT
	PORT_A_PIN_14_AF15_EVENT_OUT			= 15,                                         //!< PORT_A_PIN_14_AF15_EVENT_OUT
	PORT_A_PIN_15_AF15_EVENT_OUT			= 15,                                         //!< PORT_A_PIN_15_AF15_EVENT_OUT

	PORT_B_PIN_0_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_0_AF15_EVENT_OUT
	PORT_B_PIN_1_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_1_AF15_EVENT_OUT
	PORT_B_PIN_2_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_2_AF15_EVENT_OUT
	PORT_B_PIN_3_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_3_AF15_EVENT_OUT
	PORT_B_PIN_4_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_4_AF15_EVENT_OUT
	PORT_B_PIN_5_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_5_AF15_EVENT_OUT
	PORT_B_PIN_6_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_6_AF15_EVENT_OUT
	PORT_B_PIN_7_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_7_AF15_EVENT_OUT
	PORT_B_PIN_8_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_8_AF15_EVENT_OUT
	PORT_B_PIN_9_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_9_AF15_EVENT_OUT
	PORT_B_PIN_10_AF15_EVENT_OUT			= 15,                                         //!< PORT_B_PIN_10_AF15_EVENT_OUT
	PORT_B_PIN_11_AF15_EVENT_OUT			= 15,                                         //!< PORT_B_PIN_11_AF15_EVENT_OUT
	PORT_B_PIN_12_AF15_EVENT_OUT			= 15,                                         //!< PORT_B_PIN_12_AF15_EVENT_OUT
	PORT_B_PIN_13_AF15_EVENT_OUT			= 15,                                         //!< PORT_B_PIN_13_AF15_EVENT_OUT
	PORT_B_PIN_14_AF15_EVENT_OUT			= 15,                                         //!< PORT_B_PIN_14_AF15_EVENT_OUT
	PORT_B_PIN_15_AF15_EVENT_OUT			= 15,                                         //!< PORT_B_PIN_15_AF15_EVENT_OUT

	PORT_C_PIN_0_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_0_AF15_EVENT_OUT
	PORT_C_PIN_1_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_1_AF15_EVENT_OUT
	PORT_C_PIN_2_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_2_AF15_EVENT_OUT
	PORT_C_PIN_3_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_3_AF15_EVENT_OUT
	PORT_C_PIN_4_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_4_AF15_EVENT_OUT
	PORT_C_PIN_5_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_5_AF15_EVENT_OUT
	PORT_C_PIN_6_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_6_AF15_EVENT_OUT
	PORT_C_PIN_7_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_7_AF15_EVENT_OUT
	PORT_C_PIN_8_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_8_AF15_EVENT_OUT
	PORT_C_PIN_9_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_9_AF15_EVENT_OUT
	PORT_C_PIN_10_AF15_EVENT_OUT			= 15,                                         //!< PORT_C_PIN_10_AF15_EVENT_OUT
	PORT_C_PIN_11_AF15_EVENT_OUT			= 15,                                         //!< PORT_C_PIN_11_AF15_EVENT_OUT
	PORT_C_PIN_12_AF15_EVENT_OUT			= 15,                                         //!< PORT_C_PIN_12_AF15_EVENT_OUT
	PORT_C_PIN_13_AF15_EVENT_OUT			= 15,                                         //!< PORT_C_PIN_13_AF15_EVENT_OUT
	PORT_C_PIN_14_AF15_EVENT_OUT			= 15,                                         //!< PORT_C_PIN_14_AF15_EVENT_OUT
	PORT_C_PIN_15_AF15_EVENT_OUT			= 15,                                         //!< PORT_C_PIN_15_AF15_EVENT_OUT


	PORT_D_PIN_0_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_0_AF15_EVENT_OUT
	PORT_D_PIN_1_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_1_AF15_EVENT_OUT
	PORT_D_PIN_2_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_2_AF15_EVENT_OUT
	PORT_D_PIN_3_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_3_AF15_EVENT_OUT
	PORT_D_PIN_4_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_4_AF15_EVENT_OUT
	PORT_D_PIN_5_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_5_AF15_EVENT_OUT
	PORT_D_PIN_6_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_6_AF15_EVENT_OUT
	PORT_D_PIN_7_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_7_AF15_EVENT_OUT
	PORT_D_PIN_8_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_8_AF15_EVENT_OUT
	PORT_D_PIN_9_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_9_AF15_EVENT_OUT
	PORT_D_PIN_10_AF15_EVENT_OUT			= 15,                                         //!< PORT_D_PIN_10_AF15_EVENT_OUT
	PORT_D_PIN_11_AF15_EVENT_OUT			= 15,                                         //!< PORT_D_PIN_11_AF15_EVENT_OUT
	PORT_D_PIN_12_AF15_EVENT_OUT			= 15,                                         //!< PORT_D_PIN_12_AF15_EVENT_OUT
	PORT_D_PIN_13_AF15_EVENT_OUT			= 15,                                         //!< PORT_D_PIN_13_AF15_EVENT_OUT
	PORT_D_PIN_14_AF15_EVENT_OUT			= 15,                                         //!< PORT_D_PIN_14_AF15_EVENT_OUT
	PORT_D_PIN_15_AF15_EVENT_OUT			= 15,                                         //!< PORT_D_PIN_15_AF15_EVENT_OUT

	PORT_E_PIN_0_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_0_AF15_EVENT_OUT
	PORT_E_PIN_1_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_1_AF15_EVENT_OUT
	PORT_E_PIN_2_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_2_AF15_EVENT_OUT
	PORT_E_PIN_3_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_3_AF15_EVENT_OUT
	PORT_E_PIN_4_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_4_AF15_EVENT_OUT
	PORT_E_PIN_5_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_5_AF15_EVENT_OUT
	PORT_E_PIN_6_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_6_AF15_EVENT_OUT
	PORT_E_PIN_7_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_7_AF15_EVENT_OUT
	PORT_E_PIN_8_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_8_AF15_EVENT_OUT
	PORT_E_PIN_9_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_9_AF15_EVENT_OUT
	PORT_E_PIN_10_AF15_EVENT_OUT			= 15,                                         //!< PORT_E_PIN_10_AF15_EVENT_OUT
	PORT_E_PIN_11_AF15_EVENT_OUT			= 15,                                         //!< PORT_E_PIN_11_AF15_EVENT_OUT
	PORT_E_PIN_12_AF15_EVENT_OUT			= 15,                                         //!< PORT_E_PIN_12_AF15_EVENT_OUT
	PORT_E_PIN_13_AF15_EVENT_OUT			= 15,                                         //!< PORT_E_PIN_13_AF15_EVENT_OUT
	PORT_E_PIN_14_AF15_EVENT_OUT			= 15,                                         //!< PORT_E_PIN_14_AF15_EVENT_OUT
	PORT_E_PIN_15_AF15_EVENT_OUT			= 15,                                         //!< PORT_E_PIN_15_AF15_EVENT_OUT

	PORT_F_PIN_0_AF15_EVENT_OUT				= 15,                                         //!< PORT_F_PIN_0_AF15_EVENT_OUT
	PORT_F_PIN_1_AF15_EVENT_OUT				= 15,                                         //!< PORT_F_PIN_1_AF15_EVENT_OUT
	PORT_F_PIN_2_AF15_EVENT_OUT				= 15,                                         //!< PORT_F_PIN_2_AF15_EVENT_OUT
	PORT_F_PIN_3_AF15_EVENT_OUT				= 15,                                         //!< PORT_F_PIN_3_AF15_EVENT_OUT
	PORT_F_PIN_4_AF15_EVENT_OUT				= 15,                                         //!< PORT_F_PIN_4_AF15_EVENT_OUT
	PORT_F_PIN_5_AF15_EVENT_OUT				= 15,                                         //!< PORT_F_PIN_5_AF15_EVENT_OUT
	PORT_F_PIN_6_AF15_EVENT_OUT				= 15,                                         //!< PORT_F_PIN_6_AF15_EVENT_OUT
	PORT_F_PIN_7_AF15_EVENT_OUT				= 15,                                         //!< PORT_F_PIN_7_AF15_EVENT_OUT
	PORT_F_PIN_8_AF15_EVENT_OUT				= 15,                                         //!< PORT_F_PIN_8_AF15_EVENT_OUT
	PORT_F_PIN_9_AF15_EVENT_OUT				= 15,                                         //!< PORT_F_PIN_9_AF15_EVENT_OUT
	PORT_F_PIN_10_AF15_EVENT_OUT			= 15,                                         //!< PORT_F_PIN_10_AF15_EVENT_OUT
	PORT_F_PIN_11_AF15_EVENT_OUT			= 15,                                         //!< PORT_F_PIN_11_AF15_EVENT_OUT
	PORT_F_PIN_12_AF15_EVENT_OUT			= 15,                                         //!< PORT_F_PIN_12_AF15_EVENT_OUT
	PORT_F_PIN_13_AF15_EVENT_OUT			= 15,                                         //!< PORT_F_PIN_13_AF15_EVENT_OUT
	PORT_F_PIN_14_AF15_EVENT_OUT			= 15,                                         //!< PORT_F_PIN_14_AF15_EVENT_OUT
	PORT_F_PIN_15_AF15_EVENT_OUT			= 15,                                         //!< PORT_F_PIN_15_AF15_EVENT_OUT

	PORT_G_PIN_0_AF15_EVENT_OUT				= 15,                                         //!< PORT_G_PIN_0_AF15_EVENT_OUT
	PORT_G_PIN_1_AF15_EVENT_OUT				= 15,                                         //!< PORT_G_PIN_1_AF15_EVENT_OUT
	PORT_G_PIN_2_AF15_EVENT_OUT				= 15,                                         //!< PORT_G_PIN_2_AF15_EVENT_OUT
	PORT_G_PIN_3_AF15_EVENT_OUT				= 15,                                         //!< PORT_G_PIN_3_AF15_EVENT_OUT
	PORT_G_PIN_4_AF15_EVENT_OUT				= 15,                                         //!< PORT_G_PIN_4_AF15_EVENT_OUT
	PORT_G_PIN_5_AF15_EVENT_OUT				= 15,                                         //!< PORT_G_PIN_5_AF15_EVENT_OUT
	PORT_G_PIN_6_AF15_EVENT_OUT				= 15,                                         //!< PORT_G_PIN_6_AF15_EVENT_OUT
	PORT_G_PIN_7_AF15_EVENT_OUT				= 15,                                         //!< PORT_G_PIN_7_AF15_EVENT_OUT
	PORT_G_PIN_8_AF15_EVENT_OUT				= 15,                                         //!< PORT_G_PIN_8_AF15_EVENT_OUT
	PORT_G_PIN_9_AF15_EVENT_OUT				= 15,                                         //!< PORT_G_PIN_9_AF15_EVENT_OUT
	PORT_G_PIN_10_AF15_EVENT_OUT			= 15,                                         //!< PORT_G_PIN_10_AF15_EVENT_OUT
	PORT_G_PIN_11_AF15_EVENT_OUT			= 15,                                         //!< PORT_G_PIN_11_AF15_EVENT_OUT
	PORT_G_PIN_12_AF15_EVENT_OUT			= 15,                                         //!< PORT_G_PIN_12_AF15_EVENT_OUT
	PORT_G_PIN_13_AF15_EVENT_OUT			= 15,                                         //!< PORT_G_PIN_13_AF15_EVENT_OUT
	PORT_G_PIN_14_AF15_EVENT_OUT			= 15,                                         //!< PORT_G_PIN_14_AF15_EVENT_OUT
	PORT_G_PIN_15_AF15_EVENT_OUT			= 15,                                         //!< PORT_G_PIN_15_AF15_EVENT_OUT

	PORT_H_PIN_0_AF15_EVENT_OUT				= 15,                                         //!< PORT_H_PIN_0_AF15_EVENT_OUT
	PORT_H_PIN_1_AF15_EVENT_OUT				= 15,                                         //!< PORT_H_PIN_1_AF15_EVENT_OUT
/***************************************************************************/

/***************************************************************************/

/************* Alternative Function  = 17 to DIO ordinary mode ************/
	DIO_PIN								= 17                                                          //!< DIO_PIN
/***************************************************************************/



}Port_PinModeEnum;

#elif defined STM32F407

typedef enum{

/********* Alternative function = 0 For all Pins that have it **************/
	PORT_A_PIN_8_AF0_MCO1					= 0,                                               //!< PORT_A_PIN_8_AF0_MCO1
	PORT_A_PIN_13_AF0_JTMS_SWDIO			= 0,                                          //!< PORT_A_PIN_13_AF0_JTMS_SWDIO
	PORT_A_PIN_14_AF0_JTCK_SWCLK			= 0,                                          //!< PORT_A_PIN_14_AF0_JTCK_SWCLK
	PORT_A_PIN_15_AF0_JTDI					= 0,                                              //!< PORT_A_PIN_15_AF0_JTDI

	PORT_B_PIN_3_AF0_JTDO_TRACES_WO			= 0,                                       //!< PORT_B_PIN_3_AF0_JTDO_TRAC_ESWO
	PORT_B_PIN_4_AF0_NTJRST					= 0,                                             //!< PORT_B_PIN_4_AF0_NTJRST
	PORT_B_PIN_15_AF0_RTC_REFIN				= 0,                                          //!< PORT_B_PIN_15_AF0_RTC_REFIN

	PORT_C_PIN_9_AF0_MCO2					= 0,                                               //!< PORT_C_PIN_9_AF0_MCO2

	PORT_E_PIN_2_AF0_TRAC_ECLK				= 0,                                           //!< PORT_E_PIN_2_AF0_TRAC_ECLK
	PORT_E_PIN_3_AF0_TRAC_ED0				= 0,                                            //!< PORT_E_PIN_3_AF0_TRAC_ED0
	PORT_E_PIN_4_AF0_TRAC_ED1				= 0,                                            //!< PORT_E_PIN_4_AF0_TRAC_ED1
	PORT_E_PIN_5_AF0_TRAC_ED2				= 0,                                            //!< PORT_E_PIN_5_AF0_TRAC_ED2
	PORT_E_PIN_6_AF0_TRAC_ED3				= 0,                                            //!< PORT_E_PIN_6_AF0_TRAC_ED3

/***************************************************************************/

/*********** Alternative Function  = 1 For all Pins that have it ***********/
    PORT_A_PIN_0_AF1_TMI2_CH1_ETR		    = 1,                         //!< PORT_A_PIN_0_AF1_TMI2_CH1_ETR
	PORT_A_PIN_1_AF1_TIM2_CH2				= 1,                                            //!< PORT_A_PIN_1_AF1_TIM2_CH2
	PORT_A_PIN_2_AF1_TIM2_CH3				= 1,                                            //!< PORT_A_PIN_2_AF1_TIM2_CH3
	PORT_A_PIN_3_AF1_TIM2_CH4				= 1,                                            //!< PORT_A_PIN_3_AF1_TIM2_CH4
	PORT_A_PIN_5_AF1_TIM2_CH1_ETR			= 1,                               //!< PORT_A_PIN_5_AF1_TIM2_CH1_ETR
	PORT_A_PIN_6_AF1_TIM1_BKIN				= 1,                                           //!< PORT_A_PIN_6_AF1_TIM1_BKIN
	PORT_A_PIN_7_AF1_TIM1_CH1N				= 1,                                           //!< PORT_A_PIN_7_AF1_TIM1_CH1N
	PORT_A_PIN_8_AF1_TIM1_CH1				= 1,                                            //!< PORT_A_PIN_8_AF1_TIM1_CH1
	PORT_A_PIN_9_AF1_TIM1_CH2				= 1,                                            //!< PORT_A_PIN_9_AF1_TIM1_CH2
	PORT_A_PIN_10_AF1_TIM1_CH3				= 1,                                           //!< PORT_A_PIN_10_AF1_TIM1_CH3
	PORT_A_PIN_11_AF1_TIM1_CH4				= 1,                                           //!< PORT_A_PIN_11_AF1_TIM1_CH4
	PORT_A_PIN_12_AF1_TIM1_ETR				= 1,                                           //!< PORT_A_PIN_12_AF1_TIM1_ETR
	PORT_A_PIN_15_AF1_TIM2_CH1				= 1, /* Note: PA15 AF0 has 2modes*/            //!< PORT_A_PIN_15_AF1_TIM2_CH1
	PORT_A_PIN_15_AF1_TIM2_ETR				= 1, /* TIM2 (CH1 & ETR) (as PA0)*/            //!< PORT_A_PIN_15_AF1_TIM2_ETR

	PORT_B_PIN_0_AF1_TIM1_CH2N				= 1,                                           //!< PORT_B_PIN_0_AF1_TIM1_CH2N
	PORT_B_PIN_1_AF1_TIM1_CH3N				= 1,                                           //!< PORT_B_PIN_1_AF1_TIM1_CH3N
	PORT_B_PIN_3_AF1_TIM1_CH2				= 1,                                            //!< PORT_B_PIN_3_AF1_TIM1_CH2
	PORT_B_PIN_10_AF1_TIM2_CH3				= 1,                                          //!< PORT_B_PIN_10_AF1_TIM12_CH3
	PORT_B_PIN_11_AF1_TIM2_CH4				= 1,                                           //!< PORT_B_PIN_11_AF1_TIM2_CH4
	PORT_B_PIN_12_AF1_TIM1_BKIN				= 1,                                          //!< PORT_B_PIN_12_AF1_TIM1_BKIN
	PORT_B_PIN_13_AF1_TIM1_CH1N				= 1,                                          //!< PORT_B_PIN_13_AF1_TIM1_CH1N
	PORT_B_PIN_14_AF1_TIM1_CH2N			 	= 1,                                         //!< PORT_B_PIN_14_AF1_TIM1_CH2N
	PORT_B_PIN_15_AF1_TIM1_CH3N				= 1,                                          //!< PORT_B_PIN_15_AF1_TIM1_CH3N

	/*--------------------------- No AF1 In Port C ------------------------*/

	/*--------------------------- No AF1 In Port D ------------------------*/

	PORT_E_PIN_7_AF1_TIM1_ETR				= 1,                                            //!< PORT_E_PIN_7_AF1_TIM1_ETR
	PORT_E_PIN_8_AF1_TIM1_CH1N 				= 1,                                          //!< PORT_E_PIN_8_AF1_TIM1_CH1N
	PORT_E_PIN_9_AF1_TIM1_CH1 				= 1,                                           //!< PORT_E_PIN_9_AF1_TIM1_CH1
	PORT_E_PIN_10_AF1_TIM1_CH2N				= 1,                                          //!< PORT_E_PIN_10_AF1_TIM1_CH2N
	PORT_E_PIN_11_AF1_TIM1_CH2 				= 1,                                          //!< PORT_E_PIN_11_AF1_TIM1_CH2
	PORT_E_PIN_12_AF1_TIM1_CH3N	 			= 1,                                         //!< PORT_E_PIN_12_AF1_TIM1_CH3N
	PORT_E_PIN_13_AF1_TIM1_CH3 				= 1,                                          //!< PORT_E_PIN_13_AF1_TIM1_CH3
	PORT_E_PIN_14_AF1_TIM1_CH4 				= 1,                                          //!< PORT_E_PIN_14_AF1_TIM1_CH4
	PORT_E_PIN_15_AF1_TIM1_BKIN 			= 1,                                          //!< PORT_E_PIN_15_AF1_TIM1_BKIN

	/*--------------------------- No AF1 In Port H ------------------------*/


/***************************************************************************/

/*********** Alternative Function  = 2 For all Pins that have it ***********/
    PORT_A_PIN_0_AF2_TIM5_CH1				= 2,                                         //!< PORT_A_PIN_0_AF2_TIM5_CH1
	PORT_A_PIN_1_AF2_TIM5_CH2				= 2,                                            //!< PORT_A_PIN_1_AF2_TIM5_CH2
	PORT_A_PIN_2_AF2_TIM5_CH3				= 2,                                            //!< PORT_A_PIN_2_AF2_TIM5_CH3
	PORT_A_PIN_3_AF2_TIM5_CH4				= 2,                                            //!< PORT_A_PIN_3_AF2_TIM5_CH4
	PORT_A_PIN_6_AF2_TIM3_CH1				= 2,                                            //!< PORT_A_PIN_6_AF2_TIM3_CH1
	PORT_A_PIN_6_AF2_TIM3_CH2				= 2,                                            //!< PORT_A_PIN_6_AF2_TIM3_CH2

	PORT_B_PIN_0_AF2_TIM3_CH3				= 2,                                            //!< PORT_B_PIN_0_AF2_TIM3_CH3
	PORT_B_PIN_1_AF2_TIM3_CH4				= 2,                                            //!< PORT_B_PIN_1_AF2_TIM3_CH4
	PORT_B_PIN_4_AF2_TIM3_CH1				= 2,                                            //!< PORT_B_PIN_4_AF2_TIM3_CH1
	PORT_B_PIN_5_AF2_TIM3_CH2				= 2,                                            //!< PORT_B_PIN_5_AF2_TIM3_CH2
	PORT_B_PIN_6_AF2_TIM4_CH1				= 2,                                            //!< PORT_B_PIN_6_AF2_TIM4_CH1
	PORT_B_PIN_7_AF2_TIM4_CH2				= 2,                                            //!< PORT_B_PIN_7_AF2_TIM4_CH2
	PORT_B_PIN_8_AF2_TIM4_CH3				= 2,                                            //!< PORT_B_PIN_8_AF2_TIM4_CH3
	PORT_B_PIN_9_AF2_TIM4_CH4				= 2,                                            //!< PORT_B_PIN_9_AF2_TIM4_CH4

	PORT_C_PIN_6_AF2_TIM3_CH1 				= 2,                                           //!< PORT_C_PIN_6_AF2_TIM3_CH1
	PORT_C_PIN_7_AF2_TIM3_CH2 				= 2,                                           //!< PORT_C_PIN_7_AF2_TIM3_CH2
	PORT_C_PIN_8_AF2_TIM3_CH3 				= 2,                                           //!< PORT_C_PIN_8_AF2_TIM3_CH3
	PORT_C_PIN_9_AF2_TIM3_CH4 				= 2,                                           //!< PORT_C_PIN_9_AF2_TIM3_CH4

	PORT_D_PIN_2_AF2_TIM3_ETR 				= 2,                                           //!< PORT_D_PIN_2_AF2_TIM3_ETR
	PORT_D_PIN_12_AF2_TIM4_CH1 				= 2,                                          //!< PORT_D_PIN_12_AF2_TIM4_CH1
	PORT_D_PIN_13_AF2_TIM4_CH2 				= 2,                                          //!< PORT_D_PIN_13_AF2_TIM4_CH2
	PORT_D_PIN_14_AF2_TIM4_CH3 				= 2,                                          //!< PORT_D_PIN_14_AF2_TIM4_CH3
	PORT_D_PIN_15_AF2_TIM4_CH4 				= 2,                                          //!< PORT_D_PIN_15_AF2_TIM4_CH4

	PORT_E_PIN_0_AF2_TIM4_ETR 				= 2,                                           //!< PORT_E_PIN_0_AF2_TIM4_ETR

	/*--------------------------- No AF2 In Port H ------------------------*/

/***************************************************************************/

/*********** Alternative Function  = 3 For all Pins that have it ***********/
    PORT_A_PIN_0_AF3_TIM8_ETR    		    = 3,                                   //!< PORT_A_PIN_0_AF3_TIM8_ETR
	PORT_A_PIN_2_AF3_TIM9_CH1				= 3,                                            //!< PORT_A_PIN_2_AF3_TIM9_CH1
	PORT_A_PIN_3_AF3_TIM9_CH2				= 3,                                            //!< PORT_A_PIN_3_AF3_TIM9_CH2
	PORT_A_PIN_5_AF3_TIM8_CH1N				= 3,                                           //!< PORT_A_PIN_5_AF3_TIM8_CH1N
	PORT_A_PIN_6_AF3_TIM8_BKIN				= 3,                                           //!< PORT_A_PIN_6_AF3_TIM8_BKIN
	PORT_A_PIN_7_AF3_TIM8_CH1N				= 3,                                           //!< PORT_A_PIN_7_AF3_TIM8_CH1N

	PORT_B_PIN_0_AF3_TIM8_CH2N				= 3,                                           //!< PORT_B_PIN_0_AF3_TIM8_CH2N
	PORT_B_PIN_1_AF3_TIM8_CH3N				= 3,                                           //!< PORT_B_PIN_1_AF3_TIM8_CH3N
	PORT_B_PIN_8_AF3_TIM10_CH1				= 3,                                           //!< PORT_B_PIN_8_AF3_TIM10_CH1
	PORT_B_PIN_9_AF3_TIM11_CH1				= 3,                                           //!< PORT_B_PIN_9_AF3_TIM11_CH1
	PORT_B_PIN_14_AF3_TIM8_CH2N 			= 3,                                          //!< PORT_B_PIN_14_AF3_TIM8_CH2N
	PORT_B_PIN_15_AF3_TIM8_CH3N 			= 3,                                          //!< PORT_B_PIN_15_AF3_TIM8_CH3N

	PORT_C_PIN_6_AF3_TIM8_CH1 				= 3,                                           //!< PORT_C_PIN_6_AF3_TIM8_CH1
	PORT_C_PIN_7_AF3_TIM8_CH2 				= 3,                                           //!< PORT_C_PIN_7_AF3_TIM8_CH2
	PORT_C_PIN_8_AF3_TIM8_CH3			 	= 3,                                           //!< PORT_C_PIN_8_AF3_TIM8_CH3
	PORT_C_PIN_9_AF3_TIM8_CH4				= 3,                                            //!< PORT_C_PIN_9_AF3_TIM8_CH4

	/*--------------------------- No AF3 In Port D ------------------------*/

	PORT_E_PIN_5_AF3_TIM9_CH1 				= 3,                                           //!< PORT_E_PIN_5_AF3_TIM9_CH1
	PORT_E_PIN_6_AF3_TIM9_CH2 				= 3,                                           //!< PORT_E_PIN_6_AF3_TIM9_CH2

	/*--------------------------- No AF3 In Port H ------------------------*/

/***************************************************************************/

/*********** Alternative Function  = 4 For all Pins that have it ***********/
    PORT_A_PIN_8_AF4_I2C3_SCL     			= 4,                                     //!< PORT_A_PIN_8_AF4_I2C3_SCL
	PORT_A_PIN_9_AF4_I2C3_SMBA				= 4,                                           //!< PORT_A_PIN_9_AF4_I2C3_SMBA

	PORT_B_PIN_5_AF4_I2C1_SMBA				= 4,                                           //!< PORT_B_PIN_5_AF4_I2C1_SMBA
	PORT_B_PIN_6_AF4_I2C1_SCL				= 4,                                            //!< PORT_B_PIN_6_AF4_I2C1_SCL
	PORT_B_PIN_7_AF4_I2C1_SDA			 	= 4,                                           //!< PORT_B_PIN_7_AF4_I2C1_SDA
	PORT_B_PIN_8_AF4_I2C1_SCL				= 4,                                            //!< PORT_B_PIN_8_AF4_I2C1_SCL
	PORT_B_PIN_9_AF4_I2C1_SDA				= 4,                                            //!< PORT_B_PIN_9_AF4_I2C1_SDA
	PORT_B_PIN_10_AF4_I2C2_SCL				= 4,                                           //!< PORT_B_PIN_10_AF4_I2C2_SCL
	PORT_B_PIN_11_AF4_I2C2_SDA				= 4,                                           //!< PORT_B_PIN_11_AF4_I2C2_SDA
	PORT_B_PIN_12_AF4_I2C2_SMBA				= 4,                                          //!< PORT_B_PIN_12_AF4_I2C2_SMBA

	PORT_C_PIN_9_AF4_I2C3_SDA				= 4,                                            //!< PORT_C_PIN_9_AF4_I2C3_SDA

	/*--------------------------- No AF4 In Port D ------------------------*/

	/*--------------------------- No AF4 In Port E ------------------------*/

	/*--------------------------- No AF4 In Port H ------------------------*/


/***************************************************************************/

/*********** Alternative Function  = 5 For all Pins that have it ***********/
    PORT_A_PIN_4_AF5_SPI1_NSS     			= 5,                                     //!< PORT_A_PIN_4_AF5_SPI1_NSS
	PORT_A_PIN_5_AF5_SPI1_SCK				= 5,                                            //!< PORT_A_PIN_5_AF5_SPI1_SCK
	PORT_A_PIN_6_AF5_SPI1_MISO				= 5,                                           //!< PORT_A_PIN_6_AF5_SPI1_MISO
	PORT_A_PIN_7_AF5_SPI1_MOSI				= 5,                                           //!< PORT_A_PIN_7_AF5_SPI1_MOSI
	PORT_A_PIN_15_AF5_SPI1_NSS				= 5,                                           //!< PORT_A_PIN_15_AF5_SPI1_NSS

	PORT_B_PIN_3_AF5_SPI1_SCK				= 5,                                            //!< PORT_B_PIN_3_AF5_SPI1_SCK
	PORT_B_PIN_4_AF5_SPI1_MISO				= 5,                                           //!< PORT_B_PIN_4_AF5_SPI1_MISO
	PORT_B_PIN_5_AF5_SPI1_MOSI				= 5,                                           //!< PORT_B_PIN_5_AF5_SPI1_MOSI
	PORT_B_PIN_9_AF5_SPI2_NSS				= 5, /* Note: PB9 AF5 Has 2 modes */            //!< PORT_B_PIN_9_AF5_SPI2_NSS
	PORT_B_PIN_9_AF5_I2S2_WS				= 5, /* SPI2 NSS & I2S2 WS	      */              //!< PORT_B_PIN_9_AF5_I2S2_WS
	PORT_B_PIN_10_AF5_SPI2_SCK				= 5, /* Note: PB10 AF5 Has 2 modes*/           //!< PORT_B_PIN_10_AF5_SPI2_SCK
	PORT_B_PIN_10_AF5_I2S2_CK				= 5, /* SPI2 SCK & I2S2 CK	      */             //!< PORT_B_PIN_10_AF5_I2S2_CK
	PORT_B_PIN_12_AF5_SPI2_NSS 				= 5, /* Note: PB12 AF5 has 2 modes*/          //!< PORT_B_PIN_12_AF5_SPI2_NSS
	PORT_B_PIN_12_AF5_I2S2_WS 				= 5, /* SPI2 NSS & I2S2 WS 		  */              //!< PORT_B_PIN_12_AF5_I2S2_WS
	PORT_B_PIN_13_AF5_SPI2_SCK			 	= 5, /* NoteL PB13 AF5 has 2 modes*/          //!< PORT_B_PIN_13_AF5_SPI2_SCK
	PORT_B_PIN_13_AF5_I2S2_CK 				= 5, /* SPI2 SCK & I2S2 CK 		  */              //!< PORT_B_PIN_13_AF5_I2S2_CK
	PORT_B_PIN_14_AF5_SPI2_MISO 			= 5,                                          //!< PORT_B_PIN_14_AF5_SPI2_MISO
	PORT_B_PIN_15_AF5_SPI2_MOSI 			= 5, /*Note: PB15 AF5 has 2 modes */          //!< PORT_B_PIN_15_AF5_SPI2_MOSI
	PORT_B_PIN_15_AF5_I2S2_SD 				= 5, /* SPI2 MOSI & I2S2 SD 	  */              //!< PORT_B_PIN_15_AF5_I2S2_SD

	PORT_C_PIN_2_AF5_SPI2_MISO 				= 5,                                          //!< PORT_C_PIN_2_AF5_SPI2_MISO
	PORT_C_PIN_3_AF5_SPI2_MOSI			 	= 5, /* Note: PC3 AF5 has 2 modes */          //!< PORT_C_PIN_3_AF5_SPI2_MOSI
	PORT_C_PIN_3_AF5_I2S2_SD 				= 5, /* SPI2 MOSI & I2S2 SD 	  */               //!< PORT_C_PIN_3_AF5_I2S2_SD
	PORT_C_PIN_6_AF5_I2S2_MCK			 	= 5,                                           //!< PORT_C_PIN_6_AF5_I2S2_MCK
	PORT_C_PIN_9_AF5_I2S_CKIN 				= 5,                                           //!< PORT_C_PIN_9_AF5_I2S_CKIN
	PORT_C_PIN_11_AF5_I2S3_EXT_SD 			= 5,                                        //!< PORT_C_PIN_11_AF5_I2S3_EXT_SD

	/*--------------------------- No AF5 In Port H ------------------------*/

/***************************************************************************/

/************ Alternative Function  = 6 For all Pins that have it *************/
    PORT_A_PIN_4_AF6_SPI3_NSS				= 6, /* Note: PA6 AF6 Has 2 modes */         //!< PORT_A_PIN_4_AF6_SPI3_NSS
	PORT_A_PIN_4_AF6_I2S3_WS				= 6, /* SPI3 NSS & I2S3 WS 		  */                //!< PORT_A_PIN_4_AF6_I2S3_WS
	PORT_A_PIN_15_AF6_SPI3_NSS 				= 6, /* Note: PA15 AF6 Has 2 modes*///!< PORT_A_PIN_15_AF6_SPI3_NSS
	PORT_A_PIN_15_AF6_I2S3_WS 				= 6, /* SPI3 NSS & I2S3 WS 		  */    //!< PORT_A_PIN_15_AF6_I2S3_WS

	PORT_B_PIN_3_AF6_SPI3_SCK				= 6, /* Note: PB3 AF6 Has 2 modes */            //!< PORT_B_PIN_3_AF6_SPI3_SCK
	PORT_B_PIN_3_AF6_I2S3_CK				= 6, /* SPI3 SCK & I2S3 CK	      */              //!< PORT_B_PIN_3_AF6_I2S3_CK
	PORT_B_PIN_4_AF6_SPI3_MISO				= 6,                                           //!< PORT_B_PIN_4_AF6_SPI1_MISO
	PORT_B_PIN_5_AF6_SPI3_MOSI				= 6, /* Note: PB5 AF6 has 2 modes */           //!< PORT_B_PIN_5_AF6_SPI1_MOSI
	PORT_B_PIN_5_AF6_I2S3_SD			    = 6, /* SPI1 MOSI & I2S3 SD	      */          //!< PORT_B_PIN_5_AF6_I2S3_SD
	PORT_B_PIN_14_AF6_I2S2_EXT_SD 			= 6,                                         //!< PORT_B_PIN_14_AF6_I2S2_EXT_SD

	PORT_C_PIN_2_AF6_I2S2_EXT_SD 			= 6,                                         //!< PORT_C_PIN_2_AF6_I2S2_EXT_SD
	PORT_C_PIN_7_AF6_I2S3_MCK 				= 6,                                           //!< PORT_C_PIN_7_AF6_I2S3_MCK
	PORT_C_PIN_10_AF6_SPI3_SCK 				= 6, /* Note: PC10 AF6 has 2 modes*/          //!< PORT_C_PIN_10_AF6_SPI3_SCK
	PORT_C_PIN_10_AF6_I2S3_CK 				= 6, /* SPI3 SCK & I2S3 CK 		  */              //!< PORT_C_PIN_10_AF6_I2S3_CK
	PORT_C_PIN_11_AF6_SPI3_MISO 			= 6,                                          //!< PORT_C_PIN_11_AF6_SPI3_MISO
	PORT_C_PIN_12_AF6_SPI3_MOSI 			= 6, /* Note: PC12 AF6 has 2 modes*/          //!< PORT_C_PIN_12_AF6_SPI3_MOSI
	PORT_C_PIN_12_AF6_I2S3_SD 				= 6, /* SPI3 MOSI & I2S3 SD	 	  */             //!< PORT_C_PIN_12_AF6_I2S3_SD

	/*--------------------------- No AF6 In Port H ------------------------*/


/***************************************************************************/

/*********** Alternative Function  = 7 For all Pins that have it ***********/
    PORT_A_PIN_0_AF7_USART2_CTS				= 7,                                       //!< PORT_A_PIN_0_AF7_USART2_CTS
	PORT_A_PIN_1_AF7_USART2_RTS			    = 7,                                       //!< PORT_A_PIN_1_AF7_USART2_RTS
	PORT_A_PIN_2_AF7_USART2_TX				= 7,                                           //!< PORT_A_PIN_2_AF7_USART2_TX
	PORT_A_PIN_3_AF7_USART2_RX				= 7,                                           //!< PORT_A_PIN_3_AF7_USART2_RX
	PORT_A_PIN_4_AF7_USART2_CK				= 7,                                           //!< PORT_A_PIN_4_AF7_USART2_CK
	PORT_A_PIN_8_AF7_USART1_CK				= 7,                                           //!< PORT_A_PIN_8_AF7_USART1_CK
	PORT_A_PIN_9_AF7_USART1_TX				= 7,                                           //!< PORT_A_PIN_9_AF7_USART1_TX
	PORT_A_PIN_10_AF7_USART1_RX				= 7,                                          //!< PORT_A_PIN_10_AF7_USART1_RX
	PORT_A_PIN_11_AF7_USART1_CTS			= 7,                                          //!< PORT_A_PIN_11_AF7_USART1_CTS
	PORT_A_PIN_12_AF7_USART1_RTS			= 7,                                          //!< PORT_A_PIN_12_AF7_USART1_RTS

	PORT_B_PIN_4_AF7_I2S3_EXT_SD			= 7,                                          //!< PORT_B_PIN_4_AF7_I2S3_EXT_SD
	PORT_B_PIN_6_AF7_USART1_TX				= 7,                                           //!< PORT_B_PIN_6_AF7_USART1_TX
	PORT_B_PIN_7_AF7_USART1_RX				= 7,                                           //!< PORT_B_PIN_7_AF7_USART1_RX
	PORT_B_PIN_10_AF7_USART3_TX				= 7,                                          //!< PORT_B_PIN_10_AF7_USART3_TX
	PORT_B_PIN_11_AF7_USART3_RX				= 7,                                          //!< PORT_B_PIN_11_AF7_USART3_RX
	PORT_B_PIN_12_AF7_USART3_CK 			= 7,                                          //!< PORT_B_PIN_12_AF7_USART3_CK
	PORT_B_PIN_13_AF7_USART3_CTS 			= 7,                                         //!< PORT_B_PIN_13_AF7_USART3_CTS
	PORT_B_PIN_14_AF7_USART3_RTS 			= 7,                                         //!< PORT_B_PIN_14_AF7_USART3_RTS

	PORT_C_PIN_10_AF7_USART3_TX 			= 7,                                          //!< PORT_C_PIN_10_AF7_USART3_TX
	PORT_C_PIN_11_AF7_USART3_RX 			= 7,                                          //!< PORT_C_PIN_11_AF7_USART3_RX
	PORT_C_PIN_12_AF7_USART3_CK 			= 7,                                          //!< PORT_C_PIN_12_AF7_USART3_CK

	PORT_D_PIN_3_AF7_USART2_CTS 			= 7,                                          //!< PORT_D_PIN_3_AF7_USART2_CTS
	PORT_D_PIN_4_AF7_USART2_RTS 			= 7,                                          //!< PORT_D_PIN_4_AF7_USART2_RTS
	PORT_D_PIN_5_AF7_USART2_TX 				= 7,                                          //!< PORT_D_PIN_5_AF7_USART2_TX
	PORT_D_PIN_6_AF7_USART2_RX 				= 7,                                          //!< PORT_D_PIN_6_AF7_USART2_RX
	PORT_D_PIN_7_AF7_USART2_CK			 	= 7,                                          //!< PORT_D_PIN_7_AF7_USART2_CK
	PORT_D_PIN_8_AF7_USART3_TX 				= 7,                                          //!< PORT_D_PIN_8_AF7_USART3_TX
	PORT_D_PIN_9_AF7_USART3_RX 				= 7,                                          //!< PORT_D_PIN_9_AF7_USART3_RX
	PORT_D_PIN_10_AF7_USART3_CK 			= 7,                                          //!< PORT_D_PIN_10_AF7_USART3_CK
	PORT_D_PIN_11_AF7_USART3_CTS 			= 7,                                         //!< PORT_D_PIN_11_AF7_USART3_CTS
	PORT_D_PIN_12_AF7_USART3_RTS			= 7,                                          //!< PORT_D_PIN_12_AF7_USART3_RTS

	/*--------------------------- No AF7 In Port H ------------------------*/



/***************************************************************************/

/*********** Alternative Function  = 8 For all Pins that have it ***********/
    PORT_A_PIN_0_AF8_UART4_TX				= 8,                                         //!< PORT_A_PIN_0_AF8_UART4_TX
	PORT_A_PIN_1_AF8_UART4_RX				= 8,                                            //!< PORT_A_PIN_1_AF8_UART4_RX

	/*--------------------------- No AF8 In Port B ------------------------*/

	PORT_C_PIN_6_AF8_USART6_TX				= 8,                                           //!< PORT_C_PIN_6_AF8_USART6_TX
	PORT_C_PIN_7_AF8_USART6_RX 				= 8,                                          //!< PORT_C_PIN_7_AF8_USART6_RX
	PORT_C_PIN_8_AF8_USART6_CK 				= 8,                                          //!< PORT_C_PIN_8_AF8_USART6_CK
	PORT_C_PIN_10_AF8_UART4_TX 				= 8,                                          //!< PORT_C_PIN_10_AF8_UART4_TX
	PORT_C_PIN_11_AF8_UART4_RX 				= 8,                                          //!< PORT_C_PIN_11_AF8_UART4_RX
	PORT_C_PIN_12_AF8_UART5_TX 				= 8,                                          //!< PORT_C_PIN_12_AF8_UART5_TX

	PORT_D_PIN_2_AF8_UART5_RX 				= 8,                                           //!< PORT_D_PIN_2_AF8_UART5_RX

	/*--------------------------- No AF8 In Port E ------------------------*/

	/*--------------------------- No AF8 In Port H ------------------------*/


/***************************************************************************/

/*********** Alternative Function  = 9 For all Pins that have it ***********/
    PORT_A_PIN_6_AF9_TIM13_CH1				= 9,                                        //!< PORT_A_PIN_6_AF9_TIM13_CH1
	PORT_A_PIN_7_AF9_TIM14_CH1				= 9,                                           //!< PORT_A_PIN_7_AF9_TIM14_CH1
	PORT_A_PIN_11_AF9_CAN1_RX				= 9,                                            //!< PORT_A_PIN_11_AF9_CAN1_RX
	PORT_A_PIN_12_AF9_CAN1_TX				= 9,                                            //!< PORT_A_PIN_12_AF9_CAN1_TX

	PORT_B_PIN_5_AF9_CAN2_RX				= 9,                                             //!< PORT_B_PIN_5_AF9_CAN2_RX
	PORT_B_PIN_6_AF9_CAN2_TX				= 9,                                             //!< PORT_B_PIN_6_AF9_CAN2_TX
	PORT_B_PIN_8_AF9_CAN1_RX				= 9,                                             //!< PORT_B_PIN_8_AF9_CAN1_RX
	PORT_B_PIN_9_AF9_CAN1_TX				= 9,                                             //!< PORT_B_PIN_9_AF9_CAN1_TX
	PORT_B_PIN_12_AF9_CAN2_RX 				= 9,                                           //!< PORT_B_PIN_12_AF9_CAN2_RX
	PORT_B_PIN_13_AF9_CAN2_TX 				= 9,                                           //!< PORT_B_PIN_13_AF9_CAN2_TX
	PORT_B_PIN_14_AF9_TIM12_CH1				= 9,                                          //!< PORT_B_PIN_14_AF9_TIM12_CH1
	PORT_B_PIN_15_AF9_TIM12_CH2				= 9,                                          //!< PORT_B_PIN_15_AF9_TIM12_CH2

	/*--------------------------- No AF9 In Port C ------------------------*/

	PORT_D_PIN_0_AF9_CAN1_RX				= 9,                                             //!< PORT_D_PIN_0_AF9_CAN1_RX
	PORT_D_PIN_1_AF9_CAN1_TX 				= 9,                                            //!< PORT_D_PIN_1_AF9_CAN1_TX

	/*--------------------------- No AF9 In Port E ------------------------*/

	/*--------------------------- No AF9 In Port H ------------------------*/



/***************************************************************************/

/*********** Alternative Function  = 10 For all Pins that have it **********/
	PORT_A_PIN_3_AF10_OTG_HS_ULPI_D0		= 10,                                      //!< PORT_A_PIN_3_AF10_OTG_HS_ULPI_D0
	PORT_A_PIN_5_AF10_OTG_HS_ULPI_CK		= 10,                                      //!< PORT_A_PIN_5_AF10_OTG_HS_ULPI_CK
	PORT_A_PIN_8_AF10_OTG_FS_SOF			= 10,                                         //!< PORT_A_PIN_8_AF10_OTG_FS_SOF
	PORT_A_PIN_10_AF10_OTG_FS_ID			= 10,                                         //!< PORT_A_PIN_10_AF10_OTG_FS_ID
	PORT_A_PIN_11_AF10_OTG_FS_DM			= 10,                                         //!< PORT_A_PIN_11_AF10_OTG_FS_DM
	PORT_A_PIN_12_AF10_OTG_FS_DP			= 10,                                         //!< PORT_A_PIN_12_AF10_OTG_FS_DP

	PORT_B_PIN_0_AF10_OTG_HS_ULPI_D1		= 10,                                      //!< PORT_B_PIN_0_AF10_OTG_HS_ULPI_D1
	PORT_B_PIN_1_AF10_OTG_HS_ULPI_D2		= 10,                                      //!< PORT_B_PIN_1_AF10_OTG_HS_ULPI_D2
	PORT_B_PIN_5_AF10_OTG_HS_ULPI_D7		= 10,                                      //!< PORT_B_PIN_5_AF10_OTG_HS_ULPI_D7
	PORT_B_PIN_10_AF10_OTG_HS_ULPI_D3		= 10,                                     //!< PORT_B_PIN_10_AF10_OTG_HS_ULPI_D3
	PORT_B_PIN_11_AF10_OTG_HS_ULPI_D4		= 10,                                     //!< PORT_B_PIN_11_AF10_OTG_HS_ULPI_D4
	PORT_B_PIN_12_AF10_OTG_HS_ULPI_D5		= 10,                                     //!< PORT_B_PIN_12_AF10_OTG_HS_ULPI_D5
	PORT_B_PIN_13_AF10_OTG_HS_ULPI_D6		= 10,                                     //!< PORT_B_PIN_13_AF10_OTG_HS_ULPI_D6

	PORT_C_PIN_0_AF10_OTG_HS_ULPI_STP		= 10,                                     //!< PORT_C_PIN_0_AF10_OTG_HS_ULPI_STP
	PORT_C_PIN_2_AF10_OTG_HS_ULPI_DIR		= 10,                                     //!< PORT_C_PIN_2_AF10_OTG_HS_ULPI_DIR
	PORT_C_PIN_3_AF10_OTG_HS_ULPI_NXT		= 10,                                     //!< PORT_C_PIN_3_AF10_OTG_HS_ULPI_NXT

	/*--------------------------- No AF10 In Port D ------------------------*/

	/*--------------------------- No AF10 In Port E ------------------------*/

	/*--------------------------- No AF10 In Port H ------------------------*/



/***************************************************************************/

/*********** Alternative Function  = 11 For all Pins that have it **********/
	PORT_A_PIN_0_AF11_ETH_MII_CRS			= 11,                                        //!< PORT_A_PIN_0_AF11_ETH_MII_CRS
	PORT_A_PIN_1_AF11_ETH_MII_RX_CLK		= 11, /* Note: PA1 AF11 has 2 modes  */    //!< PORT_A_PIN_1_AF11_ETH_MII_RX_CLK
	PORT_A_PIN_1_AF11_ETH_RMII_REF_CLK		= 11, /* ETH (MII RX & RMII REF)CLK  */  //!< PORT_A_PIN_1_AF11_ETH_RMII_REF_CLK
	PORT_A_PIN_2_AF11_ETH_MDIO				= 11,                                          //!< PORT_A_PIN_2_AF11_ETH_MDIO
	PORT_A_PIN_3_AF11_ETH_MII_COL			= 11,                                        //!< PORT_A_PIN_3_AF11_ETH_MII_COL
	PORT_A_PIN_7_AF11_ETH_MII_RX_DV			= 11, /* Note: PA7 AF11 has 2 modes  */    //!< PORT_A_PIN_7_AF11_ETH_MII_RX_DV
	PORT_A_PIN_7_AF11_ETH_RMII_CRS_DV		= 11, /* ETH(MII RX DV & RMII CRS DV)*/   //!< PORT_A_PIN_7_AF11_ETH_RMII_CRS_DV

	PORT_B_PIN_0_AF11_ETH_MII_RXD2			= 11,                                       //!< PORT_B_PIN_0_AF11_ETH_MII_RXD2
	PORT_B_PIN_1_AF11_ETH_MII_RXD3			= 11,                                       //!< PORT_B_PIN_1_AF11_ETH_MII_RXD3
	PORT_B_PIN_5_AF11_ETH_PPS_OUT			= 11,                                        //!< PORT_B_PIN_5_AF11_ETH_PPS_OUT
	PORT_B_PIN_8_AF11_ETH_MII_TXD3			= 11,                                       //!< PORT_B_PIN_8_AF11_ETH_MII_TXD3
	PORT_B_PIN_10_AF11_ETH_MII_RX_ER		= 11,                                      //!< PORT_B_PIN_10_AF11_ETH_MII_RX_ER
	PORT_B_PIN_11_AF11_ETH_MII_TX_EN 		= 11, /* Note: PB11 AF11 has 2 modes */   //!< PORT_B_PIN_11_AF11_ETH_MII_TX_EN
	PORT_B_PIN_11_AF11_ETH_RMII_TX_EN 		= 11, /* ETH (MII TX & RMII TX )EN   */  //!< PORT_B_PIN_11_AF11_ETH_RMII_TX_EN
	PORT_B_PIN_12_AF11_ETH_MII_TXD0 		= 11, /* Note: PB12 AF11 has 2 modes */    //!< PORT_B_PIN_12_AF11_ETH_MII_TXD0
	PORT_B_PIN_12_AF11_ETH_RMII_TXD0 		= 11, /* ETH (MII TXD0 & RMII TXD0)  */   //!< PORT_B_PIN_12_AF11_ETH_RMII_TXD0
	PORT_B_PIN_12_AF11_ETH_MII_TXD1			= 11, /* Note: PB13 AF11 has 2 modes */    //!< PORT_B_PIN_12_AF11_ETH_MII_TXD
	PORT_B_PIN_12_AF11_ETH_RMII_TXD1 		= 11, /* ETH (MII TXD & RMII TXD1    */   //!< PORT_B_PIN_12_AF11_ETH_RMII_TXD1

	PORT_C_PIN_1_AF11_ETH_MDC 				= 11,                                          //!< PORT_C_PIN_1_AF11_ETH_MDC
	PORT_C_PIN_2_AF11_ETH_MII_TXD2 			= 11,                                      //!< PORT_C_PIN_2_AF11_ETH_MII_TXD2
	PORT_C_PIN_3_AF11_ETH_MII_CLK 			= 11,                                       //!< PORT_C_PIN_3_AF11_ETH_MII_CLK
	PORT_C_PIN_4_AF11_ETH_MII_RXD0 			= 11, /* Note: PC4 AF11 has 2 modes  */    //!< PORT_C_PIN_4_AF11_ETH_MII_RXD0
	PORT_C_PIN_4_AF11_ETH_RMII_RXD0			= 11, /* ETH (MII RXD0 & RMII RXD0)  */    //!< PORT_C_PIN_4_AF11_ETH_RMII_RXD0
	PORT_C_PIN_5_AF11_ETH_MII_RXD1 			= 11, /* Note: PC5 AF11 has 2 modes  */    //!< PORT_C_PIN_5_AF11_ETH_MII_RXD1
	PORT_C_PIN_5_AF11_ETH_RMII_RXD1			= 11, /* ETH (MII RXD1 & RMII RXD1)  */    //!< PORT_C_PIN_5_AF11_ETH_RMII_RXD1

	/*------------------------------ No AF11 In Port D --------------------------*/

	PORT_E_PIN_2_AF11_ETH_MII_TXD3			= 11,                                       //!< PORT_E_PIN_2_AF11_ETH_MII_TXD3

	/*------------------------------ No AF11 In Port H --------------------------*/



/***************************************************************************/

/*********** Alternative Function  = 12 For all Pins that have it **********/
	PORT_A_PIN_4_AF12_OTG_HS_SOF			= 12,                                         //!< PORT_A_PIN_4_AF12_OTG_HS_SOF

	PORT_B_PIN_7_AF12_FMC_NL				= 12,                                            //!< PORT_B_PIN_7_AF12_FMC_NL
	PORT_B_PIN_8_AF12_SDIO_D4				= 12,                                           //!< PORT_B_PIN_8_AF12_SDIO_D4
	PORT_B_PIN_9_AF12_SDIO_D5				= 12,                                           //!< PORT_B_PIN_9_AF12_SDIO_D5
	PORT_B_PIN_12_AF12_OTG_HS_ID 			= 12,                                        //!< PORT_B_PIN_12_AF12_OTG_HS_ID
	PORT_B_PIN_14_AF12_OTG_HS_DM 			= 12,                                        //!< PORT_B_PIN_14_AF12_OTG_HS_DM
	PORT_B_PIN_15_AF12_OTG_HS_DP 			= 12,                                        //!< PORT_B_PIN_15_AF12_OTG_HS_DP

	PORT_C_PIN_6_AF12_SDIO_D6 				= 12,                                          //!< PORT_C_PIN_6_AF12_SDIO_D6
	PORT_C_PIN_7_AF12_SDIO_D7 				= 12,                                          //!< PORT_C_PIN_7_AF12_SDIO_D7
	PORT_C_PIN_8_AF12_SDIO_D0 				= 12,                                          //!< PORT_C_PIN_8_AF12_SDIO_D0
	PORT_C_PIN_9_AF12_SDIO_D1 				= 12,                                          //!< PORT_C_PIN_9_AF12_SDIO_D1
	PORT_C_PIN_10_AF12_SDIO_D2 				= 12,                                         //!< PORT_C_PIN_10_AF12_SDIO_D2
	PORT_C_PIN_11_AF12_SDIO_D3 				= 12,                                         //!< PORT_C_PIN_11_AF12_SDIO_D3
	PORT_C_PIN_12_AF12_SDIO_CK 				= 12,                                         //!< PORT_C_PIN_12_AF12_SDIO_CK

	PORT_D_PIN_0_AF12_FMC_D2				= 12,                                            //!< PORT_D_PIN_0_AF12_FMC_D2
	PORT_D_PIN_1_AF12_FMC_D3				= 12,                                            //!< PORT_D_PIN_1_AF12_FMC_D3
	PORT_D_PIN_2_AF12_SDIO_CMD	 			= 12,                                         //!< PORT_D_PIN_2_AF12_SDIO_CMD
	PORT_D_PIN_3_AF12_FMC_CLK 				= 12,                                          //!< PORT_D_PIN_3_AF12_FMC_CLK
	PORT_D_PIN_4_AF12_FMC_NOE 				= 12,                                          //!< PORT_D_PIN_4_AF12_FMC_NOE
	PORT_D_PIN_5_AF12_FMC_NWE 				= 12,                                          //!< PORT_D_PIN_5_AF12_FMC_NWE
	PORT_D_PIN_6_AF12_FMC_NWAIT 			= 12,                                         //!< PORT_D_PIN_6_AF12_FMC_NWAIT
	PORT_D_PIN_7_AF12_FMC_NE1 				= 12, /* Note: PD7 AF12 has 2 modes */         //!< PORT_D_PIN_7_AF12_FMC_NE1
	PORT_D_PIN_7_AF12_FMC_NCE2 				= 12, /* FMC (NE1 & NCE2)		    */             //!< PORT_D_PIN_7_AF12_FMC_NCE2
	PORT_D_PIN_8_AF12_FMC_D13 				= 12,                                          //!< PORT_D_PIN_8_AF12_FMC_D13
	PORT_D_PIN_9_AF12_FMC_D14 				= 12,                                          //!< PORT_D_PIN_9_AF12_FMC_D14
	PORT_D_PIN_10_AF12_FMC_D15 				= 12,                                         //!< PORT_D_PIN_10_AF12_FMC_D15
	PORT_D_PIN_11_AF12_FMC_A16 				= 12,                                         //!< PORT_D_PIN_11_AF12_FMC_A16
	PORT_D_PIN_12_AF12_FMC_A17 				= 12,                                         //!< PORT_D_PIN_12_AF12_FMC_A17
	PORT_D_PIN_13_AF12_FMC_A18 				= 12,                                         //!< PORT_D_PIN_13_AF12_FMC_A18
	PORT_D_PIN_14_AF12_FMC_D0 				= 12,                                          //!< PORT_D_PIN_14_AF12_FMC_D0
	PORT_D_PIN_15_AF12_FMC_D1 				= 12,                                          //!< PORT_D_PIN_15_AF12_FMC_D1


	PORT_E_PIN_0_AF12_FMC_NBL0 				= 12,                                         //!< PORT_E_PIN_0_AF12_FMC_NBL0
	PORT_E_PIN_1_AF12_FMC_NBL1 				= 12,                                         //!< PORT_E_PIN_1_AF12_FMC_NBL1
	PORT_E_PIN_2_AF12_FMC_A23 				= 12,                                          //!< PORT_E_PIN_2_AF12_FMC_A23
	PORT_E_PIN_3_AF12_FMC_A19 				= 12,                                          //!< PORT_E_PIN_3_AF12_FMC_A19
	PORT_E_PIN_4_AF12_FMC_A20 				= 12,                                          //!< PORT_E_PIN_4_AF12_FMC_A20
	PORT_E_PIN_5_AF12_FMC_A21 				= 12,                                          //!< PORT_E_PIN_5_AF12_FMC_A21
	PORT_E_PIN_6_AF12_FMC_A22 				= 12,                                          //!< PORT_E_PIN_6_AF12_FMC_A22
	PORT_E_PIN_7_AF12_FMC_D4				= 12,                                            //!< PORT_E_PIN_7_AF12_FMC_D4
	PORT_E_PIN_8_AF12_FMC_D5				= 12,                                            //!< PORT_E_PIN_8_AF12_FMC_D5
	PORT_E_PIN_9_AF12_FMC_D6				= 12,                                            //!< PORT_E_PIN_9_AF12_FMC_D6
	PORT_E_PIN_10_AF12_FMC_D7				= 12,                                           //!< PORT_E_PIN_10_AF12_FMC_D7
	PORT_E_PIN_11_AF12_FMC_D8				= 12,                                           //!< PORT_E_PIN_11_AF12_FMC_D8
	PORT_E_PIN_12_AF12_FMC_D9				= 12,                                           //!< PORT_E_PIN_12_AF12_FMC_D9
	PORT_E_PIN_13_AF12_FMC_D10				= 12,                                          //!< PORT_E_PIN_13_AF12_FMC_D10
	PORT_E_PIN_14_AF12_FMC_D11				= 12,                                          //!< PORT_E_PIN_14_AF12_FMC_D11
	PORT_E_PIN_15_AF12_FMC_D12				= 12,                                          //!< PORT_E_PIN_15_AF12_FMC_D12
	/*------------------------------ No AF12 In Port H --------------------------*/


/***************************************************************************/

/*********** Alternative Function  = 13 For all Pins that have it **********/
	PORT_A_PIN_4_AF13_DCMI_HSYNC			= 13,                                         //!< PORT_A_PIN_4_AF13_DCMI_HSYNC
	PORT_A_PIN_6_AF13_DCMI_PIXCLK			= 13,                                        //!< PORT_A_PIN_6_AF13_DCMI_PIXCLK
	PORT_A_PIN_9_AF13_DCMI_D0				= 13,                                           //!< PORT_A_PIN_9_AF13_DCMI_D0
	PORT_A_PIN_10_AF13_DCMI_D1				= 13,                                          //!< PORT_A_PIN_10_AF13_DCMI_D1

	PORT_B_PIN_5_AF13_DCMI_D10				= 13,                                          //!< PORT_B_PIN_5_AF13_DCMI_D10
	PORT_B_PIN_6_AF13_DCMI_D5				= 13,                                           //!< PORT_B_PIN_6_AF13_DCMI_D5
	PORT_B_PIN_7_AF13_DCMI_VSYNC			= 13,                                         //!< PORT_B_PIN_7_AF13_DCMI_VSYNC
	PORT_B_PIN_8_AF13_DCMI_D6				= 13,                                           //!< PORT_B_PIN_8_AF13_DCMI_D6
	PORT_B_PIN_9_AF13_DCMI_D7				= 13,                                           //!< PORT_B_PIN_9_AF13_DCMI_D7

	PORT_C_PIN_6_AF13_DCMI_D0				= 13,                                           //!< PORT_C_PIN_6_AF13_DCMI_D0
	PORT_C_PIN_7_AF13_DCMI_D1				= 13,                                           //!< PORT_C_PIN_7_AF13_DCMI_D1
	PORT_C_PIN_8_AF13_DCMI_D2				= 13,                                           //!< PORT_C_PIN_8_AF13_DCMI_D2
	PORT_C_PIN_9_AF13_DCMI_D3				= 13,                                           //!< PORT_C_PIN_9_AF13_DCMI_D3
	PORT_C_PIN_10_AF13_DCMI_D8				= 13,                                          //!< PORT_C_PIN_10_AF13_DCMI_D8
	PORT_C_PIN_11_AF13_DCMI_D4				= 13,                                          //!< PORT_C_PIN_11_AF13_DCMI_D4
	PORT_C_PIN_12_AF13_DCMI_D9				= 13,                                          //!< PORT_C_PIN_12_AF13_DCMI_D9

	PORT_D_PIN_2_AF13_DCMI_D11				= 13,                                          //!< PORT_D_PIN_2_AF13_DCMI_D11

	PORT_E_PIN_0_AF13_DCMI_D2				= 13,                                           //!< PORT_E_PIN_0_AF13_DCMI_D2
	PORT_E_PIN_1_AF13_DCMI_D3				= 13,                                           //!< PORT_E_PIN_1_AF13_DCMI_D3
	PORT_E_PIN_4_AF13_DCMI_D4				= 13,                                           //!< PORT_E_PIN_4_AF13_DCMI_D4
	PORT_E_PIN_5_AF13_DCMI_D6				= 13,                                           //!< PORT_E_PIN_5_AF13_DCMI_D6
	PORT_E_PIN_6_AF13_DCMI_D7				= 13,                                           //!< PORT_E_PIN_6_AF13_DCMI_D7


	/*------------------------------ No AF13 In Port H --------------------------*/


/***************************************************************************/

/*********** Alternative Function  = 14 For all Pins that have it **********/
	/*------------------------------ No AF14 In Port A --------------------------*/

	/*------------------------------ No AF14 In Port B --------------------------*/

	/*------------------------------ No AF14 In Port C --------------------------*/

	/*------------------------------ No AF14 In Port D --------------------------*/

	/*------------------------------ No AF14 In Port E --------------------------*/

	/*------------------------------ No AF14 In Port H --------------------------*/


/***************************************************************************/

/*********** Alternative Function  = 15 For all Pins that have it **********/
	PORT_A_PIN_0_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_0_AF15_EVENT_OUT
	PORT_A_PIN_1_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_1_AF15_EVENT_OUT
	PORT_A_PIN_2_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_2_AF15_EVENT_OUT
	PORT_A_PIN_3_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_3_AF15_EVENT_OUT
	PORT_A_PIN_4_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_4_AF15_EVENT_OUT
	PORT_A_PIN_5_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_5_AF15_EVENT_OUT
	PORT_A_PIN_6_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_6_AF15_EVENT_OUT
	PORT_A_PIN_7_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_7_AF15_EVENT_OUT
	PORT_A_PIN_8_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_8_AF15_EVENT_OUT
	PORT_A_PIN_9_AF15_EVENT_OUT				= 15,                                         //!< PORT_A_PIN_9_AF15_EVENT_OUT
	PORT_A_PIN_10_AF15_EVENT_OUT			= 15,                                         //!< PORT_A_PIN_10_AF15_EVENT_OUT
	PORT_A_PIN_11_AF15_EVENT_OUT			= 15,                                         //!< PORT_A_PIN_11_AF15_EVENT_OUT
	PORT_A_PIN_12_AF15_EVENT_OUT			= 15,                                         //!< PORT_A_PIN_12_AF15_EVENT_OUT
	PORT_A_PIN_13_AF15_EVENT_OUT			= 15,                                         //!< PORT_A_PIN_13_AF15_EVENT_OUT
	PORT_A_PIN_14_AF15_EVENT_OUT			= 15,                                         //!< PORT_A_PIN_14_AF15_EVENT_OUT
	PORT_A_PIN_15_AF15_EVENT_OUT			= 15,                                         //!< PORT_A_PIN_15_AF15_EVENT_OUT

	PORT_B_PIN_0_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_0_AF15_EVENT_OUT
	PORT_B_PIN_1_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_1_AF15_EVENT_OUT
	PORT_B_PIN_2_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_2_AF15_EVENT_OUT
	PORT_B_PIN_3_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_3_AF15_EVENT_OUT
	PORT_B_PIN_4_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_4_AF15_EVENT_OUT
	PORT_B_PIN_5_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_5_AF15_EVENT_OUT
	PORT_B_PIN_6_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_6_AF15_EVENT_OUT
	PORT_B_PIN_7_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_7_AF15_EVENT_OUT
	PORT_B_PIN_8_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_8_AF15_EVENT_OUT
	PORT_B_PIN_9_AF15_EVENT_OUT				= 15,                                         //!< PORT_B_PIN_9_AF15_EVENT_OUT
	PORT_B_PIN_10_AF15_EVENT_OUT			= 15,                                         //!< PORT_B_PIN_10_AF15_EVENT_OUT
	PORT_B_PIN_11_AF15_EVENT_OUT			= 15,                                         //!< PORT_B_PIN_11_AF15_EVENT_OUT
	PORT_B_PIN_12_AF15_EVENT_OUT			= 15,                                         //!< PORT_B_PIN_12_AF15_EVENT_OUT
	PORT_B_PIN_13_AF15_EVENT_OUT			= 15,                                         //!< PORT_B_PIN_13_AF15_EVENT_OUT
	PORT_B_PIN_14_AF15_EVENT_OUT			= 15,                                         //!< PORT_B_PIN_14_AF15_EVENT_OUT
	PORT_B_PIN_15_AF15_EVENT_OUT			= 15,                                         //!< PORT_B_PIN_15_AF15_EVENT_OUT

	PORT_C_PIN_0_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_0_AF15_EVENT_OUT
	PORT_C_PIN_1_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_1_AF15_EVENT_OUT
	PORT_C_PIN_2_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_2_AF15_EVENT_OUT
	PORT_C_PIN_3_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_3_AF15_EVENT_OUT
	PORT_C_PIN_4_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_4_AF15_EVENT_OUT
	PORT_C_PIN_5_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_5_AF15_EVENT_OUT
	PORT_C_PIN_6_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_6_AF15_EVENT_OUT
	PORT_C_PIN_7_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_7_AF15_EVENT_OUT
	PORT_C_PIN_8_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_8_AF15_EVENT_OUT
	PORT_C_PIN_9_AF15_EVENT_OUT				= 15,                                         //!< PORT_C_PIN_9_AF15_EVENT_OUT
	PORT_C_PIN_10_AF15_EVENT_OUT			= 15,                                         //!< PORT_C_PIN_10_AF15_EVENT_OUT
	PORT_C_PIN_11_AF15_EVENT_OUT			= 15,                                         //!< PORT_C_PIN_11_AF15_EVENT_OUT
	PORT_C_PIN_12_AF15_EVENT_OUT			= 15,                                         //!< PORT_C_PIN_12_AF15_EVENT_OUT
	PORT_C_PIN_13_AF15_EVENT_OUT			= 15,                                         //!< PORT_C_PIN_13_AF15_EVENT_OUT
	PORT_C_PIN_14_AF15_EVENT_OUT			= 15,                                         //!< PORT_C_PIN_14_AF15_EVENT_OUT
	PORT_C_PIN_15_AF15_EVENT_OUT			= 15,                                         //!< PORT_C_PIN_15_AF15_EVENT_OUT


	PORT_D_PIN_0_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_0_AF15_EVENT_OUT
	PORT_D_PIN_1_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_1_AF15_EVENT_OUT
	PORT_D_PIN_2_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_2_AF15_EVENT_OUT
	PORT_D_PIN_3_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_3_AF15_EVENT_OUT
	PORT_D_PIN_4_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_4_AF15_EVENT_OUT
	PORT_D_PIN_5_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_5_AF15_EVENT_OUT
	PORT_D_PIN_6_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_6_AF15_EVENT_OUT
	PORT_D_PIN_7_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_7_AF15_EVENT_OUT
	PORT_D_PIN_8_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_8_AF15_EVENT_OUT
	PORT_D_PIN_9_AF15_EVENT_OUT				= 15,                                         //!< PORT_D_PIN_9_AF15_EVENT_OUT
	PORT_D_PIN_10_AF15_EVENT_OUT			= 15,                                         //!< PORT_D_PIN_10_AF15_EVENT_OUT
	PORT_D_PIN_11_AF15_EVENT_OUT			= 15,                                         //!< PORT_D_PIN_11_AF15_EVENT_OUT
	PORT_D_PIN_12_AF15_EVENT_OUT			= 15,                                         //!< PORT_D_PIN_12_AF15_EVENT_OUT
	PORT_D_PIN_13_AF15_EVENT_OUT			= 15,                                         //!< PORT_D_PIN_13_AF15_EVENT_OUT
	PORT_D_PIN_14_AF15_EVENT_OUT			= 15,                                         //!< PORT_D_PIN_14_AF15_EVENT_OUT
	PORT_D_PIN_15_AF15_EVENT_OUT			= 15,                                         //!< PORT_D_PIN_15_AF15_EVENT_OUT

	PORT_E_PIN_0_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_0_AF15_EVENT_OUT
	PORT_E_PIN_1_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_1_AF15_EVENT_OUT
	PORT_E_PIN_2_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_2_AF15_EVENT_OUT
	PORT_E_PIN_3_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_3_AF15_EVENT_OUT
	PORT_E_PIN_4_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_4_AF15_EVENT_OUT
	PORT_E_PIN_5_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_5_AF15_EVENT_OUT
	PORT_E_PIN_6_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_6_AF15_EVENT_OUT
	PORT_E_PIN_7_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_7_AF15_EVENT_OUT
	PORT_E_PIN_8_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_8_AF15_EVENT_OUT
	PORT_E_PIN_9_AF15_EVENT_OUT				= 15,                                         //!< PORT_E_PIN_9_AF15_EVENT_OUT
	PORT_E_PIN_10_AF15_EVENT_OUT			= 15,                                         //!< PORT_E_PIN_10_AF15_EVENT_OUT
	PORT_E_PIN_11_AF15_EVENT_OUT			= 15,                                         //!< PORT_E_PIN_11_AF15_EVENT_OUT
	PORT_E_PIN_12_AF15_EVENT_OUT			= 15,                                         //!< PORT_E_PIN_12_AF15_EVENT_OUT
	PORT_E_PIN_13_AF15_EVENT_OUT			= 15,                                         //!< PORT_E_PIN_13_AF15_EVENT_OUT
	PORT_E_PIN_14_AF15_EVENT_OUT			= 15,                                         //!< PORT_E_PIN_14_AF15_EVENT_OUT
	PORT_E_PIN_15_AF15_EVENT_OUT			= 15,                                         //!< PORT_E_PIN_15_AF15_EVENT_OUT

	PORT_H_PIN_0_AF15_EVENT_OUT				= 15,                                         //!< PORT_H_PIN_0_AF15_EVENT_OUT
	PORT_H_PIN_1_AF15_EVENT_OUT				= 15,                                         //!< PORT_H_PIN_1_AF15_EVENT_OUT
/***************************************************************************/

/***************************************************************************/

/************* Alternative Function  = 17 to DIO ordinary mode ************/
	DIO_PIN								= 17                                                          //!< DIO_PIN
/***************************************************************************/



}Port_PinModeEnum;

#endif


/**
 * @enum	Port_PinNumEnum
 *
 * @brief	This enum used to numbering the pins on the TM4C123GH6PM
 */
#ifdef STM32F429
typedef enum{

/*********************** PORT A Pin Numbering ***********************/
    PORT_A_PIN_0                = 0, 			 //!< PORT_A_PIN_0
    PORT_A_PIN_1                = 1,			 //!< PORT_A_PIN_1
    PORT_A_PIN_2                = 2,			 //!< PORT_A_PIN_2
    PORT_A_PIN_3                = 3,			 //!< PORT_A_PIN_3
    PORT_A_PIN_4                = 4, 			 //!< PORT_A_PIN_4
    PORT_A_PIN_5                = 5, 		 	 //!< PORT_A_PIN_5
    PORT_A_PIN_6                = 6, 		 	 //!< PORT_A_PIN_6
    PORT_A_PIN_7                = 7, 		     //!< PORT_A_PIN_7
    PORT_A_PIN_8				= 8,           	 //!< PORT_A_PIN_8
	PORT_A_PIN_9				= 9,             //!< PORT_A_PIN_9
	PORT_A_PIN_10				= 10,            //!< PORT_A_PIN_10
	PORT_A_PIN_11				= 11,            //!< PORT_A_PIN_11
	PORT_A_PIN_12				= 12,            //!< PORT_A_PIN_12
	PORT_A_PIN_13				= 13,            //!< PORT_A_PIN_13
	PORT_A_PIN_14				= 14,            //!< PORT_A_PIN_14
	PORT_A_PIN_15				= 15,            //!< PORT_A_PIN_15
/********************************************************************/

/*********************** PORT B Pin Numbering ***********************/
    PORT_B_PIN_0                = 0,			 //!< PORT_B_PIN_0
    PORT_B_PIN_1                = 1,			 //!< PORT_B_PIN_1
    PORT_B_PIN_2                = 2,			 //!< PORT_B_PIN_2
    PORT_B_PIN_3                = 3,			 //!< PORT_B_PIN_3
    PORT_B_PIN_4                = 4,			 //!< PORT_B_PIN_4
    PORT_B_PIN_5                = 5,			 //!< PORT_B_PIN_5
    PORT_B_PIN_6                = 6,			 //!< PORT_B_PIN_6
    PORT_B_PIN_7                = 7,			 //!< PORT_B_PIN_7
    PORT_B_PIN_8				= 8,             //!< PORT_B_PIN_8
	PORT_B_PIN_9				= 9,             //!< PORT_B_PIN_9
	PORT_B_PIN_10				= 10,            //!< PORT_B_PIN_10
	PORT_B_PIN_11				= 11,            //!< PORT_B_PIN_11
	PORT_B_PIN_12				= 12,            //!< PORT_B_PIN_12
	PORT_B_PIN_13				= 13,            //!< PORT_B_PIN_13
	PORT_B_PIN_14				= 14,            //!< PORT_B_PIN_14
	PORT_B_PIN_15				= 15,            //!< PORT_B_PIN_15
/********************************************************************/

/*********************** PORT C Pin Numbering ***********************/
    PORT_C_PIN_0                = 0, 			 //!< PORT_B_PIN_0
    PORT_C_PIN_1                = 1,			 //!< PORT_B_PIN_1
    PORT_C_PIN_2                = 2,			 //!< PORT_B_PIN_2
    PORT_C_PIN_3                = 3,			 //!< PORT_B_PIN_3
    PORT_C_PIN_4                = 4,			 //!< PORT_B_PIN_4
    PORT_C_PIN_5                = 5,			 //!< PORT_B_PIN_5
    PORT_C_PIN_6                = 6,			 //!< PORT_B_PIN_6
    PORT_C_PIN_7                = 7,			 //!< PORT_B_PIN_7
    PORT_C_PIN_8				= 8,             //!< PORT_C_PIN_8
	PORT_C_PIN_9				= 9,             //!< PORT_C_PIN_9
	PORT_C_PIN_10				= 10,            //!< PORT_C_PIN_10
	PORT_C_PIN_11				= 11,            //!< PORT_C_PIN_11
	PORT_C_PIN_12				= 12,            //!< PORT_C_PIN_12
	PORT_C_PIN_13				= 13,            //!< PORT_C_PIN_13
	PORT_C_PIN_14				= 14,            //!< PORT_C_PIN_14
	PORT_C_PIN_15				= 15,            //!< PORT_C_PIN_15
/********************************************************************/

/*********************** PORT D Pin Numbering ***********************/
    PORT_D_PIN_0                = 0,			 //!< PORT_D_PIN_0
    PORT_D_PIN_1                = 1,			 //!< PORT_D_PIN_1
    PORT_D_PIN_2                = 2,  			 //!< PORT_D_PIN_2
    PORT_D_PIN_3                = 3,			 //!< PORT_D_PIN_3
    PORT_D_PIN_4                = 4,			 //!< PORT_D_PIN_4
    PORT_D_PIN_5                = 5,			 //!< PORT_D_PIN_5
    PORT_D_PIN_6                = 6,			 //!< PORT_D_PIN_6
    PORT_D_PIN_7                = 7,			 //!< PORT_D_PIN_7
    PORT_D_PIN_8				= 8,             //!< PORT_D_PIN_8
	PORT_D_PIN_9				= 9,             //!< PORT_D_PIN_9
	PORT_D_PIN_10				= 10,            //!< PORT_D_PIN_10
	PORT_D_PIN_11				= 11,            //!< PORT_D_PIN_11
	PORT_D_PIN_12				= 12,            //!< PORT_D_PIN_12
	PORT_D_PIN_13				= 13,            //!< PORT_D_PIN_13
	PORT_D_PIN_14				= 14,            //!< PORT_D_PIN_14
	PORT_D_PIN_15				= 15,            //!< PORT_D_PIN_15
/********************************************************************/

/*********************** PORT E Pin Numbering ***********************/

    PORT_E_PIN_0                = 0,			 //!< PORT_E_PIN_0
    PORT_E_PIN_1                = 1,			 //!< PORT_E_PIN_1
    PORT_E_PIN_2                = 2,			 //!< PORT_E_PIN_2
    PORT_E_PIN_3                = 3,			 //!< PORT_E_PIN_3
    PORT_E_PIN_4                = 4,			 //!< PORT_E_PIN_4
    PORT_E_PIN_5                = 5,			 //!< PORT_E_PIN_5
    PORT_E_PIN_6                = 6,			 //!< PORT_E_PIN_6
    PORT_E_PIN_7                = 7,			 //!< PORT_E_PIN_7
    PORT_E_PIN_8				= 8,             //!< PORT_E_PIN_8
	PORT_E_PIN_9				= 9,             //!< PORT_E_PIN_9
	PORT_E_PIN_10				= 10,            //!< PORT_E_PIN_10
	PORT_E_PIN_11				= 11,            //!< PORT_E_PIN_11
	PORT_E_PIN_12				= 12,            //!< PORT_E_PIN_12
	PORT_E_PIN_13				= 13,            //!< PORT_E_PIN_13
	PORT_E_PIN_14				= 14,            //!< PORT_E_PIN_14
	PORT_E_PIN_15				= 15,            //!< PORT_E_PIN_15
/********************************************************************/

/*********************** PORT F Pin Numbering ***********************/

    PORT_F_PIN_0                = 0,			 //!< PORT_F_PIN_0
    PORT_F_PIN_1                = 1,			 //!< PORT_F_PIN_1
    PORT_F_PIN_2                = 2,			 //!< PORT_F_PIN_2
    PORT_F_PIN_3                = 3, 			 //!< PORT_F_PIN_3
    PORT_F_PIN_4                = 4,			 //!< PORT_F_PIN_4
	PORT_F_PIN_5                = 5,   			 //!< PORT_F_PIN_5
    PORT_F_PIN_6                = 6,			 //!< PORT_F_PIN_6
    PORT_F_PIN_7                = 7,			 //!< PORT_F_PIN_7
    PORT_F_PIN_8				= 8,             //!< PORT_F_PIN_8
	PORT_F_PIN_9				= 9,             //!< PORT_F_PIN_9
	PORT_F_PIN_10				= 10,            //!< PORT_F_PIN_10
	PORT_F_PIN_11				= 11,            //!< PORT_F_PIN_11
	PORT_F_PIN_12				= 12,            //!< PORT_F_PIN_12
	PORT_F_PIN_13				= 13,            //!< PORT_F_PIN_13
	PORT_F_PIN_14				= 14,            //!< PORT_F_PIN_14
	PORT_F_PIN_15				= 15,            //!< PORT_F_PIN_15
/********************************************************************/

/*********************** PORT G Pin Numbering ***********************/

	PORT_G_PIN_0                = 0,   			 //!< PORT_G_PIN_0
	PORT_G_PIN_1                = 1,	         //!< PORT_G_PIN_1
	PORT_G_PIN_2                = 2,   			 //!< PORT_G_PIN_2
	PORT_G_PIN_3                = 3, 		     //!< PORT_G_PIN_3
	PORT_G_PIN_4                = 4,   			 //!< PORT_G_PIN_4
	PORT_G_PIN_5                = 5,   			 //!< PORT_G_PIN_5
	PORT_G_PIN_6                = 6,   			 //!< PORT_G_PIN_6
	PORT_G_PIN_7                = 7,   			 //!< PORT_G_PIN_7
	PORT_G_PIN_8				= 8,             //!< PORT_G_PIN_8
	PORT_G_PIN_9				= 9,             //!< PORT_G_PIN_9
	PORT_G_PIN_10				= 10,            //!< PORT_G_PIN_10
	PORT_G_PIN_11				= 11,            //!< PORT_G_PIN_11
	PORT_G_PIN_12				= 12,            //!< PORT_G_PIN_12
	PORT_G_PIN_13				= 13,            //!< PORT_G_PIN_13
	PORT_G_PIN_14				= 14,            //!< PORT_G_PIN_14
	PORT_G_PIN_15				= 15,            //!< PORT_G_PIN_15
/********************************************************************/

/*********************** PORT H Pin Numbering ***********************/

/*
 * Note: Port H has only PH0 & PH1 and they mostly used as
 * OSC_IN & OSC_OUT Pins
*/
	PORT_H_PIN_0                = 0,   			 //!< PORT_H_PIN_0
	PORT_H_PIN_1                = 1   			 //!< PORT_H_PIN_1
/********************************************************************/

}Port_PinNumEnum;

#elif defined STM32F07
typedef enum{

/*********************** PORT A Pin Numbering ***********************/
    PORT_A_PIN_0                = 0, 			 //!< PORT_A_PIN_0
    PORT_A_PIN_1                = 1,			 //!< PORT_A_PIN_1
    PORT_A_PIN_2                = 2,			 //!< PORT_A_PIN_2
    PORT_A_PIN_3                = 3,			 //!< PORT_A_PIN_3
    PORT_A_PIN_4                = 4, 			 //!< PORT_A_PIN_4
    PORT_A_PIN_5                = 5, 		 	 //!< PORT_A_PIN_5
    PORT_A_PIN_6                = 6, 		 	 //!< PORT_A_PIN_6
    PORT_A_PIN_7                = 7, 		     //!< PORT_A_PIN_7
    PORT_A_PIN_8				= 8,           	 //!< PORT_A_PIN_8
	PORT_A_PIN_9				= 9,             //!< PORT_A_PIN_9
	PORT_A_PIN_10				= 10,            //!< PORT_A_PIN_10
	PORT_A_PIN_11				= 11,            //!< PORT_A_PIN_11
	PORT_A_PIN_12				= 12,            //!< PORT_A_PIN_12
	PORT_A_PIN_13				= 13,            //!< PORT_A_PIN_13
	PORT_A_PIN_14				= 14,            //!< PORT_A_PIN_14
	PORT_A_PIN_15				= 15,            //!< PORT_A_PIN_15
/********************************************************************/

/*********************** PORT B Pin Numbering ***********************/
    PORT_B_PIN_0                = 0,			 //!< PORT_B_PIN_0
    PORT_B_PIN_1                = 1,			 //!< PORT_B_PIN_1
    PORT_B_PIN_2                = 2,			 //!< PORT_B_PIN_2
    PORT_B_PIN_3                = 3,			 //!< PORT_B_PIN_3
    PORT_B_PIN_4                = 4,			 //!< PORT_B_PIN_4
    PORT_B_PIN_5                = 5,			 //!< PORT_B_PIN_5
    PORT_B_PIN_6                = 6,			 //!< PORT_B_PIN_6
    PORT_B_PIN_7                = 7,			 //!< PORT_B_PIN_7
    PORT_B_PIN_8				= 8,             //!< PORT_B_PIN_8
	PORT_B_PIN_9				= 9,             //!< PORT_B_PIN_9
	PORT_B_PIN_10				= 10,            //!< PORT_B_PIN_10
	PORT_B_PIN_11				= 11,            //!< PORT_B_PIN_11
	PORT_B_PIN_12				= 12,            //!< PORT_B_PIN_12
	PORT_B_PIN_13				= 13,            //!< PORT_B_PIN_13
	PORT_B_PIN_14				= 14,            //!< PORT_B_PIN_14
	PORT_B_PIN_15				= 15,            //!< PORT_B_PIN_15
/********************************************************************/

/*********************** PORT C Pin Numbering ***********************/
    PORT_C_PIN_0                = 0, 			 //!< PORT_B_PIN_0
    PORT_C_PIN_1                = 1,			 //!< PORT_B_PIN_1
    PORT_C_PIN_2                = 2,			 //!< PORT_B_PIN_2
    PORT_C_PIN_3                = 3,			 //!< PORT_B_PIN_3
    PORT_C_PIN_4                = 4,			 //!< PORT_B_PIN_4
    PORT_C_PIN_5                = 5,			 //!< PORT_B_PIN_5
    PORT_C_PIN_6                = 6,			 //!< PORT_B_PIN_6
    PORT_C_PIN_7                = 7,			 //!< PORT_B_PIN_7
    PORT_C_PIN_8				= 8,             //!< PORT_C_PIN_8
	PORT_C_PIN_9				= 9,             //!< PORT_C_PIN_9
	PORT_C_PIN_10				= 10,            //!< PORT_C_PIN_10
	PORT_C_PIN_11				= 11,            //!< PORT_C_PIN_11
	PORT_C_PIN_12				= 12,            //!< PORT_C_PIN_12
	PORT_C_PIN_13				= 13,            //!< PORT_C_PIN_13
	PORT_C_PIN_14				= 14,            //!< PORT_C_PIN_14
	PORT_C_PIN_15				= 15,            //!< PORT_C_PIN_15
/********************************************************************/

/*********************** PORT D Pin Numbering ***********************/
    PORT_D_PIN_0                = 0,			 //!< PORT_D_PIN_0
    PORT_D_PIN_1                = 1,			 //!< PORT_D_PIN_1
    PORT_D_PIN_2                = 2,  			 //!< PORT_D_PIN_2
    PORT_D_PIN_3                = 3,			 //!< PORT_D_PIN_3
    PORT_D_PIN_4                = 4,			 //!< PORT_D_PIN_4
    PORT_D_PIN_5                = 5,			 //!< PORT_D_PIN_5
    PORT_D_PIN_6                = 6,			 //!< PORT_D_PIN_6
    PORT_D_PIN_7                = 7,			 //!< PORT_D_PIN_7
    PORT_D_PIN_8				= 8,             //!< PORT_D_PIN_8
	PORT_D_PIN_9				= 9,             //!< PORT_D_PIN_9
	PORT_D_PIN_10				= 10,            //!< PORT_D_PIN_10
	PORT_D_PIN_11				= 11,            //!< PORT_D_PIN_11
	PORT_D_PIN_12				= 12,            //!< PORT_D_PIN_12
	PORT_D_PIN_13				= 13,            //!< PORT_D_PIN_13
	PORT_D_PIN_14				= 14,            //!< PORT_D_PIN_14
	PORT_D_PIN_15				= 15,            //!< PORT_D_PIN_15
/********************************************************************/

/*********************** PORT E Pin Numbering ***********************/

    PORT_E_PIN_0                = 0,			 //!< PORT_E_PIN_0
    PORT_E_PIN_1                = 1,			 //!< PORT_E_PIN_1
    PORT_E_PIN_2                = 2,			 //!< PORT_E_PIN_2
    PORT_E_PIN_3                = 3,			 //!< PORT_E_PIN_3
    PORT_E_PIN_4                = 4,			 //!< PORT_E_PIN_4
    PORT_E_PIN_5                = 5,			 //!< PORT_E_PIN_5
    PORT_E_PIN_6                = 6,			 //!< PORT_E_PIN_6
    PORT_E_PIN_7                = 7,			 //!< PORT_E_PIN_7
    PORT_E_PIN_8				= 8,             //!< PORT_E_PIN_8
	PORT_E_PIN_9				= 9,             //!< PORT_E_PIN_9
	PORT_E_PIN_10				= 10,            //!< PORT_E_PIN_10
	PORT_E_PIN_11				= 11,            //!< PORT_E_PIN_11
	PORT_E_PIN_12				= 12,            //!< PORT_E_PIN_12
	PORT_E_PIN_13				= 13,            //!< PORT_E_PIN_13
	PORT_E_PIN_14				= 14,            //!< PORT_E_PIN_14
	PORT_E_PIN_15				= 15,            //!< PORT_E_PIN_15
/********************************************************************/

/** Note: in STM32F407, There is no availability for PORTF & PORTG **/

/*********************** PORT H Pin Numbering ***********************/

	PORT_H_PIN_0                = 0,   			 //!< PORT_H_PIN_0
	PORT_H_PIN_1                = 1,   			 //!< PORT_H_PIN_1
	PORT_H_PIN_2                = 2,   			 //!< PORT_H_PIN_2
	PORT_H_PIN_3                = 3,   			 //!< PORT_H_PIN_3
	PORT_H_PIN_4                = 4,   			 //!< PORT_H_PIN_4
	PORT_H_PIN_5                = 5,   			 //!< PORT_H_PIN_5
	PORT_H_PIN_6                = 6,   			 //!< PORT_H_PIN_6
	PORT_H_PIN_7                = 7,		     //!< PORT_H_PIN_7
	PORT_H_PIN_8				= 8,             //!< PORT_H_PIN_8
	PORT_H_PIN_9				= 9,             //!< PORT_H_PIN_9
	PORT_H_PIN_10				= 10,            //!< PORT_H_PIN_10
	PORT_H_PIN_11				= 11,            //!< PORT_H_PIN_11
	PORT_H_PIN_12				= 12,            //!< PORT_H_PIN_12
	PORT_H_PIN_13				= 13,            //!< PORT_H_PIN_13
	PORT_H_PIN_14				= 14,            //!< PORT_H_PIN_14
	PORT_H_PIN_15				= 15             //!< PORT_H_PIN_15
/********************************************************************/


}Port_PinNumEnum;

#endif


/**
 * @enum	Port_PortNumEnum
 * @brief	Used to decide the Port Number
 */
typedef enum{

    PORTA,//!< PORTA
    PORTB,//!< PORTB
    PORTC,//!< PORTC
    PORTD,//!< PORTD
    PORTE,//!< PORTE
    PORTF,//!< PORTF
	PORTG,//!< PORTG
	PORTH //!< PORTH
}Port_PortNumEnum;

/**
 * @enum	Port_PinOutputSpeed
 *
 * @brief	Decide The speed of the output pin
 */
typedef enum{

	NO_SPEED,			//!< NO_SPEED
	LOW_SPEED = 0,      //!< LOW_SPEED
	MEDIUM_SPEED,  		//!< MEDIUM_SPEED
	HIGH_SPEED,    		//!< HIGH_SPEED
	VERY_HIGH_SPEED		//!< VERY_HIGH_SPEED
}Port_PinOutputSpeed;

/**
 * @typedef Port_PinType
 * Type definition for Port_PinType used by PORT APIs
 * Which used to decide which pin is used
 * Note: You can find these values @Port_PinNumEnum
*/

typedef uint8       Port_PinType;

/**
 * @typedef Port_PinModeType
 * Type definition for Port_PinModeType used by PORT APIs
 * Which used to decide the mode of the Pin
 * Note: You can find these values @Port_PinModeEnum
*/

typedef uint8       Port_PinModeType;



/****************** Defines used in Port_ConfigType variables *****************/

/* Define used to decide pin direction changeability on run time */
#define PIN_DIRECTION_CHANGEABILITY_ON      STD_ON
#define PIN_DIRECTION_CHANGEABILITY_OFF     STD_OFF

/* Defines used to decide Pin mode changeability during run time */
#define PIN_MODE_CHANGEABILITY_ON           STD_ON
#define PIN_MODE_CHANGEABILITY_OFF          STD_OFF

/* Defines used to set initial value for output pins             */
#define INITIAL_VALUE_HIGH                  STD_HIGH
#define INITIAL_VALUE_LOW                   STD_LOW

/* Define Used to check if the Pin is Analog mode or not         */
#define ANALOG_MODE_SELECTED                16

/* Define used to decide Output type							 */
#define OUTPUT_TYPE_OFF						STD_LOW
#define OUTPUT_TYPE_PUSH_PULL				STD_LOW
#define OUTPUT_TYPE_OPEN_DRAIN				STD_HIGH

/* Define used as Max number of pins in microcontroller 		 */
#ifdef STM32F429
#define MAX_NUM_OF_PINS						(114U)

#elif defined STM32F407
#define MAX_NUM_OF_PINS						(82U)
#endif

/*---------------- MODER Register Defined used ------------------*/
/* Define used as Mask value of MODER Register 					 */
#define MODER_REGISTER_MASK_VALUE			(0x00000003)

/* Define used as MODER Register Bits for every Pin				 */
#define MODER_REGISTER_BIT_NUMBERS			(2U)

/* Define used as MODER Register Values							 */
#define MODER_REGISTER_INPUT_VALUE			(0x00000000)
#define MODER_REGISTER_GENERAL_PURPOSE_OUT	(0x00000001)
#define MODER_REGISTER_ALTERNATIVE_FUNCTION	(0x00000002)
#define MODER_REGISTER_ANALOG_MODE			(0x00000003)
/*---------------------------------------------------------------*/

/*-------------- AFRL & AFRH Registers Defined used -------------*/

/* Defines used as Maximum Pins for every Register				 */
#define AFRL_REGISTER_MAX_PIN_NUM			(7U)
#define AFRH_REGISTER_MAX_PIN_NUM			(15U)

/* Define used as pin difference for High pins (Pin 8 till 15)   */
#define AFRH_REGISTER_PIN_DIFFERENCE 		(8U)

/* Define used as AFR Registers Bits for every Pin				*/
#define AFR_REGISTER_BIT_NUMBERS			(4U)

/* Define used as Mask value of AFR Registers 					 */
#define AFR_REGISTER_MASK_VALUE				(0x0000000F)
/*---------------------------------------------------------------*/

/*--------------- OSPEEDR Register Defined used -----------------*/

/* Define used as OSPEEDR Registers Bits for every Pin		     */
#define OSPEEDR_REGISTER_BIT_NUMBERS		(2U)

/* Define used as Mask value of OSPEEDR Registers 				 */
#define OSPEEDR_REGISTER_MASK_VALUE			(0x00000003)
/*---------------------------------------------------------------*/

/*---------------- PUDR Register Defined used -------------------*/

/* Define used as Mask value of PUDR Registers 					 */
#define PUDR_REGISTER_MASK_VALUE			(0x00000003)

/* Define used as PUDR Registers Bits for every Pin		     	 */
#define PUDR_REGISTER_BIT_NUMBERS			(2U)
/*---------------------------------------------------------------*/


/*--------------- OTYPER Register Defined used ------------------*/
#define OTYPER_REGISTER_MASK_VALUE			(0x000000001)
/*---------------------------------------------------------------*/

/* Define used as number of bits for every pin in PCTL Register  */
#define PORT_CONTROL_BIT_NUMBERS            (4U)
/*****************************************************************************/

/**
 * @struct  Port_ConfigChannel
 *
 * @brief   Used to set the configurations of a
 *          Specific pin in Port Module
 *
 * @var     Port_ConfigChannel::pinNum
 *          member 'pinNum' used to hold Pin & port number
 *          You can find its value @Port_PinNumEnum
 *
 * @var     Port_ConfigChannel::portNum
 *          member 'portNum' used to decide which port are used with the required pin
 *          You can find its vale @Port_PortNumEnum
 *
 * @var     Port_ConfigChannel::direction
 *          member 'direction' used to decide if the pin is input or output
 *          You can find its value @Port_PinDirectionType
 *
 * @var     Port_ConfigChannel::mode
 *          member 'mode' used to decide which mode is used (GPIO or any alternative function)
 *          You can find its value @Port_PinModeEnum
 *
 * @var     Port_ConfigChannel::resistor
 *          member 'resistor' used to decide if internal resistor is used or not and
 *          its mode if used (Pull-up or Pull-Down)
 *          You can find its value @Port_InternalResistor
 *
 * @var     Port_ConfigChannel::pinDirection_Changable
 *          member 'pinDirection_Changable' used to decide if the pin direction can be
 *          Changeable in run time or not
 *          You can find its value @PIN_DIRECTION_CHANGEABILITY
 *
 * @var     Port_ConfigChannel::pinMode_Changable
 *          member 'pinMode_Changable' used to decide if the pin mode can be changeable
 *          during run time or not
 *          You can find its value @PIN_MODE_CHANGEABILITY
 *
 * @var     Port_ConfigChannel::initialValue
 *          member 'initialValue' used to set an initial value for output pins
 *          You can find its value @INITIAL_VALUE
 *
 * @var     Port_ConfigChannel::speed
 * 			member 'speed' used to decide what speed the o/p will operate
 *		    You can find its value @Port_PinOutputSpeed
 *
 *
 * @var     Port_ConfigChannel::outputType
 * 			member 'outputType' used to decide if the output is push pull or open drain
 *			You can find its value @OUTPUT_TYPE
 *
 */
typedef struct{

    Port_PinType                pinNum;                    /* member 'pinNum' used to hold Pin & port number
                                                              You can find its value @Port_PinNumEnum  */

    Port_PortNumEnum            portNum;                   /* member 'portNum' used to decide which port are used with the required pin
                                                              You can find its vale @Port_PortNumEnum */

    Port_PinDirectionType       direction;                 /* member 'direction' used to decide if the pin is input or output
                                                              You can find its value @Port_PinDirectionType */

    Port_PinModeType            mode;                      /* member 'direction' used to decide if the pin is input or output
                                                              You can find its value @Port_PinDirectionType */

    Port_InternalResistor       resistor;                  /* member 'mode' used to decide which mode is used
                                                              (GPIO or any alternative function)
                                                              You can find its value @Port_PinModeEnum */

    uint8                       pinDirection_Changeable;   /* member 'pinDirection_Changable' used to decide if the pin direction
                                                              can be Changeable in run time or not
                                                              You can find its value @PIN_DIRECTION_CHANGEABILITY */

    uint8                       pinMode_Changeable;         /* member 'pinMode_Changable' used to decide if the pin mode
                                                              can be changeable during run time or not
                                                              You can find its value @PIN_MODE_CHANGEABILITY */

    uint8                       initialValue;              /* member 'initialValue' used to set an initial value for output pins
                                                              You can find its value @INITIAL_VALUE */

    Port_PinOutputSpeed			speed;					   /* member 'speed' used to decide what speed the o/p will operate
     	 	 	 	 	 	 	 	 	 	 	 	 	 	  You can find its value @Port_PinOutputSpeed */

    uint8						outputType;				   /* member 'outputType' used to decide if the output is push pull or open drain
     	 	 	 	 	 	 	 	 	 	 	 	 	 	  You can find its value @OUTPUT_TYPE */


}Port_ConfigChannel;


/**
 * @struct Port_ConfigType
 *
 * @brief This structure holds an array of structures
 *        that holds the configurations of the pins
 *
 * @note  Unused pins shall configured with the initial value
 *        which got from TM4C123GH6PM data sheet, GPIO chapter
 *        so that, PORT_CONFIGURED_CHANNELS shall equal 36 in TM4C123GH6PM
 *
 * @var   Port_ConfigType::portChannels
 *        member 'portChannels' used as an array to hold the configurations of
 *        the pins
 */
typedef struct{

    Port_ConfigChannel          portChannels [PORT_CONFIGURED_CHANNLES]; /* member 'portChannels' used as an array to
                                                                            hold the configurations of the pins */
}Port_ConfigType;
/********************************************************************************/


/*******************************************************************************
 *                              Function Prototypes                             *
 *******************************************************************************/

/* Function used to initiate Port Module and configure the Pins of MC */
void Port_Init(const Port_ConfigType* ConfigPtr);

/* Static check if this API is needed or not */
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/* Function used to set pin direction during run time */
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
#endif

/* Function used to refresh the direction of all configured ports to configured direction */
void Port_RefreshPortDirection(void);

/* Static check if this API is needed or not */
#if(PORT_VERSION_INFO_API == STD_ON)
/* Function used to get Port Module Id, Vendor Id and Vendor specific version Number */
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

/* Function used to set port pin mode during run time */
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
/********************************************************************************/


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Dio and other modules */
extern const Port_ConfigType Port_Configuration;

/********************************************************************************/

#endif /* PORT_H_ */
