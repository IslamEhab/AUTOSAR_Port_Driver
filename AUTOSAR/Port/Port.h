 /******************************************************************************
 *
 * Module:      Port
 *
 * File Name:   Port.h
 *
 * Description: Header file for Port Module on TM4C123GH6PM Microcontroller
 *
 * Version      1.0.0
 *
 * Author:      Islam Ehab
 *
 * Date:        10/12/2020
 *
 ******************************************************************************/

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
#define PORT_AR_RELEASE_MINOR_VERSION           (0U)
#define PORT_AR_RELEASE_PATCH_VERSION           (3U)


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

/* DET Code for Port_Init called with wrong Parameter            */
#define PORT_E_PARAM_CONFIG                     (uint8)0x0C

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


/* Type definition for Port_PinDirectionType used by PORT APIs */
typedef enum{

    PORT_PIN_IN,    //!< PORT_PIN_IN
    PORT_PIN_OUT,   //!< PORT_PIN_OUT
    PORT_PIN_DEFAULT//!< PORT_PIN_DEFAULT

}Port_PinDirectionType;

/* Used to decide the mode of internal pull up or to disable it at all */
typedef enum{

    OFF,     //!< OFF
    PULL_UP, //!< PULL_UP
    PULL_DOWN//!< PULL_DOWN

}Port_InternalResistor;



/**
 * This enum has all the alternative function values of the TM4C123GH6PM
 * to be used with Port_PinModeType data type
 */
typedef enum{

/********* Alternative function = 0,  Pin used as DIO  **************/
    DIO_PIN                     = 0, //!< DIO_PIN
/********************************************************************/

/******** Alternative Function  = 1 For all Pins that have it *******/
    PORT_A_PIN_0_AF1_U0RX       = 1, //!< PORT_A_PIN_0_AF1_U0RX
    PORT_A_PIN_1_AF1_U0TX       = 1, //!< PORT_A_PIN_1_AF1_U0TX

    PORT_B_PIN_0_AF1_U1RX       = 1, //!< PORT_B_PIN_0_AF1_U1RX
    PORT_B_PIN_1_AF1_U1TX       = 1, //!< PORT_B_PIN_1_AF1_U1TX

    PORT_C_PIN_4_AF1_U4RX       = 1, //!< PORT_C_PIN_4_AF1_U4RX
    PORT_C_PIN_5_AF1_U4TX       = 1, //!< PORT_C_PIN_5_AF1_U4TX
    PORT_C_PIN_6_AF1_U3RX       = 1, //!< PORT_C_PIN_6_AF1_U3RX
    PORT_C_PIN_7_AF1_U3TX       = 1, //!< PORT_C_PIN_7_AF1_U3TX

    PORT_D_PIN_0_AF1_SSI3CLK    = 1, //!< PORT_D_PIN_0_AF1_SSI3CLK
    PORT_D_PIN_1_AF1_SSI3FSS    = 1, //!< PORT_D_PIN_1_AF1_SSI3FSS
    PORT_D_PIN_2_AF1_SSI3RX     = 1, //!< PORT_D_PIN_2_AF1_SSI3RX
    PORT_D_PIN_3_AF1_SSI3TX     = 1, //!< PORT_D_PIN_3_AF1_SSI3TX
    PORT_D_PIN_4_AF1_U6RX       = 1, //!< PORT_D_PIN_4_AF1_U6RX
    PORT_D_PIN_5_AF1_U6TX       = 1, //!< PORT_D_PIN_5_AF1_U6TX
    PORT_D_PIN_6_AF1_U2RX       = 1, //!< PORT_D_PIN_6_AF1_U2RX
    PORT_D_PIN_7_AF1_U2TX       = 1, //!< PORT_D_PIN_7_AF1_U2TX

    PORT_E_PIN_0_AF1_U7RX       = 1, //!< PORT_E_PIN_0_AF1_U7RX
    PORT_E_PIN_1_AF1_U7TX       = 1, //!< PORT_E_PIN_1_AF1_U7TX
    PORT_E_PIN_4_AF1_U5RX       = 1, //!< PORT_E_PIN_4_AF1_U5RX
    PORT_E_PIN_5_AF1_U5TX       = 1, //!< PORT_E_PIN_5_AF1_U5TX

    PORT_F_PIN_0_AF1_U1RTS      = 1, //!< PORT_F_PIN_0_AF1_U1RTS
    PORT_F_PIN_1_AF1_U1CTS      = 1, //!< PORT_F_PIN_1_AF1_U1CTS
/********************************************************************/

/******** Alternative Function  = 2 For all Pins that have it *******/
    PORT_A_PIN_2_AF2_SSI0CLK    = 2, //!< PORT_A_PIN_2_AF2_SSI0CLK
    PORT_A_PIN_3_AF2_SSI0FSS    = 2, //!< PORT_A_PIN_3_AF2_SSI0FSS
    PORT_A_PIN_4_AF2_SSI0RX     = 2, //!< PORT_A_PIN_4_AF2_SSI0RX
    PORT_A_PIN_5_AF2_SSI0TX     = 2, //!< PORT_A_PIN_5_AF2_SSI0TX

    PORT_B_PIN_4_AF2_SSI2CLK    = 2, //!< PORT_B_PIN_4_AF2_SSI2CLK
    PORT_B_PIN_5_AF2_SSI2FSS    = 2, //!< PORT_B_PIN_5_AF2_SSI2FSS
    PORT_B_PIN_6_AF2_SSI2RX     = 2, //!< PORT_B_PIN_6_AF2_SSI2RX
    PORT_B_PIN_7_AF2_SSI2TX     = 2, //!< PORT_B_PIN_7_AF2_SSI2TX

    PORT_C_PIN_4_AF2_U1RX       = 2, //!< PORT_C_PIN_4_AF2_U1RX
    PORT_C_PIN_5_AF2_U1TX       = 2, //!< PORT_C_PIN_5_AF2_U1TX

    PORT_D_PIN_0_AF2_SSI1CLK    = 2, //!< PORT_D_PIN_0_AF2_SSI1CLK
    PORT_D_PIN_1_AF2_SSI1FSS    = 2, //!< PORT_D_PIN_1_AF2_SSI1FSS
    PORT_D_PIN_2_AF2_SSI1RX     = 2, //!< PORT_D_PIN_2_AF2_SSI1RX
    PORT_D_PIN_3_AF2_SSI1TX     = 2, //!< PORT_D_PIN_3_AF2_SSI1TX

    PORT_F_PIN_0_AF2_SSI1RX     = 2, //!< PORT_F_PIN_0_AF2_SSI1RX
    PORT_F_PIN_1_AF2_SSI1TX     = 2, //!< PORT_F_PIN_1_AF2_SSI1TX
    PORT_F_PIN_2_AF2_SSI1CLK    = 2, //!< PORT_F_PIN_2_AF2_SSI1CLK
    PORT_F_PIN_3_AF2_SSI1FSS    = 2, //!< PORT_F_PIN_3_AF2_SSI1FSS
/********************************************************************/

/******** Alternative Function  = 3 For all Pins that have it *******/
    PORT_A_PIN_6_AF3_I2C1SCL    = 3, //!< PORT_A_PIN_6_AF3_I2C1SCL
    PORT_A_PIN_7_AF3_I2C1SDA    = 3, //!< PORT_A_PIN_7_AF3_I2C1SDA

    PORT_B_PIN_2_AF3_I2C0SCL    = 3, //!< PORT_B_PIN_2_AF3_I2C0SCL
    PORT_B_PIN_3_AF3_I2C0SDA    = 3, //!< PORT_B_PIN_3_AF3_I2C0SDA


    PORT_D_PIN_0_AF3_I2C3SCL    = 3, //!< PORT_D_PIN_0_AF3_I2C3SCL
    PORT_D_PIN_1_AF3_I2C3SDA    = 3, //!< PORT_D_PIN_1_AF3_I2C3SDA

    PORT_E_PIN_4_AF3_I2C2SCL    = 3, //!< PORT_E_PIN_4_AF3_I2C2SCL
    PORT_E_PIN_5_AF3_I2C2SDA    = 3, //!< PORT_E_PIN_5_AF3_I2C2SDA

    PORT_F_PIN_0_AF3_CAN0RX     = 3, //!< PORT_F_PIN_0_AF3_CAN0RX
    PORT_F_PIN_3_AF3_CAN0TX     = 3, //!< PORT_F_PIN_3_AF3_CAN0TX
/********************************************************************/

/******** Alternative Function  = 4 For all Pins that have it *******/

    PORT_B_PIN_4_AF4_M0PWM2     = 4, //!< PORT_B_PIN_4_AF4_M0PWM2
    PORT_B_PIN_5_AF4_M0PWM3     = 4, //!< PORT_B_PIN_5_AF4_M0PWM3
    PORT_B_PIN_6_AF4_M0PWM0     = 4, //!< PORT_B_PIN_6_AF4_M0PWM0
    PORT_B_PIN_7_AF4_M0PWM1     = 4, //!< PORT_B_PIN_7_AF4_M0PWM1

    PORT_C_PIN_4_AF4_M0PWM6     = 4, //!< PORT_C_PIN_4_AF4_M0PWM6
    PORT_C_PIN_5_AF4_M0PWM7     = 4, //!< PORT_C_PIN_5_AF4_M0PWM7

    PORT_D_PIN_0_AF4_M0PWM6     = 4, //!< PORT_D_PIN_0_AF4_M0PWM6
    PORT_D_PIN_1_AF4_M0PWM7     = 4, //!< PORT_D_PIN_1_AF4_M0PWM7
    PORT_D_PIN_2_AF4_M0FAULT0   = 4, //!< PORT_D_PIN_2_AF4_M0FAULT0
    PORT_D_PIN_6_AF4_M0FAULT0   = 4, //!< PORT_D_PIN_6_AF4_M0FAULT0

    PORT_E_PIN_4_AF4_M0PWM4     = 4, //!< PORT_E_PIN_4_AF4_M0PWM4
    PORT_E_PIN_5_AF4_M0PWM5     = 4, //!< PORT_E_PIN_5_AF4_M0PWM5

    PORT_F_PIN_2_AF4_M0FAULT0   = 4, //!< PORT_F_PIN_2_AF4_M0FAULT0
/********************************************************************/

/******** Alternative Function  = 5 For all Pins that have it *******/
    PORT_A_PIN_6_AF5_M1PWM2     = 5, //!< PORT_A_PIN_6_AF5_M1PWM2
    PORT_A_PIN_7_AF5_M1PWM3     = 5, //!< PORT_A_PIN_7_AF5_M1PWM3

    PORT_D_PIN_0_AF5_M1PWM0     = 5, //!< PORT_D_PIN_0_AF5_M1PWM0
    PORT_D_PIN_1_AF5_M1PWM1     = 5, //!< PORT_D_PIN_1_AF5_M1PWM1

    PORT_E_PIN_4_AF5_M1PWM2     = 5, //!< PORT_E_PIN_4_AF5_M1PWM2
    PORT_E_PIN_5_AF5_M1PWM3     = 5, //!< PORT_E_PIN_5_AF5_M1PWM3

    PORT_F_PIN_0_AF5_M1PWM4     = 5, //!< PORT_F_PIN_0_AF5_M1PWM4
    PORT_F_PIN_1_AF5_M1PWM5     = 5, //!< PORT_F_PIN_1_AF5_M1PWM5
    PORT_F_PIN_2_AF5_M1PWM6     = 5, //!< PORT_F_PIN_2_AF5_M1PWM6
    PORT_F_PIN_3_AF5_M1PWM7     = 5, //!< PORT_F_PIN_3_AF5_M1PWM7
    PORT_F_PIN_4_AF5_M1FAULT0   = 5, //!< PORT_F_PIN_4_AF5_M1FAULT0
/********************************************************************/

/******** Alternative Function  = 6 For all Pins that have it *******/
    PORT_C_PIN_4_AF6_IDX1       = 6, //!< PORT_C_PIN_4_AF6_IDX1
    PORT_C_PIN_5_AF6_PHA1       = 6, //!< PORT_C_PIN_5_AF6_PHA1
    PORT_C_PIN_6_AF6_PHB1       = 6, //!< PORT_C_PIN_6_AF6_PHB1

    PORT_D_PIN_3_AF6_IDX0       = 6, //!< PORT_D_PIN_3_AF6_IDX0
    PORT_D_PIN_6_AF6_PHA0       = 6, //!< PORT_D_PIN_6_AF6_PHA0
    PORT_D_PIN_7_AF6_PHB0       = 6, //!< PORT_D_PIN_7_AF6_PHB0

    PORT_F_PIN_0_AF6_PHA0       = 6, //!< PORT_F_PIN_0_AF6_PHA0
    PORT_F_PIN_1_AF6_PHB0       = 6, //!< PORT_F_PIN_1_AF6_PHB0
    PORT_F_PIN_4_AF6_IDX0       = 6, //!< PORT_F_PIN_4_AF6_IDX0
/********************************************************************/

/******** Alternative Function  = 7 For all Pins that have it *******/
    PORT_B_PIN_0_AF7_T2CCP0     = 7, //!< PORT_B_PIN_0_AF7_T2CCP0
    PORT_B_PIN_1_AF7_T2CCP1     = 7, //!< PORT_B_PIN_1_AF7_T2CCP1
    PORT_B_PIN_2_AF7_T3CCP0     = 7, //!< PORT_B_PIN_2_AF7_T3CCP0
    PORT_B_PIN_3_AF7_T3CCP1     = 7, //!< PORT_B_PIN_3_AF7_T3CCP1
    PORT_B_PIN_4_AF7_T1CCP0     = 7, //!< PORT_B_PIN_4_AF7_T1CCP0
    PORT_B_PIN_5_AF7_T1CCP1     = 7, //!< PORT_B_PIN_5_AF7_T1CCP1
    PORT_B_PIN_6_AF7_T0CCP0     = 7, //!< PORT_B_PIN_6_AF7_T0CCP0
    PORT_B_PIN_7_AF7_T0CCP1     = 7, //!< PORT_B_PIN_7_AF7_T0CCP1

    PORT_C_PIN_4_AF7_WT0CCP0    = 7, //!< PORT_C_PIN_4_AF7_WT0CCP0
    PORT_C_PIN_5_AF7_WT0CCP1    = 7, //!< PORT_C_PIN_5_AF7_WT0CCP1
    PORT_C_PIN_6_AF7_WT1CCP0    = 7, //!< PORT_C_PIN_6_AF7_WT1CCP0
    PORT_C_PIN_7_AF7_WT1CCP1    = 7, //!< PORT_C_PIN_7_AF7_WT1CCP1

    PORT_D_PIN_0_AF7_WT2CCP0    = 7, //!< PORT_D_PIN_0_AF7_WT2CCP0
    PORT_D_PIN_1_AF7_WT2CCP1    = 7, //!< PORT_D_PIN_1_AF7_WT2CCP1
    PORT_D_PIN_2_AF7_WT3CCP0    = 7, //!< PORT_D_PIN_2_AF7_WT3CCP0
    PORT_D_PIN_3_AF7_WT3CCP1    = 7, //!< PORT_D_PIN_3_AF7_WT3CCP1
    PORT_D_PIN_4_AF7_WT4CCP0    = 7, //!< PORT_D_PIN_4_AF7_WT4CCP0
    PORT_D_PIN_5_AF7_WT4CCP1    = 7, //!< PORT_D_PIN_5_AF7_WT4CCP1
    PORT_D_PIN_6_AF7_WT5CCP0    = 7, //!< PORT_D_PIN_6_AF7_WT5CCP0
    PORT_D_PIN_7_AF7_WT5CCP1    = 7, //!< PORT_D_PIN_7_AF7_WT5CCP1

    PORT_F_PIN_0_AF7_T0CCP0     = 7, //!< PORT_F_PIN_0_AF7_T0CCP0
    PORT_F_PIN_1_AF7_T0CCP1     = 7, //!< PORT_F_PIN_1_AF7_T0CCP1
    PORT_F_PIN_2_AF7_T1CCP0     = 7, //!< PORT_F_PIN_2_AF7_T1CCP0
    PORT_F_PIN_3_AF7_T1CCP1     = 7, //!< PORT_F_PIN_3_AF7_T1CCP1
    PORT_F_PIN_4_AF7_T2CCP0     = 7, //!< PORT_F_PIN_4_AF7_T2CCP0
/********************************************************************/

/******** Alternative Function  = 8 For all Pins that have it *******/
    PORT_A_PIN_0_AF8_CAN1RX     = 8, //!< PORT_A_PIN_0_AF8_CAN1RX
    PORT_A_PIN_1_AF8_CAN1TX     = 8, //!< PORT_A_PIN_1_AF8_CAN1TX

    PORT_B_PIN_4_AF8_CAN0RX     = 8, //!< PORT_B_PIN_4_AF8_CAN0RX
    PORT_B_PIN_5_AF8_CAN0TX     = 8, //!< PORT_B_PIN_5_AF8_CAN0TX

    PORT_C_PIN_4_AF8_U1RTS      = 8, //!< PORT_C_PIN_4_AF8_U1RTS
    PORT_C_PIN_5_AF8_U1CTS      = 8, //!< PORT_C_PIN_5_AF8_U1CTS
    PORT_C_PIN_6_AF8_USB0EPEN   = 8, //!< PORT_C_PIN_6_AF8_USB0EPEN
    PORT_C_PIN_7_AF8_USB0PFLT   = 8, //!< PORT_C_PIN_7_AF8_USB0PFLT

    PORT_D_PIN_2_AF8_USB0EPEN   = 8, //!< PORT_D_PIN_2_AF8_USB0EPEN
    PORT_D_PIN_3_AF8_USB0PFLT   = 8, //!< PORT_D_PIN_3_AF8_USB0PFLT
    PORT_D_PIN_7_AF8_NMI        = 8, //!< PORT_D_PIN_7_AF8_NMI

    PORT_E_PIN_4_AF8_CAN0RX     = 8, //!< PORT_E_PIN_4_AF8_CAN0RX
    PORT_E_PIN_5_AF8_CAN0TX     = 8, //!< PORT_E_PIN_5_AF8_CAN0TX

    PORT_F_PIN_0_AF8_NMI        = 8, //!< PORT_F_PIN_0_AF8_NMI
    PORT_F_PIN_4_AF8_USB0EPEN   = 8, //!< PORT_F_PIN_4_AF8_USB0EPEN
/*********************************************************************/

/******** Alternative Function  = 9 For all Pins that have it ********/
    PORT_F_PIN_0_AF9_C0O        = 9, //!< PORT_F_PIN_0_AF9_C0O
    PORT_F_PIN_1_AF9_C01        = 9, //!< PORT_F_PIN_1_AF9_C01
/*********************************************************************/

/******** Alternative Function  = 14 For all Pins that have it *******/
    PORT_F_PIN_1_AF14_TRD1      = 14,//!< PORT_F_PIN_1_AF14_TRD1
    PORT_F_PIN_2_AF14_TRD0      = 14,//!< PORT_F_PIN_2_AF14_TRD0
    PORT_F_PIN_3_AF14_TRCLK     = 14,//!< PORT_F_PIN_3_AF14_TRCLK
/*********************************************************************/

/********       Analog mode = 15 For all Pins that have it     *******/

    PORT_B_PIN_4_AIN_10         = 15,//!< PORT_B_PIN_4_AIN_10
    PORT_B_PIN_5_AIN_11         = 15,//!< PORT_B_PIN_5_AIN_11

    PORT_D_PIN_0_AIN_7          = 15,//!< PORT_D_PIN_0_AIN_7
    PORT_D_PIN_1_AIN_6          = 15,//!< PORT_D_PIN_1_AIN_6
    PORT_D_PIN_2_AIN_5          = 15,//!< PORT_D_PIN_2_AIN_5
    PORT_D_PIN_3_AIN_4          = 15,//!< PORT_D_PIN_3_AIN_4

    PORT_E_PIN_0_AIN_3          = 15,//!< PORT_E_PIN_0_AIN_3
    PORT_E_PIN_2_AIN_2          = 15,//!< PORT_E_PIN_2_AIN_2
    PORT_E_PIN_3_AIN_0          = 15,//!< PORT_E_PIN_3_AIN_0
    PORT_E_PIN_4_AIN_9          = 15,//!< PORT_E_PIN_4_AIN_9
    PORT_E_PIN_5_AIN_8          = 15,//!< PORT_E_PIN_5_AIN_8

/*********************************************************************/


/****** Analog Comparators mode = 16 For all Pins that have it *******/

    PORT_C_PIN_4_C1_MINUS       = 16,//!< PORT_C_PIN_4_C1_MINUS
    PORT_C_PIN_5_C1_PLUS        = 16,//!< PORT_C_PIN_5_C1_PLUS
    PORT_C_PIN_6_C0_MINUS       = 16,//!< PORT_C_PIN_6_C0_MINUS
    PORT_C_PIN_7_C0_PLUS        = 16,//!< PORT_C_PIN_7_C0_PLUS

/*********************************************************************/

/********        USB mode = 17 For all Pins that have it       *******/

    PORT_D_PIN_4_USB0DM         = 17,//!< PORT_D_PIN_4_USB0DM
    PORT_D_PIN_4_USB0DP         = 17 //!< PORT_D_PIN_4_USB0DP

/*********************************************************************/
}Port_PinModeEnum;



/**
 * This enum used to numbering the pins on the TM4C123GH6PM
 */
typedef enum{

/*********************** PORT A Pin Numbering ***********************/
    PORT_A_PIN_0                = 0, //!< PORT_A_PIN_0
    PORT_A_PIN_1                = 1, //!< PORT_A_PIN_1
    PORT_A_PIN_2                = 2, //!< PORT_A_PIN_2
    PORT_A_PIN_3                = 3, //!< PORT_A_PIN_3
    PORT_A_PIN_4                = 4, //!< PORT_A_PIN_4
    PORT_A_PIN_5                = 5, //!< PORT_A_PIN_5
    PORT_A_PIN_6                = 6, //!< PORT_A_PIN_6
    PORT_A_PIN_7                = 7, //!< PORT_A_PIN_7
/********************************************************************/

/*********************** PORT B Pin Numbering ***********************/
    PORT_B_PIN_0                = 0, //!< PORT_B_PIN_0
    PORT_B_PIN_1                = 1, //!< PORT_B_PIN_1
    PORT_B_PIN_2                = 2,//!< PORT_B_PIN_2
    PORT_B_PIN_3                = 3,//!< PORT_B_PIN_3
    PORT_B_PIN_4                = 4,//!< PORT_B_PIN_4
    PORT_B_PIN_5                = 5,//!< PORT_B_PIN_5
    PORT_B_PIN_6                = 6,//!< PORT_B_PIN_6
    PORT_B_PIN_7                = 7,//!< PORT_B_PIN_7
/********************************************************************/

/*********************** PORT C Pin Numbering ***********************/
/*
 * Note: pins From PC0 -> PC3 used for JTAG, so that they removed
 * from the Enum to avoid using them by mistake
*/

    PORT_C_PIN_4                = 4,//!< PORT_C_PIN_4
    PORT_C_PIN_5                = 5,//!< PORT_C_PIN_5
    PORT_C_PIN_6                = 6,//!< PORT_C_PIN_6
    PORT_C_PIN_7                = 7,//!< PORT_C_PIN_7
/********************************************************************/

/*********************** PORT D Pin Numbering ***********************/
    PORT_D_PIN_0                = 0,//!< PORT_D_PIN_0
    PORT_D_PIN_1                = 1,//!< PORT_D_PIN_1
    PORT_D_PIN_2                = 2,//!< PORT_D_PIN_2
    PORT_D_PIN_3                = 3,//!< PORT_D_PIN_3
    PORT_D_PIN_4                = 4,//!< PORT_D_PIN_4
    PORT_D_PIN_5                = 5,//!< PORT_D_PIN_5
    PORT_D_PIN_6                = 6,//!< PORT_D_PIN_6
    PORT_D_PIN_7                = 7,//!< PORT_D_PIN_7
/********************************************************************/

/*********************** PORT E Pin Numbering ***********************/
/*
 * Note: There are no Physical pins From PE6 -> PE7 so that they're
 * removed from Enum
*/
    PORT_E_PIN_0                = 0,//!< PORT_E_PIN_0
    PORT_E_PIN_1                = 1,//!< PORT_E_PIN_1
    PORT_E_PIN_2                = 2,//!< PORT_E_PIN_2
    PORT_E_PIN_3                = 3,//!< PORT_E_PIN_3
    PORT_E_PIN_4                = 4,//!< PORT_E_PIN_4
    PORT_E_PIN_5                = 5,//!< PORT_E_PIN_5
/********************************************************************/

/*********************** PORT F Pin Numbering ***********************/
/*
 * Note: There are no Physical pins From PF5 -> PF7 so that they're
 * removed from Enum
*/
    PORT_F_PIN_0                = 0,//!< PORT_F_PIN_0
    PORT_F_PIN_1                = 1,//!< PORT_F_PIN_1
    PORT_F_PIN_2                = 2,//!< PORT_F_PIN_2
    PORT_F_PIN_3                = 3,//!< PORT_F_PIN_3
    PORT_F_PIN_4                = 4 //!< PORT_F_PIN_4
/********************************************************************/
}Port_PinNumEnum;

/**
 * Used to decide the Port Number
 */
typedef enum{

    PORTA,//!< PORTA
    PORTB,//!< PORTB
    PORTC,//!< PORTC
    PORTD,//!< PORTD
    PORTE,//!< PORTE
    PORTF //!< PORTF

}Port_PortNumEnum;

/*
 * Type definition for Port_PinType used by PORT APIs
 * Which used to decide which pin is used
 * Note: You can find these values @Port_PinNumEnum
*/

typedef uint8       Port_PinType;

/*
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
#define ANALOG_MODE_SELECTED                15

/*
 * Define used to enable/disable slew rate
 * as if it is an AUTOSAR Requirement
*/
#define SLEW_RATE_ENABLE                    STD_ON
#define SLEW_RATE_DISABLE                   STD_OFF

/*
 * Defines used for JTAG Pins in PortC
 * used as defines not in the enum to avoid using them
 * Chosed from 100 till 103 to avoid using them
*/
#define PORT_C_PIN_0_JTAG                   (100U)
#define PORT_C_PIN_1_JTAG                   (101U)
#define PORT_C_PIN_2_JTAG                   (102U)
#define PORT_C_PIN_3_JTAG                   (103U)

/* Define used as the Unlock value of the LOCK Register          */
#define LOCK_REGISTER_UNLOCK_VALUE          (0x4C4F434B)

/* Define used as mask value for PCTL Register */
#define PORT_CONTROL_MASK_VALUE             (0x0000000F)

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
 * @var     Port_ConfigChannel::slewRate
 *          member 'slewRate' used to decide if Slew rate is enabled/disabled for the pin
 *          You can find its value @SLEW_RATE
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

    uint8                       slewRate;                  /* member 'slewRate' used to decide if Slew rate is enabled/disabled for the pin
                                                              You can find its value @SLEW_RATE */


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
